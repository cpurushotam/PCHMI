/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Declares COMM Thread - responsible for  state machine and its transition

--------------------------- REVISION HISTORY ------------------------------
rev1: 26/05/2023 - Initial implementation.
rev2: 10/08/2023 - Implementation of welder discovery related code.
rev3: 16/10/2023 - Updated HMI Platform config status

***************************************************************************/

#include "CommThread.h"
#include "WDSServer.h"
#include "CommPeerWrapper.h"

/*****************************************************************************
* \brief   - Initilize communication thread class
*            1. Initialize Peer ID with received parameter.
*            2. Initialize Current State with Start request.
*            3. Initialize Peer Info object
*
* \param   - int        WeldorId
*            QObject    *parent
*
* \return  - None
******************************************************************************/
CommThread::CommThread(int PeerId, QObject *parent)
{
    // Initialize Peer ID with received parameter.
    m_PeerId = PeerId;

    // Initialize Current State with Start request.
    m_CurrentState = COMM_START_REQUEST;

    // Initialize log ID
    this->m_LogId = Logger::enroll(this);

    /* Created instance of background communication class. */
    m_PtrBackComm = new BgCommThread();
}

/*****************************************************************************
* \brief   - COMM thread is responsible for running logic related communication
*            between ASC and HMI
*            1. Waiting for start request -  Create instance of CommClass.
*            2. Start communication with peer
*            3. if any failure in starting communication the raise event and alarm.
*            4. Process on Tx/Rx frames.
*            5. Disconnect from peer if any failure in process.
*
* \param   - None.
*
* \return  - void
******************************************************************************/
void CommThread::run()
{
    int status;
    int RetryCount = 0;
    char BioPort [5]={0};

    PlatformConfig *PlatformConfigInt = nullptr;

    while(1)
    {
        /* Implementation State machine */
        switch (m_CurrentState)
        {
            case COMM_START_REQUEST:
            {
                // Log general information
                snprintf ( this->m_LogBuffer, buff_size_config, "Comm %d wait for start request.", m_PeerId);
                Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, (this->m_LogBuffer));

                // Initialize Peer Info object
                try{
                    /* Created instance of peer info class. */
                    m_PtrPeerInfo = new PeerInfo();

                    // Insert Peer Info object into map
                    CommPeerWrapper::SetPeerData(m_PeerId, m_PtrPeerInfo);
                } catch (std::exception &e)
                {
                    // Log alarm
                    snprintf ( this->m_LogBuffer, buff_size_config, "PeerInfo:%s", e.what() );
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                }

                // Read any error to make background communication ideal
                msleep(BG_CYCLIC_TIME);
                m_PtrBackComm->ReadError();

                if (m_PtrPeerInfo->GetCommSSLConfig()->RoleIs == CLIENT)
                {
                    /* Waiting for connection start request and connection details of discovered peer*/
                    strcpy(m_PeerIpAddr, m_PtrPeerInfo->WaitTriggerStartRequest());
                }

                // Log Event
                snprintf ( this->m_LogBuffer, buff_size_config, "Comm Thread %d Triggered.", m_PeerId);
                Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));

                try
                {
                    /* Created instance of data interface config class. */
                    m_ptrDataInterfaceConfig = new DataInterfaceConfig_HMI(m_PeerId, m_PtrPeerInfo->GetActiveConfiguration());

                    PlatformConfigInt = dynamic_cast<PlatformConfig*> (m_ptrDataInterfaceConfig->GetCommDataConfig(m_PeerId)->TXConfig[std::make_pair(MB_ID_PLATFORM_CONFIG,SUB_ID_PLATFORM_CONFIG)]);
                    m_PtrPeerInfo->SetPlatformConfigState(PlatformConfigInt->GetConfigState());

                    // copy configure port in bio_config to create DestinationIPandPort
                    strcpy(BioPort, m_PtrPeerInfo->GetCommSSLConfig()->DestinationIPandPort);

                    /* Use this for configuring destination IP and Port */
                    sprintf(m_PtrPeerInfo->GetCommSSLConfig()->DestinationIPandPort, "%s:%s", m_PeerIpAddr, BioPort);                    

                    /* Created instance of comm class to use function of comm class */
                    m_PtrComm = new Comm(m_PtrPeerInfo->GetCommSSLConfig(), m_ptrDataInterfaceConfig->GetCommDataConfig(m_PeerId));
                }
                catch (std::exception &e)
                {
                    // Log fault
                    snprintf ( this->m_LogBuffer, buff_size_config, "Comm class:%s",e.what() );
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                }

                /* Now communication will start */
                m_CurrentState = COMM_START;
                m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                break;
            }
            case COMM_START:
            {
                sleep(COMM_START_TIME);

                /* Created instance of BIO Wrapper class */
                status = m_PtrComm->Start();
                if (status != 0)
                {
                    /* Failed to create instance of BIO wrapper class then log event */
                    m_CurrentState = COMM_EVENT;

                    /* check upto max retry count to connect with peer */
                    if (RetryCount == COMM_START_MAX_RETRY_COUNT)
                    {
                        // Log fault
                        snprintf ( this->m_LogBuffer, buff_size_config, "Max count reached to start comm" );
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

                        /* Once reach to max retry count to connect with peer then log alarm */
                       m_CurrentState = COMM_ALARM;

                       m_PtrBackComm->RaiseError(COMM_FAILURE);

                       if (WDSServer::GetInstance() != nullptr)
                       {
                            WDSServer::GetInstance()->SetPeerConnStatus(m_PeerId, BLACKLIST);
                       }
                    }

                    // Log fault
                    snprintf ( this->m_LogBuffer, buff_size_config, "Error in starting communication" );
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

                } else
                {
                    /* Cconnected with peer successfully now process on communication frames */
                    m_CurrentState = COMM_PROCESS;
                    m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                    // Log Event
                    snprintf ( this->m_LogBuffer, buff_size_config, "Comm started : %s", m_PeerIpAddr);
                    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));

                    if (WDSServer::GetInstance() != nullptr)
                    {
                        WDSServer::GetInstance()->SetPeerConnStatus(m_PeerId, SUCCESS);
                    }

                    if (m_PtrBackComm->StartConnection(m_PeerId, m_PeerIpAddr) < 0 )
                    {
                        // Log alarm
                        snprintf ( this->m_LogBuffer, buff_size_config, "Failed to start background communication " );
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                    }
                }

                m_PtrPeerInfo->SetCurrentState(m_CurrentState);
                break;
            }
            case COMM_PROCESS:
            {
                /* Waiting for cyclic activity signal of comm thread */
                m_PtrPeerInfo->WaitTriggerCyclicActivity();

                /* Process on communication frames */
                status = m_PtrComm->Process();

                /*Check any failure while processing comm frames or Graceful shutdown flag */
                if ((status < 0) || (m_PtrPeerInfo->GetGracefulShutdownFlag()))
                {
                   /* Failed while processing comm frames or graceful shutdown flag raised */
                   /* Now disconnect from peer */
                   m_CurrentState = COMM_EXIT;

                   m_PtrBackComm->RaiseError(COMM_FAILURE);

                   /* Cleared/Reset graceful shutdown flag */
                   m_PtrPeerInfo->SetGracefulShutdownFlag(false);                   

                   // Log fault
                   snprintf ( this->m_LogBuffer, buff_size_config, "Error in processing tx/rx frame" );
                   Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

                }
                else if (m_PtrBackComm->ReadError() == COMM_FAILURE) /* Check any error in background communication */
                {
                    m_CurrentState = COMM_EXIT;
                }
                else
                {
                    // Notify HMI to update UI
                    emit HMIScreenUpdated(m_PeerId, m_ptrDataInterfaceConfig);

                    if (m_PtrPeerInfo->GetPlatformConfigState() == E_IN_PROCESS)
                    {
                        // Read configuration status from HMI Platform config MB and update Peer Info
                        m_PtrPeerInfo->SetPlatformConfigState(PlatformConfigInt->GetConfigState());

                        // Send signal to config interface class and then QML to update configuration status
                        emit HMIConfigStatusUpdated(m_PeerId);
                    }

                   /* Continue to process communication frames */
                   m_CurrentState = COMM_PROCESS;
                }

                m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                break;
            }
            case COMM_EXIT:
            {
                /* Disconnected from peer */
                status = m_PtrComm->Exit();
                if (status != 0)
                {
                    /*  Failed to disconnect with peer, raised log alarm */
                    m_CurrentState = COMM_ALARM;

                    // Log fault
                    snprintf ( this->m_LogBuffer, buff_size_config, "Failed to disconnect with peer" );
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                }
                else
                {
                    // Log Event
                    snprintf ( this->m_LogBuffer, buff_size_config, "Peer %s disconnected.", m_PeerIpAddr);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

                    if (WDSServer::GetInstance() != nullptr)
                    {
                        // Removed welder information from discovery info table.
                        WDSServer::GetInstance()->UpdateDiscoveryInfoTable(m_PeerId);
                    }

                    /* Remove entry from m_PeerMap*/
                    if(CommPeerWrapper::RemovePeerData(m_PeerId))
                    {
                        // Log Event
                        snprintf ( this->m_LogBuffer, buff_size_config, "Removed entry from m_PeerMap");
                        Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));
                    }

                    /* Delete instance of peer info class */
                    delete m_PtrPeerInfo;

                    delete m_ptrDataInterfaceConfig;

                    /*Delete instance of comm class */
                    delete m_PtrComm;

                    /* Disconnected peer successfully, now waiting for connection start request. */
                    m_CurrentState = COMM_START_REQUEST;
                }
                break;
            }
            case COMM_EVENT:
            {
                // Log Event
                snprintf ( this->m_LogBuffer, buff_size_config, "Log Event generated...");
                Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));

                /* Retry count increamented by 1 on every failure of starting communication with peer */
                RetryCount++;

                /* Starting for communication at max retry count */
                m_CurrentState = COMM_START;
                m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                break;
            }
            case COMM_ALARM:
            {
                // Log Alarm
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Log Alarm generated..."));

                /* Failed to starting for communication with peer at max retry count */
                /* Cleared/Reset retry count to 0 */
                RetryCount = 0;

                /* Remove entry from m_PeerMap*/
                if(CommPeerWrapper::RemovePeerData(m_PeerId))
                {
                    // Log Event
                    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, ("Removed entry from m_PeerMap"));
                }

                /* Delete instance of peer info class */
                delete m_PtrPeerInfo;

                delete m_ptrDataInterfaceConfig;

                /*Delete instance of comm class */
                delete m_PtrComm;

                /* Waiting for starting communication */
                m_CurrentState = COMM_START_REQUEST;                

                break;
            }
            default:
                // Log fault
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Invalid comm state"));
        }
    }
}

/*****************************************************************************
* \brief   - Delete instance of Peer Info class
* \param   - None
*
* \return  - None
******************************************************************************/
CommThread::~CommThread()
{

    if (m_PtrComm->Exit() != 0)
    {
        // Log alarm
        snprintf ( this->m_LogBuffer, buff_size_config, "Failed to disconnect with peer" );
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
    }

    /* Delete instance of background communication class */
    delete m_PtrBackComm;
}

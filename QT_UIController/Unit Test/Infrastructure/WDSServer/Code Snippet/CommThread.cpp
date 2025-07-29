/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Declares COMM Thread - responsible for  state machine and its transition

--------------------------- REVISION HISTORY ------------------------------
rev1: 26/05/2023 - Initial implementation.

***************************************************************************/

#include <unistd.h>
#include "CommPeerWrapper.h"
#include "CommThread.h"
#include "WDSServer.h"
#include "DataInterfaceConfig_HMI.h"
#include "BIOConfig.h"
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
    this->m_LogId = logger::enroll(this);

    // Initialize Peer Info object
    try{
        m_PtrPeerInfo = new PeerInfo();
        // Log Event
        snprintf ( this->m_LogBuffer, buff_size_config, "PeerInfo instance created.");
        logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

    } catch (std::exception &e)
    {
        // Log alarm
        snprintf ( this->m_LogBuffer, buff_size_config, "PeerInfo:%s", e.what() );
        logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
    }

    // Insert Peer Info object into map
    CommPeerWrapper::SetPeerData(m_PeerId, m_PtrPeerInfo);
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

    while(1)
    {
        /* Implementation State machine */
        switch (m_CurrentState)
        {
            case COMM_START_REQUEST:
            {
                // Log Debug
                snprintf ( this->m_LogBuffer, buff_size_config, "Comm Thread %d.", m_PeerId);
                logger::add_entry(this->m_LogId,SEVERITY::LOG_DEB, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                // Log general information
                snprintf ( this->m_LogBuffer, buff_size_config, "Waiting for start request.");
                logger::add_entry(this->m_LogId,SEVERITY::LOG_GENERAL_INFO, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                if (m_PtrPeerInfo->GetCommSSLConfig()->RoleIs == CLIENT)
                {
                    /* Waiting for connection start request and connection details of discovered peer*/
                    m_PeerConnDetails = m_PtrPeerInfo->WaitTriggerStartRequest();
                }

                std::cout << "COMM Thread " << m_PeerId << "Triggered: " << std::endl;

                try
                {
                    /* Created instance of data interface config class. */
                    m_ptrDataInterfaceConfig = new DataInterfaceConfig_HMI(m_PeerId);

                    /* Use this for configuring destination IP and Port */
                    sprintf(m_PtrPeerInfo->GetCommSSLConfig()->DestinationIPandPort, "%s:%d", m_PeerConnDetails.IpAddr, m_PeerConnDetails.Port);

                    /* Created instance of comm class to use function of comm class */
                    m_PtrComm = new Comm(m_PtrPeerInfo->GetCommSSLConfig(), m_ptrDataInterfaceConfig->GetCommDataConfig(m_PeerId));

                }
                catch (std::exception &e)
                {
                    // Log fault
                    snprintf ( this->m_LogBuffer, buff_size_config, "Comm class:%s",e.what() );
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
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
                        logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                        /* Once reach to max retry count to connect with peer then log alarm */
                       m_CurrentState = COMM_ALARM;

                       WDSServer::SetPeerConnStatus(m_PeerId, BLACKLIST);
                    }

                    // Log fault
                    snprintf ( this->m_LogBuffer, buff_size_config, "Error in starting communication" );
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                } else
                {
                    /* Cconnected with peer successfully now process on communication frames */
                    m_CurrentState = COMM_PROCESS;
                    m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                    // Log Event
                    snprintf ( this->m_LogBuffer, buff_size_config, "Communication started...");
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                    WDSServer::SetPeerConnStatus(m_PeerId, SUCCESS);

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

                   /* Cleared/Reset graceful shutdown flag */
                   m_PtrPeerInfo->SetGracefulShutdownFlag(false);

                   // Log fault
                   snprintf ( this->m_LogBuffer, buff_size_config, "Error in processing tx/rx frame" );
                   logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                } else {
                    // Notify HMI to update UI
                    emit HMIScreenUpdated(m_PeerId, m_ptrDataInterfaceConfig);

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
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                }
                else
                {

                    WDSServer::RemovePeerInfo(m_PeerId);

                    delete m_ptrDataInterfaceConfig;

                    /*Delete instance of comm class */
                    delete m_PtrComm;

                    /* Disconnected peer successfully, now waiting for connection start request. */
                    m_CurrentState = COMM_START_REQUEST;

                    // Log Event
                    snprintf ( this->m_LogBuffer, buff_size_config, "Disconnected peer successfully");
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
                    emit PeerDisconnected(QString::fromStdString(m_PeerConnDetails.IpAddr));
                }
                m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                break;
            }
            case COMM_EVENT:
            {
                // Log Event
                snprintf ( this->m_LogBuffer, buff_size_config, "Log Event generated...");
                logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

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
                snprintf ( this->m_LogBuffer, buff_size_config, "Log Alarm generated...");
                logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                /* Failed to starting for communication with peer at max retry count */
                /* Cleared/Reset retry count to 0 */
                RetryCount = 0;

                WDSServer::RemovePeerInfo(m_PeerId);

                delete m_ptrDataInterfaceConfig;

                /*Delete instance of comm class */
                delete m_PtrComm;

                /* Waiting for starting communication */
                m_CurrentState = COMM_START_REQUEST;
                m_PtrPeerInfo->SetCurrentState(m_CurrentState);

                break;
            }
            default:
                // Log fault
                snprintf ( this->m_LogBuffer, buff_size_config, "Invalid comm state" );
                logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
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
        logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
    }

    /* Remove entry from m_PeerMap*/
    if(CommPeerWrapper::RemovePeerData(m_PeerId))
    {
        // Log Event
        snprintf ( this->m_LogBuffer, buff_size_config, "Removed entry from m_PeerMap");
        logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
    }

    /* Delete instance of peer info class */
    delete m_PtrPeerInfo;
}

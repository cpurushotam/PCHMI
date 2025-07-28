/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares background COMM Thread - responsible for background comm between
                                     ASC and HMI

--------------------------- REVISION HISTORY ------------------------------
 rev1: 18/01/2024 - Initial implementation.

***************************************************************************/

#include "BgCommThread.h"
#include "BIOConfig_BgCommAce.h"
#include "Common_Definitions.h"
/*****************************************************************************
* \brief   - Initilize communication thread class
*            1. Initialize Peer ID with received parameter.
*            2. Initialize Current State with Start request.
*
* \param   - int        WeldorId
*            QObject    *parent
*
* \return  - None
******************************************************************************/
BgCommThread::BgCommThread(QObject *parent)
{
    m_PtrSSLConfig = &BgCommAceParam;

    strcpy(m_BioPort, m_PtrSSLConfig->DestinationIPandPort); /* Extract port from configuration */

    // Initialize Current State with Start request.
    m_CurrentState = BG_COMM_IDLE;

    // Initialize log ID
    this->m_LogId = Logger::enroll(this);

    this->start();
}

/*****************************************************************************
* \brief   - BgCOMM thread is responsible for running logic related background
*            communication between ASC and HMI
*            1. Waiting for start request -  Create instance of CommClass.
*            2. Start background communication with peer
*            3. if any failure in starting communication the raise event and alarm.
*            4. Process on Tx/Rx frames.
*            5. Disconnect from peer if any failure in process.
*
* \param   - None.
*
* \return  - void
******************************************************************************/
void BgCommThread::run()
{
    int status;
    int RetryCount = 0;
    comm_stat *DataInt = nullptr;
    ProductionScreen_MB *ProdDataInt = nullptr;

    while(1)
    {
        /* Implementation State machine */
        switch (m_CurrentState)
        {
            case BG_COMM_IDLE:
            {
                // Idle state for background communication
                // Do nothing
                break;
            }
            case BG_COMM_START:
            {
                sleep(BG_COMM_START_TIME);
                status = m_PtrComm->Start();    /* Start background communication */
                if (status != 0)
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Error in starting background communication"));   /* Log Alarm */
                    m_ErrorCode     = COMM_FAILURE;
                    m_CurrentState  = BG_COMM_EXIT;

                } else
                {                    
                    m_CurrentState = BG_COMM_PROCESS;  /* connected with peer successfully now process on communication frames */

                    // Log Event
                    snprintf ( this->m_LogBuffer, buff_size_config, "Background Comm started : %s", m_PeerIpAddr.c_str());
                    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));
                }
                break;
            }
            case BG_COMM_PROCESS:
            {
                /* Process on background communication frames */
                status = m_PtrComm->Process();
                /*Check any failure while processing Background comm frames */
                if ((status < 0) || (m_ErrorCode == COMM_FAILURE))
                {
                   /* Failed while processing Background comm frames */
                   /* Now disconnect from peer */
                   m_ErrorCode     = COMM_FAILURE;
                   m_CurrentState  = BG_COMM_EXIT;

                   // Log fault
                   Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Error in processing tx/rx frame for Background comm"));
                }
                else
                {
                   /* Continue to process Background communication frames */
                   m_CurrentState = BG_COMM_PROCESS;
                }
                break;
            }
            case BG_COMM_EXIT:
            {                
                /* Disconnected from peer */
                status = m_PtrComm->Exit();
                if (status != 0)
                {
                    delete m_PtrComm;

                    // Log fault
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Failed to disconnect with peer for Background comm"));
                }
                else
                {
                    // Log Alarm
                    snprintf ( this->m_LogBuffer, buff_size_config, "Peer %s disconnected Background comm", m_PeerIpAddr.c_str());
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

                    /*Delete instance of data interface and comm class */
                    delete m_ptrBgDataInterface;
                    delete m_PtrComm;
                }
                m_CurrentState = BG_COMM_FAULT;

                break;
            }

            case BG_COMM_FAULT:
            {
                break;
            }
            default:
                // Log fault
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Invalid comm state"));
        }
        msleep(BG_CYCLIC_TIME);
    }
}

/*****************************************************************************
* \brief   - Initialize background communication parameters
*
* \param   - std::string PeerIpAddr - IP Address of background peer
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int BgCommThread::StartConnection(int PeerId, std::string PeerIpAddr)
{
    int status = -1;

    memset(m_PtrSSLConfig->DestinationIPandPort, 0, 20);    /* Initilize Destination IP and Port*/
    m_PeerIpAddr  = PeerIpAddr;

    try
    {
        sprintf(m_PtrSSLConfig->DestinationIPandPort, "%s:%s", m_PeerIpAddr.c_str(), m_BioPort);  /* Create connection details to start comm */

        m_ptrBgDataInterface = new BgDataInterfaceConfig_HMI(PeerId); /* Created instance of data interface for background comm. */

        m_PtrComm = new Comm(m_PtrSSLConfig, m_ptrBgDataInterface->GetBgCommDataIntrConfig(), BACK_THREAD);

        m_CurrentState  = BG_COMM_START;
        m_ErrorCode     = COMM_SUCCESS;
        status = 0;
    }
    catch (std::exception &e)
    {
        m_ErrorCode     = COMM_FAILURE;

        snprintf ( this->m_LogBuffer, buff_size_config, "Bg Comm Error: %s", e.what() );
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));  /* Log Alarm */
    }

    return status;
}

/*****************************************************************************
* \brief   - Raise communication error
*
* \param   - COMM_ERROR_CODE - status of communication
*
* \return  - None
******************************************************************************/
void BgCommThread::RaiseError(COMM_ERROR_CODE ErrorCode)
{
    if (m_CurrentState == BG_COMM_PROCESS || m_CurrentState == BG_COMM_START)
    {
        m_ErrorCode     = ErrorCode;
        m_CurrentState  = BG_COMM_EXIT;
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM,("Internal error: Invalid state"));  /* Log Alarm */
    }
}

/*****************************************************************************
* \brief   - Read communiction error
*
* \param   - None
*
* \return  - COMM_ERROR_CODE - COMM_FAILURE,
*                              COMM_SUCCESS
******************************************************************************/
COMM_ERROR_CODE BgCommThread::ReadError()
{
    if (m_CurrentState == BG_COMM_FAULT)
    {
        m_CurrentState = BG_COMM_IDLE;
    }
    return m_ErrorCode;
}

/*****************************************************************************
* \brief   - Disconnect background comm with peer
*
* \param   - None
*
* \return  - None
******************************************************************************/
BgCommThread::~BgCommThread()
{
    if (m_PtrComm->Exit() != 0)
    {
        // Log alarm
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, ("Failed to disconnect background comm with peer"));
    }

    delete m_PtrComm;
}

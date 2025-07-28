/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Definition Peer Info -	Responsible for store each peer (welder) information-
  	  	  	  	  	    1. Current state of peer
  	  	  	  	  	    2. Communication status of peer - is peer shutdown or connected.
  	  	  	  	  	    3. Cyclic activity of respective peer.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.

***************************************************************************/
#include "CommPeerInfo.h"

/*****************************************************************************
* \brief   - Initilize Peer info class.
*            1. Initilize graceful shutdown flag
*            2. Initialize current state as waiting for start request
*            3. Initilize semaphore for thread cyclic activity and start request.
* \param   - None
*
* \return  - None
******************************************************************************/
PeerInfo::PeerInfo()
{
    /* Initially gracefull shutdown is off */
    this->m_GracefulShutdown=false;

    /* Initialize current state as waiting for start request*/
    this->m_CurrentState=COMM_START_REQUEST;

    // Initialize communication configuration.
    m_SSLConfig = ClientParam;

    /* Initilize semaphore for thread cyclic activity */
    if (sem_init(&this->m_ThreadCyclicActivitySem, 0, 0) != 0)
    {
        throw std::runtime_error ("CyclicActivitySem init failed");
    }

    /* Initilize semaphore for start request */
    if (sem_init(&this->m_StartRequestSem, 0, 0) != 0)
    {
        throw std::runtime_error ("StartRequestSem init failed");
    }
}

/*****************************************************************************
* \brief   - Triggered cyclic activity for comm thread
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::TriggerCyclicActivity()
{
    /* Release semaphore for cyclic activity signal for comm thread */
    if (sem_post(&m_ThreadCyclicActivitySem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_post failed");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
        return false;
    }

    return  true;
}

/*****************************************************************************
* \brief   - Triggered start request.
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::TriggerStartRequest(PeerConnDetails PeerConnDetails)
{
    /* Release semaphore for connection start request */
    if (sem_post(&m_StartRequestSem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequestSem sem_post failed");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
        return false;
    }

    m_PeerConnDetails = PeerConnDetails;

    return true;
}

/*****************************************************************************
* \brief   - Wait for cyclic activity semaphore
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::WaitTriggerCyclicActivity()
{
    /* Waiting for cyclic activity signal for comm thread */
    if (sem_wait(&m_ThreadCyclicActivitySem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_wait failed");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
        return false;
    }
    return  true;
}

/*****************************************************************************
* \brief   - wait for start request semaphore.
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
PeerConnDetails PeerInfo::WaitTriggerStartRequest()
{
    /* Waiting for connection start request */
    if (sem_wait(&m_StartRequestSem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequestSem sem_wait failed");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
    }

    return  m_PeerConnDetails;
}

/*****************************************************************************
* \brief   - Set status of graceful shutdown flag.
*
* \param   - bool status
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::SetGracefulShutdownFlag(bool status)
{
    // Set status of graceful shutdown flag.
    m_GracefulShutdown=status;
    return true;
}

/*****************************************************************************
* \brief   - Read status of graceful shutdown flag.
*
* \param   - None
*
* \return  - status of graceful shutdown flag.
******************************************************************************/
bool PeerInfo::GetGracefulShutdownFlag()
{
    // Read status of graceful shutdown flag.
    return m_GracefulShutdown;
}

/*****************************************************************************
* \brief   - Set current state of peer.
*
* \param   - bool    CurrentState
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::SetCurrentState(int CurrentState)
{
    // Set current state of peer.
    m_CurrentState=(COMM_THREAD_STATES) CurrentState;
    return true;
}

/*****************************************************************************
* \brief   - Get current state of peer.
*
* \param   - None
*
* \return  - int - Return current state of peer
******************************************************************************/
int PeerInfo::GetCurrentState()
{
    // Return current state of peer.
    return m_CurrentState;
}

/*****************************************************************************
* \brief   - Return communication SSL configuration for BIO Wrapper.
*
* \param   - None
*
* \return  - CommConfig *- Pointer to communication SSL configuration.
******************************************************************************/
CommConfig *PeerInfo::GetCommSSLConfig()
{
    return &m_SSLConfig;
}

/*****************************************************************************
* \brief   - Delete semaphore
*
* \param   - None
*
* \return  - None
******************************************************************************/
PeerInfo::~PeerInfo()
{
    // Delete semaphore of cyclic activity
    if(sem_destroy(&m_ThreadCyclicActivitySem) == -1)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_destroy fail");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
    }

    // delete semaphore of start request
    if(sem_destroy(&m_StartRequestSem) == -1)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequest sem_destroy failed");
        //Log with Severity: LOG_ALARM
        logger::add_entry(m_LogId ,SEVERITY::LOG_ALARM, (uint8_t*)m_LogBuffer, sizeof(m_LogBuffer));
    }
}

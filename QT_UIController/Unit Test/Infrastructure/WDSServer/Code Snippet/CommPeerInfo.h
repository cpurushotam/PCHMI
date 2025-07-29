/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Peer Info -	Responsible for store each peer (welder) information-
  	  	  	  	  	    1. Current state of peer
  	  	  	  	  	    2. Communication status of peer - is peer shutdown or connected.
  	  	  	  	  	    3. Cyclic activity of respective peer.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.

***************************************************************************/
#ifndef PeerInfo_H
#define PeerInfo_H

#include <semaphore.h>
#include <atomic>
#include "BIOConfig.h"
#include "logger.h"
#include "WDSServer.h"

// Max Retry count to start connection
constexpr unsigned int COMM_START_MAX_RETRY_COUNT = 3;

/* Enum to define states implemented by COMM thread & its transition*/
enum COMM_THREAD_STATES
{
    COMM_START_REQUEST = 0,  /* State machine for connection start request */
    COMM_START,         	 /* State machine for starting Communication  */
    COMM_PROCESS,       	 /* State machine for Communication process */
    COMM_EXIT,          	 /* State machine for exiting communication  */
    COMM_EVENT,         	 /* State machine for Logging Event */
    COMM_ALARM          	 /* State machine for logging alarm */
};

// PeerInfo class defination
class PeerInfo
{
private:
    // Semaphore for synchronization of comm thread
    sem_t m_ThreadCyclicActivitySem;

    // Semaphore for start request communication
    sem_t m_StartRequestSem;

    // Gracefully shutdown for communication process
    std::atomic<bool> m_GracefulShutdown;

    // Connect flag for peer connected or not
    COMM_THREAD_STATES m_CurrentState;

    // log identifier
    size_t m_LogId;

    // log buffer
    char m_LogBuffer[buff_size_config]={0};

    // Structure variable declaration to store configuration for communication.
    CommConfig m_SSLConfig;

    // connection details of peer
    PeerConnDetails m_PeerConnDetails;

public:
    // Contructor declaration
    PeerInfo();

    // Destructor declarion to perform cleanup activity
    ~PeerInfo();

    // Trigger cyclic activity semaphore.
    bool TriggerCyclicActivity();

    // Trigger start request semaphore.
    bool TriggerStartRequest(PeerConnDetails PeerConnDetails);

    // Wait for cyclic activity semaphore.
    bool WaitTriggerCyclicActivity();

    // Wait start request semaphore.
    PeerConnDetails WaitTriggerStartRequest();

    // Set status of graceful shutdown flag.
    bool SetGracefulShutdownFlag(bool);

    // Read status of graceful shutdown flag.
    bool GetGracefulShutdownFlag();

    // Set current state of peer
    bool SetCurrentState(int CurrentState);

    // Get current state of peer.
    int GetCurrentState();

    // Get communication SSL configuration for BIO Wrapper.
    CommConfig *GetCommSSLConfig();

};

#endif // PeerInfo_H

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Background COMM Thread - responsible for background comm between
                                     ASC and HMI

--------------------------- REVISION HISTORY ------------------------------
 rev1: 18/01/2024 - Initial implementation.

***************************************************************************/

#ifndef BACKCOMMTHREAD_H
#define BACKCOMMTHREAD_H

#include <QThread>
#include <semaphore.h>
#include "Comm.h"
#include "BgDataInterfaceConfig_HMI.h"

 /* Enum for communication error codes */
typedef enum {
    COMM_FAILURE = -1,
    COMM_SUCCESS = 0
} COMM_ERROR_CODE;

// BgCommThread Class definition
class BgCommThread : public QThread
{
    static constexpr unsigned int BG_COMM_START_TIME           = 1;

    /* Enum to define states implemented by COMM thread & its transition*/
    enum BG_COMM_STATES
    {
        BG_COMM_IDLE = 0,        /* State machine for connection start request */
        BG_COMM_START,         	 /* State machine for starting Communication  */
        BG_COMM_PROCESS,       	 /* State machine for Communication process */
        BG_COMM_EXIT,          	 /* State machine for exiting communication  */
        BG_COMM_FAULT            /* State machine for handling fault */
    };

    CommConfig                *m_PtrSSLConfig;          /* Structure variable declaration to store configuration for communication. */
    Comm                      *m_PtrComm;               /* Comm class instance to access comm class functions */
    BgDataInterfaceConfig_HMI *m_ptrBgDataInterface;    /* Pointer to data interface config for Bg comm */
    std::string                m_PeerIpAddr;            /* IP Address of peer */
    BG_COMM_STATES             m_CurrentState;          /* IP Address of connected peer */
    COMM_ERROR_CODE            m_ErrorCode;             /* To store status of communication */
    char                       m_BioPort [5]={0};       /* BIO Port for background communication */
    size_t                     m_LogId;                 /* log identifier */
    char                       m_LogBuffer[buff_size_config]={0};  /* log buffer */
public:
    BgCommThread(QObject *parent = nullptr);            /* Constructor declaration */
    ~BgCommThread();                                    /* Destructor declaration to perform cleanup activity */

    void run();                                         /* Implemention of state machine. */

    int StartConnection(int PeerId, std::string PeerIpAddr);        /* Start background communication */
    void RaiseError(COMM_ERROR_CODE ErrorCode);         /* Raise any error in communication */
    COMM_ERROR_CODE ReadError();                        /* Read error in communication */
};

#endif // BACKCOMMTHREAD_H

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

#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>
#include "Comm.h"
#include "CommPeerInfo.h"
#include "BgCommThread.h"
#include "DataInterfaceConfig_HMI.h"

// CommThread Class definition
class CommThread : public QThread
{
public:
    // Constructor declaration
    CommThread(int PeerId, QObject *parent = nullptr);

    // Destructor declaration to perform cleanup activity
    ~CommThread();

    // Implemention of state machine.
    void run();

signals:
    // Signal defined to notined screen updated
    void HMIScreenUpdated(int PeerId, DataInterfaceConfig_HMI *ptrDataInterfaceConfig);

    // Signal defined to notined status of HMI configuration
    void HMIConfigStatusUpdated(int PeerId);

private:
    // Declaration of Q_OBJECT for signals and slots mechanism
    Q_OBJECT

    static constexpr unsigned int COMM_START_TIME = 1;

    // Comm class instance to access comm class functions
    Comm *m_PtrComm;

    // Background comm class instance
    BgCommThread *m_PtrBackComm;

   // Pointer to data interface config.
    DataInterfaceConfig_HMI *m_ptrDataInterfaceConfig;

    // Variable declaration to store peer id of each communication peer
    int m_PeerId;

    // Enum declaration to store current state of state machine
    COMM_THREAD_STATES m_CurrentState;

    // Instance of Peer Info class to access its functions
    PeerInfo *m_PtrPeerInfo;

    // log identifier
    size_t m_LogId;

    // log buffer
    char m_LogBuffer[buff_size_config]={0};

    // connection details of peer
    char  m_PeerIpAddr[20];

};

#endif // COMMTHREAD_H

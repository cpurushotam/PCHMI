/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares System logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/

#ifndef SYSLOGGER_H
#define SYSLOGGER_H

#include <QThread>
#include "LoggerInterface.h"

static constexpr char SYS_LOG_TASK  []   = "/sys_queue_hmi";    /* System log queue name */

// Definition of SysLogger class
class SysLogger : public LoggerInterface, public QThread
{
    int m_priority =-1;
public:
    SysLogger();                /* Constructor declaration */
    void run() override;        /* Thread Function */

    void Init() override;       /* Initialize system logger message queue */
    void AddEntry(LogEntry *log_entry, uint32_t msg_len) override;  /* Send log entry to system logger message queue */
};

#endif // SYSLOGGER_H

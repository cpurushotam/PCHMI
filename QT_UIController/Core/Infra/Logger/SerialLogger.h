/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares Serial logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/
#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

#include <QThread>

#include "LoggerInterface.h"

static constexpr char SERIAL_LOG_TASK [] =   "/serial_queue_hmi";       /* System log queue name */

// Definition of SerialLogger class
class SerialLogger : public LoggerInterface, public QThread
{
public:
    SerialLogger();                         /* Constructor declaration */
    void run() override;                    /* Thread Function */
    void Init() override;                   /* Initialize serial logger message queue */
    void AddEntry(LogEntry* log_entry, uint32_t msg_len) override;  /* Send log entry to serial logger message queue */
};

#endif // SERIALLOGGER_H

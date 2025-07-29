/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares DB logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/

#ifndef DBLOGGER_H
#define DBLOGGER_H

#include "LoggerCommon.h"

// Definition of DBLogger class
class DBLogger
{
public:
    static void AddEntry(LogEntry* log_entry, uint32_t msg_len); /* Dummy implementation of DB Logger */
};

#endif // DBLOGGER_H

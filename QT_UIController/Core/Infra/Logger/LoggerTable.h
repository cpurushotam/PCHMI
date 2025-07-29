/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares logger table.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/
#ifndef LOGGERTABLE_H
#define LOGGERTABLE_H

#include <map>

#include "SerialLogger.h"
#include "SysLogger.h"

// Table to store information of logger interface
std::map <std::string, LoggerInterface*> LoggerTable =
{
    {SERIAL_LOG_TASK,  new SerialLogger},
    {SYS_LOG_TASK,      new SysLogger},
};

#endif // LOGGERTABLE_H

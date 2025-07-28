/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declaration of logger variables.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 - Interface definition
 
***************************************************************************/

#ifndef LOGGERCOMMON_H
#define LOGGERCOMMON_H

#include <iostream>
#include "Common_Definitions.h"
#include <cstring>

// Declaration of severity for logger map to system logger Message Severities
typedef enum
{
    E_LOG_CRITICAL,				/* LOG_CRITICAL map to syslog severity LOG_EMERG(0) 		: use this in an critical case, highest severity */
    E_LOG_ALARM,				/* LOG_ALARM map to syslog severity LOG_ALERT(1) 			: use this for alarms or errors generated in the system, Condition that should be corrected immediately, highest severity */
	E_LOG_EVENT,				/* LOG_EVENT map to syslog severity LOG_CRIT(2) 			: use this for important events in the system, high severity */
	E_LOG_ERROR,				/* LOG_ERROR map to syslog severity LOG_ERR(3) 				: use this for ERROR */
	E_LOG_WARN,					/* LOG_WARN map to syslog severity LOG_WARNING(4) 			: use this for warnings */
	E_LOG_NOTIFICATION,  		/* LOG_NOTIFICATION map to syslog severity LOG_NOTICE(5)	: use this for notifications, medium severity */
	E_LOG_GENERAL_INFO,  		/* LOG_GENERAL_INFO map to syslog severity LOG_INFO(6) 		: use this for general information, Low severity */
	E_LOG_DEB    				/* LOG_DEB map to syslog severity LOG_DEBUG(7) 				: use for debug purpose, lowest severity */
	
}E_SEVERITY;

// Declaration of Logger entry
typedef struct LogEntry
{
    size_t      log_id;       						/* identifier for log entry */
    E_SEVERITY 	severity;   						/* severity of the entry */
    uint64_t 	timestamp;  						/* time-stamp of the entry(number of ticks) */
    uint8_t 	*byte_array; 						/* buffer for storing log information */
    
    LogEntry()
    {
    	log_id     = 0;
    	severity   = E_LOG_GENERAL_INFO;
    	timestamp  = 0;
    	byte_array = nullptr;
    }
    
}LogEntry;


#endif // LOGGERCOMMON_H

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Implementation of logger interface.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 - Interface definition

***************************************************************************/

#ifndef LOGGERINTERFACE_H
#define LOGGERINTERFACE_H

#include <sstream>
#include <ctime>
#include <mqueue.h>

#include "LoggerCommon.h"
#include "Common_Definitions.h"
#include "EventLogStructure.h"
#include "AlarmLogStructure.h"

typedef enum
{
	OK = 0,
	ERROR = -1
}LOGGER_ERROR_CODES;

// Message queue OFFSETS
static constexpr unsigned int MAX_MSG                = 5;
static constexpr unsigned int MAX_MSG_LEN            = 1024;

// Definition of LoggerInterface
class LoggerInterface
{
    const std::string currentDateTime();
    char m_MsgBuffer[MAX_SIZE_OF_MSG_LENGTH] = {0x00};
protected:
    //Initialize message queue descriptor
    mqd_t m_MqID = 0;
    
    int         CreateMsgQ    (const char *key);
    int         SendMsgQ      (mqd_t MsgID, LogEntry *log_entry, uint32_t msg_len);
    std::string ReceiveMsgQ   ();
    std::string LogEntryToStr (char *log_entry);
public:
   
    virtual ~LoggerInterface() = default;
    virtual void Init()     = 0;
    virtual void AddEntry(LogEntry* log_entry, uint32_t msg_len) = 0;    
};

#endif // LOGGERINTERFACE_H

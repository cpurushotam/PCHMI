/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Implements logger functionality.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 09/02/2024 - Interface definition

***************************************************************************/
#include <ctime>
#include "DataLogger.h"
#include "DBLogger.h"
#include "LoggerTable.h"
#include "DataLoggerManager.h"

#if defined(__RTP__)
#include "Utility.h"
#include "ControlTask.h"
#endif

static constexpr uint32_t ALARM_MSG_LENGTH = sizeof(AlarmLogEntry) + BUFF_SIZE;
static constexpr uint32_t EVENT_MSG_LENGTH = sizeof(EventLogEntry) + BUFF_SIZE;
bool Logger::ConsoleModeEnabled = true;
bool Logger::m_MaintenanceMode = false;

/**************************************************************************//**
* \brief   - Logger entry function
*
* \param   - LogEntry *log_entry --> Logger Entry.
*
* \return  - 0 if success, -1 if failed.
*
******************************************************************************/
int Logger::add_entry(LogEntry *log_entry)
{
    int return_val = 0;
    uint32_t msg_len = 0;

    // Check if parameters are valid
    if((log_entry != nullptr) && (log_entry->byte_array != nullptr) &&
        (log_entry->severity <= E_LOG_DEB) && (log_entry->severity >= E_LOG_CRITICAL))
    {
        // Create message length
        if      (log_entry->severity == E_LOG_ALARM)  { msg_len = ALARM_MSG_LENGTH ;}
        else if (log_entry->severity == E_LOG_EVENT)  { msg_len = EVENT_MSG_LENGTH ;}
        else    { msg_len = BUFF_SIZE_MAX;}

        if (m_MaintenanceMode)
        {
            // If Maintenance mode is enabled, then all logs will be redirected to system logger irrespective of the severity level
        	
             //LoggerTable[SYS_LOG_TASK]->AddEntry(log_entry, msg_len);
        }
        else
        {
            if ((log_entry->severity == E_LOG_ALARM) || (log_entry->severity == E_LOG_EVENT))
            {
                // If Maintenance mode is disable and severity is equal to LOG_EVENT or LOG_ALARM then Logger sends the 
            	// LE content to Database Write task to update corresponding data tables
            	
                 DBLogger::AddEntry(log_entry, msg_len);
            }
            else
            {
                // If Maintenance mode is disable and severity is other than LOG_EVENT or LOG_ALARM then logger send the LE to system logger
                // for writing logs to a file on EMMC.
            	
               //LoggerTable[SYS_LOG_TASK]->AddEntry(log_entry, msg_len);
            }
        }

        if (ConsoleModeEnabled)
        {
        	// Log entry will be printed on standard output if the console mode is enabled
            // This feature is made available to ease development, and will be disabled for production code.
            #if defined(__RTP__)
            //std::cout << "Logger[" << Utility::GetDateAndTime().c_str()  <<"], TimeStamp: " << log_entry->timestamp << ", S: " << log_entry->severity << ",M: " << log_entry->byte_array << std::endl;
            #endif
            std::cout << log_entry->byte_array << std::endl;
            //LoggerTable[SERIAL_LOG_TASK]->AddEntry(log_entry, msg_len);
        }
    }
    else
    {
    	return_val = -1;
    	
        // log fault on standard output
		std::cout << "***************Logger add_entry failure" <<std::endl;
    }
    return return_val;
}

/**************************************************************************//**
* \brief   - API to log messages
*
* \param   - severity - message severity
* 			 data - message to log
*
* \return  - none
*
******************************************************************************/
int Logger::add_entry(E_SEVERITY severity, std::string data)
{
	//In case someone uses this API by passing E_LOG_ALARM or E_LOG_EVENT, change it to E_LOG_ERROR.
	//There are separate APIs to log event and alarms.
	if(severity == E_LOG_ALARM || severity == E_LOG_EVENT)
	{
		severity = E_LOG_ERROR;
	}
	LogEntry LogEntryData;
	LogEntryData.log_id = 0;
	LogEntryData.severity = severity;
 #if defined(__RTP__)
    LogEntryData.timestamp = ControlTask::GetNonResetableAuxClockTickCounter();
    if(severity == E_LOG_NOTIFICATION )
    {
        DataLogger::SaveDataLoggerMsgInQueue(data);
    }
#else
    LogEntryData.timestamp = 0;
#endif
	LogEntryData.byte_array = (uint8_t*)data.c_str();
	return add_entry(&LogEntryData);
}

/**************************************************************************//**
* \brief   - Enable debug messages on ASC console
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void Logger::EnableConsoleMode()
{
	ConsoleModeEnabled = true;
}

/**************************************************************************//**
* \brief   - Enable maintenance mode
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void Logger::EnableMaintainanceMode()
{
	m_MaintenanceMode = true;
}

/**************************************************************************//**
* \brief   - Disable debug messages on ASC console
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void Logger::DisableConsoleMode()
{
	ConsoleModeEnabled = false;
}

/**************************************************************************//**
* \brief   - Disable maintenance mode
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void Logger::DisableMaintainanceMode()
{
	m_MaintenanceMode = false;
}



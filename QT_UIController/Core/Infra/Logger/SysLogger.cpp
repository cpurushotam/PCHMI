/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Implementation System logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/
#include "SysLogger.h"
#ifdef _WIN32
#include <fstream>
#else
#include <syslog.h>
#endif
#include <iostream>

/**************************************************************************//**
* \brief   - Initialize system logger
*
* \param   - None
*
* \return  - None
******************************************************************************/
SysLogger::SysLogger()
{

    // Initialize message queue for system logger
    // this->Init();
}

/**************************************************************************//**
* \brief   - SysLogger thread is responsible Send a message to the system logger
*
* \param   - None
*
* \return  - None
******************************************************************************/
void SysLogger::run()
{
    std::string log_msg;
    while(1)
    {
        log_msg = ReceiveMsgQ();
#ifdef _WIN32
        // On Windows: write to a file, keep it simple
        static std::mutex file_mutex;
        std::lock_guard<std::mutex> lock(file_mutex);
        std::ofstream file("SysLogger.log", std::ios::app);
        if (file.is_open())
        {
            file << log_msg << std::endl;
        }
#else

        //Send a message to the system logger
        syslog(m_priority, (char*)log_msg.c_str());
#endif
    }
}

/**************************************************************************//**
* \brief   - Initialize system logger
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void SysLogger::Init()
{
    if (CreateMsgQ(SYS_LOG_TASK) == ERROR)
    {
        std::cout << "Failed to create mq for: " << SYS_LOG_TASK << "\n";
    }

    // Start system logger
    this->start();
}

/**************************************************************************//**
* \brief   - Send msg to  system logger message queue
*
* \param   - LogEntry* log_entry - Logger entry(e.g E_LOG_ALARM, E_LOG_EVENT etc.).
* 			 uint32_t msg_len    - Length of message.
*
* \return  - None.
******************************************************************************/
void SysLogger::AddEntry(LogEntry* log_entry, uint32_t msg_len)
{
    //priority argument are formed by OR'ing together a severity-level value and an optional facility value.
#ifdef _WIN32
    m_priority = log_entry->severity; // LOG_USER not needed for file logging
#else
    m_priority = log_entry->severity|LOG_USER;
#endif

    int status = SendMsgQ(m_MqID, log_entry, msg_len);
    if(status == ERROR)
    {
        std::cout << "Failed to send mq for: " << SYS_LOG_TASK << "\n";
    }
}

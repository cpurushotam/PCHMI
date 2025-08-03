/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Implementation of Serial logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/
#include "SerialLogger.h"

/**************************************************************************//**
* \brief   - Initialize Serial logger
*
* \param   - None
*
* \return  - None
******************************************************************************/
SerialLogger::SerialLogger()
{
    // Initialize message queue for serial logger
    Init();
}

/**************************************************************************//**
* \brief   - Serial logger thread is responsible Send a message to the serial
*
* \param   - None
*
* \return  - void *.
******************************************************************************/
void SerialLogger::run()
{
    std::string log_msg;
    while(1)
    {
        log_msg = ReceiveMsgQ();

        std::cout << log_msg << "\n";
    }
}

/**************************************************************************//**
* \brief   - Initialize serial logger
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void SerialLogger::Init()
{
    if (CreateMsgQ(SERIAL_LOG_TASK) == ERROR)
    {
        std::cout << "Failed to create mq for: " << SERIAL_LOG_TASK << "\n";
    }

    // Start Serial logger
    this->start();
}

/**************************************************************************//**
* \brief   - Send msg to serial logger message queue
*
* \param   - LogEntry* log_entry - Logger entry(e.g E_LOG_ALARM, E_LOG_EVENT etc.)
*            uint32_t msg_len    - Length of message
*
* \return  - None.
******************************************************************************/
void SerialLogger::AddEntry(LogEntry* log_entry, uint32_t msg_len)
{
    if (log_entry != nullptr)
    {
        int status = SendMsgQ(m_MqID, log_entry, msg_len);
        if(status == ERROR)
        {
            std::cout << "Failed to send mq for: " << SERIAL_LOG_TASK << "\n";
        }
    }
}

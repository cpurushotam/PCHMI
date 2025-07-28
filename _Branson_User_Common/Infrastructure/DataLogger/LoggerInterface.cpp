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

#include "LoggerInterface.h"
#ifdef _WIN32
#include <map>
#include <string>
static std::map<std::string, std::queue<std::string>*> namedQueues;
static std::mutex namedQueuesMutex;
#endif
static constexpr int datetime_buffSize = 100;
static char DateTimeBuff[datetime_buffSize];

/**************************************************************************//**
*
* \brief   - Get current date & time in YYYY-MM-DD HH:mm:ss format
*
* \param   - none
*
* \return  - Date & time in string format
*
******************************************************************************/
const std::string LoggerInterface::currentDateTime()
{
    time_t     current_time = time(0);
    struct tm  tstruct;
    tstruct = *localtime(&current_time);
    strftime(DateTimeBuff, datetime_buffSize, "%Y-%m-%d %X", &tstruct);
    return (DateTimeBuff);
}

/**************************************************************************//**
*
* \brief   - Create message queue for logger
*
* \param   - Logger Name - Logger entry(e.g E_LOG_ALARM, E_LOG_EVENT etc.)
*
* \return  -  0 if success, -1 if failed.
*
******************************************************************************/
int LoggerInterface::CreateMsgQ(const char* LoggerName)
{
#ifdef _WIN32
    std::lock_guard<std::mutex> lock(namedQueuesMutex);
    std::string name(LoggerName ? LoggerName : "");
    auto it = namedQueues.find(name);
    if (it == namedQueues.end())
    {
        namedQueues[name] = new std::queue<std::string>();
    }
    m_MqID = namedQueues[name];
    return (m_MqID != nullptr) ? OK : ERROR;
#else
    int status = ERROR;
    // Initialize the queue attributes
    struct mq_attr m_mqAttr;

    m_mqAttr.mq_flags 	= 0;                            // Message queue description flags: 0 or O_NONBLOCK
    m_mqAttr.mq_maxmsg 	= MAX_MSG;                      // Maximum number of messages on queue
    m_mqAttr.mq_msgsize = MAX_SIZE_OF_MSG_LENGTH;       // Maximum message size (in bytes)
    m_mqAttr.mq_curmsgs = 0;                            // Number of messages currently in queue

    //Create MsgQ for all tasks
    m_MqID = mq_open(LoggerName, O_RDWR | O_CREAT, 0666, &m_mqAttr);
    if (m_MqID >= OK)
    {
        status = OK;
    }
    else
    {
        perror("mq_open: ");
    }
    return status;
#endif
}

/**************************************************************************//**
*
* \brief   - Send logger message to the queue
*
* \param   - MsgID     - Unique Message ID.
* 			 log_entry - Logger entry(e.g E_LOG_ALARM, E_LOG_EVENT etc.)
* 			 msg_Len   - Length of message.
*
* \return  -  0 if success, -1 if failed.
*
******************************************************************************/
int LoggerInterface::SendMsgQ(MsgQueueHandle MsgID, LogEntry *log_entry, uint32_t msg_len)
{
    int status = OK;

#ifdef _WIN32
    if (!MsgID) return ERROR;
    std::string logMsg(reinterpret_cast<char*>(log_entry), msg_len);
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        MsgID->push(logMsg);
    }
    m_queueCV.notify_one();
    return OK;
#else
    const char* msg_ptr = reinterpret_cast<char *>(log_entry);
    if (mq_send(MsgID, msg_ptr, msg_len, 0) == ERROR)
    {
        status = ERROR;
        std::cout << "mq_send failed \n";
    }
    return status;
#endif
}

/**************************************************************************//**
*
* \brief   - Receive logger message from the queue
*
* \param   - None
*
* \return  -  0 if success, -1 if failed.
*
******************************************************************************/
std::string LoggerInterface::ReceiveMsgQ()
{
    std::string Msg;

#ifdef _WIN32
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_queueCV.wait(lock, [this] { return m_MqID && !m_MqID->empty(); });
    std::string msg = m_MqID->front();
    m_MqID->pop();
    return msg;
#else
    int status = mq_receive(m_MqID, m_MsgBuffer, MAX_SIZE_OF_MSG_LENGTH, NULL);
    if( status != ERROR)
    {
        Msg = LogEntryToStr(m_MsgBuffer);
    }
    else
    {
        std::cout << "mq_receive failed: \n" << status;
    }
    return Msg;
#endif
}

/**************************************************************************//**
*
* \brief   - Create log message based on severity
*
* \param   - log_entry - Logger entry(e.g E_LOG_ALARM, E_LOG_EVENT etc.)
*
* \return  - Log message in string format
*
******************************************************************************/
std::string LoggerInterface::LogEntryToStr(char *log_entry)
{
    std::ostringstream stringStream;
    LogEntry* ptr_log_msg = reinterpret_cast<LogEntry*> (log_entry);
    if(ptr_log_msg != nullptr)
    {

        if (ptr_log_msg->severity == E_LOG_ALARM)
        {
            AlarmLogEntry *ptr_alarm_msg = reinterpret_cast<AlarmLogEntry*> (ptr_log_msg->byte_array);

            stringStream << "Logger[" << currentDateTime()  <<"] ID:" << std::hex << ptr_log_msg->log_id << " S:" << ptr_log_msg->severity << std::dec
                         << " Machine Name: " << ptr_alarm_msg->MachineName << ","
                         << " User Name: " << ptr_alarm_msg->UserName << ","
                         << " DateTime: " << ptr_alarm_msg->DateTime << ","
                         << " Alarm ID: " << ptr_alarm_msg->AlarmID << ","
                         << " Alarm Type: " << ptr_alarm_msg->AlarmType << ","
                         << " Alarm Sub Type: " << ptr_alarm_msg->AlarmSubType << ","
                         << " Weld Recipe Number: " <<  ptr_alarm_msg->WeldRecipeNumber << ","
                         << " Weld Recipe Version Number: " << ptr_alarm_msg->WeldRecipeVersionNumber << ","
                         << " Cycle Counter: " << ptr_alarm_msg->CycleCounter;
        }
        else if (ptr_log_msg->severity == E_LOG_EVENT)
        {
            EventLogEntry *ptr_event_msg = reinterpret_cast<EventLogEntry*> (ptr_log_msg->byte_array);

            stringStream << "Logger[" << currentDateTime()  <<"] ID:" << std::hex << ptr_log_msg->log_id << " S:" << ptr_log_msg->severity << std::dec
                         << " User Name: " << ptr_event_msg->UserName << ","
                         << " DateTime: " << ptr_event_msg->DateTime << ","
                         << " Event ID: " << ptr_event_msg->EventID << ","
                         << " Parameter ID: " << ptr_event_msg->ParameterID << ","
                         << " ASC Serial Number: " << ptr_event_msg->ASCSerialNumber << ","
                         << " HMI Serial Number: " <<  ptr_event_msg->HMISerialNumber << ","
                         << " ACSerialNumber: " << ptr_event_msg->ACSerialNumber << ","
                         << " PS Serial Number: " << ptr_event_msg->PSSerialNumber << ","
                         << " Old Parameters: " << ptr_event_msg->OldParameters << ","
                         << " New Parameters: " << ptr_event_msg->NewParameters << ","
                         << " Source: " << ptr_event_msg->SourceOfEvent << ","
                         << " Comment: " << ptr_event_msg->Comment;
        }
        else
        {
            stringStream << "Logger[" << currentDateTime()  <<"], TimeStamp: " << ptr_log_msg->timestamp << ", S: " << ptr_log_msg->severity << ",M: " << ptr_log_msg->byte_array << "\n";
        }
    }

    return stringStream.str();
}

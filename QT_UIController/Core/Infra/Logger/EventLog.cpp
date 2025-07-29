/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the event log related implementation

***************************************************************************/

#include <cstring>
#include "EventLog.h"
#include "DataLogger.h"

size_t EventLog::static_log_id=0;

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
EventLog::EventLog()
{
    pthread_mutex_init(&m_HistoricalEventLogDataMutex, nullptr);
    
    m_EventLogHistorySampleNumberToRead = 0;
    m_SendHistoricalEventLogReadRequest = true;
    m_IsLastEventLogUpdated             = false;
    
    //enroll to use logger functionality
    static_log_id = Logger::enroll(this);
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
EventLog::~EventLog()
{
    pthread_mutex_destroy(&m_HistoricalEventLogDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_EVENT_LOG_DATA
*           
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int EventLog::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_EVENT_LOG_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			//Send request to ASC to get the historical event log data
			case READ_HISTORICAL_EVENT_LOG_DATA:
			{
				retVal = 0;
				sendHistoricalEventLogReadRequestToASC(destination);
				break;
			}
			break;
			
			default:
			{				
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config,"EventLog GetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				break;
			}
		}
	}
	else
	{
		// error! invalid memory block id, default retVal (failure) will be returned
		// clear valid bit, reset size
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"EventLog GetData invalid case");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_EVENT_LOG_DATA            
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int EventLog::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	//check parameter
	if( (source != nullptr) && (source->id == MB_ID_EVENT_LOG_DATA) )
	{
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response coming from ASC for last event log data
				case READ_LAST_EVENT_LOG_DATA:
				{
					retVal = 0;
					processLastEventLogDataFromASC(source);
					break;
				}
				
				//Process response coming from ASC for historical event log data.
				case READ_HISTORICAL_EVENT_LOG_DATA:
				{
					retVal = 0;
					processHistoricalEventLogDataFromASC(source);
					break;
                }
                case SYNC_EVENTLOG_DATA_ON_DATETIME_FORMAT_CHANGE:
                {
                    retVal = 0;
                    processEventLogDataFromASConDateTimeFormatChange();
                    break;
                }
				default:
				{
					char  msg[buff_size_config] = {0};
					snprintf(msg,buff_size_config,"EventLog SetData default case");
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					//Error ! default retVal (failure) will be returned
				}
			}
		}
		else
		{
			retVal = 0;
		}
	}
	else
	{
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"EventLog SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - Send historical event log read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void EventLog::sendHistoricalEventLogReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
		if(m_SendHistoricalEventLogReadRequest == true)
		{
	       	int *Data = reinterpret_cast<int *>(destination->data);
			*Data = m_EventLogHistorySampleNumberToRead;
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendHistoricalEventLogReadRequest = false;
		}
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
	}
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}

/**************************************************************************//**
*
* \brief   - process the last event log data coming from ASC
*
* \param   - source - memory block holding the last event log data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void EventLog::processLastEventLogDataFromASC(const MEMORY_BLOCK *const source)
{
	EventLogEntry* EventLogData = reinterpret_cast< EventLogEntry*>(source->data);
	
	pthread_mutex_lock(&m_HistoricalEventLogDataMutex);
	m_HistoricalEventLogData.push_front(*EventLogData);
	if(m_HistoricalEventLogData.size() > MAX_NUM_OF_HISTORICAL_EVENT_LOGS_TO_SEND)
	{
		m_HistoricalEventLogData.pop_back();
	}
	pthread_mutex_unlock(&m_HistoricalEventLogDataMutex);
	m_IsLastEventLogUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the event log read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void EventLog::processEventLogDataFromASConDateTimeFormatChange()
{
    m_HistoricalEventLogData.clear();
    m_EventLogHistorySampleNumberToRead = 0;
    m_SendHistoricalEventLogReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - process the historical event log data coming from ASC
*
* \param   - source - memory block holding the historical event log data
*			 received from ASC
*			 
* \return  - none
*
******************************************************************************/
void EventLog::processHistoricalEventLogDataFromASC(const MEMORY_BLOCK *const source)
{
	int TotalSamples = *reinterpret_cast< int*>(source->data);
	bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
	EventLogEntry* EventLogData = reinterpret_cast< EventLogEntry*>(source->data + sizeof(int) + sizeof(bool));
	
	for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
	{
        m_HistoricalEventLogData.push_back(*EventLogData);
        EventLogData++;
	}

	m_EventLogHistorySampleNumberToRead = m_EventLogHistorySampleNumberToRead + TotalSamples;

	if(IsCompleteDataRead == true)
    {
		m_EventLogHistorySampleNumberToRead = 0;
		m_SendHistoricalEventLogReadRequest = false;
        m_IsLastEventLogUpdated = true;
	}
	else
	{
		m_SendHistoricalEventLogReadRequest = true;
	}
}

/**************************************************************************//**
*
* \brief   - Print Historical Event Log Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void EventLog::printHistoricalEventLog()
{
    if(m_HistoricalEventLogData.empty())
    {
        std::cout << "No Historical Event log Available" << std::endl;
    }
    else
    {
        pthread_mutex_lock(&m_HistoricalEventLogDataMutex);
        std::cout << "**********Historical Event Log Data**********" << std::endl;
        for (unsigned int Index = 0; Index < m_HistoricalEventLogData.size(); Index++)
        {
        	std::cout << "EventLogIndex: " << m_HistoricalEventLogData[Index].EventIndex << std::endl;
            std::cout << "DateTime: " << m_HistoricalEventLogData[Index].DateTime << std::endl;
            std::cout << "PSSerialNumber: " << m_HistoricalEventLogData[Index].PSSerialNumber << std::endl;
            std::cout << "ACSerialNumber: " << m_HistoricalEventLogData[Index].ACSerialNumber << std::endl;
            std::cout << "ASCSerialNumber: " << m_HistoricalEventLogData[Index].ASCSerialNumber << std::endl;
            std::cout << "HMISerialNumber: " << m_HistoricalEventLogData[Index].HMISerialNumber << std::endl;
            std::cout << "Username: " << m_HistoricalEventLogData[Index].UserName << std::endl;
            std::cout << "EventID: " << m_HistoricalEventLogData[Index].EventID << std::endl;
            std::cout << "ParameterID: " << m_HistoricalEventLogData[Index].ParameterID << std::endl;
            std::cout << "OldParam: " << m_HistoricalEventLogData[Index].OldParameters << std::endl;
            std::cout << "NewParam: " << m_HistoricalEventLogData[Index].NewParameters << std::endl;
            std::cout << "Commnet: " << m_HistoricalEventLogData[Index].Comment << std::endl;
            std::cout << "SourceEvent: " << m_HistoricalEventLogData[Index].SourceOfEvent << std::endl;
            std::cout << "*************************************" << std::endl;
        }
        pthread_mutex_unlock(&m_HistoricalEventLogDataMutex);
    }
}

/**************************************************************************//**
*
* \brief   - To get the status of the Event log data whether it is updated ot not.
*
* \param   - none
*
* \return  - bool - m_IsLastEventLogUpdated
*
******************************************************************************/
bool EventLog::GetIsLastEventLogUpdated()
{
    return m_IsLastEventLogUpdated;
}
/**************************************************************************//**
*
* \brief   - To get the latest Event log data.
*
* \param   - none
*
* \return  - deque
*
******************************************************************************/
std::deque<EventLogEntry> EventLog::GetHistoricalEventLogData()
{
    return m_HistoricalEventLogData;
}
/**************************************************************************//**
*
* \brief   - To set the m_IsLastEventLogUpdated variable after the data is beign read.
*
* \param   - bool - Value
*
* \return  - none
*
******************************************************************************/
void EventLog::SetIsLastEventLogTableUpdated(bool Value)
{
    m_IsLastEventLogUpdated = Value;
}

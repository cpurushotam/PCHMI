/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the alarm log related implementation

***************************************************************************/

#include <cstring>
#include "AlarmLog.h"
#include "DataLogger.h"

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
AlarmLog::AlarmLog()
{
    pthread_mutex_init(&m_HistoricalAlarmLogDataMutex, nullptr);
    
    m_AlarmLogHistorySampleNumberToRead  = 0;
    m_SendHistoricalAlarmLogReadRequest  = true;
    m_IsLastAlarmLogUpdated              = false;
    m_SendUpdateAlarmNotesRequest        = false;
    m_AlarmLogIndex                      = 0;
    memset(m_UpdateAlarmNotes, 0, sizeof(m_UpdateAlarmNotes));
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
AlarmLog::~AlarmLog()
{
    pthread_mutex_destroy(&m_HistoricalAlarmLogDataMutex);
}


/**************************************************************************//**
*
* \brief   - Send historical alarm log read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void AlarmLog::SendHistoricalAlarmLogReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendHistoricalAlarmLogReadRequest == true)
		{
	       	int *Data = reinterpret_cast<int *>(destination->data);
			*Data = m_AlarmLogHistorySampleNumberToRead;
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendHistoricalAlarmLogReadRequest = false;
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
* \brief   - Send add alarm notes request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void AlarmLog::SendAddAlarmNotesRequestToASC(MEMORY_BLOCK * const destination)
{
	//Check that sufficient buffer is available in memory block to hold the request data.
	if( destination->size >= (sizeof(m_AlarmLogIndex) + sizeof(m_UpdateAlarmNotes)) )
	{
		if(m_SendUpdateAlarmNotesRequest == true)
		{
			memcpy(reinterpret_cast<int*>(destination->data), &m_AlarmLogIndex, sizeof(m_AlarmLogIndex));
			strncpy(reinterpret_cast<char*>(destination->data + sizeof(m_AlarmLogIndex)), m_UpdateAlarmNotes, ALARM_NOTES_SIZE);

			destination->size = sizeof(m_AlarmLogIndex) + sizeof(m_UpdateAlarmNotes);

			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_SendUpdateAlarmNotesRequest = false;

			//Reset the alarm notes holding variable once the request is sent
			memset(m_UpdateAlarmNotes, 0, sizeof(m_UpdateAlarmNotes));
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
* \brief   - process the last alarm log data coming from ASC
*
* \param   - source - memory block holding the last alarm log data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void AlarmLog::ProcessLastAlarmLogDataFromASC(const MEMORY_BLOCK *const source)
{
	AlarmLogEntry* AlarmLogData = reinterpret_cast< AlarmLogEntry*>(source->data);
	
	pthread_mutex_lock(&m_HistoricalAlarmLogDataMutex);
	m_HistoricalAlarmLogData.push_front(*AlarmLogData);
	if(m_HistoricalAlarmLogData.size() > MAX_NUM_OF_HISTORICAL_ALARM_LOGS_TO_SEND)
	{
		m_HistoricalAlarmLogData.pop_back();
	}
	pthread_mutex_unlock(&m_HistoricalAlarmLogDataMutex);
	m_IsLastAlarmLogUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the historical alarm log data coming from ASC
*
* \param   - source - memory block holding the historical alarm log data
*			 received from ASC
*			 
* \return  - none
*
******************************************************************************/
void AlarmLog::ProcessHistoricalAlarmLogDataFromASC(const MEMORY_BLOCK *const source)
{
	int TotalSamples = *reinterpret_cast< int*>(source->data);
	bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
	AlarmLogEntry* AlarmLogData = reinterpret_cast< AlarmLogEntry*>(source->data + sizeof(int) + sizeof(bool));
	
	for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
	{
        m_HistoricalAlarmLogData.push_back(*AlarmLogData);
        AlarmLogData++;
	}

	m_AlarmLogHistorySampleNumberToRead = m_AlarmLogHistorySampleNumberToRead + TotalSamples;

	if(IsCompleteDataRead == true)
    {
		m_AlarmLogHistorySampleNumberToRead = 0;
		m_SendHistoricalAlarmLogReadRequest = false;
        m_IsLastAlarmLogUpdated = true;
	}
	else
	{
		m_SendHistoricalAlarmLogReadRequest = true;
	}
}

/**************************************************************************//**
*
* \brief   - process the alarm index and alarm note from alarm log data coming from ASC
*
* \param   - source - memory block holding the alarm log data received from ASC
*
* \return  - none
*
******************************************************************************/
void AlarmLog::ProcessAlarmNotesUpdateStatusFromASC(const MEMORY_BLOCK *const source)
{
	int Index = 0;
	AlarmLogEntry* AlarmLogData = reinterpret_cast< AlarmLogEntry*>(source->data);

	//Search for the AlarmLogIndex in m_HistoricalAlarmLogData
	for (auto it = m_HistoricalAlarmLogData.begin(); it != m_HistoricalAlarmLogData.end(); ++it)
	{
		if (it->AlarmLogIndex == AlarmLogData->AlarmLogIndex)
		{
			break;
		}
		++Index;
	}

	//Check if the AlarmLogIndex was found
	if (Index < m_HistoricalAlarmLogData.size())
	{
		// Copy the alarm log data to the destination
		pthread_mutex_lock(&m_HistoricalAlarmLogDataMutex);
		memcpy(&m_HistoricalAlarmLogData[Index], AlarmLogData, sizeof(AlarmLogEntry));
		pthread_mutex_unlock(&m_HistoricalAlarmLogDataMutex);
    }
    m_IsLastAlarmLogUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the AlarmLog read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void AlarmLog::ProcessHistoricalAlarmLogDataFromASConDatetimeFormatChg()
{
    m_HistoricalAlarmLogData.clear();
    m_AlarmLogHistorySampleNumberToRead = 0;
    m_SendHistoricalAlarmLogReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - Print Historical Alarm Log Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void AlarmLog::PrintHistoricalAlarmLog()
{
    if(m_HistoricalAlarmLogData.empty())
    {
        std::cout << "No Historical Alarm log Available" << std::endl;
    }
    else
    {
        pthread_mutex_lock(&m_HistoricalAlarmLogDataMutex);
        std::cout << "**********Historical Alarm Log Data**********" << std::endl;
        for (unsigned int Index = 0; Index < m_HistoricalAlarmLogData.size(); Index++)
        {
        	std::cout << "AlarmLogIndex: " <<m_HistoricalAlarmLogData[Index].AlarmLogIndex << std::endl;
			std::cout << "WeldRecipeNumber: " << m_HistoricalAlarmLogData[Index].WeldRecipeNumber << std::endl;
			std::cout << "WeldRecipeVersionNumber: " << m_HistoricalAlarmLogData[Index].WeldRecipeVersionNumber << std::endl;
			std::cout << "AlarmID: " << m_HistoricalAlarmLogData[Index].AlarmID << std::endl;
			std::cout << "AlarmType: " << m_HistoricalAlarmLogData[Index].AlarmType << std::endl;
			std::cout << "AlarmSubType: " << m_HistoricalAlarmLogData[Index].AlarmSubType << std::endl;
			std::cout << "CycleCounter: " << m_HistoricalAlarmLogData[Index].CycleCounter << std::endl;
			std::cout << "DateTime: " << m_HistoricalAlarmLogData[Index].DateTime << std::endl;
			std::cout << "MachineName: " << m_HistoricalAlarmLogData[Index].MachineName << std::endl;
			std::cout << "UserName: " << m_HistoricalAlarmLogData[Index].UserName << std::endl;
			std::cout << "AlarmNotes: " << m_HistoricalAlarmLogData[Index].AlarmNotes << std::endl;
            std::cout << "*************************************" << std::endl;
        }
        pthread_mutex_unlock(&m_HistoricalAlarmLogDataMutex);
    }
}

/**************************************************************************//**
*
* \brief   - Returns historical alarm log data.
*
* \param   - none.
*
* \return  - Historical alarm log data.
*
******************************************************************************/
std::deque<AlarmLogEntry> AlarmLog::GetHistoricalAlarmLogData()
{
    return m_HistoricalAlarmLogData;
}

/**************************************************************************//**
*
* \brief   - Returns flag IsAlarmLogUpdated when the data from ASC is updated.
*
* \param   - none.
*
* \return  - bool
*
******************************************************************************/
bool AlarmLog::IsAlarmLogUpdated()
{
    return m_IsLastAlarmLogUpdated;
}

/**************************************************************************//**
*
* \brief   - Updates flag IsAlarmLognUpdated when the data from ASC is updated.
*
* \param   - none.
*
* \return  - bool
*
******************************************************************************/
void AlarmLog::UpdateAlarmLogUpdatedFlag(bool Value)
{
    m_IsLastAlarmLogUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - Updates Notes for Alarm from HMI to ASC.
*
* \param   - int - index , std::string - AalrmNOtes.
*
* \return  - none
*
******************************************************************************/
void AlarmLog::SetAddAlarmNotesFlag(int index ,std::string AlarmNotes)
{
    std::strncpy(m_UpdateAlarmNotes, AlarmNotes.c_str(), ALARM_NOTES_SIZE);
    m_AlarmLogIndex = index;
    m_SendUpdateAlarmNotesRequest = true;
}


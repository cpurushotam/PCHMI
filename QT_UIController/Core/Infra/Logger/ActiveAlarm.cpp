/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the active alarm related implementation

***************************************************************************/

#include <cstring>
#include "ActiveAlarm.h"
#include "DataLogger.h"

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
ActiveAlarm::ActiveAlarm()
{
    pthread_mutex_init(&m_ActiveAlarmDataMutex, nullptr);
    
    m_ActiveAlarmSampleNumberToRead = 0;
    m_SendActiveAlarmReadRequest = true;
    m_SendEstopStatusReadRequest = true;
    m_IsLastActiveAlarmUpdated = false;
    m_SendResetActiveAlarmRequest = false;
    m_SendResetEstopRequest = false;
    m_SendResetAllActiveAlarmRequest = false;
    m_AlarmResetStatus = false;
    m_ResetActiveAlarmID = ALARM_NONE;
    m_EstopStatus = false;
    m_EstopResetResponse = false;
    m_HornClampOnAlrmStatus = false;
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
ActiveAlarm::~ActiveAlarm()
{
    pthread_mutex_destroy(&m_ActiveAlarmDataMutex);
}

/**************************************************************************//**
*
* \brief   - Send active alarm read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SendActiveAlarmReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendActiveAlarmReadRequest == true)
		{
	       	int *Data = reinterpret_cast<int *>(destination->data);
			*Data = m_ActiveAlarmSampleNumberToRead;
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendActiveAlarmReadRequest = false;
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
* \brief   - process the active alarm data coming from ASC
*
* \param   - source - memory block holding the active alarm data
*			 received from ASC
*			 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::ProcessActiveAlarmDataFromASC(const MEMORY_BLOCK *const source)
{
	int TotalSamples = *reinterpret_cast< int*>(source->data);
	bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
	ActiveAlarmEntry* ActiveAlarmData = reinterpret_cast< ActiveAlarmEntry*>(source->data + sizeof(int) + sizeof(bool));
	
	m_ActiveAlarmData.clear();

	for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
	{
        m_ActiveAlarmData.push_back(*ActiveAlarmData);
        ActiveAlarmData++;
	}

	m_ActiveAlarmSampleNumberToRead = m_ActiveAlarmSampleNumberToRead + TotalSamples;

	if(IsCompleteDataRead == true)
    {
		m_ActiveAlarmSampleNumberToRead = 0;
		m_SendActiveAlarmReadRequest = false;
        m_IsLastActiveAlarmUpdated = true;
	}
	else
	{
		m_SendActiveAlarmReadRequest = true;
	}
}

/**************************************************************************//**
*
* \brief   - Print Active Alarm Log Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::PrintActiveAlarm()
{
    if(m_ActiveAlarmData.empty())
    {
        std::cout << "No Active Alarm Available" << std::endl;
    }
    else
    {
        pthread_mutex_lock(&m_ActiveAlarmDataMutex);
        std::cout << "********** Active Alarm Data**********" << std::endl;
        for (unsigned int Index = 0; Index < m_ActiveAlarmData.size(); Index++)
        {
			std::cout << "IsResetRequired: " << static_cast<bool>(m_ActiveAlarmData[Index].IsResetRequired) << std::endl;
			std::cout << "IsLogRequired: " 	<< static_cast<bool>(m_ActiveAlarmData[Index].IsLogRequired) << std::endl;
			std::cout << "AlarmID: " << m_ActiveAlarmData[Index].AlarmID << std::endl;
            std::cout << "*************************************" << std::endl;
        }
        pthread_mutex_unlock(&m_ActiveAlarmDataMutex);
    }
}

/**************************************************************************//**
*
* \brief   - Returns active alarm log data.
*
* \param   - none.
*
* \return  - Active alarm log data.
*
******************************************************************************/
std::deque<ActiveAlarmEntry> ActiveAlarm::GetActiveAlarmLogData()
{
    return m_ActiveAlarmData;
}

/**************************************************************************//**
*
* \brief   - Returns flag IsActiveAlarmLogUpdated when the data from ASC is updated.
*
* \param   - none.
*
* \return  - bool
*
******************************************************************************/
bool ActiveAlarm::IsActiveAlarmLogUpdated()
{
    return m_IsLastActiveAlarmUpdated;
}

/**************************************************************************//**
*
* \brief   - Updates flag IsActiveAlarmLognUpdated when the data from ASC is updated.
*
* \param   - none.
*
* \return  - bool
*
******************************************************************************/
void ActiveAlarm::UpdateActiveAlarmLogUpdatedFlag(bool Value)
{
    m_IsLastActiveAlarmUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - Send reset active alarm request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SendResetActiveAlarmRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendResetActiveAlarmRequest == true)
		{
            uint16_t *Data = reinterpret_cast<uint16_t *>(destination->data);
			*Data = m_ResetActiveAlarmID;
            destination->size = sizeof(uint16_t);
			destination->config = VALID_BIT;
			m_SendResetActiveAlarmRequest = false;
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
* \brief   - Send reset all active alarms request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SendResetAllActiveAlarmsRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendResetAllActiveAlarmRequest == true)
		{
            uint16_t *Data = reinterpret_cast<uint16_t *>(destination->data);
			*Data = 0; //No Alarm ID is needed
            destination->size = sizeof(uint16_t);
			destination->config = VALID_BIT;
            m_SendResetAllActiveAlarmRequest = false;
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
* \brief   - process the reset active alarm data coming from ASC
*
* \param   - source - memory block holding the last active alarm data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::ProcessResetActiveAlarmDataFromASC(const MEMORY_BLOCK *const source)
{
    uint8_t* AlarmResetStatus = reinterpret_cast< uint8_t*>(source->data);

	m_AlarmResetStatus = *AlarmResetStatus;
}

/**************************************************************************//**
*
* \brief   - process the Estop status data coming from ASC
*
* \param   - source - memory block holding the estop status data
*			 received from ASC
*			 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::ProcessEstopStatusDataFromASC(const MEMORY_BLOCK *const source)
{
    uint8_t* EstopStatus = reinterpret_cast< uint8_t*>(source->data);

	m_EstopStatus = *EstopStatus;
}

/**************************************************************************//**
*
* \brief   - process the reset estop data coming from ASC
*
* \param   - source - memory block holding the estop reset response data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::ProcessEstopResetRespFromASC(const MEMORY_BLOCK *const source)
{
    uint8_t* EstopResetResp = reinterpret_cast< uint8_t*>(source->data);

    m_EstopResetResponse = *EstopResetResp;
}

/**************************************************************************//**
*
* \brief   - Send Estop status read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SendEstopStatusReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendEstopStatusReadRequest == true)
		{
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendEstopStatusReadRequest = false;
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
* \brief   - Send reset active alarm request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SendEstopResetRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendResetEstopRequest == true)
		{
            destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendResetEstopRequest = false;
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
* \brief   - Set the alarm ID to be reset
*
* \param   - ALARM_IDS
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SetAlarmIDtoBeReset(ALARM_IDS id)
{
	m_ResetActiveAlarmID = id;
    m_SendResetActiveAlarmRequest = true;
}

/**************************************************************************//**
*
* \brief   - Set reset all active alarm request
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SetResetAllActiveAlarm()
{
    m_SendResetAllActiveAlarmRequest = true;
}

/**************************************************************************//**
*
* \brief   - Get the reset status
*
* \param   - none
*
* \return  - UINT8 status
*
******************************************************************************/
uint8_t ActiveAlarm::GetAlarmResetStatus()
{
	return m_AlarmResetStatus;
}

/**************************************************************************//**
*
* \brief   - Get the estop status
*
* \param   - none
*
* \return  - UINT8 status
*
******************************************************************************/
uint8_t ActiveAlarm::GetEstopStatus()
{
	return m_EstopStatus;
}

/**************************************************************************//**
*
* \brief   - Set estop reset request
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::SetEstopResetRequest()
{
    m_SendResetEstopRequest = true;
}

/**************************************************************************//**
*
* \brief   - Get the estop reset response
*
* \param   - none
*
* \return  - UINT8 status
*
******************************************************************************/
uint8_t ActiveAlarm::GetEstopResetResponse()
{
	return m_EstopResetResponse;
}

/**************************************************************************//**
*
* \brief   - process the horn clamp on alarm status data coming from ASC
*
* \param   - source - memory block holding the horn clamp on alarm status data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ActiveAlarm::ProcessHornClampOnAlarmStatusFromASC(const MEMORY_BLOCK *const source)
{
    uint8_t* HornClampOnAlrmStatus = reinterpret_cast< uint8_t*>(source->data);

    m_HornClampOnAlrmStatus = *HornClampOnAlrmStatus;
}

/**************************************************************************//**
*
* \brief   - Get the horn clamp on alarm status
*
* \param   - none
*
* \return  - UINT8 status
*
******************************************************************************/
uint8_t ActiveAlarm::GetHornClampOnAlrmStatus()
{
	return m_HornClampOnAlrmStatus;
}
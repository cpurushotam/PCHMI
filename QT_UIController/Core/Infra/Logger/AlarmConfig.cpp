/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the alarm configuration related implementation

***************************************************************************/

#include <cstring>
#include "AlarmConfig.h"
#include "DataLogger.h"

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
AlarmConfig::AlarmConfig()
{
    pthread_mutex_init(&m_AlarmConfigDataMutex, nullptr);
    m_SendAlarmConfigReadRequest = true;
    m_SendResetToDefaultAlarmRequest = false;
    m_SendAlarmConfigSaveRequest = false;
    m_IsLastAlarmConfigurationUpdated = false;
    m_AlarmConfigUpdateStatus = ALARM_CONFIG_UPDATE_FAILURE;
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
AlarmConfig::~AlarmConfig()
{
    pthread_mutex_destroy(&m_AlarmConfigDataMutex);
}

/**************************************************************************//**
*
* \brief   - Send alarm config read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void AlarmConfig::SendAlarmConfigReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(int))
	{
        if(m_SendAlarmConfigReadRequest == true)
		{
            destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendAlarmConfigReadRequest = false;
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
* \brief   - Send alarm config save request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void AlarmConfig::SendAlarmConfigSaveRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(AlarmConfiguration))
	{
        if(m_SendAlarmConfigSaveRequest == true)
        {
            AlarmConfiguration* AlarmConfigData = reinterpret_cast<AlarmConfiguration*>(destination->data);
        
        	pthread_mutex_lock(&m_AlarmConfigDataMutex);
        	memcpy(AlarmConfigData,&m_AlarmConfig,sizeof(m_AlarmConfig));
        	pthread_mutex_unlock(&m_AlarmConfigDataMutex);
        	
			destination->size = sizeof(AlarmConfiguration);
			destination->config = VALID_BIT;
			m_SendAlarmConfigSaveRequest = false;
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
* \brief   - Send alarm config reset to default request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* 
* \return  - none
*
******************************************************************************/
void AlarmConfig::SendAlarmConfigResetToDefaultRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
	{
        if(m_SendResetToDefaultAlarmRequest == true)
        {
            destination->size = sizeof(int);
			destination->config = VALID_BIT;
			m_SendResetToDefaultAlarmRequest = false;
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
* \brief   - process the alarm config data response coming from ASC
*
* \param   - source - memory block holding the alarm config data received from ASC
*
* \return  - none
*
******************************************************************************/
void AlarmConfig::ProcessAlarmConfigDataFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming alarm config data to structure member variable
	AlarmConfiguration *AlarmConfigData = reinterpret_cast<AlarmConfiguration*>(source->data);
	pthread_mutex_lock(&m_AlarmConfigDataMutex);
	memcpy(&m_AlarmConfig, AlarmConfigData, sizeof(AlarmConfiguration));
    pthread_mutex_unlock(&m_AlarmConfigDataMutex);
    m_IsLastAlarmConfigurationUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the alarm config update status response coming from ASC
*
* \param   - source - memory block holding the alarm config update status received from ASC
*
* \return  - none
*
******************************************************************************/
void AlarmConfig::ProcessAlarmConfigUpdateStatusFromASC(const MEMORY_BLOCK *const source)
{
	ALARM_CONFIG_UPDATE_STATUS *AlarmConfigUpdateStatus = reinterpret_cast<ALARM_CONFIG_UPDATE_STATUS*>(source->data);
	
    m_AlarmConfigUpdateStatus = *AlarmConfigUpdateStatus;
}

/**************************************************************************//**
* 
* \brief  - This method is used to get the alarm config update status. 
*
* \param  - None
*
* \return - Returns fetched value from ProcessAlarmConfigUpdateStatusFromASC().
*
******************************************************************************/
ALARM_CONFIG_UPDATE_STATUS AlarmConfig::GetAlarmConfigUpdateStatus()
{
	return m_AlarmConfigUpdateStatus;
}

/**************************************************************************//**
*
* \brief   - Print Alarm Config Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void AlarmConfig::PrintAlarmConfig()
{
    if(sizeof(m_AlarmConfig) == 0)
    {
        std::cout << "Requested Alarm config data is empty" << std::endl;
    }
    else
    {
        std::cout << "m_AlarmConfig.OverloadAlarmActions.ResetRequired: "  << static_cast<bool>(m_AlarmConfig.OverloadAlarmActions.ResetRequired) << std::endl;
        std::cout << "m_AlarmConfig.OverloadAlarmActions.LogAlarm: "  << static_cast<bool>(m_AlarmConfig.OverloadAlarmActions.LogAlarm) << std::endl;
        std::cout << "m_AlarmConfig.OverloadAlarmActions.GeneralAlarm: "  << static_cast<bool>(m_AlarmConfig.OverloadAlarmActions.GeneralAlarm) << std::endl;
        std::cout << "m_AlarmConfig.OverloadAlarmActions.CycleCounter: "  << static_cast<bool>(m_AlarmConfig.OverloadAlarmActions.CycleCounter) << std::endl;
        std::cout << "m_AlarmConfig.OverloadAlarmActions.CustomAlarmOutput: "  << static_cast<bool>(m_AlarmConfig.OverloadAlarmActions.CustomAlarmOutput) << std::endl;

        std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

        std::cout << "m_AlarmConfig.HardwareFailureAlarmActions.ResetRequired: "  << static_cast<bool>(m_AlarmConfig.HardwareFailureAlarmActions.ResetRequired) << std::endl;
        std::cout << "m_AlarmConfig.HardwareFailureAlarmActions.LogAlarm: "  << static_cast<bool>(m_AlarmConfig.HardwareFailureAlarmActions.LogAlarm) << std::endl;
        std::cout << "m_AlarmConfig.HardwareFailureAlarmActions.GeneralAlarm: "  << static_cast<bool>(m_AlarmConfig.HardwareFailureAlarmActions.GeneralAlarm )<< std::endl;
        std::cout << "m_AlarmConfig.HardwareFailureAlarmActions.CycleCounter: "  << static_cast<bool>(m_AlarmConfig.HardwareFailureAlarmActions.CycleCounter) << std::endl;
        std::cout << "m_AlarmConfig.HardwareFailureAlarmActions.CustomAlarmOutput: "  << static_cast<bool>(m_AlarmConfig.HardwareFailureAlarmActions.CustomAlarmOutput) << std::endl;
    }
}

/**************************************************************************//**
*
* \brief   - Set the AlarmConfiguration checkboxes values at HMI from ASC.
*
* \param   - none
*
* \return  - AlarmConfiguration structure.
*
******************************************************************************/
AlarmConfiguration AlarmConfig::GetAlarmConfiguration()
{
    return m_AlarmConfig;
}
/**************************************************************************//**
*
* \brief   - Returns flag m_IsLastAlarmConfigurationUpdated when the data from ASC is updated.
*
* \param   - none
*
* \return  - bool - m_IsLastAlarmConfigurationUpdated
*
******************************************************************************/
bool AlarmConfig :: IsAlarmConfigurationUpdated()
{
    return m_IsLastAlarmConfigurationUpdated;
}
/**************************************************************************//**
*
* \brief   - Send save request to ASC when user presses the save button with the updated values.
*
* \param   - AlarmConfiguration structure.
*
* \return  - none
*
******************************************************************************/
void  AlarmConfig::saveAlarmConfigValues(AlarmConfiguration alarmConfiguration)
{
     m_AlarmConfig = alarmConfiguration;
     m_SendAlarmConfigSaveRequest =true;
}

/**************************************************************************//**
*
* \brief   - Set the ResetToDefault Alarm Request from HMI.
*
* \param   - bool value.
*
* \return  - none
*
******************************************************************************/
void  AlarmConfig ::setResetToDefaultAlarmRequest(bool value)
{
    m_SendResetToDefaultAlarmRequest =value;
}

/**************************************************************************//**
*
* \brief   - Set the AlarmConfig Save Request from HMI.
*
* \param   - bool value.
*
* \return  - none
*
******************************************************************************/
void  AlarmConfig ::ResetAlarmConfigurationUpdatedFlag ()
{
    m_IsLastAlarmConfigurationUpdated = false;
}

/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of event log support.

***************************************************************************/

#include "EventLogSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
EventLogSupport::EventLogSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of event log feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int EventLogSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case EVENT_LOG_NOT_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Event Logs NOT Supported");
		}
		break;
		
		case EVENT_LOG_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Event Logs Supported");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set event log configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of event log feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int EventLogSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of event log feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int EventLogSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case EVENT_LOG_NOT_SUPPORTED:
		break;
		case EVENT_LOG_SUPPORTED:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in event log configuration");
			status = -1;
		}
		break;
	}
	return status;
}

/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Standard PC Utility support.

***************************************************************************/

#include "PCUtilitySupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
PCUtilitySupport::PCUtilitySupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of PC Utility feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int PCUtilitySupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case PC_UTILITY_NOT_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "PC Utility NOT Supported");
		}
		break;
		
		case PC_UTILITY_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "PC Utility Supported");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set PC Utility configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of PC Utility feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int PCUtilitySupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of PC Utility feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int PCUtilitySupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case PC_UTILITY_NOT_SUPPORTED:
		break;
		case PC_UTILITY_SUPPORTED:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in PC Utility configuration");
			status = -1;
		}
		break;
	}
	return status;
}

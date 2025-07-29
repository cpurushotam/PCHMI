/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of User Access Level type support.

***************************************************************************/

#include "UserAccessLevelSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
UserAccessLevelSupport::UserAccessLevelSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of User Access Level Type feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int UserAccessLevelSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case STANDARD_USER_ACCESS_LEVEL:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "User Access Level Type is Standard");
		}
		break;
		
		case ADVANCED_USER_ACCESS_LEVEL:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "User Access Level Type is Advanced");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "SetConfigParameter - error in User Access Level Type config");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of User Access Level Type feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int UserAccessLevelSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of User Access Level Type feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int UserAccessLevelSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case STANDARD_USER_ACCESS_LEVEL:
		break;
		case ADVANCED_USER_ACCESS_LEVEL:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "VerifyConfigParameter - error in User Access Level Type config");
			status = -1;
		}
		break;
	}
	return status;
}

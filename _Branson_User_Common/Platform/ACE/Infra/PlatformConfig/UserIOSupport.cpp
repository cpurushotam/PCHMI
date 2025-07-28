/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of User IO support.

***************************************************************************/

#include "UserIOSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
UserIOSupport::UserIOSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of User IO feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int UserIOSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case USER_IO_NOT_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "User IO NOT Supported");
		}
		break;
		
		case USER_IO_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "User IO Supported");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "SetConfigParameter - error in User IO config");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of User IO feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int UserIOSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of User IO feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int UserIOSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case USER_IO_NOT_SUPPORTED:
		break;
		case USER_IO_SUPPORTED:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "VerifyConfigParameter - error in User IO config");
			status = -1;
		}
		break;
	}
	return status;
}

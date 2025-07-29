/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of LDAP support.

***************************************************************************/

#include "LDAPSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
LDAPSupport::LDAPSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of LDAP feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int LDAPSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case LDAP_NOT_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "LDAP NOT Supported");
		}
		break;
		
		case LDAP_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "LDAP Supported");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set LDAP configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of LDAP feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int LDAPSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of LDAP feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int LDAPSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case LDAP_NOT_SUPPORTED:
		break;
		case LDAP_SUPPORTED:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in LDAP configuration");
			status = -1;
		}
		break;
	}
	return status;
}

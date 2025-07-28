/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of fieldbus support.

***************************************************************************/

#include "FieldbusSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
FieldbusSupport::FieldbusSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Fieldbus Type feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int FieldbusSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case NO_FIELDBUS:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Fieldbus NOT supported");
		}
		break;
		
		case ETHERNET_IP_FIELDBUS:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Fieldbus - Ethernet/IP supported");
		}
		break;
		
		case PROFINET_FIELDBUS:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Fieldbus - Profinet supported");
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set Fieldbus Type configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Fieldbus Type feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int FieldbusSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Type Fieldbus feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int FieldbusSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case NO_FIELDBUS:
		break;
		case ETHERNET_IP_FIELDBUS:
		break;
		case PROFINET_FIELDBUS:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in Fieldbus Type configuration");
			status = -1;
		}
		break;
	}
	return status;
}

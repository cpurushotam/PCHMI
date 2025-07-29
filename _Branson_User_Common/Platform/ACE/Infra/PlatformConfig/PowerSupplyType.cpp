/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of power supply type support.

***************************************************************************/

#include "PowerSupplyType.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
PowerSupplyTypeSupport::PowerSupplyTypeSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Power Supply Type feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int PowerSupplyTypeSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case P_2100_POWER_SUPPLY:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Power Supply Type is P_2100");
		}
		break;
		
		case P_2200_POWER_SUPPLY:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Power Supply Type is P_2200");
		}
		break;
	
		case P_2300_POWER_SUPPLY:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "Power Supply Type is P_2300, NOT Supported yet");
			status = -1; //Since Support for P_2300 Power Supply is not added yet, return -1.
		}
		break;
			
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set Power Supply Type configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Power Supply Type feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int PowerSupplyTypeSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Power Supply Type feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int PowerSupplyTypeSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case P_2100_POWER_SUPPLY:
		break;
		case P_2200_POWER_SUPPLY:
		break;
		
		case P_2300_POWER_SUPPLY:
		{
			//Since Support for P_2300 Power Supply is not added yet, return -1.
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in P2300 Power Supply Type configuration");
			status = -1;
		}
		break;	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in Power Supply Type configuration");
			status = -1;
		}
		break;
	}
	return status;
}

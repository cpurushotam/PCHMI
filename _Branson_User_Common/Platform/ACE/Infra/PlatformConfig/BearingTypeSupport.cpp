/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Bearing Type support.

***************************************************************************/

#include "BearingTypeSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
BearingTypeSupport::BearingTypeSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Bearing Type feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int BearingTypeSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{				
		case STANDARD_BEARING:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Standard Bearing supported");
		}
		break;
		
		case STAINLESS_STEEL_BEARING:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Stainless Steel Bearing supported");
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "Error to set bearing type configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Bearing Type feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int BearingTypeSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Bearing Type feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int BearingTypeSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case STANDARD_BEARING:
		break;
		case STAINLESS_STEEL_BEARING:
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in Bearing Type configuration");
			status = -1;
		}
		break;
	}
	return status;
}

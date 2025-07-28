/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Batch Control support.

***************************************************************************/

#include "BatchControlSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
BatchControlSupport::BatchControlSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Batch Control feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int BatchControlSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case BATCH_CONTROL_NOT_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Batch Control NOT Supported");
		}
		break;
		
		case BATCH_CONTROL_SUPPORTED:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Batch Control Supported");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set Batch Control configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Batch Control feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int BatchControlSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Batch Control feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int BatchControlSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case BATCH_CONTROL_NOT_SUPPORTED:
		break;
		case BATCH_CONTROL_SUPPORTED:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "Error in Batch Control config");
			status = -1;
		}
		break;
	}
	return status;
}

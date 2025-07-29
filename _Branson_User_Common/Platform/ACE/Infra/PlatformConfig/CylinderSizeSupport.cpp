/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Cylinder Size support.

***************************************************************************/

#include "CylinderSizeSupport.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
CylinderSizeSupport::CylinderSizeSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Cylinder Size feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int CylinderSizeSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{				
		case FORTY_MM_CYLINDER:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Cylinder Size 40 mm supported");
		}
		break;
		
		case FIFTY_MM_CYLINDER:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Cylinder Size 50 mm supported");
		}
		break;
		
		case SIXTY_THREE_MM_CYLINDER:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Cylinder Size 63 mm supported");
		}
		break;
		
		case EIGHTY_MM_CYLINDER:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Cylinder Size 80 mm supported");
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set Cylinder Size configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Cylinder Size feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int CylinderSizeSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Cylinder Size feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int CylinderSizeSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case FORTY_MM_CYLINDER:
		break;
		case FIFTY_MM_CYLINDER:
		break;
		case SIXTY_THREE_MM_CYLINDER:
		break;
		case EIGHTY_MM_CYLINDER:
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in Cylinder Size configuration");
			status = -1;
		}
		break;
	}
	return status;
}

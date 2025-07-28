/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of stroke length support.

***************************************************************************/

#include "StrokeLength.h"
#include "PlatformConfig.h"

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
StrokelengthSupport::StrokelengthSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Set configuration value of Stroke Length feature.
*
* \param   - ConfigValue - Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int StrokelengthSupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case HUNDRED_MM_STROKE_LENGTH:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Stroke Length 100 mm supported");
		}
		break;
				
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "SetConfigParameter - error in Stroke Length config");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of Stroke Length feature.
*
* \param   - None
*
* \return  - configuration value
*
******************************************************************************/
int StrokelengthSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify configuration value of Stroke Length feature.
*
* \param   - ConfigValue: Configuration Value
*
* \return  - 0 on success, -1 on error.
*
*******************************************************************************/
int StrokelengthSupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case HUNDRED_MM_STROKE_LENGTH:
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ERROR, "VerifyConfigParameter - error in Stroke Length config");
			status = -1;
		}
		break;
	}
	return status;
}

/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares ActuatorConfig Class - Responsible for actuator Configuration
 	 	 	 	 	 	 	 	 1. Handle type of actuator configuration

--------------------------- REVISION HISTORY ------------------------------
 rev1: 15/09/2023 - Initial implementation.
 	 	 	 	 	Support for no and manual actuator configuration. 

***************************************************************************/

#include "ActuatorInit.h"

/**************************************************************************//**
* \brief   - Initialization of ActuatorInit class .
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
ActuatorInit::ActuatorInit()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Handle supported feature of actuator configuration.
*
* \param   - int - Type of actuator
*
* \return  - status 0 on success else -1-.
*
*******************************************************************************/
int ActuatorInit::SetConfigParameter( int ActuatorType)
{
	int status = 0;
	m_ConfiguredValue = ActuatorType;
	
	switch (ActuatorType)
	{
		case NO_ACTUATOR:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "NO Actuator Configured");
		}
		break;

		case ACTUATOR_MANUAL:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Manual Actuator Configured");
		}
		break;
		
		case ACTUATOR_ELECTRONIC:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Electronic Actuator Configured");
		}
		break;

		default:
			status = -1;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of actuator configuration.
*
* \param   - None
*
* \return  - int Type.--> Actuator type.
*
******************************************************************************/
int ActuatorInit::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify supported feature of actuator configuration.
*
* \param   - int - Type of actuator
*
* \return  - status 0 on success else -1-.
*
*******************************************************************************/
int ActuatorInit::VerifyConfigParameter( int ActuatorType)
{
    int status = 0;

    switch (ActuatorType)
    {
        case NO_ACTUATOR:
        break;
        case ACTUATOR_MANUAL:
        break;
        case ACTUATOR_ELECTRONIC:
        break;	
        default:
            status = -1;
    }

    return status;
}

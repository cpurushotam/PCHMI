/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of number of amplitude steps and pressure steps.

***************************************************************************/

#include "AmplitudeAndPressureStepsSupport.h"
#include "PowerSupplyType.h"
#include "ActuatorInit.h"
#include "PlatformConfig.h"
#if !defined(__RTP__)
////When compiled on HMI (Ubuntu, Raspberry PI)
#include "MultiwelderInterface.h"
#endif

size_t AmplitudeAndPressureStepsSupport::m_StaticLogId = 0;

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
AmplitudeAndPressureStepsSupport::AmplitudeAndPressureStepsSupport()
{
    m_StaticLogId = Logger::enroll(this);
}

/**************************************************************************//**
* 
* \brief   - Return the number of amplitude steps supported based 
* 			 on the JSON Configuration value for Power Supply Type
*
* \param   - None.
*
* \return  - Number of amplitude steps supported
*
******************************************************************************/
unsigned int AmplitudeAndPressureStepsSupport::GetSupportedAmplitudeStepsFromJSON()
{
	unsigned int SupportedAmplitudeSteps = 0;
	
	int PowerSupplyType = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	PowerSupplyType = PlatformConfig::GetConfig(POWER_SUPPLY_TYPE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	PowerSupplyType = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), POWER_SUPPLY_TYPE_KEY);
#endif
	
	switch (PowerSupplyType)
	{
		case P_2100_POWER_SUPPLY: 
		{
			SupportedAmplitudeSteps = SUPPORTED_AMPLITUDE_STEPS_P_2100_PS;	
		}
		break;
		
		case P_2200_POWER_SUPPLY: 
		{
			SupportedAmplitudeSteps = SUPPORTED_AMPLITUDE_STEPS_P_2200_PS;		
		}
		break;
				
		case P_2300_POWER_SUPPLY: 
		{
			SupportedAmplitudeSteps = SUPPORTED_AMPLITUDE_STEPS_P_2300_PS;		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Invalid Power Supply type to Get Amplitude Steps.");
		}
		break;
	}
	
	return SupportedAmplitudeSteps;
}


/**************************************************************************//**
*
* \brief   - Return the number of pressure steps supported based
* 			 on the JSON Configuration value  for Power Supply Type
*
* \param   - None.
*
* \return  - Number of pressure steps supported
*
******************************************************************************/
unsigned int AmplitudeAndPressureStepsSupport::GetSupportedPressureStepsFromJSON()
{
	unsigned int SupportedPressureSteps = 0;
	int PowerSupplyType = -1;
	int ActuatorType = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	PowerSupplyType = PlatformConfig::GetConfig(POWER_SUPPLY_TYPE_KEY);
	ActuatorType = PlatformConfig::GetConfig(ACTUATOR_TYPE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	PowerSupplyType = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), POWER_SUPPLY_TYPE_KEY);
	ActuatorType = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), ACTUATOR_TYPE_KEY);
#endif
	switch (PowerSupplyType)
	{
		case P_2100_POWER_SUPPLY: 
		{
			SupportedPressureSteps = SUPPORTED_PRESSURE_STEPS_P_2100_PS;		
		}
		break;
		
		case P_2200_POWER_SUPPLY: 
		{
			if(ActuatorType == NO_ACTUATOR || ActuatorType == ACTUATOR_MANUAL)
			{
				SupportedPressureSteps = SUPPORTED_PRESSURE_STEPS_NO_ACTUATOR_OR_MANUAL_ACTUATOR;		
			}
			else if(ActuatorType == ACTUATOR_ELECTRONIC || ActuatorType == ACTUATOR_ELECTRONIC_PLUS)
			{
				SupportedPressureSteps = SUPPORTED_PRESSURE_STEPS_P_2200_PS;		
			}
		}
		break;
				
		case P_2300_POWER_SUPPLY: 
		{
			if(ActuatorType == NO_ACTUATOR || ActuatorType == ACTUATOR_MANUAL)
			{
				SupportedPressureSteps = SUPPORTED_PRESSURE_STEPS_NO_ACTUATOR_OR_MANUAL_ACTUATOR;		
			}
			else if(ActuatorType == ACTUATOR_ELECTRONIC || ActuatorType == ACTUATOR_ELECTRONIC_PLUS)
			{
				SupportedPressureSteps = SUPPORTED_PRESSURE_STEPS_P_2300_PS;		
			}		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Error to get Supported Pressure Steps From JSON");
		}
		break;
	}
	
	return SupportedPressureSteps;
}


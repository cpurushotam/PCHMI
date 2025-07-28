/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of power level and system frequency.

***************************************************************************/

#include "PowerLevelSysFrequencySupport.h"
#include "PlatformConfig.h"
#if !defined(__RTP__)
////When compiled on HMI (Ubuntu, Raspberry PI)
#include "MultiwelderInterface.h"
#endif

size_t PowerLevelSysFrequencySupport::m_StaticLogId = 0;

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
PowerLevelSysFrequencySupport::PowerLevelSysFrequencySupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
    m_StaticLogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Handle supported feature of power level and system frequency configuration.
*
* \param   - ConfigValue - power level and system frequency Configuration Value
*
* \return  - status 0 on success else -1 on error.
*
*******************************************************************************/
int PowerLevelSysFrequencySupport::SetConfigParameter( int ConfigValue)
{
	int status = 0;
	m_ConfiguredValue = ConfigValue;
	
	switch (ConfigValue)
	{
		case TWENTY_KHZ_1250_WATT:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "TWENTY_KHZ_1250_WATT power level configured");
		}
		break;
		
		case TWENTY_KHZ_2500_WATT:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "TWENTY_KHZ_2500_WATT power level configured");
		}
		break;
		
		case TWENTY_KHZ_4000_WATT:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "TWENTY_KHZ_4000_WATT power level configured");
		}
		break;
		
		case THIRTY_KHZ_1500_WATT:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "THIRTY_KHZ_1500_WATT power level configured");
		}
		break;
		
		case FORTY_KHZ_800_WATT:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "FORTY_KHZ_800_WATT power level configured");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to set power level and system frequency configuration");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of power level and system frequency configuration.
*
* \param   - None
*
* \return  - Power level and system frequency configuration value
*
******************************************************************************/
int PowerLevelSysFrequencySupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify supported feature of storage configuration.
*
* \param   - ConfigValue: power level and system frequency configuration Value
*
* \return  - status 0 on success else -1 on error.
*
*******************************************************************************/
int PowerLevelSysFrequencySupport::VerifyConfigParameter(int ConfigValue) 
{
	int status = 0;
	
	switch (ConfigValue)
	{
		case TWENTY_KHZ_1250_WATT:
		break;
		case TWENTY_KHZ_2500_WATT:
		break;
		case TWENTY_KHZ_4000_WATT:
		break;
		case THIRTY_KHZ_1500_WATT:
		break;
		case FORTY_KHZ_800_WATT:
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error in power level and system frequency configuration");
			status = -1;
		}
		break;
	}
	return status;
}

/******************************************************************************
* \brief - Get the maximum power in watts value as per JSON Config
*
* \param - none
*
* \return - maximum power in watts supported as per JSON Config
*
******************************************************************************/
float PowerLevelSysFrequencySupport::GetMaxPowerFromJSON()
{
	float MaxPower = 0.0f;
	int ConfigValue = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	ConfigValue = PlatformConfig::GetConfig(POWER_LEVEL_SYSTEM_FREQUENCY_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	ConfigValue = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), POWER_LEVEL_SYSTEM_FREQUENCY_KEY);
#endif
	
	switch (ConfigValue)
	{
		case TWENTY_KHZ_1250_WATT: 
		{
			MaxPower = MAX_POWER_VALUE_1250_WATT;	
		}
		break;
		
		case TWENTY_KHZ_2500_WATT: 
		{
			MaxPower = MAX_POWER_VALUE_2500_WATT;	
		}
		break;
		
		case TWENTY_KHZ_4000_WATT: 
		{
			MaxPower = MAX_POWER_VALUE_4000_WATT;	
		}
		break;
		
		case THIRTY_KHZ_1500_WATT: 
		{
			MaxPower = MAX_POWER_VALUE_1500_WATT;	
		}
		break;
		
		case FORTY_KHZ_800_WATT: 
		{
			MaxPower = MAX_POWER_VALUE_800_WATT;	
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_NOTIFICATION, "Error to Get the maximum power");
		}
		break;
	}	
	return MaxPower;
}

/******************************************************************************
* \brief - Get the  system frequency value as per JSON Config
* \param - none
* \return - maximum number of weld results that can be stored in database
*			as per JSON Config
******************************************************************************/
int PowerLevelSysFrequencySupport::GetSystemFrequencyFromJSON()
{
	int SystemFrequency = FREQ_UNKNOWN ;
	int ConfigValue = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	ConfigValue = PlatformConfig::GetConfig(POWER_LEVEL_SYSTEM_FREQUENCY_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	ConfigValue = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), POWER_LEVEL_SYSTEM_FREQUENCY_KEY);
#endif
	
	switch (ConfigValue)
	{
		case TWENTY_KHZ_1250_WATT: 
		{
            SystemFrequency = FREQ_20KHZ;
		}
		break;
		
		case TWENTY_KHZ_2500_WATT: 
		{
            SystemFrequency = FREQ_20KHZ;
		}
		break;
		
		case TWENTY_KHZ_4000_WATT: 
		{
            SystemFrequency = FREQ_20KHZ;
		}
		break;
		
		case THIRTY_KHZ_1500_WATT: 
		{
            SystemFrequency = FREQ_30KHZ;
		}
		break;
		
		case FORTY_KHZ_800_WATT: 
		{
            SystemFrequency = FREQ_40KHZ;
		}
		break;
		
		default:
		{
			SystemFrequency=FREQ_UNKNOWN;
		}
		break;
	}	
	return SystemFrequency;
}

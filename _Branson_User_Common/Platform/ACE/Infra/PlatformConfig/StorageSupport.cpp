/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of storage capacity.

***************************************************************************/

#include "StorageSupport.h"
#include "PlatformConfig.h"
#if !defined(__RTP__)
////When compiled on HMI (Ubuntu, Raspberry PI)
#include "MultiwelderInterface.h"
#endif

size_t StorageSupport::m_StaticLogId = 0;

/**************************************************************************//**
* \brief   - Constructor.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
StorageSupport::StorageSupport()
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);
    m_StaticLogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Handle supported feature of storage configuration.
*
* \param   - StorageConfig - Storage Configuration Value
*
* \return  - status 0 on success else -1 on error.
*
*******************************************************************************/
int StorageSupport::SetConfigParameter( int StorageConfig)
{
	int status = 0;
	m_ConfiguredValue = StorageConfig;
	
	switch (StorageConfig)
	{
		case BASIC_STORAGE:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Basic Storage configured");
		}
		break;
		
		case ADVANCE_STORAGE:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Advance Storage configured");
		}
		break;
		
		case ELITE_STORAGE:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Elite Storage configured");
		}
		break;
	
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "SetConfigParameter - error in storage config");
			status = -1;
		}
		break;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Return configured value of storage configuration.
*
* \param   - None
*
* \return  -storage configuration value
*
******************************************************************************/
int StorageSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify supported feature of storage configuration.
*
* \param   - StorageConfig: storage Configuration Value
*
* \return  - status 0 on success else -1 on error.
*
*******************************************************************************/
int StorageSupport::VerifyConfigParameter(int StorageConfig) 
{
	int status = 0;
	
	switch (StorageConfig)
	{
		case BASIC_STORAGE:
		break;
		case ADVANCE_STORAGE:
		break;
		case ELITE_STORAGE:
		break;
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_EVENT, "VerifyConfigParameter - error in storage config");
			status = -1;
		}
		break;
	}
	return status;
}

/******************************************************************************
* \brief - Get the maximum number of recipes supported as per JSON Config
*
* \param - none
*
* \return - maximum number of recipes that are supported as per JSON Config
*
******************************************************************************/
int StorageSupport::GetMaxRecipeNumberSupportedFromJSON()
{
	int MaxSupportedRecipeNumbers = 16;
	int StorageConfig = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	StorageConfig = PlatformConfig::GetConfig(STORAGE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	StorageConfig = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STORAGE_KEY);
#endif
	
	switch (StorageConfig)
	{
		case BASIC_STORAGE: 
		{
			MaxSupportedRecipeNumbers = 16;	
		}
		break;
		
		case ADVANCE_STORAGE: 
		{
			MaxSupportedRecipeNumbers = 50;		
		}
		break;
				
		case ELITE_STORAGE: 
		{
			MaxSupportedRecipeNumbers = 1000;		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetMaxRecipeNumberSupportedFromJSON Error");
		}
		break;
	}	
	return MaxSupportedRecipeNumbers;
}

/******************************************************************************
* \brief - Get the maximum number of weld results that can be stored in database
*		   as per JSON Config
* \param - none
*
* \return - maximum number of weld results that can be stored in database
*			as per JSON Config
******************************************************************************/
int StorageSupport::GetMaxWeldResultStorageSupportedFromJSON()
{
	int MaxWeldResultsNumber = 100000;
	int StorageConfig = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	StorageConfig = PlatformConfig::GetConfig(STORAGE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	StorageConfig = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STORAGE_KEY);
#endif
	switch (StorageConfig)
	{
		case BASIC_STORAGE: 
		{
			MaxWeldResultsNumber = 100000;	
		}
		break;
		
		case ADVANCE_STORAGE: 
		{
			MaxWeldResultsNumber = 500000;		
		}
		break;
				
		case ELITE_STORAGE: 
		{
			MaxWeldResultsNumber = 10000000;		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetMaxWeldResultStorageSupportedFromJSON Error");
		}
		break;
	}	
	return MaxWeldResultsNumber;
}

/******************************************************************************
* \brief - Get the maximum number of weld signatures that can be stored in database
* 		   as per JSON Config
*
* \param - none
*
* \return - maximum number of weld signatures that can be stored in database
*			as per JSON Config
******************************************************************************/
int StorageSupport::GetMaxWeldSignatureStorageSupportedFromJSON()
{
	int MaxWeldSignaturesNumber = 100;
	int StorageConfig = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	StorageConfig = PlatformConfig::GetConfig(STORAGE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	StorageConfig = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STORAGE_KEY);
#endif
	switch (StorageConfig)
	{
		case BASIC_STORAGE: 
		{
			MaxWeldSignaturesNumber = 100;	
		}
		break;
		
		case ADVANCE_STORAGE: 
		{
			MaxWeldSignaturesNumber = 500;		
		}
		break;
				
		case ELITE_STORAGE: 
		{
			MaxWeldSignaturesNumber = 1000;		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetMaxWeldSignatureStorageSupportedFromJSON Error");
		}
		break;
	}	
	return MaxWeldSignaturesNumber;
}

/******************************************************************************
* \brief - Get the maximum number of alarms that can be stored in database
*		   as per JSON Config
* \param - none
*
* \return - maximum number of alarms that can be stored in database 
*			as per JSON Config
******************************************************************************/
int StorageSupport::GetMaxAlarmsStorageSupportedFromJSON()
{
	int MaxAlarmsNumber = 100;
	int StorageConfig = -1;
#if defined(__RTP__)
	//When compiled on VxWorks
	StorageConfig = PlatformConfig::GetConfig(STORAGE_KEY);
#else
	//When compiled on HMI (Ubuntu, Raspberry PI)
	StorageConfig = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STORAGE_KEY);
#endif
	
	switch (StorageConfig)
	{
		case BASIC_STORAGE: 
		{
			MaxAlarmsNumber = 100;	
		}
		break;
		
		case ADVANCE_STORAGE: 
		{
			MaxAlarmsNumber = 500;		
		}
		break;
				
		case ELITE_STORAGE: 
		{
			MaxAlarmsNumber = 1000;		
		}
		break;
		
		default:
		{
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetMaxAlarmsStorageSupportedFromJSON Error");
		}
		break;
	}	
	return MaxAlarmsNumber;
}

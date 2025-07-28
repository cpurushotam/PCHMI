/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2025

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Identifies if welder supports local/touch screen HMI or not

***************************************************************************/

#include "HMIDeviceSupport.h"

size_t HMIDeviceSupport::m_StaticLogId;

/**************************************************************************//**
* \brief   - Constructor
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
HMIDeviceSupport::HMIDeviceSupport() 
{
	// Initialize log ID
	this->m_LogId = Logger::enroll(this);
	m_StaticLogId = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - Handle supported feature of HMI device configuration.
*
* \param   - SupportHMIDevice - Local/Touch Screen HMI device supported or not

* \return  - status 0 on success else -1-.
*
*******************************************************************************/
int HMIDeviceSupport::SetConfigParameter( int SupportHMIDevice)
{
	int status = 0;

	m_ConfiguredValue = SupportHMIDevice;
	
	switch (SupportHMIDevice)
	{
        case LOCAL_HMI:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_EVENT, "Local HMI supported");
		}
		break;

        case PC_HMI:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "PC HMI supported");
		}
		break;

        case BOTH:
        {
            Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Both Local and PC HMI supported");
        }
        break;

		default:
			status = -1;
	}

	return status;
}

/**************************************************************************//**
* \brief   - Returns Local/Touch Screen HMI device supported or not
*
* \param   - None
*
* \return  - Local/Touch Screen HMI device supported or not
******************************************************************************/
int HMIDeviceSupport::GetConfigParameter()
{
	return m_ConfiguredValue;
}

/**************************************************************************//**
* \brief   - Verify supported feature of Local/Touch Screen HMI device configuration.
*
* \param   - Feature - HMI device supported or not

*
* \return  - status 0 on success else -1-.
*
*******************************************************************************/
int HMIDeviceSupport::VerifyConfigParameter(int Feature) 
{
	int status = 0;
	
	switch (Feature)
	{
        case LOCAL_HMI:
		break;

        case PC_HMI:
		break;

        case BOTH:
        break;

		default:
			status = -1;
	}

	return status;
}

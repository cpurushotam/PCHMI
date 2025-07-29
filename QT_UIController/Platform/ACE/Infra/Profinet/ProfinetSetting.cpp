/**************************************************************************

 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 This program is the property of Branson Ultrasonics Corporation
 Copying of this software is expressly forbidden, without the prior
 written consent of Branson Ultrasonics Corporation.


 --------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Profinet Settings Data related implementation

 ***************************************************************************/

#include "ProfinetSetting.h"
#include "DataLogger.h"

size_t ProfinetSetting::static_log_id = 0;
/******************************************************************************
 * \brief - Constructor
 *
 * \param - none
 *
 * \return - none
 *
 ******************************************************************************/
ProfinetSetting::ProfinetSetting()
{
	//enroll to use logger functionality
	static_log_id = Logger::enroll(this);

	//Send the request to read Profinet Settings data to ASC at power up of HMI
	m_InitiateProfinetSettingsDataReadRequest = true;
	//This flag is used to send a write settings request to ASC 
	m_InitiateProfinetSettingsDataSaveRequest = false;
	//This flag is used to send a request to ASC to Reset Profinet Settings to Default
	m_InitiateProfinetSettingsDataToDefault = false;
	//This flag is used to know if data is updated or not from ASC,
    m_IsProfinetDataUpdated = false;
}

/******************************************************************************
 * \brief - Destructor
 *
 * \param - none
 *
 * \return - none
 *
 ******************************************************************************/
ProfinetSetting::~ProfinetSetting()
{
	// Destructor implementation (even if empty)
}

/**************************************************************************//**
 *
 * \brief   - send the requests to ASC to receive data for memory block ID MB_ID_PROFINET_NETWORK_SETTINGS_DATA
 *
 * \param   - destination - Memory block containing data to be sent to ASC
 *
 * \return  - 0 on success, -1 on failure
 *
 ******************************************************************************/
int ProfinetSetting::GetData(MEMORY_BLOCK *const destination)
{
	int retVal = -1;
	// check parameter
	if ((destination != nullptr) && (destination->id == MB_ID_PROFINET_NETWORK_SETTINGS_DATA))
	{
		// perform operation based on sub id
		switch (destination->sub_id)
		{
			//Send Profinet Settings data save request to ASC
			case PROFINET_NETWORK_SETUP_DATA_SAVE:
			{
				retVal = 0;
				ProfinetDataSaveRequestToASC(destination);
				break;
			}
			//Send Profinet Settings data read request to ASC
			case PROFINET_NETWORK_DATA_READ:
			{
				SendProfinetSettingsReadRequestToASC(destination);
				retVal = 0;
				break;
			}
			//Send Profinet Settings data reset to default request to ASC
			case PROFINET_NETWORK_DATA_RESET_TO_DEFAULT:
			{
				RequestASCToResetProfinetSettingsToDefault(destination);
				retVal = 0;
				break;
			}

			default:
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ProfinetSetting:GetData default");
				break;
		}
	}
	else
	{
		// error! invalid memory block id, default retVal (failure) will be returned
		// clear valid bit, reset size
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ProfinetSetting:GetData invalid req");
	}
	return (retVal);
}

/**************************************************************************//**
 *
 * \brief   - process the data coming from ASC for memory block ID MB_ID_PROFINET_NETWORK_SETTINGS_DATA
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - 0 on success, -1 on failure
 *
 ******************************************************************************/
int ProfinetSetting::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
	if ((source != nullptr) && (source->id == MB_ID_PROFINET_NETWORK_SETTINGS_DATA))
	{
		// perform operation based on sub id
		if ((source->config & VALID_BIT) == (VALID_BIT))
		{
			switch (source->sub_id)
			{
				//Process read response coming from ASC for Profinet Settings data
				case PROFINET_NETWORK_DATA_READ:
				{
					retVal = 0;
					ProcessProfinetSettingsReadFromASC(source);
					break;
				}
				default:
				{
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ProfinetSetting:SetData default");
					break;
				}
			}
		}
		else
		{
			retVal = 0;
		}
	}
	else
	{
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ProfinetSetting:SetData invalid req");
	}
	return (retVal);
}

/**************************************************************************//**
 *
 * \brief   - This function will populate the profinet settings data which
 * needs to send to ASC
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - none.
 *
 ******************************************************************************/
void ProfinetSetting::ProfinetDataSaveRequestToASC(MEMORY_BLOCK *const destination)
{
	// Check that sufficient buffer is available in memory block to hold the settings data.
	if (destination->size >= sizeof(ProfinetSettingsStruct))
	{
		//check that Profinet Data save Request Flag is set.
		if (m_InitiateProfinetSettingsDataSaveRequest == true)
		{
			destination->size = sizeof(ProfinetSettingsStruct);
			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateProfinetSettingsDataSaveRequest = false;
			ProfinetSettingsStruct *ProfinetData = reinterpret_cast<ProfinetSettingsStruct*>(destination->data);			
			memcpy(ProfinetData, &m_ProfinetSettingsData, sizeof(ProfinetSettingsStruct));
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}

/**************************************************************************//**
 *
 * \brief   - This function will process the profinet settings data received
 * from ASC
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - none.
 *
 ******************************************************************************/
void ProfinetSetting::ProcessProfinetSettingsReadFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	ProfinetSettingsStruct *ProfinetSettingsData = reinterpret_cast<ProfinetSettingsStruct*>(source->data);
	memcpy(&m_ProfinetSettingsData, ProfinetSettingsData, sizeof(m_ProfinetSettingsData));
    m_IsProfinetDataUpdated =true;
}

/**************************************************************************//**
 *
 * \brief   - This function will send the request to ASC to read Profinet Settings.
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - none.
 *
 ******************************************************************************/
void ProfinetSetting::SendProfinetSettingsReadRequestToASC(MEMORY_BLOCK *const destination)
{
	if (destination->size >= sizeof(int))
	{
		if (m_InitiateProfinetSettingsDataReadRequest == true)
		{
			//destination->data = 0;
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			//Reset the flag to false as we have sent the request.
			m_InitiateProfinetSettingsDataReadRequest = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}

/**************************************************************************//**
 *
 * \brief   - This function will send the request to ASC to Set Profinet Settings To
 * Default Values.
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - none.
 *
 ******************************************************************************/
void ProfinetSetting::RequestASCToResetProfinetSettingsToDefault(MEMORY_BLOCK *const destination)
{
	if (destination->size >= sizeof(int))
	{
		if (m_InitiateProfinetSettingsDataToDefault == true)
		{
			//destination->data = 0;
			destination->size = sizeof(int);
			destination->config = VALID_BIT;
			//Reset the flag to false as we have sent the request.
			m_InitiateProfinetSettingsDataToDefault = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Profinet Settings Update Request
* Update/fill Station Name, IP Address, Netmask and Gatway values.
* \param   - ProfinetSettingData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void ProfinetSetting::InitiateProfinetSettingsUpdateRequest(ProfinetSettingsStruct ProfinetSettingData)
{
	m_ProfinetSettingsData = ProfinetSettingData;
	m_InitiateProfinetSettingsDataSaveRequest = true;
}


/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Reset to Default request to ASC.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ProfinetSetting::InitiateRestToDefaultRequest()
{
    m_InitiateProfinetSettingsDataToDefault = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to know if data is updated or not
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
bool  ProfinetSetting::GetIsProfinetDataAvailable()
{

    return m_IsProfinetDataUpdated;
}
/**************************************************************************//**
*
* \brief   - QML should call this method to reset the data updated flag.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void  ProfinetSetting::SetIsProfinetDataAvailable()
{

     m_IsProfinetDataUpdated = false;
}
/**************************************************************************//**
*
* \brief   - QML should call this method to read the ProfinetSettingsStruct data from ASC.
*
* \param   - ProfinetSettingData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
ProfinetSettingsStruct  ProfinetSetting::GetProfinetSettingsStruct()
{

    return m_ProfinetSettingsData;
}




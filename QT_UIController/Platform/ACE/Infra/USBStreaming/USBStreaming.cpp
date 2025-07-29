/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

This file contains the Stream Data related implementation

***************************************************************************/

#include "USBStreaming.h"
#include "DataLogger.h"
#include "USBStreamStructure.h"


size_t USBStreaming::static_log_id=0;
/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
USBStreaming::USBStreaming()
{
	//enroll to use logger functionality
	static_log_id = Logger::enroll(this);
 
	m_InitiateStreamDataSaveRequest = false;
	//Send the request to read latest streaming data to ASC at power up of HMI
	m_InitiateStreamDataReadRequest = true;
 
}
 
/******************************************************************************
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
USBStreaming::~USBStreaming()
{
    // Destructor implementation (even if empty)
}
 
/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_USB_STREAM_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int USBStreaming :: GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_USB_STREAM_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
		//Send stream data save request to ASC
		case STREAM_DATA_SAVE:
 
			retVal = 0;
			sendStreamDataSaveRequestToASC(destination);
			break;
			
		//Send stream data read request to ASC
		case STREAM_DATA:
		{
			sendStreamDataReadRequestToASC(destination);
			retVal = 0;
			break;
		}
		default:
			// Error ! default retVal (failure) will be returned
			// clear valid bit, reset size
			destination->size = 0;
			// clear valid bit
			destination->config = 0;
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBStreaming:GetData default");
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
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBStreaming:GetData invalid req");
	}
	return (retVal);
}
 
/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_USB_STREAM_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int USBStreaming::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
	if((source != nullptr) && (source->id == MB_ID_USB_STREAM_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process read response coming from ASC for stream data
				case STREAM_DATA:
				{
					retVal = 0;
					processStreamDataReadRequestFromASC(source);
					break;
				}
 
				default:
				{
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBStreaming:SetData default");
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
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBStreaming:SetData invalid req");
	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click save button.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void USBStreaming::InitiateStreamDataSaveRequest(USBStreamStruct StreamDataToSave)
{
	m_USBStreamData = StreamDataToSave;
	m_InitiateStreamDataSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_USB_STREAM_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void USBStreaming :: sendStreamDataSaveRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(USBStreamStruct))
	{
		if(m_InitiateStreamDataSaveRequest == true)
		{
			// update size in destination
			destination->size = sizeof(USBStreamStruct);
 
			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateStreamDataSaveRequest = false;
 
			USBStreamStruct *USBData = reinterpret_cast<USBStreamStruct *>(destination->data);
 
			USBData->EnableWeldData = m_USBStreamData.EnableWeldData;
			USBData->EnableEncryption = m_USBStreamData.EnableEncryption;
			USBData->WeldCyclesCompleted = m_USBStreamData.WeldCyclesCompleted;
			USBData->UsbAmplitude = m_USBStreamData.UsbAmplitude;
			USBData->UsbPower = m_USBStreamData.UsbPower;
			USBData->UsbPhase = m_USBStreamData.UsbPhase;
			USBData->UsbCurrent = m_USBStreamData.UsbCurrent;
			USBData->UsbFrequency = m_USBStreamData.UsbFrequency;
			USBData->UsbEnergy = m_USBStreamData.UsbEnergy;
			USBData->UsbRequestAmplitude = m_USBStreamData.UsbRequestAmplitude;
			USBData->UsbAbsoluteDist = m_USBStreamData.UsbAbsoluteDist;
			USBData->UsbColDist = m_USBStreamData.UsbColDist;
			USBData->UsbForce = m_USBStreamData.UsbForce;
			USBData->UsbVelocity = m_USBStreamData.UsbVelocity;
			USBData->SaveOnAlarm = m_USBStreamData.SaveOnAlarm;
			USBData->StreamingStorageOption = m_USBStreamData.StreamingStorageOption;
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
* \brief   - Send a stream data read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void USBStreaming :: sendStreamDataReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateStreamDataReadRequest == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
 
            //Reset the flag to false as we have sent the request.
            m_InitiateStreamDataReadRequest = false;
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
* \brief   - process the stream data coming from ASC
*
* \param   - source - memory block holding the stream data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void USBStreaming :: processStreamDataReadRequestFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	USBStreamStruct *USBData = reinterpret_cast<USBStreamStruct *>(source->data);
	memcpy(&m_USBStreamData, USBData, sizeof(USBStreamStruct));
}

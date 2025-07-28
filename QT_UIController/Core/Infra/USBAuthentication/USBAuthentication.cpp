/**********************************************************************************************************

 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 This program is the property of Branson Ultrasonics Corporation
 Copying of this software is expressly forbidden, without the prior
 written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 It contains USB Authentication implementation.
 
 **********************************************************************************************************/

#include "USBAuthentication.h"
#include "DataLogger.h"

size_t USBAuthentication::static_log_id=0;
/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
USBAuthentication::USBAuthentication()
{
	//enroll to use logger functionality
	static_log_id = Logger::enroll(this);
	//Send the request to register the usb device to ASC.
	m_InitiateUsbDeviceDataRegistrationRequest = false;
	//Send the request to deregister the usb device to ASC.
	m_InitiateUsbDeviceDeregistrationRequest  =  false;
	//Send the request to read latest usb device data to ASC at power up of HMI
	m_InitiateUsbDeviceDataReadRequest = true;
	//Send the request to read usb status data to ASC at power up of HMI
	m_InitiateUsbStatusReadRequest     = true;
	//the usb status is initialized to usb not connected.
	m_USBStatus 					   = USB_DEVICE_NOT_CONNECTED;
    //Flag setted to false if device details are not updated at HMI powerup
    m_IsUSBDeviceDescriptionDetailsUpdated = false;

}

/******************************************************************************
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
USBAuthentication::~USBAuthentication()
{
    // Destructor implementation (even if empty)
}


/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_USB_AUTHENTICATION_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int USBAuthentication :: GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_USB_AUTHENTICATION_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			case USB_DEVICE_REGISTRATION :
			{
				retVal = 0;
				SendUsbDeviceRegistrationRequestToASC(destination);
				break;
			}
	
			case READ_USB_DEVICES_REGISTERED :
			{
				SendUsbDeviceDataReadRequestToASC(destination);
				retVal = 0;
				break;
			}
			case USB_DEVICE_DEREGISTRATION :
			{
				SendUsbDeviceDeregistrationRequestToASC(destination);
				retVal = 0;
				break;
			}
			case READ_USB_CONNECT_AUTHENTICATION_STATUS :
			{
				SendUsbStatusRequestToASC(destination);
				retVal = 0;
				break;
			}
			default:
			{
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBAuthentication:GetData default");
				break;
			}
		}
	}
	  else
	{
		// error! invalid memory block id, default retVal (failure) will be returned
		// clear valid bit, reset size
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBAuthentication:GetData invalid req");
	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_USB_AUTHENTICATION_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int USBAuthentication::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
	if((source != nullptr) && (source->id == MB_ID_USB_AUTHENTICATION_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				case READ_USB_DEVICES_REGISTERED :
				{
					retVal = 0;
					ProcessUsbDeviceDataReadRequestFromASC(source);
					break;
				}
				case READ_USB_CONNECT_AUTHENTICATION_STATUS :
				{
					retVal = 0;
					ProcessUsbStatusReadRequestFromASC(source);
					break;
				}
				default:
				{
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBAuthentication:SetData default");
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
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "USBAuthentication:SetData invalid req");
	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - Send a Usb Device data read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void USBAuthentication :: SendUsbDeviceDataReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateUsbDeviceDataReadRequest == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateUsbDeviceDataReadRequest = false;
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
* \brief   - process the usb device data coming from ASC
*
* \param   - source - memory block holding the usb device data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void USBAuthentication :: ProcessUsbDeviceDataReadRequestFromASC(const MEMORY_BLOCK *const source)
{
	int *usbDeviceCount = reinterpret_cast< int*>(source->data);
	int usbDeviceDataIndex = 0 ;
	USBDeviceDescriptionStruct *usbDetails = reinterpret_cast< USBDeviceDescriptionStruct*> (source->data+ sizeof(int));
	
	m_UsbDeviceDescriptionData.clear();
	for(usbDeviceDataIndex = 0; usbDeviceDataIndex < *usbDeviceCount ; usbDeviceDataIndex++ )
	{
		m_UsbDeviceDescriptionData.push_back(*usbDetails);
		usbDetails++;
	}
    //Set flag to true so that HMI uses this flag to know if data is available or not.
    m_IsUSBDeviceDescriptionDetailsUpdated  = true;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click Usb Register button.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void USBAuthentication::InitiateUsbDeviceRegistrationRequest()
{
	m_InitiateUsbDeviceDataRegistrationRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID USB_DEVICE_REGISTRATION.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void USBAuthentication :: SendUsbDeviceRegistrationRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
		if(m_InitiateUsbDeviceDataRegistrationRequest == true)
		{
			// update size in destination
			destination->size = sizeof(int);

			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateUsbDeviceDataRegistrationRequest = false;

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
* \brief   - call this method on HMI side when you click Usb Degistration button after updating
* 				 the m_UsbDeviceDescriptionData deque with the EnableDeregistration flag.
*
* \param   - UsbDeviceDescriptionDetails - .Dequeue to hold the USB Details to be be unregistered.
*
* \return  - None
*
******************************************************************************/
void USBAuthentication::InitiateUsbDeviceDeregistrationRequest(std::deque<USBDeviceDescriptionStruct> UsbDeviceDescriptionDetails)
{
    m_UsbDeviceDescriptionData = UsbDeviceDescriptionDetails;
	m_InitiateUsbDeviceDeregistrationRequest = true;
}
/**************************************************************************//**
*
* \brief   - Send a Usb Device data to ASC to perform the Deregistration of the usb device
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void USBAuthentication :: SendUsbDeviceDeregistrationRequestToASC(MEMORY_BLOCK * const destination)
{
	int usbdevicedataIndex = 0;
	//actual size in bytes
	int DataSize = 0;
	int *usbIndex = reinterpret_cast< int*>(destination->data);
	USBDeviceDescriptionStruct *usbDetails = reinterpret_cast< USBDeviceDescriptionStruct*>(destination->data + sizeof(int));

	//Check that sufficient buffer is available in memory block to hold the chunk.
	if(destination->size >= ( ( MAX_NUM_OF_USB_DEVICES_REGISTER * sizeof(USBDeviceDescriptionStruct) ) + sizeof(int) ))
	{
		if(m_InitiateUsbDeviceDeregistrationRequest == true)
		{
			if(!m_UsbDeviceDescriptionData.empty())
			{	
				for (auto usbDeviceData = m_UsbDeviceDescriptionData.begin(); usbDeviceData != m_UsbDeviceDescriptionData.end(); ++usbDeviceData)
				{
					if(usbDeviceData->EnableDeregistration == true)
					{
						*usbDetails = *usbDeviceData;
						usbdevicedataIndex++;
						usbDetails++;
						DataSize += sizeof(USBDeviceDescriptionStruct);
					}
				}
				*usbIndex = usbdevicedataIndex;
		    }
			// update size in destination
			destination->size = DataSize + sizeof(int);
			// Set valid bit
			destination->config = VALID_BIT;

			m_InitiateUsbDeviceDeregistrationRequest = false;
		}
		else
		{
			// update size in destination
	        destination->size = 0;

	        // Set valid bit
	        destination->config = VALID_BIT;
		}

	}
	else
	{
		// update size in destination
		destination->size = 0;

		// set config bit
		destination->config = 0;
	}
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when usb status is needed.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void USBAuthentication::InitiateUsbStatusReadRequest()
{
	m_InitiateUsbStatusReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - Method used to know if USB details is updated or not
*
* \param   - None.
*
* \return  - m_IsUSBDeviceDescriptionDetailsUpdated - Is USB Device data updated from ASC.
*
******************************************************************************/
bool USBAuthentication::GetIsUSBDevDescriptionDetailsUpdated()
{
    return m_IsUSBDeviceDescriptionDetailsUpdated;
}
/**************************************************************************//**
*
* \brief   - Reset the m_IsUSBDeviceDescriptionDetailsUpdated to false once data is read.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void USBAuthentication::SetIsUSBDeviceDescriptionDetailsUpdatedFlag()
{
    m_IsUSBDeviceDescriptionDetailsUpdated = false;
}
/**************************************************************************//**
*
* \brief   - Function used to get USB Device details on HMI.
*
* \param   - None.
*
* \return  - m_UsbDeviceDescriptionData - USB Device detaisl dequeue.
*
******************************************************************************/
std::deque<USBDeviceDescriptionStruct> USBAuthentication::GetUSBDeviceDescriptionList()
{
    return m_UsbDeviceDescriptionData;
}


/**************************************************************************//**
*
* \brief   - Send a usb status request to ASC to get the usb status.
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void USBAuthentication :: SendUsbStatusRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
		if(m_InitiateUsbStatusReadRequest == true)
		{
			// update size in destination
			destination->size = sizeof(bool);

			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateUsbStatusReadRequest = false;

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
* \brief   - process the usb status data coming from ASC
*
* \param   - source - memory block holding the usb status data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void USBAuthentication :: ProcessUsbStatusReadRequestFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	int *usbConnectedStatus = reinterpret_cast< int*>(source->data);
	m_USBStatus = (USB_STATUS)*usbConnectedStatus;

}


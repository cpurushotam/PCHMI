/**************************************************************************
 
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
 
--------------------------- MODULE DESCRIPTION ----------------------------

 It contains USBAuthentication class declaration.
 Use this class to USB Authentication.
 
 **********************************************************************************************************/

#ifndef USBAUTHENTICATION_H_
#define USBAUTHENTICATION_H_


#include <deque>
#include "DataInterface.h"
#include "Common_Definitions.h"
#include "USBAuthenticationStructure.h"

class USBAuthentication : public DataInterface
{
public:
	USBAuthentication();
	virtual ~USBAuthentication();

    static size_t static_log_id;

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void InitiateUsbDeviceRegistrationRequest();
    void InitiateUsbDeviceDeregistrationRequest (std::deque<USBDeviceDescriptionStruct> UsbDeviceDescriptionDetails);
    void InitiateUsbStatusReadRequest();
    std::deque<USBDeviceDescriptionStruct> GetUSBDeviceDescriptionList();
    bool GetIsUSBDevDescriptionDetailsUpdated();
    void SetIsUSBDeviceDescriptionDetailsUpdatedFlag();

	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;};

private:

    //flag to initiate the request to ASC
	bool m_InitiateUsbDeviceDataReadRequest;
	bool m_InitiateUsbDeviceDataRegistrationRequest;
	bool m_InitiateUsbDeviceDeregistrationRequest;
	bool m_InitiateUsbStatusReadRequest;
    bool m_IsUSBDeviceDescriptionDetailsUpdated;
    //Holds usb status 
    USB_STATUS m_USBStatus;
	//Holds USB Device data.
	std::deque<USBDeviceDescriptionStruct> m_UsbDeviceDescriptionData;
	//Send read Usb Device data request to ASC
	void SendUsbDeviceDataReadRequestToASC(MEMORY_BLOCK * const destination);
	//Process read Usb Device data request from ASC
	void ProcessUsbDeviceDataReadRequestFromASC(const MEMORY_BLOCK *const source);
	//Send Usb Device Registration request to ASC
	void SendUsbDeviceRegistrationRequestToASC(MEMORY_BLOCK * const destination);
	//Send Usb Device Deregistration request to ASC
	void SendUsbDeviceDeregistrationRequestToASC(MEMORY_BLOCK * const destination);
	//Send Usb status read request to ASC
	void SendUsbStatusRequestToASC(MEMORY_BLOCK * const destination);
	//Process Usb status read request from ASC
	void ProcessUsbStatusReadRequestFromASC(const MEMORY_BLOCK *const source);
};


#endif /* USBAUTHENTICATION_H_ */

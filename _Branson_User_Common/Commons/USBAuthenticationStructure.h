/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the USB Authentication related structures, enum and Macros
 ***************************************************************************/

#ifndef USBAUTHENTICATIONSTRUCTURE_H_
#define USBAUTHENTICATIONSTRUCTURE_H_

#include <cstring>
#include "Common_Definitions.h"

#define MAX_SINGLE_PARAMETER_DATA_SIZE              20 /*Maximum size of the single parameter of the usb device data */
#define MAX_USB_DEVICE_SERIAL_DATA_SIZE             8  /*Maximum size of the usb device serial code */
#define MAX_NUM_OF_USB_DEVICES_REGISTER 			10 /*Maximum number of usb devices registered*/
#define YEAR_START 									1900 /*Year stating from 1900 */
#define MONTH_SUBTRACT_VALUE                        1   /*std::time_t expect month value - 1 */
#define MAX_DATE_SIZE                               10 /*maximum date size*/  

// Data Interface ID declarations
typedef enum
{
	USB_DEVICE_REGISTRATION = 1,
	READ_USB_DEVICES_REGISTERED,
	USB_DEVICE_DEREGISTRATION,
	READ_USB_CONNECT_AUTHENTICATION_STATUS
}MEMORY_BLOCK_SUB_ID_USB_AUTHENTICATION;

//usb status
typedef enum USB_STATUS
{
	USB_DEVICE_NOT_CONNECTED=0,
	USB_DEVICE_CONNECTED,
	USB_DEVICE_AUTHENTICATED
}USB_STATUS;

typedef struct USBDeviceDescriptionStruct
{
	bool    EnableDeregistration;
	int		UsbIndexNumber;
	char 	VendorCode[MAX_SINGLE_PARAMETER_DATA_SIZE];
	char 	ProductCode[MAX_SINGLE_PARAMETER_DATA_SIZE];
	char 	SerialCode[MAX_SINGLE_PARAMETER_DATA_SIZE];
	char    DeviceName[MAX_SINGLE_PARAMETER_DATA_SIZE];
	char    UsedDate[MAX_SINGLE_PARAMETER_DATA_SIZE];
 
	USBDeviceDescriptionStruct()
	{
		EnableDeregistration	= false;
		UsbIndexNumber          = 0;
		memset(VendorCode, 0, sizeof(VendorCode) );
		memset(ProductCode,0, sizeof(ProductCode));
		memset(SerialCode, 0, sizeof(SerialCode) );
		memset(DeviceName, 0, sizeof(DeviceName) );
		memset(UsedDate,   0, sizeof(UsedDate)   );
	}
}__attribute__((packed)) USBDeviceDescriptionStruct;
 
#ifndef  __VXWORKS__
typedef struct USBHostDescriptionStruct
{
	uint16_t idVendor;
	uint16_t idProduct;
}__attribute__((packed)) USBHostDescriptionStruct;
#endif

#endif /* USBAUTHENTICATIONSTRUCTURE_H_ */

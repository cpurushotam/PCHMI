/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains Opcua Client Certificate Upload related implementation
 ***************************************************************************/

#ifndef OPCUA_CLIENT_CERTIFICATE_STRUCTURE_H_
#define OPCUA_CLIENT_CERTIFICATE_STRUCTURE_H_

#include <stdint.h>
#include <string>
#include "Common_Definitions.h"
#include "DataInterface.h"

//  Used to Validate Opcua Client Certificate Extension in ".der" Format
#define  OPCUA_CLIENT_CERTIFICATE_FILE_EXTENSION                       ".der" 
//  Used to Validate Opcua Client Certificate FileName as None
#define  OPCUA_CLIENT_CERTIFICATE_EMPTY_FILE_NAME                      "None"    
// Defining IP Address size for char array size
#define  IP_ADDRESS_SIZE												30
// Defining Port Number size for char array size
#define  PORT_NUMBER_SIZE												5
// Defining Ip Address for PubSub Subscriber
#define OPCUA_PUBSUB_SUBSCRIBER_DEFAULT_IP_ADDRESS                     "192.168.2.100"
// Defining Port Number for PubSub Subscriber
#define OPCUA_PUBSUB_SUBSCRIBER_DEFAULT_PORT_NUMBER                    "4840" 

typedef enum
{
    MB_READ_OPCUA_CERTIFICATE_FROM_USB_REQUEST = 1,
    MB_COPY_OPCUA_CERTIFICATE_USB_EMMC_REQUEST,    
	MB_READ_OPCUA_PUBSUB_IP_PORT,
	MB_WRITE_OPCUA_PUBSUB_IP_PORT,
}OPCUA_CLIENT_CERTIFICATE_MB_SUB_ID;

typedef enum
{
	OPCUA_CERTIFICATES_ERROR_UNKNOWN = 0,
	OPCUA_CERTIFICATES_FAILURE,
	OPCUA_CERTIFICATES_SUCCESS
}OPCUA_CERTIFICATES_ERROR_CODES;

typedef struct OpcuaCertificateUploadStruct
{
	char OpcuaCertificateFileName[OPCUA_CERTIFICATE_MAX_FILE_NAME_SIZE];
    OpcuaCertificateUploadStruct()
    {
		// Use strncpy to copy the string and ensure null termination
		strncpy(OpcuaCertificateFileName, OPCUA_CLIENT_CERTIFICATE_EMPTY_FILE_NAME, sizeof(OpcuaCertificateFileName) - 1);
		OpcuaCertificateFileName[sizeof(OpcuaCertificateFileName) - 1] = '\0'; // Ensure null termination
    }
		
}__attribute__((packed)) OpcuaCertificateUploadStruct;

typedef struct OpcuaIpPortStruct
{
	char IpAddress[IP_ADDRESS_SIZE];
	char PortNumber[PORT_NUMBER_SIZE];

	OpcuaIpPortStruct()
	{
		strncpy(IpAddress,OPCUA_PUBSUB_SUBSCRIBER_DEFAULT_IP_ADDRESS,sizeof(IpAddress));
		strncpy(PortNumber,OPCUA_PUBSUB_SUBSCRIBER_DEFAULT_PORT_NUMBER,sizeof(PortNumber));
	}
};

#endif


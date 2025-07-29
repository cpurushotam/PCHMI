/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

This file contains the System Configuration Branson Service related implementation
 ***************************************************************************/

#ifndef SYSTEM_CONFIG_BRANSON_SERVICE_H_
#define SYSTEM_CONFIG_BRANSON_SERVICE_H_

#include <stdint.h>
#include "Common_Definitions.h"
#include <ctime>
#include <map>

static constexpr int MAX_NUM_OF_SERVICE_LOGS_IN_ONE_CHUNK = 10;

typedef enum
{
    MB_READ_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST = 1,
    MB_UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST,
}SYSTEM_CONFIG_BRANSON_SERVICE_SUB_ID;

typedef enum
{
    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_UNKNOWN = 0,
	UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_FAILURE,
	UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_SUCCESS
}UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES;


typedef enum
{
    FACTORY_RESET_REQUEST = 1,
    DB_DELETE_REQUEST,
    DB_COPY_TO_USB_REQUEST,
    EMMC_MEMORY_USAGE,
    BOARD_REPLACED_REQUEST,
    SYSTEM_CLEANED_REQUEST,
    ADD_SERVICE_NOTES_REQUEST,
    SEND_REQUEST_STATUS,
    READ_SERVICE_LOG,
	SYNC_SERVICE_LOG
}BRANSON_SERVICE_SUB_ID;


typedef enum
{
	FACTORY_RESET_REQUEST_IN_PROGRESS = 1,
    FACTORY_RESET_REQUEST_SUCCESSFULL,
	FACTORY_RESET_REQUEST_FAIL,
    DB_DELETE_REQUEST_SUCCESS,
	DB_DELETE_REQUEST_FAIL,
    DB_COPY_TO_USB_REQUEST_SUCCESS,
	DB_COPY_TO_USB_REQUEST_FAIL,
    BOARD_REPLACED_REQUEST_SUCCESS,
    BOARD_REPLACED_REQUEST_FAIL,
    SYSTEM_CLEANED_REQUEST_SUCCESS,
    SYSTEM_CLEANED_REQUEST_FAIL,
    SERVICE_UNKNOWN_ERROR
}BRANSON_SERVICE_REQUESTS_RESPONSE_CODES;

typedef struct SystemConfigBransonServiceStruct
{
    char MachineSerialNumber[SERIAL_NUM_SIZE];
    char PowerSupplySerialNumber[SERIAL_NUM_SIZE];
    char ActuatorSerialNumber[SERIAL_NUM_SIZE];
	
    SystemConfigBransonServiceStruct()
	{       
        strncpy(MachineSerialNumber, "0", SERIAL_NUM_SIZE - 1);
		MachineSerialNumber[SERIAL_NUM_SIZE - 1] = '\0'; 

		strncpy(PowerSupplySerialNumber, "0", SERIAL_NUM_SIZE - 1);
		PowerSupplySerialNumber[SERIAL_NUM_SIZE - 1] = '\0'; 

		strncpy(ActuatorSerialNumber, "0", SERIAL_NUM_SIZE - 1);
		ActuatorSerialNumber[SERIAL_NUM_SIZE - 1] = '\0';
	}
			
}__attribute__((packed))  SystemConfigBransonServiceStruct;


//Structure for storing ervice note and DateTIme.
typedef struct BransonServiceTabStructure
{
    char ServiceNote[SERVICENOTES_SIZE];
    char DateTime[DATE_SIZE_12_HR_FORMAT];

}__attribute__((packed))  BransonServiceTabStructure;


extern const std::map <BRANSON_SERVICE_REQUESTS_RESPONSE_CODES , std::string> BransonServiceErrorType;

#endif


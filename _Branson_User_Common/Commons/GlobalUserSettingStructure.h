/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains global User setting related implementation
 ***************************************************************************/

#ifndef GLOBAL_USER_STRUCTURES_H_
#define GLOBAL_USER_STRUCTURES_H_

#include <stdint.h>
#include "Common_Definitions.h"

typedef enum
{
    MB_READ_GLOBAL_USER_SETTINGS_REQUEST = 1,
    MB_UPDATE_GLOBAL_USER_SETTINGS_REQUEST,
    MB_RESET_GLOBAL_USER_SETTINGS_REQUEST,
}GLOBAL_USER_SETTINGS_MB_SUB_ID;

typedef enum
{
    UPDATE_GLOBAL_USER_SETTING_ERROR_UNKNOWN = 0,
    UPDATE_GLOBAL_USER_SETTING_FAILURE,
    UPDATE_GLOBAL_USER_SETTING_SUCCESS
}UPDATE_GLOBAL_USER_SETTING_ERROR_CODES;

typedef struct GlobalUserSettingStruct
{
	uint32_t PasswordExpiryInDays;
	uint32_t IdleTimeLogoffInMinute;
	uint32_t LockOutTimeInMinute;
    bool AutoLoginStatus;
    char AutoLoginUserName[USER_NAME_SIZE];
	
	GlobalUserSettingStruct()
	{
		PasswordExpiryInDays = 90;
		IdleTimeLogoffInMinute = 30;
		LockOutTimeInMinute = 15;
        AutoLoginStatus = false;
        strncpy(AutoLoginUserName, "0", USER_NAME_SIZE - 1);
        AutoLoginUserName[USER_NAME_SIZE - 1] = '\0'; 
	}
			
}__attribute__((packed))  GlobalUserSettingStruct;

#endif


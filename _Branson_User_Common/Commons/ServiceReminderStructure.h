/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Service reminder related implementation
 ***************************************************************************/

#ifndef SERVICE_REMINDER_STRUCTURES_H_
#define SERVICE_REMINDER_STRUCTURES_H_

#include <map>
#include <tuple>
#include <string.h>
#include "Common_Definitions.h"

typedef enum
{
	MB_REMINDER_LIST_REQUEST = 1,	
	MB_ADD_REMINDER_REQUEST,
    MB_MODIFY_REMINDER_REQUEST,
	MB_DELETE_REMINDER_REQUEST,
	MB_PAUSE_RESUME_REMINDER_REQUEST,
	MB_RESET_REMINDER_REQUEST,
	MB_SNOOZE_REMINDER_REQUEST,
	SYNCH_SERVICE_REMIDER_DATA
}SERVICE_REMINDER_MB_SUB_ID;

typedef enum
{
	ADD_REMINDER_ERROR_UNKNOWN = 0,
	ADD_REMINDER_SUCCESS,
	ADD_REMINDER_FAIL,
	REMINDER_ALREADY_EXIST,
	ADD_REMINDER_LIMIT_CROSSED
}ADD_REMINDER_ERROR_CODES;

typedef enum
{
	MODIFY_REMINDER_ERROR_UNKNOWN = 0,
	MODIFY_REMINDER_SUCCESS,
	MODIFY_REMINDER_FAIL,
	MODIFY_REMINDER_NOT_EXIST_IN_DB,
	DELETE_REMINDER_SUCCESS,
    DELETE_REMINDER_FAIL,
	PAUSE_RESUME_REMINDER_SUCCESS,
	PAUSE_RESUME_REMINDER_FAIL,
	RESET_REMINDER_SUCCESS,
	RESET_REMINDER_FAIL,
	SNOOZE_REMINDER_SUCCESS,
	SNOOZE_REMINDER_FAIL
}MODIFY_REMINDER_ERROR_CODES;

typedef enum
{
	REMINDER_STATUS_DISABLED,
	REMINDER_STATUS_ENABLED
}REMINDER_STATUS;

typedef enum
{
	METHOD_COUNTER,
	METHOD_TIME
}REMINDER_METHOD;

typedef enum
{
	AFTER_NONE,
	AFTER_12_HRS, 	//0.5 day
	AFTER_24_HRS,	//1 day
	AFTER_72_HRS,	//3 days
	AFTER_144_HRS	//6 days
}SNOOZE_DURATION;

typedef enum
{
	ADD_REMINDER_OPERATION,
	MODIFY_REMINDER_OPERATION,
	DELETE_REMINDER_OPERATION,
	PAUSE_RESUME_REMINDER_OPERATION,
	RESET_REMINDER_OPERATION,
	SNOOZE_REMINDER_OPERATION,
	UPDATE_REMINDER_COUNTER_OPERATION
}REMINDER_UPDATE_OPERATION;

typedef struct ReminderInfoStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	REMINDER_METHOD method;
	int counter;
	int counterLimit;
	time_t dateTimeLimit;
	REMINDER_STATUS status;
	SNOOZE_DURATION snooze;
	time_t scheduledTime;
	
	ReminderInfoStruct()
	{
		memset(serviceName, '\0', sizeof(serviceName));		
		method 			= METHOD_COUNTER;
		counter 		= 0;
		counterLimit 	= 0;
		dateTimeLimit 	= 0;
		status 			= REMINDER_STATUS_ENABLED;
		snooze 			= AFTER_NONE;
		scheduledTime	= 0;
	}
}__attribute__((packed)) ReminderInfoStruct;

typedef struct ReminderCounterStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	int counter;
	
	ReminderCounterStruct()
	{
		memset(serviceName, '\0', sizeof(serviceName));		
		counter = 0;
	}
}__attribute__((packed)) ReminderCounterStruct;

typedef struct addReminderStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	REMINDER_METHOD method;
	int counterLimit;
	time_t dateTimeLimit;
	REMINDER_STATUS status;
	SNOOZE_DURATION snooze;
	
	addReminderStruct()
	{
		memcpy(serviceName, "0", sizeof(serviceName));
		method 			= METHOD_COUNTER;
		counterLimit 	= 0;
		dateTimeLimit 	= 0;
		status 			= REMINDER_STATUS_ENABLED;
		snooze			= AFTER_NONE;
	}	
}__attribute__((packed)) addReminderStruct;

typedef struct reminderListStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	REMINDER_METHOD method;
	int counter;
	int counterLimit;
	time_t dateTimeLimit;
	REMINDER_STATUS status;
	SNOOZE_DURATION snooze;
	
	reminderListStruct()
	{
		memcpy(serviceName, "0", sizeof(serviceName));
		method 			= METHOD_COUNTER;
		counter 		= 0;
		counterLimit 	= 0;
		dateTimeLimit 	= 0;
		status 			= REMINDER_STATUS_ENABLED;
		snooze			= AFTER_NONE;
	}	
}__attribute__((packed)) reminderListStruct;

typedef struct reminderPauseResumeStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	REMINDER_STATUS status;
	
	reminderPauseResumeStruct()
	{
		memcpy(serviceName, "0", sizeof(serviceName));
		status = REMINDER_STATUS_ENABLED;
	}
}__attribute__((packed)) reminderPauseResumeStruct;

typedef struct reminderResetStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	int counter;
	time_t dateTimeLimit;
	SNOOZE_DURATION snooze;
	time_t scheduledTime;
	
	reminderResetStruct()
	{
		memcpy(serviceName, "0", sizeof(serviceName));
		counter 		= 0;
		dateTimeLimit 	= 0;
		snooze			= AFTER_NONE;
		scheduledTime	= 0;
	}
}__attribute__((packed)) reminderResetStruct;

typedef struct reminderSnoozeStruct
{
	char serviceName[SERVICE_NAME_SIZE];
	SNOOZE_DURATION snooze;

	reminderSnoozeStruct()
	{
		memcpy(serviceName, "0", sizeof(serviceName));
		snooze = AFTER_NONE;
	}
}__attribute__((packed)) reminderSnoozeStruct;
#endif //SERVICE_REMINDER_STRUCTURES_H_

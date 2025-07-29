/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld reslut related structure definition.
 
***************************************************************************/

#ifndef WELD_RESULT_STRUCTURES_ACE_H_
#define WELD_RESULT_STRUCTURES_ACE_H_

#include "Common_Definitions.h"
#include <string>
#include <cstring>
//Maximum number of weld result structures (WeldResultACEStruct) sent in one chunk
constexpr int MAX_NUM_OF_WELD_RESULTS_IN_ONE_CHUNK = 30; 


constexpr int MAX_NUM_OF_HISTORICAL_WELD_RESULTS_TO_SEND = 3000;

//Maximum number of weld result structures (WeldResultACEStruct) sent to Storage
constexpr int MAX_NUM_OF_HISTORICAL_WELD_RESULTS_TO_SEND_TO_STORAGE = 3000;

typedef enum
{
	DB_READ_LAST_WELD_RESULT_DATA = 1,
	DB_READ_HISTORICAL_WELD_RESULT_DATA,
	DB_READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER,
	DB_READ_HISTORICAL_WELD_RESULT_DATA_FOR_WELD_RESULT_INDEX,
	DB_READ_HISTORICAL_WELD_RESULT_DATA_TO_STORAGE,
	
}WELD_RESULT_DB_READ_OPERATION_ID;

typedef enum
{
	WELD_CYCLE_OK	= 1,
	WELD_SUSPECT,
	WELD_REJECTED
}WELD_STATUS_ID;

typedef struct WeldResultACEStruct
{
	int32_t WeldResultIndex;
	int32_t WeldRecipeNumber; 
	int32_t WeldRecipeVersionNumber; 
	char DateTime[DATE_SIZE_12_HR_FORMAT];
	char StackSerialNumber[SERIAL_NUM_SIZE]; 
	char PowerSupplySerialNumber[SERIAL_NUM_SIZE]; 
	char ActuatorSerialNumber[SERIAL_NUM_SIZE];
	char ASCSerialNumber[SERIAL_NUM_SIZE]; 
	int32_t CycleCounter;
	WELDMODES WeldMode;
	float WeldTime; 
	float HoldTime; 
	float WeldEnergy; 
	float WeldPeakPower;  
	uint32_t StartFrequency;
	int32_t FrequencyChange;
	float CycleTime; 
	char UserName[USER_NAME_SIZE];
	char PartID[BARCODE_DATA_SIZE]; 
	char BatchID[BATCHID_SIZE];
	float TriggerPoint; 
	float WeldSonicPoint; 
	float HoldPoint; 
	char AlarmID[ALARM_ID_SIZE]; 
	int32_t WeldStatus;
	int32_t RecipeStatus; 
	float WeldPressure;
	float HoldPressure;	
	float MaxWeldForce; 
	float MaxHoldForce; 
	float EndWeldForce;
	float EndHoldForce;
	float WeldAbsolute;
	float TotalAbsolute;
	float Velocity;
	float DownSpeed; 
	float TriggerDistance;
	float WeldCollapseDistance;
	float HoldCollapseDistance;
	float TotalCollapseDistance;
	
	WeldResultACEStruct()
	{
		ResetParameters();
	}

	void ResetParameters()
	{
		std::string string_NA  = "N/A";
		
		WeldResultIndex = 0;
		WeldRecipeNumber = 0;
		WeldRecipeVersionNumber = 0;
		strncpy(DateTime, string_NA.c_str(), sizeof(DateTime));
		strncpy(StackSerialNumber, string_NA.c_str(), sizeof(StackSerialNumber));
		strncpy(PowerSupplySerialNumber, string_NA.c_str(), sizeof(PowerSupplySerialNumber));
		strncpy(ActuatorSerialNumber, string_NA.c_str(), sizeof(ActuatorSerialNumber));
		strncpy(ASCSerialNumber, string_NA.c_str(), sizeof(ASCSerialNumber));
		CycleCounter = 0;
		WeldMode = TIMEMODE;
		WeldTime = 0.0f;
		HoldTime = 0.0f;
		WeldEnergy = 0.0f;
		WeldPeakPower = 0.0f;
		StartFrequency = 0;
		FrequencyChange = 0;
		CycleTime = 0.0f;
		strncpy(UserName, string_NA.c_str(), sizeof(UserName));
		strncpy(PartID, string_NA.c_str(), sizeof(PartID));
		strncpy(BatchID, string_NA.c_str(), sizeof(BatchID));
		TriggerPoint = 0.0f;
		WeldSonicPoint = 0.0f;
		HoldPoint = 0.0f;
		strncpy(AlarmID, string_NA.c_str(), sizeof(AlarmID));
		WeldStatus = WELD_CYCLE_OK;
		RecipeStatus = 0;
		WeldPressure = 0.0f;
		HoldPressure = 0.0f;
		MaxWeldForce = 0.0f;
		MaxHoldForce = 0.0f;
		EndWeldForce = 0.0f;
		EndHoldForce = 0.0f;
		WeldAbsolute = 0.0f;
		TotalAbsolute = 0.0f;
		Velocity = 0.0f;
		DownSpeed = 0.0f;
		TriggerDistance = 0.0f;
		WeldCollapseDistance = 0.0f;
		HoldCollapseDistance = 0.0f;
		TotalCollapseDistance = 0.0f;
	}

}__attribute__((packed))  WeldResultACEStruct;



#endif /* WELD_RESULT_STRUCTURES_ACE_H_ */

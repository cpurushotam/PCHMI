/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains System Information related implementation
 ***************************************************************************/

#ifndef SYSTEM_INFORMATION_STRUCTURE_H_
#define SYSTEM_INFORMATION_STRUCTURE_H_

#include <stdint.h>
#include "Common_Definitions.h"

#define EEPROM_PATH		              "/eeprom/0"
#define EEPROM_MAC_ADDRESS_OFFSET   	0x2E0
#define FIOSEEK                         7   /* set current file char position */

typedef enum
{
    MB_READ_SYSTEM_INFORMATION_REQUEST = 1,
}SYSTEM_INFORMATION_MB_SUB_ID;

enum DATABASE_UPDATE_INFO
{
	SYSTEM_INFO_COUNTER_TABLE_UPDATED = 1,
	SERIAL_NUMBER_TABLE_UPDATED,
};

enum SYSTEM_INFO_PARAM_ID
{
	LIFETIME_WELD_CYCLE_COUNTER=1,
	TOTAL_ALARM_CYCLE_COUNTER,
	ACTUATOR_CYCLES_RUN_COUNTER,
	CONVERTER_CYCLE_RUN_COUNTER,
	HORN_CYCLE_COUNTER,
	CYLINDER_COUNTER,
	POWER_SUPPLY_OVERLOAD_COUNTER,
	MAX_COUNTER
};

//Holds the changed system information parameter identifier and value.
typedef struct ChangedSystemInformationParameter
{
	uint32_t SystemInfoParamID; //Holds the changed system information parameter identifier.
	uint32_t CounterValue;//Holds the changed value.
	ChangedSystemInformationParameter()
	{
		CounterValue = 0;
	}
}__attribute__((packed)) ChangedSystemInformationParameter;

typedef struct SystemInformationStruct
{
	uint32_t LifetimeWeldCyclesCounter;
	uint32_t TotalAlarmCyclesCounter;
	uint32_t ActuatorCyclesRunCounter;
	uint32_t ConvertersCyclesRunCounter;
	uint32_t HornCyclesCounter;
	uint32_t CylinderCounter;
	uint32_t PowerSupplyOverLoadCounter;
	
	SystemInformationStruct()
	{
		LifetimeWeldCyclesCounter = 0;
		TotalAlarmCyclesCounter = 0;
		ActuatorCyclesRunCounter = 0;
		ConvertersCyclesRunCounter = 0;
		HornCyclesCounter = 0;
		CylinderCounter = 0;
		PowerSupplyOverLoadCounter = 0;
	}
			
}__attribute__((packed))  SystemInformationStruct;


typedef struct MachineDetailsStruct
{
	uint32_t NumberOfAlarms;	
	uint32_t PowerSupplyLifetimeWeld;
	uint32_t ActuatorLifetimeCycle;
	uint32_t PowerSupplyOverLoad;	
	char SCVersion[VERSION_SIZE];
	char ACVersion[VERSION_SIZE];
	char PCVersion[VERSION_SIZE];
	char PowerSupplySerialNumber[SERIAL_NUM_SIZE];
	char ActuatorSerialNumber[SERIAL_NUM_SIZE];
	char CalibrationDate[DATE_SIZE_12_HR_FORMAT];
    char MacId[MAC_ID_SIZE];
    char SafetyVersion[VERSION_SIZE];

	MachineDetailsStruct()
	{
		NumberOfAlarms = 0;
		PowerSupplyLifetimeWeld = 0;
		ActuatorLifetimeCycle = 0;
		PowerSupplyOverLoad = 0;
		
		strncpy(SCVersion, "0", VERSION_SIZE - 1);
		SCVersion[VERSION_SIZE - 1] = '\0'; // Ensure null termination
		
		strncpy(ACVersion, "0", VERSION_SIZE - 1);
		ACVersion[VERSION_SIZE - 1] = '\0'; 

		strncpy(PCVersion, "0", VERSION_SIZE - 1);
		PCVersion[VERSION_SIZE - 1] = '\0'; 

		strncpy(PowerSupplySerialNumber, "0", SERIAL_NUM_SIZE - 1);
		PowerSupplySerialNumber[SERIAL_NUM_SIZE - 1] = '\0'; 
		
		strncpy(ActuatorSerialNumber, "0", SERIAL_NUM_SIZE - 1);
		ActuatorSerialNumber[SERIAL_NUM_SIZE - 1] = '\0'; 

		strncpy(CalibrationDate, "0", DATE_SIZE_12_HR_FORMAT - 1);
		CalibrationDate[DATE_SIZE_12_HR_FORMAT - 1] = '\0';

		strncpy(MacId, "0", MAC_ID_SIZE - 1);
		MacId[MAC_ID_SIZE - 1] = '\0'; 

		strncpy(SafetyVersion, "0", VERSION_SIZE - 1);
		SafetyVersion[VERSION_SIZE - 1] = '\0'; 
	}
	
}__attribute__((packed))  MachineDetailsStruct;

#endif


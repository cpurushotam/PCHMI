/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 		This file contains the Prototypes for various common code and macros that are used for all components.
***************************************************************************/
#ifndef COMMONS_H_
#define COMMONS_H_

// debug control
#define ACT_DBG 	0
#define LOGIN_DBG	0
#define SOCKET_DBG  0
#define CTRL_DBG 	1
#define DSP_DBG 	0
#define UI_DBG 		0
#define DB_DBG 		0
#define CONSOLE_DBG	1

//MMC2/eMMC Storage
#ifdef __VXWORKS__
	#define MMC_EMMC_DEV_NAME "/mmc1"
	#define ROMFS_DEV_NAME "/romfs"
	#define USB_DEV_NAME "/bd0a"
	#define NFS_MOUNT_PATH "/nfs"
#else //When running RTP application on Ubuntu Linux
	#define MMC_EMMC_DEV_NAME "mmc1"
	#define ROMFS_DEV_NAME "romfs"
	#define USB_DEV_NAME "bd0a"
	#define NFS_MOUNT_PATH "nfs"
#endif

#define PATH_SEPARATOR		"/"
#define CONFIG_FILES_DIR "config_files"

//EMMC wear levels
#define EMMC_WEAR_LEVEL_LOW				0
#define EMMC_WEAR_LEVEL_MEDUIM			50
#define EMMC_WEAR_LEVEL_ALARM			80
#define EMMC_WEAR_LEVEL_MAX				100
#define EMMC_WEAR_CYCLE_CHECK			100000	//count for checking wear level of eMMC after every 100000 weld cycle counts.
//Database file names.
#define COMMON_DB_FILE_NAME 			"common_database.db"
#define ACE_DB_FILE_NAME 				"ace_database.db"
//Config file names
#define CONF_A_FILE_NAME 				"config_A.out"
#define CONF_B_FILE_NAME 				"config_B.out"
#define SYSTEM_TYPE_FILE_NAME 			"SystemType.txt"
#define SYSTEM_FREQUENCY_FILE_NAME 		"SystemFrequency.txt"
#define LAST_USED_WELD_RECIPE_NUMBER_FILE_NAME "last_used_weld_recipe_number.txt"
#define DELETED_WELD_RECIPES_FILE_NAME "deleted_recipes.txt"
#define SEND_CYLINDER_SIZE_AND_STROKE_LENGTH_TO_AC_TXT_FILE "SendCylinderSizeAndStrokeLengthToAC.txt"
#define SEND_ACTUATOR_SERIAL_NUM_TO_AC_TXT_FILE "SendSerialNumberToAC.txt"

//Database file paths on EMMC.
#define COMMON_DB_FILE_PATH_EMMC 		MMC_EMMC_DEV_NAME PATH_SEPARATOR COMMON_DB_FILE_NAME 
#define ACE_DB_FILE_PATH_EMMC 			MMC_EMMC_DEV_NAME PATH_SEPARATOR ACE_DB_FILE_NAME

//Config file paths on EMMC.
#define CONF_A_FILE_PATH_EMMC 		    MMC_EMMC_DEV_NAME PATH_SEPARATOR CONFIG_FILES_DIR PATH_SEPARATOR CONF_A_FILE_NAME 
#define CONF_B_FILE_PATH_EMMC 			MMC_EMMC_DEV_NAME PATH_SEPARATOR CONFIG_FILES_DIR PATH_SEPARATOR CONF_B_FILE_NAME

//Database file paths on romfs.
#define COMMON_DB_FILE_PATH_ROMFS 		ROMFS_DEV_NAME PATH_SEPARATOR COMMON_DB_FILE_NAME
#define ACE_DB_FILE_PATH_ROMFS 			ROMFS_DEV_NAME PATH_SEPARATOR ACE_DB_FILE_NAME

//Config file paths on ROMFS
#define CONF_A_FILE_PATH_ROMFS 			ROMFS_DEV_NAME PATH_SEPARATOR CONF_A_FILE_NAME
#define CONF_B_FILE_PATH_ROMFS 			ROMFS_DEV_NAME PATH_SEPARATOR CONF_B_FILE_NAME

//TO_BE_DONE - Temporary solution to store System Type choice of user. This text file should be removed in future. 
#define SYSTEM_TYPE_FILE_PATH_EMMC 	MMC_EMMC_DEV_NAME PATH_SEPARATOR SYSTEM_TYPE_FILE_NAME
//TO_BE_DONE - Temporary solution to store System Frequency choice of user. This text file should be removed in future. 
#define SYSTEM_FREQUENCY_FILE_PATH_EMMC  MMC_EMMC_DEV_NAME PATH_SEPARATOR  SYSTEM_FREQUENCY_FILE_NAME
//To store the last used weld recipe number to avoid duplication in weld recipe serial number
#define LAST_USED_WELD_RECIPE_NUMBER_FILE_PATH_EMMC  MMC_EMMC_DEV_NAME PATH_SEPARATOR LAST_USED_WELD_RECIPE_NUMBER_FILE_NAME
//To store the list of deleted weld recipe
#define DELETED_WELD_RECIPES_FILE_NAME_FILE_PATH_EMMC  MMC_EMMC_DEV_NAME PATH_SEPARATOR DELETED_WELD_RECIPES_FILE_NAME

//Text file to know if config install is done or not
#define SEND_VAL_TO_ACTUTOR_TEXT_FILE_PATH_EMMC  MMC_EMMC_DEV_NAME PATH_SEPARATOR SEND_CYLINDER_SIZE_AND_STROKE_LENGTH_TO_AC_TXT_FILE
//Text file to know if AC serial is setted or not
#define SEND_SERIAL_NUM_TO_ACTUTOR_TEXT_FILE_PATH_EMMC  MMC_EMMC_DEV_NAME PATH_SEPARATOR SEND_ACTUATOR_SERIAL_NUM_TO_AC_TXT_FILE

#define AC_FIRMWARE_BINARY_NAME "actuator.bin"
/*This file holds the serial numbers read from database during factory reset operation. 
The file gets deleted on next power cycle when the serial numbers from this file are read and updated back in database*/
#define FACTORY_RESET_TXT_NAME "factoryReset.txt"

#define FACTORY_RESET_FILE_PATH_EMMC   MMC_EMMC_DEV_NAME PATH_SEPARATOR FACTORY_RESET_TXT_NAME

#define FACTORY_RESET_KEY_VALUE_SEPRATOR        ": "

#define MACHINE_SERIAL_NO        "MachineSerialNumber"
#define POWER_SUPPLY_SERIAL_NO   "PowerSupplySerialNumber"
#define ACTUATOR_SERIAL_NO       "ActuatorSerialNumber"

#define MACHINE_SERIAL_NO_TXT          MACHINE_SERIAL_NO FACTORY_RESET_KEY_VALUE_SEPRATOR
#define POWER_SUPPLY_SERIAL_NO_TXT     POWER_SUPPLY_SERIAL_NO FACTORY_RESET_KEY_VALUE_SEPRATOR
#define ACTUATOR_SERIAL_NO_TXT         ACTUATOR_SERIAL_NO FACTORY_RESET_KEY_VALUE_SEPRATOR

//TODO:Please uncomment to use RS-485 interface
#ifdef __VXWORKS__
#define RS_485 
#endif

#define HMI_SOCKET_PORT   1600
#define AC_SOCKET_PORT    1601

// ACInputs bits of TxPDO_AC
#define SS1MASK 					0x01
#define SS2MASK 					0x02

#ifdef  RS_485
#define GRDDETMASK 					0x00000002 
#define ULSMASK 					0x00000001
#define TRSMASK 					0x00000008
#else
#define GRDDETMASK 					0x04
#define ULSMASK 					0x08
#define TRSMASK 					0x10
#endif
#define PB_OUT_STATUS				0x00000004
 
#define BOTHSTARTSWITCHMASK 		0x03


typedef struct RxPDO_AC
{
	uint32_t	SCState;
	uint32_t	ACControlEvent;
	uint32_t	ACOutputs;
}RxPDO_AC;

typedef struct TxPDO_AC
{
	uint32_t  ActualForce; //TO_BE_DONE - Change to float
	float 	ActualDistance;
	float 	WeldPressure;
	float	ActualVelocity;
	uint32_t  ACStatusEvent;
	uint32_t  ACState;
	uint32_t  ACInputs;
}TxPDO_AC;

typedef enum
{
	EVENT_AC_CLEAR_ALARMS,
	FIELDBUS_WELD_CYCLE_REQUEST,
} AC_CONTROL_EVENTS;

typedef enum 
{
	PB_RELEASED		= 0,
	BOTH_PB_PRESSED,
	EN_FAULT,
	HOME_POS,
	READY_POS,
	PART_CONTACT_FOUND
} AC_STATUS_EVENTS;


typedef enum
{
	CONVERTER_COOLING = 7
} AC_OUTPUT_BIT;

// alarms process limits ID ranges
enum
{
	ALARM_PROCESS_LIMIT_PRA_START = 0x500,
	ALARM_PROCESS_LIMIT_PSA_START = 0x550,
};

enum ErrorTypeAC {
  ERR_NONE = 				0,
  ERR_PART_WINDOW =			0x0001,
  ERR_RECALIBRATE =			0x0004,
};

typedef	enum 
{
	NO_STATE = -1,
	PREREADY, 
	SC_READY, 
	START_SWITCH, 
	WAIT_FOR_TRIGGER, 
	WELD_SONIC_ON, 
	HOLD, 
	WAIT_FOR_READY_POSITION, 
	SC_ALARM, 
	WAIT_FOR_PART_CONTACT,
	SEEK_SONIC_ON, 
	SCAN_SONIC_ON, 
	PRESSURE_CALIBRATION, 
	FORCE_CALIBRATION,
	TEST_SONICS_ON,
	HORN_DOWN,
	UNDEFINED_STATE,
	JOG_UP,
	JOG_DOWN,
	HORN_CLAMP_ALARM,
	TOOLING,
	POWER_UP,
	AC_TO_HOME,
	AC_TO_READY,
	SC_UNREACHABLE = 0xFF
 } SCSTATES;

typedef enum
{
	POWERUP,
	AC_READY,
	DOWN_STROKE,
	RETURN_STROKE,
	AC_ALARM,
	WELD_HOLD,
	AC_ESTOP,
	GOING_TO_POSITION,
} ACSTATES;
#endif

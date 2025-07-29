/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE system general data related structure definition.

***************************************************************************/
#ifndef SYS_CONFG_GEN_STRUCT_ACE_H_
#define SYS_CONFG_GEN_STRUCT_ACE_H_

#include <cstring>
#include <map>
#include "Common_Definitions.h"

// Size of KEY
constexpr int  SERVICE_KEY_SIZE = 13;
// Size of BARCODE_RECIPE_PREFIX
constexpr int  BARCODE_RECIPE_PRFX_SIZE = 50;
// Size of WELDER_NAME
constexpr int  MAX_WELDER_NAME_LENGTH  = 21;

// Maximum IP Address supported
constexpr int  MAX_WELDER_IPADDRESS  = 20;

// Staring IP Address range - number
constexpr int  IP_ADDRESS_START_RANGE  = 100;

constexpr char ASC_SUBNET_MASK_FOR_HMI[] = "255.255.255.0";
#define ASC_HMI_COMMUNICATION_INTERFACE_NAME "cpsw0"

// definition for SUB-ID of memory block
typedef enum{
    SUB_ID_SYSTEM_CONFIG_GEN_READDATA = 1,
    SUB_ID_SYSTEM_CONFIG_GEN_UPDATE_DATA,
	SUB_ID_SYSTEM_CONFIG_GEN_RESET_TO_DEFAULT_REQUEST,
	SUB_ID_SYSTEM_CONFIG_GEN_KEY_VERIFY_REQUEST,
	SUB_ID_SYSTEM_CONFIG_GEN_RESULT,
	SUB_ID_SYSTEM_CONFIG_GEN_SET_SINGLE_DATA,
    SUB_ID_SYSTEM_CONFIG_GEN_RESET_BRSNSRVC_KEY,

}UNIT_SUB_ID;

// definition for UNIT ENUM
typedef enum UNIT {
    METRIC =0 ,
    IMPERIAL
}UNIT;

// definition for AUTHORITYCHECK ENUM.
typedef enum AUTHORITYCHECK {
    OFF = 0 ,
    BASIC
}AUTHORITYCHECK;

// definition for MEMORYFULLACTION ENUM
typedef enum MEMORYFULLACTION {
    CONTINUE =0 ,
    STOP
}MEMORYFULLACTION;

// definition for POWERUPOPTION ENUM
typedef enum POWERUPOPTION {
	POWER_UP_NONE = 0,
	POWER_UP_SEEK,
	POWER_UP_SCAN
}POWERUPOPTION;

// definition for system configuration status
typedef enum
{
	SYSTEM_CONFIG_UPDATE_SUCCESS,
	SYSTEM_CONFIG_UPDATE_RESPONSE_UNKNOWN,
	SYSTEM_CONFIG_UPDATE_FAILURE,
}SYSTEM_CONFIG_UPDATE_STATUS;

// definition for key verify status
typedef enum
{
	KEY_VERIFY_SUCCESS,
	KEY_VERIFY_FAILURE
}KEY_VERIFY_STATUS;

// ENUM of Attributes for system information Object.
typedef enum 
{
    SG_WELDERNAME=1,
	SG_AUTHORITYCHECK,
	SG_MEMORYFULLACTION,
	SG_BARCODERECALLRECIPEPREFIX,
	SG_POWERUPOPTION,
	SG_PARTID,
	SG_UNITDISPLAY,
	SG_CLEARMEMORYATPOWERUP,
	SG_CLEARMEMORYWITHRESET,
	SG_PARALLELWELDRESULTSTORAGE,
	SG_CLAMPONALARM,
	SG_WELDRECIPEUNIQUESERIALNUMGENSTATUS
}SYS_CONFIG_GENERAL_INDEX;

typedef enum {
    ASC_IP_ADDRESS_192_168_1_100 = 100,
    ASC_IP_ADDRESS_192_168_1_101,
    ASC_IP_ADDRESS_192_168_1_102,
    ASC_IP_ADDRESS_192_168_1_103,
    ASC_IP_ADDRESS_192_168_1_104,
    ASC_IP_ADDRESS_192_168_1_105,
    ASC_IP_ADDRESS_192_168_1_106,
    ASC_IP_ADDRESS_192_168_1_107,
    ASC_IP_ADDRESS_192_168_1_108,
    ASC_IP_ADDRESS_192_168_1_109,
    ASC_IP_ADDRESS_192_168_1_110,
    ASC_IP_ADDRESS_192_168_1_111,
    ASC_IP_ADDRESS_192_168_1_112,
    ASC_IP_ADDRESS_192_168_1_113,
    ASC_IP_ADDRESS_192_168_1_114,
    ASC_IP_ADDRESS_192_168_1_115,
    ASC_IP_ADDRESS_192_168_1_116,
    ASC_IP_ADDRESS_192_168_1_117,
    ASC_IP_ADDRESS_192_168_1_118,
    ASC_IP_ADDRESS_192_168_1_119
} ASC_IP_ADDRESS_FOR_HMI;

//Holds the changed parameter identifier and value.
typedef struct ChangedSysConfGenParameter
{
	int GeneralParamID; //Holds the changed parameter identifier.
	char Value[BARCODE_RECIPE_PRFX_SIZE]; //Holds the changed value.
	ChangedSysConfGenParameter()
	{
		GeneralParamID = -1;
		memset(Value, 0, sizeof(Value));
	}
}__attribute__((packed)) ChangedSysConfGenParameter;

// Elements present at address pointed by Memoryblock::data
typedef struct SystemConfigGeneralStruct{
	char					  welderName[MAX_WELDER_NAME_LENGTH ];
	AUTHORITYCHECK         	  AuthorityCheck;
	MEMORYFULLACTION          memoryFullAction;
	char  					  BarcodeRecipePrefix[BARCODE_RECIPE_PRFX_SIZE];
	POWERUPOPTION 			  powerupoption;
	bool                      PartID;
    UNIT         			  currUnit;
    bool                      ClearMemoryAtPowerup;
    bool                      ClearMemoryWithReset;
    bool                      ParallelWeldResultStorageStatus;
    bool                      ClampOnAlarm;    
    char					  key[SERVICE_KEY_SIZE];
    bool                      WeldRecipeUniqueSerialNumGenStatus;
    ASC_IP_ADDRESS_FOR_HMI      ASCIPAddress;
    
    // Constructor
    SystemConfigGeneralStruct() 
    {
    	strncpy(welderName, "Polaris Welder", MAX_WELDER_NAME_LENGTH - 1);
    	welderName[MAX_WELDER_NAME_LENGTH - 1] = '\0';
    	AuthorityCheck = BASIC;
    	memoryFullAction = CONTINUE;
    	strncpy(BarcodeRecipePrefix, "", BARCODE_RECIPE_PRFX_SIZE - 1);
    	BarcodeRecipePrefix[BARCODE_RECIPE_PRFX_SIZE - 1] = '\0';
    	powerupoption = POWER_UP_NONE;
    	PartID = false;
		currUnit = METRIC;
		ClearMemoryAtPowerup = false;
		ClearMemoryWithReset = false;
		ParallelWeldResultStorageStatus = true;
		ClampOnAlarm = false;		
		strncpy(key, "", SERVICE_KEY_SIZE - 1);
		key[SERVICE_KEY_SIZE - 1] = '\0';
		WeldRecipeUniqueSerialNumGenStatus = true;
        ASCIPAddress = ASC_IP_ADDRESS_192_168_1_100;
    }
}__attribute__((packed)) SystemConfigGeneralStruct;

extern const std::map <MEMORYFULLACTION , std::string> MemmFullActTypeName;
extern const std::map <UNIT , std::string> UnitTypeName;
extern const std::map <AUTHORITYCHECK , std::string> AuthorityChkTypeName;
extern const std::map <POWERUPOPTION , std::string> PowerUpOptTypeName;
extern const std::map<ASC_IP_ADDRESS_FOR_HMI, std::string> ASCIPAddressTypeNameForHMI;

#endif

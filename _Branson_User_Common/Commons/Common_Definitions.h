/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
This file includes common structures and enums definition.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/06/2023 - Initial version
 
***************************************************************************/

#ifndef COMMON_DEFINITIONS_H_
#define COMMON_DEFINITIONS_H_
#include <cstdint>
#include <string>
#include <map>

#define WAL_FILE_NAME      "-wal"
#define SHM_FILE_NAME      "-shm"

//tuple values for Minimum values for 20K, 30K and 40K Frequencies
constexpr int MIN_VALUE_20K 	   			= 1;
constexpr int MIN_VALUE_30K 	   			= 4;
constexpr int MIN_VALUE_40K 	   			= 7;

//tuple values for Maximum values for 20K, 30K and 40K Frequencies
constexpr int MAX_VALUE_20K 	   			= 2;
constexpr int MAX_VALUE_30K	   				= 5;
constexpr int MAX_VALUE_40K	   				= 8;

//tuple values for default values for 20K, 30K and 40K Frequencies
constexpr int DEFAULT_VALUE_20K 	   		= 3;
constexpr int DEFAULT_VALUE_30K	   			= 6;
constexpr int DEFAULT_VALUE_40K 	   		= 9;

//tuple values for Column name, Table name and data type for recipe parameters
constexpr int COLUMN_NAME 	   				= 11;
constexpr int TABLE_NAME 	   				= 10;
constexpr int DATA_TYPE   					= 0;
constexpr int PARAM_NAME 	   				= 12;

//tuple values for alarm subcategory, error type, description and reason
constexpr int ALARM_SUB_CATEGORY			= 0;
constexpr int ALARM_ERROR_TYPE				= 1;
constexpr int ALARM_DESC					= 2;
constexpr int ALARM_REASON					= 3;

// Static configuration for byte_array size used for log info except alarm and event.
static constexpr int BUFF_SIZE_MAX 	= 64;
static constexpr int BUFF_SIZE 		= 16;

#ifdef __VXWORKS__
constexpr unsigned int MAX_SIZE_OF_MSG_LENGTH = 1000;
#else
constexpr unsigned int MAX_SIZE_OF_MSG_LENGTH = 768;
#endif

constexpr unsigned int BARCODE_DATA_SIZE = 51;
constexpr unsigned int BATCHID_SIZE = 51;
constexpr unsigned int USER_NAME_SIZE = 16;
constexpr unsigned int SERIAL_NUM_SIZE = 12;
constexpr unsigned int DATE_TIME_SIZE = 20;
constexpr unsigned int MACHINE_NAME_SIZE = 16;
constexpr unsigned int INTERFACE_SOURCE_SIZE = 30;
constexpr unsigned int PARAMETERID_SIZE = 100;
static constexpr unsigned int ALARM_ID_SIZE = 20;
constexpr unsigned int HASHED_PASSWORD_SIZE = 65;
constexpr unsigned int PLAIN_TEXT_PASSWORD_SIZE = 21;
constexpr unsigned int SALT_SIZE = 33;
constexpr unsigned int ALARM_NOTES_SIZE = 101;
constexpr unsigned int SERVICE_NAME_SIZE = 20;
constexpr unsigned int MAC_ID_SIZE = 20;
constexpr unsigned int VERSION_SIZE = 16;
constexpr unsigned int IP_SIZE = 16;
constexpr unsigned int GETPACKET_TIMEOUT = 10;	//10 milliseconds
constexpr unsigned int GETPACKET_TIMEOUT_EXTENDED = 1000;	//1000 milliseconds
constexpr unsigned int PUTPACKET_TIMEOUT = 10;	//10 millisecond
constexpr unsigned int TRANSFERPACKET_TIMEOUT = 10;	//10 millisecond
constexpr unsigned int SW_UPGRADE_MAX_FILE_NAME_SIZE = 30; //software upgrade max file name size
constexpr unsigned int OPCUA_CERTIFICATE_MAX_FILE_NAME_SIZE = 50; //Opcua Certification max file name size
constexpr unsigned int OPCUA_CERTIFICATE_MIN_FILE_NAME_SIZE = 4; //Opcua Certification min file name size

//Cycle time for background communication thread
static constexpr unsigned int BG_CYCLIC_TIME = 10; //10 milliseconds
static constexpr unsigned int HEART_BEAT_MESSAGE_COUNTER = (1000/BG_CYCLIC_TIME); //1000 = 1 second, so heart beat message gets sent every 1 second.
//Max read retry count for ASC to HMI communication
static const int MAX_READ_RETRY_COUNT = (HEART_BEAT_MESSAGE_COUNTER * 2);

static constexpr uint16_t	DIGITAL_IO_MAX_INPUTS	= 9;
static constexpr uint16_t	DIGITAL_IO_MAX_OUTPUTS 	= 8;
static constexpr uint16_t	ANALOG_IO_MAX_INPUTS	= 2;
static constexpr uint16_t	ANALOG_IO_MAX_OUTPUTS	= 2;

static constexpr uint16_t 	FB_IO_MAX_INPUTS       = 3;
static constexpr uint16_t	FB_IO_MAX_OUTPUTS		= 3;

static constexpr uint16_t	MAX_NUMBER_OF_REFERENCE_WELD_DATA 	= 3;
constexpr unsigned int REF_GRAPH_NAME_SIZE = 21;

constexpr unsigned int SERVICENOTES_SIZE = 1000;
constexpr unsigned int SERVICE_HISTORY_NOTES = 10;
constexpr unsigned int BOARD_NAME_SIZE = 21;

constexpr unsigned int DATEFORMAT_SIZE = 9;
constexpr unsigned int TIMEFORMAT_SIZE = 9;
constexpr unsigned int TWELVEHRFORMAT_SIZE = 12;
constexpr unsigned int DATE_SIZE_12_HR_FORMAT = 23;

// ENUM defined for different types of WELD that supported by system
typedef enum 
{ 
	TIMEMODE,
	ENERGYMODE,
	PEAKPOWERMODE,
	GRDDETECTMODE,
	ABSMODE,
	COLLAPSEMODE,
	CONTINUOUS,
	MULTI,
	MAX_MODES
}WELDMODES;

// ENUM to identify interface
typedef enum
{
	UNKNOWN_INTERFACE,
	ASC_FIRMWARE,
	ASC_CONSOLE_INTERFACE,
	HMI_INTERFACE,
	FIELDBUS_INTERFACE,
	OPC_UA_INTERFACE,
	DIGITAL_INPUT_INTERFACE,
	KEYPAD_INTERFACE
}INTERFACE_IDENTIFIER;

// buffer to hold changed value of seek, test and horn scan parameter value
#define BUFFER_TO_HOLD_CHANGED_VALUE 	16

typedef enum PARAM_DATA_TYPE
{
    INT_PARAM,
	UNSIGNED_INT_PARAM,
    FLOAT_PARAM,
    DOUBLE_PARAM,
    BOOL_PARAM,
    CHAR_ARRAY_PARAM,
	UNKNOWN_DATA_TYPE
}PARAM_DATA_TYPE;


extern const std::map <bool , std::string> boolStringTypeName;

#endif /* COMMON_DEFINITIONS_H_*/

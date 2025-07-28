/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Profinet Network Configuration Settings(IP Address, Netmask, Gateway Address, Station Name)
  related implementation.
 ***************************************************************************/

#ifndef BRANSON_USER_COMMON_COMMONS_PROFINETSTRUCTURE_H_
#define BRANSON_USER_COMMON_COMMONS_PROFINETSTRUCTURE_H_

#include "Common_Definitions.h"

#define IM_RECORD_SIZE                     64
#define PN_STATION_NAME_SIZE               240
#define IP_ADDRESS_SIZE                    16
#define HEX_CHARS_PER_BYTE                 2 /* characters for each byte of Hex value */

// Data Interface ID declarations
typedef enum
{
	PROFINET_NETWORK_SETUP_DATA_SAVE = 1,
	PROFINET_NETWORK_DATA_READ,
	PROFINET_NETWORK_DATA_RESET_TO_DEFAULT,
}MEMORY_BLOCK_SUB_ID_PROFINET;

/* Type of parameters get stored in Database through HMI or Profinet*/
typedef enum PROFINET_NETWORK_SETTINGS_TYPE_DB
{
	IP_NETMASK_GATEWAY = 1,
	STATION_NAME,
	IM1_RECORD,
	IM2_RECORD,
	IM3_RECORD,
	IP_NETMASK_GATEWAY_STATION_NAME,
	PNS_NONE,
}PROFINET_NETWORK_SETTINGS_PARAM_TYPE;

typedef struct ProfinetSettingsStruct
{

	char StationName[PN_STATION_NAME_SIZE];
	char IpAddress[IP_ADDRESS_SIZE];
	char Netmask[IP_ADDRESS_SIZE];
	char Gateway[IP_ADDRESS_SIZE];
	uint8_t IM1_Record[IM_RECORD_SIZE];
	uint8_t IM2_Record[IM_RECORD_SIZE];
	uint8_t IM3_Record[IM_RECORD_SIZE];

}__attribute__((packed)) ProfinetSettingsStruct;

typedef enum
{
	INDEX_STATION_NAME = 0,
	INDEX_IP_ADDRESS,
	INDEX_NETMASK,
	INDEX_GATEWAY,
	INDEX_IM1,
	INDEX_IM2,
	INDEX_IM3,
}PROFINET_SET_PARAMS;


#endif /* BRANSON_USER_COMMON_COMMONS_PROFINETSTRUCTURE_H_ */

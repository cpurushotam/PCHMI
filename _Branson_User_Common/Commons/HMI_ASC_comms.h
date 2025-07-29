/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
/*
  * shared_common.h
 *
 *  Created on: May 28, 2021
 *      Author: JWang
 *      
 *  All the definition that need to be used both on ASC and HMI software should be in here.
 *  
 *  
 */

#ifndef SHARED_COMMON_H_
#define SHARED_COMMON_H_

#include <stdint.h>

//system information structure for the HMI response parsing 
#define SYSINFO_SIZE						16
#define MAC_ADDR_SIZE      					18

struct SYSTEMINFO
{
	int32_t	psLifeCounter;
	int32_t   actuatorlifecounter;
	int32_t   generalAlarmCounter;
	int32_t   overloadAlarmCounter;
	int32_t	actuatorOverloads;
	int32_t	actuatorStrokeLength;
	uint16_t  psFrequency;
	int32_t   psWatt;
	uint8_t   calibrationStatus;
	uint8_t   psType;
	uint8_t   actuatorType;
	char    modelName[SYSINFO_SIZE];
	char    version_SC[SYSINFO_SIZE];
	char    version_PC[SYSINFO_SIZE];
	char    version_AC[SYSINFO_SIZE];
	char    psAssemblyNumber[SYSINFO_SIZE];
	char    actuatorAssembly[SYSINFO_SIZE];
	char    stackAssembly[SYSINFO_SIZE];
	char    psMacID[MAC_ADDR_SIZE];
	char    psIP[SYSINFO_SIZE];
	char    dateTime[2 * SYSINFO_SIZE];
	uint16_t  crc_SC;
	uint16_t  crc_AC;
};


#endif

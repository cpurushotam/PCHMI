/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the seek result related implementation
 ***************************************************************************/

#ifndef SEEK_RESULT_STRUCTURES_H_
#define SEEK_RESULT_STRUCTURES_H_

#include <map>
#include <tuple>
#include "Common_Definitions.h"


typedef enum
{
	SEEK_RUN_OPERATION = 1,
	SEEK_RESULT_DATA,
	SYNC_SEEK_RESULT_DATA
}SEEK_RESULT_ACE_SUB_ID;

typedef struct SeekResultstruct
{
	int32_t SeekResultIndex;
	float PeakPower;
	uint32_t StartFrequency;
	uint32_t EndFrequency;
	char DateTime[DATE_SIZE_12_HR_FORMAT];
	
	SeekResultstruct()
	{
		ResetParameters();
	}
	
	void ResetParameters()
	{
		SeekResultIndex = 1;
		PeakPower = 0.0f;
		StartFrequency = 0;
		EndFrequency = 0;
		strncpy(DateTime, "NA", sizeof(DateTime));
	}
		
}__attribute__((packed))  SeekResultstruct;

#endif


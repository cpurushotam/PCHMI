/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Horn Scan Result related implementation
 ***************************************************************************/

#ifndef HORN_SCAN_RESULT_STRUCTURES_H_
#define HORN_SCAN_RESULT_STRUCTURES_H_

#include <map>
#include <tuple>
#include "Common_Definitions.h"

//Maximum number of Horn Scan result structures (HornScanResultstruct) sent in one chunk
constexpr int MAX_NUM_OF_HORN_SCAN_RESULTS_IN_ONE_CHUNK = 100; //not confirm with value

//Maximum number of Horn Scan result structures sent to HMI
constexpr int MAX_NUM_OF_HISTORICAL_HORN_SCAN_RESULTS_TO_SEND = 1000;  //not confirm with value

typedef enum
{
    READ_LAST_HORN_SCAN_RESULT_DATA = 1,
    READ_HISTORICAL_HORN_SCAN_RESULT_DATA,
    START_HORN_SCAN_OPERATION,
	ABORT_HORN_SCAN_OPERATION,
	SYNC_HORN_SCAN_RESULT_DATA
}HORN_SCAN_RESULT_SUB_ID;

typedef enum
{
	DB_READ_LAST_HORN_SCAN_RESULT_DATA = 1,
    DB_READ_HISTORICAL_HORN_SCAN_RESULT_DATA
}HORN_SCAN_RESULT_DB_READ_OPERATION_ID;

typedef struct HornScanResultstruct
{
	int32_t HornScanResultIndex;
	char DateTime[DATE_SIZE_12_HR_FORMAT];
	uint32_t MainParallelResonantFrequency;
	uint16_t SecondParallelResonantFrequency;
	uint32_t ThirdParallelResonantFrequency;
	uint32_t FirstSeriesResonantFrequency;
	uint32_t SecondSeriesResonantFrequency;
	uint32_t ThirdSeriesResonantFrequency;
	
	
	HornScanResultstruct()
	{
		ResetParameters();
	}
	
	void ResetParameters()
	{
		HornScanResultIndex = 1;
		strncpy(DateTime, "NA", sizeof(DateTime));
		MainParallelResonantFrequency = 0;
		SecondParallelResonantFrequency = 0;
		ThirdParallelResonantFrequency = 0;
		FirstSeriesResonantFrequency = 0;
		SecondSeriesResonantFrequency = 0;
		ThirdSeriesResonantFrequency = 0;		
	}
		
}__attribute__((packed)) HornScanResultstruct;

#endif


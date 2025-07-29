/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the seek recipe related implementation
 ***************************************************************************/

#ifndef SEEK_RECIPE_STRUCTURES_H_
#define SEEK_RECIPE_STRUCTURES_H_

#include <map>
#include <tuple>
#include <string>
#include "Common_Definitions.h"

typedef struct SeekRecipestruct
{
	SeekRecipestruct();
	void SetParametersAsPerSystemFrequency();
	
	int32_t SeekFreqLimitHigh;    		//This is the upper frequency limit for the Seek function.If the read frequency from the DSP
										//exceeds this value, it will generate an alarm
	int32_t SeekFreqLimitLow;     		//This is the lower frequency limit for the Seek function. If the read frequency from the DSP
										//drops below this value, it will generate an alarm
	int32_t SeekFreqOffset;       		//This value will be applied to the start frequency value when Seek is initiated.
	                             		//Weld Start Frequency = Digital Tune + Frequency Offset + Memory Offset
	                             		//Seek Start Frequency = System Midband + Frequency Offset + Memory Offset
	bool   SeekMemClearBeforeSeek;  	//This will set MemoryOffset equal to 0 at the start of the Seek
	float    SeekTime;                	//time required for the seek operation
	float    SeekAmplitudeRampTime;   	//Time in milliseconds that it will take for the amplitude to reach 100%
	uint32_t SeekAmplitude;           	//Target amplitude for the DSP during seek function
	int32_t SeekAmpProportionalGain; 	//The following 6 values are the control loop parameters for the ultrasonics.
										//Weld and Seek ideally have different optimal values
	int32_t SeekAmpIntegralGain;
	int32_t SeekAmpDerivativeGain;
	int32_t SeekPhaseProportionalGain;
	int32_t SeekPhaseIntegralGain;
	int32_t SeekPhaseDerivativeGain;
	int32_t	BlindtimeSeek;
/*following parameter's are present in GSX-E2 project only . */
	int32_t SeekPhaseloopCF;
		
}__attribute__((packed))  SeekRecipestruct;

typedef enum
{
	SEEK_RECIPE_SAVE = 1,
	SEEK_RECIPE_RESET_TO_DEFAULT,
	SEEK_RECIPE_DATA,
	SEEK_RECIPE_UPDATE_RESULT
}SEEK_RECIPE_ID;

typedef enum
{
	SEEK_RECIPE_UPDATE_SUCCESS,
	SEEK_RECIPE_UPDATE_RESPONSE_UNKNOWN,
	SEEK_RECIPE_UPDATE_FAILURE,
	SEEK_RECIPE_UPDATE_VALUE_OUT_OF_RANGE,
	SEEK_RECIPE_UPDATE_DATATYPE_NOT_SUPPORTED,

}SEEK_RECIPE_UPDATE_STATUS;

typedef enum
{
	SEEK_FREQ_LIMIT_HIGH,
	SEEK_FREQ_LIMIT_LOW,
	SEEK_FREQ_OFFSET,
	SEEK_MEM_CLEAR_BEFORE_SEEK,
	SEEK_TIME,
	SEEK_AMPLITUDE_RAMP_TIME,
	SEEK_AMPLITUDE,
	SEEK_AMPLITUDE_PROPORTIONAL_GAIN,
	SEEK_AMPLITUDE_INTEGRAL_GAIN,
	SEEK_AMPLITUDE_DERIVATIVE_GAIN,
	SEEK_PHASE_PROPORTIONAL_GAIN,
	SEEK_PHASE_INTEGRAL_GAIN,
	SEEK_PHASE_DERIVATIVE_GAIN,
	BLIND_TIME_SEEK,
	SEEK_PHASE_LOOPCF,
	
}SEEK_RECIPE_PARAM_ID;

extern const std::map < SEEK_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > SeekRecipeParamMap;


//Holds the changed seek recipe parameter identifier and value.
typedef struct ChangedSeekRecipeParameter
{
	SEEK_RECIPE_PARAM_ID SeekRecipeParamID; //Holds the changed recipe parameter identifier.
	char Value[BUFFER_TO_HOLD_CHANGED_VALUE];//Holds the changed value.
	
}__attribute__((packed)) ChangedSeekRecipeParameter;

#endif


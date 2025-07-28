/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test recipe related implementation
 ***************************************************************************/

#ifndef TEST_RECIPE_STRUCTURE_H_
#define TEST_RECIPE_STRUCTURE_H_

#include <map>
#include <tuple>
#include <string>
#include "Common_Definitions.h"

typedef struct TestRecipestruct
{
	TestRecipestruct();
	void SetParametersAsPerSystemFrequency();

	int32_t  TestFreqLimitHigh;
	int32_t  TestFreqLimitLow;
	int32_t  TestFreqOffset;
	bool   	 ClearMemoryBeforeTest;
	float 	 TestAmplitudeRampTime;
	uint32_t TestAmplitude;
	int32_t  TestAmpProportionalGain;
	int32_t  TestAmpIntegralGain;
	int32_t  TestAmpDerivativeGain;
	int32_t  TestPhaseProportionalGain;
	int32_t  TestPhaseIntegralGain;
	int32_t  TestPhaseDerivativeGain;
	int32_t  TestPhaseloopCF;
}__attribute__((packed))  TestRecipestruct;

typedef enum
{
	TEST_RECIPE_SAVE = 1,
	TEST_RECIPE_RESET_TO_DEFAULT,
	TEST_RECIPE_DATA,
	TEST_RECIPE_UPDATE_RESULT

}TEST_RECIPE_ID;


typedef enum
{
	TEST_RECIPE_UPDATE_SUCCESS,
	TEST_RECIPE_UPDATE_RESPONSE_UNKNOWN,
	TEST_RECIPE_UPDATE_FAILURE,
	TEST_RECIPE_UPDATE_VALUE_OUT_OF_RANGE,
	TEST_RECIPE_UPDATE_DATATYPE_NOT_SUPPORTED,
}TEST_RECIPE_UPDATE_STATUS;

typedef enum
{
	TEST_FREQ_LIMIT_HIGH,
	TEST_FREQ_LIMIT_LOW,
	TEST_FREQ_OFFSET,
	CLEAR_MEMORY_BEFORE_TEST,
	TEST_AMPLITUDE_RAMP_TIME,
	TEST_AMPLITUDE,
	TEST_AMPLITUDE_PROPORTIONAL_GAIN,
	TEST_AMPLITUDE_INTEGRAL_GAIN,
	TEST_AMPLITUDE_DERIVATIVE_GAIN,
	TEST_PHASE_PROPORTIONAL_GAIN,
	TEST_PHASE_INTEGRAL_GAIN,
	TEST_PHASE_DERIVATIVE_GAIN,
	TEST_PHASE_LOOPCF,
	
}TEST_RECIPE_PARAM_ID;

extern const std::map < TEST_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > TestRecipeParamMap;

//Holds the changed test recipe parameter identifier and value.
typedef struct ChangedTestRecipeParameter
{
	TEST_RECIPE_PARAM_ID TestRecipeParamID; //Holds the changed recipe parameter identifier.
	char Value[BUFFER_TO_HOLD_CHANGED_VALUE]; //Holds the changed value.
	
}__attribute__((packed)) ChangedTestRecipeParameter;

#endif //TEST_RECIPE_STRUCTURE_H_

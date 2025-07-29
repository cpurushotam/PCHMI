/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the TestRecipeParamMap definition
 ***************************************************************************/

 #include "TestRecipeStructure.h"

const std::map < TEST_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > TestRecipeParamMap =
{
		//TO_BE_DONE - add proper min, max values.
		//Parameter Identifier, 			Data Type,  			20K_Min, 20K_Max, 20K_Def 	30K_Min,30K_Max ,30K_Def 	40K_Min, 40K_Max , 40K_Def 	Table Name, 		Column Name
		//Data from TestRecipe Table
        { TEST_FREQ_LIMIT_HIGH, 			{INT_PARAM,	 			"19950", "20450",  "20450",	"30000", "30750", "30750",	"39990", "40990", "40990", "TestRecipe", "TestFreqLimitHigh","Test Freq Limit High" } },
        { TEST_FREQ_LIMIT_LOW,				{INT_PARAM,  			"19450", "19950",  "19450", "29250", "30000", "29250", "38990", "39990", "38990", "TestRecipe", "TestFreqLimitLow",  "Test Freq Limit Low" } },
        { TEST_FREQ_OFFSET, 				{INT_PARAM, 			"-500",	"500", "0","-750", "750", "0", "-1000","1000", "0", "TestRecipe", "TestFreqOffset", "Test Freq Offset" } },
       
        { CLEAR_MEMORY_BEFORE_TEST, 		{BOOL_PARAM,  			"0",	"1", 	 "0",		"0",    "1", 	 "0",		"0",	"1", 	"0",		"TestRecipe",		"ClearMemoryBeforeTest", "Clear Memory Before Test" } },
		
        { TEST_AMPLITUDE_RAMP_TIME, 		{FLOAT_PARAM,	 		"0.0", 	"1.0",	 "0.08",	"0.0",	"1.0", "0.08",	"0.0",	"1.0", 	"0.08",		"TestRecipe",		"TestAmplitudeRampTime" , "Test Amplitude Ramp Time" } },
        { TEST_AMPLITUDE, 					{UNSIGNED_INT_PARAM,	 "10", 	"100",	 "50",		"10",	"100", 	 "50",		"10",	"100", 	"50",		"TestRecipe",		"TestAmplitude", "Test Amplitude" } },
		//TO_BE_DONE : PID Max values and Min values are dummy values need to change, might be changed
		//Default Values are refer from GSX-E1 build, might be changed
        { TEST_AMPLITUDE_PROPORTIONAL_GAIN, {INT_PARAM, 			 "-2147483648",	"2147483647", "20",	"-2147483648", "2147483647", "20", "-2147483648", "2147483647", "80", "TestRecipe",	"TestAmpProportionalGain", "Test Amp Proportional Gain" } },
        { TEST_AMPLITUDE_INTEGRAL_GAIN, 	{INT_PARAM,  			 "-2147483648",	"2147483647", "0", "-2147483648", "2147483647",	 "0", "-2147483648", "2147483647", 	"0", "TestRecipe", "TestAmpIntegralGain", "Test Amp Integral Gain" } },
        { TEST_AMPLITUDE_DERIVATIVE_GAIN, 	{INT_PARAM, 			 "-2147483648",	"2147483647", "0", "-2147483648", "2147483647",	 "0", "-2147483648", "2147483647", 	"0", "TestRecipe", "TestAmpDerivativeGain" ,"Test Amp Derivative Gain"} },
        { TEST_PHASE_PROPORTIONAL_GAIN, 	{INT_PARAM, 			 "-2147483648",	"2147483647", "4000", "-2147483648", "2147483647", "16000",	"-2147483648", "2147483647", "16000", "TestRecipe",	"TestPhaseProportionalGain", "Test Phase Proportional Gain" } },
        { TEST_PHASE_INTEGRAL_GAIN, 		{INT_PARAM, 			 "-2147483648",	"2147483647", "100", "-2147483648",	"2147483647", "400", "-2147483648", "2147483647", "2000", "TestRecipe",	"TestPhaseIntegralGain", "Test Phase Integral Gain" } },
        { TEST_PHASE_DERIVATIVE_GAIN, 		{INT_PARAM,				 "-2147483648",	"2147483647", "0", "-2147483648", "2147483647",	"-500", "-2147483648", "2147483647", "-500", "TestRecipe",	"TestPhaseDerivativeGain", "Test Phase Derivative Gain" } },
        
        { TEST_PHASE_LOOPCF, 				{INT_PARAM, 			 "50",	"500",	 "450",		"50",	"500",	"200",		"50",	"500","200",		"TestRecipe",		"TestPhaseloopCF", "Test Phase loop CF" } }

};  

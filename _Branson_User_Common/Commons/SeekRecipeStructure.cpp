/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the SeekRecipeParamMap definition
 ***************************************************************************/
 
 #include "SeekRecipeStructure.h"

const std::map < SEEK_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > SeekRecipeParamMap =
{
		//TO_BE_DONE - add proper min, max values.
		//Parameter Identifier, 			Data Type, 			 Min_20K, Max_20K, Def_20K, 	Min_30K, Max_30K, Def_30K, 	 Min_40K, Max_40K, Def_40K, Table Name, Column Name
		//Data from SeekRecipe Table
        { SEEK_FREQ_LIMIT_HIGH, 			{INT_PARAM,			 "19950",  "20450", "20450", 	 	"30000", "30750", "30750",	"39990", "40990", "40990",	"SeekRecipe", "SeekFreqLimitHigh", "Seek Freq Limit High" } },
        { SEEK_FREQ_LIMIT_LOW, 				{INT_PARAM,		 	 "19450",  "19950", "19450",		"29250", "30000", "29250",	"38990", "39990", "38990",	"SeekRecipe", "SeekFreqLimitLow", "Seek Freq Limit Low"  } },
        { SEEK_FREQ_OFFSET, 				{INT_PARAM,			 "-500",   "500",   "0",		 "-750", "750",   "0",		"-1000", "1000",  "0",		"SeekRecipe", "SeekFreqOffset", "Seek Freq Offset" } },
       
        { SEEK_MEM_CLEAR_BEFORE_SEEK, 		{BOOL_PARAM,		 "0",     "1",     "0",		 	"0",    "1",     "0",		"0",    "1",     "0",		"SeekRecipe", "SeekMemClearBeforeSeek", "Seek Mem Clear Before Seek" } },
		
        { SEEK_TIME, 						{FLOAT_PARAM, 		 "0.001", "1.0",  "0.5",	"0.001", "1.0",  "0.5",  "0.001", "1.0",  "0.5",	   "SeekRecipe",  "SeekTime",  "Seek Time" } },
        { SEEK_AMPLITUDE_RAMP_TIME, 		{FLOAT_PARAM, 		 "0.01",   "1.0",  "0.08",	"0.01",   "1.0",  "0.08", "0.01",   "1.0",  "0.08",	   "SeekRecipe", "SeekAmplitudeRampTime", "Seek Amplitude Ramp Time" } },
        { SEEK_AMPLITUDE, 					{UNSIGNED_INT_PARAM, "10",    "100",   "10",	 	"10",   "100",   "10",		"10",   "100",   "10",		"SeekRecipe", "SeekAmplitude", "Seek Amplitude" } },
       
		//TO_BE_DONE : PID Max values and Min values are dummy values need to change, might be changed
		//Default Values are refer from GSX-E1 build, might be changed
        { SEEK_AMPLITUDE_PROPORTIONAL_GAIN, {INT_PARAM,			 "-2147483648",     "2147483647",   "20", "-2147483648",   "2147483647",    "20",		"-2147483648",    "2147483647",   "80",		"SeekRecipe", "SeekAmpProportionalGain", "Seek Amp Proportional Gain" } },
        { SEEK_AMPLITUDE_INTEGRAL_GAIN, 	{INT_PARAM,			 "-2147483648",     "2147483647",   "0",  "-2147483648",   "2147483647",    "0",	 	"-2147483648",    "2147483647",   "0",		"SeekRecipe", "SeekAmpIntegralGain", "Seek Amp Integral Gain" } },
        { SEEK_AMPLITUDE_DERIVATIVE_GAIN, 	{INT_PARAM, 		 "-2147483648",     "2147483647",   "0",  "-2147483648",   "2147483647",    "0",		"-2147483648",    "2147483647",   "0",		"SeekRecipe", "SeekAmpDerivativeGain", "Seek Amp Derivative Gain" } },
        { SEEK_PHASE_PROPORTIONAL_GAIN, 	{INT_PARAM,          "-2147483648",     "2147483647",  "4000", "-2147483648", "2147483647",     "16000",	"-2147483648",    "2147483647", "16000",	"SeekRecipe", "SeekPhaseProportionalGain", "Seek Phase Proportional Gain" } },
        { SEEK_PHASE_INTEGRAL_GAIN, 		{INT_PARAM,          "-2147483648",     "2147483647",   "100",	 "-2147483648", "2147483647",    "400",		"-2147483648",    "2147483647", "12000",	"SeekRecipe", "SeekPhaseIntegralGain", "Seek Phase Integral Gain" } },
        { SEEK_PHASE_DERIVATIVE_GAIN, 		{INT_PARAM,          "-2147483648",     "2147483647",   "0",	 "-2147483648", "2147483647",    "-500",	"-2147483648", 	  "2147483647", "-500",	    "SeekRecipe", "SeekPhaseDerivativeGain", "Seek Phase Derivative Gain" } },
        
        { BLIND_TIME_SEEK, 					{INT_PARAM,          "0",     "1000",  "0",		 	"0",   "1000",   "0",		"0",    "1000",  "0",		"SeekRecipe", "BlindtimeSeek", "Blind time Seek" } },
        { SEEK_PHASE_LOOPCF, 				{INT_PARAM,          "50",    "500",   "200",	 	"50",  "500",    "200",		"50",   "500",   "200",		"SeekRecipe", "SeekPhaseloopCF", "Seek Phase loop CF" } }

};

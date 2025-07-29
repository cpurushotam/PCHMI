/**************************************************************************
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the HornScanRecipeParamMap definition
 ***************************************************************************/

#include "HornScanRecipeStructure.h"

const std::map < HORNSCAN_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string,std::string, std::string, std::string,std::string, std::string, std::string, std::string, std::string, std::string > > HornScanRecipeParamMap =
{
		//TO_BE_DONE - add proper min, max values.
		//Parameter Identifier, Data Type,      20_Min,  20_Max,  	20_Def    30_Min,  30_Max,  30_Def   40_Min,  40_Max,  40_Def     Table Name,         Column Name
		//Data from Horn Scan Recipe Table
        { FREQUENCY_START, {UNSIGNED_INT_PARAM, "19450",  "20450",	"19450", "29250", "30750", "29250", "38900", "40900", "38900",	"HornScanRecipe",	"FrequencyStart", "Frequency Start" } },
        { FREQUENCY_STOP,  {UNSIGNED_INT_PARAM, "19450",  "20450",	"20450", "29250", "30750", "30750", "38900", "40900", "40900",	"HornScanRecipe",	"FrequencyStop", "Frequency Stop" } },
        { FREQUENCY_STEP,  {UNSIGNED_INT_PARAM, "1",	  "100",	"1",     "1",	  "100",	"1",	"1",	 "100",		"1",	"HornScanRecipe",	"FrequencyStep", "Frequency Step" } },
		{ TIMEDELAY,       {FLOAT_PARAM, 		"0.01",  "0.1",	"0.01",	 	"0.01",  "0.1",	"0.01",		"0.01",  "0.1",	"0.01",		"HornScanRecipe",	"TimeDelay", "Time Delay" } },
		{ MAX_AMPLITUDE,   {UNSIGNED_INT_PARAM, "1",	  "100",	"10",    "1",     "100",	"10",	"1",	 "100",		"10",	"HornScanRecipe",	"MaxAmplitude", "Maximum Amplitude" } },
        { MAX_CURRENT,     {UNSIGNED_INT_PARAM, "1",	  "100",	"10",	 "1",     "100",	"10",	"1",	 "100",		"10",	"HornScanRecipe",	"MaxCurrent", "Maximum Current" } },
        { SET_DEGTUNE_WITHHORNSCAN, {BOOL_PARAM,"0",	  "1",		"1",	"0",      "1",		"1",	"0",	 "1",		"1",	"HornScanRecipe",	"SetDigTuneWithHornScan", "Digital Tune HornScan" } }
 
};



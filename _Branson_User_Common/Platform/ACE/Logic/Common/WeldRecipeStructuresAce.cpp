/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE WeldRecipeParamMap definition.
 
***************************************************************************/


#include "WeldRecipeStructuresAce.h"

const std::string TABLE_WELD_RECIPE_INFORMATION = "WeldRecipeInformation";
const std::string TABLE_WELD_RECIPE = "WeldRecipe";
const std::string TABLE_CUTOFF_LIMIT = "CutoffLimit";
const std::string TABLE_REJECT_LIMIT = "RejectLimit";
const std::string TABLE_SUSPECT_LIMIT = "SuspectLimit";
const std::string TABLE_STACK_RECIPE = "StackRecipe"; 

#define FLOAT_MIN "-10000000000.00"
#define FLOAT_MAX "10000000000.00"

/*Initialization of Weld Recipe parameters*/
const std::map <int, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > WeldRecipeParamMap =
{
		//TO_BE_DONE - add proper min, max and default values.
		//Parameter Identifier, 				Data Type, 20_Min, 20_Max, 20_Def, 30_Min, 30_Max, 30_Def,40_Min, 40_Max, 40_Def, Table Name, Column Name
		//Data from WeldRecipeInformation Table
        { WeldRecipe::WELD_RECIPE_NUMBER_PARAM, {INT_PARAM, "1","2147483647","-1","1","2147483647","-1","1","2147483647","-1",TABLE_WELD_RECIPE_INFORMATION, "WeldRecipeNumber", "Weld Recipe Number" } },
        { WeldRecipe::WELD_RECIPE_VERSION_NUM_PARAM, {INT_PARAM, "0","2147483647","0","0","2147483647","0","0","2147483647","0",TABLE_WELD_RECIPE_INFORMATION, "WeldRecipeVersionNumber" , "Weld Recipe Version Number" } },
        { STACK_RECIPE_NUM_PARAM, 				{INT_PARAM, "1","2147483647","1","1","2147483647","1","1","2147483647","1", TABLE_WELD_RECIPE_INFORMATION, "StackRecipeNumber", "Stack Recipe Number" } },
        { WeldRecipe::WELD_RECIPE_NAME_PARAM, 	{CHAR_ARRAY_PARAM, "1","50","N/A","1","50","N/A","1","50","N/A",TABLE_WELD_RECIPE_INFORMATION, "WeldRecipeName", "Weld Recipe Name" } },
        { WeldRecipe::WELD_MODE_PARAM, 			{INT_PARAM, "0","7","0","0","7","0","0","7","0",TABLE_WELD_RECIPE_INFORMATION, "WeldMode", "Weld Mode" } },
        { MODE_VALUE_TIME_PARAM, 				{FLOAT_PARAM, "0.01", "10.0","0.01", "0.01", "10.0","0.01", "0.01", "10.0","0.01", TABLE_WELD_RECIPE_INFORMATION, "ModeValueTime", "Time" } }, //Unit is seconds
        { MODE_VALUE_ENERGY_PARAM, 				{FLOAT_PARAM, "1.0", "120000.0", "1.0", "1.0", "45000.0", "1.0", "1.0", "24000.0", "1.0", TABLE_WELD_RECIPE_INFORMATION, "ModeValueEnergy", "Energy" } }, //Unit is Joule
        { MODE_VALUE_PEAK_POWER_PARAM,			{FLOAT_PARAM, "1.0", "4000.0", "400.0", "1.0", "1500.0", "150.0", "1.0", "800.0", "80.0", TABLE_WELD_RECIPE_INFORMATION, "ModeValuePeakPower", "Peak Power" } }, //Unit is Watt
        { MODE_VALUE_GROUND_DETECT_PARAM, 		{FLOAT_PARAM, "0.001", "0.5", "0.001", "0.001", "0.5", "0.001", "0.001", "0.5", "0.001", TABLE_WELD_RECIPE_INFORMATION, "ModeValueGroundDetect", "Ground Detect" } }, //Unit is seconds
        { MODE_VALUE_ABSOLUTE_DISTANCE_PARAM, 	{FLOAT_PARAM, "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", TABLE_WELD_RECIPE_INFORMATION, "ModeValueAbsoluteDistance", "Absolute Distance" } }, //Unit is mm
        { MODE_VALUE_COLLAPSE_DISTANCE_PARAM, 	{FLOAT_PARAM,"0.0", "125.0", "0.0", "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", TABLE_WELD_RECIPE_INFORMATION, "ModeValueCollapseDistance", "Collapse Distance" } }, //Unit is mm
        { IS_SAVED_PARAM, 						{BOOL_PARAM, "0","1","1","0","1","1","0","1","1",TABLE_WELD_RECIPE_INFORMATION, "IsSaved", "Saved" } },
        { WeldRecipe::CYCLE_COUNT_PARAM, 		{INT_PARAM, "0","2147483647","0","0","2147483647","0","0","2147483647","0",TABLE_WELD_RECIPE_INFORMATION, "CycleCount", "Cycle Count" } },
        { WeldRecipe::CYCLES_OK_COUNT_PARAM, 	{INT_PARAM, "0","2147483647","0","0","2147483647","0","0","2147483647","0",TABLE_WELD_RECIPE_INFORMATION, "CyclesOK", "Cycles OK" } },
        { WeldRecipe::REJECT_COUNT_PARAM,		{INT_PARAM, "0","2147483647","0","0","2147483647","0","0","2147483647","0",TABLE_WELD_RECIPE_INFORMATION, "Reject", "Reject" } },
        { WeldRecipe::SUSPECT_COUNT_PARAM,		{INT_PARAM, "0","2147483647","0","0","2147483647","0","0","2147483647","0",TABLE_WELD_RECIPE_INFORMATION, "Suspect", "Suspect" } },
        { BATCH_SETUP_ENABLE_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE_INFORMATION, "BatchSetupEnable", "Batch Setup Enable" } },
        { BATCH_ALARM_ENABLE_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE_INFORMATION, "BatchAlarmEnable", "Batch Alarm Enable" } },
        { BATCH_COUNTER_PARAM, 					{UNSIGNED_INT_PARAM, "0","4294967295","0","0","4294967295","0","0","4294967295","0", TABLE_WELD_RECIPE_INFORMATION, "BatchCounter", "Batch Counter" } },
        { BATCH_COUNT_LIMIT_PARAM, 				{UNSIGNED_INT_PARAM, "1","1000000","1","1","1000000","1","1","1000000","1", TABLE_WELD_RECIPE_INFORMATION, "BatchCountLimit", "Batch Count Limit" } },
        { BATCH_ID_PARAM, 						{CHAR_ARRAY_PARAM, "1","50","N/A","1","50","N/A","1","50","N/A", TABLE_WELD_RECIPE_INFORMATION, "BatchID", "Batch ID" } },
        { ACTUATOR_TYPE_PARAM, 				    {INT_PARAM, "1","2147483647","1","1","2147483647","1","1","2147483647","1", TABLE_WELD_RECIPE_INFORMATION, "ActuatorType", "Actuator Type" } },
		
		
		//Data from WeldRecipe Table
        { WELD_PRESSURE_PARAM, 					{FLOAT_PARAM, "0.0", "690.0", "138.0", "0.0", "690.0", "138.0", "0.0", "690.0", "138.0", TABLE_WELD_RECIPE, "WeldPressure", "Weld Pressure" } }, //Unit is kPA
        { HOLD_PRESSURE_PARAM, 					{FLOAT_PARAM, "0.0", "690.0", "138.0", "0.0", "690.0", "138.0", "0.0", "690.0", "138.0", TABLE_WELD_RECIPE, "HoldPressure", "Hold Pressure" } }, //Unit is kPA
        { FLOW_RATE_PARAM, 						{FLOAT_PARAM, "0.0", "100.0", "0.0", "0.0", "100.0", "0.0", "0.0", "100.0", "0.0", TABLE_WELD_RECIPE, "FlowRate", "Flow Rate" } },
        { HOLD_TIME_PARAM, 						{FLOAT_PARAM, "0.0", "10.0","0.01", "0.0", "10.0","0.01", "0.0", "10.0","0.01", TABLE_WELD_RECIPE, "HoldTime", "Hold Time" } }, //Unit is seconds
        { MAX_WELD_TIMEOUT_PARAM, 				{FLOAT_PARAM, "0.05","10.0","6", "0.05","10.0","6", "0.05","10.0","6", TABLE_WELD_RECIPE, "MaxWeldTimeout", "Max Weld Timeout" } },  //Unit is seconds
        { WELD_AMPLITUDE_PARAM, 				{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "WeldAmplitude", "Weld Amplitude" } }, //Unit is %
		
        { NUM_AMPLITUDE_STEPS_PARAM, 			{UNSIGNED_INT_PARAM, "0","10","0","0","10","0","0","10","0",TABLE_WELD_RECIPE, "NumAmplitudeSteps", "Num Amplitude Steps" } },
        { AMPLITUDE_STEPAT_PARAM, 				{INT_PARAM, "0","5","0","0","5","0","0","5","0",TABLE_WELD_RECIPE, "AmplitudeStepAt", "Amplitude Step At"  } },
        { AMPLITUDE_STEPAT_VALUE_1_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue1", "Amplitude Step At Value 1" } }, //Unit is Seconds or Joule or Watt depending on "AmplitudeStepAt" selection
        { AMPLITUDE_STEP_TARGET_1_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget1", "Amplitude Step Target 1" } }, //Unit is %
        { AMPLITUDE_STEP_RAMP_1_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp1", "Amplitude Step Ramp 1" } }, //Unit is seconds
        { AMPLITUDE_STEPAT_VALUE_2_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue2", "Amplitude Step At Value 2" } },
        { AMPLITUDE_STEP_TARGET_2_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget2", "Amplitude Step Target 2" } },
        { AMPLITUDE_STEP_RAMP_2_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp2", "Amplitude Step Ramp 2" } },
        { AMPLITUDE_STEPAT_VALUE_3_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue3", "Amplitude Step At Value 3" } },
        { AMPLITUDE_STEP_TARGET_3_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget3", "Amplitude Step Target 3" } },
        { AMPLITUDE_STEP_RAMP_3_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp3",  "Amplitude Step Ramp 3" } },
        { AMPLITUDE_STEPAT_VALUE_4_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue4", "Amplitude Step At Value 4" } },
        { AMPLITUDE_STEP_TARGET_4_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget4", "Amplitude Step Target 4" } },
        { AMPLITUDE_STEP_RAMP_4_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp4", "Amplitude Step Ramp 4" } },
        { AMPLITUDE_STEPAT_VALUE_5_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue5", "Amplitude Step At Value 5" } },
        { AMPLITUDE_STEP_TARGET_5_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget5", "Amplitude Step Target 5" } },
        { AMPLITUDE_STEP_RAMP_5_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp5", "Amplitude Step Ramp 5" } },
        { AMPLITUDE_STEPAT_VALUE_6_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue6", "Amplitude Step At Value 6" } },
        { AMPLITUDE_STEP_TARGET_6_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget6", "Amplitude Step Target 6" } },
        { AMPLITUDE_STEP_RAMP_6_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp6", "Amplitude Step Ramp 6" } },
        { AMPLITUDE_STEPAT_VALUE_7_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue7", "Amplitude Step At Value 7" } },
        { AMPLITUDE_STEP_TARGET_7_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget7", "Amplitude Step Target 7" } },
        { AMPLITUDE_STEP_RAMP_7_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp7", "Amplitude Step Ramp 7"} },
        { AMPLITUDE_STEPAT_VALUE_8_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue8", "Amplitude Step At Value 8" } },
        { AMPLITUDE_STEP_TARGET_8_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget8", "Amplitude Step Target 8" } },
        { AMPLITUDE_STEP_RAMP_8_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp8", "Amplitude Step Ramp 8" } },
        { AMPLITUDE_STEPAT_VALUE_9_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue9","Amplitude Step At Value 9" } },
        { AMPLITUDE_STEP_TARGET_9_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget9", "Amplitude Step Target 9" } },
        { AMPLITUDE_STEP_RAMP_9_PARAM, 			{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp9", "Amplitude Step Ramp 9"  } },
        { AMPLITUDE_STEPAT_VALUE_10_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "AmplitudeStepAtValue10",  "Amplitude Step At Value 10" } },
        { AMPLITUDE_STEP_TARGET_10_PARAM,	 	{UNSIGNED_INT_PARAM, "10","100","10","10","100","10","10","100","10",TABLE_WELD_RECIPE, "AmplitudeStepTarget10", "Amplitude Step Target 10" } },
        { AMPLITUDE_STEP_RAMP_10_PARAM, 		{FLOAT_PARAM, "0.08","1.0","0.08","0.08","1.0","0.08","0.08","1.0","0.08",TABLE_WELD_RECIPE, "AmplitudeStepRamp10", "Amplitude Step Ramp 10" } },

        { NUM_PRESSURE_STEPS_PARAM, 			{UNSIGNED_INT_PARAM, "0","10","0","0","10","0","0","10","0",TABLE_WELD_RECIPE, "NumPressureSteps", "Num Pressure Steps" } },
        { PRESSURE_STEPAT_PARAM, 				{INT_PARAM, "0","5","0","0","5","0","0","5","0",TABLE_WELD_RECIPE, "PressureStepAt",  "Pressure Step At" } },
        { PRESSURE_STEPAT_VALUE_1_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue1", "Pressure Step At Value 1" } }, //Unit is Seconds or Joule or Watt depending on "PressureStepAt" selection
        { PRESSURE_STEP_TARGET_1_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget1", "Pressure Step Target 1" } }, //Unit is kPA
        { PRESSURE_STEP_RAMP_1_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp1", "Pressure Step Ramp 1" } }, //Unit is seconds
        { PRESSURE_STEPAT_VALUE_2_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue2", "Pressure Step At Value 2" } },
        { PRESSURE_STEP_TARGET_2_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget2", "Pressure Step Target 2" } },
        { PRESSURE_STEP_RAMP_2_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp2", "Pressure Step Ramp 2" } },
        { PRESSURE_STEPAT_VALUE_3_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue3", "Pressure Step At Value 3" } },
        { PRESSURE_STEP_TARGET_3_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget3",  "Pressure Step Target 3" } },
        { PRESSURE_STEP_RAMP_3_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp3", "Pressure Step Ramp 3" } },
        { PRESSURE_STEPAT_VALUE_4_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue4", "Pressure Step At Value 4" } },
        { PRESSURE_STEP_TARGET_4_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget4", "Pressure Step Target 4" } },
        { PRESSURE_STEP_RAMP_4_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp4", "Pressure Step Ramp 4" } },
        { PRESSURE_STEPAT_VALUE_5_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue5", "Pressure Step At Value 5" } },
        { PRESSURE_STEP_TARGET_5_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget5", "Pressure Step Target 5" } },
        { PRESSURE_STEP_RAMP_5_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp5", "Pressure Step Ramp 5" } },
        { PRESSURE_STEPAT_VALUE_6_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue6", "Pressure Step At Value 6" } },
        { PRESSURE_STEP_TARGET_6_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget6", "Pressure Step Target 6" } },
        { PRESSURE_STEP_RAMP_6_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp6", "Pressure Step Ramp 6" } },
        { PRESSURE_STEPAT_VALUE_7_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue7", "Pressure Step At Value 7" } },
        { PRESSURE_STEP_TARGET_7_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget7", "Pressure Step Target 7" } },
        { PRESSURE_STEP_RAMP_7_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp7", "Pressure Step Ramp 7" } },
        { PRESSURE_STEPAT_VALUE_8_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue8", "Pressure Step At Value 8" } },
        { PRESSURE_STEP_TARGET_8_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget8", "Pressure Step Target 8" } },
        { PRESSURE_STEP_RAMP_8_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp8", "Pressure Step Ramp 8" } },
        { PRESSURE_STEPAT_VALUE_9_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue9", "Pressure Step At Value 9" } },
        { PRESSURE_STEP_TARGET_9_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget9", "Pressure Step Target 9" } },
        { PRESSURE_STEP_RAMP_9_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp9","Pressure Step Ramp 9" } },
        { PRESSURE_STEPAT_VALUE_10_PARAM, 		{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PressureStepAtValue10", "Pressure Step At Value 10" } },
        { PRESSURE_STEP_TARGET_10_PARAM, 		{FLOAT_PARAM, "0","690.0","0","0","690.0","0","0","690.0","0", TABLE_WELD_RECIPE, "PressureStepTarget10", "Pressure Step Target 10" } },
        { PRESSURE_STEP_RAMP_10_PARAM, 			{FLOAT_PARAM, "0.0","1.0","0.0","0.0","1.0","0.0","0.0","1.0","0.0", TABLE_WELD_RECIPE, "PressureStepRamp10", "Pressure Step Ramp 10" } },
		
        { IS_COOLING_VALVE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",TABLE_WELD_RECIPE, "IsCoolingValveEnabled", "Cooling Valve Enabled" } },
		
        { TRIGGER_TYPE_PARAM, 					{INT_PARAM, "0","2","0","0","2","0","0","2","0",TABLE_WELD_RECIPE, "TriggerType", "Trigger Type" } },
        { TRIGGER_FORCE_PARAM, 					{FLOAT_PARAM, FLOAT_MIN,FLOAT_MAX,"50.0",FLOAT_MIN,FLOAT_MAX,"50.0",FLOAT_MIN,FLOAT_MAX,"50.0",TABLE_WELD_RECIPE, "TriggerForce", "Trigger Force"} },
        { TRIGGER_DISTANCE_PARAM, 				{FLOAT_PARAM, "0.0", "125.0","0.0","0.0", "125.0","0.0","0.0", "125.0","0.0",TABLE_WELD_RECIPE, "TriggerDistance", "Trigger Distance" } },
        { PRE_TRIGGER_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE,	"PreTriggerEnabled", "PreTrigger Enabled" } },
        { PRE_TRIGGER_TYPE_PARAM, 				{INT_PARAM, "0","2","0","0","2","0","0","2","0", TABLE_WELD_RECIPE, "PreTriggerType", "PreTrigger Type" } },
        { PRE_TRIGGER_AMPLITUDE_PARAM,			{INT_PARAM,	"10","100","10","10","100","10","10","100","10", TABLE_WELD_RECIPE, "PreTriggerAmplitude", "PreTrigger Amplitude"} }, //Unit is %
        { PRE_TRIGGER_TIME_PARAM,				{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_WELD_RECIPE, "PreTriggerTime", "PreTrigger Time"} }, //Unit is seconds
        { PRE_TRIGGER_DISTANCE_PARAM,			{FLOAT_PARAM, "3.175","125.0","3.175","3.175","125.0","3.175","3.175","125.0","3.175", TABLE_WELD_RECIPE, "PreTriggerDistance", "PreTrigger Distance"} }, //Unit is mm

        { AFTER_BURST_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "AfterBurstEnabled", "AfterBurst Enabled" } },
        { AFTER_BURST_AMPLITUDE_PARAM, 			{INT_PARAM,	"10","100","10","10","100","10","10","100","10", TABLE_WELD_RECIPE, "AfterBurstAmplitude", "AfterBurst Amplitude" } }, //Unit is %
        { AFTER_BURST_DELAY_PARAM, 				{FLOAT_PARAM, "0.05","2.0","0.1", "0.05","2.0","0.1", "0.05","2.0","0.1", TABLE_WELD_RECIPE, "AfterBurstDelay", "AfterBurst Delay" } }, //Unit is seconds
        { AFTER_BURST_TIME_PARAM,		 		{FLOAT_PARAM, "0.1","2.0","0.1", "0.1","2.0","0.1", "0.1","2.0","0.1", TABLE_WELD_RECIPE, "AfterBurstTime", "AfterBurst Time" } }, //Unit is seconds
     
        { ENERGY_BRAKE_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "EnergyBrakeEnabled", "EnergyBrake Enabled"} },
        { ENERGY_BRAKE_AMPLITUDE_PARAM,			{INT_PARAM,	"1","100","3","1","100","3","1","100","3", TABLE_WELD_RECIPE,	"EnergyBrakeAmplitude", "EnergyBrake Amplitude" } }, //Unit is %
        { ENERGY_BRAKE_TIME_PARAM, 				{FLOAT_PARAM, "0.01","1.0","0.02", "0.01","1.0","0.02", "0.01","1.0","0.02", TABLE_WELD_RECIPE, "EnergyBrakeTime", "EnergyBrake Time" } }, //Unit is seconds
       
	    { ENERGY_COMPENSATION_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "EnergyCompensationEnabled", "Energy Compensation Enabled"} },
		{ ENERGY_COMPENSATION_MIN_VALUE_PARAM,	{FLOAT_PARAM, "1.0", "120000.0", "1.0", "1.0", "45000.0", "1.0", "1.0", "24000.0", "1.0", TABLE_WELD_RECIPE,	"EnergyCompensationMinValue", "Energy Compensation Min Value" } }, //Unit is J
		{ ENERGY_COMPENSATION_MAX_VALUE_PARAM, 	{FLOAT_PARAM, "1.0", "120000.0", "120000.0", "1.0", "45000.0", "45000.0", "1.0", "24000.0", "24000.0", TABLE_WELD_RECIPE, "EnergyCompensationMaxValue", "Energy Compensation Max Value" } }, //Unit is J
	   
        { TIMED_SEEK_PERIOD_PARAM, 				{FLOAT_PARAM, "1.0","59.0","1.0", "1.0","59.0","1.0", "1.0","59.0","1.0", TABLE_WELD_RECIPE, "TimedSeekPeriod", "Timed Seek Period" } }, //Unit is seconds
        { IS_TIMED_SEEKENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "IsTimedSeekEnabled", "Is Timed Seek Enabled" } },
        { IS_PREWELD_SEEK_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "IsPreWeldSeekEnabled", "Is PreWeldSeek Enabled" } },
        { IS_POSTWELD_SEEK_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "IsPostWeldSeekEnabled", "Is PostWeld Seek Enabled" } },
        { SCRUB_AMPLITUDE_PARAM, 				{UNSIGNED_INT_PARAM, "10","100","100","10","100","100","10","100","100", TABLE_WELD_RECIPE, "ScrubAmplitude", "Scrub Amplitude" } }, //Unit is %
		
        { RAPID_TRAVERSE_PARAM, 				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "RapidTraverse", "Rapid Traverse" } },
        { RAPID_TRAVERSE_DISTANCE_PARAM, 		{FLOAT_PARAM,  "0", "125", "0.0",   "0", "125", "0.0",  "0", "125", "0.0",  TABLE_WELD_RECIPE, "RapidTraverseDistance", "Rapid Traverse Distance" } }, //Unit is mm.
        { TRIGGER_LOST_PARAM, 				    {BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "TriggerLost", "Trigger Lost" } },
        { ENABLE_ACTUATOR_CLEAR_PARAM, 		    {BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE, "EnableActuatorClear", "Enable Actuator Clear" } },
        { ACTUATOR_CLEAR_TYPE_PARAM,			{INT_PARAM,	"0","1","0","0","1","0","0","1","0", TABLE_WELD_RECIPE,	"ActuatorClearType", "Actuator Clear Type" } },
        { ACTUATOR_CLEAR_TIME, 					{FLOAT_PARAM,  FLOAT_MIN, FLOAT_MAX, "0.0",  FLOAT_MIN, FLOAT_MAX, "0.0",  FLOAT_MIN, FLOAT_MAX, "0.0",  TABLE_WELD_RECIPE, "ActuatorClearTime", "Actuator Clear Time" } },
        { ACTUATOR_CLEAR_DISTANCE_PARAM, 		{FLOAT_PARAM,  FLOAT_MIN, FLOAT_MAX, "0.0",  FLOAT_MIN, FLOAT_MAX, "0.0",  FLOAT_MIN, FLOAT_MAX, "0.0",  TABLE_WELD_RECIPE, "ActuatorClearDistance", "Actuator Clear Distance" } },

		
		//Data from CutoffLimit Table
        { CUTOFF_LIMITS_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "CutOffLimitsEnabled", "CutOff Limits Enabled"} },
        { PEAKPOWER_CUTOFF_ENABLE_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "PeakPowerCutoffEnable", "PeakPower Cutoff Enable"} },
        { PEAKPOWER_CUTOFF_VALUE_PARAM,			{FLOAT_PARAM, "1.0","4000.0","400.0", "1.0","1500.0","150.0", "1.0","800.0","80.0", TABLE_CUTOFF_LIMIT, "PeakPowerCutoffValue", "PeakPower Cutoff Value"} }, //Unit is Watt
        { TIME_CUTOFF_ENABLE_PARAM,				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "TimeCutoffEnable", "Time Cutoff Enable"} },
        { TIME_CUTOFF_VALUE_PARAM,				{FLOAT_PARAM, "0.01","10.0","10.0", "0.01","10.0","10.0", "0.01","10.0","10.0", TABLE_CUTOFF_LIMIT, "TimeCutoffValue", "Time Cutoff Value"} }, //Unit is seconds
        { FREQUENCY_LOW_CUTOFF_ENABLE_PARAM, 	{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_CUTOFF_LIMIT,	"FrequencyLowCutoffEnable", "Frequency Low Cutoff Enable"} },
        { FREQUENCY_LOW_CUTOFF_VALUE_PARAM,		{FLOAT_PARAM, "19450.0","19950.0","19450.0","29250.0","30000.0","29250.0","38990.0","39990.0","38990.0", TABLE_CUTOFF_LIMIT, "FrequencyLowCutoffValue", "Frequency Low Cutoff Value"} }, //Unit is HZ
        { FREQUENCY_HIGH_CUTOFF_ENABLE_PARAM, 	{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "FrequencyHighCutoffEnable", "Frequency High Cutoff Enable"} },
        { FREQUENCY_HIGH_CUTOFF_VALUE_PARAM, 	{FLOAT_PARAM, "19950.0","20450.0","20450.0","30000.0","30750.0","30750.0", "39990.0","40990.0","40990.0", TABLE_CUTOFF_LIMIT, "FrequencyHighCutoffValue", "Frequency High Cutoff Value"} }, //Unit is HZ
        { ENERGY_CUTOFF_ENABLE_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "EnergyCutoffEnable", "Energy Cutoff Enable"} },
        { ENERGY_CUTOFF_VALUE_PARAM, 			{FLOAT_PARAM, "1.0","120000.0","120000.0", "1.0","45000.0", "45000.0",  "1.0","24000.0", "24000.0",TABLE_CUTOFF_LIMIT, "EnergyCutoffValue", "Energy Cutoff Value"} }, //Unit is Joule
        { GROUND_DETECT_CUTOFF_ENABLE_PARAM, 	{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "GroundDetectCutoffEnable", "Ground Detect Cutoff Enable"} },
        { GROUND_DETECT_CUTOFF_VALUE_PARAM, 	{FLOAT_PARAM, "0.001","0.5","0.001", "0.001","0.5","0.001", "0.001","0.5","0.001", TABLE_CUTOFF_LIMIT, "GroundDetectCutoffValue", "Ground Detect Cutoff Value"} }, //Unit is seconds
        { ABS_DISTANCE_CUTOFF_ENABLE_PARAM, 	{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "AbsoluteDistanceCutoffEnable", "Absolute Distance Cutoff Enable"} },
        { ABS_DISTANCE_CUTOFF_VALUE_PARAM, 	    {FLOAT_PARAM, "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", TABLE_CUTOFF_LIMIT, "AbsoluteDistanceCutoffValue",  "Absolute Distance Cutoff Value"} }, //Unit is mm
        { COLLAPSE_DISTANCE_CUTOFF_ENABLE_PARAM, {BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_CUTOFF_LIMIT, "CollapseDistanceCutoffEnable",  "Collapse Distance Cutoff Enable"} },
        { COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM,  {FLOAT_PARAM, "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", "0.0", "125.0", "0.0", TABLE_CUTOFF_LIMIT, "CollapseDistanceCutoffValue", "Collapse Distance Cutoff Value"} }, //Unit is mm
						
		//Data from RejectLimit Table
        { REJECT_LIMITS_ENABLED_PARAM, 			{BOOL_PARAM, "0", "1", "0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "RejectLimitsEnabled", "Reject Limits Enabled"} },

        { REJECT_TIME_ENABLED_PARAM, 					{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_REJECT_LIMIT,	"TimeEnabled", "Time Enabled"} },
        { REJECT_TIME_LOW_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1",	TABLE_REJECT_LIMIT,	"TimeLowEnabled", "Time Low Enabled"} },
        { REJECT_TIME_HIGH_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "TimeHighEnabled", "Time High Enabled"} },
        { REJECT_TIME_LOW_LIMIT_PARAM,					{FLOAT_PARAM, "0.01","10.0","0.01", "0.01","10.0","0.01", "0.01","10.0","0.01", TABLE_REJECT_LIMIT,	"TimeLowLimit", "Time Low Limit"} }, //Unit is seconds
        { REJECT_TIME_HIGH_LIMIT_PARAM, 				{FLOAT_PARAM, "0.01","10.0","10.0", "0.01","10.0","10.0", "0.01","10.0","10.0", TABLE_REJECT_LIMIT, "TimeHighLimit", "Time High Limit"} }, //Unit is seconds
		
        { REJECT_ENERGY_ENABLED_PARAM,					{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_REJECT_LIMIT,	"EnergyEnabled", "Energy Enabled"} },
        { REJECT_ENERGY_LOW_ENABLED_PARAM,				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "EnergyLowEnabled", "Energy Low Enabled"} },
        { REJECT_ENERGY_HIGH_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1",	TABLE_REJECT_LIMIT,	"EnergyHighEnabled", "Energy High Enabled"} },
        { REJECT_ENERGY_LOW_LIMIT_PARAM, 				{FLOAT_PARAM, "1.0","120000.0", "1.0", "1.0","45000.0", "1.0", "1.0","24000.0", "1.0", TABLE_REJECT_LIMIT, "EnergyLowLimit", "Energy Low Limit"} }, //Unit is Joule
        { REJECT_ENERGY_HIGH_LIMIT_PARAM, 				{FLOAT_PARAM, "1.0","120000.0", "120000.0", "1.0","45000.0", "45000.0", "1.0","24000.0", "24000.0", TABLE_REJECT_LIMIT,	"EnergyHighLimit", "Energy High Limit"} }, //Unit is Joule
		
        { REJECT_PEAKPOWER_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "PeakPowerEnabled", "PeakPower Enabled"} },
        { REJECT_PEAKPOWER_LOW_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "PeakPowerLowEnabled", "PeakPower Low Enabled"} },
        { REJECT_PEAKPOWER_HIGH_ENABLED_PARAM,			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "PeakPowerHighEnabled", "PeakPower High Enabled"} },
        { REJECT_PEAKPOWER_LOW_LIMIT_PARAM, 			{FLOAT_PARAM, "1.0","4000.0","1.0", "1.0","1500.0","1.0", "1.0","800.0","1.0", TABLE_REJECT_LIMIT, "PeakPowerLowLimit", "PeakPower Low Limit"} }, //Unit is Watt
        { REJECT_PEAKPOWER_HIGH_LIMIT_PARAM, 			{FLOAT_PARAM, "1.0","4000.0","4000.0", "1.0","1500.0","1500.0", "1.0","800.0","800.0", TABLE_REJECT_LIMIT, "PeakPowerHighLimit", "PeakPower High Limit"} }, //Unit is Watt
		
        { REJECT_FREQUENCY_ENABLED_PARAM,				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "FrequencyEnabled", "Frequency Enabled"} },
        { REJECT_FREQUENCY_LOW_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "FrequencyLowEnabled", "Frequency Low Enabled"} },
        { REJECT_FREQUENCY_HIGH_ENABLED_PARAM,			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "FrequencyHighEnabled", "Frequency High Enabled"} },
        { REJECT_FREQUENCY_LOW_LIMIT_PARAM, 			{FLOAT_PARAM, "19450.0","19950.0","19450.0","29250.0","30000.0","29250.0","38990.0","39990.0","38990.0", TABLE_REJECT_LIMIT, "FrequencyLowLimit", "Frequency Low Limit"} }, //Unit is HZ
        { REJECT_FREQUENCY_HIGH_LIMIT_PARAM, 			{FLOAT_PARAM, "19950.0","20450.0","20450.0","30000.0","30750.0","30750.0", "39990.0","40990.0","40990.0", TABLE_REJECT_LIMIT, "FrequencyHighLimit", "Frequency High Limit"} }, //Unit is HZ
        	
        { REJECT_ABS_DISTANCE_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "AbsoluteDistanceEnabled", "Absolute Distance Enabled"} },
        { REJECT_ABS_DISTANCE_LOW_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "AbsoluteDistanceLowEnabled", "Absolute Distance Low Enabled"} },
        { REJECT_ABS_DISTANCE_HIGH_ENABLED_PARAM,		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "AbsoluteDistanceHighEnabled", "Absolute Distance High Enabled"} },
        { REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM, 			{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "AbsoluteDistanceLowLimit","Absolute Distance Low Limit"} }, //Unit is mm
        { REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "AbsoluteDistanceHighLimit", "Absolute Distance High Limit"} }, //Unit is mm
		
        { REJECT_COLLAPSE_DISTANCE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "CollapseDistanceEnabled", "Collapse Distance Enabled"} },
        { REJECT_COLLAPSE_DISTANCE_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "CollapseDistanceLowEnabled", "Collapse Distance Low Enabled"} },
        { REJECT_COLLAPSE_DISTANCE_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "CollapseDistanceHighEnabled", "Collapse Distance High Enabled"} },
        { REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "CollapseDistanceLowLimit", "Collapse Distance Low Limit"} }, //Unit is mm
        { REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "CollapseDistanceHighLimit", "Collapse Distance High Limit"} }, //Unit is mm
		
        { REJECT_TRIGGER_DISTANCE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "TriggerDistanceEnabled", "Trigger Distance Enabled"} },
        { REJECT_TRIGGER_DISTANCE_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "TriggerDistanceLowEnabled", "Trigger Distance Low Enabled"} },
        { REJECT_TRIGGER_DISTANCE_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "TriggerDistanceHighEnabled", "Trigger Distance High Enabled"} },
        { REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "TriggerDistanceLowLimit", "Trigger Distance Low Limit"} }, //Unit is mm
        { REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "TriggerDistanceHighLimit", "Trigger Distance High Limit"} }, //Unit is mm
		
        { REJECT_END_WELD_FORCE_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "EndWeldForceEnabled", "End Weld Force Enabled"} },
        { REJECT_END_WELD_FORCE_LOW_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "EndWeldForceLowEnabled", "End Weld Force Low Enabled"} },
        { REJECT_END_WELD_FORCE_HIGH_ENABLED_PARAM,		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "EndWeldForceHighEnabled", "End Weld Force High Enabled"} },
        { REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "EndWeldForceLowLimit", "End Weld Force Low Limit"} },
        { REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_REJECT_LIMIT, "EndWeldForceHighLimit", "End Weld Force High Limit"} },
		
        { REJECT_VELOCITY_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_REJECT_LIMIT, "VelocityEnabled", "Velocity Enabled"} },
        { REJECT_VELOCITY_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "VelocityLowEnabled", "Velocity Low Enabled"} },
        { REJECT_VELOCITY_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_REJECT_LIMIT, "VelocityHighEnabled", "Velocity High Enabled"} },
        { REJECT_VELOCITY_LOW_LIMIT_PARAM, 		{FLOAT_PARAM, "7.62", "177.8", "7.62", "7.62", "177.8", "7.62", "7.62", "177.8", "7.62", TABLE_REJECT_LIMIT, "VelocityLowLimit", "Velocity Low Limit"} }, //Unit is mm/s
        { REJECT_VELOCITY_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, "7.62", "177.8", "177.8", "7.62", "177.8", "177.8", "7.62", "177.8", "177.8", TABLE_REJECT_LIMIT, "VelocityHighLimit", "Velocity High Limit"} }, //Unit is mm/s
		
		//Data from SuspectLimit Table
        { SUSPECT_LIMITS_ENABLED_PARAM, 			    {BOOL_PARAM, "0", "1", "0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "SuspectLimitsEnabled", "Suspect Limits Enabled"} },

        { SUSPECT_TIME_ENABLED_PARAM, 					{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_SUSPECT_LIMIT, "TimeEnabled","Time Enabled"} },
        { SUSPECT_TIME_LOW_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1",	TABLE_SUSPECT_LIMIT, "TimeLowEnabled", "Time Low Enabled"} },
        { SUSPECT_TIME_HIGH_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "TimeHighEnabled", "Time High Enabled"} },
        { SUSPECT_TIME_LOW_LIMIT_PARAM,					{FLOAT_PARAM, "0.01","10.0","0.02", "0.01","10.0","0.02", "0.01","10.0","0.02", TABLE_SUSPECT_LIMIT,	"TimeLowLimit",	"Time Low Limit"} }, //Unit is seconds
        { SUSPECT_TIME_HIGH_LIMIT_PARAM, 				{FLOAT_PARAM, "0.01","10.0","9.0", "0.01","10.0","9.0", "0.01","10.0","9.0", TABLE_SUSPECT_LIMIT, "TimeHighLimit", "Time High Limit"} }, //Unit is seconds
		
        { SUSPECT_ENERGY_ENABLED_PARAM,					{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_SUSPECT_LIMIT, "EnergyEnabled","Energy Enabled"} },
        { SUSPECT_ENERGY_LOW_ENABLED_PARAM,				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "EnergyLowEnabled", "Energy Low Enabled"} },
        { SUSPECT_ENERGY_HIGH_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1",	TABLE_SUSPECT_LIMIT, "EnergyHighEnabled", "Energy High Enabled"} },
        { SUSPECT_ENERGY_LOW_LIMIT_PARAM, 				{FLOAT_PARAM, "1.0","120000.0", "2.0", "1.0","45000.0", "2.0", "1.0","24000.0", "2.0", TABLE_SUSPECT_LIMIT, "EnergyLowLimit", "Energy Low Limit"} }, //Unit is Joule
        { SUSPECT_ENERGY_HIGH_LIMIT_PARAM, 				{FLOAT_PARAM, "1.0","120000.0", "119999.0", "1.0","45000.0", "44999.0", "1.0","24000.0", "23999.0", TABLE_SUSPECT_LIMIT,	"EnergyHighLimit", "Energy High Limit"} }, //Unit is Joule
		
        { SUSPECT_PEAKPOWER_ENABLED_PARAM, 				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "PeakPowerEnabled", "PeakPower Enabled"} },
        { SUSPECT_PEAKPOWER_LOW_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "PeakPowerLowEnabled", "PeakPower Low Enabled"} },
        { SUSPECT_PEAKPOWER_HIGH_ENABLED_PARAM,			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "PeakPowerHighEnabled", "PeakPower High Enabled"} },
        { SUSPECT_PEAKPOWER_LOW_LIMIT_PARAM, 			{FLOAT_PARAM, "1.0","4000.0","2.0", "1.0","1500.0","2.0", "1.0","800.0","2.0", TABLE_SUSPECT_LIMIT, "PeakPowerLowLimit","PeakPower Low Limit"} }, //Unit is Watt
        { SUSPECT_PEAKPOWER_HIGH_LIMIT_PARAM, 			{FLOAT_PARAM, "1.0","4000.0","3999.0", "1.0","1500.0","1499.0", "1.0","800.0","799.0", TABLE_SUSPECT_LIMIT, "PeakPowerHighLimit", "PeakPower High Limit"} }, //Unit is Watt
		
        { SUSPECT_FREQUENCY_ENABLED_PARAM,				{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "FrequencyEnabled","Frequency Enabled"} },
        { SUSPECT_FREQUENCY_LOW_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "FrequencyLowEnabled","Frequency Low Enabled"} },
        { SUSPECT_FREQUENCY_HIGH_ENABLED_PARAM,			{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "FrequencyHighEnabled","Frequency High Enabled"} },
        { SUSPECT_FREQUENCY_LOW_LIMIT_PARAM, 			{FLOAT_PARAM, "19450.0","19950.0","19451.0","29250.0","30000.0","29251.0","38990.0","39990.0","38991.0", TABLE_SUSPECT_LIMIT, "FrequencyLowLimit","Frequency Low Limit"} }, //Unit is HZ
        { SUSPECT_FREQUENCY_HIGH_LIMIT_PARAM, 			{FLOAT_PARAM, "19950.0","20450.0","20449.0","30000.0","30750.0","30749.0", "39990.0","40990.0","40989.0", TABLE_SUSPECT_LIMIT, "FrequencyHighLimit", "Frequency High Limit"} }, //Unit is HZ
			
        { SUSPECT_ABS_DISTANCE_ENABLED_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "AbsoluteDistanceEnabled","Absolute Distance Enabled"} },
        { SUSPECT_ABS_DISTANCE_LOW_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "AbsoluteDistanceLowEnabled", "Absolute Distance Low Enabled"} },
        { SUSPECT_ABS_DISTANCE_HIGH_ENABLED_PARAM,		{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "AbsoluteDistanceHighEnabled","Absolute Distance High Enabled"} },
        { SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "AbsoluteDistanceLowLimit","Absolute Distance Low Limit"} }, //Unit is mm
        { SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "AbsoluteDistanceHighLimit","Absolute Distance High Limit"} }, //Unit is mm
		
        { SUSPECT_COLLAPSE_DISTANCE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "CollapseDistanceEnabled","Collapse Distance Enabled"} },
        { SUSPECT_COLLAPSE_DISTANCE_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "CollapseDistanceLowEnabled", "Collapse Distance Low Enabled"} },
        { SUSPECT_COLLAPSE_DISTANCE_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "CollapseDistanceHighEnabled", "Collapse Distance High Enabled"} },
        { SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "CollapseDistanceLowLimit", "Collapse Distance Low Limit"} }, //Unit is mm
        { SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "CollapseDistanceHighLimit", "Collapse Distance High Limit"} }, //Unit is mm
		
        { SUSPECT_TRIGGER_DISTANCE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "TriggerDistanceEnabled", "Trigger Distance Enabled"} },
        { SUSPECT_TRIGGER_DISTANCE_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "TriggerDistanceLowEnabled", "Trigger Distance Low Enabled"} },
        { SUSPECT_TRIGGER_DISTANCE_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "TriggerDistanceHighEnabled", "Trigger Distance High Enabled"} },
        { SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "TriggerDistanceLowLimit", "Trigger Distance Low Limit"} }, //Unit is mm
        { SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "TriggerDistanceHighLimit", "Trigger Distance High Limit"} }, //Unit is mm
		
        { SUSPECT_END_WELD_FORCE_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "EndWeldForceEnabled", "End Weld Force Enabled"} },
        { SUSPECT_END_WELD_FORCE_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "EndWeldForceLowEnabled", "End Weld Force Low Enabled"} },
        { SUSPECT_END_WELD_FORCE_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "EndWeldForceHighEnabled", "End Weld Force High Enabled"} },
        { SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "EndWeldForceLowLimit", "End Weld Force Low Limit"} },
        { SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM, 		{FLOAT_PARAM, FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", FLOAT_MIN, FLOAT_MAX, "0.0", TABLE_SUSPECT_LIMIT, "EndWeldForceHighLimit", "End Weld Force High Limit"} },
		
        { SUSPECT_VELOCITY_ENABLED_PARAM, 		{BOOL_PARAM, "0","1","0","0","1","0","0","1","0", TABLE_SUSPECT_LIMIT, "VelocityEnabled", "Velocity Enabled"} },
        { SUSPECT_VELOCITY_LOW_ENABLED_PARAM, 	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "VelocityLowEnabled", "Velocity Low Enabled" } },
        { SUSPECT_VELOCITY_HIGH_ENABLED_PARAM,	{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_SUSPECT_LIMIT, "VelocityHighEnabled", "Velocity High Enabled"} },
        { SUSPECT_VELOCITY_LOW_LIMIT_PARAM, 	{FLOAT_PARAM, "7.62", "177.8", "7.63", "7.62", "177.8", "7.63", "7.62", "177.8", "7.63", TABLE_SUSPECT_LIMIT, "VelocityLowLimit", "Velocity Low Limit"} }, //Unit is mm/s
        { SUSPECT_VELOCITY_HIGH_LIMIT_PARAM, 	{FLOAT_PARAM, "7.62", "177.8", "177.7", "7.62", "177.8", "177.7", "7.62", "177.8", "177.7", TABLE_SUSPECT_LIMIT, "VelocityHighLimit", "Velocity High Limit"} }, //Unit is mm/s
		
		//Data from StackRecipe Table
        { FREQUENCY_LOW_PARAM, 					{INT_PARAM, "-2147483648","2147483647","0","-2147483648","2147483647","0","-2147483648","2147483647","0",	TABLE_STACK_RECIPE,	"FrequencyLow", "Frequency Low"} }, //Unit is HZ
        { FREQUENCY_HIGH_PARAM,					{INT_PARAM,	"-2147483648","2147483647","0","-2147483648","2147483647","0","-2147483648","2147483647","0", TABLE_STACK_RECIPE, "FrequencyHigh", "Frequency High"} }, //Unit is HZ
       
        { PHASE_LIMIT_TIME_PARAM, 				{FLOAT_PARAM, "0",FLOAT_MAX,"0.001","0",FLOAT_MAX,"0.001","0",FLOAT_MAX,"0.001", TABLE_STACK_RECIPE,"PhaseLimitTime", "Phase Limit Time"} }, //Unit is seconds
        { PHASE_LIMIT_PARAM, 					{INT_PARAM,	"-2147483648","2147483647","4","-2147483648","2147483647","4", "-2147483648","2147483647","4",TABLE_STACK_RECIPE, "PhaseLimit", "Phase Limit"} },
      
        { CONTROL_MODE_PARAM, 					{INT_PARAM, "-2147483648","2147483647","1","-2147483648","2147483647","1","-2147483648","2147483647","1",	TABLE_STACK_RECIPE,	"ControlMode", 	"Control Mode"} },
        { BLIND_TIME_WELD_PARAM, 				{FLOAT_PARAM,"0",FLOAT_MAX,"0","0",FLOAT_MAX,"0","0",FLOAT_MAX,"0", TABLE_STACK_RECIPE, "BlindTimeWeld", "Blind Time Weld"} }, //Unit is seconds
      
        { AMP_PROPORTIONAL_GAIN_PARAM, 			{INT_PARAM, "-2147483648","2147483647","20","-2147483648","2147483647","20","-2147483648","2147483647","80",	TABLE_STACK_RECIPE,	"AmpProportionalGain", "AmpProportional Gain"} }, //no units
        { AMP_INTEGRAL_GAIN_PARAM, 				{INT_PARAM, "-2147483648","2147483647","0","-2147483648","2147483647","0","-2147483648","2147483647","0",	TABLE_STACK_RECIPE,	"AmpIntegralGain", "AmpIntegral Gain"} }, //no units
        { AMP_DERIVATIVE_GAIN_PARAM, 			{INT_PARAM, "-2147483648","2147483647","0","-2147483648","2147483647","0", "-2147483648","2147483647","0",TABLE_STACK_RECIPE,	"AmpDerivativeGain", "AmpDerivative Gain"} }, //no units
      
        { PHASE_PROPORTIONAL_GAIN_PARAM, 		{INT_PARAM, "-2147483648","2147483647","4000","-2147483648","2147483647","16000","-2147483648","2147483647","16000", TABLE_STACK_RECIPE,	"PhaseProportionalGain",	"Phase Proportional Gain"} }, //no units
        { PHASE_INTEGRAL_GAIN_PARAM,	 		{INT_PARAM, "-2147483648","2147483647","100","-2147483648","2147483647","400","-2147483648","2147483647","2000", TABLE_STACK_RECIPE,	"PhaseIntegralGain", "Phase Integral Gain"} }, //no units
        { PHASE_DERIVATIVE_GAIN_PARAM, 			{INT_PARAM, "-2147483648","2147483647","0","-2147483648","2147483647","-500","-2147483648","2147483647","-500",	TABLE_STACK_RECIPE,	"PhaseDerivativeGain", "Phase Derivative Gain"} }, //no units
      
        { WELD_RAMP_TIME_PARAM,					{FLOAT_PARAM,"0.08","1","0.08","0.08","1","0.08","0.08","1","0.08",TABLE_STACK_RECIPE, "WeldRampTime",  "Weld Ramp Time"} }, //Unit is seconds
        { START_FREQUENCY_PARAM,				{INT_PARAM,	"19450","20450","19950","29250","30750","30000", "38990","40990","39990",TABLE_STACK_RECIPE, "StartFrequency",  "Start Frequency"} }, //Unit is HZ
        { WeldRecipe::MEMORY_OFFSET_PARAM, 		{INT_PARAM,	"-2147483648","2147483647","0","-2147483648","2147483647","0","-2147483648","2147483647","0", TABLE_STACK_RECIPE, "MemoryOffset", "Memory Offset"} }, //Unit is HZ
        { WeldRecipe::DIGITAL_TUNE_PARAM, 		{INT_PARAM, "19450","20450","19950","29250","30750","30000", "38990","40990","39990", TABLE_STACK_RECIPE,	"DigitalTune", "Digital Tune"} }, //Unit is HZ
        { FREQUENCY_OFFSET_PARAM, 				{INT_PARAM, "-500","500","0","-750","750","0","-1000","1000","0", TABLE_STACK_RECIPE,	"FrequencyOffset", "Frequency Offset"} }, //Unit is HZ
        { END_OF_WELD_STORE_PARAM, 				{BOOL_PARAM, "0","1","1","0","1","1","0","1","1", TABLE_STACK_RECIPE, "EndOfWeldStore", "End Of WeldStore"} },
        { INTERNAL_OFFSET_FLAG_PARAM, 			{BOOL_PARAM, "0","1","0","0","1","0","0","1","0",	TABLE_STACK_RECIPE,	"InternalOffsetFlag", "Internal Offset Flag"} },
        { EXTERNAL_AMPLITUDE_SETTING, 		    {BOOL_PARAM, "0","1","0","0","1","0","0","1","0",TABLE_WELD_RECIPE, "ExternalAmplitudeSetting", "External Amplitude Setting" } },
};

const std::map <WELDMODES , std::string> WeldModeTypeName =
    {
        {TIMEMODE,"Time"},
        {ENERGYMODE,"Energy"},
        {PEAKPOWERMODE,"Peak Power"},
        {GRDDETECTMODE,"Ground Detect"},
        {ABSMODE,"Absolute Distance"},
        {COLLAPSEMODE,"Collapse Distance"},
        {CONTINUOUS,"Continiuous"},
        {MULTI,"Multi"},
        {MAX_MODES,"Maximum Modes"}
};

const std::map <std::string , std::string> EnableDisableTypeName =
    {
        {"0","Disable"},
        {"1", "Enable"}
};

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE  weld recipe related implementation
 
***************************************************************************/

#ifndef WELD_RECIPE_STRUCTURES_ACE_H_
#define WELD_RECIPE_STRUCTURES_ACE_H_

#include <cstdint>
#include <cstring>
#include <map>
#include <tuple>
#include "Common_Definitions.h"
#include "WeldRecipe.h"
#include "ActuatorInit.h"

extern const std::map < int, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string > > WeldRecipeParamMap;
extern const std::string TABLE_WELD_RECIPE_INFORMATION;
extern const std::string TABLE_WELD_RECIPE;
extern const std::string TABLE_CUTOFF_LIMIT;
extern const std::string TABLE_REJECT_LIMIT;
extern const std::string TABLE_SUSPECT_LIMIT;
extern const std::string TABLE_STACK_RECIPE;
extern const std::map < WELDMODES , std::string> WeldModeTypeName ;
extern const std::map <std::string , std::string> EnableDisableTypeName;

constexpr unsigned int MAX_NUMBER_OF_RECIPE_REVISIONS = 50;
constexpr int MAX_VALID_RECIPE_NUMBER = 100000000;//A sufficiently large valid recipe number that can be assigned to a weld recipe.
constexpr int MIN_VALID_RECIPE_NUMBER = 1; //A Minimum valid recipe number
constexpr unsigned int MAX_LENGTH_RECIPE_NAME = 51;
constexpr unsigned int BUFFER_TO_HOLD_CHANGED_WELD_RECIPE_DATA = MAX_LENGTH_RECIPE_NAME;
//Maximum number of recipe card structures sent in one chunk
constexpr int MAX_NUM_OF_RECIPE_CARDS_IN_ONE_CHUNK = 4;
constexpr int MAX_NUMBER_OF_AMPLITUDE_STEPS_SUPPORTED = 10;
constexpr int MAX_NUMBER_OF_PRESSURE_STEPS_SUPPORTED = 10;

typedef enum
{
	WELD_RECIPE_CARD_DATA = 1, //For handling weld recipe card data in chunks
	WELD_RECIPE_CHANGE_DATA, //For handling  weld recipe changed data
	WELD_RECIPE_CREATE, //For handling weld recipe create request
	WELD_RECIPE_DELETE, //For handling weld recipe delete request
	ACTIVE_WELD_RECIPE_DATA, //For handling active weld recipe data transfer
	WELD_RECIPE_PARAMETER_UPDATE, //For handling weld recipe parameter update requests,
	SET_WELD_RECIPE_AS_ACTIVE, //For setting the weld recipe as active weld recipe.
	WELD_RECIPE_COPY, //For Weld Recipe Copy Operation.
	WELD_RECIPE_RECALL, //For Weld Recipe Recall Operation.
	WELD_RECIPE_AMPLITUDE_STEP_DATA, //For Sending Weld Recipe Amplitude Stepping Data to ASC.
	WELD_RECIPE_PRESSURE_STEP_DATA, //For Sending Weld Recipe Pressure Stepping Data to ASC.
	SYNCH_WELD_RECIPE_DATA, // For Weld Recipe data synch whenever system's unit type is change.
	WELD_RECIPE_RESET_TO_DEFAULT, //For handling weld recipe reset to default request.
	WELD_RECIPE_OBJECT_SET_ALL // For handling Weld Recipe Set All EIP service
}WELD_RECIPE_ACE_SUB_ID;

typedef enum
{
	WELD_RECIPE_DELETE_RESPONSE_UNKNOWN = -1,
	WELD_RECIPE_DELETE_SUCCESS = 0,
	WELD_RECIPE_DELETE_FAILURE,
	WELD_RECIPE_TO_DELETE_DOES_NOT_EXIST,
	CAN_NOT_DELETE_ACTIVE_WELD_RECIPE,
}WELD_RECIPE_DELETE_RESPONSE;

typedef enum
{
	WELD_RECIPE_CREATE_RESPONSE_UNKNOWN = -1,
	WELD_RECIPE_CREATE_SUCCESS = 0,
	WELD_RECIPE_CREATE_FAILURE,
	MAX_RECIPES_LIMIT_REACHED,
	INVALID_RECIPE_NUMBER
}WELD_RECIPE_CREATE_RESPONSE;

typedef enum
{
	WELD_RECIPE_UPDATE_RESPONSE_UNKNOWN = -1,
	WELD_RECIPE_UPDATE_SUCCESS = 0,
	WELD_RECIPE_UPDATE_FAILURE,
	WELD_RECIPE_UPDATE_PARAMETER_NOT_FOUND,
	WELD_RECIPE_UPDATE_DATATYPE_NOT_SUPPORTED,
	WELD_RECIPE_UPDATE_VALUE_OUT_OF_RANGE,
	WELD_RECIPE_SET_AS_ACTIVE_FAILURE,
	WELD_RECIPE_COPY_FAILURE,
	WELD_RECIPE_REVISION_CREATION_FAILURE,
	WELD_RECIPE_NUMBER_DOES_NOT_EXIST,
	INVALID_WELD_RECIPE_NUMBER,
	INVALID_WELD_RECIPE_REVISION_NUMBER,
	WELD_RECIPE_DOES_NOT_EXIST,
	FAILURE_TO_READ_WELD_RECIPE_DATA,
	SOURCE_AND_DESTINATION_WELD_RECIPE_NUMBER_IS_SAME,
	CAN_NOT_DELETE_ACTIVE_WELD_RECIPE_REVISION,
	WELD_RECIPE_RECALL_FAILURE,
	AMPLITUDE_STEP_DATA_UPDATE_FAILURE,
	PRESSURE_STEP_DATA_UPDATE_FAILURE
}WELD_RECIPE_UPDATE_RESPONSE;

//Enum for recipe actions
typedef enum RECIPE_ACTION
{
	RECIPE_CREATE,
	RECIPE_DELETE,
	RECIPE_UPDATE
}RECIPE_ACTION;

//Enum for recipe unit type
typedef enum WELD_RECIPE_UNIT_TYPE
{
	BASE_UNIT   = 1,
	SYSTEM_UNIT,
}WELD_RECIPE_UNIT_TYPE;

typedef struct RecipeChange
{
	int32_t WeldRecipeNumber;//Recipe Number for which this change belongs.
	RECIPE_ACTION Action; //Identifies whether the action is recipe creation, deletion, or modification.
	int Result; //Identifies whether the operation was successful or failed, stored failure enum value in case of fail.
}__attribute__((packed))  RecipeChange;

enum WELD_RECIPE_ACE_PARAM_ID
{
	STACK_RECIPE_NUM_PARAM = WeldRecipe::WELD_RECIPE_MAX_PARAM,
	MODE_VALUE_TIME_PARAM,
	MODE_VALUE_ENERGY_PARAM,
	MODE_VALUE_PEAK_POWER_PARAM,
	MODE_VALUE_GROUND_DETECT_PARAM,
	MODE_VALUE_ABSOLUTE_DISTANCE_PARAM,
	MODE_VALUE_COLLAPSE_DISTANCE_PARAM,
	IS_SAVED_PARAM,
	BATCH_SETUP_ENABLE_PARAM,
	BATCH_ALARM_ENABLE_PARAM,
	BATCH_COUNTER_PARAM,
	BATCH_COUNT_LIMIT_PARAM,
	BATCH_ID_PARAM,
	ACTUATOR_TYPE_PARAM,
	
	WELD_PRESSURE_PARAM,
	HOLD_PRESSURE_PARAM,
	FLOW_RATE_PARAM,
	HOLD_TIME_PARAM,
	MAX_WELD_TIMEOUT_PARAM,
	WELD_AMPLITUDE_PARAM,
	NUM_AMPLITUDE_STEPS_PARAM,
	AMPLITUDE_STEPAT_PARAM,
	AMPLITUDE_STEPAT_VALUE_1_PARAM,
	AMPLITUDE_STEP_TARGET_1_PARAM,
	AMPLITUDE_STEP_RAMP_1_PARAM,
	AMPLITUDE_STEPAT_VALUE_2_PARAM,
	AMPLITUDE_STEP_TARGET_2_PARAM,
	AMPLITUDE_STEP_RAMP_2_PARAM,
	AMPLITUDE_STEPAT_VALUE_3_PARAM,
	AMPLITUDE_STEP_TARGET_3_PARAM,
	AMPLITUDE_STEP_RAMP_3_PARAM,
	AMPLITUDE_STEPAT_VALUE_4_PARAM,
	AMPLITUDE_STEP_TARGET_4_PARAM,
	AMPLITUDE_STEP_RAMP_4_PARAM,
	AMPLITUDE_STEPAT_VALUE_5_PARAM,
	AMPLITUDE_STEP_TARGET_5_PARAM,
	AMPLITUDE_STEP_RAMP_5_PARAM,
	AMPLITUDE_STEPAT_VALUE_6_PARAM,
	AMPLITUDE_STEP_TARGET_6_PARAM,
	AMPLITUDE_STEP_RAMP_6_PARAM,
	AMPLITUDE_STEPAT_VALUE_7_PARAM,
	AMPLITUDE_STEP_TARGET_7_PARAM,
	AMPLITUDE_STEP_RAMP_7_PARAM,
	AMPLITUDE_STEPAT_VALUE_8_PARAM,
	AMPLITUDE_STEP_TARGET_8_PARAM,
	AMPLITUDE_STEP_RAMP_8_PARAM,
	AMPLITUDE_STEPAT_VALUE_9_PARAM,
	AMPLITUDE_STEP_TARGET_9_PARAM,
	AMPLITUDE_STEP_RAMP_9_PARAM,
	AMPLITUDE_STEPAT_VALUE_10_PARAM,
	AMPLITUDE_STEP_TARGET_10_PARAM,
	AMPLITUDE_STEP_RAMP_10_PARAM,
	NUM_PRESSURE_STEPS_PARAM,
	PRESSURE_STEPAT_PARAM,
	PRESSURE_STEPAT_VALUE_1_PARAM,
	PRESSURE_STEP_TARGET_1_PARAM,
	PRESSURE_STEP_RAMP_1_PARAM,
	PRESSURE_STEPAT_VALUE_2_PARAM,
	PRESSURE_STEP_TARGET_2_PARAM,
	PRESSURE_STEP_RAMP_2_PARAM,
	PRESSURE_STEPAT_VALUE_3_PARAM,
	PRESSURE_STEP_TARGET_3_PARAM,
	PRESSURE_STEP_RAMP_3_PARAM,
	PRESSURE_STEPAT_VALUE_4_PARAM,
	PRESSURE_STEP_TARGET_4_PARAM,
	PRESSURE_STEP_RAMP_4_PARAM,
	PRESSURE_STEPAT_VALUE_5_PARAM,
	PRESSURE_STEP_TARGET_5_PARAM,
	PRESSURE_STEP_RAMP_5_PARAM,
	PRESSURE_STEPAT_VALUE_6_PARAM,
	PRESSURE_STEP_TARGET_6_PARAM,
	PRESSURE_STEP_RAMP_6_PARAM,
	PRESSURE_STEPAT_VALUE_7_PARAM,
	PRESSURE_STEP_TARGET_7_PARAM,
	PRESSURE_STEP_RAMP_7_PARAM,
	PRESSURE_STEPAT_VALUE_8_PARAM,
	PRESSURE_STEP_TARGET_8_PARAM,
	PRESSURE_STEP_RAMP_8_PARAM,
	PRESSURE_STEPAT_VALUE_9_PARAM,
	PRESSURE_STEP_TARGET_9_PARAM,
	PRESSURE_STEP_RAMP_9_PARAM,
	PRESSURE_STEPAT_VALUE_10_PARAM,
	PRESSURE_STEP_TARGET_10_PARAM,
	PRESSURE_STEP_RAMP_10_PARAM,
	IS_COOLING_VALVE_ENABLED_PARAM,
	TRIGGER_TYPE_PARAM,
	TRIGGER_FORCE_PARAM,
	TRIGGER_DISTANCE_PARAM,
	PRE_TRIGGER_ENABLED_PARAM,
	PRE_TRIGGER_TYPE_PARAM,
	PRE_TRIGGER_AMPLITUDE_PARAM,
	PRE_TRIGGER_TIME_PARAM,
	PRE_TRIGGER_DISTANCE_PARAM,
	AFTER_BURST_ENABLED_PARAM,
	AFTER_BURST_AMPLITUDE_PARAM,
	AFTER_BURST_DELAY_PARAM,
	AFTER_BURST_TIME_PARAM,
	ENERGY_BRAKE_ENABLED_PARAM,
	ENERGY_BRAKE_AMPLITUDE_PARAM,
	ENERGY_BRAKE_TIME_PARAM,
	ENERGY_COMPENSATION_ENABLED_PARAM, 
	ENERGY_COMPENSATION_MIN_VALUE_PARAM,
	ENERGY_COMPENSATION_MAX_VALUE_PARAM,
	TIMED_SEEK_PERIOD_PARAM,
	IS_TIMED_SEEKENABLED_PARAM,
	IS_PREWELD_SEEK_ENABLED_PARAM,
	IS_POSTWELD_SEEK_ENABLED_PARAM,
	SCRUB_AMPLITUDE_PARAM,
	RAPID_TRAVERSE_PARAM,
	RAPID_TRAVERSE_DISTANCE_PARAM,
	TRIGGER_LOST_PARAM,
	ENABLE_ACTUATOR_CLEAR_PARAM,
	ACTUATOR_CLEAR_TYPE_PARAM,
	ACTUATOR_CLEAR_TIME,
	ACTUATOR_CLEAR_DISTANCE_PARAM,
	
	CUTOFF_LIMITS_ENABLED_PARAM,
	PEAKPOWER_CUTOFF_ENABLE_PARAM,
	PEAKPOWER_CUTOFF_VALUE_PARAM,
	TIME_CUTOFF_ENABLE_PARAM,
	TIME_CUTOFF_VALUE_PARAM,
	FREQUENCY_LOW_CUTOFF_ENABLE_PARAM,
	FREQUENCY_LOW_CUTOFF_VALUE_PARAM,
	FREQUENCY_HIGH_CUTOFF_ENABLE_PARAM,
	FREQUENCY_HIGH_CUTOFF_VALUE_PARAM,
	ENERGY_CUTOFF_ENABLE_PARAM,
	ENERGY_CUTOFF_VALUE_PARAM,
	GROUND_DETECT_CUTOFF_ENABLE_PARAM,
	GROUND_DETECT_CUTOFF_VALUE_PARAM,
	ABS_DISTANCE_CUTOFF_ENABLE_PARAM,
	ABS_DISTANCE_CUTOFF_VALUE_PARAM, 
	COLLAPSE_DISTANCE_CUTOFF_ENABLE_PARAM,
	COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM, 

	REJECT_LIMITS_ENABLED_PARAM,
	REJECT_TIME_ENABLED_PARAM,
	REJECT_TIME_LOW_ENABLED_PARAM,
	REJECT_TIME_HIGH_ENABLED_PARAM,
	REJECT_TIME_LOW_LIMIT_PARAM,
	REJECT_TIME_HIGH_LIMIT_PARAM,
	REJECT_ENERGY_ENABLED_PARAM,
	REJECT_ENERGY_LOW_ENABLED_PARAM,
	REJECT_ENERGY_HIGH_ENABLED_PARAM,
	REJECT_ENERGY_LOW_LIMIT_PARAM,
	REJECT_ENERGY_HIGH_LIMIT_PARAM,
	REJECT_PEAKPOWER_ENABLED_PARAM,
	REJECT_PEAKPOWER_LOW_ENABLED_PARAM,
	REJECT_PEAKPOWER_HIGH_ENABLED_PARAM,
	REJECT_PEAKPOWER_LOW_LIMIT_PARAM,
	REJECT_PEAKPOWER_HIGH_LIMIT_PARAM,
	REJECT_FREQUENCY_ENABLED_PARAM,
	REJECT_FREQUENCY_LOW_ENABLED_PARAM,
	REJECT_FREQUENCY_HIGH_ENABLED_PARAM,
	REJECT_FREQUENCY_LOW_LIMIT_PARAM,
	REJECT_FREQUENCY_HIGH_LIMIT_PARAM,	
	REJECT_ABS_DISTANCE_ENABLED_PARAM,
	REJECT_ABS_DISTANCE_LOW_ENABLED_PARAM,
	REJECT_ABS_DISTANCE_HIGH_ENABLED_PARAM,
	REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM,
	REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM,
	REJECT_COLLAPSE_DISTANCE_ENABLED_PARAM,
	REJECT_COLLAPSE_DISTANCE_LOW_ENABLED_PARAM,
	REJECT_COLLAPSE_DISTANCE_HIGH_ENABLED_PARAM,
	REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM,
	REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM,
	REJECT_TRIGGER_DISTANCE_ENABLED_PARAM,
	REJECT_TRIGGER_DISTANCE_LOW_ENABLED_PARAM,
	REJECT_TRIGGER_DISTANCE_HIGH_ENABLED_PARAM,
	REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM,
	REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM,
	REJECT_END_WELD_FORCE_ENABLED_PARAM,
	REJECT_END_WELD_FORCE_LOW_ENABLED_PARAM,
	REJECT_END_WELD_FORCE_HIGH_ENABLED_PARAM,
	REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM,
	REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM,
	REJECT_VELOCITY_ENABLED_PARAM,
	REJECT_VELOCITY_LOW_ENABLED_PARAM,
	REJECT_VELOCITY_HIGH_ENABLED_PARAM,
	REJECT_VELOCITY_LOW_LIMIT_PARAM,
	REJECT_VELOCITY_HIGH_LIMIT_PARAM,
	
	SUSPECT_LIMITS_ENABLED_PARAM,
	SUSPECT_TIME_ENABLED_PARAM,
	SUSPECT_TIME_LOW_ENABLED_PARAM,
	SUSPECT_TIME_HIGH_ENABLED_PARAM,
	SUSPECT_TIME_LOW_LIMIT_PARAM,
	SUSPECT_TIME_HIGH_LIMIT_PARAM,
	SUSPECT_ENERGY_ENABLED_PARAM,
	SUSPECT_ENERGY_LOW_ENABLED_PARAM,
	SUSPECT_ENERGY_HIGH_ENABLED_PARAM,
	SUSPECT_ENERGY_LOW_LIMIT_PARAM,
	SUSPECT_ENERGY_HIGH_LIMIT_PARAM,
	SUSPECT_PEAKPOWER_ENABLED_PARAM,
	SUSPECT_PEAKPOWER_LOW_ENABLED_PARAM,
	SUSPECT_PEAKPOWER_HIGH_ENABLED_PARAM,
	SUSPECT_PEAKPOWER_LOW_LIMIT_PARAM,
	SUSPECT_PEAKPOWER_HIGH_LIMIT_PARAM,
	SUSPECT_FREQUENCY_ENABLED_PARAM,
	SUSPECT_FREQUENCY_LOW_ENABLED_PARAM,
	SUSPECT_FREQUENCY_HIGH_ENABLED_PARAM,
	SUSPECT_FREQUENCY_LOW_LIMIT_PARAM,
	SUSPECT_FREQUENCY_HIGH_LIMIT_PARAM,
	SUSPECT_ABS_DISTANCE_ENABLED_PARAM,
	SUSPECT_ABS_DISTANCE_LOW_ENABLED_PARAM,
	SUSPECT_ABS_DISTANCE_HIGH_ENABLED_PARAM,
	SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM,
	SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM,
	SUSPECT_COLLAPSE_DISTANCE_ENABLED_PARAM,
	SUSPECT_COLLAPSE_DISTANCE_LOW_ENABLED_PARAM,
	SUSPECT_COLLAPSE_DISTANCE_HIGH_ENABLED_PARAM,
	SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM,
	SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM,
	SUSPECT_TRIGGER_DISTANCE_ENABLED_PARAM,
	SUSPECT_TRIGGER_DISTANCE_LOW_ENABLED_PARAM,
	SUSPECT_TRIGGER_DISTANCE_HIGH_ENABLED_PARAM,
	SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM,
	SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM,
	SUSPECT_END_WELD_FORCE_ENABLED_PARAM,
	SUSPECT_END_WELD_FORCE_LOW_ENABLED_PARAM,
	SUSPECT_END_WELD_FORCE_HIGH_ENABLED_PARAM,
	SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM,
	SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM,
	SUSPECT_VELOCITY_ENABLED_PARAM,
	SUSPECT_VELOCITY_LOW_ENABLED_PARAM,
	SUSPECT_VELOCITY_HIGH_ENABLED_PARAM,
	SUSPECT_VELOCITY_LOW_LIMIT_PARAM,
	SUSPECT_VELOCITY_HIGH_LIMIT_PARAM,

	FREQUENCY_LOW_PARAM,
	FREQUENCY_HIGH_PARAM,
	PHASE_LIMIT_TIME_PARAM,
	PHASE_LIMIT_PARAM,
	CONTROL_MODE_PARAM,
	BLIND_TIME_WELD_PARAM,
	AMP_PROPORTIONAL_GAIN_PARAM,
	AMP_INTEGRAL_GAIN_PARAM,
	AMP_DERIVATIVE_GAIN_PARAM,
	PHASE_PROPORTIONAL_GAIN_PARAM,
	PHASE_INTEGRAL_GAIN_PARAM,
	PHASE_DERIVATIVE_GAIN_PARAM,
	WELD_RAMP_TIME_PARAM,
	START_FREQUENCY_PARAM,
	FREQUENCY_OFFSET_PARAM,
	END_OF_WELD_STORE_PARAM,
	INTERNAL_OFFSET_FLAG_PARAM,
    EXTERNAL_AMPLITUDE_SETTING
};

typedef enum STEP_TYPE 
{
   STEP_TIME,
   STEP_ENERGY,
   STEP_POWER,
   STEP_EXTERNAL,
   STEP_ABSOLUTE_DISTANCE,
   STEP_COLLAPSE_DISTANCE,
}STEP_TYPE;

//Holds the changed weld recipe parameter identifier and value.
typedef struct ChangedWeldRecipeParameter
{
	int RecipeNumber; //Holds the Recipe Number to which the change belongs
	int WeldRecipeParamID; //Holds the changed recipe parameter identifier.
	char Value[BUFFER_TO_HOLD_CHANGED_WELD_RECIPE_DATA]; //Holds the changed value.
	ChangedWeldRecipeParameter()
	{
		memset(Value, 0, sizeof(Value));
	}
}__attribute__((packed)) ChangedWeldRecipeParameter;

typedef struct AmplitudeStepACEStruct
{
	float AmplitudeStepAtValue; //Holds the value that is monitored during the weld to tell the power supply when to perform the step.
								   //For example, if step at is set to TIME, and this value is 500, then after 500 milliseconds, 
								   //the power supply will step to the next amplitude setting.
	uint32_t AmplitudeStepTarget; //The target amplitude that gets sent to the power supply after meeting the criteria defined
								  //in StepAt and StepAtValue
	float AmplitudeStepRamp;   //This defines the rate at which the power supply changes the amplitude from
								  //the current setting to the new step value.
	AmplitudeStepACEStruct()
	{
		AmplitudeStepAtValue = 0.0f;
		AmplitudeStepTarget = 0;
		AmplitudeStepRamp = 0.0f;
	}
}__attribute__((packed)) AmplitudeStepACEStruct;


typedef struct AmplitudeStepDataACE
{
	uint32_t NumAmplitudeSteps;	//The number of amplitude changes or steps that need to occur during the weld.
	STEP_TYPE AmplitudeStepAt; //This holds the attribute of the amplitude step value. This can be time, energy, etc.
							   //and this determines the data type that is present in AmplitudeStepAtValue.
							   //For example, if this variable is set to TIME, then the contents of AmplitudeStepAtValue is a
							   //time based value
	AmplitudeStepACEStruct AmplitudeStepParameters[MAX_NUMBER_OF_AMPLITUDE_STEPS_SUPPORTED];
	AmplitudeStepDataACE()
	{
		NumAmplitudeSteps = 0;
		AmplitudeStepAt = STEP_TIME;
	}
}__attribute__((packed)) AmplitudeStepDataACE;


typedef struct PressureStepACEStruct
{
    float PressureStepAtValue; //Holds the value that is monitored during the weld to tell the actuator when to perform the step.
								  //For example, if step at is set to TIME, and this value is 500, then after 500 milliseconds,
                                  //the actuator will step to the next pressure setting.
    float PressureStepTarget; //The target pressure that gets sent to the actuator after meeting the criteria defined
								 //in StepAt and StepAtValue
    float PressureStepRamp; //NOT APPLICABLE for Pressure stepping.
    PressureStepACEStruct()
    {
        PressureStepAtValue = 0.0f;
        PressureStepTarget = 0.0f;
        PressureStepRamp = 0.0f;
    }
}__attribute__((packed)) PressureStepACEStruct;

typedef struct PressureStepDataACE
{
    uint32_t NumPressureSteps;	//The number of pressure changes or steps that need to occur during the weld.
    STEP_TYPE PressureStepAt; //This holds the attribute of the amplitude step value. This can be time, energy, etc.
        //and this determines the data type that is present in PressureStepAtValue.
        //For example, if this variable is set to TIME, then the contents of PressureStepAtValue is a
        //time based value
    PressureStepACEStruct PressureStepParameters[MAX_NUMBER_OF_PRESSURE_STEPS_SUPPORTED];
    PressureStepDataACE()
    {
        NumPressureSteps = 0;
        PressureStepAt = STEP_TIME;
    }
}__attribute__((packed)) PressureStepDataACE;

typedef struct AfterBurstACEStruct
{
	bool bEnabled; //When true, enables the afterburst function which will turn on sonics during 
				   //the upstroke for a short period of time to shake any stuck plastic off the horn
	int32_t BurstAmplitude; //Amplitude setting for the afterburst function
	float BurstDelay; //A value in seconds that the system will wait after the end of hold time
						//(during upstroke) before turning on sonics.
	float BurstTime; //A value in seconds that determines the duration that sonics will be on for
					   //the afterburst function
}__attribute__((packed))  AfterBurstACEStruct;

typedef struct EnergyBrakeACEStruct
{
	bool bEnabled;
	int32_t EnergyBrakeAmplitude;
	float EnergyBrakeTime;
}__attribute__((packed))  EnergyBrakeACEStruct;

typedef struct EnergyCompensationACEStruct
{
	bool EnergyCompensationEnabled;
	float EnergyCompensationMinValue;
	float EnergyCompensationMaxValue;
}__attribute__((packed))  EnergyCompensationACEStruct;

// ACE Pro only has one method of triggering so keeping this enum for future code reuse.
typedef enum TRIGGER_TYPE
{
    TRIGGER_SWITCH, 
	TRIGGER_FORCE,
	TRIGGER_DISTANCE
}TRIGGER_TYPE;

typedef enum ACTUATOR_CLEAR_TYPE
{
	ACTUATOR_CLEAR_TIME_BASED, 
	ACTUATOR_CLEAR_DISTANCE_BASED //For Prime
}ACTUATOR_CLEAR_TYPE;

typedef struct TriggerDataACEStruct
{
	TRIGGER_TYPE TriggerType;
	float TriggerForce; //Trigger Force - For Prime
	float TriggerDistance; //Trigger Distance - For Prime
		
}__attribute__((packed))  TriggerDataACEStruct;

typedef struct ActuatorClearACEStruct
{
	bool EnableActuatorClear;
	ACTUATOR_CLEAR_TYPE ActuatorClearType;
	float ActuatorClearTime; 
	float ActuatorClearDistance; //For Prime
		
}__attribute__((packed))  ActuatorClearACEStruct;

typedef enum PRE_TRIGGER_TYPE
{
    AUTO_PRETRIGGER, //sonics turns on when leaving ULS
	TIME_PRETRIGGER, //sonics turns on at the specified time after the horn leaves ready position
	DISTANCE_PRETRIGGER //sonics turns on at the specified distance after the horn leaves ready position
}PRE_TRIGGER_TYPE;

typedef struct PreTriggerACEStruct
{
	bool bEnabled;
	PRE_TRIGGER_TYPE PreTriggerType;
	int32_t  Amplitude;
	float PreTriggerTime;
	float PreTriggerDistance;
}__attribute__((packed))  PreTriggerACEStruct;

typedef struct LimitsACEStruct
{
   bool	bEnabled;
   bool bLowEnabled;
   bool bHighEnabled;
   float LowLimit;
   float HighLimit;
}__attribute__((packed))  LimitsACEStruct;

typedef struct SuspectLimitsACEStruct
{
	bool SuspectLimitsEnabled;
	LimitsACEStruct Time;	
	LimitsACEStruct Energy;
	LimitsACEStruct PeakPower;
	LimitsACEStruct Frequency;
	LimitsACEStruct AbsoluteDistance; //For Prime
	LimitsACEStruct CollapseDistance; //For Prime
	LimitsACEStruct TriggerDistance; //For Prime
	LimitsACEStruct EndWeldForce; //For Prime
	LimitsACEStruct Velocity; //For Prime
}__attribute__((packed)) SuspectLimitsACEStruct;

typedef struct RejectLimitsACEStruct
{
	bool RejectLimitsEnabled;
	LimitsACEStruct Time;	
	LimitsACEStruct Energy;
	LimitsACEStruct PeakPower;
	LimitsACEStruct Frequency;
	LimitsACEStruct AbsoluteDistance; //For Prime
	LimitsACEStruct CollapseDistance; //For Prime
	LimitsACEStruct TriggerDistance; //For Prime
	LimitsACEStruct EndWeldForce; //For Prime
	LimitsACEStruct Velocity; //For Prime
}__attribute__((packed))  RejectLimitsACEStruct;

typedef struct CutoffLimitsPropACEStruct
{
	bool bEnabled;
	float Value;
}__attribute__((packed))  CutoffLimitsPropACEStruct;

typedef struct CutOffLimitsACEStruct
{
	bool CutOffLimitsEnabled;
	CutoffLimitsPropACEStruct PeakPowerCutoff;
	CutoffLimitsPropACEStruct TimeCutoff;  
	CutoffLimitsPropACEStruct FrequencyLowCutoff;
	CutoffLimitsPropACEStruct FrequencyHighCutoff;
	CutoffLimitsPropACEStruct EnergyCutoff;
	CutoffLimitsPropACEStruct GroundDetectCutoff;
	CutoffLimitsPropACEStruct AbsoluteDistanceCutoff; //For Prime
	CutoffLimitsPropACEStruct CollapseDistanceCutoff; //For Prime
}__attribute__((packed))  CutOffLimitsACEStruct;

typedef struct CycleCountersACEStruct
{
	int32_t CycleCount;	//Total cycle count for this recipe
	int32_t CyclesOKCount; //OK cycle count for this recipe
	int32_t RejectCount; //Reject cycle count for this recipe
	int32_t SuspectCount; //Suspect cycle count for this recipe - For Prime
}__attribute__((packed))  CycleCountersACEStruct;

typedef struct StackRecipeACEStruct
{
public:
	StackRecipeACEStruct();
	void SetParametersAsPerSystemFrequency();
	int32_t StackRecipeNumber; //Stack Recipe Number
	//int32_t PhaseLoopCF; //reserved for future use
	int32_t	FrequencyLow; //FrequencyLow is the lower frequency limit for the Weld function. The DSP will use this value 
						  //to set a band where the output frequency will not go below this value during the weld.					 
	int32_t	FrequencyHigh; //FrequencyHigh is the higher frequency limit for the Weld function. The DSP will use this value 
	  	  	  	  	  	  //to set a band where the output frequency will not go above this value during the weld.
	float	PhaseLimitTime; //System will generate an alarm if the Phase value reported from the power supply
							//exceeds PhaseLimit for a certain time period. This is the time period.
	int32_t PhaseLimit; //This is a threshold that will generate an alarm in conjunction with the
						//PhaseLimitTime if the Phase value read from the Power supply exceeds it.
	int32_t	ControlMode; //reserved for future use
	float BlindTimeWeld; //Time in seconds that tells the power supply to run open loop at the start
						   //of the weld prior to enabling the control loops.
	int32_t	AmpProportionalGain;
	int32_t	AmpIntegralGain;
	int32_t	AmpDerivativeGain;
	int32_t	PhaseProportionalGain;
	int32_t PhaseIntegralGain;
	int32_t	PhaseDerivativeGain;
	float WeldRampTime;
	int32_t StartFrequency; //A value in tenths of hertz that tells the power supply what frequency to start
							//running at. Weld Start Frequency = Digital Tune + Frequency Offset + Memory Offset
	int32_t MemoryOffset; //Value in tenths of hertz that is applied to the Ditigital Tune value. This value
						  //is automatically calculated and updated in software at the end of the weld depending
						  //on the value of EndOfWeldStore. If the flag is true, this value is updated with the
						  //difference of the frequency read at the end of the weld minus the start frequency.
						  //It effectively acts as a tracking mechanism as the stack frequency shifts during
						  //production.
	int32_t DigitalTune; //This is the frequency at which the stack "wants" to run at. It is typically found
						 //during a horn scan, but can also be manually overridden on the HMI.
	int32_t FrequencyOffset; //A value in tenths of hertz that can be applied to the Start Frequency. This is
							 //manually entered from the HMI for special conditions where Digital Tune and Memory Offset
							 //are not enough. This value can also come from other interfaces like analog input or fieldbus.
	                         //The value is applied to the Start Frequency when InternalOffsetFlag is true or when false,
							 //it will use the externally provided value
	bool EndOfWeldStore; //When true, the MemoryOffset value will be updated at the end of the weld (if no alarm is present) as follows:
						 //MemoryOffset = End Frequency - DigitalTune.
						 //FrequencyOffset has no effect on this value.
						 //End Frequency is defined as the frequency value read at the time the sonics are turned off.
						 //When false, MemoryOffset will not be modified (previous value will be maintained)
	bool InternalOffsetFlag;
}__attribute__((packed))  StackRecipeACEStruct;

typedef struct WeldRecipeACEStruct
{
	void SetParametersAsPerSystemFrequency();
	int32_t WeldRecipeNumber; //Weld Recipe Number
	int32_t WeldRecipeVersionNumber; //Weld Recipe Version Number
	char WeldRecipeName[MAX_LENGTH_RECIPE_NAME]; //Weld Recipe Name
	WELDMODES WeldMode; //weld mode type i.e. time,energy etc.
	float ModeValueTime; //Time mode value in seconds
	float ModeValueEnergy; //Energy mode value in Joule
	float ModeValuePeakPower; //Peak Power mode value in Watt
	float ModeValueGroundDetect; //Ground Detect mode value (Scrub Time) in seconds
	float ModeValueAbsoluteDistance; //Absolute distance in mm - For Prime
	float ModeValueCollapseDistance; //Collapse distance in mm - For Prime
	bool IsSaved; //Flag to indicated if the weld recipe is saved or not
	CycleCountersACEStruct CycleCounterData;
	bool BatchSetupEnable;
	bool BatchAlarmEnable;
	uint32_t BatchCounter;
	uint32_t BatchCountLimit;
	char BatchID[BATCHID_SIZE];
	ACTUATOR_TYPE ActuatorType;
	
	float WeldPressure; //Weld Pressure - For Prime
	float HoldPressure; //Hold Pressure - For Prime
	float FlowRate; //Flow Rate  - For Prime
	float HoldTime; //Weld Hold Time
	float MaxWeldTimeout; // the weld operation time out period
	uint32_t WeldAmplitude; //Weld amplitude value
	uint32_t NumAmplitudeSteps;	//The number of amplitude changes or steps that need to occur during the weld.
	STEP_TYPE AmplitudeStepAt; //This holds the attribute of the amplitude step value. This can be time, energy, etc.
							   //and this determines the data type that is present in AmplitudeStepAtValue.
							   //For example, if this variable is set to TIME, then the contents of AmplitudeStepAtValue is a
							   //time based value
	AmplitudeStepACEStruct AmplitudeStepParameters[MAX_NUMBER_OF_AMPLITUDE_STEPS_SUPPORTED];
	uint32_t NumPressureSteps; //The number of pressure changes or steps that need to occur during the weld. //For Prime
	STEP_TYPE PressureStepAt; //This holds the attribute of the pressure step value. This can be time, energy, etc. //For Prime
							  //and this determines the data type that is present in PressureStepAtValue.
							  //For example, if this variable is set to TIME, then the contents of PressureStepAtValue is a
							  //time based value
	PressureStepACEStruct PressureStepParameters[MAX_NUMBER_OF_PRESSURE_STEPS_SUPPORTED]; //For Prime
	
	bool IsCoolingValveEnabled; //When true, the actuator board will turn on a valve that allows extra
                                //air to be applied to the converter to prevent overheating.
    bool ExternalAmplitudeSetting;

	TriggerDataACEStruct TriggerData;	

	PreTriggerACEStruct PreTrigger;
	AfterBurstACEStruct AfterBurst;
	EnergyBrakeACEStruct EnergyBrake;
	EnergyCompensationACEStruct EnergyCompensation;
	
    float TimedSeekPeriod; //This is a time value in seconds that determines the period of how often the
							  //power supply will automatically initiate a Seek function. (only if system is idle)
	bool IsTimedSeekEnabled; //When true, enables the Timed Seek function
	bool IsPreWeldSeekEnabled; //When true, during the downstroke of the actuator for a weld, the power supply
							   //will perform a seek function
	bool IsPostWeldSeekEnabled; //When true, during the upstroke of the actuator for a weld, the power supply
								//will perform a seek function
	uint32_t ScrubAmplitude; //This value is only applicable when the system is in ground detect mode.
							 //After the system has detected ground, the power supply will change its amplitude to this value.	
	bool RapidTraverse; //For Prime
	float RapidTraverseDistance; //For Prime
	bool TriggerLost; //For Prime
	ActuatorClearACEStruct ActuatorClearData; //For Prime
	
	CutOffLimitsACEStruct CutoffLimit;
	RejectLimitsACEStruct RejectLimit;
	SuspectLimitsACEStruct SuspectLimit;
	StackRecipeACEStruct StackRecipe;
	
	WeldRecipeACEStruct();
}__attribute__((packed))  WeldRecipeACEStruct;

//Structure for data to be shown on recipe card screen
typedef struct RecipeCardDataACEStruct
{
	int32_t WeldRecipeNumber;
	int32_t WeldRecipeVersionNumber;
	char WeldRecipeName[MAX_LENGTH_RECIPE_NAME];
	WELDMODES WeldMode;
	float ModeValue;
	int32_t CycleCount;
	RecipeCardDataACEStruct()
	{
		memset(WeldRecipeName, 0, sizeof(WeldRecipeName));
	}
}__attribute__((packed))  RecipeCardDataACEStruct;

#endif /* WELD_RECIPE_STRUCTURES_ACE_H_ */

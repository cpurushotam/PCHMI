/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE UserIO data related structure definition.

***************************************************************************/
#ifndef DGT_USER_IO_STRUCT_ACE_H_
#define DGT_USER_IO_STRUCT_ACE_H_

#include "Common_Definitions.h"
#include <map>
#include <cstring>

// max IO functions
typedef	enum
{
    INPUT_FUNCTION_NONE = 0,
    INPUT_DISABLE,

    IN_ULTRASONIC_SONIC_DISABLE,
    IN_CABLE_DETECT,
    IN_DISPLAY_LOCK,
    IN_CYCLE_ABORT,			//Ends cycle and returns actuator to the home position.
    IN_ALARM_RESET,			//Resets all alarms in the system.
    IN_ULTRASONIC_DELAY,	//Ultrasonic start is delayed until trigger and U/S delay are active.
    IN_HOLD_DELAY,
    IN_LOAD_RECIPE,
    EXT_TOOLING_INPUT,
    IN_HORN_SCAN,
    IN_HORN_SEEK,
    IN_HORN_TEST,
    IN_MEMORY_CLEAR,
	PART_PRESENT_INPUT,
	INPUT_PSWD_OVERRIDE,
    IN_ESTOP_RESET,

    RECIPE_1,
    RECIPE_2,
    RECIPE_4,
    RECIPE_8,
	
	EXTERNAL_AMPLITUDE_TRIGGER_1,
	EXTERNAL_AMPLITUDE_TRIGGER_2,
	EXTERNAL_AMPLITUDE_TRIGGER_3,

    INPUT_FUNCTION_MAX
}INPUT_LINE_FUNCTION;
typedef enum
{
    OUTPUT_FUNCTION_NONE,
    OUTPUT_DISABLED,

    SYSTEM_READY,			// the system is in the ready state.
    CYCLE_RUNNING,
    CYCLE_OK,
    ULTRASONIC_ACTIVE,		//ultrasonics active
    SOLENOID_ACTIVE,		//internal solenoid drive is active.
    ACTUATOR_CLEAR,

    AFTERBURST_DELAY,
    AFTERBURST_TIME,

    PB_RELEASE,
    HOLD_TIME_ACTIVE,		//Indicates the system is in the hold time state.
    ACTUATOR_HOME,			//actuator is at the home position?and the part is ready to be removed from the base.
    HORN_SEEK,
    HORN_SCAN,
	HORN_TEST,

    ALARM_GENERAL,
    ALARM_CUSTOM,
    ALARM_REJECT_PART,
    ALARM_CUTTOFF,
    ALARM_OVERLOAD,

    EXT_TOOLING_OUTPUT,
    CONFIRM_RECIPE,
	MEMORY_CLEAR_ACTIVE,	//Indicates memory clear is active
	
	OUTPUT_PSWD_OVERRIDE,

    OUTPUT_FUNCTION_MAX
} OUTPUT_LINE_FUNCTION;

// Analog IO functions
typedef	enum
{
    AN_INPUT_FUNCTION_NONE = 0,
    AN_INPUT_DISABLE,
    AN_INPUT_AMPLITUDE,
    AN_INPUT_FREQUENCY_OFFSET,
    AN_INPUT_FUNCTION_MAX
}ANALOG_INPUT_LINE_FUNCTION;

typedef	enum
{
    AN_OUTPUT_FUNCTION_NONE = 0,
    AN_OUTPUT_DISABLE,
    AN_OUTPUT_POWER,
    AN_OUTPUT_AMPLITUDE,
    AN_OUTPUT_CURRENT,
    AN_OUTPUT_FREQUENCY,
    AN_OUTPUT_FUNCTION_MAX
}ANALOG_OUTPUT_LINE_FUNCTION;

/********************** User I/O Interface Structures **********************/
typedef struct
{
    INPUT_LINE_FUNCTION PS_EVENT;
    bool Status;//Active High/Low
    bool IsPinEnabled;
}__attribute__((packed)) PS_INPUT;

typedef struct
{
    OUTPUT_LINE_FUNCTION PS_EVENT;
    bool Status;//Active High/Low
    bool IsPinEnabled;
}__attribute__((packed)) PS_OUTPUT;

typedef struct
{
    ANALOG_INPUT_LINE_FUNCTION PS_EVENT;
    bool IsPinEnabled;
}__attribute__((packed)) PS_ANALOG_INPUT;

typedef struct
{
    ANALOG_OUTPUT_LINE_FUNCTION PS_EVENT;
    bool IsPinEnabled;
}__attribute__((packed)) PS_ANALOG_OUTPUT;

typedef struct
{
    PS_INPUT 	J116_01;
    PS_INPUT 	J116_02;
    PS_INPUT 	J116_03;
    PS_INPUT 	J116_04;
    PS_INPUT 	J116_11;
    PS_INPUT 	J116_12;
    PS_INPUT 	J116_13;
    PS_INPUT 	J116_16;
    PS_INPUT 	J116_23;
}__attribute__((packed)) PS_DIGITALINPUT;

typedef struct
{
    PS_OUTPUT 	J116_07;
    PS_OUTPUT 	J116_08;
    PS_OUTPUT 	J116_09;
    PS_OUTPUT 	J116_10;
    PS_OUTPUT 	J116_19;
    PS_OUTPUT 	J116_20;
    PS_OUTPUT 	J116_21;
    PS_OUTPUT 	J116_22;
}__attribute__((packed)) PS_DIGITALOUTPUT;

typedef struct
{
    PS_ANALOG_INPUT J3_17;
    PS_ANALOG_INPUT J3_18;
}__attribute__((packed)) PS_ANALOGINPUT;

typedef struct
{
    PS_ANALOG_OUTPUT J3_24;
    PS_ANALOG_OUTPUT J3_25;
}__attribute__((packed)) PS_ANALOGOUTPUT;

typedef struct
{
    PS_DIGITALINPUT 	PsDigitalInput;
    PS_DIGITALOUTPUT 	PsDigitalOutput;
}__attribute__((packed)) POWERSUPPLY_USERIO;

typedef struct USERIO
{
    POWERSUPPLY_USERIO PS_USERIO;
    //definantion of default structure
    bool GlobalDigitalInputSwitchState;
    bool GlobalDigitalOutputSwitchState;
    USERIO()
    {

    	 GlobalDigitalInputSwitchState = true;
         GlobalDigitalOutputSwitchState = true;

        PS_USERIO.PsDigitalInput.J116_01.PS_EVENT		= IN_CYCLE_ABORT ;
        PS_USERIO.PsDigitalInput.J116_01.Status			= true ;
        PS_USERIO.PsDigitalInput.J116_01.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalInput.J116_02.PS_EVENT       = IN_ULTRASONIC_SONIC_DISABLE;
        PS_USERIO.PsDigitalInput.J116_02.Status         = true ;
        PS_USERIO.PsDigitalInput.J116_02.IsPinEnabled   = false ; // intentionally disabled for ultrasonic disable

        PS_USERIO.PsDigitalInput.J116_03.PS_EVENT       = IN_ALARM_RESET;
        PS_USERIO.PsDigitalInput.J116_03.Status         = true ;
        PS_USERIO.PsDigitalInput.J116_03.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalInput.J116_04.PS_EVENT       = RECIPE_1;
        PS_USERIO.PsDigitalInput.J116_04.Status         = true ;
        PS_USERIO.PsDigitalInput.J116_04.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalInput.J116_11.PS_EVENT       = IN_HOLD_DELAY;
        PS_USERIO.PsDigitalInput.J116_11.Status         = true ;
        PS_USERIO.PsDigitalInput.J116_11.IsPinEnabled   = false ; // intentionally disabled for hold delay

        PS_USERIO.PsDigitalInput.J116_12.PS_EVENT       = IN_HORN_SEEK;
        PS_USERIO.PsDigitalInput.J116_12.Status	        = true ;
        PS_USERIO.PsDigitalInput.J116_12.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalInput.J116_13.PS_EVENT       = IN_CABLE_DETECT;
        PS_USERIO.PsDigitalInput.J116_13.Status         = true ;
        PS_USERIO.PsDigitalInput.J116_13.IsPinEnabled   = false ; // intentionally disabled for cable detect

        PS_USERIO.PsDigitalInput.J116_16.PS_EVENT       = RECIPE_2;
        PS_USERIO.PsDigitalInput.J116_16.Status	        = true ;
        PS_USERIO.PsDigitalInput.J116_16.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalInput.J116_23.PS_EVENT       = IN_ESTOP_RESET;
        PS_USERIO.PsDigitalInput.J116_23.Status	        = true ;
        PS_USERIO.PsDigitalInput.J116_23.IsPinEnabled   = true ;

        PS_USERIO.PsDigitalOutput.J116_07.PS_EVENT      = SYSTEM_READY ;
        PS_USERIO.PsDigitalOutput.J116_07.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_07.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_08.PS_EVENT      = ULTRASONIC_ACTIVE;
        PS_USERIO.PsDigitalOutput.J116_08.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_08.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_09.PS_EVENT      = ALARM_GENERAL;
        PS_USERIO.PsDigitalOutput.J116_09.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_09.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_10.PS_EVENT      = CYCLE_RUNNING ;
        PS_USERIO.PsDigitalOutput.J116_10.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_10.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_19.PS_EVENT      = HORN_SEEK;
        PS_USERIO.PsDigitalOutput.J116_19.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_19.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_20.PS_EVENT      = CYCLE_OK;
        PS_USERIO.PsDigitalOutput.J116_20.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_20.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_21.PS_EVENT      = PB_RELEASE;
        PS_USERIO.PsDigitalOutput.J116_21.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_21.IsPinEnabled  = true ;

        PS_USERIO.PsDigitalOutput.J116_22.PS_EVENT      = ALARM_REJECT_PART ;
        PS_USERIO.PsDigitalOutput.J116_22.Status	    = true ;
        PS_USERIO.PsDigitalOutput.J116_22.IsPinEnabled  = true ;
    }
}__attribute__((packed)) USERIO;

typedef struct
{
    PS_ANALOGINPUT      PsAnalogInput;
    PS_ANALOGOUTPUT 	PsAnalogOutput;
}__attribute__((packed)) POWERSUPPLY_USERIO_ANALOG;

typedef struct USERIO_ANALOG
{
    POWERSUPPLY_USERIO_ANALOG PS_USERIO_ANALOG;
    //definantion of default structure
    bool GlobalAnalogInputSwitchState;
    bool GlobalAnalogOutputSwitchState;
    USERIO_ANALOG()
    {      

    	GlobalAnalogInputSwitchState = true;
		GlobalAnalogOutputSwitchState = true;
        PS_USERIO_ANALOG.PsAnalogInput.J3_17.PS_EVENT          = AN_INPUT_AMPLITUDE;
        PS_USERIO_ANALOG.PsAnalogInput.J3_17.IsPinEnabled      = false ;

        PS_USERIO_ANALOG.PsAnalogInput.J3_18.PS_EVENT          = AN_INPUT_FREQUENCY_OFFSET;
        PS_USERIO_ANALOG.PsAnalogInput.J3_18.IsPinEnabled      = false ;

        PS_USERIO_ANALOG.PsAnalogOutput.J3_24.PS_EVENT         = AN_OUTPUT_POWER;
        PS_USERIO_ANALOG.PsAnalogOutput.J3_24.IsPinEnabled     = false ;

        PS_USERIO_ANALOG.PsAnalogOutput.J3_25.PS_EVENT         = AN_OUTPUT_AMPLITUDE;
        PS_USERIO_ANALOG.PsAnalogOutput.J3_25.IsPinEnabled     = false ;
    }
}__attribute__((packed)) USERIO_ANALOG;

typedef struct DiagnosticUserIOInputs{
    bool DIAGNOSTIC_USERIO_DIGINPUTS[DIGITAL_IO_MAX_INPUTS];
    float Analog_Input_1 ;
    float Analog_Input_2 ;

}__attribute__((packed)) DiagnosticDigitalInputs;

typedef struct DiagnosticUserIOOutputs{
     bool DIAGNOSTIC_USERIO_DIGOUTPUTS[DIGITAL_IO_MAX_OUTPUTS];
    float Analog_Output_1 ;
    float Analog_Output_2 ;

}__attribute__((packed)) DiagnosticUserIOOutputs;

/*This enum defines on screen operations HMI to ASC */
typedef enum
{
    SAVE_DIGITAL_USER_IO_DATA = 1,
    DIGITAL_USER_IO_RESET_TO_DEFAULT,
    READ_DIGITAL_USER_IO_DATA,
	READ_DIAGNOSTIC_USERIO_DATA,
    REFRESH_DIAGNOSTIC_USERIO,
    SAVE_ANALOG_USER_IO_DATA,
    ANALOG_USER_IO_RESET_TO_DEFAULT,
    READ_ANALOG_USER_IO_DATA,
}DIGITAL_USER_IO_SUB_ID;

/*This enum defines responses */
typedef enum
{
    DIGITAL_USER_IO_UPDATE_RESPONSE_UNKNOWN,
    DIGITAL_USER_IO_UPDATE_SUCCESS,
    DIGITAL_USER_IO_UPDATE_FAILURE,
}DIGITAL_USER_IO_UPDATE_RESPONSE;


typedef enum  {
    DIGITAL_INPUT1 = 1,
    DIGITAL_INPUT2,
    DIGITAL_INPUT3,
    DIGITAL_INPUT4,
    DIGITAL_INPUT5,
    DIGITAL_INPUT6,
    DIGITAL_INPUT7,
    DIGITAL_INPUT8,
    DIGITAL_INPUT9,
    DIGITAL_OUTPUT1,
    DIGITAL_OUTPUT2,
    DIGITAL_OUTPUT3,
    DIGITAL_OUTPUT4,
    DIGITAL_OUTPUT5,
    DIGITAL_OUTPUT6,
    DIGITAL_OUTPUT7,
    DIGITAL_OUTPUT8
}DGTUSERIOENUM;

typedef enum {
    ANALOG_INPUT1 = 1,
    ANALOG_INPUT2,
    ANALOG_OUTPUT1,
    ANALOG_OUTPUT2
} ANALOGUSERIOENUM;

extern const std::map <INPUT_LINE_FUNCTION , std::string> UserInputEventName;
extern const std::map <OUTPUT_LINE_FUNCTION , std::string> UserOutputEventName;
extern const std::map <ANALOG_INPUT_LINE_FUNCTION , std::string> UserIOAnalogIpEventName;
extern const std::map <ANALOG_OUTPUT_LINE_FUNCTION , std::string> UserIOAnalogOpEventName;
extern const std::map<DGTUSERIOENUM, std::string> DigitalUserIOStringMap;
extern const std::map<ANALOGUSERIOENUM, std::string> AnalogUserIOStringMap;

#endif /* DGT_USER_IO_STRUCT_ACE_H_ */


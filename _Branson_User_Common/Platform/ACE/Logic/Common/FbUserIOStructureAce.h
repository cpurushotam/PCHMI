/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the FieldBus ACE UserIO data related structure definition.

***************************************************************************/

#ifndef FB_USER_IO_STRUCT_ACE_H_
#define FB_USER_IO_STRUCT_ACE_H_

#include "Common_Definitions.h"
#include <map>
#include <cstring>

// user configurable FieldBus functions
typedef	enum
{
    FB_INPUT_FUNCTION_NONE = 0,
    FB_INPUT_DISABLE,
	IN_WELD_MODE,
	IN_TIME_MODE,
	IN_ENERGY_MODE,
	IN_PEAK_POWER_MODE,
	IN_GRD_DETECT_MODE,
	IN_ABS_MODE,
	IN_COLLAPSE_MODE,
	IN_WELD_AMPLITUDE,
	IN_DOWN_SPEED,
	IN_TRIGGER_FORCE,
	IN_WELD_PRESSURE,
	IN_HOLD_TIME,
	IN_HOLD_PRESSURE,
	
    FB_INPUT_FUNCTION_MAX

}INPUT_FB_FUNCTION;

typedef	enum
{
	FB_OUTPUT_FUNCTION_NONE = 0,
	FB_OUTPUT_DISABLED,

	OUT_WELD_MODE,
	OUT_TIME_MODE,
	OUT_ENERGY_MODE,
	OUT_PEAK_POWER_MODE,
	OUT_GRD_DETECT_MODE,
	OUT_ABS_MODE,
	OUT_COLLAPSE_MODE,
	OUT_WELD_AMPLITUDE,
	OUT_DOWN_SPEED,
	OUT_TRIGGER_FORCE,
	OUT_WELD_PRESSURE,
	OUT_HOLD_TIME,
	OUT_HOLD_PRESSURE,
	
	FB_OUTPUT_FUNCTION_MAX

}OUTPUT_FB_FUNCTION;

/********************** User EIP Interface Structures **********************/
typedef struct
{
	INPUT_FB_FUNCTION FB_EVENT;
	bool IsControlWordEnabled;
}__attribute__((packed)) FB_INPUT;

typedef struct
{
	OUTPUT_FB_FUNCTION FB_EVENT;
	bool IsStatusWordEnabled;
}__attribute__((packed)) FB_OUTPUT;

typedef struct
{
	FB_INPUT Control_Word_01;
	FB_INPUT Control_Word_02;
	FB_INPUT Control_Word_03;
}__attribute__((packed)) FB_IMPLICITINPUT;

typedef struct
{
	FB_OUTPUT Status_Word_01;
	FB_OUTPUT Status_Word_02;
	FB_OUTPUT Status_Word_03;
}__attribute__((packed)) FB_IMPLICITOUTPUT;

typedef struct
{
	FB_IMPLICITINPUT	FbImplicitInput;
	FB_IMPLICITOUTPUT 	FbImplicitOutput;
}__attribute__((packed)) FIED_BUS_CUSTOMIO;


typedef struct FB_USERIO
{
	FIED_BUS_CUSTOMIO	FB_CUSTOMIO;
	
	FB_USERIO()
	{
		// control word
		FB_CUSTOMIO.FbImplicitInput.Control_Word_01.FB_EVENT = FB_INPUT_DISABLE;
		FB_CUSTOMIO.FbImplicitInput.Control_Word_01.IsControlWordEnabled = false;
		
		FB_CUSTOMIO.FbImplicitInput.Control_Word_02.FB_EVENT = FB_INPUT_DISABLE;
		FB_CUSTOMIO.FbImplicitInput.Control_Word_02.IsControlWordEnabled = false;
		
		FB_CUSTOMIO.FbImplicitInput.Control_Word_03.FB_EVENT = FB_INPUT_DISABLE;
		FB_CUSTOMIO.FbImplicitInput.Control_Word_03.IsControlWordEnabled = false;
		
		// status word
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.FB_EVENT = FB_OUTPUT_DISABLED;
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.IsStatusWordEnabled = false;
		
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.FB_EVENT = FB_OUTPUT_DISABLED;
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.IsStatusWordEnabled = false;
		
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.FB_EVENT = FB_OUTPUT_DISABLED;
		FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.IsStatusWordEnabled = false;
	}
}__attribute__((packed)) FB_USERIO;

/*This enum defines on screen operations HMI to ASC */
typedef enum
{
    SAVE_FIELDBUS_USER_IO_DATA = 1,
    FIELDBUS_USER_IO_RESET_TO_DEFAULT,
    READ_FIELDBUS_USER_IO_DATA,
}FIELDBUS_USER_IO_SUB_ID;

typedef enum 
{
    FIELDBUS_CONTROL_WORD1 = 1,
	FIELDBUS_CONTROL_WORD2,
	FIELDBUS_CONTROL_WORD3,
	FIELDBUS_STATUS_WORD1,
	FIELDBUS_STATUS_WORD2,
	FIELDBUS_STATUS_WORD3
} FIELDBUSUSERIOENUM;

extern const std::map <INPUT_FB_FUNCTION , std::string> UserIOFieldbusIpEventName;
extern const std::map <OUTPUT_FB_FUNCTION , std::string> UserIOFieldbusOpEventName;
extern const std::map<FIELDBUSUSERIOENUM, std::string> FieldbusUserIOStringMap;
#endif /* FB_USER_IO_STRUCT_ACE_H_ */

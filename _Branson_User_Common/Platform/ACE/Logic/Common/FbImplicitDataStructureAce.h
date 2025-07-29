/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the FieldBus Implicit Data related structure definition.

***************************************************************************/

#ifndef FB_IMPLICIT_DATA_STRUCT_ACE_H_
#define FB_IMPLICIT_DATA_STRUCT_ACE_H_

#include "Common_Definitions.h"
#include <cstring>


#define FB_INPUT_BITS		    	80	/* Max Input Cyclic Data from Netx90 device */
#define FB_INPUT_BITS_ONE			96	/*size of the input local buffer created for custom control words*/
#define FB_OUTPUT_BITS				64  /* Max Output Cyclic Data to Netx90 device */ 

#define FB_INPUT_BYTES				FB_INPUT_BITS/16      /* Total Number of halfwords for input  data */
#define FB_INPUT_BYTES_ONE			FB_INPUT_BITS_ONE/32  /*size of the input one local buffer created for custom control words*/

// This are the sizes of the buffers required to contemplate implicit outputs data.
#define FB_OUTPUT_BYTES_ONE			4  /* macros used in sending cyclic output data to create a specific buffer size */
#define FB_OUTPUT_BYTES_TWO			5  /* macros used in sending cyclic output data to create a specific buffer size */
#define FB_OUTPUT_BYTES_THREE	    7  /* macros used in sending cyclic output data to create a specific buffer size */
#define FB_OUTPUT_BYTES_FOUR		3  /* macros used in sending cyclic output data to create a specific buffer size */

#define FB_MAX_OUTPUT_BYTES	    	(FB_OUTPUT_BYTES_ONE*2)+(FB_OUTPUT_BYTES_TWO*4)+(FB_OUTPUT_BYTES_THREE*4)+(FB_OUTPUT_BYTES_FOUR*4)+(4) //Last 4bytes are meant to contemplate AlarmID



typedef	enum
{
	LINE_LOW_FB,
	LINE_HIGH_FB,
	
	LINE_NONE_FB

} FB_LINE_VALUE;

typedef	enum
{
	STATE_ACTIVE_LOW_FB,
	STATE_ACTIVE_HIGH_FB,

	STATE_NONE
} FB_LINE_STATE;

typedef struct{

	FB_LINE_VALUE value;
	FB_LINE_STATE logic;

}DigIOProperty;

typedef enum
{
		NO_B,	//NOT USED
		ES,		//ESTOP
		TEE,	//NOT USED
		HFSE,	//NOT USED
		HFS0,	//NOT USED
		HFS1,	//NOT USED
		HFS2,	//NOT USED
		HFS3,	//NOT USED
		RCPB0,	//NOT USED
		RCPB1,	//NOT USED
		RCPB2,	//NOT USED
		RCPB3,	//NOT USED
		RCPB4,	//NOT USED
		PSCA ,	//NOT USED
		MA,		//NOT USED
		OL_0 ,	// msb
}StatusWord1;

typedef enum 
{
		SE_2,		//NOT USED
		CM_3 ,		//NOT USED
		WA_4,		//NOT USED
		EQ_6 ,		//NOT USED
		NC_7,		//NOT USED
		CF_8 ,		//NOT USED
		HW_A,		//NOT USED
		CU_1,		//NOT USED
		TP_9,		//NOT USED
		SM,			//NOT USED
		READY_ST,	//OUTPUT_SYSTEM_READY
		SONIC_ON ,	//OUTPUT_ULTRASONIC
		WELD_OK ,	//OUTPUT_CYCLE_OK
		LM_5,		//NOT USED
		MCLR,		//OUTPUT_MEMORY_CLEAR
		ACLR,	    //OUTPUT_ACTUATOR_CLEAR
}StatusWord2;

typedef enum
{
		CYRU ,	//OUTPUT_CYCLE_RUN
		H_SEEK,	//OUTPUT_HORN_SEEK
		WACT,	//NOT USED(Active weld)
		HACT,	//OUTPUT_HOLD_ACTIVE
		HPOS,	//OUTPUT_AC_HOME
		RPOS,   //NOT USED(Ready position)
		PBR,	//OUTPUT_PB_RELEASE
		GR_AL,	//general alarm
		STP_MD,	//setup mode
		VAL_R,	//validated recipe -> Future scope
		S_AL,	//Suspect alarm
		R_AL,	//Reject alarm
		ABRST,	//Afterburst active
		FPC,	//NOT USED(Part contact in Progress)
		H_SCAN, //Horn scan
		H_TEST,	//Horn Test
}StatusWord3;

typedef enum
{
	CW1_USDIS,	//U/S Disable
	CW1_ES,		//DCX use only
	CW1_HPOS,	//NOT_USED(Home Position)
	CW1_RPOS,	//NOT_USED(Ready Position)
	CW1_HFS0,	//DCX use only
	CW1_HFS1,	//DCX use only
	CW1_HFS2,	//DCX use only
	CW1_HFS3,	//DCX use only
	CW1_RCPB0,	//Weld Recipe Bit 0 -> DCX use only
	CW1_RCPB1,	//Weld Recipe Bit 1 -> DCX use only
 	CW1_RCPB2,	//Weld Recipe Bit 2 -> DCX use only
	CW1_RCPB3,	//Weld Recipe Bit 3 -> DCX use only
	CW1_RCPB4,	//Weld Recipe Bit 4 -> DCX use only
	CW1_HDEL,	//Hold Delay
	CW1_MA,		//Manual/Auto -> DCX use only
	CW1_UILOCK, //HMI lock/Unlock mode.
}ControlWord1;

typedef enum
{
	CW2_FCT,	//Weld Function
	CW2_SFCT,	//Stack Function
	CW2_SFCT0,	//Stack Function 0
	CW2_SFCT1,	//Stack Function 1
	CW2_SFCT2,	//Stack Function 2
	CW2_EXTWA,	//External Weld Amplitude
	CW2_MCLR,	//Memory Clear
	CW2_RES1,	//Reserved
	CW2_RST,	//Reset
	CW2_ON,		//Run Ultrasonics
	CW2_CYAB,	//Cycle Abort
	CW2_RES2,	//Reserved
	CW2_GNDDT,	//NOT_USED(Ground Detect)
	CW2_APROF,	//Amplitude Profile ->  DCX use only
	CW2_RES3,	//Reserved
	CW2_RES4,	//Reserved
}ControlWord2;

typedef enum
{
	CW3_ACFT,	//Actuator Function
	CW3_ACFT0,	//Actuator Function 0
	CW3_ACFT1,	//Actuator Function 1
	CW3_ACFT2,	//Actuator Function 2
	CW3_RES0,	//Reserved
	CW3_GSXR0,	//Weld Recipe Number 0
	CW3_GSXR1,	//Weld Recipe Number 1
	CW3_GSXR2,	//Weld Recipe Number 2
	CW3_GSXR3,	//Weld Recipe Number 3
	CW3_GSXR4,	//Weld Recipe Number 4
	CW3_GSXR5,	//Weld Recipe Number 5
	CW3_GSXR6,	//Weld Recipe Number 6
	CW3_GSXR7,	//Weld Recipe Number 7
	CW3_GSXR8,	//Weld Recipe Number 8
	CW3_GSXR9,	//Weld Recipe Number 9
	CW3_RES1,	//Reserved
}ControlWord3;	

typedef struct ImplicitOutputs
{
	UINT16	
		Reserved1,
		Reserved2;
	UINT16
		StatusWord1,
		StatusWord2,
		StatusWord3;
	UINT32
		Amplitude,
		Current,
		Phase,
		Frequency,
		RequestAmplitude;
	float
	    Time,
	    Power,
	    Energy,
		Force,
		Velocity,
		AbsoluteDistance,
		CollapseDistance;
}ImplicitOutputs;

typedef struct ImplicitInputs
{
	UINT16
		ControlWord1,
		ControlWord2,
		ControlWord3,
	    ActiveRecipeNumber,
		ExtWeldAmplitude;
	float
		CW_CUSTOM_1,
		CW_CUSTOM_2,
		CW_CUSTOM_3;
}ImplicitInputs;

enum StatusWordNum
{
	SW1 = 1,
	SW2,
	SW3
};

/* In Cyclic data to read and write the control words from local buffer of uint16, the below mentioned indexes are used */
enum INDEXES
{
	INDEX_0,
	INDEX_1,
	INDEX_2,
	INDEX_3,
	INDEX_4
};

#endif /* FB_IMPLICIT_DATA_STRUCT_ACE_H_ */

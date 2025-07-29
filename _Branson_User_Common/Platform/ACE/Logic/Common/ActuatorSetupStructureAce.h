/**************************************************************************
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the horn down structure implementation 
 ***************************************************************************/

#include "Common_Definitions.h"

#ifndef ACTUATOR_SETUP_STRUCTURE_H_
#define ACTUATOR_SETUP_STRUCTURE_H_

typedef enum
{
	READ_ACTUATOR_SETUP_DATA        = 1,
    ENTER_LEAVE_ACTUATOR_SETUP_SCREEN,
	SELECT_ACTUATOR_SETUP_OPEARTION_TYPE,
	INITIATE_ACTUATOR_SETUP_HORN_RETRACT,
	ACTUATOR_SETUP_HORN_CLAMP_ON_OFF,
	SYNCH_ACTUATOR_SETUP_DATA,
}ACTUATOR_SETUP_ACE_SUB_ID;

/* The structure used for sending response to UIC, While performing any of actuator setup operations */
typedef struct ActuatorSetupStruct
{
	uint32_t	ResponseType;			/* FIND_PART_CONTACT_OP, JOG-UP/DOWN, HORN_DOWN, HORN_RETRACT, READY POSITION */
	uint32_t	ResponseStatus;			/* Indicates operation status - Success or fail */		
	float 	    AbsolutePosition;
	float       Pressure;
	float       MaxVelocity;
	float	    ActualForce;
	bool 		isHornPositionOnGround;
	
	ActuatorSetupStruct()
	{
		ResetParameters();
	}
	
	void ResetParameters()
	{
		ResponseType     = 0;
		ResponseStatus   = 0;
		AbsolutePosition = 0.0f;
		Pressure         = 0.0f;
		MaxVelocity      = 0.0f;
		ActualForce      = 0.0f;
	}
	
}__attribute__((packed)) ActuatorSetupStruct;



#endif /* ACTUATOR_SETUP_STRUCTURE_H_ */

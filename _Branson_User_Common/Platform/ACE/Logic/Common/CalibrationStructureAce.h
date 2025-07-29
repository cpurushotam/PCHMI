/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the actuator calibration related implementation
 
***************************************************************************/

#ifndef CALIBRATION_STRUCTURE_ACE_H_
#define CALIBRATION_STRUCTURE_ACE_H_

typedef	enum 
{
	CALIBRATION_ENTER = 0,
	CALIBRATION_FIRST_POINT,
	CALIBRATION_SECOND_POINT,
	CALIBRATION_THIRD_POINT,
	CLIBRATION_ABORT,
}CALIBRATION_STAGE;

typedef	enum 
{
	FORCE_CALIBRATION_INIT = 0,
	FORCE_CALIBRATION_WAIT_FOR_TRIGGER,
	FORCE_CALIBRATION_HOLD,

}FORCE_CALIBRATION_STATUS;

typedef	enum 
{
	CALIBRATION_ABORTED = 0,
	CALIBRATION_PASSED,
	CALIBRATION_FAILED,
	CALIBRATION_DEFAULT
}CALIBRATION_RESULT;

typedef	enum 
{
	TYPE_UNKNOWN_CALIBRATION = -1,
	TYPE_QUICK_CALIBRATION,
	TYPE_PRESSURE_CALIBRATION,
	TYPE_FORCE_CALIBRATION,
	TYPE_RESET_CALIBRATION
}CALIBRATION_TYPE;

typedef enum
{
	SUB_ID_ABORT_CALIBRATION = 1,
	SUB_ID_RESET_CALIBRATION,
	SUB_ID_START_QUICK_CALIBRATION,
   SUB_ID_START_PRESSURE_CALIBRATION,
   SUB_ID_START_FORCE_CALIBRATION,
   SUB_ID_USER_ENTERED_PRESSURE_1,
   SUB_ID_USER_ENTERED_PRESSURE_2,
   SUB_ID_USER_ENTERED_PRESSURE_3,
   SUB_ID_USER_ENTERED_FORCE_1,
   SUB_ID_USER_ENTERED_FORCE_2,
   SUB_ID_CALIBRATION_PART_CONTACT_FOUND
}CALIBRATION_ACE_SUB_ID;


#endif /* CALIBRATION_STRUCTURE_ACE_H_ */

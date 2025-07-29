/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE Display Manager data related structure definition.

***************************************************************************/
#ifndef DISP_MGR_STRUCT_ACE_H_
#define DISP_MGR_STRUCT_ACE_H_

// Supported display modes
typedef	enum
{
    MODE_UNKNOWN = 0,
    MODE_READ_ONLY,
    MODE_LOCKED,
    MODE_FULLY_FUNCTIONAL
}DISPLAY_MODE;

typedef enum
{
	TOKEN_RELEASED_BY_FIELDBUS=0,
	TOKEN_ACQUIRED_BY_FIELDBUS,
}FIELDBUS_TOKEN;

// definition for SUB-ID of memory block
typedef enum
{
	SUB_ID_DISPLAY_MODE = 1,
	SUB_ID_FIELDBUS_TOKEN_STATUS
}DISPLAY_MANAGEMENT_SUB_ID;


#endif /* DISP_MGR_STRUCT_ACE_H_ */


/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
This file includes configuration for system type.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 01/09/2023 - Initial version, configuration for system type
***************************************************************************/

#ifndef SYSTEM_TYPE_H_
#define SYSTEM_TYPE_H_

#include <iostream>

enum SYSTEM_TYPE
{
	SYSTEM_UNKNOWN = 0,
	//Add new system types here (after/below of SYSTEM_UNKNOWN)
    SYSTEM_ACE,
	SYSTEM_L20,
	//Add new system types here (before/above of SYSTEM_TYPE_ENUM_MAX)
	SYSTEM_TYPE_ENUM_MAX 
};

// Declaration of GetSystemTypeFromStorage function.
SYSTEM_TYPE GetSystemTypeFromStorage();

// Declaration of SetSystemType function.
bool SetSystemType(SYSTEM_TYPE enSystemType);

// Declaration of GetSystemTypeName function.
std::string GetSystemTypeName();

#endif //SYSTEM_TYPE_H_

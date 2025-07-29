/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Config Utility Version related implementation
 ***************************************************************************/

#ifndef CONFIG_UTILITY_VERSION_STRUCTURE_H_
#define CONFIG_UTILITY_VERSION_STRUCTURE_H_
#include <string.h>
#include "Common_Definitions.h"

// definition for SUB-ID of memory block
typedef enum
{
	CONFIG_UTILITY_VERSION_DATA = 1
	
}CONFIG_UTILITY_VERSION_SUB_ID;

constexpr int CONFIG_UTILITY_VERSION_SIZE = 20;

#endif //CONFIG_UTILITY_VERSION

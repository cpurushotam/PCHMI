/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------
This file includes ACE PRO platform system type implementation.

--------------------------- REVISION HISTORY -------------------------------
rev1: 01/09/2023 - Initial version, ACE PRO platform system type implementation

*****************************************************************************/

#include "AcePlatformInit.h"
#include "BIOConfig_Ace.h"

/******************************************************************************
* \brief - Load BIOConfiguration based on ACE-PRO platform.
* 
* \param - none
*
* \return - int value ERROR(-1) in case of error else return OK(0) for success
*
******************************************************************************/
int AcePlatformInit::AceInit()
{
	//By default set ERROR status
    int status = -1;
	
    ASCConfig::ptrASCParameters = &ASCAceProParam;

	return status;
}


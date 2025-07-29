/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
This file includes Get/Set System Type Implementation

--------------------------- REVISION HISTORY ------------------------------
rev1: 01/09/2023 - Initial version, Get/Set System Type Implementation

***************************************************************************/

//#include <fstream>
#include <map>
#include "SystemType.h"

/******************************************************************************
* \brief - Read the system type from persistent storage.
*
* \param - none
*
* \return - System Type
*
******************************************************************************/
SYSTEM_TYPE GetSystemTypeFromStorage()
{
//    SYSTEM_TYPE enSystemType = SYSTEM_UNKNOWN;
//    std::fstream SystemTypeFile;
//    SystemTypeFile.open(SYSTEM_TYPE_FILE_PATH_EMMC, std::ios::in);
//    if (SystemTypeFile.is_open())
//    {
//        std::string strSystemTypeValue = "";
//        getline(SystemTypeFile, strSystemTypeValue);
//        enSystemType = (SYSTEM_TYPE)atoi(strSystemTypeValue.c_str());
//        SystemTypeFile.close();
//    }

    SYSTEM_TYPE enSystemType = SYSTEM_ACE;
	
	if(enSystemType < SYSTEM_UNKNOWN || enSystemType >= SYSTEM_TYPE_ENUM_MAX)
	{
		enSystemType = SYSTEM_UNKNOWN;
	}
	return enSystemType;
}

/******************************************************************************
* \brief - Set/Save the System Type value in persistent storage.
*
* \param - enSystemType: System Type value
*
* \return - status: true/false
*
******************************************************************************/
bool SetSystemType(SYSTEM_TYPE enSystemType)
{
	bool bResult = false;
	if(enSystemType > SYSTEM_UNKNOWN && enSystemType < SYSTEM_TYPE_ENUM_MAX)
	{
//		std::fstream SystemTypeFile;
//        SystemTypeFile.open(SYSTEM_TYPE_FILE_PATH_EMMC, std::ios::out);
//		if (SystemTypeFile.is_open())
//		{
//			SystemTypeFile << enSystemType;
//			SystemTypeFile.close();
//			bResult = true;
//		}
	}
	else
	{
		// set system type as SYSTEM_UNKNOWN
		enSystemType = SYSTEM_UNKNOWN;
	}	
	return bResult;
}

/******************************************************************************
* \brief - Read the system type name
* \param - none
*
* \return - System Type Name
*
******************************************************************************/
std::string GetSystemTypeName()
{
	std::string strSystemType = "Unknown";
	SYSTEM_TYPE enSystemType = GetSystemTypeFromStorage();
	const std::map<SYSTEM_TYPE, std::string> mapOfSystemTypeEnumToName = 
	{
          { SYSTEM_ACE, "ACE"}
	};
	
	for (auto iterator = mapOfSystemTypeEnumToName.begin(); iterator != mapOfSystemTypeEnumToName.end(); ++iterator) 
	{
	   if(iterator->first == enSystemType) 
	   {
		   strSystemType = iterator->second;
		   break;
	   }
	}
	
	return strSystemType;
}

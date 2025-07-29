/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares alarm name API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 06/06/2024 -  Initial version.

***************************************************************************/

#include "AlarmNames.h"

size_t AlarmNames::static_log_id = 0;
/******************************************************************************//**
* \brief - Constructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
AlarmNames::AlarmNames()
{
	//enroll to use Logger functionality
	static_log_id = Logger::enroll(this);
}

/******************************************************************************//**
* \brief - Destructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
AlarmNames::~AlarmNames()
{

}

/**************************************************************************//**
*
* \brief   - Get the alarm sub-category for passed alarm ID
*
* \param   - AlarmID - Alarm Parameter Identifier that is used to get alarm 
* 			 sub-category
*
* \return  - Alarm sub category value for passed alarm ID. NONE_SUBCAT if alarm
*			 ID does not exist.
*
******************************************************************************/
ALARM_SUBCATEGORY AlarmNames::GetAlarmSubcategory(ALARM_IDS AlarmID)
{
	ALARM_SUBCATEGORY Value = NONE_SUBCAT;
    auto MapIterator = AlarmParamMap.find(AlarmID);
    if (MapIterator != AlarmParamMap.end())
    {
    	auto MapTuple = MapIterator->second;
        Value = std::get<ALARM_SUB_CATEGORY>(MapTuple);        
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Alarm ID not found");
    }
    
    return Value;
}

/**************************************************************************//**
*
* \brief   - Get the alarm error type for passed alarm ID
*
* \param   - AlarmID - Alarm Parameter Identifier that is used to get alarm 
* 			 error type
*
* \return  - Alarm error type value for passed alarm ID. Empty string if alarm
*			 ID does not exist.
*
******************************************************************************/
std::string AlarmNames::GetAlarmErrorType(ALARM_IDS AlarmID)
{
	std::string Value = "";
    auto MapIterator = AlarmParamMap.find(AlarmID);
    if (MapIterator != AlarmParamMap.end())
    {
    	auto MapTuple = MapIterator->second;
        Value = std::get<ALARM_ERROR_TYPE>(MapTuple);        
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Alarm ID not found");
    }
    
    return Value;
}

/**************************************************************************//**
*
* \brief   - Get the alarm description for passed alarm ID
*
* \param   - AlarmID - Alarm Parameter Identifier that is used to get alarm 
* 			 description
*
* \return  - Alarm description value for passed alarm ID. Empty string if alarm
*			 ID does not exist.
*
******************************************************************************/
std::string AlarmNames::GetAlarmDescription(ALARM_IDS AlarmID)
{
	std::string Value = "";
    auto MapIterator = AlarmParamMap.find(AlarmID);
    if (MapIterator != AlarmParamMap.end())
    {
    	auto MapTuple = MapIterator->second;
        Value = std::get<ALARM_DESC>(MapTuple);        
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Alarm ID not found");
    }
    
    return Value;
}

/**************************************************************************//**
*
* \brief   - Get the alarm reason for passed alarm ID
*
* \param   - AlarmID - Alarm Parameter Identifier that is used to get alarm 
* 			 reason
*
* \return  - Alarm description value for passed alarm ID. Empty string if alarm
*			 ID does not exist.
*
******************************************************************************/
std::string AlarmNames::GetAlarmReason(ALARM_IDS AlarmID)
{
	std::string Value = "";
    auto MapIterator = AlarmParamMap.find(AlarmID);
    if (MapIterator != AlarmParamMap.end())
    {
    	auto MapTuple = MapIterator->second;
        Value = std::get<ALARM_REASON>(MapTuple);        
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Alarm ID not found");
    }
    
    return Value;
}


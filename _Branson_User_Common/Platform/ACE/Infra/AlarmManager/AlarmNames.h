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
#ifndef ALARMNAME_H
#define ALARMNAME_H

#include "AlarmLogStructure.h"
#include "DataLogger.h"

class AlarmNames
{
public:
	AlarmNames();
	virtual ~AlarmNames();
	
	ALARM_SUBCATEGORY GetAlarmSubcategory(ALARM_IDS AlarmID);
	std::string GetAlarmErrorType(ALARM_IDS AlarmID);
	std::string GetAlarmDescription(ALARM_IDS AlarmID);
	std::string GetAlarmReason(ALARM_IDS AlarmID);

private: 
	static size_t static_log_id;
};

#endif //ALARMNAME_H

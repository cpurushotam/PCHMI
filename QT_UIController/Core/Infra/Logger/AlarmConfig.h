/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the alarm configuration header implementation

***************************************************************************/

#ifndef ALARM_CONFIG_H
#define ALARM_CONFIG_H

#include <stdint.h>
#include "AlarmLogStructure.h"
#include "DataInterface.h"

// Definition of AlarmConfig class
class AlarmConfig
{
public:
	AlarmConfig();
	virtual ~AlarmConfig();

	void ProcessAlarmConfigDataFromASC(const MEMORY_BLOCK *const source);
    void ProcessAlarmConfigUpdateStatusFromASC(const MEMORY_BLOCK *const source);
	void SendAlarmConfigReadRequestToASC(MEMORY_BLOCK * const destination);
	void SendAlarmConfigSaveRequestToASC(MEMORY_BLOCK * const destination);
	void SendAlarmConfigResetToDefaultRequestToASC(MEMORY_BLOCK * const destination);
	ALARM_CONFIG_UPDATE_STATUS GetAlarmConfigUpdateStatus();

    void PrintAlarmConfig();

    AlarmConfiguration GetAlarmConfiguration(void);
    bool IsAlarmConfigurationUpdated(void);
    void setResetToDefaultAlarmRequest(bool value);
    void ResetAlarmConfigurationUpdatedFlag();
    void saveAlarmConfigValues(AlarmConfiguration alarmConfiguration);

private:

	//Holds alarm config data.
	AlarmConfiguration m_AlarmConfig;
	
	//mutex for m_AlarmConfigData access
	pthread_mutex_t m_AlarmConfigDataMutex;

	//Alarm config update status to hold data received from ASC
	ALARM_CONFIG_UPDATE_STATUS m_AlarmConfigUpdateStatus;
	
    //Alarm config read request is sent to ASC when this flag is true
    bool m_SendAlarmConfigReadRequest;

    //Reset to default Alarm config request is sent to ASC when this flag is true
    bool m_SendResetToDefaultAlarmRequest;

    //Save Alarm config request is sent to ASC when this flag is true
    bool m_SendAlarmConfigSaveRequest;

    //flag is set to true when last AlarmConfiguration gets updated
    bool m_IsLastAlarmConfigurationUpdated;
};

#endif /* ALARM_CONFIG_H */

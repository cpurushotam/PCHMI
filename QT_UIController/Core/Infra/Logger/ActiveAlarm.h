/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the active alarm header implementation

***************************************************************************/

#ifndef ACTIVE_ALARM_H
#define ACTIVE_ALARM_H

#include <deque>
#include "AlarmLogStructure.h"
#include "DataInterface.h"
#include <stdint.h>

// Definition of ActiveAlarm class
class ActiveAlarm
{
public:
	ActiveAlarm();
	virtual ~ActiveAlarm();

	void ProcessActiveAlarmDataFromASC(const MEMORY_BLOCK *const source);
    void ProcessResetActiveAlarmDataFromASC(const MEMORY_BLOCK *const source);
    void ProcessEstopStatusDataFromASC(const MEMORY_BLOCK *const source);
    void ProcessEstopResetRespFromASC(const MEMORY_BLOCK *const source);
    void ProcessHornClampOnAlarmStatusFromASC(const MEMORY_BLOCK *const source);
	void SendActiveAlarmReadRequestToASC(MEMORY_BLOCK * const destination);
	void SendResetActiveAlarmRequestToASC(MEMORY_BLOCK * const destination);
	void SendResetAllActiveAlarmsRequestToASC(MEMORY_BLOCK * const destination);
	void SendEstopStatusReadRequestToASC(MEMORY_BLOCK * const destination);
	void SendEstopResetRequestToASC(MEMORY_BLOCK * const destination);
	void SetAlarmIDtoBeReset(ALARM_IDS id);
    void SetResetAllActiveAlarm();
    uint8_t GetAlarmResetStatus();
    uint8_t GetEstopStatus();
    uint8_t GetEstopResetResponse();
    void SetEstopResetRequest();
    uint8_t GetEstopResetStatus();
    uint8_t GetHornClampOnAlrmStatus();
    void PrintActiveAlarm();

    std::deque<ActiveAlarmEntry> GetActiveAlarmLogData(void);
    bool IsActiveAlarmLogUpdated(void);
    void UpdateActiveAlarmLogUpdatedFlag(bool Value);

private:
  
	//Holds active alarm data.
	std::deque<ActiveAlarmEntry> m_ActiveAlarmData;
	
	//mutex for m_ActiveAlarmData access
	pthread_mutex_t m_ActiveAlarmDataMutex;
	
    //flag is set to true when last active alarm gets updated
    bool m_IsLastActiveAlarmUpdated;
     
    //Holds ActiveAlarm sample number to read in case of active alarm transfer is in progress for active alarm data
    int m_ActiveAlarmSampleNumberToRead;
    
    //Active Alarm read request is sent to ASC when this flag is true
    bool m_SendActiveAlarmReadRequest;

    //Reset Active Alarm request is sent to ASC when this flag is true
    bool m_SendResetActiveAlarmRequest;

    //Reset all Active Alarm request is sent to ASC when this flag is true
    bool m_SendResetAllActiveAlarmRequest;
    
    //Estop status read request is sent to ASC when this flag is true
    bool m_SendEstopStatusReadRequest;
    
    //Reset Estop request is sent to ASC when this flag is true
    bool m_SendResetEstopRequest;

    //Holds Alarm ID to be reset  
    ALARM_IDS m_ResetActiveAlarmID;
    
    //Holds the Estop status  
    uint8_t m_EstopStatus;
        
    //Holds the Alarm reset status  
    uint8_t m_AlarmResetStatus;

    //Holds the Estop reset response  
    uint8_t m_EstopResetResponse;

    //Holds the horn clamp on alarm status
    uint8_t m_HornClampOnAlrmStatus;
};

#endif /* ACTIVE_ALARM_H */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE alarm manager related implementation
 
***************************************************************************/

#ifndef ALARM_MANAGER_ACE_H_
#define ALARM_MANAGER_ACE_H_

#include "AlarmManager.h"
#include "AlarmLog.h"
#include "ActiveAlarm.h"
#include "AlarmConfig.h"

class AlarmMgrACE : public AlarmMgr
{
public:
	AlarmMgrACE();
	virtual ~AlarmMgrACE();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
    AlarmConfiguration GetAlarmConfiguration(void);
    void setResetToDefaultAlarmRequest(bool Value);
    void ResetAlarmConfigurationUpdatedFlag ();
    void saveAlarmConfigValues(AlarmConfiguration alarmConfiguration);
    bool IsAlarmConfigurationUpdated(void);

    std::deque<AlarmLogEntry> GetHistoricalAlarmLogData(void);
    bool IsAlarmLogUpdated(void);
    void UpdateAlarmLogUpdatedFlag(bool Value);

    std::deque<ActiveAlarmEntry> GetActiveAlarmLogData(void);
    bool IsActiveAlarmLogUpdated(void);
    void UpdateActiveAlarmLogUpdatedFlag(bool Value);
    void SetAlarmIDtoBeReset(ALARM_IDS Id);
    void SetResetAllActiveAlarm(void);

    uint8_t GetEstopStatus();
    void SetEstopResetRequest();
    uint8_t GetEstopResetResponse();
    uint8_t GetHornClampOnAlrmStatus();

    void SetAddAlarmNotesFlag(int index, std::string Notes);

private:

    static size_t static_log_id;

	std::unique_ptr<AlarmLog> m_ptrAlarmLogObj;		
	std::unique_ptr<ActiveAlarm> m_ptrActiveAlarmObj;
	std::unique_ptr<AlarmConfig> m_ptrAlarmConfigObj;
};

#endif /* ALARM_MANAGER_ACE_H_ */

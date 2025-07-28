/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the alarm log header implementation

***************************************************************************/

#ifndef ALARMLOG_H
#define ALARMLOG_H

#include <deque>
#include "AlarmLogStructure.h"
#include "DataInterface.h"

// Definition of AlarmLog class
class AlarmLog
{
public:
	AlarmLog();
	virtual ~AlarmLog();

	void ProcessLastAlarmLogDataFromASC(const MEMORY_BLOCK *const source);
	void ProcessHistoricalAlarmLogDataFromASC(const MEMORY_BLOCK *const source);
	void ProcessAlarmNotesUpdateStatusFromASC(const MEMORY_BLOCK *const source);
	void SendHistoricalAlarmLogReadRequestToASC(MEMORY_BLOCK * const destination);
    void SendAddAlarmNotesRequestToASC(MEMORY_BLOCK * const destination);
    void ProcessHistoricalAlarmLogDataFromASConDatetimeFormatChg();

	void PrintHistoricalAlarmLog();
    std::deque<AlarmLogEntry> GetHistoricalAlarmLogData(void);
    bool IsAlarmLogUpdated(void);
    void UpdateAlarmLogUpdatedFlag(bool Value);
    void SetAddAlarmNotesFlag(int index ,std::string AlarmNotes);

private:
  
	//Holds historical alarm log data.
	std::deque<AlarmLogEntry> m_HistoricalAlarmLogData;
	
   //mutex for m_HistoricalAlarmLogData access
	pthread_mutex_t m_HistoricalAlarmLogDataMutex;
	
    //flag is set to true when last alarm log gets updated
     bool m_IsLastAlarmLogUpdated;
     
    //Holds AlarmLog sample number to read in case of alarm log transfer is in progress for historical alarm log data
    int m_AlarmLogHistorySampleNumberToRead;
    
    //Historical Alarm Log read request is sent to ASC when this flag is true
    bool m_SendHistoricalAlarmLogReadRequest;

    //Update alarm note request is send to ASC when this flag is true
    bool m_SendUpdateAlarmNotesRequest;

    //Holds the alarm log index to be sent to ASC
    int m_AlarmLogIndex;

    //Holds the alarm notes to be sent to ASC
    char m_UpdateAlarmNotes[ALARM_NOTES_SIZE];

};

#endif /* ALARMLOG_H */

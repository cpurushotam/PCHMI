/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the event log header implementation

***************************************************************************/

#ifndef EVENTLOG_H_
#define EVENTLOG_H_

#include <deque>
#include "EventLogStructure.h"
#include "DataInterface.h"

// Definition of EventLog class
class EventLog : public DataInterface
{
public:
	EventLog();
	virtual ~EventLog();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    bool GetIsLastEventLogUpdated(void);
    std::deque<EventLogEntry> GetHistoricalEventLogData();
    void SetIsLastEventLogTableUpdated(bool value);

private:
    void processLastEventLogDataFromASC(const MEMORY_BLOCK *const source);
    void processHistoricalEventLogDataFromASC(const MEMORY_BLOCK *const source);
    void sendHistoricalEventLogReadRequestToASC(MEMORY_BLOCK * const destination);
    void processEventLogDataFromASConDateTimeFormatChange();

    void printHistoricalEventLog();

     static size_t static_log_id;
    
	//Holds historical event log data.
	std::deque<EventLogEntry> m_HistoricalEventLogData;
	
    //mutex for m_HistoricalEventLogData access
    pthread_mutex_t m_HistoricalEventLogDataMutex;

    //flag is set to true when last event log gets updated
     bool m_IsLastEventLogUpdated;
     
    //Holds EventLog sample number to read in case of event log transfer is in progress for historical event log data
    int m_EventLogHistorySampleNumberToRead;
    
    //Historical Event Log read request is sent to ASC when this flag is true
    bool m_SendHistoricalEventLogReadRequest;
	
};

#endif /* EVENTLOG_H_ */

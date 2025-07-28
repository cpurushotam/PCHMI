/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld result related implementation

***************************************************************************/

#ifndef WELD_RESULT_ACE_H_
#define WELD_RESULT_ACE_H_

#include <deque>
#include "WeldResult.h"
#include "WeldResultStructuresAce.h"

class WeldResultACE : public WeldResult
{
public:
	WeldResultACE();
    virtual ~WeldResultACE();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateSearchByCycleNumReadRequestToASC(int CycleNumber);
    std::deque<WeldResultACEStruct> GetHistoricalWeldResultData();
    std::deque<WeldResultACEStruct> GetCycleNumWeldResultData();
    bool GetIsLastWeldResultUpdated(void);
    void SetIsLastWeldResultUpdated(bool Value);
    int GetHistoricalWeldResultDataSize(void);
    int GetSearchByCycleNumWeldResultDataSize(void);

   
private:
    //Dummy Implementation for HMI side.
    bool ReadRequestedWeldResultHistory() {return false;}
    static size_t static_log_id;

    //Holds historical weld result data.
    std::deque<WeldResultACEStruct> m_HistoricalWeldResultData;
    
    //Holds search by cycle number weld result data.
    std::deque<WeldResultACEStruct> m_SearchByCycleNumWeldResultData;
    
     int m_CycleNumToSearch;
     
     //Holds WeldResult sample number to read in case of weld result transfer is in progress for search by cycle number operation
     int m_WeldResultSampleNumberToRead;
     
     //Holds WeldResult sample number to read in case of weld result transfer is in progress for historical weld result data
     int m_WeldResultHistorySampleNumberToRead;
     
     //This flag gets set to true when user requests to search a new/different weld cycle number data
     bool m_RequestNewCycleNumberData;

     //mutex for m_HistoricalWeldResultData access
     pthread_mutex_t m_HistoricalWeldResultDataMutex;
     
     //mutex for m_SearchByCycleNumWeldResultData access
     pthread_mutex_t m_SearchByCycleNumWeldResultDataMutex;

     //flag is set to true when last weld result gets updated
     bool m_IsLastWeldResultUpdated;
    
     //Historical Weld Result read request is sent to ASC when this flag is true
     bool m_SendHistoricalWeldResultReadRequest;
     
     //Search by cycle number Weld Result read request is sent to ASC when this flag is true
     bool m_SendSearchByCycleNumWeldResultReadRequest;

    void sendHistoricalWeldResultReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendSearchByCycleNumWeldResultReadRequestToASC(MEMORY_BLOCK * const destination);
    void processLastWeldResultDataFromASC(const MEMORY_BLOCK *const source);
    void processHistoricalWeldResultDataFromASC(const MEMORY_BLOCK *const source);
    void processSearchByCycleNumWeldResultDataFromASC(const MEMORY_BLOCK *const source);
    void processSynchHistoricalWeldResultDataFromASC(const MEMORY_BLOCK *const source);
    void processSynchHistoricalWeldResultDataFromASConDateTimeFormatChange();

    void printHistoricalWeldResult();
    void printLastWeldResult();
    void printSearchByCycleNumberdWeldResult();
};

#endif /* WELD_RESULT_ACE_H_ */

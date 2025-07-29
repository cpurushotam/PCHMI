/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE Horn Scan Result related implementation

***************************************************************************/

#ifndef HORN_SCAN_RESULT_H_
#define HORN_SCAN_RESULT_H_

#include <deque>
#include "DataInterface.h"
#include "HornScanResultStructure.h"

class HornScanResult : public DataInterface
{
public:
    HornScanResult();
    virtual ~HornScanResult();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateScanRunOperation();
    void AbortScanRunOperation();
    std::deque<HornScanResultstruct> GetHistoricalHornScanResultData();
    bool GetIsLastHornScanResultUpdated();
    void SetIsLastHornScanResultUpdated(bool Value);
private:
    static size_t static_log_id;

    //Holds historical HornScan result data.
    std::deque<HornScanResultstruct> m_HistoricalHornScanResultData;
     
     //Holds HornScanResult sample number to read in case of horn scan result transfer is in progress for historical horn scan result data
     int m_HornScanResultHistorySampleNumberToRead;

     //flag is set to true when user click on start horn scan button
     bool m_StartHornScanOperation;

     //flag is set to true when user click on abort horn scan button
     bool m_AbortHornScanOperation;

     //flag is set to true when last HornScan result gets updated
     bool m_IsLastHornScanResultUpdated;
    
     //Historical Horn Scan Result read request is sent to ASC when this flag is true
     bool m_SendHistoricalHornScanResultReadRequest;

     //mutex for m_HistoricalHornScanResultData access
     pthread_mutex_t m_HistoricalHornScanResultDataMutex;

    void sendHistoricalHornScanResultReadRequestToASC(MEMORY_BLOCK * const destination);
    void processHistoricalHornScanResultDataFromASC(const MEMORY_BLOCK *const source);
    void SendStartHornScanOperationToASC(MEMORY_BLOCK * const destination);
    void sendAbortHornScanOperationToASC(MEMORY_BLOCK * const destination);
    void processLastHornScanResultDataFromASC(const MEMORY_BLOCK *const source);
    void processHornScanResultDataFromASConDateTimeFormatChange();

    void printHistoricalHornScanResult();
    void printLastHornScanResult();
};

#endif /* HORN_SCAN_RESULT_H_ */

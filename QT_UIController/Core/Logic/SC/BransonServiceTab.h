/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Branson Service  Tab related implementation
 
***************************************************************************/

#ifndef BransonServiceTab_H_
#define BransonServiceTab_H_

#include <deque>
#include "DataInterface.h"
#include "SystemConfigBransonServiceStructure.h"

class BransonServiceTab : public DataInterface
{ 
public:
	
    BransonServiceTab();
    
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void initiateFactoryResetRequest();
    void initiateDBDeleteRequest();
    void initiateCopyDBFilesToUSBRequest();
    void initiateSystemCleanedRequest();

    void getServiceNoteStructFromHMI(std::string &serviceNote);
    int getEmmcMemoryUsage();

    std::deque<BransonServiceTabStructure> GetServiceLogs();
    BRANSON_SERVICE_REQUESTS_RESPONSE_CODES GetBransonServiceRequestResponsecodes();

    void GetOldBoardNewBoardName(std::string &oldboard, std::string &newboard,  std::string &boardName);

    bool GetIsDataUpdated();
    void SetDataUpdatedFlag();

    bool GetIsEmmcMemoryUsageUpdated();
    void SetEmmcMemoryUsageFlag();

    bool GetBransonServiceStatusUpdate();
    void SetBransonServiceStatusUpdate();

private:

    void sendFactoryResetRequestFromHMI(MEMORY_BLOCK * const destination);
    void sendDeleteDBRequestFromHMI(MEMORY_BLOCK * const destination);
    void sendCopyDBtoUSBRequestFromHMI(MEMORY_BLOCK * const destination);
    void sendBoardReplacedRequestFromHMI(MEMORY_BLOCK * const destination);
    void sendSystemCleanRequestFromHMI(MEMORY_BLOCK * const destination);
    void sendAddNoteRequestFromHMI(MEMORY_BLOCK * const destination);

    void sendHistoricalServiceNoteReadReq(MEMORY_BLOCK * const destination);
    void processHistoricalServiceLogDataFromASC(const MEMORY_BLOCK *const source);

    void processEmmcUsageDeatilsResponse(const MEMORY_BLOCK *const source);
    void processBransonServiceRequestResponse(const MEMORY_BLOCK *const source);
    void printHistoricalServiceLog();
    void processServiceLogDataFromASConDateTimeFormatChange();

    bool m_FactoryResetRequest;
    bool m_DeleteDBRequest;
    bool m_DbCopyEmmctoUSB;
    bool m_BoardReplaced;
    bool m_SystemCleaned;
    bool m_AddNoteRequest;

    int m_EmmcMemoryUsage;

    bool m_SendServiceNotesReadReq;
    //Holds Service log sample number to read in case of event log transfer is in progress for historical Service log data
    int m_ServiceHistorySampleNumberToRead;
    bool m_IsServiceLogDataUpdated;
    bool m_IsEmmcMemoryUsageFlag;
    bool m_IsBransonServiceStatusUpdated;

    std::deque<BransonServiceTabStructure> m_BransonServiceLogTabData;
    BRANSON_SERVICE_REQUESTS_RESPONSE_CODES m_ServiceResponse;

    char m_ServiceNote[SERVICENOTES_SIZE];

    char m_oldBoardRevNo[BOARD_NAME_SIZE];
    char m_newBoardRevNo[BOARD_NAME_SIZE];
    char m_boardName[BOARD_NAME_SIZE];

    size_t m_LogID;
};

#endif /* BransonServiceTab_H_ */

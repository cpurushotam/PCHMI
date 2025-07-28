/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Software Upgrade related implementation
 
***************************************************************************/

#ifndef SOFTWARE_UPGRADE_H_
#define SOFTWARE_UPGRADE_H_

#include <queue>
#include "DataInterface.h"
#include "SoftwareUpgradeStructure.h"

class SoftwareUpgrade : public DataInterface
{ 
public:
	
    SoftwareUpgrade();
    virtual ~SoftwareUpgrade();
    
    void InitiateSoftwareUpgradeRequest(std::string SCFileName, std::string ACFileName, std::string HMIFileName);
    void InitiateSoftwareUpgradeReadUSBRequest();

    bool GetReadUSBStatus();
    std::queue<SoftwareUpgradeStruct> GetReadUSBData();

    bool GetSoftwareUpgradeStatus();
    SOFTWARE_UPGRADE_ERROR_CODES GetSoftwareUpgradeErrorCode();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //to store list of USB content executable files.
    std::queue<SoftwareUpgradeStruct> m_SoftwareUpgradeData;


    size_t m_SizeOfVectorStrings;

    //Stores the update/reset to default response code coming from ASC
    SOFTWARE_UPGRADE_ERROR_CODES m_SoftwareUpgradeResult;

    bool m_SendSoftwareUpgradeReadUSBRequest;
    bool m_SendSoftwareUpgradeRequest;
    bool m_isSoftwareUpgradeDataUpdated;
    bool m_isUSBRead;
    void sendSoftwareUpgradeReadUSBRequest(MEMORY_BLOCK * const destination);
    void sendSoftwareUpgradeRequest(MEMORY_BLOCK * const destination);
    void processSoftwareUpgradeReadUSBResponse(const MEMORY_BLOCK *const source);
    void processSoftwareUpgradeResponse(const MEMORY_BLOCK *const source);
	
    void ShowSoftwareUpgradeList();

};

#endif /* SOFTWARE_UPGRADE_H_ */

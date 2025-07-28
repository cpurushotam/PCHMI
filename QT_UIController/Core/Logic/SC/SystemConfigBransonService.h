/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the System Configuration Branson Service related implementation
 
***************************************************************************/

#ifndef SYSTEMCONFIGBRANSONSERVICE_H_
#define SYSTEMCONFIGBRANSONSERVICE_H_

#include "DataInterface.h"
#include "SystemConfigBransonServiceStructure.h"

class SystemConfigBransonService : public DataInterface
{ 
public:
	
    SystemConfigBransonService();
    virtual ~SystemConfigBransonService();
    
    void InitiateSystemConfigBransonServiceUpdateRequest(SystemConfigBransonServiceStruct SystemConfigBransonServiceData);

    bool GetSystemConfigBransonServiceUpdateStatus();

    SystemConfigBransonServiceStruct GetSystemConfigBransonServiceData();
    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES GetSystemConfigBransonServiceUpdatedErrorCode();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //cached Branson system configuration data.
    SystemConfigBransonServiceStruct m_BransonServiceData;
    //Stores the update response code coming from ASC
    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES m_SystemConfigBransonServiceUpdateResult;

    bool m_SendSystemConfigBransonServiceReadRequest;
    bool m_SendSystemConfigBransonServiceUpdateRequest;
    bool m_isSystemConfigBransonServiceUpdated;

    void sendSystemConfigBransonServiceReadRequest(MEMORY_BLOCK * const destination);
    void sendSystemConfigBransonServiceUpdateRequest(MEMORY_BLOCK * const destination);
    void processSystemConfigBransonServiceReadResponse(const MEMORY_BLOCK *const source);
    void processSystemConfigBransonServiceUpdateResponse(const MEMORY_BLOCK *const source);
	
    void ShowSystemConfigBransonService();

};

#endif /* SYSTEMCONFIGBRANSONSERVICE_H_ */

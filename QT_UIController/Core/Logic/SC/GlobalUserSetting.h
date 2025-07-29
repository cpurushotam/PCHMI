/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Global User setting related implementation
 
***************************************************************************/

#ifndef GLOBALUSERSETTING_H_
#define GLOBALUSERSETTING_H_

#include "DataInterface.h"
#include "GlobalUserSettingStructure.h"

class GlobalUserSetting : public DataInterface
{ 
public:
	
	GlobalUserSetting();
	virtual ~GlobalUserSetting();
    
    void InitiateGlobalUserSettingsUpdateRequest(GlobalUserSettingStruct GlobalUserSettingData);
    void InitiateGlobalUserSettingsResetRequest();

    bool GetIsGlobalUserSettingDataUpdated();
    bool GetIsGlobalUserSettingDataRead();
    void SetGlobalUserSettingDataRead();
    bool GetAutoLoginStatus();
    uint32_t GetIdleTimeLoggOffTime();
    std::string GetAutoLoginUserName();
    GlobalUserSettingStruct GetGlobalUserSettingData();
    UPDATE_GLOBAL_USER_SETTING_ERROR_CODES GetGlobalUserSettigsDataUpdatedErrorCode();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //cached global user settings data.
    GlobalUserSettingStruct m_GlobalUserData;
    //Stores the update/reset to default response code coming from ASC
    UPDATE_GLOBAL_USER_SETTING_ERROR_CODES m_GlobalUserDataUpdateResult;

    bool m_SendGlobalUserSettigsReadRequest;
    bool m_SendGlobalUserSettigsUdateRequest;
    bool m_SendGlobalUserSettigsResetRequest;

    bool m_isGlobalUserSettigsDataUpdated;
    bool m_isGlobalUserSettigsDataReadOnPowerUp;


    void sendGlobalUserSettingsReadRequest(MEMORY_BLOCK * const destination);
    void sendGlobalUserSettingsUpdateRequest(MEMORY_BLOCK * const destination);
    void sendGlobalUserSettingsResetRequest(MEMORY_BLOCK * const destination);
    void processGlobalUserSettingsReadResponse(const MEMORY_BLOCK *const source);
    void processGlobalUserSettingsUpdateResponse(const MEMORY_BLOCK *const source);
	
	void ShowGlobalUserSetting();

};

#endif /* GLOBALUSERSETTING_H_ */

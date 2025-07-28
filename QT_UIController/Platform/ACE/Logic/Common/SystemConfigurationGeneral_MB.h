/**************************************************************************

            Copyright (c) Branson Ultrasonics Corporation, 1996-2023

            This program is the property of Branson Ultrasonics Corporation
            Copying of this software is expressly forbidden, without the prior
            written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

            This file contains the SystemConfigurationGeneral screen related information

***************************************************************************/

#ifndef SYSTEMCONFIGURATIONGENERAL_MB_H_
#define SYSTEMCONFIGURATIONGENERAL_MB_H_

#include "DataInterface.h"
#include "SysConfgGenStructureAce.h"

/* Definition of SystemConfigurationGeneral_MB class - To Get/Set SystemConfigurationGeneral screen related information */
class SystemConfigurationGeneral_MB:public DataInterface{

public:

	SystemConfigurationGeneral_MB();
	virtual ~SystemConfigurationGeneral_MB();

    /* Read  SystemConfigurationGeneral screen data MB from DB */
    int GetData(MEMORY_BLOCK * const destination) override;

    /* Write SystemConfigurationGeneral screen data MB into DB */
    int SetData(const MEMORY_BLOCK *const source) override;

    /*Function to update values from HMI are updated to ASC */
    void setSystemDetailsFromHMI(SystemConfigGeneralStruct Local_SystemConfigGeneralStruct);

    /*Function to Get data from SystemConfigurationGeneral_MB to SystemGeneral Class */
    SystemConfigGeneralStruct GetSystemDetailsFromASC();

    /* To know if MemoryBlock data is updated or not*/
    bool IsDataUpdated();

    /*To set value of isDataUpdated if data is changed from HMI. */
    void SetIsDataUpdated(bool isUpdate);
    
    UNIT GetSystemUnitType();
    bool GetAuthorityCheck();

    bool getDataUpdatedFlag();
    void setDataUpdatedFlag();

    bool getIsDataAvailableFlag();
    void setIsDataAvailableFlag();

    bool getSysGeneralDataChangeFlag();
    void setSysGeneralDataChangeFlag();

    /* Send key data to ASC for verification */
    void SetKeyVerifyRequest(std::string key);

    /* Get the system config update or Key process status.*/
    int GetSystConfigUpdateProcessStatus();

    /* Get the system key process status */
    bool IsBransonServiceUserLoggedIn();

    /* Set the ResetToDefault system config Request from HMI */
    void SetSystConfigResetToDefaultRequest();

    void PrintSysConfigData();

    int GetAuthortiyCheckStatus();
    bool GetKeyVerifyDataReadStatus();
    void ResetKeyVerifyDataReadStatus();
    void ResetBrsnSrvcKeyVerifyStatus();

private:
    /* Structure to updated data from ASC and HMI */
    SystemConfigGeneralStruct m_SystemConfigGenScreenData;

    /* flag is set to true when data on the screen needs to be updated. */
    bool m_IsDataUpdated;

    bool m_DataChanged;

    bool m_ConfigGeneralDataUpdated;
    //Key verify request is sent to ASC when this flag is true
    bool m_SendKeyVerifyRequest;

	//Holds System configuration update data received from ASC
	int m_SysConfigUpdateProcessStatus;

	//Flag is set to true when key entered is successfully verified.
	bool m_IsBransonServiceUserLoggedIn;
    bool m_IsKeyVerifyDataRead;

    //Flag is used by HMI when data is avialble from ASC.
    bool m_IsDataAvailable;

	//Reset to default system configuration request is sent to ASC when this flag is true
    bool m_SendResetToDefaultRequest;

    bool m_InitiateSaveRequest;
    bool m_InitiateSysConfigGenrealReadReq;


    bool m_ResetBransonServiceKey;

    void SendSysConfigGeneralReadRequestToASC(MEMORY_BLOCK *const destination);

    void SendSysConfigGeneralResetBrsnSrvcKey(MEMORY_BLOCK *const destination);

};

#endif /* SYSTEMCONFIGURATIONGENERAL_MB_H_ */

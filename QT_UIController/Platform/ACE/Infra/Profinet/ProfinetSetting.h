/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

This file contains the Profinet Settings related implementation

***************************************************************************/

#ifndef PROFINET_NETWORK_SETTINGS_H_
#define PROFINET_NETWORK_SETTINGS_H_

#include <vector>
#include <memory>
#include "DataInterface.h"
#include "Common_Definitions.h"
#include "ProfinetStructure.h"

class ProfinetSetting : public DataInterface
{
public:
	ProfinetSetting();
	virtual ~ProfinetSetting();
	
    static size_t static_log_id;
    INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;
    int  GetData(MEMORY_BLOCK * const destination) override;
    int  SetData(const MEMORY_BLOCK *const source) override;
    void InitiateProfinetSettingsUpdateRequest(ProfinetSettingsStruct ProfinetSettingData);	
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;};

    void InitiateRestToDefaultRequest();
    bool GetIsProfinetDataAvailable();
    void SetIsProfinetDataAvailable();
    ProfinetSettingsStruct GetProfinetSettingsStruct();

private:
    //structure variable to store Profinet Settings
	ProfinetSettingsStruct m_ProfinetSettingsData;
	bool m_InitiateProfinetSettingsDataReadRequest;
	bool m_InitiateProfinetSettingsDataSaveRequest;
	bool m_InitiateProfinetSettingsDataToDefault;
	void SendProfinetSettingsReadRequestToASC(MEMORY_BLOCK * const destination);
	void ProcessProfinetSettingsReadFromASC(const MEMORY_BLOCK *const source);
	void ProfinetDataSaveRequestToASC(MEMORY_BLOCK * const destination);
	void RequestASCToResetProfinetSettingsToDefault(MEMORY_BLOCK *const destination);

    bool m_IsProfinetDataUpdated;
	
};

#endif /* PROFINET_NETWORK_SETTINGS_H_ */

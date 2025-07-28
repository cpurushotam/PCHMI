/**************************************************************************
 
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
 
--------------------------- MODULE DESCRIPTION ----------------------------
 
This file contains the Stream Data related implementation
 
***************************************************************************/
#ifndef QT_UICONTROLLER_PLATFORM_ACE_INFRA_USBSTREAMING_USBSTREAMING_H_
#define QT_UICONTROLLER_PLATFORM_ACE_INFRA_USBSTREAMING_USBSTREAMING_H_

#include <vector>
#include <memory>
#include "DataInterface.h"
#include "Common_Definitions.h"
#include "USBStreamStructure.h"

class USBStreaming : public DataInterface
{
public:
	USBStreaming();
	virtual ~USBStreaming();
 
    static size_t static_log_id;
 
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
    void InitiateStreamDataSaveRequest(USBStreamStruct StreamDataToSave);
 
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;};
 
private:
 
    //structure variable to store streamdata
	USBStreamStruct m_USBStreamData;
 
	//Latest streaming data read request is sent to ASC when this flag is true
	bool m_InitiateStreamDataReadRequest;
	bool m_InitiateStreamDataSaveRequest;
 
	//Send read stream data request to ASC
	void sendStreamDataReadRequestToASC(MEMORY_BLOCK * const destination);
	//Send save stream data request to ASC
	void sendStreamDataSaveRequestToASC(MEMORY_BLOCK * const destination);
	//Process read stream data request to ASC
	void processStreamDataReadRequestFromASC(const MEMORY_BLOCK *const source);
};

#endif /* QT_UICONTROLLER_PLATFORM_ACE_INFRA_USBSTREAMING_USBSTREAMING_H_ */

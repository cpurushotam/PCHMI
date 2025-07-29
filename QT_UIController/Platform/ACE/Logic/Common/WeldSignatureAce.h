/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld signature related implementation

***************************************************************************/

#ifndef WELD_SIGNATURE_ACE_H_
#define WELD_SIGNATURE_ACE_H_

#include <deque>

#include "WeldSignature.h"
#include "WeldSignatureStructuresAce.h"

class WeldSignatureACE : public WeldSignature
{
public:
	WeldSignatureACE();
    virtual ~WeldSignatureACE();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateWeldSignatureReadRequest(int WeldResultIndexNumber);
	void InitiateAutoSaveGraphUpdateRequest(bool Value);
	bool InitiateGraphSamplingIntervalUpdateRequest(uint32_t Value);
 	void ShowRequestedWeldSignatureDataFromCache();

    std::deque<WeldSignatureACEStruct> GetRequestedWeldSignatureData(void);
    bool GetIsCompleteWeldSignatureReceived(void);
    void SetIsCompleteWeldSignatureReceived(bool Value);
    bool GetIsAutoSaveGraphEnabled();
    int  GetGraphSamplingInterval();

private:
 	//Dummy Implementation for HMI side.
 	bool ReadRequestedWeldSignature() {return false;}
    static size_t static_log_id;

    //Holds Requested Weld Signature Data
    std::deque<WeldSignatureACEStruct> m_RequestedWeldSignatureData;

     //Requested Weld signature read request is sent to ASC when this flag is true
     bool m_SendRequestedWeldSignatureReadRequest;

     //This flag gets set to true when user requests to read a new/different weld signature data
     bool m_RequestNewWeldSignatureData;

     //Holds WeldResultIndex number for which user has requested weld signature to read
     int m_WeldResultIndexNumberToRead;

     //Holds WeldSignature sample number to read in case of weld signature transfer is in progress
     int m_WeldSignatureSampleNumberToRead;

    //Weld signature configuration (AutoSaveGraph, GraphSamplingInterval) read request is sent to ASC when this flag is true
    bool m_SendWeldSignatureConfigReadRequest;
	
	//Cached value of auto save graph option that decides whether to save the weld graph in database or not
	bool m_bIsAutoSaveGraphEnabled;
	
	//Cached value of weld graph sampling interval value in milliseconds
	uint32_t m_GraphSamplingInterval;
	
	//AutoSaveGraph update request is sent to ASC when this flag is true
	bool m_InitiateAutoSaveGraphUpdateRequest;
	
	//GraphSamplingInterval update request is sent to ASC when this flag is true
	bool m_InitiateGraphSamplingIntervalUpdateRequest;

    bool m_IsCompleteWeldSignatureReceived;

	void sendRequestedWeldSignatureReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendWeldSignatureConfigReadRequestToASC(MEMORY_BLOCK * const destination);
	void sendAutoSaveGraphUpdateRequestToASC(MEMORY_BLOCK * const destination);
	void sendGraphSamplingIntervalUpdateRequestToASC(MEMORY_BLOCK * const destination);
	void procesRequestedWeldSignatureDataFromASC(const MEMORY_BLOCK *const source);
    void processWeldSignatureConfigDataFromASC(const MEMORY_BLOCK *const source);
};

#endif /* WELD_SIGNATURE_ACE_H_ */

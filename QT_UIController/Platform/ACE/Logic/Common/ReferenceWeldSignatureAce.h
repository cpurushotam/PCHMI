/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Reference Weld SignatureAce related implementation

 ***************************************************************************/

#ifndef REFERENCE_WELD_SIGNATURE_ACE_H_
#define REFERENCE_WELD_SIGNATURE_ACE_H_

#include <queue>
#include <deque>
#include <pthread.h>

#include "WeldSignatureStructuresAce.h"
#include "WeldResultStructuresAce.h"
#include "DataInterface.h"

class ReferenceWeldSignature :public DataInterface
{
public:	
	ReferenceWeldSignature();

	int GetData(MEMORY_BLOCK * const destination) override;
	int SetData(const MEMORY_BLOCK *const source) override;

    void SetReferenceWeldSignatureRequestFromHMI(int WeldResultIndexNumber);
    void InitiateReferenceWeldSignatureNameUpdateRequest(int WeldResultIndexNumber, std::string Name );
    void InitiateReplaceOldRefGraphWithNewRefGraphRequest(int OldWeldResultIndexNumber, int NewWeldResultIndexNumber);

    std::deque<ReferenceGraphStruct> GetReferenceGraphStruct();
    std::deque<WeldSignatureACEStruct> GetRequestedReferenceWeldSignatureData();
    std::queue<std::deque<WeldSignatureACEStruct>> GetAvailableReferenceWeldData();

    void SetIsReferenceGraphDetailsAvailable();
    bool GetIsReferenceGraphDetailsAvailable();
    void SetReplaceRefGraphStatus();
    bool GetRefGraphStatusFromASC();

private:

    void sendRequestedReferenceWeldSignatureReadRequestToASC(MEMORY_BLOCK * const destination);
    void procesRequestedReferenceWeldSignatureDataFromASC(const MEMORY_BLOCK *const source);

    void sendReferenceWeldResultReadRequestToASC(MEMORY_BLOCK * const destination);
    void processRefereceWeldResultDataFromASC(const MEMORY_BLOCK *const source);

    void sendReferenceGraphReadRequestToASC(MEMORY_BLOCK * const destination);
    void processReferenceGraphDataFromASC(const MEMORY_BLOCK *const source);

    void sendReferenceGraphNameUpdateRequestToASC(MEMORY_BLOCK * const destination);
    void sendReferenceGraphReplaceRequestToASC(MEMORY_BLOCK * const destination);
    void processReplaceReferenceGraphStatusFromASC(const MEMORY_BLOCK *const source);

    void sendReferenceGraphReadRequestToASConPowerUp(MEMORY_BLOCK * const destination);

    void printSearchByCycleNumberdWeldResult();
    void printReferenceGraphDetails();
    void ShowRequestedWeldSignatureDataFromCache();

    static size_t static_log_id;

    bool m_IsCompleteRefWeldSignatureReceived;

    std::queue<std::deque<WeldSignatureACEStruct>> m_AvailableReferenceWeldData;

    //Holds Requested ReferenceGraphData Data
    std::deque<ReferenceGraphStruct> m_ReferenceGraphStructData;
    //Holds Requested Reference Weld Signature Data
    std::deque<WeldSignatureACEStruct> m_RequestedReferenceWeldSignatureData;
    //Holds search by Reference weld result data.
    std::deque<WeldResultACEStruct> m_RequestedReferenceWeldResultData;

    //Reference WeldResult Index of the selected graph whos name to be updated.
    int m_ReferenceGraphIndexToUpdate;
    //Reference WeldResult Index of the selected graph which is to be replaced.
    int m_ReferenceGraphOldWeldResultToUpdate;
    //Reference WeldResult Index of the new selected graph .
    int m_ReferenceGraphNewWeldResultToUpdate;
    //Holds the reference graph Name to be sent to ASC
    char m_UpdateRefGraphName[REF_GRAPH_NAME_SIZE];
    //Holds the flag status to update ASC to change name.
    bool m_SendUpdateRefGraphNameRequest;
    //Holds the flag status to Replace Graph, ASC to change name.
    bool m_SendReplaceRefGraphRequest;
    //Reference weld Signature request read is sent to ASC when this flag is true
    bool m_SendReferenceWeldGraphSignatureReadRequest;
    //Reference weld result read request is sent to ASC when this flag is true
    bool m_SendReferenceWeldReadRequestonPowerUp;
    //Requested Weld signature read request is sent to ASC when this flag is true
    bool m_SendRequestedRefWeldSignatureReadRequest;
    //This flag gets set to true when user requests to read a new/different reference weld signature data
    bool m_ReqReferenceWeldSignatureData;
    //Holds Reference WeldResultIndex number for which user has requested reference weld signature to read
    int m_RefWeldResultIndexNumberToRead;
    //Holds Reference WeldSignature sample number to read in case of reference weld signature transfer is in progress
    int m_RefWeldSignSampleNumberToRead;
    //Holds WeldResult sample number to read in case of weld result transfer is in progress for search by WeldResult Index number operation
    int m_WeldResultSampleNumberToRead;
    //This flag gets set to true when user requests to fetch a new/different WeldResult number data
    bool m_RequestedReferenceWeldResultIndex;
    //Search by Reference Weld Result read request is sent to ASC when this flag is true
    bool m_SendReferenceWeldSignWeldResultReadRequest;
    //This flag gets sets to true when replace request takes place successfully.
    bool m_ReplaceRefGraphStatus;

    bool m_IsReferenceGraphDetailsAvailable;
    int m_WeldResultIndex;
    bool m_sendNewDequeue;

};
#endif /* REFERENCE_WELD_SIGNATURE_ACE_H_ */

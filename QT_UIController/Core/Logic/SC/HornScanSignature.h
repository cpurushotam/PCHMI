/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE horn scan signature related implementation

***************************************************************************/

#ifndef HORN_SCAN_SIGNATURE_H_
#define HORN_SCAN_SIGNATURE_H_

#include <deque>
#include "DataInterface.h"
#include "HornScanSignatureStructure.h"

class HornScanSignature : public DataInterface
{
public:
    HornScanSignature();
    virtual ~HornScanSignature();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateHornScanSignatureReadRequest(int HornScanResultIndexNumber);
    void ShowRequestedHornScanSignatureDataFromCache();
    std::deque<HornScanSignatureStruct> GetHornScanSignatureData();
    bool GetIsLastHornScanSignatureUpdated();
    void SetIsLastHornScanSignatureUpdated(bool Value);

private:
    static size_t static_log_id;

    //Holds Requested Horn Scan Signature Data
    std::deque<HornScanSignatureStruct> m_RequestedHornScanSignatureData;

    //Requested horn scan signature read request is sent to ASC when this flag is true
    bool m_SendRequestedHornScanSignatureReadRequest;

    //This flag gets set to true when user requests to read a new/different horn scan signature data
    bool m_RequestNewHornScanSignatureData;

    //Holds HornScanResultIndex number for which user has requested horn scan signature to read
    int m_HornScanResultIndexNumberToRead;

    //Holds HornScanSignature sample number to read in case of horn scan signature transfer is in progress
    int m_HornScanSignatureSampleNumberToRead;

    bool m_IsCompleteHornScanSignatureReceived;

    void sendRequestedHornScanSignatureReadRequestToASC(MEMORY_BLOCK * const destination);
    void procesRequestedHornScanSignatureDataFromASC(const MEMORY_BLOCK *const source);
};

#endif /* HORN_SCAN_SIGNATURE_H_ */

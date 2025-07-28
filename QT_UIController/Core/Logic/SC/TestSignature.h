/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE Test signature related implementation

***************************************************************************/

#ifndef TEST_SIGNATURE_H_
#define TEST_SIGNATURE_H_

#include <deque>

#include "DataInterface.h"
#include "TestSignatureStructure.h"

class TestSignature : public DataInterface
{
public:
    TestSignature();
    virtual ~TestSignature();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    std::deque<TestSignatureStruct> GetRequestedTestSignatureData(void);
    bool GetIsCompleteTestSignatureReceived(void);
    void SetIsCompleteTestSignatureReceived(bool Value);

private:
    static size_t static_log_id;

    //Holds Requested Test Signature Data
    std::deque<TestSignatureStruct> m_RequestedTestSignatureData;

    //Requested test signature read request is sent to ASC when this flag is true
    bool m_SendRequestedTestSignatureReadRequest;

    bool m_IsCompleteTestSignatureReceived;

    //Holds TestSignature sample number to read in case of test signature transfer is in progress
    int m_TestSignatureSampleNumberToRead;

    void procesTestSignatureDataFromASC(const MEMORY_BLOCK *const source);
    void sendRequestedTestSignatureReadRequestToASC(MEMORY_BLOCK * const destination);
    void ShowRequestedTestSignatureDataFromCache();

};

#endif /* TEST_SIGNATURE_H_ */

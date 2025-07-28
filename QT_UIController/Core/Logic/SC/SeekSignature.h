/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE seek signature related implementation

***************************************************************************/

#ifndef SEEK_SIGNATURE_H_
#define SEEK_SIGNATURE_H_

#include <deque>

#include "DataInterface.h"
#include "SeekSignatureStructure.h"

class SeekSignature : public DataInterface
{
public:
    SeekSignature();
    virtual ~SeekSignature();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateSeekSignatureReadRequest(void);
    std::deque<SeekSignatureStruct> GetRequestedSeekSignatureData(void);
    bool GetIsCompleteSeekSignatureReceived(void);
    void SetIsCompleteSeekSignatureReceived(bool Value);

private:
    static size_t static_log_id;

    //Holds Requested Seek Signature Data
    std::deque<SeekSignatureStruct> m_RequestedSeekSignatureData;

    //Requested Seek signature read request is sent to ASC when this flag is true
    bool m_SendRequestedSeekSignatureReadRequest;

    bool m_IsCompleteSeekSignatureReceived;
    //Holds SeekSignature sample number to read in case of Seek signature transfer is in progress
    int m_SeekSignatureSampleNumberToRead;

    void procesSeekSignatureDataFromASC(const MEMORY_BLOCK *const source);
    void sendRequestedSeekSignatureReadRequestToASC(MEMORY_BLOCK * const destination);
    void ShowRequestedSeekSignatureDataFromCache();

};

#endif /* SEEK_SIGNATURE_H_ */

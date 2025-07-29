/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the seek result related implementation

***************************************************************************/

#ifndef SEEKRESULT_H_
#define SEEKRESULT_H_

#include "DataInterface.h"
#include "SeekResultStructure.h"

class SeekResult : public DataInterface
{

public:

	SeekResult();
    virtual ~SeekResult();

	//Write Seek Result data
	int GetData(MEMORY_BLOCK * const destination) override;

	//Read Seek Result data
    int SetData(const MEMORY_BLOCK *const source) override;
	void InitiateSeekRunOperation();
    SeekResultstruct GetSeekResultData(void);
    void ShowSeekResult();
private:
	
	bool m_InitiateSeekRunOperation;
    bool m_InitiateSeekReadOnPowerUp;

	size_t m_LogID;
	
	//structure variable to store seek result data
	SeekResultstruct m_SeekResultData;
	
	//mutex for m_SeekResultData access
	pthread_mutex_t m_SeekResultDataMutex;
		
    //initiate to send Seek run request to ASC
	void SendSeekRunOperationToASC(MEMORY_BLOCK * const destination);
    void SendSeekResultReadRequestToASC(MEMORY_BLOCK * const destination);
    //Process Seek Result read request
    void processSeekResultReadResponseFromASC(const MEMORY_BLOCK *const source);
    void processSyncSeekResultonDateTimeFormatChg();

};

#endif /* SEEKRESULT_H_ */




















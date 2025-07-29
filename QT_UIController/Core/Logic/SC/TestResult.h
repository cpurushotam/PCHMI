/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test Result related implementation
 
***************************************************************************/

#ifndef TEST_RESULT_H_
#define TEST_RESULT_H_

#include <pthread.h>

#include "DataInterface.h"
#include "TestResultStructure.h"

class TestResult : public DataInterface
{
public:
	TestResult();
	int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    /*Function to update values from HMI are updated to ASC - To be used by Qml to update this button status */
    void setButtonStatusFromHMI(TESTSTATUS Local_TestStatusStruct);
    TestResultStruct GetTestResultData(void);
    TestProgressStruct GetTestProgressResultData(void);

private: 
	static size_t log_id;

    bool m_InitiateTestResultReadReq;
    bool m_InitiateTestProgressReadReq;

    //Local structures to store TestResult data .
    TestResultStruct m_TestResultStruct;

    //Local structures to store TestProgress data .
    TestProgressStruct m_TestProgressStruct;

    //Local TESTSTATUS Enum to store TestStatus.
    TESTSTATUS m_TestCommand;

    //flag is set to true when user presses or release start button on HMI - else false.
    bool SendTestStartOrAbortRequest = false;

    //mutex for m_TestResult access
    pthread_mutex_t m_TestResultMutex;

    //mutex for m_TestProgress access
    pthread_mutex_t m_TestProgressMutex;

	//flag is set to true when m_TestResultMutex is initialized
    bool m_isMutexInitialised;
	
    size_t m_LogID;

    //Function to receive TestResult data from ASC .
    void processTestResultData(const MEMORY_BLOCK *const source);

    //Function to receive TestProgress data from ASC .
    void processTestProgressData(const MEMORY_BLOCK *const source);

    //Function to send Start Test button status to ASC .
    void sendTestOperationRequest(MEMORY_BLOCK *const destination);

    void SendTestResultReadRequestToASC(MEMORY_BLOCK *const destination);

    void SendTestProgressReadRequestToASC(MEMORY_BLOCK *const destination);

};
#endif /* TEST_RESULT_H_ */

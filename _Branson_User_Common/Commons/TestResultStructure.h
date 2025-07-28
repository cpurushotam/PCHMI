/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test result related implementation
 ***************************************************************************/

#ifndef TEST_RESULT_STRUCTURE_H_
#define TEST_RESULT_STRUCTURE_H_
#include <string.h>
#include "Common_Definitions.h"

// definition for SUB-ID of memory block
typedef enum{
    SUB_ID_START_OR_ABORT_OPERATION = 1,
    SUB_ID_SEND_TEST_RESULT_DATA,
    SUB_ID_SEND_TEST_PROGRESS_DATA,

}TEST_OPERATION_SUB_ID;

typedef enum{
    START_TEST_PROCESS =0,
    ABORT_TEST_PROCESS
}TESTSTATUS;

    typedef struct TestResultStruct
{
    int32_t TestResultIndex;
    char DateTime[DATE_SIZE_12_HR_FORMAT];
    float TestTime;
    float TestPeakPower;
    int32_t StartFrequency;
    int32_t EndFrequency;

    TestResultStruct()
    {
        ResetParameters();
    }

    void ResetParameters()
    {
        TestResultIndex = 1;
        memset(DateTime, '\0', sizeof(DateTime));
        TestTime = 0.0f;
        TestPeakPower = 0.0f;
        StartFrequency = 0;
        EndFrequency = 0;
    }

}__attribute__((packed)) TestResultStruct;

typedef struct TestProgressStruct
{
    int32_t Frequency;
    int32_t StoredFrequency;
    float Power;

    TestProgressStruct()
    {
        Frequency = 0;
        StoredFrequency = 0;
        Power = 0.0f;
    }
}__attribute__((packed)) TestProgressStruct;

#endif //TEST_RESULT_STRUCTURE_H_

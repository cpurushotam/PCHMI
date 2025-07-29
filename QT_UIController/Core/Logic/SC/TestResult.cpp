/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the test result related implementation

***************************************************************************/
#include <string.h>
#include "TestResult.h"
#include "DataLogger.h"

size_t TestResult::log_id = 0;

/******************************************************************************//**
* \brief - Constructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
TestResult::TestResult()
{
    //enroll to use logger functionality
    log_id = Logger::enroll(this);

    //initialize static mutexes only once as they are common across all objects.
    if(m_isMutexInitialised == false)
    {
        pthread_mutex_init(&m_TestResultMutex, nullptr);
        m_isMutexInitialised = true;
    }

    SendTestStartOrAbortRequest =false;
    m_InitiateTestResultReadReq=true;
    m_InitiateTestProgressReadReq=true;
}

/**************************************************************************//**
*
* \brief   - GetData Interface implementation for test result data. 
*           
* \param   - Address of destination Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int TestResult::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_TEST_OPERATION))
    {
        // perform operation based on sub id
        switch(destination->sub_id)
        {
        case SUB_ID_START_OR_ABORT_OPERATION:
        {
            retVal = 0;
            sendTestOperationRequest(destination);
            break;
        }
        case SUB_ID_SEND_TEST_RESULT_DATA:
        {
            retVal = 0;
            SendTestResultReadRequestToASC(destination);
            break;
        }
        case SUB_ID_SEND_TEST_PROGRESS_DATA:
        {
            retVal = 0;
            SendTestProgressReadRequestToASC(destination);
            break;
        }

        default:
        {
            // Error ! default retVal (failure) will be returned
            // clear valid bit, reset size
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestProcess:GetData default");
            break;
        }
        }
    }
    else
    {
        // error! invalid memory block id, default retVal (failure) will be returned
        // clear valid bit, reset size
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestProcess:GetData invalid req");

    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - SetData Interface implementation for test result data.           
*
* \param   - Address of source Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int TestResult::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_TEST_OPERATION))
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            // perform operation based on sub id
            switch(source->sub_id)
            {

            case SUB_ID_SEND_TEST_RESULT_DATA:
            {
                retVal =0;
                processTestResultData(source);
                break;
            }
            case SUB_ID_SEND_TEST_PROGRESS_DATA:
            {
                retVal =0;
                processTestProgressData(source);
                break;
            }
            default:
            {
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestResult:SetData default");
                break;
            }

            }
        }
        else
        {
            retVal = 0;
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestResult:SetData invalid req");
    }

    return (retVal);
}

/**************************************************************************//**
*
* \brief   - To receive data from ASC for Sub-Id SUB_ID_SEND_TEST_RESULT_DATA
*
* \param   - source - Memory block containing data from ASC
*
* \return  - None
*
******************************************************************************/
void TestResult::processTestResultData(const MEMORY_BLOCK * const source)
{
    TestResultStruct *TestResultDataPtr = reinterpret_cast<TestResultStruct *>(source->data);

    pthread_mutex_lock(&m_TestResultMutex);
    m_TestResultStruct.TestResultIndex =TestResultDataPtr ->TestResultIndex;
    m_TestResultStruct.TestPeakPower =TestResultDataPtr ->TestPeakPower;
    m_TestResultStruct.TestTime =TestResultDataPtr ->TestTime;
    strncpy(m_TestResultStruct.DateTime ,TestResultDataPtr ->DateTime,DATE_TIME_SIZE);
    m_TestResultStruct.EndFrequency =TestResultDataPtr ->EndFrequency;
    m_TestResultStruct.StartFrequency =TestResultDataPtr ->StartFrequency;
    pthread_mutex_unlock(&m_TestResultMutex);
}

/**************************************************************************//**
*
* \brief   - To receive data from ASC for Sub-Id SUB_ID_SEND_TEST_PROGRESS_DATA
*
* \param   - source - Memory block containing data from ASC
*
* \return  - None
*
******************************************************************************/
void TestResult::processTestProgressData(const MEMORY_BLOCK * const source)
{
    TestProgressStruct *TestProgressDataPtr = reinterpret_cast<TestProgressStruct *>(source->data);

    pthread_mutex_lock(&m_TestProgressMutex);
    m_TestProgressStruct.Frequency =TestProgressDataPtr ->Frequency;
    m_TestProgressStruct.StoredFrequency =TestProgressDataPtr ->StoredFrequency;
    m_TestProgressStruct.Power =TestProgressDataPtr ->Power;
    pthread_mutex_unlock(&m_TestProgressMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_TEST_OPERATION.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void TestResult::sendTestOperationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >=sizeof(m_TestCommand))
    {
        if(SendTestStartOrAbortRequest)
        {
            // update size in destination
            destination->size = sizeof(m_TestCommand);

            // set valid bit
            destination->config = VALID_BIT;

            TESTSTATUS *TestCommandPtr = reinterpret_cast<TESTSTATUS *>(destination->data);

            *TestCommandPtr= m_TestCommand; //Send Test command on clicked or released.

            SendTestStartOrAbortRequest =false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }

}

/**************************************************************************//**
*
* \brief   - setSystemDetailsFromHMI - QML will use this function to send status of Test button to ASC.
*
* \param   - TestStatusStruct - To store current status of the button.
*
* \return  - none.
*
******************************************************************************/
void TestResult::setButtonStatusFromHMI(TESTSTATUS HMI_TestCommand)
{
    m_TestCommand = HMI_TestCommand;
    SendTestStartOrAbortRequest =true;
}

/**************************************************************************//**
*
* \brief   - This function returns test result structure parameters.
*
* \param   - None.
*
* \return  - m_TestResultStruct : The test result structure parameters.
*
******************************************************************************/
TestResultStruct TestResult::GetTestResultData()
{
    return m_TestResultStruct;
}

/**************************************************************************//**
*
* \brief   - This function returns test progress structure parameters.
*
* \param   - None.
*
* \return  - m_TestProgressStruct : The test progress structure parameters.
*
******************************************************************************/
TestProgressStruct TestResult::GetTestProgressResultData()
{
    return m_TestProgressStruct;
}
/**************************************************************************//**
*
* \brief   - Send a TestResult Operation request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void TestResult::SendTestResultReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateTestResultReadReq == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateTestResultReadReq = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}

/**************************************************************************//**
*
* \brief   - Send a Test result read request on power up to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void TestResult::SendTestProgressReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateTestProgressReadReq == true )
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateTestProgressReadReq = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}

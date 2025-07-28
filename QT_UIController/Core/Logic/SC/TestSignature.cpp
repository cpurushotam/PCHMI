/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE test signature related implementation

***************************************************************************/
#include <cstring>
#include "TestSignature.h"
#include "DataLogger.h"

size_t TestSignature::static_log_id = 0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
TestSignature::TestSignature()
{
    m_SendRequestedTestSignatureReadRequest = true;
    m_IsCompleteTestSignatureReceived = false;
    m_TestSignatureSampleNumberToRead =0;

    //enroll to use logger functionality
    static_log_id = Logger::enroll(this);
}

/******************************************************************************
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
TestSignature::~TestSignature()
{

}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_TEST_SIGNATURE_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int TestSignature::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if( (destination != nullptr) && (destination->id == MB_ID_TEST_SIGNATURE_DATA) )
    {
        switch(destination->sub_id)
        {
        //Send request to ASC to get the Test signature data
        case SUB_ID_SEND_TEST_SIGNATURE_DATA:
        {
            retVal = 0;
            sendRequestedTestSignatureReadRequestToASC(destination);
            break;
        }

        default:
        {
            // Error ! default retVal (failure) will be returned
            // clear valid bit, reset size
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"TestSignature GetData default case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
            break;
        }
        }
    }
    else
    {
        // error! invalid sub-id, default retVal (failure) will be returned
        // clear valid bit, reset size
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"TestSignature GetData invalid case");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);

}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_TEST_SIGNATURE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int TestSignature::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_TEST_SIGNATURE_DATA))
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            // perform operation based on sub id
            switch(source->sub_id)
            {

            case SUB_ID_SEND_TEST_SIGNATURE_DATA:
            {
                retVal =0;
                procesTestSignatureDataFromASC(source);
                break;
            }

            default:
            {
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestSignature:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestSignature:SetData invalid req");
    }

    return (retVal);

}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to read a deque of test signature of type TestSignatureStruct.
*
*
* \param   - void
*
* \return  - void
******************************************************************************/
std::deque<TestSignatureStruct> TestSignature::GetRequestedTestSignatureData()
{
    return m_RequestedTestSignatureData;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to read a flag to indicate complete test signature read or not.
*
* \param   - void
*
* \return  - m_IsCompleteTestSignatureReceived - Test signature received flag.
******************************************************************************/
bool TestSignature::GetIsCompleteTestSignatureReceived()
{
    return m_IsCompleteTestSignatureReceived;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when complete test
*           test signature get read by HMI.
*
*
* \param   - Value - flag status from HMI.
*
* \return  - void
******************************************************************************/
void TestSignature::SetIsCompleteTestSignatureReceived(bool Value)
{
    m_IsCompleteTestSignatureReceived = Value;
}

/**************************************************************************//**
*
* \brief   - process the requested weld signature data coming from ASC
*
* \param   - source - memory block holding the requested weld signature data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void TestSignature::procesTestSignatureDataFromASC(const MEMORY_BLOCK *const source)
{
    int TotalTestSignatureSamples = *reinterpret_cast< int*>(source->data);
    bool IsCompleTestSignatureRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
    TestSignatureStruct* TestSignatureData = reinterpret_cast< TestSignatureStruct*>(source->data + sizeof(int) + sizeof(bool));

    if(m_TestSignatureSampleNumberToRead == 0)
    {
        m_RequestedTestSignatureData.clear();
    }

    for(int SignatureSampleNumber = 0; SignatureSampleNumber < TotalTestSignatureSamples; SignatureSampleNumber++)
    {
        m_RequestedTestSignatureData.push_back(*TestSignatureData);
        TestSignatureData++;
    }

    m_TestSignatureSampleNumberToRead = m_TestSignatureSampleNumberToRead + TotalTestSignatureSamples;

    if(IsCompleTestSignatureRead == true)
    {
        m_TestSignatureSampleNumberToRead = 0;
        m_SendRequestedTestSignatureReadRequest = false;
        m_IsCompleteTestSignatureReceived = true;
    }
    else
    {
        m_SendRequestedTestSignatureReadRequest = true;
    }
}

/**************************************************************************//**
*
* \brief   - Send requested Test signature read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void TestSignature::sendRequestedTestSignatureReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= (sizeof(m_TestSignatureSampleNumberToRead)))
    {
        if( m_SendRequestedTestSignatureReadRequest == true )
        {
            destination->size = (sizeof(m_TestSignatureSampleNumberToRead));
            destination->config = VALID_BIT;

            //Set the TestSignature Sample Number to be read.
            int *TestSignatureSampleNumber = reinterpret_cast<int *>(destination->data);
            *TestSignatureSampleNumber = m_TestSignatureSampleNumberToRead;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRequestedTestSignatureReadRequest = false;
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
* \brief   - Show the test signature data available in cache
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void TestSignature::ShowRequestedTestSignatureDataFromCache()
{
    if(m_RequestedTestSignatureData.size() == 0)
    {
        std::cout << "Requested Test Signature is empty" << std::endl;
    }
    else
    {
        std::cout << "Requested Test Signature Data: " << std::endl;
        std::cout << "Time,Amplitude,Frequency,Power,Current,Phase" << std::endl;
        for (unsigned int Index = 0; Index < m_RequestedTestSignatureData.size(); Index++)
        {
            std::cout << m_RequestedTestSignatureData[Index].Time << ',';
            std::cout << m_RequestedTestSignatureData[Index].Amplitude << ',';
            std::cout << m_RequestedTestSignatureData[Index].Frequency << ',';
            std::cout << m_RequestedTestSignatureData[Index].Power<< ',';
            std::cout << m_RequestedTestSignatureData[Index].Current << ',';
            std::cout << m_RequestedTestSignatureData[Index].Phase<< '\n';
        }
    }
}

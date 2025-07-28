/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the seek signature related implementation

***************************************************************************/
#include <cstring>
#include "SeekSignature.h"
#include "DataLogger.h"

size_t SeekSignature::static_log_id = 0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
SeekSignature::SeekSignature()
{
    m_SendRequestedSeekSignatureReadRequest = true;
    m_IsCompleteSeekSignatureReceived = false;
    m_SeekSignatureSampleNumberToRead = 0;

    m_RequestedSeekSignatureData.clear();
	
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
SeekSignature::~SeekSignature()
{

}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_SEEK_SIGNATURE_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int SeekSignature::GetData(MEMORY_BLOCK * const destination)
{   
    int retVal = -1;

    if( (destination != nullptr) && (destination->id == MB_ID_SEEK_SIGNATURE_DATA))
    {
        switch(destination->sub_id)
        {
            //Send request to ASC to get the requested Seek signature data
            case READ_SEEK_SIGNATURE_DATA:
            {
                retVal = 0;
                sendRequestedSeekSignatureReadRequestToASC(destination);
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
                snprintf(msg,buff_size_config,"SeekSignature GetData default case");
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
        snprintf(msg,buff_size_config,"SeekSignature GetData invalid case");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_SEEK_SIGNATURE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int SeekSignature::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;
    if((source != nullptr) && (source->id == MB_ID_SEEK_SIGNATURE_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                //Process response coming from ASC for requested Seek signature data
                case READ_SEEK_SIGNATURE_DATA:
                {
                    retVal = 0;
                    procesSeekSignatureDataFromASC(source);
                    break;
                }

                default:
                {
                    char  msg[buff_size_config] = {0};
                    snprintf(msg,buff_size_config,"seekSignature SetData default case");
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
                    //Error ! default retVal (failure) will be returned
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
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"SeekSignature SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Initiates the seek signature read request from HMI by setting
*            m_SendRequestedSeekSignatureReadRequest flag true.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSignature::InitiateSeekSignatureReadRequest()
{
    m_SendRequestedSeekSignatureReadRequest = true;
}

/**************************************************************************//**
*
* \brief   - Retuns the seek signature data available into deque.
*
* \param   - None.
*
* \return  - m_RequestedSeekSignatureData : Seek signature data deque.
*
******************************************************************************/
std::deque<SeekSignatureStruct> SeekSignature::GetRequestedSeekSignatureData()
{
    auto SeekSignatureData = m_RequestedSeekSignatureData;

    return SeekSignatureData;
}

/**************************************************************************//**
*
* \brief   - Retuns the status of read signature whether complete data read or not.
*
* \param   - None.
*
* \return  - m_IsCompleteSeekSignatureReceived : Seek signature data read status.
*
******************************************************************************/
bool SeekSignature::GetIsCompleteSeekSignatureReceived()
{
    return m_IsCompleteSeekSignatureReceived;
}

/**************************************************************************//**
*
* \brief   - Sets the status of read signature true once all data read completed.
*
* \param   - Value : Status flag value from interface.
*
* \return  - None.
*
******************************************************************************/
void SeekSignature::SetIsCompleteSeekSignatureReceived(bool Value)
{
    m_IsCompleteSeekSignatureReceived = Value;
}

/**************************************************************************//**
*
* \brief   - process the requested Seek signature data coming from ASC
*
* \param   - source - memory block holding the requested seek signature data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void SeekSignature::procesSeekSignatureDataFromASC(const MEMORY_BLOCK *const source)
{
    int TotalSignatureSamples = *reinterpret_cast< int*>(source->data);
    bool IsCompleSeekSignatureRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
    SeekSignatureStruct* SeekSignatureData = reinterpret_cast< SeekSignatureStruct*>(source->data + sizeof(int) + sizeof(bool));

    if(m_SeekSignatureSampleNumberToRead == 0)
    {
        m_RequestedSeekSignatureData.clear();
    }

    for(int SignatureSampleNumber = 0; SignatureSampleNumber < TotalSignatureSamples; SignatureSampleNumber++)
    {
        m_RequestedSeekSignatureData.push_back(*SeekSignatureData);
        SeekSignatureData++;
    }

    m_SeekSignatureSampleNumberToRead = m_SeekSignatureSampleNumberToRead + TotalSignatureSamples;

    if(IsCompleSeekSignatureRead == true)
    {
        m_SeekSignatureSampleNumberToRead = 0;
        m_SendRequestedSeekSignatureReadRequest = false;
        m_IsCompleteSeekSignatureReceived = true;
    }
    else
    {
        m_SendRequestedSeekSignatureReadRequest = true;
    }
}

/**************************************************************************//**
*
* \brief   - Send requested Seek signature read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SeekSignature::sendRequestedSeekSignatureReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= (sizeof(m_SeekSignatureSampleNumberToRead)))
    {
        if( m_SendRequestedSeekSignatureReadRequest == true )
        {
            destination->size = (sizeof(m_SeekSignatureSampleNumberToRead));
            destination->config = VALID_BIT;

            //Set the SeekSignature Sample Number to be read.
            int *SeekSignatureSampleNumber = reinterpret_cast<int *>(destination->data);
            *SeekSignatureSampleNumber = m_SeekSignatureSampleNumberToRead;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRequestedSeekSignatureReadRequest = false;
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
* \brief   - Show the requested Seek signature data available in cache
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void SeekSignature::ShowRequestedSeekSignatureDataFromCache()
{
    if(m_RequestedSeekSignatureData.size() == 0)
    {
        std::cout << "Requested Seek Signature is empty" << std::endl;
    }
    else
    {
        std::cout << "Requested Seek Signature Data Size: " << m_RequestedSeekSignatureData.size() << std::endl;
        std::cout << "Time,Amplitude,Frequency,Power,Current,Phase" << std::endl;
        for (unsigned int Index = 0; Index < m_RequestedSeekSignatureData.size(); Index++)
        {
            if(Index == m_RequestedSeekSignatureData.size() - 1)
            {
                std::cout << m_RequestedSeekSignatureData[Index].Time << ',';
                std::cout << m_RequestedSeekSignatureData[Index].Amplitude << ',';
                std::cout << m_RequestedSeekSignatureData[Index].Frequency << ',';
                std::cout << m_RequestedSeekSignatureData[Index].Power<< ',';
                std::cout << m_RequestedSeekSignatureData[Index].Current << ',';
                std::cout << m_RequestedSeekSignatureData[Index].Phase<< '\n';
            }
        }
    }
}






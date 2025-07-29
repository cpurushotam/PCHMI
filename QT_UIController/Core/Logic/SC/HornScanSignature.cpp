/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Horn scan signature related implementation

***************************************************************************/
#include <cstring>
#include "HornScanSignature.h"
#include "DataLogger.h"

size_t HornScanSignature::static_log_id = 0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
HornScanSignature::HornScanSignature()
{
    m_SendRequestedHornScanSignatureReadRequest = false;
    m_RequestNewHornScanSignatureData = false;
    m_HornScanResultIndexNumberToRead = -1;
    m_HornScanSignatureSampleNumberToRead = 0;
    m_IsCompleteHornScanSignatureReceived = false;
	
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
HornScanSignature::~HornScanSignature()
{

}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_HORN_SCAN_SIGNATURE_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int HornScanSignature::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

        if( (destination != nullptr) && (destination->id == MB_ID_HORN_SCAN_SIGNATURE_DATA) )
        {
            switch(destination->sub_id)
            {
               //Send request to ASC to get the requested horn scan signature data
                case READ_REQUESTED_HORN_SCAN_SIGNATURE_DATA:
				{
					retVal = 0;
                    sendRequestedHornScanSignatureReadRequestToASC(destination);
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
                    snprintf(msg,buff_size_config,"HornScanSignature GetData default case");
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
            snprintf(msg,buff_size_config,"HornScanSignature GetData invalid case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_HORN_SCAN_SIGNATURE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int HornScanSignature::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_HORN_SCAN_SIGNATURE_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
               //Process response coming from ASC for requested horn scan signature data
                case READ_REQUESTED_HORN_SCAN_SIGNATURE_DATA:
				{
					retVal = 0;
                    procesRequestedHornScanSignatureDataFromASC(source);
					break;
				}				
                default:
                {
                    char  msg[buff_size_config] = {0};
                    snprintf(msg,buff_size_config,"HornScanSignature SetData default case");
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
        snprintf(msg,buff_size_config,"HornScanSignature SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Send requested horn scan signature read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void HornScanSignature::sendRequestedHornScanSignatureReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if( destination->size >= ( sizeof( m_RequestNewHornScanSignatureData )  + sizeof( m_HornScanResultIndexNumberToRead ) + sizeof(m_HornScanSignatureSampleNumberToRead) ) )
    {
        if( m_SendRequestedHornScanSignatureReadRequest == true )
        {
            destination->size = ( sizeof(m_RequestNewHornScanSignatureData)  + sizeof(m_HornScanResultIndexNumberToRead) + sizeof(m_HornScanSignatureSampleNumberToRead) );
            destination->config = VALID_BIT;

            bool *RequestNewHornScanSignatureData = reinterpret_cast<bool *>(destination->data) ;
            //Set the RequestNewHornScanSignatureData flag to indicate that user has requested different horn scan signature data in case data transfer for different horn scan signature is in progress.
            *RequestNewHornScanSignatureData = m_RequestNewHornScanSignatureData;

            if(m_RequestNewHornScanSignatureData == true)
            {
                //Clear contents of existing horn scan signature data in case user has requested data for different horn scan signature
                m_RequestedHornScanSignatureData.clear();
                m_HornScanSignatureSampleNumberToRead = 0;
            }

            int *HornScanResultIndexNumber = reinterpret_cast<int *>(destination->data + sizeof(bool));
            //Set the HornScanResultIndex number for which horn scan signature is to be read.
            *HornScanResultIndexNumber = m_HornScanResultIndexNumberToRead;

            //Set the HornScanSignature Sample Number to be read.
            int *HornScanSignatureSampleNumber = reinterpret_cast<int *>(destination->data + sizeof(bool) + sizeof(int));
            *HornScanSignatureSampleNumber = m_HornScanSignatureSampleNumberToRead;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRequestedHornScanSignatureReadRequest = false;

            //Reset the flag to false as we have sent the request.
            m_RequestNewHornScanSignatureData = false;
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
* \brief   - HMI/front end code should call this function when it wants
* 			 to read a particular Horn Scan signature.
*
* \param   - HornScanResultIndexNumber - Horn Scan Result Index Number for which the
* 			 horn scan signature needs to be fetched
*
* \return  - void
******************************************************************************/
void HornScanSignature::InitiateHornScanSignatureReadRequest(int HornScanResultIndexNumber)
{
    if(m_HornScanResultIndexNumberToRead != HornScanResultIndexNumber)
    {
        m_HornScanResultIndexNumberToRead = HornScanResultIndexNumber;

        //User has requested data for different horn scan signature
        m_RequestNewHornScanSignatureData = true;
        m_SendRequestedHornScanSignatureReadRequest = true;
    }
}

/**************************************************************************//**
*
* \brief   - process the requested Horn Scan signature data coming from ASC
*
* \param   - source - memory block holding the requested Horn Scan signature data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void HornScanSignature::procesRequestedHornScanSignatureDataFromASC(const MEMORY_BLOCK *const source)
{
    //First byte from response contains HornScanResultndex Number to which the horn scan signature belongs
    int HornScanResultIndexNumber = *reinterpret_cast< int*>(source->data);
    int TotalSignatureSamples = *reinterpret_cast< int*>(source->data + sizeof(int));
    bool IsCompleteHornScanSignatureRead = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int));
    HornScanSignatureStruct* HornScanSignatureData = reinterpret_cast< HornScanSignatureStruct*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool));

    if(HornScanResultIndexNumber != m_HornScanResultIndexNumberToRead)
    {
        //Clear older Horn Scan signature data
        m_RequestedHornScanSignatureData.clear();
        m_HornScanSignatureSampleNumberToRead = 0;
        m_SendRequestedHornScanSignatureReadRequest = true;
    }
    else
    {
        for(int SignatureSampleNumber = 0; SignatureSampleNumber < TotalSignatureSamples; SignatureSampleNumber++)
        {
            m_RequestedHornScanSignatureData.push_back(*HornScanSignatureData);
            HornScanSignatureData++;
        }

        m_HornScanSignatureSampleNumberToRead = m_HornScanSignatureSampleNumberToRead + TotalSignatureSamples;

        if(IsCompleteHornScanSignatureRead == true)
        {
            m_HornScanResultIndexNumberToRead = -1;
            m_HornScanSignatureSampleNumberToRead = 0;
            m_SendRequestedHornScanSignatureReadRequest = false;
            m_IsCompleteHornScanSignatureReceived = true;
        }
        else
        {
            m_SendRequestedHornScanSignatureReadRequest = true;
        }
    }
}
/**************************************************************************//**
*
* \brief   - Show the requested horn scan signature data available in cache
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void HornScanSignature::ShowRequestedHornScanSignatureDataFromCache()
{
    if(m_RequestedHornScanSignatureData.size() == 0)
    {
        std::cout << "Requested Horn Scan Signature is empty" << std::endl;
    }
    else
    {
        std::cout << "Requested Horn Scan Signature Data: " << std::endl;
        std::cout << "Amplitude,Current,Phase,Frequency,TargetAmplitude" << std::endl;
        for (unsigned int Index = 0; Index < m_RequestedHornScanSignatureData.size(); Index++)
        {
            std::cout << m_RequestedHornScanSignatureData[Index].Amplitude << ',';
            std::cout << m_RequestedHornScanSignatureData[Index].Current << ',';
            std::cout << m_RequestedHornScanSignatureData[Index].Phase << ',';
            std::cout << m_RequestedHornScanSignatureData[Index].Frequency << ',';
            std::cout << m_RequestedHornScanSignatureData[Index].TargetAmplitude << '\n';
        }
    }
}

/**************************************************************************//**
*
* \brief   - Retuns the signature scan result data.
*
* \param   - None.
*
* \return  - m_RequestedHornScanSignatureData : Scan signature data.
*
******************************************************************************/
std::deque<HornScanSignatureStruct> HornScanSignature::GetHornScanSignatureData()
{
    return m_RequestedHornScanSignatureData;
}

/**************************************************************************//**
*
* \brief   - Set the status of read signature that complete data read.
*
* \param   - None.
*
* \return  - m_IsCompleteHornScanSignatureReceived : Scan signature data read status.
*
******************************************************************************/
bool HornScanSignature::GetIsLastHornScanSignatureUpdated()
{
    return m_IsCompleteHornScanSignatureReceived;
}

/**************************************************************************//**
*
* \brief   - Retuns the status of read signature whether complete data read or not.
*
* \param   - Value : Scan signature data read status.
*
* \return  - None.
*
******************************************************************************/
void HornScanSignature::SetIsLastHornScanSignatureUpdated(bool Value)
{
    m_IsCompleteHornScanSignatureReceived = Value;
}



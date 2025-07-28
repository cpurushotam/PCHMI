/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld signature related implementation

***************************************************************************/
#include <cstring>
#include "WeldSignatureAce.h"
#include "DataLogger.h"

size_t WeldSignatureACE::static_log_id = 0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
WeldSignatureACE::WeldSignatureACE()
{
    m_SendRequestedWeldSignatureReadRequest = false;
    m_RequestNewWeldSignatureData = false;
    m_WeldResultIndexNumberToRead = -1;
    m_WeldSignatureSampleNumberToRead = 0;

    //Send the request to read weld signature configuration data to ASC at power up of HMI
    m_SendWeldSignatureConfigReadRequest = true;
	
	m_InitiateAutoSaveGraphUpdateRequest = false;
	m_InitiateGraphSamplingIntervalUpdateRequest = false;

	m_bIsAutoSaveGraphEnabled = false;
	m_GraphSamplingInterval = MIN_GRAPH_SAMPLING_INTERVAL_IN_MILLISECONDS;
    m_IsCompleteWeldSignatureReceived = false;
	
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
WeldSignatureACE::~WeldSignatureACE()
{

}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_WELD_SIGNATURE_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldSignatureACE::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

        if( (destination != nullptr) && (destination->id == MB_ID_WELD_SIGNATURE_DATA) )
        {
            switch(destination->sub_id)
            {
			   //Send request to ASC to get the requested weld signature data
				case READ_REQUESTED_WELD_SIGNATURE_DATA:
				{
					retVal = 0;
					sendRequestedWeldSignatureReadRequestToASC(destination);
					break;
				}

                //Send request to ASC to get the weld signature configuration data
                case READ_WELD_SIGNATURE_CONFIG:
                {
                    retVal = 0;
                    sendWeldSignatureConfigReadRequestToASC(destination);
                    break;
                }
                
				case UPDATE_AUTO_SAVE_GRAPH:
                {
                    retVal = 0;
                    sendAutoSaveGraphUpdateRequestToASC(destination);
                    break;
                }
				
				case UPDATE_GRAPH_SAMPLING_INTERVAL:
                {
                    retVal = 0;
                    sendGraphSamplingIntervalUpdateRequestToASC(destination);
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
                    snprintf(msg,buff_size_config,"WeldSignatureACE GetData default case");
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
            snprintf(msg,buff_size_config,"WeldSignatureACE GetData invalid case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_WELD_SIGNATURE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldSignatureACE::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_WELD_SIGNATURE_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
			   //Process response coming from ASC for requested weld signature data
				case READ_REQUESTED_WELD_SIGNATURE_DATA:
				{
					retVal = 0;
					procesRequestedWeldSignatureDataFromASC(source);
					break;
				}

                //Process response coming from ASC for weld signature configuration data
                case READ_WELD_SIGNATURE_CONFIG:
                {
                    retVal = 0;
                    processWeldSignatureConfigDataFromASC(source);
                    break;
                }
				
                default:
                {
                    char  msg[buff_size_config] = {0};
                    snprintf(msg,buff_size_config,"WeldSignatureACE SetData default case");
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
        snprintf(msg,buff_size_config,"WeldSignatureACE SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Send requested weld signature read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldSignatureACE::sendRequestedWeldSignatureReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if( destination->size >= ( sizeof( m_RequestNewWeldSignatureData )  + sizeof( m_WeldResultIndexNumberToRead ) + sizeof(m_WeldSignatureSampleNumberToRead) ) )
    {
        if( m_SendRequestedWeldSignatureReadRequest == true )
        {
            destination->size = ( sizeof(m_RequestNewWeldSignatureData)  + sizeof(m_WeldResultIndexNumberToRead) + sizeof(m_WeldSignatureSampleNumberToRead) );
            destination->config = VALID_BIT;

            bool *RequestNewWeldSignatureData = reinterpret_cast<bool *>(destination->data) ;
            //Set the RequestNewWeldSignatureData flag to indicate that user has requested different weld signature data in case data transfer for different weld signature is in progress.
            *RequestNewWeldSignatureData = m_RequestNewWeldSignatureData;

            if(m_RequestNewWeldSignatureData == true)
            {
            	//Clear contents of existing weld signature data in case user has requested data for different weld signature
            	m_RequestedWeldSignatureData.clear();
            	m_WeldSignatureSampleNumberToRead = 0;
            }

            int *WeldResultIndexNumber = reinterpret_cast<int *>(destination->data + sizeof(bool));
            //Set the WeldResultIndex number for which weld signature is to be read.
            *WeldResultIndexNumber = m_WeldResultIndexNumberToRead;

            //Set the WeldSignature Sample Number to be read.
            int *WeldSignatureSampleNumber = reinterpret_cast<int *>(destination->data + sizeof(bool) + sizeof(int));
            *WeldSignatureSampleNumber = m_WeldSignatureSampleNumberToRead;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRequestedWeldSignatureReadRequest = false;

            //Reset the flag to false as we have sent the request.
            m_RequestNewWeldSignatureData = false;
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
* \brief   - Send weld signature configuration data read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void WeldSignatureACE::sendWeldSignatureConfigReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_SendWeldSignatureConfigReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_SendWeldSignatureConfigReadRequest = false;
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
* \brief   - Send AutoSaveGraph Update Request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldSignatureACE::sendAutoSaveGraphUpdateRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_bIsAutoSaveGraphEnabled))
    {
        if(m_InitiateAutoSaveGraphUpdateRequest == true)
        {
            bool *Data = reinterpret_cast<bool *>(destination->data);
            *Data = m_bIsAutoSaveGraphEnabled;
            destination->size = sizeof(m_bIsAutoSaveGraphEnabled);
            destination->config = VALID_BIT;
            m_InitiateAutoSaveGraphUpdateRequest = false;
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
* \brief   - Send GraphSamplingInterval Update Request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldSignatureACE::sendGraphSamplingIntervalUpdateRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_GraphSamplingInterval))
    {
        if(m_InitiateGraphSamplingIntervalUpdateRequest == true)
        {
            uint32_t *Data = reinterpret_cast<uint32_t *>(destination->data);
            *Data = m_GraphSamplingInterval;
            destination->size = sizeof(m_GraphSamplingInterval);
            destination->config = VALID_BIT;
            m_InitiateGraphSamplingIntervalUpdateRequest = false;
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
* \brief   - process the requested weld signature data coming from ASC
*
* \param   - source - memory block holding the requested weld signature data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void WeldSignatureACE::procesRequestedWeldSignatureDataFromASC(const MEMORY_BLOCK *const source)
{
	//First byte from response contains WeldResultndex Number to which the weld signature belongs
	int WeldResultIndexNumber = *reinterpret_cast< int*>(source->data);
	int TotalSignatureSamples = *reinterpret_cast< int*>(source->data + sizeof(int));
	bool IsCompleWeldSignatureRead = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int));
	WeldSignatureACEStruct* WeldSignatureData = reinterpret_cast< WeldSignatureACEStruct*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool));

	if(WeldResultIndexNumber != m_WeldResultIndexNumberToRead)
	{
		//Clear older weld signature data
		m_RequestedWeldSignatureData.clear();
    	m_WeldSignatureSampleNumberToRead = 0;
    	m_SendRequestedWeldSignatureReadRequest = true;
	}
	else
	{
		for(int SignatureSampleNumber = 0; SignatureSampleNumber < TotalSignatureSamples; SignatureSampleNumber++)
		{
			m_RequestedWeldSignatureData.push_back(*WeldSignatureData);
			WeldSignatureData++;
		}

		m_WeldSignatureSampleNumberToRead = m_WeldSignatureSampleNumberToRead + TotalSignatureSamples;

		if(IsCompleWeldSignatureRead == true)
		{
			m_WeldResultIndexNumberToRead = -1;
			m_WeldSignatureSampleNumberToRead = 0;
			m_SendRequestedWeldSignatureReadRequest = false;
            m_IsCompleteWeldSignatureReceived = true;
		}
		else
		{
			m_SendRequestedWeldSignatureReadRequest = true;
		}
	}
}

/**************************************************************************//**
*
* \brief   - process the weld signature configuration data  coming from ASC
*
* \param   - source - memory block holding the weld signature configuration data 
* 			 received from ASC
*
* \return  - none
*
******************************************************************************/
void WeldSignatureACE::processWeldSignatureConfigDataFromASC(const MEMORY_BLOCK *const source)
{
	m_bIsAutoSaveGraphEnabled = *reinterpret_cast< bool*>(source->data);
	m_GraphSamplingInterval = *reinterpret_cast< uint32_t*>(source->data + sizeof(bool));
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to read a particular weld signature.
*
*
* \param   - WeldResultIndexNumber - Weld Result Index Number for which the
* 			weld signature needs to be fetched
*
* \return  - void
******************************************************************************/
void WeldSignatureACE::InitiateWeldSignatureReadRequest(int WeldResultIndexNumber)
{
	if(m_WeldResultIndexNumberToRead != WeldResultIndexNumber)
	{
		m_WeldResultIndexNumberToRead = WeldResultIndexNumber;

		//User has requested data for different weld signature
		m_RequestNewWeldSignatureData = true;
		m_SendRequestedWeldSignatureReadRequest = true;
	}
}

/**************************************************************************//**
*
* \brief   - HMI should call this function when user wants to update AutoSaveGraph
* 			 value.
*
*
* \param   - Value - AutoSaveGraph value (true/false)
*
* \return  - None
******************************************************************************/
void WeldSignatureACE::InitiateAutoSaveGraphUpdateRequest(bool Value)
{
    m_bIsAutoSaveGraphEnabled = Value;
    m_InitiateAutoSaveGraphUpdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI should call this function when user wants to update AutoSaveGraph
* 			 value.
*
*
* \param   - Value - AutoSaveGraph value (true/false)
*
* \return  - true on success else false
******************************************************************************/
bool WeldSignatureACE::InitiateGraphSamplingIntervalUpdateRequest(uint32_t Value)
{
	bool bResult = false;
	
	if(Value >= MIN_GRAPH_SAMPLING_INTERVAL_IN_MILLISECONDS && Value <= MAX_GRAPH_SAMPLING_INTERVAL_IN_MILLISECONDS )
	{
		m_GraphSamplingInterval = Value;
		m_InitiateGraphSamplingIntervalUpdateRequest = true;
		bResult = true;
	}
	else
	{
		char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"InitiateGraphSamplingIntervalUpdateRequest fail");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	
	return bResult;
}

/**************************************************************************//**
*
* \brief   - Show the requested weld signature data available in cache
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void WeldSignatureACE::ShowRequestedWeldSignatureDataFromCache()
{
	if(m_RequestedWeldSignatureData.size() == 0)
	{
		std::cout << "Requested Weld Signature is empty" << std::endl;
	}
	else
	{
		std::cout << "Requested Weld Signature Data: " << std::endl;
		std::cout << "Time,Amplitude,Phase,Current,Frequency,Power,Energy,RequestAmplitude,AbsoluteDistance,CollapseDistance,Force,Velocity" << std::endl;
		for (unsigned int Index = 0; Index < m_RequestedWeldSignatureData.size(); Index++)
		{
			std::cout << m_RequestedWeldSignatureData[Index].Time << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Amplitude << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Phase << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Current << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Frequency << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Power << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Energy << ',';
			std::cout << m_RequestedWeldSignatureData[Index].RequestAmplitude << ',';
			std::cout << m_RequestedWeldSignatureData[Index].AbsoluteDistance << ',';
			std::cout << m_RequestedWeldSignatureData[Index].CollapseDistance << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Force << ',';
			std::cout << m_RequestedWeldSignatureData[Index].Velocity  << '\n';
		}
    }
}

std::deque<WeldSignatureACEStruct> WeldSignatureACE::GetRequestedWeldSignatureData()
{
    return m_RequestedWeldSignatureData;
}

bool WeldSignatureACE::GetIsCompleteWeldSignatureReceived()
{
    return m_IsCompleteWeldSignatureReceived;
}

void WeldSignatureACE::SetIsCompleteWeldSignatureReceived(bool Value)
{
    m_IsCompleteWeldSignatureReceived = Value;
}

bool WeldSignatureACE::GetIsAutoSaveGraphEnabled()
{
    return m_bIsAutoSaveGraphEnabled;
}

int WeldSignatureACE::GetGraphSamplingInterval()
{
    return m_GraphSamplingInterval;
}




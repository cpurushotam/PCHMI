/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE Horn Scan Result related implementation

***************************************************************************/
#include <cstring>
#include "HornScanResult.h"
#include "DataLogger.h"

size_t HornScanResult::static_log_id=0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
HornScanResult::HornScanResult()
{
    pthread_mutex_init(&m_HistoricalHornScanResultDataMutex, nullptr);
       
    //Send the request to read historical Horn Scan result data to ASC at power up of HMI
    m_SendHistoricalHornScanResultReadRequest = true;
       
    m_HornScanResultHistorySampleNumberToRead = 0;
    m_StartHornScanOperation = false;
    m_IsLastHornScanResultUpdated = false;
    m_AbortHornScanOperation = false;

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
HornScanResult::~HornScanResult()
{
    pthread_mutex_destroy(&m_HistoricalHornScanResultDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_HORN_SCAN_RESULT_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int HornScanResult::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

        if( (destination != nullptr) && (destination->id == MB_ID_HORN_SCAN_RESULT_DATA) )
        {
            switch(destination->sub_id)
            {
                //Send request to ASC to get the historical Horn Scan result data
                case READ_HISTORICAL_HORN_SCAN_RESULT_DATA:
				{
					retVal = 0;
                    sendHistoricalHornScanResultReadRequestToASC(destination);
					break;
				}
                case START_HORN_SCAN_OPERATION:
                {
                    retVal = 0;
                    SendStartHornScanOperationToASC(destination);
                    break;
                }
                case ABORT_HORN_SCAN_OPERATION:
                {
                	retVal = 0;
                	sendAbortHornScanOperationToASC(destination);
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
                    snprintf(msg,buff_size_config,"HornScanResult GetData default case");
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
            snprintf(msg,buff_size_config,"HornScanResult GetData invalid case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_HORN_SCAN_RESULT_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int HornScanResult::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_HORN_SCAN_RESULT_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                //Process response coming from ASC for last Horn Scan Result data
                case READ_LAST_HORN_SCAN_RESULT_DATA:
                {
                    retVal = 0;
                    processLastHornScanResultDataFromASC(source);
                    break;
                }
                
               //Process response coming from ASC for historical horn scan result data
               case READ_HISTORICAL_HORN_SCAN_RESULT_DATA:
			   {
				   retVal = 0;
                   processHistoricalHornScanResultDataFromASC(source);
				   break;
               }
               case SYNC_HORN_SCAN_RESULT_DATA:
               {
                   retVal = 0;
                   processHornScanResultDataFromASConDateTimeFormatChange();
                   break;
               }
			  default:
			  {
				char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"HornScanResult SetData default case");
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
        snprintf(msg,buff_size_config,"HornScanResult SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press Scan Run button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void HornScanResult::InitiateScanRunOperation()
{
    m_StartHornScanOperation = true;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press Scan Abort button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void HornScanResult::AbortScanRunOperation()
{
	m_AbortHornScanOperation = true;
}

/**************************************************************************//**
*
* \brief   - Retuns the historical scan result data.
*
* \param   - None.
*
* \return  - m_HistoricalHornScanResultData : Scan historical data.
*
******************************************************************************/
std::deque<HornScanResultstruct> HornScanResult::GetHistoricalHornScanResultData()
{
    return m_HistoricalHornScanResultData;
}

/**************************************************************************//**
*
* \brief   - Retuns the status of scan whether complete data read or not.
*
* \param   - None.
*
* \return  - m_IsLastHornScanResultUpdated : Scan data read status.
*
******************************************************************************/
bool HornScanResult::GetIsLastHornScanResultUpdated()
{
    return m_IsLastHornScanResultUpdated;
}

/**************************************************************************//**
*
* \brief   - Set the status of read scan that complete data read.
*
* \param   - Value : Scan data read status.
*
* \return  - None.
*
******************************************************************************/
void HornScanResult::SetIsLastHornScanResultUpdated(bool Value)
{
    m_IsLastHornScanResultUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - Send historical Horn Scan result read request to ASC on Power Up
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void HornScanResult::sendHistoricalHornScanResultReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_SendHistoricalHornScanResultReadRequest == true)
        {
        	int *Data = reinterpret_cast<int *>(destination->data);
            *Data = m_HornScanResultHistorySampleNumberToRead;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_SendHistoricalHornScanResultReadRequest = false;
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
* \brief   - process the historical horn scan result data coming from ASC
*
* \param   - source - memory block holding the historical horn scan result data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void HornScanResult::processHistoricalHornScanResultDataFromASC(const MEMORY_BLOCK *const source)
{
    int TotalSamples = *reinterpret_cast< int*>(source->data);
    bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
    HornScanResultstruct* HornScanResultData = reinterpret_cast< HornScanResultstruct*>(source->data + sizeof(int) + sizeof(bool));

    for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
    {
        m_HistoricalHornScanResultData.push_back(*HornScanResultData);
        HornScanResultData++;
    }

    m_HornScanResultHistorySampleNumberToRead = m_HornScanResultHistorySampleNumberToRead + TotalSamples;

    if(IsCompleteDataRead == true)
    {
        m_HornScanResultHistorySampleNumberToRead = 0;
        m_SendHistoricalHornScanResultReadRequest = false;
        m_IsLastHornScanResultUpdated = true;
    }
    else
    {
        m_SendHistoricalHornScanResultReadRequest = true;
    }
}
/**************************************************************************//**
*
* \brief   - Send a start horn scan Operation request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void HornScanResult::SendStartHornScanOperationToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_StartHornScanOperation == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_StartHornScanOperation = false;
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
* \brief   - Send abort horn scan operation request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void HornScanResult::sendAbortHornScanOperationToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_AbortHornScanOperation == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_AbortHornScanOperation = false;
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
* \brief   - process the last horn scan result data coming from ASC
*
* \param   - source - memory block holding the last horn scan result data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void HornScanResult::processLastHornScanResultDataFromASC(const MEMORY_BLOCK *const source)
{
    HornScanResultstruct* HornScanResultData = reinterpret_cast< HornScanResultstruct*>(source->data);

    pthread_mutex_lock(&m_HistoricalHornScanResultDataMutex);
    m_HistoricalHornScanResultData.push_front(*HornScanResultData);
    if(m_HistoricalHornScanResultData.size() > MAX_NUM_OF_HISTORICAL_HORN_SCAN_RESULTS_TO_SEND)
    {
        m_HistoricalHornScanResultData.pop_back();
    }
    pthread_mutex_unlock(&m_HistoricalHornScanResultDataMutex);
    m_IsLastHornScanResultUpdated = true;
}
/**************************************************************************//**
*
* \brief   - process the Service log read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void HornScanResult::processHornScanResultDataFromASConDateTimeFormatChange()
{
    m_HistoricalHornScanResultData.clear();
    m_HornScanResultHistorySampleNumberToRead = 0;
    m_SendHistoricalHornScanResultReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - print Historical Horn Scan Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void HornScanResult::printHistoricalHornScanResult()
{
    if(m_HistoricalHornScanResultData.empty())
    {
        std::cout << "No Historical Horn Scan Result Available" << std::endl;
    }
    else
    {
        pthread_mutex_lock(&m_HistoricalHornScanResultDataMutex);
        std::cout << "**********Historical Horn Scan Result Data**********" << std::endl;
        for (unsigned int Index = 0; Index < m_HistoricalHornScanResultData.size(); Index++)
        {
            std::cout << "HornScanResultIndex: " << m_HistoricalHornScanResultData[Index].HornScanResultIndex << std::endl;
            std::cout << "DateTime: " << m_HistoricalHornScanResultData[Index].DateTime << std::endl;
            std::cout << "MainParallelResonantFrequency: " << m_HistoricalHornScanResultData[Index].MainParallelResonantFrequency << std::endl;
            std::cout << "SecondParallelResonantFrequency: " << m_HistoricalHornScanResultData[Index].SecondParallelResonantFrequency << std::endl;
            std::cout << "ThirdParallelResonantFrequency: " << m_HistoricalHornScanResultData[Index].ThirdParallelResonantFrequency << std::endl;
            std::cout << "FirstSeriesResonantFrequency: " << m_HistoricalHornScanResultData[Index].FirstSeriesResonantFrequency << std::endl;
            std::cout << "SecondSeriesResonantFrequency: " << m_HistoricalHornScanResultData[Index].SecondSeriesResonantFrequency << std::endl;
            std::cout << "ThirdSeriesResonantFrequency: " << m_HistoricalHornScanResultData[Index].ThirdSeriesResonantFrequency << std::endl;
            std::cout << "*************************************" << std::endl;
        }
        pthread_mutex_unlock(&m_HistoricalHornScanResultDataMutex);
    }
}
/**************************************************************************//**
*
* \brief   - print Last Horn Scan Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void HornScanResult::printLastHornScanResult()
{
    if(m_HistoricalHornScanResultData.empty())
    {
        std::cout << "No Last Horn Scan Result Available" << std::endl;
    }
    else
    {
        pthread_mutex_lock(&m_HistoricalHornScanResultDataMutex);
        std::cout << "**********Last Horn Scan Result Data**********" << std::endl;

        std::cout << "HornScanResultIndex: " << m_HistoricalHornScanResultData.front().HornScanResultIndex << std::endl;
        std::cout << "DateTime: " << m_HistoricalHornScanResultData.front().DateTime << std::endl;
        std::cout << "MainParallelResonantFrequency: " << m_HistoricalHornScanResultData.front().MainParallelResonantFrequency << std::endl;
        std::cout << "SecondParallelResonantFrequency: " << m_HistoricalHornScanResultData.front().SecondParallelResonantFrequency << std::endl;
        std::cout << "ThirdParallelResonantFrequency: " << m_HistoricalHornScanResultData.front().ThirdParallelResonantFrequency << std::endl;
        std::cout << "FirstSeriesResonantFrequency: " << m_HistoricalHornScanResultData.front().FirstSeriesResonantFrequency << std::endl;
        std::cout << "SecondSeriesResonantFrequency: " << m_HistoricalHornScanResultData.front().SecondSeriesResonantFrequency << std::endl;
        std::cout << "ThirdSeriesResonantFrequency: " << m_HistoricalHornScanResultData.front().ThirdSeriesResonantFrequency << std::endl;
        std::cout << "*************************************" << std::endl;
        pthread_mutex_unlock(&m_HistoricalHornScanResultDataMutex);
    }
}

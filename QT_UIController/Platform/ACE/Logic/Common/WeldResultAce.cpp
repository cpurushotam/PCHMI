/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld result related implementation

***************************************************************************/
#include <cstring>
#include "WeldResultAce.h"
#include "DataLogger.h"

size_t WeldResultACE::static_log_id=0;

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
WeldResultACE::WeldResultACE()
{
    pthread_mutex_init(&m_HistoricalWeldResultDataMutex, nullptr);
    pthread_mutex_init(&m_SearchByCycleNumWeldResultDataMutex, nullptr);
    
    m_IsLastWeldResultUpdated = false;
    
    //Send the request to read historical weld result data to ASC at power up of HMI
    m_SendHistoricalWeldResultReadRequest = true;
    
    m_SendSearchByCycleNumWeldResultReadRequest = false;
    
    m_CycleNumToSearch = -1;
    m_WeldResultSampleNumberToRead = 0;
    m_WeldResultHistorySampleNumberToRead = 0;
    m_RequestNewCycleNumberData = false;

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
WeldResultACE::~WeldResultACE()
{
    pthread_mutex_destroy(&m_HistoricalWeldResultDataMutex);
    pthread_mutex_destroy(&m_SearchByCycleNumWeldResultDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_WELD_RESULT_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldResultACE::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

        if( (destination != nullptr) && (destination->id == MB_ID_WELD_RESULT_DATA) )
        {
            switch(destination->sub_id)
            {
                //Send request to ASC to get the historical weld result data
				case READ_HISTORICAL_WELD_RESULT_DATA:
				{
					retVal = 0;
					sendHistoricalWeldResultReadRequestToASC(destination);
					break;
				}
				break;
				
				//Send request to ASC to get the historical weld result data for cycle number
				case READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER:
				{
					retVal = 0;
					sendSearchByCycleNumWeldResultReadRequestToASC(destination);
					break;
				}
				break;
                default:
                {
                    // Error ! default retVal (failure) will be returned
                    // clear valid bit, reset size
                    destination->size = 0;
                    // clear valid bit
                    destination->config = 0;
                    char  msg[buff_size_config] = {0};
                    snprintf(msg,buff_size_config,"WeldResultACE GetData default case");
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
            snprintf(msg,buff_size_config,"WeldResultACE GetData invalid case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_WELD_RESULT_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldResultACE::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_WELD_RESULT_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                //Process response coming from ASC for last weld result data
                case READ_LAST_WELD_RESULT_DATA:
                {
                    retVal = 0;
                    processLastWeldResultDataFromASC(source);
                    break;
                }
                
               //Process response coming from ASC for historical weld result data
			   case READ_HISTORICAL_WELD_RESULT_DATA:
			   {
				   retVal = 0;
				   processHistoricalWeldResultDataFromASC(source);
				   break;
			   }
			   
			  //Process response coming from ASC for historical weld result data for cycle number
			  case READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER:
			  {
				  retVal = 0;
				  processSearchByCycleNumWeldResultDataFromASC(source);
				  break;
			  }
			  
			  //Process response coming from ASC to synch historical weld result data on unit change
			  case SYNCH_HISTORICAL_WELD_RESULT_DATA:
			  {
				  retVal = 0;
				  processSynchHistoricalWeldResultDataFromASC(source);
				  break;
              }
              //Process response coming from ASC to synch historical weld result data on DateTime format change
              case SYNCH_HISTORICAL_WELDRESULT_DATA_ON_DATETIME_FORMAT_CHANGE:
              {
                  retVal = 0;
                  processSynchHistoricalWeldResultDataFromASConDateTimeFormatChange();
                  break;
              }
			  default:
			  {
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config,"WeldResultACE SetData default case");
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
        snprintf(msg,buff_size_config,"WeldResultACE SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Send historical weld result read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void WeldResultACE::sendHistoricalWeldResultReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_SendHistoricalWeldResultReadRequest == true)
        {
        	int *Data = reinterpret_cast<int *>(destination->data);
        	*Data = m_WeldResultHistorySampleNumberToRead;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_SendHistoricalWeldResultReadRequest = false;
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
* \brief   - Send search by cycle number weld result read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void WeldResultACE::sendSearchByCycleNumWeldResultReadRequestToASC(MEMORY_BLOCK * const destination)
{
	if( destination->size >= ( sizeof( m_RequestNewCycleNumberData )  + sizeof( m_CycleNumToSearch ) + sizeof(m_WeldResultSampleNumberToRead) ) )
	{
		if( m_SendSearchByCycleNumWeldResultReadRequest == true )
		{
			destination->size = ( sizeof(m_RequestNewCycleNumberData)  + sizeof(m_CycleNumToSearch) + sizeof(m_WeldResultSampleNumberToRead) );
			destination->config = VALID_BIT;

			bool *RequestNewData = reinterpret_cast<bool *>(destination->data) ;
			//Set the RequestNewData flag to indicate that user has requested different weld cycle number data in case data transfer for different weld cycle is in progress.
			*RequestNewData = m_RequestNewCycleNumberData;

			if(m_RequestNewCycleNumberData == true)
			{
				//Clear contents of existing data in case user has requested data for different weld cycle number
				m_SearchByCycleNumWeldResultData.clear();
				m_WeldResultSampleNumberToRead = 0;
			}

			int *CycleNumberToSearch = reinterpret_cast<int *>(destination->data + sizeof(bool));
			//Set the Cycle Number To Search/
			*CycleNumberToSearch = m_CycleNumToSearch;

			//Set the WeldResult Sample Number to be read.
			int *WeldResultSampleNumberToRead = reinterpret_cast<int *>(destination->data + sizeof(bool) + sizeof(int));
			*WeldResultSampleNumberToRead = m_WeldResultSampleNumberToRead;

			//Reset the flag to false as we have sent the request.
			//Next request will go when we have received a response for previous request.
			m_SendSearchByCycleNumWeldResultReadRequest = false;

			//Reset the flag to false as we have sent the request.
			m_RequestNewCycleNumberData = false;
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
* 			 to read a particular cycle number.
*
*
* \param   - CycleNumber - CycleNumber for which the weld result
* 			needs to be fetched
*
* \return  - void
******************************************************************************/
void WeldResultACE::InitiateSearchByCycleNumReadRequestToASC(int CycleNumber)
{
	if(m_CycleNumToSearch != CycleNumber)
	{
		m_CycleNumToSearch = CycleNumber;
	
		//User has requested data for different cycle number
		m_RequestNewCycleNumberData = true;
		m_SendSearchByCycleNumWeldResultReadRequest = true;
    }
}

std::deque<WeldResultACEStruct> WeldResultACE::GetHistoricalWeldResultData()
{
    return m_HistoricalWeldResultData;
}

std::deque<WeldResultACEStruct> WeldResultACE::GetCycleNumWeldResultData()
{
    return m_SearchByCycleNumWeldResultData;
}

bool WeldResultACE::GetIsLastWeldResultUpdated()
{
    return m_IsLastWeldResultUpdated;
}

void WeldResultACE::SetIsLastWeldResultUpdated(bool Value)
{
    m_IsLastWeldResultUpdated = Value;
}

int WeldResultACE::GetHistoricalWeldResultDataSize()
{
    m_HistoricalWeldResultData.size();
}

int WeldResultACE::GetSearchByCycleNumWeldResultDataSize()
{
    m_SearchByCycleNumWeldResultData.size();
}

/**************************************************************************//**
*
* \brief   - process the last weld result data coming from ASC
*
* \param   - source - memory block holding the last weld result data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void WeldResultACE::processLastWeldResultDataFromASC(const MEMORY_BLOCK *const source)
{
	WeldResultACEStruct* WeldResultData = reinterpret_cast< WeldResultACEStruct*>(source->data);
	
	pthread_mutex_lock(&m_HistoricalWeldResultDataMutex);
	m_HistoricalWeldResultData.push_front(*WeldResultData);
	if(m_HistoricalWeldResultData.size() > MAX_NUM_OF_HISTORICAL_WELD_RESULTS_TO_SEND)
	{
		m_HistoricalWeldResultData.pop_back();
	}
	pthread_mutex_unlock(&m_HistoricalWeldResultDataMutex);
	m_IsLastWeldResultUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the historical weld result data coming from ASC
*
* \param   - source - memory block holding the historical weld result data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void WeldResultACE::processHistoricalWeldResultDataFromASC(const MEMORY_BLOCK *const source)
{
	int TotalSamples = *reinterpret_cast< int*>(source->data);
	bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
	WeldResultACEStruct* WeldResultData = reinterpret_cast< WeldResultACEStruct*>(source->data + sizeof(int) + sizeof(bool));

	for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
	{
		m_HistoricalWeldResultData.push_back(*WeldResultData);
		WeldResultData++;
	}

	m_WeldResultHistorySampleNumberToRead = m_WeldResultHistorySampleNumberToRead + TotalSamples;

	if(IsCompleteDataRead == true)
	{
		m_WeldResultHistorySampleNumberToRead = 0;
		m_SendHistoricalWeldResultReadRequest = false;
        m_IsLastWeldResultUpdated = true;
	}
	else
	{
		m_SendHistoricalWeldResultReadRequest = true;
	}
}

/**************************************************************************//**
*
* \brief   - process the requested cycle number weld result data coming from ASC
*
* \param   - source - memory block holding the requested weld result data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void WeldResultACE::processSearchByCycleNumWeldResultDataFromASC(const MEMORY_BLOCK *const source)
{
	//First byte from response contains CycleNumber to which the weld result belongs
	int CycleNumber = *reinterpret_cast< int*>(source->data);
	int TotalSamples = *reinterpret_cast< int*>(source->data + sizeof(int));
	bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int));
	WeldResultACEStruct* WeldResultData = reinterpret_cast< WeldResultACEStruct*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool));

	if(CycleNumber != m_CycleNumToSearch)
	{
		//Clear older data
		m_SearchByCycleNumWeldResultData.clear();
		m_WeldResultSampleNumberToRead = 0;
		m_SendSearchByCycleNumWeldResultReadRequest = true;
	}
	else
	{
		for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
		{
			m_SearchByCycleNumWeldResultData.push_back(*WeldResultData);
			WeldResultData++;
		}

		m_WeldResultSampleNumberToRead = m_WeldResultSampleNumberToRead + TotalSamples;

		if(IsCompleteDataRead == true)
		{
			m_CycleNumToSearch = -1;
			m_WeldResultSampleNumberToRead = 0;
			m_SendSearchByCycleNumWeldResultReadRequest = false;
            m_IsLastWeldResultUpdated = true;
		}
		else
		{
			m_SendSearchByCycleNumWeldResultReadRequest = true;
		}
	}
}

/**************************************************************************//**
*
* \brief   - process the requested re-synch historical weld result data coming from ASC
*
* \param   - source - memory block holding the requested weld result data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void WeldResultACE::processSynchHistoricalWeldResultDataFromASC(const MEMORY_BLOCK *const source)
{
	//Clear all the previous elements from the m_HistoricalWeldResultData deque.
    m_HistoricalWeldResultData.clear();
    m_WeldResultHistorySampleNumberToRead = 0;        
    
    //Set the historical weld result read request to true.
    m_SendHistoricalWeldResultReadRequest = true;
}

/**************************************************************************//**
*
* \brief   - process the requested re-synch historical weld result data coming from ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldResultACE::processSynchHistoricalWeldResultDataFromASConDateTimeFormatChange()
{
    //Clear all the previous elements from the m_HistoricalWeldResultData deque.
    m_HistoricalWeldResultData.clear();
    m_WeldResultHistorySampleNumberToRead = 0;
    //Set the historical weld result read request to true.
    m_SendHistoricalWeldResultReadRequest = true;
}

/**************************************************************************//**
*
* \brief   - print Historical Weld Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldResultACE::printHistoricalWeldResult()
{
	if(m_HistoricalWeldResultData.empty())
	{
		std::cout << "No Historical Weld Result Available" << std::endl;
	}
	else
	{
		pthread_mutex_lock(&m_HistoricalWeldResultDataMutex);
		std::cout << "**********Historical Weld Result Data**********" << std::endl;
		for (unsigned int Index = 0; Index < m_HistoricalWeldResultData.size(); Index++)
		{
			std::cout << "WeldResultIndex: " << m_HistoricalWeldResultData[Index].WeldResultIndex << std::endl;
			std::cout << "WeldRecipeNumber: " << m_HistoricalWeldResultData[Index].WeldRecipeNumber << std::endl;
			std::cout << "WeldRecipeVersionNumber: " << m_HistoricalWeldResultData[Index].WeldRecipeVersionNumber << std::endl;
			std::cout << "DateTime: " << m_HistoricalWeldResultData[Index].DateTime << std::endl;
			std::cout << "StackSerialNumber: " << m_HistoricalWeldResultData[Index].StackSerialNumber << std::endl;
			std::cout << "PowerSupplySerialNumber: " << m_HistoricalWeldResultData[Index].PowerSupplySerialNumber << std::endl;
			std::cout << "ActuatorSerialNumber: " << m_HistoricalWeldResultData[Index].ActuatorSerialNumber << std::endl;
			std::cout << "ASCSerialNumber: " << m_HistoricalWeldResultData[Index].ASCSerialNumber << std::endl;
			std::cout << "CycleCounter: " << m_HistoricalWeldResultData[Index].CycleCounter << std::endl;
			std::cout << "WeldMode: " << m_HistoricalWeldResultData[Index].WeldMode << std::endl;
			std::cout << "WeldTime: " << m_HistoricalWeldResultData[Index].WeldTime << std::endl;
			std::cout << "HoldTime: " << m_HistoricalWeldResultData[Index].HoldTime << std::endl;
			std::cout << "WeldEnergy: " << m_HistoricalWeldResultData[Index].WeldEnergy << std::endl;
			std::cout << "WeldPeakPower: " << m_HistoricalWeldResultData[Index].WeldPeakPower << std::endl;
			std::cout << "StartFrequency: " << m_HistoricalWeldResultData[Index].StartFrequency << std::endl;
			std::cout << "FrequencyChange: " << m_HistoricalWeldResultData[Index].FrequencyChange << std::endl;
			std::cout << "CycleTime: " << m_HistoricalWeldResultData[Index].CycleTime << std::endl;
			std::cout << "UserName: " << m_HistoricalWeldResultData[Index].UserName << std::endl;
			std::cout << "PartID: " << m_HistoricalWeldResultData[Index].PartID << std::endl;
			std::cout << "BatchID: " << m_HistoricalWeldResultData[Index].BatchID << std::endl;
			std::cout << "TriggerPoint: " << m_HistoricalWeldResultData[Index].TriggerPoint	 << std::endl;
			std::cout << "WeldSonicPoint: " << m_HistoricalWeldResultData[Index].WeldSonicPoint << std::endl;
			std::cout << "HoldPoint: " << m_HistoricalWeldResultData[Index].HoldPoint << std::endl;
			std::cout << "AlarmID: " << m_HistoricalWeldResultData[Index].AlarmID << std::endl;
			std::cout << "WeldStatus: " << m_HistoricalWeldResultData[Index].WeldStatus << std::endl;
			std::cout << "RecipeStatus: " << m_HistoricalWeldResultData[Index].RecipeStatus << std::endl;
			std::cout << "WeldPressure: " << m_HistoricalWeldResultData[Index].WeldPressure << std::endl;
			std::cout << "HoldPressure: " << m_HistoricalWeldResultData[Index].HoldPressure << std::endl;
			std::cout << "MaxWeldForce: " << m_HistoricalWeldResultData[Index].MaxWeldForce << std::endl;
			std::cout << "MaxHoldForce: " << m_HistoricalWeldResultData[Index].MaxHoldForce << std::endl;
			std::cout << "EndWeldForce: " << m_HistoricalWeldResultData[Index].EndWeldForce << std::endl;
			std::cout << "EndHoldForce: " << m_HistoricalWeldResultData[Index].EndHoldForce << std::endl;
			std::cout << "WeldAbsolute: " << m_HistoricalWeldResultData[Index].WeldAbsolute << std::endl;
			std::cout << "TotalAbsolute: " << m_HistoricalWeldResultData[Index].TotalAbsolute << std::endl;
			std::cout << "Velocity: " << m_HistoricalWeldResultData[Index].Velocity << std::endl;
			std::cout << "DownSpeed: " << m_HistoricalWeldResultData[Index].DownSpeed << std::endl;
			std::cout << "TriggerDistance: " << m_HistoricalWeldResultData[Index].TriggerDistance << std::endl;
			std::cout << "WeldCollapseDistance: " << m_HistoricalWeldResultData[Index].WeldCollapseDistance << std::endl;
			std::cout << "HoldCollapseDistance: " << m_HistoricalWeldResultData[Index].HoldCollapseDistance << std::endl;
			std::cout << "TotalCollapseDistance: " << m_HistoricalWeldResultData[Index].TotalCollapseDistance << std::endl;
			std::cout << "*************************************" << std::endl;
		}
		pthread_mutex_unlock(&m_HistoricalWeldResultDataMutex);
	}
}


/**************************************************************************//**
*
* \brief   - print Last Weld Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldResultACE::printLastWeldResult()
{
	if(m_HistoricalWeldResultData.empty())
	{
		std::cout << "No Last Weld Result Available" << std::endl;
	}
	else
	{
		pthread_mutex_lock(&m_HistoricalWeldResultDataMutex);
		std::cout << "**********Last Weld Result Data**********" << std::endl;

		std::cout << "WeldResultIndex: " << m_HistoricalWeldResultData.front().WeldResultIndex << std::endl;
		std::cout << "WeldRecipeNumber: " << m_HistoricalWeldResultData.front().WeldRecipeNumber << std::endl;
		std::cout << "WeldRecipeVersionNumber: " << m_HistoricalWeldResultData.front().WeldRecipeVersionNumber << std::endl;
		std::cout << "DateTime: " << m_HistoricalWeldResultData.front().DateTime << std::endl;
		std::cout << "StackSerialNumber: " << m_HistoricalWeldResultData.front().StackSerialNumber << std::endl;
		std::cout << "PowerSupplySerialNumber: " << m_HistoricalWeldResultData.front().PowerSupplySerialNumber << std::endl;
		std::cout << "ActuatorSerialNumber: " << m_HistoricalWeldResultData.front().ActuatorSerialNumber << std::endl;
		std::cout << "ASCSerialNumber: " << m_HistoricalWeldResultData.front().ASCSerialNumber << std::endl;
		std::cout << "CycleCounter: " << m_HistoricalWeldResultData.front().CycleCounter << std::endl;
		std::cout << "WeldMode: " << m_HistoricalWeldResultData.front().WeldMode << std::endl;
		std::cout << "WeldTime: " << m_HistoricalWeldResultData.front().WeldTime << std::endl;
		std::cout << "HoldTime: " << m_HistoricalWeldResultData.front().HoldTime << std::endl;
		std::cout << "WeldEnergy: " << m_HistoricalWeldResultData.front().WeldEnergy << std::endl;
		std::cout << "WeldPeakPower: " << m_HistoricalWeldResultData.front().WeldPeakPower << std::endl;
		std::cout << "StartFrequency: " << m_HistoricalWeldResultData.front().StartFrequency << std::endl;
		std::cout << "FrequencyChange: " << m_HistoricalWeldResultData.front().FrequencyChange << std::endl;
		std::cout << "CycleTime: " << m_HistoricalWeldResultData.front().CycleTime << std::endl;
		std::cout << "UserName: " << m_HistoricalWeldResultData.front().UserName << std::endl;
		std::cout << "PartID: " << m_HistoricalWeldResultData.front().PartID << std::endl;
		std::cout << "BatchID: " << m_HistoricalWeldResultData.front().BatchID << std::endl;
		std::cout << "TriggerPoint: " << m_HistoricalWeldResultData.front().TriggerPoint	 << std::endl;
		std::cout << "WeldSonicPoint: " << m_HistoricalWeldResultData.front().WeldSonicPoint << std::endl;
		std::cout << "HoldPoint: " << m_HistoricalWeldResultData.front().HoldPoint << std::endl;
		std::cout << "AlarmID: " << m_HistoricalWeldResultData.front().AlarmID << std::endl;
		std::cout << "WeldStatus: " << m_HistoricalWeldResultData.front().WeldStatus << std::endl;
		std::cout << "RecipeStatus: " << m_HistoricalWeldResultData.front().RecipeStatus << std::endl;
		std::cout << "WeldPressure: " << m_HistoricalWeldResultData.front().WeldPressure << std::endl;
		std::cout << "HoldPressure: " << m_HistoricalWeldResultData.front().HoldPressure << std::endl;
		std::cout << "MaxWeldForce: " << m_HistoricalWeldResultData.front().MaxWeldForce << std::endl;
		std::cout << "MaxHoldForce: " <<  m_HistoricalWeldResultData.front().MaxHoldForce << std::endl;
		std::cout << "EndWeldForce: " <<  m_HistoricalWeldResultData.front().EndWeldForce << std::endl;
		std::cout << "EndHoldForce: " << m_HistoricalWeldResultData.front().EndHoldForce << std::endl;
		std::cout << "WeldAbsolute: " << m_HistoricalWeldResultData.front().WeldAbsolute << std::endl;
		std::cout << "TotalAbsolute: " << m_HistoricalWeldResultData.front().TotalAbsolute << std::endl;
		std::cout << "Velocity: " << m_HistoricalWeldResultData.front().Velocity << std::endl;
		std::cout << "DownSpeed: " << m_HistoricalWeldResultData.front().DownSpeed << std::endl;
		std::cout << "TriggerDistance: " << m_HistoricalWeldResultData.front().TriggerDistance << std::endl;
		std::cout << "WeldCollapseDistance: " << m_HistoricalWeldResultData.front().WeldCollapseDistance << std::endl;
		std::cout << "HoldCollapseDistance: " << m_HistoricalWeldResultData.front().HoldCollapseDistance << std::endl;
		std::cout << "TotalCollapseDistance: " << m_HistoricalWeldResultData.front().TotalCollapseDistance << std::endl;
		std::cout << "*************************************" << std::endl;
		pthread_mutex_unlock(&m_HistoricalWeldResultDataMutex);
	}
}

/**************************************************************************//**
*
* \brief   - print search by cycle number Weld Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldResultACE::printSearchByCycleNumberdWeldResult()
{
	if(m_SearchByCycleNumWeldResultData.empty())
	{
		std::cout << "No Weld Result Available for searched cycle number" << std::endl;
	}
	else
	{
		pthread_mutex_lock(&m_SearchByCycleNumWeldResultDataMutex);
		std::cout << "**********searched cycle number Weld Result Data**********" << std::endl;

		for (unsigned int Index = 0; Index < m_SearchByCycleNumWeldResultData.size(); Index++)
		{
			std::cout << "WeldResultIndex: " << m_SearchByCycleNumWeldResultData[Index].WeldResultIndex << std::endl;
			std::cout << "WeldRecipeNumber: " << m_SearchByCycleNumWeldResultData[Index].WeldRecipeNumber << std::endl;
			std::cout << "WeldRecipeVersionNumber: " << m_SearchByCycleNumWeldResultData[Index].WeldRecipeVersionNumber << std::endl;
			std::cout << "DateTime: " << m_SearchByCycleNumWeldResultData[Index].DateTime << std::endl;
			std::cout << "StackSerialNumber: " << m_SearchByCycleNumWeldResultData[Index].StackSerialNumber << std::endl;
			std::cout << "PowerSupplySerialNumber: " << m_SearchByCycleNumWeldResultData[Index].PowerSupplySerialNumber << std::endl;
			std::cout << "ActuatorSerialNumber: " << m_SearchByCycleNumWeldResultData[Index].ActuatorSerialNumber << std::endl;
			std::cout << "ASCSerialNumber: " << m_SearchByCycleNumWeldResultData[Index].ASCSerialNumber << std::endl;
			std::cout << "CycleCounter: " << m_SearchByCycleNumWeldResultData[Index].CycleCounter << std::endl;
			std::cout << "WeldMode: " << m_SearchByCycleNumWeldResultData[Index].WeldMode << std::endl;
			std::cout << "WeldTime: " << m_SearchByCycleNumWeldResultData[Index].WeldTime << std::endl;
			std::cout << "HoldTime: " << m_SearchByCycleNumWeldResultData[Index].HoldTime << std::endl;
			std::cout << "WeldEnergy: " << m_SearchByCycleNumWeldResultData[Index].WeldEnergy << std::endl;
			std::cout << "WeldPeakPower: " << m_SearchByCycleNumWeldResultData[Index].WeldPeakPower << std::endl;
			std::cout << "StartFrequency: " << m_SearchByCycleNumWeldResultData[Index].StartFrequency << std::endl;
			std::cout << "FrequencyChange: " << m_SearchByCycleNumWeldResultData[Index].FrequencyChange << std::endl;
			std::cout << "CycleTime: " << m_SearchByCycleNumWeldResultData[Index].CycleTime << std::endl;
			std::cout << "UserName: " << m_SearchByCycleNumWeldResultData[Index].UserName << std::endl;
			std::cout << "PartID: " << m_SearchByCycleNumWeldResultData[Index].PartID << std::endl;
			std::cout << "BatchID: " << m_SearchByCycleNumWeldResultData[Index].BatchID << std::endl;
			std::cout << "TriggerPoint: " << m_SearchByCycleNumWeldResultData[Index].TriggerPoint	 << std::endl;
			std::cout << "WeldSonicPoint: " << m_SearchByCycleNumWeldResultData[Index].WeldSonicPoint << std::endl;
			std::cout << "HoldPoint: " << m_SearchByCycleNumWeldResultData[Index].HoldPoint << std::endl;
			std::cout << "AlarmID: " << m_SearchByCycleNumWeldResultData[Index].AlarmID << std::endl;
			std::cout << "WeldStatus: " << m_SearchByCycleNumWeldResultData[Index].WeldStatus << std::endl;
			std::cout << "RecipeStatus: " << m_SearchByCycleNumWeldResultData[Index].RecipeStatus << std::endl;
			std::cout << "WeldPressure: " << m_SearchByCycleNumWeldResultData[Index].WeldPressure << std::endl;
			std::cout << "HoldPressure: " << m_SearchByCycleNumWeldResultData[Index].HoldPressure << std::endl;
			std::cout << "MaxWeldForce: " << m_SearchByCycleNumWeldResultData[Index].MaxWeldForce << std::endl;
			std::cout << "MaxHoldForce: " << m_SearchByCycleNumWeldResultData[Index].MaxHoldForce << std::endl;
			std::cout << "EndWeldForce: " <<m_SearchByCycleNumWeldResultData[Index].EndWeldForce << std::endl;
			std::cout << "EndHoldForce: " << m_SearchByCycleNumWeldResultData[Index].EndHoldForce << std::endl;
			std::cout << "WeldAbsolute: " << m_SearchByCycleNumWeldResultData[Index].WeldAbsolute << std::endl;
			std::cout << "TotalAbsolute: " << m_SearchByCycleNumWeldResultData[Index].TotalAbsolute << std::endl;
			std::cout << "Velocity: " << m_SearchByCycleNumWeldResultData[Index].Velocity << std::endl;
			std::cout << "DownSpeed: " << m_SearchByCycleNumWeldResultData[Index].DownSpeed << std::endl;
			std::cout << "TriggerDistance: " << m_SearchByCycleNumWeldResultData[Index].TriggerDistance << std::endl;
			std::cout << "WeldCollapseDistance: " << m_SearchByCycleNumWeldResultData[Index].WeldCollapseDistance << std::endl;
			std::cout << "HoldCollapseDistance: " << m_SearchByCycleNumWeldResultData[Index].HoldCollapseDistance << std::endl;
			std::cout << "TotalCollapseDistance: " << m_SearchByCycleNumWeldResultData[Index].TotalCollapseDistance << std::endl;
			std::cout << "*************************************" << std::endl;
		}
		pthread_mutex_unlock(&m_SearchByCycleNumWeldResultDataMutex);
	}
}



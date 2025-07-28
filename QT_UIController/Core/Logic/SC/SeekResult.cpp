/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Seek result related implementation

***************************************************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string.h>
#include "SeekResult.h"
#include "DataLogger.h"
/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

SeekResult::SeekResult()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    pthread_mutex_init(&m_SeekResultDataMutex, nullptr);
    //Send the request to read seek result data to ASC at power up of HMI
    m_InitiateSeekRunOperation = false;
    m_InitiateSeekReadOnPowerUp = true;
}


/**************************************************************************//**
*
* \brief   - destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
SeekResult::~SeekResult()
{
	pthread_mutex_destroy(&m_SeekResultDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_SEEK_RESULT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SeekResult::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_SEEK_RESULT_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			case SEEK_RUN_OPERATION:
			{
				retVal =0;
				SendSeekRunOperationToASC(destination);
				break;
			}
            case SEEK_RESULT_DATA:
            {
                retVal =0;
                SendSeekResultReadRequestToASC(destination);
                break;
            }
			default:
			{
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "seekResult:GetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "seekRecipe:GetData invalid req");

	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_SEEK_RESULT_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SeekResult::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_SEEK_RESULT_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
                case SEEK_RESULT_DATA:
                {
                    retVal = 0;
                    processSeekResultReadResponseFromASC(source);
                    break;
                }
                case SYNC_SEEK_RESULT_DATA:
                {
                    retVal = 0;
                    processSyncSeekResultonDateTimeFormatChg();
                    break;
                }
				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SeekResult:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SeekResult:SetData invalid req");
	}

	return (retVal);

}

/*
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press Seek Run button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void SeekResult::InitiateSeekRunOperation()
{
    m_InitiateSeekRunOperation = true;
}

/**************************************************************************//**
*
* \brief   - This function returns seek structure parameters.
*
* \param   - None.
*
* \return  - m_SeekResultData : The seek structure parameters.
*
******************************************************************************/
SeekResultstruct SeekResult::GetSeekResultData()
{
    return m_SeekResultData;
}

/**************************************************************************//**
*
* \brief   - Send a seek Run Operation request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SeekResult::SendSeekRunOperationToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateSeekRunOperation == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateSeekRunOperation = false;
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
* \brief   - Send a seek result read request on power up to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SeekResult::SendSeekResultReadRequestToASC(MEMORY_BLOCK * const destination)
{ 
        if(destination->size >= sizeof(int))
        {
            if(m_InitiateSeekReadOnPowerUp == true )
            {
                destination->size = sizeof(int);
                destination->config = VALID_BIT;
                m_InitiateSeekReadOnPowerUp = false;
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
* \brief   - process the read Seek result response coming from ASC
*
* \param   - source - memory block holding the seek result data received from ASC
*
* \return  - none
*
******************************************************************************/
void SeekResult::processSeekResultReadResponseFromASC(const MEMORY_BLOCK *const source)
{
    //copy incoming data to structure member variable
    SeekResultstruct *SeekResultData = reinterpret_cast<SeekResultstruct *>(source->data);
    pthread_mutex_lock(&m_SeekResultDataMutex);
    memcpy(&m_SeekResultData, SeekResultData, sizeof(SeekResultstruct));
    pthread_mutex_unlock(&m_SeekResultDataMutex);
}

/**************************************************************************//**
*
* \brief   - process the SeekResult list read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SeekResult::processSyncSeekResultonDateTimeFormatChg()
{
    m_InitiateSeekReadOnPowerUp = true;
}
/**************************************************************************//**
*
* \brief   - show the seek result data for last seek operation
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SeekResult::ShowSeekResult()
{
    if(sizeof(m_SeekResultData) == 0)
    {
        std::cout << "Requested Seek result is empty" << std::endl;
    }
    else
    {
        std::cout << "m_SeekResultData.PeakPower: "  << m_SeekResultData.PeakPower << std::endl;
        std::cout << "m_SeekResultData.StartFrequency: "  << m_SeekResultData.StartFrequency << std::endl;
        std::cout << "m_SeekResultData.EndFrequency: "  << m_SeekResultData.EndFrequency << std::endl;
        std::cout << "m_SeekResultData.DateTime: "  << m_SeekResultData.DateTime << std::endl;
        std::cout << "m_SeekResultData.SeekResultIndex: "  << m_SeekResultData.SeekResultIndex << std::endl;
    }
}


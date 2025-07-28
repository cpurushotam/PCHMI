/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Seek recipe related implementation

***************************************************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string.h>
#include "SeekRecipe.h"
#include "DataLogger.h"
#include "PowerLevelSysFrequencySupport.h"
/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

SeekRecipe::SeekRecipe()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    pthread_mutex_init(&m_SeekRecipeDataMutex, nullptr);
    m_InitiateRecipeSaveRequest = false;
    m_InitiateRecipeReseToDefaultRequest = false;
    //Send the request to read seek recipe data to ASC at power up of HMI
    m_InitiateRecipeReadRequest = true;
    m_IsSeekRecipeUpdated = false;

}
/**************************************************************************//**
*
* \brief   - Constructor
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
SeekRecipestruct::SeekRecipestruct()
{
	
}

/**************************************************************************//**
*
* \brief   - Set Parameters as per System Frequency.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void SeekRecipestruct::SetParametersAsPerSystemFrequency()
{
	//TODO:HMI side Empty function for now 
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
SeekRecipe::~SeekRecipe()
{
	pthread_mutex_destroy(&m_SeekRecipeDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_SEEK_RECIPE_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SeekRecipe::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_SEEK_RECIPE_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			case SEEK_RECIPE_SAVE:
			{			
				retVal = 0;
				sendSeekRecipeSaveRequestToASC(destination);				
				break;
			}
			case SEEK_RECIPE_RESET_TO_DEFAULT:
			{
				retVal = 0;
				sendSeekRecipeRestToDefaultRequestToASC(destination);
				break;
			}
			case SEEK_RECIPE_DATA:
			{
				retVal =0;
				SendRecipeReadRequestToASC(destination);
				break;
			}
			default:
			{
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "seekRecipe:GetData default");
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
* \brief   - process the data coming from ASC for memory block ID MB_ID_SEEK_RECIPE_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SeekRecipe::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_SEEK_RECIPE_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for Seek Recipe Data
				case SEEK_RECIPE_DATA:
				{
					retVal = 0;
					processRecipeReadResponseFromASC(source);
					break;
				}
				
				case SEEK_RECIPE_UPDATE_RESULT:
				{
					retVal = 0;
					processRecipeUpdateStatusFromASC(source);
					break;
				}

				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "seekRecipe:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "seekRecipe:SetData invalid req");
	}

	return (retVal);

}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click save button.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void SeekRecipe::InitiateRecipeSaveRequest()
{
    m_InitiateRecipeSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   - This function returns seek recipe data parameters.
*
* \param   - None.
*
* \return  - m_SeekRecipeData : The seek recipe data parameters.
*
******************************************************************************/
SeekRecipestruct SeekRecipe::GetSeekRecipeData()
{
    return m_SeekRecipeData;
}

/**************************************************************************//**
*
* \brief   - Retuns the status the seek recipe update.
*
* \param   - None.
*
* \return  - m_IsSeekRecipeUpdated : The seek recipe update status.
*
******************************************************************************/
bool SeekRecipe::GetIsSeekRecipeUpdated()
{
    return m_IsSeekRecipeUpdated;
}

/**************************************************************************//**
*
* \brief   - Sets the status of the seek recipe update.
*
* \param   - Value : Status flag value from interface.
*
* \return  - None.
*
******************************************************************************/
void SeekRecipe::SetIsSeekRecipeUpdated(bool Value)
{
    m_IsSeekRecipeUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - This function saves seek recipe data parameters.
*
* \param   - m_SeekRecipeStruct : The seek recipe data parameters.
*
* \return  - None.
*
******************************************************************************/
void SeekRecipe::SetSeekRecipeData(SeekRecipestruct m_SeekRecipeStruct)
{
    m_SeekRecipeData = m_SeekRecipeStruct;
    InitiateRecipeSaveRequest();
}

/**************************************************************************//**
*
* \brief   - Get the maximum value for passed parameter ID
*
* \param   - ParamID - Seek Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string SeekRecipe::GetSeekRecipeParamMinValue(SEEK_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator = SeekRecipeParamMap.find(ParamID);
    if (MapIterator != SeekRecipeParamMap.end())
    {
        //Get the system frequency and update Max value according to paramID
        switch(PowerLevelSysFrequencySupport::GetSystemFrequencyFromJSON())
        {
        case FREQ_20KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MIN_VALUE_20K>(MapTuple);
        }
        break;
        case FREQ_30KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MIN_VALUE_30K>(MapTuple);
        }
        break;
        case FREQ_40KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MIN_VALUE_40K>(MapTuple);
        }
        break;
        default:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MIN_VALUE_20K>(MapTuple);
        }
        break;
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ParamID3 not found");
    }

    return Value;
}

/**************************************************************************//**
*
* \brief   - Get the maximum value for passed parameter ID
*
* \param   - ParamID - Seek Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string SeekRecipe::GetSeekRecipeParamMaxValue(SEEK_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator = SeekRecipeParamMap.find(ParamID);
    if (MapIterator != SeekRecipeParamMap.end())
    {
        //Get the system frequency and update Max value according to paramID
        switch(PowerLevelSysFrequencySupport::GetSystemFrequencyFromJSON())
        {
        case FREQ_20KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MAX_VALUE_20K>(MapTuple);
        }
        break;
        case FREQ_30KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MAX_VALUE_30K>(MapTuple);
        }
        break;
        case FREQ_40KHZ:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MAX_VALUE_40K>(MapTuple);
        }
        break;
        default:
        {
            auto MapTuple = MapIterator->second;
            Value = std::get<MAX_VALUE_20K>(MapTuple);
        }
        break;
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ParamID3 not found");
    }

    return Value;
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_SEEK_RECIPE_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void SeekRecipe::sendSeekRecipeSaveRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >=sizeof(SeekRecipestruct))
    {
        if(m_InitiateRecipeSaveRequest == true)
        {
            // update size in destination
            destination->size = sizeof(SeekRecipestruct);

            // set valid bit
            destination->config = VALID_BIT;
            m_InitiateRecipeSaveRequest = false;

            SeekRecipestruct *RecipeData = reinterpret_cast<SeekRecipestruct *>(destination->data);

            pthread_mutex_lock(&m_SeekRecipeDataMutex);

            RecipeData->SeekFreqLimitHigh = m_SeekRecipeData.SeekFreqLimitHigh;
            RecipeData->SeekFreqLimitLow = m_SeekRecipeData.SeekFreqLimitLow;
            RecipeData->SeekFreqOffset = m_SeekRecipeData.SeekFreqOffset;
            RecipeData->SeekMemClearBeforeSeek = m_SeekRecipeData.SeekMemClearBeforeSeek;
            RecipeData->SeekTime = m_SeekRecipeData.SeekTime;
            RecipeData->SeekAmplitudeRampTime = m_SeekRecipeData.SeekAmplitudeRampTime;
            RecipeData->SeekAmplitude = m_SeekRecipeData.SeekAmplitude;
            RecipeData->SeekAmpProportionalGain = m_SeekRecipeData.SeekAmpProportionalGain;
            RecipeData->SeekAmpIntegralGain = m_SeekRecipeData.SeekAmpIntegralGain;
            RecipeData->SeekAmpDerivativeGain = m_SeekRecipeData.SeekAmpDerivativeGain;
            RecipeData->SeekPhaseProportionalGain = m_SeekRecipeData.SeekPhaseProportionalGain;
            RecipeData->SeekPhaseIntegralGain = m_SeekRecipeData.SeekPhaseIntegralGain;
            RecipeData->SeekPhaseDerivativeGain = m_SeekRecipeData.SeekPhaseDerivativeGain;
            RecipeData->BlindtimeSeek = m_SeekRecipeData.BlindtimeSeek;
            RecipeData->SeekPhaseloopCF = m_SeekRecipeData.SeekPhaseloopCF;

            pthread_mutex_unlock(&m_SeekRecipeDataMutex);
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
* \brief   - Send a reset to default recipe request to ASC.
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  - None
*
******************************************************************************/
void SeekRecipe::sendSeekRecipeRestToDefaultRequestToASC(MEMORY_BLOCK * const destination)
{
    if (destination->size >= sizeof(int))
    {
        if( m_InitiateRecipeReseToDefaultRequest == true )
        {
            destination->data = 0;
            // update size in destination
            destination->size = sizeof(int);

            // set valid bit
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateRecipeReseToDefaultRequest = false;
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
* \brief   - this function will set m_InitiateRecipeReseToDefaultRequest to true .
*			 i.e Reset to default request will send .
*
*
* \param   - NA
*
* \return  - void
******************************************************************************/
void SeekRecipe::InitiateResetToDefaultSeekRequest()
{
	m_InitiateRecipeReseToDefaultRequest = true;
}

/**************************************************************************//**
*
* \brief   - Send a seek recipe read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SeekRecipe::SendRecipeReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateRecipeReadRequest == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateRecipeReadRequest = false;
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
* \brief   - process the read recipe response coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void SeekRecipe::processRecipeReadResponseFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	SeekRecipestruct *RecipeData = reinterpret_cast<SeekRecipestruct *>(source->data);

	pthread_mutex_lock(&m_SeekRecipeDataMutex);

    m_SeekRecipeData.SeekFreqLimitHigh = RecipeData->SeekFreqLimitHigh;
	m_SeekRecipeData.SeekFreqLimitLow = RecipeData->SeekFreqLimitLow;
	m_SeekRecipeData.SeekFreqOffset = RecipeData->SeekFreqOffset;
	m_SeekRecipeData.SeekMemClearBeforeSeek = RecipeData->SeekMemClearBeforeSeek;
	m_SeekRecipeData.SeekTime = RecipeData->SeekTime;
	m_SeekRecipeData.SeekAmplitudeRampTime = RecipeData->SeekAmplitudeRampTime;
	m_SeekRecipeData.SeekAmplitude = RecipeData->SeekAmplitude;
	m_SeekRecipeData.SeekAmpProportionalGain = RecipeData->SeekAmpProportionalGain;
	m_SeekRecipeData.SeekAmpIntegralGain = 	RecipeData->SeekAmpIntegralGain;
	m_SeekRecipeData.SeekAmpDerivativeGain = RecipeData->SeekAmpDerivativeGain;
	m_SeekRecipeData.SeekPhaseProportionalGain = RecipeData->SeekPhaseProportionalGain;
	m_SeekRecipeData.SeekPhaseIntegralGain = RecipeData->SeekPhaseIntegralGain;
	m_SeekRecipeData.SeekPhaseDerivativeGain = RecipeData->SeekPhaseDerivativeGain;
	m_SeekRecipeData.BlindtimeSeek = RecipeData->BlindtimeSeek;
	m_SeekRecipeData.SeekPhaseloopCF = RecipeData->SeekPhaseloopCF;

    m_IsSeekRecipeUpdated = true;

	pthread_mutex_unlock(&m_SeekRecipeDataMutex);
}

/**************************************************************************//**
*
* \brief   - process the seek recipe update status coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void SeekRecipe::processRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source)
{
	SEEK_RECIPE_UPDATE_STATUS RecipeUpdateStatus = static_cast<SEEK_RECIPE_UPDATE_STATUS>(*source->data);

	//Copy seek recipe updated status
	m_seekRecipeStatus = RecipeUpdateStatus;
}

/**************************************************************************//**
*
* \brief   - Show Seek Recipe Data
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void SeekRecipe::ShowSeekRecipe()
{
	std::cout << "SeekFreqLimitHigh: " << m_SeekRecipeData.SeekFreqLimitHigh << std::endl;
	std::cout << "SeekFreqLimitLow: " << m_SeekRecipeData.SeekFreqLimitLow << std::endl;
	std::cout << "SeekFreqOffset: " << m_SeekRecipeData.SeekFreqOffset << std::endl;
	std::cout << "SeekMemClearBeforeSeek: " << m_SeekRecipeData.SeekMemClearBeforeSeek << std::endl;
	std::cout << "SeekTime: " << m_SeekRecipeData.SeekTime << std::endl;
	std::cout << "SeekAmplitudeRampTime: " << m_SeekRecipeData.SeekAmplitudeRampTime << std::endl;
	std::cout << "SeekAmplitude: " << m_SeekRecipeData.SeekAmplitude << std::endl;
	std::cout << "SeekAmpProportionalGain: " << m_SeekRecipeData.SeekAmpProportionalGain << std::endl;
	std::cout << "SeekAmpIntegralGain: " << m_SeekRecipeData.SeekAmpIntegralGain << std::endl;
	std::cout << "SeekAmpDerivativeGain: " << m_SeekRecipeData.SeekAmpDerivativeGain << std::endl;
	std::cout << "SeekPhaseProportionalGain: " << m_SeekRecipeData.SeekPhaseProportionalGain << std::endl;
	std::cout << "SeekPhaseIntegralGain: " << m_SeekRecipeData.SeekPhaseIntegralGain << std::endl;
	std::cout << "SeekPhaseDerivativeGain: " << m_SeekRecipeData.SeekPhaseDerivativeGain << std::endl;
	std::cout << "BlindtimeSeek: " << m_SeekRecipeData.BlindtimeSeek << std::endl;
	std::cout << "SeekPhaseloopCF: " << m_SeekRecipeData.SeekPhaseloopCF << std::endl;
}

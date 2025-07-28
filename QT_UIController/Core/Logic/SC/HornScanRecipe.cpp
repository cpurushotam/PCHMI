/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------
	 It contains the Horn  Scan recipe related implementation

**********************************************************************************************************/
#include "HornScanRecipe.h"
#include "PowerLevelSysFrequencySupport.h"
#include "DataLogger.h"
#include <cstring>

/* init log variable */
size_t HornScanRecipe::m_hslog_id = 0 ;
/**************************************************************************//**
*
* \brief   - Horn Scan constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
HornScanRecipe::HornScanRecipe()
{
	/* enroll to use logger functionality */
    m_hslog_id = Logger::enroll(this);
	/* Init pthread with NUll*/
	pthread_mutex_init(&m_hornScanDataMutex, nullptr);
	m_InitiateRecipeSaveRequest = false;
	m_InitiateRecipeResetToDefaultRequest = false;
    //Send the request to read horn scan recipe data to ASC at power up of HMI
    m_InitiateRecipeReadRequest = true ;
    m_IsHornScanRecipeUpdated = false;
}

/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
structHornScanRecipe::structHornScanRecipe()
{
	//Empty on HMI side
}

/**************************************************************************//**
*
* \brief   - Horn Scan destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
HornScanRecipe::~HornScanRecipe()
{
   /* destroy pthread mutex */
	pthread_mutex_destroy(&m_hornScanDataMutex);
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
void HornScanRecipe::InitiateRecipeSaveRequest(structHornScanRecipe RecipeData)
{
    m_HornScanRecipe = RecipeData;
	m_InitiateRecipeSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   -HMI/QML should call this function when it wants to send the 
* 	        request to ASC to reset the horn scan recipe to default values
* 	        
* \param   - None
*
* \return  - void
******************************************************************************/
void HornScanRecipe::InitiateResetToDefaultRequest()
{
	/* set flag */
	m_InitiateRecipeResetToDefaultRequest = true ;
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_HORN_SCAN_DATA.
* 		     Send save command or request to ASC for saving horn scan recipe related data
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void HornScanRecipe::sendSaveRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(structHornScanRecipe))
    {
        /* Check the save request has came or not */
        if(m_InitiateRecipeSaveRequest == true)
        {
            /* Update the Data to be send to ASC */
            /* clear the save request flag */
            m_InitiateRecipeSaveRequest = false ;
            /* update size in destination */
            destination->size = sizeof(structHornScanRecipe);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* hornScan structure pointer point's to actual memory block Data */
            structHornScanRecipe *hornScanData = reinterpret_cast<structHornScanRecipe *>(destination->data);
            /* lock the resources using mutex */
            pthread_mutex_lock(&m_hornScanDataMutex);
            memcpy(hornScanData,&m_HornScanRecipe,sizeof(m_HornScanRecipe));
            /* Unlock the resources */
            pthread_mutex_unlock(&m_hornScanDataMutex);

        }
        else
        {
            /* reset size */
            destination->size = 0;
            /* clear valid bit */
            destination->config = VALID_BIT;
        }
    }
    else
    {
        /* reset size */
        destination->size = 0;
        /* clear valid bit */
        destination->config = 0;
    }

}



/**************************************************************************//**
*
* \brief   - send reset to default requests to ASC for memory block ID MB_ID_HORN_SCAN_DATA.
*
* 		     Get the default horn scan recipe value from ASC
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void HornScanRecipe::sendHornScanRecipeResetToDefaultRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateRecipeResetToDefaultRequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateRecipeResetToDefaultRequest = false;
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
* \brief   - send the requests to ASC for memory block ID MB_ID_HORN_SCAN_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int HornScanRecipe::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	if((destination != nullptr) && (destination->id == MB_ID_HORN_SCAN_DATA) && (destination->size >=(sizeof(structHornScanRecipe))))
	{
		/* Perform Operation Based on sub ID*/
		switch(destination->sub_id)
		{
			case HORN_SCAN_RECIPE_SAVE:
			{
				sendSaveRequest(destination);
				retVal = 0;
				break;
			}
			case HORN_SCAN_RECIPE_RESET_TO_DEFAULT:
			{
				sendHornScanRecipeResetToDefaultRequest(destination);	
				retVal = 0;
				break;
			}
			case HORN_SCAN_RECIPE_DATA:
			{
				SendRecipeReadRequestToASC(destination);
				retVal = 0;
				break;
			}
			default:
			{
				/* reset size */
				destination->size = 0;
				/* clear valid bit */
				destination->config = 0;
				/* Log the Alarm */
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "hornScan:GetData default");
				break;
			}
		}
	}
	else
	{
		// error! invalid memory block id, default retVal (failure) will be returned
		/* reset size */
		destination->size = 0;

		/* clear valid bit */
		destination->config = 0;

		/* Log the Alarm */
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "hornScanRecipe:GetData invalid req");
	}
	return (retVal);

}
/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_HORN_SCAN_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int HornScanRecipe::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_HORN_SCAN_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for Horn Scan Recipe Data
				case HORN_SCAN_RECIPE_DATA:
				{
					retVal = 0;
					processRecipeReadResponseFromASC(source);
					break;
				}
				case HORN_SCAN_RECIPE_UPDATE_RESULT:
				{
					retVal = 0;
					processRecipeUpdateStatusFromASC(source);
					break;
				}
				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "hornScanRecipe:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "hornScanRecipe:SetData invalid req");
	}

	return (retVal);
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
void HornScanRecipe::processRecipeReadResponseFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	structHornScanRecipe *RecipeData = reinterpret_cast<structHornScanRecipe *>(source->data);
	pthread_mutex_lock(&m_hornScanDataMutex);
    memcpy(&m_HornScanRecipe,RecipeData,sizeof(structHornScanRecipe));
    m_IsHornScanRecipeUpdated = true;
	pthread_mutex_unlock(&m_hornScanDataMutex);
}
/**************************************************************************//**
*
* \brief   - Send a Horn Scan recipe read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void HornScanRecipe::SendRecipeReadRequestToASC(MEMORY_BLOCK * const destination)
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
* \brief   - process the Horn Scan recipe update status coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void HornScanRecipe::processRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source)
{
	HORN_SCAN__RECIPE_UPDATE_RESPONSE RecipeUpdateStatus = static_cast<HORN_SCAN__RECIPE_UPDATE_RESPONSE>(*source->data);
	//Copy horn scan recipe updated status
	m_hornScanRecipeUpdateStatus = RecipeUpdateStatus;
}

/**************************************************************************//**
*
* \brief   - Show Horn Scan Recipe Data
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void HornScanRecipe::ShowHornScanRecipe()
{
    std::cout << "FrequencyStart: " << m_HornScanRecipe.FrequencyStart << std::endl;
    std::cout << "FrequencyStop: " << m_HornScanRecipe.FrequencyStop << std::endl;
    std::cout << "FrequencyStep: " << m_HornScanRecipe.FrequencyStep << std::endl;
    std::cout << "TimeDelay: " << m_HornScanRecipe.TimeDelay << std::endl;
    std::cout << "MaxAmplitude: " << m_HornScanRecipe.MaxAmplitude << std::endl;
    std::cout << "MaxCurrent: " << m_HornScanRecipe.MaxCurrent << std::endl;
    std::cout << "SetDigTuneWithHornScan: " << m_HornScanRecipe.SetDigTuneWithHornScan << std::endl;
}

/**************************************************************************//**
*
* \brief   - This function returns scan recipe data parameters.
*
* \param   - None.
*
* \return  - m_HornScanRecipe : The scan recipe data parameters.
*
******************************************************************************/
structHornScanRecipe HornScanRecipe::GetHornScanRecipeData()
{
    return m_HornScanRecipe;
}

/**************************************************************************//**
*
* \brief   - This function saves scan recipe data parameters.
*
* \param   - m_structHornScanRecipe : The scan recipe data parameters.
*
* \return  - None.
*
******************************************************************************/
void HornScanRecipe::SetHornScanRecipeData(structHornScanRecipe m_structHornScanRecipe)
{
    m_HornScanRecipe = m_structHornScanRecipe;
    InitiateRecipeSaveRequest(m_HornScanRecipe);
}

/**************************************************************************//**
*
* \brief   - Retuns the status the horn scan recipe update.
*
* \param   - None.
*
* \return  - m_IsHornScanRecipeUpdated : The horn scan recipe update status.
*
******************************************************************************/
bool HornScanRecipe::GetIsHornScanRecipeUpdated()
{
    return m_IsHornScanRecipeUpdated;
}

/**************************************************************************//**
*
* \brief   - Sets the status of the horn scan recipe update.
*
* \param   - Value : Status flag value from interface.
*
* \return  - None.
*
******************************************************************************/
void HornScanRecipe::SetIsHornScanRecipeUpdated(bool Value)
{
    m_IsHornScanRecipeUpdated = Value;
}
/**************************************************************************//**
*
* \brief   - Get the minimum value for passed parameter ID
*
* \param   - ParamID - Horn Scan Recipe Parameter Identifier
*
* \return  - Minimum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string HornScanRecipe::GetHornScanRecipeParamMinValue(HORNSCAN_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator =   HornScanRecipeParamMap.find(ParamID);
    if (MapIterator != HornScanRecipeParamMap.end())
    {
        //Get the system frequency and update Min value according to paramID
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetHornScanRecipeParamMinValue failed");
    }
    return Value;
}

/**************************************************************************//**
*
* \brief   - Get the maximum value for passed parameter ID
*
* \param   - ParamID - Horn Scan Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string HornScanRecipe::GetHornScanRecipeParamMaxValue(HORNSCAN_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator = HornScanRecipeParamMap.find(ParamID);
    if (MapIterator != HornScanRecipeParamMap.end())
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetHornScanRecipeParamMaxValue failed");
    }
    return Value;
}

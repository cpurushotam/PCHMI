/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld recipe related implementation

***************************************************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string.h>
#include "WeldRecipeAce.h"
#include "DataLogger.h"
#include "AmplitudeAndPressureStepsSupport.h"
#include "PowerLevelSysFrequencySupport.h"
#include "UnitConversion.h"
#include "CommPeerInfo.h"
#include "MultiwelderInterface.h"
#include "CommPeerWrapper.h"
#include "UnitConversion.h"

size_t WeldRecipeACE::static_log_id=0;


/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
WeldRecipeACEStruct::WeldRecipeACEStruct()
{
    //Kept empty as ASC sends the active weld recipe data to HMI.
    memset(WeldRecipeName, 0, sizeof(WeldRecipeName));
}

/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
StackRecipeACEStruct::StackRecipeACEStruct()
{
    //Kept empty as ASC sends the stack recipe data along with active weld recipe data to HMI.
}

/******************************************************************************
* \brief -WeldRecipeACE()  Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
WeldRecipeACE::WeldRecipeACE()
{
    pthread_mutex_init(&m_ActiveWeldRecipeDataMutex, nullptr);
    pthread_mutex_init(&m_RecipeCardDataMapMutex, nullptr);
    pthread_mutex_init(&m_ChangedWeldRecipeParameterMutex, nullptr);

    m_IsActiveWeldRecipeUpdated = false;
    m_IsMapUpdated = false;
    m_RecipeCardIndexNumber = 0;
    //Send the request to read active weld recipe data to ASC at power up of HMI
    m_SendActiveWeldRecipeReadRequest = true;
    //Send the request to read recipe card data to ASC at power up of HMI
    m_SendRecipeCardReadRequest = true;

    m_InitiateRecipeCreateRequest = false;
    m_InitiateRecipeDeleteRequest = false;
    m_InitiateSetWeldRecipeAsActiveRequest = false;
    m_InitiateCopyWeldRecipeRequest = false;
    m_InitiateRecallWeldRecipeRequest = false;
    m_InitiateAmplitudeStepDataSendRequest = false;
    m_InitiatePressureStepDataSendRequest = false;
    m_InitiateRecipeResetToDefaultRequest = false;

    m_RecipeNumberToBeDeleted = -1;
    m_RecipeNumberToBeSetAsActive = -1;
    m_SourceRecipeNumberForCopyOperation = -1;
    m_DestinationRecipeNumberForCopyOperation = -1;
    m_RecipeNumberFoRecallOperation = -1;
    m_RecipeVersionNumberFoRecallOperation = -1;
    m_RecipeNumberToBeResetToDefault = -1;

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
WeldRecipeACE::~WeldRecipeACE()
{
    pthread_mutex_destroy(&m_ActiveWeldRecipeDataMutex);
    pthread_mutex_destroy(&m_RecipeCardDataMapMutex);
    pthread_mutex_destroy(&m_ChangedWeldRecipeParameterMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_WELD_RECIPE_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldRecipeACE::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

        if( (destination != nullptr) && (destination->id == MB_ID_WELD_RECIPE_DATA) )
        {
            switch(destination->sub_id)
            {
                //Send request to ASC to get the active weld recipe data
                case ACTIVE_WELD_RECIPE_DATA:
                {
                    retVal = 0;
                    sendActiveRecipeReadRequestToASC(destination);
                    break;
                }
                break;

                //Send request to ASC to create a weld recipe
                case WELD_RECIPE_CREATE:
                {
                    retVal = 0;
                    sendRecipeCreateRequestToASC(destination);
                    break;
                }

                //Send request to ASC to delete a weld recipe
                case WELD_RECIPE_DELETE:
                {
                    retVal = 0;
                    sendRecipeDeleteRequestToASC(destination);
                    break;
                }

                //Send request to ASC to read map of recipe card data
                case WELD_RECIPE_CARD_DATA:
                {
                    retVal = 0;
                    sendRecipeCardRequestToASC(destination);
                    break;
                }

                //Send request to ASC to update weld recipe parameter
                case WELD_RECIPE_PARAMETER_UPDATE:
                {
                    retVal = 0;
                    sendRecipeParameterUpdateRequestToASC(destination);
                    break;
                }

                //Send request to ASC to set the passed weld recipe number as active recipe
                case SET_WELD_RECIPE_AS_ACTIVE:
                {
                    retVal = 0;
                    sendRecipeSetAsActiveReuestToASC(destination);
                    break;
                }

                //Send request to ASC to copy the passed source recipe to passed destination recipe
                case WELD_RECIPE_COPY:
                {
                    retVal = 0;
                    sendWeldRecipeCopyReuestToASC(destination);
                    break;
                }

                //Send request to ASC to recall the passed weld recipe number to passed weld recipe version number
                case WELD_RECIPE_RECALL:
                {
                    retVal = 0;
                    sendWeldRecipeRecallReuestToASC(destination);
                    break;
                }

                //Send Amplitude Stepping data to ASC
			   case WELD_RECIPE_AMPLITUDE_STEP_DATA:
			   {
				   retVal = 0;
				   sendAmplitudeStepDataToASC(destination);
				   break;
			   }
			   
			   //Send Pressure Stepping data to ASC
			   case WELD_RECIPE_PRESSURE_STEP_DATA:
			   {
				   retVal = 0;
				   sendPressureStepDataToASC(destination);
				   break;
			   }

			   case WELD_RECIPE_RESET_TO_DEFAULT:
			   {
				   retVal = 0;
				   sendWeldRecipeResetToDefaultRequestToASC(destination);
				   break;
			   }

                default:
                {
                    // Error ! default retVal (failure) will be returned
                    // clear valid bit, reset size
                    destination->size = 0;
                    // clear valid bit
                    destination->config = 0;
                    char  msg[buff_size_config];
                    snprintf(msg,buff_size_config,"GetData-defaultcase\n");
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
            char  msg[buff_size_config];
            snprintf(msg,buff_size_config,"GetData invalid case\n");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_WELD_RECIPE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int WeldRecipeACE::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_WELD_RECIPE_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                //Process response coming from ASC for active weld recipe data
                case ACTIVE_WELD_RECIPE_DATA:
                {
                    retVal = 0;
                    processActiveWeldRecipeDataFromASC(source);
                    break;
                }

                //Process response from ASC for map of recipe card data
                case WELD_RECIPE_CARD_DATA:
                {
                    retVal = 0;
                    processRecipeCardResponseFromASC(source);
                    break;
                }

                //Process recipe changes coming from ASC for changes happening in recipe data
                case WELD_RECIPE_CHANGE_DATA:
                {
                    retVal = 0;
                    processRecipeChangesFromASC(source);
                    break;
                }
                
                //Process response coming from ASC to synch weld recipe data on unit change
                case SYNCH_WELD_RECIPE_DATA:
                {
                	retVal = 0;
                	processSynchWeldRecipeDataFromASC(source);
                	break;
                }

                default:
                {
                    char  msg[buff_size_config];
                    snprintf(msg,buff_size_config,"SetData default case\n");
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
        char  msg[buff_size_config];
        snprintf(msg,buff_size_config,"SetData invalid request\n");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - HMI front end/QML should use this API to set individual active weld
* 			recipe parameter value when user changes the parameter.
*
*
* \param   - WeldRecipeParamID: Weld Recipe Parameter Identifier
* 			 Value: Changed Value for the parameter.
*
* \return  - true on success else false
******************************************************************************/
bool WeldRecipeACE::SetActiveWeldRecipeParameter(int WeldRecipeParamID, void* Value)
{
    bool bResult = false;
    int ActiveWeldRecipeNumber = GetActiveWeldRecipeNumber();
    if(ActiveWeldRecipeNumber > 0)
    {
        bResult = SetWeldRecipeParameter(ActiveWeldRecipeNumber, WeldRecipeParamID, Value);
    }
    else
    {
        char  msg[buff_size_config];
        snprintf(msg,buff_size_config,"SetActiveWeldRecipeParam fail");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }

    return bResult;
}

/**************************************************************************//**
*
* \brief   - HMI front end/QML should use this API to set individual weld recipe parameter
* 			value when user changes the parameter for selected recipe.
*
*
* \param   - RecipeNumber - Weld Recipe Number
* 			WeldRecipeParamID: Weld Recipe Parameter Identifier
* 			Value: Changed Value for the parameter.
*
* \return  - true on success else false
******************************************************************************/
bool WeldRecipeACE::SetWeldRecipeParameter(int RecipeNumber, int WeldRecipeParamID, void* Value)
{
    bool bResult = false;
    bool bErrorOccured = false;

    //Check if passed parameter identifier exists in the map WeldRecipeParamMap.
    auto MapIterator = WeldRecipeParamMap.find(WeldRecipeParamID);

    if (MapIterator != WeldRecipeParamMap.end())
    {
        auto MapTuple = MapIterator->second;
        PARAM_DATA_TYPE ParamDataType = std::get<0>(MapTuple);
        ChangedWeldRecipeParameter ChangedParamData;
        ChangedParamData.RecipeNumber = RecipeNumber;
        ChangedParamData.WeldRecipeParamID = WeldRecipeParamID;
        switch (ParamDataType)
        {
            case INT_PARAM:
            {
                int *Data = reinterpret_cast<int *>(Value);
                memcpy(ChangedParamData.Value, Data, sizeof(int));
            }
            break;

            case UNSIGNED_INT_PARAM:
            {
                unsigned int *Data = reinterpret_cast<unsigned int *>(Value);
                memcpy(ChangedParamData.Value, Data, sizeof(unsigned int));
            }
            break;

            case FLOAT_PARAM:
            {
                float *Data = reinterpret_cast<float *>(Value);
                memcpy(ChangedParamData.Value, Data, sizeof(float));
            }
            break;

            case DOUBLE_PARAM:
            {
                double *Data = reinterpret_cast<double *>(Value);
                memcpy(ChangedParamData.Value, Data, sizeof(double));
            }
            break;

            case BOOL_PARAM:
            {
                bool *Data = reinterpret_cast<bool *>(Value);
                memcpy(ChangedParamData.Value, Data, sizeof(bool));
            }
            break;

            case CHAR_ARRAY_PARAM:
            {
                char *Data = reinterpret_cast<char *>(Value);
                strncpy(ChangedParamData.Value, Data, ( sizeof(ChangedParamData.Value) - 1) );
            }
            break;

            default:
            {
                char  msg[buff_size_config];
                snprintf(msg,buff_size_config,"SetWeldRecipeParamInvalidType");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
                bErrorOccured = true;
            }
            break;
        }

        //push the parameter in queue so that it gets sent to ASC
        if(bErrorOccured == false)
        {
            pthread_mutex_lock(&m_ChangedWeldRecipeParameterMutex);
            m_ChangedWeldRecipeParameter.push(ChangedParamData);
            pthread_mutex_unlock(&m_ChangedWeldRecipeParameterMutex);
            bResult = true;
        }
    }
    else
    {
        char  msg[buff_size_config];
        snprintf(msg,buff_size_config,"SetWeldRecipeParamInvalidID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }

    return bResult;
}

/**************************************************************************//**
*
* \brief   - HMI should call this function when user presses create weld recipe
* 			button.
*
*
* \param   - none
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateRecipeCreateRequest()
{
    m_InitiateRecipeCreateRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI should call this function when user presses delete weld recipe
* 			 button.
*
*
* \param   - RecipeNumber - Recipe Number to be deleted
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateRecipeDeleteRequest(int RecipeNumber)
{
    m_RecipeNumberToBeDeleted = RecipeNumber;
    m_InitiateRecipeDeleteRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to set a particular weld recipe as active weld recipe.
*
*
* \param   - RecipeNumber - Recipe Number to be set as active weld recipe.
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateRecipeSetAsActiveRequest(int RecipeNumber)
{
    m_RecipeNumberToBeSetAsActive = RecipeNumber;
    m_InitiateSetWeldRecipeAsActiveRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate weld recipe copy operation.
*
*
* \param   - SourceRecipeNumber - Source Recipe Number for copy operation.
* 			 DestinationRecipeNumber - Destination Recipe Number for copy operation.
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateWeldRecipeCopyRequest(int SourceRecipeNumber, int DestinationRecipeNumber)
{
    m_SourceRecipeNumberForCopyOperation = SourceRecipeNumber;
    m_DestinationRecipeNumberForCopyOperation = DestinationRecipeNumber;
    m_InitiateCopyWeldRecipeRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate weld recipe recall operation.
*
*
* \param   - RecipeNumber - Recipe Number whose version needs to be recalled.
* 			 RecipeVersionNumber - Recipe Version Number to be recalled.
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateWeldRecipeRecallRequest(int RecipeNumber, int RecipeVersionNumber)
{
    m_RecipeNumberFoRecallOperation = RecipeNumber;
    m_RecipeVersionNumberFoRecallOperation = RecipeVersionNumber;
    m_InitiateRecallWeldRecipeRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate sending amplitude step data to ASC.
*
*
* \param   - AmplitudeStepDataToBeSentToASC - amplitude stepping data
*
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiateAmplitudeStepDataSendRequest(struct  AmplitudeStepDataACE &AmplitudeStepDataToBeSentToASC)
{
	m_AmplitudeStepDataToBeSentToASC = AmplitudeStepDataToBeSentToASC;
	m_InitiateAmplitudeStepDataSendRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate sending pressure step data to ASC.
*
*
* \param   - PressureStepDataToBeSentToASC - pressure stepping data
*
*
* \return  - void
******************************************************************************/
void WeldRecipeACE::InitiatePressureStepDataSendRequest(struct  PressureStepDataACE &PressureStepDataToBeSentToASC)
{
    m_PressureStepDataToBeSentToASC = PressureStepDataToBeSentToASC;
    m_InitiatePressureStepDataSendRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to reset the cycle count to 0 for selected recipe on recipe card screen.
*
*
* \param   - RecipeNumber - Recipe number whose cycle count is to be reset to 0.
*
* \return  - true on success else false
******************************************************************************/
bool WeldRecipeACE::InitiateRecipeCycleCountResetRequest(int RecipeNumber)
{
    int CycleCount = 0;
    return SetWeldRecipeParameter(RecipeNumber, CYCLE_COUNT_PARAM, &CycleCount);
}

/**************************************************************************//**
*
* \brief   - Get Active Weld Recipe Number
*
* \param   - none

* \return  - Active Weld Recipe Number
*
******************************************************************************/
int WeldRecipeACE::GetActiveWeldRecipeNumber()
{
    pthread_mutex_lock(&m_ActiveWeldRecipeDataMutex);
    int ActiveWeldRecipeNumber = m_ActiveWeldRecipeData.WeldRecipeNumber;
    pthread_mutex_unlock(&m_ActiveWeldRecipeDataMutex);

    return ActiveWeldRecipeNumber;
}

/**************************************************************************//**
*
* \brief   - return the copy of active weld recipe data
*
* \param   - none

* \return  - copy of active weld recipe data
*
******************************************************************************/
WeldRecipeACEStruct WeldRecipeACE::GetActiveWeldRecipeData()
{
    pthread_mutex_lock(&m_ActiveWeldRecipeDataMutex);

    WeldRecipeACEStruct ActiveRecipeData = m_ActiveWeldRecipeData;
    //Reset the flag to false once the value is read
    m_IsActiveWeldRecipeUpdated = false;

    pthread_mutex_unlock(&m_ActiveWeldRecipeDataMutex);

    return ActiveRecipeData;

}

/**************************************************************************//**
*
* \brief   - return the save status of active recipe.
*
* \param   - none

* \return  - active recipe save status.
*
******************************************************************************/
bool WeldRecipeACE::IsActiveWeldRecipeSaved()
{
    pthread_mutex_lock(&m_ActiveWeldRecipeDataMutex);

    bool IsSaved = m_ActiveWeldRecipeData.IsSaved;

    pthread_mutex_unlock(&m_ActiveWeldRecipeDataMutex);

    return IsSaved;

}

/**************************************************************************//**
*
* \brief   - return the copy of recipe card data map
*
* \param   - none

* \return  - copy of recipe data card map
*
******************************************************************************/
std::map<int, RecipeCardDataACEStruct> WeldRecipeACE::GetRecipeCardDataMap()
{
    pthread_mutex_lock(&m_RecipeCardDataMapMutex);

    std::map<int, RecipeCardDataACEStruct> RecipeCardDataMap = m_RecipeCardDataMap;
    //Reset the flag to false once the value is read
    m_IsMapUpdated = false;

    pthread_mutex_unlock(&m_RecipeCardDataMapMutex);
    return RecipeCardDataMap;

}

/**************************************************************************//**
*
* \brief   - HMI side code uses this method to decide when it needs to read the
*			 active weld recipe data present in the m_ActiveWeldRecipeData.
*			 When the data in the m_ActiveWeldRecipeData gets updated, then we
*			 set m_IsActiveWeldRecipeUpdated flag to true. HMI then rereads the
*			 m_ActiveWeldRecipeData and shows the updated active weld recipe data.
* \param   - none
*
* \return  - returns true when active weld recipe data is updated else
* 			 returns false
*
******************************************************************************/
bool WeldRecipeACE::IsActiveWeldRecipeUpdated()
{
    return m_IsActiveWeldRecipeUpdated;
}

/**************************************************************************//**
*
* \brief   - HMI side code uses this method to decide when it needs to read the
*			 recipe card data present in the m_RecipeCardDataMap.
*			 When the data in the m_RecipeCardDataMap gets updated, then we
*			 set m_IsMapUpdated flag to true. HMI then rereads the m_RecipeCardDataMap
*			 and shows the updated recipe cards on the recipe card screen.
* \param   - none
*
* \return  - returns true when recipe card map is updated else returns false
*
******************************************************************************/
bool WeldRecipeACE::IsMapUpdated()
{
    return m_IsMapUpdated;
}

/**************************************************************************//**
*
* \brief   - HMI side code uses this method to fetch total available recipes
*            entries into the map.
* \param   - none
*
* \return  - returns total recipe cards map entries count.
*
******************************************************************************/
int WeldRecipeACE::GetTotalRecipesEntries()
{
    pthread_mutex_lock(&m_RecipeCardDataMapMutex);

    /*Fetch total available recipes entries into the recipe cards map*/
    int TotalRecipeEntries = m_RecipeCardDataMap.size();

    pthread_mutex_unlock(&m_RecipeCardDataMapMutex);

    return TotalRecipeEntries;
}

/**************************************************************************//**
*
* \brief   - Get the minimum value for passed parameter ID
*
* \param   - ParamID - Weld Recipe Parameter Identifier
*
* \return  - Minimum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string WeldRecipeACE::GetWeldRecipeParamMinValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType)
{
    std::string Value = "";
        auto MapIterator = WeldRecipeParamMap.find(ParamID);
        if (MapIterator != WeldRecipeParamMap.end())
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
            
    		if(UnitType == SYSTEM_UNIT)
            {
                auto systemConfigPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetSystemConfigObjPtr();
                if(systemConfigPtr != nullptr)
                {
                    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
                    {
                        Value = WeldRecipeMinMaxParametersImperialConversion(ParamID, Value);
                    }
                }
                else
                {
                   Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetSystemConfigObjPtr failed");
                }
    		}
        }
        else
        {
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ParamID2 not found");
        }
        return Value;
}

/**************************************************************************//**
*
* \brief   - Get the maximum value for passed parameter ID
*
* \param   - ParamID - Weld Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string WeldRecipeACE::GetWeldRecipeParamMaxValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType)
{
    std::string Value = "";
        auto MapIterator = WeldRecipeParamMap.find(ParamID);
        if (MapIterator != WeldRecipeParamMap.end())
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

            if(ParamID == NUM_AMPLITUDE_STEPS_PARAM)
            {
                unsigned int MaxStepsSupported = AmplitudeAndPressureStepsSupport::GetSupportedAmplitudeStepsFromJSON();
                Value = std::to_string (MaxStepsSupported);
            }

            if(ParamID == NUM_PRESSURE_STEPS_PARAM)
            {
                unsigned int MaxStepsSupported = AmplitudeAndPressureStepsSupport::GetSupportedPressureStepsFromJSON();
                Value = std::to_string (MaxStepsSupported);
            }
            
    		if(UnitType == SYSTEM_UNIT)
    		{
                auto systemConfigPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetSystemConfigObjPtr();
                if(systemConfigPtr != nullptr)
                {
                   if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
                   {
                        Value = WeldRecipeMinMaxParametersImperialConversion(ParamID, Value);
                   }
                }
                else
                {
                   Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetSystemConfigObjPtr failed");
                }
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
* \brief   - Get the default value for passed parameter ID
*
* \param   - ParamID - Weld Recipe Parameter Identifier
*
* \return  - Default value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string WeldRecipeACE::GetWeldRecipeParamDefaultValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType)
{
    std::string Value = "";
    auto MapIterator = WeldRecipeParamMap.find(ParamID);
    if (MapIterator != WeldRecipeParamMap.end())
    {
        //Get the system frequency and update default value according to paramID
        switch(PowerLevelSysFrequencySupport::GetSystemFrequencyFromJSON())
        {
            case FREQ_20KHZ:
            {
                auto MapTuple = MapIterator->second;
                Value = std::get<DEFAULT_VALUE_20K>(MapTuple);
            }
            break;
            case FREQ_30KHZ:
            {
                auto MapTuple = MapIterator->second;
                Value = std::get<DEFAULT_VALUE_30K>(MapTuple);
            }
            break;
            case FREQ_40KHZ:
            {
                auto MapTuple = MapIterator->second;
                Value = std::get<DEFAULT_VALUE_40K>(MapTuple);
            }
            break;
            default:
            {
                auto MapTuple = MapIterator->second;
                Value = std::get<DEFAULT_VALUE_20K>(MapTuple);
            }
            break;
        }
        
		if(UnitType == SYSTEM_UNIT)
		{
            auto systemConfigPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetSystemConfigObjPtr();
            if(systemConfigPtr != nullptr)
            {
               if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
               {
                    Value = WeldRecipeMinMaxParametersImperialConversion(ParamID, Value);
               }
            }
            else
            {
               Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "GetSystemConfigObjPtr failed");
            }
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ParamID4 not found");
    }
    return Value;
}

/**************************************************************************//**
*
* \brief   - Send a recipe create request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendRecipeCreateRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateRecipeCreateRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateRecipeCreateRequest = false;
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
* \brief   - Send a recipe delete request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendRecipeDeleteRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateRecipeDeleteRequest == true)
        {
            int *RecipeNumberToBeDeleted = reinterpret_cast<int *>(destination->data);
            *RecipeNumberToBeDeleted = m_RecipeNumberToBeDeleted;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateRecipeDeleteRequest = false;
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
* \brief   - Send weld recipe parameter update request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendRecipeParameterUpdateRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(ChangedWeldRecipeParameter))
    {
        ChangedWeldRecipeParameter WeldRecipeDataFromQueue;
        bool bSendData = false;

        //Check if data exists in the queue, if exists send it to ASC, else do not send.
        pthread_mutex_lock(&m_ChangedWeldRecipeParameterMutex);
        if (!m_ChangedWeldRecipeParameter.empty())
        {
            WeldRecipeDataFromQueue = m_ChangedWeldRecipeParameter.front();
            m_ChangedWeldRecipeParameter.pop();
            bSendData = true;
        }
        pthread_mutex_unlock(&m_ChangedWeldRecipeParameterMutex);

        if(bSendData == true)
        {
            ChangedWeldRecipeParameter *ChangedWeldRecipeData = reinterpret_cast<ChangedWeldRecipeParameter *>(destination->data);
            memcpy(ChangedWeldRecipeData, &WeldRecipeDataFromQueue, sizeof(ChangedWeldRecipeParameter));
            destination->size = sizeof(ChangedWeldRecipeParameter);
            destination->config = VALID_BIT;
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
* \brief   - Send set weld recipe as active weld recipe request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendRecipeSetAsActiveReuestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateSetWeldRecipeAsActiveRequest == true)
        {
            //Store the recipe number in memory block at offset 0.
            int *RecipeNumber = reinterpret_cast<int *>(destination->data);
            *RecipeNumber = m_RecipeNumberToBeSetAsActive;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateSetWeldRecipeAsActiveRequest = false;
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
* \brief   - Send request to ASC to copy the passed source recipe to passed
* 			 destination recipe
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendWeldRecipeCopyReuestToASC(MEMORY_BLOCK * const destination)
{
    //Make sure sufficient buffer space is available to hold source recipe number and destination recipe number
    if(destination->size >= 2 * sizeof(int))
    {
        if(m_InitiateCopyWeldRecipeRequest == true)
        {
            //Store the source recipe number in memory block at offset 0.
            int *SourceRecipeNumber = reinterpret_cast<int *>(destination->data);
            *SourceRecipeNumber = m_SourceRecipeNumberForCopyOperation;
            //Store the destination recipe number in memory block at offset sizeof(int).
            int *DestinationRecipeNumber = reinterpret_cast<int *>(destination->data + sizeof(int));
            *DestinationRecipeNumber = m_DestinationRecipeNumberForCopyOperation;
            //set the size of memory block as 2 * sizeof(int) as we are sending source recipe number and destination recipe number both.
            destination->size = (2 * sizeof(int));
            destination->config = VALID_BIT;
            m_InitiateCopyWeldRecipeRequest = false;
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
* \brief   - Send request to ASC to recall the passed weld recipe number to passed
* 			 weld recipe version number
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendWeldRecipeRecallReuestToASC(MEMORY_BLOCK * const destination)
{
    //Make sure sufficient buffer space is available to hold the weld recipe number and weld recipe version number
    if(destination->size >= 2 * sizeof(int))
    {
        if(m_InitiateRecallWeldRecipeRequest == true)
        {
            //Store the weld recipe number in memory block at offset 0.
            int *RecipeNumber = reinterpret_cast<int *>(destination->data);
            *RecipeNumber = m_RecipeNumberFoRecallOperation;
            //Store the weld recipe version number in memory block at offset sizeof(int).
            int *RecipeVersionNumber = reinterpret_cast<int *>(destination->data + sizeof(int));
            *RecipeVersionNumber = m_RecipeVersionNumberFoRecallOperation;
            //set the size of memory block as 2 * sizeof(int) as we are sending weld recipe number and weld recipe version number both.
            destination->size = (2 * sizeof(int));
            destination->config = VALID_BIT;
            m_InitiateRecallWeldRecipeRequest = false;
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
* \brief   - Send Amplitude Stepping Data to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendAmplitudeStepDataToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=  ( sizeof(AmplitudeStepDataACE) + sizeof(int)) )
	{
		if(m_InitiateAmplitudeStepDataSendRequest == true)
		{
			int RecipeNumber = GetActiveWeldRecipeNumber();
			*destination->data = RecipeNumber;
			AmplitudeStepDataACE *AmplitudeStepData = reinterpret_cast<AmplitudeStepDataACE *>(destination->data + sizeof(int));
			memcpy(AmplitudeStepData, &m_AmplitudeStepDataToBeSentToASC, sizeof(AmplitudeStepDataACE));
			destination->size =  ( sizeof(AmplitudeStepDataACE) + sizeof(int) );
			destination->config = VALID_BIT;
			m_InitiateAmplitudeStepDataSendRequest = false;
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
* \brief   - Send Pressure Stepping Data to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendPressureStepDataToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=  ( sizeof(PressureStepDataACE) + sizeof(int)) )
	{
		if(m_InitiatePressureStepDataSendRequest == true)
		{
			int RecipeNumber = GetActiveWeldRecipeNumber();
			*destination->data = RecipeNumber;
			PressureStepDataACE *PressureStepData = reinterpret_cast<PressureStepDataACE *>(destination->data + sizeof(int));
			memcpy(PressureStepData, &m_PressureStepDataToBeSentToASC, sizeof(PressureStepDataACE));
			destination->size =  ( sizeof(PressureStepDataACE) + sizeof(int) );
			destination->config = VALID_BIT;
			m_InitiatePressureStepDataSendRequest = false;
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
* \brief   - Send active recipe read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendActiveRecipeReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_SendActiveWeldRecipeReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_SendActiveWeldRecipeReadRequest = false;
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
* \brief   - Send a read request to ASC to read recipe card data in chunks
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendRecipeCardRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_SendRecipeCardReadRequest == true )
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;


            int *RecipeCardIndexNumber = reinterpret_cast<int *>(destination->data);
            //Set the index number of recipe card map to be read.
            *RecipeCardIndexNumber = m_RecipeCardIndexNumber;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRecipeCardReadRequest = false;
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
* \brief   - Send a recipe reset to default request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void WeldRecipeACE::sendWeldRecipeResetToDefaultRequestToASC(MEMORY_BLOCK * const destination)
{
   if(destination->size >= sizeof(int))
   {
	   if(m_InitiateRecipeResetToDefaultRequest == true)
	   {
		   int *RecipeNumberToBeResetToDefault = reinterpret_cast<int *>(destination->data);
		   *RecipeNumberToBeResetToDefault = m_RecipeNumberToBeResetToDefault;
		   destination->size = sizeof(int);
		   destination->config = VALID_BIT;
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
* \brief   - process the active weld recipe data coming from ASC
*
* \param   - source - memory block holding the active weld recipe data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::processActiveWeldRecipeDataFromASC(const MEMORY_BLOCK *const source)
{
    //first 1 byte (sizeof (bool)), hold the status whether the active weld recipe is updated or not.
    bool IsActiveRecipeUpdated = static_cast<bool>(*source->data);
    if(IsActiveRecipeUpdated == true)
    {
        //Actual active weld recipe data starts at offset sizeof(bool)
        const WeldRecipeACEStruct* ActiveWeldRecipeData = reinterpret_cast<const WeldRecipeACEStruct*>(source->data + sizeof(bool));

        pthread_mutex_lock(&m_ActiveWeldRecipeDataMutex);
        memcpy(&m_ActiveWeldRecipeData, ActiveWeldRecipeData, sizeof(WeldRecipeACEStruct));
        m_IsActiveWeldRecipeUpdated = true;
        pthread_mutex_unlock(&m_ActiveWeldRecipeDataMutex);
    }
}

/**************************************************************************//**
*
* \brief   - process the recipe card response coming from ASC
*
* \param   - source - memory block holding the recipe card data received from ASC
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::processRecipeCardResponseFromASC(const MEMORY_BLOCK *const source)
{
    //first four bytes (sizeof (int)), hold the actual number of recipe cards sent by ASC
    int ReceivedRecipeCardsCount = static_cast<int>(*source->data);
    //Actual recipe card data starts at offset sizeof(int)
    const RecipeCardDataACEStruct* data = reinterpret_cast<const RecipeCardDataACEStruct*>(source->data + sizeof(int));

    pthread_mutex_lock(&m_RecipeCardDataMapMutex);
    for (int RecipeCardNumber = 0; RecipeCardNumber < ReceivedRecipeCardsCount; ++RecipeCardNumber)
    {
        //fill the map with recipe card data coming from ASC
        m_RecipeCardDataMap[data[RecipeCardNumber].WeldRecipeNumber] = data[RecipeCardNumber];
    }
    pthread_mutex_unlock(&m_RecipeCardDataMapMutex);

    //Increment next request for recipe card index based on the number of recipe cards received.
    m_RecipeCardIndexNumber = m_RecipeCardIndexNumber + ReceivedRecipeCardsCount;

    //ASC will send the number 0 if no further recipe cards available.
    //Stop sending further requests to ASC in such case.
    //Else continue sending the request for further chunks.
    if(ReceivedRecipeCardsCount == 0)
    {
        m_RecipeCardIndexNumber = 0;
        m_SendRecipeCardReadRequest = false;

        //Set the flag true when we have received the complete recipe card map data
        m_IsMapUpdated = true;
    }
    else
    {
        m_SendRecipeCardReadRequest = true;
    }
}

/**************************************************************************//**
*
* \brief   - process the recipe data changes coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::processRecipeChangesFromASC(const MEMORY_BLOCK *const source)
{
    RecipeChange *RecipeChangeDataValue = reinterpret_cast<RecipeChange *>(source->data);
    RecipeCardDataACEStruct *RecipeCardDataValue = reinterpret_cast<RecipeCardDataACEStruct *>(source->data + sizeof(RecipeChange));

    switch(RecipeChangeDataValue->Action)
    {
        case RECIPE_CREATE:
        {
            if( RecipeChangeDataValue->Result == WELD_RECIPE_CREATE_SUCCESS )
            {
                    //Make sure the notification holds valid recipe number containing valid recipe card data.
                    if(RecipeCardDataValue->WeldRecipeNumber > -1)
                    {
                        pthread_mutex_lock(&m_RecipeCardDataMapMutex);
                        //fill the map with recipe card data coming from ASC
                        m_RecipeCardDataMap[RecipeCardDataValue->WeldRecipeNumber] = *RecipeCardDataValue;
                        m_IsMapUpdated = true;
                        pthread_mutex_unlock(&m_RecipeCardDataMapMutex);
                    }
            }
            else
            {
                //No need to copy recipe card map data as this is the case of recipe creation failure notification. So map data does not exist in such case.
            }
        }
        break;

        case RECIPE_DELETE:
        {
            if( RecipeChangeDataValue->Result == WELD_RECIPE_DELETE_SUCCESS )
            {
                    pthread_mutex_lock(&m_RecipeCardDataMapMutex);
                    //remove the map entry because the recipe is deleted and no longer available
                    m_RecipeCardDataMap.erase(RecipeChangeDataValue->WeldRecipeNumber);
                    m_IsMapUpdated = true;
                    pthread_mutex_unlock(&m_RecipeCardDataMapMutex);
            }
            else
            {
                //No need to delete recipe card map data as this is the case of recipe deletion failure notification.
            }
        }
        break;

        case RECIPE_UPDATE:
        {
            if( RecipeChangeDataValue->Result == WELD_RECIPE_UPDATE_SUCCESS )
            {
                    //Make sure the notification holds valid recipe number containing valid recipe card data.
                    if(RecipeCardDataValue->WeldRecipeNumber > -1)
                    {
                        pthread_mutex_lock(&m_RecipeCardDataMapMutex);
                        //fill the map with recipe card data coming from ASC
                        m_RecipeCardDataMap[RecipeCardDataValue->WeldRecipeNumber] = *RecipeCardDataValue;
                        m_IsMapUpdated = true;
                        pthread_mutex_unlock(&m_RecipeCardDataMapMutex);
                    }
            }
            else
            {
                //No need to copy recipe card map data as this is the case of recipe update failure notification. So map data does not exist in such case.
            }
        }
        break;

        default:
        {
            char  msg[buff_size_config];
            snprintf(msg,buff_size_config,"RecipeChangesFromASC-fail");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
        }
        break;
    }
}

/**************************************************************************//**
*
* \brief   - process synch the weld recipe data changes coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::processSynchWeldRecipeDataFromASC(const MEMORY_BLOCK *const source)
{
	//Clear previous active weld recipe and recipe card data
    memset(&m_ActiveWeldRecipeData, 0, sizeof(WeldRecipeACEStruct));
	m_RecipeCardDataMap.clear();
	m_RecipeCardIndexNumber = 0;
	
	m_SendActiveWeldRecipeReadRequest = true;
	m_SendRecipeCardReadRequest = true;
}

/**************************************************************************//**
* 
* \brief  - Unit conversion from metric to imperial for weld recipe min-max parameters.
*
* \param  - ParamID  - Weld Recipe Parameter Identifier
*           Value    - Weld Recipe Min-Max values for passed ParamID.
*
* \return -  maximum/minimum possible value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string WeldRecipeACE::WeldRecipeMinMaxParametersImperialConversion(WELD_RECIPE_ACE_PARAM_ID ParamID, std::string Value)
{
	switch(ParamID)
	{
		case MODE_VALUE_ABSOLUTE_DISTANCE_PARAM:
		case MODE_VALUE_COLLAPSE_DISTANCE_PARAM:
		case TRIGGER_DISTANCE_PARAM:
		case PRE_TRIGGER_DISTANCE_PARAM:
		case RAPID_TRAVERSE_DISTANCE_PARAM:
		case ACTUATOR_CLEAR_DISTANCE_PARAM:
		case ABS_DISTANCE_CUTOFF_VALUE_PARAM:
		case COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM:
		case REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM:
		case REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM:
		case REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM:
		case REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM:
		case REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM:
		case REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM:
		case SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM:
		case SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM:
		case SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM:
		case SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM:
		case SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM:
		case SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM:
		{
			float distanceMetricValue = std::stof(Value);
			distanceMetricValue = UnitConversion::ConvertMilliMeterToInches(distanceMetricValue);
			Value = std::to_string(distanceMetricValue);
			break;
		}
			
		case WELD_PRESSURE_PARAM:
		case HOLD_PRESSURE_PARAM:
		{
			float pressureMetricValue = std::stof(Value);
			pressureMetricValue = UnitConversion::ConvertKPascalToPsi(pressureMetricValue);
			Value = std::to_string(pressureMetricValue);
			break;
		}
		
		case TRIGGER_FORCE_PARAM:
		case REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM:
		case REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM:
		case SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM:
		case SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM:
		{
			float forceMetricValue = std::stof(Value);
			forceMetricValue = UnitConversion::ConvertNewtonToLbs(forceMetricValue);
			Value = std::to_string(forceMetricValue);
            break;
		}
		
		case REJECT_VELOCITY_LOW_LIMIT_PARAM:
		case REJECT_VELOCITY_HIGH_LIMIT_PARAM:
		case SUSPECT_VELOCITY_LOW_LIMIT_PARAM:
		case SUSPECT_VELOCITY_HIGH_LIMIT_PARAM:
		{
			float velocityMetricValue = std::stof(Value);
			velocityMetricValue = UnitConversion::ConvertMilliMeterPerSecToInchPerSec(velocityMetricValue);
			Value = std::to_string(velocityMetricValue);
			break;
		}
			
		default:
		{
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Imperial Conversion ParamID not found");
			break;
		}
	}
	
	return Value;
}

/**************************************************************************//**
*
* \brief   - print active weld recipe data from cache
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::printActiveWeldRecipe()
{
    std::cout << "ActiveWeldRecipeData.WeldRecipeNumber:" << m_ActiveWeldRecipeData.WeldRecipeNumber << std::endl;
    std::cout << "ActiveWeldRecipeData.WeldRecipeVersionNumber:" << m_ActiveWeldRecipeData.WeldRecipeVersionNumber << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.StackRecipeNumber:" << m_ActiveWeldRecipeData.StackRecipe.StackRecipeNumber << std::endl;
    std::cout << "ActiveWeldRecipeData.WeldRecipeName:" << m_ActiveWeldRecipeData.WeldRecipeName << std::endl;
    std::cout << "ActiveWeldRecipeData.WeldMode:" << m_ActiveWeldRecipeData.WeldMode << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValueTime:" << m_ActiveWeldRecipeData.ModeValueTime << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValueEnergy:" << m_ActiveWeldRecipeData.ModeValueEnergy << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValuePeakPower:" << m_ActiveWeldRecipeData.ModeValuePeakPower << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValueGroundDetect:" << m_ActiveWeldRecipeData.ModeValueGroundDetect << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValueAbsoluteDistance:" << m_ActiveWeldRecipeData.ModeValueAbsoluteDistance << std::endl;
    std::cout << "ActiveWeldRecipeData.ModeValueCollapseDistance:" << m_ActiveWeldRecipeData.ModeValueCollapseDistance << std::endl;
    std::cout << "ActiveWeldRecipeData.IsSaved:" << m_ActiveWeldRecipeData.IsSaved << std::endl;
    std::cout << "ActiveWeldRecipeData.CycleCounterData.CycleCount:" << m_ActiveWeldRecipeData.CycleCounterData.CycleCount << std::endl;
    std::cout << "ActiveWeldRecipeData.CycleCounterData.CyclesOKCount:" << m_ActiveWeldRecipeData.CycleCounterData.CyclesOKCount << std::endl;
    std::cout << "ActiveWeldRecipeData.CycleCounterData.RejectCount:" << m_ActiveWeldRecipeData.CycleCounterData.RejectCount << std::endl;
    std::cout << "ActiveWeldRecipeData.CycleCounterData.SuspectCount:" << m_ActiveWeldRecipeData.CycleCounterData.SuspectCount << std::endl;
    std::cout << "ActiveWeldRecipeData.BatchSetupEnable:" << m_ActiveWeldRecipeData.BatchSetupEnable << std::endl;
    std::cout << "ActiveWeldRecipeData.BatchAlarmEnable:" << m_ActiveWeldRecipeData.BatchAlarmEnable << std::endl;
    std::cout << "ActiveWeldRecipeData.BatchCounter:" << m_ActiveWeldRecipeData.BatchCounter << std::endl;
    std::cout << "ActiveWeldRecipeData.BatchID:" << m_ActiveWeldRecipeData.BatchID << std::endl;

    
    std::cout << "ActiveWeldRecipeData.WeldPressure:" << m_ActiveWeldRecipeData.WeldPressure << std::endl;
    std::cout << "ActiveWeldRecipeData.HoldPressure:" << m_ActiveWeldRecipeData.HoldPressure << std::endl;
    std::cout << "ActiveWeldRecipeData.FlowRate:" << m_ActiveWeldRecipeData.FlowRate << std::endl;
    std::cout << "ActiveWeldRecipeData.HoldTime:" << m_ActiveWeldRecipeData.HoldTime << std::endl;
    std::cout << "ActiveWeldRecipeData.MaxWeldTimeout:" << m_ActiveWeldRecipeData.MaxWeldTimeout << std::endl;
    std::cout << "ActiveWeldRecipeData.WeldAmplitude:" << m_ActiveWeldRecipeData.WeldAmplitude << std::endl;
    std::cout << "ActiveWeldRecipeData.NumAmplitudeSteps:" << m_ActiveWeldRecipeData.NumAmplitudeSteps << std::endl;
    std::cout << "ActiveWeldRecipeData.AmplitudeStepAt:" << m_ActiveWeldRecipeData.AmplitudeStepAt << std::endl;
    for(int Index = 0; Index < MAX_NUMBER_OF_AMPLITUDE_STEPS_SUPPORTED; Index++)
    {
		std::cout << "ActiveWeldRecipeData.AmplitudeStepParameters.AmplitudeStepAtValue " << Index << ": " << m_ActiveWeldRecipeData.AmplitudeStepParameters[Index].AmplitudeStepAtValue << std::endl;
		std::cout << "ActiveWeldRecipeData.AmplitudeStepParameters.AmplitudeStepTarget " << Index << ": " << m_ActiveWeldRecipeData.AmplitudeStepParameters[Index].AmplitudeStepTarget << std::endl;
		std::cout << "ActiveWeldRecipeData.AmplitudeStepParameters.AmplitudeStepRamp " << Index << ": " << m_ActiveWeldRecipeData.AmplitudeStepParameters[Index].AmplitudeStepRamp << std::endl;
    }
    std::cout << "ActiveWeldRecipeData.NumPressureSteps:" << m_ActiveWeldRecipeData.NumPressureSteps << std::endl;
    std::cout << "ActiveWeldRecipeData.PressureStepAt:" << m_ActiveWeldRecipeData.PressureStepAt << std::endl;
    for(int Index = 0; Index < MAX_NUMBER_OF_PRESSURE_STEPS_SUPPORTED; Index++)
    {
		std::cout << "ActiveWeldRecipeData.PressureStepParameters.PressureStepAtValue " << Index << ": " << m_ActiveWeldRecipeData.PressureStepParameters[Index].PressureStepAtValue << std::endl;
		std::cout << "ActiveWeldRecipeData.PressureStepParameters.PressureStepTarget " << Index << ": " << m_ActiveWeldRecipeData.PressureStepParameters[Index].PressureStepTarget << std::endl;
		std::cout << "ActiveWeldRecipeData.PressureStepParameters.PressureStepRamp " << Index << ": " << m_ActiveWeldRecipeData.PressureStepParameters[Index].PressureStepRamp << std::endl;
	}
    std::cout << "ActiveWeldRecipeData.IsCoolingValveEnabled:" << m_ActiveWeldRecipeData.IsCoolingValveEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.TriggerData.TriggerType:" << m_ActiveWeldRecipeData.TriggerData.TriggerType << std::endl;
    std::cout << "ActiveWeldRecipeData.TriggerData.TriggerForce:" << m_ActiveWeldRecipeData.TriggerData.TriggerForce << std::endl;
    std::cout << "ActiveWeldRecipeData.TriggerData.TriggerDistance:" << m_ActiveWeldRecipeData.TriggerData.TriggerDistance << std::endl;
    std::cout << "ActiveWeldRecipeData.PreTrigger.bEnabled:" << m_ActiveWeldRecipeData.PreTrigger.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.PreTrigger.PreTriggerType:" << m_ActiveWeldRecipeData.PreTrigger.PreTriggerType << std::endl;
    std::cout << "ActiveWeldRecipeData.PreTrigger.Amplitude:" << m_ActiveWeldRecipeData.PreTrigger.Amplitude << std::endl;
    std::cout << "ActiveWeldRecipeData.PreTrigger.PreTriggerTime:" << m_ActiveWeldRecipeData.PreTrigger.PreTriggerTime << std::endl;
    std::cout << "ActiveWeldRecipeData.PreTrigger.PreTriggerDistance:" << m_ActiveWeldRecipeData.PreTrigger.PreTriggerDistance << std::endl;
    std::cout << "ActiveWeldRecipeData.AfterBurst.bEnabled :" << m_ActiveWeldRecipeData.AfterBurst.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.AfterBurst.BurstAmplitude:" << m_ActiveWeldRecipeData.AfterBurst.BurstAmplitude << std::endl;
    std::cout << "ActiveWeldRecipeData.AfterBurst.BurstDelay" << m_ActiveWeldRecipeData.AfterBurst.BurstDelay<< std::endl;
    std::cout << "ActiveWeldRecipeData.AfterBurst.BurstTime:" << m_ActiveWeldRecipeData.AfterBurst.BurstTime << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyBrake.bEnabled:" << m_ActiveWeldRecipeData.EnergyBrake.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyBrake.EnergyBrakeAmplitude:" << m_ActiveWeldRecipeData.EnergyBrake.EnergyBrakeAmplitude << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyBrake.EnergyBrakeTime:" << m_ActiveWeldRecipeData.EnergyBrake.EnergyBrakeTime << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationEnabled:" << m_ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationMinValue:" << m_ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationMinValue << std::endl;
    std::cout << "ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationMaxValue:" << m_ActiveWeldRecipeData.EnergyCompensation.EnergyCompensationMaxValue << std::endl;
    std::cout << "ActiveWeldRecipeData.TimedSeekPeriod:" << m_ActiveWeldRecipeData.TimedSeekPeriod << std::endl;
    std::cout << "ActiveWeldRecipeData.IsTimedSeekEnabled:" << m_ActiveWeldRecipeData.IsTimedSeekEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.IsPreWeldSeekEnabled:" << m_ActiveWeldRecipeData.IsPreWeldSeekEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.IsPostWeldSeekEnabled:" << m_ActiveWeldRecipeData.IsPostWeldSeekEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.ScrubAmplitude:" << m_ActiveWeldRecipeData.ScrubAmplitude << std::endl;
    std::cout << "ActiveWeldRecipeData.RapidTraverse:" << m_ActiveWeldRecipeData.RapidTraverse << std::endl;
    std::cout << "ActiveWeldRecipeData.TriggerLost:" << m_ActiveWeldRecipeData.TriggerLost << std::endl;
    std::cout << "ActiveWeldRecipeData.ActuatorClearData.EnableActuatorClear:" << m_ActiveWeldRecipeData.ActuatorClearData.EnableActuatorClear << std::endl;
    std::cout << "ActiveWeldRecipeData.ActuatorClearData.ActuatorClearType:" << m_ActiveWeldRecipeData.ActuatorClearData.ActuatorClearType << std::endl;
    std::cout << "ActiveWeldRecipeData.ActuatorClearData.ActuatorClearTime:" << m_ActiveWeldRecipeData.ActuatorClearData.ActuatorClearTime << std::endl;
    std::cout << "ActiveWeldRecipeData.ActuatorClearData.ActuatorClearDistance:" << m_ActiveWeldRecipeData.ActuatorClearData.ActuatorClearDistance << std::endl;


    std::cout << "ActiveWeldRecipeData.CutoffLimit.CutOffLimitsEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.CutOffLimitsEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.PeakPowerCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.PeakPowerCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.PeakPowerCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.PeakPowerCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.TimeCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.TimeCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.TimeCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.TimeCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.FrequencyLowCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.FrequencyLowCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.FrequencyLowCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.FrequencyLowCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.FrequencyHighCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.FrequencyHighCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.FrequencyHighCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.FrequencyHighCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.EnergyCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.EnergyCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.EnergyCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.EnergyCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.GroundDetectCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.GroundDetectCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.GroundDetectCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.GroundDetectCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.AbsoluteDistanceCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.AbsoluteDistanceCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.AbsoluteDistanceCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.AbsoluteDistanceCutoff.Value  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.CollapseDistanceCutoff.bEnabled :" << m_ActiveWeldRecipeData.CutoffLimit.CollapseDistanceCutoff.bEnabled  << std::endl;
    std::cout << "ActiveWeldRecipeData.CutoffLimit.CollapseDistanceCutoff.Value :" << m_ActiveWeldRecipeData.CutoffLimit.CollapseDistanceCutoff.Value  << std::endl;

    std::cout << "ActiveWeldRecipeData.RejectLimit.RejectLimitsEnabled :" << m_ActiveWeldRecipeData.RejectLimit.RejectLimitsEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Time.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Time.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Time.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Time.bLowEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Time.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Time.bHighEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Time.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.Time.LowLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Time.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.Time.HighLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Energy.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Energy.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Energy.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Energy.bLowEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Energy.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Energy.bHighEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Energy.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.Energy.LowLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Energy.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.Energy.HighLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.PeakPower.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.PeakPower.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.PeakPower.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.PeakPower.bLowEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.PeakPower.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.PeakPower.bHighEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.PeakPower.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.PeakPower.LowLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.PeakPower.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.PeakPower.HighLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Frequency.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Frequency.bEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Frequency.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Frequency.bLowEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Frequency.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Frequency.bHighEnabled << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Frequency.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.Frequency.LowLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.Frequency.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.Frequency.HighLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.AbsoluteDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.CollapseDistance.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.CollapseDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.CollapseDistance.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.CollapseDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.CollapseDistance.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.CollapseDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.CollapseDistance.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.CollapseDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.CollapseDistance.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.CollapseDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.TriggerDistance.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.TriggerDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.TriggerDistance.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.TriggerDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.TriggerDistance.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.TriggerDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.TriggerDistance.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.TriggerDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.TriggerDistance.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.TriggerDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.EndWeldForce.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.EndWeldForce.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.EndWeldForce.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.EndWeldForce.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.EndWeldForce.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.EndWeldForce.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.EndWeldForce.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.EndWeldForce.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.EndWeldForce.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.EndWeldForce.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.Velocity.bEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Velocity.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.Velocity.bLowEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Velocity.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.Velocity.bHighEnabled :" << m_ActiveWeldRecipeData.RejectLimit.Velocity.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.Velocity.LowLimit :" << m_ActiveWeldRecipeData.RejectLimit.Velocity.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.RejectLimit.Velocity.HighLimit :" << m_ActiveWeldRecipeData.RejectLimit.Velocity.HighLimit << std::endl;
	
	std::cout << "ActiveWeldRecipeData.SuspectLimit.SuspectLimitsEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.SuspectLimitsEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Time.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Time.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Time.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Time.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Time.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Time.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Time.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Time.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Time.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Time.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Energy.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Energy.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Energy.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Energy.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Energy.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Energy.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Energy.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Energy.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Energy.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Energy.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.PeakPower.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.PeakPower.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.PeakPower.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.PeakPower.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.PeakPower.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.PeakPower.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.PeakPower.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.PeakPower.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.PeakPower.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.PeakPower.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Frequency.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Frequency.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Frequency.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Frequency.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Frequency.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Frequency.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Frequency.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Frequency.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Frequency.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Frequency.HighLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.AbsoluteDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.CollapseDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.CollapseDistance.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.CollapseDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.CollapseDistance.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.CollapseDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.TriggerDistance.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.TriggerDistance.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.TriggerDistance.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.TriggerDistance.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.TriggerDistance.HighLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.EndWeldForce.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.EndWeldForce.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.EndWeldForce.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.EndWeldForce.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.EndWeldForce.HighLimit << std::endl;   
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Velocity.bEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Velocity.bEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Velocity.bLowEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Velocity.bLowEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Velocity.bHighEnabled :" << m_ActiveWeldRecipeData.SuspectLimit.Velocity.bHighEnabled << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Velocity.LowLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Velocity.LowLimit << std::endl;
	std::cout << "ActiveWeldRecipeData.SuspectLimit.Velocity.HighLimit :" << m_ActiveWeldRecipeData.SuspectLimit.Velocity.HighLimit << std::endl;   
	
	
    std::cout << "ActiveWeldRecipeData.StackRecipe.FrequencyLow :" << m_ActiveWeldRecipeData.StackRecipe.FrequencyLow << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.FrequencyHigh :" << m_ActiveWeldRecipeData.StackRecipe.FrequencyHigh << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.PhaseLimitTime :" << m_ActiveWeldRecipeData.StackRecipe.PhaseLimitTime << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.PhaseLimit :" << m_ActiveWeldRecipeData.StackRecipe.PhaseLimit << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.ControlMode :" << m_ActiveWeldRecipeData.StackRecipe.ControlMode << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.BlindTimeWeld :" << m_ActiveWeldRecipeData.StackRecipe.BlindTimeWeld << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.AmpProportionalGain :" << m_ActiveWeldRecipeData.StackRecipe.AmpProportionalGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.AmpIntegralGain :" << m_ActiveWeldRecipeData.StackRecipe.AmpIntegralGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.AmpDerivativeGain :" << m_ActiveWeldRecipeData.StackRecipe.AmpDerivativeGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.PhaseProportionalGain :" << m_ActiveWeldRecipeData.StackRecipe.PhaseProportionalGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.PhaseIntegralGain :" << m_ActiveWeldRecipeData.StackRecipe.PhaseIntegralGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.PhaseDerivativeGain :" << m_ActiveWeldRecipeData.StackRecipe.PhaseDerivativeGain << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.WeldRampTime :" << m_ActiveWeldRecipeData.StackRecipe.WeldRampTime << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.StartFrequency :" << m_ActiveWeldRecipeData.StackRecipe.StartFrequency << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.MemoryOffset :" << m_ActiveWeldRecipeData.StackRecipe.MemoryOffset << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.DigitalTune :" << m_ActiveWeldRecipeData.StackRecipe.DigitalTune << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.FrequencyOffset :" << m_ActiveWeldRecipeData.StackRecipe.FrequencyOffset << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.EndOfWeldStore :" << m_ActiveWeldRecipeData.StackRecipe.EndOfWeldStore << std::endl;
    std::cout << "ActiveWeldRecipeData.StackRecipe.InternalOffsetFlag :" << m_ActiveWeldRecipeData.StackRecipe.InternalOffsetFlag << std::endl;
}
/**************************************************************************//**
*
* \brief   - print Recipe Card Map m_RecipeCardDataMap
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void WeldRecipeACE::printRecipeCardMap()
{
    pthread_mutex_lock(&m_RecipeCardDataMapMutex);
    if(m_RecipeCardDataMap.size() == 0)
    {
        std::cout << "**********HMI side Recipe MAP Empty " << std::endl;
    }
    else
    {
        for (auto it=m_RecipeCardDataMap.begin(); it!=m_RecipeCardDataMap.end(); ++it)
        {
            std::cout << "HMI side Recipe Card Data: " << std::endl;
            std::cout << "**********Recipe Number in map key:" << it->first << std::endl;
            std::cout << "**********Recipe Number:" << it->second.WeldRecipeNumber << std::endl;
            std::cout << "**********Recipe Version Number:" << it->second.WeldRecipeVersionNumber << std::endl;
            std::cout << "**********Recipe Name:" << it->second.WeldRecipeName << std::endl;
            std::cout << "**********Recipe WeldMode:" << it->second.WeldMode << std::endl;
            std::cout << "**********Recipe ModeValue:" << it->second.ModeValue << std::endl;
            std::cout << "**********Recipe CycleCount:" << it->second.CycleCount << std::endl;
        }
    }
    pthread_mutex_unlock(&m_RecipeCardDataMapMutex);
}


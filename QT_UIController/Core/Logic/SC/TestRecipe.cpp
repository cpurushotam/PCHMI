/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test recipe (HMI side) related implementation

***************************************************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string.h>
#include "TestRecipe.h"
#include "DataLogger.h"
#include "PowerLevelSysFrequencySupport.h"

size_t TestRecipe::static_log_id=0;
/******************************************************************************
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
TestRecipe::TestRecipe()
{
    pthread_mutex_init(&m_TestRecipeDataMutex, nullptr);
    //enroll to use logger functionality
    static_log_id = Logger::enroll(this);
	m_InitiateTestRecipeSaveRequest = false;
	m_InitiateTestRecipeResetToDefaultRequest = false;
	//Send the request to read test recipe data to ASC at power up of HMI
    m_InitiateTestRecipeReadRequest = true;
    m_IsTestRecipeUpdated = false;
}

/******************************************************************************
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
TestRecipe::~TestRecipe()
{
	pthread_mutex_destroy(&m_TestRecipeDataMutex);
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
TestRecipestruct::TestRecipestruct()
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
void TestRecipestruct::SetParametersAsPerSystemFrequency()
{
	//TODO:HMI side Empty function for now
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_TEST_RECIPE_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int TestRecipe::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_TEST_RECIPE_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			case TEST_RECIPE_SAVE:
			{
				retVal = 0;
				sendTestRecipeSaveRequestToASC(destination);
				break;
			}

			case TEST_RECIPE_RESET_TO_DEFAULT:
			{
				retVal = 0;
				sendTestRecipeResetToDefaultRequestToASC(destination);
				break;
			}

			case TEST_RECIPE_DATA:
			{
				retVal = 0;
				SendTestRecipeReadRequestToASC(destination);
				break;
			}

			default:
			{
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestRecipe:GetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestRecipe:GetData invalid req");

	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_TEST_RECIPE_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int TestRecipe::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_TEST_RECIPE_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for Test Recipe Data
				case TEST_RECIPE_DATA:
				{
					retVal = 0;
					processTestRecipeReadResponseFromASC(source);
					break;
				}

				case TEST_RECIPE_UPDATE_RESULT:
				{
					retVal = 0;
					processTestRecipeUpdateStatusFromASC(source);
					break;
				}

				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestRecipe:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "TestRecipe:SetData invalid req");
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
void TestRecipe::InitiateTestRecipeSaveRequest()
{
    m_InitiateTestRecipeSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   - Get the maximum value for passed parameter ID
*
* \param   - ParamID - Test Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string TestRecipe::GetTestRecipeParamMinValue(TEST_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator = TestRecipeParamMap.find(ParamID);
    if (MapIterator != TestRecipeParamMap.end())
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
* \param   - ParamID - Test Recipe Parameter Identifier
*
* \return  - Maximum value for passed parameter ID. Empty string if parameter
*			 ID does not exist.
*
******************************************************************************/
std::string TestRecipe::GetTestRecipeParamMaxValue(TEST_RECIPE_PARAM_ID ParamID)
{
    std::string Value = "";
    auto MapIterator = TestRecipeParamMap.find(ParamID);
    if (MapIterator != TestRecipeParamMap.end())
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
* \brief   - This function returns test recipe data parameters.
*
* \param   - None.
*
* \return  - m_TestRecipeData : The test recipe data parameters.
*
******************************************************************************/
TestRecipestruct TestRecipe::GetTestRecipeData()
{
    return m_TestRecipeData;
}

/**************************************************************************//**
*
* \brief   - Retuns the status the test recipe update.
*
* \param   - None.
*
* \return  - m_IsTestRecipeUpdated : The test recipe update status.
*
******************************************************************************/
bool TestRecipe::GetIsTestRecipeUpdated()
{
    return m_IsTestRecipeUpdated;
}

/**************************************************************************//**
*
* \brief   - Sets the status of the test recipe update.
*
* \param   - Value : Status flag value from interface.
*
* \return  - None.
*
******************************************************************************/
void TestRecipe::SetIsTestRecipeUpdated(bool Value)
{
    m_IsTestRecipeUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - This function saves test recipe data parameters.
*
* \param   - None.
*
* \return  - m_TestRecipeStruct : The test recipe data parameters.
*
******************************************************************************/
void TestRecipe::SetTestRecipeData(TestRecipestruct m_TestRecipeStruct)
{
    m_TestRecipeData = m_TestRecipeStruct;
    InitiateTestRecipeSaveRequest();
}
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_TEST_RECIPE_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void TestRecipe::sendTestRecipeSaveRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(TestRecipestruct))
    {
        if(m_InitiateTestRecipeSaveRequest == true)
        {
            // update size in destination
            destination->size = sizeof(TestRecipestruct);

            // set valid bit
            destination->config = VALID_BIT;
            m_InitiateTestRecipeSaveRequest = false;

            TestRecipestruct *RecipeData = reinterpret_cast<TestRecipestruct*>(destination->data);

            pthread_mutex_lock(&m_TestRecipeDataMutex);

            RecipeData->TestFreqLimitHigh = m_TestRecipeData.TestFreqLimitHigh;
            RecipeData->TestFreqLimitLow = m_TestRecipeData.TestFreqLimitLow;
            RecipeData->TestFreqOffset = m_TestRecipeData.TestFreqOffset;
            RecipeData->ClearMemoryBeforeTest = m_TestRecipeData.ClearMemoryBeforeTest;
            RecipeData->TestAmplitudeRampTime = m_TestRecipeData.TestAmplitudeRampTime;
            RecipeData->TestAmplitude = m_TestRecipeData.TestAmplitude;
            RecipeData->TestAmpProportionalGain = m_TestRecipeData.TestAmpProportionalGain;
            RecipeData->TestAmpIntegralGain = m_TestRecipeData.TestAmpIntegralGain;
            RecipeData->TestAmpDerivativeGain = m_TestRecipeData.TestAmpDerivativeGain;
            RecipeData->TestPhaseProportionalGain = m_TestRecipeData.TestPhaseProportionalGain;
            RecipeData->TestPhaseIntegralGain = m_TestRecipeData.TestPhaseIntegralGain;
            RecipeData->TestPhaseDerivativeGain = m_TestRecipeData.TestPhaseDerivativeGain;
            RecipeData->TestPhaseloopCF = m_TestRecipeData.TestPhaseloopCF;

            pthread_mutex_unlock(&m_TestRecipeDataMutex);

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
* \brief   - this function will set m_InitiateTestRecipeResetToDefaultRequest to true .
*			 i.e Reset to default request will send .
*
*
* \param   - NA
*
* \return  - void
*
******************************************************************************/
void TestRecipe::InitiateTestRecipeResetToDefaultRequest()
{
	m_InitiateTestRecipeResetToDefaultRequest = true;
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
void TestRecipe::sendTestRecipeResetToDefaultRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateTestRecipeResetToDefaultRequest == true )
        {
            destination->data = 0;
            // update size in destination
            destination->size = sizeof(int);

            // set valid bit
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateTestRecipeResetToDefaultRequest = false;
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
* \brief   - Send a test recipe read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void TestRecipe::SendTestRecipeReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateTestRecipeReadRequest == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateTestRecipeReadRequest = false;
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
void TestRecipe::processTestRecipeReadResponseFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	TestRecipestruct *RecipeData = reinterpret_cast<TestRecipestruct *>(source->data);

	pthread_mutex_lock(&m_TestRecipeDataMutex);

	m_TestRecipeData.TestFreqLimitHigh = RecipeData->TestFreqLimitHigh;
	m_TestRecipeData.TestFreqLimitLow = RecipeData->TestFreqLimitLow;
	m_TestRecipeData.TestFreqOffset = RecipeData->TestFreqOffset;
	m_TestRecipeData.ClearMemoryBeforeTest = RecipeData->ClearMemoryBeforeTest;
	m_TestRecipeData.TestAmplitudeRampTime = RecipeData->TestAmplitudeRampTime;
	m_TestRecipeData.TestAmplitude = RecipeData->TestAmplitude;
	m_TestRecipeData.TestAmpProportionalGain = RecipeData->TestAmpProportionalGain;
	m_TestRecipeData.TestAmpIntegralGain = RecipeData->TestAmpIntegralGain;
	m_TestRecipeData.TestAmpDerivativeGain = RecipeData->TestAmpDerivativeGain;
	m_TestRecipeData.TestPhaseProportionalGain = RecipeData->TestPhaseProportionalGain;
	m_TestRecipeData.TestPhaseIntegralGain = RecipeData->TestPhaseIntegralGain;
	m_TestRecipeData.TestPhaseDerivativeGain = RecipeData->TestPhaseDerivativeGain;
	m_TestRecipeData.TestPhaseloopCF = RecipeData->TestPhaseloopCF;

    m_IsTestRecipeUpdated = true;

	pthread_mutex_unlock(&m_TestRecipeDataMutex);

}

/**************************************************************************//**
*
* \brief   - process the test recipe update status coming from ASC
*
* \param   - source - memory block holding the recipe data received from ASC
*
* \return  - none
*
******************************************************************************/
void TestRecipe::processTestRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source)
{
	TEST_RECIPE_UPDATE_STATUS RecipeUpdateStatus = static_cast<TEST_RECIPE_UPDATE_STATUS>(*source->data);

	//Copy test recipe updated status
	m_testRecipeStatus = RecipeUpdateStatus;

}

/**************************************************************************//**
*
* \brief   - Show Test Recipe Data
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void TestRecipe::ShowTestRecipe()
{
	std::cout << "TestFreqLimitHigh: " << m_TestRecipeData.TestFreqLimitHigh << std::endl;
	std::cout << "TestFreqLimitLow: " << m_TestRecipeData.TestFreqLimitLow << std::endl;
	std::cout << "TestFreqOffset: " << m_TestRecipeData.TestFreqOffset << std::endl;
	std::cout << "ClearMemoryBeforeTest: " << m_TestRecipeData.ClearMemoryBeforeTest << std::endl;
	std::cout << "TestAmplitudeRampTime: " << m_TestRecipeData.TestAmplitudeRampTime << std::endl;
	std::cout << "TestAmplitude: " << m_TestRecipeData.TestAmplitude << std::endl;
	std::cout << "TestAmpProportionalGain: " << m_TestRecipeData.TestAmpProportionalGain << std::endl;
	std::cout << "TestAmpIntegralGain: " << m_TestRecipeData.TestAmpIntegralGain << std::endl;
	std::cout << "TestAmpDerivativeGain: " << m_TestRecipeData.TestAmpDerivativeGain << std::endl;
	std::cout << "TestPhaseProportionalGain: " << m_TestRecipeData.TestPhaseProportionalGain << std::endl;
	std::cout << "TestPhaseIntegralGain: " << m_TestRecipeData. TestPhaseIntegralGain << std::endl;
	std::cout << "TestPhaseDerivativeGain: " << m_TestRecipeData.TestPhaseDerivativeGain << std::endl;
	std::cout << "TestPhaseloopCF: " << m_TestRecipeData.TestPhaseloopCF << std::endl;
}

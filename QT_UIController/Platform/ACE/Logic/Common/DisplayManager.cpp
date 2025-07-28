/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the function is responsible for Display Manager
***************************************************************************/

#include "DisplayManager.h"
#include "DataLogger.h"

//Initialize variable
/* init log variable */
size_t DisplayMgr::m_log_id = 0;

/**************************************************************************//**
* \brief  - upon creation, creates and saves available inputs and outputs 
*
* \param  - none
*
* \return  - none
*
******************************************************************************/
DisplayMgr::DisplayMgr ()
{
	//enroll to use logger functionality
    m_log_id = Logger::enroll(this);

    m_displayMode = MODE_UNKNOWN;
    m_IsDisplayModeUpdated = false;
}
/**************************************************************************//**
* \brief  - Destructor - delete inputs and outputs 
*
* \param  - none
*
* \return  - none
*
******************************************************************************/

DisplayMgr::~DisplayMgr ()
{
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_DISPLAY_MANAGEMNT_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int DisplayMgr::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	if((destination != nullptr) && (destination->id == MB_ID_DISPLAY_MANAGEMNT_DATA))
	{
		/* Perform Operation Based on sub ID*/
		switch(destination->sub_id)
        {
			// Add cases here as needed

			default:
			{
				/* reset size */
				destination->size = 0;
				/* clear valid bit */
				destination->config = 0;
				/* Log the Alarm */
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DisplayMgr:GetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DisplayMgr:GetData Inval Request");
	}
	return (retVal);

}
/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_DISPLAY_MANAGEMNT_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int DisplayMgr::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_DISPLAY_MANAGEMNT_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for Display Mode Data
                
                case SUB_ID_DISPLAY_MODE:
                {
                	retVal = 0;
                	processDisplayModeFromASC(source);
                	break;
                }
                case SUB_ID_FIELDBUS_TOKEN_STATUS:
                {
                    retVal = 0;
                    processFieldBusTokenStatus(source);
                    break;
                }
				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DisplayMgr:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DisplayMgr:SetData Inval Request");
	}

	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the Display mode coming from ASC.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - None
*
******************************************************************************/
void DisplayMgr::processDisplayModeFromASC(const MEMORY_BLOCK *const source)
{
    //copy incoming data to member variable
    DISPLAY_MODE *displayMode = reinterpret_cast<DISPLAY_MODE *>(source->data);
    m_displayMode = *displayMode;
    m_IsDisplayModeUpdated = true;
}
/**************************************************************************//**
*
* \brief   - process the Fieldbus token coming from ASC.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - None
*
******************************************************************************/
void DisplayMgr::processFieldBusTokenStatus(const MEMORY_BLOCK *const source)
{
    //copy incoming data to member variable
    FIELDBUS_TOKEN *fieldBusTokenStatus = reinterpret_cast<FIELDBUS_TOKEN *>(source->data);
    m_FieldBusTokenStatus = *fieldBusTokenStatus;
    m_IsDisplayModeUpdated = true;
}

/**************************************************************************//**
*
* \brief   - Get the Display mode.
*
* \param   - None
*
* \return  - DISPLAY_MODE - display mode
*
******************************************************************************/
DISPLAY_MODE DisplayMgr::GetDisplayMode()
{
    return m_displayMode;
}

/**************************************************************************//**
*
* \brief   - Get the FieldBus TOken Status.
*
* \param   - None
*
* \return  - TokenStatus
*
******************************************************************************/
FIELDBUS_TOKEN DisplayMgr::GetFieldBusTokenStatus()
{
    return m_FieldBusTokenStatus;
}
/**************************************************************************//**
*
* \brief   - Get the m_IsDisplayModeUpdated flag.
*
* \param   - None
*
* \return  - bool - m_IsDisplayModeUpdated
*
******************************************************************************/
bool DisplayMgr::GetIsDisplayModeUpdatedFlag()
{
    return m_IsDisplayModeUpdated;
}

/**************************************************************************//**
*
* \brief   - set the m_IsDisplayModeUpdated.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void DisplayMgr::SetIsDisplayModeUpdated()
{
    m_IsDisplayModeUpdated = false;
}

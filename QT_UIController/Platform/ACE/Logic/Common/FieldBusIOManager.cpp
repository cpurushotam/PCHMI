/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------
  	 It contains the function is responsible for FieldBus IO Manager
***************************************************************************/
#include  <iostream>
#include  <fstream>
#include  <cstring>
#include  "FieldBusIOManager.h"
#include "DataLogger.h"

//Initialize variable
/* init log variable */
size_t FieldBusIOMgr::m_log_id = 0;

/**************************************************************************//**
* \brief  - upon creation, creates and saves available inputs and outputs
*
* \param  - none
*
* \return  - none
*
******************************************************************************/
FieldBusIOMgr::FieldBusIOMgr ()
{
	//enroll to use logger functionality
    m_log_id = Logger::enroll(this);
	/* Initialize pthread mutex */
	pthread_mutex_init(&m_FbUserIODataMutex, nullptr);
	m_InitiateFieldBusUserIOSaveRequest = false;
	m_InitiateResetToDefaultFieldBusUserIORequest = false;
    //Send the request to read user io data to ASC at power up of HMI
    m_InitiateReadFieldBusUserIORequest = true;
    m_IsLastFieldBusIOUpdated = false;

}

/**************************************************************************//**
* \brief  - Destructor - delete inputs and outputs
*
* \param  - none
*
* \return  - none
*
******************************************************************************/
FieldBusIOMgr::~FieldBusIOMgr ()
{
	pthread_mutex_destroy(&m_FbUserIODataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_FIELDBUS_USER_IO_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int FieldBusIOMgr::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	if((destination != nullptr) && (destination->id == MB_ID_FIELDBUS_USER_IO_DATA))
	{
		/* Perform Operation Based on sub ID*/
		switch(destination->sub_id)
        {
            case READ_FIELDBUS_USER_IO_DATA:
            {
                sendReadFieldBusUserIORequestToASC(destination);
                retVal = 0;
                break;
            }

            case SAVE_FIELDBUS_USER_IO_DATA:
            {
                sendFieldBusUserIOSaveRequest(destination);
                retVal = 0;
                break;
            }

            case FIELDBUS_USER_IO_RESET_TO_DEFAULT:
            {
                sendResetToDefaultFieldBusUserIORequest(destination);
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
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "FieldBusUserIO:GetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "FieldBusUserIO:GetData Invalid Request");
	}

	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_FIELDBUS_USER_IO_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int FieldBusIOMgr::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_FIELDBUS_USER_IO_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for User IO Data
                case READ_FIELDBUS_USER_IO_DATA:
                {
                    retVal = 0;
                    processReadFieldBusUserIOResponseFromASC(source);
                    break;
                }

				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "FieldBusUserIO:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "FieldBusUserIO:SetData Invalid Request");
	}

	return (retVal);
}

/**************************************************************************/ /**
*
* \brief   - send read FieldBus user IO(control/status words) requests
* 			 to ASC for memory block ID MB_ID_FIELDBUS_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void FieldBusIOMgr::sendReadFieldBusUserIORequestToASC(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(int))
    {
        if (m_InitiateReadFieldBusUserIORequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateReadFieldBusUserIORequest = false;
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

/**************************************************************************/ /**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_FIELDBUS_USER_IO_DATA.
* 		     Send save command or request to ASC for saving FieldBus User IO data
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void FieldBusIOMgr::sendFieldBusUserIOSaveRequest(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(m_strFieldBusUserIO))
    {
        /* Check the save request has came or not */
        if (m_InitiateFieldBusUserIOSaveRequest == true)
        {
            /* Update the Data to be send to ASC */
            /* clear the save request flag */
        	m_InitiateFieldBusUserIOSaveRequest = false;

        	/* update size in destination */
            destination->size = sizeof(m_strFieldBusUserIO);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* User IO structure pointer point's to actual memory block Data */
            FB_USERIO *FieldBusUserIOData = reinterpret_cast<FB_USERIO *>(destination->data);
            /* lock the resources using mutex */
            pthread_mutex_lock(&m_FbUserIODataMutex);
            memcpy(FieldBusUserIOData, &m_strFieldBusUserIO, sizeof(m_strFieldBusUserIO));
            /* Unlock the resources */
            pthread_mutex_unlock(&m_FbUserIODataMutex);
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

/**************************************************************************/ /**
*
* \brief   - send FieldBus reset to default requests to ASC for memory block
*            ID MB_ID_FIELDBUS_USER_IO_DATA.
*
* 		     Get the default FieldBus User IO(Control/Status Words) value from ASC
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void FieldBusIOMgr::sendResetToDefaultFieldBusUserIORequest(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(int))
    {
        if (m_InitiateResetToDefaultFieldBusUserIORequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateResetToDefaultFieldBusUserIORequest = false;
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

/**************************************************************************/ /**
*
* \brief   - send the Read response to HMI for memory block ID MB_ID_FIELDBUS_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent
*
* \return  - None
*
******************************************************************************/
void FieldBusIOMgr::processReadFieldBusUserIOResponseFromASC(const MEMORY_BLOCK *const source)
{
    // copy incoming data to structure member variable
	FB_USERIO *FieldBusUserIOData = reinterpret_cast<FB_USERIO *>(source->data);
    pthread_mutex_lock(&m_FbUserIODataMutex);
    memcpy(&m_strFieldBusUserIO, FieldBusUserIOData, sizeof(FB_USERIO));
    pthread_mutex_unlock(&m_FbUserIODataMutex);
    m_IsLastFieldBusIOUpdated = true;
}

/**************************************************************************/ /**
*
* \brief   - Returns flag m_IsLastFieldBusIOUpdated when the data from ASC is updated.
*
* \param   - None
*
* \return  - bool
*
******************************************************************************/
bool FieldBusIOMgr::IsFieldBusUsrIOStructUpdated()
{
    return m_IsLastFieldBusIOUpdated;
}

/**************************************************************************/ /**
*
* \brief   - Returns m_strFieldBusUserIO struct when the data from ASC is updated.
*
* \param   - None
*
* \return  - bool
*
******************************************************************************/
FB_USERIO FieldBusIOMgr::GetFieldBusUsrIOStruct()
{
    return m_strFieldBusUserIO;
}

/**************************************************************************/ /**
*
* \brief   - Reset the m_IsLastFieldBusIOUpdated flag to false .
*
* \param   - None
*
* \return  - none
*
******************************************************************************/
void FieldBusIOMgr::ResetFieldBusUsrIOUpdatedFlag()
{
    m_IsLastFieldBusIOUpdated = false;
}

/**************************************************************************/ /**
*
* \brief   - Send save request to ASC when user presses the save button with the updated values.
*
* \param   - FB_USERIO structure.
*
* \return  - none
*
******************************************************************************/
void FieldBusIOMgr::SaveIndFieldBusUserIOValues(FB_USERIO Fb_UserIO)
{
    m_strFieldBusUserIO = Fb_UserIO;
    m_InitiateFieldBusUserIOSaveRequest = true;
}

/**************************************************************************/ /**
*
* \brief   - Set the ResetToDefault Request from HMI.
*
* \param   - bool value.
*
* \return  - none
*
******************************************************************************/
void FieldBusIOMgr::SetResetToDefaultIndFieldBusUsrIORequest(bool value)
{
    m_InitiateResetToDefaultFieldBusUserIORequest = value;
}

/**************************************************************************/ /**
*
* \brief   - Print FieldBus User IO(Control/Status Words) values.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void FieldBusIOMgr::PrintFieldBusUserIO()
{
    std::cout << "****FieldBus User IO(Control/Status Words) Data****" << std::endl;
    std::cout << "Control Input 1 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.FB_EVENT << std::endl;
    std::cout << "Control Input 1 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.IsControlWordEnabled << std::endl;

    std::cout << "Control Input 2 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.FB_EVENT << std::endl;
    std::cout << "Control Input 2 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.IsControlWordEnabled << std::endl;

    std::cout << "Control Input 3 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.FB_EVENT << std::endl;
    std::cout << "Control Input 3 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.IsControlWordEnabled << std::endl;

    std::cout << "Status Output 1 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.FB_EVENT << std::endl;
    std::cout << "Status Output 1 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.IsStatusWordEnabled << std::endl;

    std::cout << "Status Output 2 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.FB_EVENT << std::endl;
    std::cout << "Status Output 2 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.IsStatusWordEnabled << std::endl;

    std::cout << "Status Output 3 Event: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.FB_EVENT << std::endl;
    std::cout << "Status Output 3 IsPinEnabled: " << m_strFieldBusUserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.IsStatusWordEnabled << std::endl;
}

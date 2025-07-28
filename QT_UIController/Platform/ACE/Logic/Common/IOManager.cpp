/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the function is responsible for Digital IO Manager 
***************************************************************************/
#include  <iostream>
#include  <fstream>
#include  "IOManager.h"
#include "DataLogger.h"
#include  <cstring>

//Initialize variable
/* init log variable */
size_t DigitalIOMgr::m_log_id = 0;

/**************************************************************************//**
* \brief  - upon creation, creates and saves available inputs and outputs 
*
* \param  - none
*
* \return  - none
*
******************************************************************************/
DigitalIOMgr::DigitalIOMgr ()
{
	//enroll to use logger functionality
    m_log_id = Logger::enroll(this);
	/* Initialize pthread mutex */
	pthread_mutex_init(&m_DgtUserIODataMutex, nullptr);
	m_InitiateUserIOSaveRequest = false;
	m_InitiateAnalogUserIOSaveRequest = false;
	m_InitiateResetToDefaultRequest = false;
    m_InitiateResetToDefaultAnalogUserIORequest = false;
    //Send the request to read user io data to ASC at power up of HMI
    m_InitiateReadRequest = true ;
    m_InitiateReadAnalogUserIORequest = true;
    m_InitiateReadDigitalOPRequest = true;
    m_IsLastDigitalIOUpdated=false;
    m_IsLastAnalogIOUpdated = false;
    m_InitiateRefreshUserIORequest=false;
    m_IsLastDigitalInputsUpdated=false;

}
/**************************************************************************//**
* \brief  - Destructor - delete inputs and outputs 
*
* \param  - none
*
* \return  - none
*
******************************************************************************/

DigitalIOMgr::~DigitalIOMgr ()
{
	pthread_mutex_destroy(&m_DgtUserIODataMutex);
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
void DigitalIOMgr::InitiateUserIOSaveRequest()
{
	/* set flag */
	m_InitiateUserIOSaveRequest = true;
}

/**************************************************************************/ /**
*
* \brief   - call this method on HMI side when you click analog user IO save button.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::InitiateAnalogUserIOSaveRequest()
{
    /* set flag */
    m_InitiateAnalogUserIOSaveRequest = true;
}
/**************************************************************************/ /**
*
* \brief   -HMI/QML should call this function when it wants to send the 
* 	        request to ASC to set user io value to its default value
* 	        
* \param   - None
*
* \return  - void
******************************************************************************/
void DigitalIOMgr::InitiateResetToDefaultRequest()
{
	/* set flag */
	m_InitiateResetToDefaultRequest = true ;
}

/**************************************************************************/ /**
*
* \brief   -HMI/QML should call this function when it wants to send the
* 	        request to ASC to set analog user io value to its default value
*
* \param   - None
*
* \return  - void
******************************************************************************/
void DigitalIOMgr::InitiateResetToDefaultAnalogUserIORequest()
{
    /* set flag */
    m_InitiateResetToDefaultAnalogUserIORequest = true;
}
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
* 		     Send save command or request to ASC for saving User IO data
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendSaveRequest(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(m_strUserIO))
    {
        /* Check the save request has came or not */
        if(m_InitiateUserIOSaveRequest == true)
        {
            /* Update the Data to be send to ASC */
            /* clear the save request flag */
        	m_InitiateUserIOSaveRequest = false ;
            /* update size in destination */
            destination->size = sizeof(m_strUserIO);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* User IO structure pointer point's to actual memory block Data */
            USERIO *UserIOData = reinterpret_cast<USERIO *>(destination->data);
            /* lock the resources using mutex */
            pthread_mutex_lock(&m_DgtUserIODataMutex);
            memcpy(UserIOData,&m_strUserIO,sizeof(m_strUserIO));
            /* Unlock the resources */
            pthread_mutex_unlock(&m_DgtUserIODataMutex);
  

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
* \brief   - send the requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
* 		     Send save command or request to ASC for saving Analog User IO data
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendAnalogUserIOSaveRequest(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(m_strAnalogUserIO))
    {
        /* Check the save request has came or not */
        if (m_InitiateAnalogUserIOSaveRequest == true)
        {
            /* Update the Data to be send to ASC */
            /* clear the save request flag */
            m_InitiateAnalogUserIOSaveRequest = false;
            /* update size in destination */
            destination->size = sizeof(m_strAnalogUserIO);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* User IO structure pointer point's to actual memory block Data */
            USERIO_ANALOG *AnalogUserIOData = reinterpret_cast<USERIO_ANALOG *>(destination->data);
            /* lock the resources using mutex */
            pthread_mutex_lock(&m_DgtUserIODataMutex);
            memcpy(AnalogUserIOData, &m_strAnalogUserIO, sizeof(m_strAnalogUserIO));
            /* Unlock the resources */
            pthread_mutex_unlock(&m_DgtUserIODataMutex);
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
* \brief   - send reset to default requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* 		     Get the default User IO value from ASC
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendResetToDefaultRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateResetToDefaultRequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateResetToDefaultRequest = false;
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
* \brief   - send analog reset to default requests to ASC for memory block
*            ID MB_ID_DIGITAL_USER_IO_DATA.
*
* 		     Get the default Analog User IO value from ASC
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendResetToDefaultAnalogUserIORequest(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(int))
    {
        if (m_InitiateResetToDefaultAnalogUserIORequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateResetToDefaultAnalogUserIORequest = false;
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
* \brief   - send reset to default requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* 		     Get the default User IO value from ASC
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendReadDgtUserIORequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateReadRequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateReadRequest = false;
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
* \brief   - send read analog user IO requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendReadAnalogUserIORequestToASC(MEMORY_BLOCK *const destination)
{
    if (destination->size >= sizeof(int))
    {
        if (m_InitiateReadAnalogUserIORequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateReadAnalogUserIORequest = false;
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
* \brief   - send reset to default requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* 		     
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendReadDiagtUserIODigitalIpReq(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateReadDigitalOPRequest == true)
        {
            destination->data = 0;
            /* update size in destination */
            destination->size = sizeof(int);
            /* set valid bit */
            destination->config = VALID_BIT;
            /* Reset the flag to false as we have sent the request */
            m_InitiateReadDigitalOPRequest = false;
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
* \brief   -  Send Digital OUtput pins to ASC on Refresh button clciked.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void DigitalIOMgr::sendDiagnosticUserIODigitalOpPins(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_DiagnosticsDigitalOutputs))
    {
        /* Check the save request has came or not */
        if(m_InitiateRefreshUserIORequest == true)
        {
            /* Update the Data to be send to ASC */
            /* update size in destination */
            destination->size = sizeof(m_DiagnosticsDigitalOutputs);
            /* set valid bit */
            destination->config = VALID_BIT;
            /*DiagnosticUserIOOutputs structure pointer point's to actual memory block Data */
            DiagnosticUserIOOutputs *DiagnosticUserIODigitalOutputs = reinterpret_cast<DiagnosticUserIOOutputs *>(destination->data);
            /* lock the resources using mutex */
            pthread_mutex_lock(&m_DgtUserIODataMutex);
            memcpy(DiagnosticUserIODigitalOutputs,&m_DiagnosticsDigitalOutputs,sizeof(m_DiagnosticsDigitalOutputs));
            /* Unlock the resources */
            pthread_mutex_unlock(&m_DgtUserIODataMutex);

            m_InitiateRefreshUserIORequest = false ;

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
* \brief   - send the requests to ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int DigitalIOMgr::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	if((destination != nullptr) && (destination->id == MB_ID_DIGITAL_USER_IO_DATA))
	{
		/* Perform Operation Based on sub ID*/
		switch(destination->sub_id)
        {
            case READ_DIGITAL_USER_IO_DATA:
            {
                retVal = 0;
                sendReadDgtUserIORequestToASC(destination);
                break;
            }
			case SAVE_DIGITAL_USER_IO_DATA:
            {
				sendSaveRequest(destination);
				retVal = 0;
				break;
			}
			case DIGITAL_USER_IO_RESET_TO_DEFAULT:
			{
				sendResetToDefaultRequest(destination);	
				retVal = 0;
				break;
			}
            case REFRESH_DIAGNOSTIC_USERIO:
            {
                sendDiagnosticUserIODigitalOpPins(destination);
                retVal = 0;
                break;
            }
            case READ_DIAGNOSTIC_USERIO_DATA:
            {
                sendReadDiagtUserIODigitalIpReq(destination);
                retVal = 0;
                break;
            }
            case READ_ANALOG_USER_IO_DATA:
            {
                sendReadAnalogUserIORequestToASC(destination);
                retVal = 0;
                break;
            }
            case SAVE_ANALOG_USER_IO_DATA:
            {               
                sendAnalogUserIOSaveRequest(destination);
                retVal = 0;
                break;
            }
            case ANALOG_USER_IO_RESET_TO_DEFAULT:
            {
                sendResetToDefaultAnalogUserIORequest(destination);
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
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DigitalUserIO:GetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DgtUserIO:GetData Inval Request");
	}
	return (retVal);

}
/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* \param   - source - Memory block containing data coming from ASC.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int DigitalIOMgr::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_DIGITAL_USER_IO_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response from ASC for User IO Data
				case READ_DIGITAL_USER_IO_DATA:
				{
					retVal = 0;
					processReadResponseFromASC(source);
					break;
                }
                case READ_DIAGNOSTIC_USERIO_DATA:
                {
                    retVal = 0;
                    processReadUserIODgInputsFromASC(source);
                    break;
                }
                case READ_ANALOG_USER_IO_DATA:
                {
                    retVal = 0;
                    processReadAnalogUserIOResponseFromASC(source);                   
                    break;
                }
                                
				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DgtUserIO:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DgtUserIO:SetData Inval Request");
	}

	return (retVal);
}



/**************************************************************************//**
*
* \brief   - send the Read response to HMI for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::processReadResponseFromASC(const MEMORY_BLOCK *const source)
{
	//copy incoming data to structure member variable
	USERIO *UserIOData = reinterpret_cast<USERIO *>(source->data);
	pthread_mutex_lock(&m_DgtUserIODataMutex);
	memcpy(&m_strUserIO,UserIOData,sizeof(USERIO));
	pthread_mutex_unlock(&m_DgtUserIODataMutex);
    m_IsLastDigitalIOUpdated =true;
}

/**************************************************************************/ /**
*
* \brief   - send the Read response to HMI for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::processReadAnalogUserIOResponseFromASC(const MEMORY_BLOCK *const source)
{
    // copy incoming data to structure member variable
    USERIO_ANALOG *AnalogUserIOData = reinterpret_cast<USERIO_ANALOG *>(source->data);
    pthread_mutex_lock(&m_DgtUserIODataMutex);
    memcpy(&m_strAnalogUserIO, AnalogUserIOData, sizeof(USERIO_ANALOG));
    pthread_mutex_unlock(&m_DgtUserIODataMutex);
    m_IsLastAnalogIOUpdated = true;
}

/**************************************************************************//**
*
* \brief   - send the Read response to HMI for memory block ID MB_ID_DIGITAL_USER_IO_DATA.
*
* \param   - destination - Memory block containing data to be sent
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::processReadUserIODgInputsFromASC(const MEMORY_BLOCK *const source)
{
    //copy incoming data to structure member variable
    DiagnosticDigitalInputs *UserIOData = reinterpret_cast<DiagnosticDigitalInputs *>(source->data);
    pthread_mutex_lock(&m_DgtUserIODataMutex);
    memcpy(&m_DiagnosticsDigitalInputs,UserIOData,sizeof(DiagnosticDigitalInputs));
    pthread_mutex_unlock(&m_DgtUserIODataMutex);
    m_IsLastDigitalInputsUpdated = true;
}

/**************************************************************************//**
*
* \brief   - Initiate the Refresh request from HMI to ASC to update the pins.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::InitiateRefreshRequest()
{
    /* set flag */
    m_InitiateRefreshUserIORequest = true;
}

/**************************************************************************//**
*
* \brief   - Initiate the Stop request from HMI to ASC to update the pins.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::InitiateStopRequest()
{
    /* set flag */
    m_InitiateRefreshUserIORequest = false;
}

/**************************************************************************//**
*
* \brief   - Sets the USERIO on HMI..
*
* \param   - None
*
* \return  - USERIO
*
******************************************************************************/
USERIO DigitalIOMgr::GetDigitalIOStruct()
{
    return m_strUserIO;
}

/**************************************************************************/ /**
*
* \brief   - Sets the USERIO Analog on HMI..
*
* \param   - None
*
* \return  - USERIO_ANALOG
*
******************************************************************************/
USERIO_ANALOG DigitalIOMgr::GetAnalogIOStruct()
{
    return m_strAnalogUserIO;
}

/**************************************************************************//**
*
* \brief   - Returns flag m_IsLastDigitalIOUpdated when the data from ASC is updated.
*
* \param   - None
*
* \return  - bool
*
******************************************************************************/
bool DigitalIOMgr::IsDigitalIOStructUpdated()
{
    return m_IsLastDigitalIOUpdated;
}

/**************************************************************************/ /**
*
* \brief   - Returns flag m_IsLastAnalogIOUpdated when the data from ASC is updated.
*
* \param   - None
*
* \return  - bool
*
******************************************************************************/
bool DigitalIOMgr::IsAnalogIOStructUpdated()
{
    return m_IsLastAnalogIOUpdated;
}

/**************************************************************************//**
*
* \brief   - Reset the m_IsLastDigitalIOUpdated flag to false .
*
* \param   - None
*
* \return  - none
*
******************************************************************************/
void  DigitalIOMgr ::ResetIsLastDigitalIOUpdatedFlag ()
{
    m_IsLastDigitalIOUpdated = false;
}

/**************************************************************************/ /**
*
* \brief   - Reset the m_IsLastAnalogIOUpdated flag to false .
*
* \param   - None
*
* \return  - none
*
******************************************************************************/
void DigitalIOMgr::ResetIsLastAnalogIOUpdatedFlag()
{
    m_IsLastAnalogIOUpdated = false;
}

/**************************************************************************//**
*
* \brief   - Send save request to ASC when user presses the save button with the updated values.
*
* \param   - USERIO structure.
*
* \return  - none
*
******************************************************************************/
void  DigitalIOMgr::saveDigitalUserIOValues(USERIO userI0)
{
    m_strUserIO = userI0;
    m_InitiateUserIOSaveRequest =true;
}

/**************************************************************************/ /**
*
* \brief   - Send save request to ASC when user presses the save button with the updated values.
*
* \param   - USERIO structure.
*
* \return  - none
*
******************************************************************************/
void DigitalIOMgr::SaveAnalogUserIOValues(USERIO_ANALOG AnalogUserI0)
{
    m_strAnalogUserIO = AnalogUserI0;
    m_InitiateAnalogUserIOSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   - Set the ResetToDefault Request from HMI.
*
* \param   - bool value.
*
* \return  - none
*
******************************************************************************/
void  DigitalIOMgr ::setResetToDefaultDigiUsrIORequest(bool value)
{
    m_InitiateResetToDefaultRequest =value;
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
void DigitalIOMgr::SetResetToDefaultAnalogUsrIORequest(bool value)
{
    m_InitiateResetToDefaultAnalogUserIORequest = value;
}

/**************************************************************************//**
*
* \brief   - UPdate the pins configured by user to ASC from HMI.
*
* \param   - DiagnosticUserIOOutputs.
*
* \return  - none
*
******************************************************************************/
void  DigitalIOMgr:: setDignUserIODigitalOP(DiagnosticUserIOOutputs diagnosticDigtalOp)
{
    m_DiagnosticsDigitalOutputs = diagnosticDigtalOp;
}

/**************************************************************************//**
*
* \brief   - Returns flag m_IsLastDigitalIOUpdated when the data from ASC is updated.
*
* \param   - None
*
* \return  - bool
*
******************************************************************************/
bool DigitalIOMgr::IsDiagnosticDigitalInputsUpdated()
{
    return m_IsLastDigitalInputsUpdated;
}
/**************************************************************************//**
*
* \brief   - Reset the m_IsLastDigitalInputsUpdated flag to false .
*
* \param   - None
*
* \return  - none
*
******************************************************************************/
void  DigitalIOMgr ::ResetDiagnosticDigitalInputsUpdatedFlag ()
{
    m_IsLastDigitalInputsUpdated = false;
}
/**************************************************************************//**
*
* \brief   - Used to return the DiagnosticDigitalInputs structure to HMI .
*
* \param   - None
*
* \return  - DiagnosticDigitalInputs
*
******************************************************************************/
DiagnosticDigitalInputs DigitalIOMgr::GetDignosticDigitalInputs()
{
    return m_DiagnosticsDigitalInputs;
}

/**************************************************************************/ /**
*
* \brief   - Print Analog User IO values.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void DigitalIOMgr::PrintAnalogUserIO()
{
    std::cout << "****Analog User IO Data****" << std::endl;
    std::cout << "Analog Input 1 Event: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogInput.J3_17.PS_EVENT << std::endl;
    std::cout << "Analog Input 1 IsPinEnabled: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogInput.J3_17.IsPinEnabled << std::endl;

    std::cout << "Analog Input 2 Event: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogInput.J3_18.PS_EVENT << std::endl;
    std::cout << "Analog Input 2 IsPinEnabled: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogInput.J3_18.IsPinEnabled << std::endl;

    std::cout << "Analog Output 1 Event: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.PS_EVENT << std::endl;
    std::cout << "Analog Output 1 IsPinEnabled: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.IsPinEnabled << std::endl;

    std::cout << "Analog Output 2 Event: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.PS_EVENT << std::endl;
    std::cout << "Analog Output 2 IsPinEnabled: " << m_strAnalogUserIO.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.IsPinEnabled << std::endl;
}

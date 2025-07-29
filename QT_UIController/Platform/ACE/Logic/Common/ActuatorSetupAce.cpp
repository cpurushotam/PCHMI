/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Actuator setup related implementation

***************************************************************************/

#include <cstring>
#include <algorithm>
#include "ActuatorSetupAce.h"
#include "DataLogger.h"

size_t ActuatorSetupACE::static_log_id = 0;

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
ActuatorSetupACE::ActuatorSetupACE()
{
    //enroll to use logger functionality
    static_log_id = Logger::enroll(this);
    pthread_mutex_init(&m_ActuatorSetupDataMutex, nullptr);

    m_InitiateActuatorSetupReadOnPowerUp   = true;
    m_InitiateActuatorSetupScreenOnRequest = false;
    m_InitiateActuatorSetupOperationType   = false;
    m_InitiateActuatorSetupHornRetract     = false;
    m_InitiateActuatorSetupHornClampOnOff  = false;

    m_IsActuatorSetupDataUpdated     = false;
    m_HornDownClampOnOff             = false;
    m_ActuatorSetupScreenOpenOnHMI   = REQUEST_ACTUATOR_SETUP_LEAVE_SCREEN;
    m_ActuatorSetupOperationType     = HORN_DOWN_OP_TYPE;
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
ActuatorSetupACE::~ActuatorSetupACE()
{
	pthread_mutex_destroy(&m_ActuatorSetupDataMutex);
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_ACTUATOR_SETUP_DATA
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int ActuatorSetupACE::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

	if( (destination != nullptr) && (destination->id == MB_ID_ACTUATOR_SETUP_DATA) )
	{
        switch(destination->sub_id)
        {
        	//Send request to ASC to get the requested actuator setup data
			case READ_ACTUATOR_SETUP_DATA:
			{
				retVal = 0;
				sendActuatorSetupReadRequestToASC(destination);
				break;
			}
			case ENTER_LEAVE_ACTUATOR_SETUP_SCREEN:
			{
                retVal = 0;
				sendActuatorSetupScreenOnReadRequestToASC(destination);
				break;
			}
			case SELECT_ACTUATOR_SETUP_OPEARTION_TYPE:
			{
				retVal = 0;
				sendActuatorSetupOperationTypeReadRequestToASC(destination);
				break;
			}
			case INITIATE_ACTUATOR_SETUP_HORN_RETRACT:
			{
				retVal = 0;
				sendActuatorSetupHornRetractRequestToASC(destination);
				break;
			}
			case ACTUATOR_SETUP_HORN_CLAMP_ON_OFF:
			{
				retVal = 0;
				sendActuatorSetupHornClampOnOffRequestToASC(destination);
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
				snprintf(msg,buff_size_config,"ActuatorSetup GetData default case");
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
        snprintf(msg,buff_size_config,"ActuatorSetup invalid case\n");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }

   return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_ACTUATOR_SETUP_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int ActuatorSetupACE::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if((source != nullptr) && (source->id == MB_ID_ACTUATOR_SETUP_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response coming from ASC for actuator setup data
				case READ_ACTUATOR_SETUP_DATA:
				{
					retVal = 0;
					processActuatorSetupReadResponseFromASC(source);
					break;
				}
				
				//Process response coming from ASC to synch actuator setup data on unit change.
				case SYNCH_ACTUATOR_SETUP_DATA:
				{
					retVal = 0;
					processSynchActuatorSetupDataFromASC(source);
					break;
				}
				
				default:
				{
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ActuatorSetup:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ActuatorSetup:SetData invalid req");
	}

	return (retVal);
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate Actuator Setup Horn Retract.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::initiateActuatorSetupHornRetractRequest()
{
    m_InitiateActuatorSetupHornRetract = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate Actuator Setup Screen On Request.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::initiateActuatorSetupScreenOnRequestRequest()
{
    m_InitiateActuatorSetupScreenOnRequest = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate Actuator Setup Operation Type .
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::initiateActuatorSetupOperationTypeRequest()
{
    m_InitiateActuatorSetupOperationType = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to initiate Actuator Setup Horn Clamp On Off.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::initiateActuatorSetupHornClampOnOffRequest()
{
    m_InitiateActuatorSetupHornClampOnOff = true;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to set Horn Down Clamp On Off status.
*
* \param   - status : Horn Down Clamp On Off status.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::setHornDownClampOnOff(bool status)
{
    m_HornDownClampOnOff = status;
    initiateActuatorSetupHornClampOnOffRequest();
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to set Actuator Setup Operation Type.
*
* \param   - type : Actuator Setup Operation Type.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::setActuatorSetupOperationType(ACTUATOR_SETUP_OP_TYPE type)
{
    m_ActuatorSetupOperationType = type;
    initiateActuatorSetupOperationTypeRequest();
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to get Actuator Setup Operation Type.
*
* \param   - None.
*
* \return  - m_ActuatorSetupOperationType : Actuator Setup Operation Type.
******************************************************************************/
ACTUATOR_SETUP_OP_TYPE ActuatorSetupACE::getActuatorSetupOperationType()
{
    return m_ActuatorSetupOperationType;
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to set Actuator Setup Screen Open On HMI value.
*
* \param   - data : Actuator Setup Screen Open On HMI value.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::setActuatorSetupScreenOpenOnHMI(ACTUATOR_SETUP_SCREEN_DATA data)
{
    m_ActuatorSetupScreenOpenOnHMI = data;
    initiateActuatorSetupScreenOnRequestRequest();
}

/**************************************************************************//**
*
* \brief   - HMI/front end code should call this function to read Actuator Setup Data.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ActuatorSetupStruct ActuatorSetupACE::getActuatorSetupData()
{
    return m_SetupData;
}

/**************************************************************************//**
*
* \brief   - Below function returns the update status of Actuator Setup Data.
*
* \param   - None.
*
* \return  - m_IsActuatorSetupDataUpdated :
******************************************************************************/
bool ActuatorSetupACE::getIsDataFlagUpdated()
{
    return m_IsActuatorSetupDataUpdated;
}

/**************************************************************************//**
*
* \brief   - Below function reset the update status of Actuator Setup Data.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupACE::resetDataFlagUpdated()
{
    m_IsActuatorSetupDataUpdated =false;
}

/**************************************************************************//**
*
* \brief   - Send a actuator setup read request on power up to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ActuatorSetupACE::sendActuatorSetupReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateActuatorSetupReadOnPowerUp == true )
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            m_InitiateActuatorSetupReadOnPowerUp = false;
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
* \brief   - Send a actuator setup screen enter/leave request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ActuatorSetupACE::sendActuatorSetupScreenOnReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
	{
		if(m_InitiateActuatorSetupScreenOnRequest == true )
		{
            ACTUATOR_SETUP_SCREEN_DATA *Data = reinterpret_cast<ACTUATOR_SETUP_SCREEN_DATA *>(destination->data);
            *Data = m_ActuatorSetupScreenOpenOnHMI;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

			//Reset the flag to false as we have sent the request.
			m_InitiateActuatorSetupScreenOnRequest = false;
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
* \brief   - Send a actuator setup operation type read request to ASC(e.g Horn Down or Find part contact)
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ActuatorSetupACE::sendActuatorSetupOperationTypeReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
	{
		if(m_InitiateActuatorSetupOperationType == true )
		{
            ACTUATOR_SETUP_OP_TYPE *Data = reinterpret_cast<ACTUATOR_SETUP_OP_TYPE *>(destination->data);
            *Data = m_ActuatorSetupOperationType;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
			
			//Reset the flag to false as we have sent the request.
			m_InitiateActuatorSetupOperationType = false;
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
* \brief   - Send a actuator setup horn retract read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ActuatorSetupACE::sendActuatorSetupHornRetractRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(bool))
	{
		if(m_InitiateActuatorSetupHornRetract == true )
		{
			destination->size = sizeof(bool);
			destination->config = VALID_BIT;
			
			//Reset the flag to false as we have sent the request.
			m_InitiateActuatorSetupHornRetract = false;
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
* \brief   - Send a actuator setup horn clamp ON/OFF read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ActuatorSetupACE::sendActuatorSetupHornClampOnOffRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(bool))
	{
		if(m_InitiateActuatorSetupHornClampOnOff == true )
		{
            bool *Data = reinterpret_cast<bool *>(destination->data);
            *Data = m_HornDownClampOnOff;
            destination->size = sizeof(bool);
            destination->config = VALID_BIT;
			
			//Reset the flag to false as we have sent the request.
			m_InitiateActuatorSetupHornClampOnOff = false;
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
* \brief   - process the read Actuator setup response coming from ASC
*
* \param   - source - memory block holding the actuator setup data received from ASC
*
* \return  - none
*
******************************************************************************/
void ActuatorSetupACE::processActuatorSetupReadResponseFromASC(const MEMORY_BLOCK *const source)
{
    //copy incoming data to structure member variable
	ActuatorSetupStruct *ActuatorSetupData = reinterpret_cast<ActuatorSetupStruct *>(source->data);
    pthread_mutex_lock(&m_ActuatorSetupDataMutex);
    memcpy(&m_SetupData, ActuatorSetupData, sizeof(ActuatorSetupStruct));
    pthread_mutex_unlock(&m_ActuatorSetupDataMutex);
    m_IsActuatorSetupDataUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the requested synch actuator setup data coming from ASC
*
* \param   - source - memory block holding the requested actuator setup data
*			 received from ASC
*			 
* \return  - none
*
******************************************************************************/
void ActuatorSetupACE::processSynchActuatorSetupDataFromASC(const MEMORY_BLOCK *const source)
{
	//Clear all the previous data from the m_SetupData structure.
    memset(&m_SetupData, 0, sizeof(m_SetupData));
   
    //Set the actuator setup read request to true.
    m_InitiateActuatorSetupReadOnPowerUp = true;
}

/**************************************************************************//**
*
* \brief   - show the actuator setup data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ActuatorSetupACE::ShowActuatorSetupData()
{
    if(sizeof(m_SetupData) == 0)
    {
        std::cout << "Requested Actuator Setup is empty" << std::endl;
    }
    else
    {
        std::cout << "m_SetupData.isHornPositionOnGround: "  << m_SetupData.isHornPositionOnGround << std::endl;

        std::cout << "m_SetupData.ActualForce: "  << m_SetupData.ActualForce << std::endl;
        std::cout << "m_SetupData.AbsolutePosition: "  << m_SetupData.AbsolutePosition << std::endl;
        std::cout << "m_SetupData.MaxVelocity: "  << m_SetupData.MaxVelocity << std::endl;
        std::cout << "m_SetupData.Pressure: "  << m_SetupData.Pressure << std::endl;
    }
}

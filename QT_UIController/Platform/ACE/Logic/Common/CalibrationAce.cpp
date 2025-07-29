/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the actuator calibration related implementation
 
***************************************************************************/

#include "CalibrationAce.h"


/******************************************************************************//**
* \brief - Constructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
CalibrationAce::CalibrationAce()
{
	m_bIsPartContactFound = false;
    m_InitiateCalibrationAbortRequest = false;
    m_InitiateCalibrationResetRequest = false;
    m_InitiateQuickCalibrationRequest = false;
    m_InitiatePressureCalibrationRequest = false;
    m_InitiateForceCalibrationRequest = false;
    m_InitiateUserEnteredPressure1SendRequest = false;
    m_InitiateUserEnteredPressure2SendRequest = false;
    m_InitiateUserEnteredPressure3SendRequest = false;
    m_InitiateUserEnteredForce1SendRequest = false;
    m_InitiateUserEnteredForce2SendRequest = false;
    m_UserEnterdPressure1 = 0.0f;
    m_UserEnterdPressure2 = 0.0f;
    m_UserEnterdPressure3 = 0.0f;
    m_UserEnterdForce1 = 0.0f;
    m_UserEnterdForce2 = 0.0f;
}

/******************************************************************************//**
* \brief - Destructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
CalibrationAce::~CalibrationAce()
{

}

/**************************************************************************//**
*
* \brief   - GetData Interface implementation for calibration data. 
*           
* \param   - Address of destination Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int CalibrationAce::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	
	if( (destination != nullptr) && (destination->id == MB_ID_CALIBRATION_DATA) )
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			case SUB_ID_ABORT_CALIBRATION:
			{
				retVal = 0;
				sendAbortCalibrationRequest(destination);
				break;
			}
			
			case SUB_ID_RESET_CALIBRATION:
			{
				retVal = 0;
				sendResetCalibrationRequest(destination);
				break;
			}
			
			case SUB_ID_START_QUICK_CALIBRATION:
			{
				retVal = 0;
				sendStartQuickCalibrationRequest(destination);
				break;
			}
						
			case SUB_ID_START_PRESSURE_CALIBRATION:
			{
				retVal = 0;
				sendStartPressureCalibrationRequest(destination);
				break;
			}
			
			case SUB_ID_START_FORCE_CALIBRATION:
			{
				retVal = 0;
				sendStartForceCalibrationRequest(destination);
				break;
			}
							
			case SUB_ID_USER_ENTERED_PRESSURE_1:
			{
				retVal = 0;
				sendUserEnteredPressure1(destination);
				break;
			}
			
			case SUB_ID_USER_ENTERED_PRESSURE_2:
			{
				retVal = 0;
				sendUserEnteredPressure2(destination);
				break;
			}
			
			case SUB_ID_USER_ENTERED_PRESSURE_3:
			{
				retVal = 0;
				sendUserEnteredPressure3(destination);
				break;
			}
			
			case SUB_ID_USER_ENTERED_FORCE_1:
			{
				retVal = 0;
				sendUserEnteredForce1(destination);
				break;
			}
			
			case SUB_ID_USER_ENTERED_FORCE_2:
			{
				retVal = 0;
				sendUserEnteredForce2(destination);
				break;
			}

			default:
			{				
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Calibration GetData default case");
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
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Calibration GetData invalid request");
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - SetData Interface implementation for calibration data.           
*
* \param   - Address of source Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int CalibrationAce::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
	
	if( (source != nullptr) && (source->id == MB_ID_CALIBRATION_DATA) )
	{
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			// perform operation based on sub id
			switch(source->sub_id)
			{				
			 	case SUB_ID_CALIBRATION_PART_CONTACT_FOUND:
				{
					retVal = 0;
					processPartContactFoundStatusValue(source);
					break;
				}
				
				default:
				{
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Calibration SetData default case");
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
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Calibration SetData invalid request");
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - Get the Part Contact Found Status Value
*
* \param   - none
* \return  - true if part contact is found else false
*
******************************************************************************/
bool CalibrationAce::GetPartContactFoundStatusValue()
{
    return m_bIsPartContactFound;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the calibration abort request to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateCalibrationAbortRequest()
{
    m_InitiateCalibrationAbortRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the calibration reset request to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateCalibrationResetRequest()
{
    m_InitiateCalibrationResetRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the quick calibration request to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateQuickCalibrationRequest()
{
    m_InitiateQuickCalibrationRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the pressure calibration request to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiatePressureCalibrationRequest()
{
    m_InitiatePressureCalibrationRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the force calibration request to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateForceCalibrationRequest()
{
    m_InitiateForceCalibrationRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the user entered pressure value 1 to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateUserEnteredPressure1SendRequest(float Value)
{
    m_UserEnterdPressure1 = Value;
    m_InitiateUserEnteredPressure1SendRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the user entered pressure value 2 to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateUserEnteredPressure2SendRequest(float Value)
{
    m_UserEnterdPressure2 = Value;
    m_InitiateUserEnteredPressure2SendRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the user entered pressure value 3 to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateUserEnteredPressure3SendRequest(float Value)
{
    m_UserEnterdPressure3 = Value;
    m_InitiateUserEnteredPressure3SendRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the user entered force value 1 to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateUserEnteredForce1SendRequest(float Value)
{
    m_UserEnterdForce1 = Value;
    m_InitiateUserEnteredForce1SendRequest = true;
}

/**************************************************************************//**
*
* \brief   - Call this from QML to send the user entered force value 2 to ASC
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void CalibrationAce::InitiateUserEnteredForce2SendRequest(float Value)
{
    m_UserEnterdForce2 = Value;
    m_InitiateUserEnteredForce2SendRequest = true;
}

/**************************************************************************//**
*
* \brief   - Send calibration abort request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendAbortCalibrationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateCalibrationAbortRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateCalibrationAbortRequest = false;
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
* \brief   - Send calibration reset request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendResetCalibrationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateCalibrationResetRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateCalibrationResetRequest = false;
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
* \brief   - Send quick calibration reset request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendStartQuickCalibrationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateQuickCalibrationRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateQuickCalibrationRequest = false;
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
* \brief   - Send start pressure calibration request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendStartPressureCalibrationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiatePressureCalibrationRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiatePressureCalibrationRequest = false;
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
* \brief   - Send start force calibration request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendStartForceCalibrationRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_InitiateForceCalibrationRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_InitiateForceCalibrationRequest = false;
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
* \brief   - Send user entered pressure 1 request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendUserEnteredPressure1(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(float))
    {
        if(m_InitiateUserEnteredPressure1SendRequest == true)
        {
		    float *Value = reinterpret_cast<float *>(destination->data);

            *Value = m_UserEnterdPressure1;
            destination->size = sizeof(float);
            destination->config = VALID_BIT;
            m_InitiateUserEnteredPressure1SendRequest = false;
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
* \brief   - Send user entered pressure 2 request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendUserEnteredPressure2(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(float))
    {
        if(m_InitiateUserEnteredPressure2SendRequest == true)
        {
           float *Value = reinterpret_cast<float *>(destination->data);

            *Value = m_UserEnterdPressure2;
            destination->size = sizeof(float);
            destination->config = VALID_BIT;
            m_InitiateUserEnteredPressure2SendRequest = false;
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
* \brief   - Send user entered pressure 3 request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendUserEnteredPressure3(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(float))
    {
        if(m_InitiateUserEnteredPressure3SendRequest == true)
        {
            float *Value = reinterpret_cast<float *>(destination->data);

            *Value = m_UserEnterdPressure3;
            destination->size = sizeof(float);
            destination->config = VALID_BIT;
            m_InitiateUserEnteredPressure3SendRequest = false;
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
* \brief   - Send user entered force 1 request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendUserEnteredForce1(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(float))
    {
        if(m_InitiateUserEnteredForce1SendRequest == true)
        {
            float *Value = reinterpret_cast<float *>(destination->data);

            *Value = m_UserEnterdForce1;
            destination->size = sizeof(float);
            destination->config = VALID_BIT;
            m_InitiateUserEnteredForce1SendRequest = false;
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
* \brief   - Send user entered force 2 request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void CalibrationAce::sendUserEnteredForce2(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(float))
    {
        if(m_InitiateUserEnteredForce2SendRequest == true)
        {
            float *Value = reinterpret_cast<float *>(destination->data);

            *Value = m_UserEnterdForce2;
            destination->size = sizeof(float);
            destination->config = VALID_BIT;
            m_InitiateUserEnteredForce2SendRequest = false;
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
* \brief   - Process the part contact found value coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void CalibrationAce::processPartContactFoundStatusValue(const MEMORY_BLOCK *const source)
{
    bool *Data = reinterpret_cast<bool *>(source->data);
    memcpy(&m_bIsPartContactFound,Data,sizeof(bool));
}

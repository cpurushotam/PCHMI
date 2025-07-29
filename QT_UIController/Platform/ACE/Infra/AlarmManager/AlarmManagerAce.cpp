/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE alarm manager related implementation

***************************************************************************/

#include "AlarmManagerAce.h"
#include "DataLogger.h"

size_t AlarmMgrACE::static_log_id=0;

/******************************************************************************
* \brief  -	AlarmMgrACE  Constructor
* 
* \param  - none
*
* \return - none
*
******************************************************************************/
AlarmMgrACE::AlarmMgrACE()
{	
	//enroll to use logger functionality
    static_log_id = Logger::enroll(this);
	
	m_ptrAlarmLogObj = std::make_unique<AlarmLog>();
	m_ptrActiveAlarmObj = std::make_unique<ActiveAlarm>();
	m_ptrAlarmConfigObj = std::make_unique<AlarmConfig>();
}

/******************************************************************************
* \brief  - Destructor
* 
* \param  - none
*
* \return - none
*
******************************************************************************/
AlarmMgrACE::~AlarmMgrACE()
{
	m_ptrAlarmLogObj    = nullptr;
	m_ptrActiveAlarmObj = nullptr;
	m_ptrAlarmConfigObj = nullptr;
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC to receive data for memory block ID MB_ID_ALARM_DATA
*           
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int AlarmMgrACE::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
	// check parameter
	if((destination != nullptr) && (destination->id == MB_ID_ALARM_DATA))
	{
		// perform operation based on sub id
		switch(destination->sub_id)
		{
			//Send request to ASC to get the historical alarm log data
			case READ_HISTORICAL_ALARM_LOG_DATA:
			{
				retVal = 0;
				m_ptrAlarmLogObj->SendHistoricalAlarmLogReadRequestToASC(destination);
				break;
			}
			break;

			//Send request to ASC to get the active alarm data
			case READ_ACTIVE_ALARM_DATA:
			{
				retVal = 0;
				m_ptrActiveAlarmObj->SendActiveAlarmReadRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to reset the active alarm data
			case RESET_ACTIVE_ALARM:
			{
				retVal = 0;
				m_ptrActiveAlarmObj->SendResetActiveAlarmRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to reset all the active alarm data
			case RESET_ALL_ACTIVE_ALARMS:
			{
				retVal = 0;
				m_ptrActiveAlarmObj->SendResetAllActiveAlarmsRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to get the alarm configuration data
			case ALARM_CONFIG_DATA:
			{
				retVal = 0;
				m_ptrAlarmConfigObj->SendAlarmConfigReadRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to save the alarm configuration data
			case ALARM_CONFIG_SAVE:
			{
				retVal = 0;
				m_ptrAlarmConfigObj->SendAlarmConfigSaveRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to reset the alarm configuration data to default
			case ALARM_CONFIG_RESET_TO_DEFAULT:
			{
				retVal = 0;
				m_ptrAlarmConfigObj->SendAlarmConfigResetToDefaultRequestToASC(destination);
				break;
			}
			
			//Send request to ASC to get the estop status data
			case ESTOP_ACTIVE_INDICATION:
			{
				retVal = 0;
				m_ptrActiveAlarmObj->SendEstopStatusReadRequestToASC(destination);
				break;				
			}
			
			//Send request to ASC to reset the estop status data
			case ESTOP_RESET_REQUEST:
			{
				retVal = 0;
				m_ptrActiveAlarmObj->SendEstopResetRequestToASC(destination);
				break;				
			}
			
			case ADD_ALARM_NOTES:
			{
				retVal = 0;
				m_ptrAlarmLogObj->SendAddAlarmNotesRequestToASC(destination);
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
				snprintf(msg,buff_size_config,"AlarmMgr GetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
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
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"AlarmMgr GetData invalid case");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_ALARM_DATA            
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int AlarmMgrACE::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	//check parameter
	if( (source != nullptr) && (source->id == MB_ID_ALARM_DATA) )
	{
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
				//Process response coming from ASC for last alarm log data
				case READ_LAST_ALARM_LOG_DATA:
				{
					retVal = 0;
					m_ptrAlarmLogObj->ProcessLastAlarmLogDataFromASC(source);
					break;
				}
				
				//Process response coming from ASC for historical alarm log data.
				case READ_HISTORICAL_ALARM_LOG_DATA:
				{
					retVal = 0;
					m_ptrAlarmLogObj->ProcessHistoricalAlarmLogDataFromASC(source);
					break;
				}
				
				//Process response coming from ASC for active alarm data.
				case READ_ACTIVE_ALARM_DATA:
				{
					retVal = 0;
					m_ptrActiveAlarmObj->ProcessActiveAlarmDataFromASC(source);
					break;
				}
				
				//Process response coming from ASC for reset one or all active alarm data.
				case RESET_ACTIVE_ALARM:
                case RESET_ALL_ACTIVE_ALARMS:
				{
					retVal = 0;
					m_ptrActiveAlarmObj->ProcessResetActiveAlarmDataFromASC(source);
					break;
				}
				
                case ALARM_CONFIG_DATA:
                {
                	retVal = 0;
                	m_ptrAlarmConfigObj->ProcessAlarmConfigDataFromASC(source);
                	break;
                }
                
                case ALARM_CONFIG_UPDATE_RESULT:
                {
                	retVal = 0;
                	m_ptrAlarmConfigObj->ProcessAlarmConfigUpdateStatusFromASC(source);
                	break;
                }
                
                case ADD_ALARM_NOTES:
                {
                	retVal = 0;
                	m_ptrAlarmLogObj->ProcessAlarmNotesUpdateStatusFromASC(source);
                	break;
                }

                //Process response coming from ASC for estop status data.
    			case ESTOP_ACTIVE_INDICATION:
    			{
    				retVal = 0;
    				m_ptrActiveAlarmObj->ProcessEstopStatusDataFromASC(source);
    				break;
    			}
    			
    			//Process response coming from ASC for estop reset response data.
    			case ESTOP_RESET_RESPONSE:
    			{
    				retVal = 0;
    				m_ptrActiveAlarmObj->ProcessEstopResetRespFromASC(source);
    				break;
                }
                //Process re-sending request to ASC on Datetime format change.
                case SYNCH_ALARMSLOG_ON_DATETIME_FORMAT_CHANGE:
                {
                    retVal = 0;
                    m_ptrAlarmLogObj->ProcessHistoricalAlarmLogDataFromASConDatetimeFormatChg();
                    break;
                }
				 //Process response from ASC on horn clamp on alarm status change.
                case HORN_CLAMP_ON_ALARM_STATUS:
                {
                    retVal = 0;
                    m_ptrActiveAlarmObj->ProcessHornClampOnAlarmStatusFromASC(source);
                    break;
                }
    			
                default:
				{
					char  msg[buff_size_config] = {0};
                    snprintf(msg,buff_size_config,"AlarmMgr SetData default case, sub_id: %d", source->sub_id);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					//Error ! default retVal (failure) will be returned
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
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"AlarmMgr SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - Set the AlarmConfiguration on HMI.
*
* \param   - None
*
* \return  - AlarmConfiguration structure.
*
******************************************************************************/
AlarmConfiguration AlarmMgrACE::GetAlarmConfiguration()
{
    return m_ptrAlarmConfigObj->GetAlarmConfiguration();
}
/**************************************************************************//**
*
* \brief   - Save the AlarmConfiguration from HMI on Save request.
*
* \param   - AlarmConfiguration structure.
*
* \return  - None
*
******************************************************************************/
void  AlarmMgrACE::saveAlarmConfigValues(AlarmConfiguration alarmConfiguration)
{
    m_ptrAlarmConfigObj->saveAlarmConfigValues( alarmConfiguration);
}

/**************************************************************************//**
*
* \brief   - Set the ResetToDefault Alarm Request from HMI.
*
* \param   - bool value.
*
* \return  - None
*
******************************************************************************/
void  AlarmMgrACE ::setResetToDefaultAlarmRequest(bool Value)
{
    m_ptrAlarmConfigObj->setResetToDefaultAlarmRequest(Value);
}
/**************************************************************************//**
*
* \brief   - Set the AlarmConfig read Request from HMI.
*
* \param   - bool value.
*
* \return  - None
*
******************************************************************************/
void  AlarmMgrACE ::ResetAlarmConfigurationUpdatedFlag ()
{
    m_ptrAlarmConfigObj->ResetAlarmConfigurationUpdatedFlag ();
}
/**************************************************************************//**
*
* \brief   - Returns flag m_IsLastAlarmConfigurationUpdated when the data from ASC is updated.
*
* \param   - None.
*
* \return  - bool
*
******************************************************************************/
bool  AlarmMgrACE ::IsAlarmConfigurationUpdated()
{
    return m_ptrAlarmConfigObj->IsAlarmConfigurationUpdated();
}

/**************************************************************************//**
*
* \brief   - Returns historical alarm log data.
*
* \param   - None.
*
* \return  - Historical alarm log data.
*
******************************************************************************/
std::deque<AlarmLogEntry> AlarmMgrACE::GetHistoricalAlarmLogData()
{
    return m_ptrAlarmLogObj->GetHistoricalAlarmLogData();
}

/**************************************************************************//**
*
* \brief   - Returns flag IsAlarmLogUpdated when the data from ASC is updated.
*
* \param   - None.
*
* \return  - bool
*
******************************************************************************/
bool AlarmMgrACE::IsAlarmLogUpdated()
{
    return m_ptrAlarmLogObj->IsAlarmLogUpdated();
}

/**************************************************************************//**
*
* \brief   - Updates flag IsAlarmLognUpdated when the data from ASC is updated.
*
* \param   - None.
*
* \return  - bool
*
******************************************************************************/
void AlarmMgrACE::UpdateAlarmLogUpdatedFlag(bool Value)
{
    return m_ptrAlarmLogObj->UpdateAlarmLogUpdatedFlag(Value);
}

/**************************************************************************//**
*
* \brief   - Returns active alarm log data.
*
* \param   - None.
*
* \return  - Active alarm log data.
*
******************************************************************************/
std::deque<ActiveAlarmEntry> AlarmMgrACE::GetActiveAlarmLogData()
{
    return m_ptrActiveAlarmObj->GetActiveAlarmLogData();
}

/**************************************************************************//**
*
* \brief   - Returns flag IsActiveAlarmLogUpdated when the data from ASC is updated.
*
* \param   - None.
*
* \return  - bool
*
******************************************************************************/
bool AlarmMgrACE::IsActiveAlarmLogUpdated()
{
    return m_ptrActiveAlarmObj->IsActiveAlarmLogUpdated();
}

/**************************************************************************//**
*
* \brief   - Updates flag IsActiveAlarmLognUpdated when the data from ASC is updated.
*
* \param   - None.
*
* \return  - bool
*
******************************************************************************/
void AlarmMgrACE::UpdateActiveAlarmLogUpdatedFlag(bool Value)
{
    m_ptrActiveAlarmObj->UpdateActiveAlarmLogUpdatedFlag(Value);
}

/**************************************************************************//**
*
* \brief   - Reset the alarm based on id provided.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void AlarmMgrACE::SetAlarmIDtoBeReset(ALARM_IDS Id)
{
    m_ptrActiveAlarmObj->SetAlarmIDtoBeReset(Id);
}

/**************************************************************************//**
*
* \brief   - Reset all the alarms.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmMgrACE::SetResetAllActiveAlarm()
{
    m_ptrActiveAlarmObj->SetResetAllActiveAlarm();
}

/**************************************************************************//**
*
* \brief   - Get the Estop status.
*
* \param   - None.
*
* \return  - Estop status.
*
******************************************************************************/
uint8_t AlarmMgrACE::GetEstopStatus()
{
    return m_ptrActiveAlarmObj->GetEstopStatus();
}

/**************************************************************************//**
*
* \brief   - Reset the Estop request.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void AlarmMgrACE::SetEstopResetRequest()
{
    m_ptrActiveAlarmObj->SetEstopResetRequest();
}

/**************************************************************************//**
*
* \brief   - Get the Estop reset status.
*
* \param   - None.
*
* \return  - Estop reset status.
*
******************************************************************************/
uint8_t AlarmMgrACE::GetEstopResetResponse()
{
    return m_ptrActiveAlarmObj->GetEstopResetResponse();
}

/**************************************************************************//**
*
* \brief   - Get the Horn Clamp on Alarm status.
*
* \param   - None.
*
* \return  - Horn Clamp on Alarm status.
*
******************************************************************************/
uint8_t AlarmMgrACE::GetHornClampOnAlrmStatus()
{
    return m_ptrActiveAlarmObj->GetHornClampOnAlrmStatus();
}
/**************************************************************************//**
*
* \brief   - Reset all the alarms.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void AlarmMgrACE::SetAddAlarmNotesFlag(int index, std::string Notes)
{
    m_ptrAlarmLogObj->SetAddAlarmNotesFlag(index, Notes);
}



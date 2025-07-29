/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Service Reminder Management related implementation
 
***************************************************************************/
#include <algorithm>
#include <cctype>
#include "ServiceReminderManagement.h"
#include "DataLogger.h"

/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

ServiceManagement::ServiceManagement()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
  
    m_SendReminderListReadRequest = true; 
  
    m_SendAddReminderRequest = false;
    m_SendModifyReminderRequest = false;
    m_SendDeleteReminderRequest = false; 
    m_IsReminderListUpdated = false;

    m_AddReminderResponse = ADD_REMINDER_ERROR_UNKNOWN;
    m_ModifyReminderResponse = MODIFY_REMINDER_ERROR_UNKNOWN;
    m_deleteReminderResponse = MODIFY_REMINDER_ERROR_UNKNOWN;
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
ServiceManagement::~ServiceManagement()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate add reminder request to ASC
*
* \param   - ReminderData - Reminder Data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiateAddReminderRequest(const addReminderStruct& ReminderData)
{
    m_AddOrModifyReminderData = ReminderData;
    m_SendAddReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate modify Reminder request to ASC
*
* \param   - ReminderData - Reminder Data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiateModifyReminderRequest(const addReminderStruct& ReminderData)
{
    m_AddOrModifyReminderData = ReminderData;
    m_SendModifyReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate delete Reminder request to ASC
*
* \param   - ReminderName - ReminderName to be deleted.
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiateDeleteReminderRequest(const std::string& ServiceName)
{
    strncpy(m_DeleteServiceName, ServiceName.c_str(), sizeof(m_DeleteServiceName));
    m_SendDeleteReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate pause/reset reminder request to ASC
*
* \param   - ReminderData - Reminder Data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiatePauseResumeReminderRequest(const reminderPauseResumeStruct& ReminderData)
{
	m_reminderPauseResumeData = ReminderData;
	m_SendPauseResumeReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate reset reminder request to ASC
*
* \param   - ReminderData - Reminder Data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiateResetReminderRequest(const reminderResetStruct& ReminderData)
{
	m_reminderResetData = ReminderData;
	m_SendResetReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate snooze reminder request to ASC
*
* \param   - ReminderData - Reminder Data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::InitiateSnoozeReminderRequest(const reminderSnoozeStruct& ReminderData)
{
	m_reminderSnoozeData = ReminderData;
	m_SendSnoozeReminderRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for service reminder Management
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int ServiceManagement::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	if((destination != nullptr) && (destination->id == MB_ID_SERVICE_REMINDER_DATA))
	{
		switch(destination->sub_id)
        {
            case MB_REMINDER_LIST_REQUEST:
            {
               retVal = 0;
               sendReminderListReadRequest(destination);
               break;
            }
	
            case MB_ADD_REMINDER_REQUEST:
            {
                retVal = 0;
                sendAddReminderRequest(destination);
                break;
            }

            case MB_MODIFY_REMINDER_REQUEST:
            {
                retVal = 0;
                sendModifyReminderRequest(destination);
                break;
            }

            case MB_DELETE_REMINDER_REQUEST:
            {
                retVal = 0;
                sendDeleteReminderRequest(destination);
                break;
            }

            case MB_PAUSE_RESUME_REMINDER_REQUEST:
            {
            	retVal = 0;
            	sendPauseResumeReminderRequest(destination);
            	break;
            }

            case MB_RESET_REMINDER_REQUEST:
            {
            	retVal = 0;
            	sendResetReminderRequest(destination);
            	break;
            }

            case MB_SNOOZE_REMINDER_REQUEST:
            {
            	retVal = 0;
            	sendSnoozeReminderRequest(destination);
            	break;
            }

			default:
			{
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config,"ServiceManagement GetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				break;
			}
		}
	}
	else
	{
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"ServiceManagement GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming to HMI from ASC for service reminder Management
*
* \param   - source - Memory block containing data coming to HMI
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ServiceManagement::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_SERVICE_REMINDER_DATA) )
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
                switch(source->sub_id)
                {
                    case MB_REMINDER_LIST_REQUEST:
                    {
                        retVal = 0;
                        processReminderListResponse(source);
                        break;
                    }
    
                    case MB_ADD_REMINDER_REQUEST:
                    {
                        retVal = 0;
                        processAddReminderResponse(source);
                        break;
                    }

                    case MB_MODIFY_REMINDER_REQUEST:
                    {
                        retVal = 0;
                        processModifyReminderResponse(source);
                        break;
                    }

                    case MB_DELETE_REMINDER_REQUEST:
                    {
                        retVal = 0;
                        processDeleteReminderResponse(source);
                        break;
                    }

                    case MB_PAUSE_RESUME_REMINDER_REQUEST:
                    {
                    	retVal = 0;
                    	processPauseResumeReminderResponse(source);
                    	break;
                    }

                    case MB_RESET_REMINDER_REQUEST:
                    {
                    	retVal = 0;
                    	processResetReminderResponse(source);
                    	break;
                    }

                    case MB_SNOOZE_REMINDER_REQUEST:
                    {
                    	retVal = 0;
                    	processSnoozeReminderResponse(source);
                    	break;
                    }
                    case SYNCH_SERVICE_REMIDER_DATA:
                    {
                        retVal = 0;
                        processSyncReminderListonDateTimeFormatChg();
                        break;
                    }
                    default:
                    {
                        char  msg[buff_size_config] = {0};
                        snprintf(msg,buff_size_config,"ServiceManagement SetData default case");
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
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
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"ServiceManagement SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the read reminder list request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendReminderListReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendReminderListReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendReminderListReadRequest = false;
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
* \brief   - Send the add reminder request to ASC
*
* \param   - destination - memory block to hold the add reminder request data
*            
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendAddReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the add reminder request data.
    if(destination->size >= sizeof(addReminderStruct))
    {
        if(m_SendAddReminderRequest == true)
        {
            addReminderStruct *Data = reinterpret_cast<addReminderStruct *>(destination->data);           
            strncpy(Data->serviceName, m_AddOrModifyReminderData.serviceName, sizeof(m_AddOrModifyReminderData.serviceName));
            
            Data->method = m_AddOrModifyReminderData.method;
            Data->counterLimit = m_AddOrModifyReminderData.counterLimit;
            Data->dateTimeLimit = m_AddOrModifyReminderData.dateTimeLimit;
            Data->status = m_AddOrModifyReminderData.status;
            Data->snooze = m_AddOrModifyReminderData.snooze;

            destination->size = sizeof(addReminderStruct);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendAddReminderRequest = false;
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
* \brief   - Send the modify reminder request to ASC
*
* \param   - destination - memory block to hold the modify reminder request data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendModifyReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the modify reminder request data.
    if( destination->size >= sizeof(addReminderStruct))
    {
        if(m_SendModifyReminderRequest == true)
        {
            addReminderStruct *Data = reinterpret_cast<addReminderStruct *>(destination->data);

            strncpy(Data->serviceName, m_AddOrModifyReminderData.serviceName, sizeof(m_AddOrModifyReminderData.serviceName));
            Data->method = m_AddOrModifyReminderData.method;
            Data->counterLimit = m_AddOrModifyReminderData.counterLimit;
            Data->dateTimeLimit = m_AddOrModifyReminderData.dateTimeLimit;
            Data->status = m_AddOrModifyReminderData.status;
            Data->snooze = m_AddOrModifyReminderData.snooze;

            destination->size = sizeof(addReminderStruct);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendModifyReminderRequest = false;
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
* \brief   - Send the delete Reminder request to ASC
*
* \param   - destination - memory block to hold the delete Reminder request data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendDeleteReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the delete Reminder request data containing Remindername to be deleted.
    if( destination->size >= sizeof(m_DeleteServiceName))
    {
        if(m_SendDeleteReminderRequest == true)
        {
            strncpy(reinterpret_cast<char *>(destination->data), m_DeleteServiceName, sizeof(m_DeleteServiceName));

            destination->size = sizeof(m_DeleteServiceName);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendDeleteReminderRequest = false;
            //Reset the variable once the request is sent to ASC.
            memset(m_DeleteServiceName, 0, sizeof(m_DeleteServiceName));
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
* \brief   - Send the Pause/Resume Reminder request to ASC
*
* \param   - destination - memory block to hold the Pause/Resume Reminder request data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendPauseResumeReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the pause/resume Reminder request data containing Remindername to be pause/resume.
    if(destination->size >= sizeof(reminderPauseResumeStruct))
    {
        if(m_SendPauseResumeReminderRequest == true)
        {
            reminderPauseResumeStruct *Data = reinterpret_cast<reminderPauseResumeStruct *>(destination->data);

            strncpy(Data->serviceName, m_reminderPauseResumeData.serviceName, sizeof(m_reminderPauseResumeData.serviceName));
            Data->status = m_reminderPauseResumeData.status;

            destination->size = sizeof(reminderPauseResumeStruct);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendPauseResumeReminderRequest = false;
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
* \brief   - Send the reset Reminder request to ASC
*
* \param   - destination - memory block to hold the reset Reminder request data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendResetReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the reset Reminder request data containing Remindername to be reset.
    if(destination->size >= sizeof(reminderResetStruct))
    {
        if(m_SendResetReminderRequest == true)
        {
            reminderResetStruct *Data = reinterpret_cast<reminderResetStruct *>(destination->data);

            strncpy(Data->serviceName, m_reminderResetData.serviceName, sizeof(m_reminderResetData.serviceName));

            destination->size = sizeof(reminderResetStruct);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendResetReminderRequest = false;
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
* \brief   - Send the reset Reminder request to ASC
*
* \param   - destination - memory block to hold the snooze Reminder request data
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::sendSnoozeReminderRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the snooze Reminder request data containing Remindername to be snooze.
    if(destination->size >= sizeof(reminderSnoozeStruct))
    {
        if(m_SendSnoozeReminderRequest == true)
        {
        	reminderSnoozeStruct *Data = reinterpret_cast<reminderSnoozeStruct *>(destination->data);

            strncpy(Data->serviceName, m_reminderSnoozeData.serviceName, sizeof(m_reminderSnoozeData.serviceName));
            Data->snooze = m_reminderSnoozeData.snooze;

            destination->size = sizeof(reminderSnoozeStruct);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSnoozeReminderRequest = false;
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
* \brief   - Process the reminder list data coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processReminderListResponse(const MEMORY_BLOCK *const source)
{
    int *NumberOfReminders = reinterpret_cast<int *>(source->data);
    reminderListStruct *Data = reinterpret_cast<reminderListStruct *>(source->data + sizeof(int));
    m_ReminderDetails.clear();

    for(int ReminderNumber = 0; ReminderNumber < *NumberOfReminders; ReminderNumber++)
    {
    	reminderListStruct ReminderInfo;
        strncpy(ReminderInfo.serviceName, Data->serviceName, sizeof(ReminderInfo.serviceName));
        ReminderInfo.method = Data->method;
        ReminderInfo.counter = Data->counter;
        ReminderInfo.counterLimit = Data->counterLimit;
        ReminderInfo.dateTimeLimit = Data->dateTimeLimit;
        ReminderInfo.status = Data->status;
        ReminderInfo.snooze = Data->snooze;
        m_ReminderDetails.insert(std::make_pair(ReminderNumber, ReminderInfo));
        Data++;
    }
    m_IsReminderListUpdated = true;
    m_IsReminderListUpdatedForGlobalReminderSettingScreen = true;
}


/**************************************************************************//**
*
* \brief   - Process the add reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processAddReminderResponse(const MEMORY_BLOCK *const source)
{
    m_AddReminderResponse = *reinterpret_cast<ADD_REMINDER_ERROR_CODES *>(source->data);
    m_AddReminderRespRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the modify Reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processModifyReminderResponse(const MEMORY_BLOCK *const source)
{
    m_ModifyReminderResponse = *reinterpret_cast<MODIFY_REMINDER_ERROR_CODES *>(source->data);
    m_ModifyReminderRespRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the delete Reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processDeleteReminderResponse(const MEMORY_BLOCK *const source)
{
    m_deleteReminderResponse = *reinterpret_cast<MODIFY_REMINDER_ERROR_CODES *>(source->data);
    m_DeleteReminderRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the Pause/Resume Reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processPauseResumeReminderResponse(const MEMORY_BLOCK *const source)
{
	m_pauseResumeReminderResponse = *reinterpret_cast<MODIFY_REMINDER_ERROR_CODES *>(source->data);
	m_PauseResumeReminderRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the reset Reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processResetReminderResponse(const MEMORY_BLOCK *const source)
{
	m_resetReminderResponse = *reinterpret_cast<MODIFY_REMINDER_ERROR_CODES *>(source->data);
	m_ResetResumeReminderRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the snooze Reminder response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void ServiceManagement::processSnoozeReminderResponse(const MEMORY_BLOCK *const source)
{
	m_snoozeReminderResponse = *reinterpret_cast<MODIFY_REMINDER_ERROR_CODES *>(source->data);
	m_SnoozeResumeReminderRecieved = true;
}


/**************************************************************************//**
*
* \brief   - process the ServiceReminder log read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::processSyncReminderListonDateTimeFormatChg()
{
    m_ReminderDetails.clear();
    m_SendReminderListReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - Function returns the modify Reminder error code to HMI.
*
* \param   - None
*
* \return  - m_ModifyReminderResponse.
*
******************************************************************************/
MODIFY_REMINDER_ERROR_CODES ServiceManagement::GetModifyReminderResponse()
{
    return m_ModifyReminderResponse;
}
/**************************************************************************//**
*
* \brief   - Function returns the delete Reminder error code to HMI.
*
* \param   - None
*
* \return  - m_deleteReminderResponse.
*
******************************************************************************/
MODIFY_REMINDER_ERROR_CODES ServiceManagement::GetDeleteReminderResponse()
{
    return m_deleteReminderResponse;
}
/**************************************************************************//**
*
* \brief   - Function returns the Add Reminder error code to HMI.
*
* \param   - None
*
* \return  - m_AddReminderResponse.
*
******************************************************************************/
ADD_REMINDER_ERROR_CODES ServiceManagement::GetAddReminderResponse()
{
    return m_AddReminderResponse;
}

/**************************************************************************//**
*
* \brief   - Function to notify whether service reminder data updated or not?
*
* \param   - none.
*
* \return  - m_IsReminderListUpdated.
*
******************************************************************************/
bool ServiceManagement::GetIsReminderListUpdated()
{
    return m_IsReminderListUpdated;
}

void ServiceManagement::SetIsReminderListUpdated(bool Value)
{
    m_IsReminderListUpdated = Value;
}

/**************************************************************************//**
*
* \brief   - Function ReminderDetails map to HMI upon update.
*
* \param   - none.
*
* \return  - m_ReminderDetails.
*
******************************************************************************/
std::map<int,reminderListStruct> ServiceManagement::GetReminderList()
{
    return m_ReminderDetails;
}

/**************************************************************************//**
*
* \brief   - Print the Reminder List from cached data
* \param   - None
*
* \return  - none
*
******************************************************************************/
void ServiceManagement::printReminderList()
{
    if(m_ReminderDetails.size() == 0)
    {
        std::cout << "**********HMI side Reminder List is Empty " << std::endl;
    }
    else
    {
        for (auto it=m_ReminderDetails.begin(); it!=m_ReminderDetails.end(); ++it)
        {
            std::cout << "HMI side Reminder List Data: " << std::endl;
            std::cout << "**********Reminder Sr. Index in map key:" << it->first << std::endl;
            std::cout << "**********Service Name:" << it->second.serviceName << std::endl;
            std::cout << "**********Method (0: Counter, 1: Time):" << it->second.method << std::endl;
            std::cout << "**********Counter: " << it->second.counter << std::endl;
            std::cout << "**********CounterLimit: " << it->second.counterLimit << std::endl;
            std::cout << "**********DateTimeLimit: " << it->second.dateTimeLimit << std::endl;
            std::cout << "**********Status (0:Enable, 1: Disable): " << it->second.status << std::endl;
            std::cout << "**********Snooze (0:None, 1:12_Hrs, 2:24_Hrs, 3:72_Hrs, 4:144_Hrs): " << it->second.snooze << std::endl;
        }
    }
}

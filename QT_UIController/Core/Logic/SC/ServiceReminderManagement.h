/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Service Reminder Management related implementation
 
***************************************************************************/

#ifndef SERVICE_REMINDER_MANAGEMENT_H_
#define SERVICE_REMINDER_MANAGEMENT_H_

#include <map>
#include "DataInterface.h"
#include "ServiceReminderStructure.h"


class ServiceManagement : public DataInterface
{ 
public:
	
	ServiceManagement();
	virtual ~ServiceManagement();
    
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void InitiateAddReminderRequest(const addReminderStruct& ReminderData);
    void InitiateModifyReminderRequest(const addReminderStruct& ReminderData);
    void InitiateDeleteReminderRequest(const std::string& ReminderName);
    void InitiatePauseResumeReminderRequest(const reminderPauseResumeStruct& ReminderData);
    void InitiateResetReminderRequest(const reminderResetStruct& ReminderData);
    void InitiateSnoozeReminderRequest(const reminderSnoozeStruct& ReminderData);

    MODIFY_REMINDER_ERROR_CODES GetDeleteReminderResponse();
    ADD_REMINDER_ERROR_CODES GetAddReminderResponse();
    MODIFY_REMINDER_ERROR_CODES GetModifyReminderResponse();

    bool GetIsReminderListUpdated();
    void SetIsReminderListUpdated(bool Value);
    std::map<int,reminderListStruct> GetReminderList();

private:
    size_t m_LogID;

    //Holds the Reminder List data cached on HMI side.
    std::map<int,reminderListStruct> m_ReminderDetails;

    //This flag is set to true whenever the Reminder list data gets updated in cached data m_ReminderDetails
    bool m_IsReminderListUpdated;
    //Reminder list screen used to set m_IsReminderListUpdated flag whenever the Reminder list data gets updated and
    //Global Reminder setting screen used to set m_IsReminderListUpdatedForGlobalReminderSettingScreen flag whenever the reminder list data gets updated
    bool m_IsReminderListUpdatedForGlobalReminderSettingScreen;

    //Read Reminder List request is sent to ASC when this flag is true
    bool m_SendReminderListReadRequest;
    //Add Reminder request is sent to ASC when this flag is true
    bool m_SendAddReminderRequest;
    //Modify Reminder request is sent to ASC when this flag is true
    bool m_SendModifyReminderRequest;
    //Delete Reminder request is sent to ASC when this flag is true
    bool m_SendDeleteReminderRequest;
    //Pause Resume Reminder request is sent to ASC when this flag is true
    bool m_SendPauseResumeReminderRequest;
    //Reset Reminder request is sent to ASC when this flag is true
    bool m_SendResetReminderRequest;
    //Snooze Reminder request is sent to ASC when this flag is true
	bool m_SendSnoozeReminderRequest;
 
    //Flag to update HMI upon delete Reminder error code received from SC.
    bool m_DeleteReminderRecieved;
    //Flag to update HMI upon Add Reminder error code received from SC.
    bool m_AddReminderRespRecieved;
    //Flag to update HMI upon modify Reminder error code received from SC.
    bool m_ModifyReminderRespRecieved;
    //Flag to update HMI upon pause/resume Reminder error code received from SC.
    bool m_PauseResumeReminderRecieved;
    //Flag to update HMI upon reset Reminder error code received from SC.
    bool m_ResetResumeReminderRecieved;
    //Flag to update HMI upon snooze Reminder error code received from SC.
    bool m_SnoozeResumeReminderRecieved;
   
    //Holds the Add/Modify Reminder data to be sent to ASC during add Reminder or modify Reminder request
    addReminderStruct m_AddOrModifyReminderData;
    //Holds the Pause/Resume Reminder data to be sent to ASC during pause/resume Reminder request
    reminderPauseResumeStruct m_reminderPauseResumeData;
    //Holds the Reset Reminder data to be sent to ASC during reset Reminder request
    reminderResetStruct m_reminderResetData;
    //Holds the Snooze Reminder data to be sent to ASC during snooze Reminder request
    reminderSnoozeStruct m_reminderSnoozeData;

    //Holds the Reminder name to be sent to ASC during delete Reminder request
    char m_DeleteServiceName[SERVICE_NAME_SIZE] = {0};

    //Holds the add Reminder response code coming from ASC
    ADD_REMINDER_ERROR_CODES m_AddReminderResponse;
    //Holds the modify Reminder response code coming from ASC
    MODIFY_REMINDER_ERROR_CODES m_ModifyReminderResponse;
    //Holds the delete Reminder response code coming from ASC
    MODIFY_REMINDER_ERROR_CODES m_deleteReminderResponse;
    //Holds the pause/resume Reminder response code coming from ASC
    MODIFY_REMINDER_ERROR_CODES m_pauseResumeReminderResponse;
    //Holds the reset Reminder response code coming from ASC
    MODIFY_REMINDER_ERROR_CODES m_resetReminderResponse;
    //Holds the snooze Reminder response code coming from ASC
    MODIFY_REMINDER_ERROR_CODES m_snoozeReminderResponse;
  
    void sendAddReminderRequest(MEMORY_BLOCK * const destination);
    void sendModifyReminderRequest(MEMORY_BLOCK * const destination);
    void sendDeleteReminderRequest(MEMORY_BLOCK * const destination);
    void sendReminderListReadRequest(MEMORY_BLOCK * const destination);
    void sendPauseResumeReminderRequest(MEMORY_BLOCK * const destination);
    void sendResetReminderRequest(MEMORY_BLOCK * const destination);
    void sendSnoozeReminderRequest(MEMORY_BLOCK * const destination);

    void processReminderListResponse(const MEMORY_BLOCK *const source);
    void processAddReminderResponse(const MEMORY_BLOCK *const source);
    void processModifyReminderResponse(const MEMORY_BLOCK *const source);
    void processDeleteReminderResponse(const MEMORY_BLOCK *const source);
    void processPauseResumeReminderResponse(const MEMORY_BLOCK *const source);
    void processResetReminderResponse(const MEMORY_BLOCK *const source);
    void processSnoozeReminderResponse(const MEMORY_BLOCK *const source);
    void processSyncReminderListonDateTimeFormatChg();

    void printReminderList();
};

#endif /* SERVICE_REMINDER_MANAGEMENT_H_ */

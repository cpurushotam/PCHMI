/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Global User Setting related implementation
 
***************************************************************************/

#include <cstring>
#include "GlobalUserSetting.h"
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

GlobalUserSetting::GlobalUserSetting()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_SendGlobalUserSettigsReadRequest = true;
    m_SendGlobalUserSettigsUdateRequest = false;
    m_SendGlobalUserSettigsResetRequest = false;
    m_isGlobalUserSettigsDataUpdated = false;
    m_isGlobalUserSettigsDataReadOnPowerUp = false;
    m_GlobalUserDataUpdateResult = UPDATE_GLOBAL_USER_SETTING_ERROR_UNKNOWN;
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
GlobalUserSetting::~GlobalUserSetting()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Global User Settings Update Request
*
* \param   - GlobalUserSettingData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::InitiateGlobalUserSettingsUpdateRequest(GlobalUserSettingStruct GlobalUserSettingData)
{
    m_GlobalUserData = GlobalUserSettingData;
    m_SendGlobalUserSettigsUdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Global User Settings reset Request
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::InitiateGlobalUserSettingsResetRequest()
{
    m_SendGlobalUserSettigsResetRequest = true;
}


/**************************************************************************//**
*
* \brief   - send the request to ASC server for global user setting memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int GlobalUserSetting::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_GLOBAL_USER_SETTINGS_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_GLOBAL_USER_SETTINGS_REQUEST:
        {
            retVal = 0;
            sendGlobalUserSettingsReadRequest(destination);
            break;
        }

        case MB_UPDATE_GLOBAL_USER_SETTINGS_REQUEST:
        {
            retVal = 0;
            sendGlobalUserSettingsUpdateRequest(destination);
            break;
        }

        case MB_RESET_GLOBAL_USER_SETTINGS_REQUEST:
        {
            retVal = 0;
            sendGlobalUserSettingsResetRequest(destination);
            break;
        }

        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"GlobalUserSetting GetData default case");
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
        snprintf(msg,buff_size_config,"GlobalUserSetting GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for global user setting memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int GlobalUserSetting::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_GLOBAL_USER_SETTINGS_DATA) )
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case MB_READ_GLOBAL_USER_SETTINGS_REQUEST:
            {
                retVal = 0;
                processGlobalUserSettingsReadResponse(source);
                break;
            }
            case MB_UPDATE_GLOBAL_USER_SETTINGS_REQUEST:
            case MB_RESET_GLOBAL_USER_SETTINGS_REQUEST:
            {
                retVal = 0;
                processGlobalUserSettingsUpdateResponse(source);
                break;
            }

            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"GlobalUserSetting SetData default case");
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
        snprintf(msg,buff_size_config,"GlobalUserSetting SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the global user setting read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::sendGlobalUserSettingsReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendGlobalUserSettigsReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendGlobalUserSettigsReadRequest = false;
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
* \brief   - Send the global user setting update request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::sendGlobalUserSettingsUpdateRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_GlobalUserData))
    {
        if(m_SendGlobalUserSettigsUdateRequest == true)
        {
            GlobalUserSettingStruct *Data = reinterpret_cast<GlobalUserSettingStruct *>(destination->data);
            memcpy(Data,&m_GlobalUserData,sizeof(m_GlobalUserData));

            destination->size = sizeof(m_GlobalUserData);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendGlobalUserSettigsUdateRequest = false;
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
* \brief   - Send the global user setting reset to default request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::sendGlobalUserSettingsResetRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendGlobalUserSettigsResetRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendGlobalUserSettigsResetRequest = false;
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
* \brief   - Process the global user setting data coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::processGlobalUserSettingsReadResponse(const MEMORY_BLOCK *const source)
{
    GlobalUserSettingStruct *Data = reinterpret_cast<GlobalUserSettingStruct *>(source->data);
    memcpy(&m_GlobalUserData,Data,sizeof(GlobalUserSettingStruct));
    m_isGlobalUserSettigsDataReadOnPowerUp = true;
}

/**************************************************************************//**
*
* \brief   - Process the global user setting update response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::processGlobalUserSettingsUpdateResponse(const MEMORY_BLOCK *const source)
{
    int *Data = reinterpret_cast<int *>(source->data);
    memcpy(&m_GlobalUserDataUpdateResult,Data,sizeof(int));
    m_isGlobalUserSettigsDataUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show Global User Setting details        
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void GlobalUserSetting::ShowGlobalUserSetting()
{
	std::cout << "m_GlobalUserData.PasswordExpiryInDays: "  << m_GlobalUserData.PasswordExpiryInDays << std::endl;
	std::cout << "m_GlobalUserData.IdleTimeLogoffInMinute: "  << m_GlobalUserData.IdleTimeLogoffInMinute << std::endl;
	std::cout << "m_GlobalUserData.LockOutTimeInMinute: "  << m_GlobalUserData.LockOutTimeInMinute << std::endl;
    std::cout << "m_GlobalUserData.AutoLoginStatus: "  << m_GlobalUserData.AutoLoginStatus << std::endl;
    std::cout << "m_GlobalUserData.AutoLoginUserName: "  << m_GlobalUserData.AutoLoginUserName << std::endl;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting data updated details
*
* \param   - none
*
* \return  - bool - m_isGlobalUserSettigsDataUpdated -
*
******************************************************************************/
bool GlobalUserSetting::GetIsGlobalUserSettingDataUpdated()
{
    return m_isGlobalUserSettigsDataUpdated;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting data updated details
*
* \param   - none
*
* \return  - bool - m_isGlobalUserSettigsDataReadOnPowerUp 
*
******************************************************************************/
bool GlobalUserSetting::GetIsGlobalUserSettingDataRead()
{
    return m_isGlobalUserSettigsDataReadOnPowerUp;
}

/**************************************************************************//**
*
* \brief   - set Global User Setting data read
*
* \param   - none
*
* \return  - none 
*
******************************************************************************/
void GlobalUserSetting::SetGlobalUserSettingDataRead()
{
    m_isGlobalUserSettigsDataReadOnPowerUp = false;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting AutoLogin status
*
* \param   - none
*
* \return  - bool - AutoLoginStatus
*
******************************************************************************/
bool GlobalUserSetting::GetAutoLoginStatus()
{
    return m_GlobalUserData.AutoLoginStatus;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting Idle time Logout value
*
* \param   - none
*
* \return  - uint32_t - IdleTimeLogoffInMinute
*
******************************************************************************/
uint32_t GlobalUserSetting::GetIdleTimeLoggOffTime()
{
    return m_GlobalUserData.IdleTimeLogoffInMinute;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting AutoLogin User Name
*
* \param   - none
*
* \return  - bool - AutoLoginStatus
*
******************************************************************************/
std::string GlobalUserSetting::GetAutoLoginUserName()
{
    std::string AutoLoginUsername(m_GlobalUserData.AutoLoginUserName);
    return AutoLoginUsername;
}

/**************************************************************************//**
*
* \brief   - return the copy of global user setting structure data
*
* \param   - none

* \return  - copy of global user setting structure data
*
******************************************************************************/
GlobalUserSettingStruct GlobalUserSetting::GetGlobalUserSettingData()
{
    GlobalUserSettingStruct GlobalUserSettingData = m_GlobalUserData;
    //Reset the flag to false once the value is read
    m_isGlobalUserSettigsDataUpdated = false;

    return GlobalUserSettingData;
}

/**************************************************************************//**
*
* \brief   - return the copy of user data updated error code
*
* \param   - none

* \return  - copy of user data updated error code
*
******************************************************************************/
UPDATE_GLOBAL_USER_SETTING_ERROR_CODES GlobalUserSetting::GetGlobalUserSettigsDataUpdatedErrorCode()
{
    UPDATE_GLOBAL_USER_SETTING_ERROR_CODES GlobalUserDataUpdateResult = m_GlobalUserDataUpdateResult;
    return GlobalUserDataUpdateResult;
}

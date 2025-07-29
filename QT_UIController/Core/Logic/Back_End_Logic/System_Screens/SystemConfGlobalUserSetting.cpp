/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares SystemConfGlobalUserSetting class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "SystemConfGlobalUserSetting.h"

/**************************************************************************//**
*
* \brief  - Global User Setting Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SystemConfGlobalUserSetting::SystemConfGlobalUserSetting(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::GlobalUserSettingDataUpdated, this, &SystemConfGlobalUserSetting::OnGlobalUserSettingDataUpdated);
}

/**************************************************************************//**
*
* \brief  - Return password expiration value
*
* \param  - None.
*
* \return - int m_PasswordExpirationValue.
*
******************************************************************************/
int SystemConfGlobalUserSetting::getPasswordExpiration() const
{
    return m_PasswordExpirationValue;
}

/**************************************************************************//**
*
* \brief  - Updates the password expiration value.
*
* \param  - int newPasswordExpirationValue - password expiration value to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updatePasswordExpiration(int newPasswordExpirationValue)
{
    if (m_PasswordExpirationValue != newPasswordExpirationValue)
    {
        m_PasswordExpirationValue = newPasswordExpirationValue;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Idle Time Logout value
*
* \param  - None.
*
* \return - int m_IdleTimeLogoutValue.
*
******************************************************************************/
int SystemConfGlobalUserSetting::getIdleTimeLogout() const
{
    return m_IdleTimeLogoutValue;
}

/**************************************************************************//**
*
* \brief  - Update Idle Time Logout value
*
* \param  - int newIdleTimeLogoutValue - idle time value to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updateIdleTimeLogout(int newIdleTimeLogoutValue)
{
    if (m_IdleTimeLogoutValue != newIdleTimeLogoutValue)
    {
        m_IdleTimeLogoutValue = newIdleTimeLogoutValue;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Lock Out Time value
*
* \param  - None.
*
* \return - int m_LockOutTimeValue.
*
******************************************************************************/
int SystemConfGlobalUserSetting::getLockOutTime() const
{
    return m_LockOutTimeValue;
}

/**************************************************************************//**
*
* \brief  - Update Lock Out Time value
*
* \param  - int newLockOutTimeValue - Lock Out Time to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updateLockOutTime(int newLockOutTimeValue)
{
    if (m_LockOutTimeValue != newLockOutTimeValue)
    {
        m_LockOutTimeValue = newLockOutTimeValue;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Lock Out Time value
*
* \param  - None.
*
* \return - int m_LockOutTimeValue.
*
******************************************************************************/
bool SystemConfGlobalUserSetting::getAutoLoginStatus() const
{
    return m_AutoLoginStatus;
}

/**************************************************************************//**
*
* \brief  - Update Lock Out Time value
*
* \param  - int newLockOutTimeValue - Lock Out Time to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updateAutoLoginStatus(bool autoLoginStaus)
{
    if (m_AutoLoginStatus != autoLoginStaus)
    {
        m_AutoLoginStatus = autoLoginStaus;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Lock Out Time value
*
* \param  - None.
*
* \return - int m_LockOutTimeValue.
*
******************************************************************************/
QString SystemConfGlobalUserSetting::getAutoLoginUser() const
{
    return m_AutoLoginUser;
}

/**************************************************************************//**
*
* \brief  - Update Lock Out Time value
*
* \param  - int newLockOutTimeValue - Lock Out Time to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updateAutoLoginUser(QString autoLoginUser)
{
    if (m_AutoLoginUser != autoLoginUser)
    {
        m_AutoLoginUser = autoLoginUser;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Authority chcek status
*
* \param  - None.
*
* \return - AUTHORITYCHECK AuthorityCheck.
*
******************************************************************************/
bool SystemConfGlobalUserSetting::getAuthorityCheck()
{
    return m_AuthorityCheck;
}

/**************************************************************************//**
*
* \brief  - Update Authority check
*
* \param  - int newLockOutTimeValue - Lock Out Time to be update
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::updateAuthorityCheck(bool AuthorityCheck)
{
    if (m_AuthorityCheck != AuthorityCheck)
    {
        m_AuthorityCheck = AuthorityCheck;
        emit globalUserSettingDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return data updated in db error code
*
* \param  - None.
*
* \return - UPDATE_GLOBAL_USER_SETTING_ERROR_CODES - error code.
*
******************************************************************************/
UPDATE_GLOBAL_USER_SETTING_ERROR_CODES SystemConfGlobalUserSetting::getGlobalUserDataUpdateResult()
{
    return m_GlobalUserDataUpdateResult;
}
/**************************************************************************//**
*
* \brief  - set autologin status and autologin user name
*
* \param  - bool - auto login status enable or disable
*
* \return - None
*
******************************************************************************/
void SystemConfGlobalUserSetting::setAutoLogin(bool autoLoginStatus, QString autoLoginUser)
{
    m_AutoLoginStatus = autoLoginStatus;
    m_AutoLoginUser = autoLoginUser;
}
/**************************************************************************//**
*
* \brief  - send user settings save request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::saveRequest()
{
    GlobalUserSettingStruct globalUserSettingData;
    globalUserSettingData.PasswordExpiryInDays = m_PasswordExpirationValue;
    globalUserSettingData.IdleTimeLogoffInMinute = m_IdleTimeLogoutValue;
    globalUserSettingData.LockOutTimeInMinute = m_LockOutTimeValue;
    globalUserSettingData.AutoLoginStatus = m_AutoLoginStatus;
    strncpy(globalUserSettingData.AutoLoginUserName,m_AutoLoginUser.toStdString().c_str(),sizeof(globalUserSettingData.AutoLoginUserName));
    m_GlobalUserSetting->InitiateGlobalUserSettingsUpdateRequest(globalUserSettingData);

}

/**************************************************************************//**
*
* \brief  - send user settings reset to default request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::resetToDefaultRequest()
{
    m_GlobalUserSetting->InitiateGlobalUserSettingsResetRequest();
}

/**************************************************************************//**
*
* \brief  - send Operator user list to global user setting screen
*
* \param  - None.
*
* \return - QStringList - operator user list.
*
******************************************************************************/
QStringList SystemConfGlobalUserSetting::loadOperatorUser()
{
    operatorUserList.clear();
    std::string operatorUserName;

    for(const auto& pair:m_UserDetailsList)
    {
        if(pair.second.Level == OPERATOR)
        {
            operatorUserName = pair.first;
            operatorUserList.append(QString::fromStdString(operatorUserName));
        }
    }
    return operatorUserList;
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnGlobalUserSettingDataUpdated is to update values on Global User Setting screen.
*
* \param  - GlobalUserSetting_Obj : Object pointer of type GlobalUserSetting.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void SystemConfGlobalUserSetting::OnGlobalUserSettingDataUpdated(GlobalUserSetting *GlobalUserSetting_Obj, UserManagement *UserManagementScreen_Obj, SystemConfigurationGeneral_MB *SysConfgGeneral_Obj, int welderId)
{
    m_GlobalUserSetting = GlobalUserSetting_Obj;
    m_UserManagement = UserManagementScreen_Obj;
    m_SysConfigGeneral = SysConfgGeneral_Obj;
    if(m_GlobalUserSetting->GetIsGlobalUserSettingDataUpdated() || m_UserManagement->IsUserListCopyUpdated()|| m_SysConfigGeneral->getSysGeneralDataChangeFlag() || m_ActiveWelderId != welderId)
    {
        if(m_GlobalUserSetting->GetIsGlobalUserSettingDataUpdated())
        {
            m_GlobalUserDataUpdateResult = m_GlobalUserSetting->GetGlobalUserSettigsDataUpdatedErrorCode();
            emit globalUserSettingErrorCodeUpdated();
        }
        GlobalUserSettingStruct globalUserSettingUpdatedData;
        globalUserSettingUpdatedData = m_GlobalUserSetting->GetGlobalUserSettingData();
        m_PasswordExpirationValue = globalUserSettingUpdatedData.PasswordExpiryInDays;
        m_IdleTimeLogoutValue = globalUserSettingUpdatedData.IdleTimeLogoffInMinute;
        m_LockOutTimeValue = globalUserSettingUpdatedData.LockOutTimeInMinute;
        m_AutoLoginStatus = globalUserSettingUpdatedData.AutoLoginStatus;
        m_AutoLoginUser = QString::fromUtf8(globalUserSettingUpdatedData.AutoLoginUserName);

        m_AuthorityCheck = m_SysConfigGeneral->GetAuthorityCheck();
        m_UserDetailsList = m_UserManagement->GetUserList();
        m_UserManagement->ResetUserListCopyUpdatedFlag();

        m_ActiveWelderId = welderId;
        m_SysConfigGeneral->setSysGeneralDataChangeFlag();
        emit globalUserSettingDataChanged();
    }
}


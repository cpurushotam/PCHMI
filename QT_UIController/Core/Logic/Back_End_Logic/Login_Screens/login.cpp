/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Login back-end code for the login qml screen
 
 **********************************************************************************************************/

#include "login.h"
#include "logindef.h"
#include "UpdateScreens.h"
#include "MultiwelderInterface.h"
#include "CommPeerWrapper.h"
#include <unistd.h>
#include<chrono>
#include<thread>

/**************************************************************************//**
*
* \brief Constructor
*
* \param parent object
*
* \return login object
*
******************************************************************************/
Login::Login(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::LoginScreenViewUpdated, this, &Login::OnLoginScreenDetailsUpdated);
}

/**************************************************************************//**
*
* \brief - The function initiates the login login request from HMI to SC.
*
* \param - UserName , Password -- Entered by user
*
* \return - None
*
******************************************************************************/

void Login::onLoginButtonClicked(const QString userName, const QString password)
{
    m_UserManagement->InitiateLoginRequest(userName.toStdString().c_str(), password.toStdString().c_str());
    m_IsLoadingFlag =true;
}


/**************************************************************************//**
*
* \brief - The function initiates the auto login request from HMI to SC.
*
* \param - UserName -- Operator level User Name
*
* \return - None
*
******************************************************************************/

void Login::onAutoLoginRequest()
{
    m_UserManagement->InitiateAutoLoginRequest(m_AutoLoginUserName.toStdString().c_str());
    m_IsLoadingFlag =true;
}
/**************************************************************************//**
*
* \brief - This function receives the validatation response from SC upon validating crediantials.
*
* \param - None
*
* \return - Error code response.
*
******************************************************************************/
int Login::loginValidationFromASC()
{
    return m_UserManagement->GetLoginErrorCodes();
}

/**************************************************************************//**
*
* \brief - The function initialtes the Reset Password request from HMI.
*
* \param - UserName , Exisitingpassword ,Newpassword
*
* \return - None.
*
******************************************************************************/
void Login::onLoginResetButtonClicked(const QString userName, const QString Existingpassword, const QString Newpassword)
{
    m_UserManagement->InitiateVerifyAndChangePasswordRequest(userName.toStdString().c_str(), Existingpassword.toStdString().c_str(), Newpassword.toStdString().c_str(), true);
}
/**************************************************************************//**
*
* \brief - This function receives the validatation response from SC upon validating crediantials.
*
* \param - None
*
* \return - Error code response.
*
******************************************************************************/
int Login::passWordResetValidationFromASC()
{
    return m_UserManagement->GetChangePasswordResponse();
}


int Login::passWordChangeValidationFromASC()
{
    return m_UserManagement->GetChangePasswordResponse();
}
/**************************************************************************//**
*
* \brief - This function returns the response error string to HMI , defined in map based on Error code received.
*
* \param  - None.
*
* \return - Error code string.
*
******************************************************************************/
QString Login::modifyUserWarningMessages()
{
    for(auto it: ModifyUserErrorCodesMap)
    {
        if(it.first == m_UserManagement->GetChangePasswordResponse())
        {
            m_ModifyErrorCodes = QString::fromStdString(it.second);
            break;
        }
    }
    return m_ModifyErrorCodes;
}

/**************************************************************************//**
*
* \brief - This function returns the response error string to HMI , defined in map based on Error code received.
*
* \param  - None.
*
* \return - Error code string.
*
******************************************************************************/
QString Login::loginWarningMessages()
{
    for(auto it: LoginErrorCodesMap)
    {
        if(it.first == m_UserManagement->GetLoginErrorCodes())
        {
            m_LoginErrorCodesQ = QString::fromStdString(it.second);
            break;
        }
    }
    return m_LoginErrorCodesQ;
}

/**************************************************************************//**
*
* \brief - The function initiates the logout request from HMI.
*
* \param - None
*
* \return - None
*
******************************************************************************/

void Login::onLogoutButtonClicked()
{
    m_UserManagement->InitiateLogoutRequest();
}

/**************************************************************************//**
*
* \brief - The function initiates the change password request from HMI.
*
* \param - None
*
* \return - None
*
******************************************************************************/
void Login::onChangePasswordButtonClicked(const QString userName, const QString Existingpass, const QString password)
{
    m_UserManagement->InitiateVerifyAndChangePasswordRequest(userName.toStdString().c_str(), Existingpass.toStdString().c_str(), password.toStdString().c_str() , false);
}

/**************************************************************************//**
*
* \brief - This function returns the Screen Navigation flag for RestPasswprd screen.
*
* \param  - None.
*
* \return - bool - m_IsScreenNavigated.
*
******************************************************************************/
bool Login::getIsScreenNavigated() const
{
    return m_IsScreenNavigated;
}

/**************************************************************************//**
*
* \brief - This function updated the ScreenNavigated flag for resetPassword screen.
*
* \param  - newIsScreenNavigated.
*
* \return - None.
*
******************************************************************************/
void Login::updateIsScreenNavigated(bool newIsScreenNavigated)
{
    if (m_IsScreenNavigated == newIsScreenNavigated)
        return;
    m_IsScreenNavigated = newIsScreenNavigated;
}

/**************************************************************************//**
*
* \brief - This function returns the Screen Navigation flag for Change Password screen.
*
* \param  - None.
*
* \return - bool - m_IsResetScreenNavigated.
*
******************************************************************************/
bool Login::getIsResetScreenNavigated() const
{
    return m_IsResetScreenNavigated;
}

/**************************************************************************//**
*
* \brief - This function updated the ScreenNavigated flag for changePassword screen.
*
* \param  - newIsScreenNavigated.
*
* \return - None.
*
******************************************************************************/
void Login::updateIsResetScreenNavigated(bool newIsResetScreenNavigated)
{
    if (m_IsResetScreenNavigated == newIsResetScreenNavigated)
        return;
    m_IsResetScreenNavigated = newIsResetScreenNavigated;
}

/**************************************************************************//**
*
* \brief - This function returns the user level for login user.
*
* \param  - None.
*
* \return - Qstring - m_loginUserLevel.
*
******************************************************************************/
QString Login::getLoginUserLevel()
{
    std::string name = m_UserManagement->GetLoggedInUserAccessLevel();
    m_loginUserLevel =  QString::fromStdString(name);
    return m_loginUserLevel;
}

/**************************************************************************//**
*
* \brief - This function updates the CUrrent Active screen from QML
*
* \param  - int screen - Current Active screen on QML
*
* \return - None.
*
******************************************************************************/
void Login::setCurrentActiveScreen(int screen)
{
    m_CurrentActiveScreen =screen;
}

/**************************************************************************//**
*
* \brief - This function returns the autoLogin status.
*
* \param  - None.
*
* \return - bool - isAutoLoginEnable.
*
******************************************************************************/
bool Login::getAutoLoginStatus()
{
    bool isAutoLoginEnable = false;
    bool flag = true;
    globalUserSettingPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetGlobalUserSettingsObjPtr();
    if(globalUserSettingPtr != nullptr)
    {
        int counter = 0;
        do
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if((globalUserSettingPtr->GetIsGlobalUserSettingDataRead()) == true || (counter == 10))
            {
                flag = false;
            }
            counter++;
        }while(flag == true);

        globalUserSettingPtr->SetGlobalUserSettingDataRead();

        if(globalUserSettingPtr->GetAutoLoginStatus() == true)
        {
            isAutoLoginEnable = true;
            m_AutoLoginUserName = QString::fromStdString(globalUserSettingPtr->GetAutoLoginUserName());
        }
        else
        {
            isAutoLoginEnable = false;
        }
    }
    m_IsAutoLoginStatusRead = true;
    return isAutoLoginEnable;
}


/**************************************************************************//**
*
* \brief - This function returns the Authority Check status.
*
* \param  - None.
*
* \return - bool - isAuthorityCheckDisabled.
*
******************************************************************************/

bool Login::getAuthorityCheckStatus()
{
    bool isAuthorityCheckDisabled = false;
    bool flag = true;
    sysConfigGenPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetSystemConfigObjPtr();
    if(sysConfigGenPtr != nullptr)
    {
        int counter  = 0 ;
        do
        {
            //This is added for getting the SystemConfigurationGeneral_MB class data as Authority check needs to be checked on power up of HMI.
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if((sysConfigGenPtr->getDataUpdatedFlag()) == true || counter == 10)
            {
                flag = false;
            }

            counter ++;
        }while(flag == true);

        if(!(sysConfigGenPtr->GetAuthortiyCheckStatus()) )
        {
            isAuthorityCheckDisabled = true;
        }
        else
        {
            isAuthorityCheckDisabled = false;
        }
    }
    m_IsAuthorityCheckStatusRead = true;
    return isAuthorityCheckDisabled;
}

/**************************************************************************//**
*
* \brief - This function returns the AutoLogin user Name.
*
* \param  - None.
*
* \return - Qstring - m_AutoLoginUserName.
*
******************************************************************************/
QString Login::getAutoLoginUserName()
{
    return m_AutoLoginUserName;
}


/**************************************************************************//**
*
* \brief - This function returns the Logged in user Name.
*
* \param  - None.
*
* \return - Qstring - logged in username.
*
******************************************************************************/
QString Login::getLoginUserName()
{
    return  QString::fromStdString(m_UserManagement->GetLoggedInUserName());
}


/**************************************************************************//**
*
* \brief - This function returns Idle Logoff Time.
*
* \param  - None.
*
* \return - uint32_t - m_IdleLogoffTime.
*
******************************************************************************/
uint32_t Login::getIdleLogOffTime()
{
    uint32_t m_IdleLogoffTime;
    m_IdleLogoffTime = globalUserSettingPtr->GetIdleTimeLoggOffTime();
    return m_IdleLogoffTime;
}

/**************************************************************************//**
*
* \brief - This function returns updated Authority check status.
*
* \param  - None.
*
* \return - bool - updated authority check status.
*
******************************************************************************/
bool Login::getUpdatedAuthCheck()
{
    bool AuthCheckStatus = sysConfigGenPtr->GetAuthortiyCheckStatus();
    return AuthCheckStatus;
}

/**************************************************************************//**
*
* \brief - This function returns the autoLogin status read or not.
*
* \param  - None.
*
* \return - bool - m_IsAutoLoginStatusRead.
*
******************************************************************************/
bool Login::autoLoginStatusRead()
{
    return m_IsAutoLoginStatusRead;
}

/**************************************************************************//**
*
* \brief - This function returns the Authority check status read or not.
*
* \param  - None.
*
* \return - bool - m_IsAuthorityCheckStatusRead.
*
******************************************************************************/

bool Login::authorityCheckStatusRead()
{
    return m_IsAuthorityCheckStatusRead;
}
/**************************************************************************//**
*
* \brief - This function returns the password override status read or not.
*
* \param  - None.
*
* \return - bool - m_IsPasswordOverrideStatusRead.
*
******************************************************************************/
bool Login::passwordOverrideStatusRead()
{
    return m_IsPasswordOverrideStatusRead;
}
/**************************************************************************//**
*
* \brief - This function returns the password override status.
*
* \param  - None.
*
* \return - bool - isDongleKeyConnected.
*
******************************************************************************/
bool Login::getPasswordOverrideStatus()
{
    bool isDongleKeyConnected = false;
    bool flag = true;
    UserManagement *userManagementPtr = CommPeerWrapper::GetPeerData(MultiwelderInterface::GetActiveWelder())->GetUserManagementObjPtr();
    if(userManagementPtr != nullptr)
    {
        int counter = 0;
        do
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if((userManagementPtr->getPasswordOverrideDataRead()) == true || (counter == 10))
            {
                flag = false;
            }
            counter++;
        }while(flag == true);

        userManagementPtr->ResetPasswordOverrideDataRead();

        if(userManagementPtr->GetPasswordOverride() == true)
        {
            isDongleKeyConnected = true;
        }
        else
        {
            isDongleKeyConnected = false;
        }
    }
    m_IsPasswordOverrideStatusRead = true;
    return isDongleKeyConnected;
}
/**************************************************************************//**
*
* \brief  - Role of the slot OnLoginScreenDetailsUpdated to update the error code responses for Login , Rest , Changepassword request.
*
* \param - UserManagement_Obj : Object pointer of type UserManagement .
*
* \return  - None.
******************************************************************************/
void Login::OnLoginScreenDetailsUpdated(UserManagement * UserManagement_Obj, int WelderId)
{
    m_UserManagement = UserManagement_Obj;

    if(m_UserManagement -> GetResetPassRepsonseChange() && m_IsScreenNavigated &&  (m_CurrentActiveScreen == UIScreenEnum::SYSTEM_CONFIG_USER_LIST_RESET_PASSWORD))
    {
        emit isScreenNavigatedChanged();
        m_UserManagement->SetResetPassRepsonseChange();
        m_IsScreenNavigated = false;
        m_CurrentActiveScreen = -1;
    }

    if(m_UserManagement -> GetLoginRepsonseChange())
    {
        m_UserManagement->SetLoginRepsonseChange();
        m_IsLoadingFlag = false;
        emit loadingDataChangedd();
    }

    if(m_UserManagement -> GetResetPassRepsonseChange() && m_IsResetScreenNavigated && (m_CurrentActiveScreen == UIScreenEnum::LOGIN))
    {
        m_UserManagement->SetResetPassRepsonseChange();
        m_IsLoadingFlag = false;
        emit modifyPassChangedd();
        m_IsResetScreenNavigated =false;
        m_CurrentActiveScreen =-1;
    }


    if( m_ActiveWelderId != WelderId)
    {
        m_ActiveWelderId = WelderId;
    }
}


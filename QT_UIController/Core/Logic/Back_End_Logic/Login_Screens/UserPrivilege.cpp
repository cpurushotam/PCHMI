/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 UserPrivilege back-end code for the UserPrivilege qml screen
 
 **********************************************************************************************************/

#include "UserPrivilege.h"
#include "UpdateScreens.h"
#include <unistd.h>

/**************************************************************************//**
*
* \brief Constructor
*
* \param parent object
*
* \return UserPrivilege object
*
******************************************************************************/
UserPrivilege::UserPrivilege(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::LoginScreenViewUpdated, this, &UserPrivilege::OnUserPrivilegeScreenDetailsUpdated);
}

/**************************************************************************//**
*
* \brief   - Below function returns the RunValidatedWeldRecipeAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsRunValidatedWeldRecipeAllowed
******************************************************************************/
bool UserPrivilege::getIsRunValidatedWeldRecipeAllowed() const
{
    return m_IsRunValidatedWeldRecipeAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the newIsRunValidatedWeldRecipeAllowed for user or not..
*
* \param   - newIsRunValidatedWeldRecipeAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsRunValidatedWeldRecipeAllowed(bool newIsRunValidatedWeldRecipeAllowed)
{
    if (m_IsRunValidatedWeldRecipeAllowed == newIsRunValidatedWeldRecipeAllowed)
        return;
    m_IsRunValidatedWeldRecipeAllowed = newIsRunValidatedWeldRecipeAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the RunUnValidatedWeldRecipeAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsRunUnValidatedWeldRecipeAllowed
******************************************************************************/
bool UserPrivilege::getIsRunUnValidatedWeldRecipeAllowed() const
{
    return m_IsRunUnValidatedWeldRecipeAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsRunUnValidatedWeldRecipeAllowed for user or not..
*
* \param   - IsRunUnValidatedWeldRecipeAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsRunUnValidatedWeldRecipeAllowed(bool newIsRunUnValidatedWeldRecipeAllowed)
{
    if (m_IsRunUnValidatedWeldRecipeAllowed == newIsRunUnValidatedWeldRecipeAllowed)
        return;
    m_IsRunUnValidatedWeldRecipeAllowed = newIsRunUnValidatedWeldRecipeAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the ResetAlarmsAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsResetAlarmsAllowed
******************************************************************************/
bool UserPrivilege::getIsResetAlarmsAllowed() const
{
    return m_IsResetAlarmsAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the newIsResetAlarmsAllowed for user or not..
*
* \param   - newIsResetAlarmsAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsResetAlarmsAllowed(bool newIsResetAlarmsAllowed)
{
    if (m_IsResetAlarmsAllowed == newIsResetAlarmsAllowed)
        return;
    m_IsResetAlarmsAllowed = newIsResetAlarmsAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the SetRecipeAsActiveAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsSetRecipeAsActiveAllowed
******************************************************************************/
bool UserPrivilege::getIsSetRecipeAsActiveAllowed() const
{
    return m_IsSetRecipeAsActiveAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsSetRecipeAsActiveAllowed for user or not..
*
* \param   - IsSetRecipeAsActiveAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsSetRecipeAsActiveAllowed(bool newIsSetRecipeAsActiveAllowed)
{
    if (m_IsSetRecipeAsActiveAllowed == newIsSetRecipeAsActiveAllowed)
        return;
    m_IsSetRecipeAsActiveAllowed = newIsSetRecipeAsActiveAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the ResetBatchCounterAndIDAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsResetBatchCounterAndIDAllowed
******************************************************************************/
bool UserPrivilege::getIsResetBatchCounterAndIDAllowed() const
{
    return m_IsResetBatchCounterAndIDAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsResetBatchCounterAndIDAllowed for user or not..
*
* \param   - newIsResetBatchCounterAndIDAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsResetBatchCounterAndIDAllowed(bool newIsResetBatchCounterAndIDAllowed)
{
    if (m_IsResetBatchCounterAndIDAllowed == newIsResetBatchCounterAndIDAllowed)
        return;
    m_IsResetBatchCounterAndIDAllowed = newIsResetBatchCounterAndIDAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the ResetRecipeCycleCountsAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsResetRecipeCycleCountsAllowed
******************************************************************************/
bool UserPrivilege::getIsResetRecipeCycleCountsAllowed() const
{
    return m_IsResetRecipeCycleCountsAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the newIsResetRecipeCycleCountsAllowed for user or not..
*
* \param   - newIsResetRecipeCycleCountsAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsResetRecipeCycleCountsAllowed(bool newIsResetRecipeCycleCountsAllowed)
{
    if (m_IsResetRecipeCycleCountsAllowed == newIsResetRecipeCycleCountsAllowed)
        return;
    m_IsResetRecipeCycleCountsAllowed = newIsResetRecipeCycleCountsAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the EditRecipesAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsEditRecipesAllowed
******************************************************************************/
bool UserPrivilege::getIsEditRecipesAllowed() const
{
    return m_IsEditRecipesAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsEditRecipesAllowed for user or not..
*
* \param   - IsEditRecipesAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsEditRecipesAllowed(bool newIsEditRecipesAllowed)
{
    if (m_IsEditRecipesAllowed == newIsEditRecipesAllowed)
        return;
    m_IsEditRecipesAllowed = newIsEditRecipesAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the CalibrationAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsCalibrationAllowed
******************************************************************************/
bool UserPrivilege::getIsCalibrationAllowed() const
{
    return m_IsCalibrationAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsCalibrationAllowed for user or not..
*
* \param   - newIsCalibrationAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsCalibrationAllowed(bool newIsCalibrationAllowed)
{
    if (m_IsCalibrationAllowed == newIsCalibrationAllowed)
        return;
    m_IsCalibrationAllowed = newIsCalibrationAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the ActuatorSetupAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsActuatorSetupAllowed
******************************************************************************/
bool UserPrivilege::getIsActuatorSetupAllowed() const
{
    return m_IsActuatorSetupAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsActuatorSetupAllowed for user or not..
*
* \param   - IsActuatorSetupAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsActuatorSetupAllowed(bool newIsActuatorSetupAllowed)
{
    if (m_IsActuatorSetupAllowed == newIsActuatorSetupAllowed)
        return;
    m_IsActuatorSetupAllowed = newIsActuatorSetupAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the DignosticsAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsDignosticsAllowed
******************************************************************************/
bool UserPrivilege::getIsDignosticsAllowed() const
{
    return m_IsDignosticsAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsDignosticsAllowed for user or not..
*
* \param   - IsDignosticsAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsDignosticsAllowed(bool newIsDignosticsAllowed)
{
    if (m_IsDignosticsAllowed == newIsDignosticsAllowed)
        return;
    m_IsDignosticsAllowed = newIsDignosticsAllowed;

}

/**************************************************************************//**
*
* \brief   - Below function returns the SaveCopyCreateRecipeAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsSaveCopyCreateRecipeAllowed
******************************************************************************/
bool UserPrivilege::getIsSaveCopyCreateRecipeAllowed() const
{
    return m_IsSaveCopyCreateRecipeAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsSaveCopyCreateRecipeAllowed for user or not..
*
* \param   - IsSaveCopyCreateRecipeAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsSaveCopyCreateRecipeAllowed(bool newIsSaveCopyCreateRecipeAllowed)
{
    if (m_IsSaveCopyCreateRecipeAllowed == newIsSaveCopyCreateRecipeAllowed)
        return;
    m_IsSaveCopyCreateRecipeAllowed = newIsSaveCopyCreateRecipeAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function returns the ExtractUSBDataFromWelderAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsExtractUSBDataFromWelderAllowed
******************************************************************************/
bool UserPrivilege::getIsExtractUSBDataFromWelderAllowed() const
{
    return m_IsExtractUSBDataFromWelderAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsExtractUSBDataFromWelderAllowed for user or not..
*
* \param   - IsExtractUSBDataFromWelderAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsExtractUSBDataFromWelderAllowed(bool newIsExtractUSBDataFromWelderAllowed)
{
    if (m_IsExtractUSBDataFromWelderAllowed == newIsExtractUSBDataFromWelderAllowed)
        return;
    m_IsExtractUSBDataFromWelderAllowed = newIsExtractUSBDataFromWelderAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the SystemConfigurationAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsSystemConfigurationAllowed
******************************************************************************/
bool UserPrivilege::getIsSystemConfigurationAllowed() const
{
    return m_IsSystemConfigurationAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsSystemConfigurationAllowed for user or not..
*
* \param   - newIsSystemConfigurationAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsSystemConfigurationAllowed(bool newIsSystemConfigurationAllowed)
{
    if (m_IsSystemConfigurationAllowed == newIsSystemConfigurationAllowed)
        return;
    m_IsSystemConfigurationAllowed = newIsSystemConfigurationAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the ValidateAndLockWeldRecipesAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsValidateAndLockWeldRecipesAllowed
******************************************************************************/
bool UserPrivilege::getIsValidateAndLockWeldRecipesAllowed() const
{
    return m_IsValidateAndLockWeldRecipesAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsValidateAndLockWeldRecipesAllowed for user or not..
*
* \param   - IsValidateAndLockWeldRecipesAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsValidateAndLockWeldRecipesAllowed(bool newIsValidateAndLockWeldRecipesAllowed)
{
    if (m_IsValidateAndLockWeldRecipesAllowed == newIsValidateAndLockWeldRecipesAllowed)
        return;
    m_IsValidateAndLockWeldRecipesAllowed = newIsValidateAndLockWeldRecipesAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the AddModifyUserIDSetupAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsAddModifyUserIDSetupAllowed
******************************************************************************/
bool UserPrivilege::getIsAddModifyUserIDSetupAllowed() const
{
    return m_IsAddModifyUserIDSetupAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updated the IsAddModifyUserIDSetupAllowed for user or not..
*
* \param   - newIsAddModifyUserIDSetupAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsAddModifyUserIDSetupAllowed(bool newIsAddModifyUserIDSetupAllowed)
{
    if (m_IsAddModifyUserIDSetupAllowed == newIsAddModifyUserIDSetupAllowed)
        return;
    m_IsAddModifyUserIDSetupAllowed = newIsAddModifyUserIDSetupAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the ModifyAuthoritiyCheckAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsModifyAuthoritiyCheckAllowed
******************************************************************************/
bool UserPrivilege::getIsModifyAuthoritiyCheckAllowed() const
{
    return m_IsModifyAuthoritiyCheckAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the newIsModifyAuthoritiyCheckAllowed for user or not..
*
* \param   - newIsModifyAuthoritiyCheckAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsModifyAuthoritiyCheckAllowed(bool newIsModifyAuthoritiyCheckAllowed)
{
    if (m_IsModifyAuthoritiyCheckAllowed == newIsModifyAuthoritiyCheckAllowed)
        return;
    m_IsModifyAuthoritiyCheckAllowed = newIsModifyAuthoritiyCheckAllowed;
}
/**************************************************************************//**
*
* \brief   - Below function returns the DeleteRecipeAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsDeleteRecipeAllowed
******************************************************************************/
bool UserPrivilege::getIsDeleteRecipeAllowed() const
{
    return m_IsDeleteRecipeAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the DeleteRecipeAllowed for user or not..
*
* \param   - newIsDeleteRecipeAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsDeleteRecipeAllowed(bool newIsDeleteRecipeAllowed)
{
    if (m_IsDeleteRecipeAllowed == newIsDeleteRecipeAllowed)
        return;
    m_IsDeleteRecipeAllowed = newIsDeleteRecipeAllowed;
}
/**************************************************************************//**
*
* \brief   - Below function updates the UpdateSoftwareAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsUpdateSoftwareAllowed
******************************************************************************/
bool UserPrivilege::getIsUpdateSoftwareAllowed() const
{
    return m_IsUpdateSoftwareAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the UpdateSoftwareAllowed for user or not..
*
* \param   - newIsUpdateSoftwareAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsUpdateSoftwareAllowed(bool newIsUpdateSoftwareAllowed)
{
    if (m_IsUpdateSoftwareAllowed == newIsUpdateSoftwareAllowed)
        return;
    m_IsUpdateSoftwareAllowed = newIsUpdateSoftwareAllowed;

}
/**************************************************************************//**
*
* \brief   - Below function returns the BarcoderecipeRecallAllowed for user or not.
*
* \param   - None.
*
* \return  - m_IsBarcoderecipeRecallAllowed
******************************************************************************/
bool UserPrivilege::getIsBarcoderecipeRecallAllowed() const
{
    return m_IsBarcoderecipeRecallAllowed;
}

/**************************************************************************//**
*
* \brief   - Below function updates the BarcoderecipeRecallAllowed for user or not..
*
* \param   - newIsBarcoderecipeRecallAllowed
*
* \return  - None.
******************************************************************************/
void UserPrivilege::updateIsBarcoderecipeRecallAllowed(bool newIsBarcoderecipeRecallAllowed)
{
    if (m_IsBarcoderecipeRecallAllowed == newIsBarcoderecipeRecallAllowed)
        return;
    m_IsBarcoderecipeRecallAllowed = newIsBarcoderecipeRecallAllowed;

}

/**************************************************************************//**
*
* \brief   - To get the current loggedin userlevel.
*
* \param  -  None .
*
* \return  - None.
******************************************************************************/
QString UserPrivilege::getLogedInUserLevel()
{
    std::string UserLevel = "";
    UserLevel = m_UserManagement->GetLoggedInUserAccessLevel();
    return QString::fromStdString(UserLevel);
}
/**************************************************************************//**
*
* \brief   - To process the userlevel privilege and display on HMI.
*
* \param  -  None .
*
* \return  - None.
******************************************************************************/
void UserPrivilege:: processUserPrivilige()
{
    std::string UserLevel = "";
    UserLevel = m_UserManagement->GetLoggedInUserAccessLevel();

    std::transform(UserLevel.begin(), UserLevel.end(), UserLevel.begin(), ::toupper);

    for (auto it = m_UserPrivilegeDetails.begin(); it != m_UserPrivilegeDetails.end(); ++it)
    {
        if(it->first == UserLevel)
        {
            m_IsRunValidatedWeldRecipeAllowed    =  it->second.IsRunValidatedWeldRecipeAllowed; //static_castit->second.IsRunValidatedWeldRecipeAllowed;
            m_IsRunUnValidatedWeldRecipeAllowed  = it->second.IsRunUnValidatedWeldRecipeAllowed ;
            m_IsResetAlarmsAllowed               = it->second.IsResetAlarmsAllowed;
            m_IsSetRecipeAsActiveAllowed         = it->second.IsSetRecipeAsActiveAllowed;
            m_IsResetBatchCounterAndIDAllowed    = it->second.IsResetBatchCounterAndIDAllowed;
            m_IsResetRecipeCycleCountsAllowed    = it->second.IsResetRecipeCycleCountsAllowed;
            m_IsEditRecipesAllowed               = it->second.IsEditRecipesAllowed;
            m_IsCalibrationAllowed               = it->second.IsCalibrationAllowed;
            m_IsActuatorSetupAllowed             = it->second.IsActuatorSetupAllowed;
            m_IsDignosticsAllowed                = it->second.IsDignosticsAllowed;
            m_IsSaveCopyCreateRecipeAllowed      = it->second.IsSaveCopyCreateRecipeAllowed;
            m_IsExtractUSBDataFromWelderAllowed  =  it->second.IsExtractUSBDataFromWelderAllowed;
            m_IsSystemConfigurationAllowed       = it->second.IsSystemConfigurationAllowed;
            m_IsValidateAndLockWeldRecipesAllowed  =  it->second.IsValidateAndLockWeldRecipesAllowed;
            m_IsAddModifyUserIDSetupAllowed      = it->second.IsAddModifyUserIDSetupAllowed;
            m_IsModifyAuthoritiyCheckAllowed     = it->second.IsModifyAuthoritiyCheckAllowed;
            m_IsDeleteRecipeAllowed              = it->second.IsDeleteRecipeAllowed;
            m_IsUpdateSoftwareAllowed            = it->second.IsUpdateSoftwareAllowed;
            m_IsBarcoderecipeRecallAllowed       = it->second.IsBarcoderecipeRecallAllowed;
            m_IsUsbAuthenticationAllowed         = it->second.IsUsbAuthenticationAllowed;
            
        }
    }
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnUserPrivilegeScreenDetailsUpdated to update the error code responses for UserPrivilege , Rest , Changepassword request.
*
* \param  - UserManagement_Obj : Object pointer of type UserManagement .
*
* \return  - None.
******************************************************************************/
void UserPrivilege::OnUserPrivilegeScreenDetailsUpdated(UserManagement * UserManagement_Obj, int WelderId)
{
    m_UserManagement = UserManagement_Obj;

    if(m_UserManagement->GetUsrPrivilegeRepsonseChange())
    {
        m_UserPrivilegeDetails = m_UserManagement->GetUserPrivilege();
        m_UserManagement->SetUsrPrivilegeRepsonseChange();
        processUserPrivilige();
    }

    if( m_ActiveWelderId != WelderId)
    {
        m_ActiveWelderId = WelderId;
    }
}


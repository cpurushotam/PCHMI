/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UserListDetailsListModel.cpp file handles Alarm details list model container includes :
    Alarm counts, date and time.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 30/05/2024 - Initial version.
***************************************************************************/
#include "UserListDetailsListModel.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <algorithm>
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
UserListDetailsListModel::UserListDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::UserListScreenViewUpdated, this, &UserListDetailsListModel::OnUserListDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
UserListDetailsListModel::~UserListDetailsListModel()
{
    qDeleteAll(m_ListData.begin(), m_ListData.end());
    m_ListData.clear();
}

/**************************************************************************//**
*
* \brief - Qt Item model standard interface
*          The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*          Note: This function can be invoked via the meta-object system and from QML.
*          To get the list size number.
*
* \param  - QModelIndex object to determine the size.
*
* \return - Return weld alarm details list size.
*
******************************************************************************/
int UserListDetailsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ListData.count();
}

/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*           The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*           To locate at the specific object using the Model Index and get the data from the specific object then.
*           Note: This function can be invoked via the meta-object system and from QML.
*           Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index and role : To determine the row for designated role.
*
* \return - The property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant UserListDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const UserListDetailsListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {
    case UserIdRole:
        return ptrListObj->getUserID();
        break;

    case AuthorityLevelRole:
        return ptrListObj->getUserLevelString();
        break;

    case UserStatusRole:
        return ptrListObj->getUserStatusString();
        break;

    case UserLockUnlockRole:
        return ptrListObj->getUserIsLocked();
        break;

    case DateTimeRole:
        return ptrListObj->getUserCreationDateTime();
        break;

    default:
        return QVariant();
        break;
    }

    return QVariant();
}

/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*         - The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*         - Returns the index of the data in row and column with parent.
*         - Note: This function can be invoked via the meta-object system and from QML.
*         - Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index.row should be in the range of the User list.
*
* \return - If the row is in the range of the User list list,
*         - the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex UserListDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    UserListDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<UserListDetailsListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief - To clear the UserListDetailsListData list.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void UserListDetailsListModel::clearAlarmDetailsList()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    qDeleteAll(m_ListData);
    m_ListData.clear();
    endRemoveRows();
}

/**************************************************************************//**
*
* \brief - Below function add new content into the detail list.  .
*
* \param  - UserDetailsList : List data of type UserListDetailsListData.
*
* \return - None.
*
******************************************************************************/
void UserListDetailsListModel::addNewAlarmDetailsList(UserListDetailsListData *AlarmDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(AlarmDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadAlarmDetailsList function called by qml while loading of
*            alarm detail list, to display available alarm details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::loadAlarmDetailsList()
{
    createNewAlarmDetailsList();
    clearAlarmDetailsList();

    UserListDetailsListData* ptrListObj = nullptr;

    for (auto it=m_UserDetailsList.begin(); it!=m_UserDetailsList.end(); ++it)
    {
       ptrListObj = new UserListDetailsListData(it->second.UserID,it->second.Level,it->second.Status,it->second.IsLocked ,it->second.CreationDateTime);
       addNewAlarmDetailsList(ptrListObj);
   }
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type UserListDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::createNewAlarmDetailsList()
{
    UserListDetailsListData* ptrListObj = new UserListDetailsListData();
    addNewAlarmDetailsList(ptrListObj);
}

/**************************************************************************//**
*
* \brief -  Define which properties need to expose to QML under the User details list
*        -  Model. To generate a link table between Model and list data.
*
* \param -  None
*
* \return - Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> UserListDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AlarmRoles::UserIdRole]           = "UserId";
    roles[AlarmRoles::AuthorityLevelRole]   = "AuthorityLevel";
    roles[AlarmRoles::UserStatusRole]       = "UserStatus";
    roles[AlarmRoles::UserLockUnlockRole]   = "UserLockUnlock";
    roles[AlarmRoles::DateTimeRole]         = "DateTime";

    return roles;
}

/**************************************************************************//**
*
* \brief   - QINNOVAKABLE function used by QML to update backend on Update button clicked.
*
* \param   - userID, authorityLevel, status, islocked.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::onModifyUserButtonClicked(const QString userID, const int authorityLevel, const bool status, const bool islocked)
{
    addUserStruct modifieduserStruct;

    strcpy( modifieduserStruct.UserID,userID.toStdString().c_str());
    modifieduserStruct.AuthLevel = static_cast< USER_LEVEL>(authorityLevel);
    modifieduserStruct.Status = static_cast< USER_STATUS>(status);
    modifieduserStruct.IsUserLocked = static_cast< USER_ISLOCKED>(islocked);

    m_UserManagement->InitiateModifyUserRequest(modifieduserStruct);
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
int UserListDetailsListModel::modifyuserResponseFromASC()
{
    return m_UserManagement->GetModifyUserResponse();
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
QString UserListDetailsListModel::editUserWarningMessages()
{
    for(auto it: ModifyUserErrorCodesMap)
    {
       if(it.first == m_UserManagement->GetModifyUserResponse())
       {
           m_EditUserErrorCodes = QString::fromStdString(it.second);
           break;
       }
    }
    return m_EditUserErrorCodes;
}

/**************************************************************************//**
*
* \brief   - This function is called by QML when user wants to create to use add user functionality.
*
* \param   - userID, password, authorityLevel, status, islocked.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel:: onAddUserRequest(const QString userID, const QString password, const int authorityLevel, const bool status, const bool islocked)
{
    addUserStruct newuserStruct;

    strcpy( newuserStruct.UserID,userID.toStdString().c_str());
    strcpy( newuserStruct.Password,password.toStdString().c_str());
    newuserStruct.AuthLevel = static_cast< USER_LEVEL>(authorityLevel);
    newuserStruct.Status = static_cast< USER_STATUS>(status);
    newuserStruct.IsUserLocked = static_cast< USER_ISLOCKED>(islocked);

    m_UserManagement->InitiateAddUserRequest(newuserStruct);
}

/**************************************************************************//**
*
* \brief - This function receives the validatation response from SC upon validating crediantials for add user request.
*
* \param - None
*
* \return - Error code response.
*
******************************************************************************/
int UserListDetailsListModel::addUserResponseFromASC()
{
    return m_UserManagement->GetAddUserResponse();
}

/**************************************************************************//**
*
* \brief - This function returns the response error string to HMI , defined in map based on Error code received.
*
* \param  - None.
*
* \return - m_AddUserErrorCodes - Error code string.
*
******************************************************************************/
QString UserListDetailsListModel::addUserWarningMessages()
{
    for(auto it: AddUserErrorCodesMap)
    {
       if(it.first == m_UserManagement->GetAddUserResponse())
       {
           m_AddUserErrorCodes = QString::fromStdString(it.second);
           break;
       }
    }
    return m_AddUserErrorCodes;
}


/**************************************************************************//**
*
* \brief   - This function is used by QML for using Delete user request form QML.
*
* \param   - userID .
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::onDeleteUserRequest(const QString userID)
{
    m_UserManagement->InitiateDeleteUserRequest(userID.toStdString().c_str());
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
int UserListDetailsListModel::deleteUserResponseFromASC()
{
    return m_UserManagement->GetDeleteUserResponse();
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
QString UserListDetailsListModel::modifyUserWarningMessages()
{
    for(auto it: ModifyUserErrorCodesMap)
    {
       if(it.first == m_UserManagement->GetDeleteUserResponse())
       {
           m_ModifyErrorCodes = QString::fromStdString(it.second);
           break;
       }
    }
    return m_ModifyErrorCodes;
}

/**************************************************************************//**
*
* \brief   -  This function is used by QML for chnage pasword request from QML to SC.
*
* \param   - userID, password.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::onChangePasswordRequest(const QString userID,const QString password)
{
    m_UserManagement->InitiateChangePasswordRequest(userID.toStdString().c_str(), password.toStdString().c_str());
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
int UserListDetailsListModel::changePassResponseFromASC()
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
QString UserListDetailsListModel::changePasswordWarningMessages()
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
* \brief   - Role of the slot OnUserListDetailsListUpdated to update the user
*            details list data.
*
* \param   - UserManagementScreen_Obj : The UserManagement object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::OnUserListDetailsListUpdated(UserManagement *UserManagementScreen_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);

    m_UserManagement = UserManagementScreen_Obj;

    if(m_UserManagement -> GetResetPassRepsonseChange() && m_IsChangeScreenNavigated && (m_CurrentActiveScreen == UIScreenEnum::SYSTEM_CONFIG_USER_LIST_CHANGE_PASSWORD))
    {
       emit changeUserpassResponseChanged();
       m_UserManagement -> SetResetPassRepsonseChange();
       m_IsChangeScreenNavigated = false;
       m_CurrentActiveScreen = -1;
    }

    if(m_UserManagement ->GetModifyUsrReqRepsonseChange())
    {
       emit modifyUserResponseChanged();
       m_UserManagement -> SetModifyUsrReqRepsonseChange();
    }

    if(m_UserManagement ->GetDelUsrReqRepsonseChange())
    {
       emit deleteUserResponseChanged();
       m_UserManagement -> SetDelUsrReqRepsonseChange();
    }

    if(m_UserManagement ->GetAddUsrReqRepsonseChange())
    {
       emit addUserResponseChanged();
       m_UserManagement -> SetAddUsrReqRepsonseChange();
    }

    if( m_UserManagement->IsUserListUpdated() || m_ActiveWelderId != WelderId)
    {
        m_UserDetailsList = m_UserManagement->GetUserList();
        m_UserManagement->ResetUserListUpdatedFlag();
        m_IsScreenReNavigated = false;
        m_ActiveWelderId = WelderId;
        loadAlarmDetailsList();
        emit alarmDetailsListDataChanged();
    }

    pthread_mutex_unlock(&mtx);
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsChangeScreenNavigated.
*
* \param   - None.
*
* \return  - m_IsChangeScreenNavigated : IsChangeScreenNavigated flag .
******************************************************************************/
bool UserListDetailsListModel::getIsChangeScreenNavigated() const
{
    return m_IsChangeScreenNavigated;
}
/**************************************************************************//**
*
* \brief   - Below function updates the IsChangeScreenNavigated flag upon screen navigated.
*
* \param   - newIsChangeScreenNavigated : Boolean value for screen navigagted or not.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::updateIsChangeScreenNavigated(bool newIsChangeScreenNavigated)
{
    if (m_IsChangeScreenNavigated == newIsChangeScreenNavigated)
        return;
    m_IsChangeScreenNavigated = newIsChangeScreenNavigated;
}
/**************************************************************************//**
*
* \brief   - Below function updates the currentActive screen from QML.
*
* \param   - int screen : Current active screen from QML.
*
* \return  - None.
******************************************************************************/
void UserListDetailsListModel::setCurrentActiveScreenUserChange(int screen)
{
    m_CurrentActiveScreen =screen;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UserListDetailsListData.h file provides alarm detail list container data
    handeled by AlarmDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#ifndef UserListDetailsListData_H
#define UserListDetailsListData_H

#include <QString>
#include "UserManagementStructure.h"

class UserListDetailsListData
{
public:

    UserListDetailsListData();
    UserListDetailsListData(const QString& p_UserID, const USER_LEVEL& p_Level, const USER_STATUS& p_Status, const USER_ISLOCKED& p_IsLocked,
                         const QString& p_CreationDateTime);

private:

    QString m_UserID;
    USER_LEVEL m_Level;
    USER_STATUS m_Status;
    USER_ISLOCKED m_IsLocked;
    QString m_CreationDateTime;

public:

    QString getUserID() const;
    USER_LEVEL getUserLevel() const;
    USER_STATUS getUserStatus() const;
    USER_ISLOCKED getUserIsLocked() const;
    QString getUserCreationDateTime() const;
    QString getUserLevelString() const;
    QString getUserStatusString() const;

};

#endif // UserListDetailsListData_H

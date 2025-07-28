/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UserListDetailsListData.h file provides alarm detail list container data
    handled by UserListDetailsListDataModel.
***************************************************************************/
#include "UserListDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
UserListDetailsListData::UserListDetailsListData()
{

}

UserListDetailsListData::UserListDetailsListData(const QString& p_UserID, const USER_LEVEL& p_Level, const USER_STATUS& p_Status, const USER_ISLOCKED& p_IsLocked,
                                                 const QString& p_CreationDateTime)
    : m_UserID(p_UserID),
      m_Level(p_Level),
      m_Status(p_Status),
      m_IsLocked(p_IsLocked),
      m_CreationDateTime(p_CreationDateTime)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the User Id.
*
* \param   - None.
*
* \return  - m_UserID
******************************************************************************/
QString UserListDetailsListData::getUserID() const
{
   return m_UserID;
}

/**************************************************************************//**
*
* \brief   - Below function returns the User Level.
*
* \param   - None.
*
* \return  - m_Level
******************************************************************************/
USER_LEVEL UserListDetailsListData::getUserLevel() const
{
    return m_Level;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Status .
*
* \param   - None.
*
* \return  - m_Status
******************************************************************************/
USER_STATUS UserListDetailsListData::getUserStatus() const
{
    return m_Status;
}

/**************************************************************************//**
*
* \brief   - Below function returns the user IsLocked or unlocked.
*
* \param   - None.
*
* \return  - m_IsLocked.
******************************************************************************/
USER_ISLOCKED UserListDetailsListData::getUserIsLocked() const
{
    return m_IsLocked;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Creation Date Time.
*
* \param   - None.
*
* \return  - m_CreationDateTime.
******************************************************************************/
QString UserListDetailsListData::getUserCreationDateTime() const
{
   return m_CreationDateTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns the UserLevelType .
*
* \param   - None.
*
* \return  - UserLevelType
******************************************************************************/
QString UserListDetailsListData::getUserLevelString() const
{
   QString UserLevelType;

   for(auto it: UserLevelStringMap)
   {
       if(it.first == m_Level)
       {
           UserLevelType = QString::fromStdString(it.second);
           break;
       }
   }
   return UserLevelType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the UserLevelType .
*
* \param   - None.
*
* \return  - UserLevelType
******************************************************************************/
QString UserListDetailsListData::getUserStatusString() const
{
   QString UserStatusType;

   if(m_Status == 0)
   {
       UserStatusType = "Enable";
   }
   else
   {
        UserStatusType = "Disable";
   }
   return UserStatusType;
}

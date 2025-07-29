/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AlarmDetailsListData.h file provides alarm detail list container data
    handled by AlaramDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#include "AlarmDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
AlarmDetailsListData::AlarmDetailsListData()
{

}

AlarmDetailsListData::AlarmDetailsListData(const int& p_ErrorType, const ALARM_IDS &p_AlarmID, const int &p_AlarmSubType, const int& p_RecipeNo,
                                           const int& p_RecipeVersion, const int& p_CycleNo, const QString & p_CycleDateTime,
                                           const QString& p_UserName, const int& p_AlarmType,   const QString& p_AddedNotes, const int& p_AlarmLogIndex)
    : m_ErrorType(p_ErrorType),
      m_AlarmID(p_AlarmID),
      p_AlarmSubType(p_AlarmSubType),
      m_RecipeNo(p_RecipeNo),
      m_RecipeVersion(p_RecipeVersion),
      m_CycleNo(p_CycleNo),
      m_CycleDateTime(p_CycleDateTime),
      m_UserName(p_UserName),
      m_AlarmType(p_AlarmType),
      m_AddedNotes(p_AddedNotes),
      m_AlarmLogIndex(p_AlarmLogIndex)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm error type.
*
* \param   - None.
*
* \return  - m_ErrorType
******************************************************************************/
int AlarmDetailsListData::getErrorType() const
{
   return m_ErrorType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm ID.
*
* \param   - None.
*
* \return  - m_AlarmID
******************************************************************************/
ALARM_IDS AlarmDetailsListData::getAlarmID() const
{
    return m_AlarmID;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm sub type.
*
* \param   - None.
*
* \return  - p_AlarmSubType
******************************************************************************/
int AlarmDetailsListData::getAlarmSubType() const
{
    return p_AlarmSubType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm recipe number.
*
* \param   - None.
*
* \return  - m_RecipeNo.
******************************************************************************/
int AlarmDetailsListData::getRecipeNo() const
{
    return m_RecipeNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm recipe version number.
*
* \param   - None.
*
* \return  - m_RecipeVersion.
******************************************************************************/
int AlarmDetailsListData::getRecipeVersion() const
{
   return m_RecipeVersion;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm cycle number.
*
* \param   - None.
*
* \return  - m_CycleNo : Alarm Cycle number.
******************************************************************************/
int AlarmDetailsListData::getCycleNo() const
{
    return m_CycleNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm date and time.
*
* \param   - None.
*
* \return  - m_CycleDateTime : Alarm date and time.
******************************************************************************/
QString AlarmDetailsListData::getCycleDateTime() const
{
    return m_CycleDateTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns the user name.
*
* \param   - None.
*
* \return  - m_UserName : The user name.
******************************************************************************/
QString AlarmDetailsListData::getUserName() const
{
    return m_UserName;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm type.
*
* \param   - None.
*
* \return  - m_AlarmType : The alarm type.
******************************************************************************/
int AlarmDetailsListData::getAlarmType() const
{
    return m_AlarmType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Added Notes.
*
* \param   - None.
*
* \return  - m_AddedNotes : The Added Notes.
******************************************************************************/
QString AlarmDetailsListData::getAddedNotes() const
{
    return m_AddedNotes;
}
/**************************************************************************//**
*
* \brief   - Below function returns the m AlarmLogIndex.
*
* \param   - None.
*
* \return  - m_AlarmLogIndex : The alarm log index.
******************************************************************************/
int AlarmDetailsListData::getAlarmLogIndex() const
{
    return m_AlarmLogIndex;
}

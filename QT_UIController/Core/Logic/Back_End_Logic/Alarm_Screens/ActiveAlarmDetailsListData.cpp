/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ActiveAlarmDetailsListData.h file provides alarm detail list container data
    handled by AlaramDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#include "ActiveAlarmDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
ActiveAlarmDetailsListData::ActiveAlarmDetailsListData()
{

}

ActiveAlarmDetailsListData::ActiveAlarmDetailsListData(const ALARM_IDS &p_AlarmID, const int &p_AlarmSubType, const bool &p_IsAlarmLogRequired, const QString &p_ServiceName)
    : m_AlarmID(p_AlarmID),
      m_AlarmSubType(p_AlarmSubType),
      m_IsAlarmLogRequired(p_IsAlarmLogRequired),
      m_ServiceName(p_ServiceName)

{

}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm ID.
*
* \param   - None.
*
* \return  - m_AlarmID
******************************************************************************/
ALARM_IDS ActiveAlarmDetailsListData::getAlarmID() const
{
    return m_AlarmID;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm sub type.
*
* \param   - None.
*
* \return  - m_AlarmSubType
******************************************************************************/
int ActiveAlarmDetailsListData::getAlarmSubType() const
{
    return m_AlarmSubType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm log required status.
*
* \param   - None.
*
* \return  - m_IsAlarmLogRequired
******************************************************************************/
bool ActiveAlarmDetailsListData::getIsAlarmLogRequired() const
{
    return m_IsAlarmLogRequired;
}

/**************************************************************************//**
*
* \brief   - Below function returns the alarm service name.
*
* \param   - None.
*
* \return  - m_ServiceName
******************************************************************************/
QString ActiveAlarmDetailsListData::getServiceName() const
{
    return m_ServiceName;
}



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
#include "ServiceCountListData.h"
#include <QDateTime>
/**************************************************************************//**

/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
ServiceCountListData::ServiceCountListData()
{

}

ServiceCountListData::ServiceCountListData(const QString &p_ServiceName, const int &p_Counter, const int &p_Limit, const QString &p_StartTime, int &p_ReminderMethod, int &p_ReminderStatus, int &p_SnoozeDuration)
    : m_ServiceName(p_ServiceName),
      m_Counter(p_Counter),
      m_Limit(p_Limit),
      m_StartTime(p_StartTime),
      m_ReminderMethod(p_ReminderMethod),
      m_ReminderStatus(p_ReminderStatus),
      m_SnoozeDuration(p_SnoozeDuration)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the service name.
*
* \param   - None.
*
* \return  - m_ServiceName
******************************************************************************/
QString ServiceCountListData::getServiceName() const
{
    return m_ServiceName;
}

/**************************************************************************//**
*
* \brief   - Below function returns the counter.
*
* \param   - None.
*
* \return  - m_Counter
******************************************************************************/
int ServiceCountListData::getCounter() const
{
    return m_Counter;
}

/**************************************************************************//**
*
* \brief   - Below function returns the limit.
*
* \param   - None.
*
* \return  - m_Limit
******************************************************************************/
int ServiceCountListData::getLimit() const
{
    return m_Limit;
}

/**************************************************************************//**
*
* \brief   - Below function returns the start time.
*
* \param   - None.
*
* \return  - m_StartTime
******************************************************************************/
QString ServiceCountListData::getStartTime() const
{
    return m_StartTime;
}

int ServiceCountListData::getReminderMethod() const
{
    return m_ReminderMethod;
}

int ServiceCountListData::getReminderStatus() const
{
    return m_ReminderStatus;
}

int ServiceCountListData::getSnoozeDuration() const
{
    return m_SnoozeDuration;
}

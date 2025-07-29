/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ActiveServiceReminderDetailsListData.h file provides alarm detail list container data
    handled by ServiceReminderDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 08/10/2024 - Initial version.
***************************************************************************/
#include "ActiveServiceReminderDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
ActiveServiceReminderDetailsListData::ActiveServiceReminderDetailsListData()
{

}

ActiveServiceReminderDetailsListData::ActiveServiceReminderDetailsListData(const ALARM_IDS &p_ServiceReminderID, const int &p_ServiceReminderSubType, const bool &p_IsServiceReminderLogRequired, const QString &p_ServiceName, const int &p_SnoozeDuration)
    : m_ServiceReminderID(p_ServiceReminderID),
      m_ServiceReminderSubType(p_ServiceReminderSubType),
      m_IsServiceReminderLogRequired(p_IsServiceReminderLogRequired),
      m_ServiceName(p_ServiceName),
      m_SnoozeDuration(p_SnoozeDuration)

{

}

/**************************************************************************//**
*
* \brief   - Below function returns the service reminder ID.
*
* \param   - None.
*
* \return  - m_ServiceReminderID
******************************************************************************/
ALARM_IDS ActiveServiceReminderDetailsListData::getServiceReminderID() const
{
    return m_ServiceReminderID;
}

/**************************************************************************//**
*
* \brief   - Below function returns the service reminder sub type.
*
* \param   - None.
*
* \return  - m_ServiceReminderSubType
******************************************************************************/
int ActiveServiceReminderDetailsListData::getServiceReminderSubType() const
{
    return m_ServiceReminderSubType;
}

/**************************************************************************//**
*
* \brief   - Below function returns the service reminder log required status.
*
* \param   - None.
*
* \return  - m_IsServiceReminderLogRequired
******************************************************************************/
bool ActiveServiceReminderDetailsListData::getIsServiceReminderLogRequired() const
{
    return m_IsServiceReminderLogRequired;
}

/**************************************************************************//**
*
* \brief   - Below function returns the service reminder service name.
*
* \param   - None.
*
* \return  - m_ServiceName
******************************************************************************/
QString ActiveServiceReminderDetailsListData::getServiceName() const
{
    return m_ServiceName;
}

/**************************************************************************//**
*
* \brief   - Below function returns the service reminder snooze duration.
*
* \param   - None.
*
* \return  - m_SnoozeDuration
******************************************************************************/
int ActiveServiceReminderDetailsListData::getSnoozeDuration() const
{
    return m_SnoozeDuration;
}



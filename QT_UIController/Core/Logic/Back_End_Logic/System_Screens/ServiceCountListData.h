/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ActiveAlarmDetailsListData.h file provides alarm detail list container data
    handeled by AlarmDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#ifndef SERVICECOUNTLISTDATA_H
#define SERVICECOUNTLISTDATA_H

#include <QString>
#include "Common_Definitions.h"
#include "ServiceReminderStructure.h"

class ServiceCountListData
{
public:

    ServiceCountListData();
    ServiceCountListData(const QString& p_ServiceName, const int& p_Counter, const int& p_Limit, const QString &p_StartTime,
                         int& p_ReminderMethod, int& p_ReminderStatus, int& p_SnoozeDuration);

private:

    QString m_ServiceName;
    int m_Counter;
    int m_Limit;
    QString m_StartTime;
    int m_ReminderMethod;
    int m_ReminderStatus;
    int m_SnoozeDuration;

public:

    QString getServiceName() const;
    int getCounter() const;
    int getLimit() const;
    QString getStartTime() const;
    int getReminderMethod() const;
    int getReminderStatus() const;
    int getSnoozeDuration() const;

};

#endif // SERVICECOUNTLISTDATA_H

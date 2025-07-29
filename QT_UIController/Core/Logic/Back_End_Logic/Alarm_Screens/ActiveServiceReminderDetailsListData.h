/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ActiveServiceReminderDetailsListData.h file provides alarm detail list container data
    handeled by ServiceReminderDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 08/10/2024 - Initial version.
***************************************************************************/
#ifndef ACTIVESERVICEREMINDERDETAILSLISTDATA_H
#define ACTIVESERVICEREMINDERDETAILSLISTDATA_H

#include <QString>
#include "AlarmLogStructure.h"
#include "ServiceReminderStructure.h"

class ActiveServiceReminderDetailsListData
{
public:

    ActiveServiceReminderDetailsListData();
    ActiveServiceReminderDetailsListData(const ALARM_IDS& p_ServiceReminderID, const int& p_ServiceReminderSubType, const bool& p_IsServiceReminderLogRequired,
                                         const QString& p_ServiceName, const int& p_SnoozeDuration);

private:

    ALARM_IDS m_ServiceReminderID;
    int m_ServiceReminderSubType;
    bool m_IsServiceReminderLogRequired;
    QString m_ServiceName;
    int m_SnoozeDuration;

public:

    ALARM_IDS getServiceReminderID() const;
    int getServiceReminderSubType() const;
    bool getIsServiceReminderLogRequired() const;
    QString getServiceName() const;
    int getSnoozeDuration() const;

};

#endif // ACTIVESERVICEREMINDERDETAILSLISTDATA_H

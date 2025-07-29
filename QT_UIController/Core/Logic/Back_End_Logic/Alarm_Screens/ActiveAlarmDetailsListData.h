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
#ifndef ACTIVEALARMDETAILSLISTDATA_H
#define ACTIVEALARMDETAILSLISTDATA_H

#include <QString>
#include "AlarmLogStructure.h"

class ActiveAlarmDetailsListData
{
public:

    ActiveAlarmDetailsListData();
    ActiveAlarmDetailsListData(const ALARM_IDS& p_AlarmID, const int& p_AlarmSubType, const bool& p_IsAlarmLogRequired, const QString& p_ServiceName);

private:

    ALARM_IDS m_AlarmID;
    int m_AlarmSubType;
    bool m_IsAlarmLogRequired;
    QString m_ServiceName;

public:

    ALARM_IDS getAlarmID() const;
    int getAlarmSubType() const;
    bool getIsAlarmLogRequired() const;
    QString getServiceName() const;

};

#endif // ACTIVEALARMDETAILSLISTDATA_H

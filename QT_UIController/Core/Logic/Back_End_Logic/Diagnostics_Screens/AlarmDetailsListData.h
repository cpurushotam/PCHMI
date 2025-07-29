/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AlarmDetailsListData.h file provides alarm detail list container data
    handeled by AlarmDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#ifndef ALARMDETAILSLISTDATA_H
#define ALARMDETAILSLISTDATA_H

#include <QString>
#include "AlarmLogStructure.h"

class AlarmDetailsListData
{
public:

    AlarmDetailsListData();
    AlarmDetailsListData(const int& p_ErrorType, const ALARM_IDS& p_AlarmID, const int& p_AlarmSubType, const int& p_RecipeNo,
                         const int& p_RecipeVersion, const int& p_CycleNo, const QString & p_CycleDateTime,
                         const QString& p_UserName, const int& p_AlarmType,  const QString& p_AddedNotes,  const int& p_AlarmLogIndex);

private:

    int m_ErrorType;
    ALARM_IDS m_AlarmID;
    int p_AlarmSubType;
    int m_RecipeNo;
    int m_RecipeVersion;
    int m_CycleNo;
    QString m_CycleDateTime;
    QString m_UserName;
    int m_AlarmType;
    QString m_AddedNotes;
    int m_AlarmLogIndex;

public:

    int getErrorType() const;
    ALARM_IDS getAlarmID() const;
    int getAlarmSubType() const;
    int getRecipeNo() const;
    int getRecipeVersion() const;
    int getCycleNo() const;
    QString getCycleDateTime() const;
    QString getUserName() const;
    int getAlarmType() const;
    QString getAddedNotes() const;
    int getAlarmLogIndex() const;

};

#endif // ALARMDETAILSLISTDATA_H

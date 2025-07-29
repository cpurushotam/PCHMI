/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps track for current system type configured.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 15/09/2023 - Initial version.
***************************************************************************/
#ifndef SYSTEMCONFIGURATION_H
#define SYSTEMCONFIGURATION_H

#include "SystemTypeDef.h"
#include <QObject>

/*SystemConfiguration class declaration*/
class SystemConfiguration : public QObject
{
private:
    Q_OBJECT

    Q_PROPERTY(int CurrentSystemType READ getCurrentSystemType NOTIFY CurrentSystemTypeChanged)

    Q_PROPERTY(int EventLogSupportSystemType READ getEventLogSupportSystemType NOTIFY EventLogSupportTypeChanged)
    Q_PROPERTY(int UserIOSupportSystemType READ getUserIOSupportSystemType NOTIFY UserIOSupportTypeChanged)
    Q_PROPERTY(int UserAccessLevelType READ getUserAccessLevelType NOTIFY UserAccessLevelTypeChanged)
    Q_PROPERTY(int BatchSettingSupportSystemType READ getBatchSettingSupportSystemType NOTIFY BatchSettingSupportTypeChanged)
    Q_PROPERTY(int FieldBusSupportSystemType READ getFieldBusSupportSystemType NOTIFY FieldBusSupportSystemTypeChanged)


    int m_CurrentSystemType;
    int m_EventLogSupportSystemType;
    int m_UserIOSupportSystemType;
    int m_UserAccessLevelType;
    int m_BatchSettingSupportSystemType;
    int m_FieldBusSupportSystemType;

public:

    explicit SystemConfiguration(QObject *parent = nullptr);

    int getCurrentSystemType() const;

    int getEventLogSupportSystemType() const;

    int getUserIOSupportSystemType() const;

    int getUserAccessLevelType() const;

    int getBatchSettingSupportSystemType() const;

    int getFieldBusSupportSystemType() const;

signals:

    void CurrentSystemTypeChanged();
    void EventLogSupportTypeChanged();
    void UserIOSupportTypeChanged();
    void UserAccessLevelTypeChanged();
    void BatchSettingSupportTypeChanged();
    void FieldBusSupportSystemTypeChanged();
};
#endif // SYSTEMCONFIGURATION_H

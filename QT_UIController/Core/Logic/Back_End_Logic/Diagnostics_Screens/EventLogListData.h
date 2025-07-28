/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    EventLogListData.h file provides Eventlog detail listmodel which is used by QMl.

***************************************************************************/
#ifndef EventLogListData_H
#define EventLogListData_H

#include <QString>

class EventLogListData
{
public:
    EventLogListData();
    EventLogListData(const int& p_EventIdx ,const int& p_EventId, const QString& p_ParameterId, const QString& p_DateTime, const QString& p_UserName, const QString & p_OldParameters,
                     const QString& p_NewParameters, const QString& p_SourceOfEvent, const QString& p_PsSerialNo, const QString& p_AcSerialNo ,
                     const QString & p_HMISerialNo , const QString&p_Comment);

private:

    int m_EventIdx;
    int m_EventID;
    QString  m_ParameterID;
    QString m_DateTime;
    QString m_UserName;
    QString m_OldParameters;
    QString m_NewParameters;
    QString m_SourceOfEvent;
    QString m_PSSerialNumber;
    QString m_ACSerialNumber;
    QString m_HMISerialNumber;
    QString m_Comment;

public:

    int getEventIndex() const;
    int getEventID() const;
    QString getParameterID() const;
    QString getDateTime() const;
    QString getUserName() const;
    QString getOldParameters() const;
    QString getNewParameters() const;
    QString getSourceOfEvent() const;
    QString getPSSerialNumber() const;
    QString getACSerialNumber() const;
    QString getHMISerialNumber() const;
    QString getComment() const;

    QString getEventType() const;
};

#endif // EventLogListData_H

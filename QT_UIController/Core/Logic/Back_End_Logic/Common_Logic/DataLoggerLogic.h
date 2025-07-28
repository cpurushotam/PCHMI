/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DataLogger related implementation
 ***************************************************************************/
#ifndef DATALOGGERLOGIC_H
#define DATALOGGERLOGIC_H

#include <QObject>
#include <QString>
#include <queue>
#include "DataLoggerManager.h"

class DataLoggerLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList DataLoggerList    READ getDataLoggerMessageList   NOTIFY dataLoggerMsgChanged)

public:
    explicit DataLoggerLogic(QObject *parent = nullptr);
    QStringList getDataLoggerMessageList();

signals:
    void dataLoggerMsgChanged();

private:
    DataLogger *DataLoggerPtr;
    std::queue<std::string> DataLoggerMsgQueue;
    QStringList DataLoggerMsgList;

private slots:
    void OnDataLoggerMessageUpdated(DataLogger *DataLogger_Obj, int WelderId);
};

#endif // DATALOGGERLOGIC_H

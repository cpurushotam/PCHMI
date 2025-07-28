/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

SoftwareUpgradeInterface class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef SOFTWARE_UPGRADE_H
#define SOFTWARE_UPGRADE_H

#include <QObject>
#include "SoftwareUpgradeStructure.h"
#include "UpdateScreens.h"

class SoftwareUpgradeInterface : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/

public:
    explicit SoftwareUpgradeInterface(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getSCFileNameList();
    Q_INVOKABLE QStringList getACFileNameList();
    Q_INVOKABLE QStringList getHMIFileNameList();
    Q_INVOKABLE SOFTWARE_UPGRADE_ERROR_CODES getSoftwareUpgradeErrorCode();

    Q_INVOKABLE void readUSBRequest();
    Q_INVOKABLE void softwareUpgradeRequest(QString SCUpgradeVersion, QString ACUpgradeVersion, QString HMIUpgradeVersion);

    // Signal to notify QML about updated values
signals:
    void softwareUpgradeReadUsbDataChanged();
    void softwareUpgradeErrorCodeUpdated();


private:
    /*Holds SoftwareUpgrade data*/
    SoftwareUpgrade *m_SoftwareUpgrade;
    QString m_SCFileName;
    QString m_ACFileName;
    QString m_HMIFileName;

    QStringList SCFileNameList;
    QStringList ACFileNameList;
    QStringList HMIFileNameList;
    int m_ActiveWelderId = -1;

    SOFTWARE_UPGRADE_ERROR_CODES m_SoftwareUpgradeResult;

private slots:
    void OnSoftwareUpgradeDataUpdated(SoftwareUpgrade *SoftwareUpgrade_Obj, int welderId);
};

#endif // SOFTWARE_UPGRADE_H



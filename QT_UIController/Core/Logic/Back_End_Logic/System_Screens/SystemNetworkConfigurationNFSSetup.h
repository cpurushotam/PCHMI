/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

System Network Configuration NFS Setup class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef SystemNetworkConfigurationNFSSetup_H
#define SystemNetworkConfigurationNFSSetup_H

#include <QObject>
#include "NfsManager.h"
#include "UpdateScreens.h"

class SystemNetworkConfigurationNFSSetup : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(QString NFSSetupIPAdress  READ getNFSSetupIPAdress NOTIFY networkConfigurationNFSDataChanged)
    Q_PROPERTY(QString NFSMountPath  READ getNFSMountPath  NOTIFY networkConfigurationNFSDataChanged)

public:
    explicit SystemNetworkConfigurationNFSSetup(QObject *parent = nullptr);

    Q_INVOKABLE void saveRequest(QString hostIp, QString mountPath);
    QString getNFSSetupIPAdress() const;
    QString getNFSMountPath() const;

    // Signal to notify QML about updated values
signals:
    void networkConfigurationNFSDataChanged();

private:

    NfsManager *m_NfsManagerPtr;
    int m_ActiveWelderId = -1;   // Active welder Id

    QString m_NFSSetupIPAdress; // NFS Setup IpAddress
    QString m_NFSMountPath;     // NFS Mount Path

    NfsConfig m_nfsConfiData;  //TO cache the data from QML.

private slots:
    void OnNetworkConfigurationNFSSetupUpdated(NfsManager *NfsManager_Obj, int welderId);
};

#endif // SystemNetworkConfigurationNFSSetup_H



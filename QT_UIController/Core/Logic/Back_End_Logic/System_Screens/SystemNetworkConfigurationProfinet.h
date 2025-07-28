/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

SystemNetworkConfigurationProfinet - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef SystemNetworkConfigurationProfinet_H
#define SystemNetworkConfigurationProfinet_H

#include <QObject>
#include "ProfinetStructure.h"
#include "UpdateScreens.h"
#include "ProfinetSetting.h"

class SystemNetworkConfigurationProfinet : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(QString StationName                 READ getStationName         WRITE updateStationName             NOTIFY profinetConfigurationDataChanged)
    Q_PROPERTY(QString IpAddress                   READ getIpAddress           WRITE updateIpAddress               NOTIFY profinetConfigurationDataChanged)
    Q_PROPERTY(QString Netmask                     READ getNetmask             WRITE updateNetmask                 NOTIFY profinetConfigurationDataChanged)
    Q_PROPERTY(QString Gateway                     READ getGateway             WRITE updateGateway                 NOTIFY profinetConfigurationDataChanged)


public:
    explicit SystemNetworkConfigurationProfinet(QObject *parent = nullptr);

    Q_INVOKABLE void saveRequest();
    Q_INVOKABLE void resetToDefaultRequest();
    Q_INVOKABLE void cancelRequest();
    Q_INVOKABLE void updateProfinetDetails(QString IPAdress, QString NetMask, QString Gateway, QString StationName);

    QString getStationName() const;
    void updateStationName(const QString &newStationName);

    QString getIpAddress() const;
    void updateIpAddress(const QString &newIpAddress);

    QString getNetmask() const;
    void updateNetmask(const QString &newNetmask);

    QString getGateway() const;
    void updateGateway(const QString &newGateway);

    // Signal to notify QML about updated values
signals:
    void profinetConfigurationDataChanged();

private:
    /*Holds Profinet data*/
    ProfinetSetting *m_ProfinetSettingPtr;

    /*Holds System Network Configuration Profinet updated data from HMI*/
    ProfinetSettingsStruct m_ProfinetSettingsStructCopy;

    int m_ActiveWelderId = -1; //Active welder ID

    QString m_StationName;
    QString m_IpAddress;
    QString m_Netmask;
    QString m_Gateway;

private slots:
    void OnSystemNetworkConfigurationProfinetUpdated(ProfinetSetting *ProfinetSetting_Obj, int welderId);
};

#endif // SystemNetworkConfigurationProfinet_H



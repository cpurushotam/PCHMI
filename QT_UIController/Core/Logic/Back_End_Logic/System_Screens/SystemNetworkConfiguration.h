/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

System Network Configuration class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef NetworkConfiguration_H
#define NetworkConfiguration_H

#include <QObject>
#include "NetworkConfigStructure.h"
#include "NetworkConfiguration.h"
#include "UpdateScreens.h"

class SystemNetworkConfiguration : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(bool EthernetIPConfig  READ getEthernetIPConfig  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString EthernetIPAdress  READ getEthernetIPAdress NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString EthernetSubnetMask  READ getEthernetSubnetMask  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString EthernetDefaultGateway  READ getEthernetDefaultGateway NOTIFY networkConfigurationDataChanged)

public:
    explicit SystemNetworkConfiguration(QObject *parent = nullptr);

    bool getEthernetIPConfig() const;

    QString getEthernetIPAdress() const;
    QString getEthernetSubnetMask() const;
    void updateEthernetSubnetMask(QString EthernetSubnetMask);
    QString getEthernetDefaultGateway() const;
    void updateEthernetDefaultGateway(QString EthernetDefaultGateway);

    Q_INVOKABLE void saveRequest();
    Q_INVOKABLE void resetToDefaultRequest();
    Q_INVOKABLE void cancelRequest();

    Q_INVOKABLE NETWORK_CONFIG_ERROR_CODES getNetworkConfigUpdateResult();
    Q_INVOKABLE void updateEthernetIPConfigStatus(int EthernetIPConfigStatus);
    Q_INVOKABLE void updateEthernetIPSetup(QString EthernetIPAdress, QString EthernetSubnetMask, QString EthernetDefaultGateway);

    // Signal to notify QML about updated values
signals:
    void networkConfigurationDataChanged();
    void networkConfigurationErrorCodeUpdated();


private:
    /*Holds System Network Configuration data*/
    NetworkConfiguration *m_SystemNetworkConfiguration;

    /*Holds System Network Configuration updated data from HMI*/
    NetworkConfigurationStruct m_SystemNetworkConfigurationCopy;

    NETWORK_CONFIG_ERROR_CODES m_SysNetworkConfigUpdateResult;
    int m_ActiveWelderId = -1;

    ETHERNET_IP_SETUP_STATUS m_EthernetIPConfig;
    QString m_EthernetIPAdress;
    QString m_EthernetSubnetMask;
    QString m_EthernetDefaultGateway;

private slots:
    void OnNetworkConfigurationUpdated(NetworkConfiguration *NetworkConfiguration_Obj, int welderId);
};

#endif // NetworkConfiguration_H



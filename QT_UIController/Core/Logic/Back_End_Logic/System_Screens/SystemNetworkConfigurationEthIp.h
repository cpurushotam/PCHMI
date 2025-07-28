/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

System Network Configuration Industrail EthernetIp class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef SystemNetworkConfigurationEthIp_H
#define SystemNetworkConfigurationEthIp_H

#include <QObject>
#include "NetworkConfigStructure.h"
#include "NetworkConfigurationEthernetIp.h"
#include "UpdateScreens.h"

class SystemNetworkConfigurationEthIp : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(bool InduEthernetIPConfig  READ getIndustrialEthernetIPConfig  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString InduEthernetIPAdress  READ getIndustrialEthernetIPAddress  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString InduEthernetSubnetMask  READ getIndustrialEthernetSubnetMask  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString InduEthernetDefaultGateway  READ getIndustrialEthernetDefaultGateway NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString NameServer  READ getNameServer  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString NameServer2  READ getNameServer2  NOTIFY networkConfigurationDataChanged)
    Q_PROPERTY(QString DomainName  READ getDomainName  NOTIFY networkConfigurationDataChanged)

public:
    explicit SystemNetworkConfigurationEthIp(QObject *parent = nullptr);

    bool getIndustrialEthernetIPConfig() const;
    QString getIndustrialEthernetIPAddress() const;
    QString getIndustrialEthernetSubnetMask() const;
    QString getIndustrialEthernetDefaultGateway() const;

    QString getNameServer() const;
    QString getNameServer2() const;
    QString getDomainName() const;

    Q_INVOKABLE void saveRequest();
    Q_INVOKABLE void resetToDefaultRequest();
    Q_INVOKABLE void cancelRequest();

    Q_INVOKABLE NETWORK_CONFIG_ERROR_CODES getNetworkConfigUpdateResult();
    Q_INVOKABLE void updateInduEthernetIPConfigStatus(int InduEthernetIPConfigStatus);
    Q_INVOKABLE void updateIndustrialEthernetIP(QString InduEthernetIPAdress, QString IndustrialEthernetSubnetMask, QString IndustrialEthernetDefaultGateway);
    Q_INVOKABLE void updateIndustrialServerAndDomainName(QString NameServer, QString NameServer2, QString DomainName);

    // Signal to notify QML about updated values
signals:
    void networkConfigurationDataChanged();
    void networkConfigurationErrorCodeUpdated();


private:
    /*Holds System Network Configuration data*/
    NetworkConfigurationEthernetIp *m_SystemNetworkConfiguration;

    /*Holds System Network Configuration updated data from HMI*/
    NetworkConfigurationEthernetIpStruct m_SystemNetworkConfigurationCopy;

    NETWORK_CONFIG_ERROR_CODES m_SysNetworkConfigUpdateResult;
    int m_ActiveWelderId = -1;

    ETHERNET_IP_SETUP_STATUS m_EthernetIPConfig;
    QString m_EthernetIPAdress;
    QString m_EthernetSubnetMask;
    QString m_EthernetDefaultGateway;

    INDUSTRIAL_ETHERNET_IP_SETUP_STATUS m_IndustrialEthernetIPConfig;
    QString m_IndustrialEthernetIPAddress;
    QString m_IndustrialEthernetSubnetMask;
    QString m_IndustrialEthernetDefaultGateway;
    QString m_NameServer;
    QString m_NameServer2;
    QString m_DomainName;

private slots:
    void OnNetworkConfigurationIndEthEipUpdated(NetworkConfigurationEthernetIp *NetworkConfiguration_Obj, int welderId);
};

#endif // SystemNetworkConfigurationEthIp_H



/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2025

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
System Network Configuration ETH ip class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "SystemNetworkConfigurationEthIp.h"

/**************************************************************************//**
*
* \brief  - SystemNetworkConfigurationEthIp Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SystemNetworkConfigurationEthIp::SystemNetworkConfigurationEthIp(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SysNetworkConfgIndusEthIpDataUpdated, this, &SystemNetworkConfigurationEthIp::OnNetworkConfigurationIndEthEipUpdated);
}

/**************************************************************************//**
*
* \brief  - Return Industrial Ethernet IP Config
*
* \param  - None.
*
* \return - bool - return true if INDU_ETHERNET_STATIC_IP_ENABLED else return false.
*
******************************************************************************/
bool SystemNetworkConfigurationEthIp::getIndustrialEthernetIPConfig() const
{
    if(m_IndustrialEthernetIPConfig == INDU_ETHERNET_STATIC_IP_ENABLED)
        return true;
    else
        return false;
}
/**************************************************************************//**
*
* \brief  - Update Ethernet IP Adress
*
* \param  - QString EthernetIPAdress -  Ethernet IP Adress to be update
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::updateInduEthernetIPConfigStatus(int InduEthernetIPConfigStatus)
{
    if(InduEthernetIPConfigStatus == INDU_ETHERNET_STATIC_IP_ENABLED)
    {
        m_IndustrialEthernetIPConfig = INDU_ETHERNET_STATIC_IP_ENABLED;
    }
    else if (InduEthernetIPConfigStatus == INDU_ETHERNET_DHCP_CLIENT_ENABLED)
    {
        m_IndustrialEthernetIPConfig = INDU_ETHERNET_DHCP_CLIENT_ENABLED;
    }
}

/**************************************************************************//**
*
* \brief  - Return Industrial Ethernet IP Adress
*
* \param  - None.
*
* \return - QString Industrial Ethernet IP Adress.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getIndustrialEthernetIPAddress() const
{
    return m_IndustrialEthernetIPAddress;
}

/**************************************************************************//**
*
* \brief  - Return Industrial Ethernet SubnetMask
*
* \param  - None.
*
* \return - QString m_EthernetSubnetMask.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getIndustrialEthernetSubnetMask() const
{
    return m_IndustrialEthernetSubnetMask;
}

/**************************************************************************//**
*
* \brief  - Return Industrial Ethernet DefaultGateway
*
* \param  - None.
*
* \return - QString m_IndustrialEthernetDefaultGateway.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getIndustrialEthernetDefaultGateway() const
{
    return m_IndustrialEthernetDefaultGateway;
}

/**************************************************************************//**
*
* \brief  - Return name server
*
* \param  - None.
*
* \return - QString - error code.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getNameServer()const
{
    return m_NameServer;
}

/**************************************************************************//**
*
* \brief  - Return name server2
*
* \param  - None.
*
* \return - QString m_NameServer2.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getNameServer2() const
{
    return m_NameServer2;
}

/**************************************************************************//**
*
* \brief  - Return domain name
*
* \param  - None.
*
* \return - QString m_DomainName.
*
******************************************************************************/
QString SystemNetworkConfigurationEthIp::getDomainName() const
{
    return m_DomainName;
}

/**************************************************************************//**
*
* \brief  - Return data updated in db error code
*
* \param  - None.
*
* \return - NETWORK_CONFIG_ERROR_CODES - error code.
*
******************************************************************************/
NETWORK_CONFIG_ERROR_CODES SystemNetworkConfigurationEthIp::getNetworkConfigUpdateResult()
{
    return m_SysNetworkConfigUpdateResult;
}

/**************************************************************************//**
*
* \brief  - Update Industrial Ethernet parameters value
*
* \param  - QString InduEthernetIPAdress -  Industrial Ethernet IP Adress to be update
*           QString IndustrialEthernetSubnetMask - Industrial Ethernet subnet mask to be update
*           QString IndustrialEthernetDefaultGateway -  Industrial Ethernet Default Gateway to be update
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::updateIndustrialEthernetIP(QString InduEthernetIPAdress, QString IndustrialEthernetSubnetMask, QString IndustrialEthernetDefaultGateway)
{
    strncpy(m_SystemNetworkConfigurationCopy.IndustrialEthernetIPAddress,m_IndustrialEthernetIPAddress.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IndustrialEthernetIPAddress));
    strncpy(m_SystemNetworkConfigurationCopy.IndustrialEthernetSubnetMask,m_IndustrialEthernetIPAddress.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IndustrialEthernetSubnetMask));
    strncpy(m_SystemNetworkConfigurationCopy.IndustrialEthernetDefaultGateway,m_IndustrialEthernetIPAddress.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IndustrialEthernetDefaultGateway));
    m_IndustrialEthernetIPAddress = InduEthernetIPAdress;
    m_IndustrialEthernetSubnetMask = IndustrialEthernetSubnetMask;
    m_IndustrialEthernetDefaultGateway = IndustrialEthernetDefaultGateway;
}

/**************************************************************************//**
*
* \brief  - Update Industrial Ethernet parameters value
*
* \param  - QString NameServer -  Name Server to be update
*           QString NameServer2 - Name Server2 to be update
*           QString DomainName -  Domain Name to be update
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::updateIndustrialServerAndDomainName(QString NameServer, QString NameServer2, QString DomainName)
{
    strncpy(m_SystemNetworkConfigurationCopy.NameServer,m_NameServer.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.NameServer));
    strncpy(m_SystemNetworkConfigurationCopy.NameServer2,m_NameServer2.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.NameServer2));
    strncpy(m_SystemNetworkConfigurationCopy.DomainName,m_DomainName.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.DomainName));
    m_NameServer = NameServer;
    m_NameServer2 = NameServer2;
    m_DomainName = DomainName;
}
/**************************************************************************//**
*
* \brief  - systemNetworkConfigurationEthIp save request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::saveRequest()
{
    NetworkConfigurationEthernetIpStruct networkConfigurationData;
    networkConfigurationData.IndustrialEthernetIPConfig = m_IndustrialEthernetIPConfig;
    strncpy(networkConfigurationData.IndustrialEthernetIPAddress,m_IndustrialEthernetIPAddress.toStdString().c_str(),sizeof(networkConfigurationData.IndustrialEthernetIPAddress));
    strncpy(networkConfigurationData.IndustrialEthernetSubnetMask,m_IndustrialEthernetSubnetMask.toStdString().c_str(),sizeof(networkConfigurationData.IndustrialEthernetSubnetMask));
    strncpy(networkConfigurationData.IndustrialEthernetDefaultGateway,m_IndustrialEthernetDefaultGateway.toStdString().c_str(),sizeof(networkConfigurationData.IndustrialEthernetDefaultGateway));

    strncpy(networkConfigurationData.NameServer,m_NameServer.toStdString().c_str(),sizeof(networkConfigurationData.NameServer));
    strncpy(networkConfigurationData.NameServer2,m_NameServer2.toStdString().c_str(),sizeof(networkConfigurationData.NameServer2));
    strncpy(networkConfigurationData.DomainName,m_DomainName.toStdString().c_str(),sizeof(networkConfigurationData.DomainName));
    m_SystemNetworkConfiguration->InitiateNetworkConfigurationEthernetIpUpdateRequest(networkConfigurationData);
}

/**************************************************************************//**
*
* \brief  - SystemNetworkConfigurationEthIp reset to default request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::resetToDefaultRequest()
{
    m_SystemNetworkConfiguration->InitiateNetworkConfigurationEthernetIpResetRequest();
}

/**************************************************************************//**
*
* \brief  - Revert back to previously saved values on HMI when cancel button is pressed
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationEthIp::cancelRequest()
{
    m_IndustrialEthernetIPConfig =  m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().IndustrialEthernetIPConfig;
    m_IndustrialEthernetIPAddress = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().IndustrialEthernetIPAddress);
    m_IndustrialEthernetSubnetMask = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().IndustrialEthernetSubnetMask);
    m_IndustrialEthernetDefaultGateway = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().IndustrialEthernetDefaultGateway);
    m_NameServer = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().NameServer);
    m_NameServer2 = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().NameServer2);
    m_DomainName = QString::fromUtf8( m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData().DomainName);

    emit networkConfigurationDataChanged();
}
/**************************************************************************//**
*
* \brief  - Role of the slot OnNetworkConfigurationIndEthEipUpdated is to update values on System network Config screen.
*
* \param  - NetworkConfigurationEth_Obj : Object pointer of type NetworkConfigurationEthernetIp.
*           welderId : welder id
*
* \return - None.
*
**************************************************7****************************/
void SystemNetworkConfigurationEthIp::OnNetworkConfigurationIndEthEipUpdated(NetworkConfigurationEthernetIp *NetworkConfigurationEth_Obj, int welderId)
{
    m_SystemNetworkConfiguration = NetworkConfigurationEth_Obj;
    if(m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpUpdateStatus() || m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpReadData()
        ||m_ActiveWelderId != welderId)
    {
        NetworkConfigurationEthernetIpStruct NetworkConfigurationStructUpdatedData;
        if(m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpUpdateStatus() == true)
        {
            m_SysNetworkConfigUpdateResult = m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpUpdatedErrorCode();
            emit networkConfigurationErrorCodeUpdated();
        }
        if(m_SysNetworkConfigUpdateResult != UPDATE_NETWORK_CONFIG_FAIL || m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpReadData() == true)
        {
            NetworkConfigurationStructUpdatedData = m_SystemNetworkConfiguration->GetNetworkConfigurationEthernetIpData();
        }
        else
        {
            memcpy(&NetworkConfigurationStructUpdatedData,&m_SystemNetworkConfigurationCopy,sizeof(m_SystemNetworkConfigurationCopy));
            m_SystemNetworkConfiguration->ResetNetworkConfigurationEthernetIpUpdateStatus();
        }

        m_IndustrialEthernetIPConfig = NetworkConfigurationStructUpdatedData.IndustrialEthernetIPConfig;
        m_IndustrialEthernetIPAddress = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IndustrialEthernetIPAddress);
        m_IndustrialEthernetSubnetMask = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IndustrialEthernetSubnetMask);
        m_IndustrialEthernetDefaultGateway = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IndustrialEthernetDefaultGateway);
        m_NameServer = QString::fromUtf8(NetworkConfigurationStructUpdatedData.NameServer);
        m_NameServer2 = QString::fromUtf8(NetworkConfigurationStructUpdatedData.NameServer2);
        m_DomainName = QString::fromUtf8(NetworkConfigurationStructUpdatedData.DomainName);

        m_ActiveWelderId = welderId;
        emit networkConfigurationDataChanged();
    }
}

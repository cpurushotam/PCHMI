/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
System Network Configuration class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "SystemNetworkConfiguration.h"

/**************************************************************************//**
*
* \brief  - System Network Configuration Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SystemNetworkConfiguration::SystemNetworkConfiguration(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SysNetworkConfgDataUpdated, this, &SystemNetworkConfiguration::OnNetworkConfigurationUpdated);
}


/**************************************************************************//**
*
* \brief  - Return Ethernet IP Config
*
* \param  - None.
*
* \return - bool - return true if ETHERNET_STATIC_IP_ENABLED else return false.
*
******************************************************************************/
bool SystemNetworkConfiguration::getEthernetIPConfig() const
{
    if(m_EthernetIPConfig == ETHERNET_STATIC_IP_ENABLED)
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
void SystemNetworkConfiguration::updateEthernetIPConfigStatus(int EthernetIPConfigStatus)
{
    if(EthernetIPConfigStatus == ETHERNET_STATIC_IP_ENABLED)
    {
        m_EthernetIPConfig = ETHERNET_STATIC_IP_ENABLED;
    }
    else if (EthernetIPConfigStatus == ETHERNET_DHCP_CLIENT_ENABLED)
    {
        m_EthernetIPConfig = ETHERNET_DHCP_CLIENT_ENABLED;
    }
}

/**************************************************************************//**
*
* \brief  - Return Ethernet IP Adress
*
* \param  - None.
*
* \return - QString m_EthernetIPAdress.
*
******************************************************************************/
QString SystemNetworkConfiguration::getEthernetIPAdress() const
{
    return m_EthernetIPAdress;
}

/**************************************************************************//**
*
* \brief  - Return Ethernet SubnetMask
*
* \param  - None.
*
* \return - QString m_EthernetSubnetMask.
*
******************************************************************************/
QString SystemNetworkConfiguration::getEthernetSubnetMask() const
{
    return m_EthernetSubnetMask;
}

/**************************************************************************//**
*
* \brief  - Return Ethernet DefaultGateway
*
* \param  - None.
*
* \return - QString m_EthernetDefaultGateway.
*
******************************************************************************/
QString SystemNetworkConfiguration::getEthernetDefaultGateway() const
{
    return m_EthernetDefaultGateway;
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
NETWORK_CONFIG_ERROR_CODES SystemNetworkConfiguration::getNetworkConfigUpdateResult()
{
    return m_SysNetworkConfigUpdateResult;
}

/**************************************************************************//**
*
* \brief  - Update Ethernet IP Adress
*
* \param  - QString EthernetIPAdress -  Ethernet IP Adress to be update
*           QString EthernetSubnetMask -  Ethernet Subnet Mask to be update
*           QString EthernetDefaultGateway -  Ethernet Default Gateway to be update
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfiguration::updateEthernetIPSetup(QString EthernetIPAdress, QString EthernetSubnetMask, QString EthernetDefaultGateway)
{
    strncpy(m_SystemNetworkConfigurationCopy.IpSetupIPAdress,m_EthernetIPAdress.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IpSetupIPAdress));
    strncpy(m_SystemNetworkConfigurationCopy.IpSetupSubnetMask,m_EthernetSubnetMask.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IpSetupSubnetMask));
    strncpy(m_SystemNetworkConfigurationCopy.IpSetupDefaultGateway,m_EthernetDefaultGateway.toStdString().c_str(),sizeof(m_SystemNetworkConfigurationCopy.IpSetupDefaultGateway));
    m_EthernetIPAdress = EthernetIPAdress;
    m_EthernetSubnetMask = EthernetSubnetMask;
    m_EthernetDefaultGateway = EthernetDefaultGateway;
}

/**************************************************************************//**
*
* \brief  - send Network configuration save request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfiguration::saveRequest()
{
    NetworkConfigurationStruct networkConfigurationData;
    networkConfigurationData.IpSetupIPConfig = m_EthernetIPConfig;
    strncpy(networkConfigurationData.IpSetupIPAdress,m_EthernetIPAdress.toStdString().c_str(),sizeof(networkConfigurationData.IpSetupIPAdress));
    strncpy(networkConfigurationData.IpSetupSubnetMask,m_EthernetSubnetMask.toStdString().c_str(),sizeof(networkConfigurationData.IpSetupSubnetMask));
    strncpy(networkConfigurationData.IpSetupDefaultGateway,m_EthernetDefaultGateway.toStdString().c_str(),sizeof(networkConfigurationData.IpSetupDefaultGateway));
    m_SystemNetworkConfiguration->InitiateNetworkConfigurationUpdateRequest(networkConfigurationData);
}

/**************************************************************************//**
*
* \brief  - send Network Config reset to default request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfiguration::resetToDefaultRequest()
{
    m_SystemNetworkConfiguration->InitiateNetworkConfigurationResetRequest();
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
void SystemNetworkConfiguration::cancelRequest()
{
    m_EthernetIPConfig = m_SystemNetworkConfiguration->GetNetworkConfigurationData().IpSetupIPConfig;
    m_EthernetIPAdress = QString::fromUtf8(m_SystemNetworkConfiguration->GetNetworkConfigurationData().IpSetupIPAdress);
    m_EthernetSubnetMask = QString::fromUtf8(m_SystemNetworkConfiguration->GetNetworkConfigurationData().IpSetupSubnetMask);
    m_EthernetDefaultGateway = QString::fromUtf8(m_SystemNetworkConfiguration->GetNetworkConfigurationData().IpSetupDefaultGateway);
    emit networkConfigurationDataChanged();
}
/**************************************************************************//**
*
* \brief  - Role of the slot OnNetworkConfigurationUpdated is to update values on System network Config screen.
*
* \param  - NetworkConfiguration_Obj : Object pointer of type NetworkConfiguration.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfiguration::OnNetworkConfigurationUpdated(NetworkConfiguration *NetworkConfiguration_Obj, int welderId)
{

    m_SystemNetworkConfiguration = NetworkConfiguration_Obj;

    if((m_SystemNetworkConfiguration->GetNetworkConfigurationUpdateStatus() )|| (m_SystemNetworkConfiguration->GetNetworkConfigurationReadData())
        || (m_ActiveWelderId != welderId))
    {

        NetworkConfigurationStruct NetworkConfigurationStructUpdatedData;
        if(m_SystemNetworkConfiguration->GetNetworkConfigurationUpdateStatus() == true)
        {
            m_SysNetworkConfigUpdateResult = m_SystemNetworkConfiguration->GetNetworkConfigurationUpdatedErrorCode();
            emit networkConfigurationErrorCodeUpdated();
        }
        if(m_SysNetworkConfigUpdateResult != UPDATE_NETWORK_CONFIG_FAIL || m_SystemNetworkConfiguration->GetNetworkConfigurationReadData() == true)
        {
            NetworkConfigurationStructUpdatedData = m_SystemNetworkConfiguration->GetNetworkConfigurationData();
        }
        else
        {
            memcpy(&NetworkConfigurationStructUpdatedData,&m_SystemNetworkConfigurationCopy,sizeof(m_SystemNetworkConfigurationCopy));
            m_SystemNetworkConfiguration->ResetNetworkConfigurationUpdateStatus();
        }

        m_EthernetIPConfig = NetworkConfigurationStructUpdatedData.IpSetupIPConfig;
        m_EthernetIPAdress = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IpSetupIPAdress);

        m_EthernetSubnetMask = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IpSetupSubnetMask);
        m_EthernetDefaultGateway = QString::fromUtf8(NetworkConfigurationStructUpdatedData.IpSetupDefaultGateway);


        m_ActiveWelderId = welderId;
        emit networkConfigurationDataChanged();
    }
}

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2025

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
SystemNetworkConfigurationProfinet  class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "SystemNetworkConfigurationProfinet.h"

/**************************************************************************//**
*
* \brief  - SystemNetworkConfigurationProfinet Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SystemNetworkConfigurationProfinet::SystemNetworkConfigurationProfinet(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SysNetworkConfgProfinetDataUpdated, this, &SystemNetworkConfigurationProfinet::OnSystemNetworkConfigurationProfinetUpdated);
}

/**************************************************************************//**
*
* \brief  - Update Profinet parameters value
*
* \param  - QString IPAddress -    IP Adress to be update
*           QString SubnetMask -  Ethernet subnet mask to be update
*           QString DefaultGateway -    Default Gateway to be update
**          QString StationName -    StationName  to be update

* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::updateProfinetDetails(QString IPAdress, QString NetMask, QString Gateway, QString StationName)
{
    strncpy( m_ProfinetSettingsStructCopy.StationName, StationName.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.StationName));
    m_StationName = StationName;
    strncpy( m_ProfinetSettingsStructCopy.IpAddress, IPAdress.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.IpAddress));
    m_IpAddress = IPAdress;
    strncpy( m_ProfinetSettingsStructCopy.Netmask, NetMask.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.Netmask));
    m_Netmask = NetMask;
    strncpy( m_ProfinetSettingsStructCopy.Gateway, Gateway.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.Gateway));
    m_Gateway = Gateway;
}

/**************************************************************************//**
*
* \brief  -  To initaite SAve  request form HMI to ASC
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::saveRequest()
{
    m_ProfinetSettingPtr->InitiateProfinetSettingsUpdateRequest(m_ProfinetSettingsStructCopy);
}

/**************************************************************************//**
*
* \brief  - To initaite reset to default request form HMI to ASC
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::resetToDefaultRequest()
{
    m_ProfinetSettingPtr-> InitiateRestToDefaultRequest();
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
void SystemNetworkConfigurationProfinet::cancelRequest()
{
    m_ProfinetSettingsStructCopy = m_ProfinetSettingPtr->GetProfinetSettingsStruct();
    m_IpAddress =  QString::fromUtf8(m_ProfinetSettingsStructCopy.IpAddress);
    m_Netmask =  QString::fromUtf8(m_ProfinetSettingsStructCopy.Netmask);
    m_Gateway =  QString::fromUtf8(m_ProfinetSettingsStructCopy.Gateway);
    m_StationName =  QString::fromUtf8(m_ProfinetSettingsStructCopy.StationName);
    emit profinetConfigurationDataChanged();
}
/**************************************************************************//**
*
* \brief  - Role of the slot OnSystemNetworkConfigurationProfinetUpdated is to update values on System network Config Profinet screen.
*
* \param  - ProfinetSetting_Obj : Object pointer of type ProfinetSetting.
*           welderId : welder id
*
* \return - None.
*
**************************************************7****************************/
void SystemNetworkConfigurationProfinet::OnSystemNetworkConfigurationProfinetUpdated(ProfinetSetting *ProfinetSetting_Obj, int welderId)
{
    m_ProfinetSettingPtr = ProfinetSetting_Obj;

    if(m_ProfinetSettingPtr->GetIsProfinetDataAvailable() || m_ActiveWelderId != welderId)
    {
        m_ProfinetSettingsStructCopy = m_ProfinetSettingPtr->GetProfinetSettingsStruct();
        m_IpAddress =  QString::fromUtf8(m_ProfinetSettingsStructCopy.IpAddress);
        m_Netmask =  QString::fromUtf8(m_ProfinetSettingsStructCopy.Netmask);
        m_Gateway =  QString::fromUtf8(m_ProfinetSettingsStructCopy.Gateway);
        m_StationName =  QString::fromUtf8(m_ProfinetSettingsStructCopy.StationName);
        m_ProfinetSettingPtr->SetIsProfinetDataAvailable();
        emit profinetConfigurationDataChanged();
        m_ActiveWelderId = welderId;
    }
}

/**************************************************************************//**
*
* \brief  - To get stationName on HMI
*
* \param  - None.
*
* \return - m_StationName.
*
******************************************************************************/
QString SystemNetworkConfigurationProfinet::getStationName() const
{
    return m_StationName;
}

/**************************************************************************//**
*
* \brief  - Update stationName from HMI
*
* \param  - newStationName - stationName entered from HMI.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::updateStationName(const QString &newStationName)
{
    if (m_StationName != newStationName)
    {
        strncpy( m_ProfinetSettingsStructCopy.StationName, newStationName.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.StationName));

        m_StationName = newStationName;
    }
}

/**************************************************************************//**
*
* \brief  - To get IpAddress on HMI
*
* \param  - None.
*
* \return - m_IpAddress.
*
******************************************************************************/
QString SystemNetworkConfigurationProfinet::getIpAddress() const
{
    return m_IpAddress;
}

/**************************************************************************//**
*
* \brief  - Update IPAddress from HMI
*
* \param  - newIpAddress - IpAddress entered from HMI.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::updateIpAddress(const QString &newIpAddress)
{
    if (m_IpAddress != newIpAddress)
    {
        strncpy( m_ProfinetSettingsStructCopy.IpAddress, newIpAddress.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.IpAddress));
        m_IpAddress = newIpAddress;
    }
}

/**************************************************************************//**
*
* \brief  - To get Netmask on HMI
*
* \param  - None.
*
* \return - m_Netmask.
*
******************************************************************************/
QString SystemNetworkConfigurationProfinet::getNetmask() const
{
    return m_Netmask;
}

/**************************************************************************//**
*
* \brief  - Update Netmask from HMI
*
* \param  - newNetmask - Netmask entered from HMI.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::updateNetmask(const QString &newNetmask)
{
    if (m_Netmask != newNetmask)
    {
        strncpy( m_ProfinetSettingsStructCopy.Netmask, newNetmask.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.Netmask));
        m_Netmask = newNetmask;
    }
}

/**************************************************************************//**
*
* \brief  - To get Gateway on HMI
*
* \param  - None.
*
* \return - m_Gateway.
*
******************************************************************************/
QString SystemNetworkConfigurationProfinet::getGateway() const
{
    return m_Gateway;
}


/**************************************************************************//**
*
* \brief  - Update Gateway from HMI
*
* \param  - newGateway - Gateway entered from HMI.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationProfinet::updateGateway(const QString &newGateway)
{
    if (m_Gateway != newGateway)
    {
        strncpy( m_ProfinetSettingsStructCopy.Gateway, newGateway.toStdString().c_str(), sizeof(m_ProfinetSettingsStructCopy.Gateway));
        m_Gateway = newGateway;
    }
}

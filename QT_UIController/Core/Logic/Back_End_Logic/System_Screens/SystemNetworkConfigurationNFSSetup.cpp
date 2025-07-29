/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2025

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
System Network Configuration NFS SETUP bclass which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "SystemNetworkConfigurationNFSSetup.h"

/**************************************************************************//**
*
* \brief  - System Network Configuration NFS Setup Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SystemNetworkConfigurationNFSSetup::SystemNetworkConfigurationNFSSetup(QObject *parent) : QObject(parent)
{
   connect(UpdateScreen::getInstance(), &UpdateScreen::SysNetworkConfgNFSDataUpdated, this, &SystemNetworkConfigurationNFSSetup::OnNetworkConfigurationNFSSetupUpdated);
}

/**************************************************************************//**
*
* \brief  - send Network configuration  NFS Setup save request to Memory Block
*
* \param  - hostIp - NFS Host IP Address, mountPath - NFS mount path.
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationNFSSetup::saveRequest(QString hostIp, QString mountPath)
{
    strncpy(m_nfsConfiData.hostIp,hostIp.toStdString().c_str(),sizeof(m_nfsConfiData.hostIp));
    strncpy(m_nfsConfiData.exportPath,mountPath.toStdString().c_str(),sizeof(m_nfsConfiData.exportPath));
    m_NfsManagerPtr->InitiateNfsMountRequest(m_nfsConfiData);
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnNetworkConfigurationNFSSetupUpdated is to update values on System network Config  nfs setup screen.
*
* \param  - NfsManager_Obj : Object pointer of type NfsManager.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void SystemNetworkConfigurationNFSSetup::OnNetworkConfigurationNFSSetupUpdated(NfsManager *NfsManager_Obj, int welderId)
{
    m_NfsManagerPtr = NfsManager_Obj;
    m_ActiveWelderId = welderId;
}

/**************************************************************************//**
*
* \brief  - To get the nfsSetupIpAddress to qml.
*
* \param  - None.
*
* \return - m_NFSSetupIPAdress - IP Address.
*
******************************************************************************/
QString SystemNetworkConfigurationNFSSetup::getNFSSetupIPAdress() const
{
    return m_NFSSetupIPAdress;
}

/**************************************************************************//**
*
* \brief  - To get the nfs mount path to QML
*
* \param  - None.
*
* \return - m_NFSMountPath - NFs Mount path.
*
******************************************************************************/
QString SystemNetworkConfigurationNFSSetup::getNFSMountPath() const
{
    return m_NFSMountPath;
}

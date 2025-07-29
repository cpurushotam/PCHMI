/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares SoftwareUpgradeInterface class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include <string>
#include "SoftwareUpgradeInterface.h"

/**************************************************************************//**
*
* \brief  - Software Upgrade Interface Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
SoftwareUpgradeInterface::SoftwareUpgradeInterface(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SoftwareUpgradeDataUpdated, this, &SoftwareUpgradeInterface::OnSoftwareUpgradeDataUpdated);
}

/**************************************************************************//**
*
* \brief  - Return SC File Name List
*
* \param  - None.
*
* \return - QStringList SCFileNameList.
*
******************************************************************************/
QStringList SoftwareUpgradeInterface::getSCFileNameList()
{
    return SCFileNameList;
}

/**************************************************************************//**
*
* \brief  - Return AC File Name List
*
* \param  - None.
*
* \return - QStringList SCFileNameList.
*
******************************************************************************/
QStringList SoftwareUpgradeInterface::getACFileNameList()
{
    return ACFileNameList;
}

/**************************************************************************//**
*
* \brief  - Return HMI File Name List
*
* \param  - None.
*
* \return - QStringList SCFileNameList.
*
******************************************************************************/
QStringList SoftwareUpgradeInterface::getHMIFileNameList()
{
    return HMIFileNameList;
}
/**************************************************************************//**
*
* \brief  - send read USB Request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void SoftwareUpgradeInterface::readUSBRequest()
{
    m_SoftwareUpgrade->InitiateSoftwareUpgradeReadUSBRequest();
}

/**************************************************************************//**
*
* \brief  - send software UpgradeR equest to Memory Block
*
* \param  - SCUpgradeVersion - SCFileName to upgrade.
*           ACUpgradeVersion - ACFileName to upgrade.
*           HMIUpgradeVersion - HMIFileName to upgrade.
*
* \return - None.
*
******************************************************************************/
void SoftwareUpgradeInterface::softwareUpgradeRequest(QString SCUpgradeVersion, QString ACUpgradeVersion, QString HMIUpgradeVersion)
{
    std::string SCFileName = SCUpgradeVersion.toStdString();
    std::string ACFileName = ACUpgradeVersion.toStdString();
    std::string HMIFileName = HMIUpgradeVersion.toStdString();

    m_SoftwareUpgrade->InitiateSoftwareUpgradeRequest(SCFileName,ACFileName,HMIFileName);
}

/**************************************************************************//**
*
* \brief  - send Software Upgrade Error Code to Software Upgrade screen
*
* \param  - None.
*
* \return - SOFTWARE_UPGRADE_ERROR_CODES - Error code.
*
******************************************************************************/
SOFTWARE_UPGRADE_ERROR_CODES SoftwareUpgradeInterface::getSoftwareUpgradeErrorCode()
{ 
   return m_SoftwareUpgradeResult;
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnSoftwareUpgradeDataUpdated is to update values on Software Upgrade screen.
*
* \param  - SoftwareUpgrade_Obj : Object pointer of type SoftwareUpgrade.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void SoftwareUpgradeInterface::OnSoftwareUpgradeDataUpdated(SoftwareUpgrade *SoftwareUpgrade_Obj, int welderId)
{
    m_SoftwareUpgrade = SoftwareUpgrade_Obj;
    if(m_SoftwareUpgrade->GetReadUSBStatus() || m_SoftwareUpgrade->GetSoftwareUpgradeStatus() || m_ActiveWelderId != welderId)
    {
        if(m_SoftwareUpgrade->GetSoftwareUpgradeStatus())
        {
            m_SoftwareUpgradeResult = m_SoftwareUpgrade->GetSoftwareUpgradeErrorCode();
            emit softwareUpgradeErrorCodeUpdated();
        }
        else
        {
            std::queue<SoftwareUpgradeStruct> SoftwareUpgradeReadUSBData;
            SoftwareUpgradeReadUSBData = m_SoftwareUpgrade->GetReadUSBData();
            SCFileNameList.clear();
            ACFileNameList.clear();
            HMIFileNameList.clear();
            SCFileNameList.append(FIRMWARE_UPGRADE_EMPTY_FILE_NAME);
            ACFileNameList.append(FIRMWARE_UPGRADE_EMPTY_FILE_NAME);
            HMIFileNameList.append(FIRMWARE_UPGRADE_EMPTY_FILE_NAME);
            while(!SoftwareUpgradeReadUSBData.empty())
            {
                SoftwareUpgradeStruct FileName = SoftwareUpgradeReadUSBData.front();
                SoftwareUpgradeReadUSBData.pop();
                std::string StrFileName(FileName.SoftwareUpgradeFileName);
                if (StrFileName.rfind(SC_FIRMWARE_UPGRADE_FILE_PREFIX, 0) == 0)
                {
                    SCFileNameList.append(QString::fromStdString(StrFileName));
                }
                else if (StrFileName.rfind(AC_FIRMWARE_UPGRADE_FILE_PREFIX, 0) == 0)
                {
                    ACFileNameList.append(QString::fromStdString(StrFileName));
                }
                else if (StrFileName.rfind(HMI_FIRMWARE_UPGRADE_FILE_PREFIX, 0) == 0)
                {
                    HMIFileNameList.append(QString::fromStdString(StrFileName));
                }
            }
            if(m_ActiveWelderId == welderId)
            {
                emit softwareUpgradeReadUsbDataChanged();
            }
            m_ActiveWelderId = welderId;
        }
    }
}


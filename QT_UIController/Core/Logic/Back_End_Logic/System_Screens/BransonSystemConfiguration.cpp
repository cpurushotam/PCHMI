/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares Branson System Configuration class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "BransonSystemConfiguration.h"

/**************************************************************************//**
*
* \brief  -Branson System Configuration Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
BransonSystemConfiguration::BransonSystemConfiguration(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::BransonSysConfgDataUpdated, this, &BransonSystemConfiguration::OnBransonSystemConfigurationUpdated);
}


/**************************************************************************//**
*
* \brief  - Return Machine Serial Number
*
* \param  - None.
*
* \return - QString m_machineSerialNumber.
*
******************************************************************************/
QString BransonSystemConfiguration::getMachineSerialNumber() const
{
    return m_machineSerialNumber;
}

/**************************************************************************//**
*
* \brief  - Update Machine Serial Number
*
* \param  - QString machineSerialNumber -  Machine Serial Number to be update
*
* \return - None.
*
******************************************************************************/
void BransonSystemConfiguration::updateMachineSerialNumber(QString machineSerialNumber)
{
    if (m_machineSerialNumber != machineSerialNumber)
    {
        m_machineSerialNumber = machineSerialNumber;
        emit bransonSystemConfigurationChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Machine Serial Number
*
* \param  - None.
*
* \return - QString m_powerSupplySerialNumber.
*
******************************************************************************/
QString BransonSystemConfiguration::getPowerSupplySerialNumber() const
{
    return m_powerSupplySerialNumber;
}

/**************************************************************************//**
*
* \brief  - Update Power Supply Serial Number
*
* \param  - QString powerSupplySerialNumber -  Power Supply Serial Number to be update
*
* \return - None.
*
******************************************************************************/
void BransonSystemConfiguration::updatePowerSupplySerialNumber(QString powerSupplySerialNumber)
{
    if (m_powerSupplySerialNumber != powerSupplySerialNumber)
    {
        m_powerSupplySerialNumber = powerSupplySerialNumber;
        emit bransonSystemConfigurationChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return Actuator Serial Number
*
* \param  - None.
*
* \return - QString m_actuatorSerialNumber.
*
******************************************************************************/
QString BransonSystemConfiguration::getActuatorSerialNumber() const
{
    return m_actuatorSerialNumber;
}

/**************************************************************************//**
*
* \brief  - Update Actuator Serial Number
*
* \param  - QString actuatorSerialNumber -  Actuator Serial Number to be update
*
* \return - None.
*
******************************************************************************/
void BransonSystemConfiguration::updateActuatorSerialNumber(QString actuatorSerialNumber)
{
    if (m_actuatorSerialNumber != actuatorSerialNumber)
    {
        m_actuatorSerialNumber = actuatorSerialNumber;
        emit bransonSystemConfigurationChanged();
    }
}

/**************************************************************************//**
*
* \brief  - Return data updated in db error code
*
* \param  - None.
*
* \return - UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES - error code.
*
******************************************************************************/
UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES BransonSystemConfiguration::getBransonSystemConfigUpdateResult()
{
    return m_BransonSystemConfigUpdateResult;
}

/**************************************************************************//**
*
* \brief  - send Branson system configuration save request to Memory Block
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonSystemConfiguration::saveRequest()
{
    SystemConfigBransonServiceStruct bransonServiceData;
    strncpy(bransonServiceData.MachineSerialNumber,m_machineSerialNumber.toStdString().c_str(),sizeof(bransonServiceData.MachineSerialNumber));
    strncpy(bransonServiceData.PowerSupplySerialNumber,m_powerSupplySerialNumber.toStdString().c_str(),sizeof(bransonServiceData.PowerSupplySerialNumber));
    strncpy(bransonServiceData.ActuatorSerialNumber,m_actuatorSerialNumber.toStdString().c_str(),sizeof(bransonServiceData.ActuatorSerialNumber));
    m_SystemConfigBransonService->InitiateSystemConfigBransonServiceUpdateRequest(bransonServiceData);
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnBransonSystemConfigurationUpdated is to update values on Branson System Config screen.
*
* \param  - SystemConfigBransonService_Obj : Object pointer of type SystemConfigBransonService.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void BransonSystemConfiguration::OnBransonSystemConfigurationUpdated(SystemConfigBransonService *SystemConfigBransonService_Obj, int welderId)
{
    m_SystemConfigBransonService = SystemConfigBransonService_Obj;
    if(m_SystemConfigBransonService->GetSystemConfigBransonServiceUpdateStatus() || m_ActiveWelderId != welderId)
    {
        if(m_SystemConfigBransonService->GetSystemConfigBransonServiceUpdateStatus() == true)
        {
            m_BransonSystemConfigUpdateResult = m_SystemConfigBransonService->GetSystemConfigBransonServiceUpdatedErrorCode();
            emit bransonSystemConfigurationErrorCodeUpdated();
        }

        SystemConfigBransonServiceStruct systemConfigBransonServiceStructUpdatedData;
        systemConfigBransonServiceStructUpdatedData = m_SystemConfigBransonService->GetSystemConfigBransonServiceData();

        m_machineSerialNumber = QString::fromUtf8(systemConfigBransonServiceStructUpdatedData.MachineSerialNumber);
        m_powerSupplySerialNumber = QString::fromUtf8(systemConfigBransonServiceStructUpdatedData.PowerSupplySerialNumber);
        m_actuatorSerialNumber = QString::fromUtf8(systemConfigBransonServiceStructUpdatedData.ActuatorSerialNumber);

        m_ActiveWelderId = welderId;
        emit bransonSystemConfigurationChanged();
    }
}


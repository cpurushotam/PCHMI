/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file is a source file and it is used to implement the system information screens data.

 **********************************************************************************************************/

#include "SystemInformationInterface.h"
#include "version_common.h"
#include "ActuatorInit.h"
#include "StrokeLength.h"
#include "PowerSupplyType.h"
#include "MultiwelderInterface.h"
#include "PowerLevelSysFrequencySupport.h"

/**************************************************************************//**
*
* \brief - This is the constructor.
*
* \param - None.
*
* \return - None
*
******************************************************************************/
SystemInformationInterface::SystemInformationInterface(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SystemInformationDataUpdated, this, &SystemInformationInterface::OnSystemInformationDataUpdated);
}

/**************************************************************************//**
*
* \brief - To get the general alarm.
*
* \param - None.
*
* \return - generalAlarm value.
*
******************************************************************************/
int SystemInformationInterface::getGeneralAlarm() const
{
    return m_NoOfAlarms;
}

/**************************************************************************//**
*
* \brief -To get the UI controller version.
*
* \param - None.
*
* \return - version of UI controller.
*
******************************************************************************/
QString SystemInformationInterface::getUIControllerVersion() const
{
    return m_UIVersion;
}

/**************************************************************************//**
*
* \brief - To get the Supervisory controller version.
*
* \param - None.
*
* \return - version of Supervisory controller.
*
******************************************************************************/
QString SystemInformationInterface::getSupervisoryControllerVersion() const
{
    return m_SCVersion;
}

/**************************************************************************//**
*
* \brief - To get the Actuator controller version.
*
* \param - None.
*
* \return - version of Actuator controller.
*
******************************************************************************/
QString SystemInformationInterface::getActuatorControllerVersion() const
{
    return m_ACVersion;
}

/**************************************************************************//**
*
* \brief - To get the Power controller version.
*
* \param - None.
*
* \return - version of Power controller.
*
******************************************************************************/
QString SystemInformationInterface::getPowerControllerVersion() const
{
    return m_PCVersion;
}

/**************************************************************************//**
*
* \brief - To get the power supply serial number
*
* \param - None.
*
* \return - power supply serial number.
*
******************************************************************************/
QString SystemInformationInterface::getPSSerialNumber() const
{
    return m_PowerSupplySerialNumber;
}

/**************************************************************************//**
*
* \brief - To get the power supply life time welds.
*
* \param - None.
*
* \return - value of PS life time welds.
*
******************************************************************************/
int SystemInformationInterface::getPSLifeWelds() const
{
    return m_PSLifeWelds;
}

/**************************************************************************//**
*
* \brief - To get the PS overloads.
*
* \param - None.
*
* \return - value of PS overloads.
*
******************************************************************************/
int SystemInformationInterface::getPSOverloads() const
{
    return m_PSOverloads;
}

/**************************************************************************//**
*
* \brief - To get the PS type.
*
* \param - None.
*
* \return - PS type value.
*
******************************************************************************/
QString SystemInformationInterface::getPSModel() const
{
    return m_PSModel;
}

/**************************************************************************//**
*
* \brief - To get the PS frequency.
*
* \param - None.
*
* \return - PS frequency.
*
******************************************************************************/
int SystemInformationInterface::getPSFrequency() const
{
    return m_PSFrequency;
}

/**************************************************************************//**
*
* \brief - To get the PS wattage.
*
* \param - None.
*
* \return - value of PS wattage.
*
******************************************************************************/
int SystemInformationInterface::getPSWattage() const
{
    return m_PSWattage;
}

/**************************************************************************//**
*
* \brief - To get the AC serial number
*
* \param - None.
*
* \return - AC serial number.
*
******************************************************************************/
QString SystemInformationInterface::getACSerialNumber() const
{
    return m_ActuatorSerialNumber;
}

/**************************************************************************//**
*
* \brief - To get the actuator life time cycle.
*
* \param - None.
*
* \return - value of actuator life time cycle.
*
******************************************************************************/
int SystemInformationInterface::getActuatorLifeCycle() const
{
    return m_ActuatorLifeCycle;
}

/**************************************************************************//**
*
* \brief - To get the actuator model.
*
* \param - None.
*
* \return - Actuator model.
*
******************************************************************************/
QString SystemInformationInterface::getActuatorModel() const
{
    return m_ActuatorModel;
}

/**************************************************************************//**
*
* \brief - To get the actuator calibration date.
*
* \param - None.
*
* \return - Actuator calibration date.
*
******************************************************************************/
QString SystemInformationInterface::getActuatorCaliDate() const
{
    return m_CalibrationDate;
}

/**************************************************************************//**
*
* \brief - To get the stroken length.
*
* \param - None.
*
* \return - stroken length value.
*
******************************************************************************/
QString SystemInformationInterface::getStrokeLength() const
{
    return m_StrokeLength;
}

/**************************************************************************//**
*
* \brief - To get the MAC ID.
*
* \param - None.
*
* \return - MAC ID.
*
******************************************************************************/
QString SystemInformationInterface::getMACAddress() const
{
    return m_MacAddress;
}
/**************************************************************************//**
*
* \brief - To get the Cylinder Size.
*
* \param - None.
*
* \return - Cylinder Size.
*
******************************************************************************/
int SystemInformationInterface::getCylinderSize() const
{
    switch (PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), CYLINDER_SIZE_KEY))
    {
    case FORTY_MM_CYLINDER:
    {
        return FORTY_MM_CYLINDER_Size;
    }
    break;

    case FIFTY_MM_CYLINDER:
    {
        return FIFTY_MM_CYLINDER_Size;
    }
    break;

    case SIXTY_THREE_MM_CYLINDER:
    {
        return SIXTY_THREE_MM_CYLINDER_Size;
    }
    break;

    case EIGHTY_MM_CYLINDER:
    {
        return EIGHTY_MM_CYLINDER_Size;
    }
    break;
    }
    return 0;
}

/**************************************************************************//**
*
* \brief - To get the Safety controller version
*
* \param - None.
*
* \return - SafetyControllerVersion
*
******************************************************************************/
QString SystemInformationInterface::getSafetyControllerVersion() const
{
    return m_SafetyControllerVersion;
}
/**************************************************************************//**
*
* \brief - Below function returns that 	type of bearing supported from json.
*
* \param - None.
*
* \return - BearingTYpe 
******************************************************************************/
BEARING_TYPE_CONFIG SystemInformationInterface::getbearingType() const
{
    BEARING_TYPE_CONFIG BearingTYpe = static_cast<BEARING_TYPE_CONFIG>(PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), BEARING_TYPE_KEY));

    return BearingTYpe;
}
/**************************************************************************//**
*
* \brief - Below function returns that machine serial numaber to HMI.
*
* \param - None.
*
* \return - Machine serial number
******************************************************************************/
QString SystemInformationInterface::getMachineSerialNumber() const
{
    return m_MachineSerialNumber;
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnSystemInformationDataUpdated is to update values on system information screen.
*
* \param  - SystemInformation_Obj : Object pointer of type SystemInformation.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void SystemInformationInterface::OnSystemInformationDataUpdated(SystemInformation *SystemInformation_Obj,SystemConfigBransonService * SystemConfigBransonServiceObj, int welderId)
{
    m_SystemInformationMachineDetails = SystemInformation_Obj;
    m_SystemConfigBransonService = SystemConfigBransonServiceObj;
    if(m_SystemConfigBransonService->GetSystemConfigBransonServiceUpdateStatus() || m_SystemInformationMachineDetails->GetSystemInformationMachineDetailsUpdateStatus() || m_ActiveWelderId != welderId)
    {
        MachineDetailsStruct systemInforMachineDetailsUpdatedData;
        systemInforMachineDetailsUpdatedData = m_SystemInformationMachineDetails->GetSystemInformationMachineDetailsData();
        m_NoOfAlarms = systemInforMachineDetailsUpdatedData.NumberOfAlarms;

        m_UIVersion = QString::number(UIC_VERSION_NUM_MAJOR) + "." + QString::number(UIC_VERSION_NUM_MINOR) + "." \
                            + QString::number(UIC_VERSION_NUM_BUILD) + "." + QString::number(UIC_VERSION_NUM_AUTOS);
        m_SCVersion = QString::fromUtf8(systemInforMachineDetailsUpdatedData.SCVersion);
        m_ACVersion = QString::fromUtf8(systemInforMachineDetailsUpdatedData.ACVersion);
        m_PCVersion = QString::fromUtf8(systemInforMachineDetailsUpdatedData.PCVersion);
        m_SafetyControllerVersion =  QString::fromUtf8(systemInforMachineDetailsUpdatedData.SafetyVersion);

        m_PowerSupplySerialNumber = QString::fromUtf8(systemInforMachineDetailsUpdatedData.PowerSupplySerialNumber);
        m_PSLifeWelds = systemInforMachineDetailsUpdatedData.PowerSupplyLifetimeWeld;
        m_PSOverloads = systemInforMachineDetailsUpdatedData.PowerSupplyOverLoad;

        m_PSFrequency = PowerLevelSysFrequencySupport::GetSystemFrequencyFromJSON();
        m_PSWattage = static_cast<int>(PowerLevelSysFrequencySupport::GetMaxPowerFromJSON());

        m_ActuatorSerialNumber = QString::fromUtf8(systemInforMachineDetailsUpdatedData.ActuatorSerialNumber);
        m_ActuatorLifeCycle = systemInforMachineDetailsUpdatedData.ActuatorLifetimeCycle;
        m_CalibrationDate = QString::fromUtf8(systemInforMachineDetailsUpdatedData.CalibrationDate);
        m_MacAddress = QString::fromUtf8(systemInforMachineDetailsUpdatedData.MacId);

        SystemConfigBransonServiceStruct systemConfigBransonServiceStructUpdatedData;
        systemConfigBransonServiceStructUpdatedData = m_SystemConfigBransonService->GetSystemConfigBransonServiceData();
        m_MachineSerialNumber = QString::fromUtf8(systemConfigBransonServiceStructUpdatedData.MachineSerialNumber);
        POWER_SUPPLY_TYPE PSModel = static_cast<POWER_SUPPLY_TYPE>(PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), POWER_SUPPLY_TYPE_KEY));
        switch(PSModel)
        {
            case P_2100_POWER_SUPPLY:
            {
                m_PSModel = P_2100_PS;
                break;
            }
            case P_2200_POWER_SUPPLY:
            {
                m_PSModel = P_2200_PS;
                break;
            }
            case P_2300_POWER_SUPPLY:
            {
                m_PSModel = P_2300_PS;
                break;
            }
        }
        ACTUATOR_TYPE ActModel = static_cast<ACTUATOR_TYPE>(PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), ACTUATOR_TYPE_KEY));
        switch(ActModel)
        {
            case ACTUATOR_MANUAL:
            {
                m_ActuatorModel = ACT_MANUAL;
                break;
            }
            case ACTUATOR_ELECTRONIC:
            {
                m_ActuatorModel = ACT_ELECTRONIC;
                break;
            }
            case ACTUATOR_ELECTRONIC_PLUS:
            {
                m_ActuatorModel = ACT_ELECTRONIC_PLUS;
                break;
            }
        }

        STROKE_LENGTH_CONFIG StrokLength = static_cast<STROKE_LENGTH_CONFIG>(PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STROKE_LENGTH_KEY));
        switch(StrokLength)
        {
            case HUNDRED_MM_STROKE_LENGTH:
            {
                m_StrokeLength = STROKE_LENGTH_100MM;
                break;
            }
        }

        m_ActiveWelderId = welderId;
        emit systemInfoMachineDetailsChanged();
    }
}

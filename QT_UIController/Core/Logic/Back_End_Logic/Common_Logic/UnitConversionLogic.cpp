/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the unit conversion related implementation
 ***************************************************************************/
#include "UnitConversionLogic.h"
#include <QDebug>
#include "UpdateScreens.h"


/**************************************************************************//**
*
* \brief   - Constructor unit conversion class.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
UnitConversionLogic::UnitConversionLogic(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::UnitChangedScreenUpdated, this, &UnitConversionLogic::OnUnitChangedScreenUpdated);
}

/*************************************************************************//**
* \brief   - Wrapper function to display Pressure (kPa/psi) Unit on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getPressureUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
       currUnit  = "kPa";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "psi";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Distance (mm/in) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getDistanceUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit  =  "mm";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit  =  "in";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Velocity unit (mm/s || in/s) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getVelocityUnit() const
{

    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
         currUnit = "mm/s";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
         currUnit = "in/s";
    }
    return  currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Force unit (N/lb) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getForceUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "N";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "lbs";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Time unit (s) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getTimeUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "s";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "s";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Energy unit (j) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getEnergyUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "J";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "J";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Power Unit (W) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getPowerUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "W";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "W";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Frequency unit (Hz) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getFrequencyUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit =  "Hz";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit =  "Hz";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Phase unit (deg) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getPhaseUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "deg";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit= "deg";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Current unit (%) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getCurrentUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "%";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "%";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Amplitude unit (%) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getAmplitudeUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "%";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "%";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display Requested Amplitude unit (%) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getRequestAmplitudeUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "%";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "%";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Wrapper function to display DownSpeed unit (%) on HMI based on Unit selection
*
* \param   - None
*
* \return  - return QString unit to QML.
*
******************************************************************************/
QString UnitConversionLogic::getDownSpeedUnit() const
{
    QString currUnit = "";

    if(systemConfigPtr->GetSystemUnitType() == METRIC)
    {
        currUnit = "%";
    }
    if(systemConfigPtr->GetSystemUnitType() == IMPERIAL)
    {
        currUnit = "%";
    }
    return currUnit;
}
/*************************************************************************//**
* \brief   - Function used by QML to get the current unit setted from ASC
*
* \param   - None
*
* \return  - UNIT .
*
******************************************************************************/
UNIT UnitConversionLogic::currentUnit()
{
    return systemConfigPtr->GetSystemUnitType();
}
/*************************************************************************//**
* \brief   -Function to set the Unit from HMI to ASC.
*
* \param   - unit setted from right action menu.
*
* \return  - None
*
******************************************************************************/
void UnitConversionLogic::sendUnitChangeRequest(int unit)
{
    SystemConfigGeneralStruct m_SystemConfigGeneralStruct;  /* Instance of SystemConfigGeneralStruct structure*/
    m_SystemConfigGeneralStruct.currUnit = static_cast< UNIT>(unit);
    m_SystemConfigGeneralStruct.AuthorityCheck= systemConfigPtr->GetSystemDetailsFromASC().AuthorityCheck;
    m_SystemConfigGeneralStruct.memoryFullAction=systemConfigPtr->GetSystemDetailsFromASC().memoryFullAction;
    strcpy( m_SystemConfigGeneralStruct.BarcodeRecipePrefix,systemConfigPtr->GetSystemDetailsFromASC().BarcodeRecipePrefix);
    strcpy(m_SystemConfigGeneralStruct.welderName, systemConfigPtr->GetSystemDetailsFromASC().welderName);
    m_SystemConfigGeneralStruct.powerupoption= systemConfigPtr->GetSystemDetailsFromASC().powerupoption;
    m_SystemConfigGeneralStruct.PartID =systemConfigPtr->GetSystemDetailsFromASC().PartID;
    m_SystemConfigGeneralStruct.ClearMemoryAtPowerup =systemConfigPtr->GetSystemDetailsFromASC().ClearMemoryAtPowerup;
    m_SystemConfigGeneralStruct.ClearMemoryWithReset = systemConfigPtr->GetSystemDetailsFromASC().ClearMemoryWithReset;
    m_SystemConfigGeneralStruct.ParallelWeldResultStorageStatus = systemConfigPtr->GetSystemDetailsFromASC().ParallelWeldResultStorageStatus;
    m_SystemConfigGeneralStruct.ClampOnAlarm = systemConfigPtr->GetSystemDetailsFromASC().ClampOnAlarm;
    m_SystemConfigGeneralStruct.WeldRecipeUniqueSerialNumGenStatus = systemConfigPtr->GetSystemDetailsFromASC().WeldRecipeUniqueSerialNumGenStatus;
    m_SystemConfigGeneralStruct.ASCIPAddress = systemConfigPtr->GetSystemDetailsFromASC().ASCIPAddress;

    systemConfigPtr->setSystemDetailsFromHMI(m_SystemConfigGeneralStruct);
}
/*************************************************************************//**
* \brief   - Slot to initlaize the SystemConfigurationGeneral_MB class pointer to get SystemConfigurationGeneral_MB class data .
*
* \param   - SystemConfigurationGeneral_MB class pointer, Welder Id - Current welder Id.
*
* \return  - None.
*
******************************************************************************/
void UnitConversionLogic::OnUnitChangedScreenUpdated(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId)
{
    systemConfigPtr = SysConfgGenData_Obj;

    if(systemConfigPtr->getDataUpdatedFlag())
    {
        emit currentUnitChanged();
        systemConfigPtr->setDataUpdatedFlag();
    }
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AnalyticTableListData.h file provides cycle detail list container data
    handled by CycleDetailtablemodel.
***************************************************************************/
#include "AnalyticTableListData.h"
#include "recipedef.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the following variables...
*       m_RecipeNo;
*       m_RecipeMode;
*       m_RecipeVersionNo;
*       m_CycleDateTime;
*       m_WeldCollapseDistance;
*       m_HoldCollapseDistance;
*       m_TotalCollapseDistance;
*       m_MaxWeldForce;
*       m_MaxHoldForce;
*       m_StackSerialNumber;
*       m_CycleCounter;
*       m_WeldAbsolute;
*       m_TotalAbsolute;
*       m_TriggerDistance;
*       m_Velocity;
*
* \param  - None
*
* \return - None
*
******************************************************************************/
AnalyticTableListData::AnalyticTableListData()
{

}

AnalyticTableListData::    AnalyticTableListData(const int& p_RecipeNo, const int& p_RecipeMode, const QString & p_CycleDateTime, const float& p_WeldCollapseDistance, const float& p_HoldCollapseDistance,
                          const float& p_TotalCollapseDistance, const float& p_MaxWeldForce, const float& p_MaxHoldForce,
                          const QString& p_StackSerialNumber, const int& p_CycleCounter, const float& p_WeldAbsolute
                          , const float& p_TotalAbsolute, const float& p_TriggerDistance
                          , const float& p_Velocity, const int& p_RecipeVersionNo
                          , const float& p_WeldTime, const float& p_WeldEnergy, const float& p_WeldPeakPower
                          ,const QString& p_PowerSupplySerialNumber, const QString& p_ActuatorSerialNumber, const QString& p_ASCSerialNumber
                          , const float& p_HoldTime, const int& p_StartFrequency, const int& p_FrequencyChange
                          , const float& p_CycleTime, const QString& p_UserName, const QString &p_PartID
                          , const QString &p_BatchID, const float& p_TriggerPoint, const float& p_WeldSonicPoint
                          , const float& p_HoldPoint, const QString &p_AlarmID, const int &p_WeldStatus
                          , const int &p_RecipeStatus, const float& p_WeldPressure, const float& p_HoldPressure
                          , const float& p_EndWeldForce,const float& p_EndHoldForce)
                    : m_RecipeNo(p_RecipeNo),
                    m_RecipeMode(p_RecipeMode),
                    m_CycleDateTime(p_CycleDateTime),
                    m_WeldCollapseDistance(p_WeldCollapseDistance),
                    m_HoldCollapseDistance(p_HoldCollapseDistance),
                    m_TotalCollapseDistance(p_TotalCollapseDistance),
                    m_MaxWeldForce(p_MaxWeldForce),
                    m_MaxHoldForce(p_MaxHoldForce),
                    m_StackSerialNumber(p_StackSerialNumber),
                    m_CycleCounter(p_CycleCounter),
                    m_WeldAbsolute(p_WeldAbsolute),
                    m_TotalAbsolute(p_TotalAbsolute),
                    m_TriggerDistance(p_TriggerDistance),
                    m_Velocity(p_Velocity),
                    m_RecipeVersionNo(p_RecipeVersionNo),
                    m_WeldTime(p_WeldTime),
                    m_WeldEnergy(p_WeldEnergy),
                    m_WeldPeakPower(p_WeldPeakPower),
                    m_PowerSupplySerialNumber(p_PowerSupplySerialNumber),
                    m_ActuatorSerialNumber(p_ActuatorSerialNumber),
                    m_ASCSerialNumber(p_ASCSerialNumber),
                    m_HoldTime(p_HoldTime),
                    m_StartFrequency(p_StartFrequency),
                    m_FrequencyChange(p_FrequencyChange),
                    m_CycleTime(p_CycleTime),
                    m_UserName(p_UserName),
                    m_PartID(p_PartID),
                    m_BatchID(p_BatchID),
                    m_TriggerPoint(p_TriggerPoint),
                    m_WeldSonicPoint(p_WeldSonicPoint),
                    m_HoldPoint(p_HoldPoint),
                    m_AlarmID(p_AlarmID),
                    m_WeldStatus(p_WeldStatus),
                    m_RecipeStatus(p_RecipeStatus),
                    m_WeldPressure(p_WeldPressure),
                    m_HoldPressure(p_HoldPressure),
                    m_EndHoldForce(p_EndHoldForce),
                    m_EndWeldForce(p_EndWeldForce)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the WeldCollapseDistance.
*
* \param   - None.
*
* \return  - m_WeldCollapseDistance
******************************************************************************/
float AnalyticTableListData::getWeldCollapseDistance() const
{
    return m_WeldCollapseDistance;
}


/**************************************************************************//**
*
* \brief   - Below function returns the recipe number.
*
* \param   - None.
*
* \return  - m_RecipeNo.
******************************************************************************/
int AnalyticTableListData::getRecipeNo() const
{
    return m_RecipeNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the HoldCollapseDistance.
*
* \param   - None.
*
* \return  - m_HoldCollapseDistance .
******************************************************************************/
float AnalyticTableListData::getHoldCollapseDistance() const
{
    return m_HoldCollapseDistance;
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe mode.
*
* \param   - None.
*
* \return  - m_RecipeMode.
******************************************************************************/
int AnalyticTableListData::getRecipeMode() const
{
    return m_RecipeMode;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld cycle date and time.
*
* \param   - None.
*
* \return  - m_CycleDateTime : Weld Cycle date and time.
******************************************************************************/
QString AnalyticTableListData::getCycleDateTime() const
{
    return m_CycleDateTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns the TotalCollapseDistance.
*
* \param   - None.
*
* \return  - m_TotalCollapseDistance.
******************************************************************************/
float AnalyticTableListData::getTotalCollapseDistance() const
{
    return m_TotalCollapseDistance;
}

/**************************************************************************//**
*
* \brief   - Below function returns the MaxWeldForce.
*
* \param   - None.
*
* \return  - m_MaxWeldForce.
******************************************************************************/
float AnalyticTableListData::getMaxWeldForce() const
{
    return m_MaxWeldForce;
}

/**************************************************************************//**
*
* \brief   - Below function returns the MaxHoldForce.
*
* \param   - None.
*
* \return  - m_MaxHoldForce.
******************************************************************************/
float AnalyticTableListData::getMaxHoldForce() const
{
    return m_MaxHoldForce;
}

/**************************************************************************//**
*
* \brief   - Below function returns the StackSerialNumber.
*
* \param   - None.
*
* \return  - m_StackSerialNumber.
******************************************************************************/
QString AnalyticTableListData::getStackSerialNumber() const
{
    return m_StackSerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the CycleCounter.
*
* \param   - None.
*
* \return  - m_CycleCounter.
******************************************************************************/
int AnalyticTableListData::getCycleCounter() const
{
    return m_CycleCounter;
}

/**************************************************************************//**
*
* \brief   - Below function returns the WeldAbsolute.
*
* \param   - None.
*
* \return  - m_WeldAbsolute.
******************************************************************************/
float AnalyticTableListData::getWeldAbsolute() const
{
    return m_WeldAbsolute;
}
/**************************************************************************//**
*
* \brief   - Below function returns the TotalAbsolute.
*
* \param   - None.
*
* \return  - m_TotalAbsolute.
******************************************************************************/
float AnalyticTableListData::getTotalAbsolute() const
{
    return m_TotalAbsolute;
}
/**************************************************************************//**
*
* \brief   - Below function returns the TriggerDistance.
*
* \param   - None.
*
* \return  - m_TriggerDistance.
******************************************************************************/
float AnalyticTableListData::getTriggerDistance() const
{
    return m_TriggerDistance;
}
/**************************************************************************//**
*
* \brief   - Below function returns the Velocity.
*
* \param   - None.
*
* \return  - m_Velocity.
******************************************************************************/
float AnalyticTableListData::getVelocity() const
{
    return m_Velocity;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldModeType.
*
* \param   - None.
*
* \return  - WeldModeType.
******************************************************************************/
QString AnalyticTableListData::getWeldModeType() const
{
    QString WeldModeType;
    switch(m_RecipeMode)
    {
    case RecipeEnum::TIME_IDX :
        WeldModeType = "Time";
        break;
    case RecipeEnum::ENERGY_IDX :
        WeldModeType = "Energy";
        break;
    case RecipeEnum::PEAKPOWER_IDX :
        WeldModeType = "Peak Power";
        break;
    case RecipeEnum::GROUND_IDX :
        WeldModeType ="Scrub Time";
        break;
    case RecipeEnum::ABSDISTANCE_IDX :
        WeldModeType ="Absolute Distance";
        break;
    case RecipeEnum::COLDISTANCE_IDX :
        WeldModeType ="Collapse Distance";
        break;
    }
    return WeldModeType;
}
/**************************************************************************//**
*
* \brief   - Below function returns the RecipeVersionNo.
*
* \param   - None.
*
* \return  - m_RecipeVersionNo.
******************************************************************************/
int AnalyticTableListData::getRecipeVersionNo() const
{
    return m_RecipeVersionNo;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldTime.
*
* \param   - None.
*
* \return  - m_WeldTime.
******************************************************************************/
QString AnalyticTableListData::getWeldTime() const
{
    QString value = QString("%1").arg(m_WeldTime, 0, 'f', 3);
    return value;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldEnergy.
*
* \param   - None.
*
* \return  - m_WeldEnergy.
******************************************************************************/
QString AnalyticTableListData::getWeldEnergy() const
{
    QString value = QString("%1").arg(m_WeldEnergy, 0, 'f', 3);
    return value;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldPeakPower.
*
* \param   - None.
*
* \return  - m_WeldPeakPower.
******************************************************************************/
QString AnalyticTableListData::getWeldPeakPower() const
{
    QString value = QString("%1").arg(m_WeldPeakPower, 0, 'f', 3);
    return value;
}
/**************************************************************************//**
*
* \brief   - Below function returns the PowerSupplySerialNumber.
*
* \param   - None.
*
* \return  - m_PowerSupplySerialNumber.
******************************************************************************/
QString AnalyticTableListData::getPowerSupplySerialNumber()const
{
    return m_PowerSupplySerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the ActuatorSerialNumber.
*
* \param   - None.
*
* \return  - m_PowerSupplySerialNumber.
******************************************************************************/
QString AnalyticTableListData::getActuatorSerialNumber() const
{
    return m_ActuatorSerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the ASCSerialNumber.
*
* \param   - None.
*
* \return  - m_ASCSerialNumber.
******************************************************************************/
QString AnalyticTableListData::getASCSerialNumber() const
{
    return m_ASCSerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the HoldTime.
*
* \param   - None.
*
* \return  - m_HoldTime.
******************************************************************************/
float AnalyticTableListData::getHoldTime() const
{
    return m_HoldTime;
}
/**************************************************************************//**
*
* \brief   - Below function returns the StartFrequency.
*
* \param   - None.
*
* \return  - m_StartFrequency.
******************************************************************************/
int AnalyticTableListData::getStartFrequency() const
{
    return m_StartFrequency;
}
/**************************************************************************//**
*
* \brief   - Below function returns the FrequencyChange.
*
* \param   - None.
*
* \return  - m_FrequencyChange.
******************************************************************************/
int AnalyticTableListData::getFrequencyChange() const
{
    return m_FrequencyChange;
}
/**************************************************************************//**
*
* \brief   - Below function returns the CycleTime.
*
* \param   - None.
*
* \return  - m_CycleTime.
******************************************************************************/
float AnalyticTableListData::getCycleTime() const
{
    return m_CycleTime;
}
/**************************************************************************//**
*
* \brief   - Below function returns the UserName.
*
* \param   - None.
*
* \return  - m_UserName.
******************************************************************************/
QString AnalyticTableListData::getUserName() const
{
    return m_UserName;
}
/**************************************************************************//**
*
* \brief   - Below function returns the PartID.
*
* \param   - None.
*
* \return  - m_PartID.
******************************************************************************/
QString AnalyticTableListData::getPartID() const
{
    return m_PartID;
}
/**************************************************************************//**
*
* \brief   - Below function returns the BatchID.
*
* \param   - None.
*
* \return  - m_BatchID.
******************************************************************************/
QString AnalyticTableListData::getBatchID() const
{
    return m_BatchID;
}
/**************************************************************************//**
*
* \brief   - Below function returns the TriggerPoint.
*
* \param   - None.
*
* \return  - m_TriggerPoint.
******************************************************************************/
float AnalyticTableListData::getTriggerPoint() const
{
    return m_TriggerPoint;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldSonicPoint.
*
* \param   - None.
*
* \return  - m_WeldSonicPoint.
******************************************************************************/
float AnalyticTableListData::getWeldSonicPoint() const
{
    return m_WeldSonicPoint;
}
/**************************************************************************//**
*
* \brief   - Below function returns the HoldPoint.
*
* \param   - None.
*
* \return  - m_HoldPoint.
******************************************************************************/
float AnalyticTableListData::getHoldPoint() const
{
    return m_HoldPoint;
}
/**************************************************************************//**
*
* \brief   - Below function returns the AlarmID.
*
* \param   - None.
*
* \return  - m_AlarmID.
******************************************************************************/
QString AnalyticTableListData::getAlarmID() const
{
    return m_AlarmID;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldStatus.
*
* \param   - None.
*
* \return  - m_WeldStatus.
******************************************************************************/
int AnalyticTableListData::getWeldStatus() const
{
    return m_WeldStatus;
}
/**************************************************************************//**
*
* \brief   - Below function returns the RecipeStatus.
*
* \param   - None.
*
* \return  - m_RecipeStatus.
******************************************************************************/
int AnalyticTableListData::getRecipeStatus() const
{
    return m_RecipeStatus;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldPressure.
*
* \param   - None.
*
* \return  - m_WeldPressure.
******************************************************************************/
float AnalyticTableListData::getWeldPressure() const
{
        return m_WeldPressure;
}
/**************************************************************************//**
*
* \brief   - Below function returns the HoldPressure.
*
* \param   - None.
*
* \return  - m_HoldPressure.
******************************************************************************/
float AnalyticTableListData::getHoldPressure() const
{
    return m_HoldPressure;
}
/**************************************************************************//**
*
* \brief   - Below function returns the EndWeldForce.
*
* \param   - None.
*
* \return  - m_EndWeldForce.
******************************************************************************/
float AnalyticTableListData::getEndWeldForce() const
{
    return m_EndWeldForce;
}
/**************************************************************************//**
*
* \brief   - Below function returns the EndHoldForce.
*
* \param   - None.
*
* \return  - m_EndHoldForce.
******************************************************************************/
float AnalyticTableListData::getEndHoldForce() const
{
    return m_EndHoldForce;
}

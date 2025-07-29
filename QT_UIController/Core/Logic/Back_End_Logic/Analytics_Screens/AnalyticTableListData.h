/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AnalyticTableListData.h file provides cycle detail list container data
    handeled by CycleDetailsListModel
***************************************************************************/
#ifndef AnalyticTableListData_H
#define AnalyticTableListData_H

#include <QString>

class AnalyticTableListData
{
public:
    AnalyticTableListData();
    AnalyticTableListData(const int& p_RecipeNo, const int& p_RecipeMode, const QString & p_CycleDateTime, const float& p_WeldCollapseDistance, const float& p_HoldCollapseDistance,
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
                          , const float& p_EndWeldForce,const float& p_EndHoldForce);

private:

    int m_RecipeNo;
    int m_RecipeMode;
    int m_RecipeVersionNo;
    QString m_CycleDateTime;
    float m_WeldCollapseDistance;
    float m_HoldCollapseDistance;
    float m_TotalCollapseDistance;
    float m_MaxWeldForce;
    float m_MaxHoldForce;
    QString m_StackSerialNumber;
    int m_CycleCounter;
    float m_WeldAbsolute;
    float m_TotalAbsolute;
    float m_TriggerDistance;
    float m_Velocity;
    float m_WeldTime;
    float m_WeldEnergy;
    float m_WeldPeakPower;
    QString m_PowerSupplySerialNumber;
    QString m_ActuatorSerialNumber;
    QString m_ASCSerialNumber;
    float m_HoldTime;
    int   m_StartFrequency;
    int   m_FrequencyChange;
    float  m_CycleTime;
    QString  m_UserName;
    QString  m_PartID;
    QString  m_BatchID;
    float    m_TriggerPoint;
    float    m_WeldSonicPoint;
    float    m_HoldPoint;
    QString      m_AlarmID;
    int  m_WeldStatus;
    int  m_RecipeStatus;
    float    m_WeldPressure;
    float    m_HoldPressure;
    float    m_EndWeldForce;
    float    m_EndHoldForce;

public:

    int     getRecipeNo() const;
    int     getRecipeMode() const;
    QString getCycleDateTime() const;
    float   getWeldCollapseDistance() const;
    float   getHoldCollapseDistance() const;
    float   getTotalCollapseDistance() const;
    float   getMaxWeldForce() const;
    float   getMaxHoldForce() const;
    QString getStackSerialNumber() const;
    int     getCycleCounter() const;
    float   getWeldAbsolute() const;
    float   getTotalAbsolute() const;
    float   getTriggerDistance() const;
    float   getVelocity() const;
    QString getWeldModeType() const;
    int     getRecipeVersionNo() const;
    QString getWeldTime() const;
    QString getWeldEnergy() const;
    QString getWeldPeakPower() const;
    QString getPowerSupplySerialNumber() const;
    QString getActuatorSerialNumber() const;
    QString getASCSerialNumber() const;
    int     getStartFrequency() const;
    int     getFrequencyChange() const;
    QString getUserName() const;
    QString getPartID() const;
    QString getBatchID() const;
    float   getTriggerPoint() const;
    float   getWeldSonicPoint() const;
    float   getHoldPoint() const;
    QString getAlarmID() const;
    float   getWeldPressure() const;
    float   getHoldPressure() const;
    float   getEndWeldForce() const;
    float   getEndHoldForce() const;
    float   getHoldTime() const;
    float   getCycleTime() const;
    int     getWeldStatus() const;
    int     getRecipeStatus() const;
};

#endif // AnalyticTableListData_H

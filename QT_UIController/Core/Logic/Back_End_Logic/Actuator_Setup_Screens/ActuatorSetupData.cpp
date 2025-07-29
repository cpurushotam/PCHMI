/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

This file contains the Actuator Setup Data related implementation

***************************************************************************/
#include "ActuatorSetupData.h"
#include "UpdateScreens.h"
#include "CommPeerWrapper.h"
#include "MultiwelderInterface.h"
#include "WeldRecipeStructuresAce.h"
#include "PlatformConfig.h"
#include "UnitConversion.h"

/**************************************************************************//**
*
* \brief  - Actuator Setup Data Constructor.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
ActuatorSetupData::ActuatorSetupData(QObject *parent): QObject{parent}
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::ActuatorSetupScreenUpdated, this, &ActuatorSetupData::OnActuatorSetupDataUpdated);
}

/**************************************************************************//**
*
* \brief  - Actuator Setup Data Distructor.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
ActuatorSetupData::~ActuatorSetupData()
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the Absolute Position value.
*
* \param   - None.
*
* \return  - m_AbsolutePosition : Absolute Position value.
******************************************************************************/
float ActuatorSetupData::getAbsolutePosition() const
{
    return m_AbsolutePosition;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Pressure value.
*
* \param   - None.
*
* \return  - m_Pressure : Pressure value.
******************************************************************************/
float ActuatorSetupData::getPressure() const
{
    return m_Pressure;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Maximum Velocity value.
*
* \param   - None.
*
* \return  - m_MaximumVelocity : Maximum Velocity value.
******************************************************************************/
float ActuatorSetupData::getMaximumVelocity() const
{
    return m_MaximumVelocity;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Actual Force value.
*
* \param   - None.
*
* \return  - m_ActualForce : Actual Force value.
******************************************************************************/
float ActuatorSetupData::getActualForce() const
{
    return m_ActualForce;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Actuator Setup Operation Type value.
*
* \param   - None.
*
* \return  - m_OperationType : Actuator Setup Operation Type value.
******************************************************************************/
ACTUATOR_SETUP_OP_TYPE ActuatorSetupData::getOperationType() const
{
    return m_OperationType;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Actuator Setup Operation Type value.
*
* \param   - newOperationType : Actuator Setup Operation Type value.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::updateOperationType(ACTUATOR_SETUP_OP_TYPE newOperationType)
{
    if (m_OperationType != newOperationType)
    {
        m_OperationType = newOperationType;
        m_ActuatorSetupData->setActuatorSetupOperationType(m_OperationType);
        emit actuatorSetupDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function update the Horn Down Clamp On Off.
*
* \param   - status.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::updateHornDownClampOnOff(bool status)
{
    m_ActuatorSetupData->setHornDownClampOnOff(status);
    emit actuatorSetupDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function send the Horn Retract Request.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::sendHornRetractRequest()
{
    m_ActuatorSetupData->initiateActuatorSetupHornRetractRequest();
    emit actuatorSetupDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function send the Actuator Setup Screen Navigated ststus.
*
* \param   - status : Actuator Setup Screen Navigated ststus.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::isActuatorScreenNav(bool status)
{
    m_IsActuatorScreenNav = status;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Screen Open On HMI status.
*
* \param   - None.
*
* \return  - m_ScreenOpenOnHMI.
******************************************************************************/
bool ActuatorSetupData::getScreenOpenOnHMI() const
{
    return m_ScreenOpenOnHMI;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Screen Open On HMI status.
*
* \param   - newScreenOpenOnHMI: Screen Open On HMI status.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::updateScreenOpenOnHMI(bool newScreenOpenOnHMI)
{
    if (m_ScreenOpenOnHMI != newScreenOpenOnHMI )
    {
        m_ScreenOpenOnHMI = newScreenOpenOnHMI;
        if(m_ScreenOpenOnHMI == true){
            m_ActuatorSetupData->setActuatorSetupScreenOpenOnHMI(REQUEST_ACTUATOR_SETUP_ENTER_SCREEN);
        }
        else if(m_ScreenOpenOnHMI == false){
            m_ActuatorSetupData->setActuatorSetupScreenOpenOnHMI(REQUEST_ACTUATOR_SETUP_LEAVE_SCREEN);
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Weld Pressure value.
*
* \param   - None.
*
* \return  - m_RecipeWeldPressure.
******************************************************************************/
float ActuatorSetupData::getRecipeWeldPressure() const
{
    return m_RecipeWeldPressure;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Weld Pressure value.
*
* \param   - newRecipeWeldPressure: Weld Pressure value.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::updateRecipeWeldPressure(float newRecipeWeldPressure)
{
    if (m_RecipeWeldPressure!= newRecipeWeldPressure)
    {
        m_RecipeWeldPressure = newRecipeWeldPressure;
        m_RecipeData->SetActiveWeldRecipeParameter(WELD_PRESSURE_PARAM, &m_RecipeWeldPressure);
        emit actuatorSetupDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Recipe Number.
*
* \param   - None.
*
* \return  - m_RecipeNumber.
******************************************************************************/
int ActuatorSetupData::getRecipeNumber() const
{
    return m_RecipeNumber;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Recipe Name.
*
* \param   - None.
*
* \return  - m_RecipeName.
******************************************************************************/
QString ActuatorSetupData::getRecipeName() const
{
    return m_RecipeName;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Is Horn Position On Ground.
*
* \param   - None.
*
* \return  - m_IsHornPositionOnGround.
******************************************************************************/
bool ActuatorSetupData::getIsHornPositionOnGround() const
{
    return m_IsHornPositionOnGround;
}

/**************************************************************************//**
*
* \brief   - Below function updates the strokelenght value to HMI
*
* \param   - None
*
* \return  - StrokeLengthValue.
******************************************************************************/
float ActuatorSetupData::getStrokeLengthValue() const
{
    int StrokeLength = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STROKE_LENGTH_KEY);
    float StrokeLengthValue = 100;
     

    if(StrokeLength == HUNDRED_MM_STROKE_LENGTH)
    {
        if(currUnit == METRIC)
        {
            StrokeLengthValue = 100;
        }
        else
        {
           StrokeLengthValue = UnitConversion:: ConvertMilliMeterToInches(100);
        }
    }
    return StrokeLengthValue;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnActuatorSetupDataUpdated to update the Actuator
*            Setup Data..
*
* \param   - ActuatorSetup_Obj : Object pointer of type ActuatorSetupACE.
*
* \return  - None.
******************************************************************************/
void ActuatorSetupData::OnActuatorSetupDataUpdated(ActuatorSetupACE *ActuatorSetup_Obj, WeldRecipeACE *WeldRecipeACE_Obj, SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId)
{
    m_ActuatorSetupData = ActuatorSetup_Obj;
    m_RecipeData = WeldRecipeACE_Obj;
    m_SystemConfigurationGeneral_MB = SysConfgGenData_Obj;

    if((m_ActuatorSetupData->getIsDataFlagUpdated()) || m_ActiveWelderId != WelderId || m_IsActuatorScreenNav == true)
    {
        currUnit = m_SystemConfigurationGeneral_MB->GetSystemUnitType();
        m_SetupDataAct = m_ActuatorSetupData->getActuatorSetupData();

        WeldRecipeACEStruct m_WeldLabData;
        m_WeldLabData = m_RecipeData->GetActiveWeldRecipeData();
        m_RecipeWeldPressure = m_WeldLabData.WeldPressure;
        m_RecipeName = m_WeldLabData.WeldRecipeName;
        m_RecipeNumber = m_WeldLabData.WeldRecipeNumber;

        m_AbsolutePosition = m_SetupDataAct.AbsolutePosition;
        m_Pressure = m_SetupDataAct.Pressure;
        m_MaximumVelocity = m_SetupDataAct.MaxVelocity;
        m_ActualForce = m_SetupDataAct.ActualForce;
        m_OperationType = m_ActuatorSetupData->getActuatorSetupOperationType();

        m_IsHornPositionOnGround = m_SetupDataAct.isHornPositionOnGround;

        m_ActuatorSetupData->resetDataFlagUpdated();
        m_IsActuatorScreenNav = false;
        emit actuatorSetupDataChanged();
        m_ActiveWelderId = WelderId;
    }
}

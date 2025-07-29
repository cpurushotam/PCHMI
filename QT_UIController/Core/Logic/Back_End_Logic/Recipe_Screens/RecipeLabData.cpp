/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2023

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
This file updates the Recipe Lab Screen qml variables.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 24/08/2023 - Initial version.
***************************************************************************/
#include "RecipeLabData.h"
#include "MultiwelderInterface.h"
#include "WeldRecipeStructuresAce.h"
#include "WeldRecipe.h"
#include "StorageSupport.h"
#include "AmplitudeAndPressureStepsSupport.h"
#include "recipedef.h"
#define SUPPORTEDAMPLITUDESTEPS 10
#define SUPPORTEDPRESSURESTEPS 10
/**************************************************************************//**
*
* \brief  - Recipe Lab Data Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
RecipeLabData::RecipeLabData(QObject *parent) : QObject(parent)
{

    connect(UpdateScreen::getInstance(), &UpdateScreen::RecipeLabScreenUpdated, this, &RecipeLabData::OnRecipeLabDataUpdated);
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe number.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : Weld recipe number.
******************************************************************************/
int RecipeLabData::getWeldRecipeNumber() const
{
    return m_WeldRecipeNumber;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe number.
*
* \param   - WeldRecipeNumber : Weld recipe number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldRecipeNumber(const int &WeldRecipeNumber)
{
    if(m_WeldRecipeNumber != WeldRecipeNumber)
    {
        m_WeldRecipeNumber = WeldRecipeNumber;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe version number.
*
* \param   - None.
*
* \return  - m_WeldRecipeVersionNumber : Weld recipe version number.
******************************************************************************/
int RecipeLabData::getWeldRecipeVersionNumber() const
{
    return m_WeldRecipeVersionNumber;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe version number.
*
* \param   - WeldRecipeVersionNumber : Weld recipe version number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldRecipeVersionNumber(const int &WeldRecipeVersionNumber)
{
    if(m_WeldRecipeVersionNumber != WeldRecipeVersionNumber)
    {
        m_WeldRecipeVersionNumber = WeldRecipeVersionNumber;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe name.
*
* \param   - None.
*
* \return  - m_WeldRecipeName : Weld recipe name.
******************************************************************************/
QString RecipeLabData::getWeldRecipeName() const
{
    return m_WeldRecipeName;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe name.
*
* \param   - WeldRecipeName : Weld recipe name.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldRecipeName(const QString WeldRecipeName)
{
    if(m_WeldRecipeName != WeldRecipeName)
    {
        m_WeldRecipeName = WeldRecipeName;
        m_RecipeLabData->SetActiveWeldRecipeParameter(WeldRecipe::WELD_RECIPE_NAME_PARAM, const_cast<char*> (m_WeldRecipeName.toStdString().c_str()));
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe mode.
*
* \param   - None.
*
* \return  - m_WeldMode : Weld recipe mode.
******************************************************************************/
int RecipeLabData::getWeldMode() const
{
    return m_WeldMode;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe number.
*
* \param   - WeldMode : Weld recipe mode.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldMode(const int &WeldMode)
{
    if(m_WeldMode != WeldMode)
    {
        m_WeldMode = WeldMode;
        m_RecipeLabData->SetActiveWeldRecipeParameter(WeldRecipe::WELD_MODE_PARAM, &m_WeldMode);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe time.
*
* \param   - None.
*
* \return  - m_ModeValueTime : Weld recipe time.
******************************************************************************/
float RecipeLabData::getModeValueTime() const
{
    return m_ModeValueTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe time.
*
* \param   - None.
*
* \return  - m_ModeValueTime : Weld recipe time.
******************************************************************************/
void RecipeLabData::updateModeValueTime(const float &ModeValueTime)
{
    if(m_ModeValueTime != ModeValueTime)
    {
        m_ModeValueTime = ModeValueTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_TIME_PARAM, &m_ModeValueTime);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the energy value.
*
* \param   - None.
*
* \return  - m_ModeValueEnergy : Weld recipe energy value.
******************************************************************************/
float RecipeLabData::getModeValueEnergy() const
{
    return m_ModeValueEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe time.
*
* \param   - ModeValueEnergy : Weld recipe energy value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateModeValueEnergy(const float &ModeValueEnergy)
{
    if(m_ModeValueEnergy != ModeValueEnergy)
    {
        m_ModeValueEnergy = ModeValueEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_ENERGY_PARAM, &m_ModeValueEnergy);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe time.
*
* \param   - None.
*
* \return  - m_ModeValuePeakPower : Weld recipe peak power value.
******************************************************************************/
float RecipeLabData::getModeValuePeakPower() const
{
    return m_ModeValuePeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe time.
*
* \param   - ModeValuePeakPower : Weld recipe peak power value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateModeValuePeakPower(const float &ModeValuePeakPower)
{
    if(m_ModeValuePeakPower != ModeValuePeakPower)
    {
        m_ModeValuePeakPower = ModeValuePeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_PEAK_POWER_PARAM, &m_ModeValuePeakPower);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe ground detect value.
*
* \param   - None.
*
* \return  - m_ModeValueGroundDetect : Weld recipe ground detect value.
******************************************************************************/
float RecipeLabData::getModeValueGroundDetect() const
{
    return m_ModeValueGroundDetect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe ground detect value.
*
* \param   - ModeValueGroundDetect : Weld recipe ground detect value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateModeValueGroundDetect(const float &ModeValueGroundDetect)
{
    if(m_ModeValueGroundDetect != ModeValueGroundDetect)
    {
        m_ModeValueGroundDetect = ModeValueGroundDetect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_GROUND_DETECT_PARAM, &m_ModeValueGroundDetect);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe absolute distance value.
*
* \param   - None.
*
* \return  - m_ModeValueAbsDistance : Weld recipe absolute distance value.
******************************************************************************/
float RecipeLabData::getModeValueAbsDistance() const
{
    return m_ModeValueAbsDistance;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe absolute distance value.
*
* \param   - ModeValueAbsDistance : Weld recipe absolute distance value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateModeValueAbsDistance(const float &ModeValueAbsDistance)
{
    if(m_ModeValueAbsDistance != ModeValueAbsDistance)
    {
        m_ModeValueAbsDistance = ModeValueAbsDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_ABSOLUTE_DISTANCE_PARAM, &m_ModeValueAbsDistance);
    }
    emit recipeLabDataChanged();

}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe collapse distance value.
*
* \param   - None.
*
* \return  - m_ModeValueColDistance : Weld recipe collapse distance value.
******************************************************************************/
float RecipeLabData::getModeValueColDistance() const
{
    return m_ModeValueColDistance;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe collapse distance value.
*
* \param   - ModeValueColDistance : Weld recipe collapse distance value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateModeValueColDistance(const float &ModeValueColDistance)
{
    if(m_ModeValueColDistance != ModeValueColDistance)
    {
        m_ModeValueColDistance = ModeValueColDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MODE_VALUE_COLLAPSE_DISTANCE_PARAM, &m_ModeValueColDistance);

    }
    emit recipeLabDataChanged();

}

/**************************************************************************//**
*
* \brief   - Below function returns the weld recipe cycle count.
*
* \param   - None.
*
* \return  - m_CycleCount : Weld recipe cycle count value.
******************************************************************************/
int RecipeLabData::getCycleCount() const
{
    return m_CycleCount;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld recipe cycle count value.
*
* \param   - CycleCount : Weld recipe cycle count value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateCycleCount(const int &CycleCount)
{
    if(m_CycleCount != CycleCount)
    {
        m_CycleCount = CycleCount;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the ok weld cycles counts.
*
* \param   - None.
*
* \return  - m_CyclesOKCount : Ok weld cycles counts.
******************************************************************************/
int RecipeLabData::getCyclesOKCount() const
{
    return m_CyclesOKCount;
}

/**************************************************************************//**
*
* \brief   - Below function updates the ok weld cycles counts.
*
* \param   - CyclesOKCount : Ok weld cycles counts
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateCyclesOKCount(const int &CyclesOKCount)
{
    if(m_CyclesOKCount != CyclesOKCount)
    {
        m_CyclesOKCount = CyclesOKCount;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld reject count.
*
* \param   - None.
*
* \return  - m_RejectCount : Weld reject count.
******************************************************************************/
int RecipeLabData::getRejectCount() const
{
    return m_RejectCount;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld reject count.
*
* \param   - RejectCount : Weld reject count.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectCount(const int &RejectCount)
{
    if(m_RejectCount != RejectCount)
    {
        m_RejectCount = RejectCount;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld pressure value.
*
* \param   - None.
*
* \return  - m_WeldPressure : Weld pressure value.
******************************************************************************/
float RecipeLabData::getWeldPressure() const
{
    return m_WeldPressure;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld pressure value.
*
* \param   - WeldPressure : Weld pressure value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldPressure(const float &WeldPressure)
{
    if(m_WeldPressure != WeldPressure)
    {
        m_WeldPressure = WeldPressure;
        m_RecipeLabData->SetActiveWeldRecipeParameter(WELD_PRESSURE_PARAM, &m_WeldPressure);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the Pressure steps value.
*
* \param   - None.
*
* \return  - NumPressureSteps : Pressure steps value.
******************************************************************************/
int RecipeLabData::getNumPressureSteps() const
{
    return m_PressureStepDataACE.NumPressureSteps;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Pressure steps.
*
* \param   - NumPressureSteps : Pressure steps value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateNumPressureSteps(const int &NumPressureSteps)
{
    if(m_PressureStepDataACE.NumPressureSteps != NumPressureSteps)
    {
        m_PressureStepDataACE.NumPressureSteps = NumPressureSteps;
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the attribute of the Pressure step.
*
* \param   - None.
*
* \return  - PressureStepAt : The attribute at given Pressure step.
******************************************************************************/
int RecipeLabData::getPressureStepAt() const
{
    return m_PressureStepDataACE.PressureStepAt;
}

/**************************************************************************//**
*
* \brief   - Below function sets the attribute of the Pressure step.
*
* \param   - PressureStepAt : The attribute at given Pressure step.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updatePressureStepAt(const int &PressureStepAt)
{
    m_PressureStepDataACE.PressureStepAt = static_cast<STEP_TYPE>(PressureStepAt);
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the hold pressure value.
*
* \param   - None.
*
* \return  - m_HoldPressure : Hold pressure value.
******************************************************************************/
float RecipeLabData::getHoldPressure() const
{
    return m_HoldPressure;
}

/**************************************************************************//**
*
* \brief   - Below function updates the hold pressure value.
*
* \param   - HoldPressure : Hold pressure value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateHoldPressure(const float &HoldPressure)
{
    if(m_HoldPressure != HoldPressure)
    {
        m_HoldPressure = HoldPressure;
        m_RecipeLabData->SetActiveWeldRecipeParameter(HOLD_PRESSURE_PARAM, &m_HoldPressure);

    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the flow rate.
*
* \param   - None.
*
* \return  - m_FlowRate : Flow rate.
******************************************************************************/
float RecipeLabData::getFlowRate() const
{
    return m_FlowRate;
}

/**************************************************************************//**
*
* \brief   - Below function updates the flow rate.
*
* \param   - FlowRate : Flow rate.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateFlowRate(const float &FlowRate)
{
    if(m_FlowRate != FlowRate)
    {
        m_FlowRate = FlowRate;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FLOW_RATE_PARAM, &m_FlowRate);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the Trigger Force.
*
* \param   - None.
*
* \return  - m_TriggerForce : Trigger Force.
******************************************************************************/
float RecipeLabData::getTriggerForce() const
{
    return m_TriggerForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the TriggerForce.
*
* \param   - TriggerForce : TriggerForce.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateTriggerForce(float newTriggerForce)
{
    if (m_TriggerForce != newTriggerForce)
    {
         m_TriggerForce = newTriggerForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TRIGGER_FORCE_PARAM, &m_TriggerForce);
    }
    emit recipeLabDataChanged();
}
/**************************************************************************//**
*
* \brief   - Below function returns the hold time.
*
* \param   - None.
*
* \return  - m_HoldTime : Hold time.
******************************************************************************/
float RecipeLabData::getHoldTime() const
{
    return m_HoldTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the hold time.
*
* \param   - HoldTime : Hold time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateHoldTime(const float &HoldTime)
{
    if(m_HoldTime != HoldTime)
    {
        m_HoldTime = HoldTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(HOLD_TIME_PARAM, &m_HoldTime);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the maximum weld timeout value.
*
* \param   - None.
*
* \return  - m_MaxWeldTimeout : Weld timeout value.
******************************************************************************/
float RecipeLabData::getMaxWeldTimeout() const
{
    return m_MaxWeldTimeout;
}

/**************************************************************************//**
*
* \brief   - Below function updates the maximum weld timeout value.
*
* \param   - MaxWeldTimeout : Weld timeout value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateMaxWeldTimeout(const float &MaxWeldTimeout)
{
    if(m_MaxWeldTimeout != MaxWeldTimeout)
    {
        m_MaxWeldTimeout = MaxWeldTimeout;
        m_RecipeLabData->SetActiveWeldRecipeParameter(MAX_WELD_TIMEOUT_PARAM, &m_MaxWeldTimeout);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld amplitude.
*
* \param   - None.
*
* \return  - m_WeldAmplitude : Weld amplitude.
******************************************************************************/
int RecipeLabData::getWeldAmplitude() const
{
    return m_WeldAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld amplitude.
*
* \param   - WeldAmplitude : Weld amplitude.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateWeldAmplitude(const int &WeldAmplitude)
{
    if(m_WeldAmplitude != WeldAmplitude)
    {
        m_WeldAmplitude = WeldAmplitude;
        m_RecipeLabData->SetActiveWeldRecipeParameter(WELD_AMPLITUDE_PARAM, &m_WeldAmplitude);
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the Amplitude steps value.
*
* \param   - None.
*
* \return  - NumAmplitudeSteps : Amplitude steps value.
******************************************************************************/
int RecipeLabData::getNumAmplitudeSteps() const
{
    return m_AmplitudeStepDataACE.NumAmplitudeSteps;
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude steps.
*
* \param   - NumAmplitudeSteps : Amplitude steps value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateNumAmplitudeSteps(const int &NumAmplitudeSteps)
{
    if(m_AmplitudeStepDataACE.NumAmplitudeSteps != NumAmplitudeSteps)
    {
        m_AmplitudeStepDataACE.NumAmplitudeSteps = NumAmplitudeSteps;
    }

    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the attribute of the amplitude step.
*
* \param   - None.
*
* \return  - AmplitudeStepAt : The attribute at given amplitude step.
******************************************************************************/
int RecipeLabData::getAmplitudeStepAt() const
{
    return m_AmplitudeStepDataACE.AmplitudeStepAt;
}

/**************************************************************************//**
*
* \brief   - Below function sets the attribute of the amplitude step.
*
* \param   - AmplitudeStepAt : The attribute at given amplitude step.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateAmplitudeStepAt(const int &AmplitudeStepAt)
{
    m_AmplitudeStepDataACE.AmplitudeStepAt = static_cast<STEP_TYPE>(AmplitudeStepAt);
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe save status.
*
* \param   - None.
*
* \return  - m_IsRecipeSaved : The recipe save status.
******************************************************************************/
bool RecipeLabData::getIsRecipeSaved() const
{
    return m_IsRecipeSaved;
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe lab loading status.
*
* \param   - None.
*
* \return  - m_IsLoadingFlag : The recipe lab loading status.
******************************************************************************/
bool RecipeLabData::getIsLoading() const
{
    return m_IsLoadingFlag;
}

/**************************************************************************//**
*
* \brief   - Below function updates the recipe lab loading status.
*
* \param   - IsLoading : The recipe lab loading status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsLoading(const bool &IsLoading)
{
    m_IsLoadingFlag = IsLoading;
    emit loadingLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe amplitude parameter validity
*            status.
*
* \param   - None.
*
* \return  - m_IsParamValid : The recipe amplitude parameter validity status.
******************************************************************************/
bool RecipeLabData::getIsParamValid() const
{
    return m_IsParamValid;
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe amplitude parameter validity
*            status.
*
* \param   - m_IsParamValid : The recipe amplitude parameter validity status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsParamValid(const bool &IsParamValid)
{
    m_IsParamValid = IsParamValid;
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the value that is monitored during the weld
*            to tell the power supply when to perform the step.
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - AmplitudeStepAtValue : The value when to perform the step.
******************************************************************************/
float RecipeLabData::getAmplitudeStepAtValue(int StepNo)
{
    return m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepAtValue;
}


/**************************************************************************//**
*
* \brief   - Below function defines the rate at which the power supply changes
*            the amplitude from the current setting to the new step value.
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - AmplitudeStepRamp : The rate value at given amplitude step.
******************************************************************************/
float RecipeLabData::getAmplitudeStepRamp(int StepNo)
{
    return m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepRamp;
}

/**************************************************************************//**
*
* \brief   - Below function returns the target amplitude that gets sent to the
*            power supply after meeting the criteria defined in StepAt and
*            StepAtValue
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - AmplitudeStepTarget : The target amplitude at given
*            amplitude step.
******************************************************************************/
float RecipeLabData::getAmplitudeStepTarget(int StepNo)
{
    return m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepTarget;
}

/**************************************************************************//**
*
* \brief   - Below function returns the value that is monitored during the weld
*            to tell the power supply when to perform the step.
*
* \param   - StepNo : Pressure steps number.
*
* \return  - PressureStepAtValue : The value when to perform the step.
******************************************************************************/
float RecipeLabData::getPressureStepAtValue(int StepNo)
{
    return m_PressureStepDataACE.PressureStepParameters[StepNo].PressureStepAtValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the target Pressure that gets sent to the
*            power supply after meeting the criteria defined in StepAt and
*            StepAtValue
*
* \param   - StepNo : Pressure steps number.
*
* \return  - PressureStepTarget : The target Pressure at given
*            Pressure step.
******************************************************************************/
float RecipeLabData::getPressureStepTarget(int StepNo)
{
    return m_PressureStepDataACE.PressureStepParameters[StepNo].PressureStepTarget;
}

/**************************************************************************//**
*
* \brief   - Below function sets the value that is monitored during the weld
*            to tell the power supply when to perform the step.
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setAmplitudeStepAtValue(float Value, int StepNo)
{
    m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepAtValue = Value;
    emit recipeLabDataChanged();
}


/**************************************************************************//**
*
* \brief   - Below function sets the value which defines the rate at which
*            the power supply changes the amplitude from the current setting
*            to the new step value.
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setAmplitudeStepRamp(float Value, int StepNo)
{
    m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepRamp = Value;
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function sets the target amplitude that gets sent to the
*            power supply after meeting the criteria defined in StepAt and
*            StepAtValue
*
* \param   - StepNo : Amplitude steps number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setAmplitudeStepTarget(float Value, int StepNo)
{
    m_AmplitudeStepDataACE.AmplitudeStepParameters[StepNo].AmplitudeStepTarget = Value;
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function sets the value that is monitored during the weld
*            to tell the power supply when to perform the step.
*
* \param   - StepNo : Pressure steps number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setPressureStepAtValue(float Value, int StepNo)
{
    m_PressureStepDataACE.PressureStepParameters[StepNo].PressureStepAtValue = Value;
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function sets the target Pressure that gets sent to the
*            power supply after meeting the criteria defined in StepAt and
*            StepAtValue
*
* \param   - StepNo : Pressure steps number.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setPressureStepTarget(float Value, int StepNo)
{
    m_PressureStepDataACE.PressureStepParameters[StepNo].PressureStepTarget = Value;
    emit recipeLabDataChanged();
}


/**************************************************************************//**
*
* \brief   - Role of the createNewRecipeRequest to create recipe as request
*            initiated from weld mode screen.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
bool RecipeLabData::createNewRecipeRequest()
{
    /*Recipe create call*/
    m_RecipeLabData->InitiateRecipeCreateRequest();

    /*To verify max recipe count reached or not*/
    if(m_RecipeLabData->GetTotalRecipesEntries() >= StorageSupport::GetMaxRecipeNumberSupportedFromJSON())
    {
        return false;
    }

    return true;
}

/**************************************************************************//**
*
* \brief   - Role of the initiateRecipeSaveRequest to initiate recipe save
*            functionality.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::initiateRecipeSaveRequest()
{
    /*Make IsSaved flag as true*/
    bool Value = 1;

    m_RecipeLabData->SetActiveWeldRecipeParameter(IS_SAVED_PARAM, &Value);
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxAmplitudeStepCountSupported to fetch maximum
*            amplitude steps count supported.
*
* \param   - None.
*
* \return  - GetSupportedAmplitudeStepsFromJSON() : Function returns maximum
*            amplitude steps count supported.
******************************************************************************/
int RecipeLabData::getMaxAmplitudeStepCountSupported()
{
    return AmplitudeAndPressureStepsSupport::GetSupportedAmplitudeStepsFromJSON();
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxPressureStepCountSupported to fetch maximum
*            Pressure steps count supported.
*
* \param   - None.
*
* \return  - GetSupportedPressureStepsFromJSON() : Function returns maximum
*            Pressure steps count supported.
******************************************************************************/
int RecipeLabData::getMaxPressureStepCountSupported()
{
    return AmplitudeAndPressureStepsSupport::GetSupportedPressureStepsFromJSON();
}

/**************************************************************************//**
*
* \brief   - Role of the getMinParamValue to fetch minimum
*            amplitude steps at value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MinVal : Minimum amplitude steps at value supported.
******************************************************************************/
QString RecipeLabData::getMinParamValue(int mode)
{
    std::string  MinVal;

    switch(mode)
    {
    case RecipeEnum::TIME_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_TIME_PARAM);
        break;

    case RecipeEnum::ENERGY_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_ENERGY_PARAM);
        break;

    case RecipeEnum::PEAKPOWER_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_PEAK_POWER_PARAM);
        break;

    case RecipeEnum::GROUND_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_GROUND_DETECT_PARAM);
        break;

    case RecipeEnum::ABSDISTANCE_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_ABSOLUTE_DISTANCE_PARAM);
        break;

    case RecipeEnum::COLDISTANCE_IDX :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_COLLAPSE_DISTANCE_PARAM);
        break;

    case WELD_AMPLITUDE :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(WELD_AMPLITUDE_PARAM);
        break;

    case WELD_PRESSURE :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(WELD_PRESSURE_PARAM);
        break;

    case WELD_FLOWRATE :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(FLOW_RATE_PARAM);
        break;

    case WELD_HOLDTIME :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(HOLD_TIME_PARAM);
        break;

    case WELD_TRIGGERFORCE :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(TRIGGER_FORCE_PARAM);
        break;

    case WELD_HOLDPRESSURE :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(HOLD_PRESSURE_PARAM);
        break;
    default :

        MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_TIME_PARAM);
        break;
    }

    return QString::fromLocal8Bit(MinVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMinAmplitudeStepRamp to fetch minimum
*            amplitude steps ramp value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MinVal : Minimum amplitude steps ramp value supported.
******************************************************************************/
QString RecipeLabData::getMinAmplitudeStepRamp()
{
    std::string  MinVal;
    MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(AMPLITUDE_STEP_RAMP_1_PARAM);

    return QString::fromLocal8Bit(MinVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMinAmplitudeStepTarget to fetch minimum
*            amplitude steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MinVal : Minimum amplitude steps target value supported.
******************************************************************************/
QString RecipeLabData::getMinAmplitudeStepTarget()
{
    std::string MinVal;
    MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(AMPLITUDE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(MinVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMinPressureStepTarget to fetch minimum
*            Pressure steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MinVal : Minimum Pressure steps target value supported.
******************************************************************************/
QString RecipeLabData::getMinPressureStepTarget()
{
    std::string MinVal;
    MinVal = m_RecipeLabData->GetWeldRecipeParamMinValue(PRESSURE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(MinVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxParamValue to fetch maximum
*            amplitude steps at value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MaxVal : Maximum amplitude steps at value supported.
******************************************************************************/
QString RecipeLabData::getMaxParamValue(int mode)
{
    std::string  MaxVal;

    switch(mode)
    {
    case RecipeEnum::TIME_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_TIME_PARAM);
        break;

    case RecipeEnum::ENERGY_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_ENERGY_PARAM);
        break;

    case RecipeEnum::PEAKPOWER_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_PEAK_POWER_PARAM);
        break;

    case RecipeEnum::GROUND_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_GROUND_DETECT_PARAM);
        break;

     case RecipeEnum::ABSDISTANCE_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_ABSOLUTE_DISTANCE_PARAM);
        break;

    case RecipeEnum::COLDISTANCE_IDX :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_COLLAPSE_DISTANCE_PARAM);
        break;

    case WELD_AMPLITUDE :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(WELD_AMPLITUDE_PARAM);
        break;

    case WELD_PRESSURE :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(WELD_PRESSURE_PARAM);
        break;

    case WELD_FLOWRATE :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(FLOW_RATE_PARAM);
        break;

    case WELD_HOLDTIME :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(HOLD_TIME_PARAM);
        break;

    case WELD_TRIGGERFORCE :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(TRIGGER_FORCE_PARAM);
        break;

    case WELD_HOLDPRESSURE :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(HOLD_PRESSURE_PARAM);
        break;

    default :

        MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_TIME_PARAM);
        break;
    }

    return QString::fromLocal8Bit(MaxVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxAmplitudeStepRamp to fetch maximum
*            amplitude steps ramp value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MaxVal : Maximum amplitude steps ramp value supported.
******************************************************************************/
QString RecipeLabData::getMaxAmplitudeStepRamp()
{
    std::string  MaxVal;
    MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(AMPLITUDE_STEP_RAMP_1_PARAM);

    return QString::fromLocal8Bit(MaxVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxAmplitudeStepTarget to fetch maximum
*            amplitude steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MaxVal : Maximum amplitude steps target value supported.
******************************************************************************/
QString RecipeLabData::getMaxAmplitudeStepTarget()
{
    std::string MaxVal;
    MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(AMPLITUDE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(MaxVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getMaxPressureStepTarget to fetch maximum
*            Pressure steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - MaxVal : Maximum Pressure steps target value supported.
******************************************************************************/
QString RecipeLabData::getMaxPressureStepTarget()
{
    std::string MaxVal;
    MaxVal = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRESSURE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(MaxVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getDefaultParamValue to fetch default
*            amplitude steps at value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - DefVal : Default amplitude steps at value supported.
******************************************************************************/
QString RecipeLabData::getDefaultParamValue(int mode)
{
    std::string  DefVal;

    switch(mode)
    {
    case RecipeEnum::TIME_IDX :

        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM);
        break;

    case RecipeEnum::ENERGY_IDX :
        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_ENERGY_PARAM);
        break;

    case RecipeEnum::PEAKPOWER_IDX :
        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_PEAK_POWER_PARAM);
        break;

        /*case RecipeEnum::GROUND_IDX :

        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_GROUND_DETECT_PARAM);
        break;

        case RecipeEnum::ABSDISTANCE_IDX :

        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEPAT_VALUE_1_PARAM);
        break;

    case RecipeEnum::COLDISTANCE_IDX :

        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEPAT_VALUE_1_PARAM);
        break;*/

    default :

        DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM);
        break;
    }

    return QString::fromLocal8Bit(DefVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getDefaultAmplitudeStepRamp to fetch default
*            amplitude steps ramp value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - DefVal : Default amplitude steps ramp value supported.
******************************************************************************/
QString RecipeLabData::getDefaultAmplitudeStepRamp()
{
    std::string  DefVal;
    DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEP_RAMP_1_PARAM);

    return QString::fromLocal8Bit(DefVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getDefaultAmplitudeStepTarget to fetch default
*            amplitude steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - DefVal : Default amplitude steps target value supported.
******************************************************************************/
QString RecipeLabData::getDefaultAmplitudeStepTarget()
{
    std::string DefVal;
    DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(DefVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the getDefaultPressureStepTarget to fetch default
*            Pressure steps target value supported.
*
* \param   - StepNo : Step number for which value to be fetch.
*
* \return  - DefVal : Default Pressure steps target value supported.
******************************************************************************/
QString RecipeLabData::getDefaultPressureStepTarget()
{
    std::string DefVal;
    DefVal = m_RecipeLabData->GetWeldRecipeParamDefaultValue(PRESSURE_STEP_TARGET_1_PARAM);

    return QString::fromLocal8Bit(DefVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of the setDefaultAmplitudeValues to fetch default
*            steps values.
*
* \param   - mode : The mode in which system is operating.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setDefaultAmplitudeValues(int mode)
{
    for(int i = 0 ; i < SUPPORTEDAMPLITUDESTEPS ; i++)
    {
        switch(mode)
        {
        case RecipeEnum::TIME_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM));
            break;

        case RecipeEnum::ENERGY_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_ENERGY_PARAM));
            break;

        case RecipeEnum::PEAKPOWER_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_PEAK_POWER_PARAM));
            break;

        case RecipeEnum::GROUND_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_GROUND_DETECT_PARAM));
            break;

        case RecipeEnum::ABSDISTANCE_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEPAT_VALUE_1_PARAM));
            break;

        case RecipeEnum::COLDISTANCE_IDX :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEPAT_VALUE_1_PARAM));
            break;

        default :

            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM));
            break;
        }

        m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepRamp = std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEP_RAMP_1_PARAM));

        m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepTarget = std::stoi(m_RecipeLabData->GetWeldRecipeParamDefaultValue(AMPLITUDE_STEP_TARGET_1_PARAM));

    }
}


/**************************************************************************//**
*
* \brief   - Role of the setDefaultPressureValues to fetch default
*            steps values.
*
* \param   - mode : The mode in which system is operating.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setDefaultPressureValues(int mode)
{
    for(int i = 0 ; i < SUPPORTEDPRESSURESTEPS ; i++)
    {
        switch(mode)
        {
        case RecipeEnum::TIME_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM));
            break;

        case RecipeEnum::ENERGY_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_ENERGY_PARAM));
            break;

        case RecipeEnum::PEAKPOWER_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_PEAK_POWER_PARAM));
            break;

        case RecipeEnum::GROUND_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_GROUND_DETECT_PARAM));
            break;

        case RecipeEnum::ABSDISTANCE_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(PRESSURE_STEPAT_VALUE_1_PARAM));
            break;

        case RecipeEnum::COLDISTANCE_IDX :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(PRESSURE_STEPAT_VALUE_1_PARAM));
            break;

        default :

            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue =
                    std::stof(m_RecipeLabData->GetWeldRecipeParamDefaultValue(MODE_VALUE_TIME_PARAM));
            break;
        }

        m_PressureStepDataACE.PressureStepParameters[i].PressureStepTarget = std::stoi(m_RecipeLabData->GetWeldRecipeParamDefaultValue(PRESSURE_STEP_TARGET_1_PARAM));
    }
}

/**************************************************************************//**
*
* \brief   - This function initiates amplitude step send request
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::onDonePressedForAmplitude()
{
    m_RecipeLabData->InitiateAmplitudeStepDataSendRequest(m_AmplitudeStepDataACE);
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - This function initiates pressure step send request
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::onDonePressedForPressure()
{
    m_RecipeLabData->InitiatePressureStepDataSendRequest(m_PressureStepDataACE);
    emit recipeLabDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the global suspect select status.
*
* \param   - None.
*
* \return  - m_IsGlobalSuspect : The global suspect select status.
******************************************************************************/
bool RecipeLabData::getIsGlobalSuspect() const
{
    return m_IsGlobalSuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the global suspect select status.
*
* \param   - IsGlobalSuspect : The global suspect select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsGlobalSuspect(const bool &IsGlobalSuspect)
{
    if(m_IsGlobalSuspect != IsGlobalSuspect)
    {
        m_IsGlobalSuspect = IsGlobalSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_LIMITS_ENABLED_PARAM, &m_IsGlobalSuspect);
        emit recipeLabDataChanged();
    }

}

/**************************************************************************//**
*
* \brief   - Below function returns the global reject select status.
*
* \param   - None.
*
* \return  - m_IsGlobalReject : The global reject select status.
******************************************************************************/
bool RecipeLabData::getIsGlobalReject() const
{
    return m_IsGlobalReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the global reject select status.
*
* \param   - IsGlobalReject : The global reject select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsGlobalReject(const bool &IsGlobalReject)
{
    if(m_IsGlobalReject != IsGlobalReject)
    {
        m_IsGlobalReject = IsGlobalReject;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_LIMITS_ENABLED_PARAM, &m_IsGlobalReject);
        emit recipeLabDataChanged();

    }

}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect time select status.
*
* \param   - None.
*
* \return  - m_IsSuspectTime : The suspect time select status.
******************************************************************************/
bool RecipeLabData::getIsSuspectTime() const
{
    return m_IsSuspectTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the select status of suspect time.
*
* \param   - IsSuspectTime : The suspect time select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsSuspectTime(const bool &IsSuspectTime)
{
    if(m_IsSuspectTime != IsSuspectTime)
    {
        m_IsSuspectTime = IsSuspectTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TIME_ENABLED_PARAM, &m_IsSuspectTime);
        emit recipeLabDataChanged();

    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the suspect energy.
*
* \param   - None.
*
* \return  - m_IsSuspectEnergy : The select status of the suspect energy.
******************************************************************************/
bool RecipeLabData::getIsSuspectEnergy() const
{
   return m_IsSuspectEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function updates the select status of the suspect energy.
*
* \param   - IsSuspectEnergy : The select status of the suspect energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsSuspectEnergy(const bool &IsSuspectEnergy)
{
    if(m_IsSuspectEnergy != IsSuspectEnergy)
    {
        m_IsSuspectEnergy = IsSuspectEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ENERGY_ENABLED_PARAM, &m_IsSuspectEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the suspect peak power.
*
* \param   - None.
*
* \return  - AmplitudeStepAt : The select status of suspect peak power.
******************************************************************************/
bool RecipeLabData::getIsSuspectPeakPower() const
{
    return m_IsSuspectPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function update suspect peak power.
*
* \param   - IsSuspectPeakPower : The suspect peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsSuspectPeakPower(const bool &IsSuspectPeakPower)
{
    if(m_IsSuspectPeakPower != IsSuspectPeakPower)
    {
        m_IsSuspectPeakPower = IsSuspectPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_PEAKPOWER_ENABLED_PARAM, &m_IsSuspectPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the suspect frequncy.
*
* \param   - None.
*
* \return  - m_IsSuspectFrequency : The the select status of the suspect frequncy.
******************************************************************************/
bool RecipeLabData::getIsSuspectFrequency() const
{
   return m_IsSuspectFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates the select status of the suspect frequncy.
*
* \param   - IsSuspectFrequency : The select status of the suspect frequncy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsSuspectFrequency(const bool &IsSuspectFrequency)
{
    if(m_IsSuspectFrequency != IsSuspectFrequency)
    {
        m_IsSuspectFrequency = IsSuspectFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_FREQUENCY_ENABLED_PARAM, &m_IsSuspectFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the reject time.
*
* \param   - None.
*
* \return  - m_IsRejectTime : The status of the reject time.
******************************************************************************/
bool RecipeLabData::getIsRejectTime() const
{
    return m_IsRejectTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the status of the reject time.
*
* \param   - IsRejectTime : The status of the reject time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsRejectTime(const bool &IsRejectTime)
{
    if(m_IsRejectTime != IsRejectTime)
    {
        m_IsRejectTime = IsRejectTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TIME_ENABLED_PARAM, &m_IsRejectTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the reject energy.
*
* \param   - None.
*
* \return  - m_IsRejectEnergy : The select status of the reject energy.
******************************************************************************/
bool RecipeLabData::getIsRejectEnergy() const
{
    return m_IsRejectEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function updates select status of the reject energy.
*
* \param   - IsRejectEnergy : The select status of the reject energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsRejectEnergy(const bool &IsRejectEnergy)
{
    if(m_IsRejectEnergy != IsRejectEnergy)
    {
        m_IsRejectEnergy = IsRejectEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ENERGY_ENABLED_PARAM, &m_IsRejectEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the reject peak power.
*
* \param   - None.
*
* \return  - m_IsRejectPeakPower : The select status of the reject peak power.
******************************************************************************/
bool RecipeLabData::getIsRejectPeakPower() const
{
    return m_IsRejectPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function updates select status of the reject peak power.
*
* \param   - IsRejectPeakPower : The select status of the reject peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsRejectPeakPower(const bool &IsRejectPeakPower)
{
    if(m_IsRejectPeakPower != IsRejectPeakPower)
    {
        m_IsRejectPeakPower = IsRejectPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_PEAKPOWER_ENABLED_PARAM, &m_IsRejectPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the select status of the reject frequency.
*
* \param   - None.
*
* \return  - m_IsRejectFrequency : The select status of the reject frequency.
******************************************************************************/
bool RecipeLabData::getIsRejectFrequency() const
{
   return m_IsRejectFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates select status of the reject frequency.
*
* \param   - IsRejectFrequency : The select status of the reject frequency.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsRejectFrequency(const bool &IsRejectFrequency)
{
    if(m_IsRejectFrequency != IsRejectFrequency)
    {
        m_IsRejectFrequency = IsRejectFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_FREQUENCY_ENABLED_PARAM, &m_IsRejectFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect low time.
*
* \param   - None.
*
* \return  - m_SuspectLowTime : The suspect low time.
******************************************************************************/
float RecipeLabData::getSuspectLowTime() const
{
    return m_SuspectLowTime ;
}

/**************************************************************************//**
*
* \brief   - Below function updates the suspect low time.
*
* \param   - SuspectLowTime : The suspect low time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowTime(const float &SuspectLowTime)
{
    if(m_SuspectLowTime != SuspectLowTime)
    {
        m_SuspectLowTime = SuspectLowTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TIME_LOW_LIMIT_PARAM, &m_SuspectLowTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect high time.
*
* \param   - None.
*
* \return  - m_SuspectHighTime : The suspect high time.
******************************************************************************/
float RecipeLabData::getSuspectHighTime() const
{
    return m_SuspectHighTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates suspect high time.
*
* \param   - SuspectHighTime : The suspect high time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighTime(const float &SuspectHighTime)
{
    if(m_SuspectHighTime != SuspectHighTime)
    {
        m_SuspectHighTime = SuspectHighTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TIME_HIGH_LIMIT_PARAM, &m_SuspectHighTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect low energy.
*
* \param   - None.
*
* \return  - m_SuspectLowEnergy : The suspect low energy.
******************************************************************************/
float RecipeLabData::getSuspectLowEnergy() const
{
    return m_SuspectLowEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function update suspect low energy.
*
* \param   - SuspectLowEnergy : The suspect low energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowEnergy(const float &SuspectLowEnergy)
{
    if(m_SuspectLowEnergy != SuspectLowEnergy)
    {
        m_SuspectLowEnergy = SuspectLowEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ENERGY_LOW_LIMIT_PARAM, &m_SuspectLowEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect high energy.
*
* \param   - None.
*
* \return  - m_SuspectHighEnergy : The suspect high energy.
******************************************************************************/
float RecipeLabData::getSuspectHighEnergy() const
{
    return m_SuspectHighEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function updates suspect high energy.
*
* \param   - SuspectHighEnergy : The suspect high energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighEnergy(const float &SuspectHighEnergy)
{
    if(m_SuspectHighEnergy != SuspectHighEnergy)
    {
        m_SuspectHighEnergy = SuspectHighEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ENERGY_HIGH_LIMIT_PARAM, &m_SuspectHighEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect low peak power.
*
* \param   - None.
*
* \return  - m_SuspectLowPeakPower : The suspect low peak power.
******************************************************************************/
float RecipeLabData::getSuspectLowPeakPower() const
{
    return m_SuspectLowPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function updates the suspect low peak power.
*
* \param   - SuspectLowPeakPower : The suspect low peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowPeakPower(const float &SuspectLowPeakPower)
{
    if(m_SuspectLowPeakPower != SuspectLowPeakPower)
    {
        m_SuspectLowPeakPower = SuspectLowPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_PEAKPOWER_LOW_LIMIT_PARAM, &m_SuspectLowPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect high peak power.
*
* \param   - None.
*
* \return  - m_SuspectHighPeakPower : The suspect high peak power.
******************************************************************************/
float RecipeLabData::getSuspectHighPeakPower() const
{
    return m_SuspectHighPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function updates suspect high peak power.
*
* \param   - SuspectHighPeakPower : The suspect high peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighPeakPower(const float &SuspectHighPeakPower)
{
    if(m_SuspectHighPeakPower != SuspectHighPeakPower)
    {
        m_SuspectHighPeakPower = SuspectHighPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_PEAKPOWER_HIGH_LIMIT_PARAM, &m_SuspectHighPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect low frequency.
*
* \param   - None.
*
* \return  - m_SuspectLowFrequency : The suspect low frequency.
******************************************************************************/
float RecipeLabData::getSuspectLowFrequency() const
{
    return m_SuspectLowFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates the suspect low frequency.
*
* \param   - SuspectLowFrequency : The suspect low frequency.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowFrequency(const float &SuspectLowFrequency)
{
    if(m_SuspectLowFrequency != SuspectLowFrequency)
    {
        m_SuspectLowFrequency = SuspectLowFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_FREQUENCY_LOW_LIMIT_PARAM, &m_SuspectLowFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the suspect high frequency.
*
* \param   - None.
*
* \return  - m_SuspectHighFrequency : The suspect high frequency.
******************************************************************************/
float RecipeLabData::getSuspectHighFrequency() const
{
    return m_SuspectHighFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates suspect high frequency.
*
* \param   - SuspectHighFrequency : The suspect high frequency.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighFrequency(const float &SuspectHighFrequency)
{
    if(m_SuspectHighFrequency != SuspectHighFrequency)
    {
        m_SuspectHighFrequency = SuspectHighFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_FREQUENCY_HIGH_LIMIT_PARAM, &m_SuspectHighFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject low time.
*
* \param   - None.
*
* \return  - m_RejectLowTime : The reject low time.
******************************************************************************/
float RecipeLabData::getRejectLowTime() const
{
    return m_RejectLowTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject low time.
*
* \param   - RejectLowTime : The reject low time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowTime(const float &RejectLowTime)
{
    if(m_RejectLowTime != RejectLowTime)
    {
        m_RejectLowTime = RejectLowTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TIME_LOW_LIMIT_PARAM, &m_RejectLowTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject high time.
*
* \param   - None.
*
* \return  - m_RejectHighTime : The reject high time.
******************************************************************************/
float RecipeLabData::getRejectHighTime() const
{
   return m_RejectHighTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates reject high time.
*
* \param   - RejectHighTime : The reject high time.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighTime(const float &RejectHighTime)
{
    if(m_RejectHighTime != RejectHighTime)
    {
        m_RejectHighTime = RejectHighTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TIME_HIGH_LIMIT_PARAM, &m_RejectHighTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject low energy.
*
* \param   - None.
*
* \return  - m_RejectLowEnergy : The reject low energy.
******************************************************************************/
float RecipeLabData::getRejectLowEnergy() const
{
   return m_RejectLowEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject low energy.
*
* \param   - RejectLowEnergy : The reject low energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowEnergy(const float &RejectLowEnergy)
{
    if(m_RejectLowEnergy != RejectLowEnergy)
    {
        m_RejectLowEnergy = RejectLowEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ENERGY_LOW_LIMIT_PARAM, &m_RejectLowEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject high energy.
*
* \param   - None.
*
* \return  - m_RejectHighEnergy : The reject high energy.
******************************************************************************/
float RecipeLabData::getRejectHighEnergy() const
{
    return m_RejectHighEnergy;
}

/**************************************************************************//**
*
* \brief   - Below function updates reject high energy.
*
* \param   - RejectHighEnergy : The reject high energy.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighEnergy(const float &RejectHighEnergy)
{
    if(m_RejectHighEnergy != RejectHighEnergy)
    {
        m_RejectHighEnergy = RejectHighEnergy;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ENERGY_HIGH_LIMIT_PARAM, &m_RejectHighEnergy);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject low peak power.
*
* \param   - None.
*
* \return  - m_RejectLowPeakPower : The reject low peak power.
******************************************************************************/
float RecipeLabData::getRejectLowPeakPower() const
{
    return m_RejectLowPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function updates reject low peak power.
*
* \param   - RejectLowPeakPower : The reject low peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowPeakPower(const float &RejectLowPeakPower)
{
    if(m_RejectLowPeakPower != RejectLowPeakPower)
    {
        m_RejectLowPeakPower = RejectLowPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_PEAKPOWER_LOW_LIMIT_PARAM, &m_RejectLowPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject high peak power.
*
* \param   - None.
*
* \return  - m_RejectHighPeakPower : The reject high peak power.
******************************************************************************/
float RecipeLabData::getRejectHighPeakPower() const
{
    return m_RejectHighPeakPower;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject high peak power.
*
* \param   - RejectLowPeakPower : The reject high peak power.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighPeakPower(const float &RejectHighPeakPower)
{
    if(m_RejectHighPeakPower != RejectHighPeakPower)
    {
        m_RejectHighPeakPower = RejectHighPeakPower;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_PEAKPOWER_HIGH_LIMIT_PARAM, &m_RejectHighPeakPower);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject low frequency.
*
* \param   - None.
*
* \return  - m_RejectLowFrequency : The reject low frequency.
******************************************************************************/
float RecipeLabData::getRejectLowFrequency() const
{
    return m_RejectLowFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates reject low frequency.
*
* \param   - RejectLowFrequency : The reject low frequency.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowFrequency(const float &RejectLowFrequency)
{
    if(m_RejectLowFrequency != RejectLowFrequency)
    {
        m_RejectLowFrequency = RejectLowFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_FREQUENCY_LOW_LIMIT_PARAM, &m_RejectLowFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the reject high frequency.
*
* \param   - None.
*
* \return  - m_RejectHighFrequency : The reject high frequency.
******************************************************************************/
float RecipeLabData::getRejectHighFrequency() const
{
   return m_RejectHighFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject high frequency.
*
* \param   - RejectHighFrequency : The reject high frequency.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighFrequency(const float &RejectHighFrequency)
{
    if(m_RejectHighFrequency != RejectHighFrequency)
    {
        m_RejectHighFrequency = RejectHighFrequency;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_FREQUENCY_HIGH_LIMIT_PARAM, &m_RejectHighFrequency);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Abs Dist suspect select status.
*
* \param   - None.
*
* \return  - m_IsAbsDistSuspect : The Abs Dist suspect select status.
******************************************************************************/
bool RecipeLabData::getIsAbsDistSuspect() const
{
    return m_IsAbsDistSuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Abs Distance status.
*
* \param   - IsAbsDistSuspect : The Abs Distance suspect status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsAbsDistSuspect(const bool &IsAbsDistSuspect)
{
    if(m_IsAbsDistSuspect != IsAbsDistSuspect)
    {
        m_IsAbsDistSuspect = IsAbsDistSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ABS_DISTANCE_ENABLED_PARAM, &m_IsAbsDistSuspect);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Abs Distance Reject status.
*
* \param   - None.
*
* \return  - m_IsAbsDistReject : The Abs Distance Reject status.
******************************************************************************/
bool RecipeLabData::getIsAbsDistReject() const
{
    return m_IsAbsDistReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Abs Distance Reject  status.
*
* \param   - IsGlobalSuspect : The Abs Distance Reject status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsAbsDistReject(const bool &IsIsAbsDistReject)
{
    if(m_IsAbsDistReject != IsIsAbsDistReject)
    {
        m_IsAbsDistReject = IsIsAbsDistReject;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ABS_DISTANCE_ENABLED_PARAM, &m_IsAbsDistReject);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Collapse Distance suspect status.
*
* \param   - None.
*
* \return  - m_IsCollapseDistSuspect : The Collapse Distance suspect  status.
******************************************************************************/
bool RecipeLabData::getIsCollapseDistSuspect() const
{
    return m_IsCollapseDistSuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the global suspect select status.
*
* \param   - IsCollapseDistSuspect : The Collapse Distance suspect select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsCollapseDistSuspect(const bool &IsCollapseDistSuspect)
{
    if(m_IsCollapseDistSuspect != IsCollapseDistSuspect)
    {
        m_IsCollapseDistSuspect = IsCollapseDistSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_COLLAPSE_DISTANCE_ENABLED_PARAM, &m_IsCollapseDistSuspect);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Collapse Distance suspect status.
*
* \param   - None.
*
* \return  - m_IsCollapseDistReject : The Collapse Distance suspect status.
******************************************************************************/
bool RecipeLabData::getIsCollapseDistReject() const
{
    return m_IsCollapseDistReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Collapse Distance suspect select status.
*
* \param   - IsCollapseDistSuspect : The Collapse Distance suspect select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsCollapseDistReject(const bool &IsCollapseDistSuspect)
{
    if(m_IsCollapseDistReject != IsCollapseDistSuspect)
    {
        m_IsCollapseDistReject = IsCollapseDistSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_COLLAPSE_DISTANCE_ENABLED_PARAM, &m_IsCollapseDistReject);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Trigger Distance suspect status.
*
* \param   - None.
*
* \return  - m_IsTriggerDistSuspect : The Trigger Distance suspect status.
******************************************************************************/
bool RecipeLabData::getIsTriggerDistSuspect() const
{
    return m_IsTriggerDistSuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Trigger Distance suspect status.
*
* \param   - IsTriggerDistSuspect : The Trigger Distance suspect status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsTriggerDistSuspect(const bool &IsTriggerDistSuspect)
{
    if(m_IsTriggerDistSuspect != IsTriggerDistSuspect)
    {
        m_IsTriggerDistSuspect = IsTriggerDistSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TRIGGER_DISTANCE_ENABLED_PARAM, &m_IsTriggerDistSuspect);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Trigger Distance Reject status.
*
* \param   - None.
*
* \return  - m_IsTriggerDistReject : The Trigger Distance Reject  status.
******************************************************************************/
bool RecipeLabData::getIsTriggerDistReject() const
{
    return m_IsTriggerDistReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Trigger Distance Reject status.
*
* \param   - IsTriggerDistReject : The Trigger Distance Reject status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsTriggerDistReject(const bool &IsTriggerDistReject)
{
    if(m_IsTriggerDistReject != IsTriggerDistReject)
    {
        m_IsTriggerDistReject = IsTriggerDistReject;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TRIGGER_DISTANCE_ENABLED_PARAM, &m_IsTriggerDistReject);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity suspect  status.
*
* \param   - None.
*
* \return  - m_IsVelocitySuspect : The Velocity suspect  status.
******************************************************************************/
bool RecipeLabData::getIsVelocitySuspect() const
{
    return m_IsVelocitySuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Velocity suspect  status.
*
* \param   - IsVelocitySuspect : The Velocity suspect  status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsVelocitySuspect(const bool &IsVelocitySuspect)
{
    if(m_IsVelocitySuspect != IsVelocitySuspect)
    {
        m_IsVelocitySuspect = IsVelocitySuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_VELOCITY_ENABLED_PARAM, &m_IsVelocitySuspect);
        emit recipeLabDataChanged();
    }

}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity Reject status.
*
* \param   - None.
*
* \return  - m_IsVelocityReject : The Velocity Reject status.
******************************************************************************/
bool RecipeLabData::getIsVelocityReject() const
{
    return m_IsVelocityReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Velocity Reject select status.
*
* \param   - IsVelocityReject : The Velocity Reject select status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsVelocityReject(const bool &IsVelocityReject)
{
    if(m_IsVelocityReject != IsVelocityReject)
    {
        m_IsVelocityReject = IsVelocityReject;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_VELOCITY_ENABLED_PARAM, &m_IsVelocityReject);
        emit recipeLabDataChanged();
    }

}

/**************************************************************************//**
*
* \brief   - Below function returns the EndWeldForce suspect status.
*
* \param   - None.
*
* \return  - m_IsEndWeldForceSuspect : The EndWeldForce suspect status.
******************************************************************************/
bool RecipeLabData::getIsEndWeldForceSuspect() const
{
    return m_IsEndWeldForceSuspect;
}

/**************************************************************************//**
*
* \brief   - Below function updates the EndWeldForce suspect status.
*
* \param   - IsEndWeldForceSuspect : The EndWeldForce suspect status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsEndWeldForceSuspect(const bool &IsEndWeldForceSuspect)
{
    if(m_IsEndWeldForceSuspect != IsEndWeldForceSuspect)
    {
        m_IsEndWeldForceSuspect = IsEndWeldForceSuspect;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_END_WELD_FORCE_ENABLED_PARAM, &m_IsEndWeldForceSuspect);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the EndWeldForce Reject status.
*
* \param   - None.
*
* \return  - m_IsEndWeldForceReject : The global EndWeldForce Reject status.
******************************************************************************/
bool RecipeLabData::getIsEndWeldForceReject() const
{
    return m_IsEndWeldForceReject;
}

/**************************************************************************//**
*
* \brief   - Below function updates the EndWeldForce Reject  status.
*
* \param   - IsEndWeldForceReject : The EndWeldForce global Reject  status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateIsEndWeldForceReject(const bool &IsEndWeldForceReject)
{
    if(m_IsEndWeldForceReject != IsEndWeldForceReject)
    {
        m_IsEndWeldForceReject = IsEndWeldForceReject;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_END_WELD_FORCE_ENABLED_PARAM, &m_IsEndWeldForceReject);
        emit recipeLabDataChanged();
    }
}


/**************************************************************************//**
*
* \brief   - Below function returns the Low Limit Abs Distance SUspect.
*
* \param   - None.
*
* \return  - m_SuspectLowAbsDist : The Low Limit Abs Distance SUspecty.
******************************************************************************/
float RecipeLabData::getSuspectLowAbsDist() const
{
    return m_SuspectLowAbsDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Low Limit Abs Distance SUspect.
*
* \param   - SuspectLowAbsDist : The Low Limit Abs Distance SUspect.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowAbsDist(const float &SuspectLowAbsDist)
{
    if(m_SuspectLowAbsDist != SuspectLowAbsDist)
    {
        m_SuspectLowAbsDist = SuspectLowAbsDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM, &m_SuspectLowAbsDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the High Limit Abs Distance SUspect.
*
* \param   - None.
*
* \return  - m_SuspectHighAbsDist : The High Limit Abs Distance SUspect.
******************************************************************************/
float RecipeLabData::getSuspectHighAbsDist() const
{
    return m_SuspectHighAbsDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the High Limit Abs Distance SUspect.
*
* \param   - SuspectHighAbsDist : The High Limit Abs Distance SUspect.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighAbsDist(const float &SuspectHighAbsDist)
{
    if(m_SuspectHighAbsDist != SuspectHighAbsDist)
    {
        m_SuspectHighAbsDist = SuspectHighAbsDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM, &m_SuspectHighAbsDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Low Limit Abs Distance Reject.
*
* \param   - None.
*
* \return  - m_RejectLowAbsDist : The Low Limit Abs Distance Reject.
******************************************************************************/
float RecipeLabData::getRejectLowAbsDist() const
{
    return m_RejectLowAbsDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Low Limit Abs Distance Reject.
*
* \param   - RejectLowAbsDist : The Low Limit Abs Distance Reject.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowAbsDist(const float &RejectLowAbsDist)
{
    if(m_RejectLowAbsDist != RejectLowAbsDist)
    {
        m_RejectLowAbsDist = RejectLowAbsDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM, &m_RejectLowAbsDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the High Limit Abs Distance Reject.
*
* \param   - None.
*
* \return  - m_RejectHighAbsDist : The High Limit Abs Distance Reject.
******************************************************************************/
float RecipeLabData::getRejectHighAbsDist() const
{
    return m_RejectHighAbsDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates High Limit Abs Distance Reject.
*
* \param   - RejectHighAbsDist : The High Limit Abs Distance Reject.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighAbsDist(const float &RejectHighAbsDist)
{
    if(m_RejectHighAbsDist != RejectHighAbsDist)
    {
        m_RejectHighAbsDist = RejectHighAbsDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM, &m_RejectHighAbsDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Low Limit Collapse Distance Suspect.
*
* \param   - None.
*
* \return  - m_SuspectLowCollapseDist : The Low Limit Collapse Distance Suspect.
******************************************************************************/
float RecipeLabData::getSuspectLowCollapseDist() const
{
    return m_SuspectLowCollapseDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Low Limit Collapse Distance Suspect.
*
* \param   - SuspectLowCollapseDist : The Low Limit Collapse Distance Suspect.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowCollapseDist(const float &SuspectLowCollapseDist)
{
    if(m_SuspectLowCollapseDist != SuspectLowCollapseDist)
    {
        m_SuspectLowCollapseDist = SuspectLowCollapseDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM, &m_SuspectLowCollapseDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the High Limit Collapse Distance Suspect.
*
* \param   - None.
*
* \return  - m_SuspectHighCollapseDist : The High Limit Collapse Distance Suspect.
******************************************************************************/
float RecipeLabData::getSuspectHighCollapseDist() const
{
    return m_SuspectHighCollapseDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the High Limit Collapse Distance Suspect.
*
* \param   - RejectHighFrequency : The High Limit Collapse Distance Suspect.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighCollapseDist(const float &SuspectHighCollapseDist)
{
    if(m_SuspectHighCollapseDist != SuspectHighCollapseDist)
    {
        m_SuspectHighCollapseDist = SuspectHighCollapseDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM, &m_SuspectHighCollapseDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Low Limit Collapse Distance Reject.
*
* \param   - None.
*
* \return  - m_RejectLowCollapseDist : The Low Limit Collapse Distance Reject.
******************************************************************************/
float RecipeLabData::getRejectLowCollapseDist() const
{
    return m_RejectLowCollapseDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Low Limit Collapse Distance Reject.
*
* \param   - RejectLowCollapseDist : The Low Limit Collapse Distance Reject.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowCollapseDist(const float &RejectLowCollapseDist)
{
    if(m_RejectLowCollapseDist != RejectLowCollapseDist)
    {
        m_RejectLowCollapseDist = RejectLowCollapseDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM, &m_RejectLowCollapseDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the High Limit Collapse Distance Reject.
*
* \param   - None.
*
* \return  - m_RejectHighCollapseDist : The High Limit Collapse Distance Reject.
******************************************************************************/
float RecipeLabData::getRejectHighCollapseDist() const
{
    return m_RejectHighCollapseDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the High Limit Collapse Distance Reject.
*
* \param   - RejectHighCollapseDist  : The High Limit Collapse Distance Reject.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighCollapseDist(const float &RejectHighCollapseDist )
{
    if(m_RejectHighCollapseDist != RejectHighCollapseDist )
    {
        m_RejectHighCollapseDist = RejectHighCollapseDist ;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM, &m_RejectHighCollapseDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Low Limit Trigger Distance Suspect.
*
* \param   - None.
*
* \return  - m_SuspectLowTriggerDist : The Low Limit Trigger Distance Suspect.
******************************************************************************/
float RecipeLabData::getSuspectLowTriggerDist() const
{
    return m_SuspectLowTriggerDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates Suspect Low Limit Trigger Distance.
*
* \param   - SuspectLowTriggerDist : The Suspect Low Limit Trigger Distance.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowTriggerDist(const float &SuspectLowTriggerDist)
{
    if(m_SuspectLowTriggerDist != SuspectLowTriggerDist)
    {
        m_SuspectLowTriggerDist = SuspectLowTriggerDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM, &m_SuspectLowTriggerDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Suspect HIgh Limit Trigger Distance.
*
* \param   - None.
*
* \return  - m_SuspectHighTriggerDist : The Suspect high Limit Trigger Distance.
******************************************************************************/
float RecipeLabData::getSuspectHighTriggerDist() const
{
    return m_SuspectHighTriggerDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Suspect high Limit Trigger Distance.
*
* \param   - SuspectHighTriggerDist : The Suspect high Limit Trigger Distance.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighTriggerDist(const float &SuspectHighTriggerDist)
{
    if(m_SuspectHighTriggerDist != SuspectHighTriggerDist)
    {
        m_SuspectHighTriggerDist = SuspectHighTriggerDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM, &m_SuspectHighTriggerDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the reject Low Limit Trigger Distance.
*
* \param   - None.
*
* \return  - m_RejectLowTriggerDist : The reject Low Limit Trigger Distance.
******************************************************************************/
float RecipeLabData::getRejectLowTriggerDist() const
{
    return m_RejectLowTriggerDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject  Low Limit Trigger Distance.
*
* \param   - RejectLowTriggerDist : The reject  Low Limit Trigger Distance.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowTriggerDist(const float &RejectLowTriggerDist)
{
    if(m_RejectLowTriggerDist != RejectLowTriggerDist)
    {
        m_RejectLowTriggerDist = RejectLowTriggerDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM, &m_RejectLowTriggerDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the reject high Limit Trigger Distance.
*
* \param   - None.
*
* \return  - m_RejectHighTriggerDist : The reject high Limit Trigger Distance.
******************************************************************************/
float RecipeLabData::getRejectHighTriggerDist() const
{
    return m_RejectHighTriggerDist;
}

/**************************************************************************//**
*
* \brief   - Below function updates the reject high Limit Trigger Distance.
*
* \param   - RejectHighTriggerDist : The reject high Limit Trigger Distance.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighTriggerDist(const float &RejectHighTriggerDist)
{
    if(m_RejectHighTriggerDist != RejectHighTriggerDist)
    {
        m_RejectHighTriggerDist = RejectHighTriggerDist;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM, &m_RejectHighTriggerDist);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Suspect Low Limit Velocity.
*
* \param   - None.
*
* \return  - m_SuspectLowVelocity : The Suspect Low Limit Velocity .
******************************************************************************/
float RecipeLabData::getSuspectLowVelocity() const
{
    return m_SuspectLowVelocity;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Suspect Low Limit Velocity..
*
* \param   - SuspectLowVelocity : The Suspect Low Limit Velocity..
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowVelocity(const float &SuspectLowVelocity)
{
    if(m_SuspectLowVelocity != SuspectLowVelocity)
    {
        m_SuspectLowVelocity = SuspectLowVelocity;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_VELOCITY_LOW_LIMIT_PARAM, &m_SuspectLowVelocity);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Suspect High Limit Velocity.
*
* \param   - None.
*
* \return  - m_SuspectHighVelocity : The Suspect High Limit Velocity.
******************************************************************************/
float RecipeLabData::getSuspectHighVelocity() const
{
    return m_SuspectHighVelocity;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Suspect High Limit Velocity.
*
* \param   - SuspectHighVelocity : The Suspect High Limit Velocity.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighVelocity(const float &SuspectHighVelocity )
{
    if(m_SuspectHighVelocity != SuspectHighVelocity )
    {
        m_SuspectHighVelocity = SuspectHighVelocity ;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_VELOCITY_HIGH_LIMIT_PARAM, &m_SuspectHighVelocity);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Reject Low Limit Velocity.
*
* \param   - None.
*
* \return  - m_RejectLowVelocity : The Reject Low Limit Velocity.
******************************************************************************/
float RecipeLabData::getRejectLowVelocity() const
{
    return m_RejectLowVelocity;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Reject Low Limit Velocity.
*
* \param   - RejectLowVelocity : The Reject Low Limit Velocity.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowVelocity(const float &RejectLowVelocity)
{
    if(m_RejectLowVelocity != RejectLowVelocity)
    {
        m_RejectLowVelocity = RejectLowVelocity;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_VELOCITY_LOW_LIMIT_PARAM, &m_RejectLowVelocity);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Reject High Limit Velocity.
*
* \param   - None.
*
* \return  - m_RejectHighVelocity : The Reject High Limit Velocity.
******************************************************************************/
float RecipeLabData::getRejectHighVelocity() const
{
    return m_RejectHighVelocity;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Reject High Limit Velocity.
*
* \param   - RejectHighVelocity : The Reject High Limit Velocity.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighVelocity(const float &RejectHighVelocity)
{
    if(m_RejectHighVelocity != RejectHighVelocity)
    {
        m_RejectHighVelocity = RejectHighVelocity;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_VELOCITY_HIGH_LIMIT_PARAM, &m_RejectHighVelocity);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Suspect Low Limit End WeldForce.
*
* \param   - None.
*
* \return  - m_SuspectLowEndWeldForce : The Suspect Low Limit End WeldForce.
******************************************************************************/
float RecipeLabData::getSuspectLowEndWeldForce() const
{
    return m_SuspectLowEndWeldForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Suspect Low Limit End WeldForce.
*
* \param   - SuspectLowEndWeldForce : The Suspect Low Limit End WeldForce.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectLowEndWeldForce(const float &SuspectLowEndWeldForce)
{
    if(m_SuspectLowEndWeldForce != SuspectLowEndWeldForce)
    {
        m_SuspectLowEndWeldForce = SuspectLowEndWeldForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM, &m_SuspectLowEndWeldForce);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Suspect High Limit End WeldForce.
*
* \param   - None.
*
* \return  - m_SuspectHighEndWeldForce : The Suspect High Limit End WeldForce.
******************************************************************************/
float RecipeLabData::getSuspectHighEndWeldForce() const
{
    return m_SuspectHighEndWeldForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Suspect High Limit End WeldForce.
*
* \param   - RejectHighFrequency : The Suspect High Limit End WeldForce.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateSuspectHighEndWeldForce(const float &SuspectHighEndWeldForce)
{
    if(m_SuspectHighEndWeldForce != SuspectHighEndWeldForce)
    {
        m_SuspectHighEndWeldForce = SuspectHighEndWeldForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM, &m_SuspectHighEndWeldForce);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Reject Low Limit End WeldForce.
*
* \param   - None.
*
* \return  - m_RejectLowEndWeldForce : The Reject Low Limit End WeldForce.
******************************************************************************/
float RecipeLabData::getRejectLowEndWeldForce() const
{
    return m_RejectLowEndWeldForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Reject Low Limit End WeldForce.
*
* \param   - RejectLowEndWeldForce : The Reject Low Limit End WeldForce.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectLowEndWeldForce(const float &RejectLowEndWeldForce)
{
    if(m_RejectLowEndWeldForce != RejectLowEndWeldForce)
    {
        m_RejectLowEndWeldForce = RejectLowEndWeldForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM, &m_RejectLowEndWeldForce);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Reject High Limit End WeldForce.
*
* \param   - None.
*
* \return  - m_RejectHighEndWeldForce : The Reject High Limit End WeldForce.
******************************************************************************/
float RecipeLabData::getRejectHighEndWeldForce() const
{
    return m_RejectHighEndWeldForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Reject High Limit End WeldForce.
*
* \param   - RejectHighEndWeldForce : The Reject High Limit End WeldForce.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateRejectHighEndWeldForce(const float &RejectHighEndWeldForce)
{
    if(m_RejectHighEndWeldForce != RejectHighEndWeldForce)
    {
        m_RejectHighEndWeldForce = RejectHighEndWeldForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM, &m_RejectHighEndWeldForce);
        emit recipeLabDataChanged();
    }
}


/**************************************************************************//**
*
* \brief   - Role of the slot OnRecipeLabDataUpdated to update the recipe lab data.
*
* \param   - RecipeLabData_Obj : Object pointer of type WeldRecipeACE.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::OnRecipeLabDataUpdated(WeldRecipeACE *RecipeLabData_Obj, int WelderId)
{
    /*Local copy of received data*/
    m_RecipeLabData = RecipeLabData_Obj;

    if(m_RecipeLabData->IsActiveWeldRecipeUpdated() || (m_ActiveWelderId != WelderId))
    {
    	WeldRecipeACEStruct m_WeldModeLabData;
        m_WeldModeLabData = m_RecipeLabData->GetActiveWeldRecipeData();

        m_WeldRecipeNumber = m_WeldModeLabData.WeldRecipeNumber;
        m_WeldRecipeVersionNumber = m_WeldModeLabData.WeldRecipeVersionNumber;
        m_WeldRecipeName = m_WeldModeLabData.WeldRecipeName;
        m_WeldMode = m_WeldModeLabData.WeldMode;
        m_ModeValueTime = m_WeldModeLabData.ModeValueTime;
        m_ModeValueEnergy = m_WeldModeLabData.ModeValueEnergy;
        m_ModeValuePeakPower = m_WeldModeLabData.ModeValuePeakPower;
        m_ModeValueGroundDetect = m_WeldModeLabData.ModeValueGroundDetect;
        m_ModeValueAbsDistance = m_WeldModeLabData.ModeValueAbsoluteDistance;
        m_ModeValueColDistance =m_WeldModeLabData.ModeValueCollapseDistance;
        m_CycleCount = m_WeldModeLabData.CycleCounterData.CycleCount;
        m_CyclesOKCount = m_WeldModeLabData.CycleCounterData.CyclesOKCount;
        m_RejectCount = m_WeldModeLabData.CycleCounterData.RejectCount;
        m_WeldPressure = m_WeldModeLabData.WeldPressure;
        m_HoldPressure = m_WeldModeLabData.HoldPressure;
        m_FlowRate = m_WeldModeLabData.FlowRate;
        m_HoldTime = m_WeldModeLabData.HoldTime;
        m_MaxWeldTimeout = m_WeldModeLabData.MaxWeldTimeout;
        m_WeldAmplitude = m_WeldModeLabData.WeldAmplitude;
        m_IsRecipeSaved = m_WeldModeLabData.IsSaved;
        m_TriggerForce=m_WeldModeLabData.TriggerData.TriggerForce;
        m_AmplitudeStepDataACE.NumAmplitudeSteps = m_WeldModeLabData.NumAmplitudeSteps;
        /*For amplitude stepping data read*/
        m_AmplitudeStepDataACE.AmplitudeStepAt = m_WeldModeLabData.AmplitudeStepAt;
        /*To avoid incorrect step values to be entered of unused steps*/
        setDefaultAmplitudeValues(m_AmplitudeStepDataACE.AmplitudeStepAt);

        for(int i = 0; i < AmplitudeAndPressureStepsSupport::GetSupportedAmplitudeStepsFromJSON(); i++)
        {
            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepAtValue = m_WeldModeLabData.AmplitudeStepParameters[i].AmplitudeStepAtValue ;
            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepRamp = m_WeldModeLabData.AmplitudeStepParameters[i].AmplitudeStepRamp;
            m_AmplitudeStepDataACE.AmplitudeStepParameters[i].AmplitudeStepTarget = m_WeldModeLabData.AmplitudeStepParameters[i].AmplitudeStepTarget;
        }

        m_PressureStepDataACE.NumPressureSteps = m_WeldModeLabData.NumPressureSteps;
        /*For pressure stepping data read*/
        m_PressureStepDataACE.PressureStepAt = m_WeldModeLabData.PressureStepAt;
        /*To avoid incorrect step values to be entered of unused steps*/
        setDefaultPressureValues(m_PressureStepDataACE.PressureStepAt);

        for(int i = 0; i < AmplitudeAndPressureStepsSupport::GetSupportedPressureStepsFromJSON(); i++)
        {
            m_PressureStepDataACE.PressureStepParameters[i].PressureStepAtValue = m_WeldModeLabData.PressureStepParameters[i].PressureStepAtValue ;
            m_PressureStepDataACE.PressureStepParameters[i].PressureStepTarget = m_WeldModeLabData.PressureStepParameters[i].PressureStepTarget;
        }

        /*Local copy of received data under Weld Process*/
        m_PretriggerEnable = m_WeldModeLabData.PreTrigger.bEnabled;
        m_PretriggerAmplitude = m_WeldModeLabData.PreTrigger.Amplitude;
        m_PretriggerDistance = m_WeldModeLabData.PreTrigger.PreTriggerDistance;
        m_PretriggerTime = m_WeldModeLabData.PreTrigger.PreTriggerTime;
        m_PretriggerType = m_WeldModeLabData.PreTrigger.PreTriggerType;
        m_AfterburstEnable = m_WeldModeLabData.AfterBurst.bEnabled;
        m_AfterburstAmplitude = m_WeldModeLabData.AfterBurst.BurstAmplitude;
        m_AfterburstDelay = m_WeldModeLabData.AfterBurst.BurstDelay;
        m_AfterburstTime = m_WeldModeLabData.AfterBurst.BurstTime;

        /*Local copy of received data under Stack Recipe */
        m_DigitalTune  = m_WeldModeLabData.StackRecipe.DigitalTune;
        m_InternalFreqOffset = m_WeldModeLabData.StackRecipe.FrequencyOffset;
        m_EndOfWeldStore = m_WeldModeLabData.StackRecipe.EndOfWeldStore;
        m_FrequencyOffset = m_WeldModeLabData.StackRecipe.InternalOffsetFlag;
        m_FrequencyLow = m_WeldModeLabData.StackRecipe.FrequencyLow;
        m_FrequencyHigh = m_WeldModeLabData.StackRecipe.FrequencyHigh;
        m_WeldRampTime = m_WeldModeLabData.StackRecipe.WeldRampTime;
        m_MemoryOffset = m_WeldModeLabData.StackRecipe.MemoryOffset;
        m_PhaseLimitTime = m_WeldModeLabData.StackRecipe.PhaseLimitTime;
        m_PhaseLimit = m_WeldModeLabData.StackRecipe.PhaseLimit;
        m_ControlMode = m_WeldModeLabData.StackRecipe.ControlMode;
        m_BlindTimeWeld = m_WeldModeLabData.StackRecipe.BlindTimeWeld;
        m_AmpProportionalGain = m_WeldModeLabData.StackRecipe.AmpProportionalGain;
        m_AmpIntegralGain = m_WeldModeLabData.StackRecipe.AmpIntegralGain;
        m_AmpDerivativeGain = m_WeldModeLabData.StackRecipe.AmpDerivativeGain;
        m_PhaseProportionalGain = m_WeldModeLabData.StackRecipe.PhaseProportionalGain;
        m_PhaseIntegralGain = m_WeldModeLabData.StackRecipe.PhaseIntegralGain;
        m_PhaseDerivativeGain = m_WeldModeLabData.StackRecipe.PhaseDerivativeGain;
        /*Local copy of received data under Parameter A-Z */
        m_EnergyBraking = m_WeldModeLabData.EnergyBrake.bEnabled;
        m_EnergyBrakeAmplitude = m_WeldModeLabData.EnergyBrake.EnergyBrakeAmplitude;
        m_EnergyBrakeTime = m_WeldModeLabData.EnergyBrake.EnergyBrakeTime;
        m_PreWeldSeek = m_WeldModeLabData.IsPreWeldSeekEnabled;
        m_PostWeldSeek = m_WeldModeLabData.IsPostWeldSeekEnabled;
        m_ExtraCooling = m_WeldModeLabData.IsCoolingValveEnabled;
        m_ActuatorClear =m_WeldModeLabData.ActuatorClearData.EnableActuatorClear;
        m_RapidTraverse =m_WeldModeLabData.RapidTraverse;
        m_RapidTraverseDistance =m_WeldModeLabData.RapidTraverseDistance;
        m_TriggerLost =m_WeldModeLabData.TriggerLost;
        m_ActuatorClearTime = m_WeldModeLabData.ActuatorClearData.ActuatorClearTime;
        m_ActuatorClearDistance = m_WeldModeLabData.ActuatorClearData.ActuatorClearDistance;
        m_ActuatorClearType = m_WeldModeLabData.ActuatorClearData.ActuatorClearType;
        m_ExternalAmplitudeSetting = m_WeldModeLabData.ExternalAmplitudeSetting;
        m_TriggerType = m_WeldModeLabData.TriggerData.TriggerType;
        m_TriggerTypeForce = m_WeldModeLabData.TriggerData.TriggerForce;
        m_TriggerTypeDistance = m_WeldModeLabData.TriggerData.TriggerDistance;
        m_IsTimeSeekEnable = m_WeldModeLabData.IsTimedSeekEnabled;
        m_TimeSeekPeriod = m_WeldModeLabData.TimedSeekPeriod;
        m_ScrubAmplitude = m_WeldModeLabData.ScrubAmplitude;

        /*Local copy of received data under CUttoffLImits */
        m_CutoffLimtsEnable=m_WeldModeLabData.CutoffLimit.CutOffLimitsEnabled;
        m_PeakPowerCuttOffEnabled = m_WeldModeLabData.CutoffLimit.PeakPowerCutoff.bEnabled;
        m_PeakPowerCuttoffValue = m_WeldModeLabData.CutoffLimit.PeakPowerCutoff.Value ;
        m_TimeCuttoffEnable = m_WeldModeLabData.CutoffLimit.TimeCutoff.bEnabled;
        m_TimeCuttoffValue = m_WeldModeLabData.CutoffLimit.TimeCutoff.Value;
        m_FreqLowCuttoffEnable = m_WeldModeLabData.CutoffLimit.FrequencyLowCutoff.bEnabled;
        m_FreqLowCuttoffValue = m_WeldModeLabData.CutoffLimit.FrequencyLowCutoff.Value;
        m_FreqHighCuttoffEnable = m_WeldModeLabData.CutoffLimit.FrequencyHighCutoff.bEnabled;
        m_FreqHighCuttoffValue = m_WeldModeLabData.CutoffLimit.FrequencyHighCutoff.Value;
        m_EnergyCuttoffEnable = m_WeldModeLabData.CutoffLimit.EnergyCutoff.bEnabled;
        m_EnergyCuttoffValue = m_WeldModeLabData.CutoffLimit.EnergyCutoff.Value;
        m_GroundDetectCuttoffEnable = m_WeldModeLabData.CutoffLimit.GroundDetectCutoff.bEnabled;
        m_GroundDetectCuttoffValue = m_WeldModeLabData.CutoffLimit.GroundDetectCutoff.Value;
        m_ABSDistanceCutoffEnable = m_WeldModeLabData.CutoffLimit.AbsoluteDistanceCutoff.bEnabled;
        m_ABSDistanceCutoffValue = m_WeldModeLabData.CutoffLimit.AbsoluteDistanceCutoff.Value;
        m_CollapseDistanceCutoffEnable = m_WeldModeLabData.CutoffLimit.CollapseDistanceCutoff.bEnabled;
        m_CollapseDistanceCutoffValue = m_WeldModeLabData.CutoffLimit.CollapseDistanceCutoff.Value;

      /*Local copy of received data under Batch Setting */
        m_BatchSetup = m_WeldModeLabData.BatchSetupEnable;
        m_CountWithAlarms = m_WeldModeLabData.BatchAlarmEnable;
        m_BatchCounterLimit = m_WeldModeLabData.BatchCountLimit;
        m_BatchCounter = m_WeldModeLabData.BatchCounter;
        m_BatchId = QString::fromLocal8Bit(m_WeldModeLabData.BatchID);
        /*Local copy of received data under CUttoffLImits -Suspect and Reject */

        m_IsGlobalSuspect    = m_WeldModeLabData.SuspectLimit.SuspectLimitsEnabled;
        m_IsGlobalReject     = m_WeldModeLabData.RejectLimit.RejectLimitsEnabled;

        m_IsSuspectTime      = m_WeldModeLabData.SuspectLimit.Time.bEnabled;
        m_IsSuspectEnergy    = m_WeldModeLabData.SuspectLimit.Energy.bEnabled;
        m_IsSuspectPeakPower = m_WeldModeLabData.SuspectLimit.PeakPower.bEnabled;
        m_IsSuspectFrequency = m_WeldModeLabData.SuspectLimit.Frequency.bEnabled;
        m_IsRejectTime       = m_WeldModeLabData.RejectLimit.Time.bEnabled;
        m_IsRejectEnergy     = m_WeldModeLabData.RejectLimit.Energy.bEnabled;
        m_IsRejectPeakPower  = m_WeldModeLabData.RejectLimit.PeakPower.bEnabled;
        m_IsRejectFrequency  = m_WeldModeLabData.RejectLimit.Frequency.bEnabled;
        m_SuspectLowTime       =   m_WeldModeLabData.SuspectLimit.Time.LowLimit;
        m_SuspectHighTime      =   m_WeldModeLabData.SuspectLimit .Time.HighLimit;
        m_SuspectLowEnergy     =   m_WeldModeLabData.SuspectLimit.Energy.LowLimit;
        m_SuspectHighEnergy    =   m_WeldModeLabData.SuspectLimit.Energy.HighLimit;
        m_SuspectLowPeakPower  =   m_WeldModeLabData.SuspectLimit.PeakPower.LowLimit;
        m_SuspectHighPeakPower =   m_WeldModeLabData.SuspectLimit.PeakPower.HighLimit;
        m_SuspectLowFrequency  =   m_WeldModeLabData.SuspectLimit.Frequency.LowLimit;
        m_SuspectHighFrequency =   m_WeldModeLabData.SuspectLimit.Frequency.HighLimit;
        m_RejectLowTime            = m_WeldModeLabData.RejectLimit.Time.LowLimit;
        m_RejectHighTime           = m_WeldModeLabData.RejectLimit .Time.HighLimit;
        m_RejectLowEnergy          = m_WeldModeLabData.RejectLimit.Energy.LowLimit;
        m_RejectHighEnergy         = m_WeldModeLabData.RejectLimit.Energy.HighLimit;
        m_RejectLowPeakPower       = m_WeldModeLabData.RejectLimit.PeakPower.LowLimit;
        m_RejectHighPeakPower      = m_WeldModeLabData.RejectLimit.PeakPower.HighLimit;
        m_RejectLowFrequency       = m_WeldModeLabData.RejectLimit.Frequency.LowLimit;
        m_RejectHighFrequency      = m_WeldModeLabData.RejectLimit.Frequency.HighLimit;
        m_IsAbsDistSuspect          = m_WeldModeLabData.SuspectLimit.AbsoluteDistance.bEnabled;
        m_IsAbsDistReject           = m_WeldModeLabData.RejectLimit.AbsoluteDistance.bEnabled;
        m_IsCollapseDistSuspect= m_WeldModeLabData.SuspectLimit.CollapseDistance.bEnabled;
        m_IsCollapseDistReject=  m_WeldModeLabData.RejectLimit.CollapseDistance.bEnabled;
        m_IsTriggerDistSuspect      = m_WeldModeLabData.SuspectLimit.TriggerDistance.bEnabled;
        m_IsTriggerDistReject       = m_WeldModeLabData.RejectLimit.TriggerDistance.bEnabled;
        m_IsVelocitySuspect         = m_WeldModeLabData.SuspectLimit.Velocity.bEnabled;
        m_IsVelocityReject          = m_WeldModeLabData.RejectLimit.Velocity.bEnabled;
        m_IsEndWeldForceSuspect     = m_WeldModeLabData.SuspectLimit.EndWeldForce.bEnabled;
        m_IsEndWeldForceReject      = m_WeldModeLabData.RejectLimit.EndWeldForce.bEnabled;
        m_SuspectLowAbsDist         = m_WeldModeLabData.SuspectLimit.AbsoluteDistance.LowLimit;
        m_SuspectHighAbsDist        = m_WeldModeLabData.SuspectLimit.AbsoluteDistance.HighLimit;
        m_RejectLowAbsDist          = m_WeldModeLabData.RejectLimit.AbsoluteDistance.LowLimit;
        m_RejectHighAbsDist         = m_WeldModeLabData.RejectLimit.AbsoluteDistance.HighLimit;
        m_SuspectLowCollapseDist    = m_WeldModeLabData.SuspectLimit.CollapseDistance.LowLimit;
        m_SuspectHighCollapseDist   = m_WeldModeLabData.SuspectLimit.CollapseDistance.HighLimit;
        m_RejectLowCollapseDist     = m_WeldModeLabData.RejectLimit.CollapseDistance.LowLimit;
        m_RejectHighCollapseDist    = m_WeldModeLabData.RejectLimit.CollapseDistance.HighLimit;
        m_SuspectLowTriggerDist     = m_WeldModeLabData.SuspectLimit.TriggerDistance.LowLimit;
        m_SuspectHighTriggerDist    = m_WeldModeLabData.SuspectLimit.TriggerDistance.HighLimit;
        m_RejectLowTriggerDist      = m_WeldModeLabData.RejectLimit.TriggerDistance.LowLimit;
        m_RejectHighTriggerDist     = m_WeldModeLabData.RejectLimit.TriggerDistance.HighLimit;
        m_SuspectLowVelocity        = m_WeldModeLabData.SuspectLimit.Velocity.LowLimit;
        m_SuspectHighVelocity       = m_WeldModeLabData.SuspectLimit.Velocity.HighLimit;
        m_RejectLowVelocity         = m_WeldModeLabData.RejectLimit.Velocity.LowLimit;
        m_RejectHighVelocity        = m_WeldModeLabData.RejectLimit.Velocity.HighLimit;
        m_SuspectLowEndWeldForce    = m_WeldModeLabData.SuspectLimit .EndWeldForce.LowLimit;
        m_SuspectHighEndWeldForce   = m_WeldModeLabData.SuspectLimit.EndWeldForce.HighLimit;
        m_RejectLowEndWeldForce     = m_WeldModeLabData.RejectLimit.EndWeldForce.LowLimit;
        m_RejectHighEndWeldForce    = m_WeldModeLabData.RejectLimit.EndWeldForce.HighLimit;

        /*Local copy of received data under Energy Compensation */
        m_EnergyCompensation        = m_WeldModeLabData.EnergyCompensation.EnergyCompensationEnabled;
        m_EnergyCompensationLowVal  = m_WeldModeLabData.EnergyCompensation.EnergyCompensationMinValue;
        m_EnergyCompensationHighVal = m_WeldModeLabData.EnergyCompensation.EnergyCompensationMaxValue;

        emit recipeLabDataChanged();

        m_ActiveWelderId = WelderId;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns PretriggerEnable.
*
* \param   - None
*
* \return  - bool.
******************************************************************************/
bool RecipeLabData::getPretriggerEnable() const
{
    return m_PretriggerEnable;
}

/**************************************************************************//**
*
* \brief   - Below function updates the whether pretrigger is enabled or not.
*
* \param   - newPretriggerEnable
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updatePretriggerEnable(bool newPretriggerEnable)
{
    if (m_PretriggerEnable != newPretriggerEnable)
    {
        m_PretriggerEnable = newPretriggerEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PRE_TRIGGER_ENABLED_PARAM, &m_PretriggerEnable);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerAmplitude.
*
* \param   - None
*
* \return  - int : m_PretriggerAmplitude.
******************************************************************************/
int RecipeLabData::getPretriggerAmplitude() const
{
    return m_PretriggerAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerAmplitude.
*
* \param   - PretriggerAmplitude : The PretriggerAmplitude.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updatePretriggerAmplitude(int newPretriggerAmplitude)
{
    if (m_PretriggerAmplitude != newPretriggerAmplitude)
    {
        m_PretriggerAmplitude = newPretriggerAmplitude;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PRE_TRIGGER_AMPLITUDE_PARAM, &m_PretriggerAmplitude);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerDistance.
*
* \param   - None
*
* \return  - float : m_PretriggerDistance.
******************************************************************************/
float RecipeLabData::getPretriggerDistance() const
{
    return m_PretriggerDistance;
}
/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerDistance.
*
* \param   - PretriggerDistance : The PretriggerDistance.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updatePretriggerDistance(float newPretriggerDistance)
{
    if (m_PretriggerDistance != newPretriggerDistance)
    {
        m_PretriggerDistance = newPretriggerDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PRE_TRIGGER_DISTANCE_PARAM, &m_PretriggerDistance);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerTime.
*
* \param   - None.
*
* \return  - float : m_PretriggerTime.
******************************************************************************/
float RecipeLabData::getPretriggerTime() const
{
    return m_PretriggerTime;
}
/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerTime.
*
* \param   - PretriggerTime : The PretriggerTime.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updatePretriggerTime(float newPretriggerTime)
{
    if (m_PretriggerTime != newPretriggerTime)
    {
        m_PretriggerTime = newPretriggerTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PRE_TRIGGER_TIME_PARAM, &m_PretriggerTime);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function updates PretriggerType.
*
* \param   - None
*
* \return  - int : m_PretriggerType
******************************************************************************/
int RecipeLabData::getPretriggerType() const
{
    return m_PretriggerType;
}
/**************************************************************************//**
*
* \brief   - Below function updates the PretriggerType.
*
* \param   - PretriggerType : The PretriggerType.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setPretriggerType(int newPretriggerType)
{
    if (m_PretriggerType != newPretriggerType)
    {
        m_PretriggerType = newPretriggerType;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PRE_TRIGGER_TYPE_PARAM, &m_PretriggerType);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function updates the AfterburstEnable.
*
* \param   - NOne
*
* \return  - bool.
******************************************************************************/
bool RecipeLabData::getAfterburstEnable() const
{
    return m_AfterburstEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the AfterburstEnable.
*
* \param   - AfterburstEnable : The AfterburstEnable.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateAfterburstEnable(bool newAfterburstEnable)
{
    if (m_AfterburstEnable != newAfterburstEnable)
    {
        m_AfterburstEnable = newAfterburstEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AFTER_BURST_ENABLED_PARAM, &m_AfterburstEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   -  Below function updates the AfterburstAmplitude.
*
* \param   -  None.
*
* \return  - int : m_AfterburstAmplitude
******************************************************************************/
int RecipeLabData::getAfterburstAmplitude() const
{
    return m_AfterburstAmplitude;
}
/**************************************************************************//**
*
* \brief   - Below function updates the AfterburstAmplitude.
*
* \param   - AfterburstAmplitude : The AfterburstAmplitude.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateAfterburstAmplitude(int newAfterburstAmplitude)
{
    if (m_AfterburstAmplitude != newAfterburstAmplitude)
    {
        m_AfterburstAmplitude = newAfterburstAmplitude;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AFTER_BURST_AMPLITUDE_PARAM, &m_AfterburstAmplitude);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function updates the AfterburstDelay.
*
* \param   - None
*
* \return  - float : m_AfterburstDelay.
******************************************************************************/
float RecipeLabData::getAfterburstDelay() const
{
    return m_AfterburstDelay;
}
/**************************************************************************//**
*
* \brief   - Below function updates the  AfterburstDelay.
*
* \param   -  newAfterburstDelay : The  AfterburstDelay.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateAfterburstDelay(float newAfterburstDelay)
{
    if (m_AfterburstDelay != newAfterburstDelay)
    {
        m_AfterburstDelay = newAfterburstDelay;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AFTER_BURST_DELAY_PARAM, &m_AfterburstDelay);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function updates AfterburstTime.
*
* \param   - None
*
* \return  - float : m_AfterburstTime.
******************************************************************************/
float RecipeLabData::getAfterburstTime() const
{
    return m_AfterburstTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the AfterburstTime.
*
* \param   - newAfterburstTime : The AfterburstTime.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateAfterburstTime(float newAfterburstTime)
{
    if (m_AfterburstTime != newAfterburstTime)
    {
        m_AfterburstTime = newAfterburstTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AFTER_BURST_TIME_PARAM, &m_AfterburstTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Digital Tune value.
*
* \param   - None.
*
* \return  - m_DigitalTune : Digital Tune value.
*
******************************************************************************/
int RecipeLabData::getDigitalTune() const
{
    return m_DigitalTune;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Digital Tune value.
*
* \param   - newDigitalTune.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateDigitalTune(int newDigitalTune)
{
    if (m_DigitalTune != newDigitalTune)
    {
        m_DigitalTune = newDigitalTune;
        m_RecipeLabData->SetActiveWeldRecipeParameter(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::DIGITAL_TUNE_PARAM), &m_DigitalTune);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Internal Frequency Offset value.
*
* \param   - None.
*
* \return  - m_InternalFreqOffset : Internal Frequency Offset value.
*
******************************************************************************/
int RecipeLabData::getInternalFreqOffset() const
{
    return m_InternalFreqOffset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Internal Frequency Offset value.
*
* \param   - newInternalFreqOffset.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateInternalFreqOffset(int newInternalFreqOffset)
{
    if (m_InternalFreqOffset != newInternalFreqOffset)
    {
        m_InternalFreqOffset = newInternalFreqOffset;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_OFFSET_PARAM, &m_InternalFreqOffset);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the End Of Weld Store Enable value.
*
* \param   - None.
*
* \return  - m_EndOfWeldStore : End Of Weld Store Enable value.
*
******************************************************************************/
bool RecipeLabData::getEndOfWeldStore() const
{
    return m_EndOfWeldStore;
}

/**************************************************************************//**
*
* \brief   - Below function updates the End Of Weld Store Enable value.
*
* \param   - newEndOfWeldStore.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEndOfWeldStore(bool newEndOfWeldStore)
{
    if (m_EndOfWeldStore != newEndOfWeldStore)
    {
        m_EndOfWeldStore = newEndOfWeldStore;
        m_RecipeLabData->SetActiveWeldRecipeParameter(END_OF_WELD_STORE_PARAM, &m_EndOfWeldStore);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Frequency Offset Enable value.
*
* \param   - None.
*
* \return  - m_FrequencyOffset : Frequency Offset Enable value.
*
******************************************************************************/
bool RecipeLabData::getFrequencyOffset() const
{
    return m_FrequencyOffset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Frequency Offset Enable value.
*
* \param   - newFrequencyOffset.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFrequencyOffset(bool newFrequencyOffset)
{
    if (m_FrequencyOffset != newFrequencyOffset)
    {
        m_FrequencyOffset = newFrequencyOffset;
        m_RecipeLabData->SetActiveWeldRecipeParameter(INTERNAL_OFFSET_FLAG_PARAM, &m_FrequencyOffset);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Frequency Low value.
*
* \param   - None.
*
* \return  - m_FrequencyLow : Frequency Low value.
*
******************************************************************************/
int RecipeLabData::getFrequencyLow() const
{
    return m_FrequencyLow;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Frequency Low value.
*
* \param   - newFrequencyLow.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFrequencyLow(int newFrequencyLow)
{
    if (m_FrequencyLow != newFrequencyLow)
    {
        m_FrequencyLow = newFrequencyLow;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_LOW_PARAM, &m_FrequencyLow);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Frequency High value.
*
* \param   - None.
*
* \return  - m_FrequencyHigh : Frequency High value.
*
******************************************************************************/
int RecipeLabData::getFrequencyHigh() const
{
    return m_FrequencyHigh;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Frequency High value.
*
* \param   - newFrequencyHigh.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFrequencyHigh(int newFrequencyHigh)
{
    if (m_FrequencyHigh != newFrequencyHigh)
    {
        m_FrequencyHigh = newFrequencyHigh;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_HIGH_PARAM, &m_FrequencyHigh);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Weld Ramp Time value.
*
* \param   - None.
*
* \return  - m_WeldRampTime : Weld Ramp Time value.
*
******************************************************************************/
float RecipeLabData::getWeldRampTime() const
{
    return m_WeldRampTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Weld Ramp Time value.
*
* \param   - newWeldRampTime.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateWeldRampTime(float newWeldRampTime)
{
    if (m_WeldRampTime != newWeldRampTime)
    {
        m_WeldRampTime = newWeldRampTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(WELD_RAMP_TIME_PARAM, &m_WeldRampTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Memory Offset value.
*
* \param   - None.
*
* \return  - m_MemoryOffset : Memory Offset value.
*
******************************************************************************/
int RecipeLabData::getMemoryOffset() const
{
    return m_MemoryOffset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Memory Offset value.
*
* \param   - newMemoryOffset.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateMemoryOffset(int newMemoryOffset)
{
    if (m_MemoryOffset != newMemoryOffset)
    {
        m_MemoryOffset = newMemoryOffset;
        m_RecipeLabData->SetActiveWeldRecipeParameter(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::MEMORY_OFFSET_PARAM), &m_MemoryOffset);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Clear Memory At Power Up value.
*
* \param   - None.
*
* \return  - m_ClearMemoryAtPowerUp : Clear Memory At Power Up value.
*
******************************************************************************/
bool RecipeLabData::getClearMemoryAtPowerUp() const
{
    return m_ClearMemoryAtPowerUp;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Clear Memory At Power Up value.
*
* \param   - newClearMemoryAtPowerUp.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateClearMemoryAtPowerUp(bool newClearMemoryAtPowerUp)
{
    if (m_ClearMemoryAtPowerUp != newClearMemoryAtPowerUp)
    {
        m_ClearMemoryAtPowerUp = newClearMemoryAtPowerUp;
       // m_RecipeLabData->SetActiveWeldRecipeParameter(CLEAR_MEMORY_AT_POWERUP_PARAM, &m_ClearMemoryAtPowerUp);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Clear Memory With Reset value.
*
* \param   - None.
*
* \return  - m_ClearMemoryWithReset : Clear Memory With Reset value.
*
******************************************************************************/
bool RecipeLabData::getClearMemoryWithReset() const
{
    return m_ClearMemoryWithReset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Clear Memory With Reset value.
*
* \param   - newClearMemoryWithReset.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateClearMemoryWithReset(bool newClearMemoryWithReset)
{
    if (m_ClearMemoryWithReset != newClearMemoryWithReset)
    {
        m_ClearMemoryWithReset = newClearMemoryWithReset;
       // m_RecipeLabData->SetActiveWeldRecipeParameter(CLEAR_MEMORY_WITH_RESET_PARAM, &m_ClearMemoryWithReset);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Phase Limit Time value.
*
* \param   - None.
*
* \return  - m_PhaseLimitTime : Phase Limit Time value.
*
******************************************************************************/
float RecipeLabData::getPhaseLimitTime() const
{
    return m_PhaseLimitTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Phase Limit Time value.
*
* \param   - newPhaseLimitTime.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePhaseLimitTime(float newPhaseLimitTime)
{
    if (m_PhaseLimitTime != newPhaseLimitTime)
    {
        m_PhaseLimitTime = newPhaseLimitTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PHASE_LIMIT_TIME_PARAM, &m_PhaseLimitTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Phase Limit value.
*
* \param   - None.
*
* \return  - m_PhaseLimit : Phase Limit value.
*
******************************************************************************/
int RecipeLabData::getPhaseLimit() const
{
    return m_PhaseLimit;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Phase Limit value.
*
* \param   - newPhaseLimit.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePhaseLimit(int newPhaseLimit)
{
    if (m_PhaseLimit != newPhaseLimit)
    {
        m_PhaseLimit = newPhaseLimit;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PHASE_LIMIT_PARAM, &m_PhaseLimit);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Control Mode value.
*
* \param   - None.
*
* \return  - m_ControlMode : Control Mode value.
*
******************************************************************************/
int RecipeLabData::getControlMode() const
{
    return m_ControlMode;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Control Mode value.
*
* \param   - newControlMode.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateControlMode(int newControlMode)
{
    if (m_ControlMode != newControlMode)
    {
        m_ControlMode = newControlMode;
        m_RecipeLabData->SetActiveWeldRecipeParameter(CONTROL_MODE_PARAM, &m_ControlMode);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Blind Time Weld value.
*
* \param   - None.
*
* \return  - m_BlindTimeWeld : Blind Time Weld value.
*
******************************************************************************/
float RecipeLabData::getBlindTimeWeld() const
{
    return m_BlindTimeWeld;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Blind Time Weld value.
*
* \param   - newBlindTimeWeld.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateBlindTimeWeld(float newBlindTimeWeld)
{
    if (m_BlindTimeWeld != newBlindTimeWeld)
    {
        m_BlindTimeWeld = newBlindTimeWeld;
        m_RecipeLabData->SetActiveWeldRecipeParameter(BLIND_TIME_WELD_PARAM, &m_BlindTimeWeld);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Amplitue Proportional Gain value.
*
* \param   - None.
*
* \return  - m_AmpProportionalGain : Amplitue Proportional Gain value.
*
******************************************************************************/
int RecipeLabData::getAmpProportionalGain() const
{
    return m_AmpProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Amplitue Proportional Gain value.
*
* \param   - newAmpProportionalGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateAmpProportionalGain(int newAmpProportionalGain)
{
    if (m_AmpProportionalGain != newAmpProportionalGain)
    {
        m_AmpProportionalGain = newAmpProportionalGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AMP_PROPORTIONAL_GAIN_PARAM, &m_AmpProportionalGain);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Amplitue Integral Gain value.
*
* \param   - None.
*
* \return  - m_AmpIntegralGain : Amplitue Integral Gain value.
*
******************************************************************************/
int RecipeLabData::getAmpIntegralGain() const
{
    return m_AmpIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Amplitue Integral Gain value.
*
* \param   - newAmpIntegralGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateAmpIntegralGain(int newAmpIntegralGain)
{
    if (m_AmpIntegralGain != newAmpIntegralGain)
    {
        m_AmpIntegralGain = newAmpIntegralGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AMP_INTEGRAL_GAIN_PARAM, &m_AmpIntegralGain);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Amplitue Derivative Gain value.
*
* \param   - None.
*
* \return  - m_AmpDerivativeGain : Amplitue Derivative Gain value.
*
******************************************************************************/
int RecipeLabData::getAmpDerivativeGain() const
{
    return m_AmpDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Amplitue Derivative Gain value.
*
* \param   - newAmpDerivativeGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateAmpDerivativeGain(int newAmpDerivativeGain)
{
    if (m_AmpDerivativeGain != newAmpDerivativeGain)
    {
        m_AmpDerivativeGain = newAmpDerivativeGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(AMP_DERIVATIVE_GAIN_PARAM, &m_AmpDerivativeGain);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Phase Proportional Gain value.
*
* \param   - None.
*
* \return  - m_PhaseProportionalGain : Phase Proportional Gain value.
*
******************************************************************************/
int RecipeLabData::getPhaseProportionalGain() const
{
    return m_PhaseProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Phase Proportional Gain value.
*
* \param   - newPhaseProportionalGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePhaseProportionalGain(int newPhaseProportionalGain)
{
    if (m_PhaseProportionalGain != newPhaseProportionalGain)
    {
        m_PhaseProportionalGain = newPhaseProportionalGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PHASE_PROPORTIONAL_GAIN_PARAM, &m_PhaseProportionalGain);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Phase Integral Gain value.
*
* \param   - None.
*
* \return  - m_PhaseIntegralGain : Phase Integral Gain value.
*
******************************************************************************/
int RecipeLabData::getPhaseIntegralGain() const
{
    return m_PhaseIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Phase Integral Gain value.
*
* \param   - newPhaseIntegralGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePhaseIntegralGain(int newPhaseIntegralGain)
{
    if (m_PhaseIntegralGain != newPhaseIntegralGain)
    {
        m_PhaseIntegralGain = newPhaseIntegralGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PHASE_INTEGRAL_GAIN_PARAM, &m_PhaseIntegralGain);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Phase Derivative Gain value.
*
* \param   - None.
*
* \return  - m_PhaseDerivativeGain : Phase Derivative Gain value.
*
******************************************************************************/
int RecipeLabData::getPhaseDerivativeGain() const
{
    return m_PhaseDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Phase Derivative Gain value.
*
* \param   - newPhaseDerivativeGain.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePhaseDerivativeGain(int newPhaseDerivativeGain)
{
    if (m_PhaseDerivativeGain != newPhaseDerivativeGain)
    {
        m_PhaseDerivativeGain = newPhaseDerivativeGain;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PHASE_DERIVATIVE_GAIN_PARAM, &m_PhaseDerivativeGain);
        emit recipeLabDataChanged();
    }
}



/**************************************************************************//**
*
* \brief   - Below function returns the Energy Braking Enable value.
*
* \param   - None.
*
* \return  - m_EnergyBraking : Energy Braking Enable value.
*
******************************************************************************/
bool RecipeLabData::getEnergyBraking() const
{
    return m_EnergyBraking;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Energy Braking Enable value.
*
* \param   - newEnergyBraking.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEnergyBraking(bool newEnergyBraking)
{
    if (m_EnergyBraking != newEnergyBraking)
    {
        m_EnergyBraking = newEnergyBraking;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_BRAKE_ENABLED_PARAM, &m_EnergyBraking);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Energy Brake Amplitude value.
*
* \param   - None.
*
* \return  - m_EnergyBrakeAmplitude : Energy Brake Amplitude value.
*
******************************************************************************/
int RecipeLabData::getEnergyBrakeAmplitude() const
{
    return m_EnergyBrakeAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Energy Brake Amplitude value.
*
* \param   - newEnergyBrakeAmplitude.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEnergyBrakeAmplitude(int newEnergyBrakeAmplitude)
{
    if (m_EnergyBrakeAmplitude != newEnergyBrakeAmplitude)
    {
        m_EnergyBrakeAmplitude = newEnergyBrakeAmplitude;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_BRAKE_AMPLITUDE_PARAM, &m_EnergyBrakeAmplitude);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Energy Brake Time value.
*
* \param   - None.
*
* \return  - m_EnergyBrakeTime : Energy Brake Time value.
*
******************************************************************************/
float RecipeLabData::getEnergyBrakeTime() const
{
    return m_EnergyBrakeTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Energy Brake Time value.
*
* \param   - newEnergyBrakeTime.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEnergyBrakeTime(float newEnergyBrakeTime)
{
    if (m_EnergyBrakeTime != newEnergyBrakeTime)
    {
        m_EnergyBrakeTime = newEnergyBrakeTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_BRAKE_TIME_PARAM, &m_EnergyBrakeTime);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Pre Weld Seek Enable value.
*
* \param   - None.
*
* \return  - m_PreWeldSeek : Pre Weld Seek Enable value.
*
******************************************************************************/
bool RecipeLabData::getPreWeldSeek() const
{
    return m_PreWeldSeek;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Pre Weld Seek Enable value.
*
* \param   - newPreWeldSeek.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePreWeldSeek(bool newPreWeldSeek)
{
    if (m_PreWeldSeek != newPreWeldSeek)
    {
        m_PreWeldSeek = newPreWeldSeek;
        m_RecipeLabData->SetActiveWeldRecipeParameter(IS_PREWELD_SEEK_ENABLED_PARAM, &m_PreWeldSeek);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Post Weld Seek Enable value.
*
* \param   - None.
*
* \return  - m_PostWeldSeek : Post Weld Seek Enable value.
*
******************************************************************************/
bool RecipeLabData::getPostWeldSeek() const
{
    return m_PostWeldSeek;
}

/**************************************************************************//**
*
* \brief   - Below function updates the POst Weld Seek Enable value.
*
* \param   - newPostWeldSeek.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePostWeldSeek(bool newPostWeldSeek)
{
    if (m_PostWeldSeek != newPostWeldSeek)
    {
        m_PostWeldSeek = newPostWeldSeek;
        m_RecipeLabData->SetActiveWeldRecipeParameter(IS_POSTWELD_SEEK_ENABLED_PARAM, &m_PostWeldSeek);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Extra Coolling Enable value.
*
* \param   - None.
*
* \return  - m_ExtraCooling : Extra Coolling Enable value.
*
******************************************************************************/
bool RecipeLabData:: getExtraCooling() const
{
    return m_ExtraCooling;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Extra Coolling Enable value.
*
* \param   - newExtraCooling.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateExtraCooling(bool newExtraCooling)
{
    if (m_ExtraCooling != newExtraCooling)
    {
        m_ExtraCooling = newExtraCooling;
        m_RecipeLabData->SetActiveWeldRecipeParameter(IS_COOLING_VALVE_ENABLED_PARAM, &m_ExtraCooling);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Actuator Clear Enable value.
*
* \param   - None.
*
* \return  - m_ActuatorClear : Actuator Clear Enable value.
*
******************************************************************************/
bool RecipeLabData::getActuatorClear() const
{
    return m_ActuatorClear;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Actuator Clear Enable value.
*
* \param   - newActuatorClear.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateActuatorClear(bool newActuatorClear)
{
    if(m_ActuatorClear != newActuatorClear)
    {
        m_ActuatorClear = newActuatorClear;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENABLE_ACTUATOR_CLEAR_PARAM, &m_ActuatorClear);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Actuator Clear Time value.
*
* \param   - None.
*
* \return  - m_ActuatorClearTime : Actuator Clear Time value.
*
******************************************************************************/
float RecipeLabData::getActuatorClearTime() const
{
    return m_ActuatorClearTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Actuator Clear Time value.
*
* \param   - newActuatorClearTime.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateActuatorClearTime(float newActuatorClearTime)
{
    if (m_ActuatorClearTime != newActuatorClearTime)
    {
        m_ActuatorClearTime = newActuatorClearTime;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ACTUATOR_CLEAR_TIME, &m_ActuatorClearTime);
        emit recipeLabDataChanged();
    }
}


/**************************************************************************//**
*
* \brief   - Below function returns the Actuator Clear Distance value.
*
* \param   - None.
*
* \return  - m_ActuatorClearDistance : Actuator Clear Distance value.
*
******************************************************************************/
float RecipeLabData::getActuatorClearDistance() const
{
    return m_ActuatorClearDistance;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Actuator Clear Distance value.
*
* \param   - newActuatorClearDistance.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateActuatorClearDistance(float newActuatorClearDistance)
{
    if (m_ActuatorClearDistance != newActuatorClearDistance)
    {
        m_ActuatorClearDistance = newActuatorClearDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ACTUATOR_CLEAR_DISTANCE_PARAM, &m_ActuatorClearDistance);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function updates ActuatorClearType.
*
* \param   - None
*
* \return  - int : ActuatorClearType
******************************************************************************/
int RecipeLabData::getActuatorClearType() const
{
    return m_ActuatorClearType;
}
/**************************************************************************//**
*
* \brief   - Below function updates the ActuatorClearType.
*
* \param   - ActuatorClearType : The ActuatorClearType.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::setActuatorClearType(int newActuatorClearType)
{
    if (m_ActuatorClearType != newActuatorClearType)
    {
        m_ActuatorClearType = newActuatorClearType;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ACTUATOR_CLEAR_TYPE_PARAM, &m_ActuatorClearType);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Hold Force Ramp value.
*
* \param   - None.
*
* \return  - m_HoldForceRamp : Hold Force Ramp value.
*
******************************************************************************/
float RecipeLabData::getHoldForceRamp() const
{
    return m_HoldForceRamp;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Hold Force Ramp value.
*
* \param   - newHoldForceRamp.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateHoldForceRamp(float newHoldForceRamp)
{
    if (m_HoldForceRamp != newHoldForceRamp)
    {
        m_HoldForceRamp = newHoldForceRamp;
        //        m_RecipeLabData->SetActiveWeldRecipeParameter(, &m_HoldForceRamp); // Todo - Backend not available.
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Rapid Traverse Enable value.
*
* \param   - None.
*
* \return  - m_RapidTraverse : Rapid Traverse Enable value.
*
******************************************************************************/
bool RecipeLabData::getRapidTraverse() const
{
    return m_RapidTraverse;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Rapid Traverse Enable value.
*
* \param   - newRapidTraverse.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateRapidTraverse(bool newRapidTraverse)
{
    if (m_RapidTraverse != newRapidTraverse)
    {
        m_RapidTraverse = newRapidTraverse;
        m_RecipeLabData->SetActiveWeldRecipeParameter(RAPID_TRAVERSE_PARAM, &m_RapidTraverse);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Rapid Traverse Distance value.
*
* \param   - None.
*
* \return  - m_RapidTraverseDistance : Rapid Traverse Distance value.
*
******************************************************************************/
float RecipeLabData::getRapidTraverseDistance() const
{
    return m_RapidTraverseDistance;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Rapid Traverse Distance value.
*
* \param   - newRapidTraverseDistance.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateRapidTraverseDistance(float newRapidTraverseDistance)
{
    if (m_RapidTraverseDistance != newRapidTraverseDistance)
    {
        m_RapidTraverseDistance = newRapidTraverseDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(RAPID_TRAVERSE_DISTANCE_PARAM, &m_RapidTraverseDistance);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Trigger Lost Enable value.
*
* \param   - None.
*
* \return  - m_TriggerLost : Trigger Lost Enable value.
*
******************************************************************************/
bool RecipeLabData::getTriggerLost() const
{
    return m_TriggerLost;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Trigger Lost Enable value.
*
* \param   - newTriggerLost.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateTriggerLost(bool newTriggerLost)
{
    if (m_TriggerLost != newTriggerLost)
    {
        m_TriggerLost = newTriggerLost;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TRIGGER_LOST_PARAM, &m_TriggerLost);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of Pretrigger
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinPretriggerParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case PRETRIGGER_DISTANCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_DISTANCE_PARAM);
        break;
    case PRETRIGGER_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_AMPLITUDE_PARAM);
        break;
    case PRETRIGGER_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_TIME_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of Pretrigger
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxPretriggerParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case PRETRIGGER_DISTANCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_DISTANCE_PARAM);
        break;
    case PRETRIGGER_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_AMPLITUDE_PARAM);
        break;
    case PRETRIGGER_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_TIME_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of Afterburst
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinAfterburstParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case AFTERBURST_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_TIME_PARAM);
        break;
    case AFTERBURST_DELAY:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_DELAY_PARAM);
        break;
    case AFTERBURST_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_AMPLITUDE_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of Afterburst
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxAfterburstParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case AFTERBURST_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_TIME_PARAM);
        break;
    case AFTERBURST_DELAY:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_DELAY_PARAM);
        break;
    case AFTERBURST_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_AMPLITUDE_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}


/**************************************************************************//**
*
* \brief   - Below function returns the CutOff Limts Enable value.
*
* \param   - None.
*
* \return  - bool m_CutoffLimtsEnable : CutOff Limts Enable value.
*
******************************************************************************/
bool RecipeLabData::getCutoffLimtsEnabled() const
{
    return m_CutoffLimtsEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the CutoffLimtsEnable value.
*
* \param   - newCutoffLimtsEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateCutoffLimtsEnabled(bool newCutoffLimtsEnable)
{
    if (m_CutoffLimtsEnable != newCutoffLimtsEnable)
    {
        m_CutoffLimtsEnable = newCutoffLimtsEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(CUTOFF_LIMITS_ENABLED_PARAM, &m_CutoffLimtsEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the PeakPower CuttOff Enable value.
*
* \param   - None.
*
* \return  - bool m_PeakPowerCuttOffEnabled : PeakPower CuttOff Enable value.
*
******************************************************************************/
bool RecipeLabData::getPeakPowerCuttOffEnabled() const
{
    return m_PeakPowerCuttOffEnabled;
}
/**************************************************************************//**
*
* \brief   - Below function updates the PeakPower CuttOff value.
*
* \param   - newPeakPowerCuttOffEnabled.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePeakPowerCuttOffEnabled(bool newPeakPowerCuttOffEnabled)
{
    if (m_PeakPowerCuttOffEnabled != newPeakPowerCuttOffEnabled)
    {
        m_PeakPowerCuttOffEnabled = newPeakPowerCuttOffEnabled;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PEAKPOWER_CUTOFF_ENABLE_PARAM, &m_PeakPowerCuttOffEnabled);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the PeakPower CuttOff value.
*
* \param   - None.
*
* \return  - float m_PeakPowerCuttoffValue : PeakPower CuttOff  value.
*
******************************************************************************/
float RecipeLabData::getPeakPowerCuttoffValue() const
{
    return m_PeakPowerCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the PeakPower CuttOff value.
*
* \param   - newPeakPowerCuttoffValue.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updatePeakPowerCuttoffValue(float newPeakPowerCuttoffValue)
{
    if (m_PeakPowerCuttoffValue != newPeakPowerCuttoffValue)    {
        m_PeakPowerCuttoffValue = newPeakPowerCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(PEAKPOWER_CUTOFF_VALUE_PARAM, &m_PeakPowerCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Time CuttOff enabled value.
*
* \param   - None.
*
* \return  - bool m_TimeCuttoffEnable : Time CuttOff enabled value.
*
******************************************************************************/
bool RecipeLabData::getTimeCuttoff() const
{
    return m_TimeCuttoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Time CuttOff value.
*
* \param   - newTimeCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateTimeCuttoff(bool newTimeCuttoffEnable)
{
    if (m_TimeCuttoffEnable != newTimeCuttoffEnable)
    {
        m_TimeCuttoffEnable = newTimeCuttoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TIME_CUTOFF_ENABLE_PARAM, &m_TimeCuttoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Time CuttOff  value.
*
* \param   - None.
*
* \return  - float m_TimeCuttoffEnable : Time CuttOff  value.
*
******************************************************************************/
float RecipeLabData::getTimeCuttoffValue() const
{
    return m_TimeCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Time CuttOff value.
*
* \param   - newTimeCuttoffValue.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateTimeCuttoffValue(float newTimeCuttoffValue)
{
    if (m_TimeCuttoffValue!= newTimeCuttoffValue)
    {
        m_TimeCuttoffValue = newTimeCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TIME_CUTOFF_VALUE_PARAM, &m_TimeCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the FrequencyLow CuttOff enabled value.
*
* \param   - None.
*
* \return  - bool m_FreqLowCuttoffEnable : FrequencyLow CuttOff enabled value.
*
******************************************************************************/
bool RecipeLabData::getFreqLowCuttoff() const
{
    return m_FreqLowCuttoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the FrequencyLow CuttOff value.
*
* \param   - newFreqLowCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFreqLowCuttoff(bool newFreqLowCuttoffEnable)
{
    if (m_FreqLowCuttoffEnable != newFreqLowCuttoffEnable)
    {
        m_FreqLowCuttoffEnable = newFreqLowCuttoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_LOW_CUTOFF_ENABLE_PARAM, &m_FreqLowCuttoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the FrequencyLow CuttOff value.
*
* \param   - None.
*
* \return  - float m_FreqLowCuttoffValue : FrequencyLow CuttOff  value.
*
******************************************************************************/
float RecipeLabData::getFreqLowCuttoffValue() const
{
    return m_FreqLowCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the FrequencyLow CuttOff value.
*
* \param   - newFreqLowCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFreqLowCuttoffValue(float newFreqLowCuttoffValue)
{
    if (m_FreqLowCuttoffValue != newFreqLowCuttoffValue)
    {
        m_FreqLowCuttoffValue = newFreqLowCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_LOW_CUTOFF_VALUE_PARAM, &m_FreqLowCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the FrequencyHigh CuttOff Enabled value.
*
* \param   - None.
*
* \return  - bool m_FreqHighCuttoffEnable : FrequencyLow CuttOff Enabled value.
*
******************************************************************************/
bool RecipeLabData::getFreqHighCuttoff() const
{
    return m_FreqHighCuttoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the FrequencyHigh CuttOff value.
*
* \param   - newFreqHighCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFreqHighCuttoff(bool newFreqHighCuttoffEnable)
{
    if (m_FreqHighCuttoffEnable != newFreqHighCuttoffEnable)
    {
        m_FreqHighCuttoffEnable = newFreqHighCuttoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_HIGH_CUTOFF_ENABLE_PARAM, &m_FreqHighCuttoffEnable);
        emit recipeLabDataChanged();
    }

}
/**************************************************************************//**
*
* \brief   - Below function returns the FrequencyHigh CuttOff  value.
*
* \param   - None.
*
* \return  - float m_FreqHighCuttoffValue : FrequencyLow CuttOff  value.
*
******************************************************************************/
float RecipeLabData::getFreqHighCuttoffValue() const
{
    return m_FreqHighCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the FrequencyHigh CuttOff value.
*
* \param   - newFreqHighCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateFreqHighCuttoffValue(float newFreqHighCuttoffValue)
{
    if (m_FreqHighCuttoffValue != newFreqHighCuttoffValue)
    {
        m_FreqHighCuttoffValue = newFreqHighCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(FREQUENCY_HIGH_CUTOFF_VALUE_PARAM, &m_FreqHighCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Energy CuttOff Enabled value.
*
* \param   - None.
*
* \return  - bool m_EnergyCuttoffEnable : Energy CuttOff  Enabled value.
*
******************************************************************************/
bool RecipeLabData::getEnergyCuttoff() const
{
    return m_EnergyCuttoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Energy CuttOff Enable value.
*
* \param   - newEnergyCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEnergyCuttoff(bool newEnergyCuttoffEnable)
{
    if (m_EnergyCuttoffEnable != newEnergyCuttoffEnable)
    {
        m_EnergyCuttoffEnable = newEnergyCuttoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_CUTOFF_ENABLE_PARAM, &m_EnergyCuttoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Energy CuttOff  value.
*
* \param   - None.
*
* \return  - float m_EnergyCuttoffValue : Energy CuttOff   value.
*
******************************************************************************/
float RecipeLabData::getEnergyCuttoffValue() const
{
    return m_EnergyCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Energy CuttOff value.
*
* \param   - m_EnergyCuttoffValue.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateEnergyCuttoffValue(float newEnergyCuttoffValue)
{
    if (m_EnergyCuttoffValue != newEnergyCuttoffValue)
    {
        m_EnergyCuttoffValue = newEnergyCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_CUTOFF_VALUE_PARAM, &m_EnergyCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Ground Detect CuttOff Enabled value.
*
* \param   - None.
*
* \return  - bool m_GroundDetectCuttoffEnable : Ground Detect CuttOff Enabled value.
*
******************************************************************************/
bool RecipeLabData::getGroundDetectCuttoff() const
{

    return m_GroundDetectCuttoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Ground Detect CuttOff Enabled value.
*
* \param   - newGroundDetectCuttoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateGroundDetectCuttoff(bool newGroundDetectCuttoffEnable)
{
    if (m_GroundDetectCuttoffEnable != newGroundDetectCuttoffEnable)
    {
        m_GroundDetectCuttoffEnable = newGroundDetectCuttoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(GROUND_DETECT_CUTOFF_ENABLE_PARAM, &m_GroundDetectCuttoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the Ground Detect CuttOff  value.
*
* \param   - None.
*
* \return  - float m_GroundDetectCuttoffValue : Ground Detect CuttOff  value.
*
******************************************************************************/
float RecipeLabData::getGroundDetectCuttoffValue() const
{
    return m_GroundDetectCuttoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the Ground Detect CuttOff value.
*
* \param   - newGroundDetectCuttoffValue.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateGroundDetectCuttoffValue(float newGroundDetectCuttoffValue)
{
    if (m_GroundDetectCuttoffValue!= newGroundDetectCuttoffValue)
    {
        m_GroundDetectCuttoffValue = newGroundDetectCuttoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(GROUND_DETECT_CUTOFF_VALUE_PARAM, &m_GroundDetectCuttoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the ABSDistance cuttOff Enable value.
*
* \param   - None.
*
* \return  - bool m_ABSDistanceCutoffEnable : ABSDistance CuttOff Enable value.
*
******************************************************************************/
bool RecipeLabData::getABSDistanceCutoff() const
{
    return m_ABSDistanceCutoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the ABSDistance CuttOff value.
*
* \param   - newABSDistanceCutoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateABSDistanceCutoff(bool newABSDistanceCutoffEnable)
{
    if (m_ABSDistanceCutoffEnable != newABSDistanceCutoffEnable)
    {
        m_ABSDistanceCutoffEnable = newABSDistanceCutoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ABS_DISTANCE_CUTOFF_ENABLE_PARAM, &m_ABSDistanceCutoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the ABSDistance cuttOff value.
*
* \param   - None.
*
* \return  - float m_ABSDistanceCutoffValue : ABSDistance CuttOff value.
*
******************************************************************************/
float RecipeLabData::getABSDistanceCutoffValue() const
{
    return m_ABSDistanceCutoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the ABSDistance CuttOff value.
*
* \param   - newABSDistanceCutoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateABSDistanceCutoffValue(float newABSDistanceCutoffValue)
{
    if (m_ABSDistanceCutoffValue != newABSDistanceCutoffValue)
    {
        m_ABSDistanceCutoffValue = newABSDistanceCutoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ABS_DISTANCE_CUTOFF_VALUE_PARAM, &m_ABSDistanceCutoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the CollapseDistance cuttOff Enable value.
*
* \param   - None.
*
* \return  - bool m_CollapseDistanceCutoffEnable : CollapseDistance CuttOff Enabled value.
*
******************************************************************************/
bool RecipeLabData::getCollapseDistanceCutoff() const
{
    return m_CollapseDistanceCutoffEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the CollapseDistance CuttOff Enabled value.
*
* \param   - newCollapseDistanceCutoffEnable.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateCollapseDistanceCutoff(bool newCollapseDistanceCutoffEnable)
{
    if (m_CollapseDistanceCutoffEnable != newCollapseDistanceCutoffEnable)
    {
        m_CollapseDistanceCutoffEnable = newCollapseDistanceCutoffEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(COLLAPSE_DISTANCE_CUTOFF_ENABLE_PARAM, &m_CollapseDistanceCutoffEnable);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the CollapseDistance cuttOff value.
*
* \param   - None.
*
* \return  - float m_CollapseDistanceCutoffValue : CollapseDistance CuttOff value.
*
******************************************************************************/
float RecipeLabData::getCollapseDistanceCutoffValue() const
{
    return m_CollapseDistanceCutoffValue;
}
/**************************************************************************//**
*
* \brief   - Below function updates the CollapseDistance CuttOff  value.
*
* \param   - newCollapseDistanceCutoffValue.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::updateCollapseDistanceCutoffValue(float newCollapseDistanceCutoffValue)
{
    if (m_CollapseDistanceCutoffValue!= newCollapseDistanceCutoffValue)
    {
        m_CollapseDistanceCutoffValue = newCollapseDistanceCutoffValue;
        m_RecipeLabData->SetActiveWeldRecipeParameter(COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM, &m_CollapseDistanceCutoffValue);
        emit recipeLabDataChanged();
    }
}
/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of ParameterAZ
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/

QString RecipeLabData::getMinParameterAZParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case PARAM_AZ_AFTERBURST_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_TIME_PARAM);
        break;
    case PARAM_AZ_AFTERBURST_DELAY:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_DELAY_PARAM);
        break;
    case PARAM_AZ_AFTERBURST_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AFTER_BURST_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_ENERGY_BRAKE_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ENERGY_BRAKE_TIME_PARAM);
        break;
    case PARAM_AZ_ENERGY_BRAKE_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ENERGY_BRAKE_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_MAX_TIMEOUT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(MAX_WELD_TIMEOUT_PARAM);
        break;
    case PARAM_AZ_HOLD_FORCE_RAMP:
        //MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(); BACKEND PARAMETER NOT AVAILABLE
        break;
    case PARAM_AZ_PRETRIGGER_DISTANCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_DISTANCE_PARAM);
        break;
    case PARAM_AZ_PRETRIGGER_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_PRETRIGGER_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PRE_TRIGGER_TIME_PARAM);
        break;
    case PARAM_AZ_ACT_CLEAR_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ACTUATOR_CLEAR_TIME);
        break;
    case PARAM_AZ_ACT_CLEAR_DISTANCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ACTUATOR_CLEAR_DISTANCE_PARAM);
        break;
    case PARAM_AZ_TRIGGER_FORCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(TRIGGER_FORCE_PARAM);
        break;
    case PARAM_AZ_TRIGGER_DISTANCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(TRIGGER_DISTANCE_PARAM);
        break;
    case PARAM_AZ_RAPID_TRAVERSE_DISTANCE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(RAPID_TRAVERSE_DISTANCE_PARAM);
        break;
    case PARAM_AZ_SCRUB_AMPILTUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SCRUB_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_TIME_SEEK:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(TIMED_SEEK_PERIOD_PARAM);
        break;

    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of ParameterAZ
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxParameterAZParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case PARAM_AZ_AFTERBURST_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_TIME_PARAM);
        break;
    case PARAM_AZ_AFTERBURST_DELAY:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_DELAY_PARAM);
        break;
    case PARAM_AZ_AFTERBURST_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AFTER_BURST_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_ENERGY_BRAKE_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ENERGY_BRAKE_TIME_PARAM);
        break;
    case PARAM_AZ_ENERGY_BRAKE_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ENERGY_BRAKE_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_MAX_TIMEOUT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(MAX_WELD_TIMEOUT_PARAM);
        break;
    case PARAM_AZ_HOLD_FORCE_RAMP:
        //MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(); BACKEND PARAMETER NOT AVAILABLE
        break;
    case PARAM_AZ_PRETRIGGER_DISTANCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_DISTANCE_PARAM);
        break;
    case PARAM_AZ_PRETRIGGER_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_PRETRIGGER_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PRE_TRIGGER_TIME_PARAM);
        break;
    case PARAM_AZ_RAPID_TRAVERSE_DISTANCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(RAPID_TRAVERSE_DISTANCE_PARAM);
        break;        
    case PARAM_AZ_ACT_CLEAR_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ACTUATOR_CLEAR_TIME);
        break;
    case PARAM_AZ_ACT_CLEAR_DISTANCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ACTUATOR_CLEAR_DISTANCE_PARAM);
        break;
    case PARAM_AZ_TRIGGER_FORCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(TRIGGER_FORCE_PARAM);
        break;
    case PARAM_AZ_TRIGGER_DISTANCE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(TRIGGER_DISTANCE_PARAM);
        break;
    case PARAM_AZ_SCRUB_AMPILTUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SCRUB_AMPLITUDE_PARAM);
        break;
    case PARAM_AZ_TIME_SEEK:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(TIMED_SEEK_PERIOD_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}


/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of Stack Recipe
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinStackRecipeParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case DIGITAL_TUNE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::DIGITAL_TUNE_PARAM));
        break;
    case INTERNAL_FREQUENCY_OFFSET:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FREQUENCY_OFFSET_PARAM);
        break;
    case FREQUENCY_LOW:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FREQUENCY_LOW_PARAM);
        break;
    case FREQUENCY_HIGH:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FREQUENCY_HIGH_PARAM);
        break;
    case WELD_RAMP_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(WELD_RAMP_TIME_PARAM);
        break;
    case MEMORY_OFFSET:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::MEMORY_OFFSET_PARAM));
        break;
    case PHASE_LIMIT_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PHASE_LIMIT_TIME_PARAM);
        break;
    case PHASE_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PHASE_LIMIT_PARAM);
        break;
    case CONTROL_MODE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(CONTROL_MODE_PARAM);
        break;
    case BLIND_TIME_WELD:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(BLIND_TIME_WELD_PARAM);
        break;
    case AMP_PROPORTIONAL_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AMP_PROPORTIONAL_GAIN_PARAM);
        break;
    case AMP_INTEGRAL_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AMP_INTEGRAL_GAIN_PARAM);
        break;
    case AMP_DERIVATIVE_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(AMP_DERIVATIVE_GAIN_PARAM);
        break;
    case PHASE_PROPORTIONAL_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PHASE_PROPORTIONAL_GAIN_PARAM);
        break;
    case PHASE_INTEGRAL_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PHASE_INTEGRAL_GAIN_PARAM);
        break;
    case PHASE_DERIVATIVE_GAIN:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PHASE_DERIVATIVE_GAIN_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());
}


/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of Stack Recipe
*            parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxStackRecipeParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case DIGITAL_TUNE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::DIGITAL_TUNE_PARAM));
        break;
    case INTERNAL_FREQUENCY_OFFSET:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FREQUENCY_OFFSET_PARAM);
        break;
    case FREQUENCY_LOW:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FREQUENCY_LOW_PARAM);
        break;
    case FREQUENCY_HIGH:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FREQUENCY_HIGH_PARAM);
        break;
    case WELD_RAMP_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(WELD_RAMP_TIME_PARAM);
        break;
    case MEMORY_OFFSET:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(static_cast<WELD_RECIPE_ACE_PARAM_ID>(WeldRecipe::MEMORY_OFFSET_PARAM));
        break;
    case PHASE_LIMIT_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PHASE_LIMIT_TIME_PARAM);
        break;
    case PHASE_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PHASE_LIMIT_PARAM);
        break;
    case CONTROL_MODE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(CONTROL_MODE_PARAM);
        break;
    case BLIND_TIME_WELD:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(BLIND_TIME_WELD_PARAM);
        break;
    case AMP_PROPORTIONAL_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AMP_PROPORTIONAL_GAIN_PARAM);
        break;
    case AMP_INTEGRAL_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AMP_INTEGRAL_GAIN_PARAM);
        break;
    case AMP_DERIVATIVE_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(AMP_DERIVATIVE_GAIN_PARAM);
        break;
    case PHASE_PROPORTIONAL_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PHASE_PROPORTIONAL_GAIN_PARAM);
        break;
    case PHASE_INTEGRAL_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PHASE_INTEGRAL_GAIN_PARAM);
        break;
    case PHASE_DERIVATIVE_GAIN:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PHASE_DERIVATIVE_GAIN_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of Quick Edit
*            List parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinQuickEditListParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case MODE_VALUE_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_TIME_PARAM);
        break;
    case MODE_VALUE_ENERGY:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_ENERGY_PARAM);
        break;
    case MODE_VALUE_PEAK_POWER:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_PEAK_POWER_PARAM);
        break;
    case MODE_VALUE_GROUND_DETECT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(MODE_VALUE_GROUND_DETECT_PARAM);
        break;
    case WELD_PRESSURE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(WELD_PRESSURE_PARAM);
        break;
    case FLOW_RATE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FLOW_RATE_PARAM);
        break;
    case HOLD_TIME:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(HOLD_TIME_PARAM);
        break;
    case WELD_AMPLITUDE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(WELD_AMPLITUDE_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of Quick Edit
*            List parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxQuickEditListParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case MODE_VALUE_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_TIME_PARAM);
        break;
    case MODE_VALUE_ENERGY:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_ENERGY_PARAM);
        break;
    case MODE_VALUE_PEAK_POWER:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_PEAK_POWER_PARAM);
        break;
    case MODE_VALUE_GROUND_DETECT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(MODE_VALUE_GROUND_DETECT_PARAM);
        break;
    case PARAM_WELD_PRESSURE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(WELD_PRESSURE_PARAM);
        break;
    case FLOW_RATE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FLOW_RATE_PARAM);
        break;
    case HOLD_TIME:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(HOLD_TIME_PARAM);
        break;
    case PARAM_WELD_AMPLITUDE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(WELD_AMPLITUDE_PARAM);
        break;
    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function updates the Reset To Default status.
*
* \param   - status : The Reset To Default status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::resetToDefault(bool status)
{
    // TO DO
}

/**************************************************************************//**
*
* \brief   - Below function returns BransonLogin Status.
*
* \param   - NOne
*
* \return  - Bool - m_BransonOnlyLogin .
******************************************************************************/
bool RecipeLabData::getBransonOnlyLogin() const
{
    return m_BransonOnlyLogin;
}
/**************************************************************************//**
*
* \brief   - Below function updates BransonOnly Login status.
*
* \param   - newBransonOnlyLogin : BransonOnly login key
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateBransonOnlyLogin(bool newBransonOnlyLogin)
{
    if (m_BransonOnlyLogin != newBransonOnlyLogin)
    {
        m_BransonOnlyLogin = newBransonOnlyLogin;
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maxmimun value of Cuttoff LImits
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/

QString RecipeLabData::getMaxCuttOffLimitParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case PARAM_PEAKPOWER_CUTTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(PEAKPOWER_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_TIME_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(TIME_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_FREQUENCY_LOW_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FREQUENCY_LOW_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_FREQUENCY_HIGH_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(FREQUENCY_HIGH_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_ENERGY_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ENERGY_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_GROUND_DETECT_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(GROUND_DETECT_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_ABS_DISTANCE_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ABS_DISTANCE_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_COLLAPSE_DISTANCE_CUTOFF_VALUE:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of CuttoffLimts
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/

QString RecipeLabData::getMinCuttOffLimitParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case PARAM_PEAKPOWER_CUTTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(PEAKPOWER_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_TIME_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(TIME_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_FREQUENCY_LOW_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FREQUENCY_LOW_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_FREQUENCY_HIGH_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(FREQUENCY_HIGH_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_ENERGY_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ENERGY_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_GROUND_DETECT_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(GROUND_DETECT_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_ABS_DISTANCE_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ABS_DISTANCE_CUTOFF_VALUE_PARAM);
        break;
    case PARAM_COLLAPSE_DISTANCE_CUTOFF_VALUE:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(COLLAPSE_DISTANCE_CUTOFF_VALUE_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of SuspectAndReject
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinSuspectRejectLimitParametersValue(int Type)
{
    std::string MinValue;
    switch (Type) {
    case REJECT_TIME_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_TIME_LOW_LIMIT_PARAM);
        break;
    case REJECT_TIME_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_TIME_HIGH_LIMIT_PARAM);
        break;
    case REJECT_ENERGY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_ENERGY_LOW_LIMIT_PARAM);
        break;
    case REJECT_ENERGY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_ENERGY_HIGH_LIMIT_PARAM);
        break;
    case REJECT_PEAKPOWER_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_PEAKPOWER_LOW_LIMIT_PARAM);
        break;
    case REJECT_PEAKPOWER_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_PEAKPOWER_HIGH_LIMIT_PARAM);
        break;

    case REJECT_FREQUENCY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_FREQUENCY_LOW_LIMIT_PARAM);
        break;

    case REJECT_FREQUENCY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_FREQUENCY_HIGH_LIMIT_PARAM);
        break;
    case REJECT_ABS_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case REJECT_ABS_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_COLLAPSE_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_TRIGGER_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case REJECT_TRIGGER_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case REJECT_END_WELD_FORCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM);
        break;
    case REJECT_END_WELD_FORCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_VELOCITY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_VELOCITY_LOW_LIMIT_PARAM);
        break;

    case REJECT_VELOCITY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(REJECT_VELOCITY_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_TIME_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_TIME_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_TIME_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_TIME_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_ENERGY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_ENERGY_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_ENERGY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_ENERGY_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_PEAKPOWER_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_PEAKPOWER_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_PEAKPOWER_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_PEAKPOWER_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_FREQUENCY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_FREQUENCY_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_FREQUENCY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_FREQUENCY_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_ABS_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_ABS_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_END_WELD_FORCE_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_END_WELD_FORCE_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_VELOCITY_LOW_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_VELOCITY_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_VELOCITY_HIGH_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(SUSPECT_VELOCITY_HIGH_LIMIT_PARAM);
        break;

    default:
        break;
    }
    return QString::fromLocal8Bit(MinValue.c_str());

}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maximum value of SuspectAndReject
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxSuspectRejectLimitParametersValue(int Type)
{
    std::string MaxValue;
    switch (Type) {
    case REJECT_TIME_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_TIME_LOW_LIMIT_PARAM);
        break;
    case REJECT_TIME_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_TIME_HIGH_LIMIT_PARAM);
        break;
    case REJECT_ENERGY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_ENERGY_LOW_LIMIT_PARAM);
        break;
    case REJECT_ENERGY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_ENERGY_HIGH_LIMIT_PARAM);
        break;
    case REJECT_PEAKPOWER_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_PEAKPOWER_LOW_LIMIT_PARAM);
        break;
    case REJECT_PEAKPOWER_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_PEAKPOWER_HIGH_LIMIT_PARAM);
        break;

    case REJECT_FREQUENCY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_FREQUENCY_LOW_LIMIT_PARAM);
        break;

    case REJECT_FREQUENCY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_FREQUENCY_HIGH_LIMIT_PARAM);
        break;
    case REJECT_ABS_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_ABS_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case REJECT_ABS_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_ABS_DISTANCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_COLLAPSE_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_TRIGGER_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case REJECT_TRIGGER_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case REJECT_END_WELD_FORCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_END_WELD_FORCE_LOW_LIMIT_PARAM);
        break;
    case REJECT_END_WELD_FORCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_END_WELD_FORCE_HIGH_LIMIT_PARAM);
        break;
    case REJECT_VELOCITY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_VELOCITY_LOW_LIMIT_PARAM);
        break;

    case REJECT_VELOCITY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(REJECT_VELOCITY_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_TIME_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_TIME_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_TIME_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_TIME_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_ENERGY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_ENERGY_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_ENERGY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_ENERGY_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_PEAKPOWER_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_PEAKPOWER_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_PEAKPOWER_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_PEAKPOWER_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_FREQUENCY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_FREQUENCY_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_FREQUENCY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_FREQUENCY_HIGH_LIMIT_PARAM);
        break;
    case SUSPECT_ABS_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_ABS_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_ABS_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_ABS_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT_PARAM);
        break;
    case SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_END_WELD_FORCE_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_END_WELD_FORCE_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_END_WELD_FORCE_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_END_WELD_FORCE_HIGH_LIMIT_PARAM);
        break;

    case SUSPECT_VELOCITY_LOW_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_VELOCITY_LOW_LIMIT_PARAM);
        break;

    case SUSPECT_VELOCITY_HIGH_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(SUSPECT_VELOCITY_HIGH_LIMIT_PARAM);
        break;

    default:
        break;
    }
    return QString::fromLocal8Bit(MaxValue.c_str());
}



/**************************************************************************//**
*
* \brief   - Below function returns the Batch Setup enable status.
*
* \param   - None.
*
* \return  - m_BatchSetup : Batch Setup enable status.
*
******************************************************************************/
bool RecipeLabData::getBatchSetup() const
{
    return m_BatchSetup;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Batch Setup enable status.
*
* \param   - newBatchSetup : Batch Setup enable status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateBatchSetup(bool newBatchSetup)
{
    if (m_BatchSetup != newBatchSetup)
    {
        m_BatchSetup = newBatchSetup;
        m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_SETUP_ENABLE_PARAM, &m_BatchSetup);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Count With Alarms enable status.
*
* \param   - None.
*
* \return  - m_CountWithAlarms : Count With Alarms enable status.
*
******************************************************************************/
bool RecipeLabData::getCountWithAlarms() const
{
    return m_CountWithAlarms;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Count With Alarms enable status.
*
* \param   - newCountWithAlarms : Count With Alarms enable status.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateCountWithAlarms(bool newCountWithAlarms)
{
    if (m_CountWithAlarms != newCountWithAlarms)
    {
        m_CountWithAlarms = newCountWithAlarms;
        m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_ALARM_ENABLE_PARAM, &m_CountWithAlarms);
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Batch Count Value.
*
* \param   - None.
*
* \return  - m_BatchCounterLimit : Batch Count Value.
*
******************************************************************************/
int RecipeLabData::getBatchCounterLimit() const
{
    return m_BatchCounterLimit;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Batch Count Value.
*
* \param   - newBatchCounter : Batch Count Value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateBatchCounterLimit(int newBatchCounterLimit)
{
    if (m_BatchCounterLimit != newBatchCounterLimit)
    {
        /*Triggers the confirmation when batch counter is non zero
          when modification is attempted by user*/
        if(newBatchCounterLimit <= m_BatchCounter)
        {
            m_UpdatedBatchCounterLimit = newBatchCounterLimit;
            emit batchCountLimitUpdate();
        }

        else
        {
            m_BatchCounterLimit = newBatchCounterLimit;
            m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_COUNT_LIMIT_PARAM, &m_BatchCounterLimit);
            emit recipeLabDataChanged();
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Batch Id Value.
*
* \param   - None.
*
* \return  - m_BatchId : Batch Id Value.
*
******************************************************************************/
QString RecipeLabData::getBatchId() const
{
    return m_BatchId;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Batch Id Value.
*
* \param   - newBatchId : Batch Id Value.
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateBatchId(const QString &newBatchId)
{
    if (m_BatchId != newBatchId)
    {
        m_BatchId = newBatchId;
        m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_ID_PARAM, const_cast<char*> (m_BatchId.toStdString().c_str()));
        emit recipeLabDataChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Minimun value of Batch Setting
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : Minimun value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinBatchSettingParametersValue(int Type)
{
    std::string MinValue;

    switch (Type)
    {
    case PARAM_BATCH_COUNT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(BATCH_COUNTER_PARAM);
        break;
    case PARAM_BATCH_COUNT_LIMIT:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(BATCH_COUNT_LIMIT_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maxmimun value of Batch Setting
*            screen parameters according to system frequency.
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxBatchSettingParametersValue(int Type)
{
    std::string MaxValue;

    switch (Type)
    {
    case PARAM_BATCH_COUNT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(BATCH_COUNTER_PARAM);
        break;
    case PARAM_BATCH_COUNT_LIMIT:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(BATCH_COUNT_LIMIT_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function confirms the batch count limit update when user
*            allowed to update during finite weld cycle.
*
* \param   - None.
*
* \return  - None.
*
******************************************************************************/
void RecipeLabData::batchCountLimitUpdateConfirmed()
{
    m_BatchCounterLimit = m_UpdatedBatchCounterLimit;
    m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_COUNT_LIMIT_PARAM, &m_BatchCounterLimit);
    emit recipeLabDataChanged();
}


/**************************************************************************//**
*
* \brief   - Below function fetch and returns the minimum Energy compensation
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MinValue : minimum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMinEnergyCompensationVal(int Type)
{
    std::string MinValue;

    switch (Type)
    {
    case ENERGY_COMPENSATION_MINIMUM:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ENERGY_COMPENSATION_MIN_VALUE_PARAM);
        break;
    case ENERGY_COMPENSATION_MAXIUM:
        MinValue = m_RecipeLabData->GetWeldRecipeParamMinValue(ENERGY_COMPENSATION_MAX_VALUE_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MinValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function fetch and returns the Maxmimun value of Energy compensation
*
* \param   - Type : Parameter Number for which value to be fetched.
*
* \return  - MaxValue : Maximum value of parameter.
*
******************************************************************************/
QString RecipeLabData::getMaxEnergyCompensationVal(int Type)
{
    std::string MaxValue;

    switch (Type)
    {
    case ENERGY_COMPENSATION_MINIMUM:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ENERGY_COMPENSATION_MIN_VALUE_PARAM);
        break;
    case ENERGY_COMPENSATION_MAXIUM:
        MaxValue = m_RecipeLabData->GetWeldRecipeParamMaxValue(ENERGY_COMPENSATION_MAX_VALUE_PARAM);
        break;
    default:
        break;
    }

    return QString::fromLocal8Bit(MaxValue.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function returns the returns Batch Setting status.
*
* \param   - None.
*
* \return  - m_BatchCounter :  Batch count status.
*
******************************************************************************/
int RecipeLabData::getBatchCounter() const
{
    return m_BatchCounter;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Batch Count .
*
* \param   - newBatchCounter :
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateBatchCounter(int newBatchCounter)
{
    m_BatchCounter = newBatchCounter;
    m_RecipeLabData->SetActiveWeldRecipeParameter(BATCH_COUNTER_PARAM, &m_BatchCounter);
}

/**************************************************************************//**
*
* \brief   - Below function returns the ExternalAmplitudeSetting .
*
* \param   - none :
*
* \return  - bool - ExternalAmplitudeSetting.
******************************************************************************/
bool RecipeLabData::getExternalAmplitudeSetting() const
{
    return m_ExternalAmplitudeSetting;
}

/**************************************************************************//**
*
* \brief   - Below function updates the ExternalAmplitudeSetting .
*
* \param   - ExternalAmplitudeSetting :
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateExternalAmplitudeSetting(bool newExternalAmplitudeSetting)
{
    m_ExternalAmplitudeSetting = newExternalAmplitudeSetting;
    m_RecipeLabData->SetActiveWeldRecipeParameter(EXTERNAL_AMPLITUDE_SETTING, &m_ExternalAmplitudeSetting);
}


/**************************************************************************//**
*
* \brief   - Below function returns the EnergyCompensation Enable/Disable.
*
* \param   - none :
*
* \return  - bool - m_EnergyCompensation.
******************************************************************************/
bool RecipeLabData::getEnergyCompensation() const
{
    return m_EnergyCompensation;
}

/**************************************************************************//**
*
* \brief   - Below function updates the EnergyCompensation Enable/Disable. .
*
* \param   - newEnergyCompensation :
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateEnergyCompensation(bool newEnergyCompensation)
{
    if (m_EnergyCompensation != newEnergyCompensation)
    {
        m_EnergyCompensation = newEnergyCompensation;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_COMPENSATION_ENABLED_PARAM, &m_EnergyCompensation);
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the EnergyCompensation minimum value .
*
* \param   - none :
*
* \return  - bool - EnergyCompensationLowVal.
******************************************************************************/
float RecipeLabData::getEnergyCompensationLowVal() const
{
    return m_EnergyCompensationLowVal;
}

/**************************************************************************//**
*
* \brief   - Below function updates the EnergyCompensationLowVal .
*
* \param   - newEnergyCompensationLowVal :
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateEnergyCompensationLowVal(float newEnergyCompensationLowVal)
{
    if (m_EnergyCompensationLowVal != newEnergyCompensationLowVal)
    {
        m_EnergyCompensationLowVal = newEnergyCompensationLowVal;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_COMPENSATION_MIN_VALUE_PARAM, &m_EnergyCompensationLowVal);
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the EnergyCompensationHigh value .
*
* \param   - none :
*
* \return  - float - m_EnergyCompensationHighVal.
******************************************************************************/
float RecipeLabData::getEnergyCompensationHighVal() const
{
    return m_EnergyCompensationHighVal;
}

/**************************************************************************//**
*
* \brief   - Below function updates the EnergyCompensationHighVal .
*
* \param   - newEnergyCompensationHighVal :
*
* \return  - None.
******************************************************************************/
void RecipeLabData::updateEnergyCompensationHighVal(float newEnergyCompensationHighVal)
{
    if (m_EnergyCompensationHighVal != newEnergyCompensationHighVal)
    {
        m_EnergyCompensationHighVal = newEnergyCompensationHighVal;
        m_RecipeLabData->SetActiveWeldRecipeParameter(ENERGY_COMPENSATION_MAX_VALUE_PARAM, &m_EnergyCompensationHighVal);
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the TriggerTypeForce value .
*
* \param   - none :
*
* \return  - float - TriggerTypeForce.
******************************************************************************/
float RecipeLabData::getTriggerTypeForce() const
{
    return m_TriggerTypeForce;
}

/**************************************************************************//**
*
* \brief   - Below function updates the m_TriggerTypeForce value .
*
* \param   - none :
*
* \return  - float - m_TriggerTypeForce.
******************************************************************************/
void RecipeLabData::updateTriggerTypeForce(float newTriggerTypeForce)
{
    if ( m_TriggerTypeForce != newTriggerTypeForce)
    {
        m_TriggerTypeForce = newTriggerTypeForce;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TRIGGER_FORCE_PARAM, &m_TriggerTypeForce);
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the TriggerTypeDistance value .
*
* \param   - none :
*
* \return  - float - TriggerTypeDistance.
******************************************************************************/
float RecipeLabData::getTriggerTypeDistance() const
{
    return m_TriggerTypeDistance;
}

/**************************************************************************//**
*
* \brief   - Below function updates the TriggerTypeDistance value .
*
* \param   - none :
*
* \return  - float - TriggerTypeDistance.
******************************************************************************/
void RecipeLabData::updateTriggerTypeDistance(float newTriggerTypeDistance)
{
    if (m_TriggerTypeDistance != newTriggerTypeDistance)
    {
        m_TriggerTypeDistance = newTriggerTypeDistance;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TRIGGER_DISTANCE_PARAM, &m_TriggerTypeDistance);
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the TriggerType value .
*
* \param   - none :
*
* \return  - int TriggerType.
******************************************************************************/
int RecipeLabData::getTriggerType() const
{
    return m_TriggerType;
}

/**************************************************************************//**
*
* \brief   - Below function update the TriggerType value .
*
* \param   - TriggerType :
*
* \return  - int - TriggerType.
******************************************************************************/
void RecipeLabData::updateTriggerType(int newTriggerType)
{
    if (m_TriggerType != newTriggerType)
    {
        m_TriggerType = newTriggerType;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TRIGGER_TYPE_PARAM, &m_TriggerType);
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the IsTimeSeekEnable value .
*
* \param   - none :
*
* \return  - bool - IsTimeSeekEnable.
******************************************************************************/
bool RecipeLabData::getIsTimeSeekEnable() const
{
    return m_IsTimeSeekEnable;
}
/**************************************************************************//**
*
* \brief   - Below function updates the IsTimeSeekEnable value .
*
* \param   - newIsTimeSeekEnable :
*
* \return  - bool - IsTimeSeekEnable.
******************************************************************************/
void RecipeLabData::updateIsTimeSeekEnable(bool newIsTimeSeekEnable)
{
    if (m_IsTimeSeekEnable != newIsTimeSeekEnable)
    {
        m_IsTimeSeekEnable = newIsTimeSeekEnable;
        m_RecipeLabData->SetActiveWeldRecipeParameter(IS_TIMED_SEEKENABLED_PARAM, &m_IsTimeSeekEnable);

    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the TimeSeekPeriod value .
*
* \param   - none :
*
* \return  - float - TimeSeekPeriod.
******************************************************************************/
float RecipeLabData::getTimeSeekPeriod() const
{
    return m_TimeSeekPeriod;
}
/**************************************************************************//**
*
* \brief   - Below function updates the TimeSeekPeriod value .
*
* \param   - newTimeSeekPeriod
*
* \return  - float - TimeSeekPeriod.
******************************************************************************/
void RecipeLabData::updateTimeSeekPeriod(float newTimeSeekPeriod)
{
    if (m_TimeSeekPeriod != newTimeSeekPeriod)
    {
        m_TimeSeekPeriod = newTimeSeekPeriod;
        m_RecipeLabData->SetActiveWeldRecipeParameter(TIMED_SEEK_PERIOD_PARAM, &m_TimeSeekPeriod);

    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the ScrubAmplitude value .
*
* \param   - none :
*
* \return  - int - ScrubAmplitude.
******************************************************************************/
int RecipeLabData::getScrubAmplitude() const
{
    return m_ScrubAmplitude;
}
/**************************************************************************//**
*
* \brief   - Below function updates the ScrubAmplitude value .
*
* \param   - newScrubAmplitude
*
* \return  - int - ScrubAmplitude.
******************************************************************************/
void RecipeLabData::updateScrubAmplitude(int newScrubAmplitude)
{
    if (m_ScrubAmplitude != newScrubAmplitude)
    {
        m_ScrubAmplitude = newScrubAmplitude;
        m_RecipeLabData->SetActiveWeldRecipeParameter(SCRUB_AMPLITUDE_PARAM, &m_ScrubAmplitude);
    }
}

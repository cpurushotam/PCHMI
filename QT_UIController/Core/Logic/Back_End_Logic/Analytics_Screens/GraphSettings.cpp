/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    GraphSettings.cpp file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/11/2023 - Initial version.
***************************************************************************/
#include "GraphSettings.h"
#include "CycleDetailsListModel.h"
#include "deque"
#include "algorithm"
/**************************************************************************//**
*
* \brief  - Constructor to initialize limit values for each display parameter
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
GraphSettings::GraphSettings(QObject *parent)
{
    /*Initial limit values for each parameter type*/
    m_AmpAxisMinValue     = 0;
    m_AmpAxisMaxValue     = 120;
    m_PowerAxisMinValue   = 0;
    m_PowerAxisMaxValue   = 10;
    m_FreqAxisMinValue    = 19450;
    m_FreqAxisMaxValue    = 20450;
    m_PhaseAxisMinValue   = -180;
    m_PhaseAxisMaxValue   = 180;
    m_CurrentAxisMinValue = 0;
    m_CurrentAxisMaxValue = 120;
    m_EnergyAxisMinValue  = 0;
    m_EnergyAxisMaxValue  = 50;
    m_ForceAxisMinValue   = 0;
    m_ForceAxisMaxValue   = 120;
    m_AbsDisAxisMinValue  = 0;
    m_AbsDisAxisMaxValue  = 120;
    m_ColDisAxisMinValue  = -5;
    m_ColDisAxisMaxValue  = 5;

    m_ReqAmpAxisMinValue = 0;
    m_ReqAmpAxisMaxValue = 100;

    m_VelocityAxisMinValue = 0;
    m_VelocityAxisMaxValue = 120;

    m_WeldSignatureACE = nullptr;
}

/**************************************************************************//**
*
* \brief   - Below function returns the stored Y Axis parameter.
*
* \param   - None.
*
* \return  - storedValue : The stored Y Axis parameter.
******************************************************************************/
int GraphSettings::getFirstAxisValue() const
{
    int storedValue = settings.value("FirstAxisValue").toInt();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the stored Y Axis parameter.
*
* \param   - FirstAxisValue : The stored Y Axis parameter.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateFirstAxisValuee(const int &FirstAxisValue)
{
    settings.setValue("FirstAxisValue", FirstAxisValue);
}

/**************************************************************************//**
*
* \brief   - Below function returns the stored Y Axis parameter.
*
* \param   - None.
*
* \return  - storedValue : The stored Y Axis parameter.
******************************************************************************/
int GraphSettings::getSecondAxisValue() const
{
    int storedValue = settings.value("SecondAxisValue").toInt();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the stored Y Axis parameter.
*
* \param   - SecondAxisValue : The stored Y Axis parameter.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateSecondAxisValue(const int &SecondAxisValue)
{
    settings.setValue("SecondAxisValue", SecondAxisValue);
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude min value.
*
* \param   - None.
*
* \return  - m_AmpAxisMinValue : The amplitude min value.
******************************************************************************/
int GraphSettings::getAmpAxisMinValue() const
{
    return m_AmpAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude min value.
*
* \param   - AmpAxisMinValue : The amplitude min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAmpAxisMinValue(const int &AmpAxisMinValue)
{
    if(m_AmpAxisMinValue != AmpAxisMinValue)
    {
        m_AmpAxisMinValue = AmpAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude max value.
*
* \param   - None.
*
* \return  - m_AmpAxisMaxValue : The amplitude max value.
******************************************************************************/
int GraphSettings::getAmpAxisMaxValue() const
{
    return m_AmpAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude max value.
*
* \param   - AmpAxisMaxValue : The amplitude max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAmpAxisMaxValue(const int &AmpAxisMaxValue)
{
    if(m_AmpAxisMaxValue != AmpAxisMaxValue)
    {
        m_AmpAxisMaxValue = AmpAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the power min value.
*
* \param   - None.
*
* \return  - m_PowerAxisMinValue : The power min value.
******************************************************************************/
double GraphSettings::getPowerAxisMinValue() const
{
    return m_PowerAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the power min value.
*
* \param   - PowerAxisMinValue : The power min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updatePowerAxisMinValue(const double &PowerAxisMinValue)
{
    if(m_PowerAxisMinValue != PowerAxisMinValue)
    {
        m_PowerAxisMinValue = PowerAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the power max value.
*
* \param   - None.
*
* \return  - m_PowerAxisMaxValue : The power max value.
******************************************************************************/
double GraphSettings::getPowerAxisMaxValue() const
{
    return m_PowerAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the power max value.
*
* \param   - PowerAxisMaxValue : The power max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updatePowerAxisMaxValue(const double &PowerAxisMaxValue)
{
    if(m_PowerAxisMaxValue != PowerAxisMaxValue)
    {
        m_PowerAxisMaxValue = PowerAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency min value.
*
* \param   - None.
*
* \return  - m_FreqAxisMinValue : The frequency min value.
******************************************************************************/
int GraphSettings::getFreqAxisMinValue() const
{
    return m_FreqAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency min value.
*
* \param   - FreqAxisMinValue : The frequency min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateFreqAxisMinValue(const int &FreqAxisMinValue)
{
    if(m_FreqAxisMinValue != FreqAxisMinValue)
    {
        m_FreqAxisMinValue = FreqAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency max value.
*
* \param   - None.
*
* \return  - m_FreqAxisMaxValue : The frequency max value.
******************************************************************************/
int GraphSettings::getFreqAxisMaxValue() const
{
    return m_FreqAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates The frequency max value.
*
* \param   - FreqAxisMaxValue : The frequency max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateFreqAxisMaxValue(const int &FreqAxisMaxValue)
{
    if(m_FreqAxisMaxValue != FreqAxisMaxValue)
    {
        m_FreqAxisMaxValue = FreqAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase min value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMinValue : The phase min value.
******************************************************************************/
int GraphSettings::getPhaseAxisMinValue() const
{
    return m_PhaseAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase min value.
*
* \param   - PhaseAxisMinValue : The phase min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updatePhaseAxisMinValue(const int &PhaseAxisMinValue)
{
    if(m_PhaseAxisMinValue != PhaseAxisMinValue)
    {
        m_PhaseAxisMinValue = PhaseAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase max value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMaxValue : The phase max value.
******************************************************************************/
int GraphSettings::getPhaseAxisMaxValue() const
{
    return m_PhaseAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase max value.
*
* \param   - PhaseAxisMaxValue : The phase max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updatePhaseAxisMaxValue(const int &PhaseAxisMaxValue)
{
    if(m_PhaseAxisMaxValue != PhaseAxisMaxValue)
    {
        m_PhaseAxisMaxValue = PhaseAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current min value.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : The current min value.
******************************************************************************/
int GraphSettings::getCurrentAxisMinValue() const
{
    return m_CurrentAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current min value.
*
* \param   - CurrentAxisMinValue : The current min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateCurrentAxisMinValue(const int &CurrentAxisMinValue)
{
    if(m_CurrentAxisMinValue != CurrentAxisMinValue)
    {
        m_CurrentAxisMinValue = CurrentAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current max value.
*
* \param   - None.
*
* \return  - m_CurrentAxisMaxValue : The current max value.
******************************************************************************/
int GraphSettings::getCurrentAxisMaxValue() const
{
   return m_CurrentAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current max value.
*
* \param   - WeldRecipeNumber : The current max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateCurrentAxisMaxValue(const int &CurrentAxisMaxValue)
{
    if(m_CurrentAxisMaxValue != CurrentAxisMaxValue)
    {
        m_CurrentAxisMaxValue = CurrentAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the energy min value.
*
* \param   - None.
*
* \return  - m_EnergyAxisMinValue : The energy min value.
******************************************************************************/
double GraphSettings::getEnergyAxisMinValue() const
{
    return m_EnergyAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the energy min value.
*
* \param   - EnergyAxisMinValue : The energy min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateEnergyAxisMinValue(const double &EnergyAxisMinValue)
{
    if(m_EnergyAxisMinValue != EnergyAxisMinValue)
    {
        m_EnergyAxisMinValue = EnergyAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the energy max value.
*
* \param   - None.
*
* \return  - m_EnergyAxisMaxValue : The energy max value.
******************************************************************************/
double GraphSettings::getEnergyAxisMaxValue() const
{
    return m_EnergyAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the energy max value.
*
* \param   - EnergyAxisMaxValue : The energy max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateEnergyAxisMaxValue(const double &EnergyAxisMaxValue)
{
    if(m_EnergyAxisMaxValue != EnergyAxisMaxValue)
    {
        m_EnergyAxisMaxValue = EnergyAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the force min value.
*
* \param   - None.
*
* \return  - m_ForceAxisMinValue : The force min value.
******************************************************************************/
double GraphSettings::getForceAxisMinValue() const
{
    return m_ForceAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the force min value.
*
* \param   - ForceAxisMinValue : The force min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateForceAxisMinValue(const double &ForceAxisMinValue)
{
    if(m_ForceAxisMinValue != ForceAxisMinValue)
    {
        m_ForceAxisMinValue = ForceAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the force The value.
*
* \param   - None.
*
* \return  - m_ForceAxisMaxValue : The force max value.
******************************************************************************/
double GraphSettings::getForceAxisMaxValue() const
{
    return m_ForceAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the force max value.
*
* \param   - ForceAxisMaxValue : The force max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateForceAxisMaxValue(const double &ForceAxisMaxValue)
{
    if(m_ForceAxisMaxValue != ForceAxisMaxValue)
    {
        m_ForceAxisMaxValue = ForceAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the absolute distance min value.
*
* \param   - None.
*
* \return  - m_AbsDisAxisMinValue : The absolute distance min value.
******************************************************************************/
double GraphSettings::getAbsDisAxisMinValue() const
{
    return m_AbsDisAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the absolute distance min value.
*
* \param   - AbsDisAxisMinValue : The absolute distance min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAbsDisAxisMinValue(const double &AbsDisAxisMinValue)
{
    if(m_AbsDisAxisMinValue != AbsDisAxisMinValue)
    {
        m_AbsDisAxisMinValue = AbsDisAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the absolute distance max value.
*
* \param   - None.
*
* \return  - m_AbsDisAxisMaxValue : The absolute distance max value.
******************************************************************************/
double GraphSettings::getAbsDisAxisMaxValue() const
{
    return m_AbsDisAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the absolute distance max value.
*
* \param   - AbsDisAxisMaxValue : The absolute distance max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAbsDisAxisMaxValue(const double &AbsDisAxisMaxValue)
{
    if(m_AbsDisAxisMaxValue != AbsDisAxisMaxValue)
    {
        m_AbsDisAxisMaxValue = AbsDisAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the collapse distance min value.
*
* \param   - None.
*
* \return  - m_ColDisAxisMinValue : The collapse distance min value.
******************************************************************************/
double GraphSettings::getColDisAxisMinValue() const
{
    return m_ColDisAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the collapse distance min value.
*
* \param   - ColDisAxisMinValue : The collapse distance min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateColDisAxisMinValue(const double &ColDisAxisMinValue)
{
    if(m_ColDisAxisMinValue != ColDisAxisMinValue)
    {
        m_ColDisAxisMinValue = ColDisAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the collapse distance max value.
*
* \param   - None.
*
* \return  - m_ColDisAxisMaxValue : The collapse distance max value.
******************************************************************************/
double GraphSettings::getColDisAxisMaxValue() const
{
    return m_ColDisAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the collapse distance max value.
*
* \param   - ColDisAxisMaxValue : The collapse distance max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateColDisAxisMaxValue(const double &ColDisAxisMaxValue)
{
    if(m_ColDisAxisMaxValue != ColDisAxisMaxValue)
    {
        m_ColDisAxisMaxValue = ColDisAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity min value.
*
* \param   - None
*
* \return  - m_VelocityAxisMinValue : The Velocity min value.
******************************************************************************/
double GraphSettings::getVelocityAxisMinValue() const
{
    return m_VelocityAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Velocity min value.
*
* \param   - VelocityMinValue : The Velocity min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateVelocityAxisMinValue(const double& VelocityMinValue)
{
    if(m_VelocityAxisMinValue != VelocityMinValue)
    {
        m_VelocityAxisMinValue = VelocityMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity max value.
*
* \param   - None.
*
* \return  - m_VelocityAxisMaxValue : The Velocity max value.
******************************************************************************/
double GraphSettings::getVelocityAxisMaxValue() const
{
    return m_VelocityAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Velocity max value.
*
* \param   - VelocityMaxValue : The Velocity max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateVelocityAxisMaxValue(const double& VelocityMaxValue)
{
    if(m_VelocityAxisMaxValue != VelocityMaxValue)
    {
        m_VelocityAxisMaxValue = VelocityMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Requested Amplitude min value.
*
* \param   - None.
*
* \return  - m_ReqAmpAxisMinValue : The Requested Amplitude  min value.
******************************************************************************/
int GraphSettings::getReqAmpAxisMinValue() const
{
    return m_ReqAmpAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Requested Amplitude  min value.
*
* \param   - ReqAmpMinValue : The Requested Amplitude  min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateReqAmpAxisMinValue(const int& ReqAmpMinValue)
{
    if(m_ReqAmpAxisMinValue != ReqAmpMinValue)
    {
        m_ReqAmpAxisMinValue = ReqAmpMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the Requested Amplitude max value.
*
* \param   - None.
*
* \return  - m_ReqAmpAxisMaxValue : The Requested Amplitude max value.
******************************************************************************/
int GraphSettings::getReqAmpAxisMaxValue() const
{
    return m_ReqAmpAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the Requested Amplitude max value.
*
* \param   - ReqAmpMaxValue : The Requested Amplitude max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateReqAmpAxisMaxValue(const int& ReqAmpMaxValue)
{
    if(m_ReqAmpAxisMaxValue != ReqAmpMaxValue)
    {
        m_ReqAmpAxisMaxValue = ReqAmpMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the time min value.
*
* \param   - None.
*
* \return  - m_TimeAxisMinValue : The time min value.
******************************************************************************/
double GraphSettings::getTimeAxisMinValue() const
{
    return m_TimeAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the time min value.
*
* \param   - TimeAxisMinValue : The time min value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateTimeAxisMinValue(const double &TimeAxisMinValue)
{
    if(m_TimeAxisMinValue != TimeAxisMinValue)
    {
        m_TimeAxisMinValue = TimeAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the time max value.
*
* \param   - None.
*
* \return  - m_TimeAxisMaxValue : The time max value.
******************************************************************************/
double GraphSettings::getTimeAxisMaxValue() const
{
    return m_TimeAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the time max value.
*
* \param   - TimeAxisMaxValue : The time max value.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateTimeAxisMaxValue(const double &TimeAxisMaxValue)
{
    if(m_TimeAxisMaxValue != TimeAxisMaxValue)
    {
        m_TimeAxisMaxValue = TimeAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function updates the sampling interval.
*
* \param   - None.
*
* \return  - The sampling interval.
******************************************************************************/
int GraphSettings::getSamplingInterval() const
{
    return m_SamplingInterval;
}

/**************************************************************************//**
*
* \brief   - Below function updates the sampling interval.
*
* \param   - value : The sampling interval.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateSamplingInterval(const int &SamplingInterval)
{
    m_SamplingInterval = SamplingInterval;

    if(m_WeldSignatureACE != nullptr)
    {
        m_WeldSignatureACE->InitiateGraphSamplingIntervalUpdateRequest(m_SamplingInterval);
    }

    emit OnGraphSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the auto save graph enable status.
*
* \param   - None.
*
* \return  - The auto save graph enable status.
******************************************************************************/
bool GraphSettings::getAutoSaveGraph() const
{
    return m_IsAutoSaveGraph;
}

/**************************************************************************//**
*
* \brief   - Below function updates the auto save graph status.
*
* \param   - AutoSaveGraph : The auto save graph status.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAutoSaveGraph(const bool &AutoSaveGraph)
{
    m_IsAutoSaveGraph = AutoSaveGraph;

    if(m_WeldSignatureACE != nullptr)
    {
        m_WeldSignatureACE->InitiateAutoSaveGraphUpdateRequest(m_IsAutoSaveGraph);
    }

    emit OnGraphSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function fetches the auto scale status for Y axis.
*
* \param   - None.
*
* \return  - storedValue : Auto scale status.
******************************************************************************/
bool GraphSettings::getAutoScaleYAxis() const
{
    bool storedValue = settings.value("AutoScaleYAxis").toBool();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the auto scale status for Y axis.
*
* \param   - AutoScaleYAxis : Auto scale status.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAutoScaleYAxis(const bool &AutoScaleYAxis)
{
    settings.setValue("AutoScaleYAxis", AutoScaleYAxis);
}

/**************************************************************************//**
*
* \brief   - Below function fetches the auto scale status for Time axis.
*
* \param   - None.
*
* \return  - storedValue : Auto scale status.
******************************************************************************/
double GraphSettings::getAutoScaleTimeAxis() const
{
    bool storedValue = settings.value("AutoScaleTimeAxis").toBool();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the auto scale status for Time axis.
*
* \param   - AutoScaleTimeAxis : Auto scale status.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateAutoScaleTimeAxis(const double &AutoScaleTimeAxis)
{
    settings.setValue("AutoScaleTimeAxis", AutoScaleTimeAxis);
}

/**************************************************************************//**
*
* \brief   - Below function fetches the TWH line display status.
*
* \param   - None.
*
* \return  - storedValue : The TWH line display status.
******************************************************************************/
bool GraphSettings::getTWHLineDisplay() const
{
    bool storedValue = settings.value("TWHLineDisplay").toBool();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the TWH line display status.
*
* \param   - TWHLineDisplay : The TWH line display status.
*
* \return  - None.
******************************************************************************/
void GraphSettings::updateTWHLineDisplay(const bool &TWHLineDisplay)
{
    settings.setValue("TWHLineDisplay", TWHLineDisplay);
    emit OnGraphSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude min value.
*
* \param   - None.
*
* \return  - m_ActualAmpAxisMinValue : The amplitude min value.
******************************************************************************/
int GraphSettings::getActualAmpAxisMinValue()
{
    return m_ActualAmpAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude max value.
*
* \param   - None.
*
* \return  - m_ActualAmpAxisMaxValue : The amplitude max value.
******************************************************************************/
int GraphSettings::getActualAmpAxisMaxValue()
{
    return m_ActualAmpAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the power min value.
*
* \param   - None.
*
* \return  - m_ActualPowerAxisMinValue : The power min value.
******************************************************************************/
double GraphSettings::getActualPowerAxisMinValue()
{
    return m_ActualPowerAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the power max value.
*
* \param   - None.
*
* \return  - m_ActualPowerAxisMaxValue : The power max value.
******************************************************************************/
double GraphSettings::getActualPowerAxisMaxValue()
{
    return m_ActualPowerAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency min value.
*
* \param   - None.
*
* \return  - m_FreqAxisMinValue : The frequency min value.
******************************************************************************/
int GraphSettings::getActualFreqAxisMinValue()
{
    return m_ActualFreqAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency max value.
*
* \param   - None.
*
* \return  - m_FreqAxisMaxValue : The frequency max value.
******************************************************************************/
int GraphSettings::getActualFreqAxisMaxValue()
{
    return m_ActualFreqAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase min value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMinValue : The phase min value.
******************************************************************************/
int GraphSettings::getActualPhaseAxisMinValue()
{
    return m_ActualPhaseAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase max value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMaxValue : The phase max value.
******************************************************************************/
int GraphSettings::getActualPhaseAxisMaxValue()
{
    return m_ActualPhaseAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the current min value.
*
* \param   - None.
*
* \return  - m_ActualCurrentAxisMinValue : The current min value.
******************************************************************************/
int GraphSettings::getActualCurrentAxisMinValue()
{
    return m_ActualCurrentAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the current max value.
*
* \param   - None.
*
* \return  - m_ActualCurrentAxisMaxValue : The current max value.
******************************************************************************/
int GraphSettings::getActualCurrentAxisMaxValue()
{
    return m_ActualCurrentAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the energy min value.
*
* \param   - None.
*
* \return  - m_EnergyAxisMinValue : The energy min value.
******************************************************************************/
double GraphSettings::getActualEnergyAxisMinValue()
{
    return m_ActualEnergyAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the energy max value.
*
* \param   - None.
*
* \return  - m_EnergyAxisMaxValue : The energy max value.
******************************************************************************/
double GraphSettings::getActualEnergyAxisMaxValue()
{
    return m_ActualEnergyAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the force min value.
*
* \param   - None.
*
* \return  - m_ForceAxisMinValue : The force min value.
******************************************************************************/
double GraphSettings::getActualForceAxisMinValue()
{
    return m_ActualForceAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the force The value.
*
* \param   - None.
*
* \return  - m_ForceAxisMaxValue : The force max value.
******************************************************************************/
double GraphSettings::getActualForceAxisMaxValue()
{
    return m_ActualForceAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the absolute distance min value.
*
* \param   - None.
*
* \return  - m_AbsDisAxisMinValue : The absolute distance min value.
******************************************************************************/
double GraphSettings::getActualAbsDisAxisMinValue()
{
    return m_ActualAbsDisAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the absolute distance max value.
*
* \param   - None.
*
* \return  - m_AbsDisAxisMaxValue : The absolute distance max value.
******************************************************************************/
double GraphSettings::getActualAbsDisAxisMaxValue()
{
    return m_ActualAbsDisAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the collapse distance min value.
*
* \param   - None.
*
* \return  - m_ColDisAxisMinValue : The collapse distance min value.
******************************************************************************/
double GraphSettings::getActualColDisAxisMinValue()
{
    return m_ActualColDisAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the collapse distance max value.
*
* \param   - None.
*
* \return  - m_ColDisAxisMaxValue : The collapse distance max value.
******************************************************************************/
double GraphSettings::getActualColDisAxisMaxValue()
{
    return m_ActualColDisAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity min value.
*
* \param   - None
*
* \return  - m_VelocityAxisMinValue : The Velocity min value.
******************************************************************************/
double GraphSettings::getActualVelocityAxisMinValue()
{
    return m_ActualVelocityAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Velocity max value.
*
* \param   - None.
*
* \return  - m_VelocityAxisMaxValue : The Velocity max value.
******************************************************************************/
double GraphSettings::getActualVelocityAxisMaxValue()
{
    return m_ActualVelocityAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Requested Amplitude min value.
*
* \param   - None.
*
* \return  - m_ReqAmpAxisMinValue : The Requested Amplitude  min value.
******************************************************************************/
int GraphSettings::getActualReqAmpAxisMinValue()
{
    return m_ActualReqAmpAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Requested Amplitude max value.
*
* \param   - None.
*
* \return  - m_ReqAmpAxisMaxValue : The Requested Amplitude max value.
******************************************************************************/
int GraphSettings::getActualReqAmpAxisMaxValue()
{
    return m_ActualReqAmpAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the time min value.
*
* \param   - None.
*
* \return  - m_TimeAxisMinValue : The time min value.
******************************************************************************/
double GraphSettings::getActualTimeAxisMinValue()
{
    return m_ActualTimeAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function returns the time max value.
*
* \param   - None.
*
* \return  - m_TimeAxisMaxValue : The time max value.
******************************************************************************/
double GraphSettings::getActualTimeAxisMaxValue()
{
    return m_ActualTimeAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function fetch the updated weld signature settings.
*
* \param   - WeldSignatureSettings_Obj : Weld signature object.
*
* \return  - None.
******************************************************************************/
void GraphSettings::OnNoWeldSignatureSettingsUpdated(WeldSignatureACE *WeldSignatureSettings_Obj)
{
    m_WeldSignatureACE = WeldSignatureSettings_Obj;

    m_SamplingInterval = m_WeldSignatureACE->GetGraphSamplingInterval();
    m_IsAutoSaveGraph = m_WeldSignatureACE->GetIsAutoSaveGraphEnabled();

    emit OnGraphSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function fetch the updated weld signature data.
*
* \param   - WeldSignatureSettings_Obj : Weld signature object.
*
* \return  - None.
******************************************************************************/
void GraphSettings::OnWeldSignatureSettingsUpdated(WeldSignatureACE *WeldSignatureSettings_Obj)
{
    m_WeldSignatureACE = WeldSignatureSettings_Obj;
    m_RequestedWeldSignatureData = m_WeldSignatureACE->GetRequestedWeldSignatureData();

    bool storedValueTime = settings.value("AutoScaleTimeAxis").toBool();
    bool storedValueYAxis = settings.value("AutoScaleYAxis").toBool();

    if(storedValueTime)
    {
        m_TimeAxisMinValue      = m_RequestedWeldSignatureData.front().Time;
        m_TimeAxisMaxValue      = m_RequestedWeldSignatureData.back().Time;
    }

    if(storedValueYAxis)
    {

        auto m_AmpAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Amplitude < b.Amplitude;
                                               });
        m_AmpAxisMinValue =  m_AmpAxisMinValue1->Amplitude;

        auto m_AmpAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Amplitude < b.Amplitude;
                                           });
        m_AmpAxisMaxValue=m_AmpAxisMaxValue1->Amplitude;

        auto m_PowerAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Power < b.Power;
                                               });
        m_PowerAxisMinValue =  m_PowerAxisMinValue1->Power;

        auto m_PowerAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Power < b.Power;
                                           });
        m_PowerAxisMaxValue=m_PowerAxisMaxValue1->Power;

        auto m_FreqAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Frequency < b.Frequency;
                                               });
        m_FreqAxisMinValue =  m_FreqAxisMinValue1->Frequency;

        auto m_FreqAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Frequency < b.Frequency;
                                           });
        m_FreqAxisMaxValue=m_FreqAxisMaxValue1->Frequency;

        auto m_PhaseAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Phase < b.Phase;
                                               });
        m_PhaseAxisMinValue =  m_PhaseAxisMinValue1->Phase;

        auto m_PhaseAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Phase < b.Phase;
                                           });
        m_PhaseAxisMaxValue=m_PhaseAxisMaxValue1->Phase;

        auto m_CurrentAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Current < b.Current;
                                               });
        m_CurrentAxisMinValue =  m_CurrentAxisMinValue1->Current;

        auto m_CurrentAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Current < b.Current;
                                           });
        m_CurrentAxisMaxValue=m_CurrentAxisMaxValue1->Current;

        auto m_EnergyAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Energy < b.Energy;
                                               });
        m_EnergyAxisMinValue =  m_EnergyAxisMinValue1->Energy;

        auto m_EnergyAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Energy < b.Energy;
                                           });
        m_EnergyAxisMaxValue=m_EnergyAxisMaxValue1->Energy;

        auto m_ForceAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.Force < b.Force;
                                               });
        m_ForceAxisMinValue =  m_ForceAxisMinValue1->Force;

        auto m_ForceAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.Force < b.Force;
                                           });
        m_ForceAxisMaxValue=m_ForceAxisMaxValue1->Force;

        auto m_AbsDisAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.AbsoluteDistance < b.AbsoluteDistance;
                                               });
        m_AbsDisAxisMinValue =  m_AbsDisAxisMinValue1->AbsoluteDistance;

        auto m_AbsDisAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.AbsoluteDistance < b.AbsoluteDistance;
                                           });
        m_AbsDisAxisMaxValue=m_AbsDisAxisMaxValue1->AbsoluteDistance;

        auto m_ColDisAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                               [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                   return a.CollapseDistance < b.CollapseDistance;
                                               });
        m_ColDisAxisMinValue =  m_ColDisAxisMinValue1->CollapseDistance;

        auto m_ColDisAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                           [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                               return a.CollapseDistance < b.CollapseDistance;
                                           });
        m_ColDisAxisMaxValue=m_ColDisAxisMaxValue1->CollapseDistance;

        auto m_ReqAmpMixValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                          return a.RequestAmplitude < b.RequestAmplitude;
                                                      });
        m_ReqAmpAxisMinValue =  m_ReqAmpMixValue1->RequestAmplitude;

        auto m_ReqAmpMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                          return a.RequestAmplitude < b.RequestAmplitude;
                                                      });
        m_ReqAmpAxisMaxValue = m_ReqAmpMaxValue1->RequestAmplitude;


        auto m_VelocityAxisMinValue1 = std::min_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                                  [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                      return a.Velocity < b.Velocity;
                                                  });
        m_VelocityAxisMinValue =  m_VelocityAxisMinValue1->Velocity;

        auto m_VelocityAxisMaxValue1 = std::max_element(m_RequestedWeldSignatureData.begin(), m_RequestedWeldSignatureData.end(),
                                                  [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
                                                      return a.Velocity < b.Velocity;
                                                  });
        m_VelocityAxisMaxValue = m_VelocityAxisMaxValue1->Velocity;


        if(m_AmpAxisMinValue == m_AmpAxisMaxValue)
        {
            m_AmpAxisMinValue     = 0;
            m_AmpAxisMaxValue     = 120;
        }

        if(m_PowerAxisMinValue == m_PowerAxisMaxValue)
        {
            m_PowerAxisMinValue   = 0;
            m_PowerAxisMaxValue   = 10;
        }

        if(m_FreqAxisMinValue == m_FreqAxisMaxValue)
        {
            m_FreqAxisMinValue    = 19450;
            m_FreqAxisMaxValue    = 20450;
        }

        if(m_PhaseAxisMinValue == m_PhaseAxisMaxValue)
        {
            m_PhaseAxisMinValue   = -180;
            m_PhaseAxisMaxValue   = 180;
        }

        if(m_CurrentAxisMinValue == m_CurrentAxisMaxValue)
        {
            m_CurrentAxisMinValue   = 0;
            m_CurrentAxisMaxValue   = 120;
        }

        if(m_EnergyAxisMinValue == m_EnergyAxisMaxValue)
        {
            m_EnergyAxisMinValue  = 0;
            m_EnergyAxisMaxValue  = 50;
        }

        if(m_ForceAxisMinValue == m_ForceAxisMaxValue)
        {
            m_ForceAxisMinValue   = 0;
            m_ForceAxisMaxValue   = 120;
        }

        if(m_AbsDisAxisMinValue == m_AbsDisAxisMaxValue)
        {
            m_AbsDisAxisMinValue  = 0;
            m_AbsDisAxisMaxValue  = 120;
        }

        if(m_ColDisAxisMinValue == m_ColDisAxisMaxValue)
        {
            m_ColDisAxisMinValue  = -5;
            m_ColDisAxisMaxValue  = 5;
        }

        if(m_ReqAmpAxisMinValue == m_ReqAmpAxisMaxValue)
        {
            m_ReqAmpAxisMinValue  = 0;
            m_ReqAmpAxisMaxValue  = 100;
        }

        if(m_VelocityAxisMinValue == m_VelocityAxisMaxValue)
        {
            m_VelocityAxisMinValue  = 0;
            m_VelocityAxisMaxValue  = 120;
        }

        m_ActualAmpAxisMinValue      = m_AmpAxisMinValue;
        m_ActualAmpAxisMaxValue      = m_AmpAxisMaxValue;
        m_ActualPowerAxisMinValue    = m_PowerAxisMinValue;
        m_ActualPowerAxisMaxValue    = m_PowerAxisMaxValue;
        m_ActualFreqAxisMinValue     = m_FreqAxisMinValue;
        m_ActualFreqAxisMaxValue     = m_FreqAxisMaxValue;
        m_ActualPhaseAxisMinValue    = m_PhaseAxisMinValue;
        m_ActualPhaseAxisMaxValue    = m_PhaseAxisMaxValue;
        m_ActualCurrentAxisMinValue  = m_CurrentAxisMinValue;
        m_ActualCurrentAxisMaxValue  = m_CurrentAxisMaxValue;
        m_ActualEnergyAxisMinValue   = m_EnergyAxisMinValue;
        m_ActualEnergyAxisMaxValue   = m_EnergyAxisMaxValue;
        m_ActualForceAxisMinValue    = m_ForceAxisMinValue;
        m_ActualForceAxisMaxValue    = m_ForceAxisMaxValue;
        m_ActualAbsDisAxisMinValue   = m_AbsDisAxisMinValue;
        m_ActualAbsDisAxisMaxValue   = m_AbsDisAxisMaxValue;
        m_ActualColDisAxisMinValue   = m_ColDisAxisMinValue;
        m_ActualColDisAxisMaxValue   = m_ColDisAxisMaxValue;
        m_ActualReqAmpAxisMinValue   = m_ReqAmpAxisMinValue;
        m_ActualVelocityAxisMinValue = m_VelocityAxisMinValue;
        m_ActualReqAmpAxisMaxValue   = m_ReqAmpAxisMaxValue;
        m_ActualVelocityAxisMaxValue = m_VelocityAxisMaxValue;
        m_ActualTimeAxisMinValue     = m_TimeAxisMinValue;
        m_ActualTimeAxisMaxValue     = m_TimeAxisMaxValue;
    }

    if(storedValueTime || storedValueYAxis)
    {
        emit referenceGraphSettingsChanged();
    }

    m_SamplingInterval = m_WeldSignatureACE->GetGraphSamplingInterval();
    m_IsAutoSaveGraph = m_WeldSignatureACE->GetIsAutoSaveGraphEnabled();

    emit graphSettingsChanged();
    emit OnGraphSettingsChanged();
}


/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ReferenceWeldGraphData.cpp file handles  Reference Weld Signature 
    data on HMI.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 20/11/2024 - Initial version.
***************************************************************************/
#include "ReferenceWeldGraphData.h"
#include "GraphSettings.h"
/**************************************************************************//**
*
* \brief  - Constructor
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/

ReferenceWeldGraphData::ReferenceWeldGraphData(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::ReferenceWeldSignatureUpdated, this, &ReferenceWeldGraphData::OnRefWeldSignatureGraphListUpdated);
}

/**************************************************************************//**
*
* \brief   - Below function returns the time min value.
*
* \param   - None.
*
* \return  - m_TimeAxisMinValue : The time min value.
******************************************************************************/
double ReferenceWeldGraphData::getTimeAxisMinValue() const
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
void ReferenceWeldGraphData::updateTimeAxisMinValue(const double &TimeAxisMinValue)
{
    if(m_TimeAxisMinValue != TimeAxisMinValue)
    {
        m_TimeAxisMinValue = TimeAxisMinValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getTimeAxisMaxValue() const
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
void ReferenceWeldGraphData::updateTimeAxisMaxValue(const double &TimeAxisMaxValue)
{
    if(m_TimeAxisMaxValue != TimeAxisMaxValue)
    {
        m_TimeAxisMaxValue = TimeAxisMaxValue;
        emit graphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude min value.
*
* \param   - None.
*
* \return  - m_AmpAxisMinValue : The amplitude min value.
******************************************************************************/
int ReferenceWeldGraphData::getAmpAxisMinValue() const
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
void ReferenceWeldGraphData::updateAmpAxisMinValue(const int &AmpAxisMinValue)
{
    if(m_AmpAxisMinValue != AmpAxisMinValue)
    {
        m_AmpAxisMinValue = AmpAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getAmpAxisMaxValue() const
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
void ReferenceWeldGraphData::updateAmpAxisMaxValue(const int &AmpAxisMaxValue)
{
    if(m_AmpAxisMaxValue != AmpAxisMaxValue)
    {
        m_AmpAxisMaxValue = AmpAxisMaxValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getPowerAxisMinValue() const
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
void ReferenceWeldGraphData::updatePowerAxisMinValue(const double &PowerAxisMinValue)
{
    if(m_PowerAxisMinValue != PowerAxisMinValue)
    {
        m_PowerAxisMinValue = PowerAxisMinValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getPowerAxisMaxValue() const
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
void ReferenceWeldGraphData::updatePowerAxisMaxValue(const double &PowerAxisMaxValue)
{
    if(m_PowerAxisMaxValue != PowerAxisMaxValue)
    {
        m_PowerAxisMaxValue = PowerAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getFreqAxisMinValue() const
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
void ReferenceWeldGraphData::updateFreqAxisMinValue(const int &FreqAxisMinValue)
{
    if(m_FreqAxisMinValue != FreqAxisMinValue)
    {
        m_FreqAxisMinValue = FreqAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getFreqAxisMaxValue() const
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
void ReferenceWeldGraphData::updateFreqAxisMaxValue(const int &FreqAxisMaxValue)
{
    if(m_FreqAxisMaxValue != FreqAxisMaxValue)
    {
        m_FreqAxisMaxValue = FreqAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getPhaseAxisMinValue() const
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
void ReferenceWeldGraphData::updatePhaseAxisMinValue(const int &PhaseAxisMinValue)
{
    if(m_PhaseAxisMinValue != PhaseAxisMinValue)
    {
        m_PhaseAxisMinValue = PhaseAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getPhaseAxisMaxValue() const
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
void ReferenceWeldGraphData::updatePhaseAxisMaxValue(const int &PhaseAxisMaxValue)
{
    if(m_PhaseAxisMaxValue != PhaseAxisMaxValue)
    {
        m_PhaseAxisMaxValue = PhaseAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getCurrentAxisMinValue() const
{
    return m_CurrentAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current min value.
*
* \param   - WeldRecipeNumber : The current min value.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::updateCurrentAxisMinValue(const int &CurrentAxisMinValue)
{
    if(m_CurrentAxisMinValue != CurrentAxisMinValue)
    {
        m_CurrentAxisMinValue = CurrentAxisMinValue;
        emit graphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current max value.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : The current max value.
******************************************************************************/
int ReferenceWeldGraphData::getCurrentAxisMaxValue() const
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
void ReferenceWeldGraphData::updateCurrentAxisMaxValue(const int &CurrentAxisMaxValue)
{
    if(m_CurrentAxisMaxValue != CurrentAxisMaxValue)
    {
        m_CurrentAxisMaxValue = CurrentAxisMaxValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getEnergyAxisMinValue() const
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
void ReferenceWeldGraphData::updateEnergyAxisMinValue(const double &EnergyAxisMinValue)
{
    if(m_EnergyAxisMinValue != EnergyAxisMinValue)
    {
        m_EnergyAxisMinValue = EnergyAxisMinValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getEnergyAxisMaxValue() const
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
void ReferenceWeldGraphData::updateEnergyAxisMaxValue(const double &EnergyAxisMaxValue)
{
    if(m_EnergyAxisMaxValue != EnergyAxisMaxValue)
    {
        m_EnergyAxisMaxValue = EnergyAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getForceAxisMinValue() const
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
void ReferenceWeldGraphData::updateForceAxisMinValue(const int &ForceAxisMinValue)
{
    if(m_ForceAxisMinValue != ForceAxisMinValue)
    {
        m_ForceAxisMinValue = ForceAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getForceAxisMaxValue() const
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
void ReferenceWeldGraphData::updateForceAxisMaxValue(const int &ForceAxisMaxValue)
{
    if(m_ForceAxisMaxValue != ForceAxisMaxValue)
    {
        m_ForceAxisMaxValue = ForceAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getAbsDisAxisMinValue() const
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
void ReferenceWeldGraphData::updateAbsDisAxisMinValue(const int &AbsDisAxisMinValue)
{
    if(m_AbsDisAxisMinValue != AbsDisAxisMinValue)
    {
        m_AbsDisAxisMinValue = AbsDisAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getAbsDisAxisMaxValue() const
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
void ReferenceWeldGraphData::updateAbsDisAxisMaxValue(const int &AbsDisAxisMaxValue)
{
    if(m_AbsDisAxisMaxValue != AbsDisAxisMaxValue)
    {
        m_AbsDisAxisMaxValue = AbsDisAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getColDisAxisMinValue() const
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
void ReferenceWeldGraphData::updateColDisAxisMinValue(const int &ColDisAxisMinValue)
{
    if(m_ColDisAxisMinValue != ColDisAxisMinValue)
    {
        m_ColDisAxisMinValue = ColDisAxisMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getColDisAxisMaxValue() const
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
void ReferenceWeldGraphData::updateColDisAxisMaxValue(const int &ColDisAxisMaxValue)
{
    if(m_ColDisAxisMaxValue != ColDisAxisMaxValue)
    {
        m_ColDisAxisMaxValue = ColDisAxisMaxValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getReqAmpAxisMinValue() const
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
void ReferenceWeldGraphData::updateReqAmpAxisMinValue(const int& ReqAmpMinValue)
{
    if(m_ReqAmpAxisMinValue != ReqAmpMinValue)
    {
        m_ReqAmpAxisMinValue = ReqAmpMinValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getVelocityAxisMinValue() const
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
void ReferenceWeldGraphData::updateVelocityAxisMinValue(const double& VelocityMinValue)
{
    if(m_VelocityAxisMinValue != VelocityMinValue)
    {
        m_VelocityAxisMinValue = VelocityMinValue;
        emit graphSettingsChanged();
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
int ReferenceWeldGraphData::getReqAmpAxisMaxValue() const
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
void ReferenceWeldGraphData::updateReqAmpAxisMaxValue(const int& ReqAmpMaxValue)
{
    if(m_ReqAmpAxisMaxValue != ReqAmpMaxValue)
    {
        m_ReqAmpAxisMaxValue = ReqAmpMaxValue;
        emit graphSettingsChanged();
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
double ReferenceWeldGraphData::getVelocityAxisMaxValue() const
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
void ReferenceWeldGraphData::updateVelocityAxisMaxValue(const double& VelocityMaxValue)
{
    if(m_VelocityAxisMaxValue != VelocityMaxValue)
    {
        m_VelocityAxisMaxValue = VelocityMaxValue;
        emit graphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief Destructor to clear all allocations
*
* \param none
*
* \return none
*
******************************************************************************/
ReferenceWeldGraphData::~ReferenceWeldGraphData()
{
    m_TimePoints.clear();
    m_FreqPoints.clear();
    m_PowerPoints.clear();
    m_AmpPoints.clear();
    m_EnergyPoints.clear();
    m_ForcePoints.clear();
    m_CollapsePoints.clear();
    m_AbsolutePoints.clear();
    m_VelocityPoints.clear();
    m_CurrPoints.clear();
    m_PhasPoints.clear();
    m_AxisMinParameters.clear();
    m_AxisMaxParameters.clear();
    m_ReqAmpPoints.clear();
}

/**************************************************************************//**
*
* \brief To update the specific plot of the chart view using the a_series and a_type
*
* \param a_series is the plot that has been defined in the Chart View qml.
*        a_type is the indicator of the graph and axis that
*        has been defined in the GraphAxisEnum and is available both for the c++ and qml
*
* \return the data length
*
******************************************************************************/
int ReferenceWeldGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
{
    QXYSeries *xySeries = static_cast<QXYSeries *>(a_series);

    int length = 0 ;
    /* Switch Case to determine the type*/
    switch(a_type)
    {
    case GraphAxisEnum::FREQ_IDX:   /* Frequency Graph */
        xySeries->replace(m_FreqPoints);
        length = m_FreqPoints.count();
        break;
    case GraphAxisEnum::AMP_IDX:    /* Amplitude Graph */
        xySeries->replace(m_AmpPoints);
        length = m_AmpPoints.count();
        break;
    case GraphAxisEnum::POWER_IDX:  /* Power Graph */
        xySeries->replace(m_PowerPoints);
        length = m_PowerPoints.count();
        break;
    case GraphAxisEnum::ENERGY_IDX: /* Energy Graph */
        xySeries->replace(m_EnergyPoints);
        length = m_EnergyPoints.count();
        break;
    case GraphAxisEnum::FORCE_IDX:  /* Force Graph */
        xySeries->replace(m_ForcePoints);
        length = m_ForcePoints.count();
        break;
    case GraphAxisEnum::COLLAPSEDIST_IDX: /* Collapse Distance Graph */
        xySeries->replace(m_CollapsePoints);
        length = m_CollapsePoints.count();
        break;
    case GraphAxisEnum::ABSOLUTEDIST_IDX: /* Absolute Distance Graph */
        xySeries->replace(m_AbsolutePoints);
        length = m_AbsolutePoints.count();
        break;
    case GraphAxisEnum::CURRENT_IDX:      /* Current Graph */
        xySeries->replace(m_CurrPoints);
        length = m_CurrPoints.count();
        break;
    case GraphAxisEnum::PHASE_IDX:        /* Phase Graph */
        xySeries->replace(m_PhasPoints);
        length = m_PhasPoints.count();
        break;
    case GraphAxisEnum::REQAMP_IDX:        /* Requested Amplitude Graph */
        xySeries->replace(m_ReqAmpPoints);
        length = m_ReqAmpPoints.count();
        break;
    case GraphAxisEnum::VELOCITY_IDX:        /* Velocity Graph */
        xySeries->replace(m_VelocityPoints);
        length = m_VelocityPoints.count();
        break;
    default:
        break ;
    }

    return length;
}

/**************************************************************************//**
*
* \brief To parse the graph data that should from the SC and calculate the maximum and minimum value for the each type data.
*
* \param receiveData is the raw data from SC, length is the received data length
*
* \return the parsed result, if there is any issue during the data parsing, it will return -1, otherwise it will return 0.
*
******************************************************************************/
void ReferenceWeldGraphData::receiveReferenceWeldGraphData()
{
    clearGraph();

    for(int i = 0; i < m_RequestedReferenceWeldSignatureData.size(); i++)
    {
        m_FreqPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Frequency));
        m_PowerPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Power));
        m_AmpPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Amplitude));
        m_EnergyPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Energy));
        m_ForcePoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Force));
        m_CollapsePoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].CollapseDistance));
        m_AbsolutePoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].AbsoluteDistance));
        m_CurrPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Current));
        m_PhasPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Phase));
        m_ReqAmpPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].RequestAmplitude));
        m_VelocityPoints.append(QPointF(m_RequestedReferenceWeldSignatureData[i].Time, m_RequestedReferenceWeldSignatureData[i].Velocity));
    }
}

/**************************************************************************//**
*
* \brief To save the axis minimum settings to the internal list m_AxisMinParameters.
*
* \param a_axisVal is the temporary list for the axis minimum settings.
*
* \return none.
*
******************************************************************************/
void ReferenceWeldGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
{
    m_AxisMinParameters.clear();
    m_AxisMinParameters.append(a_axisVal);
}

/**************************************************************************//**
*
* \brief To save the axis maximum settings to the internal list m_AxisMaxParameters.
*
* \param a_axisVal is the temporary list for the axis minimum settings.
*
* \return
*
******************************************************************************/
void ReferenceWeldGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
{
    m_AxisMaxParameters.clear();
    m_AxisMaxParameters.append(a_axisVal);
}

/**************************************************************************//**
*
* \brief To get the axis minimum settings from internal list m_AxisMinParameters.
*
* \param none
*
* \return QList<qreal> m_AxisMinParameters
*
******************************************************************************/
QList<qreal> ReferenceWeldGraphData::getAxisMinParameters()
{
    return m_AxisMinParameters;
}

/**************************************************************************//**
*
* \brief To get the axis maximum settings from internal list m_AxisMaxParameters.
*
* \param none
*
* \return QList<qreal> m_AxisMaxParameters
*
******************************************************************************/
QList<qreal> ReferenceWeldGraphData::getAxisMaxParameters()
{
    return m_AxisMaxParameters;
}

/**************************************************************************//**
*
* \brief To clear all the data points list of the each plot.
*
* \param none
*
* \return none
*
******************************************************************************/
void ReferenceWeldGraphData::clearGraph()
{
    m_FreqPoints.clear();
    m_PowerPoints.clear();
    m_AmpPoints.clear();
    m_EnergyPoints.clear();
    m_ForcePoints.clear();
    m_CollapsePoints.clear();
    m_AbsolutePoints.clear();
    m_CurrPoints.clear();
    m_PhasPoints.clear();
    m_ReqAmpPoints.clear();
    m_VelocityPoints.clear();
}

/**************************************************************************//**
*
* \brief   - Below function is used to fetch the weldResultIndex of the Reference Graphs.
*
* \param   - Index.
*
* \return  - weldResultIndex.
******************************************************************************/
int ReferenceWeldGraphData::refweldResultIndex(int Index)
{
    return m_RequestedReferenceGraphData[Index].RefweldResultIndex ;
}
/**************************************************************************//**
*
* \brief   - Below function fetched the Reference GRaph name based on the index.
*
* \param   - Index.
*
* \return  - RefGraphName.
******************************************************************************/
QString ReferenceWeldGraphData::refGraphName(int Index)
{
       QString refGraphName = QString::fromUtf8(m_RequestedReferenceGraphData[Index].RefGraphName);
       return refGraphName;
}
/**************************************************************************//**
*
* \brief   - Below function gives the total number of reference graphs available.
*
* \param   - None.
*
* \return  - Total reference graphs available.
******************************************************************************/
int ReferenceWeldGraphData::availableReferenceGraphSize()
{
    return  m_RequestedReferenceGraphData.size();
}
/**************************************************************************//**
*
* \brief   - Below is used by QML to set the reference weld signature from HMI.
*
* \param   - Index - WeldResultIndex of the selected graph.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::addReferenceGraphRequest(int Index)
{
    m_ReferenceWeldSignature->SetReferenceWeldSignatureRequestFromHMI(Index);
}
/**************************************************************************//**
*
* \brief   - Below function updates Reference graph name from HMI.
*
* \param   - newRefGraphName.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::addReferenceGraphNameChangeRequest(int Index, QString NewName)
{
    m_ReferenceWeldSignature->InitiateReferenceWeldSignatureNameUpdateRequest(Index, NewName.toStdString());//NewName.toStdString().c_str());
}
/**************************************************************************//**
*
* \brief   - Below function updates Reference graph name from HMI.
*
* \param   - OldIndex - GraphIndex to be replaced
*            NewIndex - Newly selected grpah .
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::replaceOldGraphWithNewGraphRequest(int OldIndex, int NewIndex)
{
    m_ReferenceWeldSignature->InitiateReplaceOldRefGraphWithNewRefGraphRequest(OldIndex, NewIndex);
}

/**************************************************************************//**
*
* \brief   - Below function updates qml when component is loaded by emiting signal.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::refereshRefGraphList()
{
    emit referenceGraphDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function set new reference weld signature based on index.
*
* \param   - Index : The index number.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::setReferenceWeldSignatureRequest(int Index)
{
    while(!m_AvailableReferenceWeldData.empty())
    {
        m_AvailableReferenceWeldData.pop();
    }

    m_AvailableReferenceWeldData = m_ReferenceWeldSignature->GetAvailableReferenceWeldData();
    m_RequestedReferenceWeldSignatureData.clear();

    for (int i = 0; !m_AvailableReferenceWeldData.empty(); ++i)
    {
        if(i == Index)
        {
            m_RequestedReferenceWeldSignatureData = m_AvailableReferenceWeldData.front();
            break;
        }

        else
        {
            m_AvailableReferenceWeldData.pop();
        }
    }

    if(settings.value("AutoScaleTimeAxis").toBool())
    {
        m_TimeAxisMinValue = m_RequestedReferenceWeldSignatureData.front().Time;
        m_TimeAxisMaxValue = m_RequestedReferenceWeldSignatureData.back().Time;
    }

    if(settings.value("AutoScaleYAxis").toBool())
    {
        auto m_AmpAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                   [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Amplitude < b.Amplitude;
        });
        m_AmpAxisMinValue =  m_AmpAxisMinValue1->Amplitude;

        auto m_AmpAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                   [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Amplitude < b.Amplitude;
        });
        m_AmpAxisMaxValue=m_AmpAxisMaxValue1->Amplitude;

        auto m_PowerAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Power < b.Power;
        });
        m_PowerAxisMinValue =  m_PowerAxisMinValue1->Power;

        auto m_PowerAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Power < b.Power;
        });
        m_PowerAxisMaxValue=m_PowerAxisMaxValue1->Power;

        auto m_FreqAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                    [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Frequency < b.Frequency;
        });
        m_FreqAxisMinValue =  m_FreqAxisMinValue1->Frequency;

        auto m_FreqAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                    [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Frequency < b.Frequency;
        });
        m_FreqAxisMaxValue=m_FreqAxisMaxValue1->Frequency;

        auto m_PhaseAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Phase < b.Phase;
        });
        m_PhaseAxisMinValue =  m_PhaseAxisMinValue1->Phase;

        auto m_PhaseAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Phase < b.Phase;
        });
        m_PhaseAxisMaxValue=m_PhaseAxisMaxValue1->Phase;

        auto m_CurrentAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                       [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Current < b.Current;
        });
        m_CurrentAxisMinValue =  m_CurrentAxisMinValue1->Current;

        auto m_CurrentAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                       [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Current < b.Current;
        });
        m_CurrentAxisMaxValue=m_CurrentAxisMaxValue1->Current;

        auto m_EnergyAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Energy < b.Energy;
        });
        m_EnergyAxisMinValue =  m_EnergyAxisMinValue1->Energy;

        auto m_EnergyAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Energy < b.Energy;
        });
        m_EnergyAxisMaxValue=m_EnergyAxisMaxValue1->Energy;

        auto m_ForceAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Force < b.Force;
        });
        m_ForceAxisMinValue =  m_ForceAxisMinValue1->Force;

        auto m_ForceAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                     [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Force < b.Force;
        });
        m_ForceAxisMaxValue=m_ForceAxisMaxValue1->Force;

        auto m_AbsDisAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.AbsoluteDistance < b.AbsoluteDistance;
        });
        m_AbsDisAxisMinValue =  m_AbsDisAxisMinValue1->AbsoluteDistance;

        auto m_AbsDisAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.AbsoluteDistance < b.AbsoluteDistance;
        });
        m_AbsDisAxisMaxValue=m_AbsDisAxisMaxValue1->AbsoluteDistance;

        auto m_ColDisAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.CollapseDistance < b.CollapseDistance;
        });
        m_ColDisAxisMinValue =  m_ColDisAxisMinValue1->CollapseDistance;

        auto m_ColDisAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                      [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.CollapseDistance < b.CollapseDistance;
        });
        m_ColDisAxisMaxValue=m_ColDisAxisMaxValue1->CollapseDistance;

        auto m_ReqAmpMixValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                  [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.RequestAmplitude < b.RequestAmplitude;
        });
        m_ReqAmpAxisMinValue =  m_ReqAmpMixValue1->RequestAmplitude;

        auto m_ReqAmpMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                  [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.RequestAmplitude < b.RequestAmplitude;
        });
        m_ReqAmpAxisMaxValue = m_ReqAmpMaxValue1->RequestAmplitude;


        auto m_VelocityAxisMinValue1 = std::min_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                        [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Velocity < b.Velocity;
        });
        m_VelocityAxisMinValue =  m_VelocityAxisMinValue1->Velocity;

        auto m_VelocityAxisMaxValue1 = std::max_element(m_RequestedReferenceWeldSignatureData.begin(), m_RequestedReferenceWeldSignatureData.end(),
                                                        [](const WeldSignatureACEStruct& a, const WeldSignatureACEStruct& b) {
            return a.Velocity < b.Velocity;
        });
        m_VelocityAxisMaxValue = m_VelocityAxisMaxValue1->Velocity;
    }

    emit graphSettingsChanged();

    /*To avoid false min max reading of each X-Y Parameters*/
    m_IsFirstRequestGenerated = true;
    receiveReferenceWeldGraphData();
}

/**************************************************************************//**
*
* \brief   - Below function provide the flag value which avoid false min max
*            reading of each X-Y Parameters.
*
* \param   - None.
*
* \return  - m_IsFirstRequestGenerated : The flag to decide min max
*            reading of each X-Y Parameters.
******************************************************************************/
bool ReferenceWeldGraphData::isFirstRequestGenerated()
{
    return m_IsFirstRequestGenerated;
}

/**************************************************************************//**
*
* \brief   - Use to copy reference weld graph data
*
* \param   - None.
*
* \return  - m_RequestedReferenceGraphData : weld result queue.
******************************************************************************/
std::deque<ReferenceGraphStruct> ReferenceWeldGraphData::copyReferenceGraphData()
{
    return m_RequestedReferenceGraphData;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnRefWeldSignatureGraphListUpdated to update the reference weld cycle
*            details list data.
*
* \param   - ReferenceWeldSignature_Obj : Object pointer of type ReferenceWeldSignature.
*
* \return  - None.
******************************************************************************/
void ReferenceWeldGraphData::OnRefWeldSignatureGraphListUpdated(ReferenceWeldSignature *ReferenceWeldSignature_Obj, int WelderId)
{
    m_ReferenceWeldSignature = ReferenceWeldSignature_Obj;
    if(m_ReferenceWeldSignature->GetIsReferenceGraphDetailsAvailable() || WelderId != m_ActiveWelderId )
    {
        m_RequestedReferenceGraphData = m_ReferenceWeldSignature->GetReferenceGraphStruct();
        m_AvailableReferenceWeldData = m_ReferenceWeldSignature->GetAvailableReferenceWeldData();

        m_ActiveWelderId = WelderId;
        m_ReferenceWeldSignature->SetIsReferenceGraphDetailsAvailable();

        emit referenceGraphDataChanged();
    }

    if(m_ReferenceWeldSignature->GetRefGraphStatusFromASC())
    {
        emit replaceGraphSuccessfully();
        m_ReferenceWeldSignature->SetReplaceRefGraphStatus();
    }
}




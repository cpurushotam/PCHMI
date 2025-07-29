/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    WeldGraphData.cpp file provides graph backend data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 17/10/2023 - Initial version.
***************************************************************************/
#include "WeldGraphData.h"
#include <QQmlContext>

extern QQmlContext* pQmlContext;

/**************************************************************************//**
*
* \brief It is the Constructor to instantiate WeldGraphData object
*
* \param parent QObject
*
* \return WeldGraphData object
*
******************************************************************************/
WeldGraphData::WeldGraphData(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::AnalyticsSignatureUpdated, this, &WeldGraphData::OnWeldSignatureUpdated);
    /*Weld signature data available flag*/
     m_IsRequestedWeldSignatureDataAvailable = false;
     /*Weld signature is emty or not*/
     m_IsEmptyWeldSignatureReceived = false;
     /*To avoid repeated initiation request while signature being read*/
     m_IsLatestWeldSignatureReadRequest = true;
     m_IsCycleCountWeldSignatureReadRequest = false;
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
WeldGraphData::~WeldGraphData()
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
int WeldGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
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
void WeldGraphData::receiveWeldGraphData()
{
        clearGraph();

        for(int i = 0; i < m_RequestedWeldSignatureData.size(); i++)
        {
            m_FreqPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Frequency));
            m_PowerPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Power));
            m_AmpPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Amplitude));
            m_EnergyPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Energy));
            m_ForcePoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Force));
            m_CollapsePoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].CollapseDistance));
            m_AbsolutePoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].AbsoluteDistance));
            m_CurrPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Current));
            m_PhasPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Phase));
            m_ReqAmpPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].RequestAmplitude));
            m_VelocityPoints.append(QPointF(m_RequestedWeldSignatureData[i].Time, m_RequestedWeldSignatureData[i].Velocity));

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
void WeldGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
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
void WeldGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
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
QList<qreal> WeldGraphData::getAxisMinParameters()
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
QList<qreal> WeldGraphData::getAxisMaxParameters()
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
void WeldGraphData::clearGraph()
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
* \brief   - Below function initiates the weld graph signature request for
*            given cyclecount.
*
* \param   - CycleCountValue : The cycle count requested.
*            Value : The flag to avoid multiple initiation request for weld
*            signature.
*
* \return  - None.
******************************************************************************/
void WeldGraphData::initiateWeldGraphSignature(int CycleCountValue, bool Value)
{
    /*Below m_RequestSelectedCycleNo value shall be updated as per requested by
      user by clicking on cycle no or by default value after new weld cycle done.*/

    /*To avoid multiple initiation request for weld signature*/
    m_IsLatestWeldSignatureReadRequest = Value;

    if(m_WeldSignatureACE != nullptr)
    {
        /*To fetch weld graph signature for default updated cycle*/
        if(m_IsLatestWeldSignatureReadRequest)
        {
            /*m_WeldSignatureACE = m_CycleDetailsListModel.getWeldSignatureACE();*/
            m_WeldSignatureACE->InitiateWeldSignatureReadRequest(CycleCountValue);

            /*To avoid repeated initiation request while signature being read*/
            m_IsRequestedWeldSignatureDataAvailable = false;
            m_IsLatestWeldSignatureReadRequest = false;
            emit updateGraphInitiated();
        }

        /*To fetch weld graph signature for requested cycle no*/
        if(m_IsCycleCountWeldSignatureReadRequest)
        {
            m_WeldSignatureACE = m_CycleDetailsListModel.getWeldSignatureACE();
            m_WeldSignatureACE->InitiateWeldSignatureReadRequest(m_RequestSelectedCycleNo);

            /*To avoid repeated initiation request while signature being read*/
            m_IsRequestedWeldSignatureDataAvailable = false;
            m_IsCycleCountWeldSignatureReadRequest = false;
            emit updateGraphInitiated();
        }

        /*Complete or not status read*/
        if(m_WeldSignatureACE->GetIsCompleteWeldSignatureReceived())
        {
            /*Reset the flag*/
            m_IsRequestedWeldSignatureDataAvailable = true;
            m_RequestedWeldSignatureData = m_WeldSignatureACE->GetRequestedWeldSignatureData();

            if(m_RequestedWeldSignatureData.size() == 0)
            {
                m_IsEmptyWeldSignatureReceived = true;
                m_WeldSignatureACE->SetIsCompleteWeldSignatureReceived(false);

                /*To update weld signature settings before display of graph*/
                emit initiateNoWeldGraphSignatureSettings(m_WeldSignatureACE);

                emit updateGraphAvailable();
            }

            else
            {
                m_IsEmptyWeldSignatureReceived = false;

                /*To update weld signature settings before display of graph*/
                emit initiateWeldGraphSignatureSettings(m_WeldSignatureACE);

                m_WeldSignatureACE->SetIsCompleteWeldSignatureReceived(false);
                receiveWeldGraphData();

                emit updateGraphAvailable();
            }
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function fetches the status whether requested signature data
*            available or not.
*
* \param   - None.
*
* \return  - m_IsRequestedWeldSignatureDataAvailable : Status of request.
******************************************************************************/
bool WeldGraphData::isRequestedWeldSignatureDataAvailable()
{
    return m_IsRequestedWeldSignatureDataAvailable;
}

/**************************************************************************//**
*
* \brief   - Below function updates cycle count value requested by user.
*
* \param   - Value : The requested cycle count number.
*
* \return  - None.
******************************************************************************/
void WeldGraphData::requestSelectedCycleNo(int Value)
{
    m_RequestSelectedCycleNo = Value;

    /*To indicate user initiated request for cycle detail*/
    m_IsCycleCountWeldSignatureReadRequest = true;
}

/**************************************************************************//**
*
* \brief   - Below function fetches the status whether empty signature
*            received or not?
*
* \param   - None.
*
* \return  - m_IsEmptyWeldSignatureReceived : Status of request.
******************************************************************************/
bool WeldGraphData::isEmptyWeldSignatureReceived()
{
    return m_IsEmptyWeldSignatureReceived;
}

/**************************************************************************//**
*
* \brief To calculate the maximum axis value.
* If the coming data is more than the maximum value, the maximum axis value will be equal to the comming data.
*
* \param a_axisVal is the current maximum axis value, a_val is the new coming data.
*
* \return none
*
******************************************************************************/
void WeldGraphData::calculateLargest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal < a_val)
    {
        a_axisVal = a_val;
    }
}

/**************************************************************************//**
*
* \brief To calculate the minimum axis value.
*
* \param a_axisVal is the current minimum axis value, a_val is the new coming data.
*
* \return none
*
******************************************************************************/
void WeldGraphData::calculateSmallest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal > a_val)
    {
        a_axisVal = a_val;
    }
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnWeldSignatureUpdated to update the weld
*            signature data.
*
* \param   - AnlyticsGraphScreenWeldSignature_Obj : The weld signature object.
*            WelderId : Active welder Id.
*
* \return  - None.
******************************************************************************/
void WeldGraphData::OnWeldSignatureUpdated(WeldSignatureACE *AnlyticsGraphScreenWeldSignature_Obj, int WelderId)
{
    if(m_ActiveWelderId != WelderId)
    {
        m_WeldSignatureACE = AnlyticsGraphScreenWeldSignature_Obj;
        m_ActiveWelderId = WelderId;
    }
}

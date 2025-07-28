/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanGraphData.cpp file provides graph backend data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 03/04/2024 - Initial version.
***************************************************************************/
#include "ScanGraphData.h"
#include <QQmlContext>

extern QQmlContext* pQmlContext;

/**************************************************************************//**
*
* \brief It is the Constructor to instantiate ScanGraphData object
*
* \param parent QObject
*
* \return ScanGraphData object
*
******************************************************************************/
ScanGraphData::ScanGraphData(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::ScanSignatureUpdated, this, &ScanGraphData::OnScanSignatureUpdated);

    /*Scan signature data available flag*/
     m_IsRequestedScanSignatureDataAvailable = false;
     /*Scan signature is emty or not*/
     m_IsEmptyScanSignatureReceived = false;
     /*To avoid repeated initiation request while signature being read*/
     m_IsLatestScanSignatureReadRequest = true;
     m_IsCycleCountScanSignatureReadRequest = false;
     /*To update TWH LinesCreating and initializing the resonant points*/
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
ScanGraphData::~ScanGraphData()
{
    m_FreqPoints.clear();
    m_AmpPoints.clear();
    m_CurrPoints.clear();
    m_PhasPoints.clear();
    m_AxisMinParameters.clear();
    m_AxisMaxParameters.clear();
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
int ScanGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
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
    case GraphAxisEnum::CURRENT_IDX:      /* Current Graph */
        xySeries->replace(m_CurrPoints);
        length = m_CurrPoints.count();
        break;
    case GraphAxisEnum::PHASE_IDX:        /* Phase Graph */
        xySeries->replace(m_PhasPoints);
        length = m_PhasPoints.count();
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
void ScanGraphData::receiveScanGraphData()
{
        clearGraph();

        for(int i = 0; i < m_ScanSignatureData.size(); i++)
        {
            m_AmpPoints.append(QPointF(m_ScanSignatureData[i].Frequency, m_ScanSignatureData[i].Amplitude));
            m_CurrPoints.append(QPointF(m_ScanSignatureData[i].Frequency, m_ScanSignatureData[i].Current));
            m_PhasPoints.append(QPointF(m_ScanSignatureData[i].Frequency, m_ScanSignatureData[i].Phase));
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
void ScanGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
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
void ScanGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
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
QList<qreal> ScanGraphData::getAxisMinParameters()
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
QList<qreal> ScanGraphData::getAxisMaxParameters()
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
void ScanGraphData::clearGraph()
{
    m_FreqPoints.clear();
    m_AmpPoints.clear();
    m_CurrPoints.clear();
    m_PhasPoints.clear();
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
void ScanGraphData::initiateScanGraphSignature(int CycleCountValue, bool Value)
{
    /*To avoid multiple initiation request for weld signature*/
    m_IsLatestScanSignatureReadRequest = Value;

    if(m_ScanSignature != nullptr)
    {
        /*To fetch weld graph signature for default updated cycle*/
        if(m_IsLatestScanSignatureReadRequest)
        {
            /*m_ScanSignatureACE = m_ScanCycleDetailsListModel.getScanSignatureACE();*/
            m_ScanSignature->InitiateHornScanSignatureReadRequest(CycleCountValue);

            /*To avoid repeated initiation request while signature being read*/
            m_IsRequestedScanSignatureDataAvailable = false;
            m_IsLatestScanSignatureReadRequest = false;

            /*Here we do not have condition where graph being initiated
              as there should be signature available every time*/
            emit updateGraphInitiated();
        }

        /*To fetch weld graph signature for requested cycle no*/
        if(m_IsCycleCountScanSignatureReadRequest)
        {
            /*m_ScanSignatureACE = m_ScanCycleDetailsListModel.getScanSignatureACE();*/
            m_ScanSignature->InitiateHornScanSignatureReadRequest(m_RequestSelectedCycleNo);

            /*To avoid repeated initiation request while signature being read*/
            m_IsRequestedScanSignatureDataAvailable = false;
            m_IsCycleCountScanSignatureReadRequest = false;
            emit updateGraphInitiated();
        }

        /*Complete or not status read*/
        if(m_ScanSignature->GetIsLastHornScanSignatureUpdated() )
        {
            /*Reset the flag*/
            m_IsRequestedScanSignatureDataAvailable = true;
            m_ScanSignatureData = m_ScanSignature->GetHornScanSignatureData();

            if(m_ScanSignatureData.size() == 0)
            {
                m_IsEmptyScanSignatureReceived = true;
                m_ScanSignature->SetIsLastHornScanSignatureUpdated(false);
                emit updateGraphAvailable();
            }
            
            else
            {
                m_IsEmptyScanSignatureReceived = false;
                
                /*To update weld signature settings before display of graph*/
                emit initiateScanGraphSignatureSettings(m_ScanSignature);
                
                m_ScanSignature->SetIsLastHornScanSignatureUpdated(false);
                receiveScanGraphData();
                
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
* \return  - m_IsRequestedScanSignatureDataAvailable : Status of request.
******************************************************************************/
bool ScanGraphData::isRequestedScanSignatureDataAvailable()
{
    return m_IsRequestedScanSignatureDataAvailable;
}

/**************************************************************************//**
*
* \brief   - Below function updates cycle count value requested by user.
*
* \param   - Value : The requested cycle count number.
*
* \return  - None.
******************************************************************************/
void ScanGraphData::requestSelectedCycleNo(int Value)
{
    m_RequestSelectedCycleNo = Value;

    /*To indicate user initiated request for cycle detail*/
    m_IsCycleCountScanSignatureReadRequest = true;
}

/**************************************************************************//**
*
* \brief   - Below function fetches the status whether empty signature
*            received or not?
*
* \param   - None.
*
* \return  - m_IsEmptyScanSignatureReceived : Status of request.
******************************************************************************/
bool ScanGraphData::isEmptyScanSignatureReceived()
{
    return m_IsEmptyScanSignatureReceived;
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
void ScanGraphData::calculateLargest(qreal &a_axisVal, qreal a_val)
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
void ScanGraphData::calculateSmallest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal > a_val)
    {
        a_axisVal = a_val;
    }
}
/**************************************************************************//**
*
* \brief   - Role of the slot OnSeekSignatureUpdated to update the horn seek
*            signature data.
*
* \param   - DiagnosticsSeekSignatureScreen_Obj : The seek signature object.
*            WelderId : Active welder Id.
*
* \return  - None.
******************************************************************************/
void ScanGraphData::OnScanSignatureUpdated(HornScanSignature *DiagnosticsScanSignatureScreen_Obj, int WelderId)
{
    if(m_ActiveWelderId != WelderId)
    {
        m_ScanSignature = DiagnosticsScanSignatureScreen_Obj;
        m_ActiveWelderId = WelderId;
    }
}

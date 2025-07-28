/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    TestGraphData.cpp file provides graph backend data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/03/2024 - Initial version.
***************************************************************************/
#include "TestGraphData.h"
#include <QQmlContext>

extern QQmlContext* pQmlContext;

/**************************************************************************//**
*
* \brief It is the Constructor to instantiate TestGraphData object
*
* \param parent QObject
*
* \return TestGraphData object
*
******************************************************************************/
TestGraphData::TestGraphData(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::TestSignatureUpdated, this, &TestGraphData::OnTestSignatureUpdated);
    /*test signature data available flag*/
     m_IsRequestedTestSignatureDataAvailable = false;
     /*test signature is emty or not*/
     m_IsEmptyTestSignatureReceived = false;
     /*To avoid repeated initiation request while signature being read*/
     m_IsLatestTestSignatureReadRequest = true;
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
TestGraphData::~TestGraphData()
{
    m_TimePoints.clear();
    m_FreqPoints.clear();
    m_PowerPoints.clear();
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
int TestGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
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
void TestGraphData::receiveTestGraphData()
{
        clearGraph();

        for(int i = 0; i < m_RequestedTestSignatureData.size(); i++)
        {
            m_FreqPoints.append(QPointF(m_RequestedTestSignatureData[i].Time, m_RequestedTestSignatureData[i].Frequency));
            m_PowerPoints.append(QPointF(m_RequestedTestSignatureData[i].Time, m_RequestedTestSignatureData[i].Power));
            m_AmpPoints.append(QPointF(m_RequestedTestSignatureData[i].Time, m_RequestedTestSignatureData[i].Amplitude));
            m_CurrPoints.append(QPointF(m_RequestedTestSignatureData[i].Time, m_RequestedTestSignatureData[i].Current));
            m_PhasPoints.append(QPointF(m_RequestedTestSignatureData[i].Time, m_RequestedTestSignatureData[i].Phase));
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
void TestGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
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
void TestGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
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
QList<qreal> TestGraphData::getAxisMinParameters()
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
QList<qreal> TestGraphData::getAxisMaxParameters()
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
void TestGraphData::clearGraph()
{
    m_FreqPoints.clear();
    m_PowerPoints.clear();
    m_AmpPoints.clear();
    m_CurrPoints.clear();
    m_PhasPoints.clear();
}

/**************************************************************************//**
*
* \brief   - Below function initiates the test graph signature request for
*            given cyclecount.
*
* \param   - Value : The flag to avoid multiple initiation request for test
*            signature.
*
* \return  - None.
******************************************************************************/
void TestGraphData::initiateTestGraphSignature(bool Value)
{
    /*To avoid multiple initiation request for test signature*/
    m_IsLatestTestSignatureReadRequest = Value;

    if(m_TestSignature != nullptr)
    {
        /*To fetch test graph signature for default updated cycle*/
        if(m_IsLatestTestSignatureReadRequest)
        {
            /*m_TestSignature = m_Test.getTestSignature();
              m_TestSignature->InitiateTestSignatureReadRequest();*/

            /*To avoid repeated initiation request while signature being read*/
            m_IsRequestedTestSignatureDataAvailable = false;
            m_IsLatestTestSignatureReadRequest = false;
            /*Here we do not have condition where graph being initiated
              as there should be signature available every time*/
            /*emit updateGraphInitiated();*/
        }

        /*Complete or not status read*/
        if(m_TestSignature->GetIsCompleteTestSignatureReceived() || (m_IsScreenReNavigated))
        {
            /*Reset the flag*/
            m_IsRequestedTestSignatureDataAvailable = true;
            m_RequestedTestSignatureData = m_TestSignature->GetRequestedTestSignatureData();
            m_IsScreenReNavigated = false;

            if(m_RequestedTestSignatureData.size() == 0)
            {
                m_IsEmptyTestSignatureReceived = true;
                m_TestSignature->SetIsCompleteTestSignatureReceived(false);
                emit updateGraphAvailable();
            }

            else
            {
                m_IsEmptyTestSignatureReceived = false;

                /*To update test signature settings before display of graph*/
                emit initiateTestGraphSignatureSettings(m_TestSignature);
                m_TestSignature->SetIsCompleteTestSignatureReceived(false);
                receiveTestGraphData();

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
* \return  - m_IsRequestedTestSignatureDataAvailable : Status of request.
******************************************************************************/
bool TestGraphData::isRequestedTestSignatureDataAvailable()
{
    return m_IsRequestedTestSignatureDataAvailable;
}

/**************************************************************************//**
*
* \brief   - Below function fetches the status whether empty signature
*            received or not?
*
* \param   - None.
*
* \return  - m_IsEmptyTestSignatureReceived : Status of request.
******************************************************************************/
bool TestGraphData::isEmptyTestSignatureReceived()
{
    return m_IsEmptyTestSignatureReceived;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void TestGraphData::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
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
void TestGraphData::calculateLargest(qreal &a_axisVal, qreal a_val)
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
void TestGraphData::calculateSmallest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal > a_val)
    {
        a_axisVal = a_val;
    }
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnSeekSignatureUpdated to update the test
*            signature data.
*
* \param   - DiagnosticsTestSignatureScreen_Obj : The test signature object.
*            WelderId : Active welder Id.
*
* \return  - None.
******************************************************************************/
void TestGraphData::OnTestSignatureUpdated(TestSignature *DiagnosticsTestSignatureScreen_Obj, int WelderId)
{
    if(m_ActiveWelderId != WelderId)
    {
        m_TestSignature = DiagnosticsTestSignatureScreen_Obj;
        m_ActiveWelderId = WelderId;
    }
}

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

double WeldGraphData::m_SonicsData[9000] = {0};
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
    /* Creating and initializing the resonant points*/
       m_weldPoints.append(new WeldResonantPoints("T", 0));
       m_weldPoints.append(new WeldResonantPoints("W", 0));
       m_weldPoints.append(new WeldResonantPoints("H", 0));

       pQmlContext->setContextProperty("weldPointModel",QVariant::fromValue(m_weldPoints));
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
    m_axisMinParameters.clear();
    m_axisMaxParameters.clear();
    m_weldPoints.clear();
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
int WeldGraphData::receiveWeldGraphData(double* receiveData, int length)
{
    int ind = 0 ;
    QString weldGraphResMsg;
    QString wordRead ;
    double* weldGraphResBuff;
    int totalParamsEntries = 0;
    int retVal = 0;
    int totalEntriesPerParams = 0;
    double tmpTime;
    double tmpFreq;
    double tmpPower;
    double tmpAmp;
    double tmpEnergy = 0;
    double tmpForce;
    double tmpCollapseDist;
    double tmpAbsoluteDist;
    double tmpCurrent;
    double tmpPhase;

    /* Time, Freq, Phase, Amp, Current, Power, Energy*/
    QList<qreal> axisMinValues ;
    QList<qreal> axisMaxValues;

    for(ind = 0; ind < GraphAxisEnum::TOTAL_IDX; ind++)
    {
        axisMinValues.append(0);
        axisMaxValues.append(100);
    }

    axisMinValues.replace(GraphAxisEnum::PHASE_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::ENERGY_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::FREQ_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::AMP_IDX, MAX_PERCENTAGE);
    axisMinValues.replace(GraphAxisEnum::CURRENT_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::POWER_IDX, MAX_PERCENTAGE);
    axisMinValues.replace(GraphAxisEnum::FORCE_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::ABSOLUTEDIST_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::COLLAPSEDIST_IDX, (uint32_t) - 1);
    axisMinValues.replace(GraphAxisEnum::TIME_IDX, (uint32_t) - 1);

    axisMaxValues.replace(GraphAxisEnum::PHASE_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::ENERGY_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::FREQ_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::AMP_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::CURRENT_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::POWER_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::FORCE_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::ABSOLUTEDIST_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::COLLAPSEDIST_IDX, 0);
    axisMaxValues.replace(GraphAxisEnum::TIME_IDX, 0);

    /* Populate the QList points class members */
    weldGraphResBuff = new double[length];
    for(int i = 0; i < length; i++)
    {
        weldGraphResBuff[i] = receiveData[i];
    }
    totalParamsEntries = length;

    clearGraph();
    try
    {
        /*****************************************************************************/
        /* The data length should be the integer multiple of the parameter count.
         * The PARAMETER_COUNT_PER_GRAPH_SAMPLE is the macro definition of the parameter count.
         * Now totally we have 9 parameters need to sample from SC.
         * If there is not equal to 0, it means the received data is the
         * part of the package rather than the integrated package.
         * So it will return -1.                                                    */
        /****************************************************************************/
        if(0 != (totalParamsEntries % PARAMETER_COUNT_PER_GRAPH_SAMPLE))
        {
            retVal = -1 ;
        }
        else
        {
            totalEntriesPerParams = totalParamsEntries / PARAMETER_COUNT_PER_GRAPH_SAMPLE;

            clearGraph();
            m_GraphPointsCount = totalEntriesPerParams;
            for(ind = 0 ; ind < totalEntriesPerParams ; ind++)
            {
                tmpTime = ind;
                QString strTime = QString::number(tmpTime/1000, 'f', 5);
                tmpTime = strTime.toDouble();

                tmpFreq = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE];
                tmpPower = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 1];
                tmpAmp = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 2];
                tmpForce = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 3];
                tmpCollapseDist = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 4];
                tmpAbsoluteDist = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 5];
                tmpCurrent = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 7];
                tmpPhase = weldGraphResBuff[ind * PARAMETER_COUNT_PER_GRAPH_SAMPLE + 8];

                QString strEnergy = QString::number(tmpPower/1000, 'f', 5);
                tmpEnergy += strEnergy.toDouble();

                calculateLargest(axisMaxValues[GraphAxisEnum::TIME_IDX] , (qreal)tmpTime);
                calculateSmallest(axisMinValues[GraphAxisEnum::TIME_IDX] , (qreal)tmpTime);

                calculateLargest(axisMaxValues[GraphAxisEnum::FREQ_IDX], (qreal)tmpFreq);
                calculateSmallest(axisMinValues[GraphAxisEnum::FREQ_IDX], (qreal)tmpFreq);

                calculateLargest(axisMaxValues[GraphAxisEnum::AMP_IDX], (qreal)tmpAmp);
                calculateSmallest(axisMinValues[GraphAxisEnum::AMP_IDX], (qreal)tmpAmp);

                calculateLargest(axisMaxValues[GraphAxisEnum::POWER_IDX], (qreal)tmpPower);
                calculateSmallest(axisMinValues[GraphAxisEnum::POWER_IDX], (qreal)tmpPower);

                calculateLargest(axisMaxValues[GraphAxisEnum::ENERGY_IDX], (qreal)tmpEnergy);
                calculateSmallest(axisMinValues[GraphAxisEnum::ENERGY_IDX], (qreal)tmpEnergy);

                calculateLargest(axisMaxValues[GraphAxisEnum::FORCE_IDX], (qreal)tmpForce);
                calculateSmallest(axisMinValues[GraphAxisEnum::FORCE_IDX], (qreal)tmpForce);

                calculateLargest(axisMaxValues[GraphAxisEnum::COLLAPSEDIST_IDX], (qreal)tmpCollapseDist);
                calculateSmallest(axisMinValues[GraphAxisEnum::COLLAPSEDIST_IDX], (qreal)tmpCollapseDist);

                calculateLargest(axisMaxValues[GraphAxisEnum::ABSOLUTEDIST_IDX], (qreal)tmpAbsoluteDist);
                calculateSmallest(axisMinValues[GraphAxisEnum::ABSOLUTEDIST_IDX], (qreal)tmpAbsoluteDist);

                calculateLargest(axisMaxValues[GraphAxisEnum::CURRENT_IDX], (qreal)tmpCurrent);
                calculateSmallest(axisMinValues[GraphAxisEnum::CURRENT_IDX], (qreal)tmpCurrent);

                calculateLargest(axisMaxValues[GraphAxisEnum::PHASE_IDX], (qreal)tmpPhase);
                calculateSmallest(axisMinValues[GraphAxisEnum::PHASE_IDX], (qreal)tmpPhase);

                m_FreqPoints.append(QPointF(tmpTime , tmpFreq));
                m_PowerPoints.append(QPointF(tmpTime , tmpPower));
                m_AmpPoints.append(QPointF(tmpTime , tmpAmp));
                m_EnergyPoints.append(QPointF(tmpTime , tmpEnergy));
                m_ForcePoints.append(QPointF(tmpTime , tmpForce));
                m_CollapsePoints.append(QPointF(tmpTime , tmpCollapseDist));
                m_AbsolutePoints.append(QPointF(tmpTime , tmpAbsoluteDist));
                m_CurrPoints.append(QPointF(tmpTime , tmpCurrent));
                m_PhasPoints.append(QPointF(tmpTime , tmpPhase));
            }

            setAxisMaxParameters(axisMaxValues);
            setAxisMinParameters(axisMinValues);
        }
    }
    catch(...)
    {
        qDebug("Crash Occured while reading or assigning the graph data");
        retVal = -1;
    }
    delete [] weldGraphResBuff;
    return retVal;
}

/**************************************************************************//**
*
* \brief To save the axis minimum settings to the internal list m_axisMinParameters.
*
* \param a_axisVal is the temporary list for the axis minimum settings.
*
* \return none.
*
******************************************************************************/
void WeldGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
{
    m_axisMinParameters.clear();
    m_axisMinParameters.append(a_axisVal);
}

/**************************************************************************//**
*
* \brief To save the axis maximum settings to the internal list m_axisMaxParameters.
*
* \param a_axisVal is the temporary list for the axis minimum settings.
*
* \return
*
******************************************************************************/
void WeldGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
{
    m_axisMaxParameters.clear();
    m_axisMaxParameters.append(a_axisVal);
}

/**************************************************************************//**
*
* \brief To get the axis minimum settings from internal list m_axisMinParameters.
*
* \param none
*
* \return QList<qreal> m_axisMinParameters
*
******************************************************************************/
QList<qreal> WeldGraphData::getAxisMinParameters()
{
    return m_axisMinParameters;
}

/**************************************************************************//**
*
* \brief To get the axis maximum settings from internal list m_axisMaxParameters.
*
* \param none
*
* \return QList<qreal> m_axisMaxParameters
*
******************************************************************************/
QList<qreal> WeldGraphData::getAxisMaxParameters()
{
    return m_axisMaxParameters;
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
}

/**************************************************************************//**
*
* \brief It is the data engine for the fake data simulation from SC data reading.
*
* \param none
*
* \return none
*
******************************************************************************/
void WeldGraphData::generateRandomNumber()
{
    QRandomGenerator* rand = new QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 9000; i++)
    {
        m_SonicsData[i] = rand->generate() % 10;
    }
    delete rand;
    receiveWeldGraphData(m_SonicsData, 9000);
}

/**************************************************************************//**
*
* \brief   - Below function fetches the trigger ponit to be shown on graph
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
double WeldGraphData::getTriggerPoint()
{
    WeldResonantPoints *tmpResonantPoints = dynamic_cast<WeldResonantPoints*>(m_weldPoints.at(0));
    double dTriggerPoint = tmpResonantPoints->getXAxisPos();
    return dTriggerPoint;
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
* \brief   - Constructor initiate member variables
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
WeldResonantPoints::WeldResonantPoints(const QString &a_labelName, const double &a_xAxisVal)
{
    m_labelName = a_labelName ;
    m_timePos = a_xAxisVal;
}

/**************************************************************************//**
*
* \brief   - Destructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
WeldResonantPoints::~WeldResonantPoints()
{

}

/**************************************************************************//**
*
* \brief   - Function to return lable name.
*
* \param   - None.
*
* \return  - m_labelName :  Lable name.
******************************************************************************/
QString WeldResonantPoints::getLabelName()
{
    return m_labelName;
}

/**************************************************************************//**
*
* \brief   - Function to return X axis position value.
*
* \param   - None.
*
* \return  - m_timePos : Time axis position i.e X axis.
******************************************************************************/
double WeldResonantPoints::getXAxisPos()
{
    return m_timePos ;
}

/**************************************************************************//**
*
* \brief   - Function to set X axis position value.
*
* \param   - a_val : X axis position value written.
*
* \return  - None.
******************************************************************************/
void WeldResonantPoints::setXAxisPos(double a_val)
{
     m_timePos = a_val;
}

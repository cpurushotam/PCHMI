/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    WeldGraphData.h file provides graph backend data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 17/10/2023 - Initial version.
***************************************************************************/
#ifndef WELDGRAPHDATA_H
#define WELDGRAPHDATA_H

#include <QObject>
#include <QTextStream>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QtMath>
#include <QFile>
#include <QQmlContext>
#include <QDateTime>
#include <QTime>
#include "GraphAxisDef.h"
#include "qrandom.h"
#include <QtCharts/QXYSeries>

#define PARAMETER_COUNT_PER_GRAPH_SAMPLE 9
#define MAX_PERCENTAGE 100

class WeldResonantPoints : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString labelName READ getLabelName NOTIFY labelNameChanged)
    Q_PROPERTY(double xAxisPos READ getXAxisPos NOTIFY xAxisPosChanged)

public :
    WeldResonantPoints(const QString &a_labelName , const double &a_xAxisVal);
    ~WeldResonantPoints();

    QString m_labelName;
    double m_timePos;
    QString getLabelName();
    double getXAxisPos();

    void setXAxisPos(double a_val);

signals:
    void labelNameChanged();
    void xAxisPosChanged();

};


class WeldGraphData : public QObject
{
    Q_OBJECT

public:
    ~WeldGraphData();
public:
    explicit WeldGraphData(QObject *parent = nullptr);
    Q_INVOKABLE int appendSamples(QAbstractSeries* a_series, quint8 a_type);

    Q_INVOKABLE void setAxisMinParameters(QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE void clearGraph();

    Q_INVOKABLE void generateRandomNumber();

    Q_INVOKABLE double getTriggerPoint();
private:
    inline void calculateLargest(qreal &a_axisVal , qreal a_val);
    inline void calculateSmallest(qreal &a_axisVal , qreal a_val);
    int receiveWeldGraphData(double *receiveData, int lenght);

    int m_GraphPointsCount;
    static double m_SonicsData[9000];
    QVector<QPointF> m_TimePoints ;
    QVector<QPointF> m_FreqPoints ;
    QVector<QPointF> m_PowerPoints ;
    QVector<QPointF> m_AmpPoints;
    QVector<QPointF> m_EnergyPoints;
    QVector<QPointF> m_ForcePoints;
    QVector<QPointF> m_CollapsePoints;
    QVector<QPointF> m_AbsolutePoints;
    QVector<QPointF> m_VelocityPoints;
    QVector<QPointF> m_CurrPoints;
    QVector<QPointF> m_PhasPoints;

    /* Axis Parameters */
    QList<qreal> m_axisMinParameters ;
    QList<qreal> m_axisMaxParameters;

    /* Resonant Points */
    QList<QObject*> m_weldPoints;

};

#endif // WELDGRAPHDATA_H

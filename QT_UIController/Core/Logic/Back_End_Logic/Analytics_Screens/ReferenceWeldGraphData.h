/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
   ReferenceWeldGraphData.H file handles the reference weld signature set , get ,
   rename , replace operations on HMI.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 20/11/2024 - Initial version.
***************************************************************************/
#ifndef REFERENCEWELDGRAPHDATA_H
#define REFERENCEWELDGRAPHDATA_H
#include <QObject>
#include <QVariantList>
#include <QtCharts/QXYSeries>
#include <QSettings>
#include "ReferenceWeldSignatureAce.h"
#include "GraphAxisDef.h"
#include "UpdateScreens.h"

/*ReferenceWeldGraphData class declaration*/
class ReferenceWeldGraphData : public QObject
{
private:
    Q_OBJECT
    Q_PROPERTY(double TimeAxisMinValue READ getTimeAxisMinValue WRITE updateTimeAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double TimeAxisMaxValue READ getTimeAxisMaxValue WRITE updateTimeAxisMaxValue NOTIFY graphSettingsChanged)

    Q_PROPERTY(int AmpAxisMinValue READ getAmpAxisMinValue WRITE updateAmpAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int AmpAxisMaxValue READ getAmpAxisMaxValue WRITE updateAmpAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double PowerAxisMinValue READ getPowerAxisMinValue WRITE updatePowerAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double PowerAxisMaxValue READ getPowerAxisMaxValue WRITE updatePowerAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int FreqAxisMinValue READ getFreqAxisMinValue WRITE updateFreqAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int FreqAxisMaxValue READ getFreqAxisMaxValue WRITE updateFreqAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMinValue READ getPhaseAxisMinValue WRITE updatePhaseAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMaxValue READ getPhaseAxisMaxValue WRITE updatePhaseAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int CurrentAxisMinValue READ getCurrentAxisMinValue WRITE updateCurrentAxisMinValue NOTIFY graphSettingsChanged )
    Q_PROPERTY(int CurrentAxisMaxValue READ getCurrentAxisMaxValue WRITE updateCurrentAxisMaxValue NOTIFY graphSettingsChanged )
    Q_PROPERTY(double EnergyAxisMinValue READ getEnergyAxisMinValue WRITE updateEnergyAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double EnergyAxisMaxValue READ getEnergyAxisMaxValue WRITE updateEnergyAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int ForceAxisMinValue READ getForceAxisMinValue WRITE updateForceAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int ForceAxisMaxValue READ getForceAxisMaxValue WRITE updateForceAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int AbsDisAxisMinValue READ getAbsDisAxisMinValue WRITE updateAbsDisAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int AbsDisAxisMaxValue READ getAbsDisAxisMaxValue WRITE updateAbsDisAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int ColDisAxisMinValue READ getColDisAxisMinValue WRITE updateColDisAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int ColDisAxisMaxValue READ getColDisAxisMaxValue WRITE updateColDisAxisMaxValue NOTIFY graphSettingsChanged)

    Q_PROPERTY(int ReqAmpAxisMinValue READ getReqAmpAxisMinValue WRITE updateReqAmpAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double VelocityAxisMinValue READ getVelocityAxisMinValue WRITE updateVelocityAxisMinValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(int ReqAmpAxisMaxValue READ getReqAmpAxisMaxValue WRITE updateReqAmpAxisMaxValue NOTIFY graphSettingsChanged)
    Q_PROPERTY(double VelocityAxisMaxValue READ getVelocityAxisMaxValue WRITE updateVelocityAxisMaxValue NOTIFY graphSettingsChanged)

public:
    ~ReferenceWeldGraphData();
    explicit ReferenceWeldGraphData(QObject *parent = nullptr);
    QSettings settings;

    double getTimeAxisMinValue() const;
    void updateTimeAxisMinValue(const double& TimeAxisMinValue);

    double getTimeAxisMaxValue() const;
    void updateTimeAxisMaxValue(const double& TimeAxisMaxValue);

    int getAmpAxisMinValue() const;
    void updateAmpAxisMinValue(const int& AmpAxisMinValue);

    int getAmpAxisMaxValue() const;
    void updateAmpAxisMaxValue(const int& AmpAxisMaxValue);

    double getPowerAxisMinValue() const;
    void updatePowerAxisMinValue(const double& PowerAxisMinValue);

    double getPowerAxisMaxValue() const;
    void updatePowerAxisMaxValue(const double& PowerAxisMaxValue);

    int getFreqAxisMinValue() const;
    void updateFreqAxisMinValue(const int& FreqAxisMinValue);

    int getFreqAxisMaxValue() const;
    void updateFreqAxisMaxValue(const int& FreqAxisMaxValue);

    int getPhaseAxisMinValue() const;
    void updatePhaseAxisMinValue(const int& PhaseAxisMinValue);

    int getPhaseAxisMaxValue() const;
    void updatePhaseAxisMaxValue(const int& PhaseAxisMaxValue);

    int getCurrentAxisMinValue() const;
    void updateCurrentAxisMinValue(const int& CurrentAxisMinValue);

    int getCurrentAxisMaxValue() const;
    void updateCurrentAxisMaxValue(const int& CurrentAxisMaxValue);

    double getEnergyAxisMinValue() const;
    void updateEnergyAxisMinValue(const double& EnergyAxisMinValue);

    double getEnergyAxisMaxValue() const;
    void updateEnergyAxisMaxValue(const double& EnergyAxisMaxValue);

    int getForceAxisMinValue() const;
    void updateForceAxisMinValue(const int& ForceAxisMinValue);

    int getForceAxisMaxValue() const;
    void updateForceAxisMaxValue(const int& ForceAxisMaxValue);

    int getAbsDisAxisMinValue() const;
    void updateAbsDisAxisMinValue(const int& AbsDisAxisMinValue);

    int getAbsDisAxisMaxValue() const;
    void updateAbsDisAxisMaxValue(const int& AbsDisAxisMaxValue);

    int getColDisAxisMinValue() const;
    void updateColDisAxisMinValue(const int& ColDisAxisMinValue);

    int getColDisAxisMaxValue() const;
    void updateColDisAxisMaxValue(const int& ColDisAxisMaxValue);

    double getVelocityAxisMinValue() const;
    void updateVelocityAxisMinValue(const double& VelocityMinValue);

    double getVelocityAxisMaxValue() const;
    void updateVelocityAxisMaxValue(const double& VelocityMaxValue);

    int getReqAmpAxisMaxValue() const;
    void updateReqAmpAxisMaxValue(const int& ReqAmpMaxValue);

    int getReqAmpAxisMinValue() const;
    void updateReqAmpAxisMinValue(const int& ReqAmpMinValue);

    Q_INVOKABLE int appendSamples(QAbstractSeries* a_series, quint8 a_type);
    Q_INVOKABLE void receiveReferenceWeldGraphData();

    Q_INVOKABLE void setAxisMinParameters(QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE void clearGraph();

    /* Q_INVOKABLE methods used by QML to perform Refernce Graph operation*/
    Q_INVOKABLE int refweldResultIndex(int Index);
    Q_INVOKABLE int availableReferenceGraphSize();
    Q_INVOKABLE QString refGraphName(int Index);
    Q_INVOKABLE void addReferenceGraphRequest(int Index);
    Q_INVOKABLE void addReferenceGraphNameChangeRequest(int Index, QString NewName);
    Q_INVOKABLE void replaceOldGraphWithNewGraphRequest(int OldIndex, int NewIndex);
    Q_INVOKABLE void refereshRefGraphList();
    Q_INVOKABLE void setReferenceWeldSignatureRequest(int Index);
    Q_INVOKABLE bool isFirstRequestGenerated();
    Q_INVOKABLE std::deque<ReferenceGraphStruct> copyReferenceGraphData();

private:

    int m_GraphPointsCount;
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

     QVector<QPointF> m_ReqAmpPoints;

    /* Axis Parameters */
    QList<qreal> m_AxisMinParameters ;
    QList<qreal> m_AxisMaxParameters;

    int m_ActiveWelderId = -1;
    ReferenceWeldSignature *m_ReferenceWeldSignature;
    //Holds Requested ReferenceGraphData Data
    std::deque<ReferenceGraphStruct> m_RequestedReferenceGraphData;
    //Holds Requested Reference Weld Signature Data
    std::deque<WeldSignatureACEStruct> m_RequestedReferenceWeldSignatureData;
    std::queue<std::deque<WeldSignatureACEStruct>> m_AvailableReferenceWeldData;

    double m_TimeAxisMinValue;
    double m_TimeAxisMaxValue;

    int     m_AmpAxisMinValue;
    int     m_AmpAxisMaxValue;
    double     m_PowerAxisMinValue;
    double     m_PowerAxisMaxValue;
    int     m_FreqAxisMinValue;
    int     m_FreqAxisMaxValue;
    int     m_PhaseAxisMinValue;
    int     m_PhaseAxisMaxValue;
    int     m_CurrentAxisMinValue;
    int     m_CurrentAxisMaxValue;
    double     m_EnergyAxisMinValue;
    double     m_EnergyAxisMaxValue;
    int     m_ForceAxisMinValue;
    int     m_ForceAxisMaxValue;
    int     m_AbsDisAxisMinValue;
    int     m_AbsDisAxisMaxValue;
    int     m_ColDisAxisMinValue;
    int     m_ColDisAxisMaxValue;

    int     m_ReqAmpAxisMinValue;
    double  m_VelocityAxisMinValue;

    int     m_ReqAmpAxisMaxValue;
    double  m_VelocityAxisMaxValue;

    bool m_IsFirstRequestGenerated = false;

signals:
    /* Signals used to update HMI */
    void referenceGraphDataChanged();
    void replaceGraphSuccessfully();
    void graphSettingsChanged();

private slots:
    /*Slot to be called when data update signal generated by communication thread*/
    void OnRefWeldSignatureGraphListUpdated(ReferenceWeldSignature *ReferenceWeldSignature_Obj, int WelderId);

};
#endif // ReferenceWeldGraphData_H

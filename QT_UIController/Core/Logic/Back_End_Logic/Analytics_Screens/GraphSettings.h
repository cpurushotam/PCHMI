/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    GraphSettings.h file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/11/2023 - Initial version.
***************************************************************************/
#ifndef GRAPHSETTINGS_H
#define GRAPHSETTINGS_H
#include <QObject>
#include <QSettings>
#include "WeldSignatureAce.h"


class GraphSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int FirstAxisValue READ getFirstAxisValue WRITE updateFirstAxisValuee NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int SecondAxisValue READ getSecondAxisValue WRITE updateSecondAxisValue NOTIFY OnGraphSettingsChanged)

    Q_PROPERTY(int AmpAxisMinValue READ getAmpAxisMinValue WRITE updateAmpAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int AmpAxisMaxValue READ getAmpAxisMaxValue WRITE updateAmpAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double PowerAxisMinValue READ getPowerAxisMinValue WRITE updatePowerAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double PowerAxisMaxValue READ getPowerAxisMaxValue WRITE updatePowerAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int FreqAxisMinValue READ getFreqAxisMinValue WRITE updateFreqAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int FreqAxisMaxValue READ getFreqAxisMaxValue WRITE updateFreqAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMinValue READ getPhaseAxisMinValue WRITE updatePhaseAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMaxValue READ getPhaseAxisMaxValue WRITE updatePhaseAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int CurrentAxisMinValue READ getCurrentAxisMinValue WRITE updateCurrentAxisMinValue NOTIFY OnGraphSettingsChanged )
    Q_PROPERTY(int CurrentAxisMaxValue READ getCurrentAxisMaxValue WRITE updateCurrentAxisMaxValue NOTIFY OnGraphSettingsChanged )
    Q_PROPERTY(double EnergyAxisMinValue READ getEnergyAxisMinValue WRITE updateEnergyAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double EnergyAxisMaxValue READ getEnergyAxisMaxValue WRITE updateEnergyAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double ForceAxisMinValue READ getForceAxisMinValue WRITE updateForceAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double ForceAxisMaxValue READ getForceAxisMaxValue WRITE updateForceAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double AbsDisAxisMinValue READ getAbsDisAxisMinValue WRITE updateAbsDisAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double AbsDisAxisMaxValue READ getAbsDisAxisMaxValue WRITE updateAbsDisAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double ColDisAxisMinValue READ getColDisAxisMinValue WRITE updateColDisAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double ColDisAxisMaxValue READ getColDisAxisMaxValue WRITE updateColDisAxisMaxValue NOTIFY OnGraphSettingsChanged)

    Q_PROPERTY(int ReqAmpAxisMinValue READ getReqAmpAxisMinValue WRITE updateReqAmpAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double VelocityAxisMinValue READ getVelocityAxisMinValue WRITE updateVelocityAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int ReqAmpAxisMaxValue READ getReqAmpAxisMaxValue WRITE updateReqAmpAxisMaxValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double VelocityAxisMaxValue READ getVelocityAxisMaxValue WRITE updateVelocityAxisMaxValue NOTIFY OnGraphSettingsChanged)

    Q_PROPERTY(double TimeAxisMinValue READ getTimeAxisMinValue WRITE updateTimeAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double TimeAxisMaxValue READ getTimeAxisMaxValue WRITE updateTimeAxisMaxValue NOTIFY OnGraphSettingsChanged)

    Q_PROPERTY(int SamplingInterval READ getSamplingInterval WRITE updateSamplingInterval NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(int AutoSaveGraph READ getAutoSaveGraph WRITE updateAutoSaveGraph NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double AutoScaleYAxis READ getAutoScaleYAxis WRITE updateAutoScaleYAxis NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double AutoScaleTimeAxis READ getAutoScaleTimeAxis WRITE updateAutoScaleTimeAxis NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double TWHLineDisplay READ getTWHLineDisplay WRITE updateTWHLineDisplay NOTIFY OnGraphSettingsChanged)

private:

    int     m_FirstAxisValue;
    int     m_SecondAxisValue;

    int     m_AmpAxisMinValue;
    int     m_AmpAxisMaxValue;
    double  m_PowerAxisMinValue;
    double  m_PowerAxisMaxValue;
    int     m_FreqAxisMinValue;
    int     m_FreqAxisMaxValue;
    int     m_PhaseAxisMinValue;
    int     m_PhaseAxisMaxValue;
    int     m_CurrentAxisMinValue;
    int     m_CurrentAxisMaxValue;
    double  m_EnergyAxisMinValue;
    double  m_EnergyAxisMaxValue;
    double  m_ForceAxisMinValue;
    double  m_ForceAxisMaxValue;
    double  m_AbsDisAxisMinValue;
    double  m_AbsDisAxisMaxValue;
    double  m_ColDisAxisMinValue;
    double  m_ColDisAxisMaxValue;

    int     m_ReqAmpAxisMinValue;
    double  m_VelocityAxisMinValue;

    int     m_ReqAmpAxisMaxValue;
    double  m_VelocityAxisMaxValue;

    double  m_TimeAxisMinValue;
    double  m_TimeAxisMaxValue;

    int m_SamplingInterval;
    bool m_IsAutoSaveGraph;

    int     m_ActualAmpAxisMinValue;
    int     m_ActualAmpAxisMaxValue;
    double     m_ActualPowerAxisMinValue;
    double     m_ActualPowerAxisMaxValue;
    int     m_ActualFreqAxisMinValue;
    int     m_ActualFreqAxisMaxValue;
    int     m_ActualPhaseAxisMinValue;
    int     m_ActualPhaseAxisMaxValue;
    int     m_ActualCurrentAxisMinValue;
    int     m_ActualCurrentAxisMaxValue;
    double  m_ActualEnergyAxisMinValue;
    double  m_ActualEnergyAxisMaxValue;
    double  m_ActualForceAxisMinValue;
    double  m_ActualForceAxisMaxValue;
    double  m_ActualAbsDisAxisMinValue;
    double  m_ActualAbsDisAxisMaxValue;
    double  m_ActualColDisAxisMinValue;
    double  m_ActualColDisAxisMaxValue;

    double  m_ActualVelocityAxisMinValue;
    double  m_ActualVelocityAxisMaxValue;

    int     m_ActualReqAmpAxisMinValue;
    int     m_ActualReqAmpAxisMaxValue;

    double  m_ActualTimeAxisMinValue;
    double  m_ActualTimeAxisMaxValue;

public:

    explicit GraphSettings(QObject *parent = nullptr);
    QSettings settings;

    int getFirstAxisValue() const;
    void updateFirstAxisValuee(const int& FirstAxisValue);

    int getSecondAxisValue() const;
    void updateSecondAxisValue(const int& SecondAxisValue);

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

    double getForceAxisMinValue() const;
    void updateForceAxisMinValue(const double& ForceAxisMinValue);

    double getForceAxisMaxValue() const;
    void updateForceAxisMaxValue(const double& ForceAxisMaxValue);

    double getAbsDisAxisMinValue() const;
    void updateAbsDisAxisMinValue(const double& AbsDisAxisMinValue);

    double getAbsDisAxisMaxValue() const;
    void updateAbsDisAxisMaxValue(const double& AbsDisAxisMaxValue);

    double getColDisAxisMinValue() const;
    void updateColDisAxisMinValue(const double& ColDisAxisMinValue);

    double getColDisAxisMaxValue() const;
    void updateColDisAxisMaxValue(const double& ColDisAxisMaxValue);

    double getTimeAxisMinValue() const;
    void updateTimeAxisMinValue(const double& TimeAxisMinValue);

    double getTimeAxisMaxValue() const;
    void updateTimeAxisMaxValue(const double& TimeAxisMaxValue);

    int getSamplingInterval() const;
    void updateSamplingInterval(const int& SamplingInterval);

    bool getAutoSaveGraph() const;
    void updateAutoSaveGraph(const bool& AutoSaveGraph);

    bool getAutoScaleYAxis() const;
    void updateAutoScaleYAxis(const bool& AutoScaleYAxis);

    double getAutoScaleTimeAxis() const;
    void updateAutoScaleTimeAxis(const double& AutoScaleTimeAxis);

    bool getTWHLineDisplay() const;
    void updateTWHLineDisplay(const bool& TWHLineDisplay);

    double getVelocityAxisMinValue() const;
    void updateVelocityAxisMinValue(const double& VelocityMinValue);

    double getVelocityAxisMaxValue() const;
    void updateVelocityAxisMaxValue(const double& VelocityMaxValue);

    int getReqAmpAxisMinValue() const;
    void updateReqAmpAxisMinValue(const int& ReqAmpMinValue);

    int getReqAmpAxisMaxValue() const;
    void updateReqAmpAxisMaxValue(const int& ReqAmpMaxValue);

    Q_INVOKABLE int    getActualAmpAxisMinValue();
    Q_INVOKABLE int    getActualAmpAxisMaxValue();
    Q_INVOKABLE double getActualPowerAxisMinValue();
    Q_INVOKABLE double getActualPowerAxisMaxValue();
    Q_INVOKABLE int    getActualFreqAxisMinValue();
    Q_INVOKABLE int    getActualFreqAxisMaxValue();
    Q_INVOKABLE int    getActualPhaseAxisMinValue();
    Q_INVOKABLE int    getActualPhaseAxisMaxValue();
    Q_INVOKABLE int    getActualCurrentAxisMinValue();
    Q_INVOKABLE int    getActualCurrentAxisMaxValue();
    Q_INVOKABLE double getActualEnergyAxisMinValue();
    Q_INVOKABLE double getActualEnergyAxisMaxValue();
    Q_INVOKABLE double getActualForceAxisMinValue();
    Q_INVOKABLE double getActualForceAxisMaxValue();
    Q_INVOKABLE double getActualAbsDisAxisMinValue();
    Q_INVOKABLE double getActualAbsDisAxisMaxValue();
    Q_INVOKABLE double getActualColDisAxisMinValue();
    Q_INVOKABLE double getActualColDisAxisMaxValue();
    Q_INVOKABLE double getActualVelocityAxisMinValue();
    Q_INVOKABLE double getActualVelocityAxisMaxValue();
    Q_INVOKABLE int    getActualReqAmpAxisMaxValue();
    Q_INVOKABLE int    getActualReqAmpAxisMinValue();

    Q_INVOKABLE double getActualTimeAxisMinValue();
    Q_INVOKABLE double getActualTimeAxisMaxValue();

    WeldSignatureACE *m_WeldSignatureACE;
    std::deque<WeldSignatureACEStruct> m_RequestedWeldSignatureData;

signals:

    void OnGraphSettingsChanged();
    void graphSettingsChanged();
    void referenceGraphSettingsChanged();


public slots:

    void OnNoWeldSignatureSettingsUpdated(WeldSignatureACE *WeldSignatureSettings_Obj);
    void OnWeldSignatureSettingsUpdated(WeldSignatureACE *WeldSignatureSettings_Obj);
};

#endif // GRAPHSETTINGS_H

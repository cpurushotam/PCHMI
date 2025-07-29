/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    SeekGraphSettings.h file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/03/2024 - Initial version.
***************************************************************************/
#ifndef SEEKGRAPHSETTINGS_H
#define SEEKGRAPHSETTINGS_H
#include <QObject>
#include <QSettings>
#include "SeekSignature.h"


class SeekGraphSettings : public QObject
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

    Q_PROPERTY(double TimeAxisMinValue READ getTimeAxisMinValue WRITE updateTimeAxisMinValue NOTIFY OnGraphSettingsChanged)
    Q_PROPERTY(double TimeAxisMaxValue READ getTimeAxisMaxValue WRITE updateTimeAxisMaxValue NOTIFY OnGraphSettingsChanged)

private:

    int     m_FirstAxisValue;
    int     m_SecondAxisValue;

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

    double     m_TimeAxisMinValue;
    double     m_TimeAxisMaxValue;

public:

    explicit SeekGraphSettings(QObject *parent = nullptr);
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

    int getTimeAxisMinValue() const;
    void updateTimeAxisMinValue(const int& TimeAxisMinValue);

    double getTimeAxisMaxValue() const;
    void updateTimeAxisMaxValue(const double& TimeAxisMaxValue);

    SeekSignature *m_SeekSignature;
    std::deque<SeekSignatureStruct> m_RequestedSeekSignatureData;

signals:

    void OnGraphSettingsChanged();

public slots:

    void OnSeekSignatureSettingsUpdated(SeekSignature *SeekSignatureSettings_Obj);
};

#endif // SEEKGRAPHSETTINGS_H

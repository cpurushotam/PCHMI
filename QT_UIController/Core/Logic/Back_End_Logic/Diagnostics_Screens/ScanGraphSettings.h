/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanGraphSettings.h file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 03/04/2024 - Initial version.
***************************************************************************/
#ifndef SCANGRAPHSETTINGS_H
#define SCANGRAPHSETTINGS_H
#include <QObject>
#include <QSettings>
#include "HornScanSignature.h"


class ScanGraphSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int AmpAxisMinValue READ getAmpAxisMinValue WRITE updateAmpAxisMinValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int AmpAxisMaxValue READ getAmpAxisMaxValue WRITE updateAmpAxisMaxValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int FreqAxisMinValue READ getFreqAxisMinValue WRITE updateFreqAxisMinValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int FreqAxisMaxValue READ getFreqAxisMaxValue WRITE updateFreqAxisMaxValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMinValue READ getPhaseAxisMinValue WRITE updatePhaseAxisMinValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int PhaseAxisMaxValue READ getPhaseAxisMaxValue WRITE updatePhaseAxisMaxValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int CurrentAxisMinValue READ getCurrentAxisMinValue WRITE updateCurrentAxisMinValue NOTIFY OnScanGraphSettingsChanged)
    Q_PROPERTY(int CurrentAxisMaxValue READ getCurrentAxisMaxValue WRITE updateCurrentAxisMaxValue NOTIFY OnScanGraphSettingsChanged)

    Q_PROPERTY(bool AmplitudeAxisVisible READ getAmplitudeAxisVisible WRITE updateAmplitudeAxisVisible NOTIFY OnScanGraphSettingsChanged )
    Q_PROPERTY(bool CurrentAxisVisible READ getCurrentAxisVisible WRITE updateCurrentAxisVisible NOTIFY OnScanGraphSettingsChanged )
    Q_PROPERTY(bool PhaseAxisVisible READ getPhaseAxisVisible WRITE updatePhaseAxisVisible NOTIFY OnScanGraphSettingsChanged )

private:

    int     m_AmpAxisMinValue;
    int     m_AmpAxisMaxValue;
    int     m_FreqAxisMinValue;
    int     m_FreqAxisMaxValue;
    int     m_PhaseAxisMinValue;
    int     m_PhaseAxisMaxValue;
    int     m_CurrentAxisMinValue;
    int     m_CurrentAxisMaxValue;

    bool    m_AmplitudeAxisVisible = true;
    bool    m_CurrentAxisVisible = true;
    bool    m_PhaseAxisVisible = true;

public:

    explicit ScanGraphSettings(QObject *parent = nullptr);
    QSettings settings;

    int getAmpAxisMinValue() const;
    void updateAmpAxisMinValue(const int& AmpAxisMinValue);

    int getAmpAxisMaxValue() const;
    void updateAmpAxisMaxValue(const int& AmpAxisMaxValue);

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

    bool getAmplitudeAxisVisible() const;
    void updateAmplitudeAxisVisible(const bool& AmplitudeAxisVisible);

    bool getCurrentAxisVisible() const;
    void updateCurrentAxisVisible(const bool& CurrentAxisVisible);

    bool getPhaseAxisVisible() const;
    void updatePhaseAxisVisible(const bool& PhaseAxisVisible);

    HornScanSignature *m_ScanSignature;
    std::deque<HornScanSignatureStruct> m_RequestedScanSignatureData;

signals:

    void OnScanGraphSettingsChanged();

public slots:

    void OnScanSignatureSettingsUpdated(HornScanSignature *ScanSignatureSettings_Obj);
};

#endif // SCANGRAPHSETTINGS_H

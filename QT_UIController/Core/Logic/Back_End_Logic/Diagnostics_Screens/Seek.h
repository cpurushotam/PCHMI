/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes horn seek screen qml variables declarations.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/
#ifndef SEEK_H
#define SEEK_H

#include <QObject>
#include "UpdateScreens.h"
#include "SeekSignature.h"

class Seek : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT

    Q_PROPERTY(QString SeekDateAndTime        READ getSeekDateAndTime            NOTIFY seekDateAndTimeChanged)
    Q_PROPERTY(int SeekEndFrequency           READ getSeekEndFrequency           NOTIFY seekEndFrequencyChanged)

    Q_PROPERTY(int SeekFreqLimitHigh          READ getSeekFreqLimitHigh          WRITE updateSeekFreqLimitHigh          NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekFreqLimitLow           READ getSeekFreqLimitLow           WRITE updateSeekFreqLimitLow           NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekFreqOffset             READ getSeekFreqOffset             WRITE updateSeekFreqOffset             NOTIFY seekDataChanged)
    Q_PROPERTY(bool SeekMemClear              READ getSeekMemClear               WRITE updateSeekMemClear               NOTIFY seekDataChanged)
    Q_PROPERTY(float SeekTime                   READ getSeekTime                   WRITE updateSeekTime                   NOTIFY seekDataChanged)
    Q_PROPERTY(float SeekAmplitudeRampTime      READ getSeekAmplitudeRampTime      WRITE updateSeekAmplitudeRampTime      NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekAmplitude              READ getSeekAmplitude              WRITE updateSeekAmplitude              NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekAmpProportionalGain    READ getSeekAmpProportionalGain    WRITE updateSeekAmpProportionalGain    NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekAmpIntegralGain        READ getSeekAmpIntegralGain        WRITE updateSeekAmpIntegralGain        NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekAmpDerivativeGain      READ getSeekAmpDerivativeGain      WRITE updateSeekAmpDerivativeGain      NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekPhaseProportionalGain  READ getSeekPhaseProportionalGain  WRITE updateSeekPhaseProportionalGain  NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekPhaseIntegralGain      READ getSeekPhaseIntegralGain      WRITE updateSeekPhaseIntegralGain      NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekPhaseDerivativeGain    READ getSeekPhaseDerivativeGain    WRITE updateSeekPhaseDerivativeGain    NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekBlindTimeSeek          READ getSeekBlindTimeSeek          WRITE updateSeekBlindTimeSeek          NOTIFY seekDataChanged)
    Q_PROPERTY(int SeekPhaseloopCF            READ getSeekPhaseloopCF            WRITE updateSeekPhaseloopCF            NOTIFY seekDataChanged)


private:

    /*List of private varibles used by methods under RecipeLabData class*/

    QString m_SeekDateAndTime;
    int m_SeekEndFrequency;

    int m_SeekFreqLimitHigh;
    int m_SeekFreqLimitLow;
    int m_SeekFreqOffset;
    bool m_SeekMemClear;
    float m_SeekTime;
    float m_SeekAmplitudeRampTime;
    int m_SeekAmplitude;
    int m_SeekAmpProportionalGain;
    int m_SeekAmpIntegralGain;
    int m_SeekAmpDerivativeGain;
    int m_SeekPhaseProportionalGain;
    int m_SeekPhaseIntegralGain;
    int m_SeekPhaseDerivativeGain;
    int m_SeekBlindTimeSeek;
    int m_SeekPhaseloopCF;

public:

    explicit Seek(QObject *parent = nullptr);

    /*List of get and set functions to update qml variables*/
    Q_INVOKABLE void seekRun();

    QString getSeekDateAndTime() const;

    int getSeekEndFrequency() const;

    int getSeekFreqLimitHigh() const;
    void updateSeekFreqLimitHigh(const int& SeekFreqLimitHigh);

    int getSeekFreqLimitLow() const;
    void updateSeekFreqLimitLow(const int& SeekFreqLimitLow);

    int getSeekFreqOffset() const;
    void updateSeekFreqOffset(const int& SeekFreqOffset);

    bool getSeekMemClear() const;
    void updateSeekMemClear(const bool& SeekMemClear);

    float getSeekTime() const;
    void updateSeekTime(const float& SeekTime);

    float getSeekAmplitudeRampTime() const;
    void updateSeekAmplitudeRampTime(const float& SeekAmplitudeRampTime);

    int getSeekAmplitude() const;
    void updateSeekAmplitude(const int& SeekAmplitude);

    int getSeekAmpProportionalGain() const;
    void updateSeekAmpProportionalGain(const int& SeekAmpProportionalGain);

    int getSeekAmpIntegralGain() const;
    void updateSeekAmpIntegralGain(const int& SeekAmpIntegralGain);

    int getSeekAmpDerivativeGain() const;
    void updateSeekAmpDerivativeGain(const int& SeekAmpDerivativeGain);

    int getSeekPhaseProportionalGain() const;
    void updateSeekPhaseProportionalGain(const int& SeekPhaseProportionalGain);

    int getSeekPhaseIntegralGain() const;
    void updateSeekPhaseIntegralGain(const int& SeekPhaseIntegralGain);

    int getSeekPhaseDerivativeGain() const;
    void updateSeekPhaseDerivativeGain(const int& SeekPhaseDerivativeGain);

    int getSeekBlindTimeSeek() const;
    void updateSeekBlindTimeSeek(const int& SeekBlindTimeSeek);

    int getSeekPhaseloopCF() const;
    void updateSeekPhaseloopCF(const int& SeekPhaseloopCF);

    enum SEEK_PARAMETERS_ENUMS
    {
        NONE_IDX = -1,
        SEEK_FREQENCY_LIMIT_HIGH,
        SEEK_FREQENCY_LIMIT_LOW,
        SEEK_FREQENCY_OFFSET,
        SEEK_MEM_CLEAR,
        SEEK_TIME_VAL,
        SEEK_AMP_RAMP_TIME,
        SEEK_AMP,
        SEEK_AMP_PROPOTIONAL_GAIN,
        SEEK_AMP_INTEGRAL_GAIN,
        SEEK_AMP_DERIVATIVE_GAIN,
        SEEK_PHASE_PROPOTIONAL_GAIN,
        SEEK_PHASE_INT_GAIN,
        SEEK_PHASE_DERI_GAIN,
        SEEK_BLIND_TIME_SEEK,
        SEEK_PHASE_LOOP_CF
    };

    Q_INVOKABLE void isScreenReNavigated(bool Value);
    Q_INVOKABLE QString getMinSeekParametersValue(int Type);
    Q_INVOKABLE QString getMaxSeekParametersValue(int Type);
    Q_INVOKABLE void onSavedPressed();
    Q_INVOKABLE void onResetToDefaultPressed();
    Q_INVOKABLE void onSeekRecipeScreenReNavigated();

    /*List of geter API's for graph's subscreens*/
    SeekSignature *getSeekSignature();

    int m_ActiveWelderId = -1;
    bool m_IsScreenReNavigated = false;

    SeekResult *m_SeekResult;
    SeekSignature *m_SeekSignature;
    SeekRecipe *m_SeekRecipe;

    SeekResultstruct m_SeekResultData;
    SeekRecipestruct m_SeekRecipeData, m_SeekRecipeDataLocal;

    bool areRecipeValuesEqual(const SeekRecipestruct &SeekRecipestruct_1, const SeekRecipestruct &SeekRecipestruct_2);

    /*Signals used to notify qml screen*/
signals:

    void seekDateAndTimeChanged();
    void seekEndFrequencyChanged();
    void seekDataChanged();
    void areSeekRecipeValuesEqual(bool Value);
    void initiateSeekGraphSignatureDisplay(bool Value);

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnSeekDataUpdated(SeekResult *DiagnosticsSeekResultScreen_Obj, SeekSignature *DiagnosticsSeekSignatureScreen_Obj, SeekRecipe *DiagnosticsSeekRecipeScreen_Obj,
                           int WelderId);
};

#endif // SEEK_H

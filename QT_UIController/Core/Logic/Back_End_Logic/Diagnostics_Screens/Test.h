/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes horn test screen qml variables declarations.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/
#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "UpdateScreens.h"
#include "TestResult.h"
#include "TestSignature.h"
#include "TestRecipe.h"

class Test : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT
    Q_PROPERTY(int TestStatus                 READ getTestStatus                       NOTIFY testDataChanged)
    Q_PROPERTY(int TestFrequency              READ getTestFrequency                    NOTIFY testFrequencyChanged)
    Q_PROPERTY(int TestStoredFrequency        READ getTestStoredFrequency               NOTIFY testStoredFrequencyChanged)
    Q_PROPERTY(float TestPower                READ getTestPower                        NOTIFY testPowerChanged)

    Q_PROPERTY(int TestFreqLimitHigh          READ getTestFreqLimitHigh                WRITE updateTestFreqLimitHigh                NOTIFY testDataChanged)
    Q_PROPERTY(int TestFreqLimitLow           READ getTestFreqLimitLow                 WRITE updateTestFreqLimitLow                 NOTIFY testDataChanged)
    Q_PROPERTY(int TestFreqOffset             READ getTestFreqOffset                   WRITE updateTestFreqOffset                   NOTIFY testDataChanged)
    Q_PROPERTY(bool TestMemClear              READ getTestMemClear                     WRITE updateTestMemClear                     NOTIFY testDataChanged)
    Q_PROPERTY(float TestAmplitudeRampTime      READ getTestAmplitudeRampTime            WRITE updateTestAmplitudeRampTime            NOTIFY testDataChanged)
    Q_PROPERTY(int TestAmplitude              READ getTestAmplitude                    WRITE updateTestAmplitude                    NOTIFY testDataChanged)
    Q_PROPERTY(int TestAmpProportionalGain    READ getTestAmpProportionalGain          WRITE updateTestAmpProportionalGain          NOTIFY testDataChanged)
    Q_PROPERTY(int TestAmpIntegralGain        READ getTestAmpIntegralGain              WRITE updateTestAmpIntegralGain              NOTIFY testDataChanged)
    Q_PROPERTY(int TestAmpDerivativeGain      READ getTestAmpDerivativeGain            WRITE updateTestAmpDerivativeGain            NOTIFY testDataChanged)
    Q_PROPERTY(int TestPhaseProportionalGain  READ getTestPhaseProportionalGain        WRITE updateTestPhaseProportionalGain        NOTIFY testDataChanged)
    Q_PROPERTY(int TestPhaseIntegralGain      READ getTestPhaseIntegralGain            WRITE updateTestPhaseIntegralGain            NOTIFY testDataChanged)
    Q_PROPERTY(int TestPhaseDerivativeGain    READ getTestPhaseDerivativeGain          WRITE updateTestPhaseDerivativeGain          NOTIFY testDataChanged)
    Q_PROPERTY(int TestPhaseloopCF            READ getTestPhaseloopCF                  WRITE updateTestPhaseloopCF                  NOTIFY testDataChanged)

    Q_PROPERTY(bool AmpUpdateFlagStatus       READ getAmpUpdateFlagStatus              WRITE updateAmpUpdateFlagStatus              NOTIFY testDataChanged)
    Q_PROPERTY(int TestAmplitude2             READ getTestAmplitude2                   WRITE updateTestAmplitude2                   NOTIFY testDataChanged)

private:

    /*List of private varibles used by methods under RecipeLabData class*/
    int m_TestStatus;
    int m_TestFrequency;
    int m_TestStoredFrequency;
    float m_TestPower;

    int m_TestFreqLimitHigh;
    int m_TestFreqLimitLow;
    int m_TestFreqOffset;
    bool m_TestMemClear;
    float m_TestAmplitudeRampTime;
    int m_TestAmplitude;
    int m_TestAmpProportionalGain;
    int m_TestAmpIntegralGain;
    int m_TestAmpDerivativeGain;
    int m_TestPhaseProportionalGain;
    int m_TestPhaseIntegralGain;
    int m_TestPhaseDerivativeGain;
    int m_TestPhaseloopCF;

    bool ampUpdateFlag = false;
    int m_TestAmplitude2;

public:

    explicit Test(QObject *parent = nullptr);


    /*List of get and set functions to update qml variables*/
    Q_INVOKABLE void startTest();
    Q_INVOKABLE void abortTest();
    Q_INVOKABLE void invokeUpdateFlag();

    int getTestStatus() const;

    int getTestFrequency() ;
    Q_INVOKABLE QString getTestFrequencyMax();
    Q_INVOKABLE QString getTestFrequencyMin();

    int getTestStoredFrequency();
    Q_INVOKABLE QString getTestStoredFrequencyMax();
    Q_INVOKABLE QString getTestStoredFrequencyMin();

    float getTestPower() const;
    Q_INVOKABLE float getTestPowerMax();

    int getTestFreqLimitHigh() const;
    void updateTestFreqLimitHigh(const int& TestFreqLimitHigh);

    int getTestFreqLimitLow() const;
    void updateTestFreqLimitLow(const int& TestFreqLimitLow);

    int getTestFreqOffset() const;
    void updateTestFreqOffset(const int& TestFreqOffset);

    bool getTestMemClear() const;
    void updateTestMemClear(const bool& TestMemClear);

    float getTestAmplitudeRampTime() const;
    void updateTestAmplitudeRampTime(const float& TestAmplitudeRampTime);

    int getTestAmplitude() const;
    void updateTestAmplitude(const int& TestAmplitude);

    int getTestAmpProportionalGain() const;
    void updateTestAmpProportionalGain(const int& TestAmpProportionalGain);

    int getTestAmpIntegralGain() const;
    void updateTestAmpIntegralGain(const int& TestAmpIntegralGain);

    int getTestAmpDerivativeGain() const;
    void updateTestAmpDerivativeGain(const int& TestAmpDerivativeGain);

    int getTestPhaseProportionalGain() const;
    void updateTestPhaseProportionalGain(const int& TestPhaseProportionalGain);

    int getTestPhaseIntegralGain() const;
    void updateTestPhaseIntegralGain(const int& TestPhaseIntegralGain);

    int getTestPhaseDerivativeGain() const;
    void updateTestPhaseDerivativeGain(const int& TestPhaseDerivativeGain);

    int getTestPhaseloopCF() const;
    void updateTestPhaseloopCF(const int& TestPhaseloopCF);

    bool getAmpUpdateFlagStatus() const;
    void updateAmpUpdateFlagStatus(const bool& AmpUpdateFlagStatus);

    int getTestAmplitude2() const;
    void updateTestAmplitude2(const int& TestAmplitude2);

    enum TEST_PARAMETERS_ENUMS
    {
        NONE_IDX = -1,
        TEST_FREQENCY_LIMIT_HIGH,
        TEST_FREQENCY_LIMIT_LOW,
        TEST_FREQENCY_OFFSET,
        TEST_MEM_CLEAR,
        TEST_AMP_RAMP_TIME,
        TEST_AMP,
        TEST_AMP_PROPOTIONAL_GAIN,
        TEST_AMP_INTEGRAL_GAIN,
        TEST_AMP_DERIVATIVE_GAIN,
        TEST_PHASE_PROPOTIONAL_GAIN,
        TEST_PHASE_INT_GAIN,
        TEST_PHASE_DERI_GAIN,
        TEST_PHASE_LOOP_CF
    };

    Q_INVOKABLE void isScreenReNavigated(bool Value);
    Q_INVOKABLE QString getMinTestParametersValue(int Type);
    Q_INVOKABLE QString getMaxTestParametersValue(int Type);
    Q_INVOKABLE void onSavedPressed();
    Q_INVOKABLE void onResetToDefaultPressed();
    Q_INVOKABLE void onTestRecipeScreenReNavigated();

    /*List of geter API's for graph's subscreens*/
    TestSignature *getTestSignature();

     int m_ActiveWelderId = -1;
     bool m_IsScreenReNavigated = false;

     TestResult *m_TestResult;
     TestSignature *m_TestSignature;
     TestRecipe *m_TestRecipe;

     TestResultStruct m_TestResultData;
     TestRecipestruct m_TestRecipeData, m_TestRecipeDataLocal;
     TestProgressStruct m_TestProgressData;

     bool areRecipeValuesEqual(const TestRecipestruct &TestRecipestruct_1, const TestRecipestruct &TestRecipestruct_2);

    /*Signals used to notify qml screen*/
signals:

     void testFrequencyChanged();
     void testStoredFrequencyChanged();
     void testPowerChanged();
     void testDataChanged();
     void areTestRecipeValuesEqual(bool Value);
     void initiateTestGraphSignatureDisplay(bool Value);

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnTestDataUpdated(TestResult *DiagnosticsTestResultScreen_Obj, TestSignature *DiagnosticsTestSignatureScreen_Obj, TestRecipe *DiagnosticsTestRecipeScreen_Obj,
                           int WelderId);
};

#endif // TEST_H

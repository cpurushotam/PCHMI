/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file handles the horn test result parameters.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/
#include "Test.h"
#include "PowerLevelSysFrequencySupport.h"
/**************************************************************************//**
*
* \brief  - Diagnostics Test Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
Test::Test(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::TestScreenUpdated, this, &Test::OnTestDataUpdated);
    m_TestRecipeDataLocal = m_TestRecipeData;
}

/**************************************************************************//**
*
* \brief   - Below function commands to start test.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::startTest()
{
    m_TestResult->setButtonStatusFromHMI(START_TEST_PROCESS);
}

/**************************************************************************//**
*
* \brief   - Below function commands to abort test.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::abortTest()
{
    m_TestResult->setButtonStatusFromHMI(ABORT_TEST_PROCESS);
}

/**************************************************************************//**
*
* \brief   - Below function updates counter value.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::invokeUpdateFlag()
{
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the test status.
*
* \param   - None.
*
* \return  - m_TestStatus : The test status.
******************************************************************************/
int Test::getTestStatus() const
{
    return m_TestStatus;
}

/**************************************************************************//**
*
* \brief   - Below function returns the test frequency.
*
* \param   - None.
*
* \return  - m_TestFrequency : The test frequency.
******************************************************************************/
int Test::getTestFrequency()
{
    if(m_TestFrequency == 0)
    {
        std::string  TestFrequencyStr =   m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_LOW);
        m_TestFrequency = std::stoi(TestFrequencyStr);
    }
    return m_TestFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function returns the test frequency maximum value.
*
* \param   - None.
*
* \return  - m_TestFrequencyMax : The test frequency maximum value.
******************************************************************************/
QString Test::getTestFrequencyMax()
{
    std::string m_TestFrequencyMax;
    m_TestFrequencyMax = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_LIMIT_HIGH);

    return QString::fromLocal8Bit(m_TestFrequencyMax.c_str());
}
/**************************************************************************//**
*
* \brief   - Below function returns the test frequency minimum value.
*
* \param   - None.
*
* \return  - m_TestFrequencyMin : The test frequency minimum value.
******************************************************************************/
QString Test::getTestFrequencyMin()
{
    std::string m_TestFrequencyMin;
    m_TestFrequencyMin = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_LOW);
    return QString::fromLocal8Bit(m_TestFrequencyMin.c_str());
}
/**************************************************************************//**
*
* \brief   - Below function returns the stored frequency.
*
* \param   - None.
*
* \return  - m_TestStoredFrequency : The stored frequency.
******************************************************************************/
int Test::getTestStoredFrequency()
{
    if(m_TestStoredFrequency == 0)
    {
        std::string  StortedTestFrequencyStr =   m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_LOW);
        m_TestStoredFrequency = std::stoi(StortedTestFrequencyStr);
    }
    return m_TestStoredFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function returns the test stored frequency maximum value.
*
* \param   - None.
*
* \return  - m_TestStoredFrequencyMax : The test stored frequency maximum value.
******************************************************************************/
QString Test::getTestStoredFrequencyMax()
{
    std::string m_TestStoredFrequencyMax;
    m_TestStoredFrequencyMax = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_LIMIT_HIGH);
    return QString::fromLocal8Bit(m_TestStoredFrequencyMax.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function returns the test stored frequency minimum value.
*
* \param   - None.
*
* \return  - m_TestStoredFrequencyMin : The test stored frequency minimum value.
******************************************************************************/
QString Test::getTestStoredFrequencyMin()
{
    std::string m_TestStoredFrequencyMin;
    m_TestStoredFrequencyMin = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_LOW);
    return QString::fromLocal8Bit(m_TestStoredFrequencyMin.c_str());
}
/**************************************************************************//**
*
* \brief   - Below function returns the test power.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : The test power.
******************************************************************************/
float Test::getTestPower() const
{
    return m_TestPower;
}

/**************************************************************************//**
*
* \brief   - Below function returns the test power maximum value.
*
* \param   - None.
*
* \return  - m_TestPowerMax : The test power maximum value.
******************************************************************************/
float Test::getTestPowerMax()
{
    float m_TestPowerMax;
    m_TestPowerMax = PowerLevelSysFrequencySupport::GetMaxPowerFromJSON();

    return m_TestPowerMax;
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency limit high.
*
* \param   - None.
*
* \return  - m_TestFreqLimitHigh : The frequency limit high.
******************************************************************************/
int Test::getTestFreqLimitHigh() const
{
    return m_TestFreqLimitHigh;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency limit high.
*
* \param   - TestFreqLimitHigh : The frequency limit high.
*
* \return  - None.
******************************************************************************/
void Test::updateTestFreqLimitHigh(const int &TestFreqLimitHigh)
{
    m_TestFreqLimitHigh = TestFreqLimitHigh;
    m_TestRecipeDataLocal.TestFreqLimitHigh = m_TestFreqLimitHigh;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency limit low.
*
* \param   - None.
*
* \return  - m_TestFreqLimitLow : The frequency limit low.
******************************************************************************/
int Test::getTestFreqLimitLow() const
{
    return m_TestFreqLimitLow;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency limit low.
*
* \param   - TestFreqLimitLow : The frequency limit low.
*
* \return  - None.
******************************************************************************/
void Test::updateTestFreqLimitLow(const int &TestFreqLimitLow)
{
    m_TestFreqLimitLow = TestFreqLimitLow;
    m_TestRecipeDataLocal.TestFreqLimitLow = m_TestFreqLimitLow;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency offset.
*
* \param   - None.
*
* \return  - m_TestFreqOffset : The frequency offset.
******************************************************************************/
int Test::getTestFreqOffset() const
{
    return m_TestFreqOffset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency offset.
*
* \param   - TestFreqOffset : The frequency offset.
*
* \return  - None.
******************************************************************************/
void Test::updateTestFreqOffset(const int &TestFreqOffset)
{
    m_TestFreqOffset = TestFreqOffset;
    m_TestRecipeDataLocal.TestFreqOffset = m_TestFreqOffset;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return the flag which states the memory offset shall be 0 or not.
*
* \param   - None.
*
* \return  - m_TestMemClear : The offset status.
******************************************************************************/
bool Test::getTestMemClear() const
{
    return m_TestMemClear;
}

/**************************************************************************//**
*
* \brief   - Below function updates the flag which states the memory offset shall be 0 or not.
*
* \param   - TestMemClear : The offset status.
*
* \return  - None.
******************************************************************************/
void Test::updateTestMemClear(const bool &TestMemClear)
{
    m_TestMemClear = TestMemClear;
    m_TestRecipeDataLocal.ClearMemoryBeforeTest = m_TestMemClear;
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude ramp time.
*
* \param   - None.
*
* \return  - m_TestAmplitudeRampTime : The amplitude ramp time.
******************************************************************************/
float Test::getTestAmplitudeRampTime() const
{
    return m_TestAmplitudeRampTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude ramp time.
*
* \param   - TestAmplitudeRampTime : The amplitude ramp time.
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmplitudeRampTime(const float &TestAmplitudeRampTime)
{
    m_TestAmplitudeRampTime = TestAmplitudeRampTime;
    m_TestRecipeDataLocal.TestAmplitudeRampTime = m_TestAmplitudeRampTime;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude value.
*
* \param   - None.
*
* \return  - m_TestAmplitude : The amplitude value.
******************************************************************************/
int Test::getTestAmplitude() const
{
    return m_TestAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude value.
*
* \param   - TestAmplitude : The amplitude value..
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmplitude(const int &TestAmplitude)
{
    m_TestAmplitude = TestAmplitude;

    m_TestRecipeDataLocal.TestAmplitude = m_TestAmplitude;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude propotional gain.
*
* \param   - None.
*
* \return  - m_TestAmpProportionalGain : The amplitude propotional gain.
******************************************************************************/
int Test::getTestAmpProportionalGain() const
{
    return m_TestAmpProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude propotional gain.
*
* \param   - TestAmpProportionalGain : The amplitude propotional gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmpProportionalGain(const int &TestAmpProportionalGain)
{
    m_TestAmpProportionalGain = TestAmpProportionalGain;
    m_TestRecipeDataLocal.TestAmpProportionalGain = m_TestAmpProportionalGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude integral gain.
*
* \param   - None.
*
* \return  - m_TestAmpIntegralGain : The amplitude integral gain.
******************************************************************************/
int Test::getTestAmpIntegralGain() const
{
    return m_TestAmpIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude integral gain.
*
* \param   - TestAmpIntegralGain : The amplitude integral gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmpIntegralGain(const int &TestAmpIntegralGain)
{
    m_TestAmpIntegralGain = TestAmpIntegralGain;
    m_TestRecipeDataLocal.TestAmpIntegralGain = m_TestAmpIntegralGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude derivative gain.
*
* \param   - None.
*
* \return  - m_TestAmpDerivativeGain : The amplitude derivative gain.
******************************************************************************/
int Test::getTestAmpDerivativeGain() const
{
    return m_TestAmpDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude derivative gain.
*
* \param   - TestAmpDerivativeGain : The amplitude derivative gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmpDerivativeGain(const int &TestAmpDerivativeGain)
{
    m_TestAmpDerivativeGain = TestAmpDerivativeGain;
    m_TestRecipeDataLocal.TestAmpDerivativeGain = m_TestAmpDerivativeGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase propotional gain.
*
* \param   - None.
*
* \return  - m_TestPhaseProportionalGain : The phase propotional gain.
******************************************************************************/
int Test::getTestPhaseProportionalGain() const
{
    return m_TestPhaseProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase propotional gain.
*
* \param   - TestPhaseProportionalGain : The phase propotional gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestPhaseProportionalGain(const int &TestPhaseProportionalGain)
{
    m_TestPhaseProportionalGain = TestPhaseProportionalGain;
    m_TestRecipeDataLocal.TestPhaseProportionalGain = m_TestPhaseProportionalGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase integral gain.
*
* \param   - None.
*
* \return  - m_TestPhaseIntegralGain : The phase integral gain.
******************************************************************************/
int Test::getTestPhaseIntegralGain() const
{
    return m_TestPhaseIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase integral gain.
*
* \param   - TestPhaseIntegralGain : The phase integral gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestPhaseIntegralGain(const int &TestPhaseIntegralGain)
{
    m_TestPhaseIntegralGain = TestPhaseIntegralGain;
    m_TestRecipeDataLocal.TestPhaseIntegralGain = m_TestPhaseIntegralGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase integral gain.
*
* \param   - None.
*
* \return  - m_TestPhaseDerivativeGain : The phase integral gain.
******************************************************************************/
int Test::getTestPhaseDerivativeGain() const
{
    return m_TestPhaseDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase integral gain.
*
* \param   - TestPhaseDerivativeGain : The phase integral gain.
*
* \return  - None.
******************************************************************************/
void Test::updateTestPhaseDerivativeGain(const int &TestPhaseDerivativeGain)
{
    m_TestPhaseDerivativeGain = TestPhaseDerivativeGain;
    m_TestRecipeDataLocal.TestPhaseDerivativeGain = m_TestPhaseDerivativeGain;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase loop value.
*
* \param   - None.
*
* \return  - m_TestPhaseloopCF : The phase loop value.
******************************************************************************/
int Test::getTestPhaseloopCF() const
{
    return m_TestPhaseloopCF;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase loop value.
*
* \param   - TestPhaseloopCF : The phase loop value.
*
* \return  - None.
******************************************************************************/
void Test::updateTestPhaseloopCF(const int &TestPhaseloopCF)
{
    m_TestPhaseloopCF = TestPhaseloopCF;
    m_TestRecipeDataLocal.TestPhaseloopCF = m_TestPhaseloopCF;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function updates the status of amplitude update flag.
*
* \param   - None.
*
* \return  - ampUpdateFlag : The amplitude update flag status.
******************************************************************************/
bool Test::getAmpUpdateFlagStatus() const
{
    return ampUpdateFlag;
}

/**************************************************************************//**
*
* \brief   - Below function updates the status of amplitude update flag.
*
* \param   - AmpUpdateFlagStatus : The amplitude update flag status.
*
* \return  - None.
******************************************************************************/
void Test::updateAmpUpdateFlagStatus(const bool &AmpUpdateFlagStatus)
{
    ampUpdateFlag = AmpUpdateFlagStatus;
    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude value.
*
* \param   - None.
*
* \return  - m_TestAmplitude2 : The amplitude value.
******************************************************************************/
int Test::getTestAmplitude2() const
{
    return m_TestAmplitude2;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude value.
*
* \param   - TestAmplitude2 : The amplitude value..
*
* \return  - None.
******************************************************************************/
void Test::updateTestAmplitude2(const int &TestAmplitude2)
{
    m_TestAmplitude2 = TestAmplitude2;

    m_TestRecipeDataLocal.TestAmplitude = m_TestAmplitude2;
    m_TestRecipe->SetTestRecipeData(m_TestRecipeDataLocal);

    emit testDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void Test::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}
/**************************************************************************//**
*
* \brief   - Below function returns min parameter values.
*
* \param   - Type : The type for which value need to fetch.
*
* \return  - None.
******************************************************************************/
QString Test::getMinTestParametersValue(int Type)
{
    std::string retVal;

    switch (Type)
    {
    case TEST_FREQENCY_LIMIT_HIGH :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_HIGH);
        break;

    case TEST_FREQENCY_LIMIT_LOW :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_LOW);
        break;

    case TEST_FREQENCY_OFFSET :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_OFFSET);
        break;

    case TEST_MEM_CLEAR :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(CLEAR_MEMORY_BEFORE_TEST);
        break;

    case TEST_AMP_RAMP_TIME :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_AMPLITUDE_RAMP_TIME);
        break;

    case TEST_AMP :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_AMPLITUDE);
        break;

    case TEST_AMP_PROPOTIONAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_AMPLITUDE_PROPORTIONAL_GAIN);
        break;

    case TEST_AMP_INTEGRAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_AMPLITUDE_INTEGRAL_GAIN);
        break;

    case TEST_AMP_DERIVATIVE_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_AMPLITUDE_DERIVATIVE_GAIN);
        break;

    case TEST_PHASE_PROPOTIONAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_PHASE_PROPORTIONAL_GAIN);
        break;

    case TEST_PHASE_INT_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_PHASE_INTEGRAL_GAIN);
        break;

    case TEST_PHASE_DERI_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_PHASE_DERIVATIVE_GAIN);
        break;

    case TEST_PHASE_LOOP_CF :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_PHASE_LOOPCF);
        break;

    default :
        retVal = m_TestRecipe->GetTestRecipeParamMinValue(TEST_FREQ_LIMIT_HIGH);
        break;
    }

    return QString::fromLocal8Bit(retVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function returns max parameter values.
*
* \param   - Type : The type for which value need to fetch.
*
* \return  - None.
******************************************************************************/
QString Test::getMaxTestParametersValue(int Type)
{
    std::string retVal;

    switch (Type)
    {
    case TEST_FREQENCY_LIMIT_HIGH :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_LIMIT_HIGH);
        break;

    case TEST_FREQENCY_LIMIT_LOW :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_LIMIT_LOW);
        break;

    case TEST_FREQENCY_OFFSET :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_OFFSET);
        break;

    case TEST_MEM_CLEAR :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(CLEAR_MEMORY_BEFORE_TEST);
        break;

    case TEST_AMP_RAMP_TIME :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_AMPLITUDE_RAMP_TIME);
        break;

    case TEST_AMP :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_AMPLITUDE);
        break;

    case TEST_AMP_PROPOTIONAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_AMPLITUDE_PROPORTIONAL_GAIN);
        break;

    case TEST_AMP_INTEGRAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_AMPLITUDE_INTEGRAL_GAIN);
        break;

    case TEST_AMP_DERIVATIVE_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_AMPLITUDE_DERIVATIVE_GAIN);
        break;

    case TEST_PHASE_PROPOTIONAL_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_PHASE_PROPORTIONAL_GAIN);
        break;

    case TEST_PHASE_INT_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_PHASE_INTEGRAL_GAIN);
        break;

    case TEST_PHASE_DERI_GAIN :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_PHASE_DERIVATIVE_GAIN);
        break;

    case TEST_PHASE_LOOP_CF :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_PHASE_LOOPCF);
        break;

    default :
        retVal = m_TestRecipe->GetTestRecipeParamMaxValue(TEST_FREQ_LIMIT_HIGH);
        break;
    }

    return QString::fromLocal8Bit(retVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of onSavedPressed is to save the Test recipedata.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::onSavedPressed()
{
    /*Below conditional statement shall be replaced with availabity of Branson Service Key*/
    if(true)
    {
        m_TestRecipeDataLocal.TestAmpProportionalGain = m_TestRecipeData.TestAmpProportionalGain;
        m_TestRecipeDataLocal.TestAmpIntegralGain = m_TestRecipeData.TestAmpIntegralGain;
        m_TestRecipeDataLocal.TestAmpDerivativeGain = m_TestRecipeData.TestAmpDerivativeGain;
        m_TestRecipeDataLocal.TestPhaseProportionalGain = m_TestRecipeData.TestPhaseProportionalGain;
        m_TestRecipeDataLocal.TestPhaseIntegralGain = m_TestRecipeData.TestPhaseIntegralGain;
        m_TestRecipeDataLocal.TestPhaseDerivativeGain = m_TestRecipeData.TestPhaseDerivativeGain;
        m_TestRecipeDataLocal.TestPhaseloopCF = m_TestRecipeData.TestPhaseloopCF;
    }

    m_TestRecipe->SetTestRecipeData(m_TestRecipeDataLocal);
}

/**************************************************************************//**
*
* \brief   - Role of onResetToDefaultPressed is to restore default test
*            recipe settings.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::onResetToDefaultPressed()
{
    m_TestRecipe->InitiateTestRecipeResetToDefaultRequest();
}

/**************************************************************************//**
*
* \brief   - Role of onTestRecipeScreenReNavigated is to make sure updated
*            recipe data available.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Test::onTestRecipeScreenReNavigated()
{
    m_TestRecipe->SetIsTestRecipeUpdated(true);
}

/**************************************************************************//**
*
* \brief   - Role of the getTestSignature is to return test signature
*            object accessed by test graph screen.
*
* \param   - None.
*
* \return  - m_TestSignature : Test signature object pointer.
******************************************************************************/
TestSignature *Test::getTestSignature()
{
    return m_TestSignature;
}

/**************************************************************************//**
*
* \brief   - Returns the info whether recipe structures are equal are not.
*
* \param   - TestRecipestruct : The recipe structure which is being compare.
*
* \return  - The info whether recipe structures are equal are not.
******************************************************************************/
bool Test::areRecipeValuesEqual(const TestRecipestruct &TestRecipestruct_1, const TestRecipestruct &TestRecipestruct_2)
{
    return std::memcmp(&TestRecipestruct_1, &TestRecipestruct_2, sizeof(TestRecipestruct)) == 0;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnTestDataUpdated to update the horn Test result data.
*
* \param   - DiagnosticsTestResultScreen_Obj : The test result object.
*            DiagnosticsTestSignatureScreen_Obj : The test signature object.
*            DiagnosticsTestRecipeScreen_Obj : The test recipe object.
*            WelderId : Active welder Id.
*
* \return  - None.
******************************************************************************/
void Test::OnTestDataUpdated(TestResult *DiagnosticsTestResultScreen_Obj, TestSignature *DiagnosticsTestSignatureScreen_Obj, TestRecipe *DiagnosticsTestRecipeScreen_Obj, int WelderId)
{
    m_TestResult = DiagnosticsTestResultScreen_Obj;
    m_TestSignature = DiagnosticsTestSignatureScreen_Obj;
    m_TestRecipe = DiagnosticsTestRecipeScreen_Obj;

    if(m_ActiveWelderId != WelderId)
    {
        m_TestResultData = m_TestResult->GetTestResultData();
        m_TestProgressData = m_TestResult->GetTestProgressResultData();

        m_TestFrequency = m_TestProgressData.Frequency;
        m_TestStoredFrequency = m_TestProgressData.StoredFrequency;
        m_TestPower = m_TestProgressData.Power;

        if((m_TestSignature->GetIsCompleteTestSignatureReceived()) || (m_IsScreenReNavigated))
        {
            emit initiateTestGraphSignatureDisplay(true);
            m_IsScreenReNavigated = false;
            m_TestSignature->SetIsCompleteTestSignatureReceived(false);
        }

        emit testFrequencyChanged();
        emit testStoredFrequencyChanged();
        emit testPowerChanged();

        m_TestRecipeData = m_TestRecipe->GetTestRecipeData();

        /*Below statement make sure update shall happend when either screen navigated or
           restored to default request generated*/

         if(m_TestRecipe->GetIsTestRecipeUpdated())
        {
             /*To check whether both recipe structures are equal or not to control
               loading status on the screen*/

             if(areRecipeValuesEqual(m_TestRecipeData, m_TestRecipeDataLocal))
             {
                 emit areTestRecipeValuesEqual(true);
             }

             else
             {
                 emit areTestRecipeValuesEqual(false);
             }

            m_TestRecipeDataLocal = m_TestRecipeData;

            m_TestFreqLimitHigh = m_TestRecipeData.TestFreqLimitHigh;
            m_TestFreqLimitLow = m_TestRecipeData.TestFreqLimitLow;
            m_TestFreqOffset = m_TestRecipeData.TestFreqOffset;
            m_TestMemClear = m_TestRecipeData.ClearMemoryBeforeTest;
            m_TestAmplitudeRampTime = m_TestRecipeData.TestAmplitudeRampTime;
            m_TestAmplitude = m_TestRecipeData.TestAmplitude;
            m_TestAmplitude2 = m_TestRecipeData.TestAmplitude;
            m_TestAmpProportionalGain = m_TestRecipeData.TestAmpProportionalGain;
            m_TestAmpIntegralGain = m_TestRecipeData.TestAmpIntegralGain;
            m_TestAmpDerivativeGain = m_TestRecipeData.TestAmpDerivativeGain;
            m_TestPhaseProportionalGain = m_TestRecipeData.TestPhaseProportionalGain;
            m_TestPhaseIntegralGain = m_TestRecipeData.TestPhaseIntegralGain;
            m_TestPhaseDerivativeGain = m_TestRecipeData.TestPhaseDerivativeGain;
            m_TestPhaseloopCF = m_TestRecipeData.TestPhaseloopCF;

            emit testDataChanged();

            m_TestRecipe->SetIsTestRecipeUpdated(false);
        }
    }
}


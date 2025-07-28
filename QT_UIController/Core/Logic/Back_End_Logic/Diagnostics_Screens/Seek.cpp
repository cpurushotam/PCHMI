/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file handles the horn seek result parameters.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/
#include "Seek.h"
#include "CommPeerWrapper.h"
/**************************************************************************//**
*
* \brief  - Diagnostics Seek Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
Seek::Seek(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SeekScreenUpdated, this, &Seek::OnSeekDataUpdated);
    m_SeekRecipeDataLocal = m_SeekRecipeData;
}

/**************************************************************************//**
*
* \brief   - Below function commands to run seek.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Seek::seekRun()
{
    m_SeekResult->InitiateSeekRunOperation();
}

/**************************************************************************//**
*
* \brief   - Below function returns seek cycle details like date and time.
*
* \param   - None.
*
* \return  - m_SeekDateAndTime : The data and time.
******************************************************************************/
QString Seek::getSeekDateAndTime() const
{
    return m_SeekDateAndTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns seek resonant frequency value.
*
* \param   - None.
*
* \return  - m_SeekEndFrequency : The resonant frequency value.
******************************************************************************/
int Seek::getSeekEndFrequency() const
{
    return m_SeekEndFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency limit high.
*
* \param   - None.
*
* \return  - m_SeekFreqLimitHigh : The frequency limit high.
******************************************************************************/
int Seek::getSeekFreqLimitHigh() const
{
    return m_SeekFreqLimitHigh;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency limit high.
*
* \param   - SeekFreqLimitHigh : The frequency limit high.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekFreqLimitHigh(const int &SeekFreqLimitHigh)
{
    m_SeekFreqLimitHigh = SeekFreqLimitHigh;
    m_SeekRecipeDataLocal.SeekFreqLimitHigh = m_SeekFreqLimitHigh;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency limit low.
*
* \param   - None.
*
* \return  - m_SeekFreqLimitLow : The frequency limit low.
******************************************************************************/
int Seek::getSeekFreqLimitLow() const
{
    return m_SeekFreqLimitLow;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency limit low.
*
* \param   - SeekFreqLimitLow : The frequency limit low.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekFreqLimitLow(const int &SeekFreqLimitLow)
{
    m_SeekFreqLimitLow = SeekFreqLimitLow;
    m_SeekRecipeDataLocal.SeekFreqLimitLow = m_SeekFreqLimitLow;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency offset.
*
* \param   - None.
*
* \return  - m_SeekFreqOffset : The frequency offset.
******************************************************************************/
int Seek::getSeekFreqOffset() const
{
    return m_SeekFreqOffset;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency offset.
*
* \param   - SeekFreqOffset : The frequency offset.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekFreqOffset(const int &SeekFreqOffset)
{
    m_SeekFreqOffset = SeekFreqOffset;
    m_SeekRecipeDataLocal.SeekFreqOffset = m_SeekFreqOffset;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return the flag which states the memory offset shall be 0 or not.
*
* \param   - None.
*
* \return  - m_SeekMemClear : The offset status.
******************************************************************************/
bool Seek::getSeekMemClear() const
{
    return m_SeekMemClear;
}

/**************************************************************************//**
*
* \brief   - Below function updates the flag which states the memory offset shall be 0 or not.
*
* \param   - SeekMemClear : The offset status.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekMemClear(const bool &SeekMemClear)
{
    m_SeekMemClear = SeekMemClear;
    m_SeekRecipeDataLocal.SeekMemClearBeforeSeek = m_SeekMemClear;
}

/**************************************************************************//**
*
* \brief   - Below function returns the seek operation time.
*
* \param   - None.
*
* \return  - m_SeekTime : The seek operation time.
******************************************************************************/
float Seek::getSeekTime() const
{
    return m_SeekTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the seek operation time.
*
* \param   - SeekTime : The seek operation time.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekTime(const float &SeekTime)
{
    m_SeekTime = SeekTime;
    m_SeekRecipeDataLocal.SeekTime = m_SeekTime;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude ramp time.
*
* \param   - None.
*
* \return  - m_SeekAmplitudeRampTime : The amplitude ramp time.
******************************************************************************/
float Seek::getSeekAmplitudeRampTime() const
{
    return m_SeekAmplitudeRampTime;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude ramp time.
*
* \param   - SeekAmplitudeRampTime : The amplitude ramp time.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekAmplitudeRampTime(const float &SeekAmplitudeRampTime)
{
    m_SeekAmplitudeRampTime = SeekAmplitudeRampTime;
    m_SeekRecipeDataLocal.SeekAmplitudeRampTime = m_SeekAmplitudeRampTime;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude value.
*
* \param   - None.
*
* \return  - m_SeekAmplitude : The amplitude value.
******************************************************************************/
int Seek::getSeekAmplitude() const
{
    return m_SeekAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude value.
*
* \param   - SeekAmplitude : The amplitude value..
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekAmplitude(const int &SeekAmplitude)
{
    m_SeekAmplitude = SeekAmplitude;
    m_SeekRecipeDataLocal.SeekAmplitude = m_SeekAmplitude;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude propotional gain.
*
* \param   - None.
*
* \return  - m_SeekAmpProportionalGain : The amplitude propotional gain.
******************************************************************************/
int Seek::getSeekAmpProportionalGain() const
{
    return m_SeekAmpProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude propotional gain.
*
* \param   - SeekAmpProportionalGain : The amplitude propotional gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekAmpProportionalGain(const int &SeekAmpProportionalGain)
{
    m_SeekAmpProportionalGain = SeekAmpProportionalGain;
    m_SeekRecipeDataLocal.SeekAmpProportionalGain = m_SeekAmpProportionalGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude integral gain.
*
* \param   - None.
*
* \return  - m_SeekAmpIntegralGain : The amplitude integral gain.
******************************************************************************/
int Seek::getSeekAmpIntegralGain() const
{
    return m_SeekAmpIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude integral gain.
*
* \param   - SeekAmpIntegralGain : The amplitude integral gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekAmpIntegralGain(const int &SeekAmpIntegralGain)
{
    m_SeekAmpIntegralGain = SeekAmpIntegralGain;
    m_SeekRecipeDataLocal.SeekAmpIntegralGain = m_SeekAmpIntegralGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude derivative gain.
*
* \param   - None.
*
* \return  - m_SeekAmpDerivativeGain : The amplitude derivative gain.
******************************************************************************/
int Seek::getSeekAmpDerivativeGain() const
{
    return m_SeekAmpDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude derivative gain.
*
* \param   - SeekAmpDerivativeGain : The amplitude derivative gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekAmpDerivativeGain(const int &SeekAmpDerivativeGain)
{
    m_SeekAmpDerivativeGain = SeekAmpDerivativeGain;
    m_SeekRecipeDataLocal.SeekAmpDerivativeGain = m_SeekAmpDerivativeGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase propotional gain.
*
* \param   - None.
*
* \return  - m_SeekPhaseProportionalGain : The phase propotional gain.
******************************************************************************/
int Seek::getSeekPhaseProportionalGain() const
{
    return m_SeekPhaseProportionalGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase propotional gain.
*
* \param   - SeekPhaseProportionalGain : The phase propotional gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekPhaseProportionalGain(const int &SeekPhaseProportionalGain)
{
    m_SeekPhaseProportionalGain = SeekPhaseProportionalGain;
    m_SeekRecipeDataLocal.SeekPhaseProportionalGain = m_SeekPhaseProportionalGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase integral gain.
*
* \param   - None.
*
* \return  - m_SeekPhaseIntegralGain : The phase integral gain.
******************************************************************************/
int Seek::getSeekPhaseIntegralGain() const
{
    return m_SeekPhaseIntegralGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase integral gain.
*
* \param   - SeekPhaseIntegralGain : The phase integral gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekPhaseIntegralGain(const int &SeekPhaseIntegralGain)
{
    m_SeekPhaseIntegralGain = SeekPhaseIntegralGain;
    m_SeekRecipeDataLocal.SeekPhaseIntegralGain = m_SeekPhaseIntegralGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase integral gain.
*
* \param   - None.
*
* \return  - m_SeekPhaseDerivativeGain : The phase integral gain.
******************************************************************************/
int Seek::getSeekPhaseDerivativeGain() const
{
    return m_SeekPhaseDerivativeGain;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase integral gain.
*
* \param   - SeekPhaseDerivativeGain : The phase integral gain.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekPhaseDerivativeGain(const int &SeekPhaseDerivativeGain)
{
    m_SeekPhaseDerivativeGain = SeekPhaseDerivativeGain;
    m_SeekRecipeDataLocal.SeekPhaseDerivativeGain = m_SeekPhaseDerivativeGain;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the blind sick time.
*
* \param   - None.
*
* \return  - m_SeekBlindTimeSeek : The blind sick time.
******************************************************************************/
int Seek::getSeekBlindTimeSeek() const
{
    return m_SeekBlindTimeSeek;
}

/**************************************************************************//**
*
* \brief   - Below function updates the blind sick time.
*
* \param   - SeekBlindTimeSeek : The blind sick time.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekBlindTimeSeek(const int &SeekBlindTimeSeek)
{
     m_SeekBlindTimeSeek = SeekBlindTimeSeek;
     m_SeekRecipeDataLocal.BlindtimeSeek = m_SeekBlindTimeSeek;
     emit seekDataChanged();
}


/**************************************************************************//**
*
* \brief   - Below function returns the phase loop value.
*
* \param   - None.
*
* \return  - m_SeekPhaseloopCF : The phase loop value.
******************************************************************************/
int Seek::getSeekPhaseloopCF() const
{
    return m_SeekPhaseloopCF;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase loop value.
*
* \param   - SeekPhaseloopCF : The phase loop value.
*
* \return  - None.
******************************************************************************/
void Seek::updateSeekPhaseloopCF(const int &SeekPhaseloopCF)
{
    m_SeekPhaseloopCF = SeekPhaseloopCF;
    m_SeekRecipeDataLocal.SeekPhaseloopCF = m_SeekPhaseloopCF;
    emit seekDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void Seek::isScreenReNavigated(bool Value)
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
QString Seek::getMinSeekParametersValue(int Type)
{
    std::string retVal;

    switch (Type)
    {
    case SEEK_FREQENCY_LIMIT_HIGH :
         retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_FREQ_LIMIT_HIGH);
        break;

    case SEEK_FREQENCY_LIMIT_LOW :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_FREQ_LIMIT_LOW);
        break;

    case SEEK_FREQENCY_OFFSET :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_FREQ_OFFSET);
        break;

    case SEEK_MEM_CLEAR :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_MEM_CLEAR_BEFORE_SEEK);
        break;

    case SEEK_TIME_VAL :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_TIME);
        break;

    case SEEK_AMP_RAMP_TIME :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_AMPLITUDE_RAMP_TIME);
        break;

    case SEEK_AMP :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_AMPLITUDE);
        break;

    case SEEK_AMP_PROPOTIONAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_AMPLITUDE_PROPORTIONAL_GAIN);
        break;

    case SEEK_AMP_INTEGRAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_AMPLITUDE_INTEGRAL_GAIN);
        break;

    case SEEK_AMP_DERIVATIVE_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_AMPLITUDE_DERIVATIVE_GAIN);
        break;

    case SEEK_PHASE_PROPOTIONAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_PHASE_PROPORTIONAL_GAIN);
        break;

    case SEEK_PHASE_INT_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_PHASE_INTEGRAL_GAIN);
        break;

    case SEEK_PHASE_DERI_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_PHASE_DERIVATIVE_GAIN);
        break;

    case SEEK_PHASE_LOOP_CF :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_PHASE_LOOPCF);
        break;

    default :
        retVal = m_SeekRecipe->GetSeekRecipeParamMinValue(SEEK_FREQ_LIMIT_HIGH);
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
QString Seek::getMaxSeekParametersValue(int Type)
{
    std::string retVal;

    switch (Type)
    {
    case SEEK_FREQENCY_LIMIT_HIGH :
         retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_FREQ_LIMIT_HIGH);
        break;

    case SEEK_FREQENCY_LIMIT_LOW :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_FREQ_LIMIT_LOW);
        break;

    case SEEK_FREQENCY_OFFSET :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_FREQ_OFFSET);
        break;

    case SEEK_MEM_CLEAR :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_MEM_CLEAR_BEFORE_SEEK);
        break;

    case SEEK_TIME_VAL :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_TIME);
        break;

    case SEEK_AMP_RAMP_TIME :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_AMPLITUDE_RAMP_TIME);
        break;

    case SEEK_AMP :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_AMPLITUDE);
        break;

    case SEEK_AMP_PROPOTIONAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_AMPLITUDE_PROPORTIONAL_GAIN);
        break;

    case SEEK_AMP_INTEGRAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_AMPLITUDE_INTEGRAL_GAIN);
        break;

    case SEEK_AMP_DERIVATIVE_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_AMPLITUDE_DERIVATIVE_GAIN);
        break;

    case SEEK_PHASE_PROPOTIONAL_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_PHASE_PROPORTIONAL_GAIN);
        break;

    case SEEK_PHASE_INT_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_PHASE_INTEGRAL_GAIN);
        break;

    case SEEK_PHASE_DERI_GAIN :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_PHASE_DERIVATIVE_GAIN);
        break;

    case SEEK_PHASE_LOOP_CF :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_PHASE_LOOPCF);
        break;

    default :
        retVal = m_SeekRecipe->GetSeekRecipeParamMaxValue(SEEK_FREQ_LIMIT_HIGH);
        break;
    }

     return QString::fromLocal8Bit(retVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Role of onSavedPressed is to save the seek recipedata.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Seek::onSavedPressed()
{
    /*Below conditional statement shall be replaced with availabity of Branson Service Key*/
    if(true)
    {
        m_SeekRecipeDataLocal.SeekAmpProportionalGain = m_SeekRecipeData.SeekAmpProportionalGain;
        m_SeekRecipeDataLocal.SeekAmpIntegralGain = m_SeekRecipeData.SeekAmpIntegralGain;
        m_SeekRecipeDataLocal.SeekAmpDerivativeGain = m_SeekRecipeData.SeekAmpDerivativeGain;
        m_SeekRecipeDataLocal.SeekPhaseProportionalGain = m_SeekRecipeData.SeekPhaseProportionalGain;
        m_SeekRecipeDataLocal.SeekPhaseIntegralGain = m_SeekRecipeData.SeekPhaseIntegralGain;
        m_SeekRecipeDataLocal.SeekPhaseDerivativeGain = m_SeekRecipeData.SeekPhaseDerivativeGain;
        m_SeekRecipeDataLocal.BlindtimeSeek = m_SeekRecipeData.BlindtimeSeek;
        m_SeekRecipeDataLocal.SeekPhaseloopCF = m_SeekRecipeData.SeekPhaseloopCF;
    }

    m_SeekRecipe->SetSeekRecipeData(m_SeekRecipeDataLocal);
}

/**************************************************************************//**
*
* \brief   - Role of onResetToDefaultPressed is to restore default seek
*            recipe settings.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Seek::onResetToDefaultPressed()
{
    m_SeekRecipe->InitiateResetToDefaultSeekRequest();
}

/**************************************************************************//**
*
* \brief   - Role of onSeekRecipeScreenReNavigated is to make sure updated
*            recipe data available.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void Seek::onSeekRecipeScreenReNavigated()
{
    m_SeekRecipe->SetIsSeekRecipeUpdated(true);
}

/**************************************************************************//**
*
* \brief   - Role of the getSeekSignature is to return test signature
*            object accessed by seek graph screen.
*
* \param   - None.
*
* \return  - m_SeekSignature : Seek signature object pointer.
******************************************************************************/
SeekSignature *Seek::getSeekSignature()
{
    return m_SeekSignature;
}

/**************************************************************************//**
*
* \brief   - Returns the info whether recipe structures are equal are not.
*
* \param   - SeekRecipestruct : The recipe structure which is being compare.
*
* \return  - The info whether recipe structures are equal are not.
******************************************************************************/
bool Seek::areRecipeValuesEqual(const SeekRecipestruct &SeekRecipestruct_1, const SeekRecipestruct &SeekRecipestruct_2)
{
    return std::memcmp(&SeekRecipestruct_1, &SeekRecipestruct_2, sizeof(SeekRecipestruct)) == 0;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnSeekDataUpdated to update the horn seek result data.
*
* \param   - DiagnosticsSeekResultScreen_Obj : The seek result object.
*            DiagnosticsSeekSignatureScreen_Obj : The seek signature object.
*            DiagnosticsSeekRecipeScreen_Obj : The seek recipe object.
*            WelderId : Active welder Id.
*
* \return  - None.
******************************************************************************/
void Seek::OnSeekDataUpdated(SeekResult *DiagnosticsSeekResultScreen_Obj, SeekSignature *DiagnosticsSeekSignatureScreen_Obj, SeekRecipe *DiagnosticsSeekRecipeScreen_Obj, int WelderId)
{
    m_SeekResult = DiagnosticsSeekResultScreen_Obj;
    m_SeekSignature = DiagnosticsSeekSignatureScreen_Obj;
    m_SeekRecipe = DiagnosticsSeekRecipeScreen_Obj;

    if(m_ActiveWelderId != WelderId)
    {
        m_SeekResultData = m_SeekResult->GetSeekResultData();
        m_SeekDateAndTime = m_SeekResultData.DateTime;
        m_SeekEndFrequency = m_SeekResultData.EndFrequency;

        if((m_SeekSignature->GetIsCompleteSeekSignatureReceived()) || (m_IsScreenReNavigated))
        {
            emit initiateSeekGraphSignatureDisplay(true);
            m_IsScreenReNavigated = false;
            m_SeekSignature->SetIsCompleteSeekSignatureReceived(false);
        }

        emit seekDateAndTimeChanged();
        emit seekEndFrequencyChanged();

        m_SeekRecipeData = m_SeekRecipe->GetSeekRecipeData();

        /*Below statement make sure update shall happend when either screen navigated or
           restored to default request generated*/

        if(m_SeekRecipe->GetIsSeekRecipeUpdated())
        {
            /*To check whether both recipe structures are equal or not to control
              loading status on the screen*/

            if(areRecipeValuesEqual(m_SeekRecipeData, m_SeekRecipeDataLocal))
            {
                emit areSeekRecipeValuesEqual(true);
            }

            else
            {
                emit areSeekRecipeValuesEqual(false);
            }

            m_SeekRecipeDataLocal = m_SeekRecipeData;

            m_SeekFreqLimitHigh = m_SeekRecipeData.SeekFreqLimitHigh;
            m_SeekFreqLimitLow = m_SeekRecipeData.SeekFreqLimitLow;
            m_SeekFreqOffset = m_SeekRecipeData.SeekFreqOffset;
            m_SeekMemClear = m_SeekRecipeData.SeekMemClearBeforeSeek;
            m_SeekTime = m_SeekRecipeData.SeekTime;
            m_SeekAmplitudeRampTime = m_SeekRecipeData.SeekAmplitudeRampTime;
            m_SeekAmplitude = m_SeekRecipeData.SeekAmplitude;
            m_SeekAmpProportionalGain = m_SeekRecipeData.SeekAmpProportionalGain;
            m_SeekAmpIntegralGain = m_SeekRecipeData.SeekAmpIntegralGain;
            m_SeekAmpDerivativeGain = m_SeekRecipeData.SeekAmpDerivativeGain;
            m_SeekPhaseProportionalGain = m_SeekRecipeData.SeekPhaseProportionalGain;
            m_SeekPhaseIntegralGain = m_SeekRecipeData.SeekPhaseIntegralGain;
            m_SeekPhaseDerivativeGain = m_SeekRecipeData.SeekPhaseDerivativeGain;
            m_SeekBlindTimeSeek = m_SeekRecipeData.BlindtimeSeek;
            m_SeekPhaseloopCF = m_SeekRecipeData.SeekPhaseloopCF;

            emit seekDataChanged();

            m_SeekRecipe->SetIsSeekRecipeUpdated(false);
        }
    }
}

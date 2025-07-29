/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    SeekGraphSettings.cpp file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/03/2024 - Initial version.
***************************************************************************/
#include "SeekGraphSettings.h"
#include "deque"
#include "algorithm"
/**************************************************************************//**
*
* \brief  - Constructor to initialize limit values for each display parameter
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
SeekGraphSettings::SeekGraphSettings(QObject *parent)
{
    /*Initial limit values for each parameter type*/
    m_AmpAxisMinValue     = 0;
    m_AmpAxisMaxValue     = 120;
    m_PowerAxisMinValue   = 0;
    m_PowerAxisMaxValue   = 10;
    m_FreqAxisMinValue    = 19450;
    m_FreqAxisMaxValue    = 20450;
    m_PhaseAxisMinValue   = -180;
    m_PhaseAxisMaxValue   = 180;
    m_CurrentAxisMinValue = 0;
    m_CurrentAxisMaxValue = 120;

    m_TimeAxisMinValue = 0;
    m_TimeAxisMaxValue = 0.5;

    m_SeekSignature = nullptr;
}

/**************************************************************************//**
*
* \brief   - Below function returns the stored Y Axis parameter.
*
* \param   - None.
*
* \return  - storedValue : The stored Y Axis parameter.
******************************************************************************/
int SeekGraphSettings::getFirstAxisValue() const
{
    int storedValue = settings.value("FirstAxisValue").toInt();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the stored Y Axis parameter.
*
* \param   - FirstAxisValue : The stored Y Axis parameter.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateFirstAxisValuee(const int &FirstAxisValue)
{
    settings.setValue("FirstAxisValue", FirstAxisValue);
}

/**************************************************************************//**
*
* \brief   - Below function returns the stored Y Axis parameter.
*
* \param   - None.
*
* \return  - storedValue : The stored Y Axis parameter.
******************************************************************************/
int SeekGraphSettings::getSecondAxisValue() const
{
    int storedValue = settings.value("SecondAxisValue").toInt();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the stored Y Axis parameter.
*
* \param   - SecondAxisValue : The stored Y Axis parameter.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateSecondAxisValue(const int &SecondAxisValue)
{
    settings.setValue("SecondAxisValue", SecondAxisValue);
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude min value.
*
* \param   - None.
*
* \return  - m_AmpAxisMinValue : The amplitude min value.
******************************************************************************/
int SeekGraphSettings::getAmpAxisMinValue() const
{
    return m_AmpAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude min value.
*
* \param   - AmpAxisMinValue : The amplitude min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateAmpAxisMinValue(const int &AmpAxisMinValue)
{
    if(m_AmpAxisMinValue != AmpAxisMinValue)
    {
        m_AmpAxisMinValue = AmpAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude max value.
*
* \param   - None.
*
* \return  - m_AmpAxisMaxValue : The amplitude max value.
******************************************************************************/
int SeekGraphSettings::getAmpAxisMaxValue() const
{
    return m_AmpAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude max value.
*
* \param   - AmpAxisMaxValue : The amplitude max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateAmpAxisMaxValue(const int &AmpAxisMaxValue)
{
    if(m_AmpAxisMaxValue != AmpAxisMaxValue)
    {
        m_AmpAxisMaxValue = AmpAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the power min value.
*
* \param   - None.
*
* \return  - m_PowerAxisMinValue : The power min value.
******************************************************************************/
double SeekGraphSettings::getPowerAxisMinValue() const
{
    return m_PowerAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the power min value.
*
* \param   - PowerAxisMinValue : The power min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updatePowerAxisMinValue(const double &PowerAxisMinValue)
{
    if(m_PowerAxisMinValue != PowerAxisMinValue)
    {
        m_PowerAxisMinValue = PowerAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the power max value.
*
* \param   - None.
*
* \return  - m_PowerAxisMaxValue : The power max value.
******************************************************************************/
double SeekGraphSettings::getPowerAxisMaxValue() const
{
    return m_PowerAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the power max value.
*
* \param   - PowerAxisMaxValue : The power max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updatePowerAxisMaxValue(const double &PowerAxisMaxValue)
{
    if(m_PowerAxisMaxValue != PowerAxisMaxValue)
    {
        m_PowerAxisMaxValue = PowerAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency min value.
*
* \param   - None.
*
* \return  - m_FreqAxisMinValue : The frequency min value.
******************************************************************************/
int SeekGraphSettings::getFreqAxisMinValue() const
{
    return m_FreqAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the frequency min value.
*
* \param   - FreqAxisMinValue : The frequency min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateFreqAxisMinValue(const int &FreqAxisMinValue)
{
    if(m_FreqAxisMinValue != FreqAxisMinValue)
    {
        m_FreqAxisMinValue = FreqAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the frequency max value.
*
* \param   - None.
*
* \return  - m_FreqAxisMaxValue : The frequency max value.
******************************************************************************/
int SeekGraphSettings::getFreqAxisMaxValue() const
{
    return m_FreqAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates The frequency max value.
*
* \param   - FreqAxisMaxValue : The frequency max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateFreqAxisMaxValue(const int &FreqAxisMaxValue)
{
    if(m_FreqAxisMaxValue != FreqAxisMaxValue)
    {
        m_FreqAxisMaxValue = FreqAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase min value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMinValue : The phase min value.
******************************************************************************/
int SeekGraphSettings::getPhaseAxisMinValue() const
{
    return m_PhaseAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase min value.
*
* \param   - PhaseAxisMinValue : The phase min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updatePhaseAxisMinValue(const int &PhaseAxisMinValue)
{
    if(m_PhaseAxisMinValue != PhaseAxisMinValue)
    {
        m_PhaseAxisMinValue = PhaseAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase max value.
*
* \param   - None.
*
* \return  - m_PhaseAxisMaxValue : The phase max value.
******************************************************************************/
int SeekGraphSettings::getPhaseAxisMaxValue() const
{
    return m_PhaseAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase max value.
*
* \param   - PhaseAxisMaxValue : The phase max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updatePhaseAxisMaxValue(const int &PhaseAxisMaxValue)
{
    if(m_PhaseAxisMaxValue != PhaseAxisMaxValue)
    {
        m_PhaseAxisMaxValue = PhaseAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current min value.
*
* \param   - None.
*
* \return  - m_CurrentAxisMinValue : The current min value.
******************************************************************************/
int SeekGraphSettings::getCurrentAxisMinValue() const
{
    return m_CurrentAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current min value.
*
* \param   - CurrentAxisMinValue : The current min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateCurrentAxisMinValue(const int &CurrentAxisMinValue)
{
    if(m_CurrentAxisMinValue != CurrentAxisMinValue)
    {
        m_CurrentAxisMinValue = CurrentAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current max value.
*
* \param   - None.
*
* \return  - m_CurrentAxisMaxValue : The current max value.
******************************************************************************/
int SeekGraphSettings::getCurrentAxisMaxValue() const
{
   return m_CurrentAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current max value.
*
* \param   - CurrentAxisMaxValue : The current max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateCurrentAxisMaxValue(const int &CurrentAxisMaxValue)
{
    if(m_CurrentAxisMaxValue != CurrentAxisMaxValue)
    {
        m_CurrentAxisMaxValue = CurrentAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the time min value.
*
* \param   - None.
*
* \return  - m_TimeAxisMinValue : The time min value.
******************************************************************************/
int SeekGraphSettings::getTimeAxisMinValue() const
{
    return m_TimeAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the time min value.
*
* \param   - TimeAxisMinValue : The time min value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateTimeAxisMinValue(const int &TimeAxisMinValue)
{
    if(m_TimeAxisMinValue != TimeAxisMinValue)
    {
        m_TimeAxisMinValue = TimeAxisMinValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the time max value.
*
* \param   - None.
*
* \return  - m_TimeAxisMaxValue : The time max value.
******************************************************************************/
double SeekGraphSettings::getTimeAxisMaxValue() const
{
    return m_TimeAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the time max value.
*
* \param   - TimeAxisMaxValue : The time max value.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::updateTimeAxisMaxValue(const double &TimeAxisMaxValue)
{
    if(m_TimeAxisMaxValue != TimeAxisMaxValue)
    {
        m_TimeAxisMaxValue = TimeAxisMaxValue;
        emit OnGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function fetch the updated seek signature data.
*
* \param   - SeekSignatureSettings_Obj : seek signature object.
*
* \return  - None.
******************************************************************************/
void SeekGraphSettings::OnSeekSignatureSettingsUpdated(SeekSignature *SeekSignatureSettings_Obj)
{
    m_SeekSignature = SeekSignatureSettings_Obj;
    m_RequestedSeekSignatureData = m_SeekSignature->GetRequestedSeekSignatureData();

    m_TimeAxisMinValue = m_RequestedSeekSignatureData.front().Time;
    m_TimeAxisMaxValue = m_RequestedSeekSignatureData.back().Time;

    auto m_AmpAxisMinValue1 = std::min_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                               [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Amplitude < b.Amplitude;
    });
    m_AmpAxisMinValue =  m_AmpAxisMinValue1->Amplitude;

    auto m_AmpAxisMaxValue1 = std::max_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                               [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Amplitude < b.Amplitude;
    });
    m_AmpAxisMaxValue = m_AmpAxisMaxValue1->Amplitude;

    auto m_PowerAxisMinValue1 = std::min_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                 [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Power < b.Power;
    });
    m_PowerAxisMinValue =  m_PowerAxisMinValue1->Power;

    auto m_PowerAxisMaxValue1 = std::max_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                 [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Power < b.Power;
    });
    m_PowerAxisMaxValue = m_PowerAxisMaxValue1->Power;

    auto m_FreqAxisMinValue1 = std::min_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Frequency < b.Frequency;
    });
    m_FreqAxisMinValue =  m_FreqAxisMinValue1->Frequency;

    auto m_FreqAxisMaxValue1 = std::max_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Frequency < b.Frequency;
    });
    m_FreqAxisMaxValue = m_FreqAxisMaxValue1->Frequency;

    auto m_PhaseAxisMinValue1 = std::min_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                 [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Phase < b.Phase;
    });
    m_PhaseAxisMinValue =  m_PhaseAxisMinValue1->Phase;

    auto m_PhaseAxisMaxValue1 = std::max_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                 [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Phase < b.Phase;
    });
    m_PhaseAxisMaxValue = m_PhaseAxisMaxValue1->Phase;

    auto m_CurrentAxisMinValue1 = std::min_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                   [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Current < b.Current;
    });
    m_CurrentAxisMinValue =  m_CurrentAxisMinValue1->Current;

    auto m_CurrentAxisMaxValue1 = std::max_element(m_RequestedSeekSignatureData.begin(), m_RequestedSeekSignatureData.end(),
                                                   [](const SeekSignatureStruct& a, const SeekSignatureStruct& b) {
        return a.Current < b.Current;
    });
    m_CurrentAxisMaxValue = m_CurrentAxisMaxValue1->Current;

    if(m_AmpAxisMinValue == m_AmpAxisMaxValue)
    {
        m_AmpAxisMinValue     = 0;
        m_AmpAxisMaxValue     = 120;
    }

    if(m_PowerAxisMinValue == m_PowerAxisMaxValue)
    {
        m_PowerAxisMinValue   = 0;
        m_PowerAxisMaxValue   = 10;
    }

    if(m_FreqAxisMinValue == m_FreqAxisMaxValue)
    {
        m_FreqAxisMinValue    = 19450;
        m_FreqAxisMaxValue    = 20450;
    }

    if(m_PhaseAxisMinValue == m_PhaseAxisMaxValue)
    {
        m_PhaseAxisMinValue   = -180;
        m_PhaseAxisMaxValue   = 180;
    }

    if(m_CurrentAxisMinValue == m_CurrentAxisMaxValue)
    {
        m_CurrentAxisMinValue   = 0;
        m_CurrentAxisMaxValue   = 120;
    }

    emit OnGraphSettingsChanged();
}


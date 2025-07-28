/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanGraphSettings.cpp file stores graph settings configured at user end.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 03/04/2024 - Initial version.
***************************************************************************/
#include "ScanGraphSettings.h"
#include "CycleDetailsListModel.h"
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
ScanGraphSettings::ScanGraphSettings(QObject *parent)
{
    /*Initial limit values for each parameter type*/
    m_AmpAxisMinValue     = 0;
    m_AmpAxisMaxValue     = 120;
    m_FreqAxisMinValue    = 19450;
    m_FreqAxisMaxValue    = 20450;
    m_PhaseAxisMinValue   = -180;
    m_PhaseAxisMaxValue   = 180;
    m_CurrentAxisMinValue = 0;
    m_CurrentAxisMaxValue = 120;
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude min value.
*
* \param   - None.
*
* \return  - m_AmpAxisMinValue : The amplitude min value.
******************************************************************************/
int ScanGraphSettings::getAmpAxisMinValue() const
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
void ScanGraphSettings::updateAmpAxisMinValue(const int &AmpAxisMinValue)
{
    if(m_AmpAxisMinValue != AmpAxisMinValue)
    {
        m_AmpAxisMinValue = AmpAxisMinValue;
        emit OnScanGraphSettingsChanged();
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
int ScanGraphSettings::getAmpAxisMaxValue() const
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
void ScanGraphSettings::updateAmpAxisMaxValue(const int &AmpAxisMaxValue)
{
    if(m_AmpAxisMaxValue != AmpAxisMaxValue)
    {
        m_AmpAxisMaxValue = AmpAxisMaxValue;
        emit OnScanGraphSettingsChanged();
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
int ScanGraphSettings::getFreqAxisMinValue() const
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
void ScanGraphSettings::updateFreqAxisMinValue(const int &FreqAxisMinValue)
{
    if(m_FreqAxisMinValue != FreqAxisMinValue)
    {
        m_FreqAxisMinValue = FreqAxisMinValue;
        emit OnScanGraphSettingsChanged();
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
int ScanGraphSettings::getFreqAxisMaxValue() const
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
void ScanGraphSettings::updateFreqAxisMaxValue(const int &FreqAxisMaxValue)
{
    if(m_FreqAxisMaxValue != FreqAxisMaxValue)
    {
        m_FreqAxisMaxValue = FreqAxisMaxValue;
        emit OnScanGraphSettingsChanged();
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
int ScanGraphSettings::getPhaseAxisMinValue() const
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
void ScanGraphSettings::updatePhaseAxisMinValue(const int &PhaseAxisMinValue)
{
    if(m_PhaseAxisMinValue != PhaseAxisMinValue)
    {
        m_PhaseAxisMinValue = PhaseAxisMinValue;
        emit OnScanGraphSettingsChanged();
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
int ScanGraphSettings::getPhaseAxisMaxValue() const
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
void ScanGraphSettings::updatePhaseAxisMaxValue(const int &PhaseAxisMaxValue)
{
    if(m_PhaseAxisMaxValue != PhaseAxisMaxValue)
    {
        m_PhaseAxisMaxValue = PhaseAxisMaxValue;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current min value.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : The current min value.
******************************************************************************/
int ScanGraphSettings::getCurrentAxisMinValue() const
{
    return m_CurrentAxisMinValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current min value.
*
* \param   - WeldRecipeNumber : The current min value.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::updateCurrentAxisMinValue(const int &CurrentAxisMinValue)
{
    if(m_CurrentAxisMinValue != CurrentAxisMinValue)
    {
        m_CurrentAxisMinValue = CurrentAxisMinValue;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current max value.
*
* \param   - None.
*
* \return  - m_WeldRecipeNumber : The current max value.
******************************************************************************/
int ScanGraphSettings::getCurrentAxisMaxValue() const
{
   return m_CurrentAxisMaxValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current max value.
*
* \param   - WeldRecipeNumber : The current max value.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::updateCurrentAxisMaxValue(const int &CurrentAxisMaxValue)
{
    if(m_CurrentAxisMaxValue != CurrentAxisMaxValue)
    {
        m_CurrentAxisMaxValue = CurrentAxisMaxValue;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the amplitude axis visibility status.
*
* \param   - None.
*
* \return  - m_AmplitudeAxisVisible : The amplitude axis visibility status.
******************************************************************************/
bool ScanGraphSettings::getAmplitudeAxisVisible() const
{
    return m_AmplitudeAxisVisible;
}

/**************************************************************************//**
*
* \brief   - Below function updates the amplitude axis visibility status.
*
* \param   - AmplitudeAxisVisible : The amplitude axis visibility status.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::updateAmplitudeAxisVisible(const bool &AmplitudeAxisVisible)
{
    if(m_AmplitudeAxisVisible != AmplitudeAxisVisible)
    {
        m_AmplitudeAxisVisible = AmplitudeAxisVisible;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the current axis visibility status.
*
* \param   - None.
*
* \return  - m_CurrentAxisVisible : The current axis visibility status.
******************************************************************************/
bool ScanGraphSettings::getCurrentAxisVisible() const
{
    return m_CurrentAxisVisible;
}

/**************************************************************************//**
*
* \brief   - Below function updates the current axis visibility status.
*
* \param   - CurrentAxisVisible : The current axis visibility status.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::updateCurrentAxisVisible(const bool &CurrentAxisVisible)
{
    if(m_CurrentAxisVisible != CurrentAxisVisible)
    {
        m_CurrentAxisVisible = CurrentAxisVisible;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the phase axis visibility status.
*
* \param   - None.
*
* \return  - m_PhaseAxisVisible : The phase axis visibility status.
******************************************************************************/
bool ScanGraphSettings::getPhaseAxisVisible() const
{
    return m_PhaseAxisVisible;
}

/**************************************************************************//**
*
* \brief   - Below function updates the phase axis visibility status.
*
* \param   - PhaseAxisVisible : The phase axis visibility status.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::updatePhaseAxisVisible(const bool &PhaseAxisVisible)
{
    if(m_PhaseAxisVisible != PhaseAxisVisible)
    {
        m_PhaseAxisVisible = PhaseAxisVisible;
        emit OnScanGraphSettingsChanged();
    }
}

/**************************************************************************//**
*
* \brief   - Below function fetch the updated weld signature data.
*
* \param   - ScanSignatureSettings_Obj : Weld signature object.
*
* \return  - None.
******************************************************************************/
void ScanGraphSettings::OnScanSignatureSettingsUpdated(HornScanSignature *ScanSignatureSettings_Obj)
{
    m_ScanSignature = ScanSignatureSettings_Obj;
    m_RequestedScanSignatureData = m_ScanSignature->GetHornScanSignatureData();

//    m_FreqAxisMinValue = m_RequestedScanSignatureData.front().Frequency;
//    m_FreqAxisMaxValue = m_RequestedScanSignatureData.back().Frequency;

    auto m_AmpAxisMinValue1 = std::min_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                               [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Amplitude < b.Amplitude;
    });
    m_AmpAxisMinValue = m_AmpAxisMinValue1->Amplitude;

    auto m_AmpAxisMaxValue1 = std::max_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                               [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Amplitude < b.Amplitude;
    });
    m_AmpAxisMaxValue = m_AmpAxisMaxValue1->Amplitude;

    auto m_FreqAxisMinValue1 = std::min_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Frequency < b.Frequency;
    });
    m_FreqAxisMinValue = m_FreqAxisMinValue1->Frequency;

    auto m_FreqAxisMaxValue1 = std::max_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Frequency < b.Frequency;
    });
    m_FreqAxisMaxValue = m_FreqAxisMaxValue1->Frequency;

    auto m_PhaseAxisMinValue1 = std::min_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                 [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Phase < b.Phase;
    });
    m_PhaseAxisMinValue = m_PhaseAxisMinValue1->Phase;

    auto m_PhaseAxisMaxValue1 = std::max_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                 [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Phase < b.Phase;
    });
    m_PhaseAxisMaxValue = m_PhaseAxisMaxValue1->Phase;

    auto m_CurrentAxisMinValue1 = std::min_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                   [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Current < b.Current;
    });
    m_CurrentAxisMinValue = m_CurrentAxisMinValue1->Current;

    auto m_CurrentAxisMaxValue1 = std::max_element(m_RequestedScanSignatureData.begin(), m_RequestedScanSignatureData.end(),
                                                   [](const HornScanSignatureStruct& a, const HornScanSignatureStruct& b) {
        return a.Current < b.Current;
    });
    m_CurrentAxisMaxValue = m_CurrentAxisMaxValue1->Current;

    emit OnScanGraphSettingsChanged();
}


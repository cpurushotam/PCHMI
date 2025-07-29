/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CalibratePressure.cpp file handles calibration related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 18/10/2024 - Initial version.
***************************************************************************/
#include "CalibratePressure.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CalibratePressure::CalibratePressure(QObject *parent)
    : QObject(parent)
{
    pthread_mutex_init(&mtx, nullptr);

    connect(UpdateScreen::getInstance(), &UpdateScreen::CalibrationDataChanged, this, &CalibratePressure::OnCalibratePressureUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CalibratePressure::~CalibratePressure()
{

}


/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void CalibratePressure::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief   - Below function initiates pressure calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibratePressure::onCalibratePressurePressed()
{
    m_CalibrationAce->InitiatePressureCalibrationRequest();
}

/**************************************************************************//**
*
* \brief   - Below function updates calibration iteration rounds.
*
* \param   - InterationCount : The iteration count.
*
* \return  - None.
******************************************************************************/
void CalibratePressure::onContinuePressed(int InterationCount)
{
    switch (InterationCount)
    {
    case InterationNo1 :
        m_CalibrationAce->InitiateUserEnteredPressure1SendRequest(m_CalibrationReadings);
        break;

    case InterationNo2 :
        m_CalibrationAce->InitiateUserEnteredPressure2SendRequest(m_CalibrationReadings);
        break;

    case InterationNo3 :
        m_CalibrationAce->InitiateUserEnteredPressure3SendRequest(m_CalibrationReadings);
        break;
    }
}

/**************************************************************************//**
*
* \brief   - Below function abort pressure calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibratePressure::onCalibrationAbortPressed()
{
    m_CalibrationAce->InitiateCalibrationAbortRequest();
}
/**************************************************************************//**
*
* \brief   - Below function returns the calibration readings.
*
* \param   - None.
*
* \return  - m_CalibrationReadings : The iteration readings.
******************************************************************************/
float CalibratePressure::getCalibrationReadings() const
{
    return m_CalibrationReadings;
}

/**************************************************************************//**
*
* \brief   - Below function updates the calibration readings.
*
* \param   - CalibrationReadings : The iteration readings.
*
* \return  - None.
******************************************************************************/
void CalibratePressure::updateCalibrationReadings(const float &CalibrationReadings)
{
    m_CalibrationReadings = CalibrationReadings;
    emit calibrationReadingsChanged();
}

/**************************************************************************//**
*
* \brief   - TBD
*
*
* \param   - TBD
*
*
* \return  - TBD
******************************************************************************/
void CalibratePressure::OnCalibratePressureUpdated(CalibrationAce *CalibrationAce_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_CalibrationAce = CalibrationAce_Obj;

    pthread_mutex_unlock(&mtx);
}

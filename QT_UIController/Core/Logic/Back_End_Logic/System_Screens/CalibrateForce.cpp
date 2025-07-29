/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CalibrateForce.cpp file handles calibration related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 18/10/2024 - Initial version.
***************************************************************************/
#include "CalibrateForce.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CalibrateForce::CalibrateForce(QObject *parent)
    : QObject(parent)
{
    pthread_mutex_init(&mtx, nullptr);

    connect(UpdateScreen::getInstance(), &UpdateScreen::CalibrationDataChanged, this, &CalibrateForce::OnCalibrateForceUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CalibrateForce::~CalibrateForce()
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
void CalibrateForce::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief   - Below function initiates force calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibrateForce::onCalibrateForcePressed()
{
    m_CalibrationAce->InitiateForceCalibrationRequest();
}

/**************************************************************************//**
*
* \brief   - Below function updates calibration iteration rounds.
*
* \param   - InterationCount : The iteration count.
*
* \return  - None.
******************************************************************************/
void CalibrateForce::onContinuePressed(int InterationCount)
{
    switch (InterationCount)
    {
    case InterationNo1 :
        m_CalibrationAce->InitiateUserEnteredForce1SendRequest(m_CalibrationReadings);
        break;

    case InterationNo2 :
        m_CalibrationAce->InitiateUserEnteredForce2SendRequest(m_CalibrationReadings);
        break;
    }
}

/**************************************************************************//**
*
* \brief   - Below function abort force calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibrateForce::onCalibrationAbortPressed()
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
float CalibrateForce::getCalibrationReadings() const
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
void CalibrateForce::updateCalibrationReadings(const float &CalibrationReadings)
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
void CalibrateForce::OnCalibrateForceUpdated(CalibrationAce *CalibrationAce_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_CalibrationAce = CalibrationAce_Obj;

    if(m_CalibrationAce->GetPartContactFoundStatusValue())
    {
      emit partContactDetected();
    }

    pthread_mutex_unlock(&mtx);
}

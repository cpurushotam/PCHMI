/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CalibrateActuator.cpp file handles calibration related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 18/10/2024 - Initial version.
***************************************************************************/
#include "CalibrateActuator.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CalibrateActuator::CalibrateActuator(QObject *parent)
    : QObject(parent)
{
    pthread_mutex_init(&mtx, nullptr);

    connect(UpdateScreen::getInstance(), &UpdateScreen::CalibrationDataChanged, this, &CalibrateActuator::OnCalibrateActuatorUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CalibrateActuator::~CalibrateActuator()
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
void CalibrateActuator::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief   - Below function initiates actuator calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibrateActuator::onQuickCalibrationPressed()
{
    m_CalibrationAce->InitiateQuickCalibrationRequest();
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
void CalibrateActuator::OnCalibrateActuatorUpdated(CalibrationAce *CalibrationAce_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_CalibrationAce = CalibrationAce_Obj;

    pthread_mutex_unlock(&mtx);
}

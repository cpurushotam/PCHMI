/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CalibrateResetSensors.cpp file handles calibration related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 18/10/2024 - Initial version.
***************************************************************************/
#include "CalibrateResetSensors.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CalibrateResetSensors::CalibrateResetSensors(QObject *parent)
    : QObject(parent)
{
    pthread_mutex_init(&mtx, nullptr);

    connect(UpdateScreen::getInstance(), &UpdateScreen::CalibrationDataChanged, this, &CalibrateResetSensors::OnCalibrateResetSensorsUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CalibrateResetSensors::~CalibrateResetSensors()
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
void CalibrateResetSensors::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief   - Below function updates reset calibration.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CalibrateResetSensors::onOKPressed()
{
    m_CalibrationAce->InitiateCalibrationResetRequest();
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
void CalibrateResetSensors::OnCalibrateResetSensorsUpdated(CalibrationAce *CalibrationAce_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_CalibrationAce = CalibrationAce_Obj;

    pthread_mutex_unlock(&mtx);
}

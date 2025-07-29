/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CalibrateQuick.cpp file handles calibration related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 18/10/2024 - Initial version.
***************************************************************************/
#include "CalibrateQuick.h"
/**************************************************************************//**
*
* \brief  - Constructor to handle calibration related signal handling
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CalibrateQuick::CalibrateQuick(QObject *parent)
    : QObject(parent)
{
    pthread_mutex_init(&mtx, nullptr);

    connect(UpdateScreen::getInstance(), &UpdateScreen::CalibrationDataChanged, this, &CalibrateQuick::OnCalibrateQuickUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CalibrateQuick::~CalibrateQuick()
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
void CalibrateQuick::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief   - Slot to be called when notification arrived from ASC.
*
*
* \param   - CalibrationAce_Obj : Object ponter for calibration data.
*            WelderId : welder ID
*
* \return  - None.
******************************************************************************/
void CalibrateQuick::OnCalibrateQuickUpdated(CalibrationAce *CalibrationAce_Obj, int WelderId)
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

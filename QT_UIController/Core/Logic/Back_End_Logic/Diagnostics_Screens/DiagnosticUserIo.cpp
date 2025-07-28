/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file handles DiagnosticUserIO  parameters.
***************************************************************************/
#include "DiagnosticUserIo.h"
/**************************************************************************//**
*
* \brief  - Diagnostics DiagnosticUserIO Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
DiagnosticUserIO::DiagnosticUserIO(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::DiagnosticUserIOUpdated, this, &DiagnosticUserIO::OnDiagnosticUserIODetailsUpdated);
}

/**************************************************************************//**
*
* \brief  - Set each pin value to High/Low from HMI .
*
* \param  - int pinNo, bool pinVal.
*
* \return - None.
*
******************************************************************************/
void DiagnosticUserIO :: setDigitalOpPinFromHMI(int pinNo, bool pinVal)
{
    m_DIAGNOSTIC_USERIO_DIGOUTPUTS.DIAGNOSTIC_USERIO_DIGOUTPUTS[pinNo] = pinVal;
}

/**************************************************************************//**
*
* \brief  - Receive the refresh command from HMI and update the Digital outputs and analog outputs.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/

void DiagnosticUserIO :: sendRefreshRequest()
{
    m_DigitalIOMgr->setDignUserIODigitalOP(m_DIAGNOSTIC_USERIO_DIGOUTPUTS);

    m_DigitalIOMgr->InitiateRefreshRequest();
}
/**************************************************************************//**
*
* \brief  -Receive the Stop command from HMI
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void DiagnosticUserIO :: sendStopRequest()
{
    m_DigitalIOMgr->InitiateStopRequest();
}

/**************************************************************************//**
*
* \brief  -Receive the Stop command from HMI
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
bool DiagnosticUserIO :: setDigitalInputs(int index)
{
    return m_DIAGNOSTIC_USERIO_DIGINPUTS.DIAGNOSTIC_USERIO_DIGINPUTS[index];
}
/**************************************************************************//**
*
* \brief  - Role of the slot OnUserIODigitalDetailsUpdated is to update values on Diagnostic UserIO screen.
*
* \param  - DigitalIOMgrDetailsResult_Obj : Object pointer of type DigitalIOMgr.
*
* \return - None.
******************************************************************************/
void DiagnosticUserIO::OnDiagnosticUserIODetailsUpdated(DigitalIOMgr *DigitalIOMgrDetailsResult_Obj  , int WelderId)
{
    m_DigitalIOMgr =DigitalIOMgrDetailsResult_Obj;

    if(m_DigitalIOMgr->IsDiagnosticDigitalInputsUpdated() || m_ActiveWelderId != WelderId)
    {
        m_DIAGNOSTIC_USERIO_DIGINPUTS = m_DigitalIOMgr->GetDignosticDigitalInputs();
        m_DigitalIOMgr->ResetDiagnosticDigitalInputsUpdatedFlag();
        emit diagnosticUserIOChanged();
        emit outputDataChanged();
        m_ActiveWelderId = WelderId;
    }
}
/**************************************************************************//**
*
* \brief  - Returns the ANalog OUtput 1 to HMI
*
* \param  - None.
*
* \return - m_AnalogOutput_1.
*
******************************************************************************/
float DiagnosticUserIO::getAnalogOutput_1() const
{
    return m_AnalogOutput_1;
}

/**************************************************************************//**
*
* \brief  - Updatw the analog input 1 value from HMI.
*
* \param  - newAnalogOutput_1.
*
* \return - None.
*
******************************************************************************/
void DiagnosticUserIO::updateAnalogOutput_1(float newAnalogOutput_1)
{
    if (m_AnalogOutput_1 != newAnalogOutput_1)
    {
        m_AnalogOutput_1 = newAnalogOutput_1;
        m_DIAGNOSTIC_USERIO_DIGOUTPUTS.Analog_Output_1 = newAnalogOutput_1;
    }
    emit outputDataChanged();
}

/**************************************************************************//**
*
* \brief  - Returns the ANalog OUtput2 to HMI
*
* \param  - None.
*
* \return - m_AnalogOutput_2.
*
******************************************************************************/
float DiagnosticUserIO::getAnalogOutput_2() const
{
    return m_AnalogOutput_2;
}

/**************************************************************************//**
*
* \brief  -  Update the Analog OUtput 2 from HMI.
*
* \param  - newAnalogOutput_2.
*
* \return - None.
*
******************************************************************************/
void DiagnosticUserIO::updateAnalogOutput_2(float newAnalogOutput_2)
{
    if (m_AnalogOutput_2 != newAnalogOutput_2)
    {
        m_AnalogOutput_2 = newAnalogOutput_2;
        m_DIAGNOSTIC_USERIO_DIGOUTPUTS.Analog_Output_2 = newAnalogOutput_2;
    }
    emit outputDataChanged();
}
/**************************************************************************//**
*
* \brief  - Returns the ANalog input 1 to HMI
*
* \param  - None.
*
* \return - Analog_Input_1.
*
******************************************************************************/
float DiagnosticUserIO::getAnalogInput_1() const
{
    return m_DIAGNOSTIC_USERIO_DIGINPUTS.Analog_Input_1;
}
/**************************************************************************//**
*
* \brief  - Returns the ANalog input 2 to HMI
*
* \param  - None.
*
* \return - Analog_Input_2.
*
******************************************************************************/
float DiagnosticUserIO::getAnalogInput_2() const
{
    return m_DIAGNOSTIC_USERIO_DIGINPUTS.Analog_Input_2;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps track for current active screen.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 20/07/2023 - Initial version.
***************************************************************************/
#include "ActiveScreen.h"
/**************************************************************************//**
*
* \brief   - ActiveScreen class constructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ActiveScreen::ActiveScreen(QObject *parent) : QObject(parent)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the instance of ActiveScreen class
*
* \param   - None.
*
* \return  - m_ActiveScreen_Obj : Object pointer of ActiveScreen class.
******************************************************************************/
ActiveScreen *ActiveScreen::getInstance()
{
    static ActiveScreen m_Instance;
    return &m_Instance;
}

/**************************************************************************//**
*
* \brief   - Below function returns active screen unique value.
*
* \param   - None.
*
* \return  - m_CurrentActiveScreen : Unique value associated to each screen.
******************************************************************************/
int ActiveScreen::getCurrentActiveScreen()
{
    return m_CurrentActiveScreen;
}

/**************************************************************************//**
*
* \brief   - Below function accepts active screen unique value update.
*
* \param   - m_IndexVal : Screen value.
*
* \return  - None.
******************************************************************************/
void ActiveScreen::updateCurrentActiveScreen(int m_IndexVal)
{
    m_CurrentActiveScreen = m_IndexVal;
    emit OnACurrentActiveScreenChanged();
}

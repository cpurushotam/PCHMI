/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
Declares IdleTimeLogout class which is responsible to set QT Timer as per Idle Time Logout
***************************************************************************/
#include<QString>
#include <QEvent>
#include <QDebug>
#include "IdleTimeLogout.h"

/**************************************************************************//**
*
* \brief  - IdleTimeLogout Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
IdleTimeLogout::IdleTimeLogout(QObject *parent) : QObject(parent)
{
    /* set max default timeout i.e to 24 (2147483647 msec) days */
    m_TimeOut = MAX_TIMEOUT_VAL;
    m_Timer.setInterval(m_TimeOut);
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(appSlepp()));
    m_Timer.start(m_TimeOut);
}

/**************************************************************************//**
*
* \brief  - Set time out value
*
* \param  - milliseconds - time out value in milisecond
*
* \return - none
*
******************************************************************************/
void IdleTimeLogout::setTimeOut(int milliseconds)
{
    m_TimeOut = milliseconds;
    m_Timer.setInterval(m_TimeOut);
}

/**************************************************************************//**
*
* \brief  - Called when UI is in sleep and emits logout signal
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void IdleTimeLogout::appSlepp()
{
    if(m_TimeOut != MAX_TIMEOUT_VAL)
    {
        emit idleTimeLogOut();
    }
}

/**************************************************************************//**
*
* \brief  - eventFilter : Checks if any event is raised or not
*
* \param  - QObject - QObject class pointer
*           QEvent - QEvent class pointer
*
* \return -  if you want to filter the event out, i.e. stop it being handled further,
*            return true; otherwise return false
*
******************************************************************************/
bool IdleTimeLogout::eventFilter(QObject *obj, QEvent *ev)
{

    if(ev->type() == QEvent::KeyPress || ev->type() == QEvent::MouseMove)
    {
        m_Timer.stop();
        m_Timer.start(m_TimeOut);
    }
    return QObject::eventFilter(obj, ev);
}

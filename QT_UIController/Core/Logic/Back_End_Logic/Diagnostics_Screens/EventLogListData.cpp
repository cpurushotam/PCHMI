/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    EventLogListData.h file file provides Eventlog detail listmodel which is used by QMl

***************************************************************************/
#include "EventLogListData.h"
#include "EventLogStructure.h"
#include "Common_Definitions.h"

/**************************************************************************//**
*
* \brief  - Constructor to initialize the  variables required under EventLOg TableDisplay.
*
*
* \param  - None
*
* \return - None
*
******************************************************************************/
EventLogListData::EventLogListData()
{

}

EventLogListData::EventLogListData(const int& p_EventIdx,const int& p_EventId, const QString& p_ParameterId, const QString& p_DateTime,
                                   const QString& p_UserName, const QString & p_OldParameters,
                                   const QString& p_NewParameters, const QString& p_SourceOfEvent, const QString& p_PsSerialNo, const QString& p_AcSerialNo ,
                                   const QString & p_HMISerialNo , const QString& p_Comment)
                                   : m_EventIdx(p_EventIdx),
                                     m_EventID(p_EventId),
                                     m_ParameterID(p_ParameterId),
                                     m_DateTime(p_DateTime),
                                     m_UserName(p_UserName),
                                     m_OldParameters(p_OldParameters),
                                     m_NewParameters(p_NewParameters),
                                     m_SourceOfEvent(p_SourceOfEvent),
                                     m_PSSerialNumber(p_PsSerialNo),
                                     m_ACSerialNumber(p_AcSerialNo),
                                     m_HMISerialNumber(p_HMISerialNo),
                                     m_Comment(p_Comment)
{

}

/**************************************************************************//**
*
* \brief   - Below function returns the eventId .
*
* \param   - None.
*
* \return  - m_EventID
******************************************************************************/
int EventLogListData::getEventID() const
{
    return m_EventID;
}

/**************************************************************************//**
*
* \brief   - Below function returns the EVent index.
*
* \param   - None.
*
* \return  - int - m_EventIdx
******************************************************************************/
int EventLogListData::getEventIndex() const
{
    return m_EventIdx;
}



/**************************************************************************//**
*
* \brief   - Below function returns the ParameterID .
*
* \param   - None.
*
* \return  - QString - m_ParameterID.
******************************************************************************/
QString EventLogListData::getParameterID() const
{
    return m_ParameterID;
}
/**************************************************************************//**
*
* \brief   - Below function returns the  Event DateTime.
*
* \param   - None.
*
* \return  - QString - m_DateTime.
******************************************************************************/
QString EventLogListData::getDateTime() const
{
    return m_DateTime;
}
/**************************************************************************//**
*
* \brief   - Below function returns the Event UserName.
*
* \param   - None.
*
* \return  - QString - m_UserName.
******************************************************************************/
QString EventLogListData::getUserName() const
{
    return m_UserName;
}
/**************************************************************************//**
*
* \brief   - Below function returns the Event log OldParameters(From).
*
* \param   - None.
*
* \return  - QString - m_OldParameters .
******************************************************************************/
QString EventLogListData::getOldParameters() const
{
    return m_OldParameters;
}
/**************************************************************************//**
*
* \brief   - Below function returns the Event NewParameters (To).
*
* \param   - None.
*
* \return  - QString - m_NewParameters.
******************************************************************************/
QString EventLogListData::getNewParameters() const
{
    return m_NewParameters;
}
/**************************************************************************//**
*
* \brief   - Below function returns the SourceOfEvent
*
* \param   - None.
*
* \return  - QString - m_SourceOfEvent .
******************************************************************************/
QString EventLogListData::getSourceOfEvent() const
{
    return m_SourceOfEvent;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Event PSSerialNumber.
*
* \param   - None.
*
* \return  - QString - m_PSSerialNumber.
******************************************************************************/
QString EventLogListData::getPSSerialNumber() const
{
    return m_PSSerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the event m_ACSerialNumber.
*
* \param   - None.
*
* \return  - QString - m_ACSerialNumber.
******************************************************************************/
QString EventLogListData::getACSerialNumber() const
{
    return m_ACSerialNumber;
}

/**************************************************************************//**
*
* \brief   - Below function returns the HMISerialNumber.
*
* \param   - None.
*
* \return  - QString - m_HMISerialNumber.
******************************************************************************/
QString EventLogListData::getHMISerialNumber() const
{
    return m_HMISerialNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the Event Comment.
*
* \param   - None.
*
* \return  - QString - m_Comment.
******************************************************************************/
QString EventLogListData::getComment() const
{
    return m_Comment;
}

/**************************************************************************//**
*
* \brief   - Below function returns the Type of Event.
*
* \param   - None.
*
* \return  - QString - EventType.
******************************************************************************/

QString EventLogListData::getEventType() const
{
    QString EventType;

    for(auto it: EventTypeName)
    {
        if(it.first == m_EventID)
        {
            EventType = QString::fromStdString(it.second);
            break;
        }
    }
    return EventType;
}






















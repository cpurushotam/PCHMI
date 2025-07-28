/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    DateTimeSettings.cpp file handles the date time settings inputs.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 28/11/2024 - Initial version.
***************************************************************************/
#include "DateTimeSettings.h"
#include <iostream>
#include <QDateTime>
#include <ctime>
#include <cstdlib>
/**************************************************************************//**
*
* \brief  - Constructor.
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/

DateTimeSettings::DateTimeSettings(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::DateAndTimeUpdated, this, &DateTimeSettings::OnDateTimeSettingsUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
DateTimeSettings::~DateTimeSettings()
{

}

/**************************************************************************//**
*
* \brief   - Below function return day value.
*
* \param   - None.
*
* \return  - m_Day.
******************************************************************************/
int DateTimeSettings::getDay() const
{
    return m_Day;
}

/**************************************************************************//**
*
* \brief   - Below function updates day value.
*
* \param   - Day.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateDay(const int &Day)
{
    m_Day = Day;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return month value.
*
* \param   - None.
*
* \return  - m_Month.
******************************************************************************/
int DateTimeSettings::getMonth() const
{
    return m_Month;
}

/**************************************************************************//**
*
* \brief   - Below function updates month value.
*
* \param   - Month.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateMonth(const int &Month)
{
    m_Month = Month;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return year value.
*
* \param   - None.
*
* \return  - m_Year.
******************************************************************************/
int DateTimeSettings::getYear() const
{
    return m_Year;
}

/**************************************************************************//**
*
* \brief   - Below function updates year value.
*
* \param   - Year.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateYear(const int &Year)
{
    m_Year = Year;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return hour value.
*
* \param   - None.
*
* \return  - m_Hours.
******************************************************************************/
int DateTimeSettings::getHours() const
{
    return m_Hours;
}

/**************************************************************************//**
*
* \brief   - Below function updates hour value.
*
* \param   - Hours.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateHours(const int &Hours)
{
    m_Hours = Hours;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return minutes value.
*
* \param   - None.
*
* \return  - m_Minutes.
******************************************************************************/
int DateTimeSettings::getMinutes() const
{
    return m_Minutes;
}

/**************************************************************************//**
*
* \brief   - Below function updates minutes value.
*
* \param   - Minutes.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateMinutes(const int &Minutes)
{
    m_Minutes = Minutes;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return seconds value.
*
* \param   - None.
*
* \return  - m_Seconds.
******************************************************************************/
int DateTimeSettings::getSeconds() const
{
    return m_Seconds;
}

/**************************************************************************//**
*
* \brief   - Below function updates seconds value.
*
* \param   - Seconds.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateSeconds(const int &Seconds)
{
    m_Seconds = Seconds;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function return merediem value.
*
* \param   - None.
*
* \return  - m_Merediem.
******************************************************************************/
int DateTimeSettings::getMerediem() const
{
    return m_Merediem;
}

/**************************************************************************//**
*
* \brief   - Below function updates merediem value.
*
* \param   - Merediem.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::updateMerediem(const int &Merediem)
{
    m_Merediem = Merediem;
    emit dateTimeSettingsChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns date format value.
*
* \param   - None.
*
* \return  - m_DateFormat.
******************************************************************************/
int DateTimeSettings::getDateFormat()
{
    return (static_cast<int> (m_DateFormat));
}

/**************************************************************************//**
*
* \brief   - Below function updates date format value.
*
* \param   - Value.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::setDateFormat(int Value)
{
    m_DateTimeConversion->setDateFormat(static_cast<DATEFORMAT>(Value));
}

/**************************************************************************//**
*
* \brief   - Below function returns time format value.
*
* \param   - None.
*
* \return  - m_TimeFormat.
******************************************************************************/
int DateTimeSettings::getTimeFormat()
{
    return (static_cast<int> (m_TimeFormat));
}

/**************************************************************************//**
*
* \brief   - Below function updates time format value.
*
* \param   - Value.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::setTimeFormat(int Value)
{
    m_DateTimeConversion->setTimeFormat(static_cast<TIMEFORMAT>(Value));
}

/**************************************************************************//**
*
* \brief   - Below function updates the date and time value.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void DateTimeSettings::onSettingsUpdated()
{
    QDate date (m_Year, m_Month, m_Day);
    QTime time (m_Hours, m_Minutes, m_Seconds);
    QDateTime dateTime(date, time);
    dateTime.setTimeSpec(Qt::UTC);
    m_DateTimeConversion->setDateTime(dateTime.toSecsSinceEpoch());
}

/**************************************************************************//**
* \brief   - OnDateTimeSettingsUpdated function updates epoch time fetch from ASC.
*            Which shall going to use for displaying it on screen.
*
* \param   - TBD
*
* \return  - TBD
******************************************************************************/
void DateTimeSettings::OnDateTimeSettingsUpdated(DateTimeConversion *DateTimeConversion_Obj, int WelderId)
{
    m_IsScreenReNavigated = false;
    m_ActiveWelderId = WelderId;

    m_DateTimeConversion = DateTimeConversion_Obj;
    m_LiveDateTime = m_DateTimeConversion->m_LiveDateTime;

    /*Convert the epoch string to a long integer*/
    m_DateTimeVal = static_cast<time_t>(std::atoll(m_LiveDateTime));

    m_Timeinfo = std::gmtime(&m_DateTimeVal);

    m_Year = m_Timeinfo->tm_year + 1900;  //tm_year gives years since 1900
    m_Month = m_Timeinfo->tm_mon + 1;     // tm_mon is 0-based (January is 0)
    m_Day = m_Timeinfo->tm_mday;
    m_Hours = m_Timeinfo->tm_hour;
    m_Minutes = m_Timeinfo->tm_min;
    m_Seconds = m_Timeinfo->tm_sec;

    if(m_DateTimeConversion->getDateFormat() != UNKNOWN_DATE_FORMAT)
    {
        m_DateFormat = m_DateTimeConversion->getDateFormat();
    }

    else
    {
        m_DateFormat = FORMAT_DDMMYYYY;
    }

    if(m_DateTimeConversion->getTimeFormat() != UNKONOWN_TIME_FORMAT)
    {
        m_TimeFormat = m_DateTimeConversion->getTimeFormat();
    }

    else
    {
        m_TimeFormat = FORMAT_TWELVE_HR;
    }

    if(m_Hours < 12)
    {
        m_Merediem = 0;
    }

    else
    {
        m_Merediem = 1;
    }

    emit dateTimeSettingsChanged();
}

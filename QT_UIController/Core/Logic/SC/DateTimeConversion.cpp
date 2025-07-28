/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DateTimeConversion related implementation
 
***************************************************************************/

#include <cstring>
#include "DateTimeConversion.h"
#include "DataLogger.h"

/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

DateTimeConversion::DateTimeConversion()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_InitiateDateTimeFormatSetting = false;
    m_InitiateDateTimeChangeRequest = false;
    m_DateTimeFormatReqdReq = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for DateTimeConversion details memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int DateTimeConversion::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_DATE_TIME_CONVERSION))
    {
        switch(destination->sub_id)
        {
        case SEND_DATE_TIME_FORMAT_FROM_HMI:
        {
            retVal = 0;
            sendDateTimeFormatRequest(destination);
            break;
        }
        case SEND_EPOCH_DATETIME_FROM_HMI:
        {
            retVal = 0;
            sendSetDateTimeOnAscRequest(destination);
            break;
        }
        case GET_DATE_TIME_FORMAT:
        {
            retVal = 0;
            sendDateTimeReadReq(destination);
            break;
        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"DateTimeConversion GetData default case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
            break;
        }
        }
    }
    else
    {
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"DateTimeConversion GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for DateTimeConversion
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int DateTimeConversion::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_DATE_TIME_CONVERSION))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case UPDATE_LIVE_DATE_TIME_ON_HMI:
            {
                retVal = 0;
                processLiveDateTimeResponse(source);
                break;
            }
            case GET_DATE_TIME_FORMAT:
            {
                retVal = 0;
                processDateTimeFormatonPowerUp(source);
                break;
            }
            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"DateTimeConversion SetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
                break;
            }
            }
        }
        else
        {
            retVal = 0;
        }
    }
    else
    {
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"DateTimeConversion SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Below function returns the date format value.
*
* \param   - None.
*
* \return  - m_DateFormat : The date format value.
******************************************************************************/
DATEFORMAT DateTimeConversion::getDateFormat()
{
    return m_DateFormat;
}

/**************************************************************************//**
*
* \brief   - Below function updates the date format value.
*
* \param   - Value : The date format value.
*
* \return  - None.
******************************************************************************/
void DateTimeConversion::setDateFormat(DATEFORMAT Value)
{
   m_DateFormat = Value;
   m_InitiateDateTimeFormatSetting = true;
}

/**************************************************************************//**
*
* \brief   - Below function returns the time format value.
*
* \param   - None.
*
* \return  - m_TimeFormat : The time format value.
******************************************************************************/
TIMEFORMAT DateTimeConversion::getTimeFormat()
{
    return m_TimeFormat;
}

/**************************************************************************//**
*
* \brief   - Below function updates the time format value.
*
* \param   - Value : The time format value.
*
* \return  - None.
******************************************************************************/
void DateTimeConversion::setTimeFormat(TIMEFORMAT Value)
{
    m_TimeFormat = Value;
    m_InitiateDateTimeFormatSetting = true;
}

/**************************************************************************//**
*
* \brief   - Below function updates the date and time value.
*
* \param   - Value : The date and time value.
*
* \return  - None.
******************************************************************************/
void DateTimeConversion::setDateTime(int Value)
{
    m_DateTime = Value;
    m_InitiateDateTimeChangeRequest = true;
}

/**************************************************************************//**
*
* \brief   - Send the Date Time Format details read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void DateTimeConversion::sendDateTimeFormatRequest(MEMORY_BLOCK * const destination)
{
    //Make sure sufficient buffer space is available to hold source DATEFORMAT and TIMEFORMAT
    if(destination->size >= sizeof(m_DateFormat) + sizeof(m_TimeFormat))
    {
        if(m_InitiateDateTimeFormatSetting == true)
        {
            //Store the source DATEFORMAT in memory block at offset 0.
            DATEFORMAT *DateFormatPtr = reinterpret_cast<DATEFORMAT *>(destination->data);
            *DateFormatPtr = m_DateFormat;
            //Store the destination TIMEFORMAT in memory block at offset sizeof(TIMEFORMAT).
            TIMEFORMAT *TimeFormatPtr = reinterpret_cast<TIMEFORMAT *>(destination->data + sizeof(m_DateFormat));
            *TimeFormatPtr = m_TimeFormat;
            destination->size = (sizeof(m_DateFormat) + sizeof(m_TimeFormat));
            destination->config = VALID_BIT;
            m_InitiateDateTimeFormatSetting = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }

}

/**************************************************************************//**
*
* \brief   - Process the current datetime from ASC
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
******************************************************************************/
void DateTimeConversion::processLiveDateTimeResponse(const MEMORY_BLOCK *const source)
{
    char* LiveDateTimePtr = reinterpret_cast< char*>(source->data );
    std::strncpy(m_LiveDateTime,  LiveDateTimePtr, DATE_SIZE_12_HR_FORMAT);
}

/**************************************************************************//**
*
* \brief   - Process the date , time format request coming from client e.g. ASC
*
* \param   - Mb - containig source data.
*
* \return  - none
*
******************************************************************************/
void DateTimeConversion::processDateTimeFormatonPowerUp(const MEMORY_BLOCK *const source)
{
    DATEFORMAT dateFormat = *reinterpret_cast<DATEFORMAT *>(source->data);
    TIMEFORMAT timeFormat = *reinterpret_cast<TIMEFORMAT *>(source->data + sizeof(DATEFORMAT));

    m_TimeFormat = timeFormat;	//Time format selected on HMI.
    m_DateFormat = dateFormat;	//Date Format selected on HMI.
}
/**************************************************************************//**
*
* \brief   - Send the DateTime Format  read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void DateTimeConversion::sendDateTimeReadReq(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_DateTimeFormatReqdReq == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_DateTimeFormatReqdReq = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_DATE_TIME_CONVERSION.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void DateTimeConversion::sendSetDateTimeOnAscRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >=sizeof(m_DateTime))
    {
        if(m_InitiateDateTimeChangeRequest)
        {
            // update size in destination
            destination->size = sizeof(m_DateTime);

            // set valid bit
            destination->config = VALID_BIT;

            int *DateTimePtr = reinterpret_cast<int *>(destination->data);

            *DateTimePtr= m_DateTime; //Send EPOCH DateTime value to ASC.

            m_InitiateDateTimeChangeRequest =false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}

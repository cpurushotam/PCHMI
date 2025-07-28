/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declaration of Date Time formats ,Enums and variables.

***************************************************************************/

#ifndef DATETIME_DEFINATIONS_H
#define DATETIME_DEFINATIONS_H

#include <iostream>
#include "Common_Definitions.h"
#include <cstring>

static constexpr char DDMMYYYY[DATEFORMAT_SIZE] = "%d/%m/%Y";
static constexpr char MMDDYYYY[DATEFORMAT_SIZE] = "%m/%d/%Y";
static constexpr char YYYYMMDD[DATEFORMAT_SIZE] = "%Y/%m/%d";

static constexpr char HHMMSS_24HOUR[TIMEFORMAT_SIZE] = "%H:%M:%S";
static constexpr char HHMMSS_12HOUR[TWELVEHRFORMAT_SIZE] = "%I:%M:%S %p";

// Declaration of Dateformat enum.
typedef enum
{
    FORMAT_DDMMYYYY ,
    FORMAT_MMDDYYYY,
    FORMAT_YYYYMMDD,
	UNKNOWN_DATE_FORMAT,
}DATEFORMAT;

// Declaration of Dateformat enum.
typedef enum
{
    FORMAT_TWELVE_HR,         //HH_MM_SS_AM/PM
    FORMAT_TWENTY_FOUR_HR  ,//HH_MM_SS
	UNKONOWN_TIME_FORMAT
}TIMEFORMAT;

typedef enum
{
	UPDATE_LIVE_DATE_TIME_ON_HMI,
    SEND_DATE_TIME_FORMAT_FROM_HMI,
    SEND_EPOCH_DATETIME_FROM_HMI,
    GET_DATE_TIME_FORMAT
}MB_DATE_TIME_SUB_ID ;


#endif // DATETIME_DEFINATIONS_H

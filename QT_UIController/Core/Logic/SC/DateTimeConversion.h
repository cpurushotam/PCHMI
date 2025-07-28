/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DateTimeConversion related implementation
 
***************************************************************************/

#ifndef DateTimeConversion_H_
#define DateTimeConversion_H_

#include "DataInterface.h"
#include "DateTime_Definations.h"

class DateTimeConversion : public DataInterface
{ 
public:
	
    DateTimeConversion();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    DATEFORMAT getDateFormat(void);
    void setDateFormat (DATEFORMAT Value);

    TIMEFORMAT getTimeFormat(void);
    void setTimeFormat (TIMEFORMAT Value);
    
    void setDateTime(int Value);
public:
    
    size_t m_LogID;

    bool m_InitiateDateTimeFormatSetting;
    DATEFORMAT m_DateFormat;
    TIMEFORMAT m_TimeFormat;

    int m_DateTime;
    bool m_InitiateDateTimeChangeRequest;
    bool m_DateTimeFormatReqdReq;

    char m_LiveDateTime[DATE_SIZE_12_HR_FORMAT];
    void sendDateTimeFormatRequest(MEMORY_BLOCK * const destination);
    void sendSetDateTimeOnAscRequest(MEMORY_BLOCK * const destination);
    void processLiveDateTimeResponse(const MEMORY_BLOCK *const source);
    void processDateTimeFormatonPowerUp(const MEMORY_BLOCK *const source);
    void sendDateTimeReadReq(MEMORY_BLOCK * const destination);

};

#endif /* DateTimeConversion_H_ */

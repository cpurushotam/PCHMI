/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares generic logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 09/02/2024 -  Initial version.

***************************************************************************/
#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "LoggerCommon.h"

typedef enum
{
	READ_LOGGER_DATA = 1,
}DATALOGGER_SUB_ID;

// Static configuration for buffer size used for logging
constexpr uint8_t buff_size_config = 100;
// Definition of logger class interface
class Logger
{
public:
    // std::map<size_t, const char*> ;
    template <typename T>
    static size_t enroll(const T *class_type);     	   /* user needs to enroll to use logging functionality, "enroll" returns the unique ID based on class type. */
    static int add_entry(E_SEVERITY severity,std::string data);

    static int  add_entry(LogEntry *log_entry);        /* use "add_entry" function to add new entry to log, requires unique id received during "enroll" */
    void EnableConsoleMode();
    void EnableMaintainanceMode();
    void DisableConsoleMode();
    void DisableMaintainanceMode();
private:
    static bool ConsoleModeEnabled;
    static bool m_MaintenanceMode;
     inline static LogEntry m_LogEntry;
};

/**************************************************************************//**
* \brief   - Implementation of logger enroll function
*
* \param   - const T *class_type - Type of class.
*
* \return  - Uniquely identify caller's object
*
******************************************************************************/
template <typename T>
size_t Logger::enroll(const T *class_type)
{
    // get hash code of the caller's object, we will use this to uniquely identify caller's object.
    std::size_t hash_code = typeid(*class_type).hash_code();

    // std::size_t hash_code1 = typeid(*class_type).name()
    return (hash_code);
}

#endif /* DATALOGGER_H_ */

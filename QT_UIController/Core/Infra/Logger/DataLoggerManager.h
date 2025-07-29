/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DataLogger header implementation

***************************************************************************/

#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <queue>
#include "DataInterface.h"

// Definition of DataLogger class
class DataLogger : public DataInterface
{
public:
    DataLogger();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    bool getDataLoggerUpdatedFlag();
    void setDataLoggerUpdatedFlag();
    std::queue<std::string> GetDataLoggerMessage();
private:
    void processDataLogFromASC(const MEMORY_BLOCK *const source);
    void printDataLog();

    //Holds Datalogger Message.
    std::queue<std::string> m_DataLoggerMsgs;
    //Flag to update once DataLogger message received.
    bool m_IsDataLoggerMsgUpdated;
};
#endif /* DATALOGGER_H*/

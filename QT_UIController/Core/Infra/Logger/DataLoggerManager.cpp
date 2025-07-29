/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DataLogger related implementation

***************************************************************************/

#include "DataLogger.h"
#include "DataLoggerManager.h"

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
DataLogger::DataLogger()
{
    //set m_IsDataLoggerMsgUpdated flag to false at power up
    m_IsDataLoggerMsgUpdated = false;
}

/**************************************************************************//**
*
* \brief   -  Implemented pure virtual function to avoid compilation error.
*             No need to actual implementation in to this.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int DataLogger::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC for memory block ID MB_ID_LOGGER_DATA
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int DataLogger::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_LOGGER_DATA) )
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                //Process response coming from ASC for Datalogger message
                case READ_LOGGER_DATA:
                {
                    retVal = 0;
                    processDataLogFromASC(source);
                    break;
                }

                default:
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DataLogger SetData default case");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "DataLogger SetData invalid request");
    }

    return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the DataLogger Message coming from ASC
*
* \param   - source - memory block holding the data logger message received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void DataLogger::processDataLogFromASC(const MEMORY_BLOCK *const source)
{
    char LoggerData[buff_size_config] = {0};
    //copy DataLogger message coming from Asc
    strncpy(LoggerData, reinterpret_cast<char*>(source->data), buff_size_config);
    std::string LoggerDataStr(LoggerData);
    //push data logger message in queue
    m_DataLoggerMsgs.push(LoggerDataStr);
    //update flag once DataLogger message recived from Asc
    m_IsDataLoggerMsgUpdated = true;
}

/**************************************************************************//**
*
* \brief   - Print Log Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void DataLogger::printDataLog()
{
    if(m_DataLoggerMsgs.empty())
    {
        std::cout << "No DataLogger Message Available" << std::endl;
    }
    else
    {
        std::cout << "**********DataLogger **********" << std::endl;
        while(!m_DataLoggerMsgs.empty())
        {
            std::string msg = m_DataLoggerMsgs.front();
            std::cout<<"DataLogger Msg : "<<msg<<std::endl;
            m_DataLoggerMsgs.pop();
        }
    }
}
/**************************************************************************//**
*
* \brief   - Update HMI if the DataLogger message is updated.
*
* \param   - none
*
* \return  - m_IsDataLoggerMsgUpdated.
*
******************************************************************************/
bool DataLogger::getDataLoggerUpdatedFlag()
{
    return m_IsDataLoggerMsgUpdated;
}

/**************************************************************************//**
*
* \brief   - Reset the flag to false after reading the data
*
* \param   - none
*
* \return  - none.
*
******************************************************************************/
void DataLogger::setDataLoggerUpdatedFlag()
{
    m_IsDataLoggerMsgUpdated = false;
    
    //Empty m_DataLoggerMsgs queue once data read
    while(!m_DataLoggerMsgs.empty())
    {
        m_DataLoggerMsgs.pop();
    }
}
/**************************************************************************//**
*
* \brief   - This method is used to get the DataLogger message update list.
*
* \param   - none
*
* \return  - std::queue<std::string> - DataLogger Message List.
*
******************************************************************************/
std::queue<std::string> DataLogger::GetDataLoggerMessage()
{
    return m_DataLoggerMsgs;
}

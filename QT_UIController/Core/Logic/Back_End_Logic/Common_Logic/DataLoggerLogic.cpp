/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DataLogger Logic related implementation
 ***************************************************************************/

#include <QDebug>
#include "DataLoggerLogic.h"
#include "UpdateScreens.h"
#include "DataLoggerManager.h"

/**************************************************************************//**
*
* \brief   - Constructor of DataLoggerLogic class.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
DataLoggerLogic::DataLoggerLogic(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::DataLoggerMessageUpdated, this, &DataLoggerLogic::OnDataLoggerMessageUpdated);
}

/**************************************************************************//**
*
* \brief  - This function return DataLogger Message list to qml.
*
* \param  - None.
*
* \return - QStringList - DataLogger Message list.
*
******************************************************************************/
QStringList DataLoggerLogic::getDataLoggerMessageList()
{
    return DataLoggerMsgList;
}
/*************************************************************************//**
* \brief   - Slot to initlaize the DataLogger class pointer to get DataLogger class data .
*
* \param   - DataLogger class pointer, Welder Id - Current welder Id.
*
* \return  - None.
*
******************************************************************************/
void DataLoggerLogic::OnDataLoggerMessageUpdated(DataLogger *DataLogger_Obj, int WelderId)
{
    DataLoggerPtr = DataLogger_Obj;

    if(DataLoggerPtr->getDataLoggerUpdatedFlag() == true)
    {
        DataLoggerMsgQueue = DataLoggerPtr->GetDataLoggerMessage();
        DataLoggerMsgList.clear();
        while(!DataLoggerMsgQueue.empty())
        {
            std::string DataLoggerMsgStr = DataLoggerMsgQueue.front();
            DataLoggerMsgList.append(QString::fromStdString(DataLoggerMsgStr));
            DataLoggerMsgQueue.pop();
        }
        emit dataLoggerMsgChanged();
        DataLoggerPtr->setDataLoggerUpdatedFlag();
    }
}

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares Branson System Configuration class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include<QString>
#include "BransonServiceInterface.h"
#include <ctime>

/**************************************************************************//**
*
* \brief  - BransonServiceInterface Constructor
*
* \param  - QObject *parent
*
* \return - None.
*
******************************************************************************/
BransonServiceInterface::BransonServiceInterface(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::BransonServiceDataUpdated, this, &BransonServiceInterface::OnBransonServiceInterfaceUpdated);
}

/**************************************************************************//**
*
* \brief  - send Factory Reset request to ASC.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::factoryResetRequest()
{
    m_BransonServiceTab->initiateFactoryResetRequest();
}

/**************************************************************************//**
*
* \brief  - sends Database delete request to ASC.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::dbDeleteRequest()
{
    m_BransonServiceTab->initiateDBDeleteRequest();
}

/**************************************************************************//**
*
* \brief  - send copy database files from Emmc1 to USB request to ASC.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::copyDbFilesToUSBRequest()
{
    m_BransonServiceTab->initiateCopyDBFilesToUSBRequest();
}

/**************************************************************************//**
*
* \brief  - send System Cleaned reques to ASC
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::systemCleanedRequest()
{
    m_BransonServiceTab->initiateSystemCleanedRequest();
}

/**************************************************************************//**
*
* \brief  - Used by QML to referesh screen on loading
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::serviceTabLoaded()
{
    emit servicenoteChanged();
}

/**************************************************************************//**
*
* \brief  - QML uses this function to known no. of characters user can enter via text.
*
* \param  - None.
*
* \return - int - SERVICENOTES_SIZE.
*
******************************************************************************/
int BransonServiceInterface::maxNotesChars()
{
    return SERVICENOTES_SIZE;
}

/**************************************************************************//**
*
* \brief  - QML uses this function to know EmmcMemoryUsage Details.
*
* \param  - None.
*
* \return - int.
*
******************************************************************************/
int BransonServiceInterface::emmcMemoryUsgae()
{
    return m_BransonServiceTab->getEmmcMemoryUsage();
}
/**************************************************************************//**
*
* \brief  - QML uses this function to know the no. of service notes available.
*
* \param  - None.
*
* \return - int.
*
******************************************************************************/
int BransonServiceInterface::getNofServiceNotes()
{
    return m_BransonServiceLogData.size();
}

/**************************************************************************//**
*
* \brief  - QML uses this function to fetch date and time of the particular service note to display.
*
* \param  - None.
*
* \return - QString NOte.
*
******************************************************************************/
QString BransonServiceInterface::getServiceNoteDateTime(int Idx)
{
    QString Note= "";
    for (unsigned int Index = 0; Index < m_BransonServiceLogData.size(); Index++)
    {
        if(Idx == Index)
        {
            Note =  m_BransonServiceLogData[Index].DateTime;
            break;
        }
    }
    return Note;
}
/**************************************************************************//**
*
* \brief  - QML uses this function to fetch Service note of the particular service note to display.
*
* \param  - None.
*
* \return - QString .
*
******************************************************************************/
QString BransonServiceInterface::getServiceNote(int Idx)
{
    QString DateTime= "";
    for (unsigned int Index = 0; Index < m_BransonServiceLogData.size(); Index++)
    {
        if(Idx == Index)
        {
            DateTime =  m_BransonServiceLogData[Index].ServiceNote;
            break;
        }
    }
    return DateTime;
}


/**************************************************************************//**
*
* \brief  - Used tgo display popup based on the response received from ASC.
*
* \param  - None.
*
* \return - QString.
*
******************************************************************************/
QString BransonServiceInterface::getServiceResponse()
{
    QString ServiceReqResp= "";

  m_ReceviedResponse = m_BransonServiceTab->GetBransonServiceRequestResponsecodes();

    for(auto it: BransonServiceErrorType)
    {
        if(it.first == m_ReceviedResponse)
        {
            ServiceReqResp = QString::fromStdString(it.second);
            break;
        }
    }

    return ServiceReqResp;
}

/**************************************************************************//**
*
* \brief  - Used to read the response received from ASC on HMI.
*
* \param  - None.
*
* \return - int  - m_ReceviedResponse.
*
******************************************************************************/
int BransonServiceInterface::getServiceResponseCode()
{
    return m_ReceviedResponse;
}

/**************************************************************************//**
*
* \brief  - Qml uses this function to fetch Board name from qml to c++.
*
* \param  - Qstring - OLdBoard name, QString - NewBoard Name.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface:: getOldBoardNewBoardName(const QString &OldBoardRevNo, const QString &NewBoardRevNo, const QString &NewBoardName)
{

    std::string OldBoardRev = OldBoardRevNo.toStdString();
    std::string NewBoardRev = NewBoardRevNo.toStdString();
    std::string BoardName = NewBoardName.toStdString();

    m_BransonServiceTab->GetOldBoardNewBoardName(OldBoardRev, NewBoardRev, BoardName);
}

/**************************************************************************//**
*
* \brief  - To service Service from QML to Memory Block.
*
* \param  - QString - Servicenote: NOte entered by user.
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::serviceNotesDetailsRequest(const QString& serviceNOte)
{
    std::string serviceNoteHMI = serviceNOte.toStdString();
    m_BransonServiceTab->getServiceNoteStructFromHMI(serviceNoteHMI);
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnBransonServiceInterfaceUpdated is to update values on Branson Service screen.
*
* \param  - BransonServiceTab_Obj : Object pointer of type BransonServiceTab.
*           welderId : welder id
*
* \return - None.
*
******************************************************************************/
void BransonServiceInterface::OnBransonServiceInterfaceUpdated(BransonServiceTab *BransonServiceTab_Obj, int welderId)
{
    m_BransonServiceTab = BransonServiceTab_Obj;

    if(m_BransonServiceTab->GetIsDataUpdated() || m_ActiveWelderId != welderId  )
    {
        m_BransonServiceLogData = m_BransonServiceTab->GetServiceLogs();
        emit servicenoteChanged();
        m_ActiveWelderId = welderId;
        m_BransonServiceTab->SetDataUpdatedFlag();
    }

    if(m_BransonServiceTab->GetIsEmmcMemoryUsageUpdated())
    {
        m_emmcMemUsage =  m_BransonServiceTab->getEmmcMemoryUsage();
        m_BransonServiceTab->SetEmmcMemoryUsageFlag();
        emit servicenoteChanged();
    }

    if(m_BransonServiceTab->GetBransonServiceStatusUpdate())
    {

        m_ReceviedResponse = m_BransonServiceTab->GetBransonServiceRequestResponsecodes();
        emit bransonServiceStatusMessage();
        m_BransonServiceTab->SetBransonServiceStatusUpdate();
    }
}

/**************************************************************************//**
*
* \brief  - To get EmmcMemory usage.
*
* \param  - none
*
* \return - m_emmcMemUsage.
*
******************************************************************************/
int BransonServiceInterface::getemmcMemUsage()
{
    return m_emmcMemUsage;
}

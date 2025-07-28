/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Global User Setting related implementation
 
***************************************************************************/

#include <cstring>
#include "SoftwareUpgrade.h"
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

SoftwareUpgrade::SoftwareUpgrade()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_SizeOfVectorStrings = 0;
    m_SendSoftwareUpgradeReadUSBRequest = false;
    m_SendSoftwareUpgradeRequest = false;
    m_isSoftwareUpgradeDataUpdated = false;
    m_isUSBRead = false;
    m_SoftwareUpgradeResult = SOFTWARE_UPGRADE_ERROR_UNKNOWN;
}

/**************************************************************************//**
*
* \brief   - destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
SoftwareUpgrade::~SoftwareUpgrade()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate SoftwareUpgrade Request
*
* \param   - SCFileName, ACFileName, HMIFileName - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::InitiateSoftwareUpgradeRequest(std::string SCFileName, std::string ACFileName, std::string HMIFileName)
{
    std::queue<SoftwareUpgradeStruct> SoftwareUpgradeEmptyData;
    //to clear the queue
    std::swap(m_SoftwareUpgradeData,SoftwareUpgradeEmptyData);

    SoftwareUpgradeStruct UpgradeFile;
    strncpy(UpgradeFile.SoftwareUpgradeFileName, SCFileName.c_str(), sizeof(SCFileName));
    m_SoftwareUpgradeData.push(UpgradeFile);
    strncpy(UpgradeFile.SoftwareUpgradeFileName, ACFileName.c_str(), sizeof(ACFileName));
    m_SoftwareUpgradeData.push(UpgradeFile);
    strncpy(UpgradeFile.SoftwareUpgradeFileName, HMIFileName.c_str(), sizeof(HMIFileName));
    m_SoftwareUpgradeData.push(UpgradeFile);

    ShowSoftwareUpgradeList();

    m_SendSoftwareUpgradeRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate read USB request
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::InitiateSoftwareUpgradeReadUSBRequest()
{
    m_SendSoftwareUpgradeReadUSBRequest = true;
}


/**************************************************************************//**
*
* \brief   - send the request to ASC server for Software Upgrade memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int SoftwareUpgrade::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_SOFTWARE_UPGRADE_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_USB_REQUEST:
        {
            retVal = 0;
            sendSoftwareUpgradeReadUSBRequest(destination);
            break;
        }

        case MB_UPGRADE_REQUEST:
        {
            retVal = 0;
            sendSoftwareUpgradeRequest(destination);
            break;
        }

        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SoftwareUpgrade GetData default case");
            break;
        }
        }
    }
    else
    {
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SoftwareUpgrade GetData invalid MB ID");
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for Software Upgrade memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SoftwareUpgrade::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_SOFTWARE_UPGRADE_DATA))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
                case MB_READ_USB_REQUEST:
                {
                    retVal = 0;
                    processSoftwareUpgradeReadUSBResponse(source);
                    break;
                }
                case MB_UPGRADE_REQUEST:
                {
                    retVal = 0;
                    processSoftwareUpgradeResponse(source);
                    break;
                }

                default:
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SoftwareUpgrade SetData default case");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "SoftwareUpgrade SetData invalid MB ID");
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the software upgrade read USB request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::sendSoftwareUpgradeReadUSBRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendSoftwareUpgradeReadUSBRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSoftwareUpgradeReadUSBRequest = false;
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
* \brief   - Send the software upgrade request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::sendSoftwareUpgradeRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= (sizeof(SoftwareUpgradeStruct) * m_SoftwareUpgradeData.size()))
    {
        if(m_SendSoftwareUpgradeRequest == true)
        {
            SoftwareUpgradeStruct *SoftwraeUpgradeFiles = reinterpret_cast<SoftwareUpgradeStruct *>(destination->data);
            int DataSize = 0;
            while (!m_SoftwareUpgradeData.empty())
            {
                *SoftwraeUpgradeFiles = m_SoftwareUpgradeData.front();
                m_SoftwareUpgradeData.pop();
                SoftwraeUpgradeFiles++;

                DataSize += sizeof(SoftwareUpgradeStruct);
            }
            destination->size = DataSize;

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSoftwareUpgradeRequest = false;
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
* \brief   - Process software upgrade read USB data coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::processSoftwareUpgradeReadUSBResponse(const MEMORY_BLOCK *const source)
{
    int *NumberOfFilesRead = reinterpret_cast<int *>(source->data);
    SoftwareUpgradeStruct *Data = reinterpret_cast<SoftwareUpgradeStruct *>(source->data + sizeof(int));
    std::queue<SoftwareUpgradeStruct> SoftwareUpgradeEmptyData;
    //to clear the queue
    std::swap(m_SoftwareUpgradeData,SoftwareUpgradeEmptyData);

    for(int FileNumber = 0; FileNumber < *NumberOfFilesRead; FileNumber++)
    {
        SoftwareUpgradeStruct FileName;
        strncpy(FileName.SoftwareUpgradeFileName, Data->SoftwareUpgradeFileName, sizeof(FileName.SoftwareUpgradeFileName));
        m_SoftwareUpgradeData.push(FileName);
        Data++;
    }
    m_isUSBRead = true;
}

/**************************************************************************//**
*
* \brief   - Process the software upgrade response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::processSoftwareUpgradeResponse(const MEMORY_BLOCK *const source)
{
    int *Data = reinterpret_cast<int *>(source->data);
    memcpy(&m_SoftwareUpgradeResult,Data,sizeof(int));
    m_isSoftwareUpgradeDataUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show Global User Setting details        
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SoftwareUpgrade::ShowSoftwareUpgradeList()
{
    std::queue<SoftwareUpgradeStruct> tempQueue = m_SoftwareUpgradeData;
    while (!tempQueue.empty())
    {
        SoftwareUpgradeStruct ReadUsbFiles = tempQueue.front();
        tempQueue.pop();
        std::cout << "FileName : "<< ReadUsbFiles.SoftwareUpgradeFileName << std::endl;
    }
}

/**************************************************************************//**
*
* \brief   - return Read USB status
*
* \param   - none
*
* \return  - bool - m_isUSBRead
*
******************************************************************************/
bool SoftwareUpgrade::GetReadUSBStatus()
{
    return m_isUSBRead;
}

/**************************************************************************//**
*
* \brief   - return Global User Setting AutoLogin User Name
*
* \param   - none
*
* \return  - bool - AutoLoginStatus
*
******************************************************************************/
bool SoftwareUpgrade::GetSoftwareUpgradeStatus()
{
    return m_isSoftwareUpgradeDataUpdated;
}

/**************************************************************************//**
*
* \brief   - return the copy of global user setting structure data
*
* \param   - none

* \return  - copy of global user setting structure data
*
******************************************************************************/
std::queue<SoftwareUpgradeStruct> SoftwareUpgrade::GetReadUSBData()
{
    std::queue<SoftwareUpgradeStruct> ReadUSBData;
    ReadUSBData = m_SoftwareUpgradeData;
    //Reset the flag to false once the value is read
    m_isUSBRead = false;

    return ReadUSBData;
}

/**************************************************************************//**
*
* \brief   - return the copy of user data updated error code
*
* \param   - none

* \return  - copy of user data updated error code
*
******************************************************************************/
SOFTWARE_UPGRADE_ERROR_CODES SoftwareUpgrade::GetSoftwareUpgradeErrorCode()
{
    SOFTWARE_UPGRADE_ERROR_CODES SoftwareUpgradeResult = m_SoftwareUpgradeResult;
    m_isSoftwareUpgradeDataUpdated = false;
    return SoftwareUpgradeResult;
}

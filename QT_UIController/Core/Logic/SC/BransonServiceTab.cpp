/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Branson Service related implementation
 
***************************************************************************/

#include <cstring>
#include "BransonServiceTab.h"
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

BransonServiceTab::BransonServiceTab()
{
    m_FactoryResetRequest =false;
    m_DeleteDBRequest= false;
    m_BoardReplaced= false;
    m_SystemCleaned= false;
    m_AddNoteRequest= false;
    m_ServiceHistorySampleNumberToRead =0;
    m_SendServiceNotesReadReq = true;
    m_IsServiceLogDataUpdated =false;
    m_IsEmmcMemoryUsageFlag = false;
    m_IsBransonServiceStatusUpdated =false;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for BransonServiceTab memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int BransonServiceTab::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_BRANSON_SERVICE))
    {
        switch(destination->sub_id)
        {
        case FACTORY_RESET_REQUEST:
        {
            retVal = 0;
           sendFactoryResetRequestFromHMI(destination);
            break;
        }

        case DB_DELETE_REQUEST:
        {
            retVal = 0;
            sendDeleteDBRequestFromHMI(destination);
            break;
        }
        case DB_COPY_TO_USB_REQUEST:
        {
            retVal = 0;
             sendCopyDBtoUSBRequestFromHMI(destination);
            break;
        }

        case BOARD_REPLACED_REQUEST:
        {
            retVal = 0;
             sendBoardReplacedRequestFromHMI(destination);
            break;
        }
        case SYSTEM_CLEANED_REQUEST:
        {
            retVal = 0;
             sendSystemCleanRequestFromHMI(destination);
            break;
        }
        case ADD_SERVICE_NOTES_REQUEST:
        {
            retVal = 0;
             sendAddNoteRequestFromHMI(destination);
            break;
        }
        case READ_SERVICE_LOG:
        {
            retVal = 0;
            sendHistoricalServiceNoteReadReq(destination);
            break;

        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"BransonServiceTab GetData default case");
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
        snprintf(msg,buff_size_config,"BransonServiceTab GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for BransonServiceTab memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int BransonServiceTab::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_BRANSON_SERVICE))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case EMMC_MEMORY_USAGE:
            {
                retVal = 0;
                processEmmcUsageDeatilsResponse(source);
                break;
            }

            case SEND_REQUEST_STATUS:
            {
                retVal = 0;
                processBransonServiceRequestResponse(source);
                break;
            }
            case READ_SERVICE_LOG:
            {
                retVal = 0;
                processHistoricalServiceLogDataFromASC(source);
                break;
            }
            case SYNC_SERVICE_LOG:
            {
                retVal = 0;
                processServiceLogDataFromASConDateTimeFormatChange();
                break;
            }
            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"BransonServiceTab SetData default case");
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
        snprintf(msg,buff_size_config,"BransonServiceTab SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the BransonServiceTab Factory Reset request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendFactoryResetRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_FactoryResetRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_FactoryResetRequest = false;
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
* \brief   - Send the BransonServiceTab DB Delete request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendDeleteDBRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_DeleteDBRequest == true)
        {

            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_DeleteDBRequest = false;
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
* \brief   - Send the BransonServiceTab COpy db files request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendCopyDBtoUSBRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_DbCopyEmmctoUSB == true)
        {

            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_DbCopyEmmctoUSB = false;
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
* \brief   - Send the BransonServiceTab Board Replaced request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendBoardReplacedRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= (sizeof(m_oldBoardRevNo) + sizeof(m_newBoardRevNo) + sizeof(m_boardName)))
    {
        if(m_BoardReplaced == true)
        {
            strncpy(reinterpret_cast<char*>(destination->data), m_newBoardRevNo, BOARD_NAME_SIZE);
            strncpy(reinterpret_cast<char*>(destination->data + sizeof(m_newBoardRevNo)), m_oldBoardRevNo, BOARD_NAME_SIZE);
            strncpy(reinterpret_cast<char*>(destination->data + sizeof(m_newBoardRevNo) + sizeof(m_oldBoardRevNo)), m_boardName, BOARD_NAME_SIZE);


            destination->size = sizeof(m_newBoardRevNo) + sizeof(m_oldBoardRevNo) + sizeof(m_boardName);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_BoardReplaced = false;
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
* \brief   - Send the BransonServiceTab  System Cleaned request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendSystemCleanRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SystemCleaned == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SystemCleaned = false;
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
* \brief   - Send the Add note request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendAddNoteRequestFromHMI(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_ServiceNote))
    {
        if(m_AddNoteRequest == true)
        {
            char *Data = reinterpret_cast<char *>(destination->data);
            memcpy(Data,&m_ServiceNote,sizeof(m_ServiceNote));

            destination->size = sizeof(m_ServiceNote);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_AddNoteRequest = false;
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
* \brief   - Send the BransonServiceTab Service NOtes historical data read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::sendHistoricalServiceNoteReadReq(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if(m_SendServiceNotesReadReq == true)
        {
            int *Data = reinterpret_cast<int *>(destination->data);
            *Data = m_ServiceHistorySampleNumberToRead;
            destination->size = sizeof(int);
            destination->config = VALID_BIT;
            m_SendServiceNotesReadReq = false;
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
* \brief   - process the historical Service log data coming from ASC
*
* \param   - source - memory block holding the historical event log data
*			 received from ASC
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::processHistoricalServiceLogDataFromASC(const MEMORY_BLOCK *const source)
{
    int TotalSamples = *reinterpret_cast< int*>(source->data);
    bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int));
    BransonServiceTabStructure* ServiceLogData = reinterpret_cast< BransonServiceTabStructure*>(source->data + sizeof(int) + sizeof(bool));

    for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
    {
        m_BransonServiceLogTabData.push_back(*ServiceLogData);
        ServiceLogData++;
    }

    m_ServiceHistorySampleNumberToRead = m_ServiceHistorySampleNumberToRead + TotalSamples;

    if(IsCompleteDataRead == true)
    {
        m_ServiceHistorySampleNumberToRead = 0;
        m_SendServiceNotesReadReq = false;
        m_IsServiceLogDataUpdated =true;
    }
    else
    {
        m_SendServiceNotesReadReq = true;
    }
}

/**************************************************************************//**
*
* \brief   - process the EmmcMemory Usage data coming from ASC
*
* \param   - source - memory block holding the  data
*			 received from ASC
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::processEmmcUsageDeatilsResponse(const MEMORY_BLOCK *const source)
{
    int* EmmcMemoryUsagePtr = reinterpret_cast< int*>(source->data );
    m_EmmcMemoryUsage = * EmmcMemoryUsagePtr;
    m_IsEmmcMemoryUsageFlag = true;
}

/**************************************************************************//**
*
* \brief   - process the BransonService Responses from ASC
*
* \param   - source - memory block holding the Response data for BransonService.
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::processBransonServiceRequestResponse(const MEMORY_BLOCK *const source)
{
    m_ServiceResponse = *reinterpret_cast<BRANSON_SERVICE_REQUESTS_RESPONSE_CODES *>(source->data);
    m_IsBransonServiceStatusUpdated = true;
}

/**************************************************************************//**
*
* \brief   - process the Service log read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::processServiceLogDataFromASConDateTimeFormatChange()
{
    m_BransonServiceLogTabData.clear();
    m_ServiceHistorySampleNumberToRead = 0;
    m_SendServiceNotesReadReq = true;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press Factory Reset button
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void BransonServiceTab::initiateFactoryResetRequest()
{
     m_FactoryResetRequest = true;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press DB Delete button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void BransonServiceTab::initiateDBDeleteRequest()
{

    m_DeleteDBRequest =true;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press Copy button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void BransonServiceTab::initiateCopyDBFilesToUSBRequest()
{
    m_DbCopyEmmctoUSB = true;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you press System Cleaned button on HMI.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void BransonServiceTab::initiateSystemCleanedRequest()
{

    m_SystemCleaned =true;
}

/**************************************************************************//**
*
* \brief   - Method used to fetch the note entered on hmi.
*
* \param   - std::string serviceNote : note entered by user.
*
* \return  - None
*
******************************************************************************/

void BransonServiceTab:: getServiceNoteStructFromHMI(std::string &serviceNote)
{
    strncpy(m_ServiceNote, serviceNote.c_str(),SERVICENOTES_SIZE);
    m_AddNoteRequest = true;
    m_BransonServiceLogTabData.clear();
}

/**************************************************************************//**
*
* \brief   - Method used to fetch Old and New board name from HMI.
*
* \param   - std::string oldboard, std::string newboard.
*
* \return  - None
*
******************************************************************************/

void BransonServiceTab::GetOldBoardNewBoardName(std::string &oldboard, std::string &newboard, std::string &boardName)
{
    strncpy(m_oldBoardRevNo, oldboard.c_str(),SERVICENOTES_SIZE);
    strncpy(m_newBoardRevNo, newboard.c_str(),SERVICENOTES_SIZE);
    strncpy(m_boardName, boardName.c_str(),SERVICENOTES_SIZE);

    m_BoardReplaced = true;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when EmmcMemoryUsage detail is required.
*
* \param   - None.
*
* \return  - int
*
******************************************************************************/

int BransonServiceTab::getEmmcMemoryUsage()
{
    return m_EmmcMemoryUsage;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI to display the error codes on HMI.
*
* \param   - None.
*
* \return  - BRANSON_SERVICE_REQUESTS_RESPONSE_CODES
*
******************************************************************************/
BRANSON_SERVICE_REQUESTS_RESPONSE_CODES BransonServiceTab::GetBransonServiceRequestResponsecodes()
{
    return m_ServiceResponse;
}
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you need to display Service notes
*
* \param   - None.
*
* \return  - std::deque<BransonServiceTabStructure>
*
******************************************************************************/

 std::deque<BransonServiceTabStructure> BransonServiceTab::GetServiceLogs()
{
    return m_BransonServiceLogTabData;
}


/**************************************************************************//**
*
* \brief   - call this method on HMI side when Service logs are updated.
*
* \param   - None.
*
* \return  - m_IsServiceLogDataUpdated
*
******************************************************************************/
bool  BransonServiceTab::GetIsDataUpdated()
{
    return m_IsServiceLogDataUpdated;
}

/**************************************************************************//**
*
* \brief   - Set the flag to false after updateing data.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void BransonServiceTab::SetDataUpdatedFlag()
{
    m_IsServiceLogDataUpdated = false;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when EmmcMemory Details are available.
*
* \param   - None.
*
* \return  - m_IsEmmcMemoryUsageFlag
*
******************************************************************************/

bool  BransonServiceTab::GetIsEmmcMemoryUsageUpdated()
{
    return m_IsEmmcMemoryUsageFlag;
}

/**************************************************************************//**
*
* \brief   - Set the flag to false once data is updated.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void BransonServiceTab::SetEmmcMemoryUsageFlag()
{
    m_IsEmmcMemoryUsageFlag = false;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when response is received from ASC.
*
* \param   - None.
*
* \return  - m_IsBransonServiceStatusUpdated
*
******************************************************************************/
bool  BransonServiceTab::GetBransonServiceStatusUpdate()
{
    return m_IsBransonServiceStatusUpdated;
}

/**************************************************************************//**
*
* \brief   - Set the flag to false once data is updated.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/

void BransonServiceTab::SetBransonServiceStatusUpdate()
{
    m_IsBransonServiceStatusUpdated = false;
}

/**************************************************************************//**
*
* \brief   - Print Historical Service Log Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void BransonServiceTab::printHistoricalServiceLog()
{
    if(m_BransonServiceLogTabData.empty())
    {
        std::cout << "No Historical Service log Available" << std::endl;
    }
    else
    {
        std::cout << "**********Historical Service Log Data**********" << std::endl;
        for (unsigned int Index = 0; Index < m_BransonServiceLogTabData.size(); Index++)
        {
            std::cout << "ServiceNote: " << m_BransonServiceLogTabData[Index].ServiceNote << std::endl;
            std::cout << "DateTime: " << m_BransonServiceLogTabData[Index].DateTime << std::endl;
            std::cout << "*************************************" << std::endl;
        }
    }
}

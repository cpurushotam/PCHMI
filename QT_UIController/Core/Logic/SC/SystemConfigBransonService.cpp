/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the System Configuration Branson Service related implementation
 
***************************************************************************/

#include <cstring>
#include "SystemConfigBransonService.h"
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

SystemConfigBransonService::SystemConfigBransonService()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_SendSystemConfigBransonServiceReadRequest = true;
    m_SendSystemConfigBransonServiceUpdateRequest = false;
    m_isSystemConfigBransonServiceUpdated = false;
    m_SystemConfigBransonServiceUpdateResult = UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_UNKNOWN;
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
SystemConfigBransonService::~SystemConfigBransonService()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate system config branson service Update Request
*
* \param   - SystemConfigBransonServiceData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::InitiateSystemConfigBransonServiceUpdateRequest(SystemConfigBransonServiceStruct SystemConfigBransonServiceData)
{
    m_BransonServiceData = SystemConfigBransonServiceData;
    m_SendSystemConfigBransonServiceUpdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for system config branson service memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int SystemConfigBransonService::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST:
        {
            retVal = 0;
            sendSystemConfigBransonServiceReadRequest(destination);
            break;
        }

        case MB_UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST:
        {
            retVal = 0;
            sendSystemConfigBransonServiceUpdateRequest(destination);
            break;
        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"SystemConfigBransonService GetData default case");
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
        snprintf(msg,buff_size_config,"SystemConfigBransonService GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for system config branson service memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SystemConfigBransonService::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case MB_READ_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST:
            {
                retVal = 0;
                processSystemConfigBransonServiceReadResponse(source);
                break;
            }
            case MB_UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST:
            {
                retVal = 0;
                processSystemConfigBransonServiceUpdateResponse(source);
                break;
            }

            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"SystemConfigBransonService SetData default case");
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
        snprintf(msg,buff_size_config,"SystemConfigBransonService SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the system configuration branson service read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::sendSystemConfigBransonServiceReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendSystemConfigBransonServiceReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSystemConfigBransonServiceReadRequest = false;
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
* \brief   - Send the system configuration branson service update request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::sendSystemConfigBransonServiceUpdateRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_BransonServiceData))
    {
        if(m_SendSystemConfigBransonServiceUpdateRequest == true)
        {
            SystemConfigBransonServiceStruct *Data = reinterpret_cast<SystemConfigBransonServiceStruct *>(destination->data);
            memcpy(Data,&m_BransonServiceData,sizeof(m_BransonServiceData));

            destination->size = sizeof(m_BransonServiceData);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSystemConfigBransonServiceUpdateRequest = false;
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
* \brief   - Process the system configuration branson service coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::processSystemConfigBransonServiceReadResponse(const MEMORY_BLOCK *const source)
{
    SystemConfigBransonServiceStruct *Data = reinterpret_cast<SystemConfigBransonServiceStruct *>(source->data);
    memcpy(&m_BransonServiceData,Data,sizeof(SystemConfigBransonServiceStruct));
}

/**************************************************************************//**
*
* \brief   - Process the system configuration branson service update response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::processSystemConfigBransonServiceUpdateResponse(const MEMORY_BLOCK *const source)
{
    int *Data = reinterpret_cast<int *>(source->data);
    memcpy(&m_SystemConfigBransonServiceUpdateResult,Data,sizeof(int));
    m_isSystemConfigBransonServiceUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show system configuration branson service details
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SystemConfigBransonService::ShowSystemConfigBransonService()
{
    std::cout << "m_BransonServiceData.MachineSerialNumber: "  << m_BransonServiceData.MachineSerialNumber << std::endl;
    std::cout << "m_BransonServiceData.PowerSupplySerialNumber: "  << m_BransonServiceData.PowerSupplySerialNumber << std::endl;
    std::cout << "m_BransonServiceData.ActuatorSerialNumber: "  << m_BransonServiceData.ActuatorSerialNumber << std::endl;
}

/**************************************************************************//**
*
* \brief   - return system configuration branson service updated details
*
* \param   - none
*
* \return  - bool - m_isSystemConfigBransonServiceUpdated
*
******************************************************************************/
bool SystemConfigBransonService::GetSystemConfigBransonServiceUpdateStatus()
{
    return m_isSystemConfigBransonServiceUpdated;
}

/**************************************************************************//**
*
* \brief   - return the copy of system configuration branson service structure data
*
* \param   - none

* \return  - copy of system configuration branson service structure data
*
******************************************************************************/
SystemConfigBransonServiceStruct SystemConfigBransonService::GetSystemConfigBransonServiceData()
{
    SystemConfigBransonServiceStruct SystemConfigBransonServiceData = m_BransonServiceData;
    //Reset the flag to false once the value is read
    m_isSystemConfigBransonServiceUpdated = false;

    return SystemConfigBransonServiceData;
}

/**************************************************************************//**
*
* \brief   - return the copy of Branson system config data updated error code
*
* \param   - none

* \return  - copy of Branson system config data updated error code
*
******************************************************************************/
UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES SystemConfigBransonService::GetSystemConfigBransonServiceUpdatedErrorCode()
{
    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES SystemConfigBransonServiceUpdateResult = m_SystemConfigBransonServiceUpdateResult;
    return SystemConfigBransonServiceUpdateResult;
}

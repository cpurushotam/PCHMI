/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Config Utility Version related implementation

***************************************************************************/
#include <string.h>
#include "ConfigUtilityVersion.h"
#include "DataLogger.h"

size_t ConfigUtilityVersion::log_id = 0;

/******************************************************************************//**
* \brief - Constructor.
*
* \param - None.
*
* \return - None.
*
******************************************************************************/
ConfigUtilityVersion::ConfigUtilityVersion()
{
    //enroll to use logger functionality
    log_id = Logger::enroll(this);
    m_InitiateConfigUtilityVersionReadReq = true;
    m_IsConfigVersionAvailable = false;
}

/**************************************************************************//**
*
* \brief   - GetData Interface implementation for Config Utility Version data.
*           
* \param   - Address of destination Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ConfigUtilityVersion::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_CONFIG_UTILITY_VERSION_DATA))
    {
        // perform operation based on sub id
        switch(destination->sub_id)
        {
            case CONFIG_UTILITY_VERSION_DATA:
            {
                retVal = 0;
                SendConfigUtilityVersionReadRequestToASC(destination);
                break;
            }

            default:
            {
                // Error ! default retVal (failure) will be returned
                // clear valid bit, reset size
                destination->size = 0;
                // clear valid bit
                destination->config = 0;
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ConfigUtilityVersion:GetData default");
                break;
            }
        }
    }
    else
    {
        // error! invalid memory block id, default retVal (failure) will be returned
        // clear valid bit, reset size
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ConfigUtilityVersion:GetData invalid req");

    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - SetData Interface implementation for Config Utility Version data.
*
* \param   - Address of source Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ConfigUtilityVersion::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_CONFIG_UTILITY_VERSION_DATA))
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            // perform operation based on sub id
            switch(source->sub_id)
            {
                case CONFIG_UTILITY_VERSION_DATA:
                {
                    retVal =0;
                    ProcessConfigUtilityVersionData(source);
                    break;
                }
                default:
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ConfigUtilityVersion:SetData default");
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
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "ConfigUtilityVersion:SetData invalid req");
    }

    return (retVal);
}

/**************************************************************************//**
*
* \brief   - To receive data from ASC for Sub-Id CONFIG_UTILITY_VERSION_DATA
*
* \param   - source - Memory block containing data from ASC
*
* \return  - None
*
******************************************************************************/
void ConfigUtilityVersion::ProcessConfigUtilityVersionData(const MEMORY_BLOCK * const source)
{
    char ConfigUtilityVersionData[CONFIG_UTILITY_VERSION_SIZE] = {0};
    //copy Config Utility Version data coming from Asc
    strncpy(ConfigUtilityVersionData, reinterpret_cast<char*>(source->data), CONFIG_UTILITY_VERSION_SIZE);
    // Copy data into the member variable
    m_ConfigUtilityVersionData = std::string(ConfigUtilityVersionData);
    m_IsConfigVersionAvailable = true;
}

/**************************************************************************//**
*
* \brief   - Send a Config Utility Version request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void ConfigUtilityVersion::SendConfigUtilityVersionReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateConfigUtilityVersionReadReq == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateConfigUtilityVersionReadReq = false;
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
* \brief   - This function Return config utility version Number
*
* \param   - none
*
* \return  -  std::string - config utility version Number
*
******************************************************************************/
std::string ConfigUtilityVersion::GetConfigUtilityVersionNumber()
{
    return m_ConfigUtilityVersionData;
}


/**************************************************************************//**
*
* \brief   - This function is used to reset m_IsConfigVersionAvailable flag
*
* \param   - none
*
* \return  -  none
*
******************************************************************************/
void ConfigUtilityVersion::SetIsConfigVersionAvailable()
{
    m_IsConfigVersionAvailable = false;
}

/**************************************************************************//**
*
* \brief   - This function Return IsConfigVersionAvailable status
*
* \param   - none
*
* \return  -  bool - m_IsConfigVersionAvailable update status
*
******************************************************************************/
bool  ConfigUtilityVersion::GetIsConfigVersionAvailable()
{
    return m_IsConfigVersionAvailable;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the network configuration related implementation
 
***************************************************************************/

#include <cstring>
#include "NetworkConfiguration.h"
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

NetworkConfiguration::NetworkConfiguration()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_SendNetworkConfigReadRequest = true;
    m_SendNetworkConfigUpdateRequest = false;
    m_isNetworkConfigUpdated = false;
    m_SendNetworkConfigResetRequest = false;
    m_isNetworkConfigReadData = false;
    m_NetworkConfigUpdateResult = UPDATE_NETWORK_CONFIG_ERROR_UNKNOWN;
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
NetworkConfiguration::~NetworkConfiguration()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Network Configuration Update Request
*
* \param   - NetworkConfigurationData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::InitiateNetworkConfigurationUpdateRequest(NetworkConfigurationStruct NetworkConfigurationData)
{
    m_NetworkConfigData = NetworkConfigurationData;
    m_SendNetworkConfigUpdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Network Configuration Reset Request
*
* \param   - NetworkConfigurationData - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::InitiateNetworkConfigurationResetRequest()
{
    m_SendNetworkConfigResetRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for network configuration memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int NetworkConfiguration::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_NETWORK_CONFIGURATION_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationReadRequest(destination);
            break;
        }

        case MB_UPDATE_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationUpdateRequest(destination);
            break;
        }

        case MB_RESET_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationResetRequest(destination);
            break;
        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"NetworkConfiguration GetData default case");
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
        snprintf(msg,buff_size_config,"NetworkConfiguration GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for network configuration memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int NetworkConfiguration::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_NETWORK_CONFIGURATION_DATA))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case MB_READ_NETWORK_CONFIGURATION_REQUEST:
            {
                retVal = 0;
                processNetworkConfigurationReadResponse(source);
                break;
            }
            case MB_RESET_NETWORK_CONFIGURATION_REQUEST:
            case MB_UPDATE_NETWORK_CONFIGURATION_REQUEST:
            {
                retVal = 0;
                processNetworkConfigurationUpdateResponse(source);
                break;
            }

            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"NetworkConfiguration SetData default case");
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
        snprintf(msg,buff_size_config,"NetworkConfiguration SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the network configuration read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::sendNetworkConfigurationReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendNetworkConfigReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendNetworkConfigReadRequest = false;
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
* \brief   - Send the network configuration update request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::sendNetworkConfigurationUpdateRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_NetworkConfigData))
    {
        if(m_SendNetworkConfigUpdateRequest == true)
        {
            NetworkConfigurationStruct *Data = reinterpret_cast<NetworkConfigurationStruct *>(destination->data);
            memcpy(Data,&m_NetworkConfigData,sizeof(m_NetworkConfigData));

            destination->size = sizeof(m_NetworkConfigData);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendNetworkConfigUpdateRequest = false;
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
* \brief   - Send the network configuration reset to default request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::sendNetworkConfigurationResetRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendNetworkConfigResetRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendNetworkConfigResetRequest = false;
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
* \brief   - Process the network configuration coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::processNetworkConfigurationReadResponse(const MEMORY_BLOCK *const source)
{
    NetworkConfigurationStruct *Data = reinterpret_cast<NetworkConfigurationStruct *>(source->data);
    memcpy(&m_NetworkConfigData,Data,sizeof(NetworkConfigurationStruct));
    m_isNetworkConfigReadData = true;
}

/**************************************************************************//**
*
* \brief   - Process the network configuration response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::processNetworkConfigurationUpdateResponse(const MEMORY_BLOCK *const source)
{
    int *Data = reinterpret_cast<int *>(source->data);
    memcpy(&m_NetworkConfigUpdateResult,Data,sizeof(int));
    m_isNetworkConfigUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show network configuration details
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void NetworkConfiguration::ShowNetworkConfiguration()
{
    std::cout << "m_NetworkConfigData.IpSetupIPConfig: "  << m_NetworkConfigData.IpSetupIPConfig << std::endl;
    std::cout << "m_NetworkConfigData.IpSetupIPAdress: "  << m_NetworkConfigData.IpSetupIPAdress << std::endl;
    std::cout << "m_NetworkConfigData.IpSetupSubnetMask: "  << m_NetworkConfigData.IpSetupSubnetMask << std::endl;
    std::cout << "m_NetworkConfigData.IpSetupDefaultGateway: "  << m_NetworkConfigData.IpSetupDefaultGateway << std::endl;

}

/**************************************************************************//**
*
* \brief   - return network configuration updated details
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigUpdated
*
******************************************************************************/
bool NetworkConfiguration::GetNetworkConfigurationUpdateStatus()
{
    return m_isNetworkConfigUpdated;
}

/**************************************************************************//**
*
* \brief   - reset network configuration updated details
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigUpdated
*
******************************************************************************/
void NetworkConfiguration::ResetNetworkConfigurationUpdateStatus()
{
    m_isNetworkConfigUpdated = false;
}

/**************************************************************************//**
*
* \brief   - return the copy of network configuration structure data
*
* \param   - none

* \return  - copy of network configurationstructure data
*
******************************************************************************/
NetworkConfigurationStruct NetworkConfiguration::GetNetworkConfigurationData()
{
    NetworkConfigurationStruct NetworkConfigurationData = m_NetworkConfigData;
    //Reset the flag to false once the value is read
    m_isNetworkConfigUpdated = false;
    m_isNetworkConfigReadData = false;

    return NetworkConfigurationData;
}

/**************************************************************************//**
*
* \brief   - return the copy of network configuration error code
*
* \param   - none

* \return  - copy of network configuration updated error code
*
******************************************************************************/
NETWORK_CONFIG_ERROR_CODES NetworkConfiguration::GetNetworkConfigurationUpdatedErrorCode()
{
    NETWORK_CONFIG_ERROR_CODES NetworkConfigUpdateResult = m_NetworkConfigUpdateResult;
    return NetworkConfigUpdateResult;
}

/**************************************************************************//**
*
* \brief   - return network configuration read data
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigReadData
*
******************************************************************************/
bool NetworkConfiguration::GetNetworkConfigurationReadData()
{
    return m_isNetworkConfigReadData;
}

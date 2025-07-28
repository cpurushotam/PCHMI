/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the network configuration INdustrial EIP related implementation
 
***************************************************************************/

#include <cstring>
#include "NetworkConfigurationEthernetIp.h"
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

NetworkConfigurationEthernetIp::NetworkConfigurationEthernetIp()
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
NetworkConfigurationEthernetIp::~NetworkConfigurationEthernetIp()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Network Configuration Update Request
*
* \param   - NetworkConfigurationEthernetIpStruct - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::InitiateNetworkConfigurationEthernetIpUpdateRequest(NetworkConfigurationEthernetIpStruct NetworkConfigurationEthernetIpData)
{
    m_NetworkConfigData = NetworkConfigurationEthernetIpData;
    m_SendNetworkConfigUpdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate Network Configuration EthernetIp Reset Request
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::InitiateNetworkConfigurationEthernetIpResetRequest()
{
    m_SendNetworkConfigResetRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for network configuration  EthernetIp memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int NetworkConfigurationEthernetIp::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationEthernetIpReadRequest(destination);
            break;
        }

        case MB_UPDATE_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationEthernetIpUpdateRequest(destination);
            break;
        }

        case MB_RESET_NETWORK_CONFIGURATION_REQUEST:
        {
            retVal = 0;
            sendNetworkConfigurationEthernetIpResetRequest(destination);
            break;
        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"NetworkConfigurationEthernetIp GetData default case");
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
        snprintf(msg,buff_size_config,"NetworkConfigurationEthernetIp GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for network configuration  EthernetIp memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int NetworkConfigurationEthernetIp::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case MB_READ_NETWORK_CONFIGURATION_REQUEST:
            {
                retVal = 0;
                processNetworkConfigurationEthernetIpReadResponse(source);
                break;
            }
            case MB_RESET_NETWORK_CONFIGURATION_REQUEST:
            case MB_UPDATE_NETWORK_CONFIGURATION_REQUEST:
            {
                retVal = 0;
                processNetworkConfigurationEthernetIpUpdateResponse(source);
                break;
            }

            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"NetworkConfigurationEthernetIp SetData default case");
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
        snprintf(msg,buff_size_config,"NetworkConfigurationEthernetIp SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the network configuration  EthernetIp read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::sendNetworkConfigurationEthernetIpReadRequest(MEMORY_BLOCK * const destination)
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
* \brief   - Send the network configuration  EthernetIp update request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::sendNetworkConfigurationEthernetIpUpdateRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(m_NetworkConfigData))
    {
        if(m_SendNetworkConfigUpdateRequest == true)
        {
           NetworkConfigurationEthernetIpStruct *Data = reinterpret_cast<NetworkConfigurationEthernetIpStruct *>(destination->data);
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
* \brief   - Send the network configuration  EthernetIp reset to default request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::sendNetworkConfigurationEthernetIpResetRequest(MEMORY_BLOCK * const destination)
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
* \brief   - Process the network configuration  EthernetIp coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::processNetworkConfigurationEthernetIpReadResponse(const MEMORY_BLOCK *const source)
{
    NetworkConfigurationEthernetIpStruct *Data = reinterpret_cast<NetworkConfigurationEthernetIpStruct *>(source->data);
    memcpy(&m_NetworkConfigData,Data,sizeof(NetworkConfigurationEthernetIpStruct));
    m_isNetworkConfigReadData = true;
}

/**************************************************************************//**
*
* \brief   - Process the network configuration EthernetIp response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::processNetworkConfigurationEthernetIpUpdateResponse(const MEMORY_BLOCK *const source)
{
    int *Data = reinterpret_cast<int *>(source->data);
    memcpy(&m_NetworkConfigUpdateResult,Data,sizeof(int));
    m_isNetworkConfigUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show network configuration EthernetIp details
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void NetworkConfigurationEthernetIp::ShowNetworkConfigurationEthernetIp()
{

    std::cout << "m_NetworkConfigData.IndustrialEthernetIPConfig: "  << m_NetworkConfigData.IndustrialEthernetIPConfig << std::endl;
    std::cout << "m_NetworkConfigData.IndustrialEthernetIPAddress: "  << m_NetworkConfigData.IndustrialEthernetIPAddress << std::endl;
    std::cout << "m_NetworkConfigData.IndustrialEthernetSubnetMask: "  << m_NetworkConfigData.IndustrialEthernetSubnetMask << std::endl;
    std::cout << "m_NetworkConfigData.IndustrialEthernetDefaultGateway: "  << m_NetworkConfigData.IndustrialEthernetDefaultGateway << std::endl;
    std::cout << "m_NetworkConfigData.NameServer: "  << m_NetworkConfigData.NameServer << std::endl;
    std::cout << "m_NetworkConfigData.NameServer2: "  << m_NetworkConfigData.NameServer2 << std::endl;
    std::cout << "m_NetworkConfigData.DomainName: "  << m_NetworkConfigData.DomainName << std::endl;
}

/**************************************************************************//**
*
* \brief   - return network configuration  EthernetIp updated details
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigUpdated
*
******************************************************************************/
bool NetworkConfigurationEthernetIp::GetNetworkConfigurationEthernetIpUpdateStatus()
{
    return m_isNetworkConfigUpdated;
}

/**************************************************************************//**
*
* \brief   - reset network configuration EthernetIp updated details
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigUpdated
*
******************************************************************************/
void NetworkConfigurationEthernetIp::ResetNetworkConfigurationEthernetIpUpdateStatus()
{
    m_isNetworkConfigUpdated = false;
}

/**************************************************************************//**
*
* \brief   - return the copy of network configuration EthernetIp structure data
*
* \param   - none

* \return  - copy of   NetworkConfigurationEthernetIpStruct data
*
******************************************************************************/
NetworkConfigurationEthernetIpStruct NetworkConfigurationEthernetIp::GetNetworkConfigurationEthernetIpData()
{
    NetworkConfigurationEthernetIpStruct NetworkConfigurationData = m_NetworkConfigData;
    //Reset the flag to false once the value is read
    m_isNetworkConfigUpdated = false;
    m_isNetworkConfigReadData = false;

    return NetworkConfigurationData;
}

/**************************************************************************//**
*
* \brief   - return the copy of network configuration  EthernetIp error code
*
* \param   - none

* \return  - copy of network configuration EthernetIp updated error code
*
******************************************************************************/
NETWORK_CONFIG_ERROR_CODES NetworkConfigurationEthernetIp::GetNetworkConfigurationEthernetIpUpdatedErrorCode()
{
    NETWORK_CONFIG_ERROR_CODES NetworkConfigUpdateResult = m_NetworkConfigUpdateResult;
    return NetworkConfigUpdateResult;
}

/**************************************************************************//**
*
* \brief   - return network configuration EthernetIp read data
*
* \param   - none
*
* \return  - bool - m_isNetworkConfigReadData
*
******************************************************************************/
bool NetworkConfigurationEthernetIp::GetNetworkConfigurationEthernetIpReadData()
{
    return m_isNetworkConfigReadData;
}

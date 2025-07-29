/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the network configuration related implementation
 
***************************************************************************/

#ifndef NetworkConfigurationEthernetIp_H_
#define NetworkConfigurationEthernetIp_H_

#include "DataInterface.h"
#include "NetworkConfigStructure.h"

class NetworkConfigurationEthernetIp : public DataInterface
{ 
public:
	
    NetworkConfigurationEthernetIp();
    virtual ~NetworkConfigurationEthernetIp();
    
    void InitiateNetworkConfigurationEthernetIpUpdateRequest(NetworkConfigurationEthernetIpStruct NetworkConfigurationEthernetIpData);
    void InitiateNetworkConfigurationEthernetIpResetRequest();

    bool GetNetworkConfigurationEthernetIpUpdateStatus();
    void ResetNetworkConfigurationEthernetIpUpdateStatus();
    bool GetNetworkConfigurationEthernetIpReadData();

    NetworkConfigurationEthernetIpStruct GetNetworkConfigurationEthernetIpData();
    NETWORK_CONFIG_ERROR_CODES GetNetworkConfigurationEthernetIpUpdatedErrorCode();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //cached Network configuration data.
    NetworkConfigurationEthernetIpStruct m_NetworkConfigData;
    //Stores the update response code coming from ASC
    NETWORK_CONFIG_ERROR_CODES m_NetworkConfigUpdateResult;

    bool m_SendNetworkConfigReadRequest;
    bool m_SendNetworkConfigUpdateRequest;
    bool m_SendNetworkConfigResetRequest;
    bool m_isNetworkConfigUpdated;
    bool m_isNetworkConfigReadData;

    void sendNetworkConfigurationEthernetIpReadRequest(MEMORY_BLOCK * const destination);
    void sendNetworkConfigurationEthernetIpUpdateRequest(MEMORY_BLOCK * const destination);
    void sendNetworkConfigurationEthernetIpResetRequest(MEMORY_BLOCK * constdestination);

    void processNetworkConfigurationEthernetIpReadResponse(const MEMORY_BLOCK *const source);
    void processNetworkConfigurationEthernetIpUpdateResponse(const MEMORY_BLOCK *const source);
	
    void ShowNetworkConfigurationEthernetIp();

};

#endif /* NetworkConfigurationEthernetIp_H_ */

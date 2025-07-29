/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the network configuration related implementation
 
***************************************************************************/

#ifndef NETWORKCONFIGURATION_H_
#define NETWORKCONFIGURATION_H_

#include "DataInterface.h"
#include "NetworkConfigStructure.h"

class NetworkConfiguration : public DataInterface
{ 
public:
	
    NetworkConfiguration();
    virtual ~NetworkConfiguration();
    
    void InitiateNetworkConfigurationUpdateRequest(NetworkConfigurationStruct NetworkConfigurationData);
    void InitiateNetworkConfigurationResetRequest();

    bool GetNetworkConfigurationUpdateStatus();
    void ResetNetworkConfigurationUpdateStatus();
    bool GetNetworkConfigurationReadData();

    NetworkConfigurationStruct GetNetworkConfigurationData();
    NETWORK_CONFIG_ERROR_CODES GetNetworkConfigurationUpdatedErrorCode();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //cached Network configuration data.
    NetworkConfigurationStruct m_NetworkConfigData;
    //Stores the update response code coming from ASC
    NETWORK_CONFIG_ERROR_CODES m_NetworkConfigUpdateResult;

    bool m_SendNetworkConfigReadRequest;
    bool m_SendNetworkConfigUpdateRequest;
    bool m_SendNetworkConfigResetRequest;
    bool m_isNetworkConfigUpdated;
    bool m_isNetworkConfigReadData;

    void sendNetworkConfigurationReadRequest(MEMORY_BLOCK * const destination);
    void sendNetworkConfigurationUpdateRequest(MEMORY_BLOCK * const destination);
    void sendNetworkConfigurationResetRequest(MEMORY_BLOCK * constdestination);

    void processNetworkConfigurationReadResponse(const MEMORY_BLOCK *const source);
    void processNetworkConfigurationUpdateResponse(const MEMORY_BLOCK *const source);
	
    void ShowNetworkConfiguration();

};

#endif /* NETWORKCONFIGURATION_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Network Configuration Ipsetup and EthernetIp related implementation
 ***************************************************************************/

#ifndef NETWORK_CONFIGURATION_STRUCTURES_H_
#define NETWORK_CONFIGURATION_STRUCTURES_H_

#include <string.h>
#include "Common_Definitions.h"


#define CLIENT_INTERFACE_NAME "cpsw1"

typedef enum
{
	 MB_READ_NETWORK_CONFIGURATION_REQUEST = 1,
	 MB_UPDATE_NETWORK_CONFIGURATION_REQUEST,
     MB_RESET_NETWORK_CONFIGURATION_REQUEST,
	 MB_UPDATE_FB_NETWORK_CONFIGURATION_REQUEST
}NETWORK_CONFIG_MB_SUB_ID;

typedef enum
{
	UPDATE_NETWORK_CONFIG_ERROR_UNKNOWN = 0,
	UPDATE_NETWORK_CONFIG_SUCCESS,
	UPDATE_NETWORK_CONFIG_FAIL
}NETWORK_CONFIG_ERROR_CODES;


typedef enum
{
	ETHERNET_STATIC_IP_ENABLED,
	ETHERNET_DHCP_CLIENT_ENABLED
}ETHERNET_IP_SETUP_STATUS;

typedef enum
{
	INDU_ETHERNET_STATIC_IP_ENABLED,
	INDU_ETHERNET_DHCP_CLIENT_ENABLED
}INDUSTRIAL_ETHERNET_IP_SETUP_STATUS;




typedef struct NetworkConfigurationEthernetIpStruct
{
    INDUSTRIAL_ETHERNET_IP_SETUP_STATUS IndustrialEthernetIPConfig;
    char IndustrialEthernetIPAddress[IP_SIZE];
    char IndustrialEthernetSubnetMask[IP_SIZE];
    char IndustrialEthernetDefaultGateway[IP_SIZE];
    char NameServer[IP_SIZE];
    char NameServer2[IP_SIZE];
    char DomainName[BUFF_SIZE];

    NetworkConfigurationEthernetIpStruct()
    {

        IndustrialEthernetIPConfig =  INDU_ETHERNET_STATIC_IP_ENABLED;

        strncpy(IndustrialEthernetIPAddress, "192.168.0.100", IP_SIZE - 1);
        IndustrialEthernetIPAddress[IP_SIZE - 1] = '\0';

        strncpy(IndustrialEthernetSubnetMask, "255.255.255.0", IP_SIZE - 1);
        IndustrialEthernetSubnetMask[IP_SIZE - 1] = '\0';

        strncpy(IndustrialEthernetDefaultGateway, "0.0.0.0", IP_SIZE - 1);
        IndustrialEthernetDefaultGateway[IP_SIZE - 1] = '\0';

        strncpy(NameServer, "0.0.0.0", IP_SIZE - 1);
        NameServer[IP_SIZE - 1] = '\0';

        strncpy(NameServer2, "0.0.0.0", IP_SIZE - 1);
        NameServer2[IP_SIZE - 1] = '\0';

        strncpy(DomainName, "Domain Test", BUFF_SIZE - 1);
        DomainName[BUFF_SIZE - 1] = '\0';
    }
}__attribute__((packed)) NetworkConfigurationEthernetIpStruct;



typedef struct NetworkConfigurationStruct
{
    ETHERNET_IP_SETUP_STATUS IpSetupIPConfig;
    char IpSetupIPAdress[IP_SIZE];
    char IpSetupSubnetMask[IP_SIZE];
    char IpSetupDefaultGateway[IP_SIZE];

	NetworkConfigurationStruct()
	{
        IpSetupIPConfig = ETHERNET_STATIC_IP_ENABLED;
        strncpy(IpSetupIPAdress, "192.168.2.101", IP_SIZE - 1); //set default Ethernet IP address
        IpSetupIPAdress[IP_SIZE - 1] = '\0'; // Ensure null termination
        
        strncpy(IpSetupSubnetMask, "255.255.255.0", IP_SIZE - 1); // set default Ethernet subnet mask
        IpSetupSubnetMask[IP_SIZE - 1] = '\0'; // Ensure null termination

        strncpy(IpSetupDefaultGateway, "192.168.2.1", IP_SIZE - 1);  // set default Ethernet Gateway
        IpSetupDefaultGateway[IP_SIZE - 1] = '\0'; // Ensure null termination
        	
	}
}__attribute__((packed)) NetworkConfigurationStruct;


extern const std::map<ETHERNET_IP_SETUP_STATUS, std::string> EthernetIpStatusStringMap;
extern const std::map<INDUSTRIAL_ETHERNET_IP_SETUP_STATUS, std::string> InduEthIpStatusStringMap;

#endif //NETWORK_CONFIGURATION_STRUCTURES_H_

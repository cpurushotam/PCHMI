/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Ldap Management related implementation
***************************************************************************/

#ifndef CORE_LOGIC_COMMON_COMMONS_LDAPMANAGEMENTSTRUCTURE_H_
#define CORE_LOGIC_COMMON_COMMONS_LDAPMANAGEMENTSTRUCTURE_H_

constexpr std::size_t LDAP_MAX_PORT_NUMBER            = 65535;
constexpr std::size_t LDAP_MIN_PORT_NUMBER            = 0;

#define LDAP_HOST_IP_BUF_LEN          17
#define LDAP_BASE_DN_BUF_LEN          100
#define LDAP_MANAGER_DN_BUF_LEN       100
#define LDAP_MANAGER_DN_PWD_BUF_LEN   100

typedef struct LdapConfigurationData
{
	char Host[LDAP_HOST_IP_BUF_LEN];
	int  Port;
	char BaseDN[LDAP_BASE_DN_BUF_LEN];
	char ManagerDN[LDAP_MANAGER_DN_BUF_LEN];
	char ManagerDNPwd[LDAP_MANAGER_DN_PWD_BUF_LEN];
	
	LdapConfigurationData()
	{
		Port = 0;
		memset(Host, 0, sizeof(Host));
		memset(BaseDN, 0, sizeof(BaseDN));
		memset(ManagerDN, 0, sizeof(ManagerDN));
		memset(ManagerDNPwd, 0, sizeof(ManagerDNPwd));
	}
}LdapConfigurationData;

#endif /* CORE_LOGIC_COMMON_COMMONS_LDAPMANAGEMENTSTRUCTURE_H_ */

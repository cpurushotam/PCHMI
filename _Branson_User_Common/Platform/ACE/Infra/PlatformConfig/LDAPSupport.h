/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of LDAP support.

***************************************************************************/

#ifndef LDAP_SUPPORT_H_
#define LDAP_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum LDAP_SUPPORT
{
	LDAP_NOT_SUPPORTED = 1,
	LDAP_SUPPORTED,
};

//configuration key.
static constexpr char LDAP_KEY[] = "LDAP";

class LDAPSupport : public PlatformConfigInterface
{
public:
	LDAPSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* LDAP_SUPPORT_H_ */

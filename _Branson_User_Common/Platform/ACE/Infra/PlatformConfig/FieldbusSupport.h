/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of fieldbus support.

***************************************************************************/

#ifndef FIELDBUS_SUPPORT_H_
#define FIELDBUS_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum FIELDBUS_TYPE
{
	NO_FIELDBUS	= 1,
	ETHERNET_IP_FIELDBUS,
	PROFINET_FIELDBUS
};

//configuration key.
static constexpr char FIELDBUS_SUPPORT_KEY[] = "Industrial_Ethernet";

class FieldbusSupport : public PlatformConfigInterface
{
public:
	FieldbusSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* FIELDBUS_SUPPORT_H_ */

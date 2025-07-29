/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of power supply type support.

***************************************************************************/

#ifndef POWER_SUPPLY_TYPE_SUPPORT_H_
#define POWER_SUPPLY_TYPE_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum POWER_SUPPLY_TYPE
{
	P_2100_POWER_SUPPLY	= 1,
	P_2200_POWER_SUPPLY,
	P_2300_POWER_SUPPLY
};

//configuration key.
static constexpr char POWER_SUPPLY_TYPE_KEY[] = "Power_Supply_Type";

class PowerSupplyTypeSupport : public PlatformConfigInterface
{
public:
	PowerSupplyTypeSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* POWER_SUPPLY_TYPE_SUPPORT_H_ */

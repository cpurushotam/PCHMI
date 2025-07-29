/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of PC Utility support.

***************************************************************************/

#ifndef PC_UTILITY_SUPPORT_H_
#define PC_UTILITY_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum PC_UTILITY_SUPPORT
{
	PC_UTILITY_NOT_SUPPORTED = 1,
	PC_UTILITY_SUPPORTED
};

//configuration key.
static constexpr char PC_UTILITY_KEY[] = "PC_Utility";

class PCUtilitySupport : public PlatformConfigInterface
{
public:
	PCUtilitySupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* PC_UTILITY_SUPPORT_H_ */

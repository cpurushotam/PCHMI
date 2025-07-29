/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Bearing Type support.

***************************************************************************/

#ifndef BEARING_TYPE_SUPPORT_H_
#define BEARING_TYPE_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum BEARING_TYPE_CONFIG
{
	STANDARD_BEARING = 1,
	STAINLESS_STEEL_BEARING
};

//configuration key.
static constexpr char BEARING_TYPE_KEY[] = "Bearing_Type";

class BearingTypeSupport : public PlatformConfigInterface
{
public:
	BearingTypeSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* BEARING_TYPE_SUPPORT_H_ */

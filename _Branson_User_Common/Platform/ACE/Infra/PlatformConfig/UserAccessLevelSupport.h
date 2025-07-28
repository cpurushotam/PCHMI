/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of User Access Level type support.

***************************************************************************/

#ifndef USER_ACCESS_LEVEL_SUPPORT_H_
#define USER_ACCESS_LEVEL_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum USER_ACCESS_LEVEL_TYPE
{
	STANDARD_USER_ACCESS_LEVEL = 1,
	ADVANCED_USER_ACCESS_LEVEL
};

//configuration key.
static constexpr char USER_ACCESS_LEVEL_TYPE_KEY[] = "User_Access_Level";

class UserAccessLevelSupport : public PlatformConfigInterface
{
public:
	UserAccessLevelSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* USER_ACCESS_LEVEL_SUPPORT_H_ */

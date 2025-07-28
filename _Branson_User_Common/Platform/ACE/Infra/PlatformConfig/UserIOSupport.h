/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of USER IO support.

***************************************************************************/

#ifndef USER_IO_SUPPORT_H_
#define USER_IO_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum USER_IO_SUPPORT
{
	USER_IO_NOT_SUPPORTED = 1,
	USER_IO_SUPPORTED,
};

//configuration key.
static constexpr char USER_IO_KEY[] = "User_IO";

class UserIOSupport : public PlatformConfigInterface
{
public:
	UserIOSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* USER_IO_SUPPORT_H_ */

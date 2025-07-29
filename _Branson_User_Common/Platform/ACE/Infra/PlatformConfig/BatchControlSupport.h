/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Batch Control support.

***************************************************************************/

#ifndef BATCH_CONTROL_SUPPORT_H_
#define BATCH_CONTROL_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum BATCH_CONTROL_SUPPORT
{
	BATCH_CONTROL_NOT_SUPPORTED	= 1,
	BATCH_CONTROL_SUPPORTED,
};

//configuration key.
static constexpr char BATCH_CONTROL_KEY[] = "Batch_Control";

class BatchControlSupport : public PlatformConfigInterface
{
public:
	BatchControlSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* BATCH_CONTROL_SUPPORT_H_ */

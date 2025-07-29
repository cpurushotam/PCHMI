/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of event log support.

***************************************************************************/

#ifndef EVENT_LOG_SUPPORT_H_
#define EVENT_LOG_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum EVENT_LOG_SUPPORT
{
	EVENT_LOG_NOT_SUPPORTED	= 1,
	EVENT_LOG_SUPPORTED
};

//configuration key.
static constexpr char EVENT_LOG_KEY[] = "Event_Logs";

class EventLogSupport : public PlatformConfigInterface
{
public:
	EventLogSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* EVENT_LOG_SUPPORT_H_ */

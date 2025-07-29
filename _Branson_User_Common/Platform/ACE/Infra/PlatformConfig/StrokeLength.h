/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of stroke length support.

***************************************************************************/

#ifndef STROKE_LENGTH_SUPPORT_H_
#define STROKE_LENGTH_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum STROKE_LENGTH_CONFIG
{
	HUNDRED_MM_STROKE_LENGTH = 1 
};

//configuration key.
static constexpr char STROKE_LENGTH_KEY[] = "Stroke_Length";

class StrokelengthSupport : public PlatformConfigInterface
{
public:
	StrokelengthSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* STROKE_LENGTH_SUPPORT_H_ */

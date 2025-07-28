/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of cylinder size support.

***************************************************************************/

#ifndef CYLINDER_SIZE_SUPPORT_H_
#define CYLINDER_SIZE_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum CYLINDER_SIZE_CONFIG
{
	FORTY_MM_CYLINDER = 1,
	FIFTY_MM_CYLINDER,
	SIXTY_THREE_MM_CYLINDER,
	EIGHTY_MM_CYLINDER
};

//configuration key.
static constexpr char CYLINDER_SIZE_KEY[] = "Cylinder_Size";

class CylinderSizeSupport : public PlatformConfigInterface
{
public:
	CylinderSizeSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;
};

#endif /* CYLINDER_SIZE_SUPPORT_H_ */

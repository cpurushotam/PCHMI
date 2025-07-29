/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares ActuatorConfig Class - Responsible for actuator Configuration
 	 	 	 	 	 	 	 	 1. Handle type of actuator configuration

--------------------------- REVISION HISTORY ------------------------------
 rev1: 15/09/2023 - Initial implementation.
					Support for no and manual actuator configuration. 
 rev2: 23/10/2023 - ACTUATOR_TYPE enum start from 1 to support latest configuration.
***************************************************************************/

#ifndef ACTUATORINIT_H_
#define ACTUATORINIT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

/* Enum declaration for actuator type configuration*/
enum ACTUATOR_TYPE
{
	ACTUATOR_MANUAL = 1,				/* Mechanical trigger switch */
	ACTUATOR_ELECTRONIC,				/* Pressure and down speed control, Load Cell, Linear Encoder */	
	ACTUATOR_ELECTRONIC_PLUS,
	NO_ACTUATOR,						/* No Actuator configuration */
	ACTUATOR_CONFIG_MAX				/* Move ACTUATOR_CONFIG_MAX variable Below base on actuator configuration implementation */		
};

/* Actuator configuration key, it will use  in m_ActiveConfig map. */
static constexpr char ACTUATOR_TYPE_KEY [] = "Actuator_Type";

// Definition of ActuatorInit class, for initial configuration of Actuator Type
class ActuatorInit : public PlatformConfigInterface
{
public:
	/* Constructor declaration */
	ActuatorInit();
		
	/* Set actuator configuration parameters */
	int SetConfigParameter(int ActuatorType) override;
	
	/* Return actuator configuration parameters */
	int GetConfigParameter() override;	
	
	/* Verify actuator configuration parameters */
	int VerifyConfigParameter(int ActuatorType) override;
};

#endif /* ACTUATORINIT_H_ */

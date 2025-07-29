/***********************************************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION -------------------------------------------------------------

 Declares PlatformInterface Class - Responsible for Platform Configuration.
 	 	 	 	 	 	 	 	   1. Add new configuration in m_ActiveConfig map.
 	 	 	 	 	 	 	 	   2. Create new class of new configuration and override GetConfigParameter,
 	 	 	 	 	 	 	 	   	  SetConfigParameter and VerifyConfigParameter functions.
 	 	 	 	 	 	 	 	   3. Handle supported features in SetConfigParameter function.

--------------------------- REVISION HISTORY ---------------------------------------------------------------
 rev1: 15/09/2023 - Initial implementation, Support for actuator configuration.

***********************************************************************************************************/

#ifndef PLATFORMCONFIGINTERFACE_H_
#define PLATFORMCONFIGINTERFACE_H_

#include "DataLogger.h"

// Definition of PlatformInterface class
class PlatformConfigInterface
{
protected:
	/* log identifier */
	size_t m_LogId;

	/* configured  value for each configuration */
	int m_ConfiguredValue =-1;
public:
	virtual int GetConfigParameter() 	= 0; 	// Return configured value of configuration.
	virtual int SetConfigParameter(int) = 0; 	// Load configuration into RAM
	virtual int VerifyConfigParameter(int) = 0; // Verify configuration
};

#endif /* PLATFORMCONFIGINTERFACE_H_ */

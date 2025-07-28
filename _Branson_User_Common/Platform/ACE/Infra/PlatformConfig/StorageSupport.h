/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of storage capacity.

***************************************************************************/

#ifndef STORAGE_SUPPORT_H_
#define STORAGE_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

// Enum declaration for storage support configuration
enum STORAGE_CONFIG
{
	BASIC_STORAGE = 1, //100 Alarms, 10k weld storage, 16 recipes
	ADVANCE_STORAGE, //500 Alarms, 100k weld storage, 32 recipes
	ELITE_STORAGE //1000 Alarms, 1M weld storage, 50 recipe
};

//Storage configuration key.
static constexpr char STORAGE_KEY[] = "Storage";

class StorageSupport : public PlatformConfigInterface
{
public:
	StorageSupport();
		
	//Set storage configuration parameter
	int SetConfigParameter(int StorageConfig) override;
	
	//Return storage configuration parameter
	int GetConfigParameter() override;	
	
	//Verify storage configuration parameter
	int VerifyConfigParameter(int StorageConfig) override;
	
	static int GetMaxRecipeNumberSupportedFromJSON();
	static int GetMaxWeldResultStorageSupportedFromJSON();
	static int GetMaxAlarmsStorageSupportedFromJSON();
	static int GetMaxWeldSignatureStorageSupportedFromJSON();
private:
	static size_t m_StaticLogId;
};

#endif /* STORAGE_SUPPORT_H_ */

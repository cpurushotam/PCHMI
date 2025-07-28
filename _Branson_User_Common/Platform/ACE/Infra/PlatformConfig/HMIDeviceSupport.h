/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares HMIDeviceSupport Class - Responsible for HMI device Configuration
 	 	 	 	 	 	 	 	   1. Support for HMI device

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/10/2023 - Initial implementation.
 rev2: 19/10/2023 - Added enum for HMI_DEVICE_SUPPORT
 
***************************************************************************/

#ifndef HMI_DEVICE_SUPPORT_H_
#define HMI_DEVICE_SUPPORT_H_

#include "PlatformConfigInterface.h"

/* JSON tag for HMI device */
static constexpr char HMI_DEVICE [] = "HMI_Type";

class HMIDeviceSupport : public PlatformConfigInterface
{
public:
	enum HMI_DEVICE_SUPPORT
	{
		LOCAL_HMI = 1,
		PC_HMI,
		BOTH
	};
	/* Constructor declaration */
	HMIDeviceSupport();

	/* Set HMI device available or not */
	int SetConfigParameter(int Feature) override;
	
	/* Return HMI device available or not */
	int GetConfigParameter() override;	
	
	/* Verify HMI device available or not */
	int VerifyConfigParameter(int Feature) override;
	
	#if defined(__RTP__)
	////When compiled on VxWorks
	static void CreateCommThreadAndWDSClinet();
	#endif
	
private:
	static size_t m_StaticLogId;
};

#endif /* HMI_DEVICE_SUPPORT_H_ */

/**************************************************************************

		Copyright (c) Branson Ultrasonics Corporation, 1996-2024
		
		This program is the property of Branson Ultrasonics Corporation
		Copying of this software is expressly forbidden, without the prior
		written consent of Branson Ultrasonics Corporation.
		
---------------------------- MODULE DESCRIPTION ----------------------------
	This file includes memory block configuration for background communication.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 18/01/2024 - Initial version.
 ***************************************************************************/
#ifndef BGDATAINTERFACECONFIG_HMI_H
#define BGDATAINTERFACECONFIG_HMI_H

#include "CommDataConfig.h"
#include "CommStatAce.h"
#include "ProductionScreen_MB.h"

class BgDataInterfaceConfig_HMI
{
    /* Back comm configuration for HMI*/
    CommDataConfig m_BgCommDataIntrConfig;
public:
    /* Constructor declaration to create memory blocks for background comm */
    BgDataInterfaceConfig_HMI(int welder_id);

    /* Destructor declaration to delete memory blocks of background comm */
    ~BgDataInterfaceConfig_HMI();

    /* To get background comm frame configuration as per requested welder */
    CommDataConfig *GetBgCommDataIntrConfig();
};

#endif // BGDATAINTERFACECONFIG_HMI_H

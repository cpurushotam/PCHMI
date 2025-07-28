/**************************************************************************

            Copyright (c) Branson Ultrasonics Corporation, 1996-2023

            This program is the property of Branson Ultrasonics Corporation
            Copying of this software is expressly forbidden, without the prior
            written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
			This file includes memory block configuration.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 22/05/2023 - Initial version.
 rev2: 20/10/2023 - Active configuration parametr of constructor and
                    MB implementation for PlatformConfig.
***************************************************************************/
#ifndef DATAINTERFACECONFIG_H
#define DATAINTERFACECONFIG_H

#include <vector>
#include "CommStatAce.h"
#include "CommDataConfig.h"
#include "PlatformConfig.h"
#include "ProductionScreen_MB.h"

// HMI Screen Config for respective welder
typedef struct
{
    std::map <std::string, DataInterface*> WelderMap;

} HMIScreenData;

/*Declaration of class DataInterfaceConfig_HMI which includes pointer object of comm status and production screen's data interface*/
class DataInterfaceConfig_HMI
{
    /*Object pointer used for each screen type*/
    ProductionScreen_MB *prod_screen_object;
    PlatformConfig      *platform_config_object;

    /*COMM Configuration for HMI*/
    std::map <int, CommDataConfig> CommDataConfig_HMI;
    std::map <int, HMIScreenData> HMIScreenDataMap;

    int m_PeerId;

public:

    /* Constructor declaration to initialize memory block and update map */
    DataInterfaceConfig_HMI(int PeerId, ActiveConfig* ActiveConfiguration);

    /* Destructor declaration to delete memory blocks and update map*/
    ~DataInterfaceConfig_HMI();

    /*To get frame configuration map done by CommDataConfig_HMI*/
    CommDataConfig *GetCommDataConfig(uint16_t PeerId);

    /*To get screen configuration map done by structure HMIScreenDataMap*/
    HMIScreenData GetHMIScreenData(uint16_t WelderID);

};

#endif // DATAINTERFACECONFIG_H

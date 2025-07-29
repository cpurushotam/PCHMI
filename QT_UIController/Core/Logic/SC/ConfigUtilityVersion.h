/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Config Utility Version related implementation
 
***************************************************************************/

#ifndef CONFIG_UTILITY_VERSION_H_
#define CONFIG_UTILITY_VERSION_H_

#include "DataInterface.h"
#include "ConfigUtilityVersionStructure.h"

class ConfigUtilityVersion : public DataInterface
{
public:
    ConfigUtilityVersion();
	int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    std::string GetConfigUtilityVersionNumber();
    void SetIsConfigVersionAvailable();
    bool GetIsConfigVersionAvailable();
    
private: 
	static size_t log_id;

    bool m_InitiateConfigUtilityVersionReadReq;
    bool m_IsConfigVersionAvailable;

    //cached data that stored config utility version string.
    std::string m_ConfigUtilityVersionData;

    size_t m_LogID;

    //Function to receive Config Utility Version data from ASC .
    void ProcessConfigUtilityVersionData(const MEMORY_BLOCK *const source);

    //Function to send Config Utility Version Read Request to ASC .
    void SendConfigUtilityVersionReadRequestToASC(MEMORY_BLOCK *const destination);

};
#endif /* CONFIG_UTILITY_VERSION_H_ */

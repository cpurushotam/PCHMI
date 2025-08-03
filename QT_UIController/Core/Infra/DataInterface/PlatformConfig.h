/**************************************************************************

          Copyright (c) Branson Ultrasonics Corporation, 1996-2023

          This program is the property of Branson Ultrasonics Corporation
          Copying of this software is expressly forbidden, without the prior
          written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
 Implements platform config data interface, used for configuration of HMI

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/10/2023 - Initial version.
***************************************************************************/

#ifndef PLATFORM_CONFIG_H_
#define PLATFORM_CONFIG_H_

#include "DataLogger.h"
#include "DataInterface.h"
#include "CommPeerInfo.h"

/* definition for SUB-ID of memory block */
typedef enum{
	SUB_ID_PLATFORM_CONFIG = 0,
}PLATFORM_CONFIG_SUB_ID;

/* Definition of PlatformConfig DataInterface class */
class PlatformConfig :public DataInterface
{
private:
    /* possible internal states of PlatformConfig class */
	typedef enum{
        E_WAITING_FOR_CONFIG = 1,       /* Waiting for configuration from ASC */
        E_SUCCESS,                      /* Configuration validation success */
        E_FAIL                          /* Configuration validation failed */
	}STATES;

    /* possible response states of PlatformConfig class */
    typedef enum
    {
        E_RESPONSE_IN_PROCESS   =  0,
        E_RESPONSE_SUCCESS      =  1,
        E_RESPONSE_FAIL         = -1
    }HMI_RESPONSE;

    /* Configuration Payload present in memory block */
    typedef struct
    {
        int ConfigSize;     /* total size of configuration */
                            /* followed by JSON string */
    }HMIConfigJSON;

    size_t          m_LogId;                                        /* log identifier */
    char            m_LogBuffer[buff_size_config]={0};              /* log buffer */    
    STATES          m_CurrentState = STATES::E_WAITING_FOR_CONFIG;  /* current state of HMIConfigSource class */
    std::map <std::string, int > m_HMI_Config;

    ActiveConfig* m_ActiveConfiguration;                            /* Store active configuration */

    bool ParseConfigJSON(const char* JSONConfig);                    /* Parse Configuration JSON */
public:
    PlatformConfig(ActiveConfig* ActiveConfiguration);              /* Constructor declaration */

    int GetData(MEMORY_BLOCK * const destination) override;         /* Retrive status of configuration exchange. */
    int SetData(const MEMORY_BLOCK *const source) override;         /* Install JSON configuration receive from ASC */

    int GetConfigState();                                           /* Return configuration state */

    static int GetConfigValue(int PeerId, std::string ConfigTag);   /* Return configured parameter using config tag. */
};
#endif /* PLATFORM_CONFIG_H_ */

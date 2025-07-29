/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the nfs Configuration common for HMI and ASC
 ***************************************************************************/
#ifndef NFS_CONFIG_H_
#define NFS_CONFIG_H_

#include <string.h>
#include "Common_Definitions.h"


#define MAX_IP_LEN 46        // Enough for IPv6 address + null terminator
#define MAX_PATH_LEN 256    // For file system paths

typedef enum
{
	NFS_MOUNT_REQUEST = 1

} NFS_CONFIGURATION_SUB_ID;

typedef struct NfsConfig
{
	char hostIp[MAX_IP_LEN];       // NFS server IP
	char exportPath[MAX_PATH_LEN];   // Path exported by the NFS server

}__attribute__((packed))NfsConfig;


#endif //NFS_CONFIG_H_

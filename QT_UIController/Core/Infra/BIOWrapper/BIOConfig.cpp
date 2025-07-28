/**************************************************************************

          Copyright (c) Branson Ultrasonics Corporation, 1996-2023

        This program is the property of Branson Ultrasonics Corporation
        Copying of this software is expressly forbidden, without the prior
        written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
This file includes configurations inputs needed for establishment of
BIO communication.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/05/2023 - Initial version, configuration for server
 rev2: 05/07/2023 - Encrypted pass key.
 rev3: 04/08/2023 - Common configuration for all peers and
                    Platform specific separation.

***************************************************************************/

#include "BIOConfig.h"

// Initialize pointer to platform specific configuration.
CommConfig* ASCConfig::ptrASCParameters = nullptr;



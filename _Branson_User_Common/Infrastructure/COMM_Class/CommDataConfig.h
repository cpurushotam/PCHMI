/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares COMM DataInterface configuration structure

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.

***************************************************************************/

#ifndef COMMDATACONFIG_H_
#define COMMDATACONFIG_H_

#include <iostream>
#include <map>
#include "DataInterface.h"

// COMM configuration structure definition
typedef struct{
	// TX configuration map table declaration
	std::map<std::pair<uint32_t,uint32_t>, DataInterface*> TXConfig;
	// RX configuration map table declaration
	std::map<std::pair<uint32_t,uint32_t>, DataInterface*> RXConfig;
}CommDataConfig;


#endif /* COMMDATACONFIG_H_ */

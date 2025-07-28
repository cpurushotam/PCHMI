/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares communication statistics data interface, used for HMI-ASC communication

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.

**************************************************************************/

#ifndef COMM_STAT_INTERFACE_H_
#define COMM_STAT_INTERFACE_H_

#include "DataInterface.h"

// Communication statistics Interface
class CommStatInterface:public DataInterface
{
public:
	
	// Clear comm stat counter
	virtual int ClearCommStatCounter() = 0;
};



#endif /* COMM_STAT_INTERFACE_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares communication statistics data interface, used for HMI-ASC communication

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.
 rev2: 05/06/2023 - Added feature to clear frame counter

**************************************************************************/

#ifndef COMM_STAT_MB_H_
#define COMM_STAT_MB_H_

#include "CommStatInterface.h"

// definition for SUB-ID of memory block
typedef enum{
	SUB_ID_OWN_STAT = 1,
	SUB_ID_PEER_STAT
}SUB_ID;

// elements present at address pointed by Memoryblock::data
typedef struct{
	uint32_t counter; // counter - incremented on each GetData function call, allowed to roll over.
	uint32_t status;  // reserved for future use
}comm_stat_data;


// Communication statistics DataInterface
class comm_stat:public CommStatInterface
{
private:
	// own statistics
	comm_stat_data m_own_stat ={0};

	// peer statistics
	comm_stat_data m_peer_stat ={0};

	// locks for Read/write in Get/Set functions
	 pthread_mutex_t m_comm_stat_mutex;

public:

	//read Communication statistics MB
	int GetData(MEMORY_BLOCK * const destination) override;

	//write Communication statistics MB
	int SetData(const MEMORY_BLOCK *const source) override;
	
	// Clear comm stat counter
	int ClearCommStatCounter() override;
};



#endif /* COMM_STAT_MB_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Data access interface.

--------------------------- REVISION HISTORY ------------------------------

 rev1: 30/04/2023 - Initial implementation
 rev2: 19/05/2023 - shifted data interfaces ID list to DataInterface_id.h

***************************************************************************/

#ifndef DATAINTERFACE_H_
#define DATAINTERFACE_H_

#include <iostream>
#include "DataInterface_id.h"
#include <cstdint>
#define VALID_BIT (0x1)    //valid bit for config element in memory block
#define ONE_TIME_USE (0x2) //one time use bit for config element in memory block

typedef struct MEMORY_BLOCK{
    uint32_t  id;        //unique identifier for memory block.
    uint32_t  sub_id;    //sub identifier for memory block, used to define for sub operation.
    uint32_t  config;    //configuration for memory block, currently bit 0 is assigned for validity check and
                         //bit 1 is assigned to check if its for one time use .
    uint32_t  size;      // For "get" function -> "In" direction indicates size of user's buffer,
                         //"Out" direction indicates size of actual data read
                         // For "set" function -> "In" direction indicates actual size of data,
                         //"Out" direction indicates size of actual data written  
    uint8_t *data;       //data buffer used for read and write operation.
    struct MEMORY_BLOCK* next;   //pointer to next memory block, reserved for future use
}__attribute__((packed)) MEMORY_BLOCK;

class DataInterface{
public:
	 DataInterface() {}
	 virtual ~DataInterface(){}
     virtual int GetData(MEMORY_BLOCK * const destination)=0;//read  memory block
     virtual int SetData(const MEMORY_BLOCK *const source)=0;//write memory block
     
};

#endif //DATAINTERFACE_H_

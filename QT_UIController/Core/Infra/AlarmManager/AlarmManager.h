/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the alarm manager interface definition which shall be 
 common across all platforms.
 
***************************************************************************/

#ifndef ALARM_MANAGER_H_
#define ALARM_MANAGER_H_

#include "DataInterface.h"
#include "AlarmLogStructure.h"
#include <memory>

class AlarmMgr : public DataInterface 
{
public:
		
	AlarmMgr();
	virtual ~AlarmMgr();	    
	
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;		
};



#endif /* ALARM_MANAGER_H_ */

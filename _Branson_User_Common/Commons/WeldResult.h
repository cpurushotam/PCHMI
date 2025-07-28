/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the weld result interface definition which shall be common across all platforms.
 
***************************************************************************/

#ifndef WELD_RESULT_H_
#define WELD_RESULT_H_

#include <memory>

#include "DataInterface.h"
#include "Common_Definitions.h"

typedef enum
{
	READ_LAST_WELD_RESULT_DATA = 1,
	READ_HISTORICAL_WELD_RESULT_DATA,
	READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER,
	SYNCH_HISTORICAL_WELD_RESULT_DATA,
	SYNCH_HISTORICAL_WELDRESULT_DATA_ON_DATETIME_FORMAT_CHANGE
}WELD_RESULT_ACE_SUB_ID;

class WeldResult : public DataInterface 
{
public:
	WeldResult() {}
    virtual ~WeldResult(){}
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;
    INTERFACE_IDENTIFIER GetInterFaceID(){return m_InterfaceID;}
    void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;}
    virtual bool ReadRequestedWeldResultHistory() = 0;
    
	//Assign this to appropriate weld result child class object based on the platform.
	static	std::unique_ptr<WeldResult>	m_ptrWeldResult;
	
protected:
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;//Identifies interface for which the weld result object is created

};

#endif /* WELD_RESULT_H_ */

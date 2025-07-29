/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the weld signature interface definition which shall be common across all platforms.
 
***************************************************************************/

#ifndef WELD_SIGNATURE_H_
#define WELD_SIGNATURE_H_

#include <memory>

#include "DataInterface.h"
#include "Common_Definitions.h"

typedef enum
{
	READ_REQUESTED_WELD_SIGNATURE_DATA = 1,
	READ_WELD_SIGNATURE_CONFIG,
	UPDATE_AUTO_SAVE_GRAPH,
	UPDATE_GRAPH_SAMPLING_INTERVAL
}WELD_SIGNATURE_ACE_SUB_ID;

class WeldSignature : public DataInterface 
{
public:
    WeldSignature() {}
    virtual ~WeldSignature(){}
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;
    INTERFACE_IDENTIFIER GetInterFaceID(){return m_InterfaceID;}
    void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;}
    virtual bool ReadRequestedWeldSignature() = 0;
    
	//Assign this to appropriate weld signature child class object based on the platform.
	static	std::unique_ptr<WeldSignature>	m_ptrWeldSignature;
	
protected:
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;//Identifies interface for which the weld signature object is created

};

#endif /* WELD_SIGNATURE_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the actuator setup definition which shall be common across all platforms.
 
***************************************************************************/

#ifndef ACTUATOR_SETUP_H_
#define ACTUATOR_SETUP_H_

#include <cstdint>
#include <memory>
#include "ActuatorSetupStructureAce.h"
#include "DataInterface.h"
#include "Common_Definitions.h"

typedef enum
{
	NONE_OP_TYPE,
	HORN_DOWN_OP_TYPE
}ACTUATOR_SETUP_OP_TYPE;

typedef enum
{
	REQUEST_ACTUATOR_SETUP_LEAVE_SCREEN,
	REQUEST_ACTUATOR_SETUP_ENTER_SCREEN,
}ACTUATOR_SETUP_SCREEN_DATA;

class ActuatorSetup : public DataInterface
{
public:
	ActuatorSetup() {}
	virtual ~ActuatorSetup(){}
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;
    
    virtual bool isHornDownClampOn() = 0;
    virtual ACTUATOR_SETUP_OP_TYPE isHornDownRequested() = 0;
    virtual ACTUATOR_SETUP_SCREEN_DATA isActuatorSetupScreenOpen() = 0;
    
	INTERFACE_IDENTIFIER GetInterFaceID(){return m_InterfaceID;}
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;}
	
	//Assign this to appropriate actuator setup child class object based on the platform.
	static	std::unique_ptr<ActuatorSetup>	m_ptrActuatorSetup;
	
private:
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;//Identifies interface for which the actuator setup object is created
};


#endif /* ACTUATOR_SETUP_H_ */

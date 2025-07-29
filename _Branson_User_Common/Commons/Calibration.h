/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the calibration interface definition which shall be common across all platforms.
 
***************************************************************************/

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "DataInterface.h"
#include "Common_Definitions.h"

class Calibration : public DataInterface
{
public:
	Calibration() {}
	virtual ~Calibration(){}
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;

	INTERFACE_IDENTIFIER GetInterFaceID(){return m_InterfaceID;}
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;}
	
private:
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;//Identifies interface for which the calibration object is created
};


#endif /* CALIBRATION_H_ */

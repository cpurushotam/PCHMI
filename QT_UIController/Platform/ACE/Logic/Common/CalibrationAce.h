/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the actuator calibration related implementation
 
***************************************************************************/

#ifndef CALIBRATION_ACE_H_
#define CALIBRATION_ACE_H_

#include "Calibration.h"
#include "CalibrationStructureAce.h"
#include "DataLogger.h"

class CalibrationAce : public Calibration
{
public:
	CalibrationAce();
	virtual ~CalibrationAce();
	
    virtual int GetData(MEMORY_BLOCK * const destination) override;
    virtual int SetData(const MEMORY_BLOCK *const source) override;
    
    bool GetPartContactFoundStatusValue();

    void InitiateCalibrationAbortRequest();
    void InitiateCalibrationResetRequest();
    void InitiateQuickCalibrationRequest();
    void InitiatePressureCalibrationRequest();
    void InitiateForceCalibrationRequest();
    void InitiateUserEnteredPressure1SendRequest(float Value);
    void InitiateUserEnteredPressure2SendRequest(float Value);
    void InitiateUserEnteredPressure3SendRequest(float Value);
    void InitiateUserEnteredForce1SendRequest(float Value);
    void InitiateUserEnteredForce2SendRequest(float Value);
    
private:
    void processPartContactFoundStatusValue(const MEMORY_BLOCK *const source);
    
	void sendAbortCalibrationRequest(MEMORY_BLOCK * const destination);
	void sendResetCalibrationRequest(MEMORY_BLOCK * const destination);
	void sendStartQuickCalibrationRequest(MEMORY_BLOCK * const destination);
	void sendStartPressureCalibrationRequest(MEMORY_BLOCK * const destination);
	void sendStartForceCalibrationRequest(MEMORY_BLOCK * const destination);
	void sendUserEnteredPressure1(MEMORY_BLOCK * const destination);
	void sendUserEnteredPressure2(MEMORY_BLOCK * const destination);
	void sendUserEnteredPressure3(MEMORY_BLOCK * const destination);
	void sendUserEnteredForce1(MEMORY_BLOCK * const destination);
	void sendUserEnteredForce2(MEMORY_BLOCK * const destination);
	
	bool m_bIsPartContactFound; 
	
	bool m_InitiateCalibrationAbortRequest;
	bool m_InitiateCalibrationResetRequest;
	bool m_InitiateQuickCalibrationRequest;
	bool m_InitiatePressureCalibrationRequest;
	bool m_InitiateForceCalibrationRequest;
	bool m_InitiateUserEnteredPressure1SendRequest;
	bool m_InitiateUserEnteredPressure2SendRequest;
	bool m_InitiateUserEnteredPressure3SendRequest;
	bool m_InitiateUserEnteredForce1SendRequest;
	bool m_InitiateUserEnteredForce2SendRequest;

	float m_UserEnterdPressure1;
	float m_UserEnterdPressure2;
	float m_UserEnterdPressure3;
	float m_UserEnterdForce1;
	float m_UserEnterdForce2;
};


#endif /* CALIBRATION_ACE_H_ */

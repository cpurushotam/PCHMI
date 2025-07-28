/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of number of amplitude steps and pressure steps.

***************************************************************************/

#ifndef AMPLITUDE_AND_PRESSURE_STEPS_SUPPORT_H_
#define AMPLITUDE_AND_PRESSURE_STEPS_SUPPORT_H_

#include "DataLogger.h"

constexpr int SUPPORTED_AMPLITUDE_STEPS_P_2100_PS = 0;
constexpr int SUPPORTED_AMPLITUDE_STEPS_P_2200_PS = 5;
constexpr int SUPPORTED_AMPLITUDE_STEPS_P_2300_PS = 10;

constexpr int SUPPORTED_PRESSURE_STEPS_P_2100_PS = 0;
constexpr int SUPPORTED_PRESSURE_STEPS_P_2200_PS = 5;
constexpr int SUPPORTED_PRESSURE_STEPS_P_2300_PS = 10;

constexpr int SUPPORTED_PRESSURE_STEPS_NO_ACTUATOR_OR_MANUAL_ACTUATOR  = 0;


class AmplitudeAndPressureStepsSupport
{
public:
	AmplitudeAndPressureStepsSupport();
	static unsigned int GetSupportedAmplitudeStepsFromJSON();
	static unsigned int GetSupportedPressureStepsFromJSON();
	
private:	
	static size_t m_StaticLogId;

};

#endif /* AMPLITUDE_AND_PRESSURE_STEPS_SUPPORT_H_ */

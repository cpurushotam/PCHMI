/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of power level and system frequency.

***************************************************************************/

#ifndef POWER_LEVEL_SYS_FREQUENCY_SUPPORT_H_
#define POWER_LEVEL_SYS_FREQUENCY_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

constexpr float MAX_POWER_VALUE_1250_WATT = 1250.0f;
constexpr float MAX_POWER_VALUE_2500_WATT = 2500.0f;
constexpr float MAX_POWER_VALUE_4000_WATT = 4000.0f;
constexpr float MAX_POWER_VALUE_1500_WATT = 1500.0f;
constexpr float MAX_POWER_VALUE_800_WATT = 800.0f;

// ENUM defined for different types of FREQUENCY that supported by system
typedef enum FREQUENCY
{
    FREQ_UNKNOWN = -1,
    FREQ_20KHZ = 20,
    FREQ_30KHZ = 30,
    FREQ_40KHZ = 40,
}FREQUENCY;

// Enum declaration for power level and system frequency support configuration
enum POWER_LEVEL_SYSTEM_FREQUENCY_CONFIG
{
	TWENTY_KHZ_1250_WATT = 1, //20 kHz, 1.25KW
	TWENTY_KHZ_2500_WATT, //20 kHz, 2.5KW
	TWENTY_KHZ_4000_WATT, //20 kHz, 4.0KW
	THIRTY_KHZ_1500_WATT, //30 kHz, 1.5KW
	FORTY_KHZ_800_WATT //40 kHz, 0.8KW
};

//power level and system frequency support configuration key.
static constexpr char POWER_LEVEL_SYSTEM_FREQUENCY_KEY[] = "Power_Level";

class PowerLevelSysFrequencySupport : public PlatformConfigInterface
{
public:
	PowerLevelSysFrequencySupport();
		
	//Set configuration parameter
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration parameter
	int GetConfigParameter() override;	
	
	//Verify configuration parameter
	int VerifyConfigParameter(int ConfigValue) override;
	
	static float GetMaxPowerFromJSON();
	static int GetSystemFrequencyFromJSON();
private:
	static size_t m_StaticLogId;
};

#endif /* POWER_LEVEL_SYS_FREQUENCY_SUPPORT_H_ */

/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2024

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Responsible for configuration of Barcode Scanner support.

***************************************************************************/

#ifndef BARCODE_SCANNER_SUPPORT_H_
#define BARCODE_SCANNER_SUPPORT_H_

#include "PlatformConfigInterface.h"
#include "DataLogger.h"

enum BARCODE_SCANNER_SUPPORT
{
	BARCODE_SCANNER_NOT_SUPPORTED = 1,
	BARCODE_SCANNER_SUPPORTED,
};

//configuration key.
static constexpr char BARCODE_SCANNER_KEY[] = "Barcode_Scanner";

class BarcodeScannerSupport : public PlatformConfigInterface
{
public:
	BarcodeScannerSupport();
		
	//Set configuration value
	int SetConfigParameter(int ConfigValue) override;
	
	//Return configuration value
	int GetConfigParameter() override;	
	
	//Verify configuration value
	int VerifyConfigParameter(int ConfigValue) override;

};

#endif /* BARCODE_SCANNER_SUPPORT_H_ */

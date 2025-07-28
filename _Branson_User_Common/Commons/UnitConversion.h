/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the unit conversion related implementation
 ***************************************************************************/

#ifndef UNIT_CONVERSION_H_
#define UNIT_CONVERSION_H_

#include <string>

class UnitConversion
{
public:
	UnitConversion();
	virtual ~UnitConversion();
	// Functions to convert metric to imperial and vice-versa
	static float ConvertKPascalToPsi(float pKPascal);
	static float ConvertNewtonToLbs(float pNewton);
	static float ConvertMilliMeterToInches(float pMillimeter);
	static float ConvertMilliMeterPerSecToInchPerSec(float pVelocity);
	static float ConvertPsiToKPascals(float dPsi);
	static float ConvertLbsToNewton(float pLbs);
	static float ConvertInchesToMillimeter(float pInch);
	static float ConvertInchesPerSecToMillimeterPerSec(float pVal);
};

#endif /* UNIT_CONVERSION_H_ */

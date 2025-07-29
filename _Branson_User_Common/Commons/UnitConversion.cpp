/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the unit conversion definition
 ***************************************************************************/

#include <cmath>
#include "UnitConversion.h"

/**************************************************************************//**
*
* \brief   - Constructor unit conversion class.
*            
* \param   - none
*
* \return  - none
*
******************************************************************************/
UnitConversion::UnitConversion() 
{

}

/**************************************************************************//**
*
* \brief   - Destructor unit conversion class.      
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
UnitConversion::~UnitConversion() 
{
	
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Kilopascals (kPa) to 
* 			 Pound per square inch (psi).
*
* \param   - None 
*
* \return  - return converted Pound per square inch (psi) value.
*
******************************************************************************/
float UnitConversion::ConvertKPascalToPsi(float pKPascal)
{
	float mPsi = 0.0f;
	
	mPsi = (pKPascal / 6.89476);

	// Round the result to 1 decimal place as imperial conversion.
	mPsi = std::round(mPsi * 10) / 10;

	return mPsi;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Newton(N) to Pounds(lbs)
*
* \param   - None 
*
* \return  - Return converted Pounds(lbs) value.
*
******************************************************************************/
float UnitConversion::ConvertNewtonToLbs(float pNewton)
{
	float mLbs = 0.0f;
    
	mLbs = (pNewton / 4.44822);
	
	// Round the result to 0 decimal places as imperial conversion.
	mLbs = std::round(mLbs);
    
    return mLbs;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Millimeter(mm) to Inches(in)
*
* \param   - None 
*
* \return  - Return converted Inches(in) value.
*
******************************************************************************/
float UnitConversion::ConvertMilliMeterToInches(float pMillimeter)
{
    float mInches = 0.0f;
    
    mInches = (pMillimeter / 25.4);
	
	// Round the result to 4 decimal places as imperial conversion.
	mInches = std::round(mInches * 10000) / 10000;

    return mInches;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Millimeter per second(mm/sec) 
*            to Inches per second(in/sec).
*
* \param   - None 
*
* \return  - Return converted Inches per second(in/sec) value.
*
******************************************************************************/
float UnitConversion::ConvertMilliMeterPerSecToInchPerSec(float pVelocity)
{
    float mTemp = 0.0f;
    
    mTemp = (pVelocity / 25.4);
	
	// Round the result to 1 decimal place as imperial conversion.
	mTemp = std::round(mTemp * 10) / 10;
    
    return mTemp;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Pound per square inch (psi) to Kilopascals (kPa).
*
* \param   - None 
*
* \return  - return converted Kilopascals (kPa) value.
*
******************************************************************************/
float UnitConversion::ConvertPsiToKPascals(float dPsi)
{
	float mKPascals = 0.0f;
	
	mKPascals = (dPsi * 6.89476);
	
	// Round the result to 0 decimal places as metric conversion.
	mKPascals = std::round(mKPascals);
	
	return mKPascals;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Pounds(lbs) to Newton(N). 
*
* \param   - None 
*
* \return  - Return converted Newton(N) value.
*
******************************************************************************/
float UnitConversion::ConvertLbsToNewton(float pLbs)
{
	float mNewton = 0.0f;
	
	mNewton = (pLbs * 4.44822);
	
	// Round the result to 0 decimal places as metric conversion.
	mNewton = std::round(mNewton);
	
	return mNewton;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Inches(in) to Millimeter(mm).
*
* \param   - None 
*
* \return  - Return converted Millimeter(mm) value.
*
******************************************************************************/
float UnitConversion::ConvertInchesToMillimeter(float pInch)
{
	float dMillimeter = 0.0f;
	
	dMillimeter = (pInch * 25.4);
	
	// Round the result to 2 decimal places as metric conversion.
	dMillimeter = std::round(dMillimeter * 100) / 100;
	
	return dMillimeter;
}

/*************************************************************************//**
* \brief   - Wrapper function to convert Inches per second(in/sec) 
*            to Millimeter per second(mm/sec).
*
* \param   - None 
*
* \return  - Return converted Millimeter per second(mm/sec) value.
*
******************************************************************************/
float UnitConversion::ConvertInchesPerSecToMillimeterPerSec(float pVal)
{
	float dTemp = 0.0f;
	
	dTemp = (pVal * 25.4);
	
	// Round the result to 0 decimal places as metric conversion.
	dTemp = std::round(dTemp);
	
	return dTemp;
}

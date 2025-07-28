/**************************************************************************
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the horn scan recipe related implementation
 ***************************************************************************/
#ifndef HORNSCANRECIPESTRUCTURE_H_
#define HORNSCANRECIPESTRUCTURE_H_

#include <map>
#include <tuple>
#include <string>
#include "Common_Definitions.h"

/*This structure defines to Horn scan recipe Parameters **/

typedef struct structHornScanRecipe
{
	structHornScanRecipe();
	/* Method to Set Horn Scan Recipe parameters as per system frequency */
	void SetParametersAsPerSystemFrequency();
    uint32_t FrequencyStart; 		
    uint32_t FrequencyStop;  		
    uint32_t FrequencyStep;  		
    float    TimeDelay;				
    uint32_t MaxAmplitude;			
    uint32_t MaxCurrent;			
    bool  SetDigTuneWithHornScan;	
}__attribute__((packed)) structHornScanRecipe;

/*This enum defines on screen operations HMI to ASC */
typedef enum
{
	HORN_SCAN_RECIPE_SAVE = 1,
	HORN_SCAN_RECIPE_RESET_TO_DEFAULT,
	HORN_SCAN_RECIPE_DATA,
	HORN_SCAN_RECIPE_UPDATE_RESULT
}HORN_SCAN_RECIPE_SUB_ID;

/*This enum defines responses */
typedef enum
{	
	HORN_SCAN_RECIPE_UPDATE_SUCCESS,
	HORN_SCAN_RECIPE_UPDATE_RESPONSE_UNKNOWN,
	HORN_SCAN_RECIPE_UPDATE_FAILURE,
	HORN_SCAN_RECIPE_UPDATE_VALUE_OUT_OF_RANGE,
	HORN_SCAN_RECIPE_UPDATE_DATATYPE_NOT_SUPPORTED,
}HORN_SCAN__RECIPE_UPDATE_RESPONSE;

typedef enum
{
	FREQUENCY_START,
	FREQUENCY_STOP,
	FREQUENCY_STEP,
	TIMEDELAY,
	MAX_AMPLITUDE,
	MAX_CURRENT,
	SET_DEGTUNE_WITHHORNSCAN,
	
}HORNSCAN_RECIPE_PARAM_ID;

#define F20KHZMIDBAND   (19950)
#define F20KHZMINABS 	(F20KHZMIDBAND - 500)
#define F20KHZMAXABS 	(F20KHZMIDBAND + 500)

#define F30KHZMIDBAND 	(30000)
#define F30KHZMINABS 	(F30KHZMIDBAND - 750)
#define F30KHZMAXABS 	(F30KHZMIDBAND + 750)

#define F40KHZMIDBAND 	(39990)
#define F40KHZMINABS 	(F40KHZMIDBAND - 1000)
#define F40KHZMAXABS 	(F40KHZMIDBAND + 1000)

extern const std::map < HORNSCAN_RECIPE_PARAM_ID, std::tuple< PARAM_DATA_TYPE, std::string, std::string, std::string,std::string, std::string, std::string,std::string, std::string, std::string, std::string, std::string, std::string > > HornScanRecipeParamMap;

//Holds the changed Horn scan recipe parameter identifier and value.
typedef struct ChangedHornScanRecipeParameter
{
	HORNSCAN_RECIPE_PARAM_ID HornScanRecipeParamID; //Holds the changed recipe parameter identifier.
	char Value[BUFFER_TO_HOLD_CHANGED_VALUE]; //Holds the changed value.
	
}__attribute__((packed)) ChangedHornScanRecipeParameter;

#endif

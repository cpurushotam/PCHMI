/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the weld recipe interface definition which shall be common across all platforms.
 
***************************************************************************/

#ifndef WELD_RECIPE_H_
#define WELD_RECIPE_H_

#include <cstdint>
#include <memory>
#include "DataInterface.h"
#include "Common_Definitions.h"

class WeldRecipe : public DataInterface 
{
public:
	enum WELD_RECIPE_PARAM_ID
	{
		//Common weld recipe parameters across all platforms
		WELD_RECIPE_NUMBER_PARAM = 1,
		WELD_RECIPE_VERSION_NUM_PARAM,
		WELD_RECIPE_NAME_PARAM,
		WELD_MODE_PARAM ,
		WELD_MODE_VALUE_PARAM,
		CYCLE_COUNT_PARAM,
		CYCLES_OK_COUNT_PARAM,
		REJECT_COUNT_PARAM,
		SUSPECT_COUNT_PARAM,
		MEMORY_OFFSET_PARAM,
		DIGITAL_TUNE_PARAM,
		
		//add before this
		WELD_RECIPE_MAX_PARAM
	};
public:
	WeldRecipe() {}
	virtual ~WeldRecipe(){}
    virtual int GetData(MEMORY_BLOCK * const destination) = 0;
    virtual int SetData(const MEMORY_BLOCK *const source) = 0;
    virtual bool SetWeldRecipeParameter(int RecipeNumber, int ParamID, void * Value)	= 0 ;
	virtual bool SetActiveWeldRecipeParameter(int ParamID, void * Value) = 0;
	virtual bool GetActiveWeldRecipeParameter(int ParamID,void *Value) = 0;
	virtual bool GetWeldRecipeParameter(int RecipeNum, int ParamID,void *Value) = 0;
	virtual int32_t GetDigitalTuneWithOffsets() = 0 ;
	virtual bool LogWeldRecipeChanges(char *SourceWeldRecipeData, char *OldDestinationWeldRecipeData, INTERFACE_IDENTIFIER InterFaceID) = 0;
	virtual void SetActiveWeldRecipeNumber(int recipeNum, INTERFACE_IDENTIFIER interFaceID) = 0;
	virtual void LoadActiveWeldRecipeNumber() = 0;
	INTERFACE_IDENTIFIER GetInterFaceID(){return m_InterfaceID;}
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;}
	
	//Assign this to appropriate weld recipe child class object based on the platform.
	static	std::unique_ptr<WeldRecipe>	m_ptrWeldRecipe;
	
private:
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;//Identifies interface for which the weld recipe object is created
};

#endif /* WELD_RECIPE_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------
	 It contains the Horn  Scan recipe related implementation

**********************************************************************************************************/
#ifndef HORNSCANRECIPE_H_
#define HORNSCANRECIPE_H_

#include <cstdint>
#include <map>
#include "HornScanRecipeStructure.h"
#include "DataInterface.h"
class HornScanRecipe: public DataInterface
{
public:

	HornScanRecipe();
	virtual ~HornScanRecipe();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void InitiateRecipeSaveRequest(structHornScanRecipe RecipeData);
    void InitiateResetToDefaultRequest();
    structHornScanRecipe GetHornScanRecipeData();
    void SetHornScanRecipeData(structHornScanRecipe m_structHornScanRecipe);
    bool GetIsHornScanRecipeUpdated(void);
    void SetIsHornScanRecipeUpdated(bool Value);

    std::string GetHornScanRecipeParamMinValue(HORNSCAN_RECIPE_PARAM_ID ParamID);
    std::string GetHornScanRecipeParamMaxValue(HORNSCAN_RECIPE_PARAM_ID ParamID);

private:
    static size_t m_hslog_id;
    structHornScanRecipe m_HornScanRecipe;
	/* Mutex to access the horn scan recipe data */
	pthread_mutex_t m_hornScanDataMutex;
    /* Declaration for save command request button notifier **/
	bool m_InitiateRecipeSaveRequest;
	/* Declaration for restore default command request button notifier*/
	bool m_InitiateRecipeResetToDefaultRequest;
	//Horn Scan Recipe read request is sent to ASC when this flag is true
	bool m_InitiateRecipeReadRequest;
    //Horn Scan Recipe update flag
    bool m_IsHornScanRecipeUpdated;
	/*Member variable to hold scan recipe update status*/
	HORN_SCAN__RECIPE_UPDATE_RESPONSE m_hornScanRecipeUpdateStatus ;
	/* Method to check save command request is receive or not  */
    void InitiateRecipeSaveRequest();
	/* Send save command or request to ASC for saving horn scan recipe data */
	void sendSaveRequest(MEMORY_BLOCK * const destination);
	/* request for default horn scan recipe data from ASC */
	void sendHornScanRecipeResetToDefaultRequest(MEMORY_BLOCK * const destination);
	//Process recipe read request
    void processRecipeReadResponseFromASC(const MEMORY_BLOCK *const source);
    //initiate to send recipe read request to ASC
    void SendRecipeReadRequestToASC(MEMORY_BLOCK * const destination);
	//Process the recipe update status
	void processRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source);

    void ShowHornScanRecipe();
};

#endif

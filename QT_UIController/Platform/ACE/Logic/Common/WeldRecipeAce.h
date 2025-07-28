/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld recipe related implementation

***************************************************************************/

#ifndef WELD_RECIPE_ACE_H_
#define WELD_RECIPE_ACE_H_

#include <cstdint>
#include <map>
#include <queue>

#include "WeldRecipe.h"
#include "WeldRecipeStructuresAce.h"

class WeldRecipeACE : public WeldRecipe
{
public:
	WeldRecipeACE();
    virtual ~WeldRecipeACE();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    bool SetActiveWeldRecipeParameter(int WeldRecipeParamID, void* Value);
    void InitiateRecipeCreateRequest();
    void InitiateRecipeDeleteRequest(int RecipeNumber);
    void InitiateRecipeSetAsActiveRequest(int RecipeNumber);
    void InitiateWeldRecipeCopyRequest(int SourceRecipeNumber, int DestinationRecipeNumber);
    void InitiateWeldRecipeRecallRequest(int RecipeNumber, int RecipeVersionNumber);
    void InitiateAmplitudeStepDataSendRequest(struct AmplitudeStepDataACE &AmplitudeStepDataToBeSentToASC);
    void InitiatePressureStepDataSendRequest(struct  PressureStepDataACE &PressureStepDataToBeSentToASC);

    bool InitiateRecipeCycleCountResetRequest(int RecipeNumber);
    int GetActiveWeldRecipeNumber();
    WeldRecipeACEStruct GetActiveWeldRecipeData();
    bool IsActiveWeldRecipeSaved();
    std::map<int, RecipeCardDataACEStruct> GetRecipeCardDataMap();
    bool IsActiveWeldRecipeUpdated();
    bool IsMapUpdated();
    int GetTotalRecipesEntries();

    std::string GetWeldRecipeParamMinValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType = SYSTEM_UNIT);
    std::string GetWeldRecipeParamMaxValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType = SYSTEM_UNIT);
    std::string GetWeldRecipeParamDefaultValue(WELD_RECIPE_ACE_PARAM_ID ParamID, WELD_RECIPE_UNIT_TYPE UnitType = SYSTEM_UNIT);

    // Dummy implementation for HMI
    bool LogWeldRecipeChanges(char *SourceWeldRecipeData, char *OldDestinationWeldRecipeData, INTERFACE_IDENTIFIER InterFaceID)
    {
        return false;
    }

        // Dummy implementation for HMI
    bool GetActiveWeldRecipeParameter(int ParamID,void *Value)
    {
        return false;
    }

    // Dummy implementation for HMI
    bool GetWeldRecipeParameter(int RecipeNum, int ParamID,void *Value)
    {
        return false;
    }

    // Dummy implementation for HMI
    int32_t GetDigitalTuneWithOffsets()
    {
        return -1;
    }

    // Dummy implementation for HMI
    void SetActiveWeldRecipeNumber(int recipeNum, INTERFACE_IDENTIFIER m_InterfaceID) {}

    // Dummy implementation for HMI
    void LoadActiveWeldRecipeNumber() {}

private:
    static size_t static_log_id;

    //Holds active weld recipe data
    WeldRecipeACEStruct m_ActiveWeldRecipeData;
    //map holds the copy of data needed to be shown on recipe card screen
    std::map<int, RecipeCardDataACEStruct> m_RecipeCardDataMap;
    //Queue holds the changed recipe parameter identifier and changed data
    std::queue<ChangedWeldRecipeParameter> m_ChangedWeldRecipeParameter;

    //mutex for m_ActiveWeldRecipeData access
     pthread_mutex_t m_ActiveWeldRecipeDataMutex;
    //mutex for m_RecipeCardDataMap access
    pthread_mutex_t m_RecipeCardDataMapMutex;
    //mutex for m_ChangedWeldRecipeParameter access
    pthread_mutex_t m_ChangedWeldRecipeParameterMutex;

    //flag is set to true when active weld recipe gets updated
    bool m_IsActiveWeldRecipeUpdated;
    //flag is set to true when recipe card data gets updated
    bool m_IsMapUpdated;
    //holds index number of recipe card map to be read from ASC in chunks
    int m_RecipeCardIndexNumber;
    //Active Recipe read request is sent to ASC when this flag is true
    bool m_SendActiveWeldRecipeReadRequest;
    //Recipe card read request is sent to ASC when this flag is true
    bool m_SendRecipeCardReadRequest;
    //Recipe create request is sent to ASC when this flag is true
    bool m_InitiateRecipeCreateRequest;
    //Recipe delete request is sent to ASC when this flag is true
    bool m_InitiateRecipeDeleteRequest;
    //Recipe reset to default request is sent to ASC when this flag is true
    bool m_InitiateRecipeResetToDefaultRequest;
    //Set Weld Recipe as active request is sent to ASC when this flag is true
    bool m_InitiateSetWeldRecipeAsActiveRequest;
    //Copy Weld Recipe request is sent to ASC when this flag is true
    bool m_InitiateCopyWeldRecipeRequest;
    //Recall Weld Recipe request is sent to ASC when this flag is true
    bool m_InitiateRecallWeldRecipeRequest;
    //Weld Amplitude Stepping data is sent to ASC when this flag is true
    bool m_InitiateAmplitudeStepDataSendRequest;
    //Weld Pressure Stepping data is sent to ASC when this flag is true
    bool m_InitiatePressureStepDataSendRequest;
    //Holds the recipe number to be deleted in case HMI initiates recipe delete request
    int m_RecipeNumberToBeDeleted;
    //Holds the recipe number to be set as active weld recipe in case HMI initiates set weld recipe as active request
    int m_RecipeNumberToBeSetAsActive;
    //Holds the recipe number to be reset to default in case HMI initiates recipe reset to default request
    int m_RecipeNumberToBeResetToDefault;
    //Holds the source recipe number for recipe copy operation
    int m_SourceRecipeNumberForCopyOperation;
    //Holds the destination recipe number for recipe copy operation
    int m_DestinationRecipeNumberForCopyOperation;
    //Holds the weld recipe number for recipe recall operation
    int m_RecipeNumberFoRecallOperation;
    //Holds the weld recipe version number for recipe recall operation
    int m_RecipeVersionNumberFoRecallOperation;
    //Holds the Amplitude stepping data to be sent to ASC
    AmplitudeStepDataACE m_AmplitudeStepDataToBeSentToASC;
    //Holds the Pressure stepping data to be sent to ASC
    PressureStepDataACE m_PressureStepDataToBeSentToASC;

    std::string WeldRecipeMinMaxParametersImperialConversion(WELD_RECIPE_ACE_PARAM_ID ParamID, std::string Value);
    bool SetWeldRecipeParameter(int RecipeNumber, int WeldRecipeParamID, void* Value);
    void sendRecipeCreateRequestToASC(MEMORY_BLOCK * const destination);
    void sendRecipeDeleteRequestToASC(MEMORY_BLOCK * const destination);
    void sendRecipeParameterUpdateRequestToASC(MEMORY_BLOCK * const destination);
    void sendRecipeSetAsActiveReuestToASC(MEMORY_BLOCK * const destination);
    void sendActiveRecipeReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendWeldRecipeCopyReuestToASC(MEMORY_BLOCK * const destination);
    void sendWeldRecipeRecallReuestToASC(MEMORY_BLOCK * const destination);
    void sendAmplitudeStepDataToASC(MEMORY_BLOCK * const destination);
    void sendPressureStepDataToASC(MEMORY_BLOCK * const destination);
    void sendRecipeCardRequestToASC(MEMORY_BLOCK * const destination);
    void sendWeldRecipeResetToDefaultRequestToASC(MEMORY_BLOCK * const destination);
    void processActiveWeldRecipeDataFromASC(const MEMORY_BLOCK *const source);
    void processRecipeCardResponseFromASC(const MEMORY_BLOCK *const source);
    void processRecipeChangesFromASC(const MEMORY_BLOCK *const source);
    void processSynchWeldRecipeDataFromASC(const MEMORY_BLOCK *const source);
    void printActiveWeldRecipe();
    void printRecipeCardMap();
};

#endif /* WELD_RECIPE_ACE_H_ */

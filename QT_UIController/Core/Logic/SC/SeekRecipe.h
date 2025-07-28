/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the seek recipe related implementation

***************************************************************************/

#ifndef SEEKRECIPE_H_
#define SEEKRECIPE_H_

#include "DataInterface.h"
#include "SeekRecipeStructure.h"

class SeekRecipe : public DataInterface
{

public:

	 SeekRecipe();
	 virtual ~SeekRecipe();

	//Write Recipe data
	int GetData(MEMORY_BLOCK * const destination) override;

	//Read Recipe data
    int SetData(const MEMORY_BLOCK *const source) override;

    void SetSeekRecipeData(SeekRecipestruct m_SeekRecipeStruct);
    void InitiateResetToDefaultSeekRequest();
    SeekRecipestruct GetSeekRecipeData();
    bool GetIsSeekRecipeUpdated(void);
    void SetIsSeekRecipeUpdated(bool Value);

    std::string GetSeekRecipeParamMinValue(SEEK_RECIPE_PARAM_ID ParamID);
    std::string GetSeekRecipeParamMaxValue(SEEK_RECIPE_PARAM_ID ParamID);
    void ShowSeekRecipe();	
    
private:
    static size_t static_log_id;

	bool m_InitiateRecipeSaveRequest;
	bool m_InitiateRecipeReseToDefaultRequest;
	//Seek Recipe read request is sent to ASC when this flag is true
	bool m_InitiateRecipeReadRequest;
    //structure variable to store seek recipe data
	SeekRecipestruct m_SeekRecipeData;
    //Seek Recipe update flag
    bool m_IsSeekRecipeUpdated;
	//Member variable to hold seek recipe update status
	SEEK_RECIPE_UPDATE_STATUS m_seekRecipeStatus;
	//mutex for m_SeekRecipeData access
	pthread_mutex_t m_SeekRecipeDataMutex;
	size_t m_LogID;

	//Send save seek recipe data request to ASC
	void sendSeekRecipeSaveRequestToASC(MEMORY_BLOCK * const destination);
	//Send reset to default seek recipe data request to ASC
	void sendSeekRecipeRestToDefaultRequestToASC(MEMORY_BLOCK * const destination);
	//initiate to send recipe read request to ASC
	void SendRecipeReadRequestToASC(MEMORY_BLOCK * const destination);
	//Process recipe read request
	void processRecipeReadResponseFromASC(const MEMORY_BLOCK *const source);
	//Process the recipe update status
	void processRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source);

    void InitiateRecipeSaveRequest();

};

#endif /* SEEKRECIPE_H_ */




















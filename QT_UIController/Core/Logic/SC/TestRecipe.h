/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test recipe (HMI side) related implementation

***************************************************************************/

#ifndef TESTRECIPE_H_
#define TESTRECIPE_H_

#include "TestRecipeStructure.h"
#include "DataInterface.h"

class TestRecipe : public DataInterface
{
public:

	TestRecipe();
	virtual ~TestRecipe();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void SetTestRecipeData(TestRecipestruct m_TestRecipeStruct);
    void InitiateTestRecipeResetToDefaultRequest();
    TestRecipestruct GetTestRecipeData();
    bool GetIsTestRecipeUpdated(void);
    void SetIsTestRecipeUpdated(bool Value);

    std::string GetTestRecipeParamMinValue(TEST_RECIPE_PARAM_ID ParamID);
    std::string GetTestRecipeParamMaxValue(TEST_RECIPE_PARAM_ID ParamID);
	void ShowTestRecipe();
	
private:
	static size_t static_log_id;

	//mutex for m_TestRecipeData access
	pthread_mutex_t m_TestRecipeDataMutex;
	
    //structure variable to store test recipe data
	TestRecipestruct m_TestRecipeData;

    //Test Recipe update flag
    bool m_IsTestRecipeUpdated;

	//Flag to initiate Save request
	bool m_InitiateTestRecipeSaveRequest;
	
	//Flag to initiate Reset To Default request
	bool m_InitiateTestRecipeResetToDefaultRequest;

	//Test Recipe read request is sent to ASC when this flag is true
	bool m_InitiateTestRecipeReadRequest;

	//Member variable to hold test recipe update status
	TEST_RECIPE_UPDATE_STATUS m_testRecipeStatus;

	//Send save test recipe data request to ASC
	void sendTestRecipeSaveRequestToASC(MEMORY_BLOCK * const destination);
	//Send reset to default test recipe data request to ASC
	void sendTestRecipeResetToDefaultRequestToASC(MEMORY_BLOCK * const destination);
	//initiate to send recipe read request to ASC
	void SendTestRecipeReadRequestToASC(MEMORY_BLOCK * const destination);
	//Process recipe read response
	void processTestRecipeReadResponseFromASC(const MEMORY_BLOCK *const source);
	//Process the Test recipe update status
	void processTestRecipeUpdateStatusFromASC(const MEMORY_BLOCK *const source);

    void InitiateTestRecipeSaveRequest();
};

#endif /* TESTRECIPE_H_ */

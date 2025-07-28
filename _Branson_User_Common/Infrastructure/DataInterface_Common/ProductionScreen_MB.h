/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the production screen related information

--------------------------- REVISION HISTORY ------------------------------

 rev1: 05/06/2023 - Initial implementation
 
***************************************************************************/

#ifndef PRODUCTIONSCREEN_MB_H_
#define PRODUCTIONSCREEN_MB_H_

#include "DataInterface.h"
#include "Common_Definitions.h"

// Size of recipe name
constexpr uint16_t  RECIPE_NAME_SIZE = 51;

// definition for SUB-ID of memory block
typedef enum{
    SUB_ID_DEFAULT = 1
}PRODUCTION_SCREEN_SUB_ID;

// Elements present at address pointed by Memoryblock::data
typedef struct{
    uint8_t     IsDataUpdated;						/* To know if MB's data is updated or not*/
    uint32_t    RecipeNum;                     		/* This variable to store recipe number*/
    char        RecipeName[RECIPE_NAME_SIZE]; 		/* This variable to store recipe name*/
    WELDMODES   WeldMode;                      		/* This variable to store weld mode*/
    float       WeldModeValue;                      /* This variable to store weld mode value */
    float       TotalCycleTime;           		    /* This variable to store total cycle time in seconds*/
    uint32_t    CycleCount;                    		/* This variable to store total cycle count*/
    uint32_t    CycleOKCount;                    	/* This variable to store cycle ok count*/
    uint32_t    CycleRejectCount;                   /* This variable to store cycle reject count*/
    uint32_t    CycleSuspectCount;                  /* This variable to store cycle suspect count*/
    uint32_t    BatchCount;                    		/* This variable to store batch count*/
    uint32_t    PartsPerMinuteCount;                /* This variable to store parts per minute count*/
    uint32_t    PeakPower;                		    /* This variable to store peak power */
    uint32_t    WelderID;                      		/* This variable to get selected welder info*/
    uint32_t    FrameCount;                    		/* This variable to exchange counter*/
    char        PartID[BARCODE_DATA_SIZE];          /* This variable will show the PartId scanned */
}__attribute__((packed)) ProdScreenData;

/* Definition of ProductionScreen_MB class - To Get/Set production screen related information */
class ProductionScreen_MB : public DataInterface
{
	/* variable declaration to store production screen related information */
	ProdScreenData m_ProductionScreenData;

	// locks for Read/write in Get/Set functions
	pthread_mutex_t m_ProductionScreenMutex;

public:

    // Read production screen data MB from DB
    int GetData(MEMORY_BLOCK * const destination) override;

    // Write production screen data MB into DB
    int SetData(const MEMORY_BLOCK *const source) override;
};

#endif /* PRODUCTIONSCREEN_MB_H_ */

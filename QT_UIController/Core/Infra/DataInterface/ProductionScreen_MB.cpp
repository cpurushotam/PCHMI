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
#include "ProductionScreen_MB.h"
#include <string.h>

/**************************************************************************//**
*
* \brief   - Read Production Screen related data. 
*            Read operation is performed based on Sub_ID of MB
*
* \param   - Address of destination MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ProductionScreen_MB::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    // check parameter
    if((destination != NULL) && (destination->id == MB_ID_PRODUCTION_DATA) && (destination->size >=sizeof(ProdScreenData)))
    {
        switch(destination->sub_id)
        {
            case SUB_ID_DEFAULT:
            {
                // locks get function
                pthread_mutex_lock(&m_ProductionScreenMutex);

                // cast MB data pointer to comm_stat_data for easy access
                ProdScreenData *peerProdScreenData = reinterpret_cast<ProdScreenData *>(destination->data);

                // copy counter value to destination
                strncpy(peerProdScreenData->RecipeName,   this->m_ProductionScreenData.RecipeName, RECIPE_NAME_SIZE);
                peerProdScreenData->RecipeNum           = this->m_ProductionScreenData.RecipeNum;
                peerProdScreenData->WeldMode            = this->m_ProductionScreenData.WeldMode;
                peerProdScreenData->WeldModeValue       = this->m_ProductionScreenData.WeldModeValue;
                peerProdScreenData->TotalCycleTime      = this->m_ProductionScreenData.TotalCycleTime;
                peerProdScreenData->CycleCount          = this->m_ProductionScreenData.CycleCount;
                peerProdScreenData->CycleOKCount        = this->m_ProductionScreenData.CycleOKCount;
                peerProdScreenData->CycleRejectCount    = this->m_ProductionScreenData.CycleRejectCount;
                peerProdScreenData->CycleSuspectCount   = this->m_ProductionScreenData.CycleSuspectCount;
                peerProdScreenData->BatchCount          = this->m_ProductionScreenData.BatchCount;
                peerProdScreenData->PartsPerMinuteCount = this->m_ProductionScreenData.PartsPerMinuteCount;
                peerProdScreenData->PeakPower      		= this->m_ProductionScreenData.PeakPower;
                strncpy(peerProdScreenData->PartID,   this->m_ProductionScreenData.PartID, BARCODE_DATA_SIZE);
                peerProdScreenData->IsDataUpdated       = this->m_ProductionScreenData.IsDataUpdated;

                // update size in destination
                destination->size = sizeof(ProdScreenData);

                // set valid bit
                destination->config = VALID_BIT;

                // update retval to success
                retVal = 0;

                // Unlock get function
                pthread_mutex_unlock(&m_ProductionScreenMutex);

                break;
            }
            default:
            {
                // Error ! default retVal (failure) will be returned
                // clear valid bit, reset size
                destination->size = 0;
                // clear valid bit
                destination->config = 0;
                break;
            }
        }
    }
    else
    {
        // error! invalid sub-id, default retVal (failure) will be returned
        // clear valid bit, reset size
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Write active recipe data. Write operation is performed based on Sub_ID of MB
*            Note: Write operation on own active recipe is not allowed.
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ProductionScreen_MB::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    // check parameter
    if((source != NULL) && (source->id == MB_ID_PRODUCTION_DATA) && ((source->config & VALID_BIT) == (VALID_BIT)))
    {
        switch(source->sub_id)
        {
            case SUB_ID_DEFAULT:
            {
                // locks get function
                pthread_mutex_lock(&m_ProductionScreenMutex);

                // cast MB data pointer to ProdScreenData for easy access
                ProdScreenData *peerProdScreen = reinterpret_cast<ProdScreenData *>(source->data);

                if (peerProdScreen->IsDataUpdated)
                {
                    strncpy(this->m_ProductionScreenData.RecipeName,   peerProdScreen->RecipeName, RECIPE_NAME_SIZE);
                    this->m_ProductionScreenData.PeakPower      	 = peerProdScreen->PeakPower;
                    this->m_ProductionScreenData.RecipeNum           = peerProdScreen->RecipeNum;
                    this->m_ProductionScreenData.WeldMode            = peerProdScreen->WeldMode;
                    this->m_ProductionScreenData.WeldModeValue       = peerProdScreen->WeldModeValue;
                    this->m_ProductionScreenData.CycleCount          = peerProdScreen->CycleCount;
                    this->m_ProductionScreenData.CycleOKCount        = peerProdScreen->CycleOKCount;
                    this->m_ProductionScreenData.CycleRejectCount    = peerProdScreen->CycleRejectCount;
                    this->m_ProductionScreenData.CycleSuspectCount   = peerProdScreen->CycleSuspectCount;
                    this->m_ProductionScreenData.BatchCount          = peerProdScreen->BatchCount;
                    this->m_ProductionScreenData.PartsPerMinuteCount = peerProdScreen->PartsPerMinuteCount;
                    this->m_ProductionScreenData.TotalCycleTime      = peerProdScreen->TotalCycleTime;
                    strncpy(this->m_ProductionScreenData.PartID, peerProdScreen->PartID, BARCODE_DATA_SIZE);
                    this->m_ProductionScreenData.IsDataUpdated       = peerProdScreen->IsDataUpdated;
                } 
                else
                {
                    this->m_ProductionScreenData.IsDataUpdated = 0;
                }

                // update retval to success
                retVal = 0;

                // Unlock get function
                pthread_mutex_unlock(&m_ProductionScreenMutex);

                break;
            }
            default:
            {
                // Error ! default retVal (failure) will be returned
                break;
            }
        }
    } else
    {
        // error! parameter check failed, default retVal (failure) will be returned
    }
    return (retVal);
}


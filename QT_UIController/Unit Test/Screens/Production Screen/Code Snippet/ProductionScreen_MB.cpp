/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
#include "ProductionScreen_MB.h"
#include <string.h>

/**************************************************************************//**
*
* \brief   - Read active reciepe data. Read operation is performed based on Sub_ID of MB
*
* \param   - Address of destination MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ProductionScreen::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    // check parameter
    if((destination != NULL) && (destination->id == PRODUCTION_SCREEN_DATA) && (destination->size >=sizeof(ProdScreenData)))
    {
        switch(destination->sub_id)
        {
            case SUB_ID_DEFAULT:
            {
                // cast MB data pointer to comm_stat_data for easy access
                ProdScreenData *peerProdScreenData = reinterpret_cast<ProdScreenData *>(destination->data);

                // copy counter value to destination
                strncpy(peerProdScreenData->RecipeName,   "Sample Recipe"/*this->m_ProductionScreenData.RecipeName*/, RECIEPE_NAME_SIZE);
                peerProdScreenData->RecipeNum           = this->m_ProductionScreenData.RecipeNum;
                peerProdScreenData->WeldMode            = this->m_ProductionScreenData.WeldMode;
                peerProdScreenData->WeldData            = this->m_ProductionScreenData.WeldData;
                peerProdScreenData->WeldUnit            = this->m_ProductionScreenData.WeldUnit;
                peerProdScreenData->TotalCycleTimeInSec = this->m_ProductionScreenData.TotalCycleTimeInSec;
                peerProdScreenData->CycleCount          = this->m_ProductionScreenData.CycleCount;
                peerProdScreenData->PeakPowerRatio      = this->m_ProductionScreenData.PeakPowerRatio;
                peerProdScreenData->IsDataUpdated       = this->m_ProductionScreenData.IsDataUpdated;

                // update size in destination
                destination->size = sizeof(ProdScreenData);

                // set valid bit
                destination->config = VALID_BIT;

                // update retval to success
                retVal = 0;

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
* \brief   - Write active reciepe data. Write operation is performed based on Sub_ID of MB
*            Note: Write operation on own active reciepe is not allowed.
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ProductionScreen::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    // check parameter
    if((source != NULL) && (source->id == PRODUCTION_SCREEN_DATA) && ((source->config & VALID_BIT) == (VALID_BIT)))
    {
        switch(source->sub_id)
        {
            case SUB_ID_DEFAULT:
            {
                // cast MB data pointer to ProdScreenData for easy access
                ProdScreenData *peerProdScreen = reinterpret_cast<ProdScreenData *>(source->data);

                if (peerProdScreen->IsDataUpdated)
                {
                    strncpy(this->m_ProductionScreenData.RecipeName,   peerProdScreen->RecipeName, RECIEPE_NAME_SIZE);
                    this->m_ProductionScreenData.PeakPowerRatio      = peerProdScreen->PeakPowerRatio;
                    this->m_ProductionScreenData.RecipeNum           = peerProdScreen->RecipeNum;
                    this->m_ProductionScreenData.WeldMode            = peerProdScreen->WeldMode;
                    this->m_ProductionScreenData.WeldData            = peerProdScreen->WeldData;
                    this->m_ProductionScreenData.WeldUnit            = peerProdScreen->WeldUnit;
                    this->m_ProductionScreenData.CycleCount          = peerProdScreen->CycleCount;
                    this->m_ProductionScreenData.TotalCycleTimeInSec = peerProdScreen->TotalCycleTimeInSec;
                    this->m_ProductionScreenData.IsDataUpdated       = peerProdScreen->IsDataUpdated;
                } else
                {
                    this->m_ProductionScreenData.IsDataUpdated = 0;
                }

                // update retval to success
                retVal = 0;

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


/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps maintains general recipe information.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/07/2023 - Initial version.
***************************************************************************/

#include "recipegeneral.h"
/**************************************************************************//**
*
* \brief Constructor and initialize as following variables...
*        1. m_iRecipeNumber;
*        2. m_strRecipeName;
*        3. m_strCompanyName;
*        4. m_iWeldMode;
*        5. m_iModeUnit;
*        6. m_iWeldModeValue;
*        7. m_bActiveStatus;
*        8. m_bValidateStatus;
*        9. m_bModifiedStatus;
*        10. m_bNewCardStatus;
*        11. m_iCycleCount
*
* \param none
*
* \return none
*
******************************************************************************/
RecipeGeneral::RecipeGeneral()
    :m_iRecipeNumber(-1)
    ,m_strRecipeName("N/A")
    ,m_iWeldMode(RecipeEnum::NONE_IDX)
    ,m_iModeUnit(0)
    ,m_iWeldModeValue(0)
    ,m_bActiveStatus(false)
    ,m_bValidateStatus(false)
    ,m_bModifiedStatus(false)
    ,m_bNewCardStatus(true)
    ,m_iCycleCount(0)
    ,m_iRecipeVersionInfo(0)
{

}

/**************************************************************************//**
*
* \brief Constructor and initialize as following variables...
*        1. m_iRecipeNumber;
*        2. m_strRecipeName;
*        3. m_strCompanyName;
*        4. m_iWeldMode;
*        5. m_iModeUnit;
*        6. m_iWeldModeValue;
*        7. m_bActiveStatus;
*        8. m_bValidateStatus;
*        9. m_bModifiedStatus;
*        10. m_bNewCardStatus;
*        11. m_iCycleCount;
*        12. m_iRecipeVersionInfo
*
* \param 1. iRecipeNum: Recipe Number;
*        2. strRecipeName: Recipe Name
*        3. strCompanyName: Customer Company Name
*        4. iWeldMode: Weld Mode enum that defined in recipedef.h
*        5. iWeldModeUnit: the value unit related to the specific weld mode of the recipe card.
*        6. iWeldModeValue: the value related to the specific weld mode of the recipe card.
*        7. bActiveStatus: active status
*        8. bValidateStatus: validate status
*        9. bModifiedStatus: modified status
*        10. bNewCardStatus: Is the new card for creating
*        11. iCycleCount: cycle count
*        12. iRecipeVersionInfo: Recipe Version
*
* \return none
*
******************************************************************************/
RecipeGeneral::RecipeGeneral(const int &iRecipeNum, const QString &strRecipeName,
                         const int &iWeldMode,
                         const int iWeldModeUnit, float iWeldModeValue,
                         const bool &bActiveStatus, const bool &bValidateStatus,
                         const bool &bModifiedStatus, const bool &bNewCardStatus, const int &iCycleCount, const int &iRecipeVersionInfo, const int &bRecipeSaveStatus)
    :m_iRecipeNumber(iRecipeNum)
    ,m_strRecipeName(strRecipeName)
    ,m_iWeldMode(iWeldMode)
    ,m_iModeUnit(iWeldModeUnit)
    ,m_iWeldModeValue(iWeldModeValue)
    ,m_bActiveStatus(bActiveStatus)
    ,m_bValidateStatus(bValidateStatus)
    ,m_bModifiedStatus(bModifiedStatus)
    ,m_bNewCardStatus(bNewCardStatus)
    ,m_iCycleCount(iCycleCount)
    ,m_iRecipeVersionInfo(iRecipeVersionInfo)
    ,m_bRecipeSaveStatus(bRecipeSaveStatus)
{

}

/**************************************************************************//**
*
* \brief To get the Recipe Number
*
* \param none
*
* \return the recipe number of the object.
*
******************************************************************************/
int RecipeGeneral::getRecipeNumber() const
{
    return m_iRecipeNumber;
}

/**************************************************************************//**
*
* \brief To get the Recipe Name
*
* \param none
*
* \return the recipe name of the object
*
******************************************************************************/
QString RecipeGeneral::getRecipeName() const
{
    return m_strRecipeName;
}

/**************************************************************************//**
*
* \brief To get the weld mode enum index
*
* \param none.
*
* \return the weld mode enum index of the object.
*
******************************************************************************/
int RecipeGeneral::getWeldModeEnum() const
{
    return m_iWeldMode;
}

/**************************************************************************//**
*
* \brief To get the value unit that related to the specific weld mode of the recipe
*
* \param none.
*
* \return the parameter unit string.
*
******************************************************************************/
int RecipeGeneral::getWeldModeUnit() const
{
    return m_iModeUnit;
}

/**************************************************************************//**
*
* \brief To get the value that related to the specific weld mode of the recipe.
*
* \param none
*
* \return the parameter value string.
*
******************************************************************************/
float RecipeGeneral::getWeldModeValue() const
{
    return m_iWeldModeValue;
}

/**************************************************************************//**
*
* \brief To get the recipe active status.
*       The flag is used for the recipe what will be available for the current weld cycle.
*
* \param none.
*
* \return the boolean active status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeActiveStatus() const
{
    return m_bActiveStatus;
}

/**************************************************************************//**
*
* \brief
*
* \param
*
* \return
*
******************************************************************************/
void RecipeGeneral::setRecipeActiveStatus(const int activeflag)
{
    if(m_bActiveStatus != activeflag)
        m_bActiveStatus = activeflag;
}

/**************************************************************************//**
*
* \brief To get the recipe validate status
*
* \param none
*
* \return the boolean validate status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeValidateStatus() const
{
    return m_bValidateStatus;
}

/**************************************************************************//**
*
* \brief To get the recipe modified status.
*        If there is any change of the recipe without saved, the status will be set true.
*
* \param none
*
* \return the boolean modified status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeModifiedStatus() const
{
    return m_bModifiedStatus;
}

/**************************************************************************//**
*
* \brief To get the new card status.
*        If the recipe card is the empty, the flag is the true.
*
* \param none.
*
* \return the boolean new card status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeNewCardStatus() const
{
    return m_bNewCardStatus;
}

/**************************************************************************//**
*
* \brief To get the recipe cycle count
*
* \param none
*
* \return the integer cycle count
*
******************************************************************************/
int RecipeGeneral::getRecipeWeldCycleCount() const
{
    return m_iCycleCount;
}

/**************************************************************************//**
*
* \brief To set the recipe cycle count.
*        If the numnber is not equal to the m_iCycleCount, the m_iCycleCount will be reset with the cycleNumber.
*
* \param cycleNumber: the new number that will be set to the m_iCycleCount
*
* \return none.
*
******************************************************************************/
void RecipeGeneral::setRecipeWeldCycleCount(const int cycleNumber)
{
    if(m_iCycleCount != cycleNumber)
        m_iCycleCount = cycleNumber;
}

/**************************************************************************//**
*
* \brief To get the recipe version information.
*
* \param none
*
* \return The recipe version information.
*
******************************************************************************/
int RecipeGeneral::getRecipeVersionInfo() const
{
    return m_iRecipeVersionInfo;
}

/**************************************************************************//**
*
* \brief To get the recipe save status.
*
* \param none
*
* \return The recipe save status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeSaveStatus() const
{
    return m_bRecipeSaveStatus;
}


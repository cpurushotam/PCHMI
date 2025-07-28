/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailsListData.h file provides cycle detail list container data
    handled by CycleDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 12/10/2023 - Initial version.
***************************************************************************/
#include "CycleDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the following variables...
*           m_CycleIndex
*           m_RecipeNo
            m_CycleNo
            m_RecipeMode
            m_CycleDateTime
*
* \param  - None
*
* \return - None
*
******************************************************************************/
CycleDetailsListData::CycleDetailsListData()
{

}

CycleDetailsListData::CycleDetailsListData(const int& p_CycleIndex, const int& p_RecipeNo, const int& p_CycleNo, const int& p_RecipeMode, const QString& p_CycleDateTime,
                                           const float& p_TriggerPoint, const float& p_WeldSonicPoint, const float& p_HoldPoint, const int& p_WeldResultIndex)
    : m_CycleIndex(p_CycleIndex),
      m_RecipeNo(p_RecipeNo),
      m_CycleNo(p_CycleNo),
      m_RecipeMode(p_RecipeMode),
      m_CycleDateTime(p_CycleDateTime),
      m_TriggerPoint(p_TriggerPoint),
      m_WeldSonicPoint(p_WeldSonicPoint),
      m_HoldPoint(p_HoldPoint),
      m_WeldResultIdx(p_WeldResultIndex)

{

}

/**************************************************************************//**
*
* \brief   - Below function returns the weld cycle index.
*
* \param   - None.
*
* \return  - m_CycleIndex
******************************************************************************/
int CycleDetailsListData::getCycleIndex() const
{
    return m_CycleIndex;
}


/**************************************************************************//**
*
* \brief   - Below function returns the recipe number.
*
* \param   - None.
*
* \return  - m_RecipeNo.
******************************************************************************/
int CycleDetailsListData::getRecipeNo() const
{
    return m_RecipeNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld cycle number.
*
* \param   - None.
*
* \return  - m_CycleNo : Weld Cycle number.
******************************************************************************/
int CycleDetailsListData::getCycleNo() const
{
    return m_CycleNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe mode.
*
* \param   - None.
*
* \return  - m_RecipeMode.
******************************************************************************/
int CycleDetailsListData::getRecipeMode() const
{
    return m_RecipeMode;
}
/**************************************************************************//**
*
* \brief   - Below function returns the WeldResult Index .
*
* \param   - None.
*
* \return  - m_WeldResultIdx.
******************************************************************************/
int CycleDetailsListData::getWeldResultIndex() const
{
    return m_WeldResultIdx;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld cycle date and time.
*
* \param   - None.
*
* \return  - m_CycleNo : Weld Cycle date and time.
******************************************************************************/
QString CycleDetailsListData::getCycleDateTime() const
{
    return m_CycleDateTime;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld cycle trigger time.
*
* \param   - None.
*
* \return  - m_TriggerPoint.
******************************************************************************/
float CycleDetailsListData::getTriggerPoint() const
{
    return m_TriggerPoint;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld sonic time.
*
* \param   - None.
*
* \return  - m_WeldSonicPoint.
******************************************************************************/
float CycleDetailsListData::getWeldSonicPoint() const
{
    return m_WeldSonicPoint;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld hold time.
*
* \param   - None.
*
* \return  - m_HoldPoint.
******************************************************************************/
float CycleDetailsListData::getHoldPoint() const
{
    return m_HoldPoint;
}



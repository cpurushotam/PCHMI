/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanCycleDetailsListData.h file provides cycle detail list container data
    handled by CycleDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 03/04/2024 - Initial version.
***************************************************************************/
#include "ScanCycleDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the following variables...
*           m_CycleIndex
            m_CycleDateTime
*
* \param  - None
*
* \return - None
*
******************************************************************************/
ScanCycleDetailsListData::ScanCycleDetailsListData()
{

}

ScanCycleDetailsListData::ScanCycleDetailsListData(const int& p_CycleIndex, const QString& p_CycleDateTime)
    : m_CycleIndex(p_CycleIndex),
      m_CycleDateTime(p_CycleDateTime)

{

}

/**************************************************************************//**
*
* \brief   - Below function returns the scan cycle index.
*
* \param   - None.
*
* \return  - m_CycleIndex
******************************************************************************/
int ScanCycleDetailsListData::getCycleIndex() const
{
    return m_CycleIndex;
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan cycle date and time.
*
* \param   - None.
*
* \return  - m_CycleNo : Weld Cycle date and time.
******************************************************************************/
QString ScanCycleDetailsListData::getCycleDateTime() const
{
    return m_CycleDateTime;
}




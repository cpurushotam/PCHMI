/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file filters the data from cycleDetailsTableModel to show
    weld data excluding reference graph data in qml.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
***************************************************************************/

#include "ResultViewWeldProxyModel.h"

/**************************************************************************//**
*
* \brief  - Result View Table Proxy Model Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/

ResultViewWeldProxyModel::ResultViewWeldProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

/**************************************************************************//**
*
* \brief  - get reference graph data and weld result data to create filter list.
*
* \param  - RequestedReferenceGraphData : reference graph data
*           WeldResultData : weld result data
*
* \return - None.
*
******************************************************************************/

void ResultViewWeldProxyModel::getWeldAndReferneceDataList(std::deque<ReferenceGraphStruct> RequestedReferenceGraphData, std::deque<WeldResultACEStruct> WeldResultData)
{
    m_RequestedReferenceGraphData = RequestedReferenceGraphData;
    m_WeldResultData = WeldResultData;
    modifyWeldGraphList();
    invalidateFilter();
    invalidateRowsFilter();
}

/**************************************************************************//**
*
* \brief  - modify Reference Graph List accourding to weld result data
*           and reference graph data.
*
* \param  - None.
*
* \return -  none.
*
******************************************************************************/

void ResultViewWeldProxyModel::modifyWeldGraphList()
{
    hiddenRowsList.clear();
    for(int i = 0; i < m_WeldResultData.size(); i++)
    {
        for(int j = 0; j < m_RequestedReferenceGraphData.size(); j++)
        {
            if(m_WeldResultData.at(i).WeldResultIndex == m_RequestedReferenceGraphData.at(j).RefweldResultIndex)
            {
                hiddenRowsList.append(i);
            }
        }
    }
}

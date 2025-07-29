/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This class is inherited from the "QSortFilterProxyModel". This class
    acts as a filter for "CycleDetailtablemodel" to filter the table data
    as per reference graph.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
***************************************************************************/

#include "ResultViewTableProxyModel.h"

/**************************************************************************//**
*
* \brief  - Result View Table Proxy Model Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/

ResultViewTableProxyModel::ResultViewTableProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    invalidateFilter();
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

void ResultViewTableProxyModel::getWeldAndReferneceDataList(std::deque<ReferenceGraphStruct> RequestedReferenceGraphData, std::deque<WeldResultACEStruct> WeldResultData)
{
    m_RequestedReferenceGraphData = RequestedReferenceGraphData;
    m_WeldResultData = WeldResultData;
    modifyReferenceGraphList();
}

/**************************************************************************//**
*
* \brief  - get filtered number of rows of a model.
*
* \param  - None.
*
* \return - hiddenRowsList.size() : filtered number of rows of a model.
*
******************************************************************************/

int ResultViewTableProxyModel::getNumberOfRows()
{
    return hiddenRowsList.size();
}

/**************************************************************************//**
*
* \brief  - get all cycle numbers in string.
*
* \param  - None.
*
* \return - cycleDetailString : all cycle numbers string..
*
******************************************************************************/

QString ResultViewTableProxyModel::getAllCycleNumber()
{
    QString cycleDetailString;
    cycleDetailString.clear();
    for(int i = 0; i < cycleDetailsList.size(); i++)
    {
        cycleDetailString.append(QString::number(cycleDetailsList.at(i)) + ",");
    }
    cycleDetailString.chop(LAST_COMMA);
    return cycleDetailString;
}


/**************************************************************************//**
*
* \brief  - remove Data from m_selectedCycleDetailsList List.
*
* \param  - index : index of list to hide data.
*
* \return -  None.
*
******************************************************************************/

void ResultViewTableProxyModel::removeDataFromList(int index)
{
     if(m_selectedCycleDetailsList.size() > index)
     {
         m_selectedCycleDetailsList.replace(index,UNSELECTED);
         invalidateFilter();
         emit rowCountChanged();
     }
}

/**************************************************************************//**
*
* \brief  - append Data to m_selectedCycleDetailsList List.
*
* \param  - index : index of list to append data.
*
* \return -  None.
*
******************************************************************************/

void ResultViewTableProxyModel::appendDataToList(int index)
{
    if(m_selectedCycleDetailsList.size() > index)
    {
        m_selectedCycleDetailsList.replace(index,SELECTED);
        invalidateFilter();
        emit rowCountChanged();
    }
}

/**************************************************************************//**
*
* \brief  - get count of reference graphs as selected in dropdown list.
*
* \param  - None.
*
* \return -  visibleRowCount : count of reference graphs.
*
******************************************************************************/

int ResultViewTableProxyModel::getVisibleRowCount()
{
    int visibleRowCount = 0;
    for(int i = 0; i < m_selectedCycleDetailsList.size(); i++)
    {
        if(m_selectedCycleDetailsList.at(i) == SELECTED)
        {
            visibleRowCount++;
        }
    }
    return visibleRowCount;
}

/**************************************************************************//**
*
* \brief  - To hide the reference graph data from second table.
*
* \param  - sourceRow : The row number in the source model to be evaluated.
*           source_parent : The parent index of the row in the source model
*
* \return -  true to show table and false to hide the row.
*
******************************************************************************/

bool ResultViewTableProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &source_parent) const
{
    if(hiddenRowsList.contains(sourceRow))
    {
        int indexAtRow = hiddenRowsList.indexOf(sourceRow);
        if(m_selectedCycleDetailsList.at(indexAtRow) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**************************************************************************//**
*
* \brief  - get Cycle Number From cycleDetailsList.
*
* \param  - index : index of list.
*
* \return -  Cycle Number.
*
******************************************************************************/

QString ResultViewTableProxyModel::getCycleNumberForListView(int index)
{
    return QString::number(cycleDetailsList.at(index));
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

void ResultViewTableProxyModel::modifyReferenceGraphList()
{
    hiddenRowsList.clear();
    cycleDetailsList.clear();
    m_selectedCycleDetailsList.clear();
    for(int i = 0; i < m_WeldResultData.size(); i++)
    {
        for(int j = 0; j < m_RequestedReferenceGraphData.size(); j++)
        {
            if(m_WeldResultData.at(i).WeldResultIndex == m_RequestedReferenceGraphData.at(j).RefweldResultIndex)
            {
                hiddenRowsList.append(i);
                cycleDetailsList.append(m_WeldResultData.at(i).CycleCounter);
                m_selectedCycleDetailsList.append(SELECTED);
            }
        }
    }
    emit rowCountChanged();
    invalidateRowsFilter();
    invalidateFilter();
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




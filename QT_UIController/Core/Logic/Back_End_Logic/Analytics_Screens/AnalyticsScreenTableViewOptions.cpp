/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AnalyticsScreenTableViewOptions.cpp file provides cycle detail list container data
    handeled by CycleDetailsListModelto hide and show columns according to checks.
***************************************************************************/
#include "AnalyticsScreenTableViewOptions.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
AnalyticsScreenTableViewOptions::AnalyticsScreenTableViewOptions() {
    for(int i =0;i<ParameterList;i++){
        hiddenRowsList.append(i);
    }
    m_cycleCounter = 0;
}
/**************************************************************************//**
*
* \brief   - Below function provide Column Checked List and Show the table content
*            according to the check and uncheck the parameters.
*
* \param   - indexes : Indexes of parameters.
*
* \return  - None.
******************************************************************************/
void AnalyticsScreenTableViewOptions::getColumnCheckedList(const QVariantList &indexes)
{
    hiddenRowsList.clear();
    for (int i = 0; i < indexes.size(); i++)
    {
        setChooseParameterIndex(i,indexes.at(i).toBool());
        if(indexes.at(i).toBool())
        {
            hiddenRowsList.append(i);
        }
    }
    invalidateColumnsFilter();
}
/**************************************************************************//**
*
* \brief   - To show the parameter list selected by user.
*
** \param  - sourceRow : The row number in the source model to be evaluated.
*           source_parent : The parent index of the row in the source mode
*
* \return  - None.
******************************************************************************/
bool AnalyticsScreenTableViewOptions::filterAcceptsColumn(int sourceRow, const QModelIndex &source_parent) const
{
     return hiddenRowsList.contains(sourceRow);
}
/**************************************************************************//**
*
* \brief   - To show the row containing the search cycle counter.
*
** \param  - sourceRow : The row number in the source model to be evaluated.
*           source_parent : The parent index of the row in the source mode
*
* \return  - None.
******************************************************************************/
bool AnalyticsScreenTableViewOptions::filterAcceptsRow(int sourceRow, const QModelIndex &source_parent) const
{
    if(m_cycleCounter != 0){
        if(rowFilterIndex == sourceRow)
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
        return true;
    }
}
/**************************************************************************//**
*
* \brief   - Below function set the parameters indexes in INI File.
*
* \param   - index : Indexes of parameters, val - Setting value.
*
* \return  - None.
******************************************************************************/
void AnalyticsScreenTableViewOptions::setChooseParameterIndex(int index, bool val)
{
    ACTUATOR_TYPE sysType = static_cast<ACTUATOR_TYPE>(m_SystemConfiguration->getCurrentSystemType());
    if(sysType == ACTUATOR_MANUAL )
    {
        QSettings settings(settingINIFilePath,QSettings::IniFormat);
        settings.beginGroup(Manual);
        settings.setValue(QString::number(index),val);
        settings.endGroup();
    }
    else
    {
        QSettings settings(settingINIFilePath,QSettings::IniFormat);
        settings.beginGroup(Electric);
        settings.setValue(QString::number(index),val);
        settings.endGroup();
    }
}
/**************************************************************************//**
*
* \brief   - Below function get the parameters indexes from the  INI File.
*
* \param   - indexes : Indexes of parameters.
*
* \return  - None.
******************************************************************************/
bool AnalyticsScreenTableViewOptions::getChooseParameterIndex(int index)
{
    bool idndexVal;
    ACTUATOR_TYPE sysType = static_cast<ACTUATOR_TYPE>(m_SystemConfiguration->getCurrentSystemType());
    if(sysType == ACTUATOR_MANUAL )
    {
        QSettings settings(settingINIFilePath,QSettings::IniFormat);
        settings.beginGroup(Manual);
        idndexVal = settings.value(QString::number(index)).toBool();
        settings.endGroup();
    }
    else
    {
        QSettings settings(settingINIFilePath,QSettings::IniFormat);
        settings.beginGroup(Electric);
        idndexVal = settings.value(QString::number(index)).toBool();
        settings.endGroup();
    }
    return idndexVal;
}
/**************************************************************************//**
*
* \brief   - This function gets weld data.
*
* \param   - weldResultData : weld details list.
*
* \return  - None.
******************************************************************************/
void AnalyticsScreenTableViewOptions::getWeldResultList(std::deque<WeldResultACEStruct> weldResultData)
{

    m_WeldResultData = weldResultData;
}
/**************************************************************************//**
*
* \brief   - This function gets searched item.
*
* \param   - searchCycleCount : searched string.
*
* \return  - None.
******************************************************************************/
void AnalyticsScreenTableViewOptions::getSearchData(QString searchCycleCount)
{
    qDebug()<<"searchCycleCount :"<< searchCycleCount;
    if(searchCycleCount.isEmpty())
    {
        m_cycleCounter = 0;
        filterData();
    }
    else
    {
        bool ok;
        m_cycleCounter = searchCycleCount.toInt(&ok);
        if(ok)
        {
            filterData();
        }
        else{
            m_cycleCounter = 0;
            filterData();
        }
    }
}
/**************************************************************************//**
*
* \brief   - This function is use to filter data and set filter row number.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AnalyticsScreenTableViewOptions::filterData()
{
    rowFilterIndex = -1;
    for(int i = 0; i < m_WeldResultData.size(); i++)
    {
        if(m_WeldResultData.at(i).CycleCounter == m_cycleCounter)
        {
            rowFilterIndex = i;
        }
    }
    invalidateRowsFilter();
}

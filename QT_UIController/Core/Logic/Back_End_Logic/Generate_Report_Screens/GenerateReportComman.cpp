/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReportComman.cpp file provides mode details and status of button and checkboxses.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 17/02/2025 - Initial version.
***************************************************************************/
/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    EventLogListData.h file file provides Eventlog detail listmodel which is used by QMl

***************************************************************************/
#include "GenerateReportComman.h"
#include <thread>
#include <iostream>

/**************************************************************************//**
*
* \brief  - Constructor to initialize the  variables required under generate report screen data display.
*
*
* \param  - None
*
* \return - None
*
******************************************************************************/
GenerateReportComman::GenerateReportComman(QObject *parent)
{
    if(m_ReportManger == nullptr)
    {
        return;
    }
    connect(UpdateScreen::getInstance(), &UpdateScreen::GenerateReportSummaryScreenUpdated, this, &GenerateReportComman::onSingleGenerateReportUpdated);
}

GenerateReportComman::~GenerateReportComman()
{

}
/**************************************************************************//**
*
* \brief   - Below function setting the filter mode of data filter of generate report.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::setMode(QString filterMode, int index, bool checkState)
{
    if(checkState)
    {
        m_mode[index].m_filterMode = filterMode;
    }
    else{
        m_mode[index].m_filterMode.clear();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the filter mode from given index.
*
* \param   - None.
*
* \return  - QString - m_mode[index].m_filterMode.
******************************************************************************/
QString GenerateReportComman::getMode(int index)
{
    return m_mode[index].m_filterMode;
}
/**************************************************************************//**
*
* \brief   - Below function cheking the checks of deleted record.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::setDeleteRecord(bool deleteRecordchecks, int index)
{
    m_mode[index].m_deleterecordchecks = deleteRecordchecks;
}
/**************************************************************************//**
*
* \brief   - Below function returns the  need to delete record data from database.
*
* \param   - None.
*
* \return  - QString - m_mode[index].m_deleterecordchecks.
******************************************************************************/
bool GenerateReportComman::getDeleteRecord(int index)
{
    return m_mode[index].m_deleterecordchecks ;
}
/**************************************************************************//**
*
* \brief   - Below function returns the  status of checked data filters.
*
* \param   - None.
*
* \return  - bool - true/false.
******************************************************************************/
bool GenerateReportComman::getCheckedFilterModeStatus(int index)
{
    if(m_mode[index].m_filterMode.isEmpty()){
        return false;
    }else{
        return true;
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the  status of checked data filters.
*
* \param   - None.
*
* \return  - bool - true/false.
******************************************************************************/
void GenerateReportComman::onSingleGenerateReportUpdated(ReportManager *ReportManager_Obj)
{

    if(ReportManager_Obj == NULL){
        return;
    }else{

        m_ReportManger = ReportManager_Obj;
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the  list of mode selcted from the row.
*
* \param   - None.
*
* \return  - QString - modelist.
******************************************************************************/
QString GenerateReportComman::getDatafiltersList()
{
    QString modelist;
    for(int i=0;i<m_ModeListCount;i++){
        if(!m_mode[i].m_filterMode.isEmpty()){
            modelist.append(m_mode[i].m_filterMode);
            modelist.append(" - ");
        }
    }
    modelist.remove(modelist.size() - 3, 3);

    return modelist;
}
/**************************************************************************//**
*
* \brief   - Below function  clear the list for second itteration usage.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::ClearTheFilterList()
{   
    for(int i=0;i<m_ModeListCount;i++){
       m_mode[i].m_filterMode.clear();
       m_mode[i].m_deleterecordchecks = false;
    }

}
/**************************************************************************//**
*
* \brief   - Below function update type of report selected from HMI.
*
* \param   - reportType.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::updateReportType(bool reportType)
{

}
/**************************************************************************//**
*
* \brief   - Below function update type of format selected from HMI.
*
* \param   - formatType.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onCheckboxSelectionFormatType(int formatType)
{
    if(formatType == 0){

        m_ReportConfig.SelectReportFormat(REPORT_FORMATS::CSV);
    }else{
        m_ReportConfig.SelectReportFormat(REPORT_FORMATS::PDF);
    }
}

/**************************************************************************//**
*
* \brief   - Below function update type of StorageOption selected from HMI.
*
* \param   - storgaeOption.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onCheckboxSelectionStorageOption(int storgaeOption)
{
    if(storgaeOption == 0){
        m_ReportConfig.SelectStorageOption(STORAGE_OPTIONS::USB);
    }else{
        m_ReportConfig.SelectStorageOption(STORAGE_OPTIONS::NFS);
    }
}
/**************************************************************************//**
*
* \brief   - Below function update type of dataFilter selected from HMI.
*
* \param   - dataFilter.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onCheckboxSelectionDataFilter(int dataFilter)
{
    if(dataFilter == 1){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::WELD_RESULT_RERORT);
    }else if(dataFilter == 2){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::WELD_GRAPH_REPORT);
    }else if(dataFilter == 4){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::ALARM_LOG_REPORT);
    }else if(dataFilter == 8){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::EVENT_LOG_REPORT);
    } else if(dataFilter == 16){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::HORN_SCAN_RESULT_REPORT);
    }else if(dataFilter == 32){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::HORN_SCAN_SIGNATURE_REPORT);
    } else if(dataFilter == 64){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::REFERENCE_WELD_SIGNATURE_REPORT);
    }else if(dataFilter == 128){
        m_ReportConfig.SelectReport(REPORT_CATEGORY::CALIBRATION_DATA_REPORT);
    }
}
/**************************************************************************//**
*
* \brief   - Below function update type of report need to delete from HMI.
*
* \param   - reportType.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onSelectDeleteReport(int reportType)
{
    if(reportType == 1){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::WELD_RESULT_RERORT);
    }else if(reportType == 2){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::WELD_GRAPH_REPORT);
    }else if(reportType == 4){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::ALARM_LOG_REPORT);
    }else if(reportType == 8){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::EVENT_LOG_REPORT);
    } else if(reportType == 16){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::HORN_SCAN_RESULT_REPORT);
    }else if(reportType == 32){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::HORN_SCAN_SIGNATURE_REPORT);
    } else if(reportType == 64){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::REFERENCE_WELD_SIGNATURE_REPORT);
    }else if(reportType == 128){
        m_ReportConfig.DeleteReport(REPORT_CATEGORY::CALIBRATION_DATA_REPORT);
    }
}
/**************************************************************************//**
*
* \brief   - Below function update type of report need to deselect from HMI.
*
* \param   - reportType.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onDeSelectDeleteReport(int reportType)
{
    if(reportType == 1){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::WELD_RESULT_RERORT);
    }else if(reportType == 2){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::WELD_GRAPH_REPORT);
    }else if(reportType == 4){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::ALARM_LOG_REPORT);
    }else if(reportType == 8){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::EVENT_LOG_REPORT);
    } else if(reportType == 16){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::HORN_SCAN_RESULT_REPORT);
    }else if(reportType == 32){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::HORN_SCAN_SIGNATURE_REPORT);
    } else if(reportType == 64){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::REFERENCE_WELD_SIGNATURE_REPORT);
    }else if(reportType == 128){
        m_ReportConfig.ResetDeleteReport(REPORT_CATEGORY::CALIBRATION_DATA_REPORT);
    }
}
/**************************************************************************//**
*
* \brief   - Below function Initiate the generate report request from HMI.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onGenerateReportClicked()
{
    m_ReportManger->InitiateReportGenerationRequest(m_ReportConfig);
    m_ReportConfig.resetToDefault();
}
/**************************************************************************//**
*
* \brief   - Below function show the progress status changed on HMI.
*
* \param   - None.
*
* \return  - PROGRESS_STATUS.
******************************************************************************/
PROGRESS_STATUS GenerateReportComman::onStatusChanged()
{
    return m_ReportManger->GetReportGenerationProgressStatus();
}
/**************************************************************************//**
*
* \brief   - Below function deselect the Data filter .
*
* \param   - dataFilter.
*
* \return  - None.
******************************************************************************/
void GenerateReportComman::onDeSelectReport(int dataFilter)
{
    if(dataFilter == 1){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::WELD_RESULT_RERORT);
    }else if(dataFilter == 2){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::WELD_GRAPH_REPORT);
    }else if(dataFilter == 4){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::ALARM_LOG_REPORT);
    }else if(dataFilter == 8){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::EVENT_LOG_REPORT);
    } else if(dataFilter == 16){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::HORN_SCAN_RESULT_REPORT);
    }else if(dataFilter == 32){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::HORN_SCAN_SIGNATURE_REPORT);
    } else if(dataFilter == 64){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::REFERENCE_WELD_SIGNATURE_REPORT);
    }else if(dataFilter == 128){
        m_ReportConfig.DisselectReport(REPORT_CATEGORY::CALIBRATION_DATA_REPORT);
    }
}


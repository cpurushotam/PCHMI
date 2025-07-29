/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReport Data Filter file show optin for single report filter options .

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.LoginIndexEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {

    id: datafilters
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_DATA_FILTERS
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextDataFilter                       : "DATA"
    property string qmltextOutput                           : "OUTPUT"
    property string qmltextUsb                              : "USB"
    property string qmltextEthernet                         : "ETHERNET"
    property string qmltextCSV                              : "CSV"
    property string qmltextPdf                              : "PDF"
    property string qmltextStorgeOutput                     : "STORAGE"
    property string qmltextDataFilters                      : "DATA"
    property string qmltextSummary                          : "SUMMARY"
    property string qmltextSingle                           : "SINGLE"
    property string qmltextContinuous                       : "CONTINUOUS"
    property string qmltextNext                             : "NEXT"
    property string qmltextPrevious                         : "PREVIOUS"
    property string qmltextMenuName                         : "Generate Report"
    property string qmltextDeleteRecordFromDatabase         : "Delete record from database"
    property string qmltextWeldResults                      : "Weld Results"
    property string qmltextWeldSignatures                   : "WeldSignatures"
    property string qmltextAlarmData                        : "AlarmData"
    property string qmltextEventData                        : "EventData"
    property string qmltextHornScanResults                  : "HornScanResults"
    property string qmltextHornScanSignatures               : "HornScanSignatures"
    property string qmltextRefrenceWeldSignatures           : "RefrenceWeldSignatures"
    property string qmltextCalibrationData                  : "CalibrationData"
    property string qmltextStorgeOutput2                    : "& OUTPUT"
    property string qmltextDataFilters2                     : "FILTERS"

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextDataFilter, qmltextOutput,
    qmltextUsb, qmltextEthernet, qmltextCSV, qmltextPdf, qmltextStorgeOutput, qmltextDataFilters, qmltextSummary, qmltextSingle, qmltextContinuous,
    qmltextNext, qmltextPrevious, qmltextMenuName, qmltextDeleteRecordFromDatabase, qmltextWeldResults, qmltextWeldSignatures, qmltextAlarmData, qmltextEventData,
    qmltextHornScanResults, qmltextHornScanSignatures, qmltextRefrenceWeldSignatures, qmltextCalibrationData, qmltextDataFilters2, qmltextStorgeOutput2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_DATA_FILTERS , qmlTextArray)
        qmltextTabBarGenerateReport        = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmltextTabBarSavedReport           = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmltextType                        = qmlTextArray[textEnum.textTypeIdx]
        qmltextDataFilter                  = qmlTextArray[textEnum.textDataFilterIdx]
        qmltextOutput                      = qmlTextArray[textEnum.textOutputIdx]
        qmltextUsb                         = qmlTextArray[textEnum.textUsbIdx]
        qmltextEthernet                    = qmlTextArray[textEnum.textEthernetIdx]
        qmltextCSV                         = qmlTextArray[textEnum.textCSVIdx]
        qmltextPdf                         = qmlTextArray[textEnum.textPdfIdx]
        qmltextStorgeOutput                = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmltextDataFilters                 = qmlTextArray[textEnum.textDataFiltersIdx]
        qmltextSummary                     = qmlTextArray[textEnum.textSummaryIdx]
        qmltextSingle                      = qmlTextArray[textEnum.textSingleIdx]
        qmltextContinuous                  = qmlTextArray[textEnum.textContinuousIdx]
        qmltextNext                        = qmlTextArray[textEnum.textNextIdx]
        qmltextPrevious                    = qmlTextArray[textEnum.textPreviousIdx]
        qmltextMenuName                    = qmlTextArray[textEnum.textMenuNameIdx]
        qmltextDeleteRecordFromDatabase    = qmlTextArray[textEnum.textDeleteRecordFromDatabaseIdx]
        qmltextWeldResults                 = qmlTextArray[textEnum.textWeldResultsIdx]
        qmltextWeldSignatures              = qmlTextArray[textEnum.textWeldSignaturesIdx]
        qmltextAlarmData                   = qmlTextArray[textEnum.textAlarmDataIdx]
        qmltextEventData                   = qmlTextArray[textEnum.textEventDataIdx]
        qmltextHornScanResults             = qmlTextArray[textEnum.textHornScanResultsIdx]
        qmltextHornScanSignatures          = qmlTextArray[textEnum.textHornScanSignaturesIdx]
        qmltextRefrenceWeldSignatures      = qmlTextArray[textEnum.textRefrenceWeldSignaturesIdx]
        qmltextCalibrationData             = qmlTextArray[textEnum.textCalibrationDataIdx]
        qmltextDataFilters2                = qmlTextArray[textEnum.textDataFilters2Idx]
        qmltextStorgeOutput2               = qmlTextArray[textEnum.textOutput2Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_DATA_FILTERS, qmlTextMenuName)
    }
    QtObject
    {
        id: textEnum
        readonly property int textTabBarGenerateReportIdx           : 0
        readonly property int textTabBarSavedReportIdx              : 1
        readonly property int textTypeIdx                           : 2
        readonly property int textDataFilterIdx                     : 3
        readonly property int textOutputIdx                         : 4
        readonly property int textUsbIdx                            : 5
        readonly property int textEthernetIdx                       : 6
        readonly property int textCSVIdx                            : 7
        readonly property int textPdfIdx                            : 8
        readonly property int textStorgeOutputIdx                   : 9
        readonly property int textDataFiltersIdx                    : 10
        readonly property int textSummaryIdx                        : 11
        readonly property int textSingleIdx                         : 12
        readonly property int textContinuousIdx                     : 13
        readonly property int textNextIdx                           : 14
        readonly property int textPreviousIdx                       : 15
        readonly property int textMenuNameIdx                       : 16
        readonly property int textDeleteRecordFromDatabaseIdx       : 17
        readonly property int textWeldResultsIdx                    : 18
        readonly property int textWeldSignaturesIdx                 : 19
        readonly property int textAlarmDataIdx                      : 20
        readonly property int textEventDataIdx                      : 21
        readonly property int textHornScanResultsIdx                : 22
        readonly property int textHornScanSignaturesIdx             : 23
        readonly property int textRefrenceWeldSignaturesIdx         : 24
        readonly property int textCalibrationDataIdx                : 25
        readonly property int textDataFilters2Idx                   : 26
        readonly property int textOutput2Idx                        : 27
    }
    QtObject
    {
        id:dataFilterReportSelection
        readonly property int weldResultReport              : 1
        readonly property int weldGraphReport               : 2
        readonly property int alarmLogRepost                : 4
        readonly property int eventLogReport                : 8
        readonly property int hornScanResultReport          : 16
        readonly property int hornScanSignatureReport       : 32
        readonly property int refrenceWeldSignatureReport   : 64
        readonly property int calibrationDataReport         : 128
    }

    Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: parent.width * 0.25
        height: parent.height * 0.05
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: parent.height * 0.05
            spacing: parent.width *0.02
            background: Rectangle
            {
                color: Style.backgroundColor
            }
            BransonTabButton
            {
                id: tabbtnGenerateReport
                width: tabBarBackground.width / 2
                tabbtnText: qmltextTabBarGenerateReport
            }
            BransonTabButton
            {
                id: tabbtnSavedReport
                width: tabBarBackground.width /2
                tabbtnText: qmltextTabBarSavedReport
            }
        }
    }
    Rectangle{
        Rectangle {
            id : typeCircle
            x:Math.round(145*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextType
            anchors.top:typeCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:typeCircle.horizontalCenter
        }
        Rectangle {
            x:Math.round(195*Style.scaleHint)
            y:Math.round(85*Style.scaleHint)
            width: Math.round(380*Style.scaleHint)
            height: Math.round( 1*Style.scaleHint)
            color: Style.generateReportCircleColor
        }
        Rectangle {
            id : strageOutputCircle
            x:Math.round(290*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)

            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextStorgeOutput + "\n" + qmltextStorgeOutput2
            anchors.top:strageOutputCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:strageOutputCircle.horizontalCenter
        }
        Rectangle {
            id : datafiltersCircle
            x:Math.round(435*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: datafilters.qmltextDataFilters + "\n" + qmltextDataFilters2
            color: Style.headerBackgroundColor
            anchors.top:datafiltersCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:datafiltersCircle.horizontalCenter
        }
        Rectangle {
            id:summeryCircle
            x:Math.round(575*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)

            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextSummary
            anchors.top:summeryCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:summeryCircle.horizontalCenter
        }
    }
    Rectangle {
        id: centerlineDataFilter
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        y:Math.round(180*Style.scaleHint)
        width: Math.round(750*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        text: qmltextDataFilter
        font.bold:true
        anchors.bottom:centerlineDataFilter.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    ListModel{
        id: listModelDataFilters
        function fillDataFilters(){
            listModelDataFilters.append({"filterText"       : qmltextWeldResults,
                                            "deleteRecord"  :false,
                                            "Index"         : 0})
            listModelDataFilters.append({"filterText"       : qmltextWeldSignatures,
                                            "deleteRecord"  :false,
                                            "Index"         : 1})
            listModelDataFilters.append({"filterText"       : qmltextAlarmData,
                                            "deleteRecord"  :false,
                                            "Index"         : 2})
            listModelDataFilters.append({"filterText"       : qmltextEventData,
                                            "deleteRecord"  :false,
                                            "Index"         : 3})
            listModelDataFilters.append({"filterText"       : qmltextHornScanResults,
                                            "deleteRecord"  :false,
                                            "Index"         : 4})
            listModelDataFilters.append({"filterText"       : qmltextHornScanSignatures,
                                            "deleteRecord"  :false,
                                            "Index"         : 5})
            listModelDataFilters.append({"filterText"       : qmltextRefrenceWeldSignatures,
                                            "deleteRecord"  :false,
                                            "Index"         : 6})
            listModelDataFilters.append({"filterText"       : qmltextCalibrationData,
                                            "deleteRecord"  :false,
                                            "Index"         : 7})
        }
    }

    ListView {
        model: listModelDataFilters
        width: parent.width
        spacing:Math.round(10 * Style.scaleHint)
        height: Math.round(130 * Style.scaleHint)
        y:Math.round(190 * Style.scaleHint)

        delegate:Item{
            width: parent.width
            height:Math.round(20 * Style.scaleHint)
            CheckBox{
                id: checkBoxDataFilters
                height:Math.round(20 * Style.scaleHint)
                width:parent.width/2
                text:model.filterText
                checked: GenerateReportUserIOObj.getCheckedFilterModeStatus(model.index)
                onCheckedChanged:{
                    if(checked){
                        switch(model.index){
                        case 0:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.weldResultReport)
                            break;
                        case 1:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.weldGraphReport)
                            break;
                        case 2:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.alarmLogRepost)
                            break;
                        case 3:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.eventLogReport)
                            break;
                        case 4:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.hornScanResultReport)
                            break;
                        case 5:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.hornScanSignatureReport)
                            break;
                        case 6:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.refrenceWeldSignatureReport)
                            break;
                        case 7:
                            GenerateReportUserIOObj.onCheckboxSelectionDataFilter(dataFilterReportSelection.calibrationDataReport)
                            break;
                        }
                    }else{
                        switch(model.index){
                        case 0:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.weldResultReport)
                            break;
                        case 1:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.weldGraphReport)
                            break;
                        case 2:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.alarmLogRepost)
                            break;
                        case 3:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.eventLogReport)
                            break;
                        case 4:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.hornScanResultReport)
                            break;
                        case 5:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.hornScanSignatureReport)
                            break;
                        case 6:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.refrenceWeldSignatureReport)
                            break;
                        case 7:
                            GenerateReportUserIOObj.onDeSelectReport(dataFilterReportSelection.calibrationDataReport)
                            break;
                        }
                    }
                    GenerateReportUserIOObj.setMode(model.filterText,model.index,checked)
                }

            }
            CheckBox{
                id: checkBoxDelete
                anchors.left:checkBoxDataFilters.right
                height:Math.round(20 * Style.scaleHint)
                width:parent.width/2
                text:qmltextDeleteRecordFromDatabase
                checked:GenerateReportUserIOObj.getDeleteRecord(model.index)
                onCheckedChanged:{
                    if(checked){
                        switch(model.index){
                        case 0:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.weldResultReport)
                            break;
                        case 1:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.weldGraphReport)
                            break;
                        case 2:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.alarmLogRepost)
                            break;
                        case 3:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.eventLogReport)
                            break;
                        case 4:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.hornScanResultReport)
                            break;
                        case 5:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.hornScanSignatureReport)
                            break;
                        case 6:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.refrenceWeldSignatureReport)
                            break;
                        case 7:
                            GenerateReportUserIOObj.onSelectDeleteReport(dataFilterReportSelection.calibrationDataReport)
                            break;
                        }
                    }else{

                        switch(model.index){
                        case 0:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.weldResultReport)
                            break;
                        case 1:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.weldGraphReport)
                            break;
                        case 2:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.alarmLogRepost)
                            break;
                        case 3:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.eventLogReport)
                            break;
                        case 4:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.hornScanResultReport)
                            break;
                        case 5:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.hornScanSignatureReport)
                            break;
                        case 6:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.refrenceWeldSignatureReport)
                            break;
                        case 7:
                            GenerateReportUserIOObj.onDeSelectDeleteReport(dataFilterReportSelection.calibrationDataReport)
                            break;
                    }
                    GenerateReportUserIOObj.setDeleteRecord(true,model.index)
                }
            }
        }
    }
    }
    BransonPrimaryButton
    {
        id: prvbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(400 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextPrevious
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked: {
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_STORAGE)
        }
    }
    BransonPrimaryButton
    {
        id: nextbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(600 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextNext
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            GenerateReportUserIOObj.getDatafiltersList()
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_SUMMARY)
        }
    }
    Component.onCompleted:{
        updateLanguage();
        listModelDataFilters.fillDataFilters()
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReport Summary file show the each block parameters status .

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
    id: dataFilter
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_CONTINUOUS_SUMMARY
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextStorgeOutput                     : "STORAGE"
    property string qmltextStorgeOutput1                    : "& OUTPUT"
    property string qmltextDataFilters                      : "DATA"
    property string qmltextDataFilters1                     : "FILTERS"
    property string qmltextSummary                          : "SUMMARY"
    property string qmltextNext                             : "NEXT"
    property string qmltextPrevious                         : "PREVIOUS"
    property string qmltextYes                              : "YES"
    property string qmltextNo                               : "NO"
    property string qmltextSaveConfiguration                : "SAVE CONFIGURATION"
    property string qmltextSaveReport                       : "SAVE REPORT"
    property string qmltextReportType                       : "Reprot Type:"
    property string qmltextStorage                          : "Storage:"
    property string qmltextOutput                           : "Output:"
    property string qmltextSample                           : "Sample"
    property string qmltextAlarm                            : "Alarm"
    property string qmltextSummaryDataFilter                : "Data Filters:"
    property string qmltextConfirmation                     : "CONFIRMATION"
    property string qmltextEneterReportName                 : "Enter report name"
    property string qmltextSingle                           : "Single"
    property string qmltextContinuous                       : "Continuous"
    property string qmltextUSB                              : "USB"
    property string qmltextNetworkAttachedStorage           : "Network Attached Storage"
    property string qmltextBINARY                           : "BINARY"
    property string qmltextCSV                              : "CSV"
    property string qmltextYES                              : "YES"
    property string qmltextNO                               : "NO"
    property string qmltextPLC                              : "PLC"

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false


    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextOutput,
        qmltextStorgeOutput, qmltextDataFilters,qmltextSummary,qmltextPrevious,qmltextNext,qmltextYes,qmltextNo,qmltextSaveConfiguration,
        qmltextReportType,qmltextSaveReport,qmltextStorage,qmltextSample,qmltextAlarm,qmltextSummaryDataFilter,qmltextEneterReportName,qmltextConfirmation,
        qmltextSingle,qmltextContinuous,qmltextUSB,qmltextNetworkAttachedStorage,qmltextBINARY,qmltextCSV,qmltextYES,qmltextNO,qmltextPLC,qmltextStorgeOutput1,qmltextDataFilters1]

    QtObject
    {
        id:storageOptionEnum
        readonly property int usb                             : 0
        readonly property int networkAttacheStorage           : 1
        readonly property int plc                             : 2
    }

    QtObject
    {
        id: textEnum
        readonly property int textTabBarGenerateReportIdx             : 0
        readonly property int textTabBarSavedReportIdx                : 1
        readonly property int textTypeIdx                             : 2
        readonly property int textOutputIdx                           : 3
        readonly property int textDataFiltersIdx                      : 4
        readonly property int textPreviousIdx                         : 5
        readonly property int textStorgeOutputIdx                     : 6
        readonly property int textSummaryIdx                          : 7
        readonly property int textNoIdx                               : 8
        readonly property int textContinuousIdx                       : 9
        readonly property int textYesIdx                              : 10
        readonly property int textNextIdx                             : 11
        readonly property int textReportTypeIdx                       : 12
        readonly property int textSaveReportIdx                       : 13
        readonly property int textSaveConfigurationIdx                : 14
        readonly property int textStorageIdx                          : 15
        readonly property int textSampleIdx                           : 16
        readonly property int textAlarmIdx                            : 17
        readonly property int textSummaryDataFilterIdx                : 18
        readonly property int textEneterReportNameIdx                 : 19
        readonly property int textConfirmationIdx                     : 20
        readonly property int textSingleIdx                           : 21
        readonly property int textUSBIdx                              : 22
        readonly property int textNetworkAttachedStorageIdx           : 23
        readonly property int textBINARYIdx                           : 24
        readonly property int textCSVIdx                              : 25
        readonly property int textYESIdx                              : 26
        readonly property int textNOIdx                               : 27
        readonly property int textPLCIdx                              : 28
        readonly property int textStorgeOutput1Idx                    : 29
        readonly property int textDataFilters1Idx                     : 30

    }
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_SUMMARY , qmlTextArray)
        qmlTextTabBarGenerateReport          = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmlTextTabBarSavedReport             = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmlTextType                          = qmlTextArray[textEnum.textTypeIdx]
        qmlTextPdf                           = qmlTextArray[textEnum.textPdfIdx]
        qmlTextOutput                        = qmlTextArray[textEnum.textOutputIdx]
        qmlTextStorgeOutput                  = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmlTextDataFilters                   = qmlTextArray[textEnum.textDataFiltersIdx]
        qmlTextSummary                       = qmlTextArray[textEnum.textSummaryIdx]
        qmlTextContinuous                    = qmlTextArray[textEnum.textContinuousIdx]
        qmlTextMenuName                      = qmlTextArray[textEnum.textMenuNameIdx]
        qmlTextPrevious                      = qmlTextArray[textEnum.textPreviousIdx]
        qmlTextReportType                    = qmlTextArray[textEnum.textReportTypeIdx]
        qmlTextStorageType                   = qmlTextArray[textEnum.textStorageTypeIdx]
        qmlTextOutputSummary                 = qmlTextArray[textEnum.textOutputSummaryIdx]
        qmlTextSaveReport                    = qmlTextArray[textEnum.textSaveReportIdx]
        qmlTextSaveConfiguration             = qmlTextArray[textEnum.textSaveConfigurationIdx]
        qmlTextSample                        = qmlTextArray[textEnum.textSampleIdx]
        qmlTextSummaryDataFilter             = qmlTextArray[textEnum.textSummaryDataFilterIdx]
        qmlTextAlarm                         = qmlTextArray[textEnum.textAlarmIdx]
        qmlTextEneterReportName              = qmlTextArray[textEnum.textEneterReportNameIdx]
        qmlTextConfirmation                  = qmlTextArray[textEnum.textConfirmationIdx]
        qmlTextSingle                        = qmlTextArray[textEnum.textSingleIdx]
        qmlTextUSB                           = qmlTextArray[textEnum.textUSBIdx]
        qmltextNetworkAttachedStorage        = qmlTextArray[textEnum.textNetworkAttachedStorageIdx]
        qmlTextBINARY                        = qmlTextArray[textEnum.textBINARYIdx]
        qmlTextCSV                           = qmlTextArray[textEnum.textCSVIdx]
        qmlTextYES                           = qmlTextArray[textEnum.textAlarmIdx]
        qmlTextNO                            = qmlTextArray[textEnum.textEneterReportNameIdx]
        qmltextPLC                           = qmlTextArray[textEnum.textPLCIdx]
        qmlTextStorgeOutput1                 = qmlTextArray[textEnum.textStorgeOutput1Idx]
        qmlTextDataFilters1                  = qmlTextArray[textEnum.textDataFilters1Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_SUMMARY, qmlTextMenuName)
    }
    Component.onCompleted:
    {
         ActiveScreen.CurrentActiveScreen = UIScreenEnum.GENERATE_REPORT_CONTINUOUS_SUMMARY
        DataFilterListModel.createDataFilterList()
    }
    function onStorageTypeAccess(storageType)
    {
        switch(storageType)
        {
        case storageOptionEnum.usb:
            return qmltextUSB;
            break;
        case storageOptionEnum.networkAttacheStorage:
            return qmltextNetworkAttachedStorage;
            break;
        case storageOptionEnum.plc:
            return qmltextPLC;
            break;
        }
    }
    Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: Math.round(190 * Style.scaleHint)
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            spacing:Math.round(26 * Style.scaleHint)
            background: Rectangle
            {
                color: Style.backgroundColor
            }
            BransonTabButton
            {
                id: tabbtnGenerateReport
                width: Math.round(150 * Style.scaleHint)
                tabbtnText: qmltextTabBarGenerateReport
            }
            BransonTabButton
            {
                id: tabbtnSavedReport
                width: Math.round(125 * Style.scaleHint)
                tabbtnText: qmltextTabBarSavedReport
            }
        }
    }

    Rectangle
    {
        Rectangle
        {
            id : typeCircle
            x:Math.round(145*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label
        {
            text: qmltextType
            anchors.top:typeCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:typeCircle.horizontalCenter
        }
        Rectangle
        {
            x:Math.round(195*Style.scaleHint)
            y:Math.round(85*Style.scaleHint)
            width: Math.round(380*Style.scaleHint)
            height: Math.round( 1*Style.scaleHint)
            color: Style.generateReportCircleColor
        }
        Rectangle
        {
            id : strageOutputCircle
            x:Math.round(290*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label
        {
            text: qmltextStorgeOutput+"\n"+qmltextStorgeOutput1
            anchors.top:strageOutputCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:strageOutputCircle.horizontalCenter
        }
        Rectangle
        {
            id : datafiltersCircle
            x:Math.round(435*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)


            border.width: Math.round(1*Style.scaleHint)
        }
        Label
        {
            text: qmltextDataFilters +"\n"+qmltextDataFilters1
            anchors.top:datafiltersCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:datafiltersCircle.horizontalCenter
        }
        Rectangle
        {
            id:summeryCircle
            x:Math.round(575*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label
        {
            text: qmltextSummary
            anchors.top:summeryCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:summeryCircle.horizontalCenter
            color: Style.headerBackgroundColor
        }
    }
    Rectangle
    {
        id: summaryCenterLine
        anchors.left:summaryLabel.left
        y:Math.round(180*Style.scaleHint)
        width: Math.round(800*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label
    {
        id:summaryLabel
        text: qmltextSummary
        font.bold: true
        anchors.bottom:summaryCenterLine.top
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.bottomMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(300 * Style.scaleHint)
    }
    Label
    {
        id:reportTypeLabel
        text: qmltextReportType
        font.bold: true
        anchors.top:summaryCenterLine.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(300 * Style.scaleHint)
    }
    Label
    {
        id:reportTypeLabelTextR
        anchors.top:reportTypeLabel.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(300 * Style.scaleHint)
        text:  DataFilterListModel.m_TypeRadioButton ? qmltextSingle :qmltextContinuous
    }
    Label
    {
        id:reportStorageLabel
        text: qmltextStorage
        font.bold: true
        anchors.top:summaryCenterLine.bottom
        anchors.left:reportTypeLabel.right
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(90 * Style.scaleHint)
    }
    Label
    {
        id:reportStorageLabelText
        anchors.top:reportStorageLabel.bottom
        anchors.left:reportStorageLabel.left
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        text:  onStorageTypeAccess(DataFilterListModel.getStorageOptionValue())
    }
    Label
    {
        id:reportSampleLabel
        text: qmltextSample
        font.bold: true
        anchors.top:summaryCenterLine.bottom
        anchors.left:reportStorageLabelText.right
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(90 * Style.scaleHint)
    }
    Label
    {
        id:reportSampleLabelText
        anchors.top:reportSampleLabel.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.left:reportSampleLabel.left
        text:  DataFilterListModel.getCycleCount()
    }
    Label
    {
        id:reportAlarmLabel
        text: qmltextAlarm
        font.bold: true
        anchors.top:summaryCenterLine.bottom
        anchors.left:reportSampleLabel.right
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(90 * Style.scaleHint)
    }
    Label
    {
        id:reportAlarmLabelText
        anchors.top:reportAlarmLabel.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.left:reportAlarmLabel.left
        text:  DataFilterListModel.m_SaveOnAlarmRadioButton ? qmltextYES :qmltextNO
    }
    Label
    {
        id:dataFiltersLabel
        text: qmltextSummaryDataFilter
        font.bold: true
        anchors.top:summaryCenterLine.bottom
        anchors.left:reportAlarmLabel.right
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(90 * Style.scaleHint)
    }
    ScrollView
    {
        anchors.top:dataFiltersLabel.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.left:dataFiltersLabel.left
        height:Math.round(100 * Style.scaleHint)
        Label{
            id:reportDatafiltersLabelText
            anchors.top:parent.top
            text:DataFilterListModel.getDatafiltersList()
        }
    }

    BransonPrimaryButton
    {
        id: prvbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(200 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextPrevious
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked: {
            DataFilterListModel.getDatafiltersList()
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_DATA_FILTER)
        }
    }
    BransonPrimaryButton
    {
        id: savebtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(400 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextSaveConfiguration
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            saveReportPopup.visible = true
            generateReportPopup.visible = false
            DataFilterListModel.onSaveConfigurationClicked();
        }
    }
    BransonPrimaryButton
    {
        id: generateReportBtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(600 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: dataFilter.qmltextSaveReport
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            generateReportPopup.visible = true
        }
    }
    BransonPopup
    {
        id:generateReportPopup
        width:Math.round(400 * Style.scaleHint)
        height:Math.round(275 * Style.scaleHint)
        anchors.centerIn:parent
        InputPanel
        {
            id: inputPanel
            z: 1
            height: parent.height
            width: parent.width
            visible: Qt.inputMethod.visible
            anchors.bottom: parent.bottom
        }
        Text{
            x:Math.round(20 * Style.scaleHint)
            y:Math.round(80 * Style.scaleHint)
            text:qmltextEneterReportName
        }

        BransonLineEdit{
            id:genreportLineEdit
            x: Math.round(20 * Style.scaleHint)
            y: Math.round(110 * Style.scaleHint)
            focus: true
            selectByMouse: true
            mouseSelectionMode: TextInput.SelectWords
            onFocusChanged:{
                if(focus){
                    Qt.inputMethod.show()
                }else{
                    Qt.inputMethod.hide()
                }
            }
        }
        onOKButtonClicked:
        {
            generateReportPopup.visible = false
        }
        onCancelButtonClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_SUMMARY)
            generateReportPopup.visible = false

        }
        Component.onCompleted:{
            generateReportPopup.isMultiButtonPopup = true
            generateReportPopup.qmltextOk = qmltextSaveReport
            generateReportPopup.qmltextLabel =qmltextSaveConfiguration
            generateReportPopup.qmltextCancel =qmltextCancel
            genreportLineEdit.implicitWidth = Math.round(240 * Style.scaleHint)
        }
    }
    Rectangle
    {
        id: saveReportPopup
        x:Math.round(550 * Style.scaleHint)
        y: Math.round(180 * Style.scaleHint)
        width: Math.round(200 * Style.scaleHint)
        height: Math.round(150 * Style.scaleHint)
        visible:false

        Rectangle
        {
            width:Math.round(200 * Style.scaleHint)
            height:Math.round(40 * Style.scaleHint)
            color:Style.opacityEffectColor
            Text
            {
                x:Math.round(10 * Style.scaleHint)
                anchors.verticalCenter:parent.verticalCenter
                text:qmltextConfirmation
            }
            Image
            {
                id: imgClosePopup
                height: parent.height * 0.50
                width: parent.height * 0.50
                anchors.right : parent.right
                anchors.rightMargin : parent.height * 0.20
                anchors.verticalCenter: parent.verticalCenter
                source:"qrc:/Images/Icon_close.svg"
                MouseArea{
                    anchors.fill:parent
                    onClicked:
                    {
                        saveReportPopup.visible = false
                    }
                }
            }
        }
        ProgressBar
        {
            id: customProgressBar
            width: Math.round(120 * Style.scaleHint)
            value: 0.7
            anchors.centerIn:parent

            background: Rectangle
            {
                implicitHeight: Math.round(10 * Style.scaleHint)
                color: Style.progressBarBackgroundColor
                radius: Math.round(5 * Style.scaleHint)
            }
            contentItem: Rectangle
            {
                width: customProgressBar.visualPosition * customProgressBar.width
                height: parent.height
                color: Style.progressBarColor // Blue color
                radius: Math.round(5 * Style.scaleHint)
            }
        }
    }
}

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

    id: summary
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_SUMMARY
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextSummary                          : "SUMMARY"
    property string qmltextOutput                           : "OUTPUT"
    property string qmltextUsb                              : "USB"
    property string qmltextEthernet                         : "ETHERNET"
    property string qmltextCSV                              : "CSV"
    property string qmltextPdf                              : "PDF"
    property string qmltextStorgeOutput                     : "STORAGE"
    property string qmltextDataFilters                      : "DATA"
    property string qmltextSingle                           : "SINGLE"
    property string qmltextContinuous                       : "CONTINUOUS"
    property string qmltextGenerateReport                   : "GENERATE REPORT"
    property string qmltextPrevious                         : "PREVIOUS"
    property string qmltextMenuName                         : "Generate Report"
    property string qmltextReportType                       : "Report Type :"
    property string qmltextStorageType                      : "Storage Type :"
    property string qmltextDataFilter                       : "Data Filter :"
    property string qmltextOutputSummary                    : "Output :"
    property string qmltextSaveReport                       :"SAVE REPORT"
    property string qmltextConfirmation                     :"CONFIRMATION"
    property string qmltextCancel                           :"CANCEL"
    property string qmltextEneterReportName                 :"Enter report name"
    property string qmltextSave                             : "SAVE"
    property string qmltextNotStarted                       :"NOT STARTED"
    property string qmltextStarted                          :"STARTED"
    property string qmltextCompleted                        : "COMPLETED"
    property string qmltextStorgeOutput2                    : "OUTPUT"
    property string qmltextDataFilters2                     : "FILTERS"


    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false


    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextSummary, qmltextOutput, qmltextUsb, qmltextEthernet, qmltextCSV, qmltextPdf,
    qmltextStorgeOutput, qmltextDataFilters, qmltextSingle, qmltextContinuous, qmltextGenerateReport, qmltextPrevious, qmltextMenuName, qmltextReportType, qmltextStorageType, qmltextDataFilter,
    qmltextOutputSummary, qmltextSaveReport, qmltextConfirmation, qmltextCancel, qmltextEneterReportName, qmltextSave, qmltextNotStarted, qmltextStarted, qmltextCompleted, qmltextStorgeOutput2, qmltextDataFilters2]

    QtObject
    {
        id: textEnum
        readonly property int textTabBarGenerateReportIdx               : 0
        readonly property int textTabBarSavedReportIdx                  : 1
        readonly property int textTypeIdx                               : 2
        readonly property int textSummaryIdx                            : 3
        readonly property int textOutputIdx                             : 4
        readonly property int textUsbIdx                                : 5
        readonly property int textEthernetIdx                           : 6
        readonly property int textCSVIdx                                : 7
        readonly property int textPdfIdx                                : 8
        readonly property int textStorgeOutputIdx                       : 9
        readonly property int textDataFiltersIdx                        : 10
        readonly property int textSingleIdx                             : 11
        readonly property int textContinuousIdx                         : 12
        readonly property int textGenerateReportIdx                     : 13
        readonly property int textPreviousIdx                           : 14
        readonly property int textMenuNameIdx                           : 15
        readonly property int textReportTypeIdx                         : 16
        readonly property int textStorageTypeIdx                        : 17
        readonly property int textDataFilterIdx                         : 18
        readonly property int textOutputSummaryIdx                      : 19
        readonly property int textSaveReportIdx                         : 20
        readonly property int textConfirmationIdx                       : 21
        readonly property int textCancelIdx                             : 22
        readonly property int textEneterReportNameIdx                   : 23
        readonly property int textSaveIdx                               : 24
        readonly property int textNotStartedIdx                         : 22
        readonly property int textStartedIdx                            : 23
        readonly property int textCompletedIdx                          : 24
        readonly property int textStorgeOutput2Idx                      : 25
        readonly property int textDataFilters2Idx                       : 26
    }


    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_SUMMARY , qmlTextArray)
        qmltextTabBarGenerateReport          = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmltextTabBarSavedReport             = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmltextType                          = qmlTextArray[textEnum.textTypeIdx]
        qmltextSummary                           = qmlTextArray[textEnum.textSummaryIdx]
        qmltextOutput                                        = qmlTextArray[textEnum.textOutputIdx]
        qmltextUsb                        = qmlTextArray[textEnum.textUsbIdx]
        qmltextEthernet                        = qmlTextArray[textEnum.textEthernetIdx]
        qmltextCSV                           = qmlTextArray[textEnum.textCSVIdx]
        qmltextPdf                      = qmlTextArray[textEnum.textPdfIdx]
        qmltextStorgeOutput                           = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmltextDataFilters                  = qmlTextArray[textEnum.textDataFiltersIdx]
        qmltextSingle                   = qmlTextArray[textEnum.textSingleIdx]
        qmltextContinuous                       = qmlTextArray[textEnum.textContinuousIdx]
        qmltextGenerateReport                    = qmlTextArray[textEnum.textGenerateReportIdx]
        qmltextPrevious                      = qmlTextArray[textEnum.textPreviousIdx]
        qmltextMenuName                      = qmlTextArray[textEnum.textMenuNameIdx]
        qmltextReportType                    = qmlTextArray[textEnum.textReportTypeIdx]
        qmltextStorageType                   = qmlTextArray[textEnum.textStorageTypeIdx]
        qmltextDataFilter                 = qmlTextArray[textEnum.textDataFilterIdx]
        qmltextOutputSummary                    = qmlTextArray[textEnum.textOutputSummaryIdx]
        qmltextSaveReport                  = qmlTextArray[textEnum.textSaveReportIdx]
        qmltextConfirmation                        = qmlTextArray[textEnum.textConfirmationIdx]
        qmltextCancel              = qmlTextArray[textEnum.textCancelIdx]
        qmltextEneterReportName                          = qmlTextArray[textEnum.textEneterReportNameIdx]
        qmltextSave                    = qmlTextArray[textEnum.textSaveIdx]
        qmltextNotStarted                    = qmlTextArray[textEnum.textNotStartedIdx]
        qmltextStarted                          = qmlTextArray[textEnum.textStartedIdx]
        qmltextCompleted                    = qmlTextArray[textEnum.textCompletedIdx]
        qmltextStorgeOutput2                           = qmlTextArray[textEnum.textStorgeOutput2Idx]
        qmltextDataFilters2                  = qmlTextArray[textEnum.textDataFilters2Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_SUMMARY, qmlTextMenuName)
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
            spacing: Math.round(26 * Style.scaleHint)
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

            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextDataFilters + "\n" + qmltextDataFilters2
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
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextSummary
            color: Style.headerBackgroundColor
            anchors.top:summeryCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:summeryCircle.horizontalCenter
        }
    }
    Rectangle {
        id: centerlineSummary
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        y:Math.round(180*Style.scaleHint)
        width: Math.round(750*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        text: qmltextSummary
        anchors.bottom:centerlineSummary.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Rectangle{
        Text{
            x:Math.round(30 * Style.scaleHint)
            y:Math.round(200 * Style.scaleHint)
            text: GenerateReportUserIOObj.m_TypeRadioButton ? qmltextReportType +" SINGLE" :qmltextReportType +" CONTINOUS"
            anchors.top:centerlineSummary.bottom
            anchors.bottomMargin:Math.round(5 * Style.scaleHint)
            anchors.leftMargin:Math.round(80 * Style.scaleHint)
        }
        Text{
            x:Math.round(30 * Style.scaleHint)
            y:Math.round(230 * Style.scaleHint)
            text:qmltextDataFilter +  GenerateReportUserIOObj.getDatafiltersList()
            anchors.top:centerlineSummary.bottom
            anchors.bottomMargin:Math.round(5 * Style.scaleHint)
            anchors.leftMargin:Math.round(80 * Style.scaleHint)
        }
        Text{
            x:Math.round(30 * Style.scaleHint)
            y:Math.round(260 * Style.scaleHint)
            text: GenerateReportUserIOObj.m_StorageoptButton ? qmltextStorageType  +" ETHERNET" :qmltextStorageType  +" USB"
            anchors.top:centerlineSummary.bottom
            anchors.bottomMargin:Math.round(5 * Style.scaleHint)
            anchors.leftMargin:Math.round(80 * Style.scaleHint)
        }
        Text{
            x:Math.round(30 * Style.scaleHint)
            y:Math.round(290 * Style.scaleHint)
            text:  GenerateReportUserIOObj.m_OutputRadioButton ? qmltextOutputSummary  +" PDF" :qmltextOutputSummary  +" CSV"
            anchors.top:centerlineSummary.bottom
            anchors.bottomMargin:Math.round(5 * Style.scaleHint)
            anchors.leftMargin:Math.round(80 * Style.scaleHint)
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
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_DATA_FILTERS)
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
        text: qmltextSave
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            generateReportPopup.visible = true
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
        text: qmltextGenerateReport
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        Timer {
            id: myTimer
            interval: 1000  // Time in milliseconds (1 second)
            running: true   // Start the timer automatically
            repeat: true    // Repeats indefinitely

            onTriggered: {
                switch(GenerateReportUserIOObj.onStatusChanged()){
                case 0:
                    progressStatusId.text = qmltextNotStarted
                    break;
                case 1:
                    progressStatusId.text = qmltextStarted
                    break;
                case 2:
                    progressStatusId.text = qmltextCompleted
                    break;
                default:progressStatusId.text = "Report Not Generated"

               }
            }
        }
        onClicked: {
            myTimer.start()
            saveReportPopup.visible = true
            GenerateReportUserIOObj.ClearTheFilterList()
            GenerateReportUserIOObj.onGenerateReportClicked()
        }
    }
    BransonPopup{
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
            generateReportPopup.visible = false
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_SUMMARY)

        }
        Component.onCompleted:{
            updateLanguage();
            generateReportPopup.isMultiButtonPopup = true
            generateReportPopup.qmltextOk = qmltextSaveReport
            generateReportPopup.qmltextLabel =qmltextTabBarGenerateReport
            generateReportPopup.qmltextCancel =qmltextCancel
            genreportLineEdit.implicitWidth = Math.round(240 * Style.scaleHint)
        }
    }
    Rectangle{
        id: saveReportPopup
        x:Math.round(550 * Style.scaleHint)
        y: Math.round(180 * Style.scaleHint)
        width: Math.round(200 * Style.scaleHint)
        height: Math.round(150 * Style.scaleHint)
        visible:false

        Rectangle{
            width:Math.round(200 * Style.scaleHint)
            height:Math.round(40 * Style.scaleHint)
            color:"#004B8D"
            Text{
                x:Math.round(10 * Style.scaleHint)
                anchors.verticalCenter:parent.verticalCenter
                text:qmltextConfirmation
            }
            Image{
                id: imgClosePopup
                height: parent.height * 0.50
                width: parent.height * 0.50
                anchors.right : parent.right
                anchors.rightMargin : parent.height * 0.20
                anchors.verticalCenter: parent.verticalCenter
                source:"qrc:/Images/Icon_close.svg"
                MouseArea{
                anchors.fill:parent
                onClicked:{
                saveReportPopup.visible = false
                }
                }
            }
        }

        ProgressBar {
            id: customProgressBar
            width: Math.round(120 * Style.scaleHint)
            value: 0.7
            anchors.centerIn:parent

            background: Rectangle {
                implicitHeight: Math.round(10 * Style.scaleHint)
                color: "#ccc"
                radius: Math.round(5 * Style.scaleHint)
            }
            contentItem: Rectangle {
                width: customProgressBar.visualPosition * customProgressBar.width
                height: parent.height
                color: "#3b82f6" // Blue color
                radius: Math.round(5 * Style.scaleHint)
            }
        }
        Text{
            id:progressStatusId
            text:" "
            anchors.horizontalCenter:customProgressBar.horizontalCenter
            anchors.top:customProgressBar.bottom
            anchors.topMargin:20

        }
    }
  Component.onCompleted:{

        ActiveScreen.CurrentActiveScreen = UIScreenEnum.GENERATE_REPORT_SUMMARY
    }
}

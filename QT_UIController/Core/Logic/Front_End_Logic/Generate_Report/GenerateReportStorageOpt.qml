/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReport Storage file provide the options for store file.

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
    id: storageoption
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_STORAGE
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextStorageOption                    : "STORAGE OPTIONS"
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
    property string qmltextStorgeOutput2                    : "& OUTPUT"
    property string qmltextDataFilters2                     : "FILTERS"

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextStorageOption, qmltextOutput,qmltextUsb,
        qmltextEthernet,qmltextCSV, qmltextStorgeOutput, qmltextDataFilters,qmltextSummary, qmltextSingle, qmltextContinuous, qmltextNext, qmltextPrevious, qmltextMenuName,
    qmltextStorgeOutput2, qmltextDataFilters2]

    QtObject
    {
        id: textEnum
        readonly property int textTabBarGenerateReportIdx             : 0
        readonly property int textTabBarSavedReportIdx                : 1
        readonly property int textTypeIdx                             : 2
        readonly property int textStorageOptionIdx                    : 3
        readonly property int textOutputIdx                           : 4
        readonly property int textUsbIdx                              : 5
        readonly property int textEthernetIdx                         : 6
        readonly property int textCSVIdx                              : 7
        readonly property int textPdfIdx                              : 8
        readonly property int textStorgeOutputIdx                     : 9
        readonly property int textDataFiltersIdx                      : 10
        readonly property int textSummaryIdx                          : 11
        readonly property int textSingleIdx                           : 12
        readonly property int textContinuousIdx                       : 13
        readonly property int textNextIdx                             : 14
        readonly property int textPreviousIdx                         : 15
        readonly property int textStorgeOutput2Idx                    : 16
        readonly property int textDataFilters2Idx                     : 17

    }
    QtObject
    {
        id:generateReportFormatEnum
        readonly property int csv             : 0
        readonly property int pdf             : 1
    }
    QtObject
    {
        id:generateReportStorageEnum
        readonly property int usb             : 0
        readonly property int ethernet        : 1
    }

    Component.onCompleted:{
        updateLanguage();
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_STORAGE , qmlTextArray)
        qmltextTabBarGenerateReport        = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmltextTabBarSavedReport           = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmltextType                        = qmlTextArray[textEnum.textTypeIdx]
        qmltextStorageOption               = qmlTextArray[textEnum.textStorageOptionIdx]
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
        qmltextStorgeOutput2                = qmlTextArray[textEnum.textStorgeOutput2Idx]
        qmltextDataFilters2                 = qmlTextArray[textEnum.textDataFilters2Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_STORAGE, qmlTextMenuName)
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
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextStorgeOutput + "\n" + qmltextStorgeOutput2
            color: Style.headerBackgroundColor
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
        id: centerlineStorageOption
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        y:Math.round(180*Style.scaleHint)
        width: Math.round(750*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        text: qmltextStorageOption
        anchors.bottom:centerlineStorageOption.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Item {
        id:radiobtnsinglecont
        anchors.top:centerlineStorageOption.bottom
        anchors.topMargin:Math.round(20 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnUsb
            text: qmltextUsb
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            font.family: Style.regular.name
            checked: GenerateReportUserIOObj.m_StorageoptButton ? false : true
            onClicked:
            {
                if(checked){
                  GenerateReportUserIOObj.onCheckboxSelectionStorageOption(generateReportStorageEnum.usb)
                }
                GenerateReportUserIOObj.m_StorageoptButton = false
            }
        }
        RadioButton
        {
            id:rdbtnEthernet
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnUsb.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: qmltextEthernet
            font.family: Style.regular.name
            checked: GenerateReportUserIOObj.m_StorageoptButton ? true : false
            onClicked:
            {
                if(checked){
                  GenerateReportUserIOObj.onCheckboxSelectionStorageOption(generateReportStorageEnum.ethernet)
                }
                GenerateReportUserIOObj.m_StorageoptButton = true
            }
        }
    }
    Rectangle {
        id: centerlineOutput
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        anchors.top:rdbtnEthernet.bottom
        y:Math.round(300*Style.scaleHint)
        width: Math.round(750*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        text: qmltextOutput
        anchors.bottom:centerlineOutput.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Item {
        id:radiobtnOutput
        anchors.top:centerlineOutput.bottom
        anchors.topMargin:Math.round(20 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnCSV
            text: qmltextCSV
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            font.family: Style.regular.name

            checked:GenerateReportUserIOObj.m_OutputRadioButton ? false : true
            onClicked:
            {
                if(checked){
                  GenerateReportUserIOObj.onCheckboxSelectionFormatType(generateReportFormatEnum.csv)
                }else{
                     GenerateReportUserIOObj.onCheckboxSelectionFormatType(generateReportFormatEnum.pdf)
                }
                GenerateReportUserIOObj.m_OutputRadioButton = false
            }
        }
        RadioButton
        {
            id:rdbtnPDF
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnCSV.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: qmltextPdf
            font.family: Style.regular.name
            checked:GenerateReportUserIOObj.m_OutputRadioButton  ? true : false
            onClicked:
            {
                if(checked){
                    GenerateReportUserIOObj.onCheckboxSelectionFormatType(generateReportFormatEnum.pdf)
                }else{
                    GenerateReportUserIOObj.onCheckboxSelectionFormatType(generateReportFormatEnum.csv)
                }
                GenerateReportUserIOObj.m_OutputRadioButton = true
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
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT)
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
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_DATA_FILTERS)
        }
    }
}

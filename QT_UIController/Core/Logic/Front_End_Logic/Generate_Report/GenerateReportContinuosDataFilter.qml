/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReport Data Filter Model with parameter addition.

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
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_CONTINUOUS_DATA_FILTER
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
    property string qmltextSaveOnAlarm                      : "SAVE ON ALARM"
    property string qmltextCycleCount                       : "Cycle Count"
    property string qmltextDataFilter                       : "DATA FILTER"
    property string qmltextSaveOnCycleCount                 : "SAVE ON CYCLE COUNT"


    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType,qmltextStorgeOutput,qmltextDataFilters,qmltextSaveOnCycleCount,
        qmltextSummary,qmltextNext,qmltextPrevious,qmltextYes,qmltextNo,qmltextSaveOnAlarm,qmltextCycleCount,qmltextDataFilter,qmltextStorgeOutput1,qmltextDataFilters1]
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_DATA_FILTERS , qmlTextArray)
        qmlTextTabBarGenerateReport        = qmlTextArray[textEnum.textabBarGenerateReportIdx]
        qmlTextTabBarSavedReport           = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmlTextType                        = qmlTextArray[textEnum.textTypeIdx]
        qmlTextDataFilter                  = qmlTextArray[textEnum.textDataFilterIdx]
        qmlTextOutput                      = qmlTextArray[textEnum.textOutputIdx]
        qmlTextNext                        = qmlTextArray[textEnum.textNextIdx]
        qmlTextStorgeOutput                = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmlTextDataFilters                 = qmlTextArray[textEnum.textDataFiltersIdx]
        qmlTextSummary                     = qmlTextArray[textEnum.textSummaryIdx]
        qmltextSaveOnCycleCount            = qmlTextArray[textEnum.textSaveOnCycleCountIdx]
        qmlTextContinuous                  = qmlTextArray[textEnum.textContinuousIdx]
        qmlTextPrevious                    = qmlTextArray[textEnum.textPreviousIdx]
        qmlTextYes                         = qmlTextArray[textEnum.textYesIdx]
        qmlTextNo                          = qmlTextArray[textEnum.textNoIdx]
        qmlTextSaveOnAlarm                 = qmlTextArray[textEnum.textSaveOnAlarmIdx]
        qmlTextCycleCount                  = qmlTextArray[textEnum.textCycleCountIdx]
        qmlTextStorgeOutput1               = qmlTextArray[textEnum.textStorgeOutput1Idx]
        qmlTextDataFilter1                 = qmlTextArray[textEnum.textDataFilter1Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_DATA_FILTERS, qmlTextMenuName)
    }
    QtObject
    {
        id: textEnum
        readonly property int textabBarGenerateReportIdx              : 0
        readonly property int textTabBarSavedReportIdx                : 1
        readonly property int textTypeIdx                             : 2
        readonly property int textDataFilterIdx                       : 3
        readonly property int textOutputIdx                           : 4
        readonly property int textStorgeOutputIdx                     : 5
        readonly property int textDataFiltersIdx                      : 6
        readonly property int textSummaryIdx                          : 7
        readonly property int textContinuousIdx                       : 8
        readonly property int textNextIdx                             : 9
        readonly property int textPreviousIdx                         : 10
        readonly property int textYesIdx                              : 11
        readonly property int textNoIdx                               : 12
        readonly property int textSaveOnAlarmIdx                      : 13
        readonly property int textCycleCountIdx                       : 14
        readonly property int textStorgeOutput1Idx                    : 15
        readonly property int textDataFilter1Idx                      : 16
    }

    QtObject
    {
        id:generateReportSaveOnAlarmEnum
        readonly property int no              : 0
        readonly property int yes             : 1
    }
    QtObject
    {
        id:storageOptionEnum
        readonly property int usb                             : 0
        readonly property int networkAttacheStorage           : 1
        readonly property int plc                             : 2
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
            text: qmltextStorgeOutput+"\n"+qmltextStorgeOutput1
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
            text: qmltextDataFilters +"\n"+qmltextDataFilters1
            anchors.top:datafiltersCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:datafiltersCircle.horizontalCenter
            color: Style.headerBackgroundColor
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
        id: saveOnAlarmCenterLine
        anchors.left:saveOnAlarmLabel.left
        y:Math.round(210*Style.scaleHint)
        width: Math.round(280*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        id:saveOnAlarmLabel
        text: qmltextSaveOnAlarm
        font.bold: true
        anchors.bottom:saveOnAlarmCenterLine.top
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.bottomMargin:Math.round(10 * Style.scaleHint)
        anchors.leftMargin:Math.round(300 * Style.scaleHint)
    }

    Item
    {
        id:radiobtnSaveOnAlarm
        anchors.top:saveOnAlarmCenterLine.bottom
        anchors.left:saveOnAlarmCenterLine.left
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnYes
            enabled:(DataFilterListModel.getStorageOptionValue() != storageOptionEnum.plc)
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            text: qmltextYes
            font.family: Style.regular.name
            checked: DataFilterListModel.m_SaveOnAlarmRadioButton ? true : false
            onClicked:
            {
                if(checked)
                {
                    DataFilterListModel.onClickOnSaveOnAlarm(generateReportSaveOnAlarmEnum.yes);
                    DataFilterListModel.m_SaveOnAlarmRadioButton = true
                }
                else
                {
                    DataFilterListModel.onClickOnSaveOnAlarm(generateReportSaveOnAlarmEnum.no);
                    DataFilterListModel.m_SaveOnAlarmRadioButton = false
                }
            }
        }
        RadioButton
        {
            id:rdbtnNo
            enabled:(DataFilterListModel.getStorageOptionValue() != storageOptionEnum.plc)
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnYes.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: qmltextNo
            font.family: Style.regular.name
            checked: DataFilterListModel.m_SaveOnAlarmRadioButton ? false : true
            onClicked:
            {
                if(checked)
                {
                    DataFilterListModel.onClickOnSaveOnAlarm(generateReportSaveOnAlarmEnum.no);
                    DataFilterListModel.m_SaveOnAlarmRadioButton = false
                }
                else
                {
                    DataFilterListModel.onClickOnSaveOnAlarm(generateReportSaveOnAlarmEnum.yes);
                    DataFilterListModel.m_SaveOnAlarmRadioButton = true
                }
            }
        }
    }
    Rectangle {
        id: dataFilterenterLine
        anchors.top:saveOnAlarmCenterLine.top
        anchors.left:saveOnAlarmCenterLine.right
        anchors.leftMargin: Math.round(50*Style.scaleHint)
        y:Math.round(210*Style.scaleHint)
        width: Math.round(460*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    ListView {
        id:datafilterListview
        anchors.top: dataFilterenterLine.bottom
        anchors.left: dataFilterenterLine.left
        anchors.bottom: prvbtn.top
        anchors.topMargin:Math.round(10*Style.scaleHint)
        anchors.bottomMargin: Math.round(25*Style.scaleHint)
        width: dataFilterenterLine.width
        height:Math.round(40*Style.scaleHint)
        boundsBehavior: Flickable.StopAtBounds
        model: DataFilterListModel
        delegate: Rectangle {
            width: datafilterListview.width
            height: Math.round(30*Style.scaleHint)
            color: Math.abs(model.index) % 2 === 0 ? "#F0F0F0" : "#FFFFFF"
            Text {
                id: textDataFilters
                anchors.left: parent.left
                anchors.leftMargin: 30
                text: model.Name
                anchors.verticalCenter: parent.verticalCenter
            }
            Switch{
                id : switchSaveOnCycleCount
                width:Math.round(40*Style.scaleHint)
                height:Math.round(20*Style.scaleHint)
                x: parent.width * 0.75
                checked: DataFilterListModel.getCheckStatus(model.index)
                anchors.verticalCenter: parent.verticalCenter
                onClicked:{
                    DataFilterListModel.onCheckStatusChanged(checked,model.index)
                }
                indicator: Rectangle{
                    width: parent.width
                    height: parent.height * 0.75
                    radius: height/2
                    color: switchSaveOnCycleCount.checked ? "#17345C" : "#C7C7C7"
                    anchors.verticalCenter: switchSaveOnCycleCount.verticalCenter

                    z:0
                }
                Rectangle{
                    radius: parent.height/2
                    width: parent.height
                    height: parent.height
                    x: switchSaveOnCycleCount.checked ? parent.width - width  : 0
                    anchors.verticalCenter: switchSaveOnCycleCount.verticalCenter
                    color: switchSaveOnCycleCount.checked ? "#004B8D" : "#666666"
                    z:1
                }
            }
        }
    }
    Label{
        id:dataFilterLabel
        text: qmltextDataFilter
        y:Math.round(180*Style.scaleHint)
        font.bold: true
        anchors.left:dataFilterenterLine.left
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.bottomMargin:Math.round(10 * Style.scaleHint)
    }
    Label{
        id:saveOnCycleCount
        text: qmltextSaveOnCycleCount
        y:Math.round(180*Style.scaleHint)
        font.bold: true
        anchors.left:dataFilterLabel.right
        anchors.leftMargin: Math.round(200*Style.scaleHint)
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        anchors.bottomMargin:Math.round(10 * Style.scaleHint)
    }

    Rectangle
    {
        id:cyclecountRectID
        Text{
            id:cycleCountID
            text:qmltextCycleCount
            font.bold: true
            anchors.bottom:rdbtnYes.top
            y:Math.round(290 * Style.scaleHint)
        }
        BransonLineEdit{
            id: cycleCountLineEdit
            text:DataFilterListModel.CycleCount
            anchors.top:cycleCountID.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            width: Math.round(200 * Style.scaleHint)
            font.pixelSize: Math.round(14 * Style.scaleHint)
            focus: true
            MouseArea
            {
                id: cycleCountArea
                anchors.fill: parent
                onClicked:
                {
                    mainWindow.showPrimaryNumpad(qmltextCycleCount, "", 3, 0, 2147483647, cycleCountLineEdit.text)
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
        anchors.topMargin:150
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextPrevious
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked: {
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE)
        }
    }
    BransonPrimaryButton
    {
        id: nextbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(600 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:150
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextNext
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            DataFilterListModel.onSelectionOfDataFilterParameter()
            DataFilterListModel.onCycleCount(cycleCountLineEdit.text)
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_SUMMARY)
        }
    }
}

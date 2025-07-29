/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

  Generate Report Type file provide the option to select the report type.

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
    id: systemWindow
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATEREPORT
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextStorgeOutput                     : "STORAGE"
    property string qmltextDataFilters                      : "DATA"
    property string qmltextSummary                          : "SUMMARY"
    property string qmltextSingle                           : "SINGLE"
    property string qmltextContinuous                       : "CONTINUOUS"
    property string qmltextNext                             : "NEXT"
    property string qmltextMenuName                         : "Generate Report"
    property string qmltextStorgeOutput2                    : "& OUTPUT"
    property string qmltextDataFilters2                     : "FILTERS"

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextStorgeOutput, qmltextSummary, qmltextSingle,
        qmltextContinuous, qmltextNext, qmltextMenuName, qmltextStorgeOutput2, qmltextDataFilters2 ]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATEREPORT , qmlTextArray)
        qmltextTabBarGenerateReport         = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmltextTabBarSavedReport            = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmltextType                         = qmlTextArray[textEnum.textTypeIdx]
        qmltextStorgeOutput                 = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmltextDataFilters                 = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmltextSummary                      = qmlTextArray[textEnum.textSummaryIdx]
        qmltextSingle                       = qmlTextArray[textEnum.textSingleIdx]
        qmltextContinuous                   = qmlTextArray[textEnum.textContinuousIdx]
        qmltextNext                         = qmlTextArray[textEnum.textNextIdx]
        qmltextMenuName                     = qmlTextArray[textEnum.textMenuNameIdx]
        qmltextStorgeOutput2                 = qmlTextArray[textEnum.textStorgeOutput2Idx]
        qmltextDataFilters2                 = qmlTextArray[textEnum.textStorgeOutput2Idx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATEREPORT, qmlTextMenuName)
    }
    QtObject
    {
        id: textEnum
        readonly property int textTabBarGenerateReportIdx               : 0
        readonly property int textTabBarSavedReportIdx                  : 1
        readonly property int textTypeIdx                               : 2
        readonly property int textStorgeOutputIdx                       : 3
        readonly property int textDataFiltersIdx                        : 4
        readonly property int textSummaryIdx                            : 5
        readonly property int textSingleIdx                             : 6
        readonly property int textContinuousIdx                         : 7
        readonly property int textNextIdx                               : 8
        readonly property int textMenuNameIdx                           : 9
        readonly property int textStorgeOutput2Idx                      : 8
        readonly property int textDataFilters2Idx                       : 9
    }

    Connections
    {
        target: mainWindow
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
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextType
            color: Style.headerBackgroundColor
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
        id: centerlineType
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        y:Math.round(180*Style.scaleHint)
        width: Math.round(750*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        text: qmltextType
        anchors.bottom:centerlineType.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Item {
        id:radiobtnsinglecont
        anchors.top:centerlineType.bottom
        anchors.topMargin:Math.round(20 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnSingle
            text: qmltextSingle
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            font.family: Style.regular.name
            checked: GenerateReportUserIOObj.m_TypeRadioButton ? true : false
            onClicked:
            {
                GenerateReportUserIOObj.updateReportType(true)
                GenerateReportUserIOObj.m_TypeRadioButton = true
            }
        }
        RadioButton
        {
            id:rdbtnContinous
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.top:rdbtnSingle.bottom
            anchors.topMargin:Math.round(20 * Style.scaleHint)
            text: qmltextContinuous
            font.family: Style.regular.name
            checked: GenerateReportUserIOObj.m_TypeRadioButton ? false : true
            onClicked:
            {
                GenerateReportUserIOObj.updateReportType(false)

                GenerateReportUserIOObj.m_TypeRadioButton = false
            }
        }
    }
    BransonPrimaryButton
    {
        id: next
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(600 * Style.scaleHint)
        y : Math.round(325 * Style.scaleHint)
        anchors.top:rdbtnContinous.bottom
        anchors.topMargin:Math.round(150 * Style.scaleHint)
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextNext
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            if(GenerateReportUserIOObj.m_TypeRadioButton == true)
            {
                mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_STORAGE)
            }
            else{
                mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE)
            }
        }
    }
    Component.onCompleted:
    {
        updateLanguage();
        GenerateReportUserIOObj.m_TypeRadioButton = true
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.GENERATEREPORT)
    }
}


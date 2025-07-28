/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonChartRightSetting.qml file controls the graph data display logic.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 20/10/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
import AxisDefine 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
Rectangle
{
    signal firstAxisChanged(var index)
    signal secondAxisChanged(var index)
    property color firstRectColor: "#ef7c7d"
    property color secondRectColor: "#ef7c7d"
    property int fontSize: Math.round(Style.style1 * Style.scaleHint)
    property int companyfontSize: Math.round(Style.style4  * Style.scaleHint)

    property string qmltextFirstAxisTitle            : qsTr("Left Axis")
    property string qmltextSecondAxisTitle           : qsTr("Right Axis")
    property string qmltextEnableGraph               : qsTr("Enable Graph")
    property string qmltextAutoGraphRefresh          : qsTr("Auto Graph Refresh")
    property string qmltextAutoScaleYAxis            : qsTr("Auto Scale Y Axis")
    property string qmltextAutoScaleTimeAxis         : qsTr("Auto Scale Time Axis")
    property string qmltextTWHLine                   : qsTr("TWH Line")
    property string qmltextSetValues                 : qsTr("Set Values")
    property string qmltextTime                      : qsTr("Time")

    property var timeValue                           : 0
    signal isGraphEnableChanged(var value)

    property var qmlTextArray: [qmltextFirstAxisTitle, qmltextSecondAxisTitle, qmltextEnableGraph, qmltextAutoGraphRefresh, qmltextAutoScaleYAxis,
                                qmltextAutoScaleTimeAxis, qmltextTWHLine, qmltextSetValues, qmltextTime]
    id: rectright
    border.color: Style.activeFrameBorderColor
    border.width: Style.scaleHint === 1.0 ? 1 : 3
    color: Style.frameButtonBackgroundColor

    QtObject
    {
        id: textEnum
        readonly property int firstAxisTitleIdx        : 0
        readonly property int secondAxisTitleIdx       : 1
        readonly property int enableGraphIdx           : 2
        readonly property int autoGraphRefreshIdx      : 3
        readonly property int autoScaleYAxisIdx        : 4
        readonly property int autoScaleTimeAxisIdx     : 5
        readonly property int tWHLineIdx               : 6
        readonly property int setValues                : 7
        readonly property int timeIdx                  : 8
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_RIGHT_SETTING, qmlTextArray)
        qmltextFirstAxisTitle = qmlTextArray[textEnum.firstAxisTitleIdx]
        qmltextSecondAxisTitle = qmlTextArray[textEnum.secondAxisTitleIdx]
        qmltextEnableGraph = qmlTextArray[textEnum.enableGraphIdx]
        qmltextAutoGraphRefresh = qmlTextArray[textEnum.autoGraphRefreshIdx]
        qmltextAutoScaleYAxis = qmlTextArray[textEnum.autoScaleYAxisIdx]
        qmltextAutoScaleTimeAxis = qmlTextArray[textEnum.autoScaleTimeAxisIdx]
        qmltextTWHLine = qmlTextArray[textEnum.tWHLineIdx]
        qmltextSetValues = qmlTextArray[textEnum.setValues]
        qmltextTime = qmlTextArray[textEnum.timeIdx]
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
    }


    Rectangle
    {
        id: timeDisplay
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
        color: "transparent"

        Text
        {
            id: timeValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmltextTime + " : " + timeValue + " s"
            font.pixelSize: fontSize
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }
    Rectangle
    {
        id: separator
        anchors.top: timeDisplay.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }

    Rectangle
    {
        id: firstAxisSetting
        anchors.top: separator.bottom
        anchors.left: parent.left
        width: parent.width
        height: Math.round(60 * Style.scaleHint)
        color: "transparent"

        BransonComboBox
        {
            anchors.top: firstAxisSetting.top
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            minWidth: Math.round(160 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            model: AxisDefine.getAxisModel()
            onCurrentTextChanged:
            {
                firstAxisChanged(currentIndex)
            }
        }

        Row
        {
            anchors.top: firstAxisSetting.top
            anchors.topMargin: Math.round(35 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(10 * Style.scaleHint)
            Rectangle
            {
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                radius: width/2
                color: firstRectColor
                anchors.verticalCenter: firstAxisValue.verticalCenter
            }
            Text {
                id: firstAxisValue
                text: qsTr("12%")
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
        }

    }
    Rectangle
    {
        id: separator2
        anchors.top: firstAxisSetting.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }

    Rectangle
    {
        id:secondAxisSetting
        anchors.top: separator2.bottom
        width: parent.width
        height: Math.round(60 * Style.scaleHint)
        color: "transparent"

        BransonComboBox
        {
            anchors.top: secondAxisSetting.top
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            minWidth: Math.round(160 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            model: AxisDefine.getAxisModel()
            onCurrentTextChanged:
            {
                secondAxisChanged(currentIndex)
            }
        }
        Row
        {
            anchors.top: secondAxisSetting.top
            anchors.topMargin: Math.round(35 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(10 * Style.scaleHint)
            Rectangle
            {
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                radius: width/2
                color: secondRectColor
                anchors.verticalCenter: secondAxisValue.verticalCenter
            }
            Text {
                id: secondAxisValue
                text: qsTr("12W")
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
        }
    }
    Rectangle
    {
        id: separator3
        anchors.top: secondAxisSetting.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }

    Rectangle
    {
        id: configRect
        anchors.top: separator3.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "transparent"
        Column
        {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(2 * Style.scaleHint)

            Text
            {
                id: enableGraphTitle
                text: qmltextEnableGraph
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonSwitch
            {
                id: enableGraphSwitch
                anchors.left: enableGraphTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(18 * Style.scaleHint)
                checked: true
                onCheckedChanged:
                {
                    isGraphEnableChanged(enableGraphSwitch.checked)
                }
            }

            Text
            {
                id: autoGraphRefeshTitle
                text: qmltextAutoGraphRefresh
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonSwitch
            {
                id: autoGraphRefreshSwitch
                anchors.left: enableGraphTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(18 * Style.scaleHint)
                checked: true
            }

            Text
            {
                id: autoScaleYAxisTitle
                text: qmltextAutoScaleYAxis
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonSwitch
            {
                id: autoScaleYAxisSwitch
                anchors.left: enableGraphTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(18 * Style.scaleHint)
                checked: true
            }

            Text
            {
                id: autoScaleTimeTitle
                text: qmltextAutoScaleTimeAxis
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonSwitch
            {
                id: autoScaleTimeAxisSwitch
                anchors.left: enableGraphTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(18 * Style.scaleHint)
                checked: true
            }


            Text
            {
                id: tWHLineTitle
                text: qmltextTWHLine
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonSwitch
            {
                id: twhLineSwitch
                anchors.left: enableGraphTitle.left
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(18 * Style.scaleHint)
                checked: true
            }
        }

        Text
        {
            id: autoScaleYAxisSwitchLink
            anchors.top: configRect.top
            anchors.topMargin: Math.round(48 * Style.scaleHint)
            anchors.left: configRect.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            text: qmltextSetValues
            font.pixelSize: fontSize
            font.family: Style.regular.name
            color: Style.blueFontColor

            MouseArea
            {
                id: autoScaleYAxisSwitchLinkMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    mainWindow.showPrimaryNumpad("Y Scale Setting", "s", 3, 0, 5, "0.123")
                }
            }
        }

        Text
        {
            id: autoScaleTimeAxisSwitchLink
            anchors.top: configRect.top
            anchors.topMargin: Math.round(78 * Style.scaleHint)
            anchors.left: configRect.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            text: qmltextSetValues
            font.pixelSize: fontSize
            font.family: Style.regular.name
            color: Style.blueFontColor

            MouseArea
            {
                id: autoScaleTAxisSwitchLinkMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                }
            }
        }


    }
}


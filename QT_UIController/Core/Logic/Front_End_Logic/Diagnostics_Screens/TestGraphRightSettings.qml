/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    TestGraphChartRightSetting.qml file controls the horn test graph data setting
    logic.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/03/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
Rectangle
{
    id: rectright
    border.color: Style.activeFrameBorderColor
    border.width: Style.scaleHint === 1.0 ? 1 : 3
    color: "#FFFFFF"

    property color firstRectColor: "#ef7c7d"
    property color secondRectColor: "#ef7c7d"
    property int fontSize: Math.round(9 * Style.scaleHint)
    property int companyfontSize: Math.round(Style.style4  * Style.scaleHint)

    property string qmltextTime                      : "Time"

    property int    firstYAxisSelectedEnum           : GraphAxisEnum.AMP_IDX
    property int    secondYAxisSelectedEnum          : GraphAxisEnum.AMP_IDX
    property double firstYAxisValueText
    property double secondYAxisValueText
    property string firstUnitValue
    property string secondUnitValue

    property real timeValue                          : 0

    signal axisChanged(var firstIndex, var secondIndex)

    property var qmlTextArray: [qmltextTime]

    QtObject
    {
        id: textEnum

        readonly property int timeIdx                  : 0
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_TEST_GRAPH_VIEW, qmlTextArray)
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

        firstYAxisSelectedEnum = TestGraphSettings.FirstAxisValue
        secondYAxisSelectedEnum = TestGraphSettings.SecondAxisValue
        axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
        firstUnitValue = AxisDefine.getUnitsTitle(TestGraphSettings.FirstAxisValue)
        secondUnitValue = AxisDefine.getUnitsTitle(TestGraphSettings.SecondAxisValue)
    }

    Rectangle
    {
        id: timeDisplay
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
        color: "#FFFFFF"

        Text
        {
            id: timeValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmltextTime + " : " + timeValue + " "+ mainWindow.qmltextTimeUnit
            font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }

    Rectangle
    {
        id: firstAxisSetting
        anchors.top: separator.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(80 * Style.scaleHint)
        color: "#FFFFFF"

        BransonComboBox
        {
            id: firstAxisComboBox
            currentIndex: TestGraphSettings.FirstAxisValue
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            minWidth: Math.round(90 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            model: AxisDefine.getTestAxisModel()
            onCurrentTextChanged:
            {
                firstYAxisSelectedEnum = currentIndex
                axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                TestGraphSettings.FirstAxisValue = firstAxisComboBox.currentIndex
                firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
            }
        }

        Row
        {
            id: firstAxisSettingRow
            anchors.left: firstAxisComboBox.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(1 * Style.scaleHint)
            Rectangle
            {
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                radius: width/2
                color: firstRectColor
                anchors.verticalCenter: firstAxisValue.verticalCenter
            }

            Text
            {
                id: firstAxisValue
                text: firstYAxisValueText + " " + firstUnitValue
                font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
        }

    }

    Rectangle
    {
        id:secondAxisSetting
        anchors.top: separator2.top
        width: parent.width
        height: Math.round(80 * Style.scaleHint)
        color: "#FFFFFF"

        BransonComboBox
        {
            id: secondAxisComboBox
            currentIndex: TestGraphSettings.SecondAxisValue
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            minWidth: Math.round(90 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            model: AxisDefine.getTestAxisModel()
            onCurrentTextChanged:
            {
                secondYAxisSelectedEnum = currentIndex
                axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                TestGraphSettings.SecondAxisValue = secondAxisComboBox.currentIndex
                firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
            }
        }

        Row
        {
            id: secondAxisSettingRow
            anchors.left: secondAxisComboBox.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(1 * Style.scaleHint)
            Rectangle
            {
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                radius: width/2
                color: secondRectColor
                anchors.verticalCenter: secondAxisValue.verticalCenter
            }

            Text
            {
                id: secondAxisValue
                text: secondYAxisValueText + " " + secondUnitValue
                font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }
        }
    }

    Rectangle
    {
        id: separator
        anchors.top: timeDisplay.bottom
        anchors.left: parent.left
        width: parent.width
        height: 1
        color: "#D4D4D4"
    }

    Rectangle
    {
        id: separator2
        anchors.top: firstAxisSetting.bottom
        anchors.left: parent.left
        width: parent.width
        height: 1
        color: "#D4D4D4"
    }

    Rectangle
    {
        id: borderRect
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "transparent"
        border.color: "#707070"
    }
}


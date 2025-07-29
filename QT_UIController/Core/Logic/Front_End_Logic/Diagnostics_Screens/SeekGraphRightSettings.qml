/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    SeekGraphChartRightSetting.qml file controls the horn seek graph data setting
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

    property string qmltextTime                 : "Time"
    property string qmltextEndFrequency         : "End Frequency"

    property int    firstYAxisSelectedEnum           : GraphAxisEnum.AMP_IDX
    property int    secondYAxisSelectedEnum          : GraphAxisEnum.AMP_IDX
    property double firstYAxisValueText
    property double secondYAxisValueText
    property string firstUnitValue
    property string secondUnitValue

    property real timeValue                          : 0

    signal axisChanged(var firstIndex, var secondIndex)

    property var qmlTextArray: [qmltextEndFrequency]

    QtObject
    {
        id: textEnum

        readonly property int timeIdx                  : 0
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SEEK_GRAPH_VIEW, qmlTextArray)
        qmltextEndFrequency = qmlTextArray[textEnum.timeIdx]
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

        firstYAxisSelectedEnum = SeekGraphSettings.FirstAxisValue
        secondYAxisSelectedEnum = SeekGraphSettings.SecondAxisValue
        axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
        firstUnitValue = AxisDefine.getUnitsTitle(SeekGraphSettings.FirstAxisValue)
        secondUnitValue = AxisDefine.getUnitsTitle(SeekGraphSettings.SecondAxisValue)
    }

    Rectangle
    {
        id: seekCycleDetails
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(75 * Style.scaleHint)
        color: "#D4D4D4"
        border.color: "#707070"

        Text
        {
            id: seekEndFrequencyValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            text: qmltextEndFrequency + " : " + SeekData.SeekEndFrequency
            font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: seekTimeValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            text: SeekData.SeekDateAndTime
            font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }

    Rectangle
    {
        id: separator
        anchors.left: parent.left
        anchors.top: seekCycleDetails.bottom
        width: parent.width
        height: 1
        color: "#D4D4D4"
    }



    /*Rectangle
    {
        id: timeDisplay
        anchors.left: parent.left
        anchors.top: separator.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
        color: "transparent"

        Text
        {
            id: timeValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmltextTime + " : " + timeValue + " "+UnitConversion.TimeUnit
            font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }

    Rectangle
    {
        id: separator2
        anchors.top: timeDisplay.bottom
        anchors.left: parent.left
        width: parent.width
        height: Style.scaleHint === 1.0 ? 1 : 3
        color: Style.activeFrameBorderColor
    }*/

    Rectangle
    {
        id: axesSettings
        anchors.top: separator.bottom
        anchors.left: parent.left
        width: parent.width
        height: Math.round(249 * Style.scaleHint)
        color: "#FFFFFF"
        border.color: "#707070"

        BransonComboBox
        {
            id: firstAxisComboBox
            currentIndex: SeekGraphSettings.FirstAxisValue
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            minWidth: Math.round(90 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            model: AxisDefine.getSeekAxisModel()
            onCurrentTextChanged:
            {
                firstYAxisSelectedEnum = currentIndex
                axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                SeekGraphSettings.FirstAxisValue = firstAxisComboBox.currentIndex
                firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
            }
        }

        Row
        {
            id: firstAxisSettingRow
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            anchors.left: firstAxisComboBox.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
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
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: separator2
            anchors.top: firstAxisComboBox.bottom
            anchors.topMargin: (10 * Style.scaleHint)
            anchors.left: parent.left
            width: parent.width
            height: 1
            color: "#D4D4D4"
        }

            BransonComboBox
            {
                id: secondAxisComboBox
                currentIndex: SeekGraphSettings.SecondAxisValue
                anchors.top: separator2.bottom
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                model: AxisDefine.getSeekAxisModel()
                onCurrentTextChanged:
                {
                    secondYAxisSelectedEnum = currentIndex
                    axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    SeekGraphSettings.SecondAxisValue = secondAxisComboBox.currentIndex
                    firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                    secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
                }
            }

            Row
            {
                id: secondAxisSettingRow
                anchors.top: separator2.bottom
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: secondAxisComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
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
                    color: Style.blackFontColor
                }
            }

            Rectangle
            {
                id: separator3
                anchors.top: secondAxisComboBox.bottom
                anchors.topMargin: (10 * Style.scaleHint)
                anchors.left: parent.left
                width: parent.width
                height: 1
                color: "#D4D4D4"
            }
    }    
}


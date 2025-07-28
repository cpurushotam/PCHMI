/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanGraphChartRightSetting.qml file controls the horn scan graph data setting
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

    property color firstRectColor: "#EF7C7D"
    property color secondRectColor: "#00AA7E"
    property color thirdRectColor: "#757577"
    property int fontSize: Math.round(9 * Style.scaleHint)
    property int companyfontSize: Math.round(Style.style4  * Style.scaleHint)

    property string qmltextParallelResonantFrequencyText         : "Parallel Resonant Frequency"
    property string qmltextFirstParallelResonantFrequency        : "First"
    property string qmltextSecondParallelResonantFrequency       : "Second"
    property string qmltextThirdParallelResonantFrequency        : "Third"
    property string qmltextSeriesResonantFrequencyText           : "Series Resonant Frequency"
    property string qmltextFirstSeriesResonantFrequency          : "First"
    property string qmltextSecondSeriesResonantFrequency         : "Second"
    property string qmltextThirdSeriesResonantFrequency          : "Third"

    property int    firstYAxisSelectedEnum           : GraphAxisEnum.AMP_IDX
    property int    secondYAxisSelectedEnum          : GraphAxisEnum.AMP_IDX
    property double firstYAxisValueText
    property double secondYAxisValueText
    property double thirdYAxisValueText
    property string firstUnitValue                    : AxisDefine.getUnitsTitle(GraphAxisEnum.AMP_IDX)
    property string secondUnitValue                   : AxisDefine.getUnitsTitle(GraphAxisEnum.CURRENT_IDX)
    property string thirdUnitValue                    : AxisDefine.getUnitsTitle(GraphAxisEnum.PHASE_IDX)
    property bool   visibleFlag                       : true
    property bool   visibleFlag2                      : true
    property bool   visibleFlag3                      : true

    property real freqValue                          : 0

    property var qmlTextArray: [qmltextParallelResonantFrequencyText, qmltextFirstParallelResonantFrequency, qmltextSecondParallelResonantFrequency, qmltextThirdParallelResonantFrequency,
                                qmltextSeriesResonantFrequencyText, qmltextFirstSeriesResonantFrequency, qmltextSecondSeriesResonantFrequency, qmltextThirdSeriesResonantFrequency]

    QtObject
    {
        id: textEnum

        readonly property int parallelResonantFrequencyTextIdx   : 0
        readonly property int firstParallelResonantFrequencyIdx  : 1
        readonly property int secondParallelResonantFrequencyIdx : 2
        readonly property int thirdParallelResonantFrequencyIdx  : 3
        readonly property int seriesResonantFrequencyTextIdx     : 4
        readonly property int firstSeriesResonantFrequencyIdx    : 5
        readonly property int secondSeriesResonantFrequencyIdx   : 6
        readonly property int thirdSeriesResonantFrequencyIdx    : 7
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SEEK_GRAPH_VIEW, qmlTextArray)
        qmltextParallelResonantFrequencyText   = qmlTextArray[textEnum.parallelResonantFrequencyTextIdx]
        qmltextFirstParallelResonantFrequency  = qmlTextArray[textEnum.firstParallelResonantFrequencyIdx]
        qmltextSecondParallelResonantFrequency = qmlTextArray[textEnum.secondParallelResonantFrequencyIdx]
        qmltextThirdParallelResonantFrequency  = qmlTextArray[textEnum.thirdParallelResonantFrequencyIdx]
        qmltextSeriesResonantFrequencyText     = qmlTextArray[textEnum.seriesResonantFrequencyTextIdx]
        qmltextFirstSeriesResonantFrequency    = qmlTextArray[textEnum.firstSeriesResonantFrequencyIdx]
        qmltextSecondSeriesResonantFrequency   = qmlTextArray[textEnum.secondSeriesResonantFrequencyIdx]
        qmltextThirdSeriesResonantFrequency    = qmlTextArray[textEnum.thirdSeriesResonantFrequencyIdx]
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

        /*firstYAxisSelectedEnum = ScanGraphSettings.FirstAxisValue
        secondYAxisSelectedEnum = ScanGraphSettings.SecondAxisValue
        firstUnitValue = AxisDefine.getUnitsTitle(ScanGraphSettings.FirstAxisValue)
        secondUnitValue = AxisDefine.getUnitsTitle(ScanGraphSettings.SecondAxisValue)*/
    }

    Rectangle
    {
        id: scanCycleDetailsSettings
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(220 * Style.scaleHint)
        color: "#D4D4D4"
        border.color: "#707070"

        Text
        {
            id: parallelResonantFreqTitle
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            text: qmltextParallelResonantFrequencyText
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: Style.blackFontColor
        }

        Text
        {
            id: firstParallelFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parallelResonantFreqTitle.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextFirstParallelResonantFrequency + " : " + ScanCycleDetailsListModel.ScanMainParallelResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: secondParallelFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: firstParallelFreqText.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextSecondParallelResonantFrequency + " : " +  ScanCycleDetailsListModel.ScanSecondParallelResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: thirdParallelFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: secondParallelFreqText.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextThirdParallelResonantFrequency + " : " + ScanCycleDetailsListModel.ScanThirdParallelResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: seriesResonantFreqTitle
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: thirdParallelFreqText.bottom
            anchors.topMargin: Math.round(25 * Style.scaleHint)
            text: qmltextSeriesResonantFrequencyText
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: Style.blackFontColor
        }

        Text
        {
            id: firstSeriesFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: seriesResonantFreqTitle.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextFirstSeriesResonantFrequency + " : " + ScanCycleDetailsListModel.ScanMainSeriesResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: secondSeriesFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: firstSeriesFreqText.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextSecondSeriesResonantFrequency + " : " + ScanCycleDetailsListModel.ScanSecondSeriesResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: thirdSeriesFreqText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: secondSeriesFreqText.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            text: qmltextThirdSeriesResonantFrequency + " : " + ScanCycleDetailsListModel.ScanThirdSeriesResFreq
            font.pixelSize: Math.round(Style.style0  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }

    Rectangle
    {
        id: separator
        anchors.top: scanCycleDetailsSettings.bottom
        anchors.left: parent.left
        width: parent.width
        height: 1
    }

    Rectangle
    {
        id: axesSettings
        anchors.top: separator.bottom
        anchors.left: parent.left
        width: parent.width
        height: Math.round(145 * Style.scaleHint)
        color: "#FFFFFF"
        border.color: "#707070"

        Image
        {
            id: visibleIcon
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(12 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            source: (ScanGraphSettings.AmplitudeAxisVisible) ? "qrc:/Images/OpenEye.png" : "qrc:/Images/HiddenEye.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            smooth: true

            MouseArea
            {
                id: visibleIconMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(visibleFlag)
                    {
                        visibleIcon.source = "qrc:/Images/HiddenEye.png"
                        ScanGraphSettings.AmplitudeAxisVisible = false
                        hiddenRectangle.visible = true
                        visibleFlag = false
                    }

                    else
                    {
                        visibleIcon.source = "qrc:/Images/OpenEye.png"
                        ScanGraphSettings.AmplitudeAxisVisible = true
                        hiddenRectangle.visible = false
                        visibleFlag = true
                    }
                }
            }
        }

        Rectangle
        {
            id: firstAxisComboBox
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: visibleIcon.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: Math.round(90 * Style.scaleHint)
            height: Math.round(25 * Style.scaleHint)
            border.color: "#707070"
            radius: Math.round(5 * Style.scaleHint)

            Text
            {
                id: firstAxisText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "Amplitude"
                font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Row
        {
            id: firstAxisSettingRow
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(18 * Style.scaleHint)
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
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: hiddenRectangle
            visible: false
            anchors.top: axesSettings.top
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left: visibleIcon.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: parent.width - Math.round(35 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            color: "#FFFFFF"
            opacity: 0.5
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

        Image
        {
            id: visibleIcon2
            anchors.top: separator2.bottom
            anchors.topMargin: Math.round(12 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            source: (ScanGraphSettings.CurrentAxisVisible) ? "qrc:/Images/OpenEye.png" : "qrc:/Images/HiddenEye.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            smooth: true

            MouseArea
            {
                id: visibleIconMa2
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(visibleFlag2)
                    {
                        visibleIcon2.source = "qrc:/Images/HiddenEye.png"
                        ScanGraphSettings.CurrentAxisVisible = false
                        hiddenRectangle2.visible = true
                        visibleFlag2 = false
                    }

                    else
                    {
                        visibleIcon2.source = "qrc:/Images/OpenEye.png"
                        ScanGraphSettings.CurrentAxisVisible = true
                        hiddenRectangle2.visible = false
                        visibleFlag2 = true
                    }
                }
            }
        }

        Rectangle
        {
            id: secondAxisComboBox
            anchors.top: separator2.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: visibleIcon2.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: Math.round(90 * Style.scaleHint)
            height: Math.round(25 * Style.scaleHint)
            border.color: "#707070"
            radius: Math.round(5 * Style.scaleHint)

            Text
            {
                id: secondAxisText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "Current"
                font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Row
        {
            id: secondAxisSettingRow
            anchors.top: separator2.bottom
            anchors.topMargin: Math.round(18 * Style.scaleHint)
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
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: hiddenRectangle2
            visible: false
            anchors.top: separator2.bottom
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left: visibleIcon.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: parent.width - Math.round(35 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            color: "#FFFFFF"
            opacity: 0.5
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

        Image
        {
            id: visibleIcon3
            anchors.top: separator3.bottom
            anchors.topMargin: Math.round(12 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            source: (ScanGraphSettings.PhaseAxisVisible) ? "qrc:/Images/OpenEye.png" : "qrc:/Images/HiddenEye.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            smooth: true

            MouseArea
            {
                id: visibleIconMa3
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(visibleFlag3)
                    {
                        visibleIcon3.source = "qrc:/Images/HiddenEye.png"
                        ScanGraphSettings.PhaseAxisVisible = false
                        hiddenRectangle3.visible = true
                        visibleFlag3 = false
                    }

                    else
                    {
                        visibleIcon3.source = "qrc:/Images/OpenEye.png"
                        ScanGraphSettings.PhaseAxisVisible = true
                        hiddenRectangle3.visible = false
                        visibleFlag3 = true
                    }
                }
            }
        }

        Rectangle
        {
            id: thirdAxisComboBox
            anchors.top: separator3.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: visibleIcon3.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: Math.round(90 * Style.scaleHint)
            height: Math.round(25 * Style.scaleHint)
            border.color: "#707070"
            radius: Math.round(5 * Style.scaleHint)

            Text
            {
                id: thirdAxisText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "Phase"
                font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Row
        {
            id: thirdAxisSettingRow
            anchors.top: separator3.bottom
            anchors.topMargin: Math.round(18 * Style.scaleHint)
            anchors.left: thirdAxisComboBox.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            spacing: Math.round(1 * Style.scaleHint)

            Rectangle
            {
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                radius: width/2
                color: thirdRectColor
                anchors.verticalCenter: thirdAxisValue.verticalCenter
            }

            Text
            {
                id: thirdAxisValue
                text: thirdYAxisValueText + " " + thirdUnitValue
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: hiddenRectangle3
            visible: false
            anchors.top: separator3.bottom
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left: visibleIcon.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            width: parent.width - Math.round(35 * Style.scaleHint)
            height: Math.round(40 * Style.scaleHint)
            color: "#FFFFFF"
            opacity: 0.5
        }
    }
}


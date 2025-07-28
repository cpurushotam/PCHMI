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
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
Rectangle
{
    id: rectright
    border.color: "#707070"
    color: "#FFFFFF"

    property color firstRectColor: "#ef7c7d"
    property color secondRectColor: "#ef7c7d"
    property color firstRefRectColor: "#ef7c7d"
    property color secondRefRectColor: "#ef7c7d"
    property int fontSize: Math.round(15 * Style.scaleHint)
    property int companyfontSize: Math.round(Style.style4  * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property string qmltextFirstAxisTitle            : "Left Axis"
    property string qmltextSecondAxisTitle           : "Right Axis"
    property string qmltextEnableGraph               : "Auto Save Graph"
    property string qmltextAutoGraphRefresh          : "Auto Graph Refresh"
    property string qmltextAutoScaleYAxis            : "Auto Scale Y Axis"
    property string qmltextAutoScaleTimeAxis         : "Auto Scale Time Axis"
    property string qmltextTWHLine                   : "TWH Line"
    property string qmltextSetValues                 : "Set Values"
    property string qmltextTime                      : "Time"

    property string qmltextYScaleSettings            : "SET AUTO SCALE Y AXIS VALUES"
    property string qmltextTimeScaleSettings         : "SET AUTO SCALE TIME AXIS VALUES"

    property string qmltextSamplingInterval          : "Sampling Interval"
    property string qmltextORG                       : "ORG"
    property string qmltextRef                       : "REF"

    property int    firstYAxisSelectedEnum           : GraphAxisEnum.AMP_IDX
    property int    secondYAxisSelectedEnum          : GraphAxisEnum.AMP_IDX
    property int    firstYRefAxisSelectedEnum        : GraphAxisEnum.AMP_IDX
    property int    secondYRefAxisSelectedEnum       : GraphAxisEnum.AMP_IDX

    property double firstYAxisValueText
    property double secondYAxisValueText
    property double firstYRefAxisValueText
    property double secondYRefAxisValueText

    property string firstUnitValue
    property string secondUnitValue

    property real timeValue                          : 0
    property bool isReferenceGraphEnable             : false

    signal axisChanged(var firstIndex, var secondIndex)
    signal isGraphEnableChanged(var value)
    signal autoScaleYAxisEnabled()
    signal autoScaleTimeAxisEnabled()

    property var qmlTextArray: [qmltextFirstAxisTitle, qmltextSecondAxisTitle, qmltextEnableGraph, qmltextAutoGraphRefresh, qmltextAutoScaleYAxis,
        qmltextAutoScaleTimeAxis, qmltextTWHLine, qmltextSetValues, qmltextTime, qmltextYScaleSettings, qmltextTimeScaleSettings,
        qmltextSamplingInterval, qmltextORG, qmltextRef]

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
        readonly property int yScaleSettingsIdx        : 9
        readonly property int timeScaleSettingsIdx     : 10
        readonly property int samplingIntervalIdx      : 11
        readonly property int oRGIdx                   : 12
        readonly property int refIdx                   : 13
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
        qmltextYScaleSettings = qmlTextArray[textEnum.yScaleSettingsIdx]
        qmltextTimeScaleSettings = qmlTextArray[textEnum.timeScaleSettingsIdx]
        qmltextSamplingInterval = qmlTextArray[textEnum.samplingIntervalIdx]
        qmltextORG = qmlTextArray[textEnum.oRGIdx]
        qmltextRef = qmlTextArray[textEnum.refIdx]
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

        firstYAxisSelectedEnum = GraphSettings.FirstAxisValue
        secondYAxisSelectedEnum = GraphSettings.SecondAxisValue
        axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
        firstUnitValue = AxisDefine.getUnitsTitle(GraphSettings.FirstAxisValue)
        secondUnitValue = AxisDefine.getUnitsTitle(GraphSettings.SecondAxisValue)
    }

    Rectangle
    {
        id: timeDisplay
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        color: "transparent"
        border.color: "#000000"

        Text
        {
            id: timeValueText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmltextTime + " : " + timeValue.toFixed(3) + " " + mainWindow.qmltextTimeUnit
            font.pixelSize: Math.round(Style.style1  * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }

    /*********************When Golden Graph is not visible******************/

    Rectangle
    {
        id: settingsWithoutRefGraphs
        visible: (! isReferenceGraphEnable)
        anchors.top: timeDisplay.bottom
        anchors.left: parent.left
        width: parent.width
        height: parent.height - timeDisplay.height

        /*Below visibility handling makes sure that axes value combo box are in sync when
          visibility changes*/

        onVisibleChanged:
        {
            firstAxisComboBox.currentIndex = GraphSettings.FirstAxisValue
            secondAxisComboBox.currentIndex = GraphSettings.SecondAxisValue
        }

        Rectangle
        {
            id: separator
            anchors.top: timeDisplay.bottom
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
            height: Math.round(80 * Style.scaleHint)
            color: "#F0F0F0"
            border.color: "#000000"

            BransonComboBox
            {
                id: firstAxisComboBox
                currentIndex: GraphSettings.FirstAxisValue
                anchors.top: axesSettings.top
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                minWidth: Math.round(90 * Style.scaleHint)
                minHeight: Math.round(25 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    firstYAxisSelectedEnum = currentIndex
                    axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    GraphSettings.FirstAxisValue = firstAxisComboBox.currentIndex
                    firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                    secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
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

            BransonComboBox
            {
                id: secondAxisComboBox
                currentIndex: GraphSettings.SecondAxisValue
                anchors.top: firstAxisComboBox.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                minWidth: Math.round(90 * Style.scaleHint)
                minHeight: Math.round(25 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    secondYAxisSelectedEnum = currentIndex
                    axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    GraphSettings.SecondAxisValue = secondAxisComboBox.currentIndex
                    firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                    secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
                }
            }

            Row
            {
                id: secondAxisSettingRow
                anchors.top: firstAxisSettingRow.bottom
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
        }

        Rectangle
        {
            id: separator2
            anchors.top: axesSettings.bottom
            anchors.left: parent.left
            width: parent.width
            height: 1
        }

        Rectangle
        {
            id: samplingInterval
            anchors.top: separator2.bottom
            anchors.left: parent.left
            width: parent.width
            height: Math.round(50 * Style.scaleHint)
            color: "transparent"

            Text
            {
                id: samplingIntervalTextInput
                anchors.left: samplingInterval.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: samplingInterval.top
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                text: qmltextSamplingInterval
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonLineEdit
            {
                id: samplingIntervalInput
                text: GraphSettings.SamplingInterval
                anchors.left: samplingInterval.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: samplingInterval.top
                anchors.topMargin: Math.round(25 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(20 * Style.scaleHint)
                font.pixelSize: Math.round(8 * Style.scaleHint)
                focus: true
                background: Rectangle
                {
                    color: "#FFFFFF"
                    radius: 5
                    border.color: "#707070"
                    border.width: 1
                }

                MouseArea
                {
                    id: searchCycleNoMouseArea
                    anchors.fill: parent
                    onClicked:
                    {
                        mainWindow.showPrimaryNumpad(qmltextSamplingInterval.toUpperCase(), "ms", 0, 0, 100, samplingIntervalInput.text)
                    }
                }
            }

            Text
            {
                id: samplingIntervalUnit
                anchors.left: samplingIntervalInput.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: samplingInterval.top
                anchors.topMargin: Math.round(23 * Style.scaleHint)
                text: "ms"
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: separator3
            anchors.top: samplingInterval.bottom
            anchors.left: parent.left
            width: parent.width
            height: 1
            color: "#707070"
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
                spacing: Math.round(5 * Style.scaleHint)

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
                    checked: GraphSettings.AutoSaveGraph
                    anchors.left: enableGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoSaveGraph = enableGraphSwitch.checked
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
                    checked: CycleDetailsListModel.isAutoRefreshGraph()
                    anchors.left: enableGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        CycleDetailsListModel.autoRefreshGraphRequest(autoGraphRefreshSwitch.checked)
                    }
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
                    checked: true /*GraphSettings.AutoScaleYAxis*/
                    anchors.left: enableGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoScaleYAxis = autoScaleYAxisSwitch.checked

                        if(autoScaleYAxisSwitch.checked)
                        {
                            autoScaleYAxisEnabled()
                        }
                    }
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
                    checked: true /*GraphSettings.AutoScaleTimeAxis*/
                    anchors.left: enableGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoScaleTimeAxis = autoScaleTimeAxisSwitch.checked

                        if(autoScaleTimeAxisSwitch.checked)
                        {
                            autoScaleTimeAxisEnabled()
                        }
                    }
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
                    checked: GraphSettings.TWHLineDisplay
                    anchors.left: enableGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.TWHLineDisplay = twhLineSwitch.checked
                    }
                }
            }

            Text
            {
                id: autoScaleYAxisSwitchLink
                anchors.left: configRect.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                anchors.top: configRect.top
                anchors.topMargin: Math.round(100 * Style.scaleHint)
                text: qmltextSetValues
                font.pixelSize: Math.round(12 * Style.scaleHint)
                font.family: Style.regular.name
                color: autoScaleYAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor

                Rectangle
                {
                    id: link
                    anchors.top: autoScaleYAxisSwitchLink.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    height: Math.round(2 * Style.scaleHint)
                    width: autoScaleYAxisSwitchLink.width
                    color: autoScaleYAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor
                }

                MouseArea
                {
                    id: autoScaleYAxisSwitchLinkMa
                    enabled: (! autoScaleYAxisSwitch.checked)
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        mainWindow.showMinMaxNumpad(qmltextYScaleSettings, true, firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    }
                }
            }

            Text
            {
                id: autoScaleTimeAxisSwitchLink
                anchors.left: configRect.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                anchors.top: configRect.top
                anchors.topMargin: Math.round(145 * Style.scaleHint)
                text: qmltextSetValues
                font.pixelSize: Math.round(12 * Style.scaleHint)
                font.family: Style.regular.name
                color: autoScaleTimeAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor

                Rectangle
                {
                    id: link2
                    anchors.top: autoScaleTimeAxisSwitchLink.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    height: Math.round(2 * Style.scaleHint)
                    width: autoScaleTimeAxisSwitchLink.width
                    color: autoScaleTimeAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor
                }

                MouseArea
                {
                    id: autoScaleTimeAxisSwitchLinkMa
                    enabled: (! autoScaleTimeAxisSwitch.checked)
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        mainWindow.showMinMaxNumpad(qmltextTimeScaleSettings, false, "NA", "NA")
                    }
                }
            }
        }
    }

    /*********************When Golden Graph is visible******************/

    Flickable
    {
        id: settingsWithRefGraphs
        visible: (isReferenceGraphEnable)
        width: parent.width
        height: parent.height * 0.91
        anchors.top: timeDisplay.bottom
        contentHeight: height * 1.20
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true

        /*Below visibility handling makes sure that axes value combo box are in sync when
          visibility changes*/

        onVisibleChanged:
        {
            firstRefAxisComboBox.currentIndex = GraphSettings.FirstAxisValue
            secondRefAxisComboBox.currentIndex = GraphSettings.SecondAxisValue
        }

        Rectangle
        {
            id: refSeparator
            anchors.top: timeDisplay.bottom
            anchors.left: parent.left
            width: parent.width
            height: 1
        }

        Rectangle
        {
            id: refAxesSettings
            anchors.top: refSeparator.bottom
            anchors.left: parent.left
            width: parent.width
            height: Math.round(150 * Style.scaleHint)
            color: "#F0F0F0"
            border.color: "#000000"

            BransonComboBox
            {
                id: firstRefAxisComboBox
                currentIndex: GraphSettings.FirstAxisValue
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: refAxesSettings.top
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                minWidth: Math.round(90 * Style.scaleHint)
                minHeight: Math.round(25 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    firstYAxisSelectedEnum = currentIndex
                    axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    GraphSettings.FirstAxisValue = firstRefAxisComboBox.currentIndex
                    firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                    secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
                }
            }

            Text
            {
                id: firstValueTypeText
                text: qmltextORG
                anchors.left: parent.left
                anchors.leftMargin: Math.round(30 * Style.scaleHint)
                anchors.top: firstRefAxisComboBox.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                font.bold: true
                color: Style.blackFontColor
            }

            Row
            {
                id: firstRefAxisSettingRow
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: firstRefAxisComboBox.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                spacing: Math.round(1 * Style.scaleHint)

                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: firstRectColor
                    anchors.verticalCenter: firstRefAxisValue.verticalCenter
                }

                Text
                {
                    id: firstRefAxisValue
                    text: firstYAxisValueText + " " + firstUnitValue
                    font.pixelSize: Math.round(9  * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
            }

            Text
            {
                id: firstValueTypeText2
                text: qmltextRef
                anchors.left: firstValueTypeText.right
                anchors.leftMargin: Math.round(50 * Style.scaleHint)
                anchors.top: firstRefAxisComboBox.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                font.bold: true
                color: Style.blackFontColor
            }

            Row
            {
                id: firstRefAxisSettingRow2
                anchors.left: firstRefAxisSettingRow.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: firstRefAxisComboBox.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                spacing: Math.round(1 * Style.scaleHint)

                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: firstRefRectColor
                    anchors.verticalCenter: firstRefAxisValue2.verticalCenter
                }

                Text
                {
                    id: firstRefAxisValue2
                    text: firstYRefAxisValueText + " " + firstUnitValue
                    font.pixelSize: Math.round(9  * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
            }

            Rectangle
            {
                id: refSeparator4
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: 1
                color: "#000000"
            }

            BransonComboBox
            {
                id: secondRefAxisComboBox
                currentIndex: GraphSettings.SecondAxisValue
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: refSeparator4.bottom
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                minWidth: Math.round(90 * Style.scaleHint)
                minHeight: Math.round(25 * Style.scaleHint)
                model: AxisDefine.getAxisModel()
                onCurrentTextChanged:
                {
                    secondYAxisSelectedEnum = currentIndex
                    axisChanged(firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    GraphSettings.SecondAxisValue = secondRefAxisComboBox.currentIndex
                    firstUnitValue = AxisDefine.getUnitsTitle(firstYAxisSelectedEnum)
                    secondUnitValue = AxisDefine.getUnitsTitle(secondYAxisSelectedEnum)
                }
            }

            Text
            {
                id: secondValueTypeText
                text: qmltextORG
                anchors.left: parent.left
                anchors.leftMargin: Math.round(30 * Style.scaleHint)
                anchors.top: secondRefAxisComboBox.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                font.bold: true
                color: Style.blackFontColor
            }

            Row
            {
                id: secondRefAxisSettingRow
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: secondRefAxisComboBox.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                spacing: Math.round(1 * Style.scaleHint)

                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: secondRectColor
                    anchors.verticalCenter: secondRefAxisValue.verticalCenter
                }

                Text
                {
                    id: secondRefAxisValue
                    text: secondYAxisValueText + " " + secondUnitValue
                    font.pixelSize: Math.round(9  * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
            }

            Text
            {
                id: secondValueTypeText2
                text: qmltextRef
                anchors.left: secondValueTypeText.right
                anchors.leftMargin: Math.round(50 * Style.scaleHint)
                anchors.top: secondRefAxisComboBox.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(9  * Style.scaleHint)
                font.family: Style.regular.name
                font.bold: true
                color: Style.blackFontColor
            }

            Row
            {
                id: secondRefAxisSettingRow2
                anchors.left: secondRefAxisSettingRow.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: secondRefAxisComboBox.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                spacing: Math.round(1 * Style.scaleHint)

                Rectangle
                {
                    width: Math.round(15 * Style.scaleHint)
                    height: Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: secondRefRectColor
                    anchors.verticalCenter: secondRefAxisValue2.verticalCenter
                }

                Text
                {
                    id: secondRefAxisValue2
                    text: secondYRefAxisValueText + " " + secondUnitValue
                    font.pixelSize: Math.round(9  * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
            }
        }

        Rectangle
        {
            id: refSeparator2
            anchors.top: refAxesSettings.bottom
            anchors.left: parent.left
            width: parent.width
            height: 1
        }

        Rectangle
        {
            id: refSamplingInterval
            anchors.top: refSeparator2.bottom
            anchors.left: parent.left
            width: parent.width
            height: Math.round(50 * Style.scaleHint)
            color: "transparent"

            Text
            {
                id: refSamplingIntervalTextInput
                anchors.left: refSamplingInterval.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: refSamplingInterval.top
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                text: qmltextSamplingInterval
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            BransonLineEdit
            {
                id: refSamplingIntervalInput
                text: GraphSettings.SamplingInterval
                anchors.left: refSamplingInterval.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: refSamplingInterval.top
                anchors.topMargin: Math.round(25 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(20 * Style.scaleHint)
                font.pixelSize: Math.round(8 * Style.scaleHint)
                focus: true
                background: Rectangle
                {
                    color: "#FFFFFF"
                    radius: 5
                    border.color: "#707070"
                    border.width: 1
                }

                MouseArea
                {
                    id: refSearchCycleNoMouseArea
                    anchors.fill: parent
                    onClicked:
                    {
                        mainWindow.showPrimaryNumpad(qmltextSamplingInterval.toUpperCase(), "ms", 0, 0, 100, refSamplingIntervalInput.text)
                    }
                }
            }

            Text
            {
                id: refSamplingIntervalUnit
                anchors.left: refSamplingIntervalInput.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: refSamplingInterval.top
                anchors.topMargin: Math.round(23 * Style.scaleHint)
                text: "ms"
                font.pixelSize: fontSize
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
        }

        Rectangle
        {
            id: refSeparator3
            anchors.top: refSamplingInterval.bottom
            anchors.left: parent.left
            width: parent.width
            height: 1
            color: "#707070"
        }

        Rectangle
        {
            id: refConfigRect
            anchors.top: refSeparator3.bottom
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
                spacing: Math.round(5 * Style.scaleHint)

                Text
                {
                    id: enableRefGraphTitle
                    text: qmltextEnableGraph
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id: enableRefGraphSwitch
                    checked: GraphSettings.AutoSaveGraph
                    anchors.left: enableRefGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoSaveGraph = enableRefGraphSwitch.checked
                    }
                }

                Text
                {
                    id: autoRefGraphRefeshTitle
                    text: qmltextAutoGraphRefresh
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id: autoRefGraphRefreshSwitch
                    checked: CycleDetailsListModel.isAutoRefreshGraph()
                    anchors.left: enableRefGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        CycleDetailsListModel.autoRefreshGraphRequest(autoRefGraphRefreshSwitch.checked)
                    }
                }

                Text
                {
                    id: autoScaleYRefAxisTitle
                    text: qmltextAutoScaleYAxis
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id: autoScaleYRefAxisSwitch
                    checked: true /*GraphSettings.AutoScaleYAxis*/
                    anchors.left: enableRefGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoScaleYAxis = autoScaleYRefAxisSwitch.checked

                        if(autoScaleYRefAxisSwitch.checked)
                        {
                            autoScaleYAxisEnabled()
                        }
                    }
                }

                Text
                {
                    id: refAutoScaleTimeTitle
                    text: qmltextAutoScaleTimeAxis
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id: autoScaleTimeRefAxisSwitch
                    checked: true /*GraphSettings.AutoScaleTimeAxis*/
                    anchors.left: enableRefGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.AutoScaleTimeAxis = autoScaleTimeRefAxisSwitch.checked

                        if(autoScaleTimeRefAxisSwitch.checked)
                        {
                            autoScaleTimeAxisEnabled()
                        }
                    }
                }


                Text
                {
                    id: refTWHLineTitle
                    text: qmltextTWHLine
                    font.pixelSize: fontSize
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id: refTWHLineSwitch
                    checked: GraphSettings.TWHLineDisplay
                    anchors.left: enableRefGraphTitle.left
                    anchors.leftMargin: Math.round(8 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(18 * Style.scaleHint)
                    onCheckedChanged:
                    {
                        GraphSettings.TWHLineDisplay = refTWHLineSwitch.checked
                    }
                }
            }

            Text
            {
                id: autoScaleYRefAxisSwitchLink
                anchors.left: refConfigRect.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                anchors.top: refConfigRect.top
                anchors.topMargin: Math.round(100 * Style.scaleHint)
                text: qmltextSetValues
                font.pixelSize: Math.round(12 * Style.scaleHint)
                font.family: Style.regular.name
                color: autoScaleYRefAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor

                Rectangle
                {
                    id: refLink
                    anchors.top: autoScaleYRefAxisSwitchLink.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    height: Math.round(2 * Style.scaleHint)
                    width: autoScaleYRefAxisSwitchLink.width
                    color: autoScaleYRefAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor
                }

                MouseArea
                {
                    id: autoScaleYRefAxisSwitchLinkMa
                    enabled: (! autoScaleYRefAxisSwitch.checked)
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        mainWindow.showMinMaxNumpad(qmltextYScaleSettings, true, firstYAxisSelectedEnum, secondYAxisSelectedEnum)
                    }
                }
            }

            Text
            {
                id: autoScaleTimeRefAxisSwitchLink
                anchors.left: refConfigRect.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                anchors.top: refConfigRect.top
                anchors.topMargin: Math.round(145 * Style.scaleHint)
                text: qmltextSetValues
                font.pixelSize: Math.round(12 * Style.scaleHint)
                font.family: Style.regular.name
                color: autoScaleTimeRefAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor

                Rectangle
                {
                    id: refLink2
                    anchors.top: autoScaleTimeRefAxisSwitchLink.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    height: Math.round(2 * Style.scaleHint)
                    width: autoScaleTimeRefAxisSwitchLink.width
                    color: autoScaleTimeRefAxisSwitch.checked ? Style.blackFontColor : Style.blueFontColor
                }

                MouseArea
                {
                    id: autoScaleTimeRefAxisSwitchLinkMa
                    enabled: (! autoScaleTimeRefAxisSwitch.checked)
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        mainWindow.showMinMaxNumpad(qmltextTimeScaleSettings, false, "NA", "NA")
                    }
                }
            }
        }
    }
}


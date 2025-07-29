/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    NormalGraphWindow.qml file displays graph data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/10/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
Item {
    property double timedata: 1
    property string qmltextCycleNumber: qsTr("Cycle Number")
    property string qmltextSaveAsGolden: qsTr("Save As A Golden Graph")

    property int firstAxisDisplayValue: GraphAxisEnum.AMP_IDX
    property int secondAxisDisplayValue: GraphAxisEnum.AMP_IDX

    property var qmlTextArray: [qmltextCycleNumber, qmltextSaveAsGolden]

    function firstLine(index)
    {
        chartView.isAmpLeftAxisVisible          = false
        chartView.isPowerLeftAxisVisible        = false
        chartView.isFreqLeftAxisVisible         = false
        chartView.isPhaseLeftAxisVisible        = false
        chartView.isCurrentLeftAxisVisible      = false
        chartView.isEnergyLeftAxisVisible       = false
        chartView.isForceLeftAxisVisible        = false
        chartView.isAbsoluteDistLeftAxisVisible = false
        chartView.isCollapseDistLeftAxisVisible = false

        switch(index)
        {
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpLeftAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerLeftAxisVisible        = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqLeftAxisVisible         = true
            break
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseLeftAxisVisible        = true
            break;
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentLeftAxisVisible      = true
            break
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyLeftAxisVisible       = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceLeftAxisVisible        = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistLeftAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistLeftAxisVisible = true
            break
        default:
            break
        }

        switch(secondAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpLeftAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerLeftAxisVisible        = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqLeftAxisVisible         = true
            break
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseLeftAxisVisible        = true
            break;
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentLeftAxisVisible      = true
            break
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyLeftAxisVisible       = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceLeftAxisVisible        = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistLeftAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistLeftAxisVisible = true
            break
        default:
            break
        }

        rectright.firstRectColor = AxisDefine.getAxisColor(index)
        rectright.secondRectColor = AxisDefine.getAxisColor(secondAxisDisplayValue)
        firstAxisDisplayValue = index
    }

    function secondLine(index)
    {
        chartView.isAmpLeftAxisVisible          = false
        chartView.isPowerLeftAxisVisible        = false
        chartView.isFreqLeftAxisVisible         = false
        chartView.isPhaseLeftAxisVisible        = false
        chartView.isCurrentLeftAxisVisible      = false
        chartView.isEnergyLeftAxisVisible       = false
        chartView.isForceLeftAxisVisible        = false
        chartView.isAbsoluteDistLeftAxisVisible = false
        chartView.isCollapseDistLeftAxisVisible = false

        switch(index)
        {
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpLeftAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerLeftAxisVisible        = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqLeftAxisVisible         = true
            break
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseLeftAxisVisible        = true
            break;
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentLeftAxisVisible      = true
            break
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyLeftAxisVisible       = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceLeftAxisVisible        = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistLeftAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistLeftAxisVisible = true
            break
        default:
            break
        }

        switch(firstAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:
            chartView.isAmpLeftAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            chartView.isPowerLeftAxisVisible        = true
            break
        case GraphAxisEnum.FREQ_IDX:
            chartView.isFreqLeftAxisVisible         = true
            break
        case GraphAxisEnum.PHASE_IDX:
            chartView.isPhaseLeftAxisVisible        = true
            break;
        case GraphAxisEnum.CURRENT_IDX:
            chartView.isCurrentLeftAxisVisible      = true
            break
        case GraphAxisEnum.ENERGY_IDX:
            chartView.isEnergyLeftAxisVisible       = true
            break
        case GraphAxisEnum.FORCE_IDX:
            chartView.isForceLeftAxisVisible        = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            chartView.isAbsoluteDistLeftAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            chartView.isCollapseDistLeftAxisVisible = true
            break
        default:
            break
        }

        rectright.secondRectColor = AxisDefine.getAxisColor(index)
        rectright.firstRectColor = AxisDefine.getAxisColor(firstAxisDisplayValue)
        secondAxisDisplayValue = index
    }

    function getGraphEnableValue(getVal)
    {
        chartView.isGraphEnable = getVal
    }

    function getTimeValue(getVal)
    {
        rectright.timeValue = getVal
    }

    QtObject
    {
        id: textEnum
        readonly property int cycleNumberIdx:       0
        readonly property int saveAsGoldenIdx:      1
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW, qmlTextArray)
        qmltextCycleNumber = qmlTextArray[textEnum.cycleNumberIdx]
        qmltextSaveAsGolden = qmlTextArray[textEnum.saveAsGoldenIdx]
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
        weldGraphLoadTimer.start()
        rectright.firstAxisChanged.connect(firstLine)
        rectright.secondAxisChanged.connect(secondLine)
        rectright.isGraphEnableChanged.connect(getGraphEnableValue)
        chartView.timeValueUpdated.connect(getTimeValue)
        updateLanguage()
    }

    BransonPrimaryButton
    {
        id: goldenGraphButton
        implicitWidth: Math.round(180 * Style.scaleHint)
        implicitHeight: Math.round(25 * Style.scaleHint)
        fontSize: Math.round(Style.style0  * Style.scaleHint)
        anchors.top: parent.top
        anchors.right: parent.right
        text: qmltextSaveAsGolden
        font.family: Style.regular.name
        buttonColor: Style.blueFontColor
        textColor: "#FFFFFF"
        onClicked:
        {
        }
    }

    CycleDetailsList
    {
        id: cycleDetailsList
        anchors.top:parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.left: parent.left
        width: Math.round(150 * Style.scaleHint)
        height: parent.height-(25 * Style.scaleHint)
    }

    Rectangle
    {
        id: graphFrame
        width: Math.round(575 * Style.scaleHint)
        height: parent.height-(25 * Style.scaleHint)
        anchors.top:parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.left: cycleDetailsList.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.activeFrameBorderColor
        Rectangle
        {
            id: chartViewHeader
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: Math.round(50 * Style.scaleHint)
            color: "transparent"
            Row
            {
                id: btnArray
                anchors.left: parent.left
                anchors.leftMargin: Math.round(6 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(92 * Style.scaleHint)
                height: Math.round(45 * Style.scaleHint)
                spacing: Math.round(2 * Style.scaleHint)
                Rectangle
                {
                    id: graphBtn
                    width: parent.width/2
                    height: parent.height
                    border.width: 1
                    border.color: Style.frameBorderColor
                    radius: 2
                    Image {
                        id: graphImage
                        source: "qrc:/Images/Graph.svg"
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        anchors.centerIn: parent
                        sourceSize.width: graphImage.width
                        sourceSize.height: graphImage.height
                        smooth: true
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            graphBtn.border.color="#6699cc"
                            recordsBtn.border.color="#9fa1a4"
                        }
                    }
                }

                Rectangle
                {
                    id: recordsBtn
                    width: parent.width/2
                    height: parent.height
                    border.width: 1
                    border.color: Style.frameBorderColor
                    radius: 2
                    Image {
                        id: recordsImage
                        source: "qrc:/Images/Table.svg"
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        anchors.centerIn: parent
                        sourceSize.width: recordsImage.width
                        sourceSize.height: recordsImage.height
                        smooth: true
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            recordsBtn.border.color="#6699cc"
                            graphBtn.border.color="#9fa1a4"
                        }
                    }
                }
            }

            Text {
                id: cyclenumber
                anchors.left: btnArray.right
                anchors.leftMargin: Math.round(12 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmltextCycleNumber + ":"
                font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            Text {
                id: cyclenum
                anchors.left: cyclenumber.right
                anchors.leftMargin: Math.round(2 * Style.scaleHint)
                anchors.verticalCenter: cyclenumber.verticalCenter
                text: qsTr("178")
                font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }

            Image
            {
                id: fullBtn
                width: Math.round(30 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: Math.round(8 * Style.scaleHint)
                source: "qrc:/Images/Maximize.svg"
                sourceSize.width: fullBtn.width
                sourceSize.height: fullBtn.height
                smooth: true
            }
            MouseArea
            {
                id: fullBtnClickArea
                width: parent.height
                height: parent.height
                anchors.centerIn: fullBtn
                onClicked:
                {
                    mainWindow.showFullScreenChart()
                }
            }

        }

        BransonChartView
        {
            id: chartView
            width: parent.width
            anchors.left: chartViewHeader.left
            anchors.top: chartViewHeader.bottom
            anchors.bottom: parent.bottom
            timemax: timedata
        }
    }

    BransonChartRightSetting
    {
        id: rectright
        anchors.top: graphFrame.top
        height: graphFrame.height
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.right: parent.right
    }

    Timer
    {
        id: weldGraphLoadTimer
        interval: 3000
        repeat: true
        onTriggered:
        {
            chartView.clearGraph()
            WeldGraphObj.clearGraph()
            WeldGraphObj.generateRandomNumber()
            chartView.plotGraph()
        }
    }

}

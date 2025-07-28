/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanGraphWindow.qml file displays horn test graph data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/03/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import "./../Common_Logic"

Item
{
    property string qmlEmptyText: "No Data To Display..!"

    property int firstYAxisDisplayValue: GraphAxisEnum.AMP_IDX
    property int secondYAxisDisplayValue: GraphAxisEnum.CURRENT_IDX
    property int thirdYAxisDisplayValue: GraphAxisEnum.PHASE_IDX

    property var qmlTextArray: [qmlEmptyText]
    property int cycleCountRequested
    property int imageSize: Math.round(20 * Style.scaleHint)

    signal initiateScanGraphSignatureDisplay()
    signal updateGraphInitiated()
    signal updateGraphAvailable()

    property int val

    function getFreqValue(getVal)
    {
        rectRight.freqValue = getVal
    }

    function getYAxisValues(ampVal, phaseVal, currentVal)
    {
        val = ampVal

        if(val < (-200000))
        {
            val = 0
        }

        rectRight.firstYAxisValueText = val

        val = currentVal

        if(val < (-200000))
        {
            val = 0
        }

        rectRight.secondYAxisValueText = val

        val = phaseVal

        if(val < (-200000))
        {
            val = 0
        }

        rectRight.thirdYAxisValueText = val
    }

    QtObject
    {
        id: textEnum
        readonly property int qmlEmptyTextIdx                  : 0
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SCAN_GRAPH_VIEW, qmlTextArray)
        qmlEmptyText = qmlTextArray[textEnum.qmlEmptyTextIdx]
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        /*Change Target*/
        target: ScanCycleDetailsListModel
        function onInitiateScanGraphSignatureDisplay(getCycleCount, value)
        {
            /*chartView.clearGraph()
            ScanGraphData.clearGraph()*/
            ScanGraphData.initiateScanGraphSignature(getCycleCount, value)
            cycleCountRequested = getCycleCount
            scanGraphLoadTimer.start()
        }
    }

    Connections
    {
        target: ScanGraphData
        function onUpdateGraphInitiated()
        {
            loadingPage.visible = true
            emptySignatureIndicator.visible = false
        }

        function onUpdateGraphAvailable()
        {
            chartView.plotGraph()
            loadingPage.visible = false
            ScanCycleDetailsListModel.ScanRunStatus = false

            if(ScanGraphData.isEmptyScanSignatureReceived())
            {
                emptySignatureIndicator.visible = true
            }

            else
            {
                emptySignatureIndicator.visible = false
            }
        }
    }

    Component.onCompleted:
    {
        /*To reinitiate scan signature read request*/
        ScanCycleDetailsListModel.isScreenReNavigated(true)

        chartView.freqValueUpdated.connect(getFreqValue)
        chartView.yAxisValueUpdated.connect(getYAxisValues)
        updateLanguage()
    }

    ScanCycleDetailsList
    {
        id: scanCycleDetailsList
        anchors.top: parent.top
        anchors.left: parent.left
        width: Math.round(125 * Style.scaleHint)
        height: parent.height
    }

    Rectangle
    {
        id: graphFrame
        width: Math.round(480 * Style.scaleHint)
        height: parent.height
        anchors.top: parent.top
        anchors.left: scanCycleDetailsList.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.activeFrameBorderColor

        BransonScanChartView
        {
            id: chartView
            visible: ((! loadingPage.visible) && (! emptySignatureIndicator.visible))
            width: parent.width
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        Rectangle
        {
            id: loadingPage
            visible: false
            anchors.fill: parent
            opacity: 0.5
            color: "#000000"

            Image
            {
                id: recipeLoadingIcon
                visible: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Images/Loading.png"
                height: imageSize * 5
                width: imageSize * 5
                fillMode: Image.PreserveAspectFit
                sourceSize.width: recipeLoadingIcon.width
                sourceSize.height: recipeLoadingIcon.height
                smooth: true
            }

            RotationAnimator
            {
                target: recipeLoadingIcon
                from: 0
                to: 360
                duration: 1000
                running: true
                loops: Animation.Infinite
            }

            MouseArea
            {
                anchors.fill: parent
                propagateComposedEvents: false
            }
        }

        Rectangle
        {
            id: emptySignatureIndicator
            visible: false
            anchors.fill: parent
            opacity: 0.5
            color: "#FFFFFF"

            Text
            {
                id: emptySignatureText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qmlEmptyText
                font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                font.family: Style.regular.name
                color: "#FF0000"
            }
        }
    }

    ScanGraphRightSettings
    {
        id: rectRight
        anchors.top: parent.top
        height: parent.height
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.right: parent.right
    }

    Timer
    {
        id: scanGraphLoadTimer
        interval: 500
        repeat: true
        onTriggered:
        {
            chartView.plotGraph()
            ScanGraphData.initiateScanGraphSignature(cycleCountRequested, false)
        }
    }
}

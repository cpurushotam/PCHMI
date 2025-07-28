/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    TestGraphWindow.qml file displays horn test graph data.

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

    property double timeMinValue: TestGraphSettings.TimeAxisMinValue
    property double timeMaxValue: TestGraphSettings.TimeAxisMaxValue

    property int firstYAxisDisplayValue: GraphAxisEnum.AMP_IDX
    property int secondYAxisDisplayValue: GraphAxisEnum.POWER_IDX

    property var qmlTextArray: [qmlEmptyText]
    property int imageSize: Math.round(20 * Style.scaleHint)

    signal initiateTestGraphSignatureDisplay()
    signal updateGraphInitiated()
    signal updateGraphAvailable()

    property int val

    function yAxesUpdate(firstYAxisIndex, secondYAxisIndex)
    {
        firstYAxisDisplayValue = firstYAxisIndex
        secondYAxisDisplayValue = secondYAxisIndex

        chartView.isAmpLeftAxisVisible          = false
        chartView.isPowerLeftAxisVisible        = false
        chartView.isFreqLeftAxisVisible         = false
        chartView.isPhaseLeftAxisVisible        = false
        chartView.isCurrentLeftAxisVisible      = false

        switch(firstYAxisIndex)
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

        default:
            break
        }

        switch(secondYAxisIndex)
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

        default:
            break
        }

        rectRight.firstRectColor = AxisDefine.getAxisColor(firstYAxisIndex)
        rectRight.secondRectColor = AxisDefine.getAxisColor(secondYAxisIndex)
    }

    function getTimeValue(getVal)
    {
        rectRight.timeValue = getVal
    }

    function getYAxisValues(ampVal, powerVal, freqVal, phaseVal, currentVal)
    {
        switch(firstYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:

            val = phaseVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        default:
            break
        }

        switch(secondYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:

            val = phaseVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        default:
            break
        }
    }

    QtObject
    {
        id: textEnum
        readonly property int qmlEmptyTextIdx                  : 0
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_TEST_GRAPH_VIEW, qmlTextArray)
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
        target: TestData
        function onInitiateTestGraphSignatureDisplay(value)
        {
            /*chartView.clearGraph()
            TestGraphData.clearGraph()*/
            TestGraphData.initiateTestGraphSignature(value)
            testGraphLoadTimer.start()
        }
    }

    Connections
    {
        target: TestGraphData
        function onUpdateGraphInitiated()
        {
             loadingPage.visible = true
            emptySignatureIndicator.visible = false
        }

        function onUpdateGraphAvailable()
        {
            chartView.plotGraph()
            loadingPage.visible = false

            if(TestGraphData.isEmptyTestSignatureReceived())
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
        /*To reinitiate test signature read request*/
        TestGraphData.isScreenReNavigated(true)

        rectRight.axisChanged.connect(yAxesUpdate)
        chartView.timeValueUpdated.connect(getTimeValue)
        chartView.yAxisValueUpdated.connect(getYAxisValues)
        updateLanguage()
    }

    Rectangle
    {
        id: graphFrame
        width: Math.round(550 * Style.scaleHint)
        height: Math.round(210 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        border.color: "#707070"

        BransonTestChartView
        {
            id: chartView
            visible: ((! loadingPage.visible) && (! emptySignatureIndicator.visible))
            width: parent.width
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            timeMin: timeMinValue
            timeMax: timeMaxValue
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

    TestGraphRightSettings
    {
        id: rectRight
        anchors.top: graphFrame.top
        height: graphFrame.height
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.right: parent.right
    }

    Timer
    {
        id: testGraphLoadTimer
        interval: 500
        repeat: true
        onTriggered:
        {
            chartView.plotGraph()
            TestGraphData.initiateTestGraphSignature(false)
        }
    }
}

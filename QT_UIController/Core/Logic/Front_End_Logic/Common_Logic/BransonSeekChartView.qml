/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonChartView.qml displays the line series graph.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/10/2023 - Initial version.
***************************************************************************/
import QtQuick 2.0
import QtCharts 2.15
import QtQuick.Controls 2.2
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Item {
    id: seekGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: isNormalScreen === true ? Math.round(Style.style1 * Style.scaleHint) : Math.round(Style.style4 * Style.scaleHint)

    property double timeMin: 1
    property double timeMax: 1

    readonly property string ampLeftPlotName:               "ampLeftPlot"
    readonly property string currentLeftPlotName:           "currentLeftPlot"
    readonly property string powerLeftPlotName:             "powerLeftPlot"
    readonly property string phaseLeftPlotName:             "phaseLeftPlot"
    readonly property string freqLeftPlotName:              "freqLeftPlot"

    readonly property string qmltextPhase0Plot:             "phase0Plot"
    readonly property string qmltextSecUnit:                mainWindow.qmltextTimeUnit

    /*Whether the axis controls the coordinate display*/
    property bool isGraphEnable                   : true
    property bool isAmpLeftAxisVisible            : true
    property bool isPowerLeftAxisVisible          : false
    property bool isFreqLeftAxisVisible           : false
    property bool isPhaseLeftAxisVisible          : false
    property bool isCurrentLeftAxisVisible        : false

    property double timePoint
    property double ampPoint
    property double powerPoint
    property double freqPoint
    property double phasePoint
    property double currPoint

    property double ampMinVal               : SeekGraphSettings.AmpAxisMinValue
    property double ampMaxVal               : SeekGraphSettings.AmpAxisMaxValue

    property double powerMinVal             : SeekGraphSettings.PowerAxisMinValue
    property double powerMaxVal             : SeekGraphSettings.PowerAxisMaxValue

    property double freqMinVal              : SeekGraphSettings.FreqAxisMinValue
    property double freqMaxVal              : SeekGraphSettings.FreqAxisMaxValue

    property double phaseMinVal             : SeekGraphSettings.PhaseAxisMinValue
    property double phaseMaxVal             : SeekGraphSettings.PhaseAxisMaxValue

    property double currentMinVal           : SeekGraphSettings.CurrentAxisMinValue
    property double currentMaxVal           : SeekGraphSettings.CurrentAxisMaxValue

    property int toolTipTimeoutValue: 5000
    property int qmlTextTickCount_X_Axis: 5
    property int qmlTextTickCount_Y_Axis: 5

    signal timeValueUpdated(var timeVal)
    signal yAxisValueUpdated(var ampVal,var powerVal, var freqVal, var phaseVal, var currentVal)

    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    Component.onCompleted:
    {
    }

    /**
    *@breif: Rounding of axis values for proper representation
    **/
    function roundAxisValues(axisMaximumVal, axisMinimumVal)
    {
        var ind = 0 ;
        var tmpValues;
        var reminder;
        var retVal = 0 ;

        tmpValues = axisMaximumVal - axisMinimumVal;
        reminder = (tmpValues % 10)

        if(reminder !== 0 )
        {
            retVal = axisMaximumVal + (10 - reminder);
        }
        else
        {
            retVal = axisMaximumVal ;
        }
        return retVal ;
    }

    /**
    *@breif: Plots the graph
    **/
    function plotGraph()
    {
        clearGraph()

        if(isAmpLeftAxisVisible && isGraphEnable)
            SeekGraphData.appendSamples(graphChartView.series(ampLeftPlotName), GraphAxisEnum.AMP_IDX);
        if(isPowerLeftAxisVisible && isGraphEnable)
            SeekGraphData.appendSamples(graphChartView.series(powerLeftPlotName), GraphAxisEnum.POWER_IDX);
        if(isFreqLeftAxisVisible && isGraphEnable)
            SeekGraphData.appendSamples(graphChartView.series(freqLeftPlotName), GraphAxisEnum.FREQ_IDX);
        if(isPhaseLeftAxisVisible && isGraphEnable)
            SeekGraphData.appendSamples(graphChartView.series(phaseLeftPlotName), GraphAxisEnum.PHASE_IDX);
        if(isCurrentLeftAxisVisible && isGraphEnable)
            SeekGraphData.appendSamples(graphChartView.series(currentLeftPlotName), GraphAxisEnum.CURRENT_IDX);

        /* Update the Min and Max values */
       /* var axisMinValues = SeekGraphData.getAxisMinParameters();
        var axisMaxValues = SeekGraphData.getAxisMaxParameters();
        timeAxis.min                = timeMin;
        ampLeftAxis.min             = 0
        powerLeftAxis.min           = Math.max(0, axisMinValues[GraphAxisEnum.POWER_IDX]);
        freqLeftAxis.min            = axisMinValues[GraphAxisEnum.FREQ_IDX] - 100;
        phaseLeftAxis.min           = -180
        currentLeftAxis.min         = 0
        energyLeftAxis.min          = Math.max(0, (axisMinValues[GraphAxisEnum.ENERGY_IDX] - 2));
        forceLeftAxis.min           = Math.max(0, (axisMinValues[GraphAxisEnum.FORCE_IDX] - 2));
        absoluteDistLeftAxis.min    = Math.max(0, (axisMinValues[GraphAxisEnum.ABSOLUTEDIST_IDX] - 2));
        collapseDistLeftAxis.min    = axisMinValues[GraphAxisEnum.COLLAPSEDIST_IDX] - 1;

        timeAxis.max                = timeMax;
        ampLeftAxis.max             = 120
        powerLeftAxis.max           = axisMaxValues[GraphAxisEnum.POWER_IDX] + 1;
        freqLeftAxis.max            = axisMaxValues[GraphAxisEnum.FREQ_IDX] + 100;
        phaseLeftAxis.max           = 180
        currentLeftAxis.max         = 120
        energyLeftAxis.max          = axisMaxValues[GraphAxisEnum.ENERGY_IDX] + 1;
        forceLeftAxis.max           = axisMaxValues[GraphAxisEnum.FORCE_IDX] + 1;
        absoluteDistLeftAxis.max    = axisMaxValues[GraphAxisEnum.ABSOLUTEDIST_IDX] + 1;
        collapseDistLeftAxis.max    = axisMaxValues[GraphAxisEnum.COLLAPSEDIST_IDX] + 1;

        /* Rounding of axis values for proper representation */
        /*ampLeftAxis.max             = roundAxisValues(ampLeftAxis.max, ampLeftAxis.min);
        powerLeftAxis.max           = roundAxisValues(powerLeftAxis.max, powerLeftAxis.min);
        freqLeftAxis.max            = roundAxisValues(freqLeftAxis.max, freqLeftAxis.min);
        phaseLeftAxis.max           = roundAxisValues(phaseLeftAxis.max, phaseLeftAxis.min);
        currentLeftAxis.max         = roundAxisValues(currentLeftAxis.max, currentLeftAxis.min);
        energyLeftAxis.max          = roundAxisValues(energyLeftAxis.max, energyLeftAxis.min);
        forceLeftAxis.max           = roundAxisValues(forceLeftAxis.max, forceLeftAxis.min);
        absoluteDistLeftAxis.max    = roundAxisValues(absoluteDistLeftAxis.max, absoluteDistLeftAxis.min);
        collapseDistLeftAxis.max    = roundAxisValues(collapseDistLeftAxis.max, collapseDistLeftAxis.min);*/

        yAxisValueUpdated(ampPoint, powerPoint, freqPoint, phasePoint, currPoint)

    }

    function clearGraph()
    {
        timeAxis.min = timeMin;
        timeAxis.max = timeMax;
        ampLeftAxisPlot.clear()
        powerLeftAxisPlot.clear()
        freqLeftAxisPlot.clear()
        phaseLeftAxisPlot.clear()
        currentLeftAxisPlot.clear()
    }

    Rectangle
    {
        id: graphFrame
        anchors.fill: parent
        color: "transparent"
        ScrollView
        {
            id:cotaingraphChartView
            width: parent.width
            height: parent.height
            clip: true
            ChartView
            {
                id: graphChartView
                legend.visible: false
                margins.top: Math.round(25  * Style.scaleHint)
                margins.right: 0
                margins.left: 0
                margins.bottom: 0
                property real plotStartPointY: plotArea.y
                property real plotStartPointX: plotArea.x
                property real deltaX: plotArea.width / (timeAxis.max - timeAxis.min)
                property real myWidth: 1
                width: parent.width
                height: parent.height
                transformOrigin: Item.Center
                PinchArea
                {
                    id:pinchzoom
                    enabled: flagDragDrop
                    anchors.fill: parent
                    pinch.target: graphChartView
                    pinch.maximumScale: 10
                    pinch.minimumScale: 1
                    pinch.dragAxis: Pinch.XAndYAxis
                    MouseArea
                    {
                        id:mousezoom
                        enabled: flagDragDrop
                        anchors.fill: parent
                        drag.target: graphChartView
                        drag.axis:Drag.XAndYAxis
                        onMouseXChanged:
                        {
                            var xfirst  =   graphChartView.width/3
                            var xsecond =   xfirst*2
                            var xthird  =   xfirst*3

                            var yfirst  =   graphChartView.height/3
                            var ysecond =   yfirst*2
                            var ythird  =   yfirst*3
                            if(graphChartView.scale===1)
                            {
                                if((mouseX>0 && mouseX<xfirst)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.TopLeft
                                }
                                else if((mouseX>0 && mouseX<xfirst)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Left
                                }
                                else if((mouseX>0 && mouseX<xfirst)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.BottomLeft
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.Top
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Center
                                }
                                else if((mouseX>xfirst && mouseX<xsecond)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.Bottom
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>0 && mouseY<yfirst))
                                {
                                    graphChartView.transformOrigin=Item.TopRight
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>yfirst && mouseY<ysecond))
                                {
                                    graphChartView.transformOrigin=Item.Right
                                }
                                else if((mouseX>xsecond && mouseX<xthird)&&(mouseY>ysecond && mouseY<ythird))
                                {
                                    graphChartView.transformOrigin=Item.BottomRight
                                }
                            }
                        }

                        onDoubleClicked:
                        {
                            if(graphChartView.x!==0 || graphChartView.y!==0)
                            {
                                graphChartView.x = 0
                                graphChartView.y = 0
                                graphChartView.scale=1
                                transformOrigin: Item.Center
                            }
                            else if(graphChartView.x === 0 && graphChartView.y === 0)
                            {
                                if(graphChartView.scale === 1)
                                {
                                    graphChartView.scale = 2
                                }
                                else
                                {
                                    graphChartView.x = 0
                                    graphChartView.y = 0
                                    graphChartView.scale = 1
                                    transformOrigin: Item.Center
                                }
                            }
                        }
                    }
                }

                ValueAxis
                {
                    id: timeAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.TIME_IDX)
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.TIME_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.TIME_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.TIME_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.3f"
                    min: timeMin
                    max: timeMax
                    tickCount: qmlTextTickCount_X_Axis
                }

                ValueAxis
                {
                    id: ampLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    visible: isAmpLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.AMP_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.AMP_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: ampMinVal //120
                    max: ampMaxVal
                    tickCount: qmlTextTickCount_Y_Axis
                }

                ValueAxis
                {
                    id: powerLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: isPowerLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.POWER_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.POWER_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: powerMinVal
                    max: powerMaxVal//10
                    tickCount: qmlTextTickCount_Y_Axis
                }

                ValueAxis
                {
                    id : freqLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: isFreqLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FREQ_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.FREQ_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    min: freqMinVal// 19450
                    max: freqMaxVal//20450
                    tickCount: qmlTextTickCount_Y_Axis
                    labelFormat: "%.0f"
                }

                ValueAxis
                {
                    id: phaseLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: isPhaseLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.PHASE_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.PHASE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    min: phaseMinVal//-180
                    max: phaseMaxVal// 180
                    tickCount: qmlTextTickCount_Y_Axis
                    labelFormat: "%.0f"
                }

                ValueAxis
                {
                    id: currentLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    visible: isCurrentLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.CURRENT_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.CURRENT_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: currentMinVal// 0
                    max: currentMaxVal// 120
                    tickCount: qmlTextTickCount_Y_Axis
                }                

                LineSeries
                {
                    id: ampLeftAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                    name: ampLeftPlotName
                    axisX: timeAxis
                    axisY: ampLeftAxis
                    visible: (isAmpLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Amplitude: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.AMP_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = ampLeftAxisPlot.at(0);
                        for(var i = 1; i < ampLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > ampLeftAxisPlot.at(i).x)
                                minX = ampLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = ampLeftAxisPlot.at(0);
                        for(var i = 1; i < ampLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < ampLeftAxisPlot.at(i).x)
                                maxX = ampLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < ampLeftAxisPlot.count; ++i)
                        {
                            if (xValue == ampLeftAxisPlot.at(i).x)
                            {
                                return ampLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < ampLeftAxisPlot.at(i).x && ampLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = ampLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > ampLeftAxisPlot.at(i).x && ampLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = ampLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: powerLeftAxisPlot
                    width: graphChartView.myWidth
                    name: powerLeftPlotName
                    axisX: timeAxis
                    axisY: powerLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: (isPowerLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Power: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.POWER_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = powerLeftAxisPlot.at(0);
                        for(var i = 1; i < powerLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > powerLeftAxisPlot.at(i).x)
                                minX = powerLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = powerLeftAxisPlot.at(0);
                        for(var i = 1; i < powerLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < powerLeftAxisPlot.at(i).x)
                                maxX = powerLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < powerLeftAxisPlot.count; ++i)
                        {
                            if (xValue == powerLeftAxisPlot.at(i).x)
                            {
                                return powerLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < powerLeftAxisPlot.at(i).x && powerLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = powerLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > powerLeftAxisPlot.at(i).x && powerLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = powerLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: freqLeftAxisPlot
                    width: graphChartView.myWidth
                    name: freqLeftPlotName
                    axisX: timeAxis
                    axisY: freqLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: (isFreqLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Frequency: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.FREQ_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = freqLeftAxisPlot.at(0);
                        for(var i = 1; i < freqLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > freqLeftAxisPlot.at(i).x)
                                minX = freqLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = freqLeftAxisPlot.at(0);
                        for(var i = 1; i < freqLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < freqLeftAxisPlot.at(i).x)
                                maxX = freqLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < freqLeftAxisPlot.count; ++i)
                        {
                            if (xValue == freqLeftAxisPlot.at(i).x)
                            {
                                return freqLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < freqLeftAxisPlot.at(i).x && freqLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = freqLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > freqLeftAxisPlot.at(i).x && freqLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = freqLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: phaseLeftAxisPlot
                    width: graphChartView.myWidth
                    name: phaseLeftPlotName
                    axisX: timeAxis
                    axisY: phaseLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: (isPhaseLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Phase: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.PHASE_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = phaseLeftAxisPlot.at(0);
                        for(var i = 1; i < phaseLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > phaseLeftAxisPlot.at(i).x)
                                minX = phaseLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = phaseLeftAxisPlot.at(0);
                        for(var i = 1; i < phaseLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < phaseLeftAxisPlot.at(i).x)
                                maxX = phaseLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < phaseLeftAxisPlot.count; ++i)
                        {
                            if (xValue == phaseLeftAxisPlot.at(i).x)
                            {
                                return phaseLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < phaseLeftAxisPlot.at(i).x && phaseLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = phaseLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > phaseLeftAxisPlot.at(i).x && phaseLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = phaseLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: currentLeftAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                    name: currentLeftPlotName
                    axisX: timeAxis
                    axisY: currentLeftAxis
                    visible: (isCurrentLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Current: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.CURRENT_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = currentLeftAxisPlot.at(0);
                        for(var i = 1; i < currentLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > currentLeftAxisPlot.at(i).x)
                                minX = currentLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = currentLeftAxisPlot.at(0);
                        for(var i = 1; i < currentLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < currentLeftAxisPlot.at(i).x)
                                maxX = currentLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < currentLeftAxisPlot.count; ++i)
                        {
                            if (xValue == currentLeftAxisPlot.at(i).x)
                            {
                                return currentLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < currentLeftAxisPlot.at(i).x && currentLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = currentLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > currentLeftAxisPlot.at(i).x && currentLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = currentLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }                

                Rectangle
                {
                    id: chartViewArea
                    x: graphChartView.plotArea.x
                    y: graphChartView.plotArea.y
                    height : graphNavigator.height + graphNavigatorImage.height + graphNavigatorLabel.height
                    width : graphChartView.plotArea.width
                    visible: false
                }

                ToolTip
                {
                    id: toolTip
                    visible: false
                    width : Math.round(90 * Style.scaleHint)
                    height : Math.round(25 * Style.scaleHint)

                    Rectangle
                    {
                        id: colorIndicator
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(5 * Style.scaleHint)
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(2 * Style.scaleHint)
                        width : Math.round(10 * Style.scaleHint)
                        height : Math.round(10 * Style.scaleHint)
                        radius: width/2
                        color: "#000000"
                    }

                    Text
                    {
                        id: graphHeader
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(6 * Style.scaleHint)
                        anchors.left: colorIndicator.right
                        anchors.leftMargin: Math.round(2 * Style.scaleHint)
                        color: "#000000"
                    }

                    background: Rectangle
                    {
                        id: toolTipBackground
                        width : Math.round(75 * Style.scaleHint)
                        height : Math.round(25 * Style.scaleHint)
                        radius : Math.round(5 * Style.scaleHint)
                        color : "#FFFFFF"
                        border.color: "#000000"
                    }
                }

                Rectangle
                {
                    id: graphSlider
                    property int raiseHeight: Math.round(15 * Style.scaleHint)
                    property string custColor : "#007BFF"
                    property int assetSize:20
                    property real xAxisVal: timeAxis.min
                    property string timeLabel: timeAxis.min.toFixed(3)
                    property double timeLabelText: timeAxis.min.toFixed(3)
                    property bool timeDecimalValFlag: true
                    y: graphChartView.plotArea.y
                    x: graphChartView.plotArea.x + (xAxisVal - timeAxis.min) * graphChartView.deltaX - width / 2
                    width : graphNavigatorLabel.width
                    height : graphChartView.plotArea.height
                    color: "transparent"
                    Rectangle
                    {
                        id: graphNavigator
                        height: graphChartView.plotArea.height - graphNavigatorImage.height/2
                        width: 2
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: parent.custColor
                    }

                    Rectangle
                    {
                        id: graphNavigatorImage
                        height: parent.assetSize
                        width : parent.assetSize
                        radius: width / 2
                        color: parent.custColor
                        anchors.bottom: graphNavigator.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        MouseArea
                        {
                            id: graphNavigatorMouseArea
                            property point posInChartArea
                            property int indexClosest1:0
                            anchors.fill: parent
                            cursorShape: Qt.ToolTip
                            hoverEnabled: false
                            onPositionChanged:
                            {
                                /* Drag position of the slider */
                                var point = mapToItem(chartViewArea , mouse.x , mouse.y);
                                var retVal ;
                                var timeVal;
                                var tmpPoint;

                                if(point.x < 0 || point.x > graphChartView.plotArea.width)
                                {
                                    if(point.x < 0)
                                    {
                                        timeVal = timeAxis.min;
                                        graphSlider.xAxisVal = timeAxis.min;
                                    }
                                    else
                                    {
                                        posInChartArea.x = graphChartView.plotArea.width ;
                                        timeVal = timeAxis.max;
                                        graphSlider.xAxisVal = timeAxis.max
                                    }
                                }
                                else
                                {
                                    posInChartArea.x = point.x;
                                    posInChartArea.y = point.y;
                                    timeVal = posInChartArea.x / graphChartView.deltaX + timeAxis.min;
                                    graphSlider.xAxisVal = posInChartArea.x / graphChartView.deltaX + timeAxis.min ;
                                }

                                /* calculating the points in the graph */
                                graphSlider.timeLabel = timeVal.toFixed(3)
                                graphSlider.timeLabelText = timeVal.toFixed(3)
                                timeValueUpdated(graphSlider.timeLabel)
                                //retVal = getClosestPoints(timeVal.toFixed(5));
                                if(-1 === retVal)
                                {
                                    tmpPoint = 0;
                                    powerPoint = 0 ;
                                    freqPoint = 0;
                                    phasePoint = 0 ;
                                    currPoint = 0 ;
                                    ampPoint = 0 ;
                                    energyPoint = 0;
                                    forcePoint = 0 ;
                                    absoluteDistPoint = 0 ;
                                    collapseDistPoint = 0 ;
                                }

                                else
                                {
                                    tmpPoint = ampLeftAxisPlot.at(indexClosest1);
                                    timePoint = tmpPoint.x;

                                    ampPoint = ampLeftAxisPlot.findY(graphSlider.timeLabel)

                                    powerPoint = powerLeftAxisPlot.findY(graphSlider.timeLabel)

                                    freqPoint = freqLeftAxisPlot.findY(graphSlider.timeLabel)

                                    phasePoint = phaseLeftAxisPlot.findY(graphSlider.timeLabel)

                                    currPoint = currentLeftAxisPlot.findY(graphSlider.timeLabel)

                                    yAxisValueUpdated(ampPoint, powerPoint, freqPoint, phasePoint, currPoint)
                                }
                            }
                        }
                    }

                    Text
                    {
                        id: graphNavigatorLabel
                        anchors.bottom: graphNavigatorImage.top
                        anchors.bottomMargin: 5
                        height: font.pixelSize
                        anchors.horizontalCenter: graphSlider.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: Style.regular.name
                        font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
                        text: parent.timeLabel + " " +qmltextSecUnit
                        color: parent.custColor
                    }
                }
            }
        }
    }
}

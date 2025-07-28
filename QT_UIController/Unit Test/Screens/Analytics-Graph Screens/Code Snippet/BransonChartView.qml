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
Item {
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: isNormalScreen === true ? Math.round(Style.style1 * Style.scaleHint) : Math.round(Style.style4 * Style.scaleHint)
    property double timemax: 1

    readonly property string energyLeftPlotName:            "energyLeftPlot"
    readonly property string energyRightPlotName:           "energyRightPlot"
    readonly property string ampLeftPlotName:               "ampLeftPlot"
    readonly property string ampRightPlotName:              "ampRightPlot"
    readonly property string currentLeftPlotName:           "currentLeftPlot"
    readonly property string currentRightPlotName:          "currentRightPlot"
    readonly property string powerLeftPlotName:             "powerLeftPlot"
    readonly property string powerRightPlotName:            "powerRightPlot"
    readonly property string phaseLeftPlotName:             "phaseLeftPlot"
    readonly property string phaseRightPlotName:            "phaseRightPlot"
    readonly property string forceLeftPlotName:             "forceLeftPlot"
    readonly property string forceRightPlotName:            "forceRightPlot"
    readonly property string velocityLeftPlotName:          "velocityLeftPlot"
    readonly property string velocityRightPlotName:         "velocityRightPlot"
    readonly property string absoluteDistLeftPlotName:      "absoluteDistLeftPlot"
    readonly property string absoluteDistRightPlotName:     "absoluteDistRightPlot"
    readonly property string collapseDistLeftPlotName:      "collapseDistLeftPlot"
    readonly property string collapseDistRightPlotName:     "collapseDistRightPlot"
    readonly property string freqLeftPlotName:              "freqLeftPlot"
    readonly property string freqRightPlotName:             "freqRightPlot"
    readonly property string qmltextPhase0Plot:             "phase0Plot"
    readonly property string qmltextSecUnit:                "s"

    /*Whether the axis controls the coordinate display*/
    property bool isGraphEnable                   : true
    property bool isAmpLeftAxisVisible            : true
    property bool isPowerLeftAxisVisible          : false
    property bool isFreqLeftAxisVisible           : false
    property bool isPhaseLeftAxisVisible          : false
    property bool isCurrentLeftAxisVisible        : false
    property bool isEnergyLeftAxisVisible         : false
    property bool isForceLeftAxisVisible          : false
    property bool isAbsoluteDistLeftAxisVisible   : false
    property bool isCollapseDistLeftAxisVisible   : false

    property int toolTipTimeoutValue: 50000
    signal timeValueUpdated(var timeVal)

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
        var tmpPoint, timePoint , powerPoint, freqPoint, energyPoint, ampPoint;

        if(isAmpLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(ampLeftPlotName), GraphAxisEnum.AMP_IDX);
        if(isPowerLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(powerLeftPlotName), GraphAxisEnum.POWER_IDX);
        if(isFreqLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(freqLeftPlotName), GraphAxisEnum.FREQ_IDX);
        if(isPhaseLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(phaseLeftPlotName), GraphAxisEnum.PHASE_IDX);
        if(isCurrentLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(currentLeftPlotName), GraphAxisEnum.CURRENT_IDX);
        if(isEnergyLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(energyLeftPlotName), GraphAxisEnum.ENERGY_IDX);
        if(isForceLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(forceLeftPlotName), GraphAxisEnum.FORCE_IDX);
        if(isAbsoluteDistLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(absoluteDistLeftPlotName), GraphAxisEnum.ABSOLUTEDIST_IDX);
        if(isCollapseDistLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(collapseDistLeftPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);

        /* Update the Min and Max values */
        var axisMinValues = WeldGraphObj.getAxisMinParameters();
        var axisMaxValues = WeldGraphObj.getAxisMaxParameters();
        timeAxis.min                = 0;
        ampLeftAxis.min             = 0
        powerLeftAxis.min           = Math.max(0, axisMinValues[GraphAxisEnum.POWER_IDX]);
        freqLeftAxis.min            = axisMinValues[GraphAxisEnum.FREQ_IDX] - 100;
        phaseLeftAxis.min           = -180
        currentLeftAxis.min         = 0
        energyLeftAxis.min          = Math.max(0, (axisMinValues[GraphAxisEnum.ENERGY_IDX] - 2));
        forceLeftAxis.min           = Math.max(0, (axisMinValues[GraphAxisEnum.FORCE_IDX] - 2));
        absoluteDistLeftAxis.min    = Math.max(0, (axisMinValues[GraphAxisEnum.ABSOLUTEDIST_IDX] - 2));
        collapseDistLeftAxis.min    = axisMinValues[GraphAxisEnum.COLLAPSEDIST_IDX] - 1;

        timeAxis.max                = timemax;
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
        ampLeftAxis.max             = roundAxisValues(ampLeftAxis.max, ampLeftAxis.min);
        powerLeftAxis.max           = roundAxisValues(powerLeftAxis.max, powerLeftAxis.min);
        freqLeftAxis.max            = roundAxisValues(freqLeftAxis.max, freqLeftAxis.min);
        phaseLeftAxis.max           = roundAxisValues(phaseLeftAxis.max, phaseLeftAxis.min);
        currentLeftAxis.max         = roundAxisValues(currentLeftAxis.max, currentLeftAxis.min);
        energyLeftAxis.max          = roundAxisValues(energyLeftAxis.max, energyLeftAxis.min);
        forceLeftAxis.max           = roundAxisValues(forceLeftAxis.max, forceLeftAxis.min);
        absoluteDistLeftAxis.max    = roundAxisValues(absoluteDistLeftAxis.max, absoluteDistLeftAxis.min);
        collapseDistLeftAxis.max    = roundAxisValues(collapseDistLeftAxis.max, collapseDistLeftAxis.min);

    }

    function clearGraph()
    {
        timeAxis.min = 0;
        timeAxis.max = timemax;
        ampLeftAxisPlot.clear()
        powerLeftAxisPlot.clear()
        freqLeftAxisPlot.clear()
        phaseLeftAxisPlot.clear()
        currentLeftAxisPlot.clear()
        energyLeftAxisPlot.clear()
        forceLeftAxisPlot.clear()
        absoluteDistLeftAxisPlot.clear()
        collapseDistLeftAxisPlot.clear()
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
                margins.top: Math.round(10  * Style.scaleHint)
                margins.right: 0
                margins.left: 0
                margins.bottom: 0
                property real plotStartPointY: plotArea.y
                property real plotStartPointX: plotArea.x
                property real deltaX: plotArea.width / (timeAxis.max - timeAxis.min)
                property real myWidth: 1
//                plotAreaColor: "red"
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
                    titleFont.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.5f"
                    max: timemax
                    min: 0.00000
                    tickCount: 5
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 10
                    min:0
                    tickCount: 11
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    max: 20450
                    min: 19450
                    tickCount: 11
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    max: 180
                    min: -180
                    tickCount: 11
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis
                {
                    id: energyLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: isEnergyLeftAxisVisible
                    gridVisible: false
                    labelsVisible: isEnergyLeftAxisVisible
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ENERGY_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.ENERGY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    max: 50
                    min: 0
                    tickCount: 11
                    labelFormat: "%.0f"
                }

                ValueAxis
                {
                    id: forceLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: isForceLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.FORCE_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.FORCE_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis
                {
                    id: absoluteDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: isAbsoluteDistLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.ABSOLUTEDIST_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 120
                    min:0
                    tickCount: 11
                }

                ValueAxis
                {
                    id: collapseDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: isCollapseDistLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.COLLAPSEDIST_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.COLLAPSEDIST_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    max: 5
                    min: -5
                    tickCount: 11
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
                        graphHeader.text = text + "%"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
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
                        graphHeader.text = text + "W"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
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
                        graphHeader.text = text + "Hz"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
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
                        graphHeader.text = text + "Deg"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
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
                        graphHeader.text = text + "%"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
                    }
                }

                LineSeries
                {
                    id: energyLeftAxisPlot
                    width: graphChartView.myWidth
                    name: energyLeftPlotName
                    axisX: timeAxis
                    axisY: energyLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: (isEnergyLeftAxisVisible && isGraphEnable)
                    useOpenGL: true
                    pointsVisible: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Energy: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + "J"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
                    }
                }

                LineSeries
                {
                    id: forceLeftAxisPlot
                    width: graphChartView.myWidth
                    name: forceLeftPlotName
                    axisX: timeAxis
                    axisY: forceLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: (isForceLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Force: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + "N"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
                    }
                }

                LineSeries
                {
                    id: absoluteDistLeftAxisPlot
                    width: graphChartView.myWidth
                    name: absoluteDistLeftPlotName
                    axisX: timeAxis
                    axisY: absoluteDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: (isAbsoluteDistLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Abs.Distance: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + "mm"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
                    }
                }

                LineSeries
                {
                    id: collapseDistLeftAxisPlot
                    width: graphChartView.myWidth
                    name: collapseDistLeftPlotName
                    axisX: timeAxis
                    axisY: collapseDistLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: (isCollapseDistLeftAxisVisible  && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Col. Distance: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + "mm"
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = true
                    }
                }


                Repeater {
                    id:graphPoints
                    model:weldPointModel
                    Component
                    {
                        id:graphPointsDelegate
                        Item
                        {
                            property double xAxisPosition: model.modelData.xAxisPos - WeldGraphObj.getTriggerPoint()
                            id: graphPointItem
                            y: graphChartView.plotStartPointY - graphPointLabel.height
                            x: graphChartView.plotStartPointX + ( (graphChartView.deltaX * (xAxisPosition - timeAxis.min)) - graphPointLine.width / 2 )
                            width : graphPointLine.width
                            height : graphPointLine.height + graphPointLabel.height
                            visible: ((xAxisPosition >= timeAxis.min) && (xAxisPosition <= timeAxis.max) && (isGraphEnable))
                            Rectangle
                            {
                                id: graphPointLine
                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                border.width: 1
                                height: graphChartView.plotArea.height
                                width:1
                                color: "#000000"
                            }
                            Text {
                                id: graphPointLabel
                                anchors.bottom: graphPointLine.top
                                anchors.bottomMargin: 5
                                anchors.horizontalCenter: parent.horizontalCenter
                                height: font.pixelSize + 10
                                width : 40
                                horizontalAlignment: Text.AlignHCenter
                                font.family : Style.semibold.name
                                font.pixelSize: Style.style4
                                text: model.modelData.labelName
                                color: "#000000"
                            }
                        }
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
                    width : Math.round(75 * Style.scaleHint)
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

                Rectangle {
                    id: graphSlider
                    property int raiseHeight: Math.round(15 * Style.scaleHint)
                    property string custColor : Style.activeFrameBorderColor
                    property int assetSize:20
                    property real xAxisVal: timeAxis.min
                    property string timeLabel: timeAxis.min
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

                    Rectangle {
                        id: graphNavigatorImage
                        height: parent.assetSize
                        width : parent.assetSize
                        radius: width / 2
                        color: parent.custColor
                        anchors.bottom: graphNavigator.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        MouseArea {
                            id: graphNavigatorMouseArea
                            property point posInChartArea
                            property int indexClosest1:0
                            anchors.fill: parent
                            cursorShape: Qt.ToolTip
                            hoverEnabled: false
                            onPositionChanged: {
                                /* Drag position of the slider */
                                var point = mapToItem(chartViewArea , mouse.x , mouse.y);
                                var retVal ;
                                var timeVal;
                                var tmpPoint,timePoint,powerPoint,freqPoint, phasePoint, currPoint, energyPoint, ampPoint, forcePoint, absoluteDistPoint, collapseDistPoint;

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
                                graphSlider.timeLabel = timeVal.toFixed(5)
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
                                    tmpPoint = powerLeftAxisPlot.at(indexClosest1);
                                    powerPoint = tmpPoint.y;
                                    timePoint = tmpPoint.x;

                                    tmpPoint = freqLeftAxisPlot.at(indexClosest1);
                                    freqPoint = tmpPoint.y;

                                    tmpPoint = ampLeftAxisPlot.at(indexClosest1);
                                    ampPoint = tmpPoint.y;

                                    tmpPoint = currentLeftAxisPlot.at(indexClosest1);
                                    currPoint = tmpPoint.y;

                                    tmpPoint = phaseLeftAxisPlot.at(indexClosest1);
                                    phasePoint = tmpPoint.y;

                                    tmpPoint = energyLeftAxisPlot.at(indexClosest1);
                                    energyPoint = tmpPoint.y ;

                                    tmpPoint = forceLeftAxisPlot.at(indexClosest1);
                                    forcePoint = tmpPoint.y ;


                                    tmpPoint = absoluteDistLeftAxisPlot.at(indexClosest1);
                                    absoluteDistPoint = tmpPoint.y ;

                                    tmpPoint = collapseDistLeftAxisPlot.at(indexClosest1);
                                    collapseDistPoint = tmpPoint.y ;

                                    // checkboxObj.updateParameterVal(ampPoint,currPoint,powerPoint,freqPoint,energyPoint,phasePoint,forcePoint,absoluteDistPoint,collapseDistPoint)
                                    //                                graphSlider.timeLabel = timePoint.toFixed(5);
                                    // gridview2.contentItem.children[0].paramVal = timePoint.toFixed(5);
                                }
                            }
                        }
                    }
                    Text {
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

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
    id: weldGraph
    property bool flagDragDrop: false
    property bool isNormalScreen: true
    property int fontsize: isNormalScreen === true ? Math.round(Style.style1 * Style.scaleHint) : Math.round(Style.style4 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property double timeMin: 1
    property double timeMax: 1
    property bool enableZoom: false
    property bool firstFlagg: true

    property var lineSeriesOne: ampLeftAxisPlot
    property var lineSeriesTwo: currentLeftAxisPlot

    property double perc: 0

    readonly property string ampLeftPlotName:               "ampLeftPlot"
    readonly property string powerLeftPlotName:             "powerLeftPlot"
    readonly property string freqLeftPlotName:              "freqLeftPlot"
    readonly property string phaseLeftPlotName:             "phaseLeftPlot"
    readonly property string currentLeftPlotName:           "currentLeftPlot"
    readonly property string energyLeftPlotName:            "energyLeftPlot"
    readonly property string forceLeftPlotName:             "forceLeftPlot"
    readonly property string absoluteDistLeftPlotName:      "absoluteDistLeftPlot"
    readonly property string collapseDistLeftPlotName:      "collapseDistLeftPlot"
    readonly property string reqAmpLeftPlotName:            "reqAmpLeftPlot"
    readonly property string velocityLeftPlotName:          "velocityLeftPlot"
    readonly property string qmltextPhase0Plot:             "phase0Plot"

    readonly property string goldenAmpPlotName:               "goldenAmpPlot"
    readonly property string goldenPowerPlotName:             "goldenPowerPlot"
    readonly property string goldenFreqPlotName:              "goldenFreqPlot"
    readonly property string goldenPhasePlotName:             "goldenPhasePlot"
    readonly property string goldenCurrentPlotName:           "goldenCurrentPlot"
    readonly property string goldenEnergyPlotName:            "goldenEnergyPlot"
    readonly property string goldenForcePlotName:             "goldenForcePlot"
    readonly property string goldenAbsoluteDistPlotName:      "goldenAbsoluteDistPlot"
    readonly property string goldenCollapseDistPlotName:      "goldenCollapseDistPlot"
    readonly property string goldenReqAmpPlotName:            "goldenReqAmpPlot"
    readonly property string goldenVelocityPlotName:          "goldenVelocityPlot"

    property string qmltextSecUnit:                "s"

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
    property bool isReqAmpLeftAxisVisible         : false
    property bool isVelocityLeftAxisVisible       : false

    property double timePoint
    property double ampPoint
    property double powerPoint
    property double freqPoint
    property double phasePoint
    property double currPoint
    property double energyPoint
    property double forcePoint
    property double absoluteDistPoint
    property double collapseDistPoint
    property double reqAmpPoint
    property double velocityPoint

    property double refTimePoint
    property double refAmpPoint
    property double refPowerPoint
    property double refFreqPoint
    property double refPhasePoint
    property double refCurrPoint
    property double refEnergyPoint
    property double refForcePoint
    property double refAbsoluteDistPoint
    property double refCollapseDistPoint
    property double refReqAmpPoint
    property double refVelocityPoint

    property double ampMinVal               : GraphSettings.AmpAxisMinValue
    property double ampMaxVal               : GraphSettings.AmpAxisMaxValue

    property double powerMinVal             : GraphSettings.PowerAxisMinValue
    property double powerMaxVal             : GraphSettings.PowerAxisMaxValue

    property double freqMinVal              : GraphSettings.FreqAxisMinValue
    property double freqMaxVal              : GraphSettings.FreqAxisMaxValue

    property double phaseMinVal             : GraphSettings.PhaseAxisMinValue
    property double phaseMaxVal             : GraphSettings.PhaseAxisMaxValue

    property double currentMinVal           : GraphSettings.CurrentAxisMinValue
    property double currentMaxVal           : GraphSettings.CurrentAxisMaxValue

    property double energyMinVal            : GraphSettings.EnergyAxisMinValue
    property double energyMaxVal            : GraphSettings.EnergyAxisMaxValue

    property double forceMinVal             : GraphSettings.ForceAxisMinValue
    property double forceMaxVal             : GraphSettings.ForceAxisMaxValue

    property double absoluteDistMinVal      : GraphSettings.AbsDisAxisMinValue
    property double absoluteDistMaxVal      : GraphSettings.AbsDisAxisMaxValue

    property double collapseDistMinVal      : GraphSettings.ColDisAxisMinValue
    property double collapseDistMaxVal      : GraphSettings.ColDisAxisMaxValue

    property double reqAmpMinVal            : GraphSettings.ReqAmpAxisMinValue
    property double reqAmpMaxVal            : GraphSettings.ReqAmpAxisMaxValue

    property double velocityMinVal          : GraphSettings.VelocityAxisMinValue
    property double velocityMaxVal          : GraphSettings.VelocityAxisMaxValue

    property int toolTipTimeoutValue        : 5000
    property int qmlTextTickCount_X_Axis    : 9
    property int qmlTextTickCount_Y_Axis    : 9

    property bool isReferenceGraphEnable    : true
    property alias timeAxisRef: timeAxis
    property var yAxisOneRef: ampLeftAxis
    property var yAxisTwoRef: currentLeftAxis
    property int graphPointItemRef : graphPointItem.x
    property double tenPercZoomFactor : 0.10
    property double maxZoomLimit : 1.50
    property double ninetyPercZoomLimit : 0.90


    property real lastDistance: 0
    property real pinchCenterX: 0
    property real pinchCenterY: 0

    property bool firstZoom : true
    property real actualXMin : timeMinValue
    property real actualXMax : timeMaxValue

    property real actualXMinPerc : 0
    property real actualXMaxPerc : 0

    property real actualYMin : axisOneMin
    property real actualYMax : axisOneMax

    property real actualY2Min : axisTwoMin
    property real actualY2Max : axisTwoMax

    property real actualYMinPerc : 0
    property real actualYMaxPerc : 0

    property real pressX : 0
    property real pressY : 0

    QtObject
    {
        id: touchPointsEnum
        readonly property int oneTouchPoint      : 1
        readonly property int twoTouchPoint      : 2
    }


    signal timeValueUpdated(var timeVal)

    signal yAxisValueUpdated(var ampVal,var powerVal, var freqVal, var phaseVal, var currentVal,var energyVal,var forceVal,var absVal,
                             var colVal,var reqAmpVal, var velocityVal)

    signal yRefAxisValueUpdated(var refAmpVal,var refPowerVal, var refFreqVal, var refPhaseVal, var refCurrentVal,var refEnergyVal,var refForceVal,var refAbsVal,
                                var refColVal,var refReqAmpVal, var refVelocityVal)

    /**
    *@breif: Rounding of axis values for proper representation
    **/


    Component.onCompleted:
    {
    }
    function resetZoom()
    {
        timeAxis.min = timeMin;
        timeAxis.max = timeMax;
        yAxisOneRef.min = axisOneMin;
        yAxisOneRef.max = axisOneMax;
        yAxisTwoRef.min = axisTwoMin;
        yAxisTwoRef.max = axisTwoMax;
        axisY.min = axisOneMin;
        axisY.max = axisOneMax;
        axisYTwo.min = axisTwoMin;
        axisYTwo.max = axisTwoMax;
        chart.timeAxisMinZoomLimit = timeMin
        chart.timeAxisMaxZoomLimit = timeMax
        startRect.x = 0;
        endRect.x = chart.width - endRect.width
    }

    function enableLineVisibility(lineNum)
    {
        switch(lineNum)
        {
        case 1:
            var tValue = graphChartView.mapToValue(Qt.point(graphPointItem.x,graphPointItem.y));
            if(tValue.x < timeAxis.min)
            {
                return false;
            }
            else
            {
                return true;
            }
            break
        case 2:
            var tValue = graphChartView.mapToValue(Qt.point(graphPointItem2.x,graphPointItem2.y));
            if(tValue.x < timeAxis.min)
            {
                return false;
            }
            else
            {
                return true;
            }
            break
        case 3:
            var tValue = graphChartView.mapToValue(Qt.point(graphPointItem3.x,graphPointItem3.y));
            if(tValue.x < timeAxis.min)
            {
                return false;
            }
            else
            {
                return true;
            }
            break
        }
    }

    function updateYAxisRef(firstYAxisIndex, secondYAxisIndex)
    {
        switch(firstYAxisIndex)
        {
        case GraphAxisEnum.AMP_IDX:
            yAxisOneRef = ampLeftAxis
            lineSeriesOne = ampLeftAxisPlot
            break;
        case GraphAxisEnum.POWER_IDX:
            yAxisOneRef = powerLeftAxis
            lineSeriesOne = powerLeftAxisPlot
            break
        case GraphAxisEnum.FREQ_IDX:
            yAxisOneRef = freqLeftAxis
            lineSeriesOne = freqLeftAxisPlot
            break
        case GraphAxisEnum.PHASE_IDX:
            yAxisOneRef = phaseLeftAxis
            lineSeriesOne = phaseLeftAxisPlot
            break;
        case GraphAxisEnum.CURRENT_IDX:
            yAxisOneRef = currentLeftAxis
            lineSeriesOne = currentLeftAxisPlot
            break
        case GraphAxisEnum.ENERGY_IDX:
            yAxisOneRef = energyLeftAxis
            lineSeriesOne = energyLeftAxisPlot
            break
        case GraphAxisEnum.FORCE_IDX:
            yAxisOneRef = forceLeftAxis
            lineSeriesOne = forceLeftAxisPlot
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            yAxisOneRef = absoluteDistLeftAxis
            lineSeriesOne = absoluteDistLeftAxisPlot
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            yAxisOneRef = collapseDistLeftAxis
            lineSeriesOne = collapseDistLeftAxisPlot
            break
        case GraphAxisEnum.REQAMP_IDX:
            yAxisOneRef = reqAmpLeftAxis
            lineSeriesOne = reqAmpLeftAxisPlot
            break
        case GraphAxisEnum.VELOCITY_IDX:
            yAxisOneRef = velocitylLeftAxis
            lineSeriesOne = velocityLeftAxisPlot
            break
        default:
            break
        }

        switch(secondYAxisIndex)
        {
        case GraphAxisEnum.AMP_IDX:
            yAxisTwoRef = ampLeftAxis
            lineSeriesTwo = ampLeftAxisPlot
            break;
        case GraphAxisEnum.POWER_IDX:
            yAxisTwoRef = powerLeftAxis
            lineSeriesTwo = powerLeftAxisPlot
            break
        case GraphAxisEnum.FREQ_IDX:
            yAxisTwoRef = freqLeftAxis
            lineSeriesTwo = freqLeftAxisPlot
            break
        case GraphAxisEnum.PHASE_IDX:
            yAxisTwoRef = phaseLeftAxis
            lineSeriesTwo = phaseLeftAxisPlot
            break;
        case GraphAxisEnum.CURRENT_IDX:
            yAxisTwoRef = currentLeftAxis
            lineSeriesTwo = currentLeftAxisPlot
            break
        case GraphAxisEnum.ENERGY_IDX:
            yAxisTwoRef = energyLeftAxis
            lineSeriesTwo = energyLeftAxisPlot
            break
        case GraphAxisEnum.FORCE_IDX:
            yAxisTwoRef = forceLeftAxis
            lineSeriesTwo = forceLeftAxisPlot
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            yAxisTwoRef = absoluteDistLeftAxis
            lineSeriesTwo = absoluteDistLeftAxisPlot
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            yAxisTwoRef = collapseDistLeftAxis
            lineSeriesTwo = collapseDistLeftAxisPlot
            break
        case GraphAxisEnum.REQAMP_IDX:
            yAxisTwoRef = reqAmpLeftAxis
            lineSeriesTwo = reqAmpLeftAxisPlot
            break
        case GraphAxisEnum.VELOCITY_IDX:
            yAxisTwoRef = velocitylLeftAxis
            lineSeriesTwo = velocityLeftAxisPlot
            break
        default:
            break
        }
    }


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

        if(isReqAmpLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(reqAmpLeftPlotName), GraphAxisEnum.REQAMP_IDX);
        if(isVelocityLeftAxisVisible && isGraphEnable)
            WeldGraphObj.appendSamples(graphChartView.series(velocityLeftPlotName), GraphAxisEnum.VELOCITY_IDX);

        if(isAmpLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenAmpPlotName), GraphAxisEnum.AMP_IDX);
        if(isPowerLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenPowerPlotName), GraphAxisEnum.POWER_IDX);
        if(isFreqLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenFreqPlotName), GraphAxisEnum.FREQ_IDX);
        if(isPhaseLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenPhasePlotName), GraphAxisEnum.PHASE_IDX);
        if(isCurrentLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenCurrentPlotName), GraphAxisEnum.CURRENT_IDX);
        if(isEnergyLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenEnergyPlotName), GraphAxisEnum.ENERGY_IDX);
        if(isForceLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenForcePlotName), GraphAxisEnum.FORCE_IDX);
        if(isAbsoluteDistLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenAbsoluteDistPlotName), GraphAxisEnum.ABSOLUTEDIST_IDX);
        if(isCollapseDistLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenCollapseDistPlotName), GraphAxisEnum.COLLAPSEDIST_IDX);

        if(isReqAmpLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenReqAmpPlotName), GraphAxisEnum.REQAMP_IDX);
        if(isVelocityLeftAxisVisible && isGraphEnable)
            ReferenceWeldGraphData.appendSamples(graphChartView.series(goldenVelocityPlotName), GraphAxisEnum.VELOCITY_IDX);

        yAxisValueUpdated(ampPoint, powerPoint, freqPoint, phasePoint, currPoint, energyPoint, forcePoint,
                          absoluteDistPoint, collapseDistPoint, reqAmpPoint, velocityPoint)

        yRefAxisValueUpdated(refAmpPoint, refPowerPoint, refFreqPoint, refPhasePoint, refCurrPoint, refEnergyPoint,
                             refForcePoint, refAbsoluteDistPoint, refCollapseDistPoint, refReqAmpPoint, refVelocityPoint)
    }

    function clearGraph()
    {
        if(firstFlagg)
        {
            timeAxis.min = timeMin;
            timeAxis.max = timeMax;
        }

        firstFlagg = false;
        ampLeftAxisPlot.clear()
        powerLeftAxisPlot.clear()
        freqLeftAxisPlot.clear()
        phaseLeftAxisPlot.clear()
        currentLeftAxisPlot.clear()
        energyLeftAxisPlot.clear()
        forceLeftAxisPlot.clear()
        absoluteDistLeftAxisPlot.clear()
        collapseDistLeftAxisPlot.clear()
        reqAmpLeftAxisPlot.clear()
        velocityLeftAxisPlot.clear()

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

                MultiPointTouchArea{
                    anchors.fill : parent
                    enabled: enableZoom
                    onReleased: {
                        if(touchPoints.length === touchPointsEnum.oneTouchPoint)
                        {
                            /*Calculate current range of x and y axis*/
                            var totalXDist = timeAxis.max - timeAxis.min;
                            var totalYDist = yAxisOneRef.max - yAxisOneRef.min;
                            var totalY2Dist = yAxisTwoRef.max - yAxisTwoRef.min;
                            /*Calculate increment factor for x and two y axis*/
                            var slideXFactor = (totalXDist * tenPercZoomFactor);
                            var slideYFactor = (totalYDist * tenPercZoomFactor);
                            var slideY2Factor = (totalY2Dist * tenPercZoomFactor);
                            var ActualYMin = Math.min(actualYMin,actualY2Min);
                            var ActualYMax = Math.max(actualYMax,actualY2Max);
                            var currentYMin = Math.min(yAxisOneRef.min,yAxisTwoRef.min);
                            var currentYMax = Math.max(yAxisOneRef.max,yAxisTwoRef.max);
                            /*Scroll chart to right till max value of chart selected*/
                            if(Math.abs(touchPoints[0].x - pressX) > Math.abs(touchPoints[0].y - pressY))
                            {
                                if(touchPoints[0].x > pressX && (timeAxis.max < chart.timeAxisMaxZoomLimit))
                                {
                                    timeAxis.min = timeAxis.min + slideXFactor;
                                    timeAxis.max = timeAxis.max + slideXFactor;
                                }
                                /*Scroll chart to left till min value of chart selected*/
                                if(touchPoints[0].x < pressX && (timeAxis.min > chart.timeAxisMinZoomLimit))
                                {
                                    timeAxis.min = timeAxis.min - slideXFactor;
                                    timeAxis.max = timeAxis.max - slideXFactor;
                                }
                            }
                            else
                            {
                                /*Scroll chart to top till max value of y axis selected*/
                                if(touchPoints[0].y > pressY && currentYMax < ActualYMax)
                                {
                                    yAxisOneRef.min = yAxisOneRef.min + slideYFactor;
                                    yAxisOneRef.max = yAxisOneRef.max + slideYFactor;

                                    yAxisTwoRef.min = yAxisTwoRef.min + slideY2Factor;
                                    yAxisTwoRef.max = yAxisTwoRef.max + slideY2Factor;
                                }
                                /*Scroll chart to bottom till min value of y axis selected*/
                                if(touchPoints[0].y < pressY && currentYMin > ActualYMin)
                                {
                                    yAxisOneRef.min = yAxisOneRef.min - slideYFactor;
                                    yAxisOneRef.max = yAxisOneRef.max - slideYFactor;

                                    yAxisTwoRef.min = yAxisTwoRef.min - slideY2Factor;
                                    yAxisTwoRef.max = yAxisTwoRef.max - slideY2Factor;
                                }
                            }
                        }
                    }

                    onPressed: (touchPoints) =>{
                                   /*get the x and y point at first touch*/
                                   if(touchPoints.length === touchPointsEnum.oneTouchPoint)
                                   {
                                       pressX = touchPoints[0].x;
                                       pressY = touchPoints[0].y;
                                   }
                               }

                    onTouchUpdated:(touchPoints)=> {
                                       var totalXDist = timeAxis.max -timeAxis.min;
                                       if(touchPoints.length === touchPointsEnum.twoTouchPoint)
                                       {
                                           /*calculate the mid point of touch to zoom on that perticular area*/
                                           var centerX = (touchPoints[0].x + touchPoints[1].x) / 2;
                                           var centerY = (touchPoints[0].y + touchPoints[1].y) / 2;
                                           /*calculate the distance between two points to modufy zoom range*/
                                           var dx = touchPoints[1].x - touchPoints[0].x;
                                           var dy = touchPoints[1].y - touchPoints[0].y;

                                           var distX = Math.sqrt(dx * dx + dy * dy)
                                           /*map actual x and y touch points accourding to graph touch points*/
                                           var convPointTime = graphChartView.mapToValue(Qt.point(centerX,centerY));
                                           var convPointAxisOne = graphChartView.mapToValue(Qt.point(centerX,centerY),lineSeriesOne);
                                           var convPointAxisTwo = graphChartView.mapToValue(Qt.point(centerX,centerY),lineSeriesTwo);
                                           /*Decide which side of graph need to be zoom(left or right) accourding to touch*/
                                           var leftXDist = convPointTime.x - timeAxis.min;
                                           var rightXDist = timeAxis.max - convPointTime.x;
                                           var leftXPerc = leftXDist / totalXDist;
                                           var rightXPerc = rightXDist / totalXDist;


                                           var totalYDist = yAxisOneRef.max - yAxisOneRef.min;
                                           var bottomYDist = convPointAxisOne.y - yAxisOneRef.min;
                                           var topYDist = yAxisOneRef.max - convPointAxisOne.y;
                                           var bottomYPerc = bottomYDist / totalYDist;
                                           var topYPerc = topYDist / totalYDist;

                                           var totalY2Dist = yAxisTwoRef.max - yAxisTwoRef.min;
                                           var bottomY2Dist = convPointAxisTwo.y - yAxisTwoRef.min;
                                           var topY2Dist = yAxisTwoRef.max - convPointAxisTwo.y;
                                           var bottomY2Perc = bottomY2Dist / totalY2Dist;
                                           var topY2Perc = topY2Dist / totalY2Dist;
                                           var sliderRange = chart.timeAxisMaxZoomLimit - chart.timeAxisMinZoomLimit
                                           /*As distance is increasing zoom in into graph*/
                                           if(lastDistance < distX)
                                           {
                                               /*Zoom in the graph till maximum limit*/
                                               if((convPointTime.x - timeAxis.min) < (timeAxis.max - convPointTime.x))
                                               {
                                                   if((sliderRange / (timeAxis.max - timeAxis.min) ) < maxZoomLimit)
                                                   {
                                                       timeAxis.min = timeAxis.min + ((actualXMax - actualXMin) * (tenPercZoomFactor * leftXPerc));
                                                       timeAxis.max = timeAxis.max - ((actualXMax - actualXMin) * (tenPercZoomFactor * rightXPerc));
                                                   }

                                               }
                                               else
                                               {
                                                   if((sliderRange / (timeAxis.max - timeAxis.min) ) < maxZoomLimit)
                                                   {
                                                       timeAxis.min = timeAxis.min + ((actualXMax - actualXMin) * (tenPercZoomFactor * leftXPerc));
                                                       timeAxis.max = timeAxis.max - ((actualXMax - actualXMin) * (tenPercZoomFactor * rightXPerc));
                                                   }
                                               }

                                               if((convPointAxisTwo.y - yAxisTwoRef.min) < (yAxisTwoRef.max - convPointAxisTwo.y))
                                               {
                                                   if(((actualY2Max - actualY2Min) / (yAxisTwoRef.max - yAxisTwoRef.min)) < maxZoomLimit)
                                                   {
                                                       yAxisTwoRef.min = yAxisTwoRef.min + ((actualY2Max - actualY2Min) * (tenPercZoomFactor * bottomY2Perc));
                                                       yAxisTwoRef.max = yAxisTwoRef.max - ((actualY2Max - actualY2Min) * (tenPercZoomFactor * topY2Perc));
                                                   }
                                               }
                                               else
                                               {
                                                   if(((actualY2Max - actualY2Min) / (yAxisTwoRef.max - yAxisTwoRef.min)) < maxZoomLimit)
                                                   {
                                                       yAxisTwoRef.min = yAxisTwoRef.min + ((actualY2Max - actualY2Min) * (tenPercZoomFactor * bottomY2Perc));
                                                       yAxisTwoRef.max = yAxisTwoRef.max - ((actualY2Max - actualY2Min) * (tenPercZoomFactor * topY2Perc));
                                                   }
                                               }

                                               if((convPointAxisOne.y - yAxisOneRef.min) < (yAxisOneRef.max - convPointAxisOne.y))
                                               {
                                                   if(((actualYMax - actualYMin) / (yAxisOneRef.max - yAxisOneRef.min)) < maxZoomLimit)
                                                   {
                                                       yAxisOneRef.min = yAxisOneRef.min + ((actualYMax - actualYMin) * (tenPercZoomFactor * bottomYPerc));
                                                       yAxisOneRef.max = yAxisOneRef.max - ((actualYMax - actualYMin) * (tenPercZoomFactor * topYPerc));
                                                   }
                                               }
                                               else
                                               {
                                                   if(((actualYMax - actualYMin) / (yAxisOneRef.max - yAxisOneRef.min)) < maxZoomLimit)
                                                   {
                                                       yAxisOneRef.min = yAxisOneRef.min + ((actualYMax - actualYMin) * (tenPercZoomFactor * bottomYPerc));
                                                       yAxisOneRef.max = yAxisOneRef.max - ((actualYMax - actualYMin) * (tenPercZoomFactor * topYPerc));
                                                   }
                                               }
                                           }
                                           /*As distance is decreasing zoom out into graph*/
                                           else
                                           {
                                               if(timeAxis.max < chart.timeAxisMaxZoomLimit)
                                               {
                                                   if((chart.timeAxisMaxZoomLimit * ninetyPercZoomLimit) < timeAxis.max)
                                                   {
                                                       timeAxis.max = chart.timeAxisMaxZoomLimit;
                                                   }
                                                   else
                                                   {
                                                       timeAxis.max = timeAxis.max + ((actualXMax - actualXMin) * tenPercZoomFactor);
                                                   }
                                               }
                                               if(timeAxis.min > chart.timeAxisMinZoomLimit)
                                               {
                                                   if((timeAxis.min * ninetyPercZoomLimit) < chart.timeAxisMinZoomLimit)
                                                   {
                                                       timeAxis.min = chart.timeAxisMinZoomLimit;
                                                   }
                                                   else{
                                                       timeAxis.min = timeAxis.min - ((actualXMax - actualXMin) * tenPercZoomFactor);
                                                   }
                                               }
                                               if(yAxisOneRef.max <= actualYMax)
                                               {
                                                   yAxisOneRef.max = yAxisOneRef.max + ((actualYMax - actualYMin) * tenPercZoomFactor);
                                                   if(yAxisOneRef.max > actualYMax)
                                                   {
                                                      yAxisOneRef.max = actualYMax;
                                                   }
                                               }
                                               if(yAxisOneRef.min >= actualYMin)
                                               {
                                                   yAxisOneRef.min = yAxisOneRef.min - ((actualYMax - actualYMin) * tenPercZoomFactor);
                                                   if(yAxisOneRef.min < actualYMin)
                                                   {
                                                      yAxisOneRef.min = actualYMin;
                                                   }
                                               }

                                               if(yAxisTwoRef.max <= actualY2Max)
                                               {
                                                   yAxisTwoRef.max = yAxisTwoRef.max + ((actualY2Max - actualY2Min) * tenPercZoomFactor);
                                                   if(yAxisTwoRef.max > actualY2Max)
                                                   {
                                                       yAxisTwoRef.max = actualY2Max;
                                                   }
                                               }
                                               if(yAxisTwoRef.min >= actualY2Min)
                                               {
                                                   yAxisTwoRef.min = yAxisTwoRef.min - ((actualY2Max - actualY2Min) * tenPercZoomFactor);
                                                   if(yAxisTwoRef.min < actualY2Min)
                                                   {
                                                       yAxisTwoRef.min = actualY2Min;
                                                   }
                                               }
                                           }
                                           lastDistance = distX
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    min:
                    {
                        if(freqMinVal === freqMaxVal)
                        {
                            freqMinVal = 19450
                            freqMaxVal = 20450
                            return freqMinVal
                        }

                        else
                            return freqMinVal
                    }

                    max: freqMaxVal
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
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
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: currentMinVal// 0
                    max: currentMaxVal// 120
                    tickCount: qmlTextTickCount_Y_Axis
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
                    min: energyMinVal// 0
                    max: energyMaxVal// 50
                    tickCount: qmlTextTickCount_Y_Axis
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
                    min: forceMinVal//0
                    max: forceMaxVal//120
                    tickCount: qmlTextTickCount_Y_Axis
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
                    min: absoluteDistMinVal// 0
                    max: absoluteDistMaxVal//120
                    tickCount: qmlTextTickCount_Y_Axis
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
                    min: collapseDistMinVal//-5
                    max: collapseDistMaxVal//5
                    tickCount: qmlTextTickCount_Y_Axis
                }

                ValueAxis
                {
                    id: reqAmpLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
                    visible: isReqAmpLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.REQAMP_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.REQAMP_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: reqAmpMinVal
                    max: reqAmpMaxVal
                    tickCount: qmlTextTickCount_Y_Axis
                }


                ValueAxis
                {
                    id: velocitylLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: isVelocityLeftAxisVisible
                    gridVisible: false
                    labelsVisible: true
                    labelsFont.family: Style.regular.name
                    labelsFont.pixelSize: fontsize
                    labelsColor: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    lineVisible: true
                    minorGridVisible: false
                    titleText: AxisDefine.getAxisTitle(GraphAxisEnum.VELOCITY_IDX) + " " + AxisDefine.getUnitsTitle(GraphAxisEnum.VELOCITY_IDX)
                    titleFont.family: Style.regular.name
                    titleFont.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    titleVisible: true
                    labelFormat: "%.0f"
                    min: velocityMinVal
                    max: velocityMaxVal
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
                        toolTip.y = p.y + 500
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
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.ENERGY_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = energyLeftAxisPlot.at(0);
                        for(var i = 1; i < energyLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > energyLeftAxisPlot.at(i).x)
                                minX = energyLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = energyLeftAxisPlot.at(0);
                        for(var i = 1; i < energyLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < energyLeftAxisPlot.at(i).x)
                                maxX = energyLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < energyLeftAxisPlot.count; ++i)
                        {
                            if (xValue == energyLeftAxisPlot.at(i).x)
                            {
                                return energyLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < energyLeftAxisPlot.at(i).x && energyLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = energyLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > energyLeftAxisPlot.at(i).x && energyLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = energyLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

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
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.FORCE_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = forceLeftAxisPlot.at(0);
                        for(var i = 1; i < forceLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > forceLeftAxisPlot.at(i).x)
                                minX = forceLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = forceLeftAxisPlot.at(0);
                        for(var i = 1; i < forceLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < forceLeftAxisPlot.at(i).x)
                                maxX = forceLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < forceLeftAxisPlot.count; ++i)
                        {
                            if (xValue == forceLeftAxisPlot.at(i).x)
                            {
                                return forceLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < forceLeftAxisPlot.at(i).x && forceLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = forceLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > forceLeftAxisPlot.at(i).x && forceLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = forceLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

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
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.ABSOLUTEDIST_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = absoluteDistLeftAxisPlot.at(0);
                        for(var i = 1; i < absoluteDistLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > absoluteDistLeftAxisPlot.at(i).x)
                                minX = absoluteDistLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = absoluteDistLeftAxisPlot.at(0);
                        for(var i = 1; i < absoluteDistLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < absoluteDistLeftAxisPlot.at(i).x)
                                maxX = absoluteDistLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < absoluteDistLeftAxisPlot.count; ++i)
                        {
                            if (xValue == absoluteDistLeftAxisPlot.at(i).x)
                            {
                                return absoluteDistLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < absoluteDistLeftAxisPlot.at(i).x && absoluteDistLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = absoluteDistLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > absoluteDistLeftAxisPlot.at(i).x && absoluteDistLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = absoluteDistLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

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
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.COLLAPSEDIST_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = collapseDistLeftAxisPlot.at(0);
                        for(var i = 1; i < collapseDistLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > collapseDistLeftAxisPlot.at(i).x)
                                minX = collapseDistLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = collapseDistLeftAxisPlot.at(0);
                        for(var i = 1; i < collapseDistLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < collapseDistLeftAxisPlot.at(i).x)
                                maxX = collapseDistLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < collapseDistLeftAxisPlot.count; ++i)
                        {
                            if (xValue == collapseDistLeftAxisPlot.at(i).x)
                            {
                                return collapseDistLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < collapseDistLeftAxisPlot.at(i).x && collapseDistLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = collapseDistLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > collapseDistLeftAxisPlot.at(i).x && collapseDistLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = collapseDistLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }


                LineSeries
                {
                    id: reqAmpLeftAxisPlot
                    width: graphChartView.myWidth
                    name: reqAmpLeftPlotName
                    axisX: timeAxis
                    axisY: reqAmpLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
                    visible: (isReqAmpLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Requested Amplitude: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.REQAMP_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = reqAmpLeftAxisPlot.at(0);
                        for(var i = 1; i < reqAmpLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > reqAmpLeftAxisPlot.at(i).x)
                                minX = reqAmpLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = reqAmpLeftAxisPlot.at(0);
                        for(var i = 1; i < reqAmpLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < reqAmpLeftAxisPlot.at(i).x)
                                maxX = reqAmpLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < reqAmpLeftAxisPlot.count; ++i)
                        {
                            if (xValue == reqAmpLeftAxisPlot.at(i).x)
                            {
                                return reqAmpLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < reqAmpLeftAxisPlot.at(i).x && reqAmpLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = reqAmpLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > reqAmpLeftAxisPlot.at(i).x && reqAmpLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = reqAmpLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: velocityLeftAxisPlot
                    width: graphChartView.myWidth
                    name: velocityLeftPlotName
                    axisX: timeAxis
                    axisY: velocitylLeftAxis
                    color: AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: (isVelocityLeftAxisVisible && isGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Velocity: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.VELOCITY_IDX)
                        colorIndicator.color = AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = velocityLeftAxisPlot.at(0);
                        for(var i = 1; i < velocityLeftAxisPlot.count; ++i)
                        {
                            if (minX.x > velocityLeftAxisPlot.at(i).x)
                                minX = velocityLeftAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = velocityLeftAxisPlot.at(0);
                        for(var i = 1; i < velocityLeftAxisPlot.count; ++i)
                        {
                            if (maxX.x < velocityLeftAxisPlot.at(i).x)
                                maxX = velocityLeftAxisPlot.at(i);
                        }

                        return maxX;
                    }

                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < velocityLeftAxisPlot.count; ++i)
                        {
                            if (xValue == velocityLeftAxisPlot.at(i).x)
                            {
                                return velocityLeftAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < velocityLeftAxisPlot.at(i).x && velocityLeftAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = velocityLeftAxisPlot.at(i)
                            }

                            if (xLarger.x > velocityLeftAxisPlot.at(i).x && velocityLeftAxisPlot.at(i).x > xValue)
                            {
                                xLarger = velocityLeftAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }
                /********************************For Golden Graphs LineSeries************************************/

                LineSeries
                {
                    id: goldenAmpAxisPlot
                    width: graphChartView.myWidth
                    name: goldenAmpPlotName
                    axisX: timeAxis
                    axisY: ampLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.AMP_IDX)
                    visible: (isAmpLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Amplitude: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.AMP_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.AMP_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenAmpAxisPlot.at(0);
                        for(var i = 1; i < goldenAmpAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenAmpAxisPlot.at(i).x)
                                minX = goldenAmpAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenAmpAxisPlot.at(0);
                        for(var i = 1; i < goldenAmpAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenAmpAxisPlot.at(i).x)
                                maxX = goldenAmpAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenAmpAxisPlot.count; ++i)
                        {
                            if (xValue == goldenAmpAxisPlot.at(i).x)
                            {
                                return goldenAmpAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenAmpAxisPlot.at(i).x && goldenAmpAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenAmpAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenAmpAxisPlot.at(i).x && goldenAmpAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenAmpAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenPowerAxisPlot
                    width: graphChartView.myWidth
                    name: goldenPowerPlotName
                    axisX: timeAxis
                    axisY: powerLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.POWER_IDX)
                    visible: (isPowerLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Power: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.POWER_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.POWER_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenPowerAxisPlot.at(0);
                        for(var i = 1; i < goldenPowerAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenPowerAxisPlot.at(i).x)
                                minX = goldenPowerAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenPowerAxisPlot.at(0);
                        for(var i = 1; i < goldenPowerAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenPowerAxisPlot.at(i).x)
                                maxX = goldenPowerAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenPowerAxisPlot.count; ++i)
                        {
                            if (xValue == goldenPowerAxisPlot.at(i).x)
                            {
                                return goldenPowerAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenPowerAxisPlot.at(i).x && goldenPowerAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenPowerAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenPowerAxisPlot.at(i).x && goldenPowerAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenPowerAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenFreqAxisPlot
                    width: graphChartView.myWidth
                    name: goldenFreqPlotName
                    axisX: timeAxis
                    axisY: freqLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.FREQ_IDX)
                    visible: (isFreqLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Frequency: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y + 500
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.FREQ_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.FREQ_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenFreqAxisPlot.at(0);
                        for(var i = 1; i < goldenFreqAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenFreqAxisPlot.at(i).x)
                                minX = goldenFreqAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenFreqAxisPlot.at(0);
                        for(var i = 1; i < goldenFreqAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenFreqAxisPlot.at(i).x)
                                maxX = goldenFreqAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenFreqAxisPlot.count; ++i)
                        {
                            if (xValue == goldenFreqAxisPlot.at(i).x)
                            {
                                return goldenFreqAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenFreqAxisPlot.at(i).x && goldenFreqAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenFreqAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenFreqAxisPlot.at(i).x && goldenFreqAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenFreqAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenPhaseAxisPlot
                    width: graphChartView.myWidth
                    name: goldenPhasePlotName
                    axisX: timeAxis
                    axisY: phaseLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.PHASE_IDX)
                    visible: (isPhaseLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Phase: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.PHASE_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.PHASE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenPhaseAxisPlot.at(0);
                        for(var i = 1; i < goldenPhaseAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenPhaseAxisPlot.at(i).x)
                                minX = goldenPhaseAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenPhaseAxisPlot.at(0);
                        for(var i = 1; i < goldenPhaseAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenPhaseAxisPlot.at(i).x)
                                maxX = goldenPhaseAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenPhaseAxisPlot.count; ++i)
                        {
                            if (xValue == goldenPhaseAxisPlot.at(i).x)
                            {
                                return goldenPhaseAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenPhaseAxisPlot.at(i).x && goldenPhaseAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenPhaseAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenPhaseAxisPlot.at(i).x && goldenPhaseAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenPhaseAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenCurrentAxisPlot
                    width: graphChartView.myWidth
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.CURRENT_IDX)
                    name: goldenCurrentPlotName
                    axisX: timeAxis
                    axisY: currentLeftAxis
                    visible: (isCurrentLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Current: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.CURRENT_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.CURRENT_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenCurrentAxisPlot.at(0);
                        for(var i = 1; i < goldenCurrentAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenCurrentAxisPlot.at(i).x)
                                minX = goldenCurrentAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenCurrentAxisPlot.at(0);
                        for(var i = 1; i < goldenCurrentAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenCurrentAxisPlot.at(i).x)
                                maxX = goldenCurrentAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenCurrentAxisPlot.count; ++i)
                        {
                            if (xValue == goldenCurrentAxisPlot.at(i).x)
                            {
                                return goldenCurrentAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenCurrentAxisPlot.at(i).x && goldenCurrentAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenCurrentAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenCurrentAxisPlot.at(i).x && goldenCurrentAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenCurrentAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenEnergyAxisPlot
                    width: graphChartView.myWidth
                    name: goldenEnergyPlotName
                    axisX: timeAxis
                    axisY: energyLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.ENERGY_IDX)
                    visible: (isEnergyLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    useOpenGL: true
                    pointsVisible: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Energy: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.ENERGY_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.ENERGY_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenEnergyAxisPlot.at(0);
                        for(var i = 1; i < goldenEnergyAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenEnergyAxisPlot.at(i).x)
                                minX = goldenEnergyAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenEnergyAxisPlot.at(0);
                        for(var i = 1; i < goldenEnergyAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenEnergyAxisPlot.at(i).x)
                                maxX = goldenEnergyAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenEnergyAxisPlot.count; ++i)
                        {
                            if (xValue == goldenEnergyAxisPlot.at(i).x)
                            {
                                return goldenEnergyAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenEnergyAxisPlot.at(i).x && goldenEnergyAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenEnergyAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenEnergyAxisPlot.at(i).x && goldenEnergyAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenEnergyAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenForceAxisPlot
                    width: graphChartView.myWidth
                    name: goldenForcePlotName
                    axisX: timeAxis
                    axisY: forceLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.FORCE_IDX)
                    visible: (isForceLeftAxisVisible && isGraphEnable  && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Force: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.FORCE_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.FORCE_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenForceAxisPlot.at(0);
                        for(var i = 1; i < goldenForceAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenForceAxisPlot.at(i).x)
                                minX = goldenForceAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenForceAxisPlot.at(0);
                        for(var i = 1; i < goldenForceAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenForceAxisPlot.at(i).x)
                                maxX = goldenForceAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenForceAxisPlot.count; ++i)
                        {
                            if (xValue == goldenForceAxisPlot.at(i).x)
                            {
                                return goldenForceAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenForceAxisPlot.at(i).x && goldenForceAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenForceAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenForceAxisPlot.at(i).x && goldenForceAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenForceAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenAbsoluteDistAxisPlot
                    width: graphChartView.myWidth
                    name: goldenAbsoluteDistPlotName
                    axisX: timeAxis
                    axisY: absoluteDistLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                    visible: (isAbsoluteDistLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Abs.Distance: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.ABSOLUTEDIST_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenAbsoluteDistAxisPlot.at(0);
                        for(var i = 1; i < goldenAbsoluteDistAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenAbsoluteDistAxisPlot.at(i).x)
                                minX = goldenAbsoluteDistAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenAbsoluteDistAxisPlot.at(0);
                        for(var i = 1; i < goldenAbsoluteDistAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenAbsoluteDistAxisPlot.at(i).x)
                                maxX = goldenAbsoluteDistAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenAbsoluteDistAxisPlot.count; ++i)
                        {
                            if (xValue == goldenAbsoluteDistAxisPlot.at(i).x)
                            {
                                return goldenAbsoluteDistAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenAbsoluteDistAxisPlot.at(i).x && goldenAbsoluteDistAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenAbsoluteDistAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenAbsoluteDistAxisPlot.at(i).x && goldenAbsoluteDistAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenAbsoluteDistAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenCollapseDistAxisPlot
                    width: graphChartView.myWidth
                    name: goldenCollapseDistPlotName
                    axisX: timeAxis
                    axisY: reqAmpLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.REQAMP_IDX)
                    visible: (isReqAmpLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Requested Amplitude: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.REQAMP_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.REQAMP_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenCollapseDistAxisPlot.at(0);
                        for(var i = 1; i < goldenCollapseDistAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenCollapseDistAxisPlot.at(i).x)
                                minX = goldenCollapseDistAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenCollapseDistAxisPlot.at(0);
                        for(var i = 1; i < goldenCollapseDistAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenCollapseDistAxisPlot.at(i).x)
                                maxX = goldenCollapseDistAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenCollapseDistAxisPlot.count; ++i)
                        {
                            if (xValue == goldenCollapseDistAxisPlot.at(i).x)
                            {
                                return goldenCollapseDistAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenCollapseDistAxisPlot.at(i).x && goldenCollapseDistAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenCollapseDistAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenCollapseDistAxisPlot.at(i).x && goldenCollapseDistAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenCollapseDistAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenReqAmpAxisPlot
                    width: graphChartView.myWidth
                    name: goldenReqAmpPlotName
                    axisX: timeAxis
                    axisY: collapseDistLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                    visible: (isCollapseDistLeftAxisVisible  && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Col. Distance: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.COLLAPSEDIST_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenReqAmpAxisPlot.at(0);
                        for(var i = 1; i < goldenReqAmpAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenReqAmpAxisPlot.at(i).x)
                                minX = goldenReqAmpAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenReqAmpAxisPlot.at(0);
                        for(var i = 1; i < goldenReqAmpAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenReqAmpAxisPlot.at(i).x)
                                maxX = goldenReqAmpAxisPlot.at(i);
                        }

                        return maxX;
                    }


                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenReqAmpAxisPlot.count; ++i)
                        {
                            if (xValue == goldenReqAmpAxisPlot.at(i).x)
                            {
                                return goldenReqAmpAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenReqAmpAxisPlot.at(i).x && goldenReqAmpAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenReqAmpAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenReqAmpAxisPlot.at(i).x && goldenReqAmpAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenReqAmpAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                LineSeries
                {
                    id: goldenVelocityAxisPlot
                    width: graphChartView.myWidth
                    name: goldenVelocityPlotName
                    axisX: timeAxis
                    axisY: velocitylLeftAxis
                    color: AxisDefine.getRefAxisColor(GraphAxisEnum.VELOCITY_IDX)
                    visible: (isVelocityLeftAxisVisible && isGraphEnable && isReferenceGraphEnable)
                    pointsVisible: true
                    useOpenGL: true
                    onHovered:
                    {
                        var p = graphChartView.mapToPosition(point)
                        var text = qsTr("Velocity: %1").arg(point.y.toFixed(0))
                        toolTip.x = p.x
                        toolTip.y = p.y - toolTip.height
                        graphHeader.text = text + AxisDefine.getUnitsTitle(GraphAxisEnum.VELOCITY_IDX)
                        colorIndicator.color = AxisDefine.getRefAxisColor(GraphAxisEnum.VELOCITY_IDX)
                        toolTip.timeout = toolTipTimeoutValue
                        toolTip.visible = false
                    }

                    function findXMin()
                    {
                        var minX = goldenVelocityAxisPlot.at(0);
                        for(var i = 1; i < goldenVelocityAxisPlot.count; ++i)
                        {
                            if (minX.x > goldenVelocityAxisPlot.at(i).x)
                                minX = goldenVelocityAxisPlot.at(i);
                        }

                        return minX;
                    }

                    function findXMax()
                    {
                        var maxX = goldenVelocityAxisPlot.at(0);
                        for(var i = 1; i < goldenVelocityAxisPlot.count; ++i)
                        {
                            if (maxX.x < goldenVelocityAxisPlot.at(i).x)
                                maxX = goldenVelocityAxisPlot.at(i);
                        }

                        return maxX;
                    }

                    function findY(xValue)
                    {
                        var yValue = 0;
                        var xSmaller = findXMin();
                        var xLarger = findXMax();

                        for(var i = 0; i < goldenVelocityAxisPlot.count; ++i)
                        {
                            if (xValue == goldenVelocityAxisPlot.at(i).x)
                            {
                                return goldenVelocityAxisPlot.at(i).y;
                            }

                            if (xSmaller.x < goldenVelocityAxisPlot.at(i).x && goldenVelocityAxisPlot.at(i).x < xValue)
                            {
                                xSmaller = goldenVelocityAxisPlot.at(i)
                            }

                            if (xLarger.x > goldenVelocityAxisPlot.at(i).x && goldenVelocityAxisPlot.at(i).x > xValue)
                            {
                                xLarger = goldenVelocityAxisPlot.at(i)
                            }
                        }

                        yValue = xSmaller.y + (xValue - xSmaller.x) * (xLarger.y - xSmaller.y) / (xLarger.x - xSmaller.x)

                        return yValue

                    }
                }

                Item
                {
                    id: graphPointItem
                    y: graphChartView.plotArea.y
                    x: graphChartView.plotStartPointX + ((graphChartView.deltaX * (CycleDetailsListModel.TriggerPoint - timeAxis.min)) - graphPointLine.width / 2 )
                    width : graphPointLine.width
                    height : graphPointLine.height
                    visible: GraphSettings.TWHLineDisplay && enableLineVisibility(1);

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

                    Text
                    {
                        id: graphPointLabel
                        visible: true
                        anchors.bottom: graphPointLine.top
                        anchors.bottomMargin: 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: font.pixelSize + 10
                        width : 40
                        horizontalAlignment: Text.AlignHCenter
                        font.family : Style.semibold.name
                        font.pixelSize: Style.style4
                        text: "T"
                        color: "#000000"
                    }
                }

                Item
                {
                    id: graphPointItem2
                    y: graphChartView.plotArea.y
                    x: graphChartView.plotStartPointX + ((graphChartView.deltaX * (CycleDetailsListModel.WeldSonicPoint - timeAxis.min)) - graphPointLine2.width / 2 )
                    width : graphPointLine2.width
                    height : graphPointLine2.height
                    visible: GraphSettings.TWHLineDisplay  && enableLineVisibility(2);

                    Rectangle
                    {
                        id: graphPointLine2
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        border.width: 1
                        height: graphChartView.plotArea.height
                        width:1
                        color: "#000000"
                    }

                    Text
                    {
                        id: graphPointLabel2
                        visible: true
                        anchors.bottom: graphPointLine2.top
                        anchors.bottomMargin: 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: font.pixelSize + 10
                        width : 40
                        horizontalAlignment: Text.AlignHCenter
                        font.family : Style.semibold.name
                        font.pixelSize: Style.style4
                        text: "W"
                        color: "#000000"
                    }
                }

                Item
                {
                    id: graphPointItem3
                    y: graphChartView.plotArea.y
                    x: graphChartView.plotStartPointX + ((graphChartView.deltaX * (CycleDetailsListModel.HoldPoint - timeAxis.min)) - graphPointLine3.width / 2 )
                    width : graphPointLine3.width
                    height : graphPointLine3.height
                    visible: GraphSettings.TWHLineDisplay && enableLineVisibility(3);

                    Rectangle
                    {
                        id: graphPointLine3
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        border.width: 1
                        height: graphChartView.plotArea.height
                        width:1
                        color: "#000000"
                    }

                    Text
                    {
                        id: graphPointLabel3
                        visible: true
                        anchors.bottom: graphPointLine3.top
                        anchors.bottomMargin: 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: font.pixelSize + 10
                        width : 40
                        horizontalAlignment: Text.AlignHCenter
                        font.family : Style.semibold.name
                        font.pixelSize: Style.style4
                        text: "H"
                        color: "#000000"
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
                    width : Math.round(150 * Style.scaleHint)
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
                        width : Math.round(85 * Style.scaleHint)
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
                            property double indexClosest1:0
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
                                var tmpPoint2;

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
                                    reqAmpPoint = 0;
                                    velocityPoint = 0;

                                    /*****************Golden Graphs Points*******************/

                                    tmpPoint = 0;
                                    refAmpPoint = 0 ;
                                    refPowerPoint = 0;
                                    refFreqPoint = 0 ;
                                    refPhasePoint = 0 ;
                                    refCurrPoint = 0 ;
                                    refEnergyPoint = 0;
                                    refForcePoint = 0 ;
                                    refAbsoluteDistPoint = 0 ;
                                    refCollapseDistPoint = 0 ;
                                    refReqAmpPoint = 0;
                                    refVelocityPoint = 0;
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

                                    energyPoint = energyLeftAxisPlot.findY(graphSlider.timeLabel)

                                    forcePoint = forceLeftAxisPlot.findY(graphSlider.timeLabel)

                                    absoluteDistPoint = absoluteDistLeftAxisPlot.findY(graphSlider.timeLabel)

                                    collapseDistPoint = collapseDistLeftAxisPlot.findY(graphSlider.timeLabel)

                                    reqAmpPoint = reqAmpLeftAxisPlot.findY(graphSlider.timeLabel)

                                    velocityPoint = velocityLeftAxisPlot.findY(graphSlider.timeLabel)

                                    yAxisValueUpdated(ampPoint, powerPoint, freqPoint, phasePoint, currPoint, energyPoint, forcePoint,
                                                      absoluteDistPoint, collapseDistPoint, reqAmpPoint, velocityPoint)

                                    /*****************Golden Graphs Points*******************/

                                    tmpPoint2 = goldenAmpAxisPlot.at(indexClosest1);
                                    refTimePoint = tmpPoint2.x;

                                    refAmpPoint = goldenAmpAxisPlot.findY(graphSlider.timeLabel)

                                    refPowerPoint = goldenPowerAxisPlot.findY(graphSlider.timeLabel)

                                    refFreqPoint = goldenFreqAxisPlot.findY(graphSlider.timeLabel)

                                    refPhasePoint = goldenPhaseAxisPlot.findY(graphSlider.timeLabel)

                                    refCurrPoint = goldenCurrentAxisPlot.findY(graphSlider.timeLabel)

                                    refEnergyPoint = goldenEnergyAxisPlot.findY(graphSlider.timeLabel)

                                    refForcePoint = goldenForceAxisPlot.findY(graphSlider.timeLabel)

                                    refAbsoluteDistPoint = goldenAbsoluteDistAxisPlot.findY(graphSlider.timeLabel)

                                    refCollapseDistPoint = goldenCollapseDistAxisPlot.findY(graphSlider.timeLabel)

                                    refReqAmpPoint = goldenReqAmpAxisPlot.findY(graphSlider.timeLabel)

                                    refVelocityPoint = goldenVelocityAxisPlot.findY(graphSlider.timeLabel)

                                    yRefAxisValueUpdated(refAmpPoint, refPowerPoint, refFreqPoint, refPhasePoint, refCurrPoint, refEnergyPoint,
                                                         refForcePoint, refAbsoluteDistPoint, refCollapseDistPoint, refReqAmpPoint, refVelocityPoint)
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
                        text: parent.timeLabelText.toFixed(3) + " " + mainWindow.qmltextTimeUnit
                        color: parent.custColor
                    }
                }
            }
        }
    }
}

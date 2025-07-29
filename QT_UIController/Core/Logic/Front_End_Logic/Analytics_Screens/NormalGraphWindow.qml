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

import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Layouts 1.15
import QtQuick 2.0
import QtCharts 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import "./../Common_Logic"
Item
{
    property double timeMaxValue : GraphSettings.TimeAxisMaxValue
    property double timeMinValue : GraphSettings.TimeAxisMinValue

    property string qmltextCycleNumber               : "Cycle Number"
    property string qmltextSaveAsGolden              : "Save As A Reference Graph"
    property string qmlEmptyText                     : "No Data To Display..!"
    property string qmlCycleDetailsText              : "Cycle Details: "
    property string qmlRecipeText                    : "Recipe: "
    property string qmlRecipeVersionText             : "Recipe Version: "
    property string qmltextRename                    : "Rename"
    property string qmltextDone                      : "Done"
    property string qmltextSelRefGrph                : "Select Reference Graph"

    property string    qmlZoomChartText                 : "Zoom chart: "
    property int firstYAxisDisplayValue: GraphAxisEnum.AMP_IDX
    property int secondYAxisDisplayValue: GraphAxisEnum.POWER_IDX
    property bool isEditing: false
    property bool isVisible: false
    property int graphIndexToRename: -1
    property int leftRectPrevX: 0
    property int rightRectPrevX: 0
    property int currentSelctedGraphComboboxIndex: -1
    property bool isComboboxVisible: false

    property int inputlimitForGraphName: 21
    property var qmlTextArray: [qmltextCycleNumber, qmltextSaveAsGolden, qmlCycleDetailsText, qmlRecipeText, qmlRecipeVersionText,qmlEmptyText,qmltextRename, qmltextDone, qmltextSelRefGrph,qmlZoomChartText]
    property int cycleCountRequested
    property int imageSize: Math.round(20 * Style.scaleHint)

    property bool  visibleFlag: true
    property bool  firstFlag: true
    property int  indexCounter: -1
    property int leftRightClicked: -1
    property int rectDistance: 0
    property int prevX: 0

    signal initiateWeldGraphSignatureDisplay()
    signal updateGraphInitiated()
    signal updateGraphAvailable()
    signal referenceGraphDataChanged()
    signal graphSettingsChanged()
    signal referenceGraphSettingsChanged()

    property int val
    property double doubleVal
    property double axisOneMin
    property double axisOneMax
    property double axisTwoMin
    property double axisTwoMax

    /*Below variable is reponsible to restrict the garbage limitvalue being displayed on Y axis, when there is error in limit range reading.
    Also when ever such scenario occurred, we have seen value which was always bigger than below mentioned value*/
    property int limitVal : -200000
    function copySeries(sourceSeries, targetSeries) {
        targetSeries.clear();
        for (let i = 0; i < sourceSeries.count; ++i) {
            let point = sourceSeries.at(i);
            targetSeries.append(point.x, point.y);
        }
    }

    function getRecipeNumber()
    {
        if(CycleDetailsListModel.RecipeNumber === 0)
        {
            return "NA";
        }
        else
        {
            return CycleDetailsListModel.RecipeNumber;
        }
    }


    function getRecipeVersion()
    {
        if(CycleDetailsListModel.RecipeNumber === 0)
        {
            return "NA";
        }
        else
        {
            return CycleDetailsListModel.RecipeVersion;
        }
    }

    function yAxesUpdate(firstYAxisIndex, secondYAxisIndex)
    {
        firstYAxisDisplayValue = firstYAxisIndex
        secondYAxisDisplayValue = secondYAxisIndex

        chartView.isAmpLeftAxisVisible          = false
        chartView.isPowerLeftAxisVisible        = false
        chartView.isFreqLeftAxisVisible         = false
        chartView.isPhaseLeftAxisVisible        = false
        chartView.isCurrentLeftAxisVisible      = false
        chartView.isEnergyLeftAxisVisible       = false
        chartView.isForceLeftAxisVisible        = false
        chartView.isAbsoluteDistLeftAxisVisible = false
        chartView.isCollapseDistLeftAxisVisible = false
        chartView.isReqAmpLeftAxisVisible       = false
        chartView.isVelocityLeftAxisVisible     = false

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
        case GraphAxisEnum.REQAMP_IDX:
            chartView.isReqAmpLeftAxisVisible = true
            break
        case GraphAxisEnum.VELOCITY_IDX:
            chartView.isVelocityLeftAxisVisible = true
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
        case GraphAxisEnum.REQAMP_IDX:
            chartView.isReqAmpLeftAxisVisible       = true
            break
        case GraphAxisEnum.VELOCITY_IDX:
            chartView.isVelocityLeftAxisVisible     = true
            break
        default:
            break
        }

        rectRight.firstRectColor = AxisDefine.getAxisColor(firstYAxisIndex)
        rectRight.secondRectColor = AxisDefine.getAxisColor(secondYAxisIndex)

        /*****************Golden Graphs Values*******************/

        rectRight.firstRefRectColor = AxisDefine.getRefAxisColor(firstYAxisIndex)
        rectRight.secondRefRectColor = AxisDefine.getRefAxisColor(secondYAxisIndex)
    }

    function getGraphEnableValue(getVal)
    {
        chartView.isGraphEnable = getVal
    }

    function getTimeValue(getVal)
    {
        rectRight.timeValue = getVal
    }

    function getYAxisValues(ampVal, powerVal, freqVal, phaseVal, currentVal, energyVal, forceVal, absVal, colVal , reqAmpVal, velocityVal)
    {
        switch(firstYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:

            val = phaseVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.REQAMP_IDX:

            doubleVal = reqAmpVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        default:
            break
        }

        switch(secondYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:
            val = phaseVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.AMP_IDX:

            doubleVal = reqAmpVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        default:
            break
        }
    }

    /*****************Golden Graphs Values*******************/

    function getYRefAxisValues(ampVal, powerVal, freqVal, phaseVal, currentVal, energyVal, forceVal, absVal, colVal , reqAmpVal, velocityVal)
    {
        switch(firstYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:

            val = phaseVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.REQAMP_IDX:

            doubleVal = reqAmpVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.firstYRefAxisValueText = doubleVal.toFixed(3)
            break

        default:
            break
        }

        switch(secondYAxisDisplayValue)
        {
        case GraphAxisEnum.AMP_IDX:

            val = ampVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.POWER_IDX:

            val = powerVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.FREQ_IDX:

            val = freqVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.PHASE_IDX:
            val = phaseVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.CURRENT_IDX:

            val = currentVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYRefAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < limitVal)
            {
                val = 0
            }

            rectRight.secondYRefAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.AMP_IDX:

            doubleVal = reqAmpVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYRefAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(doubleVal < limitVal)
            {
                doubleVal = 0
            }

            rectRight.secondYRefAxisValueText = doubleVal.toFixed(3)
            break

        default:
            break
        }

    }

    function updateMinAndMaxLimits(firstYAxisIndex, secondYAxisIndex)
    {
        switch(firstYAxisIndex)
        {
        case GraphAxisEnum.AMP_IDX:
            axisOneMin = chartView.ampMinVal
            axisOneMax = chartView.ampMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
            break;
        case GraphAxisEnum.POWER_IDX:
            axisOneMin = chartView.powerMinVal
            axisOneMax = chartView.powerMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
            break
        case GraphAxisEnum.FREQ_IDX:
            axisOneMin = chartView.freqMinVal
            axisOneMax = chartView.freqMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
            break
        case GraphAxisEnum.PHASE_IDX:
            axisOneMin = chartView.phaseMinVal
            axisOneMax = chartView.phaseMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
            break;
        case GraphAxisEnum.CURRENT_IDX:
            axisOneMin = chartView.currentMinVal
            axisOneMax = chartView.currentMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
            break
        case GraphAxisEnum.ENERGY_IDX:
            axisOneMin = chartView.energyMinVal
            axisOneMax = chartView.energyMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
            break
        case GraphAxisEnum.FORCE_IDX:
            axisOneMin = chartView.forceMinVal
            axisOneMax = chartView.forceMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            axisOneMin = chartView.absoluteDistMinVal
            axisOneMax = chartView.absoluteDistMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            axisOneMin = chartView.collapseDistMinVal
            axisOneMax = chartView.collapseDistMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
            break
        case GraphAxisEnum.REQAMP_IDX:
            axisOneMin = chartView.reqAmpMinVal
            axisOneMax = chartView.reqAmpMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
            break
        case GraphAxisEnum.VELOCITY_IDX:
            axisOneMin = chartView.velocityMinVal
            axisOneMax = chartView.velocityMaxVal
            lineSeriesOne.color = AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
            break
        default:
            break
        }
        switch(secondYAxisIndex)
        {
        case GraphAxisEnum.AMP_IDX:
            axisTwoMin = chartView.ampMinVal
            axisTwoMax = chartView.ampMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.AMP_IDX)
            break;
        case GraphAxisEnum.POWER_IDX:
            axisTwoMin = chartView.powerMinVal
            axisTwoMax = chartView.powerMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.POWER_IDX)
            break
        case GraphAxisEnum.FREQ_IDX:
            axisTwoMin = chartView.freqMinVal
            axisTwoMax = chartView.freqMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.FREQ_IDX)
            break
        case GraphAxisEnum.PHASE_IDX:
            axisTwoMin = chartView.phaseMinVal
            axisTwoMax = chartView.phaseMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.PHASE_IDX)
            break;
        case GraphAxisEnum.CURRENT_IDX:
            axisTwoMin = chartView.currentMinVal
            axisTwoMax = chartView.currentMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.CURRENT_IDX)
            break
        case GraphAxisEnum.ENERGY_IDX:
            axisTwoMin = chartView.energyMinVal
            axisTwoMax = chartView.energyMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.ENERGY_IDX)
            break
        case GraphAxisEnum.FORCE_IDX:
            axisTwoMin = chartView.forceMinVal
            axisTwoMax = chartView.forceMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.FORCE_IDX)
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            axisTwoMin = chartView.absoluteDistMinVal
            axisTwoMax = chartView.absoluteDistMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.ABSOLUTEDIST_IDX)
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            axisTwoMin = chartView.collapseDistMinVal
            axisTwoMax = chartView.collapseDistMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.COLLAPSEDIST_IDX)
            break
        case GraphAxisEnum.REQAMP_IDX:
            axisTwoMin = chartView.reqAmpMinVal
            axisTwoMax = chartView.reqAmpMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.REQAMP_IDX)
            break
        case GraphAxisEnum.VELOCITY_IDX:
            axisTwoMin = chartView.velocityMinVal
            axisTwoMax = chartView.velocityMaxVal
            lineSeriesTwo.color = AxisDefine.getAxisColor(GraphAxisEnum.VELOCITY_IDX)
            break
        default:
            break
        }
    }

    QtObject
    {
        id: textEnum
        readonly property int cycleNumberIdx      : 0
        readonly property int saveAsGoldenIdx     : 1
        readonly property int cycleDetailsIdx     : 2
        readonly property int recipeIdx           : 3
        readonly property int recipeVersionIdx    : 4
        readonly property int emptyText           : 5
        readonly property int renameIdx           : 6
        readonly property int doneIdx             : 7
        readonly property int selRefGrphIdx       : 8
        readonly property int zoomChartIdx        : 9
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW, qmlTextArray)
        qmltextCycleNumber = qmlTextArray[textEnum.cycleNumberIdx]
        qmltextSaveAsGolden = qmlTextArray[textEnum.saveAsGoldenIdx]
        qmlCycleDetailsText = qmlTextArray[textEnum.cycleDetailsIdx]
        qmlRecipeText = qmlTextArray[textEnum.recipeIdx]
        qmlRecipeVersionText = qmlTextArray[textEnum.recipeVersionIdx]
        qmlEmptyText = qmlTextArray[textEnum.emptyText]
        qmltextRename = qmlTextArray[textEnum.renameIdx]
        qmltextDone = qmlTextArray[textEnum.doneIdx]
        qmltextSelRefGrph = qmlTextArray[textEnum.selRefGrphIdx]
        qmlZoomChartText = qmlTextArray[textEnum.zoomChartIdx]
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
        target: CycleDetailsListModel
        function onInitiateWeldGraphSignatureDisplay(getCycleCount, value)
        {
            /*chartView.clearGraph()
            WeldGraphObj.clearGraph()*/
            WeldGraphObj.initiateWeldGraphSignature(getCycleCount, value)
            cycleCountRequested = getCycleCount
            weldGraphLoadTimer.start()
        }
    }

    Connections
    {
        target: WeldGraphObj
        function onUpdateGraphInitiated()
        {
            loadingPage.visible = true
            emptySignatureIndicator.visible = false
        }

        function onUpdateGraphAvailable()
        {
            chartView.plotGraph()
            loadingPage.visible = false
            chartView.resetZoom();

            if(WeldGraphObj.isEmptyWeldSignatureReceived())
            {
                emptySignatureIndicator.visible = true
            }

            else
            {
                emptySignatureIndicator.visible = false
            }
        }
    }

    ListModel
    {
        id: referenceGraph
    }

    Connections
    {
        target: ReferenceWeldGraphData

        function onGraphSettingsChanged()
        {
            /*To mailtain min and max time stamp based on reference graph*/
            if (GraphSettings.TimeAxisMinValue <= ReferenceWeldGraphData.TimeAxisMinValue)
            {
                chartView.timeMin = GraphSettings.TimeAxisMinValue
            }

            else
            {
                chartView.timeMin = ReferenceWeldGraphData.TimeAxisMinValue
            }

            if (GraphSettings.TimeAxisMaxValue >= ReferenceWeldGraphData.TimeAxisMaxValue)
            {
                chartView.timeMax = GraphSettings.TimeAxisMaxValue
            }

            else
            {
                chartView.timeMax = ReferenceWeldGraphData.TimeAxisMaxValue
            }

            if (GraphSettings.AmpAxisMinValue <= ReferenceWeldGraphData.AmpAxisMinValue)
            {
                chartView.ampMinVal = GraphSettings.AmpAxisMinValue
            }

            else
            {
                chartView.ampMinVal = ReferenceWeldGraphData.AmpAxisMinValue
            }

            if (GraphSettings.AmpAxisMaxValue >= ReferenceWeldGraphData.AmpAxisMaxValue)
            {
                chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
            }

            else
            {
                chartView.ampMaxVal = ReferenceWeldGraphData.AmpAxisMaxValue
            }

            if (GraphSettings.PowerAxisMinValue <= ReferenceWeldGraphData.PowerAxisMinValue)
            {
                chartView.powerMinVal = GraphSettings.PowerAxisMinValue
            }

            else
            {
                chartView.powerMinVal = ReferenceWeldGraphData.PowerAxisMinValue
            }

            if (GraphSettings.PowerAxisMaxValue >= ReferenceWeldGraphData.PowerAxisMaxValue)
            {
                chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
            }

            else
            {
                chartView.powerMaxVal = ReferenceWeldGraphData.PowerAxisMaxValue
            }

            if (GraphSettings.FreqAxisMinValue <= ReferenceWeldGraphData.FreqAxisMinValue)
            {
                chartView.freqMinVal = GraphSettings.FreqAxisMinValue
            }

            else
            {
                chartView.freqMinVal = ReferenceWeldGraphData.FreqAxisMinValue
            }

            if (GraphSettings.FreqAxisMaxValue >= ReferenceWeldGraphData.FreqAxisMaxValue)
            {
                chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
            }

            else
            {
                chartView.freqMaxVal = ReferenceWeldGraphData.FreqAxisMaxValue
            }

            if (GraphSettings.PhaseAxisMinValue <= ReferenceWeldGraphData.PhaseAxisMinValue)
            {
                chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
            }

            else
            {
                chartView.phaseMinVal = ReferenceWeldGraphData.PhaseAxisMinValue
            }

            if (GraphSettings.PhaseAxisMaxValue >= ReferenceWeldGraphData.PhaseAxisMaxValue)
            {
                chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
            }

            else
            {
                chartView.phaseMaxVal = ReferenceWeldGraphData.PhaseAxisMaxValue
            }

            if (GraphSettings.CurrentAxisMinValue <= ReferenceWeldGraphData.CurrentAxisMinValue)
            {
                chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
            }

            else
            {
                chartView.currentMinVal = ReferenceWeldGraphData.CurrentAxisMinValue
            }

            if (GraphSettings.CurrentAxisMaxValue >= ReferenceWeldGraphData.CurrentAxisMaxValue)
            {
                chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
            }

            else
            {
                chartView.currentMaxVal = ReferenceWeldGraphData.CurrentAxisMaxValue
            }

            if (GraphSettings.EnergyAxisMinValue <= ReferenceWeldGraphData.EnergyAxisMinValue)
            {
                chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
            }

            else
            {
                chartView.energyMinVal = ReferenceWeldGraphData.EnergyAxisMinValue
            }

            if (GraphSettings.EnergyAxisMaxValue >= ReferenceWeldGraphData.EnergyAxisMaxValue)
            {
                chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
            }

            else
            {
                chartView.energyMaxVal = ReferenceWeldGraphData.EnergyAxisMaxValue
            }

            if (GraphSettings.ForceAxisMinValue <= ReferenceWeldGraphData.ForceAxisMinValue)
            {
                chartView.forceMinVal = GraphSettings.ForceAxisMinValue
            }

            else
            {
                chartView.forceMinVal = ReferenceWeldGraphData.ForceAxisMinValue
            }

            if (GraphSettings.ForceAxisMaxValue >= ReferenceWeldGraphData.ForceAxisMaxValue)
            {
                chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
            }

            else
            {
                chartView.forceMaxVal = ReferenceWeldGraphData.ForceAxisMaxValue
            }

            if (GraphSettings.AbsDisAxisMinValue <= ReferenceWeldGraphData.AbsDisAxisMinValue)
            {
                chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
            }

            else
            {
                chartView.absoluteDistMinVal = ReferenceWeldGraphData.AbsDisAxisMinValue
            }

            if (GraphSettings.AbsDisAxisMaxValue >= ReferenceWeldGraphData.AbsDisAxisMaxValue)
            {
                chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
            }

            else
            {
                chartView.absoluteDistMaxVal = ReferenceWeldGraphData.AbsDisAxisMaxValue
            }

            if (GraphSettings.ColDisAxisMinValue <= ReferenceWeldGraphData.ColDisAxisMinValue)
            {
                chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
            }

            else
            {
                chartView.collapseDistMinVal = ReferenceWeldGraphData.ColDisAxisMinValue
            }

            if (GraphSettings.ColDisAxisMaxValue >= ReferenceWeldGraphData.ColDisAxisMaxValue)
            {
                chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
            }

            else
            {
                chartView.collapseDistMaxVal = ReferenceWeldGraphData.ColDisAxisMaxValue
            }

            if (GraphSettings.ReqAmpAxisMinValue <= ReferenceWeldGraphData.ReqAmpAxisMinValue)
            {
                chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
            }

            else
            {
                chartView.reqAmpMinVal = ReferenceWeldGraphData.ReqAmpAxisMinValue
            }

            if (GraphSettings.ReqAmpAxisMaxValue >= ReferenceWeldGraphData.ReqAmpAxisMaxValue)
            {
                chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
            }

            else
            {
                chartView.reqAmpMaxVal = ReferenceWeldGraphData.ReqAmpAxisMaxValue
            }

            if (GraphSettings.VelocityAxisMinValue <= ReferenceWeldGraphData.VelocityAxisMinValue)
            {
                chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
            }

            else
            {
                chartView.velocityMinVal = ReferenceWeldGraphData.VelocityAxisMinValue
            }

            if (GraphSettings.VelocityAxisMaxValue >= ReferenceWeldGraphData.VelocityAxisMaxValue)
            {
                chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue
            }

            else
            {
                chartView.velocityMaxVal = ReferenceWeldGraphData.VelocityAxisMaxValue
            }
        }

        function onReferenceGraphDataChanged()
        {
            referenceGraph.clear()
            if(ReferenceWeldGraphData.availableReferenceGraphSize())
            {
                isComboboxVisible = true
                refGraphStar.visible = true
                refGraphCombobx.visible  =true
            }

            for (var i=0; i<ReferenceWeldGraphData.availableReferenceGraphSize(); ++i)
            {
                var GraphName = ReferenceWeldGraphData.refGraphName(i)
                var Index = ReferenceWeldGraphData.refweldResultIndex(i)
                referenceGraph.append({"GraphName": GraphName, "Index":Index });
            }

            refGraphCombobx.currentIndex = indexCounter
        }
    }


       Connections
    {
        target: GraphSettings

        function onGraphSettingsChanged()
        {
            if(chartView.isReferenceGraphEnable)
            {
                if(ReferenceWeldGraphData.isFirstRequestGenerated())
                {
                    /*To maintain min and max time stamp based on reference graph*/
                    if (GraphSettings.TimeAxisMinValue <= ReferenceWeldGraphData.TimeAxisMinValue)
                    {
                        chartView.timeMin = GraphSettings.TimeAxisMinValue
                    }

                    else
                    {
                        chartView.timeMin = ReferenceWeldGraphData.TimeAxisMinValue
                    }

                    if (GraphSettings.TimeAxisMaxValue >= ReferenceWeldGraphData.TimeAxisMaxValue)
                    {
                        chartView.timeMax = GraphSettings.TimeAxisMaxValue
                    }

                    else
                    {
                        chartView.timeMax = ReferenceWeldGraphData.TimeAxisMaxValue
                    }

                    if (GraphSettings.AmpAxisMinValue <= ReferenceWeldGraphData.AmpAxisMinValue)
                    {
                        chartView.ampMinVal = GraphSettings.AmpAxisMinValue
                    }

                    else
                    {
                        chartView.ampMinVal = ReferenceWeldGraphData.AmpAxisMinValue
                    }

                    if (GraphSettings.AmpAxisMaxValue >= ReferenceWeldGraphData.AmpAxisMaxValue)
                    {
                        chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
                    }

                    else
                    {
                        chartView.ampMaxVal = ReferenceWeldGraphData.AmpAxisMaxValue
                    }

                    if (GraphSettings.PowerAxisMinValue <= ReferenceWeldGraphData.PowerAxisMinValue)
                    {
                        chartView.powerMinVal = GraphSettings.PowerAxisMinValue
                    }

                    else
                    {
                        chartView.powerMinVal = ReferenceWeldGraphData.PowerAxisMinValue
                    }

                    if (GraphSettings.PowerAxisMaxValue >= ReferenceWeldGraphData.PowerAxisMaxValue)
                    {
                        chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
                    }

                    else
                    {
                        chartView.powerMaxVal = ReferenceWeldGraphData.PowerAxisMaxValue
                    }

                    if (GraphSettings.FreqAxisMinValue <= ReferenceWeldGraphData.FreqAxisMinValue)
                    {
                        chartView.freqMinVal = GraphSettings.FreqAxisMinValue
                    }

                    else
                    {
                        chartView.freqMinVal = ReferenceWeldGraphData.FreqAxisMinValue
                    }

                    if (GraphSettings.FreqAxisMaxValue >= ReferenceWeldGraphData.FreqAxisMaxValue)
                    {
                        chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
                    }

                    else
                    {
                        chartView.freqMaxVal = ReferenceWeldGraphData.FreqAxisMaxValue
                    }

                    if (GraphSettings.PhaseAxisMinValue <= ReferenceWeldGraphData.PhaseAxisMinValue)
                    {
                        chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
                    }

                    else
                    {
                        chartView.phaseMinVal = ReferenceWeldGraphData.PhaseAxisMinValue
                    }

                    if (GraphSettings.PhaseAxisMaxValue >= ReferenceWeldGraphData.PhaseAxisMaxValue)
                    {
                        chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
                    }

                    else
                    {
                        chartView.phaseMaxVal = ReferenceWeldGraphData.PhaseAxisMaxValue
                    }

                    if (GraphSettings.CurrentAxisMinValue <= ReferenceWeldGraphData.CurrentAxisMinValue)
                    {
                        chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
                    }

                    else
                    {
                        chartView.currentMinVal = ReferenceWeldGraphData.CurrentAxisMinValue
                    }

                    if (GraphSettings.CurrentAxisMaxValue >= ReferenceWeldGraphData.CurrentAxisMaxValue)
                    {
                        chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
                    }

                    else
                    {
                        chartView.currentMaxVal = ReferenceWeldGraphData.CurrentAxisMaxValue
                    }

                    if (GraphSettings.EnergyAxisMinValue <= ReferenceWeldGraphData.EnergyAxisMinValue)
                    {
                        chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
                    }

                    else
                    {
                        chartView.energyMinVal = ReferenceWeldGraphData.EnergyAxisMinValue
                    }

                    if (GraphSettings.EnergyAxisMaxValue >= ReferenceWeldGraphData.EnergyAxisMaxValue)
                    {
                        chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
                    }

                    else
                    {
                        chartView.energyMaxVal = ReferenceWeldGraphData.EnergyAxisMaxValue
                    }

                    if (GraphSettings.ForceAxisMinValue <= ReferenceWeldGraphData.ForceAxisMinValue)
                    {
                        chartView.forceMinVal = GraphSettings.ForceAxisMinValue
                    }

                    else
                    {
                        chartView.forceMinVal = ReferenceWeldGraphData.ForceAxisMinValue
                    }

                    if (GraphSettings.ForceAxisMaxValue >= ReferenceWeldGraphData.ForceAxisMaxValue)
                    {
                        chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
                    }

                    else
                    {
                        chartView.forceMaxVal = ReferenceWeldGraphData.ForceAxisMaxValue
                    }

                    if (GraphSettings.AbsDisAxisMinValue <= ReferenceWeldGraphData.AbsDisAxisMinValue)
                    {
                        chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
                    }

                    else
                    {
                        chartView.absoluteDistMinVal = ReferenceWeldGraphData.AbsDisAxisMinValue
                    }

                    if (GraphSettings.AbsDisAxisMaxValue >= ReferenceWeldGraphData.AbsDisAxisMaxValue)
                    {
                        chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
                    }

                    else
                    {
                        chartView.absoluteDistMaxVal = ReferenceWeldGraphData.AbsDisAxisMaxValue
                    }

                    if (GraphSettings.ColDisAxisMinValue <= ReferenceWeldGraphData.ColDisAxisMinValue)
                    {
                        chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
                    }

                    else
                    {
                        chartView.collapseDistMinVal = ReferenceWeldGraphData.ColDisAxisMinValue
                    }

                    if (GraphSettings.ColDisAxisMaxValue >= ReferenceWeldGraphData.ColDisAxisMaxValue)
                    {
                        chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
                    }

                    else
                    {
                        chartView.collapseDistMaxVal = ReferenceWeldGraphData.ColDisAxisMaxValue
                    }

                    if (GraphSettings.ReqAmpAxisMinValue <= ReferenceWeldGraphData.ReqAmpAxisMinValue)
                    {
                        chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
                    }

                    else
                    {
                        chartView.reqAmpMinVal = ReferenceWeldGraphData.ReqAmpAxisMinValue
                    }

                    if (GraphSettings.ReqAmpAxisMaxValue >= ReferenceWeldGraphData.ReqAmpAxisMaxValue)
                    {
                        chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
                    }

                    else
                    {
                        chartView.reqAmpMaxVal = ReferenceWeldGraphData.ReqAmpAxisMaxValue
                    }

                    if (GraphSettings.VelocityAxisMinValue <= ReferenceWeldGraphData.VelocityAxisMinValue)
                    {
                        chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
                    }

                    else
                    {
                        chartView.velocityMinVal = ReferenceWeldGraphData.VelocityAxisMinValue
                    }

                    if (GraphSettings.VelocityAxisMaxValue >= ReferenceWeldGraphData.VelocityAxisMaxValue)
                    {
                        chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue
                    }

                    else
                    {
                        chartView.velocityMaxVal = ReferenceWeldGraphData.VelocityAxisMaxValue
                    }
                }
            }

            else
            {
                chartView.timeMin = GraphSettings.TimeAxisMinValue
                chartView.timeMax = GraphSettings.TimeAxisMaxValue

                chartView.ampMinVal = GraphSettings.AmpAxisMinValue
                chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
                chartView.powerMinVal = GraphSettings.PowerAxisMinValue
                chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
                chartView.freqMinVal = GraphSettings.FreqAxisMinValue
                chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
                chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
                chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
                chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
                chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
                chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
                chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
                chartView.forceMinVal = GraphSettings.ForceAxisMinValue
                chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
                chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
                chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
                chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
                chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
                chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
                chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
                chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
                chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue
            }
        }

        function onReferenceGraphSettingsChanged()
        {
            /*Get back to original limit values once auto scale settings changed*/
            chartView.timeMin = GraphSettings.TimeAxisMinValue
            chartView.timeMax = GraphSettings.TimeAxisMaxValue

            chartView.ampMinVal = GraphSettings.AmpAxisMinValue
            chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
            chartView.powerMinVal = GraphSettings.PowerAxisMinValue
            chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
            chartView.freqMinVal = GraphSettings.FreqAxisMinValue
            chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
            chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
            chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
            chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
            chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
            chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
            chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
            chartView.forceMinVal = GraphSettings.ForceAxisMinValue
            chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
            chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
            chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
            chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
            chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
            chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
            chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
            chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
            chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue

            /*Only if valid reference graph selected*/
            if(refGraphCombobx.currentIndex >= 0)
            {
                ReferenceWeldGraphData.setReferenceWeldSignatureRequest(indexCounter)
            }
        }
    }

    Component.onCompleted:
    {
        /*To reinitiate weldgraph signature read request*/
        updateLanguage()
        CycleDetailsListModel.isScreenReNavigated(true)
        CycleDetailtablemodel.loadTableViewDetailsList();
        rectRight.axisChanged.connect(updateMinAndMaxLimits)
        rectRight.axisChanged.connect(yAxesUpdate)
        rectRight.axisChanged.connect(chartView.updateYAxisRef)
        rectRight.isGraphEnableChanged.connect(getGraphEnableValue)
        chartView.timeValueUpdated.connect(getTimeValue)
        chartView.yAxisValueUpdated.connect(getYAxisValues)
        chartView.yRefAxisValueUpdated.connect(getYRefAxisValues)

        /*Initially no refernce graph shall be visible*/
        chartView.isReferenceGraphEnable = false


        chartView.resetZoom();
    }

    /*BransonPrimaryButton
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
    }*/

    InputPanel
    {
        id: inputPanelRenameKeyboard
        z: 1
        height: parent.height
        width: parent.width
        visible: Qt.inputMethod.visible
        anchors.bottom: parent.bottom
    }

    CycleDetailsList
    {
        id: cycleDetailsList
        anchors.top:parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.left: parent.left
        width: Math.round(125 * Style.scaleHint)
        height: parent.height
    }

    Image
    {
        id: refGraphStar
        visible: isComboboxVisible
        source: "qrc:/Images/star_icon.svg"
        width: Math.round(11 * Style.scaleHint)
        height: Math.round(11 * Style.scaleHint)
        anchors.left: cycleDetailsList.right
        anchors.leftMargin:  parent.width*0.05
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        sourceSize.width: graphImage.width
        sourceSize.height: graphImage.height
        smooth: true
    }

    BransonComboBox
    {
        id: refGraphCombobx
        visible: isComboboxVisible
        z: 1
        currentIndex: -1
        anchors.left: refGraphStar.right
        anchors.leftMargin: Math.round(12 * Style.scaleHint)
        anchors.top: parent.top
        minWidth: Math.round(175 * Style.scaleHint)
        minHeight: Math.round(25 * Style.scaleHint)
        textFontSize :Math.round(12* Style.scaleHint)
        model: referenceGraph

        Label
        {
            id: graphdisplayLabel
            Layout.fillWidth: refGraphCombobx
            anchors.left: refGraphCombobx.left
            anchors.leftMargin: refGraphCombobx.width*0.05
            anchors.top: refGraphCombobx.top
            anchors.topMargin: refGraphCombobx.height*0.30
            font.pixelSize: refGraphCombobx.height*0.40
            textFormat: Text.RichText
            clip: true
            text: qmltextSelRefGrph
        }

        onCurrentIndexChanged:
        {
            if(currentIndex != -1)
            {
                /*To initiate display of reference graph on screen based on current selected graph from
                avalable reference graph list*/
                ReferenceWeldGraphData.setReferenceWeldSignatureRequest(currentIndex)
                indexCounter = currentIndex

                renameButton.visible = true
                doneButton.visible = false
                renamerect.visible = false
                editTextInput.text = referenceGraph.get(currentIndex).GraphName
                graphdisplayLabel.text = referenceGraph.get(currentIndex).GraphName
                graphIndexToRename = referenceGraph.get(currentIndex).Index
                currentSelctedGraphComboboxIndex = currentIndex
                chartView.isReferenceGraphEnable = true
                rectRight.isReferenceGraphEnable = true
                visibleFlag = true
                visibleIcon.source = "qrc:/Images/OpenEye.png"
            }

            else
            {
                chartView.isReferenceGraphEnable = false
                rectRight.isReferenceGraphEnable = false
                visibleFlag = false
                visibleIcon.source = "qrc:/Images/HiddenEye.png"
            }
        }

        delegate: Item
        {
            width: refGraphCombobx.width
            height: refGraphCombobx.height*0.85

            Rectangle
            {
                width:parent.width
                height: parent.height
                border.color: "black"

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        refGraphCombobx.currentIndex = index
                        refGraphCombobx.popup.visible = false
                    }

                    hoverEnabled: true
                    onEntered:
                    {
                        parent.color = "lightblue"
                    }

                    onExited:
                    {
                        parent.color = "transparent"
                    }

                    ColumnLayout
                    {
                        anchors.left: parent.left
                        anchors.leftMargin: refGraphCombobx.width*0.05
                        anchors.top: parent.top
                        anchors.topMargin: refGraphCombobx.height*0.15
                        spacing: 2

                        Text
                        {
                            id: welderNameCmbx
                            text: model.GraphName
                            font.pixelSize: refGraphCombobx.height*0.40
                        }
                    }
                }
            }
        }
    }

    Image
    {
        id: visibleIcon
        visible: (refGraphCombobx.currentIndex != -1)
        anchors.left: (!(renameButton.visible || doneButton.visible)) ? refGraphCombobx.right : renameButton.right
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: refGraphCombobx.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        source: "qrc:/Images/OpenEye.png" /*: "qrc:/Images/HiddenEye.png"*/
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
                    /*To maintain min and max time stamp based on visiblity of reference graph*/
                    chartView.timeMin = GraphSettings.TimeAxisMinValue
                    chartView.timeMax = GraphSettings.TimeAxisMaxValue

                    chartView.ampMinVal = GraphSettings.AmpAxisMinValue
                    chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
                    chartView.powerMinVal = GraphSettings.PowerAxisMinValue
                    chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
                    chartView.freqMinVal = GraphSettings.FreqAxisMinValue
                    chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
                    chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
                    chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
                    chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
                    chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
                    chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
                    chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
                    chartView.forceMinVal = GraphSettings.ForceAxisMinValue
                    chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
                    chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
                    chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
                    chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
                    chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
                    chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
                    chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
                    chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
                    chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue

                    rectRight.firstRectColor = AxisDefine.getAxisColor(firstYAxisDisplayValue)
                    rectRight.secondRectColor = AxisDefine.getAxisColor(secondYAxisDisplayValue)

                    visibleIcon.source = "qrc:/Images/HiddenEye.png"
                    chartView.isReferenceGraphEnable = false
                    rectRight.isReferenceGraphEnable = false
                    visibleFlag = false
                }

                else
                {
                    /*To maintain min and max time stamp based on reference graph*/
                    if (GraphSettings.TimeAxisMinValue <= ReferenceWeldGraphData.TimeAxisMinValue)
                    {
                        chartView.timeMin = GraphSettings.TimeAxisMinValue
                    }

                    else
                    {
                        chartView.timeMin = ReferenceWeldGraphData.TimeAxisMinValue
                    }

                    if (GraphSettings.TimeAxisMaxValue >= ReferenceWeldGraphData.TimeAxisMaxValue)
                    {
                        chartView.timeMax = GraphSettings.TimeAxisMaxValue
                    }

                    else
                    {
                        chartView.timeMax = ReferenceWeldGraphData.TimeAxisMaxValue
                    }

                    if (GraphSettings.AmpAxisMinValue <= ReferenceWeldGraphData.AmpAxisMinValue)
                    {
                        chartView.ampMinVal = GraphSettings.AmpAxisMinValue
                    }

                    else
                    {
                        chartView.ampMinVal = ReferenceWeldGraphData.AmpAxisMinValue
                    }

                    if (GraphSettings.AmpAxisMaxValue >= ReferenceWeldGraphData.AmpAxisMaxValue)
                    {
                        chartView.ampMaxVal = GraphSettings.AmpAxisMaxValue
                    }

                    else
                    {
                        chartView.ampMaxVal = ReferenceWeldGraphData.AmpAxisMaxValue
                    }

                    if (GraphSettings.PowerAxisMinValue <= ReferenceWeldGraphData.PowerAxisMinValue)
                    {
                        chartView.powerMinVal = GraphSettings.PowerAxisMinValue
                    }

                    else
                    {
                        chartView.powerMinVal = ReferenceWeldGraphData.PowerAxisMinValue
                    }

                    if (GraphSettings.PowerAxisMaxValue >= ReferenceWeldGraphData.PowerAxisMaxValue)
                    {
                        chartView.powerMaxVal = GraphSettings.PowerAxisMaxValue
                    }

                    else
                    {
                        chartView.powerMaxVal = ReferenceWeldGraphData.PowerAxisMaxValue
                    }

                    if (GraphSettings.FreqAxisMinValue <= ReferenceWeldGraphData.FreqAxisMinValue)
                    {
                        chartView.freqMinVal = GraphSettings.FreqAxisMinValue
                    }

                    else
                    {
                        chartView.freqMinVal = ReferenceWeldGraphData.FreqAxisMinValue
                    }

                    if (GraphSettings.FreqAxisMaxValue >= ReferenceWeldGraphData.FreqAxisMaxValue)
                    {
                        chartView.freqMaxVal = GraphSettings.FreqAxisMaxValue
                    }

                    else
                    {
                        chartView.freqMaxVal = ReferenceWeldGraphData.FreqAxisMaxValue
                    }

                    if (GraphSettings.PhaseAxisMinValue <= ReferenceWeldGraphData.PhaseAxisMinValue)
                    {
                        chartView.phaseMinVal = GraphSettings.PhaseAxisMinValue
                    }

                    else
                    {
                        chartView.phaseMinVal = ReferenceWeldGraphData.PhaseAxisMinValue
                    }

                    if (GraphSettings.PhaseAxisMaxValue >= ReferenceWeldGraphData.PhaseAxisMaxValue)
                    {
                        chartView.phaseMaxVal = GraphSettings.PhaseAxisMaxValue
                    }

                    else
                    {
                        chartView.phaseMaxVal = ReferenceWeldGraphData.PhaseAxisMaxValue
                    }

                    if (GraphSettings.CurrentAxisMinValue <= ReferenceWeldGraphData.CurrentAxisMinValue)
                    {
                        chartView.currentMinVal = GraphSettings.CurrentAxisMinValue
                    }

                    else
                    {
                        chartView.currentMinVal = ReferenceWeldGraphData.CurrentAxisMinValue
                    }

                    if (GraphSettings.CurrentAxisMaxValue >= ReferenceWeldGraphData.CurrentAxisMaxValue)
                    {
                        chartView.currentMaxVal = GraphSettings.CurrentAxisMaxValue
                    }

                    else
                    {
                        chartView.currentMaxVal = ReferenceWeldGraphData.CurrentAxisMaxValue
                    }

                    if (GraphSettings.EnergyAxisMinValue <= ReferenceWeldGraphData.EnergyAxisMinValue)
                    {
                        chartView.energyMinVal = GraphSettings.EnergyAxisMinValue
                    }

                    else
                    {
                        chartView.energyMinVal = ReferenceWeldGraphData.EnergyAxisMinValue
                    }

                    if (GraphSettings.EnergyAxisMaxValue >= ReferenceWeldGraphData.EnergyAxisMaxValue)
                    {
                        chartView.energyMaxVal = GraphSettings.EnergyAxisMaxValue
                    }

                    else
                    {
                        chartView.energyMaxVal = ReferenceWeldGraphData.EnergyAxisMaxValue
                    }

                    if (GraphSettings.ForceAxisMinValue <= ReferenceWeldGraphData.ForceAxisMinValue)
                    {
                        chartView.forceMinVal = GraphSettings.ForceAxisMinValue
                    }

                    else
                    {
                        chartView.forceMinVal = ReferenceWeldGraphData.ForceAxisMinValue
                    }

                    if (GraphSettings.ForceAxisMaxValue >= ReferenceWeldGraphData.ForceAxisMaxValue)
                    {
                        chartView.forceMaxVal = GraphSettings.ForceAxisMaxValue
                    }

                    else
                    {
                        chartView.forceMaxVal = ReferenceWeldGraphData.ForceAxisMaxValue
                    }

                    if (GraphSettings.AbsDisAxisMinValue <= ReferenceWeldGraphData.AbsDisAxisMinValue)
                    {
                        chartView.absoluteDistMinVal = GraphSettings.AbsDisAxisMinValue
                    }

                    else
                    {
                        chartView.absoluteDistMinVal = ReferenceWeldGraphData.AbsDisAxisMinValue
                    }

                    if (GraphSettings.AbsDisAxisMaxValue >= ReferenceWeldGraphData.AbsDisAxisMaxValue)
                    {
                        chartView.absoluteDistMaxVal = GraphSettings.AbsDisAxisMaxValue
                    }

                    else
                    {
                        chartView.absoluteDistMaxVal = ReferenceWeldGraphData.AbsDisAxisMaxValue
                    }

                    if (GraphSettings.ColDisAxisMinValue <= ReferenceWeldGraphData.ColDisAxisMinValue)
                    {
                        chartView.collapseDistMinVal = GraphSettings.ColDisAxisMinValue
                    }

                    else
                    {
                        chartView.collapseDistMinVal = ReferenceWeldGraphData.ColDisAxisMinValue
                    }

                    if (GraphSettings.ColDisAxisMaxValue >= ReferenceWeldGraphData.ColDisAxisMaxValue)
                    {
                        chartView.collapseDistMaxVal = GraphSettings.ColDisAxisMaxValue
                    }

                    else
                    {
                        chartView.collapseDistMaxVal = ReferenceWeldGraphData.ColDisAxisMaxValue
                    }

                    if (GraphSettings.ReqAmpAxisMinValue <= ReferenceWeldGraphData.ReqAmpAxisMinValue)
                    {
                        chartView.reqAmpMinVal = GraphSettings.ReqAmpAxisMinValue
                    }

                    else
                    {
                        chartView.reqAmpMinVal = ReferenceWeldGraphData.ReqAmpAxisMinValue
                    }

                    if (GraphSettings.ReqAmpAxisMaxValue >= ReferenceWeldGraphData.ReqAmpAxisMaxValue)
                    {
                        chartView.reqAmpMaxVal = GraphSettings.ReqAmpAxisMaxValue
                    }

                    else
                    {
                        chartView.reqAmpMaxVal = ReferenceWeldGraphData.ReqAmpAxisMaxValue
                    }

                    if (GraphSettings.VelocityAxisMinValue <= ReferenceWeldGraphData.VelocityAxisMinValue)
                    {
                        chartView.velocityMinVal = GraphSettings.VelocityAxisMinValue
                    }

                    else
                    {
                        chartView.velocityMinVal = ReferenceWeldGraphData.VelocityAxisMinValue
                    }

                    if (GraphSettings.VelocityAxisMaxValue >= ReferenceWeldGraphData.VelocityAxisMaxValue)
                    {
                        chartView.velocityMaxVal = GraphSettings.VelocityAxisMaxValue
                    }

                    else
                    {
                        chartView.velocityMaxVal = ReferenceWeldGraphData.VelocityAxisMaxValue
                    }

                    rectRight.firstRefRectColor = AxisDefine.getRefAxisColor(firstYAxisDisplayValue)
                    rectRight.secondRefRectColor = AxisDefine.getRefAxisColor(secondYAxisDisplayValue)

                    visibleIcon.source = "qrc:/Images/OpenEye.png"
//                    if(refGraphCombobx.currentIndex != -1)
                    chartView.isReferenceGraphEnable = true
                    rectRight.isReferenceGraphEnable = true
                    visibleFlag = true
                }
            }
        }
    }

    Rectangle
    {
        id: renamerect
        z: 1
        anchors.left:refGraphStar.right
        anchors.leftMargin: Math.round(12 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        width:  Math.round(175 * Style.scaleHint)
        height: Math.round(25 * Style.scaleHint)
        visible: false


        TextField
        {
            id: editTextInput
            anchors.fill: parent
            text: refGraphCombobx.currentText
            font.pixelSize: Math.round(12 * Style.scaleHint)
            mouseSelectionMode: TextInput.SelectCharacters
            focus: true
            selectByMouse: true
            onTextChanged:
            {
                if (length > inputlimitForGraphName) remove(inputlimitForGraphName, length)

             graphdisplayLabel.text  =  editTextInput.text
            }
            onActiveFocusChanged:
            {
                Qt.inputMethod.hide()
                if(activeFocus)
                {
                    inputPanelRenameKeyboard.visible = true
                }
                else
                {
                    inputPanelRenameKeyboard.visible = false
                }
            }
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                editTextInput.focus = true
                inputPanelRenameKeyboard.visible = true
               // Qt.inputMethod.hide()
            }
        }
    }

    BransonPrimaryButton
    {
        id: renameButton
        visible: false
        text: qmltextRename
        anchors.left: refGraphCombobx.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: refGraphCombobx.verticalCenter
        font.family: Style.regular.name
        buttonColor: Style.blueFontColor
        textColor: "#FFFFFF"

        onClicked:
        {
            editTextInput.focus = true
            inputPanelRenameKeyboard.visible = true

            renameButton.visible = false
            doneButton.visible = true
            renamerect.visible = true
        }
    }

    BransonPrimaryButton
    {
        id: doneButton
        enabled: (editTextInput.text !== "") ? true : false
        text: qmltextDone
        anchors.left: refGraphCombobx.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: refGraphCombobx.verticalCenter
        font.family: Style.regular.name
        buttonColor: (editTextInput.text !== "") ? Style.blueFontColor : Style.disabledButtonBackgroundColor
        textColor: "#FFFFFF"
        visible:  isEditing
        z:1

        onClicked:
        {
            doneButton.visible = false
            renameButton.visible = true
            renamerect.visible = false
            if(editTextInput.text !== "")
            {
                ReferenceWeldGraphData.addReferenceGraphNameChangeRequest(graphIndexToRename, editTextInput.text)
            }
            editTextInput.text = ""
            editTextInput.focus = false
            inputPanelRenameKeyboard.visible = false
            Qt.inputMethod.hide()
            refGraphCombobx.currentIndex = indexCounter
        }
    }

    Rectangle
    {
        id: graphFrame
        width: parent.width * 0.70
        height: parent.height * 0.83
        anchors.top: refGraphStar.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.left: cycleDetailsList.right
        anchors.leftMargin: Math.round(15 * Style.scaleHint)
        border.color: "#707070"
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
                height: Math.round(25 * Style.scaleHint)
                spacing: Math.round(2 * Style.scaleHint)
                Rectangle
                {
                    id: graphBtn
                    width: parent.width/2
                    height: parent.height
                    border.width: 1
                    border.color: Style.frameBorderColor
                    radius: 2

                    Image
                    {
                        id: graphImage
                        source: "qrc:/Images/Graph.svg"
                        width: Math.round(15 * Style.scaleHint)
                        height: Math.round(15 * Style.scaleHint)
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

                    Image
                    {
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
                            mainWindow.menuChildOptionSelect(UIScreenEnum.ANALYTICS, UIScreenEnum.ANALYTICS_RESULT_TABLE_VIEW)
                        }
                    }
                }
            }
            /*Image
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
            }*/

            Rectangle{
                id: rectZoomEnable
                anchors.top: btnArray.top
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.07
                width: parent.width * 0.27
                height: parent.height * 0.70
                radius: width / 2
                color: Style.backgroundColor
                Label{
                    id: lblZoomChart
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.05
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.60
                    height: parent.height / 3
                    text: qmlZoomChartText
                    font.pixelSize: Style.style3
                }

                BransonSwitch{
                    id: enableZoomBtn
                    anchors.left: lblZoomChart.right
                    anchors.rightMargin: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.30
                    height: parent.height / 3
                    onCheckedChanged: {
                        chartView.enableZoom = checked;
                        chartView.resetZoom();
                    }
                }
            }
        }
        BransonChartView
        {
            id: chartView
            visible: ((! loadingPage.visible) && (! emptySignatureIndicator.visible))
            width: parent.width
            anchors.left: chartViewHeader.left
            anchors.top: chartViewHeader.bottom
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

    Rectangle{
        id: rectCycleDetails
        anchors.top: graphFrame.bottom
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.left: graphFrame.left
        anchors.right: graphFrame.right
        height: parent.height * 0.15
        color: Style.backgroundlightBlueColor
        visible: true

        z: 1
        Text{
            id: txtCycleDetails
            visible: !enableZoomBtn.checked
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            text:qmlCycleDetailsText
            font.bold: true
            color: Style.subHeadingTextColor
        }

        Text{
            id: txtRecipe
            visible: !enableZoomBtn.checked
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: txtCycleDetails.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: qmlRecipeText + getRecipeNumber()
            color: Style.subHeadingTextColor
        }
        Text{
            id: txtRecipeVer
            visible: !enableZoomBtn.checked
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: txtRecipe.right
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            text: qmlRecipeVersionText + getRecipeVersion()
            color: Style.subHeadingTextColor
        }

        /* Bottom chart slider*/
        /* New File for chart sliser is implemented here instead of creating
          new file in common logic as the access of variables between bransonChartView from common
          logic and this file along with new file is not possible and complex.*/
        ChartView{
            id: chart
            visible:enableZoomBtn.checked
            property double timeAxisMaxZoomLimit
            property double timeAxisMinZoomLimit
            anchors.fill: parent
            antialiasing: false
            legend.visible: false
            margins.right: 0
            margins.left: 0
            margins.bottom: 0
            margins.top: 0
            LineSeries {
                id:lineSeriesOne
                axisX: axisX
                axisY: axisY
            }
            LineSeries {
                id:lineSeriesTwo
                axisX: axisX
                axisY: axisYTwo
            }
            ValueAxis {
                id: axisX
                gridVisible: false
                labelsVisible: false
                min: timeMinValue
                max: timeMaxValue
            }

            ValueAxis {
                id: axisY
                gridVisible: false
                labelsVisible: false
                min: axisOneMin
                max: axisOneMax
            }
            ValueAxis {
                id: axisYTwo
                gridVisible: false
                labelsVisible: false
                min: axisTwoMin
                max: axisTwoMax
            }
            Rectangle{
                id: startRect
                x: 0
                z:1
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(10 * Style.scaleHint)
                height: parent.height /2
                radius: height /3
                color: "gray"
                border.width: 2
                border.color: "darkGray"
            }

            Rectangle{
                id: endRect
                x: chart.width - width
                z:1
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(10 * Style.scaleHint)
                height: parent.height /2
                radius: height /3
                color: "gray"
                border.width: 2
                border.color: "darkGray"

            }

            Rectangle{
                id: middleRect
                x: startRect.x + (startRect.width/2)
                y:0
                width: endRect.x - startRect.x
                height: parent.height
                color: "#400000FF"
                border.width: 2
                border.color: "darkGray"
            }

            MouseArea{
                id: chartMouseArea
                anchors.fill: parent
                onPositionChanged: (mouse) =>{
                                       if(leftRightClicked === 1)
                                       {
                                           if(mouse.x >= 10 && ((mouse.x + startRect.width) < (endRect.x - 50)))
                                           {
                                               startRect.x = mouse.x + startRect.width;
                                           }
                                           var xRange = chartView.timeMax - chartView.timeMin;
                                           var xStartPoint = startRect.x /chart.width
                                           if(startRect.x > leftRectPrevX)
                                           {
                                               chartView.timeAxisRef.min = chartView.timeMin + (xRange * xStartPoint)
                                               chart.timeAxisMinZoomLimit = chartView.timeAxisRef.min;
                                           }
                                           else
                                           {
                                               chartView.timeAxisRef.min = chartView.timeMin - (xRange * xStartPoint)
                                               chart.timeAxisMinZoomLimit = chartView.timeAxisRef.min;

                                           }
                                           leftRectPrevX = startRect.x;
                                       }
                                       else if(leftRightClicked === 2)
                                       {
                                           if(((mouse.x + endRect.width) < chart.width) && (mouse.x > (startRect.x + startRect.width + 50)))
                                           {
                                               endRect.x = mouse.x+ startRect.width;
                                           }
                                           var xRange = chartView.timeMax - chartView.timeMin;
                                           var xEndPoint = endRect.x /chart.width
                                           chartView.timeAxisRef.max = chartView.timeMax - (xRange - (xRange * xEndPoint))
                                           chart.timeAxisMaxZoomLimit = chartView.timeAxisRef.max
                                           rightRectPrevX = endRect.x;
                                       }
                                       else if(leftRightClicked === 3)
                                       {
                                           var count = Math.abs(mouse.x - prevX)
                                           if((mouse.x > prevX))
                                           {
                                               if((endRect.x + endRect.width) < chart.width)
                                               {
                                                   startRect.x = startRect.x + count;
                                                   endRect.x = endRect.x + count;
                                               }
                                           }
                                           else if((mouse.x < prevX))
                                           {
                                               if(startRect.x > 0)
                                               {
                                                   startRect.x = startRect.x - count;
                                                   endRect.x = endRect.x - count;
                                                   if(startRect.x < 0)
                                                   {
                                                       startRect.x = 1;
                                                   }
                                               }
                                           }

                                           if(rectDistance > (endRect.x - startRect.x))
                                           {
                                               endRect.x = startRect.x + rectDistance
                                           }
                                           if((endRect.x + endRect.width) > chart.width)
                                           {
                                               endRect.x  = chart.width - endRect.width;
                                           }
                                           prevX = mouse.x
                                           var xRange = chartView.timeMax - chartView.timeMin;
                                           var xStartPoint = startRect.x /chart.width
                                           var xEndPoint = endRect.x /chart.width
                                           chartView.timeAxisRef.min = chartView.timeMin + (xRange * xStartPoint)
                                           chartView.timeAxisRef.max = chartView.timeMax - (xRange - (xRange * xEndPoint))
                                           chart.timeAxisMinZoomLimit = chartView.timeAxisRef.min;
                                           chart.timeAxisMaxZoomLimit = chartView.timeAxisRef.max
                                       }
                                   }
                onPressed: (mouse) =>{
                               if(startRect.x <= mouse.x && (startRect.x + startRect.width) >= mouse.x)
                               {
                                   leftRightClicked = 1;
                               }
                               else if(endRect.x <= mouse.x && (endRect.x + endRect.width) >= mouse.x){
                                   leftRightClicked = 2;
                               }
                               else if(startRect.x <= mouse.x && (endRect.x + endRect.width) >= mouse.x)
                               {
                                   rectDistance = endRect.x - startRect.x
                                   prevX = mouse.x;
                                   leftRightClicked = 3;
                               }
                           }
            }

        }

    }

    GraphRightSettings
    {
        id: rectRight
        anchors.top: graphFrame.top
        anchors.bottom: rectCycleDetails.bottom
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)

        anchors.right: parent.right

        onAutoScaleYAxisEnabled:
        {
            /*Get back to original limit values once auto scale settings changed*/
            GraphSettings.AmpAxisMinValue      = GraphSettings.getActualAmpAxisMinValue()
            GraphSettings.AmpAxisMaxValue      = GraphSettings.getActualAmpAxisMaxValue()
            GraphSettings.PowerAxisMinValue    = GraphSettings.getActualPowerAxisMinValue()
            GraphSettings.PowerAxisMaxValue    = GraphSettings.getActualPowerAxisMaxValue()
            GraphSettings.FreqAxisMinValue     = GraphSettings.getActualFreqAxisMinValue()
            GraphSettings.FreqAxisMaxValue     = GraphSettings.getActualFreqAxisMaxValue()
            GraphSettings.PhaseAxisMinValue    = GraphSettings.getActualPhaseAxisMinValue()
            GraphSettings.PhaseAxisMaxValue    = GraphSettings.getActualPhaseAxisMaxValue()
            GraphSettings.CurrentAxisMinValue  = GraphSettings.getActualCurrentAxisMinValue()
            GraphSettings.CurrentAxisMaxValue  = GraphSettings.getActualCurrentAxisMaxValue()
            GraphSettings.EnergyAxisMinValue   = GraphSettings.getActualEnergyAxisMinValue()
            GraphSettings.EnergyAxisMaxValue   = GraphSettings.getActualEnergyAxisMaxValue()
            GraphSettings.ForceAxisMinValue    = GraphSettings.getActualForceAxisMinValue()
            GraphSettings.ForceAxisMaxValue    = GraphSettings.getActualForceAxisMaxValue()
            GraphSettings.AbsDisAxisMinValue   = GraphSettings.getActualAbsDisAxisMinValue()
            GraphSettings.AbsDisAxisMaxValue   = GraphSettings.getActualAbsDisAxisMaxValue()
            GraphSettings.ColDisAxisMinValue   = GraphSettings.getActualColDisAxisMinValue()
            GraphSettings.ColDisAxisMaxValue   = GraphSettings.getActualColDisAxisMaxValue()
            GraphSettings.ReqAmpAxisMinValue   = GraphSettings.getActualVelocityAxisMinValue()
            GraphSettings.ReqAmpAxisMaxValue   = GraphSettings.getActualVelocityAxisMaxValue()
            GraphSettings.VelocityAxisMinValue = GraphSettings.getActualReqAmpAxisMaxValue()
            GraphSettings.VelocityAxisMaxValue = GraphSettings.getActualReqAmpAxisMinValue()

            chartView.ampMinVal          = GraphSettings.getActualAmpAxisMinValue()
            chartView.ampMaxVal          = GraphSettings.getActualAmpAxisMaxValue()
            chartView.powerMinVal        = GraphSettings.getActualPowerAxisMinValue()
            chartView.powerMaxVal        = GraphSettings.getActualPowerAxisMaxValue()
            chartView.freqMinVal         = GraphSettings.getActualFreqAxisMinValue()
            chartView.freqMaxVal         = GraphSettings.getActualFreqAxisMaxValue()
            chartView.phaseMinVal        = GraphSettings.getActualPhaseAxisMinValue()
            chartView.phaseMaxVal        = GraphSettings.getActualPhaseAxisMaxValue()
            chartView.currentMinVal      = GraphSettings.getActualCurrentAxisMinValue()
            chartView.currentMaxVal      = GraphSettings.getActualCurrentAxisMaxValue()
            chartView.energyMinVal       = GraphSettings.getActualEnergyAxisMinValue()
            chartView.energyMaxVal       = GraphSettings.getActualEnergyAxisMaxValue()
            chartView.forceMinVal        = GraphSettings.getActualForceAxisMinValue()
            chartView.forceMaxVal        = GraphSettings.getActualForceAxisMaxValue()
            chartView.absoluteDistMinVal = GraphSettings.getActualAbsDisAxisMinValue()
            chartView.absoluteDistMaxVal = GraphSettings.getActualAbsDisAxisMaxValue()
            chartView.collapseDistMinVal = GraphSettings.getActualColDisAxisMinValue()
            chartView.collapseDistMaxVal = GraphSettings.getActualColDisAxisMaxValue()
            chartView.reqAmpMinVal       = GraphSettings.getActualVelocityAxisMinValue()
            chartView.reqAmpMaxVal       = GraphSettings.getActualVelocityAxisMaxValue()
            chartView.velocityMinVal     = GraphSettings.getActualReqAmpAxisMaxValue()
            chartView.velocityMaxVal     = GraphSettings.getActualReqAmpAxisMinValue()

            /*Only if valid reference graph selected*/
            if(refGraphCombobx.currentIndex >= 0)
            {
                ReferenceWeldGraphData.setReferenceWeldSignatureRequest(indexCounter)
            }
        }


        onAutoScaleTimeAxisEnabled:
        {
            /*Get back to original limit values once auto scale settings changed*/
            GraphSettings.TimeAxisMinValue = GraphSettings.getActualTimeAxisMinValue()
            GraphSettings.TimeAxisMaxValue = GraphSettings.getActualTimeAxisMaxValue()

            chartView.timeMin = GraphSettings.getActualTimeAxisMinValue()
            chartView.timeMax = GraphSettings.getActualTimeAxisMaxValue()

            /*Only if valid reference graph selected*/
            if(refGraphCombobx.currentIndex >= 0)
            {
                ReferenceWeldGraphData.setReferenceWeldSignatureRequest(indexCounter)
            }
        }
    }

    Timer
    {
        id: weldGraphLoadTimer
        interval: 500
        repeat: true
        onTriggered:
        {
            chartView.plotGraph()
            WeldGraphObj.initiateWeldGraphSignature(cycleCountRequested, false)
            copySeries(chartView.lineSeriesOne, lineSeriesOne);
            copySeries(chartView.lineSeriesTwo, lineSeriesTwo);
            firstFlag = false;
        }
    }
}

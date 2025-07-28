/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    recipeLabResultViewGraph.qml file displays graph data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
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
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import "./../Common_Logic"
import "../Analytics_Screens"
Item
{
    property double timeMaxValue : GraphSettings.TimeAxisMaxValue
    property double timeMinValue : GraphSettings.TimeAxisMinValue

    property string qmltextCycleNumber: "Cycle Number"
    property string qmltextSaveAsGolden: "Save As A Golden Graph"
    property string qmlEmptyText: "No Data To Display..!"
    property string    qmlCycleDetailsText              : "Cycle Details: "
    property string    qmlRecipeText                    : "Recipe: "
    property string    qmlRecipeVersionText             : "Recipe Version: "
    property int firstYAxisDisplayValue: GraphAxisEnum.AMP_IDX
    property int secondYAxisDisplayValue: GraphAxisEnum.POWER_IDX
    property bool isEditing: false
    property bool isVisible: false
    property int graphIndexToRename: -1
    property int currentSelctedGraphComboboxIndex: -1
    property bool isComboboxVisible: false

    property string qmltextRename: "Rename"
    property string qmltextDone: "Done"
    property string qmltextSelRefGrph: "Select Reference Graph"

    property var qmlTextArray: [qmltextCycleNumber, qmltextSaveAsGolden, qmlCycleDetailsText, qmlRecipeText, qmlRecipeVersionText, qmlEmptyText, qmltextRename, qmltextDone, qmltextSelRefGrph]
    property int cycleCountRequested
    property int imageSize: Math.round(20 * Style.scaleHint)

    property bool  visibleFlag: true
    property int  indexCounter: -1

    signal initiateWeldGraphSignatureDisplay()
    signal updateGraphInitiated()
    signal updateGraphAvailable()
    signal referenceGraphDataChanged()
    signal graphSettingsChanged()
    signal referenceGraphSettingsChanged()

    property int val
    property double doubleVal
    property bool fullScreenFlag: false

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

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.REQAMP_IDX:

            doubleVal = reqAmpVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.firstYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(val < (-200000))
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

        case GraphAxisEnum.ENERGY_IDX:

            doubleVal = energyVal

            if(doubleVal < (-200000))
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(1)
            break

        case GraphAxisEnum.FORCE_IDX:

            val = forceVal

            if(val < (-200000))
            {
                val = 0
            }

            rectRight.secondYAxisValueText = val
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX:

            doubleVal = absVal

            if(doubleVal < (-200000))
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX:

            doubleVal = colVal

            if(doubleVal < (-200000))
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.AMP_IDX:

            doubleVal = reqAmpVal

            if(doubleVal < (-200000))
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        case GraphAxisEnum.VELOCITY_IDX:

            doubleVal = velocityVal

            if(doubleVal < (-200000))
            {
                doubleVal = 0
            }

            rectRight.secondYAxisValueText = doubleVal.toFixed(3)
            break

        default:
            break
        }

    }

    QtObject
    {
        id: textEnum
        readonly property int cycleNumberIdx                : 0
        readonly property int saveAsGoldenIdx               : 1
        readonly property int cycleDetailsIdx               : 2
        readonly property int recipeIdx                     : 3
        readonly property int recipeVersionIdx              : 4
        readonly property int emptyText                     : 5
        readonly property int textRename                    : 6
        readonly property int textDone                      : 7
        readonly property int textSelRefGrph                : 8
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW, qmlTextArray)
        qmltextCycleNumber = qmlTextArray[textEnum.cycleNumberIdx]
        qmltextSaveAsGolden = qmlTextArray[textEnum.saveAsGoldenIdx]
        qmlCycleDetailsText =qmlTextArray[textEnum.cycleDetailsIdxIdx]
        qmlRecipeText =qmlTextArray[textEnum.recipeIdx]
        qmlRecipeVersionText =qmlTextArray[textEnum.recipeVersionIdx]
        qmlEmptyText =qmlTextArray[textEnum.emptyText]
        qmltextRename =qmlTextArray[textEnum.textRename]
        qmltextDone =qmlTextArray[textEnum.textDone]
        qmltextSelRefGrph =qmlTextArray[textEnum.textSelRefGrph]

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
            }

            for (var i=0; i<ReferenceWeldGraphData.availableReferenceGraphSize(); ++i)
            {
                var GraphName = ReferenceWeldGraphData.refGraphName(i)
                var Index = ReferenceWeldGraphData.refweldResultIndex(i)
                referenceGraph.append({"GraphName": GraphName, "Index":Index });
            }

            if(currentSelctedGraphComboboxIndex != -1)
            {
                welderdisplayLabel.text = referenceGraph.get(currentSelctedGraphComboboxIndex).GraphName
            }
        }
    }


    Connections
    {
        target: GraphSettings

        function onGraphSettingsChanged()
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
        CycleDetailsListModel.isScreenReNavigated(true)
        CycleDetailtablemodel.loadTableViewDetailsList();
        inputPanelRenameKeyboard.visible = false;
        rectRight.axisChanged.connect(yAxesUpdate)
        rectRight.isGraphEnableChanged.connect(getGraphEnableValue)
        chartView.timeValueUpdated.connect(getTimeValue)
        chartView.yAxisValueUpdated.connect(getYAxisValues)

        /*Initially no refernce graph shall be visible*/
        chartView.isReferenceGraphEnable = false

        updateLanguage()
    }

    InputPanel
    {
        id: inputPanelRenameKeyboard
        z: 1
        height: parent.height
        width: parent.width
        visible: Qt.inputMethod.visible
        anchors.bottom: parent.bottom
    }

    Rectangle
    {
        id: graphFrame
        width: parent.width * 0.75
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
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
                            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeLabResultView.qml"
                        }
                    }
                }
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
            }

            Image
            {
                id: fullBtn
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                anchors.top : btnArray.top
                anchors.right: parent.right
                anchors.rightMargin: Math.round(8 * Style.scaleHint)
                source: fullScreenFlag ? "qrc:/Images/Shrink_arrow_icon.svg" : "qrc:/Images/extendArrow.svg"
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
                    fullScreenFlag = !fullScreenFlag
                    if(fullScreenFlag)
                    {
                        rectQuickEdit.visible = false;
                        rectGraphRightSettings.visible = false;
                        graphFrame.width  = mainWindow.width * 0.94
                        subRecipeDetails.anchors.left = recipeLabWindow.left
                        chartView.anchors.right = parent.right
                    }
                    else
                    {
                        rectQuickEdit.visible = true;
                        rectGraphRightSettings.visible = true;
                        subRecipeDetails.anchors.left = rectQuickEdit.right
                        graphFrame.width  = mainWindow.width * 0.50
                        subRecipeDetails.anchors.right = rectGraphRightSettings.left
                        chartView.anchors.right = parent.right
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
        id: rectGraphRightSettings
        visible: true
        anchors.top: graphFrame.top
        anchors.bottom: graphFrame.bottom
        anchors.left: graphFrame.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        RecipeGraphRightSettings
        {
            id: rectRight
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
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
        }
    }
}


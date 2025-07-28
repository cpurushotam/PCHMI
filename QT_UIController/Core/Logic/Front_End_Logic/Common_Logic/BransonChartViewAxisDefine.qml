/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/
pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import Com.Branson.GraphAxisEnum 1.0
Item {
    id: graphAxisDefine

    property string qmltextAmpAxis:             qsTr("Amplitude")
    property string qmltextPowerAxis:           qsTr("Power")
    property string qmltextFreqAxis:            qsTr("Frequency")
    property string qmltextPhaseAxis:           qsTr("Phase")
    property string qmltextCurrentAxis:         qsTr("Current")
    property string qmltextEnergyAxis:          qsTr("Energy")
    property string qmltextForceAxis:           qsTr("Force")
    property string qmltextAbsoluteDistAxis:    qsTr("Abs Distance")
    property string qmltextCollapseDistAxis:    qsTr("Col Distance")
    property string qmltextTimeAxis:            qsTr("Time")
    property string qmltextRequestAmpAxis:      qsTr("Req Amplitude")
    property string qmltextVelocityAxis:        qsTr("Velocity")


    property string qmltextPrecent:             ""
    property string qmltextWatts:               ""
    property string qmltextHertz:               ""
    property string qmltextDegree:              ""
    property string qmltextJoule:               ""
    property string qmltextNewtons:             ""
    property string qmltextMiliMPerSec:         ""
    property string qmltextMiliM:               ""
    property string qmltextSeconds:             ""
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property var qmlTextArray: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis, qmltextEnergyAxis,
        qmltextForceAxis, qmltextAbsoluteDistAxis, qmltextCollapseDistAxis, qmltextRequestAmpAxis, qmltextVelocityAxis, qmltextTimeAxis]

    property var qmlUnitsArray: [qmltextPrecent, qmltextWatts, qmltextHertz, qmltextDegree, qmltextPrecent,qmltextJoule, qmltextNewtons,
        qmltextMiliM, qmltextMiliM, qmltextPrecent, qmltextMiliMPerSec, qmltextSeconds]

    property var qmlTextComboxModelManual: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis, qmltextEnergyAxis]

    property var qmlTextComboxModelElectric: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis, qmltextEnergyAxis,
        qmltextForceAxis,qmltextAbsoluteDistAxis,qmltextCollapseDistAxis,qmltextRequestAmpAxis,qmltextVelocityAxis]

    property var qmlTextScanComboxModel: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis]
    property var qmlTextTestComboxModel: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis]
    property var qmlTextSeekComboxModel: [qmltextAmpAxis, qmltextPowerAxis, qmltextFreqAxis, qmltextPhaseAxis, qmltextCurrentAxis]

    /*Normal graph lists*/
    readonly property color ampAxisColor             : "#F03E3E"
    readonly property color powerAxisColor           : "#A82BA8"
    readonly property color freqAxisColor            : "#4285F4"
    readonly property color phaseAxisColor           : "#000001"
    readonly property color currentAxisColor         : "#009587"
    readonly property color energyAxisColor          : "#F4B400"
    readonly property color forceAxisColor           : "#BF6000"
    readonly property color absoluteDistAxisColor    : "#8BC24A"
    readonly property color collapseDistAxisColor    : "#FF80C0"
    readonly property color reqAmplAxisColor         : "#422323"
    readonly property color velocityAxisColor        : "#524B03"
    readonly property color timeAxisColor            : "#868E96"

    /*Reference graph lists*/
    readonly property color refAmpAxisColor          : "#108382"
    readonly property color refPowerAxisColor        : "#4C7700"
    readonly property color refFreqAxisColor         : "#663300"
    readonly property color refPhaseAxisColor        : "#8A8A88"
    readonly property color refCurrentAxisColor      : "#FF5581"
    readonly property color refEnergyAxisColor       : "#086BD7"
    readonly property color refForceAxisColor        : "#97AEDF"
    readonly property color refAbsoluteDistAxisColor : "#5F3098"
    readonly property color refCollapseDistAxisColor : "#157F03"
    readonly property color refReqAmplAxisColor      : "#BDDCDC"
    readonly property color refVelocityAxisColor     : "#2617F6"
    readonly property color refTimeAxisColor         : "#797169"

    readonly property var colorArray: [ampAxisColor, powerAxisColor, freqAxisColor, phaseAxisColor, currentAxisColor, energyAxisColor,
        forceAxisColor, absoluteDistAxisColor, collapseDistAxisColor, reqAmplAxisColor, velocityAxisColor, timeAxisColor]

    readonly property var refColorArray: [refAmpAxisColor, refPowerAxisColor, refFreqAxisColor, refPhaseAxisColor, refCurrentAxisColor, refEnergyAxisColor,
        refForceAxisColor, refAbsoluteDistAxisColor, refCollapseDistAxisColor, refReqAmplAxisColor, refVelocityAxisColor, refTimeAxisColor]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_AXIS, qmlTextArray)
        qmltextAmpAxis =            qmlTextArray[GraphAxisEnum.AMP_IDX]
        qmltextPowerAxis =          qmlTextArray[GraphAxisEnum.POWER_IDX]
        qmltextFreqAxis =           qmlTextArray[GraphAxisEnum.FREQ_IDX]
        qmltextPhaseAxis =          qmlTextArray[GraphAxisEnum.PHASE_IDX]
        qmltextCurrentAxis =        qmlTextArray[GraphAxisEnum.CURRENT_IDX]
        qmltextTimeAxis =           qmlTextArray[GraphAxisEnum.TIME_IDX]

        if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)
        {
            qmltextEnergyAxis =         qmlTextArray[GraphAxisEnum.ENERGY_IDX]
            qmltextForceAxis =          qmlTextArray[GraphAxisEnum.FORCE_IDX]
            qmltextAbsoluteDistAxis =   qmlTextArray[GraphAxisEnum.ABSOLUTEDIST_IDX]
            qmltextCollapseDistAxis =   qmlTextArray[GraphAxisEnum.COLLAPSEDIST_IDX]
        }
    }

    Connections
    {
        target: UnitConversion

        function onCurrentUnitChanged()
        {
            while(qmlUnitsArray.length){

                qmlUnitsArray.pop()
            }

            qmlUnitsArray.push( "(" + UnitConversion.AmplitudeUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.PowerUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.FrequencyUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.PhaseUnit +")")
            qmlUnitsArray.push("(" + UnitConversion.AmplitudeUnit +")")
            qmlUnitsArray.push( "(" +UnitConversion.EnergyUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.ForceUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.DistanceUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.DistanceUnit +")")
            qmlUnitsArray.push("(" + UnitConversion.AmplitudeUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.VelocityUnit +")")
            qmlUnitsArray.push("(" +UnitConversion.TimeUnit +")")
        }
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
    }

    function getAxisModel()
    {
        if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)
        {
            return qmlTextComboxModelElectric

        }
        else
        {
            return qmlTextComboxModelManual
        }
    }

    function getScanAxisModel()
    {
        return qmlTextScanComboxModel
    }

    function getTestAxisModel()
    {
        return qmlTextTestComboxModel
    }

    function getSeekAxisModel()
    {
        return qmlTextSeekComboxModel
    }

    function getAxisColor(index)
    {
        if(index < colorArray.length)
        {
            return colorArray[index]
        }
        else
        {
            return "#757577";
        }
    }

    function getRefAxisColor(index)
    {
        if(index < refColorArray.length)
        {
            return refColorArray[index]
        }
        else
        {
            return "#757577";
        }
    }

    function getAxisTitle(index)
    {

        if(index < qmlTextArray.length)
            return qmlTextArray[index]
        else
            return qmlTextArray[0]
    }

    function getUnitsTitle(index)
    {

        if(index < qmlUnitsArray.length)
        {
            return qmlUnitsArray[index]
        }
        else
        {
            return qmlUnitsArray[0]
        }
    }
}


/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.0
import Style 1.0
import Com.Branson.RecipeEnum 1.0

Item {
    id: primaryNumpad

    property string qmltextTime             : "TIME"
    property string qmltextEnergy           : "ENERGY"
    property string qmltextPeakPower        : "PEAK POWER"
    property string qmltextAbsoluteDistance : "ABSOLUTE DISTANCE"
    property string qmltextCollapseDistance : "COLLAPSE DISTANCE"
    property string qmltextScrubTime        : "SCRUB TIME"
    property string qmlTextScrubAmplitude   : "SCRUB AMPLITUDE"
    property string qmltextWeldAmplitude    : "WELD AMPLITUDE"
    property string qmltextPressure         : "WELD PRESSURE"
    property string qmltextFlowRate         : "DOWNSPEED"
    property string qmltextHoldTime         : "HOLD TIME"
    property string qmltextTriggerForce     : "TRIGGER FORCE"
    property string qmltextHoldPressure    : "HOLD PRESSURE"
    property string qmltextSearchByCycleNo  : "SEARCH BY CYCLE NO"
    property string qmltextSamplingInterval : "SAMPLING INTERVAL"
    property string  qmltextPretriggerMenuName:       "PRETRIGGER"
    property string qmltextPretriggerAmplitude:        "PRETRIGGER AMPLITUDE"
    property string qmltextPretriggerDistance:         "PRETRIGGER DISTANCE"
    property string qmltextPretriggerTime:             "PRETRIGGER TIME"
    property string qmltextAfterburstMenuName:         "AFTERBURST"
    property string qmltextAfterburstDelay:            "AFTERBURST DELAY"
    property string qmltextAfterburstTime:             "AFTERBURST TIME"
    property string qmltextAfterburstAmplitude:        "AFTERBURST AMPLITUDE"
    property string qmltextCycleCount:                   "Cycle Count"
    //    property string qmltextInternalFreqOffset:          "INTERNAL FREQ OFFSET"
    //    property string qmltextDigitalTune:                 "DIGITAL TUNE"

    property string qmltextScanFrequencyStep           : "SCAN FREQUENCY STEP"
    property string qmltextScanMaxAmplitude            : "SCAN MAX AMPLITUDE"
    property string qmltextScanMaxCurrent              : "SCAN MAX CURRENT"
    property string qmltextScanStartFrequency          : "SCAN START FREQUENCY"
    property string qmltextScanStopFrequency           : "SCAN STOP FREQUENCY"
    property string qmltextScanTimeDelay               : "SCAN TIME DELAY"

    property string qmltextTestFreqLimitHigh           : "TEST FREQUENCY HIGH"
    property string qmltextTestFreqLimitLow            : "TEST FREQUENCY LOW"
    property string qmltextTestFreqOffset              : "TEST FREQUENCY OFFSET"
    property string qmltextTestMemClearBeforeTest      : "CLEAR MEMORY BEFORE TEST"
    property string qmltextTestAmplitudeRampTime       : "TEST AMPLITUDE RAMP TIME"
    property string qmltextTestAmplitude               : "TEST AMPLITUDE"
    property string qmltextTestAmpProportionalGain     : "TEST AMPLITUDE PROPOTIONAL GAIN"
    property string qmltextTestAmpIntegralGain         : "TEST AMPLITUDE INTEGRAL GAIN"
    property string qmltextTestAmpDerivativeGain       : "TEST AMPLITUDE DERIVATIVE GAIN"
    property string qmltextTestPhaseProportionalGain   : "TEST PHASE PROPOTIONAL GAIN"
    property string qmltextTestPhaseIntegralGain       : "TEST PHASE INTEGRAL GAIN"
    property string qmltextTestPhaseDerivativeGain     : "TEST PHASE DERIVATIVE GAIN"
    property string qmltextTestPhaseLoopCF             : "TEST PHASE LOOP CF"

    property string qmltextSeekFreqLimitHigh           : "SEEK FREQUENCY LIMIT HIGH"
    property string qmltextSeekFreqLimitLow            : "SEEK FREQUENCY LIMIT LOW"
    property string qmltextSeekFreqOffset              : "SEEK FREQUENCY OFFSET"
    property string qmltextSeekMemClearBeforeSeek      : "MEMORY CLEAR BEFORE SEEK"
    property string qmltextSeekTime                    : "SEEK TIME"
    property string qmltextSeekAmplitudeRampTime       : "SEEK AMPLITUDE RAMP TIME"
    property string qmltextSeekAmplitude               : "SEEK AMPLITUDE"
    property string qmltextSeekAmpProportionalGain     : "SEEK AMPLITUDE PROPOTIONAL GAIN"
    property string qmltextSeekAmpIntegralGain         : "SEEK AMPLITUDE INTEGRAL GAIN"
    property string qmltextSeekAmpDerivativeGain       : "SEEK AMPLITUDE DERIVATIVE GAIN"
    property string qmltextSeekPhaseProportionalGain   : "SEEK PHASE PROPOTIONAL GAIN"
    property string qmltextSeekPhaseIntegralGain       : "SEEK PHASE INTEGRAL GAIN"
    property string qmltextSeekPhaseDerivativeGain     : "SEEK PHASE DERIVATIVE GAIN"
    property string qmltextSeekBlindTimeSeek           : "SEEK BLIND TIME SEEK"
    property string qmltextSeekPhaseLoopCF             : "SEEK PHASE LOOP CF"
    /* Recipe Lab -> Stack Recipe */
    property string qmltextDigitalTune                  : "DIGITAL TUNE"
    property string qmltextInternalFreqOffset           : "INTERNAL FREQ OFFSET"
    property string qmltextFrequencyLow                 : "FREQUENCY LOW"
    property string qmltextFrequencyHigh                : "FREQUENCY HIGH"
    property string qmltextWeldRampTime                 : "WELD RAMP TIME"
    property string qmltextStartFrequency               : "START FREQUENCY"
    property string qmltextPhaseLimitTime               : "PHASE LIMIT TIME"
    property string qmltextPhaseLimit                   : "PHASE LIMIT"
    property string qmltextControlMode                  : "CONTROL MODE"
    property string qmltextBlindTimeWeld                : "BLIND TIME WELD"
    property string qmltextAmpProportionalGain          : "AMPLITUDE PROPORTIONAL GAIN"
    property string qmltextAmpIntegralGain              : "AMPLITUDE INTEGRAL GAIN"
    property string qmltextAmpDerivativeGain            : "AMPLITUDE DERIVATIVE GAIN"
    property string qmltextPhaseProportionalGain        : "PHASE PROPORTIONAL GAIN"
    property string qmltextPhaseIntegralGain            : "PHASE INTEGRAL GAIN"
    property string qmltextPhaseDerivativeGain          : "PHASE DERIVATIVE GAIN"
    /* Recipe Lab -> Parameter A to Z */
    property string qmltextEnergyBrakeTime:         "ENERGY BRAKE TIME"
    property string qmltextEnergyBrakeAmplitude:    "ENERGY BRAKE AMPLITUDE"
    property string qmltextExtraCooling:            "EXTRA COOLING"
    property string qmltextMaxTimeout:              "MAX TIMEOUT"
    property string qmltextHoldForceRamp:           "HOLD FORCE RAMP"
    property string qmltextRapidTraverseDistance:   "RAPID TRAVERSE DISTANCE"

    /* Recipe Lab -> Cuttoff Limits */
    property string qmlTextFrequencyLowCutOff:       "FREQUENCY LOW CUTOFF"
    property string qmlTextPeakPowerCutOff:          "PEAK POWER CUTOFF"
    property string qmlTextFrequencyHigh:            "FREQUENCY HIGH CUTOFF"
    property string qmlTextEnergyCutOff:             "ENERGY CUTOFF"
    property string qmlTextGroundDetectCutOff:       "GROUND DETECT CUTOFF"
    property string qmlTextTimeCutOff:               "TIME CUTOFF"
    property string qmlTextAbsoluteDistanceCutOff:   "ABSOLUTE DISTANCE CUTOFF"
    property string qmlTextCollapseDistanceCutOff:   "COLLAPSE DISTANCE CUTOFF"

    property string qmltextActTime:                    "ACTUATOR TIME"
    property string qmltextActDistance:                "ACTUATOR DISTANCE"
    property string qmltextForce:              "TRIGGER FORCE"
    property string qmltextTriggerDistance:    "TRIGGER DISTANCE"
    property string qmltextTimeSeek:           "TIME SEEK PERIOD"
    property string qmltextScrubAmplitude:     "SCRUB AMPLITUDE"

    /* Recipe Lab - Batch Setting */
    property string qmltextBatchCounterLimit                  : "BATCH COUNTER LIMIT"

    /* System configuration -> User Management -> Global User setting */
    property string qmltextPasswordExpiration          : "Password Expiration"
    property string qmltextIdleTimeLogout              : "Idle Time Logout"
    property string qmltextLockOutTime                 : "Lock Out Time"

    property string qmltextAnalogOut_1        : "Analog_Out_1"
    property string qmltextAnalogOut_2        : "Analog_Out_2"

    /* Service Reminder */
    property string qmlTextAddServiceCount    : "ADD SERVICE COUNT"
    property string qmlTextEditServiceCount   : "EDIT SERVICE COUNT"

    /*Calibration*/
    property string qmlTextCalibrateForce      : "CALIBRATE FORCE"
    property string qmlTextCalibratePressure   : "CALIBRATE PRESSURE"

    /*Recipe limits Energy COmpensation */
    property string qmlTextEnergyLowVal:             "ENERGY COMPENSATION MINIMUM VALUE"
    property string qmlTextEnergyHighVal:            "ENERGY COMPENSATION MAXIMUM VALUE"

    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(411 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headertext: "TRIGGER FORCE"
    property string suffix:  "%"
    property int decimals: 3
    property real minimumValue: 10
    property real maximumValue: 100
    property alias value: input.text
    property bool outofRangeFlag: false
    property bool clearedOnce: false

    function slotDigitalKeyPressed(data)
    {
        /*To  avoid use of backspace for user to clear text before any entry*/
        if(clearedOnce)
        {
            input.clear()
            clearedOnce = false
        }

        BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
    }

    function popupForLimitsExcedding(minimumValue, maximumValue, value)
    {
        if(value < minimumValue || value > maximumValue)
        {
            outofRangeFlag = true
            showMessagePopUp()
        }

        else
        {
            outofRangeFlag = false
        }
    }
    
    Component.onCompleted:
    {
        bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
    }

    onVisibleChanged:
    {
        /*Clear data once only*/
        if(visible)
        {
            clearedOnce = true
        }
    }

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight:maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        /*header title*/
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: headermaxHeight
            color: Style.headerBackgroundColor
            Text {
                id: headername
                anchors.left: numpadHeader.left
                anchors.top: numpadHeader.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headertext
                color: Style.whiteFontColor
                font{
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style2 * Style.scaleHint)
                }
            }

            Rectangle
            {
                id:rectimage
                implicitWidth: Math.round(24 * Style.scaleHint)
                implicitHeight: Math.round(24 * Style.scaleHint)
                anchors.right: numpadHeader.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: numpadHeader.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                color: "transparent"
                Image {
                    id: headerClose
                    anchors.fill: parent
                    source: "qrc:/Images/crossMark.svg"
                    sourceSize.width: headerClose.width
                    sourceSize.height: headerClose.height
                    smooth: true

                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        primaryNumpad.visible = false
                    }
                }
            }
        }
        /*main keyboard*/
        Rectangle
        {
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            anchors.topMargin: Math.round(0* Style.scaleHint)
            anchors.leftMargin: Math.round(200 * Style.scaleHint)

            BransonTextField
            {
                id: input
                anchors.top: parent.top
                anchors.topMargin: Math.round(22 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(260 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                focus: true
                onlyForNumpad: true
                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,input)
                }
            }

            Text
            {
                id: txtUnit
                visible: ((headertext !== qmltextSearchByCycleNo) &&
                          (headertext !== qmlTextAddServiceCount) && (headertext !== qmlTextEditServiceCount))
                text: suffix
                anchors.right: input.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: input.top
                anchors.topMargin: Math.round(4 * Style.scaleHint)
                color: Style.blackFontColor
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.regular.name
            }

            Label
            {
                id: labelMin
                visible: (headertext !== qmltextSearchByCycleNo)
                text: BransonNumpadDefine.qmltextMinimun + ":" //qsTr("Min:")
                anchors.top: input.bottom
                anchors.left: input.left
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }

            Text
            {
                id: txtMin
                visible: (headertext !== qmltextSearchByCycleNo)
                text: BransonNumpadDefine.numberToString(decimals, minimumValue)
                anchors.top: labelMin.top
                anchors.left: labelMin.right
                anchors.leftMargin:  Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor

            }

            Label
            {
                id: labelMax
                visible: (headertext !== qmltextSearchByCycleNo)
                text: BransonNumpadDefine.qmltextMaximum + ":" //qsTr("Max:")
                anchors.top: txtMax.top
                anchors.right: txtMax.left
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }

            Text
            {
                id: txtMax
                visible: (headertext !== qmltextSearchByCycleNo)
                text: BransonNumpadDefine.numberToString(decimals, maximumValue)
                anchors.top: input.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.right:  input.right
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blueFontColor
            }

            BransonNumKeyboard
            {
                id:bransonprimary
                anchors.top:input.bottom
                anchors.topMargin: (headertext !== qmltextSearchByCycleNo) ? Math.round(8 * Style.scaleHint) : Math.round(-5 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        /*bottom keyboard*/
        BransonPrimaryButton
        {
            id: cancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextCancel
            font.family: Style.regular.name
            buttonColor: Style.backgroundColor
            textColor: "#000000"
            onClicked:
            {
                primaryNumpad.visible = false
            }
        }

        BransonPrimaryButton
        {
            id: done
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: cancel.top
            anchors.left: cancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextDone
            font.family: Style.regular.name
            onClicked:
            {
                if(headertext !== qmltextSearchByCycleNo  )
                {
                    if(headertext !== qmltextLockOutTime)
                    {
                        popupForLimitsExcedding(minimumValue, maximumValue, value)
                    }
                }

                if(headertext === qmltextLockOutTime)
                {
                    if(value === "0" || (value >= minimumValue && value <= maximumValue))
                    {
                        GlobalUserSetting.LockOutTime = input.text
                    }
                    else
                    {
                        popupForLimitsExcedding(minimumValue, maximumValue, value)
                    }
                }
                if(! outofRangeFlag)
                {
                    if((headertext === qmltextPretriggerMenuName)){
                        RecipeLabData.PretriggerEnable = input.text
                    }
                    else if(headertext === qmltextPretriggerAmplitude){
                        RecipeLabData.PretriggerAmplitude = input.text
                    }
                    else if((headertext === qmltextCycleCount)){
                        DataFilterListModel.CycleCount = input.text;
                    }
                    else if((headertext === qmltextPretriggerDistance)){
                        RecipeLabData.PretriggerDistance = input.text
                    }
                    else if((headertext === qmltextPretriggerTime)){
                        RecipeLabData.PretriggerTime = input.text
                    }
                    else if((headertext === qmltextAfterburstMenuName)){
                        RecipeLabData.AfterburstEnable = input.text
                    }
                    else if((headertext === qmltextAfterburstDelay)){
                        RecipeLabData.AfterburstDelay = input.text
                    }
                    else if((headertext === qmltextAfterburstTime)){
                        RecipeLabData.AfterburstTime = input.text
                    }
                    else if((headertext === qmltextAfterburstAmplitude)){
                        RecipeLabData.AfterburstAmplitude = input.text
                    }
                    /* Recipe Lab - Stack Recipe */
                    else if((headertext === qmltextInternalFreqOffset)){
                        RecipeLabData.InternalFreqOffset=input.text
                    }
                    else if((headertext === qmltextDigitalTune)){
                        RecipeLabData.DigitalTune=input.text
                    }
                    else if((headertext === qmltextFrequencyLow)){
                        RecipeLabData.FrequencyLow=input.text
                    }
                    else if((headertext === qmltextFrequencyHigh)){
                        RecipeLabData.FrequencyHigh=input.text
                    }
                    else if((headertext === qmltextWeldRampTime)){
                        RecipeLabData.WeldRampTime=input.text
                    }
                    else if((headertext === qmltextStartFrequency)){
                        RecipeLabData.StartFrequency=input.text
                    }
                    else if((headertext === qmltextPhaseLimitTime)){
                        RecipeLabData.PhaseLimitTime=input.text
                    }
                    else if((headertext === qmltextPhaseLimit)){
                        RecipeLabData.PhaseLimit=input.text
                    }
                    else if((headertext === qmltextControlMode)){
                        RecipeLabData.ControlMode=input.text
                    }
                    else if((headertext === qmltextBlindTimeWeld)){
                        RecipeLabData.BlindTimeWeld=input.text
                    }
                    else if((headertext === qmltextAmpProportionalGain)){
                        RecipeLabData.AmpProportionalGain=input.text
                    }
                    else if((headertext === qmltextAmpIntegralGain)){
                        RecipeLabData.AmpIntegralGain=input.text
                    }
                    else if((headertext === qmltextAmpDerivativeGain)){
                        RecipeLabData.AmpDerivativeGain=input.text
                    }
                    else if((headertext === qmltextPhaseProportionalGain)){
                        RecipeLabData.PhaseProportionalGain=input.text
                    }
                    else if((headertext === qmltextPhaseIntegralGain)){
                        RecipeLabData.PhaseIntegralGain=input.text
                    }
                    else if((headertext === qmltextPhaseDerivativeGain)){
                        RecipeLabData.PhaseDerivativeGain=input.text
                    }

                    /* Recipe Lab - Parameter A to Z */
                    else if((headertext === qmltextEnergyBrakeTime)){
                        RecipeLabData.EnergyBrakeTime = input.text
                    }
                    else if((headertext === qmltextEnergyBrakeAmplitude)){
                        RecipeLabData.EnergyBrakeAmplitude = input.text
                    }
                    else if((headertext === qmltextMaxTimeout)){
                        RecipeLabData.MaxWeldTimeout = input.text
                    }
                    else if((headertext === qmltextHoldForceRamp)){
                        RecipeLabData.HoldForceRamp = input.text
                    }
                    else if((headertext === qmltextRapidTraverseDistance)){
                        RecipeLabData.RapidTraverseDistance = input.text
                    }

                    /* Recipe Lab - CuttoffLimits */
                    else if((headertext === qmlTextFrequencyLowCutOff)){
                        RecipeLabData.FreqLowCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextPeakPowerCutOff)){
                        RecipeLabData.PeakPowerCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextFrequencyHigh)){
                        RecipeLabData.FreqHighCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextEnergyCutOff)){
                        RecipeLabData.EnergyCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextGroundDetectCutOff)){
                        RecipeLabData.GroundDetectCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextTimeCutOff)){
                        RecipeLabData.TimeCuttoffValue = input.text
                    }
                    else if((headertext === qmlTextAbsoluteDistanceCutOff)){
                        RecipeLabData.ABSDistanceCutoffValue = input.text
                    }
                    else if((headertext === qmlTextCollapseDistanceCutOff)){
                        RecipeLabData.CollapseDistanceCutoffValue = input.text
                    }

                    /* Recipe Lab - Batch Setting */
                    else if((headertext === qmltextBatchCounterLimit)){
                        RecipeLabData.BatchCounterLimit = input.text
                    }


                    if((headertext === qmltextTime) || (headertext === qmltextEnergy) || (headertext === qmltextPeakPower) ||
                            (headertext === qmltextScrubTime) || (headertext === qmltextAbsoluteDistance) || (headertext === qmltextCollapseDistance))
                    {
                        switch (RecipeLabData.WeldMode)
                        {
                        case RecipeEnum.TIME_IDX :

                            RecipeLabData.ModeValueTime = input.text
                            break;

                        case RecipeEnum.ENERGY_IDX :

                            RecipeLabData.ModeValueEnergy = input.text
                            break;

                        case RecipeEnum.PEAKPOWER_IDX :

                            RecipeLabData.ModeValuePeakPower = input.text
                            break;

                        case RecipeEnum.GROUND_IDX :

                            RecipeLabData.ModeValueGroundDetect = input.text
                            break;

                        case RecipeEnum.ABSDISTANCE_IDX:
                            RecipeLabData.ModeValueAbsDistance = input.text
                            break;

                        case RecipeEnum.COLDISTANCE_IDX:

                            RecipeLabData.ModeValueColDistance = input.text
                            break;

                        default :

                            RecipeLabData.ModeValueTime = input.text
                            break;
                        }
                    }

                    if(headertext === qmltextPressure)
                    {
                        if(ActuatorSetupData.ScreenOpenOnHMI === true)
                        {
                            ActuatorSetupData.RecipeWeldPressure = input.text
                        }
                        else
                        {
                            RecipeLabData.WeldPressure = input.text
                        }
                    }

                    if(headertext === qmltextFlowRate)
                        RecipeLabData.FlowRate = input.text

                    if(headertext === qmltextHoldTime)
                        RecipeLabData.HoldTime = input.text

                    if(headertext === qmltextTriggerForce)
                        RecipeLabData.TriggerForce = input.text

                    if(headertext === qmltextHoldPressure)
                        RecipeLabData.HoldPressure = input.text

                    if(headertext === qmltextSearchByCycleNo)
                    {
                        if(input.text !== "")
                        {
                            CycleDetailsListModel.SearchByCycleNo = input.text
                        }

                        else
                        {
                            CycleDetailsListModel.SearchByCycleNo = -1
                        }
                    }

                    if(headertext === qmltextActTime)
                    {
                        RecipeLabData.ActuatorClearTime = input.text
                    }
                    if(headertext === qmltextActDistance)
                    {
                        RecipeLabData.ActuatorClearDistance = input.text
                    }
                    if(headertext === qmltextForce)
                    {
                        RecipeLabData.TriggerTypeForce = input.text
                    }
                    if(headertext === qmltextTriggerDistance)
                    {
                        RecipeLabData.TriggerTypeDistance = input.text
                    }
                    if(headertext === qmltextTimeSeek)
                    {
                        RecipeLabData.TimeSeekPeriod = input.text
                    }
                    if(headertext === qmltextScrubAmplitude)
                    {
                        RecipeLabData.ScrubAmplitude = input.text
                    }

                    if(headertext === qmltextSamplingInterval)
                    {
                        GraphSettings.SamplingInterval = input.text
                    }

                    /*Scan test parameters*/

                    if(headertext === qmltextScanFrequencyStep)
                    {
                        ScanCycleDetailsListModel.ScanFreqStep = input.text
                    }

                    if(headertext === qmltextScanMaxAmplitude)
                    {
                        ScanCycleDetailsListModel.ScanMaxAmplitude = input.text
                    }

                    if(headertext === qmltextScanMaxCurrent)
                    {
                        ScanCycleDetailsListModel.ScanMaxCurrent = input.text
                    }

                    if(headertext === qmltextScanStartFrequency)
                    {
                        ScanCycleDetailsListModel.ScanStartFrequency = input.text
                    }

                    if(headertext === qmltextScanStopFrequency)
                    {
                        ScanCycleDetailsListModel.ScanStopFrequency = input.text
                    }

                    if(headertext === qmltextScanTimeDelay)
                    {
                        ScanCycleDetailsListModel.ScanTimeDelay = input.text
                    }

                    /*Horn test parameters*/

                    if(headertext === qmltextTestFreqLimitHigh)
                    {
                        TestData.TestFreqLimitHigh = input.text
                    }

                    if(headertext === qmltextTestFreqLimitLow)
                    {
                        TestData.TestFreqLimitLow = input.text
                    }

                    if(headertext === qmltextTestFreqOffset)
                    {
                        TestData.TestFreqOffset = input.text
                    }

                    if(headertext === qmltextTestMemClearBeforeTest)
                    {
                        TestData.TestMemClear = input.text
                    }

                    if(headertext === qmltextTestAmplitudeRampTime)
                    {
                        TestData.TestAmplitudeRampTime = input.text
                    }

                    if(headertext === qmltextTestAmplitude)
                    {
                        if(TestData.AmpUpdateFlagStatus)
                        {
                            TestData.TestAmplitude2 = input.text
                        }

                        else
                        {
                            TestData.TestAmplitude = input.text
                        }
                    }

                    if(headertext === qmltextTestAmpProportionalGain)
                    {
                        TestData.TestAmpProportionalGain = input.text
                    }

                    if(headertext === qmltextTestAmpIntegralGain)
                    {
                        TestData.TestAmpIntegralGain = input.text
                    }

                    if(headertext === qmltextTestAmpDerivativeGain)
                    {
                        TestData.TestAmpDerivativeGain = input.text
                    }

                    if(headertext === qmltextTestPhaseProportionalGain)
                    {
                        TestData.TestPhaseProportionalGain = input.text
                    }

                    if(headertext === qmltextTestPhaseIntegralGain)
                    {
                        TestData.TestPhaseIntegralGain = input.text
                    }

                    if(headertext === qmltextTestPhaseDerivativeGain)
                    {
                        TestData.TestPhaseDerivativeGain = input.text
                    }

                    if(headertext === qmltextTestPhaseLoopCF)
                    {
                        TestData.TestPhaseloopCF = input.text
                    }

                    /*Seek parameters*/

                    if(headertext === qmltextSeekFreqLimitHigh)
                    {
                        SeekData.SeekFreqLimitHigh = input.text
                    }

                    if(headertext === qmltextSeekFreqLimitLow)
                    {
                        SeekData.SeekFreqLimitLow = input.text
                    }

                    if(headertext === qmltextSeekFreqOffset)
                    {
                        SeekData.SeekFreqOffset = input.text
                    }

                    if(headertext === qmltextSeekMemClearBeforeSeek)
                    {
                        SeekData.SeekMemClear = input.text
                    }

                    if(headertext === qmltextSeekTime)
                    {
                        SeekData.SeekTime = input.text
                    }

                    if(headertext === qmltextSeekAmplitudeRampTime)
                    {
                        SeekData.SeekAmplitudeRampTime = input.text
                    }

                    if(headertext === qmltextSeekAmplitude)
                    {
                        SeekData.SeekAmplitude = input.text
                    }

                    if(headertext === qmltextSeekAmpProportionalGain)
                    {
                        SeekData.SeekAmpProportionalGain = input.text
                    }

                    if(headertext === qmltextSeekAmpIntegralGain)
                    {
                        SeekData.SeekAmpIntegralGain = input.text
                    }

                    if(headertext === qmltextSeekAmpDerivativeGain)
                    {
                        SeekData.SeekAmpDerivativeGain = input.text
                    }

                    if(headertext === qmltextSeekPhaseProportionalGain)
                    {
                        SeekData.SeekPhaseProportionalGain = input.text
                    }

                    if(headertext === qmltextSeekPhaseIntegralGain)
                    {
                        SeekData.SeekPhaseIntegralGain = input.text
                    }

                    if(headertext === qmltextSeekPhaseDerivativeGain)
                    {
                        SeekData.SeekPhaseDerivativeGain = input.text
                    }

                    if(headertext === qmltextSeekBlindTimeSeek)
                    {
                        SeekData.SeekBlindTimeSeek = input.text
                    }

                    if(headertext === qmltextSeekPhaseLoopCF)
                    {
                        SeekData.SeekPhaseloopCF = input.text
                    }
                    /*Global User Setting parameters*/
                    if(headertext === qmltextPasswordExpiration)
                    {
                        GlobalUserSetting.PasswordExpiration = input.text
                    }
                    if(headertext === qmltextIdleTimeLogout)
                    {
                        GlobalUserSetting.IdleTimeLogout = input.text
                    }

                    //Diagnostic userIo params
                    if(headertext === qmltextAnalogOut_1)
                    {
                        DiagnosticUserIOObj.AnalogOutput_1 = input.text
                    }
                    if(headertext === qmltextAnalogOut_2)
                    {
                        DiagnosticUserIOObj.AnalogOutput_2 = input.text
                    }

                    /*Service Reminder*/
                    if((headertext === qmlTextAddServiceCount) || (headertext === qmlTextEditServiceCount))
                    {
                        ServiceCountListModel.CounterReminder = input.text
                    }

                    /*Calibration*/
                    if(headertext === qmlTextCalibrateForce)
                    {
                        CalibrateForce.CalibrationReadings = input.text
                    }

                    if(headertext === qmlTextCalibratePressure)
                    {
                        CalibratePressure.CalibrationReadings = input.text
                    }

                    /*Recipe Limits Energy Compensation */
                    if(headertext === qmlTextEnergyLowVal)
                    {
                        RecipeLabData.EnergyCompensationLowVal = input.text
                    }
                    if(headertext === qmlTextEnergyHighVal)
                    {
                        RecipeLabData.EnergyCompensationHighVal = input.text
                    }
                }
                primaryNumpad.visible = false
            }
        }
    }
}

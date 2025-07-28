/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonSteppingNumpad.qml provides stepping inputs numpad interface
    handling.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 10/27/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

Item {
    id: steppingNumpad
    property string qmltextStepTime:        "Step@Time"
    property string qmltextStepEnergy:      "Step@Energy"
    property string qmltextStepPeakPower:   "Step@Pk Power"
    property string qmltextStepAbsolute:    "Step@Absolute"
    property string qmltextStepCollapse:    "Step@Collapse"
    property string qmltextStepExtSignal:   "Step@Ext. Signal"

    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(430 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headerColor: Style.headerBackgroundColor
    property string headertext
    property string headertextColor: "#FFFFFF"
    property int fontSize: Math.round(Style.style2 * Style.scaleHint)
    property int count: 1
    property var obj: []
    property string suffix:  "%"
    property string stepSuffix: "%"
    property int decimals: 3
    property int stepDecimals: 3
    property int stepRampDecimals: 3
    property int currentStepIndex: -1
    property int currentArrayIndex: 0
    property real minimumValue: 1
    property real maximumValue: 100
    property alias value: input.text
    property int maxSteps: RecipeLabData.getMaxAmplitudeStepCountSupported()
    property int currentMaxCount: 1
    property int focusedItem: focusedItemEnum.mainFocusedIdx
    property bool stepFlag : false
    property int stepTitleIndex : -1
    property var stepTypeModel: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL) ? [qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower,
                                                                                                            qmltextStepExtSignal] : [qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower,
                                                                           qmltextStepExtSignal, qmltextStepAbsolute, qmltextStepCollapse]
    property string stepAtValuePrev
    property string stepRampValuePrev
    property string stepTargetValuePrev
    property int stepIndexPrev
    property bool warningPopupFlag : false
    property string qmltextValidationError: "Entered Values Outof Range, Restoring To Default..!"
    property string qmltextMaxStepCountError: "Max Stepping Count Reached..!"
    property int totalSteps: 10
    property bool clearedMainOnce: false
    property bool clearedAmpStepZeroOnce: false
    property bool clearedAmpStepOnce: false
    property bool clearedAmpStepRampOnce: false

    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    signal sysConfigDataChanged()

    /*Remove components dynamically*/
    function removeDynamicSteps()
    {
        /*Dynamically delete components*/
        if(count - 1 > 0)
        {
            obj[count - 1].destroy()
            if(count === stepValueModel.count)
            {
                stepValueModel.remove(count - 1)
            }
            count--
            onSignalClickAction(count - 1, false)
        }
        else
            stepValueModel.resetModel()
    }

    /*Add components dynamically*/
    function createDynamicSteps()
    {
        var component = Qt.createComponent("BransonDynamicStepButton.qml")
        if (component.status === Component.Ready)
        {

            if(count > maxSteps)
            {
                /*Max step reched popup*/
                warningPopup.visible = true
                warningPopup.qmltextWarningDialog = qmltextMaxStepCountError
                return
            }

            obj[count] = component.createObject(stepsColumn, {
                                                    "width": Math.round(30 * Style.scaleHint),
                                                    "height": Math.round(30 * Style.scaleHint),
                                                    "stepIndex": count })
            obj[count].signalClickAction.connect(onSignalClickAction)
            stepValueModel.appendNewDefaultStep(count)
            currentMaxCount = count
            onSignalClickAction(count, false)
            obj[count].color = BransonStyle.activeFrameBorderColor
            obj[count].textColor = BransonStyle.textFieldBackgoundColor
            for(var i = count-1; i > 0; i--)
            {
                obj[i].color = BransonStyle.textFieldBackgoundColor
                obj[i].textColor = BransonStyle.activeFrameBorderColor
            }

            count++
        }
    }

    function onSignalClickAction(index, clickFlag)
    {
        var clickFlagStatus

        /*Flag to check invalid entry before jumping to other step by clicking on it*/
        clickFlagStatus = clickFlag
        currentStepIndex = (index - 1)

        if(clickFlagStatus && warningPopupFlag)
        {
            warningPopup.visible = true
            warningPopup.qmltextWarningDialog = qmltextValidationError
        }

        if(currentStepIndex > -1)
        {
            stepTitle.currentIndex = stepTitleIndex
            BransonNumpadDefine.decimalsNumber(stepDecimals, stepValueInput)
            BransonNumpadDefine.decimalsNumber(stepRampDecimals, stepRampValueInput)
            stepValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepAtValue(currentStepIndex)).toFixed(stepDecimals)
            stepRampValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepRamp(currentStepIndex)).toFixed(stepRampDecimals)
            stepSuffix = stepValueModel.get(currentStepIndex).StepUnit
            input.text = RecipeLabData.getAmplitudeStepTarget(currentStepIndex).toString()

            for(var i = 1; i <= currentMaxCount; i++)
            {
                if(i !== index)
                {
                    obj[i].color = BransonStyle.textFieldBackgoundColor
                    obj[i].textColor = BransonStyle.activeFrameBorderColor
                }

                else
                {
                    obj[i].color = BransonStyle.activeFrameBorderColor
                    obj[i].textColor = BransonStyle.textFieldBackgoundColor
                }
            }
        }

        else
        {
            input.text = RecipeLabData.WeldAmplitude
        }
    }

    function slotDigitalKeyPressed(data)
    {
        switch(focusedItem)
        {
        case focusedItemEnum.mainFocusedIdx :

            /*To  avoid use of backspace for user to clear text before maintextfield entry*/
            if(clearedMainOnce)
            {
                input.clear()
                clearedMainOnce = false
            }

            BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
            break

        case focusedItemEnum.ampStepZeroFocusedIdx :

            /*To  avoid use of backspace for user to clear text before amplitude step zero entry*/
            if(clearedAmpStepZeroOnce)
            {
                stepZeroValueInput.clear()
                clearedAmpStepZeroOnce = false
            }

            BransonNumpadDefine.handleWithDigitalKeyInput(data, stepZeroValueInput, suffix)
            break

        case focusedItemEnum.ampStepFocusedIdx :

            /*To  avoid use of backspace for user to clear text before amplitude step zero entry*/
            if(clearedAmpStepOnce)
            {
                stepValueInput.clear()
                clearedAmpStepOnce = false
            }

            BransonNumpadDefine.handleWithDigitalKeyInput(data, stepValueInput, stepSuffix)
            break

        case focusedItemEnum.ampStepRampIdx :

            /*To  avoid use of backspace for user to clear text before amplitude step ramp entry*/
            if(clearedAmpStepRampOnce)
            {
                stepRampValueInput.clear()
                clearedAmpStepRampOnce = false
            }

            BransonNumpadDefine.handleWithDigitalKeyInput(data, stepRampValueInput, stepSuffix)
            break

        default :

            /*To  avoid use of backspace for user to clear text before maintextfield entry*/
            if(clearedMainOnce)
            {
                input.clear()
                clearedMainOnce = false
            }

            BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
            break
        }
    }

    ListModel {
        id: stepValueModel
        function resetModel()
        {
            stepValueModel.clear()
        }

        function appendNewDefaultStep(stepNo)
        {
            currentArrayIndex = stepNo-1

            switch (stepTitle.currentIndex)
            {
            case BransonNumpadDefine.stepTimeIdx:

                if(! stepFlag)
                {
                    /*To load deafault values*/
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepTimeIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextTimeUnit,
                                              "Decimals": 3,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepTimeIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepTimeIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextTimeUnit,
                                              "Decimals": 3,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 3

                break;

            case BransonNumpadDefine.stepEnergyIdx:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepEnergyIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextEnergyUnit,
                                              "Decimals": 1,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepEnergyIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepEnergyIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextEnergyUnit,
                                              "Decimals": 1,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 1

                break;

            case BransonNumpadDefine.stepPeakPowerIdx:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepPeakPowerIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextPowerUnit,
                                              "Decimals": 0,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepPeakPowerIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepPeakPowerIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextPowerUnit,
                                              "Decimals": 0,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 0

                break;

            case BransonNumpadDefine.stepAbsoluteIdx:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepAbsoluteIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextDistanceUnit,
                                              "Decimals": 2,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepAbsoluteIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepAbsoluteIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextDistanceUnit,
                                              "Decimals": 2,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 2

                break;

            case BransonNumpadDefine.stepCollapseIdx:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepCollapseIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextDistanceUnit,
                                              "Decimals": 2,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepCollapseIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepCollapseIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextDistanceUnit,
                                              "Decimals": 2,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 2

                break;

            case BransonNumpadDefine.stepExtSignalIdx:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepExtSignalIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": "",
                                              "Decimals": 0,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepExtSignalIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepExtSignalIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": "",
                                              "Decimals": 0,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 0

                break;

            default:

                if(! stepFlag)
                {
                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepTimeIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextTimeUnit,
                                              "Decimals": 3,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})
                }

                else
                {
                    RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepTimeIdx), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), currentArrayIndex)
                    RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), currentArrayIndex)

                    stepValueModel.append({"TitleIndex": BransonNumpadDefine.stepTimeIdx,
                                              "StepValue": RecipeLabData.getAmplitudeStepAtValue(currentArrayIndex).toString(),
                                              "StepRampValue": RecipeLabData.getAmplitudeStepRamp(currentArrayIndex).toString(),
                                              "StepUnit": mainWindow.qmltextTimeUnit,
                                              "Decimals": 3,
                                              "AmplitudeValue": RecipeLabData.getAmplitudeStepTarget(currentArrayIndex).toString()})

                    stepFlag = false
                }

                stepDecimals = 3

                break;
            }
        }
    }

    Component.onCompleted:
    {
        sysConfigDataChanged()
        bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
        stepValueModel.resetModel()
    }

   onVisibleChanged:
   {
       /*Clear data once only*/
       if(visible)
       {
           clearedMainOnce = true
           clearedAmpStepZeroOnce = true
           clearedAmpStepOnce = true
           clearedAmpStepRampOnce = true
       }

       /*Read initial data*/
       maxSteps = RecipeLabData.getMaxAmplitudeStepCountSupported()
       stepTypeModel = (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL) ? [qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower,
                                                                                                                   qmltextStepExtSignal] : [qmltextStepTime, qmltextStepEnergy, qmltextStepPeakPower,
                                                                                qmltextStepExtSignal,  qmltextStepAbsolute, qmltextStepCollapse ]

       /*To create or destroy steps*/
       if(steppingNumpad.visible)
       {
           for(var i = 0; i < (RecipeLabData.NumAmplitudeSteps); i++)
           {
               createDynamicSteps()
           }

           warningPopupFlag = false
           RecipeLabData.IsParamValid = true
       }

       else
       {
           for(i = (RecipeLabData.NumAmplitudeSteps); i > 0; i--)
           {
               removeDynamicSteps()
           }
       }

       /*Decision to show check switch button status*/
       if(RecipeLabData.NumAmplitudeSteps)
       {
           switchbtn.checked = true
       }

       else
       {
           switchbtn.checked = false
       }

       stepTitle.currentIndex = RecipeLabData.AmplitudeStepAt

       switch(RecipeLabData.AmplitudeStepAt)
       {
       case BransonNumpadDefine.stepTimeIdx:

           stepSuffix = mainWindow.qmltextTimeUnit
           stepDecimals = 3

           break

       case BransonNumpadDefine.stepEnergyIdx:

           stepSuffix = mainWindow.qmltextEnergyUnit
           stepDecimals = 1

           break

       case BransonNumpadDefine.stepPeakPowerIdx:

           stepSuffix = mainWindow.qmltextPowerUnit
           stepDecimals = 0

           break

       case BransonNumpadDefine.stepAbsoluteIdx:

           stepSuffix = mainWindow.qmltextDistanceUnit
           stepDecimals = 2

           break

       case BransonNumpadDefine.stepCollapseIdx:

           stepSuffix = mainWindow.qmltextDistanceUnit
           stepDecimals = 2

           break

       case BransonNumpadDefine.stepExtSignalIdx:

           stepSuffix = ""
           stepDecimals = 0

           break

       default :

           stepSuffix = mainWindow.qmltextTimeUnit
           stepDecimals = 3
           break
       }

       BransonNumpadDefine.decimalsNumber(stepDecimals, stepValueInput)
       BransonNumpadDefine.decimalsNumber(stepRampDecimals, stepRampValueInput)
       stepValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepAtValue(currentStepIndex)).toFixed(stepDecimals)
       stepRampValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepRamp(currentStepIndex)).toFixed(stepRampDecimals)
       input.text = RecipeLabData.getAmplitudeStepTarget(currentStepIndex).toString()

       /*To show amplitude target value as per switch button status*/
       if(! switchbtn.checked)
       {
           input.text = RecipeLabData.WeldAmplitude
       }

       else
       {
           stepZeroValueInput.text = RecipeLabData.WeldAmplitude
       }

       stepTitleIndex = RecipeLabData.AmplitudeStepAt
   }

   BransonPopup
   {
       id: warningPopup

       onOKButtonClicked:
       {
           warningPopupFlag = false
           warningPopup.visible = false
       }
   }

    QtObject
    {
        id: focusedItemEnum
        readonly property int noFocusedIdx            : -1
        readonly property int mainFocusedIdx          : 0
        readonly property int ampStepZeroFocusedIdx   : 1
        readonly property int ampStepFocusedIdx       : 2
        readonly property int forceStepFocusedIdx     : 3
        readonly property int ampStepRampIdx          : 4
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
        width: minWidth
        height: maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: headermaxHeight
            color: headerColor
            Text {
                id: headername
                anchors.left: numpadHeader.left
                anchors.top: numpadHeader.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headertext
                color: headertextColor
                font{
                    family: Style.regular.name
                    pixelSize: fontSize
                }
            }
            Rectangle
            {
                id: rectimage
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
                        steppingNumpad.visible = false
                    }
                }
            }
        }

        Rectangle
        {
            id: mykeyboard
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            width: Math.round(200 * Style.scaleHint)
            anchors.bottom: root.bottom
            Rectangle
            {
                id: rect
                width: parent.width
                anchors.top: switchbtn.top
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(25 * Style.scaleHint)
                anchors.bottom: parent.bottom
                visible: false
                Rectangle
                {
                    id:leftbtn
                    width: Math.round(30 * Style.scaleHint)
                    height: parent.height
                    Column {
                        id: stepsColumn
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(30 * Style.scaleHint)
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        width: parent.width
                    }
                    Rectangle {
                        id: deleteObjectBtn
                        anchors.top: parent.top
                        anchors.left: parent.left
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        color: BransonStyle.backgroundColor
                        border.width: BransonStyle.scaleHint === 1.0 ? 1 : 2
                        border.color: BransonStyle.activeFrameBorderColor
                        Text {
                            id: dec
                            anchors.centerIn: parent
                            text: "-"
                            font.bold: true
                            font.family: BransonStyle.regular.name
                            font.pixelSize: BransonStyle.style4
                            color: "#000000"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                removeDynamicSteps()
                            }
                        }
                    }
                    Rectangle {
                        id: createObjectBtn
                        anchors.left: parent.left
                        width: Math.round(30 * Style.scaleHint)
                        height: Math.round(30 * Style.scaleHint)
                        color: BransonStyle.backgroundColor
                        border.width: 1
                        border.color: BransonStyle.activeFrameBorderColor
                        y: count === 1 ? count * Math.round(30 * Style.scaleHint + 2) : count * Math.round(30 * Style.scaleHint)
                        Text {
                            id: inc
                            anchors.centerIn: parent
                            text: "+"
                            font.bold: true
                            font.family: BransonStyle.regular.name
                            font.pixelSize: BransonStyle.style4
                            color: "#000000"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked:
                            {
                                /*To know step added*/
                                stepFlag = true
                                createDynamicSteps()
                            }
                        }
                    }
                }

                Rectangle
                {
                    id: input_left
                    width:  Math.round(200 * Style.scaleHint)
                    height:   Math.round(95 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(50 * Style.scaleHint)
                    anchors.top: parent.top
                    Column
                    {
                        id:columnid
                        anchors.fill: input_left
                        spacing: Math.round(5 * Style.scaleHint)

                        Text
                        {
                            id: stepZeroName
                            text: qsTr("Weld Amplitude")
                            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }

                        BransonTextField
                        {
                            id: stepZeroValueInput
                            text: RecipeLabData.WeldAmplitude
                            onlyForNumpad: true
                            width: Math.round(170 * Style.scaleHint)
                            height: Math.round(40 * Style.scaleHint)
                            enabled: ((currentStepIndex < 0) && (stepTitle.currentIndex !== 3)) ? true : false

                            onSignalClickedEvent:
                            {
                                clearedAmpStepZeroOnce = true
                                focusedItem = focusedItemEnum.ampStepZeroFocusedIdx
                            }

                            onTextChanged:
                            {
                                BransonNumpadDefine.decimalsNumber(stepDecimals, stepZeroValueInput)
                                if(currentStepIndex < 1)
                                    return
                                if((currentStepIndex < stepValueModel.count) && (focusedItem === focusedItemEnum.ampStepZeroFocusedIdx))
                                {
                                    stepValueModel.setProperty(currentStepIndex, "StepValue", stepZeroValueInput.text)
                                    RecipeLabData.WeldAmplitude = stepZeroValueInput.text
                                }
                            }

                        }

                        Text
                        {
                            id: stepname
                            text: BransonNumpadDefine.qmltextStep + "@" //qsTr("Step@")
                            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }

                        BransonComboBox
                        {
                            id: stepTitle
                            minWidth: Math.round(170 * Style.scaleHint)
                            model: stepTypeModel
                            enabled: (currentStepIndex === 0) ? true : false
                            currentIndex: RecipeLabData.AmplitudeStepAt
                            comboBoxTextColor: BransonStyle.blueFontColor
                            onActivated:
                            {
                                focusedItem = focusedItemEnum.noFocusedIdx

                                if(currentStepIndex < 0)
                                    return
                                if(currentStepIndex < stepValueModel.count)
                                {
                                    switch(currentIndex)
                                    {
                                    case BransonNumpadDefine.stepTimeIdx:
                                        stepSuffix = mainWindow.qmltextTimeUnit
                                        stepDecimals = 3
                                        for (var i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepTimeIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepTimeIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    case BransonNumpadDefine.stepEnergyIdx:

                                        stepSuffix = mainWindow.qmltextEnergyUnit
                                        stepDecimals = 1
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepEnergyIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepEnergyIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    case BransonNumpadDefine.stepPeakPowerIdx:

                                        stepSuffix = mainWindow.qmltextPowerUnit
                                        stepDecimals = 0
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepPeakPowerIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepPeakPowerIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    case BransonNumpadDefine.stepAbsoluteIdx:

                                        stepSuffix = mainWindow.qmltextDistanceUnit
                                        stepDecimals = 2
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepAbsoluteIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepAbsoluteIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    case BransonNumpadDefine.stepCollapseIdx:

                                        stepSuffix = mainWindow.qmltextDistanceUnit
                                        stepDecimals = 2
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepCollapseIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepCollapseIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    case BransonNumpadDefine.stepExtSignalIdx:

                                        stepSuffix = ""
                                        stepDecimals = 0
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepExtSignalIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepExtSignalIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;

                                    default:

                                        stepSuffix = mainWindow.qmltextTimeUnit
                                        stepDecimals = 3
                                        currentIndex = 0
                                        for (i = 0; i < totalSteps; i++)
                                        {
                                            RecipeLabData.setAmplitudeStepAtValue(RecipeLabData.getDefaultParamValue(BransonNumpadDefine.stepTimeIdx), i)
                                            RecipeLabData.setAmplitudeStepRamp(RecipeLabData.getDefaultAmplitudeStepRamp(), i)
                                            RecipeLabData.setAmplitudeStepTarget(RecipeLabData.getDefaultAmplitudeStepTarget(), i)

                                            stepValueModel.setProperty(i, "TitleIndex", BransonNumpadDefine.stepTimeIdx)
                                            stepValueModel.setProperty(i, "StepValue", RecipeLabData.getAmplitudeStepAtValue(i).toString())
                                            stepValueModel.setProperty(i, "StepRampValue", RecipeLabData.getAmplitudeStepRamp(i).toString())
                                            stepValueModel.setProperty(i, "StepUnit", stepSuffix)
                                            stepValueModel.setProperty(i, "Decimals", stepDecimals)
                                            stepValueModel.setProperty(i, "AmplitudeValue", RecipeLabData.getAmplitudeStepTarget(i).toString())
                                        }

                                        break;
                                    }

                                    BransonNumpadDefine.decimalsNumber(stepDecimals, stepValueInput)
                                    BransonNumpadDefine.decimalsNumber(stepRampDecimals, stepRampValueInput)
                                    stepValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepAtValue(currentStepIndex)).toFixed(stepDecimals)
                                    stepRampValueInput.text = parseFloat(RecipeLabData.getAmplitudeStepRamp(currentStepIndex)).toFixed(stepRampDecimals)
                                    input.text = RecipeLabData.getAmplitudeStepTarget(currentStepIndex).toString()
                                    stepTitleIndex = stepTitle.currentIndex
                                }
                            }
                        }

                        Text
                        {
                            id: stepValue
                            text: BransonNumpadDefine.qmltextStepValue //qsTr("Step Value")
                            font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }

                        BransonTextField
                        {
                            id: stepValueInput
                            onlyForNumpad: true
                            width: Math.round(170 * Style.scaleHint)
                            height: Math.round(40 * Style.scaleHint)
                            enabled: true //((currentStepIndex >= 0) && (stepTitle.currentIndex !== 3)) ? true : false

                            onSignalClickedEvent:
                            {
                                clearedAmpStepOnce = true
                                focusedItem = focusedItemEnum.ampStepFocusedIdx
                                stepAtValuePrev = stepValueInput.text
                                stepIndexPrev = currentStepIndex
                            }

                            onTextChanged:
                            {
                                BransonNumpadDefine.decimalsNumber(stepDecimals, stepValueInput)
                                if(currentStepIndex < 0)
                                    return

                                if((currentStepIndex < stepValueModel.count) && (focusedItem === focusedItemEnum.ampStepFocusedIdx))
                                {
                                    if ((parseInt(RecipeLabData.getMinParamValue(stepTitle.currentIndex)) <= parseInt(stepValueInput.text)) &&
                                           (parseInt(RecipeLabData.getMaxParamValue(stepTitle.currentIndex)) >= parseInt(stepValueInput.text)))
                                    {
                                        warningPopupFlag = false
                                        stepValueModel.setProperty(currentStepIndex, "StepValue", stepValueInput.text)
                                        RecipeLabData.setAmplitudeStepAtValue(stepValueInput.text, currentStepIndex)
                                    }

                                    else
                                    {
                                        warningPopupFlag = true
                                        stepValueModel.setProperty(currentStepIndex, "StepValue", stepAtValuePrev)
                                        RecipeLabData.setAmplitudeStepAtValue(stepAtValuePrev, currentStepIndex)
                                    }
                                }
                            }
                        }

                        Text
                        {
                            id: stepRampValue
                            text: BransonNumpadDefine.qmltextStepRamp //qsTr("Step Ramp")
                            font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                            font.family: Style.regular.name
                            color: BransonStyle.blueFontColor
                        }

                        BransonTextField
                        {
                            id: stepRampValueInput
                            onlyForNumpad: true
                            width: Math.round(170 * Style.scaleHint)
                            height: Math.round(40 * Style.scaleHint)
                            enabled: true //((currentStepIndex >= 0) && (stepTitle.currentIndex !== 3)) ? true : false

                            onSignalClickedEvent:
                            {
                                clearedAmpStepRampOnce = true
                                focusedItem = focusedItemEnum.ampStepRampIdx
                                stepRampValuePrev = stepRampValueInput.text
                                stepIndexPrev = currentStepIndex
                            }

                            onTextChanged:
                            {
                                BransonNumpadDefine.decimalsNumber(stepRampDecimals, stepRampValueInput)
                                if(currentStepIndex < 0)
                                    return

                                if((currentStepIndex < stepValueModel.count) && (focusedItem === focusedItemEnum.ampStepRampIdx))
                                {
                                    if ((parseInt(RecipeLabData.getMinAmplitudeStepRamp()) <= parseInt(stepRampValueInput.text)) &&
                                           (parseInt(RecipeLabData.getMaxAmplitudeStepRamp()) >= parseInt(stepRampValueInput.text)))
                                    {
                                        warningPopupFlag = false
                                        stepValueModel.setProperty(currentStepIndex, "StepRampValue", stepRampValueInput.text)
                                        RecipeLabData.setAmplitudeStepRamp(stepRampValueInput.text, currentStepIndex)
                                    }

                                    else
                                    {
                                        warningPopupFlag = true
                                        stepValueModel.setProperty(currentStepIndex, "StepRampValue", stepRampValuePrev)
                                        RecipeLabData.setAmplitudeStepRamp(stepRampValuePrev, currentStepIndex)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Text
            {
                id: switchname
                text: BransonNumpadDefine.qmltextStepping  //qsTr("STEPPING")
                color: BransonStyle.blackFontColor
                font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
                font.family: Style.regular.name
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(140 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter

            }

            BransonSwitch
            {
                id:switchbtn
                anchors.bottom: switchname.bottom
                anchors.left: switchname.right
                anchors.leftMargin:  Math.round(15 * Style.scaleHint)
                onCheckedChanged:
                {
                    if(checked === false)
                    {
                        /*Hide the content on the left and move the coordinates to the left*/
                        rect.visible = false
                        root.width = Math.round(400 * Style.scaleHint)
                        mainkeyboard.anchors.leftMargin = Math.round(58 * Style.scaleHint)
                        switchname.anchors.left = parent.left
                        switchname.anchors.leftMargin = Math.round(140 * Style.scaleHint)
                        btnCancel.anchors.leftMargin = Math.round(60 * Style.scaleHint)
                        btnDone.anchors.leftMargin = Math.round(20 * Style.scaleHint)

                        input.text = RecipeLabData.WeldAmplitude
                    }

                    else
                    {
                        /*Enable the once only clear flag*/
                        clearedMainOnce = true
                        clearedAmpStepZeroOnce = true
                        clearedAmpStepOnce = true
                        clearedAmpStepRampOnce = true

                        /*Display the content on the left and move the coordinates to the right*/
                        rect.visible = true
                        root.width = Math.round(600 * Style.scaleHint)
                        mainkeyboard.anchors.leftMargin = Math.round(380 * Style.scaleHint)
                        switchname.anchors.left = parent.left
                        switchname.anchors.leftMargin = Math.round(20 * Style.scaleHint)
                        btnCancel.anchors.leftMargin = Math.round(270 * Style.scaleHint)
                        btnDone.anchors.leftMargin = Math.round(20 * Style.scaleHint)

                        input.text = RecipeLabData.getAmplitudeStepTarget(currentStepIndex)
                        stepZeroValueInput.text = RecipeLabData.WeldAmplitude
                    }
                }
            }

            Rectangle
            {
                id: mainkeyboard
                anchors.top: switchbtn.bottom
                anchors.topMargin: Math.round(-15 * Style.scaleHint)
                anchors.left: switchname.left
                anchors.leftMargin: Math.round(58 * Style.scaleHint)
                BransonTextField
                {
                    id: input
                    enabled:
                    {
                        if(switchbtn.checked)
                        {
                            if(currentStepIndex >= 0)

                                return true
                            else
                                return false

                        }

                        else
                            return true
                    }

                    anchors.top: parent.top
                    anchors.topMargin: Math.round(22 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: Math.round(260 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    onlyForNumpad: true
                    focus: true

                    onSignalClickedEvent:
                    {
                        clearedMainOnce = true
                        focusedItem = focusedItemEnum.mainFocusedIdx
                        stepTargetValuePrev = input.text
                        stepIndexPrev = currentStepIndex
                    }

                    onTextChanged:
                    {
                        BransonNumpadDefine.decimalsNumber(decimals, input)
                        if(currentStepIndex < 0)
                            return
                        if((currentStepIndex < stepValueModel.count) && (switchbtn.checked) && (focusedItem === focusedItemEnum.mainFocusedIdx))
                        {
                            if ((parseInt(RecipeLabData.getMinAmplitudeStepTarget()) <= parseInt(input.text)) &&
                                   (parseInt(RecipeLabData.getMaxAmplitudeStepTarget()) >= parseInt(input.text)))
                            {
                                warningPopupFlag = false
                                stepValueModel.setProperty(currentStepIndex, "AmplitudeValue", input.text)
                                RecipeLabData.setAmplitudeStepTarget(input.text, currentStepIndex)
                            }

                            else
                            {
                                warningPopupFlag = true
                                stepValueModel.setProperty(currentStepIndex, "AmplitudeValue", stepTargetValuePrev)
                                RecipeLabData.setAmplitudeStepTarget(stepTargetValuePrev, currentStepIndex)
                            }
                        }
                    }
                }

                Text
                {
                    id: txtUnit
                    text: suffix
                    anchors.right: input.right
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    anchors.top: input.top
                    anchors.topMargin: Math.round(4 * Style.scaleHint)
                    color: BransonStyle.blackFontColor
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                }

                Label
                {
                    id: labelMin
                    text: BransonNumpadDefine.qmltextMinimun + ":"
                    anchors.top: input.bottom
                    anchors.left: input.left
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor
                }

                Text
                {
                    id: txtMin
                    text: minimumValue
                    anchors.top: labelMin.top
                    anchors.left: labelMin.right
                    anchors.leftMargin:  Math.round(5 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor

                }

                Label
                {
                    id: labelMax
                    text: BransonNumpadDefine.qmltextMaximum + ":" //qsTr("Max:")
                    anchors.top: txtMax.top
                    anchors.right: txtMax.left
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor
                }

                Text
                {
                    id: txtMax
                    text: maximumValue
                    anchors.top: input.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.right: input.right
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: BransonStyle.blueFontColor

                }

                BransonNumKeyboard
                {
                    id:bransonprimary
                    anchors.top:input.bottom
                    anchors.left: input.left
                    anchors.leftMargin: Math.round(132 * Style.scaleHint)
                }
            }
        }

        BransonPrimaryButton
        {
            id: btnCancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextCancel
            font.family: Style.regular.name
            buttonColor: BransonStyle.backgroundColor
            textColor: "#000000"
            onClicked:
            {
                steppingNumpad.visible = false
            }
        }
        
        BransonPrimaryButton
        {
            id: btnDone
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: btnCancel.top
            anchors.left: btnCancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: BransonNumpadDefine.qmltextDone
            font.family: Style.regular.name
            onClicked:
            {
                /*Decision to be taken as per switch button status*/
                RecipeLabData.WeldAmplitude = (switchbtn.checked) ? stepZeroValueInput.text : input.text
                if(switchbtn.checked)
                {
                    RecipeLabData.NumAmplitudeSteps = (count - 1)
                }

                else
                {
                    RecipeLabData.NumAmplitudeSteps = 0
                }

                RecipeLabData.AmplitudeStepAt = stepTitle.currentIndex

                /*Decision to be taken whether invalid data entry popup should display or not*/
                if(! warningPopupFlag)
                {
                    RecipeLabData.onDonePressedForAmplitude()
                }

                else
                {
                    RecipeLabData.IsParamValid = false
                }

                steppingNumpad.visible = false
            }
        }
    }
}

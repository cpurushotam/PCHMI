/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonMinMaxNumpad.qml accepts the graph setting inputs.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 10/11/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.0
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import Com.Branson.UIScreenEnum 1.0

Item {
    id: primaryNumpad

    property string qmltextTimeScaleSettings           : "TIME SCALE SETTINGS"

    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(411 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headerText
    property string suffix : "s"
    property string getSuffixFirst
    property string getSuffixSecond
    property int decimals  : 4

    property bool  isMultiMinMaxNumpad: true

    property int  firstYAxisSelectedEnum  : GraphAxisEnum.AMP_IDX
    property int  secondYAxisSelectedEnum : GraphAxisEnum.AMP_IDX

    property alias minValue: minInput.text
    property alias maxValue: maxInput.text

    property alias firstMinValue  : multiFirstMinMaxInputMin.text
    property alias firstMaxValue  : multiFirstMinMaxInputMax.text
    property alias secondMinValue : multiSecondMinMaxInputMin.text
    property alias secondMaxValue : multiSecondMinMaxInputMax.text

    property bool isMinInputTextFieldFocused : false
    property bool isMaxInputTextFieldFocused : false

    property bool isMultiFirstMinMaxInputTextFieldFocusedMin   : false
    property bool isMultiFirstMinMaxInputTextFieldFocusedMax   : false
    property bool isMultiSecondMinMaxInputTextFieldFocusedMin  : false
    property bool isMultiSecondMinMaxInputTextFieldFocusedMax  : false

    property bool clearedFirstInputTextFieldMinOnced  : false
    property bool clearedFirstInputTextFieldMaxOnced  : false
    property bool clearedSecondInputTextFieldMinOnced : false
    property bool clearedSecondInputTextFieldMaxOnced : false

    signal invalidInputsEntered()

    function slotDigitalKeyPressed(data)
    {
        switch(firstYAxisSelectedEnum)
        {
        case GraphAxisEnum.AMP_IDX :
            getSuffixFirst = mainWindow.qmltextAmplitudeUnit
            break

        case GraphAxisEnum.POWER_IDX :
            getSuffixFirst = mainWindow.qmltextPowerUnit
            break

        case GraphAxisEnum.FREQ_IDX :
            getSuffixFirst = mainWindow.qmltextFrequencyUnit
            break

        case GraphAxisEnum.PHASE_IDX :
            getSuffixFirst = mainWindow.qmltextPhaseUnit
            break

        case GraphAxisEnum.CURRENT_IDX :
            getSuffixFirst = mainWindow.qmltextCurrentUnit
            break

        case GraphAxisEnum.ENERGY_IDX :
            getSuffixFirst = mainWindow.qmltextEnergyUnit
            break

        case GraphAxisEnum.FORCE_IDX :
            getSuffixFirst = mainWindow.qmltextForceUnit
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX :
            getSuffixFirst = mainWindow.qmltextDistanceUnit
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX :
            getSuffixFirst = mainWindow.qmltextDistanceUnit
            break

        case GraphAxisEnum.VELOCITY_IDX :
            getSuffixFirst = mainWindow.qmltextVelocityUnit
            break

        case GraphAxisEnum.TIME_IDX :
            getSuffixFirst = mainWindow.qmltextTimeUnit
            break

        default :
            getSuffixFirst = mainWindow.qmltextAmplitudeUnit
            break
        }

        switch(secondYAxisSelectedEnum)
        {
        case GraphAxisEnum.AMP_IDX :
            getSuffixSecond = mainWindow.qmltextAmplitudeUnit
            break

        case GraphAxisEnum.POWER_IDX :
            getSuffixSecond = mainWindow.qmltextPowerUnit
            break

        case GraphAxisEnum.FREQ_IDX :
            getSuffixSecond = mainWindow.qmltextFrequencyUnit
            break

        case GraphAxisEnum.PHASE_IDX :
            getSuffixSecond = mainWindow.qmltextPhaseUnit
            break

        case GraphAxisEnum.CURRENT_IDX :
            getSuffixSecond = mainWindow.qmltextCurrentUnit
            break

        case GraphAxisEnum.ENERGY_IDX :
            getSuffixSecond = mainWindow.qmltextEnergyUnit
            break

        case GraphAxisEnum.FORCE_IDX :
            getSuffixSecond = mainWindow.qmltextForceUnit
            break

        case GraphAxisEnum.ABSOLUTEDIST_IDX :
            getSuffixSecond = mainWindow.qmltextDistanceUnit
            break

        case GraphAxisEnum.COLLAPSEDIST_IDX :
            getSuffixSecond = mainWindow.qmltextDistanceUnit
            break

        case GraphAxisEnum.VELOCITY_IDX :
            getSuffixSecond = mainWindow.qmltextVelocityUnit
            break

        case GraphAxisEnum.TIME_IDX :
            getSuffixSecond = mainWindow.qmltextTimeUnit
            break

        default :
            getSuffixSecond = mainWindow.qmltextAmplitudeUnit
            break
        }

        if(! isMultiMinMaxNumpad)
        {
            if(isMinInputTextFieldFocused)
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedFirstInputTextFieldMinOnced)
                {
                    minInput.clear()
                    clearedFirstInputTextFieldMinOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, minInput, suffix)
            }

            else
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedSecondInputTextFieldMaxOnced)
                {
                    maxInput.clear()
                    clearedSecondInputTextFieldMaxOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, maxInput, suffix)
            }
        }

        else
        {
            if(isMultiFirstMinMaxInputTextFieldFocusedMin)
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedFirstInputTextFieldMinOnced)
                {
                    multiFirstMinMaxInputMin.clear()
                    clearedFirstInputTextFieldMinOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, multiFirstMinMaxInputMin, getSuffixFirst)
            }

            else if (isMultiFirstMinMaxInputTextFieldFocusedMax)
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedFirstInputTextFieldMaxOnced)
                {
                    multiFirstMinMaxInputMax.clear()
                    clearedFirstInputTextFieldMaxOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, multiFirstMinMaxInputMax, getSuffixFirst)
            }

            else if (isMultiSecondMinMaxInputTextFieldFocusedMin)
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedSecondInputTextFieldMinOnced)
                {
                    multiSecondMinMaxInputMin.clear()
                    clearedSecondInputTextFieldMinOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, multiSecondMinMaxInputMin, getSuffixSecond)
            }

            else if(isMultiSecondMinMaxInputTextFieldFocusedMax)
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(clearedSecondInputTextFieldMaxOnced)
                {
                    multiSecondMinMaxInputMax.clear()
                    clearedSecondInputTextFieldMaxOnced = false
                }

                BransonNumpadDefine.handleWithDigitalKeyInput(data, multiSecondMinMaxInputMax, getSuffixSecond)
            }
        }
    }

    Component.onCompleted:
    {
        bransonPrimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonPrimary.signalButtonFunc.connect(slotDigitalKeyPressed)
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

        minInput.text = ""
        maxInput.text = ""
        multiFirstMinMaxInputMin.text  = ""
        multiFirstMinMaxInputMax.text  = ""
        multiSecondMinMaxInputMin.text = ""
        multiSecondMinMaxInputMax.text = ""
    }

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea
        {
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
                text: headerText
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
            id: displayForSingleMinMaxInputs
            visible: !(isMultiMinMaxNumpad)
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            width: parent.width
            height: Math.round(75 * Style.scaleHint)
            color: "#FFFFFF"

            Label
            {
                id: labelMin
                text: BransonNumpadDefine.qmltextMinimun  //qsTr("Min:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: minInput
                anchors.top: labelMin.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(80 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,minInput)
                }

                onSignalClickedEvent:
                {
                    clearedFirstInputTextFieldMinOnced = true

                    isMinInputTextFieldFocused = true
                    isMaxInputTextFieldFocused = false
                }
            }

            Label
            {
                id: labelMax
                text: BransonNumpadDefine.qmltextMaximum  //qsTr("Max:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(10 * Style.scaleHint)
                anchors.left: labelMin.right
                anchors.leftMargin: Math.round(120 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: maxInput
                anchors.top: labelMax.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.left: minInput.left
                anchors.leftMargin: Math.round(150 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,maxInput)
                }

                onSignalClickedEvent:
                {
                    clearedSecondInputTextFieldMaxOnced = true

                    isMinInputTextFieldFocused = false
                    isMaxInputTextFieldFocused = true
                }
            }

        }

        Rectangle
        {
            id: displayForMultiMinMaxInputs
            visible: isMultiMinMaxNumpad
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            width: parent.width
            height: Math.round(75 * Style.scaleHint)
            color: "#FFFFFF"

            Rectangle
            {
                id: multiMinMaxMinIndicator
                anchors.top: parent.top
                anchors.topMargin: Math.round(18 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                width: Math.round(8 * Style.scaleHint)
                height: Math.round(8 * Style.scaleHint)
                radius: width/2
                color: AxisDefine.getAxisColor(firstYAxisSelectedEnum)
            }

            Label
            {
                id: multiFirstMinMaxLabelMin
                text: AxisDefine.getAxisTitle(firstYAxisSelectedEnum) + " " + BransonNumpadDefine.qmltextMinimun  //qsTr("Min:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(30 * Style.scaleHint)
                font.pixelSize: Math.round(9 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: multiFirstMinMaxInputMin
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,multiFirstMinMaxInputMin)
                }

                onSignalClickedEvent:
                {
                    clearedFirstInputTextFieldMinOnced = true

                    isMultiFirstMinMaxInputTextFieldFocusedMin  = true
                    isMultiFirstMinMaxInputTextFieldFocusedMax  = false
                    isMultiSecondMinMaxInputTextFieldFocusedMin = false
                    isMultiSecondMinMaxInputTextFieldFocusedMax = false
                }
            }

            Label
            {
                id: multiFirstMinMaxLabelMax
                text: AxisDefine.getAxisTitle(firstYAxisSelectedEnum) + " " + BransonNumpadDefine.qmltextMaximum  //qsTr("Max:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(100 * Style.scaleHint)
                font.pixelSize: Math.round(9 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: multiFirstMinMaxInputMax
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.left: multiFirstMinMaxInputMin.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,multiFirstMinMaxInputMax)
                }

                onSignalClickedEvent:
                {
                    clearedFirstInputTextFieldMaxOnced = true

                    isMultiFirstMinMaxInputTextFieldFocusedMin  = false
                    isMultiFirstMinMaxInputTextFieldFocusedMax  = true
                    isMultiSecondMinMaxInputTextFieldFocusedMin = false
                    isMultiSecondMinMaxInputTextFieldFocusedMax = false
                }
            }

            Rectangle
            {
                id: multiMinMaxMaxIndicator
                anchors.top: parent.top
                anchors.topMargin: Math.round(18 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(215 * Style.scaleHint)
                width: Math.round(8 * Style.scaleHint)
                height: Math.round(8 * Style.scaleHint)
                radius: width/2
                color: AxisDefine.getAxisColor(secondYAxisSelectedEnum)
            }

            Label
            {
                id: multiSecondMinMaxLabelMin
                text: AxisDefine.getAxisTitle(secondYAxisSelectedEnum) + " " + BransonNumpadDefine.qmltextMinimun  //qsTr("Min:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(230 * Style.scaleHint)
                font.pixelSize: Math.round(9 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: multiSecondMinMaxInputMin
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.left: multiFirstMinMaxInputMax.right
                anchors.leftMargin: Math.round(40 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,multiSecondMinMaxInputMin)
                }

                onSignalClickedEvent:
                {
                    clearedSecondInputTextFieldMinOnced = true

                    isMultiFirstMinMaxInputTextFieldFocusedMin  = false
                    isMultiFirstMinMaxInputTextFieldFocusedMax  = false
                    isMultiSecondMinMaxInputTextFieldFocusedMin = true
                    isMultiSecondMinMaxInputTextFieldFocusedMax = false
                }
            }


            Label
            {
                id: multiSecondMinMaxLabelMax
                text: AxisDefine.getAxisTitle(secondYAxisSelectedEnum) + " " + BransonNumpadDefine.qmltextMaximum  //qsTr("Max:")
                anchors.top: parent.top
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(300 * Style.scaleHint)
                font.pixelSize: Math.round(9 * Style.scaleHint)
                font.family: Style.regular.name
                color: "#000000"
            }

            BransonTextField
            {
                id: multiSecondMinMaxInputMax
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                anchors.left: multiSecondMinMaxInputMin.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                onlyForNumpad: true

                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,multiSecondMinMaxInputMax)
                }

                onSignalClickedEvent:
                {
                    clearedSecondInputTextFieldMaxOnced = true

                    isMultiFirstMinMaxInputTextFieldFocusedMin  = false
                    isMultiFirstMinMaxInputTextFieldFocusedMax  = false
                    isMultiSecondMinMaxInputTextFieldFocusedMin = false
                    isMultiSecondMinMaxInputTextFieldFocusedMax = true
                }
            }

        }
        BransonNumKeyboard
            {
                id: bransonPrimary
                anchors.top: displayForSingleMinMaxInputs.bottom
                anchors.topMargin: Math.round(-15  * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
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
            id:done
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
                if(! isMultiMinMaxNumpad)
                {
                    if(parseFloat(minInput.text) < parseFloat(maxInput.text))
                    {
                        GraphSettings.TimeAxisMinValue = minInput.text
                        GraphSettings.TimeAxisMaxValue = maxInput.text

                        ReferenceWeldGraphData.TimeAxisMinValue = minInput.text
                        ReferenceWeldGraphData.TimeAxisMaxValue = maxInput.text
                    }

                    else
                    {
                        invalidInputsEntered()
                    }
                }

                else
                {
                    if((parseFloat(multiFirstMinMaxInputMin.text) < parseFloat(multiFirstMinMaxInputMax.text)) &&
                            (parseFloat(multiSecondMinMaxInputMin.text) < parseFloat(multiSecondMinMaxInputMax.text)))
                    {
                        switch(firstYAxisSelectedEnum)
                        {
                        case GraphAxisEnum.AMP_IDX :

                            GraphSettings.AmpAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.AmpAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.AmpAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.AmpAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.POWER_IDX :

                            GraphSettings.PowerAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.PowerAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.PowerAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.PowerAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.FREQ_IDX :

                            GraphSettings.FreqAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.FreqAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.FreqAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.FreqAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.PHASE_IDX :

                            GraphSettings.PhaseAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.PhaseAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.PhaseAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.PhaseAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.CURRENT_IDX :

                            GraphSettings.CurrentAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.CurrentAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.CurrentAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.CurrentAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.ENERGY_IDX :

                            GraphSettings.EnergyAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.EnergyAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.EnergyAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.EnergyAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.FORCE_IDX :

                            GraphSettings.ForceAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.ForceAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.ForceAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.ForceAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.ABSOLUTEDIST_IDX :

                            GraphSettings.AbsDisAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.AbsDisAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.AbsDisAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.AbsDisAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.COLLAPSEDIST_IDX :

                            GraphSettings.ColDisAxisMinValue = multiFirstMinMaxInputMin.text
                            GraphSettings.ColDisAxisMaxValue = multiFirstMinMaxInputMax.text

                            ReferenceWeldGraphData.ColDisAxisMinValue = multiFirstMinMaxInputMin.text
                            ReferenceWeldGraphData.ColDisAxisMaxValue = multiFirstMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.REQAMP_IDX :

                            GraphSettings.ReqAmpAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.ReqAmpAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.ReqAmpAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.ReqAmpAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.VELOCITY_IDX :

                            GraphSettings.VelocityAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.VelocityAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.VelocityAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.VelocityAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;
                        }

                        switch(secondYAxisSelectedEnum)
                        {
                        case GraphAxisEnum.AMP_IDX :

                            GraphSettings.AmpAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.AmpAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.AmpAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.AmpAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.POWER_IDX :

                            GraphSettings.PowerAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.PowerAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.PowerAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.PowerAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.FREQ_IDX :

                            GraphSettings.FreqAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.FreqAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.FreqAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.FreqAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.PHASE_IDX :

                            GraphSettings.PhaseAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.PhaseAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.PhaseAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.PhaseAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.CURRENT_IDX :

                            GraphSettings.CurrentAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.CurrentAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.CurrentAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.CurrentAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.ENERGY_IDX :

                            GraphSettings.EnergyAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.EnergyAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.EnergyAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.EnergyAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.FORCE_IDX :

                            GraphSettings.ForceAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.ForceAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.ForceAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.ForceAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.ABSOLUTEDIST_IDX :

                            GraphSettings.AbsDisAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.AbsDisAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.AbsDisAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.AbsDisAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.COLLAPSEDIST_IDX :

                            GraphSettings.ColDisAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.ColDisAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.ColDisAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.ColDisAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.REQAMP_IDX :

                            GraphSettings.ReqAmpAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.ReqAmpAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.ReqAmpAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.ReqAmpAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;

                        case GraphAxisEnum.VELOCITY_IDX :

                            GraphSettings.VelocityAxisMinValue = multiSecondMinMaxInputMin.text
                            GraphSettings.VelocityAxisMaxValue = multiSecondMinMaxInputMax.text

                            ReferenceWeldGraphData.VelocityAxisMinValue = multiSecondMinMaxInputMin.text
                            ReferenceWeldGraphData.VelocityAxisMaxValue = multiSecondMinMaxInputMax.text
                            break;
                        }
                    }

                    else
                    {
                        invalidInputsEntered()
                    }
                }

                primaryNumpad.visible = false
            }
        }
    }
}

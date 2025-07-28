/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

    BransonDoubleSwitchBoard.qml file handles suspect & reject display data
    logic.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 07/02/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import QtQuick.Controls 2.0
import Com.Branson.SystemTypeDef 1.0

Item
{
    readonly property int minWidthNumpad: Math.round(248 * Style.scaleHint)
    readonly property int minHeightNumpad: Math.round(236 * Style.scaleHint)
    readonly property int minHeightTextField: Math.round(30 * Style.scaleHint)
    readonly property int fontsize: Math.round(Style.style6 * Style.scaleHint)
    readonly property string backgroundcolor: "#FFFFFF"
    readonly property int buttonNumpadSize: Math.round(50 * Style.scaleHint)
    readonly property string qmltextDigit1:  "1"
    readonly property string qmltextDigit2:  "2"
    readonly property string qmltextDigit3:  "3"
    readonly property string qmltextDigit4:  "4"
    readonly property string qmltextDigit5:  "5"
    readonly property string qmltextDigit6:  "6"
    readonly property string qmltextDigit7:  "7"
    readonly property string qmltextDigit8:  "8"
    readonly property string qmltextDigit9:  "9"
    readonly property string qmltextDigit0:  "0"
    readonly property string qmltextDot:     "."
    readonly property string qmltextBackSpaceSymbol: "⌫"
    readonly property string qmltextClr:     "Clr"
     property string suffix:  "%"
    readonly property real minimumValue: 10
    readonly property real maximumValue: 100
    property int flag: 0

    property string qmlTextTime:             "TIME"
    property string qmlTextEnergy:           "ENERGY"
    property string qmlTextPeakPower:        "PEAK POWER"
    property string qmlTextFrequency:        "FREQUENCY"
    property string qmlTextAbsoluteDistance: "ABSOLUTE DISTANCE"
    property string qmlTextCollapseDistance: "COLLAPSE DISTANCE"
    property string qmlTextTriggerDistance:  "TRIGGER DISTANCE"
    property string qmlTextEndWeldFORCE:     "END WELD FORCE"
    property string qmlTextVelocity:         "VELOCITY"

    property bool isSuspectChecked : false
    property bool isRejectChecked  : false
    property real suspectLowInputValue
    property real rejectLowInputValue
    property real suspectHighInputValue
    property real rejectHighInputValue
    property string selectedSwitch

    property alias suspectLowInput     : inputsecond.text
    property alias rejectLowInput      : input.text
    property alias suspectHighInput    : inputthird.text
    property alias rejectHighInput     : inputfourth.text

    property string qmlTextSuspectLow  : "Suspect Low"
    property string qmlTextRejectLow   : "Reject Low"
    property string qmlTextSuspectHigh : "Suspect High"
    property string qmlTextRejectHigh  : "Reject High"

    property int decimals: 3

    property bool clearedRjectLowOnce    : false
    property bool clearedSuspectLowOnce  : false
    property bool clearedSuspectHighOnce : false
    property bool clearedRejectHighOnce  : false

    QtObject
    {
        id: focusedItemEnum
        readonly property int rejectLowFocusedIdx   : 1
        readonly property int suspectLowFocusedIdx  : 2
        readonly property int suspectHighFocusedIdx : 3
        readonly property int rejectHighFocusedIdx  : 4
    }

    /*Only one decimal point can be entered*/
    function limitinput(text_input)
    {
        var contrast=text_input.text
        var num = contrast.split('.').length -1
        if(num>=2)
        {
            text_input.remove(text_input.cursorPosition-1,text_input.cursorPosition)
        }

    }
    /*Limit the number of digits after the decimal point*/
    function decimalsnumber(decimals,text_input)
    {

        var contrast=text_input.text
        var num = contrast.split('.').length -1
        if(num===1)
        {
            var position=contrast.indexOf(".");

        }
        if(decimals===0)
        {
            text_input.maximumLength=8
            if(num>=1)
            {
                text_input.remove(text_input.cursorPosition-1,text_input.cursorPosition)
            }

        }
        else
        {
            if(position+1+decimals<=8)
            {
                text_input.maximumLength=position+1+decimals
            }
            else
                text_input.maximumLength=8

        }
    }

    function slotDealKeyBoardData(data)
    {
        Qt.inputMethod.hide()
        if(flag === focusedItemEnum.rejectLowFocusedIdx)
        {
            /*To  avoid use of backspace for user to clear text before any entry*/
            if(clearedRjectLowOnce)
            {
                input.clear()
                clearedRjectLowOnce = false
                clearedSuspectLowOnce = true
                clearedSuspectHighOnce = true
                clearedRejectHighOnce = true
            }

            if(data === BransonNumpadDefine.EnumKeyboard.Clear)
            {
                input.remove(0,input.cursorPosition)
            }

            else if(data === BransonNumpadDefine.EnumKeyboard.Delete)
            {
                input.remove(input.cursorPosition-1,input.cursorPosition)
            }

            else
            {
                input.insert(input.cursorPosition,data)
            }
        }

        else if(flag === focusedItemEnum.suspectLowFocusedIdx)
        {
            /*To  avoid use of backspace for user to clear text before any entry*/
            if(clearedSuspectLowOnce)
            {
                inputsecond.clear()
                clearedRjectLowOnce = true
                clearedSuspectLowOnce = false
                clearedSuspectHighOnce = true
                clearedRejectHighOnce = true
            }

            if(data===BransonNumpadDefine.EnumKeyboard.Clear)
            {
                inputsecond.remove(0,inputsecond.cursorPosition)
            }
            else if(data===BransonNumpadDefine.EnumKeyboard.Delete)
            {
                inputsecond.remove(inputsecond.cursorPosition-1,inputsecond.cursorPosition)
            }
            else{
                inputsecond.insert(inputsecond.cursorPosition,data)
            }
        }

        else if(flag === focusedItemEnum.suspectHighFocusedIdx)
        {
            /*To  avoid use of backspace for user to clear text before any entry*/
            if(clearedSuspectHighOnce)
            {
                inputthird.clear()
                clearedRjectLowOnce = true
                clearedSuspectLowOnce = true
                clearedSuspectHighOnce = false
                clearedRejectHighOnce = true
            }

            if(data===BransonNumpadDefine.EnumKeyboard.Clear)
            {
                inputthird.remove(0,inputthird.cursorPosition)
            }
            else if(data===BransonNumpadDefine.EnumKeyboard.Delete)
            {
                inputthird.remove(inputthird.cursorPosition-1,inputthird.cursorPosition)
            }
            else
            {
                inputthird.insert(inputthird.cursorPosition,data)
            }
        }

        else if(flag === focusedItemEnum.rejectHighFocusedIdx)
        {
            /*To  avoid use of backspace for user to clear text before any entry*/
            if(clearedRejectHighOnce)
            {
                inputfourth.clear()
                clearedRjectLowOnce = true
                clearedSuspectLowOnce = true
                clearedSuspectHighOnce = true
                clearedRejectHighOnce = false
            }

            if(data===BransonNumpadDefine.EnumKeyboard.Clear)
            {
                inputfourth.remove(0,inputfourth.cursorPosition)
            }
            else if(data===BransonNumpadDefine.EnumKeyboard.Delete)
            {
                inputfourth.remove(inputfourth.cursorPosition-1,inputfourth.cursorPosition)
            }
            else
            {
                inputfourth.insert(inputfourth.cursorPosition,data)
            }
        }

    }
    Component.onCompleted:
    {
        bransonprimary.signalButtonNum.connect(slotDealKeyBoardData)
        bransonprimary.signalButtonFunc.connect(slotDealKeyBoardData)
    }

    onVisibleChanged:
    {
        /*Clear data once only*/
        if(visible)
        {
            clearedRjectLowOnce = true
            clearedSuspectLowOnce = true
            clearedSuspectHighOnce = true
            clearedRejectHighOnce = true
        }
    }

    Connections
    {
        target:mainWindow
        function onCheckSuspectRejectSwitchButton(bSuspectCheck ,bRejectCheck,realSuspectLow, realSuspectHigh, realRejectLow, realRejectHigh, decimalsVal, unitVal)
        {

            decimals = decimalsVal
             suspectSwitchBtn.checked =bSuspectCheck
            rejectSwitchBtn.checked = bRejectCheck
            inputsecond.text = realSuspectLow
            inputthird.text = realSuspectHigh
            input.text = realRejectLow
            inputfourth.text = realRejectHigh
            suffix = unitVal
        }
    }
    /*switch*/
    Text
    {
        id: suspect
        text: "SUSPECT"
        color: "#757577"
        font.family: Style.regular.name
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(1 * Style.scaleHint)

        anchors.top: parent.top
        anchors.topMargin:Math.round(-25 * Style.scaleHint)
    }

    BransonSwitch
    {
        id:suspectSwitchBtn
        checked: isSuspectChecked
        anchors.left: suspect.right
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(-20 * Style.scaleHint)

        onCheckedChanged:
        {
            isSuspectChecked = checked

            /*Clear data once only*/
            clearedRjectLowOnce = true
            clearedSuspectLowOnce = true
            clearedSuspectHighOnce = true
            clearedRejectHighOnce = true

            if(selectedSwitch == qmlTextTime)
            {
                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextEnergy)
            {

                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextPeakPower)
            {
                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextFrequency)
            {
                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextAbsoluteDistance)
            {
                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextCollapseDistance)
            {

                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextTriggerDistance)
            {

                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextEndWeldFORCE)
            {

                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextVelocity)
            {

                if(checked==true)
                {
                    inputsecond.visible=true
                    inputthird.visible=true
                }

                else if(checked==false)
                {
                    inputsecond.visible=false
                    inputthird.visible=false
                    flag=0
                }
            }
        }
    }

    Text
    {
        id: reject
        
        text: "REJECT"
        color: "#757577"
        font.family: Style.regular.name
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        anchors.left: suspectSwitchBtn.right
        anchors.top: parent.top
        anchors.topMargin: Math.round(-25 * Style.scaleHint)
        anchors.leftMargin: Math.round(50 * Style.scaleHint)
    }

    /*Control input display*/
    BransonSwitch
    {
        id: rejectSwitchBtn

        checked: isRejectChecked
        anchors.top: parent.top
        anchors.topMargin: Math.round(-25 * Style.scaleHint)
        anchors.left: reject.right
        anchors.leftMargin: Math.round(15 * Style.scaleHint)
        onCheckedChanged:
        {
            isRejectChecked = checked

            /*Clear data once only*/
            clearedRjectLowOnce = true
            clearedSuspectLowOnce = true
            clearedSuspectHighOnce = true
            clearedRejectHighOnce = true

            if(selectedSwitch == qmlTextTime)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextEnergy)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextPeakPower)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextFrequency)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextAbsoluteDistance)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextCollapseDistance)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextTriggerDistance)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }

            if(selectedSwitch == qmlTextEndWeldFORCE)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
            if(selectedSwitch == qmlTextVelocity)
            {
                if(checked==true)
                {
                    input.visible=true
                    inputfourth.visible=true
                }

                else
                {
                    input.visible=false
                    inputfourth.visible=false
                    flag=0
                }
            }
        }
    }

    Rectangle
    {
        id: header
        anchors.left: parent.left
        anchors.leftMargin: Math.round(-90 * Style.scaleHint)
        implicitWidth: Math.round(380 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        color: "#AFC3D8"
         TextField
        {
            id: input
            text: (isRejectChecked) ? rejectLowInputValue : ""
            color: "#FFFFFF"
            implicitWidth: Math.round(83 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: header.left
            focus:true
            visible: false
            maximumLength: maxLength
            background: Rectangle
            {
                id:backGroundId
                radius: 2
                color: "#B91819"
                border.color: "#B91819"
                border.width: 1
            }

            onTextChanged:
            {
                limitinput(input)
                decimalsnumber(decimals,input)
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    input.selectAll()
                    animationX.start()
                    flag = focusedItemEnum.rejectLowFocusedIdx
                    input.focus=true
                    Qt.inputMethod.hide()
                }

                onDoubleClicked:
                {
                    input.deselect()
                    input.focus=true
                    Qt.inputMethod.hide()
                }
            }

            Text
            {
                id: name
                anchors.horizontalCenter: parent.horizontalCenter
                y:(rejectSwitchBtn.checked) ? Math.round(-20 * Style.scaleHint) : Math.round(5 * Style.scaleHint)
                text: qmlTextRejectLow
                color: (rejectSwitchBtn.checked) ? "#000000" : "#FFFFFF"
                font.pixelSize:Math.round(Style.style0 * Style.scaleHint)
                font.family: Style.regular.name
            }

            /*Text movement animation*/
            NumberAnimation
            {
                id: animationX
                target: name
                properties:  "y"
                to: Math.round(-20 * Style.scaleHint)
                duration: 500
                onStopped: name.color="#000000"
            }
        }

          TextField
        {
            id: inputsecond
            text: (isSuspectChecked) ? suspectLowInputValue : ""
            color: "#FFFFFF"
            implicitWidth: Math.round(83 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: input.right
            focus:true
            visible: false
   maximumLength: maxLength

            background: Rectangle
            {
                radius: 2
                color: "#FECF22"
                border.color: "#FECF22"
                border.width: 1
            }

            onTextChanged:
            {
                limitinput(inputsecond)
                decimalsnumber(decimals,inputsecond)
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    inputsecond.selectAll()
                    inputsecond.focus=true
                    animationXsecond.start()
                    flag = focusedItemEnum.suspectLowFocusedIdx
                    Qt.inputMethod.hide()
                }
                onDoubleClicked:
                {
                    inputsecond.deselect()
                    inputsecond.focus=true
                    Qt.inputMethod.hide()
                }
            }

            Text
            {
                id: namesecond
                anchors.horizontalCenter: parent.horizontalCenter
                y:(suspectSwitchBtn.checked) ? Math.round(-20 * Style.scaleHint) : Math.round(5 * Style.scaleHint)
                text: qmlTextSuspectLow
                color: (suspectSwitchBtn.checked) ? "#000000" : "#FFFFFF"
                font.pixelSize:Math.round(Style.style0 * Style.scaleHint)
                font.family: Style.regular.name
            }

            NumberAnimation
            {
                id: animationXsecond
                target: namesecond
                properties:  "y"
                to: Math.round(-20 * Style.scaleHint)
                duration: 500
                onStopped: namesecond.color="#000000"
            }
        }

       TextField
        {
            id: inputthird
            text: (isSuspectChecked) ? suspectHighInputValue : ""
            color: "#FFFFFF"
            implicitWidth: Math.round(83 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: rect.right
            focus:true
            visible: false
            maximumLength: maxLength

            background: Rectangle
            {
                radius: 2
                color: "#FECF22"
                border.color: "#FECF22"
                border.width: 1
            }

            onTextChanged:
            {
                limitinput(inputthird)
                decimalsnumber(decimals,inputthird)
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    inputthird.selectAll()
                    inputthird.focus=true
                    animationXthird.start()
                    flag = focusedItemEnum.suspectHighFocusedIdx
                    Qt.inputMethod.hide()
                }

                onDoubleClicked:
                {
                    inputthird.deselect()
                    inputthird.focus=true
                    Qt.inputMethod.hide()
                }
            }

            Text
            {
                id: namethird
                anchors.horizontalCenter: parent.horizontalCenter
                y:(suspectSwitchBtn.checked) ? Math.round(-20 * Style.scaleHint) : Math.round(5 * Style.scaleHint)
                text: qmlTextSuspectHigh
                color: (suspectSwitchBtn.checked) ? "#000000" : "#FFFFFF"
                font.pixelSize:Math.round(Style.style0 * Style.scaleHint)
                font.family: Style.regular.name
            }

            NumberAnimation
            {
                id: animationXthird
                target: namethird
                properties:  "y"
                to:Math.round(-20 * Style.scaleHint)
                duration: 500
                onStopped: namethird.color="#000000"
            }
        }

       TextField
        {
            id: inputfourth
            text: (isRejectChecked) ? rejectHighInputValue : ""
            color: "#FFFFFF"
            implicitWidth: Math.round(83 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: inputthird.right
            focus:false
            visible: false
            maximumLength: maxLength

            background: Rectangle
            {
                radius: 2
                color: "#B91819"
                border.color: "#B91819"
                border.width: 1
            }

            onTextChanged:
            {
                limitinput(inputfourth)
                decimalsnumber(decimals,inputfourth)
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    inputfourth.selectAll()
                    inputfourth.focus=true
                    animationXfourth.start()
                    flag = focusedItemEnum.rejectHighFocusedIdx
                    Qt.inputMethod.hide()
                }

                onDoubleClicked:
                {
                    inputfourth.deselect()
                    inputfourth.focus=true
                    Qt.inputMethod.hide()
                }
            }

            Text
            {
                id: namefourth
                anchors.horizontalCenter: parent.horizontalCenter
                y:(rejectSwitchBtn.checked) ? Math.round(-20 * Style.scaleHint) : Math.round(5 * Style.scaleHint)
                text: qmlTextRejectHigh
                color: (rejectSwitchBtn.checked) ? "#000000" : "#FFFFFF"
                font.pixelSize:Math.round(Style.style0 * Style.scaleHint)
                font.family: Style.regular.name
            }

            NumberAnimation
            {
                id: animationXfourth
                target: namefourth
                properties:  "y"
                to: Math.round(-20 * Style.scaleHint)
                duration: 500
                onStopped: namefourth.color="#000000"
            }
        }

        Rectangle
        {
            id:rect
            implicitWidth: Math.round(48 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: inputsecond.right
            color: "transparent"
            Image
            {
                id: imageCheckMark
                anchors.fill: parent
                source: "qrc:/Images/checkmark_green.svg"
                sourceSize.width: imageCheckMark.width
                sourceSize.height: imageCheckMark.height
                smooth: true
            }
        }
    }

    BransonNumKeyboard
    {
        id:bransonprimary
        anchors.top: header.bottom
        anchors.topMargin: Math.round(-10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(100 * Style.scaleHint)
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import Style 1.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.1
Item {
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
    readonly property string qmltextClr:     qsTr("Clr")
    readonly property string suffix:  "%"
    readonly property int decimals: 2
    readonly property real minimumValue: 10
    readonly property real maximumValue: 100
    property int flag: 0
    function limitinput(text_input)
    {
        var contrast=text_input.text
        var num = contrast.split('.').length -1
        if(num>=2)
        {
            text_input.remove(text_input.cursorPosition-1,text_input.cursorPosition)
        }

    }
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
        if(flag===1)
        {
            if(data===BransonNumpadDefine.EnumKeyboard.Clear)
            {
                input.remove(0,input.cursorPosition)
            }
            else if(data===BransonNumpadDefine.EnumKeyboard.Delete)
            {
                input.remove(input.cursorPosition-1,input.cursorPosition)
            }
            else{
                input.insert(input.cursorPosition,data)
            }
        }
        else if(flag===2)
        {
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

    }
    Component.onCompleted: {
        bransonprimary.signalButtonNum.connect(slotDealKeyBoardData)
        bransonprimary.signalButtonFunc.connect(slotDealKeyBoardData)
    }
    Text {
        id: suspect
        text: qsTr("SETUP")
        color: "#757577"
        font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
        font.family: Style.regular.name
        anchors.left: parent.left
        anchors.leftMargin: Math.round(70 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin:Math.round(-10 * Style.scaleHint)
    }
    BransonSwitch
    {
        anchors.top: parent.top
        anchors.topMargin: Math.round(-8* Style.scaleHint)
        anchors.left: suspect.right
        anchors.leftMargin: Math.round(15 * Style.scaleHint)
        id:switchbtn
        onCheckedChanged:
        {
            if(checked==true)
            {
                inputsecond.visible=true
                input.visible=true
            }
            else if(checked==false)
            {
                inputsecond.visible=false
                input.visible=false
                flag=0
            }
        }
    }
    Rectangle
    {
        id:header
        anchors.left: parent.left
        anchors.leftMargin: Math.round(-5 * Style.scaleHint)
        implicitWidth: Math.round(258 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        color: "#AFC3D8"
        TextField
        {
            implicitWidth: Math.round(87 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: header.left
            id: input
            focus:true
            maximumLength:8
            visible: false
            /*TextField style*/
//            style: TextFieldStyle {
//                id: textStyleId
//                font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
//                textColor: "#FFFFFF"
//                placeholderTextColor:"#FFFFFF"
//                background: Rectangle {
//                    id:backGroundId
//                    radius: 2
//                    color: "#99CCFF"
//                    border.color: "#99CCFF"
//                    border.width: 1
//                }
//            }
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
                    input.focus=true
                    animationX.start()
                    flag=1
                    Qt.inputMethod.hide()
                }
                onDoubleClicked:
                {
                    input.deselect()
                    input.focus=true
                    Qt.inputMethod.hide()
                }
            }
            Text {
                id: name
                x:Math.round(40 * Style.scaleHint)
                y:Math.round(2 * Style.scaleHint)
                text: qsTr("1")
                color: "#FFFFFF"
                font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.regular.name
            }
            NumberAnimation{
                id: animationX
                target: name
                properties:  "y"
                to: Math.round(-24 * Style.scaleHint)
                duration: 500
                onStopped: name.color="#000000"
            }
        }
        TextField
        {
            implicitWidth: Math.round(83 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: rect.right
            focus:true
            id:inputsecond
            visible: false
            maximumLength:8
            /*TextField style*/
//            style: TextFieldStyle {
//                font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
//                textColor: "#FFFFFF"
//                background: Rectangle {
//                    radius: 2
//                    color: "#99CCFF"
//                    border.color: "#99CCFF"
//                    border.width: 1
//                }
//            }
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
                    flag=2
                    Qt.inputMethod.hide()
                }
                onDoubleClicked:
                {
                    inputsecond.deselect()
                    inputsecond.focus=true
                    Qt.inputMethod.hide()
                }
            }
            Text {
                id: namesecond
                x:Math.round(20 * Style.scaleHint)
                y:Math.round(2 * Style.scaleHint)
                text: qsTr("4000")
                color: "#FFFFFF"
                font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.regular.name
            }
            NumberAnimation{
                id: animationXsecond
                target: namesecond
                properties:  "y"
                to: Math.round(-24 * Style.scaleHint)
                duration: 500
                onStopped: namesecond.color="#000000"
            }
        }
        Rectangle
        {
            id:rect
            implicitWidth: Math.round(87 * Style.scaleHint)
            implicitHeight: minHeightTextField
            anchors.left: input.right
            color: "transparent"
            Image {
                id: imageCheckMark
                anchors.centerIn: parent
                width: Math.round(40 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
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
        anchors.top:header.bottom
        anchors.left: parent.left
        anchors.leftMargin: Math.round(130 * Style.scaleHint)
    }
}

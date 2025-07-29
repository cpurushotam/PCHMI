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
    readonly property int minHeightTextField: Math.round(40 * Style.scaleHint)
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
    property int flag:0
    property color inputbackground: "#17345C"
    function slotDealKeyBoardData(data)
    {
        input.focus=true
        Qt.inputMethod.hide()
        if(input.readOnly===false)
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
    }
    Component.onCompleted: {
        bransonprimary.signalButtonNum.connect(slotDealKeyBoardData)
        bransonprimary.signalButtonFunc.connect(slotDealKeyBoardData)
    }
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

    Text {
        id: switchtext
        text: qsTr("CONTROL LIMIT")
        color: "#757577"
        font{
            family: Style.regular.name
            pixelSize: fontSize
        }
        anchors.top: parent.top
        anchors.right: switchbtn.left
        anchors.rightMargin: Math.round(15 * Style.scaleHint)
    }
    BransonSwitch
    {
        id:switchbtn
        anchors.top: switchtext.top
        anchors.topMargin: Math.round(2 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(50 * Style.scaleHint)
        checked: false
        onCheckedChanged:
        {
            if(checked==false)
            {
                input.readOnly=true
                mytest.visible=false
                flag=0
                /*Control input box background*/
                inputbackground="#17345C"
            }
            else if(checked==true)
            {
                input.readOnly=false
                mytest.visible=true
                flag=1
                inputbackground="#E8E8E8"
            }
        }
    }
    TextField
    {
        anchors.top: parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        implicitWidth: Math.round(260 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        id: input
        focus:true
        readOnly: true
        maximumLength:decimalsnumber(1,input)
        font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
//        textColor: "#6699CC"
        /*TextField style*/
//        style: TextFieldStyle {
//            id: textStyleId
//            background: Rectangle
//            {
//                radius: 2
//                color: inputbackground
//                border.color: "#6699CC"
//                border.width: 1
//            }
//        }
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
                Qt.inputMethod.hide()

            }
            onDoubleClicked:
            {
                input.deselect()
                input.focus=true
                Qt.inputMethod.hide()
            }
        }
    }
    Text {
        id: mytest
        text: suffix
        visible: false
        anchors.right: input.right
        anchors.rightMargin: Math.round(5 * Style.scaleHint)
        anchors.top: input.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        color: "#000000"
        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        font.family: Style.regular.name
    }
    BransonNumKeyboard
    {
        id:bransonprimary
        anchors.top:input.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }


}

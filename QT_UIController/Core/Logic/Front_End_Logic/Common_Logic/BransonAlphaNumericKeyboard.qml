/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/

import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: keyboard
    property int minKeyboardWidth        : Math.round(400 * Style.scaleHint)
    property int maxKeyboardHeight       : Math.round(411 * Style.scaleHint)
    property int headerMaxHeight         : Math.round(30 * Style.scaleHint)
    property int textFieldWidth          : Math.round(246 * Style.scaleHint)
    property int textFieldHeight         : Math.round(30 * Style.scaleHint)
    property color backgroundColor       : Style.backgroundColor
    property color textFontColor         : Style.blueFontColor
    property color borderColor           : Style.backgroundColor
    property string placeHolderText      : "Default"
    property color placeHolderTextColor  : Style.placeHolderTextColor
    property string headertext           : "Keyboard"
    property string suffix               : "Default"
    property alias text                  : alphaNumericKeyboardTextField.text
    property alias value                 : input.text

    property real entryErrorCode         : 0

    property bool isNumeric              : false
    property bool isPassword             : false

    signal textFieldClicked()
    signal dataEntered(string value)

    /*For only alphanumeric keyboard*/
    Item{
        id: alphaNumericKeyboard
        visible: !(isNumeric)
        TextField {
            id: alphaNumericKeyboardTextField
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: false
            implicitWidth: textFieldWidth
            implicitHeight: textFieldHeight
            maximumLength: 32
            placeholderText: placeHolderText
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            echoMode: (isPassword) ? TextInput.Password : TextInput.Normal
            readOnly: false

            /*TextField style*/
//            style: TextFieldStyle {
//                id: textStyleId
//                placeholderTextColor: placeHolderTextColor
//                font.pixelSize:Math.round(Style.style4 * Style.scaleHint)
//                textColor: textFontColor
//                background: Rectangle {
//                    id:backGroundId
//                    radius: 2
//                    color: (enabled === true) ? "#ffffff" : Style.backgroundColor
//                    border.color: Style.activeFrameBorderColor
//                    border.width: 1
//                }
//            }

            MouseArea{
                id: confirmPasswordMouseArea
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked:
                {
                    /*Below part makes sure the handling of focus is proper, as forceActiveFocus() stays active always*/
                    if(! Qt.inputMethod.visible)
                        alphaNumericKeyboardTextField.focus = false
                    alphaNumericKeyboardTextField.forceActiveFocus()
                    textFieldClicked()
                }
            }
        }
    }

    /*For only numeric keyboard*/
    Item {
        id: numericKeyboard
        visible: !alphaNumericKeyboard.visible
        anchors.fill: parent

        function slotDigitalKeyPressed(data)
        {
            textErrorMessage.visible = false
            BransonNumpadDefine.handleWithDigitalKeyInput(data, input, suffix)
        }

        Component.onCompleted: {
            bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
            bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
        }


        Rectangle {
            id: background
            anchors.fill: parent
            color: Style.dialogBackgroundColor
            opacity: 0.75
            MouseArea {
                anchors.fill: parent
            }
        }

        Rectangle{
            id:root
            implicitWidth: minKeyboardWidth
            implicitHeight: maxKeyboardHeight
            anchors.centerIn: parent
            color: "#FFFFFF"
            /*header title*/
            Rectangle{
                id: numpadHeader
                width: parent.width
                implicitHeight: headerMaxHeight
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

                Rectangle{
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
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            textErrorMessage.visible = false
                            keyboard.visible = false
                        }
                    }
                }
            }
            /*main keyboard*/
            Rectangle{
                anchors.top: numpadHeader.bottom
                anchors.left: numpadHeader.left
                anchors.topMargin: Math.round(0* Style.scaleHint)
                anchors.leftMargin: Math.round(200 * Style.scaleHint)

                BransonTextField{
                    id: input
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(22 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: Math.round(260 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    focus: true
                    onlyForNumpad: true
                    echoMode: (isPassword) ? TextInput.Password : TextInput.Normal

                    Image {
                        id: imageErrorInfo
                        height: Math.round(18 * Style.scaleHint)
                        width: Math.round(18 * Style.scaleHint)
                        source: "qrc:/Images/Exclaim-Circle-Red30.svg"
                        sourceSize.width:  imageErrorInfo.width
                        sourceSize.height: imageErrorInfo.height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: Math.round(8 * Style.scaleHint)
                        visible: textErrorMessage.visible
                    }

                }

                Text {
                    id: textErrorMessage
                    anchors.left: input.left
                    anchors.top: input.bottom
                    anchors.topMargin: Math.round(4 * Style.scaleHint)
                    height: Math.round(44 * Style.scaleHint)
                    text: BransonNumpadDefine.qmltextInvalidValueMsg
                    font.family: Style.light.name
                    color: Style.errorMsgTextColor
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                    visible: false
                    wrapMode: Text.WordWrap
                }

                BransonNumKeyboard{
                    id:bransonprimary
                    anchors.top:input.bottom
                    anchors.topMargin: Math.round(8 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            /*bottom keyboard*/
            BransonPrimaryButton{
                id:cancel
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
                onClicked:{
                    textErrorMessage.visible = false
                    keyboard.visible = false
                }
            }

            BransonPrimaryButton{
                id:done
                implicitWidth: Math.round(124 * Style.scaleHint)
                implicitHeight: Math.round(30 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.top: cancel.top
                anchors.left: cancel.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                text: BransonNumpadDefine.qmltextDone
                font.family: Style.regular.name
                onClicked:{
                    /*isTextValid function needed only when IP address validation is required*/
                    if(suffix === ("IPV4"||"IPV6"))
                    {
                        if(BransonNumpadDefine.isTextValid(input))
                        {
                            textErrorMessage.visible = false
                            keyboard.visible = false
                            dataEntered(value)
                        }

                        else if(input.text !== "")
                        {
                            textErrorMessage.text = BransonNumpadDefine.qmltextInvalidValueMsg
                            textErrorMessage.visible = true
                        }

                        else
                        {
                            textErrorMessage.text = BransonNumpadDefine.qmltextBlankMsg
                            textErrorMessage.visible = true
                        }
                    }

                    else if(input.text === "")
                    {
                        textErrorMessage.text = BransonNumpadDefine.qmltextBlankMsg
                        textErrorMessage.visible = true
                    }

                    else
                    {
                        textErrorMessage.visible = false
                        keyboard.visible = false
                        dataEntered(value)
                    }
                }
            }
        }
    }
}

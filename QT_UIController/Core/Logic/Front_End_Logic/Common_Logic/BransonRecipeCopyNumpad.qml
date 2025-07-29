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
import Com.Branson.SystemTypeDef 1.0

Item {
    id: primaryNumpad

    property string headertext   : "COPY RECIPE NUMBER"
    property int minWidth        : Math.round(400 * Style.scaleHint)
    property int maxHeight       : Math.round(411 * Style.scaleHint)
    property int headermaxHeight : Math.round(30 * Style.scaleHint)
    property int decimals        : 2
    property alias value         : input.text
    property int sourceRecipeNo
    property bool clearedOnce    : false

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    function slotDigitalKeyPressed(data)
    {
        /*To  avoid use of backspace for user to clear text before any entry*/
        if(clearedOnce)
        {
            input.clear()
            clearedOnce = false
        }

        BransonNumpadDefine.handleWithDigitalKeyInput(data, input, "Default")
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
                width: Math.round(240 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                focus: true
                onlyForNumpad: true
                onTextChanged:
                {
                    BransonNumpadDefine.decimalsNumber(decimals,input)
                }
            }

            BransonNumKeyboard
            {
                id:bransonprimary
                anchors.top:input.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        /*bottom keyboard*/
        BransonPrimaryButton
        {
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
                RecipeModel.initiateRecipeCopyRequest(sourceRecipeNo, input.text, false)
                primaryNumpad.visible = false
            }
        }
    }
}

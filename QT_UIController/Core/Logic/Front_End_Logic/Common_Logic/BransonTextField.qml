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
//import QtQuick.Controls.Styles 1.4
import Style 1.0

TextField {
    id: bransonTextField
    property bool onlyForNumpad: false
    property bool isSelectedAll: false
    signal signalClickedEvent()

    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
    font.family: Style.regular.name
    font.bold: false
    implicitWidth: parent.width
    implicitHeight: parent.height
    focus: true
    maximumLength: 32
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter
    placeholderText: ""
//    validator: RegExpValidator
//    {
//        regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
//    }
    Component.onCompleted:
    {
        Qt.inputMethod.hide()
    }

    /*TextField style*/
//    style: TextFieldStyle {
//        id: textStyleId
//        placeholderTextColor: Style.placeHolderTextColor
//        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
//        textColor: Style.blueFontColor
//        background: Rectangle {
//            id:backGroundId
//            radius: 2
//            color: (enabled === true) ? "#ffffff" : Style.backgroundColor
//            border.color: Style.activeFrameBorderColor
//            border.width: 1
//        }
//    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            if(parent.onlyForNumpad === true)
            {
                parent.selectAll()
                isSelectedAll = true
            }
            signalClickedEvent()
            parent.focus = true
            Qt.inputMethod.hide()
        }
        onDoubleClicked:
        {
            if(parent.onlyForNumpad === true)
            {
                parent.deselect()
                input.focus = true
                Qt.inputMethod.hide()
                isSelectedAll = false
            }
            signalClickedEvent()
        }
    }
}

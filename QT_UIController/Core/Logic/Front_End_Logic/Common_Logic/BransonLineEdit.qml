/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.15
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.1
import Com.Branson.SystemTypeDef 1.0
import Style 1.0
TextField {
    id: input
    property int minWidth: Math.round(350 * Style.scaleHint)
    property int maxHeight: Math.round(30 * Style.scaleHint)
//    property alias readOnlyText: input.readOnly
//    property alias echoMode: input.echoMode
//    property alias text: input.text
    property color backgroundcolor: Style.backgroundColor
    property color textfieldcolor: Style.blackFontColor
    property color bordercolor: Style.backgroundColor
    property bool isBatchIDField: false
    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
    font.family: Style.regular.name
    font.bold: false
    implicitWidth: minWidth
    implicitHeight: maxHeight
    maximumLength: 50
    echoMode:TextInput.Normal
    readOnly: false
    verticalAlignment: TextInput.AlignVCenter
    validator: RegularExpressionValidator
    {
        regularExpression: (! isBatchIDField) ? /^[a-zA-Z0-9`!@#$%&*()_+={}:;<>.?-]*$/ : /^[a-zA-Z0-9]+$/
    }

    /*TextField style*/
//    style: TextFieldStyle {
//        id: textStyleId
//        font.pixelSize:Math.round(Style.style6 * Style.scaleHint)
//        textColor: textfieldcolor
//        background: Rectangle {
//            id:backGroundId
//            radius: 2
//            color: "transparent"
//        }
//    }
}

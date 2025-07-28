/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.6
//import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import Style 1.0

Button {
    readonly property string qmltextfunctionbutton : qsTr("SECONDARY")
    id: functionbutton
    text:qmltextfunctionbutton
    property int minWidth: Math.round(140 * Style.scaleHint)
    property int minHeight: Math.round(40 * Style.scaleHint)
    property int radiusWidth: 3
    property int fontSize: Math.round(Style.style6 * Style.scaleHint)
    property color buttonColor: "#E8E8E8"
    property color textColor : "#6699CC"
    property color shadowColor: "#80000000"
    /*Text in function keyboard*/
    contentItem: Text {
        text: functionbutton.text
        font{
            family: Style.regular.name
            pixelSize: fontSize
            capitalization: Font.AllUppercase
        }
        color: textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    /*Background in function keyboard*/
    background: Rectangle {
        id: buttonRect
        implicitWidth: minWidth
        implicitHeight: minHeight
        color: functionbutton.buttonColor
        radius: radiusWidth
        layer.enabled: functionbutton.pressed ? false : true
//        layer.effect: DropShadow{
//            source: buttonRect
//            anchors.fill: buttonRect
//            horizontalOffset: functionbutton.pressed ? 0 : 3
//            verticalOffset: functionbutton.pressed ? 0 : 3
//            color: shadowColor
//            opacity: 0.2
//            samples: 10
//        }
    }
}

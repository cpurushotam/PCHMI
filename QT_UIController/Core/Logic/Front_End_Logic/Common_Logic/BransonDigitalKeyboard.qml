/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.1
////import QtGraphicalEffects 1.0
import Style 1.0

Button{
    id: digiaal
    property int minWidth: Math.round(50 * Style.scaleHint)
    property int minHeight: Math.round(50 * Style.scaleHint)
    property int radiusWidth: 3
    property int fontSize: Math.round(Style.style6 * Style.scaleHint)
    property bool operator: false
    property string buttonColor: "#6699CC"
    property string textColor: "#FFFFFF"
    property string shadowColor: "#80000000"
    property alias name: digiaal.text
    /*Number in numeric keyboard*/
    contentItem: Text {
        text: digiaal.text
        color: textColor
        font{
            family: Style.regular.name
            pixelSize: fontSize
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    /*Background in numeric keyboard*/
    background: Rectangle {
        id:primaryRect
        color: buttonColor
        implicitWidth: minWidth
        implicitHeight: minHeight
        border.width:  1
        border.color: buttonColor
        radius: radiusWidth
        layer.enabled: digiaal.pressed ? false: true
//        layer.effect: DropShadow{
//            anchors.fill: primaryRect
//            horizontalOffset: digiaal.pressed ? 0 : 3
//            verticalOffset: digiaal.pressed ? 0 : 3
//            color: shadowColor
//            opacity: 0.2
//            source: primaryRect
//        }
    }
}

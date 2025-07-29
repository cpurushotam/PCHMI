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
//import QtGraphicalEffects 1.0
import Style 1.0
Button{
    id: primaryIcon
    property int maxWidth:Math.round(50 * Style.scaleHint)
    property int maxHeight: Math.round(50 * Style.scaleHint)
    property int radiusWidth: 3
    property int fontSize:Math.round(Style.style5 * Style.scaleHint)
    property bool operator: false
    property string fontFamily: Style.regular.name
    property string selectedColor: "#ECECEC"
    property string buttonColor: "#68A4EB"
    property string textColor: "#FFFFFF"
    property string shadowColor: "#80000000"
    property alias name: primaryIcon.text
    property alias primaryIcon: primaryIcon


    contentItem: Text {
        text: primaryIcon.text
        color: textColor
        font{
            family: fontFamily
            pixelSize: fontSize
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        id:primaryRect
        color: buttonColor
        implicitWidth: maxWidth
        implicitHeight: maxHeight
        border.width:  1
        border.color: buttonColor
        radius: radiusWidth
        layer.enabled: primaryIcon.pressed ? false: true 
//        layer.effect: DropShadow{
//            anchors.fill: primaryRect
//            horizontalOffset: primaryIcon.pressed ? 0 : 3
//            verticalOffset: primaryIcon.pressed ? 0 : 3
//            color: shadowColor
//            opacity: 0.2
//            source: primaryRect
//        }
    } 
}

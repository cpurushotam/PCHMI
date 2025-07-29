/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

Button
{
    readonly property string qmltextPrimary: qsTr("PRIMARY")
    id: primaryButton
    text: qmltextPrimary

    property int minWidth: 140
    property int maxHeight: 40
    property int radiusWidth: 3
    property color buttonColor: "#6699CC"
    property color textColor : "#FFFFFF"
    property color shadowColor: "#80000000"
    property int fontSize: Math.round(Style.style2 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    contentItem: Text
    {
        text: qsTr(primaryButton.text)
        font
        {
            family: Style.semibold.name
            pixelSize: fontSize
            capitalization: Font.AllUppercase
        }
        color: textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        lineHeight: 0.75
    }

    background: Rectangle
    {
        id: buttonRect
        color: buttonColor
        radius: radiusWidth
        layer.enabled: primaryButton.pressed ? false : true
        layer.effect: DropShadow
        {
            horizontalOffset: primaryButton.pressed ? 0 : 3
            verticalOffset: primaryButton.pressed ? 0 : 3
            color:  shadowColor
            opacity: 0.2
//            samples: 10
        }
    }
}


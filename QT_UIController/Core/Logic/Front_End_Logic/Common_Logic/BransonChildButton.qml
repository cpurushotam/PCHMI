/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.SystemTypeDef 1.0

Button {
    property color buttonColor: Style.buttonBackgroundColor
    signal childButtonClicked()
   // enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    width: parent.width
    height: parent.height
    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
    font.family: Style.regular.name
    highlighted: true

    background: Rectangle {
        color: buttonColor
        radius: 4
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            childButtonClicked()
        }
    }
}


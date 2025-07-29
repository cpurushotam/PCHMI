/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

RadioButton {
    id: radioButton

    signal radioButtonClick()
    property string labelText: ""
    property string offColor: Style.blackFontColor
    property string onColor: Style.blueFontColor
    property color radioEnableColor: "#004b8d"

    property int circleSize: Math.round(20 * Style.scaleHint)
    property int textSize:Math.round(12 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    indicator: Rectangle {
        implicitWidth: circleSize
        implicitHeight: circleSize
        radius: 45
        border.color: (checked === true && enabled === true) ? radioEnableColor : Style.frameBorderColor
        border.width: Math.round(2 * Style.scaleHint)
        Rectangle {
            anchors.fill: parent
            visible: checked
            color: enabled === true ? radioEnableColor : Style.frameBorderColor
            radius: 45
            anchors.margins: Math.round(4 * Style.scaleHint)
        }
    }
    Text{
        text: labelText
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: textSize
        leftPadding: Math.round(23 * Style.scaleHint)
        topPadding: Math.round(2 * Style.scaleHint)
    }
    onClicked: {
        radioButtonClick()
    }
}

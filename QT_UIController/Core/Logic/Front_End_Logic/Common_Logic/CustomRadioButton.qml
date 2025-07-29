/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Authentication key EEprom class functions for Authentication key read and write
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Style 1.0


RadioButton {
    id: radioButton

    signal radioButtonClick()
    property alias buttonGroup: radioButton.exclusiveGroup
    property alias radiobuttontext: radioButton.text
    property string fontFamily: " "
    property string labelText: " "
    property string offColor: "#898d96"
    property string onColor: "#000000"

    readonly property int circleSize: Math.round(20 * Style.scaleHint)

    text: labelText

    style: RadioButtonStyle {
        spacing: 5
        indicator: Rectangle {
            implicitWidth: circleSize
            implicitHeight: circleSize
            radius: 45
            border.color: control.checked === true ? "#004b8d" : "#666666"
            border.width: Math.round(2 * Style.scaleHint)
            Rectangle {
                anchors.fill: parent
                visible: control.checked
                color: "#004b8d"
                radius: 45
                anchors.margins: Math.round(4 * Style.scaleHint)
            }
        }
        label: Text {
            color: control.checked === true ? onColor : offColor
            text: radioButton.text
            wrapMode: Text.WordWrap
            font.family: fontFamily
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        }
    }
    onClicked: {
        radioButtonClick()
    }
}

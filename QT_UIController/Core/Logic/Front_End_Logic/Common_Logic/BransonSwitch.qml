/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.12
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

Switch {
    property int    rectWidth: Math.round(55 * Style.scaleHint)
    property int    rectHeight: Math.round(12 * Style.scaleHint)
    property int    maxWidth: Math.round(22 * Style.scaleHint)
    property int    maxHeight: Math.round(22 * Style.scaleHint)
    property string offColor: "#666666"
    property string onColor: "#007BFF"
    property string baroffColor: "#C7C7C7"
    property string barOnColor: "#004B8D"
    property alias  innerRect: circle
    property alias  outerRect: bar
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
    id: switchID
    implicitWidth: rectWidth
    implicitHeight: rectHeight
    checked: false
    //border style
    indicator: Rectangle {
        id:bar
        implicitWidth: rectWidth
        implicitHeight: rectHeight
        radius: bar.height / 2
        color: (checked === true && enabled === true) ? barOnColor : baroffColor
        border.color: (checked === true && enabled === true) ? barOnColor : baroffColor
        MouseArea{
            anchors.fill: bar
            onClicked: {
                switchID.checked =! switchID.checked
            }
        }
        //Switch button style
        Rectangle {
            id:circle
            x: checked ? bar.width - circle.width : 0
            anchors.verticalCenter: bar.verticalCenter
            implicitWidth: maxWidth
            implicitHeight: maxHeight
            color: (checked === true && enabled === true) ? onColor : offColor
            radius: circle.height
            border.color: (checked === true && enabled === true) ? onColor : offColor
            opacity: 1.0
            MouseArea{
                anchors.fill: circle
                onClicked: {
                    switchID.checked=!switchID.checked
                }
            }
            Behavior on x {
                NumberAnimation { duration: 150 }
            }
        }
    }
}

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
import Qt5Compat.GraphicalEffects
import Style 1.0

Item
{
    readonly property int barHeight: Math.round(30 * Style.scaleHint)
    readonly property color shadowColor: "#80000000"
    property string fontFamily: " "
    property real  progressValue: 0.0
    property real  progressActualValue: 0.0
    property string progressTitle: qsTr("Peak Power")
    id: progressBar
    ProgressBar
    {
        id: control
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: barHeight
        padding: 2
        value: progressValue
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: Style.backgroundColor
            radius: 3
        }
        contentItem: Item {
            implicitHeight: parent.height
            implicitWidth: parent.width
            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                radius: 2
                LinearGradient
                {
                    anchors.fill: parent
                    start: Qt.point(0, 0)
                    end: Qt.point(parent.width, 0)
                    gradient: Gradient {
                        GradientStop {position: 0.0; color: "#3d7ab3"}
                        GradientStop {position: 1.0; color: "#004b8d"}
                    }
                }
            }

        }
        layer.enabled: true
//        layer.effect: DropShadow{
//            horizontalOffset: 1
//            verticalOffset: 1
//            color: shadowColor
//            opacity: 0.2
//            source: control
//        }
    }

    Text {
        id: txtProgressValue
        anchors.centerIn: control
        text: Math.round(progressActualValue).toString() + " W"
        font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
        font.family: fontFamily
        color: control.value <= 0.5 ? Style.blackFontColor : Style.whiteFontColor;
    }
    Text {
        id: txtProgreeTitle
        anchors.left: control.left
        anchors.bottom: control.top
        anchors.bottomMargin: 10
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
        font.family: fontFamily
        color: Style.blackFontColor
        text: progressTitle
    }
}


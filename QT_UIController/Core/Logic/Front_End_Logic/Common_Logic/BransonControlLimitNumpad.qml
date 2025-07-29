/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.2
import Style 1.0
Item {
    id: controlLimitNumpad
    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(411 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headerColor: Style.headerBackgroundColor
    property string headertext: "PEAK POWER CUTOFF"
    property string headertextColor: "#FFFFFF"
    property int fontSize: Math.round(Style.style2 * Style.scaleHint)
    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }
    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight:maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        Rectangle
        {
            id:header
            width: parent.width
            implicitHeight: headermaxHeight
            color: headerColor
            Text {
                id: headername
                anchors.left: header.left
                anchors.top: header.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headertext
                color: headertextColor
                font{
                    family: Style.regular.name
                    pixelSize: fontSize
                }
            }
            Rectangle
            {
                id:rectimage
                implicitWidth: Math.round(24 * Style.scaleHint)
                implicitHeight: Math.round(24 * Style.scaleHint)
                anchors.right: header.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: header.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                color: "transparent"
                Image {
                    id: headercls
                    anchors.fill: parent
                    source: "qrc:/Images/crossMark.svg"
                    sourceSize.width: headercls.width
                    sourceSize.height: headercls.height
                    smooth: true
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        controlLimitNumpad.visible = false
                    }
                }
            }
        }
        BransonSwitchBoard
        {
            anchors.top: header.bottom
            anchors.left: header.left
            anchors.topMargin: Math.round(0 * Style.scaleHint)
            anchors.leftMargin: Math.round(200 * Style.scaleHint)
        }
        BransonPrimaryButton
        {
            id:cancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: "CANCEL"
            font.family: Style.regular.name
            buttonColor: "#E8E8E8"
            textColor: "#000000"
            onClicked:
            {
                controlLimitNumpad.visible = false
            }
        }
        BransonPrimaryButton
        {
            id:done
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: cancel.top
            anchors.left: cancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: "DONE"
            font.family: Style.regular.name
            onClicked:
            {
                controlLimitNumpad.visible = false
            }
        }

    }
}

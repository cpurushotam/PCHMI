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
TabButton {
    id: tabButton

    property alias tabbtnText: tabbtnText.text

    property string pressedColor: "#004B8D"
    property string unpressedColor: Style.backgroundColor
    property string tabTextColor: Style.blueFontColor
    property string tabTextBkColor: Style.blackFontColor
    property string backgroundColor: Style.backgroundColor
    contentItem: Text {
        id: tabbtnText
        font.bold: checked === true ? true : false
        font.family: Style.regular.name
        font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
        color: checked === true ? tabTextColor : tabTextBkColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    background: Rectangle{
        anchors.fill: parent
        color: backgroundColor
    }
    Rectangle {
        anchors.bottom: parent.bottom
        implicitHeight: Math.round(2 * Style.scaleHint)
        implicitWidth: parent.width
        color: checked === true ? pressedColor : unpressedColor
    }
}

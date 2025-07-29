/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Predfined component which can be used to display information on screen.

 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.SystemTypeDef 1.0


Item {

    id: bransonInfoElement

    width: Math.round(374 * Style.scaleHint)
    height: Math.round(35 * Style.scaleHint)

    property alias heightImg : backgroundImage.height
    property alias widthImg: backgroundImage.width

    property alias protyName:  elementName.text
    property alias protyValue: elementResult.text
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    Image{
        id: backgroundImage
        source: "qrc:/Images/InformationRectangle.svg"
        anchors.fill: parent
        height: parent.height
        width: parent.width
        Text{
            id: elementName
            anchors.left: parent.left
            anchors.leftMargin: Math.round(11 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
        Text{
            id: dwukropek
            anchors.left: elementName.left
            anchors.leftMargin: Math.round(186 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
            text: ": "
        }
        Text{
            id: elementResult
            anchors.left: dwukropek.right
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }
    }
}

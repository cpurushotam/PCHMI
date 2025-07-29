/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.SystemTypeDef 1.0

Item {
    property color activatedBigBackgroundColor: "#E1EAEA"
    property color activatedBigBackgroundBorderColor: Style.titleBackgroundColor
    property color activatedBackgroundColor: Style.buttonBackgroundColor
    property color activatedBackgroundBorderColor: Style.buttonBackgroundColor
    property color normalBigBackgroundColor: Style.recipeModeFrameColor
    property color normalBigBackgroundBorderColor: Style.recipeModeFrameColor
    property color normalBackgroundColor: Style.frameBorderColor
    property color normalBackgroundBorderColor: Style.frameBorderColor
    property bool checked: false

    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    Rectangle
    {
        id:root
        implicitWidth: parent.width
        implicitHeight: parent.height
        color: "transparent"

        DropShadow
        {
            anchors.fill: leftBorderRectAll
            horizontalOffset: 1
            verticalOffset: 1
            color: "#000000"
            opacity: 0.2
            source: leftBorderRectAll
        }

        Rectangle
        {
            /* The Largest rectangle */
            id: leftBorderRectAll
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: normalBigBackgroundColor
            border.color: (checked === true) ? activatedBigBackgroundBorderColor : normalBigBackgroundBorderColor
            border.width: 1

            Rectangle
            {
                /* The Border rectangle */
                id: leftBorderRectBorder
                width: Math.round(9 * Style.scaleHint)
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 0
                color: (checked === true) ? activatedBackgroundColor : normalBackgroundColor
                border.color: (checked === true) ? activatedBackgroundBorderColor : normalBackgroundBorderColor

                Rectangle
                {
                    id: paramRec
                    width: Math.round(7 * Style.scaleHint)
                    height: parent.height
                    color: (checked === true) ? activatedBackgroundColor : normalBackgroundColor
                    border.color: (checked === true) ? activatedBackgroundBorderColor : normalBackgroundBorderColor
                    anchors.left: leftBorderRectBorder.left
                    anchors.leftMargin: Math.round(3 * Style.scaleHint)
                }
            }
        }
    }
}

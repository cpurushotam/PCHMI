/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonDynamicStepButton.qml provides step interface used by
    BransonSteppingNumpad.qml
--------------------------- REVISION HISTORY ------------------------------
 rev1: 10/28/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.2
import Style 1.0
Rectangle
{
    id: rec
    property int stepIndex: 1
    property color textColor : BransonStyle.blackFontColor
    color: BransonStyle.activeFrameBorderColor
    border.width: (BransonStyle.scaleHint === 1.0) ? 1 : 2
    border.color: BransonStyle.frameBorderColor

    signal signalClickAction(int index, bool clickFlag)

    Text
    {
        id: txtStepIndex
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
        font.family: Style.regular.name
        color: textColor
        text: stepIndex
    }

    MouseArea
    {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onReleased:
        {
            signalClickAction(stepIndex, true)
        }
    }
}

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
//import QtQuick.Controls.Styles 1.4
import Qt5Compat.GraphicalEffects
import Style 1.0

Item
{
    signal checkStateChanged()
    property string qmltextCheckBox : "CheckBox"
    property bool qmltextCheckBoxNeeded: true
    property bool isChecked: false
    property int minWidth: Math.round(16 * Style.scaleHint)
    property int maxHeight: Math.round(16 * Style.scaleHint)
    property int fontSize: Math.round(Style.style2  * Style.scaleHint)
    property color backgroundcolor: "#E9ECEF"
    property color textcolor: "#272727"
    property color checkcolor: "#272727"
    property bool isBold: false
    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight: maxHeight
        color: "transparent"
        /*Text on the right side of the Checkbox*/
        Text
        {
            id: checkBoxText
            visible: qmltextCheckBoxNeeded
            anchors.left: checkBoxId.right
            anchors.leftMargin: Math.round(0 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: fontSize
            font.family: Style.regular.name
            text: qmltextCheckBox
            wrapMode: Text.Wrap
            color:textcolor
            font.bold: isBold
        }
        /*Check the box section*/
        CheckBox
        {
            id:checkBoxId
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            checked: isChecked
//            onCheckStateChanged:
//            {
//                checkStateChanged()
//            }
        }
    }
}

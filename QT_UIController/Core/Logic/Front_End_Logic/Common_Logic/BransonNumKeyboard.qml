/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import Style 1.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.1
Item {
    property int minWidthNumpad: Math.round(248 * Style.scaleHint)
    property int minHeightNumpad: Math.round(236 * Style.scaleHint)
    readonly property int minHeightTextField: Math.round(40 * Style.scaleHint)
    readonly property int fontsize: Math.round(Style.style6 * Style.scaleHint)
    readonly property string backgroundcolor: "#FFFFFF"
    property int buttonNumpadSize: Math.round(50 * Style.scaleHint)
    readonly property string qmltextDigit1:  "1"
    readonly property string qmltextDigit2:  "2"
    readonly property string qmltextDigit3:  "3"
    readonly property string qmltextDigit4:  "4"
    readonly property string qmltextDigit5:  "5"
    readonly property string qmltextDigit6:  "6"
    readonly property string qmltextDigit7:  "7"
    readonly property string qmltextDigit8:  "8"
    readonly property string qmltextDigit9:  "9"
    readonly property string qmltextDigit0:  "0"
    readonly property string qmltextNegative:"-"
    readonly property string qmltextDot:     "."
    readonly property string qmltextBackSpaceSymbol: "⌫"
    readonly property string qmltextClr:     "Clr"
    signal signalButtonNum(string num)
    signal signalButtonFunc(int funcBtn)
    Rectangle{
        id:numpadRec
        implicitWidth: minWidthNumpad
        implicitHeight: minWidthNumpad
        color: backgroundcolor
        anchors.top:parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter

        /*Number in keyboard*/
        Grid {
            id:numGrid
            columns: 3
            columnSpacing: Math.round(12 * Style.scaleHint)
            rowSpacing: Math.round(12 * Style.scaleHint)
            anchors.top: numpadRec.top
            anchors.topMargin: 0
            anchors.left:parent.left
            anchors.leftMargin: 0
            width: parent.width - buttonNumpadSize - Math.round(20 * Style.scaleHint)
            height: parent.height
            BransonDigitalKeyboard
            {
                id:text1
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit1
                onClicked: signalButtonNum("1")
            }

            BransonDigitalKeyboard
            {
                id:text2
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit2
                onClicked: signalButtonNum("2")
            }
            BransonDigitalKeyboard
            {
                id:text3
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit3
                onClicked: signalButtonNum("3")
            }
            BransonDigitalKeyboard
            {
                id:text4
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit4
                onClicked: signalButtonNum("4")
            }
            BransonDigitalKeyboard
            {
                id:text5
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit5
                onClicked: signalButtonNum("5")
            }
            BransonDigitalKeyboard
            {
                id:text6
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit6
                onClicked: signalButtonNum("6")
            }
            BransonDigitalKeyboard
            {
                id:text7
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit7
                onClicked: signalButtonNum("7")
            }
            BransonDigitalKeyboard
            {
                id:text8
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit8
                onClicked: signalButtonNum("8")
            }
            BransonDigitalKeyboard
            {
                id:text9
                implicitWidth: buttonNumpadSize
                implicitHeight: buttonNumpadSize
                fontSize: fontsize
                text: qmltextDigit9
                onClicked: signalButtonNum("9")
            }
        }
        /*Other on the keyboard*/
        BransonDigitalKeyboard
        {
            id: zeroButton
            anchors.left: parent.left
            anchors.top:textdot.top
            width: buttonNumpadSize
            implicitWidth: buttonNumpadSize
            implicitHeight: buttonNumpadSize
            fontSize: fontsize
            text: qmltextDigit0
            onClicked: signalButtonNum("0")
        }

        BransonDigitalKeyboard
        {
            id:negativeButton
            text: qmltextNegative
            anchors.left: zeroButton.right
            anchors.leftMargin: Math.round(12 * Style.scaleHint)
            anchors.top:textdot.top
            width: buttonNumpadSize
            implicitWidth: buttonNumpadSize
            implicitHeight: buttonNumpadSize
            fontSize: fontsize
            onClicked: signalButtonNum("-")
        }

        BransonFunctionKeyboard {
            id: deleteButton
            text: qmltextBackSpaceSymbol
            textColor: "#6699cc"
            anchors.left: numGrid.right
            anchors.top: numpadRec.top
            anchors.topMargin: 0
            implicitHeight: buttonNumpadSize
            width: customButton.width//42
            height: customButton.height*3 + Math.round(24 * Style.scaleHint)//141
            anchors.leftMargin: Math.round(12 * Style.scaleHint)
            fontSize: Math.round(Style.style7 * Style.scaleHint)
            onClicked:signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Delete)
        }
        BransonDigitalKeyboard {
            id: customButton
            text: qmltextClr
            anchors.leftMargin: Math.round(12 * Style.scaleHint)
            anchors.left: numGrid.right
            anchors.top:deleteButton.bottom
            anchors.topMargin: Math.round(12 * Style.scaleHint)
            visible: true
            implicitWidth: buttonNumpadSize
            implicitHeight: buttonNumpadSize
            fontSize: fontsize
            onClicked: signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Clear)
        }
        BransonDigitalKeyboard {
            id:textdot
            text: qmltextDot
            anchors.right: customButton.left
            anchors.rightMargin: Math.round(15 * Style.scaleHint)
            anchors.top:deleteButton.bottom
            anchors.topMargin: Math.round(12 * Style.scaleHint)
            implicitWidth: buttonNumpadSize
            implicitHeight: buttonNumpadSize
            fontSize: fontsize
            onClicked:signalButtonNum(".")
        }
    }
}

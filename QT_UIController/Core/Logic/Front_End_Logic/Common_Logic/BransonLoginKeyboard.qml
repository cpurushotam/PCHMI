/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Layouts 1.12
import Style 1.0
Item {
    property int minWidthNumpad: Math.round(50 * Style.scaleHint)
    property int minHeightNumpad: Math.round(290 * Style.scaleHint)
    property int gridRowColumnSpaceing: Math.round(12 * Style.scaleHint)
    property int loginColumnSpaceing: Math.round(22 * Style.scaleHint)
    readonly property string buttonLoginColor: "#6699CC"
    readonly property string buttonLoginTextColor: "#ffffff"
    property int buttonLoginSize: Math.round(50* Style.scaleHint)

    readonly property string buttonLogin:             "#000000"
    readonly property string buttonLoginTextNum1:     "1"
    readonly property string buttonLoginTextNum2:     "2"
    readonly property string buttonLoginTextNum3:     "3"
    readonly property string buttonLoginTextNum4:     "4"
    readonly property string buttonLoginTextNum5:     "5"
    readonly property string buttonLoginTextNum6:     "6"
    readonly property string buttonLoginTextNum7:     "7"
    readonly property string buttonLoginTextNum8:     "8"
    readonly property string buttonLoginTextNum9:     "9"
    readonly property string buttonLoginTextNum0:     "0"
    readonly property string buttonLoginDot:          "."
    readonly property string buttonLoginTextDel:      "⌫"
    readonly property string buttonLoginTextClr:      qsTr("Clr")
    property string buttonLoginTextLogin:             qsTr("Login")

    property int buttonLoginFontSize: Math.round(Style.style5  * Style.scaleHint)
    readonly property string buttonLoginFontFamily: Style.regular.name
    property int buttomLoginDeleteFontSize: Math.round(Style.style7  * Style.scaleHint)
    property alias numGrid: numGrid
    signal signalButtonNum(string num)
    signal signalButtonFunc(int funcBtn)
    Grid {
        id:numGrid
        rows: 3
        columns: 3
        columnSpacing: gridRowColumnSpaceing
        rowSpacing: gridRowColumnSpaceing
        BransonDigitalKeyboard
        {
            id:buttonLogNum1
            Layout.row: 1
            Layout.column: 1
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum1
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("1")
        }

        BransonDigitalKeyboard
        {
            id: buttonLogNum2
            Layout.row: 1
            Layout.column: 2
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum2
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("2")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum3
            Layout.row: 1
            Layout.column: 3
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum3
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("3")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum4
            Layout.row: 2
            Layout.column: 1
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum4
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("4")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum5
            Layout.row: 2
            Layout.column: 2
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum5
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("5")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum6
            Layout.row: 2
            Layout.column: 3
            implicitWidth:buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum6
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("6")
        }

        BransonDigitalKeyboard
        {
            id: buttonLogNum7
            Layout.row: 3
            Layout.column: 1
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum7
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("7")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum8
            Layout.row: 3
            Layout.column: 2
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum8
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("8")
        }

        BransonDigitalKeyboard
        {
            id:buttonLogNum9
            Layout.row: 3
            Layout.column: 3
            implicitWidth:buttonLoginSize
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum9
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("9")
        }
    }

    BransonDigitalKeyboard
    {
        id: buttonLogDel
        anchors.left: numGrid.right
        anchors.top: numGrid.top
        implicitWidth: buttonLoginSize
        implicitHeight: buttonLoginSize * 3 + gridRowColumnSpaceing * 2
        anchors.leftMargin: gridRowColumnSpaceing
        text: buttonLoginTextDel
        buttonColor: buttonLoginColor
        textColor: buttonLoginTextColor
        fontSize: buttomLoginDeleteFontSize
        font.family: buttonLoginFontFamily
        onClicked: signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Delete)
    }

    RowLayout{
        id: rowLayout
        spacing: buttonLoginSize + gridRowColumnSpaceing * 2
        anchors.top: numGrid.bottom
        anchors.left: numGrid.left
        anchors.topMargin: gridRowColumnSpaceing
        BransonDigitalKeyboard
        {
            id: buttonLogNum0
            implicitWidth: buttonLoginSize * 2 + gridRowColumnSpaceing
            implicitHeight: buttonLoginSize
            text: buttonLoginTextNum0
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked: signalButtonNum("0")
        }

        BransonDigitalKeyboard
        {

            id: buttonLoginClr
            text: buttonLoginTextClr
            implicitWidth: buttonLoginSize
            implicitHeight: buttonLoginSize
            buttonColor: buttonLoginColor
            textColor: buttonLoginTextColor
            fontSize: buttonLoginFontSize
            font.family: buttonLoginFontFamily
            onClicked:  signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Clear)
        }
    }

    BransonDigitalKeyboard
    {
        id: buttonLogin
        text: buttonLoginTextLogin
        textColor: buttonLoginTextColor
        anchors.left: rowLayout.left
        anchors.top: rowLayout.bottom
        anchors.topMargin: loginColumnSpaceing
        implicitWidth: buttonLoginSize * 4 + gridRowColumnSpaceing * 3
        implicitHeight: buttonLoginSize
        buttonColor: buttonLoginColor
        fontSize: buttonLoginFontSize
        font.family: buttonLoginFontFamily
        onClicked:  signalButtonFunc(BransonNumpadDefine.EnumKeyboard.Login)
    }
}



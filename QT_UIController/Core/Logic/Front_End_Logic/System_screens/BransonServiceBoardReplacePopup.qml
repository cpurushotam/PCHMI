/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

Branson Service - Board Replace Popup.

 **********************************************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
import "./../System_screens"

Rectangle
{
    id: popup
    z: 10
    property string qmltextLabel: "Board Replaced"
    property string qmltextSave: "Save"
    property string qmltextCancel: "Cancel"
    property string qmltextOldBoard:  "Old Board Revision "
    property string qmltextNewBoard:  "New Board Revision"
    property string qmltextBoardName:  "Board Name"

    property int rectleftMargin: parent.width * 0.43

    property var qmlTextArray: [qmltextLabel, qmltextSave, qmltextCancel, qmltextOldBoard ,qmltextNewBoard, qmltextBoardName]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.POPUP, qmlTextArray)
        qmltextLabel = qmlTextArray[textEnum.textWarningIdx]
        qmltextSave = qmlTextArray[textEnum.textOKIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextOldBoard = qmlTextArray[textEnum.textOldBoardIdx]
        qmltextNewBoard = qmlTextArray[textEnum.textNewBoardIdx]
        qmltextBoardName = qmlTextArray[textEnum.textBoardNameIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx: 0
        readonly property int textOKIdx: 1
        readonly property int textCancelIdx: 2
        readonly property int textOldBoardIdx: 3
        readonly property int textNewBoardIdx: 4
        readonly property int textBoardNameIdx: 5

    }

    signal oKButtonClicked()
    signal cancelButtonClicked()

    visible: false
    anchors.left: parent.left
    anchors.leftMargin: rectleftMargin
    x:mainWindow.showWidth*0.25
    y:mainWindow.showHeight*0.1
    width: mainWindow.showWidth * 0.35
    height: mainWindow.showHeight * 0.35
    focus: true

    Rectangle
    {
        id: popupBackground
        anchors.fill: parent
        implicitWidth: parent.width
        implicitHeight: parent.height
        opacity: 1
        color: "#ffffff"
        border.width: 0
        clip: true

        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: parent.height * 0.20
            color: Style.headerBackgroundColor
            Text
            {
                id: headername
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmltextLabel
                color: Style.whiteFontColor
                font
                {
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style1 * Style.scaleHint)
                }
            }
            Image
            {
                id: crossMark
                fillMode:Image.PreserveAspectFit;
                clip:true
                source: "qrc:/Images/crossMark.svg"
                anchors.right: parent.right
                anchors.top:          parent.top
                anchors.topMargin:    parent.height*0.15
                anchors.rightMargin:  parent.height/2
                sourceSize.width:  Math.round(Style.style4 * Style.scaleHint)
                sourceSize.height: Math.round(Style.style4 * Style.scaleHint)+5

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        oKButtonClicked()
                    }
                }
            }
        }

        Column
        {
            id: inputFieldsColumn
            anchors.top: numpadHeader.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(10 * Style.scaleHint)
            spacing: Math.round(10 * Style.scaleHint)

            TextField
            {
                id: boardName
                placeholderText: qmltextBoardName
                width: parent.width * 0.9
                font.pixelSize: Math.round(11 * Style.scaleHint)
                onTextChanged:
                {
                    if (boardName.text.length > 21) {
                        boardName.text = boardName.text.substring(0, 21)
                    }
                }

                onFocusChanged:
                {
                    if (focus)
                    {
                        Qt.inputMethod.show()
                    }
                }
            }

            TextField
            {
                id: oldBoardTextField
                placeholderText: qmltextOldBoard
                width: parent.width * 0.9
                font.pixelSize: Math.round(11 * Style.scaleHint)
                onTextChanged:
                {
                    if (oldBoardTextField.text.length > 21)
                    {
                        oldBoardTextField.text = oldBoardTextField.text.substring(0, 21)
                    }
                }

                onFocusChanged:
                {
                    if (focus)
                    {
                        Qt.inputMethod.show()
                    }
                }
            }

            TextField
            {
                id: newBoardTextField
                placeholderText: qmltextNewBoard
                width: parent.width * 0.9
                font.pixelSize: Math.round(11 * Style.scaleHint)
                onTextChanged:
                {
                    if (newBoardTextField.text.length > 21)
                    {
                        newBoardTextField.text = newBoardTextField.text.substring(0, 21)
                    }
                }

                onFocusChanged:
                {
                    if (focus)
                    {
                        Qt.inputMethod.show()
                    }
                }
            }
        }

        BransonPrimaryButton
        {
            id: ok
            implicitWidth: parent.width * 0.27
            implicitHeight: Math.round(22 * Style.scaleHint)
            fontSize: Math.round(11 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            text: qmltextSave
            font.family: Style.regular.name
            buttonColor: Style.blueFontColor
            textColor: "#FFFFFF"
            onClicked:
            {
                if(oldBoardTextField.text !== "" && newBoardTextField.text !== "")
                {
                    BransonServiceInterface.getOldBoardNewBoardName(oldBoardTextField.text,  newBoardTextField.text, boardName.text)
                }

                oKButtonClicked()
            }
        }
    }
}

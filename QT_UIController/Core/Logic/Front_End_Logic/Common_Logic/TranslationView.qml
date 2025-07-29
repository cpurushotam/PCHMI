/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.12
import Style 1.0
import Com.Branson.LanguageEnum 1.0
import Com.Branson.UIScreenEnum 1.0

Item {
    id: translationView
    readonly property int imageSize: Math.round(24 * Style.scaleHint)
    property int nCurrentLanguageIndex: 0

    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    property string qmltextSelectLanguage: qsTr("Select Language")
    property string qmltextCancel: qsTr("CANCEL")
    property string qmltextSave: qsTr("SAVE")
    property var qmlTextArray: [qmltextSelectLanguage, qmltextCancel, qmltextSave]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SELECTLANGUAGE, qmlTextArray)
        qmltextSelectLanguage = qmlTextArray[textEnum.selectLanguageIdx]
        qmltextCancel = qmlTextArray[textEnum.cancelIdx]
        qmltextSave = qmlTextArray[textEnum.saveIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int selectLanguageIdx:    0
        readonly property int cancelIdx:            1
        readonly property int saveIdx:              2
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle {
        id: languageView
        width: Math.round(520 * Style.scaleHint)
        height: Math.round(310 * Style.scaleHint)
        anchors.centerIn: parent
        Rectangle {
            id: languageHeader
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            color: Style.headerBackgroundColor
            Text {
                id: headerTitle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Math.round(14 * Style.scaleHint)
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.whiteFontColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: qmltextSelectLanguage
            }
            Image {
                id: closeMark
                width: imageSize
                height: imageSize
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                source: "qrc:/Images/crossMark.svg"
                fillMode: Image.PreserveAspectFit
                sourceSize.width: closeMark.width
                sourceSize.height: closeMark.height
                smooth: true
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        translationView.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: languageLayout
            anchors.top: languageHeader.bottom
            anchors.topMargin: 33
            anchors.bottom: saveButton.top
            anchors.bottomMargin:  33
            anchors.left: languageHeader.left
            anchors.leftMargin: 24
            anchors.right: languageHeader.right
            anchors.rightMargin: 24
            border.color: "transparent"
            Grid {
                anchors.fill: parent
                rowSpacing: Math.round(36 * Style.scaleHint)
                columns: 3
                Repeater {
                    model: LanguageModel
                    delegate: BransonRadioButton
                    {
                        id: customerRadioButtionDelegate
                        height: Math.round(20 * Style.scaleHint)
                        width: parent.width/3
                        labelText:  model.itemName
                        checked: (index == LanguageConfig.CurrentLanguage) ? true : false
                        onClicked:
                        {
                            nCurrentLanguageIndex = model.itemIndex
                        }
                    }
                }
            }
        }

        BransonPrimaryButton{
            id: saveButton
            anchors.right: parent.right
            anchors.rightMargin: Math.round(13 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(8 * Style.scaleHint)
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qmltextSave
            fontSize: Math.round(Style.style0 * Style.scaleHint)
            onClicked: {
                translationView.visible = false
                LanguageConfig.CurrentLanguage = nCurrentLanguageIndex
            }
        }

        BransonPrimaryButton{
            id: cancelButton
            anchors.right: saveButton.left
            anchors.rightMargin: Math.round(10 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(8 * Style.scaleHint)
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qmltextCancel
            fontSize: Math.round(Style.style0 * Style.scaleHint)
            onClicked: {
                translationView.visible = false
            }
        }
    }

}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 MessagePopup - This is a read-only screen where it displays warning when user enters the value below or above the limits setted.

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Window
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick 2.0
import QtQuick 2.11
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"

Popup {

    id: popup
    readonly property int qmlscreenIndicator:  UIScreenEnum.MESSAGEPOPUP

    property string qmltextWarning:        qsTr("Warning !")

    property string qmltextInvalidValueMsg : qsTr("Invalid value is entered, Reverted to old value")

    property var qmlTextArray: [qmltextWarning, qmltextInvalidValueMsg]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.MESSAGEPOPUP, qmlTextArray)
        qmltextWarning = qmlTextArray[textEnum.textWarningIdx]
        qmltextInvalidValueMsg = qmlTextArray[textEnum.textInvalidValueMsgIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx:            0
        readonly property int textInvalidValueMsgIdx:    1
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

    background: Rectangle {
        id:rectMain
        color:"transparent"
    }
    Rectangle{
        anchors.fill: parent
        id:root
        radius:15
        color:"white"
        clip:true

        Rectangle {
            id: clipper
            width: parent.width
            height: parent.height*0.30
            color: 'transparent'
            clip: true
            Rectangle {
                id: clipped
                anchors.left: parent.left
                anchors.right: parent.right
                width: parent.width+root.radius
                height: parent.height+root.radius
                radius: root.radius
                color: '#1261a6'
                Text {
                    id: mangeTextHeader
                    text:qmltextWarning
                    font.pixelSize:parent.height * 0.50
                    font.family: Style.regular.name
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.02
                    anchors.top: parent.top
                }
            }
        }

        Text{
            anchors.centerIn: parent
            font.pixelSize:parent.height * 0.20
            font.family: Style.regular.name
            text:qmltextInvalidValueMsg
        }
    }
}

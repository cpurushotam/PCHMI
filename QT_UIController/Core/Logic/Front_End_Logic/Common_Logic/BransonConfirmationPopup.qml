/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file displays the Branson Confirmation Popup Screen.

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
    signal okButtonClicked()
    signal cancelButtonClicked()

    readonly property int qmlscreenIndicator:  UIScreenEnum.CONFIRMATION_POPUP
    property string qmltextConfirmation     : "CONFIRMATION"
    property string qmltextWarningMessage   : "Warning Message"
    property string qmltextOk               : "OK"
    property string qmltextCancel           : "CANCEL"

    property var qmlTextArray: [qmltextConfirmation, qmltextWarningMessage, qmltextOk, qmltextCancel]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.CONFIRMATION_POPUP, qmlTextArray)
        qmltextConfirmation = qmlTextArray[textEnum.textConfirmationIdx]
        qmltextWarningMessage = qmlTextArray[textEnum.textWarningMessageIdx]
        qmltextOk = qmlTextArray[textEnum.textOkIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textConfirmationIdx:            0
        readonly property int textWarningMessageIdx:          1
        readonly property int textOkIdx:                      2
        readonly property int textCancelIdx:                  3
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

    background: Rectangle
    {
        id:rectMain
        color:"transparent"
    }

        Rectangle
        {
            id: clipper
            anchors.fill: parent
            color:"white"
            clip:true

            Rectangle
            {
                id: clipped
                anchors.left: parent.left
                anchors.right: parent.right
                width: parent.width
                height: parent.height*0.20
                color: Style.headerBackgroundColor
                Text
                {
                    id: mangeTextHeader
                    text:qmltextConfirmation
                    font.pixelSize:parent.height * 0.35
                    font.family: Style.regular.name
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.02
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Text
            {
                anchors.centerIn: parent
                font.pixelSize:parent.height * 0.1
                font.family: Style.regular.name
                text:qmltextWarningMessage
            }

            BransonPrimaryButton
            {
                id: btnCancel
                implicitWidth: Math.round(100 * Style.scaleHint)
                implicitHeight: Math.round(25 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin:  parent.width*0.75 - (implicitWidth/2)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(15 * Style.scaleHint)
                text: qmltextCancel
                buttonColor: Style.cancelButtonTextColor
                font.family: Style.regular.name
                onClicked:
                {
                    cancelButtonClicked()
                }
            }

            BransonPrimaryButton
            {
                id: btnOk
                implicitWidth: Math.round(100 * Style.scaleHint)
                implicitHeight: Math.round(25 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.25 - (implicitWidth/2)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(15 * Style.scaleHint)
                text: qmltextOk
                buttonColor: Style.buttonColor
                font.family: Style.regular.name
                onClicked:
                {
                    okButtonClicked()
                }
            }
        }
}

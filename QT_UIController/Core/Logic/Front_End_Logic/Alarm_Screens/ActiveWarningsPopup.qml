/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the alarm events log table .

--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/06/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import AxisDefine 1.0
import QtQuick.Layouts 1.15
import Com.Branson.GraphAxisEnum 1.0
import "./../Diagnostics_Screens"
import "./../Common_Logic"

Popup
{
    id: warningsPopup
    property string qmlTextMenuName          : "Warnings"
    property string qmlTextWarning           : "Warning"
    property string qmlTextWarningString     : "New Warning Found"
    property string qmlTextViewDetails       : "View Details"

    property var qmlTextArray: [qmlTextWarning, qmlTextWarningString, qmlTextViewDetails]
    signal closeButtonClicked()
    signal activeAlarmDetailsListEmpty()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ALARMEVENTSLOG , qmlTextArray)
        qmlTextWarning    = qmlTextArray[textEnum.textWarningIdx]
        qmlTextWarningString = qmlTextArray[textEnum.textWarningStringIdx]
        qmlTextViewDetails      = qmlTextArray[textEnum.textViewDetailsIdx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ALARMEVENTSLOG, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx           : 0
        readonly property int textWarningStringIdx     : 1
        readonly property int textViewDetailsIdx       : 2
    }

    Component.onCompleted:
    {
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        target: ActiveAlarmDetailsListModel
        function onActiveAlarmDetailsListEmpty()
        {
            closeButtonClicked()
        }
    }

    dim: true
    modal: true
    focus: true

    background: Rectangle
    {
        id:rectMain
        color:"transparent"
    }

    Overlay.modal: Rectangle
    {
        color: "#AACFDBE7"
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
    }

    Rectangle
    {
        id: popupHeader
        width: parent.width
        implicitHeight: Math.round(50 * Style.scaleHint)
        color: "#FFD022"

        Image
        {
            id: bellSymbol
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(30 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            sourceSize.width: Math.round(30 * Style.scaleHint)
            sourceSize.height: Math.round(30 * Style.scaleHint)
            source: "qrc:/Images/Alarm.png"
            fillMode: Image.PreserveAspectFit
            ColorOverlay
            {
                anchors.fill: bellSymbol
                source: bellSymbol
                color: "#FFFFFF"
            }
        }

        Text
        {
            id: headername
            anchors.left: parent.left
            anchors.leftMargin: Math.round(45 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmlTextWarning
            color: Style.whiteFontColor
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style4 * Style.scaleHint)
                bold : true
            }
        }

        Image
        {
            id: imageCross
            anchors.right: parent.right
            anchors.rightMargin: Math.round(5 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(30 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            sourceSize.width: Math.round(30 * Style.scaleHint)
            sourceSize.height: Math.round(30 * Style.scaleHint)
            source: "qrc:/Images/crossMark.svg"
            fillMode: Image.PreserveAspectFit
            ColorOverlay
            {
                anchors.fill: imageCross
                source: imageCross
                color: "#FFFFFF"
            }

            MouseArea
            {
                id: imageCrossMA
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    closeButtonClicked()
                }
            }
        }
    }

    Text
    {
        id: newAlarmFoundText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.top: popupHeader.bottom
        anchors.topMargin: Math.round(50 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextWarningString
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint) * 0.90
    }


    BransonPrimaryButton
    {
        id: viewDetailsBtn
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(20 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        text: qmlTextViewDetails
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            if(ActiveScreen.CurrentActiveScreen !== UIScreenEnum.DIAGNOSTICS_ALARM)
            {
                /*To understand that screen is navigated from active warnings popup*/
                AlarmDetailsListModel.IsScreenNavigatedFromWarningsPopup = true
                mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_ALARM)
            }

            else
            {
                /*To understand that screen is navigated from active warnings popup*/
                AlarmDetailsListModel.isScreenNavigatedWhenAlarmLogIsVisibleFromWarningsPopup(true)
            }

            closeButtonClicked()
        }
    }
}

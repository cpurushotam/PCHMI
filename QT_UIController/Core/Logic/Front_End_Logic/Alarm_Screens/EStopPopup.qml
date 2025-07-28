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
    id: eStopPopup
    property string qmlTextMenuName  : "Emergency Stop"
    property string qmlTextEStop     : "Emergency Stop"
    property string qmlTextReset     : "RESET"


    property var qmlTextArray: [qmlTextMenuName, qmlTextEStop, qmlTextReset]

    signal eStopEventOccurred()

    function updateLanguage()
    {
        qmlTextArray    = LanguageConfig.getLanguageStringList(UIScreenEnum.ESTOP_POPUP, qmlTextArray)
        qmlTextEStop    = qmlTextArray[textEnum.textEStopIdx]
        qmlTextReset    = qmlTextArray[textEnum.textResetIdx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ESTOP_POPUP, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textEStopIdx     : 0
        readonly property int textResetIdx     : 1
    }

    QtObject
    {
        id: eStopEventsEnum
        readonly property int eStopPressedEventOccurred    : 0
        readonly property int eStopReleasedEventOccurred   : 1
        readonly property int eStopResetSuccess            : 2
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
        function onEStopEventOccurred(eventType)
        {
            if(eventType === eStopEventsEnum.eStopReleasedEventOccurred)
            {
                resetBtn.visible = true
            }

            else
            {
                resetBtn.visible = false
            }
        }
    }

    dim: true
    modal: true
    focus: true

    background: Rectangle
    {
        id: rectMain
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

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        visible: true
        anchors.left: parent.Left
        anchors.top: parent.Top
        height: parent.height
        width: parent.width
        color: Style.headerBackgroundColor
        opacity: 0.25

        MouseArea
        {
            id: opacityEffectRectMa
            anchors.fill: parent
            onClicked:
            {
                /*Avoid false click*/
            }
        }
    }

    Rectangle
    {
        id: roundBG
        width: Math.round(250 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: Style.headerBackgroundColor
        radius: roundBG.width/2

        Text
        {
            id: eStopText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qmlTextEStop
            color: Style.whiteFontColor
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style5 * Style.scaleHint)
                bold : true
            }
        }

        BransonPrimaryButton
        {
            id: resetBtn
            visible: false
            implicitWidth: Math.round(100 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: eStopText.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            text: qmlTextReset
            buttonColor: "#9B9E9C"
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style3 * Style.scaleHint)
                bold : true
            }

            onClicked:
            {
                ActiveAlarmDetailsListModel.setEstopResetRequest()
            }
        }
    }
}

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
    id: notificationsPopup
    property string qmlTextMenuName       : "Service Count"
    property string qmlTextServiceCount   : "Service Count"
    property string qmlTextSnoozeReminder : "Snooze Reminder"
    property string qmlTextSet            : "SET"
    property string qmlTextNone           : "None"
    property string qmlTextAfter12Hours   : "After 12 Hours"
    property string qmlTextAfter24Hours   : "After 24 Hours"
    property string qmlTextAfter3Days     : "After  3 Days"
    property string qmlTextAfter6Days     : "After  6 Days"

    property string qmlTextServiceReminderName  : "Name"
    property string qmlTextServiceReminderID    : "Reminder ID"
    property string qmlTextAction               : "Action"
    property string qmlTextServiceReminder      : "ServiceReminder"
    property string qmlTextReset                : "Reset"
    property string qmlTextResetAll             : "Reset All"
    property string qmlTextViewDetails          : "View Details"
    property string qmlTextAlert                : "ALERT !"
    property string qmlTextInfo                 : "No Details Are Available!"
    property string qmlTextOK                   : "OK"
    property string qmlTextEmpty                : "No Details To Show !"

    property var qmlTextArray: [qmlTextServiceCount, qmlTextSnoozeReminder, qmlTextSet, qmlTextNone, qmlTextAfter12Hours, qmlTextAfter24Hours,
                                qmlTextAfter3Days, qmlTextAfter6Days]
    property var qmlServiceReminderSnoozeOptions: [qmlTextNone, qmlTextAfter12Hours, qmlTextAfter24Hours, qmlTextAfter3Days, qmlTextAfter6Days]

    signal closeButtonClicked()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ALARMEVENTSLOG , qmlTextArray)
        qmlTextServiceCount    = qmlTextArray[textEnum.textServiceCountIdx]
        qmlTextSnoozeReminder = qmlTextArray[textEnum.textSnoozeReminderIdx]
        qmlTextSet          = qmlTextArray[textEnum.textSetIdx]
        qmlTextNone         = qmlTextArray[textEnum.textNoneIdx]
        qmlTextAfter12Hours  = qmlTextArray[textEnum.textAfter12HoursIdx]
        qmlTextAfter24Hours  = qmlTextArray[textEnum.textAfter24HoursIdx]
        qmlTextAfter3Days = qmlTextArray[textEnum.textAfter3DaysIdx]
        qmlTextAfter6Days = qmlTextArray[textEnum.textAfter6DaysIdx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ALARMEVENTSLOG, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textServiceCountIdx   : 0
        readonly property int textSnoozeReminderIdx : 1
        readonly property int textSetIdx            : 2
        readonly property int textNoneIdx           : 3
        readonly property int textAfter12HoursIdx    : 4
        readonly property int textAfter3DaysIdx   : 5
        readonly property int textAfter6DaysIdx   : 6
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
        color: "#00FF00"

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
            text: qmlTextServiceCount
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

    Rectangle
    {
        id: columnRect
        width: parent.width - Math.round(40 * Style.scaleHint)
        height: Math.round(50 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: popupHeader.bottom
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        border.color:"#0F0F0F"
        clip: true

            Text
            {
                id: serviceReminderNameText
                anchors.left: parent.left
                anchors.leftMargin: Math.round(50 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: qmlTextServiceReminderName
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                font.bold: true
            }

            Text
            {
                id: serviceReminderIDText
                anchors.left: parent.left
                anchors.leftMargin: Math.round(200 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: qmlTextServiceReminderID
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                font.bold: true
            }

            Text
            {
                id: actionText
                anchors.left: parent.left
                anchors.leftMargin: Math.round(425 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: qmlTextAction
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                font.bold: true
            }
    }

    ListView
    {
        id: eventLogDetailsListView
        width: columnRect.width
        height: Math.round(225 * Style.scaleHint)
        anchors.top: columnRect.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: columnRect.left
        spacing: Math.round(0 * Style.scaleHint)
        model: ActiveServiceReminderDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCountChanged:
        {
            /*To avoid blank screen when service reminders are reset at backend*/
            if(! eventLogDetailsListView.count)
            {
                closeButtonClicked()
            }
        }

        delegate: Rectangle
        {
            id: cycleDetailsInfo
            width: eventLogDetailsListView.width
            height: Math.round(55 * Style.scaleHint)
            color: "transparent"
            Rectangle
            {
                id: delegateColorIndicatorRect
                z: 1
                anchors.left: parent.left
                width: Math.round(10 * Style.scaleHint)
                height: Math.round(50 * Style.scaleHint)
                color:"#00FF00"
                border.color:"#707070"
            }

            Rectangle
            {
                id: delegateRect
                anchors.left: delegateColorIndicatorRect.right
                anchors.leftMargin: Math.round(-1 * Style.scaleHint)
                width: parent.width - delegateColorIndicatorRect.width
                height: Math.round(50 * Style.scaleHint)
                border.color:"#707070"
                clip:true

                Text
                {
                    id: serviceReminderNameTextDelegate
                    width: Math.round(150 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    text: model.ServiceReminderServiceName
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: serviceReminderIDTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(185 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.ServiceReminderID.toString(16).toUpperCase()
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                BransonComboBox
                {
                    id: snoozeComboBox
                    currentIndex: model.ServiceReminderSnoozeDuration
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(350 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    minWidth: Math.round(110 * Style.scaleHint)
                    minHeight: Math.round(25 * Style.scaleHint)
                    model: qmlServiceReminderSnoozeOptions
                }

                BransonPrimaryButton
                {
                    id: setBtn
                    implicitWidth: Math.round(50 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    anchors.left: snoozeComboBox.right
                    anchors.leftMargin: Math.round(15 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    fontSize: Math.round(Style.style2  * Style.scaleHint)
                    text: qmlTextSet
                    buttonColor: Style.buttonBackgroundColor
                    font.family: Style.regular.name

                    onClicked:
                    {
                        ActiveServiceReminderDetailsListModel.onSetSnoozePressed(model.ServiceReminderServiceName, snoozeComboBox.currentIndex)
                    }
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: okBtn
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmlTextOK
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            closeButtonClicked()
        }
    }
}

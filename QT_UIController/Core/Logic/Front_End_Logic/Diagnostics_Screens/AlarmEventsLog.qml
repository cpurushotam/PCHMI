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
import "./../Analytics_Screens"

Item
{
    id:eventlog
    property string qmlTextMenuName          : "Alarm Log"
    property string qmlTextErrorType         : "Error Type"
    property string qmlTextAlarmID           : "Alarm ID"
    property string qmlTextRecipe            : "Recipe"
    property string qmlTextRecipeVer         : "Recipe Ver"
    property string qmlTextCycle             : "Cycle"
    property string qmlTextDateAndTime       : "Date & Time"
    property string qmlTextAlarms            : "Alarms"
    property string qmlTextWarnings          : "Warnings"
    property string qmlTextNotifications     : "Notifications"
    property string qmlTextGenerateReport    : "Generate Report"
    property string qmlTextDescription       : "Description"
    property string qmlTextUserName          : "User Name"
    property string qmlTextAlarmType         : "Alarm Type"
    property string qmlTextResults           : "Results"
    property string qmlTextAddNotes          : "Add Notes"
    property string qmlTextEditNotes         : "Edit Notes"
    property string qmlTextAddedNotes        : "Added Notes"
    property string qmlTextServiceReminder   : "Service Count"

    property string qmlTextReset             : "Reset"
    property string qmlTextResetAll          : "Reset All"
    property string qmlTextProbableReason    : "Probable Reason"
    property string qmlTextHMISerial         : "HMI Serial #"
    property string qmlTextComments          : "Comments"
    property string qmlTextSourceEvent       : "Source"
    property string qmlTextUser              : "User"
    property string qmlTextAlert             : "Alert !"
    property string qmlTextAlertMessage      : "Horn is clamped, 'Reset All' alarms action will retract the horn. Do you want to continue?"

    property int    selectedIndex
    property string qmltextdateTime          : ""
    property bool   isAlarmActive            : false

    signal alarmDetailsPressed()
    signal warningDetailsPressed()
    signal notificationDetailsPressed()
    signal serviceReminderDetailsPressed()

    property var qmlTextArray: [qmlTextErrorType, qmlTextAlarmID, qmlTextRecipe, qmlTextRecipeVer,
                                qmlTextCycle, qmlTextDateAndTime, qmlTextAlarms, qmlTextWarnings, qmlTextNotifications,
                                qmlTextGenerateReport, qmlTextDescription, qmlTextUserName, qmlTextAlarmType, qmlTextResults,
                                qmlTextAddNotes, qmlTextEditNotes, qmlTextReset, qmlTextResetAll, qmlTextProbableReason,qmlTextAddedNotes,
                                qmlTextServiceReminder, qmlTextAlert, qmlTextAlertMessage]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_ALARM , qmlTextArray)
        qmlTextErrorType        = qmlTextArray[textEnum.textErrorTypeIdx]
        qmlTextAlarmID          = qmlTextArray[textEnum.textAlarmIDIdx]
        qmlTextRecipe           = qmlTextArray[textEnum.textRecipeIdx]
        qmlTextRecipeVer        = qmlTextArray[textEnum.textRecipeVerIdx]
        qmlTextCycle            = qmlTextArray[textEnum.textCycleIdx]
        qmlTextDateAndTime      = qmlTextArray[textEnum.textDateTimeIdx]
        qmlTextAlarms           = qmlTextArray[textEnum.textAlarmsIdx]
        qmlTextWarnings         = qmlTextArray[textEnum.textWarningsIdx]
        qmlTextNotifications = qmlTextArray[textEnum.textNotificationsIdx]
        qmlTextGenerateReport   = qmlTextArray[textEnum.textGenerateReportIdx]
        qmlTextDescription      = qmlTextArray[textEnum.textDescriptionIdx]
        qmlTextUserName         = qmlTextArray[textEnum.textUserNameIdx]
        qmlTextAlarmType        = qmlTextArray[textEnum.textAlarmTypeIdx]
        qmlTextResults          = qmlTextArray[textEnum.textResultsIdx]
        qmlTextAddNotes         = qmlTextArray[textEnum.textAddNotesIdx]
        qmlTextEditNotes        = qmlTextArray[textEnum.textEditNotesIdx]
        qmlTextAddedNotes       = qmlTextArray[textEnum.textAddedNotesIdx]
        qmlTextServiceReminder     = qmlTextArray[textEnum.textServiceReminderIdx]

        qmlTextReset            = qmlTextArray[textEnum.textResetIdx]
        qmlTextResetAll         = qmlTextArray[textEnum.textResetAllIdx]
        qmlTextProbableReason   = qmlTextArray[textEnum.textProbableReasonIdx]
        qmlTextAlert            = qmlTextArray[textEnum.textAlertIdx]
        qmlTextAlertMessage     = qmlTextArray[textEnum.textAlertMessageIdx]

        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS_ALARM, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textErrorTypeIdx         : 0
        readonly property int textAlarmIDIdx           : 1
        readonly property int textRecipeIdx            : 2
        readonly property int textRecipeVerIdx         : 3
        readonly property int textCycleIdx             : 4
        readonly property int textDateTimeIdx          : 5
        readonly property int textAlarmsIdx            : 6
        readonly property int textWarningsIdx          : 7
        readonly property int textNotificationsIdx     : 8
        readonly property int textGenerateReportIdx    : 9
        readonly property int textDescriptionIdx       : 10
        readonly property int textUserNameIdx          : 11
        readonly property int textAlarmTypeIdx         : 12
        readonly property int textResultsIdx           : 13
        readonly property int textResetAllIdx          : 14
        readonly property int textAddNotesIdx          : 15
        readonly property int textEditNotesIdx         : 16
        readonly property int textResetIdx             : 17
        readonly property int textProbableReasonIdx    : 18
        readonly property int textAddedNotesIdx        : 19
        readonly property int textServiceReminderIdx   : 20
        readonly property int textAlertIdx             : 21
        readonly property int textAlertMessageIdx      : 22

    }

    QtObject
    {
        id: alarmTypeEnum
        readonly property int alarmTypeNoneIdx         : 0
        readonly property int alarmTypeAlarmIdx        : 1
        readonly property int alarmTypeWarningIdx      : 2
        readonly property int alarmTypeNotificationIdx : 3
        readonly property int alarmTypeServiceReminderIdx : 4
    }

    BransonPopup
    {
        id: clamponAlertPopup
        qmltextLabel: qmlTextAlert
        qmltextWarningDialog : qmlTextAlertMessage
        isMultiButtonPopup : true
        anchors.centerIn: parent
        onOKButtonClicked:
        {
            AlarmDetailsListModel.reset()

            clamponAlertPopup.visible = false
        }
        onCancelButtonClicked:
        {
            clamponAlertPopup.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }
    }
    Component.onCompleted:
    {
        updateLanguage();
        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.DIAGNOSTICS_ALARM)
            /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS_ALARM
        AlarmDetailsListModel.isScreenReNavigated(true)
        selectedIndex = 0

        /*To understand that screen is navigated from active alarms popup so show only alarms*/
        if(AlarmDetailsListModel.IsScreenNavigatedFromAlarmsPopup)
        {
            alarmCB.checked = true
            warningCB.checked = false
            notificationCB.checked = false
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromAlarmsPopup = false
        }

        /*To understand that screen is navigated from active warnings popup so show only warnings*/
        else if(AlarmDetailsListModel.IsScreenNavigatedFromWarningsPopup)
        {
            alarmCB.checked = false
            warningCB.checked = true
            notificationCB.checked = false
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromWarningsPopup = false
        }

        /*To understand that screen is navigated from active notifications popup so show only notifications*/
        else if(AlarmDetailsListModel.IsScreenNavigatedFromNotificationsPopup)
        {
            alarmCB.checked = false
            warningCB.checked = false
            notificationCB.checked = true
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromNotificationsPopup = false
        }

        /*To understand that screen is navigated from active service count popup so show only notifications*/
        else if(AlarmDetailsListModel.IsScreenNavigatedFromServiceReminderPopup)
        {
            alarmCB.checked = false
            warningCB.checked = false
            notificationCB.checked = false
            serviceReminderCB.checked = true
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromServiceReminderPopup = false
        }

        AlarmDetailsListModel.loadAlarmDetailsList()
    }

    Connections
    {
        target: AlarmDetailsListModel

        function onAlarmDetailsPressed()
        {
            /*To understand that screen is navigated from active alarms popup so show only alarms*/

            alarmCB.checked = true
            warningCB.checked = false
            notificationCB.checked = false
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromAlarmsPopup = false

            AlarmDetailsListModel.loadAlarmDetailsList()
        }

        function onWarningDetailsPressed()
        {
            /*To understand that screen is navigated from active warnings popup so show only warnings*/

            alarmCB.checked = false
            warningCB.checked = true
            notificationCB.checked = false
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromWarningsPopup = false

            AlarmDetailsListModel.loadAlarmDetailsList()
        }

        function onNotificationDetailsPressed()
        {
            /*To understand that screen is navigated from active notifications popup so show only notifications*/

            alarmCB.checked = false
            warningCB.checked = false
            notificationCB.checked = true
            serviceReminderCB.checked = false
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromNotificationsPopup = false

            AlarmDetailsListModel.loadAlarmDetailsList()
        }

        function onServiceReminderDetailsPressed()
        {
            /*To understand that screen is navigated from active service count popup so show only notifications*/

            alarmCB.checked = false
            warningCB.checked = false
            notificationCB.checked = false
            serviceReminderCB.checked = true
            /*Make flag off for next navigation indication*/
            AlarmDetailsListModel.IsScreenNavigatedFromServiceReminderPopup = false

            AlarmDetailsListModel.loadAlarmDetailsList()
        }
    }


    function isNotesEmpty( notes)
    {
        if(notes === "")
        {
            return false
        }
        else
        {
            return true
        }
    }
    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Rectangle
    {
        id: alarmRect
        anchors.left: parent.left
        anchors.leftMargin:  Math.round(25 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(11 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        color: "#D31346"
    }

    CheckBox
    {
        id: alarmCB
        anchors.left: alarmRect.right
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(16 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        checked: true

        Text
        {
            id: alarmName
            anchors.left: alarmCB.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(-1 * Style.scaleHint)
            text: qmlTextAlarms
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.bold: true
        }

        onCheckedChanged:
        {
            AlarmDetailsListModel.loadAlarmDetailsList()
        }
    }

    Text
    {
        id: alarmCountText
        text: "(" + AlarmDetailsListModel.AlarmCount + ")"
        anchors.left: alarmCB.right
        anchors.leftMargin: Math.round(60 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(14 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
        font.family: Style.regular.name
        color: Style.blackFontColor
        font.bold: true
    }

    Rectangle
    {
        id: alarmSelectRect
        visible: alarmCB.checked
        anchors.left: alarmRect.left
        anchors.top: alarmRect.bottom
        anchors.topMargin: Math.round(2 * Style.scaleHint)
        width: Math.round(115 * Style.scaleHint)
        height: Math.round(2 * Style.scaleHint)
        color: Style.buttonBackgroundColor
    }

    Rectangle
    {
        id: warningRect
        anchors.left: alarmCountText.right
        anchors.leftMargin:  Math.round(25 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(11 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        color: "#FFD022"
    }

    CheckBox
    {
        id: warningCB
        anchors.left: warningRect.right
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(16 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        checked: true

        Text
        {
            id: warningName
            anchors.left: warningCB.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(-1 * Style.scaleHint)
            text: qmlTextWarnings
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.bold: true
        }

        onCheckedChanged:
        {
            AlarmDetailsListModel.loadAlarmDetailsList()
        }
    }

    Text
    {
        id: warningCountText
        text: "(" + AlarmDetailsListModel.WarningCount + ")"
        anchors.left: warningCB.right
        anchors.leftMargin: Math.round(80 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(14 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
        font.family: Style.regular.name
        color: Style.blackFontColor
        font.bold: true
    }

    Rectangle
    {
        id: warningSelectRect
        visible: warningCB.checked
        anchors.left: warningRect.left
        anchors.top: warningRect.bottom
        anchors.topMargin: Math.round(2 * Style.scaleHint)
        width: Math.round(135 * Style.scaleHint)
        height: Math.round(2 * Style.scaleHint)
        color: Style.buttonBackgroundColor
    }


    Rectangle
    {
        id: notificationRect
        anchors.left: warningCountText.right
        anchors.leftMargin:  Math.round(25 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(11 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        color: "#00A4D2"
    }

    CheckBox
    {
        id: notificationCB
        anchors.left: notificationRect.right
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(16 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        checked: true

        Text
        {
            id: notificationName
            anchors.left: notificationCB.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(-1 * Style.scaleHint)
            text: qmlTextNotifications
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.bold: true
        }

        onCheckedChanged:
        {
            AlarmDetailsListModel.loadAlarmDetailsList()
        }
    }

    Text
    {
        id: notificationCountText
        text: "(" + AlarmDetailsListModel.NotificationsCount + ")"
        anchors.left: notificationCB.right
        anchors.leftMargin: Math.round(100 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(14 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
        font.family: Style.regular.name
        color: Style.blackFontColor
        font.bold: true
    }

    Rectangle
    {
        id: notificationSelectRect
        visible: notificationCB.checked
        anchors.left: notificationRect.left
        anchors.top: notificationRect.bottom
        anchors.topMargin: Math.round(2 * Style.scaleHint)
        width: Math.round(155 * Style.scaleHint)
        height: Math.round(2 * Style.scaleHint)
        color: Style.buttonBackgroundColor
    }

    Rectangle
    {
        id: serviceReminderRect
        anchors.left: notificationCountText.right
        anchors.leftMargin:  Math.round(25 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(11 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        color: "#00FF00"
    }

    CheckBox
    {
        id: serviceReminderCB
        anchors.left: serviceReminderRect.right
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(16 * Style.scaleHint)
        height: Math.round(16 * Style.scaleHint)
        checked: true

        Text
        {
            id: serviceReminderName
            anchors.left: serviceReminderCB.right
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(-1 * Style.scaleHint)
            text: qmlTextServiceReminder
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.bold: true
        }

        onCheckedChanged:
        {
            AlarmDetailsListModel.loadAlarmDetailsList()
        }
    }

    Text
    {
        id: serviceReminderCountText
        text: "(" + AlarmDetailsListModel.ServiceReminderCount + ")"
        anchors.left: serviceReminderCB.right
        anchors.leftMargin: Math.round(100 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(14 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
        font.family: Style.regular.name
        color: Style.blackFontColor
        font.bold: true
    }

    Rectangle
    {
        id: serviceReminderSelectRect
        visible: serviceReminderCB.checked
        anchors.left: serviceReminderRect.left
        anchors.top: serviceReminderRect.bottom
        anchors.topMargin: Math.round(2 * Style.scaleHint)
        width: Math.round(155 * Style.scaleHint)
        height: Math.round(2 * Style.scaleHint)
        color: Style.buttonBackgroundColor
    }

    BransonPrimaryButton
    {
        id: resetBtn
        implicitWidth: Math.round(70 * Style.scaleHint)
        implicitHeight: Math.round(35 * Style.scaleHint)
        fontSize: Math.round(9  * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.right: generateReportBtn.left
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(9 * Style.scaleHint)
        text: qmlTextResetAll
        buttonColor: UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable ? "#17345C" : "#9b9e9c"
        font.family: Style.regular.name
        onClicked:
        {

            if(UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable)
            {
                if(AlarmDetailsListModel.getHornClampOnAlarmStatus())
                {
                    clamponAlertPopup.visible = true
                }
                else
                {
                  AlarmDetailsListModel.reset()
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: generateReportBtn
        implicitWidth: Math.round(70 * Style.scaleHint)
        implicitHeight: Math.round(35 * Style.scaleHint)
        fontSize: Math.round(9  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(9 * Style.scaleHint)
        text: qmlTextGenerateReport
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {

        }
    }

        Rectangle
        {
            id: columnRect
            width: parent.width
            height: eventlog.height * 0.08
            anchors.top: generateReportBtn.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.left: parent.left
            anchors.right: parent.right
            border.color:"#0F0F0F"
            clip:true

                Text
                {
                    id: errorTypeText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(30 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextErrorType
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }

                Text
                {
                    id: alarmIDText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(175 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextAlarmID
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }

                Text
                {
                    id: recipeText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(270 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextRecipe
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }

                Text
                {
                    id: recipeVerText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(345 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextRecipeVer
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }

                Text
                {
                    id: cycleText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(455 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextCycle
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }

                Text
                {
                    id: dateTimeText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(575 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextDateAndTime
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                    font.bold: true
                }
        }

    ListView
    {
        id: eventLogDetailsListView
        width: parent.width
        height: parent.height
        anchors.top: columnRect.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: columnRect.left
        anchors.bottom: parent.bottom
        spacing: Math.round(0 * Style.scaleHint)
        model: AlarmDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCurrentIndexChanged:
        {
        }

        delegate: Rectangle
        {
            id: cycleDetailsInfo
            visible: (alarmCB.checked && (model.AlarmSubType === alarmTypeEnum.alarmTypeAlarmIdx)) ||
                     (warningCB.checked && (model.AlarmSubType === alarmTypeEnum.alarmTypeWarningIdx)) ||
                     (notificationCB.checked && (model.AlarmSubType === alarmTypeEnum.alarmTypeNotificationIdx)) ||
                     (serviceReminderCB.checked && (model.AlarmSubType === alarmTypeEnum.alarmTypeServiceReminderIdx))
            width: eventLogDetailsListView.width
            height: (cycleDetailsInfo.visible) ? Math.round(60 * Style.scaleHint) : 0
            color: "transparent"
            Rectangle
            {
                id: delegateColorIndicatorRect
                z: 1
                anchors.left: parent.left
                width: Math.round(10 * Style.scaleHint)
                height: Math.round(50 * Style.scaleHint)
                color:
                {
                    switch (model.AlarmSubType)
                    {
                    case alarmTypeEnum.alarmTypeAlarmIdx :
                        return "#D31346"

                    case alarmTypeEnum.alarmTypeWarningIdx :
                        return "#FFD022"

                    case alarmTypeEnum.alarmTypeNotificationIdx :
                        return "#00A4D2"

                    case alarmTypeEnum.alarmTypeServiceReminderIdx :
                        return "#00FF00"

                    default:
                         return "#D31346"
                    }
                }

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
                    id: errorTypeTextDelegate
                    width: Math.round(150 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    text: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? AlarmDetailsListModel.getAlarmTypeString(model.AlarmID) : // "Start Switch Time"
                                                                                               model.AlarmUserName
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: alarmIDTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(180 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.AlarmID.toString(16).toUpperCase()//"628"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: recipeTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? Math.round(280 * Style.scaleHint) :
                                                                                                             Math.round(272 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? model.AlarmRecipeNo : "N/A"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: recipeVerTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? Math.round(370 * Style.scaleHint) :
                                                                                                             Math.round(362 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? model.AlarmRecipeVersion : "N/A"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: cycleTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? Math.round(460 * Style.scaleHint) :
                                                                                                             Math.round(452 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx) ? model.AlarmCycleNo : "N/A"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: dateTimeTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(550 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.AlarmDateTime//"2024-05-24 11:15"
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
                }

                MouseArea
                {
                    id: cycleDetailsInfoMouseArea
                    anchors.fill: parent
                    onClicked:
                    {
                        selectedIndex = index
                        eventLogDetailsListView.currentIndex = index
                        if (model.AlarmSubType !== alarmTypeEnum.alarmTypeServiceReminderIdx)
                        {
                            delegateRectHidden.visible = !(delegateRectHidden.visible)
                        }
                        cycleDetailsInfo.height = (delegateRectHidden.visible) ? Math.round(210 * Style.scaleHint) : Math.round(60 * Style.scaleHint)
                    }
                }
            }

            Rectangle
            {
                id: delegateRectHidden
                visible: false
                anchors.left: parent.left
                anchors.top: delegateRect.bottom
                anchors.topMargin: Math.round(0 * Style.scaleHint)
                width: parent.width
                height: Math.round(150 * Style.scaleHint)
                border.color:"#707070"
                clip:true

                Text
                {
                    id: descriptionText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(30 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(10 * Style.scaleHint)
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextDescription
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }

                Text
                {
                    id: userNameText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(180 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(10 * Style.scaleHint)
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextUserName
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }

                Text
                {
                    id: alarmTypeText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(320 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(10 * Style.scaleHint)
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextAlarmType
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }

                Text
                {
                    id: descriptionTextDetails
                    width: Math.round(125 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(30 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(35 * Style.scaleHint)
                    wrapMode: Text.WordWrap
                    text: AlarmDetailsListModel.getAlarmDescriptionString(model.AlarmID)//"Both start switches were not pressed within the allowed time frame"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: userNameTextDetails
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(180 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(35 * Style.scaleHint)
                    wrapMode: Text.WrapAnywhere
                    text: model.AlarmUserName//"N/A"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: alarmTypeTextDetails
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(320 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(35 * Style.scaleHint)
                    wrapMode: Text.WrapAnywhere
                    text: model.AlarmType.toString(16).toUpperCase()//"600"
                    font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.90
                }

                Rectangle
                {
                    id:addedNotesRect
                    width: parent.width *0.75
                    height: delegateRect.height *0.50
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(30 * Style.scaleHint)
                    anchors.top: descriptionTextDetails.top
                    anchors.topMargin: Math.round(60 * Style.scaleHint)
                    color: "#E5F2FF"
                    visible:  isNotesEmpty(model.AlarmAddedNotes)
                    clip:true
                    Text
                    {
                        id: addedNotesText
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(15 * Style.scaleHint)
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(5 * Style.scaleHint)
                        text: qmlTextAddedNotes + " :"
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                        font.bold: true
                    }
                    Text
                    {
                        id: addedNotesTextDetails
                        width: parent.width *0.70
                        anchors.left: addedNotesText.right
                        anchors.leftMargin: Math.round(5 * Style.scaleHint)
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(5 * Style.scaleHint)
                        text: model.AlarmAddedNotes
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.90
                    }
                }

                BransonPrimaryButton
                {
                    id: resultsBtn
                    implicitWidth: Math.round(124 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    fontSize: Math.round(Style.style2  * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(5 * Style.scaleHint)
                    anchors.right: parent.right
                    anchors.rightMargin:  Math.round(25 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    text: qmlTextResults
                    buttonColor: Style.buttonBackgroundColor
                    font.family: Style.regular.name

                    onClicked:
                    {
                        CycleDetailsListModel.isScreenNavigatedFromResultsBtn(true,model.AlarmCycleNo)
                        mainWindow.menuParentOptionSelect(UIScreenEnum.ANALYTICS)
                    }
                }

                BransonPrimaryButton
                {
                    id: addNotesBtn
                    implicitWidth: Math.round(124 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    fontSize: Math.round(Style.style2  * Style.scaleHint)
                    anchors.top: resultsBtn.bottom
                    anchors.topMargin: Math.round(10 * Style.scaleHint)
                    anchors.right: parent.right
                    anchors.rightMargin:  Math.round(25 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    text:isNotesEmpty(model.AlarmAddedNotes) ? qmlTextEditNotes : qmlTextAddNotes
                    buttonColor: Style.buttonBackgroundColor
                    font.family: Style.regular.name

                    onClicked:
                    {
                        mainWindow.showBransonWritablePopup(model.AlarmLogIndex)
                    }
                }

                BransonPrimaryButton
                {
                    id: resetBtn2
                    visible: (AlarmDetailsListModel.isActiveAlarm(model.AlarmID))
                    implicitWidth: Math.round(124 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    fontSize: Math.round(Style.style2  * Style.scaleHint)
                    anchors.top: addNotesBtn.bottom
                    anchors.topMargin: Math.round(10 * Style.scaleHint)
                    anchors.right: parent.right
                    anchors.rightMargin:  Math.round(25 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    text: qmlTextReset
                    buttonColor: UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable ? "#17345C" : "#9B9E9C"
                    font.family: Style.regular.name

                    onClicked:
                    {
                        if(UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable)
                        {
                            AlarmDetailsListModel.onResetAlarmPressed(model.AlarmID)
                        }
                    }
                }

                Rectangle
                {
                    id: delegateRectBottomHidden
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(2 * Style.scaleHint)
                    anchors.bottom: delegateRectHidden.bottom
                    anchors.bottomMargin: Math.round(2 * Style.scaleHint)
                    width: parent.width - Math.round(4 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    color: "#F3F3F3"
                    clip:true

                    Image
                    {
                        id: infoIcon
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(5 * Style.scaleHint)
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/Images/Info.svg"
                        height: Math.round(20 * Style.scaleHint)
                        width: Math.round(20 * Style.scaleHint)
                        sourceSize.width: infoIcon.width
                        sourceSize.height: infoIcon.height
                        smooth: true
                        fillMode: Image.PreserveAspectFit

                        MouseArea
                        {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    Text
                    {
                        id: alarmReason
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(25 * Style.scaleHint)
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        text: qmlTextProbableReason + " : "
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
                        font.bold: true
                    }

                    Text
                    {
                        id: alarmReasonDetails
                        anchors.left: alarmReason.right
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        text: AlarmDetailsListModel.getAlarmProbableReasonString(model.AlarmID)
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
                    }
                }
            }           
        }
    }
}

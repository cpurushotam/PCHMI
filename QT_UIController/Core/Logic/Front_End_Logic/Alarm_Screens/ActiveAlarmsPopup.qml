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
    id: eventlog
    property string qmlTextMenuName          : "Alarms Log"
    property string qmlTextNewAlarmFound     : "New Alarms Found"
    property string qmlTextErrorType         : "Error Type"
    property string qmlTextAlarmID           : "Alarm ID"
    property string qmlTextAction            : "Action"
    property string qmlTextAlarms            : "ALARMS"
    property string qmlTextReset             : "Reset"
    property string qmlTextResetAll          : "Reset All"
    property string qmlTextViewDetails       : "View Details"
    property string qmlTextAlert             : "ALERT !"
    property string qmlTextInfo              : "No Details Are Available!"
    property string qmlTextOK                : "OK"
    property string qmlTextEmpty             : "No Details To Show !"

    property var qmlTextArray: [qmlTextNewAlarmFound, qmlTextErrorType, qmlTextAlarmID, qmlTextAlarms,
                                qmlTextAction, qmlTextReset, qmlTextResetAll, qmlTextViewDetails, qmlTextAlert, qmlTextInfo, qmlTextOK, qmlTextEmpty]
    signal closeButtonClicked()
    signal activeAlarmDetailsListEmpty()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ALARMEVENTSLOG , qmlTextArray)
        qmlTextNewAlarmFound    = qmlTextArray[textEnum.textNewAlarmFoundIdx]
        qmlTextErrorType        = qmlTextArray[textEnum.textErrorTypeIdx]
        qmlTextAlarmID          = qmlTextArray[textEnum.textAlarmIDIdx]
        qmlTextAction           = qmlTextArray[textEnum.textActionIDIdx]
        qmlTextAlarms           = qmlTextArray[textEnum.textAlarmsIdx]
        qmlTextReset            = qmlTextArray[textEnum.textResetIdx]
        qmlTextResetAll         = qmlTextArray[textEnum.textResetAllIdx]
        qmlTextViewDetails      = qmlTextArray[textEnum.textViewDetailsIdx]
        qmlTextAlert            = qmlTextArray[textEnum.textAlertIdx]
        qmlTextInfo             = qmlTextArray[textEnum.textInfoIdx]
        qmlTextOK               = qmlTextArray[textEnum.textOKIdx]
        qmlTextEmpty            = qmlTextArray[textEnum.textEmptyIdx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ALARMEVENTSLOG, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textNewAlarmFoundIdx     : 0
        readonly property int textErrorTypeIdx         : 1
        readonly property int textAlarmIDIdx           : 2
        readonly property int textActionIDIdx          : 3
        readonly property int textAlarmsIdx            : 4
        readonly property int textResetIdx             : 5
        readonly property int textResetAllIdx          : 6
        readonly property int textViewDetailsIdx       : 7
        readonly property int textAlertIdx             : 8
        readonly property int textInfoIdx              : 9
        readonly property int textOKIdx                : 10
        readonly property int textEmptyIdx             : 11
    }

    QtObject
    {
        id: alarmTypeEnum
        readonly property int alarmTypeNoneIdx         : 0
        readonly property int alarmTypeAlarmIdx        : 1
        readonly property int alarmTypeWarningIdx      : 2
        readonly property int alarmTypeNotificationIdx : 3
    }

    Component.onCompleted:
    {
        updateLanguage()
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
        color: "#D31346"

        Text
        {
            id: headername
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmlTextAlarms
            color: Style.whiteFontColor
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style3 * Style.scaleHint)
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

    Image
    {
        id: bellSymbol
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: popupHeader.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        width: Math.round(30 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        sourceSize.width: Math.round(30 * Style.scaleHint)
        sourceSize.height: Math.round(30 * Style.scaleHint)
        source: "qrc:/Images/Alarm2.png"
        fillMode: Image.PreserveAspectFit

        ColorOverlay
        {
            anchors.fill: bellSymbol
            source: bellSymbol
            color: "#D31346"
        }

        MouseArea
        {
            id: bellSymbolMA
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                closeButtonClicked()
            }
        }
    }

    Text
    {
        id: newAlarmFoundText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: bellSymbol.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextNewAlarmFound
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
        font.bold: true
    }
        Rectangle
        {
            id: columnRect
            width: parent.width - Math.round(40 * Style.scaleHint)
            height: eventlog.height * 0.08
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: newAlarmFoundText.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            border.color:"#0F0F0F"
            clip: true

                Text
                {
                    id: errorTypeText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(30 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextErrorType
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }

                Text
                {
                    id: alarmIDText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(180 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextAlarmID
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }

                Text
                {
                    id: actionText
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(325 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: qmlTextAction
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                    font.bold: true
                }
        }

        /*Empty list display message*/
        Text
        {
            id: emptyText
            visible: (! ActiveAlarmDetailsListModel.TotalActiveAlarmsWarningsNotificationsCount)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextEmpty
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

    ListView
    {
        id: eventLogDetailsListView
        width: columnRect.width
        height: Math.round(180 * Style.scaleHint)
        anchors.top: columnRect.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: columnRect.left
        spacing: Math.round(0 * Style.scaleHint)
        model: ActiveAlarmDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCountChanged:
        {
            /*To avoid blank screen when alarms are reset at backend*/
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

                    default :
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
                    text: ActiveAlarmDetailsListModel.getAlarmTypeString(model.AlarmID)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: alarmIDTextDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(185 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.AlarmID.toString(16).toUpperCase()
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                BransonPrimaryButton
                {
                    id: resetBtn
                    implicitWidth: Math.round(60 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    fontSize: Math.round(Style.style2  * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin:  Math.round(275 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Math.round(9 * Style.scaleHint)
                    text: qmlTextReset
                    buttonColor: UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable ? "#17345C" : "#9B9E9C"
                    font.family: Style.regular.name

                    onClicked:
                    {
                        if(UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable)
                        {
                             ActiveAlarmDetailsListModel.onResetAlarmPressed(model.AlarmID)
                        }
                    }
                }

                BransonPrimaryButton
                {
                    id: viewDetailsBtn
                    implicitWidth: Math.round(70 * Style.scaleHint)
                    implicitHeight: Math.round(30 * Style.scaleHint)
                    fontSize: Math.round(9  * Style.scaleHint)
                    anchors.left: resetBtn.right
                    anchors.leftMargin:  Math.round(9 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    text: qmlTextViewDetails
                    buttonColor: Style.buttonBackgroundColor
                    font.family: Style.regular.name

                    onClicked:
                    {
                        /*Is there is alarm log information available*/
                        if(model.AlarmIsLogRequired)
                        {
                            if(ActiveScreen.CurrentActiveScreen !== UIScreenEnum.DIAGNOSTICS_ALARM)
                            {
                                switch (model.AlarmSubType)
                                {
                                case alarmTypeEnum.alarmTypeAlarmIdx :
                                    /*To understand that screen is navigated from active alarms popup*/
                                    AlarmDetailsListModel.IsScreenNavigatedFromAlarmsPopup = true
                                    break

                                case alarmTypeEnum.alarmTypeWarningIdx :
                                    /*To understand that screen is navigated from active warnings popup*/
                                    AlarmDetailsListModel.IsScreenNavigatedFromWarningsPopup = true
                                    break

                                case alarmTypeEnum.alarmTypeNotificationIdx :
                                    /*To understand that screen is navigated from active notifications popup*/
                                    AlarmDetailsListModel.IsScreenNavigatedFromNotificationsPopup = true
                                    break

                                default:
                                    /*To understand that screen is navigated from active alarms popup*/
                                    AlarmDetailsListModel.IsScreenNavigatedFromAlarmsPopup = true
                                    break
                                }

                                mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_ALARM)
                            }

                            else
                            {
                                /*To make sure proper signal shall get emit based on current active screen*/
                                switch (model.AlarmSubType)
                                {
                                case alarmTypeEnum.alarmTypeAlarmIdx :
                                    /*To understand that screen is navigated from active alarms popup*/
                                    AlarmDetailsListModel.isScreenNavigatedWhenAlarmLogIsVisibleFromAlarmsPopup(true)
                                    break

                                case alarmTypeEnum.alarmTypeWarningIdx :
                                    /*To understand that screen is navigated from active warnings popup*/
                                    AlarmDetailsListModel.isScreenNavigatedWhenAlarmLogIsVisibleFromWarningsPopup(true)
                                    break

                                case alarmTypeEnum.alarmTypeNotificationIdx :
                                    /*To understand that screen is navigated from active notifications popup*/
                                    AlarmDetailsListModel.isScreenNavigatedWhenAlarmLogIsVisibleFromNotificationsPopup(true)
                                    break

                                default:
                                    /*To understand that screen is navigated from active alarms popup*/
                                    AlarmDetailsListModel.isScreenNavigatedWhenAlarmLogIsVisibleFromAlarmsPopup(true)
                                    break
                                }
                            }

                            closeButtonClicked()
                        }

                        /*If there is no alarm log information available*/
                        else
                        {
                            noLogAvailablePopup.visible = true
                        }
                    }
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: resetAllBtn
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.left: eventLogDetailsListView.left
        anchors.top: eventLogDetailsListView.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmlTextResetAll
        buttonColor: UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable ? "#17345C" : "#9B9E9C"
        font.family: Style.regular.name

        onClicked:
        {
            if(UserPrivilegeObj.IsResetAlarmsAllowed || mainWindow.isAuthorityCheckEnable)
            {
                ActiveAlarmDetailsListModel.reset()
                closeButtonClicked()
            }
        }
    }

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        visible: noLogAvailablePopup.visible
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

    /*When no information available popup*/
    Rectangle
    {
        id: noLogAvailablePopup
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: Math.round(150 * Style.scaleHint)

        Rectangle
        {
            id: noLogAvailablePopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: noLogAvailablePopupHeaderName
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmlTextAlert
                color: Style.whiteFontColor
                font
                {
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    bold: true
                }
            }

            Image
            {
                id: noLogAvailablePopupImageCross
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(30 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                sourceSize.width: Math.round(30 * Style.scaleHint)
                sourceSize.height: Math.round(30 * Style.scaleHint)
                source: "qrc:/Images/crossMark.svg"
                fillMode: Image.PreserveAspectFit

                MouseArea
                {
                    id: noLogAvailablePopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        noLogAvailablePopup.visible = false
                    }
                }
            }
        }

        Text
        {
            id: noLogAvailablePopupText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(5 * Style.scaleHint)
            anchors.top: noLogAvailablePopupHeader.bottom
            anchors.topMargin: Math.round(35 * Style.scaleHint)
            text: qmlTextInfo
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style2 * Style.scaleHint)
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
                noLogAvailablePopup.visible = false
            }
        }
    }
}

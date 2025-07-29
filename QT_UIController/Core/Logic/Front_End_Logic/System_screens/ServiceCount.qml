/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the service count information.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/09/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import QtQuick.VirtualKeyboard 2.15
import AxisDefine 1.0
import QtQuick.Layouts 1.15
import Com.Branson.GraphAxisEnum 1.0
import "./../Diagnostics_Screens"
import "./../Common_Logic"

Item
{
    id: eventlog
    property string qmlTextMenuName          : "Service Count"
    property string qmlTextAddServiceCount   : "ADD SERVICE COUNT"
    property string qmlTextServiceName       : "Service Name"
    property string qmlTextCounter           : "Counter"
    property string qmlTextLimit             : "Limit"
    property string qmlTextEndDateAndTime    : "End Date & Time"
    property string qmlTextAction            : "Action"
    property string qmlTextEdit              : "Edit"
    property string qmlTextReset             : "Reset"
    property string qmlTextDelete            : "Delete"
    property string qmlTextUserID            : "User ID"
    property string qmlTextServiceType       : "Method"
    property string qmlTextCounterReminder   : "Limit"
    property string qmlTextDate              : "Date"
    property string qmlTextTime              : "Time"
    property string qmlTextEditServiceCount  : "EDIT SERVICE COUNT"
    property string qmlTextCount             : "Count"
    property string qmlTextDateAndTime       : "Date & Time"
    property string qmlTextSave              : "Save"
    property string qmlTextOK                : "OK"
    property string qmlTextAlert             : "ALERT !"
    property string qmlTextErrorUnknown      : "Add Reminder Unknown Error !"
    property string qmlTextSuccess           : "Add Reminder Successful !"
    property string qmlTextFail              : "Add Reminder Fail !"
    property string qmlTextAlreadyExist      : "Reminder Name Aleady Exist !"
    property string qmlTextLimitCrossed      : "Add Reminder Maximum Limit Crossed !"
    property string qmlTextMethod            : "Method"
    property string qmlTextInvalidData       : "Entered Data Is Not Valid !"
    property string qmlTextAlertMessage      : "Are you sure. Do you want to delete ?"
    property string qmlServiceNameToDel      : ""
    property string qmlTextAccessError       : "Access Is Restricted For Branson Service"
    property string qmlTextAccessError2      : "Person Only !"

    property var qmlTextArray: [qmlTextMenuName, qmlTextAddServiceCount, qmlTextServiceName, qmlTextCounter, qmlTextLimit, qmlTextEndDateAndTime,
        qmlTextAction, qmlTextEdit, qmlTextReset, qmlTextDelete, qmlTextUserID, qmlTextServiceType, qmlTextCounterReminder, qmlTextDate,
        qmlTextTime, qmlTextEditServiceCount, qmlTextCount, qmlTextDateAndTime, qmlTextSave, qmlTextOK, qmlTextAlert, qmlTextErrorUnknown,
        qmlTextSuccess, qmlTextFail, qmlTextAlreadyExist, qmlTextLimitCrossed, qmlTextMethod, qmlTextInvalidData, qmlTextAlertMessage, qmlTextAccessError,
        qmlTextAccessError2]

    property var qmlServiceCountTypeOptions: [qmlTextCount, qmlTextDateAndTime]

    property bool isPaused      : false
    property int currentDate    : new Date().getDate()
    property int currentMonth   : new Date().getMonth()
    property int currentYear    : new Date().getFullYear()
    property int currentHours   : new Date().getHours()
    property int currentMinutes : new Date().getMinutes()
    property int currentYears   : new Date().getSeconds()
    signal counterReminderChanged()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_SERVICE_COUNT , qmlTextArray)
        qmlTextAddServiceCount  = qmlTextArray[textEnum.textAddServiceCountIdx]
        qmlTextServiceName      = qmlTextArray[textEnum.textServiceNameIdx]
        qmlTextCounter          = qmlTextArray[textEnum.textCounterIdx]
        qmlTextLimit            = qmlTextArray[textEnum.textLimitIdx]
        qmlTextEndDateAndTime   = qmlTextArray[textEnum.textEndDateAndTimeIdx]
        qmlTextAction           = qmlTextArray[textEnum.textActionIdx]
        qmlTextEdit             = qmlTextArray[textEnum.textEditIdx]
        qmlTextReset            = qmlTextArray[textEnum.textResetIdx]
        qmlTextDelete            = qmlTextArray[textEnum.textDeleteIdx]
        qmlTextUserID           = qmlTextArray[textEnum.textUserIDIdx]
        qmlTextServiceType      = qmlTextArray[textEnum.textServiceTypeIdx]
        qmlTextCounterReminder  = qmlTextArray[textEnum.textCounterReminderIdx]
        qmlTextDate             = qmlTextArray[textEnum.textDateIdx]
        qmlTextTime             = qmlTextArray[textEnum.textTimeIdx]
        qmlTextEditServiceCount = qmlTextArray[textEnum.textEditServiceCountIdx]
        qmlTextCount            = qmlTextArray[textEnum.textCountIdx]
        qmlTextDateAndTime      = qmlTextArray[textEnum.textDateAndTimeIdx]
        qmlTextSave             = qmlTextArray[textEnum.textSaveIdx]
        qmlTextOK               = qmlTextArray[textEnum.textOKIdx]
        qmlTextAlert            = qmlTextArray[textEnum.textAlertIdx]
        qmlTextErrorUnknown     = qmlTextArray[textEnum.textErrorUnknownIdx]
        qmlTextSuccess          = qmlTextArray[textEnum.textSuccessIdx]
        qmlTextFail             = qmlTextArray[textEnum.textFailIdx]
        qmlTextAlreadyExist     = qmlTextArray[textEnum.textAlredyExistIdx]
        qmlTextLimitCrossed     = qmlTextArray[textEnum.textLimitCrossedIdx]
        qmlTextMethod           = qmlTextArray[textEnum.textMethodIdx]
        qmlTextInvalidData      = qmlTextArray[textEnum.textInvalidDataIdx]
        qmlTextAlertMessage     = qmlTextArray[textEnum.alertMessageIdx]
        qmlTextAccessError      = qmlTextArray[textEnum.textAccessErrorIdx]
        qmlTextAccessError2      = qmlTextArray[textEnum.textAccessError2Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_SERVICE_COUNT, qmlTextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textAddServiceCountIdx  : 0
        readonly property int textServiceNameIdx      : 1
        readonly property int textCounterIdx          : 2
        readonly property int textLimitIdx            : 3
        readonly property int textEndDateAndTimeIdx   : 4
        readonly property int textActionIdx           : 5
        readonly property int textEditIdx             : 6
        readonly property int textResetIdx            : 7
        readonly property int textDeleteIdx           : 8
        readonly property int textUserIDIdx           : 9
        readonly property int textServiceTypeIdx      : 10
        readonly property int textCounterReminderIdx  : 11
        readonly property int textDateIdx             : 12
        readonly property int textTimeIdx             : 13
        readonly property int textEditServiceCountIdx : 14
        readonly property int textCountIdx            : 15
        readonly property int textDateAndTimeIdx      : 16
        readonly property int textSaveIdx             : 17
        readonly property int textOKIdx               : 18
        readonly property int textAlertIdx            : 19
        readonly property int textErrorUnknownIdx     : 20
        readonly property int textSuccessIdx          : 21
        readonly property int textFailIdx             : 22
        readonly property int textAlredyExistIdx      : 23
        readonly property int textLimitCrossedIdx     : 24
        readonly property int textMethodIdx           : 25
        readonly property int textInvalidDataIdx      : 26
        readonly property int alertMessageIdx         : 27
        readonly property int textAccessErrorIdx      : 28
        readonly property int textAccessError2Idx     : 29
    }

    QtObject
    {
        id: serviceTypeEnum
        readonly property int counterBasedMethod      : 0
        readonly property int dateTimeBasedMethod     : 1
    }

    QtObject
    {
        id: serviceReminderStatusEnum
        readonly property int reminderDisable         : 0
        readonly property int reminderEnable          : 1
    }

    QtObject
    {
        id: addReminderErrorCodeEnum
        readonly property int errorUnknown  : 0
        readonly property int success       : 1
        readonly property int fail          : 2
        readonly property int alreadyExist  : 3
        readonly property int limitCrossed  : 4
    }

    Component.onCompleted:
    {
        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_SERVICE_COUNT)
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_SERVICE_COUNT
        ServiceCountListModel.isScreenReNavigated(true)
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    /*Function to validate the date*/
       function isValidDate(year, month, day)
       {
           var val2 = day
           const date = new Date(year, month - 1, day)
           const val = date.getDate()

           if((date.getFullYear() === year) &&
                   (date.getMonth() === (month-1)) &&
                   (val === parseInt(val2)))

               return true

           else

               return false
       }

    BransonPopup
    {
        id: deletePopup
        qmltextLabel: qmlTextAlert
        qmltextWarningDialog : qmlTextAlertMessage
        isMultiButtonPopup : true
        anchors.centerIn: parent

        onOKButtonClicked:
        {
            ServiceCountListModel.onDeletePressed(qmlServiceNameToDel)

            deletePopup.visible = false
        }

        onCancelButtonClicked:
        {
            deletePopup.visible = false
        }
    }

    Connections
    {
        target: ServiceCountListModel
        function onCounterReminderChanged()
        {
            addServiceCountReminderTextField.text = ServiceCountListModel.CounterReminder
            editServiceCountReminderTextField.text = ServiceCountListModel.CounterReminder
        }
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        MouseArea
        {
            id : backGroundMA
            anchors.fill: parent
            onClicked:
            {
                addServiceServiceNameTextField.focus = false
                addInputPanel.visible = false
            }
        }
    }

    BransonPrimaryButton
    {
        id: addServiceCountBtn
        implicitWidth: Math.round(150 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style0  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        font.pixelSize: Math.round(7 * Style.scaleHint)
        text: qmlTextAddServiceCount
        buttonColor: (mainWindow.bransonTabEnable) ? Style.buttonColor : Style.disabledButtonBackgroundColor
        font.family: Style.regular.name
        /*enabled: mainWindow.bransonTabEnable*/

        onClicked:
        {
            /*If access available*/
            if(mainWindow.bransonTabEnable)
            {
                addServiceCountPopup.visible = true
                addServiceServiceNameTextField.text = ""
                addServiceServiceCountTypeComboBox.currentIndex = serviceTypeEnum.counterBasedMethod
                addServiceCountReminderTextField.text = ""

                /*As when user press add reminder button logically else condition wont perform
              as by default counter based method is selected*/
                if(addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
                {
                    addDayComboBox.currentIndex = addDayComboBox.indexOfValue(1)
                    addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(1)
                    addYearComboBox.currentIndex = addYearComboBox.indexOfValue(1970)
                    addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(00)
                    addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(00)
                    addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(00)
                }

                else
                {
                    /*Make sure every time user presses add button, current time gets upadted*/
                    currentDate    = new Date().getDate()
                    currentMonth   = new Date().getMonth()
                    currentYear    = new Date().getFullYear()
                    currentHours   = new Date().getHours()
                    currentMinutes = new Date().getMinutes()
                    currentYears   = new Date().getSeconds()

                    addDayComboBox.currentIndex = addDayComboBox.indexOfValue(currentDate)
                    addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(currentMonth + 1)
                    addYearComboBox.currentIndex = addYearComboBox.indexOfValue(currentYear)
                    addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(currentHours)
                    addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(currentMinutes)
                    addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(currentYears)
                }
            }

            /*No access available popup*/
            else
            {
                noAccessAlertPopup.visible = true
            }
        }
    }

    Rectangle
    {
        id: columnRect
        width: parent.width - Math.round(40 * Style.scaleHint)
        height: eventlog.height * 0.08
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: Math.round(50 * Style.scaleHint)
        border.color:"#0F0F0F"
        clip: true

        Text
        {
            id: serviceNameText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextServiceName
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

        Text
        {
            id: counterText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(150 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextCounter
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

        Text
        {
            id: limitText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(250 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextLimit
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

        Text
        {
            id: reminderMethodText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(320 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextMethod
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

        Text
        {
            id: endDateTimeText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(410 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextEndDateAndTime
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
            font.bold: true
        }

        Text
        {
            id: actionText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(625 * Style.scaleHint)
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
        height: Math.round(295 * Style.scaleHint)
        anchors.top: columnRect.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: columnRect.left
        spacing: Math.round(0 * Style.scaleHint)
        model: ServiceCountListModel
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
            width: eventLogDetailsListView.width
            height: Math.round(55 * Style.scaleHint)
            color: "transparent"

            Rectangle
            {
                id: delegateRect
                anchors.left: parent.left
                width: parent.width
                height: Math.round(50 * Style.scaleHint)
                border.color:"#707070"
                clip:true

                Text
                {
                    id: serviceNameDelegate
                    width: Math.round(150 * Style.scaleHint)
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WordWrap
                    text: model.ServiceCountServiceName
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: counterDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(170 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.ServiceCountCounter
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Text
                {
                    id: limitDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(260 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.ServiceCountLimit
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Image
                {
                    id: reminderMethodDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                                            Math.round(332 * Style.scaleHint) : Math.round(335 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                               Math.round(25 * Style.scaleHint) : Math.round(20 * Style.scaleHint)
                    height: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                                Math.round(25 * Style.scaleHint) : Math.round(20 * Style.scaleHint)
                    sourceSize.width: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                                          Math.round(25 * Style.scaleHint) : Math.round(20 * Style.scaleHint)
                    sourceSize.height: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                                           Math.round(25 * Style.scaleHint) : Math.round(20 * Style.scaleHint)
                    source: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ?
                                "qrc:/Images/Counter.png" : "qrc:/Images/Timer.png"
                    fillMode: Image.PreserveAspectFit
                }

                Text
                {
                    id: endDateTimeDelegate
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(405 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.WrapAnywhere
                    text: model.ServiceCountReminderMethod  === (serviceTypeEnum.counterBasedMethod) ? "NA" :  model.ServiceCountStartTime
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                }

                Image
                {
                    id: puseResumeBtn
                    anchors.left: parent.left
                    anchors.leftMargin:  Math.round(590 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    sourceSize.width: Math.round(20 * Style.scaleHint)
                    sourceSize.height: Math.round(20 * Style.scaleHint)
                    source: (model.ServiceCountReminderStatus === serviceReminderStatusEnum.reminderDisable) ?
                                "qrc:/Images/Play.png" : "qrc:/Images/Pause.png"
                    fillMode: Image.PreserveAspectFit

                    ColorOverlay
                    {
                        anchors.fill: puseResumeBtn
                        source: puseResumeBtn
                        color: "#004B8D"
                    }

                    MouseArea
                    {
                        id: puseResumeBtnMA
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked:
                        {
                            if(mainWindow.bransonTabEnable)
                            {
                                if(! (model.ServiceCountReminderStatus ===  serviceReminderStatusEnum.reminderDisable))
                                {
                                    ServiceCountListModel.onPausePressed(model.ServiceCountServiceName)
                                }

                                else
                                {
                                    ServiceCountListModel.onResumePressed(model.ServiceCountServiceName)
                                }
                            }

                            /*No access available popup*/
                            else
                            {
                                noAccessAlertPopup.visible = true
                            }
                        }
                    }
                }

                Image
                {
                    id: editBtn
                    anchors.left: puseResumeBtn.right
                    anchors.leftMargin:  Math.round(10 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    sourceSize.width: Math.round(20 * Style.scaleHint)
                    sourceSize.height: Math.round(20 * Style.scaleHint)
                    source: "qrc:/Images/Edit_icon.svg"
                    fillMode: Image.PreserveAspectFit
                    ColorOverlay
                    {
                        anchors.fill: editBtn
                        source: editBtn
                        color: "#004B8D"
                    }

                    MouseArea
                    {
                        id: editBtnMA
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked:
                        {
                            if(mainWindow.bransonTabEnable)
                            {
                                editServiceServiceNameTextField.text = model.ServiceCountServiceName
                                editServiceServiceCountTypeComboBox.currentIndex = model.ServiceCountReminderMethod
                                editServiceCountReminderTextField.text = model.ServiceCountLimit
                                editMonthComboBox.currentIndex = editMonthComboBox.indexOfValue(ServiceCountListModel.indexMonth(index))
                                editDayComboBox.currentIndex = editDayComboBox.indexOfValue(ServiceCountListModel.indexDay(index))
                                editYearComboBox.currentIndex = editYearComboBox.indexOfValue(ServiceCountListModel.indexYear(index))
                                editHoursComboBox.currentIndex = editHoursComboBox.indexOfValue(ServiceCountListModel.indexHours(index))
                                editMinutesComboBox.currentIndex = editMinutesComboBox.indexOfValue(ServiceCountListModel.indexMinutes(index))
                                editSecondsComboBox.currentIndex = editSecondsComboBox.indexOfValue(ServiceCountListModel.indexSeconds(index))

                                editServiceCountPopup.visible = true
                            }

                            /*No access available popup*/
                            else
                            {
                                noAccessAlertPopup.visible = true
                            }
                        }
                    }
                }

                Image
                {
                    id: resetBtn
                    anchors.left: editBtn.right
                    anchors.leftMargin:  Math.round(10 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    sourceSize.width: Math.round(20 * Style.scaleHint)
                    sourceSize.height: Math.round(20 * Style.scaleHint)
                    source: "qrc:/Images/Reset.png"
                    fillMode: Image.PreserveAspectFit
                    visible: (model.ServiceCountReminderMethod === serviceTypeEnum.counterBasedMethod) ? true :false
                    ColorOverlay
                    {
                        anchors.fill: resetBtn
                        source: resetBtn
                        color: "#004B8D"
                    }

                    MouseArea
                    {
                        id: resetBtnMA
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked:
                        {
                            if(mainWindow.bransonTabEnable)
                            {
                                ServiceCountListModel.onResetPressed(model.ServiceCountServiceName)
                            }

                            /*No access available popup*/
                            else
                            {
                                noAccessAlertPopup.visible = true
                            }
                        }
                    }
                }

                Image
                {
                    id: deleteBtn
                    anchors.left: resetBtn.right
                    anchors.leftMargin:  Math.round(10 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    sourceSize.width: Math.round(20 * Style.scaleHint)
                    sourceSize.height: Math.round(20 * Style.scaleHint)
                    source: "qrc:/Images/Blue_Trash_icon.svg"
                    fillMode: Image.PreserveAspectFit
                    ColorOverlay
                    {
                        anchors.fill: deleteBtn
                        source: deleteBtn
                        color: "#004B8D"
                    }

                    MouseArea
                    {
                        id: deleteBtnMA
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked:
                        {
                            if(mainWindow.bransonTabEnable)
                            {
                                qmlServiceNameToDel = model.ServiceCountServiceName
                                deletePopup.visible = true
                            }

                            /*No access available popup*/
                            else
                            {
                                noAccessAlertPopup.visible = true
                            }
                        }
                    }
                }
            }
        }
    }


    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        visible: (addServiceCountPopup.visible || editServiceCountPopup.visible
                  || serviceReminderOperationStatusPopup.visible || deletePopup.visible)
        anchors.left: parent.Left
        anchors.top: parent.Top
        height: mainWindow.height
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

    /*Add service count popup*/
    Rectangle
    {
        id: addServiceCountPopup
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.80
        height: Math.round(350 * Style.scaleHint)
        enabled: mainWindow.bransonTabEnable

        InputPanel
        {
            id: addInputPanel
            z: 1
            height: mainWindow.showHeight * 0.80
            width: parent.width
            visible: Qt.inputMethod.visible
            anchors.bottom: parent.bottom
        }

        Rectangle
        {
            id: addServiceCountPopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor
            enabled: mainWindow.bransonTabEnable

            Text
            {
                id: addServiceCountPopupHeaderName
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmlTextAddServiceCount
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
                id: addServiceCountPopupImageCross
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
                    id: addServiceCountPopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        addServiceCountPopup.visible = false
                    }
                }
            }
        }

        Rectangle
        {
            id: addServiceServiceNameRect
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addServiceCountPopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addServiceServiceNameText
                text: qmlTextServiceName
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id: addServiceServiceNameTextField
                z: 1
                width: parent.width * 0.90
                height: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: addServiceServiceNameText.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Normal
                placeholderText: qmlTextServiceName
                maximumLength: 15

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#FFFFFF"
                    radius: 5
                    border.color: "#707070"
                }

                MouseArea
                {
                    id : addServiceServiceNameTextFieldMA
                    anchors.fill: parent
                    onClicked:
                    {
                        addServiceServiceNameTextField.focus = true
                        addInputPanel.visible = true
                    }
                }
            }

            MouseArea
            {
                id : addServiceServiceNameMA
                anchors.fill: parent
                onClicked:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: addServiceServiceTypeRect
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: addServiceServiceNameRect.right
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addServiceCountPopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addServiceServiceTypeText
                text: qmlTextServiceType
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            BransonComboBox
            {
                id: addServiceServiceCountTypeComboBox
                z: 1
                currentIndex: 0
                anchors.top: addServiceServiceTypeText.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                minWidth: parent.width * 0.90
                minHeight: Math.round(25 * Style.scaleHint)
                model: qmlServiceCountTypeOptions

                onPressedChanged:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }

                onCurrentIndexChanged:
                {
                    /*Make sure every time user selects counter based method, default time shall get upadted*/
                    if(addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
                    {
                        addDayComboBox.currentIndex = addDayComboBox.indexOfValue(1)
                        addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(1)
                        addYearComboBox.currentIndex = addYearComboBox.indexOfValue(1970)
                        addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(00)
                        addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(00)
                        addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(00)
                    }

                    /*Make sure every time user selects time based method, current time shall get upadted*/
                    else
                    {
                        currentDate    = new Date().getDate()
                        currentMonth   = new Date().getMonth()
                        currentYear    = new Date().getFullYear()
                        currentHours   = new Date().getHours()
                        currentMinutes = new Date().getMinutes()
                        currentYears   = new Date().getSeconds()

                        addDayComboBox.currentIndex = addDayComboBox.indexOfValue(currentDate)
                        addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(currentMonth + 1)
                        addYearComboBox.currentIndex = addYearComboBox.indexOfValue(currentYear)
                        addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(currentHours)
                        addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(currentMinutes)
                        addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(currentYears)
                    }
                }
            }

            MouseArea
            {
                id : addServiceServiceCountTypeMA
                anchors.fill: parent
                onClicked:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: addServiceCountReminderRect
            visible: (addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addServiceServiceNameRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addServiceCountReminderText
                text: qmlTextCounterReminder
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id: addServiceCountReminderTextField
                z: 1
                width: parent.width * 0.90
                height: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: addServiceCountReminderText.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Normal
                placeholderText: qmlTextCounterReminder

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#FFFFFF"
                    radius: 5
                    border.color: "#707070"
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        mainWindow.showPrimaryNumpad(qmlTextAddServiceCount, "NA", 0, 1, 100000, addServiceCountReminderTextField.text)
                    }
                }
            }

            MouseArea
            {
                id : addServiceServiceCountReminderMA
                anchors.fill: parent
                onClicked:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: addServiceDateRect
            visible: (addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.dateTimeBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addServiceServiceNameRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addServiceDateText
                text: qmlTextDate
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addMonthComboBox
                z: 1
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: addServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: addMonthComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addMonthDelegateText
                    text: model.month
                    width: addMonthComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 1; i <= 12; i++)
                    {
                        addMonthComboBoxModel.append({"month": + i});
                    }
                }
            }

            ComboBox
            {
                id: addDayComboBox
                z: 1
                anchors.left: addMonthComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: addServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: addDayComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addDayDelegateText
                    text: model.day
                    width: addDayComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 1; i <= 31; i++)
                    {
                        addDayComboBoxModel.append({"day": + i});
                    }
                }
            }

            ComboBox
            {
                id: addYearComboBox
                z: 1
                anchors.left: addDayComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: addServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                model: ListModel
                {
                    id: addYearComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addYearDelegateText
                    text: model.year
                    width: addYearComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 2000; i <= 2075; i++)
                    {
                        addYearComboBoxModel.append({"year": + i});
                    }
                }
            }

            MouseArea
            {
                id : addServiceServiceDateMA
                anchors.fill: parent
                onClicked:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: addServiceTimeRect
            visible: (addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.dateTimeBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: addServiceCountReminderRect.right
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addServiceServiceTypeRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addServiceTimeText
                text: qmlTextTime
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addHoursComboBox
                z: 1
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: addServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: addHoursComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addHoursDelegateText
                    text: model.hours
                    width: addHoursComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 23; i++)
                    {
                        addHoursComboBoxModel.append({"hours": + i});
                    }

                    addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(currentHours)
                }
            }

            ComboBox
            {
                id: addMinutesComboBox
                z: 1
                anchors.left: addHoursComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: addServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: addMinutesComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addMinutesDelegateText
                    text: model.minutes
                    width: addMinutesComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 59; i++)
                    {
                        addMinutesComboBoxModel.append({"minutes": + i});
                    }

                    addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(currentMinutes)
                }
            }

            ComboBox
            {
                id: addSecondsComboBox
                z: 1
                anchors.left: addMinutesComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: addServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: addSecondsComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: addSecondsDelegateText
                    text: model.seconds
                    width: addSecondsComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 59; i++)
                    {
                        addSecondsComboBoxModel.append({"seconds": + i});
                    }

                    addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(currentYears)
                }
            }

            MouseArea
            {
                id : addServiceServiceTimeMA
                anchors.fill: parent
                onClicked:
                {
                    addServiceServiceNameTextField.focus = false
                    addInputPanel.visible = false
                }
            }
        }

        BransonPrimaryButton
        {
            id: addServiceSaveBtn
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            text: qmlTextSave
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name

            onClicked:
            {
                ServiceCountListModel.serviceName(addServiceServiceNameTextField.text)
                ServiceCountListModel.serviceType(addServiceServiceCountTypeComboBox.currentIndex)
                ServiceCountListModel.serviceCountReminder(addServiceCountReminderTextField.text)
                ServiceCountListModel.month(addMonthComboBox.currentValue)
                ServiceCountListModel.day(addDayComboBox.currentValue)
                ServiceCountListModel.year(addYearComboBox.currentValue)
                ServiceCountListModel.hours(addHoursComboBox.currentValue)
                ServiceCountListModel.minutes(addMinutesComboBox.currentValue)
                ServiceCountListModel.seconds(addSecondsComboBox.currentValue)

                /*Counter based method*/
                if(addServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
                {
                    if((addServiceServiceNameTextField.text === "") || (addServiceCountReminderTextField.text === ""))
                    {
                        serviceReminderOperationStatusPopup.visible = true
                        serviceReminderOperationStatusPopupAlertMsg.text = qmlTextInvalidData
                    }

                    else
                    {
                        ServiceCountListModel.onAddSavePressed()

                        /*Trigger the response timer*/
                        responseValidationTimer.interval = 500
                        responseValidationTimer.running = true
                        responseValidationTimer.start()
                    }
                }

                /*Date & Time based method*/
                else
                {
                    const day = addDayComboBox.currentValue;
                    const month = addMonthComboBox.currentValue;
                    const year = addYearComboBox.currentValue;

                    if (! isValidDate(year, month, day))
                    {
                        serviceReminderOperationStatusPopup.visible = true
                        serviceReminderOperationStatusPopupAlertMsg.text = qmlTextInvalidData
                    }

                    else
                    {
                        ServiceCountListModel.onAddSavePressed()

                        /*Trigger the response timer*/
                        responseValidationTimer.interval = 500
                        responseValidationTimer.running = true
                        responseValidationTimer.start()
                    }
                }
            }
        }
    }

    /*Update service count popup*/
    Rectangle
    {
        id: editServiceCountPopup
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.80
        height: Math.round(350 * Style.scaleHint)

        InputPanel
        {
            id: editInputPanel
            z: 1
            height: mainWindow.showHeight * 0.80
            width: parent.width
            visible: Qt.inputMethod.visible
            anchors.bottom: parent.bottom
        }

        Rectangle
        {
            id: editServiceCountPopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: editServiceCountPopupHeaderName
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmlTextEditServiceCount
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
                id: editServiceCountPopupImageCross
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
                    id: editServiceCountPopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        editServiceCountPopup.visible = false
                    }
                }
            }
        }

        Rectangle
        {
            id: editServiceServiceNameRect
            enabled: false
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: editServiceCountPopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: editServiceServiceNameText
                text: qmlTextServiceName
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id: editServiceServiceNameTextField
                z: 1
                width: parent.width * 0.90
                height: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: editServiceServiceNameText.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Normal

                Text
                {
                    id: editServiceServiceText
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    font.pixelSize: Math.round(10 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: "#000000"
                }

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#DDDDDD"
                    radius: 5
                    border.color: "#707070"
                }

                MouseArea
                {
                    id : editServiceServiceNameTextFieldMA
                    anchors.fill: parent
                    onClicked:
                    {
                        editServiceServiceNameTextField.focus = true
                        editInputPanel.visible = true
                    }
                }
            }

            MouseArea
            {
                id : editServiceServiceNameTextMA
                anchors.fill: parent
                onClicked:
                {
                    editServiceServiceNameTextField.focus = false
                    editInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: editServiceServiceTypeRect
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: editServiceServiceNameRect.right
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: editServiceCountPopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: editServiceServiceTypeText
                text: qmlTextServiceType
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            BransonComboBox
            {
                id: editServiceServiceCountTypeComboBox
                z: 1
                anchors.top: editServiceServiceTypeText.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                minWidth: parent.width * 0.90
                minHeight: Math.round(25 * Style.scaleHint)
                model: qmlServiceCountTypeOptions
                onPressedChanged:
               {
                   editServiceServiceNameTextField.focus = false
                   editInputPanel.visible = false
               }

                onCurrentIndexChanged:
                {
                    /*Make sure every time user selects counter based method, default time shall get upadted*/
                    if(editServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
                    {
                        editDayComboBox.currentIndex = editDayComboBox.indexOfValue(1)
                        editMonthComboBox.currentIndex = editMonthComboBox.indexOfValue(1)
                        editYearComboBox.currentIndex = editYearComboBox.indexOfValue(1970)
                        editHoursComboBox.currentIndex = editHoursComboBox.indexOfValue(00)
                        editMinutesComboBox.currentIndex = editMinutesComboBox.indexOfValue(00)
                        editSecondsComboBox.currentIndex = editSecondsComboBox.indexOfValue(00)
                    }

                    /*Make sure every time user selects time based method, current time shall get upadted*/
                    else
                    {
                        editDayComboBox.currentIndex = editDayComboBox.indexOfValue(currentDate)
                        editMonthComboBox.currentIndex = editMonthComboBox.indexOfValue(currentMonth + 1)
                        editYearComboBox.currentIndex = editYearComboBox.indexOfValue(currentYear)
                        editHoursComboBox.currentIndex = editHoursComboBox.indexOfValue(currentHours)
                        editMinutesComboBox.currentIndex = editMinutesComboBox.indexOfValue(currentMinutes)
                        editSecondsComboBox.currentIndex = editSecondsComboBox.indexOfValue(currentYears)
                    }
                }
            }

            MouseArea
            {
                id : editServiceServiceCountTypeMA
                anchors.fill: parent
                onClicked:
                {
                    editServiceServiceNameTextField.focus = false
                    editInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: editServiceCountReminderRect
            visible: (editServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: editServiceServiceNameRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: editServiceCountReminderText
                text: qmlTextCounterReminder
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id: editServiceCountReminderTextField
                z: 1
                text: ServiceCountListModel.CounterReminder
                width: parent.width * 0.90
                height: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: editServiceCountReminderText.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Normal
                placeholderText: qmlTextCounterReminder

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#FFFFFF"
                    radius: 5
                    border.color: "#707070"
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        mainWindow.showPrimaryNumpad(qmlTextEditServiceCount, "NA", 0, 0, 10000, editServiceCountReminderTextField.text)
                    }
                }
            }

            MouseArea
            {
                id : editServiceServiceCountReminderMA
                anchors.fill: parent
                onClicked:
                {
                    editServiceServiceNameTextField.focus = false
                    editInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: editServiceDateRect
            visible: (editServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.dateTimeBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: editServiceServiceNameRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: editServiceDateText
                text: qmlTextDate
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: editMonthComboBox
                z: 1
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: editServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: editMonthComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editMonthDelegateText
                    text: model.month
                    width: editMonthComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 1; i <= 12; i++)
                    {
                        editMonthComboBoxModel.append({"month": + i});
                    }
                }
            }

            ComboBox
            {
                id: editDayComboBox
                z: 1
                anchors.left: editMonthComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: editServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: editDayComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editDayDelegateText
                    text: model.day
                    width: editDayComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 1; i <= 31; i++)
                    {
                        editDayComboBoxModel.append({"day": + i});
                    }
                }
            }

            ComboBox
            {
                id: editYearComboBox
                z: 1
                anchors.left: editDayComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: editServiceDateText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(75 * Style.scaleHint)
                model: ListModel
                {
                    id: editYearComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editYearDelegateText
                    text: model.year
                    width: editYearComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 2000; i <= 2075; i++)
                    {
                        editYearComboBoxModel.append({"year": + i});
                    }
                }
            }

            MouseArea
            {
                id : editServiceServiceDateMA
                anchors.fill: parent
                onClicked:
                {
                    editServiceServiceNameTextField.focus = false
                    editInputPanel.visible = false
                }
            }
        }

        Rectangle
        {
            id: editServiceTimeRect
            visible: (editServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.dateTimeBasedMethod)
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: editServiceCountReminderRect.right
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: editServiceServiceTypeRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: editServiceTimeText
                text: qmlTextTime
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: editHoursComboBox
                z: 1
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: editServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: editHoursComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editHoursDelegateText
                    text: model.hours
                    width: editHoursComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 23; i++)
                    {
                        editHoursComboBoxModel.append({"hours": + i});
                    }

                    editHoursComboBox.currentIndex = editHoursComboBox.indexOfValue(22)
                }
            }

            ComboBox
            {
                id: editMinutesComboBox
                z: 1
                anchors.left: editHoursComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: editServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: editMinutesComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editMinutesDelegateText
                    text: model.minutes
                    width: editMinutesComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 59; i++)
                    {
                        editMinutesComboBoxModel.append({"minutes": + i});
                    }

                    editMinutesComboBox.currentIndex = editMinutesComboBox.indexOfValue(31)
                }
            }

            ComboBox
            {
                id: editSecondsComboBox
                z: 1
                anchors.left: editMinutesComboBox.right
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: editServiceTimeText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: ListModel
                {
                    id: editSecondsComboBoxModel
                }

                delegate: ItemDelegate
                {
                    id: editSecondsDelegateText
                    text: model.seconds
                    width: editSecondsComboBox.width
                }

                Component.onCompleted:
                {
                    for (var i = 0; i <= 59; i++)
                    {
                        editSecondsComboBoxModel.append({"seconds": + i});
                    }

                    editSecondsComboBox.currentIndex = editSecondsComboBox.indexOfValue(21)
                }
            }

            MouseArea
            {
                id : editServiceServiceTimeMA
                anchors.fill: parent
                onClicked:
                {
                    editServiceServiceNameTextField.focus = false
                    editInputPanel.visible = false
                }
            }
        }

        BransonPrimaryButton
        {
            id: editServiceSaveBtn
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            text: qmlTextSave
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name

            onClicked:
            {
                ServiceCountListModel.serviceName(editServiceServiceNameTextField.text)
                ServiceCountListModel.serviceType(editServiceServiceCountTypeComboBox.currentIndex)
                ServiceCountListModel.serviceCountReminder(editServiceCountReminderTextField.text)
                ServiceCountListModel.month(editMonthComboBox.currentValue)
                ServiceCountListModel.day(editDayComboBox.currentValue)
                ServiceCountListModel.year(editYearComboBox.currentValue)
                ServiceCountListModel.hours(editHoursComboBox.currentValue)
                ServiceCountListModel.minutes(editMinutesComboBox.currentValue)
                ServiceCountListModel.seconds(editSecondsComboBox.currentValue)

                /*Counter based method*/
                if(editServiceServiceCountTypeComboBox.currentIndex === serviceTypeEnum.counterBasedMethod)
                {
                    if((editServiceServiceNameTextField.text === "") || (editServiceCountReminderTextField.text === ""))
                    {
                        serviceReminderOperationStatusPopup.visible = true
                        serviceReminderOperationStatusPopupAlertMsg.text = qmlTextInvalidData
                    }

                    else
                    {
                        ServiceCountListModel.onEditSavePressed()

                        editServiceCountPopup.visible = false
                    }
                }

                /*Date & Time based method*/
                else
                {
                    const day = editDayComboBox.currentValue;
                    const month = editMonthComboBox.currentValue;
                    const year = editYearComboBox.currentValue;

                    if (! isValidDate(year, month, day))
                    {
                        serviceReminderOperationStatusPopup.visible = true
                        serviceReminderOperationStatusPopupAlertMsg.text = qmlTextInvalidData
                    }

                    else
                    {
                        ServiceCountListModel.onEditSavePressed()

                        editServiceCountPopup.visible = false
                    }
                }
            }
        }
    }

    /*Service reminder operation status popup*/
    Rectangle
    {
        id: serviceReminderOperationStatusPopup
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.50
        height: Math.round(200 * Style.scaleHint)

        Rectangle
        {
            id: serviceReminderOperationStatusPopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: serviceReminderOperationStatusPopupHeaderName
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
                id: serviceReminderOperationStatusPopupImageCross
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
                    id: serviceReminderOperationStatusPopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        serviceReminderOperationStatusPopup.visible = false
                    }
                }
            }
        }

        Text
        {
            id: serviceReminderOperationStatusPopupAlertMsg
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style3 * Style.scaleHint)
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
                serviceReminderOperationStatusPopup.visible = false
            }
        }
    }

    /*To provide response update time for getAddReminderResponse API*/
    Timer
    {
        id: responseValidationTimer
        running: false
        repeat: false
        onTriggered:
        {
            if(ServiceCountListModel.getAddReminderResponse() === addReminderErrorCodeEnum.limitCrossed)
            {
                serviceReminderOperationStatusPopup.visible = true
                serviceReminderOperationStatusPopupAlertMsg.text = qmlTextLimitCrossed
                addServiceCountPopup.visible = false
            }

            else if(ServiceCountListModel.getAddReminderResponse() === addReminderErrorCodeEnum.alreadyExist)
            {
                serviceReminderOperationStatusPopup.visible = true
                serviceReminderOperationStatusPopupAlertMsg.text = qmlTextAlreadyExist
                addServiceCountPopup.visible = false
            }

            else if((ServiceCountListModel.getAddReminderResponse() === addReminderErrorCodeEnum.fail) ||
                    (ServiceCountListModel.getAddReminderResponse() === addReminderErrorCodeEnum.errorUnknown))
            {
                serviceReminderOperationStatusPopup.visible = true
                serviceReminderOperationStatusPopupAlertMsg.text = qmlTextFail
                addServiceCountPopup.visible = false
            }

            else
            {
                addServiceCountPopup.visible = false
            }

            responseValidationTimer.running = false
        }
    }

    /*When unauthorised access is attempted*/

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect2
        visible: noAccessAlertPopup.visible
        anchors.left: parent.Left
        anchors.top: parent.Top
        height: mainWindow.height
        width: parent.width
        color: Style.headerBackgroundColor
        opacity: 0.25

        MouseArea
        {
            id: opacityEffectRectMa2
            anchors.fill: parent
            onClicked:
            {
                /*Avoid false click*/
            }
        }
    }

    /*Service reminder operation status popup*/
    Rectangle
    {
        id: noAccessAlertPopup
        visible: (! mainWindow.bransonTabEnable)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.50
        height: Math.round(200 * Style.scaleHint)

        Rectangle
        {
            id: noAccessAlertPopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: noAccessAlertPopupHeaderName
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
                id: noAccessAlertPopupImageCross
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
                    id: noAccessAlertPopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        noAccessAlertPopup.visible = false
                    }
                }
            }
        }

        Text
        {
            id: noAccessAlertPopupAlertMsg
            text: qmlTextAccessError + "\n" + qmlTextAccessError2
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style3 * Style.scaleHint)
            }
        }

        BransonPrimaryButton
        {
            id: okBtn2
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
                noAccessAlertPopup.visible = false
            }
        }
    }
}

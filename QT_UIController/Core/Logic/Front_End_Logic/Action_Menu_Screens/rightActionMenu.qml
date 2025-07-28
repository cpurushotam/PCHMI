/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the right action menu handling operation.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 28/11/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item
{
    readonly property int arcWidth: Math.round((732-359) * Style.scaleHint)
    readonly property int arcRadius: Math.round(732 / 2 * Style.scaleHint)
    readonly property int centerX: Math.round(arcWidth - arcRadius)
    readonly property int centerY: Math.round(height / 2)
    readonly property int imageSize: Math.round(30 * Style.scaleHint)
    readonly property int menuSepratorHeight: (Style.scaleHint === 1.0)? 1 : 2
    property alias rightActionAnimation: rightActionAnimation

    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    property string qmltextActionCenter:            "USER SETTING"
    property string qmltextActuatorSetup:  "Actuator Setup"
    property string qmltextDiagnostics:    "Diagnostics"
    property string qmltextImportExport:   "Import/ Export"
    property string qmltextGenerateReport:   "Generate Report"
    property string qmltextLanguage:                "English"
    property string qmltextLogout:         "Logout"
    property string qmltextExit:           "Exit"
    property string qmltextMachine:                 "Machine: "
    property string qmltextChange:         "  Change"
    property string qmltextPassword:       "Password"
    property string qmltextLogoutOkMsg:             "Yes"
    property string qmltextLogoutCancelMsg:         "No"
    property string qmltextLogoutLabel:             "CONFIRMATION"
    property string qmltextLogoutConfirmMsg:        "Are you sure want to logout?"

    property string qmltextUnit
    property int activeWindow

    property string qmltextMetric:         "Metric"
    property string qmltextImperial:       "Imperial"

    property string qmltextUserName:                "ADMIN"
    property string qmltextAuthLevel:               "(Executive)"
    property string qmlTextDate                    : "Date :"
    property string qmlTextDateFormat              : "Date Format :"
    property string qmlTextTime                    : "Time :"
    property string qmlTextTimeFormat              : "Time Format :"
    property string qmlTextOK                      : "OK"
    property string qmlTextAlert                   : "Alert !"
    property string qmlTextHeader                  : "Date & Time Settings !"
    property string qmlTextErrorUnknown            : "Unknown Error !"
    property string qmlTextInvalidData             : "Entered Data Is Not Valid !"

    property string qmlTextLoggedinAs                : "Logged in as "
    property var qmlTextDateFormatComboxModel: ["DD:MM:YYYY", "MM:DD:YYYY", "YYYY:DD:MM"]
    property var qmlTextTimeFormatComboxModel: ["AM/PM", "24 Hr"]
    property var qmlTextMeridiemFormatComboxModel: ["AM", "PM"]


    property var qmlTextArray: [qmltextActionCenter, qmltextActuatorSetup, qmltextDiagnostics, qmltextImportExport,qmltextGenerateReport,qmltextMetric,qmltextChange,qmltextLogout, qmltextMachine, qmltextLogoutOkMsg,
                                qmltextLogoutCancelMsg, qmltextLogoutLabel, qmltextLogoutConfirmMsg, qmltextMetric, qmltextImperial, qmltextUserName, qmltextAuthLevel, qmlTextDate, qmlTextDateFormat,
                                qmlTextTime, qmlTextTimeFormat, qmlTextOK, qmlTextAlert, qmlTextHeader, qmlTextErrorUnknown, qmlTextInvalidData, qmlTextLoggedinAs, qmltextPassword]

    property var menuName: ""
    property var menuIndex: 0
    /*Here backend value shall get read*/
    property int currentDate    : new Date().getDate()
    property int currentMonth   : new Date().getMonth()
    property int currentYear    : new Date().getFullYear()
    property int currentHours   : new Date().getHours()
    property int currentMinutes : new Date().getMinutes()
    property int currentYears   : new Date().getSeconds()

    signal dateTimeSettingsChanged()
    id: rightActionCenterItem

    function updateLanguage()
    {
        qmltextLanguage = LanguageModel.getLanguageName(LanguageConfig.CurrentLanguage)
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RIGHTMENU, qmlTextArray)

        qmltextActionCenter = qmlTextArray[textEnum.actionCenterIdx]
        qmltextActuatorSetup = qmlTextArray[textEnum.actuatorSetupIdx]
        qmltextDiagnostics = qmlTextArray[textEnum.diagnosticsIdx]
        qmltextImportExport = qmlTextArray[textEnum.importExportIdx]
        qmltextGenerateReport = qmlTextArray[textEnum.generateReportIdx]
        qmltextLogout = qmlTextArray[textEnum.logoutIdx]
        qmltextMachine = qmlTextArray[textEnum.machineIdx]
        qmltextChange = qmlTextArray[textEnum.changeIdx]
        qmltextLogoutOkMsg      = qmlTextArray[textEnum.qmltextLogoutOkMsgIdx]
        qmltextLogoutCancelMsg  = qmlTextArray[textEnum.qmltextLogoutCancelMsgIdx]
        qmltextLogoutLabel      = qmlTextArray[textEnum.qmltextLogoutLabelIdx]
        qmltextLogoutConfirmMsg = qmlTextArray[textEnum.qmltextLogoutConfirmMsgIdx]
        qmltextMetric           = qmlTextArray[textEnum.qmltextMetricIdx]
        qmltextImperial         = qmlTextArray[textEnum.qmltextImperialIdx]
        qmltextUserName         = qmlTextArray[textEnum.qmltextUserNameIdx]
        qmltextAuthLevel        = qmlTextArray[textEnum.qmltextAuthLevelIdx]
        qmlTextDate             = qmlTextArray[textEnum.qmlTextDateIdx]
        qmlTextDateFormat       = qmlTextArray[textEnum.qmlTextDateFormatIdx]
        qmlTextTime             = qmlTextArray[textEnum.qmlTextTimeIdx]
        qmlTextTimeFormat       = qmlTextArray[textEnum.qmlTextTimeFormatIdx]
        qmlTextOK               = qmlTextArray[textEnum.qmlTextOKIdx]
        qmlTextAlert            = qmlTextArray[textEnum.qmlTextAlertIdx]
        qmlTextHeader           = qmlTextArray[textEnum.qmlTextHeaderIdx]
        qmlTextErrorUnknown     = qmlTextArray[textEnum.qmlTextErrorUnknownIdx]
        qmlTextInvalidData      = qmlTextArray[textEnum.qmlTextInvalidDataIdx]
        qmlTextLoggedinAs       = qmlTextArray[textEnum.qmlTextLoggedinAsIdx]
        qmltextPassword         = qmlTextArray[textEnum.qmltextPasswordIdx]
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
        id: rightActionPopupMsg
        z: 6

        onOKButtonClicked:
        {
            mainWindow.bransonTabEnable = false
            rightActionPopupMsg.visible = false
            mainWindow.logoutProcess()
        }

        onCancelButtonClicked:
        {
            rightActionPopupMsg.visible = false
        }
    }

    BransonPopup
    {
        id: rightActionPopupMsg2
        z: 6

        onOKButtonClicked:
        {
            rightActionPopupMsg2.visible = false
        }

        onCancelButtonClicked:
        {
            rightActionPopupMsg2.visible = false
        }
    }

    Connections
    {
        target: mainWindow
        function onCloseRightActionMenu()
        {
            rightActionAnimationReturn.restart()
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

    Component.onCompleted:
    {
        updateLanguage()
        rightActionAnimationReturn.restart()
        rightMenuModelData.resetModel()
        systemModelData.resetModel()
    }

    QtObject
    {
        id: textEnum
        readonly property int actionCenterIdx:  0
        readonly property int actuatorSetupIdx: 1
        readonly property int diagnosticsIdx:   2
        readonly property int importExportIdx:  3
        readonly property int generateReportIdx:4
        readonly property int metricIdx:        5
        readonly property int changeIdx:        6
        readonly property int logoutIdx:        7
        readonly property int machineIdx:       8
        readonly property int qmltextLogoutOkMsgIdx      : 9
        readonly property int qmltextLogoutCancelMsgIdx  : 10
        readonly property int qmltextLogoutLabelIdx      : 11
        readonly property int qmltextLogoutConfirmMsgIdx : 12
        readonly property int qmltextMetricIdx           : 13
        readonly property int qmltextImperialIdx         : 14
        readonly property int qmltextUserNameIdx         : 15
        readonly property int qmltextAuthLevelIdx        : 16
        readonly property int qmlTextDateIdx             : 17
        readonly property int qmlTextDateFormatIdx       : 18
        readonly property int qmlTextTimeIdx             : 19
        readonly property int qmlTextTimeFormatIdx       : 20
        readonly property int qmlTextOKIdx               : 21
        readonly property int qmlTextAlertIdx            : 22
        readonly property int qmlTextHeaderIdx           : 23
        readonly property int qmlTextErrorUnknownIdx     : 24
        readonly property int qmlTextInvalidDataIdx      : 25
        readonly property int qmlTextLoggedinAsIdx       : 26
        readonly property int qmltextPasswordIdx         : 27
    }

    QtObject
    {
        id: dateFormatEnum
        readonly property int format_DD_MM_YYYY  : 0
        readonly property int format_MM_DD_YYYY  : 1
        readonly property int format_YYYY_DD_MM : 2
        readonly property int format_Unknown    : 3
    }

    QtObject
    {
        id: timeFormatEnum
        readonly property int format_12HR    : 0
        readonly property int format_24HR    : 1
        readonly property int format_Unknown : 2
    }

    QtObject
    {
        id: meridiemEnum
        readonly property int isAM : 0
        readonly property int isPM : 1
    }

    Connections
    {
        target:  mainWindow
        function onLoadRightActionModel()
        {
            rightMenuModelData.resetModel()
            systemModelData.resetModel()

        }
    }

    Connections
    {
        target:  mainWindow
        function onCurrentUnit(unit)
        {
            var currUnit =unit
            if(currUnit == 0)
            {
              qmltextUnit = qmltextMetric
            }

            else
            {
                qmltextUnit = qmltextImperial
            }

            systemModelData.resetModel()
        }
    }

    ListModel
    {
        id: rightMenuModelData
        function resetModel()
        {
            rightMenuModelData.clear()
            rightMenuModelData.append({"MenuName":   qmltextActuatorSetup,
                                          "MenuIcon":     "qrc:/Images/actuatorSetup.svg",
                                          "MenuAction":   "ActuatorSetup.qml",
                                          "MenuColor":    "#ffffff",
                                          "MenuIndex":    UIScreenEnum.ACTUATORSETUP,
                                          "MenuVisible":  true,
                                          "MenuSeparator": true,
                                          "UserLevelAccess": UserPrivilegeObj.IsActuatorSetupAllowed || mainWindow.isAuthorityCheckEnable,
                                      })
            rightMenuModelData.append({"MenuName":   qmltextDiagnostics,
                                          "MenuIcon":     "qrc:/Images/diagnostics.svg",
                                          "MenuAction":   "DiagnosticsView.qml",
                                          "MenuColor":    "#ffffff",
                                          "MenuIndex":    UIScreenEnum.DIAGNOSTICS,
                                          "MenuVisible":  true,
                                          "MenuSeparator": true,
                                          "UserLevelAccess": UserPrivilegeObj.IsDignosticsAllowed || mainWindow.isAuthorityCheckEnable,
                                      })
            rightMenuModelData.append({"MenuName":   qmltextImportExport,
                                          "MenuIcon":     "qrc:/Images/importExport.svg",
                                          "MenuAction":   "ImportExportView.qml",
                                          "MenuColor":    "#ffffff",
                                          "MenuIndex":    UIScreenEnum.IMPORTEXPORT,
                                          "MenuVisible":  true,
                                          "MenuSeparator": true,
                                          "UserLevelAccess": true,
                                      })
            rightMenuModelData.append({"MenuName":   qmltextGenerateReport,
                                          "MenuIcon":     "qrc:/Images/Generate_Report_Icon.svg",
                                          "MenuAction":   "GenerateReport.qml",
                                          "MenuColor":    "#ffffff",
                                          "MenuIndex":    UIScreenEnum.GENERATEREPORT,
                                          "MenuVisible":  true,
                                          "MenuSeparator": true,
                                          "UserLevelAccess": true,
                                      })
        }
    }



    ListModel
    {
        id: systemModelData
        function resetModel()
        {
            systemModelData.clear()
            systemModelData.append({"MenuName":     qmltextLanguage,
                                       "MenuIcon":      "qrc:/Images/Language2.svg",
                                       "MenuAction":    "LanguageView.qml",
                                       "MenuColor":     "#ffffff",
                                       "MenuIndex":     UIScreenEnum.LANGUAGE,
                                       "MenuVisible":   true
                                   })
            systemModelData.append({"MenuName":     qmltextUnit,
                                       "MenuIcon":      "qrc:/Images/Metric_icon.svg",
                                       "MenuColor":     "#ffffff",
                                       "MenuIndex":     UIScreenEnum.SYSTEM_CONFIG_GENERAL,
                                       "MenuVisible":   true,
                                   })
            systemModelData.append({"MenuName":     qmltextChange + "\n" + qmltextPassword,
                                       "MenuIcon":      "qrc:/Images/Change_password_icon.svg",
                                       "MenuAction":    "SystemConfigurationUserListResetPassword.qml",
                                       "MenuColor":     "#ffffff",
                                       "MenuIndex":     UIScreenEnum.SYSTEM_CONFIG_USER_LIST_RESET_PASSWORD,
                                       "MenuVisible":   mainWindow.isAuthorityCheckEnable ? false :true
                                   })
            systemModelData.append({"MenuName":     qmltextLogout,
                                       "MenuIcon":      "qrc:/Images/Logout Icon.svg",
                                       "MenuAction":    "Logout.qml",
                                       "MenuColor":     "#ffffff",
                                       "MenuIndex":     UIScreenEnum.LOGOUT,
                                       "MenuVisible":   mainWindow.isAuthorityCheckEnable ? false :true
                                   })
        }
    }


    NumberAnimation on x
    {
        id: rightActionAnimationReturn
        from: 0
        to: width
        duration: 250
    }

    NumberAnimation on x
    {
        id: rightActionAnimation
        from: width
        to: 0
        duration: 250
    }

    Connections
    {
        target: mainWindow
        function onLoginUserNameAndUserLevelUpdated()
        {
            mainWindow.userNameTxt = LoginObj.getLoginUserName()
            mainWindow.userLevelTxt = LoginObj.getLoginUserLevel()
            loggedInText.text = qmlTextLoggedinAs + mainWindow.userNameTxt + " " + "("+mainWindow.userLevelTxt+ ")"
        }
    }
    Rectangle
    {
        id: rootRectangle
        color: "transparent"
        anchors.top: parent.top
        anchors.right: parent.right
        width:  arcWidth
        height: parent.height
        z: 3
        //For mobile screen and small screen Canvas element is not required
        Canvas
        {
            id: canvash
            anchors.right: parent.right
            anchors.top: parent.top
            width: rootRectangle.width
            height: rootRectangle.height
            opacity: 0.8
            onPaint:
            {
                var ctx = getContext("2d")
                ctx.fillStyle = Style.titleBackgroundColor

                ctx.beginPath()
                ctx.arc(width, centerY, arcRadius, 1.5 * Math.PI, 0.5 * Math.PI, true)
                ctx.fill()
            }
            MouseArea
            {
                anchors.fill: parent
            }
        }

        Item
        {
            id: menuDetails
            width: parent.width
            height: parent.height
            anchors.right: parent.Right
            anchors.top: parent.top
            Item
            {
                id: actionCenterButton
                anchors.right: parent.right
                anchors.rightMargin: Math.round(12 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(14 * Style.scaleHint)
                height: imageSize
                width: Math.round(180 * Style.scaleHint)
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "transparent"
                    color: "transparent"
                    Row
                    {
                        id: menuLayout
                        spacing: Math.round(10 * Style.scaleHint)
                        layoutDirection: Qt.RightToLeft
                        Image
                        {
                            id: imageMenu
                            width: imageSize
                            height: imageSize
                            source: "qrc:/Images/menu_close_arrow_rightMenu.svg"
                            fillMode: Image.PreserveAspectFit
                            sourceSize.width: imageSize
                            sourceSize.height: imageSize
                            smooth: true
                            mirror: true
                        }

                        Text
                        {
                            text: qmltextActionCenter
                            height: imageSize
                            font.family: Style.regular.name
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            color: Style.whiteFontColor
                        }
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered:
                        {
                            cursorShape = Qt.PointingHandCursor
                        }

                        onClicked:
                        {
                            updateDateTimePopup.visible = false
                            rightActionAnimationReturn.restart()
                            mainWindow.hideMainWindowOpacity()
                        }
                    }
                }
            }

            Rectangle
            {
                id:loggedInUserDetailsRect
                border.color: "transparent"
                color: "transparent"
                height: imageSize
                width: Math.round(220 * Style.scaleHint)
                anchors.top: actionCenterButton.bottom
                anchors.topMargin: Math.round(9 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(165 * Style.scaleHint)
                clip:true
                Image
                {
                    id:loggedInImage
                    source: "qrc:/Images/user_icon_white.svg"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text
                {
                    id:loggedInText
                    text: qmlTextLoggedinAs + mainWindow.userNameTxt + " " + "("+mainWindow.userLevelTxt+ ")"
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(10 * Style.scaleHint)
                    font.weight : Font.Medium
                    color: Style.whiteFontColor
                    anchors.left: loggedInImage.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.Wrap
                }
            }

            Item
            {
                id: menuParentList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(113 * Style.scaleHint)
                anchors.top: actionCenterButton.bottom
                anchors.topMargin: Math.round(58 * Style.scaleHint)
                anchors.right: parent.right
                height: Math.round(285 * Style.scaleHint)
                Column
                {
                    id: menuOptionLayout
                    anchors.fill: parent
                    spacing: Math.round(22 * Style.scaleHint)
                    Repeater
                    {
                        model: rightMenuModelData
                        delegate: Item
                        {
                            id: menuOptionDelegate
                            height: imageSize + Math.round(22 * Style.scaleHint)
                            width: parent.width
                            Rectangle
                            {
                                id: menuImageTextLayout
                                height: imageSize
                                width: parent.width
                                color: "transparent"
                                border.color: "transparent"
                                Row
                                {
                                    spacing: Math.round(21 * Style.scaleHint)
                                    Image
                                    {
                                        id: menuOptionImage
                                        width: imageSize
                                        height: imageSize
                                        source: model.MenuIcon
                                        fillMode: Image.PreserveAspectFit
                                        sourceSize.width: imageSize
                                        sourceSize.height: imageSize
                                        smooth: true
                                    }
                                    Text
                                    {
                                        height: imageSize
                                        color: model.MenuColor
                                        font.family: Style.regular.name
                                        text: model.MenuName
                                        anchors.verticalCenter: menuOptionImage.verticalCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                                    }
                                }

                                MouseArea
                                {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:
                                    {
                                        cursorShape = Qt.PointingHandCursor
                                    }

                                    onClicked:
                                    {
                                        if(model.UserLevelAccess)
                                        {
                                            rightActionAnimationReturn.restart()
                                            mainWindow.hideMainWindowOpacity()
                                            menuIndex = model.MenuIndex
                                            menuName = model.MenuName
                                            mainWindow.menuParentOptionSelect( menuIndex)
                                        }

                                        else
                                        {
                                            mainWindow.showBransonPopupForAccessDenied()
                                        }

                                    }
                                }
                            }

                            Rectangle
                            {
                                id: lineSeparator
                                width: Math.round(221 * Style.scaleHint)
                                height: menuSepratorHeight
                                anchors.left: menuImageTextLayout.left
                                anchors.top: menuImageTextLayout.bottom
                                anchors.topMargin: Math.round(20 * Style.scaleHint)
                                color: Style.whiteFontColor
                                visible: model.MenuSeparator
                            }
                        }
                    }
                }
            }


            Item
            {
                id: menuSystemList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(113 * Style.scaleHint)
                anchors.top: menuParentList.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Row
                {
                    id: menuSystemLayout
                    anchors.fill: parent
                    spacing: Math.round(39 * Style.scaleHint)
                    Repeater
                    {
                        model: systemModelData
                        delegate: Item
                        {
                            id: systemOptionDelegate
                            height: parent.height
                            width: imageSize
                            Rectangle
                            {
                                id: systemImageTextLayout
                                width: imageSize
                                height: imageSize + imageSize
                                color: "transparent"
                                visible: model.MenuVisible

                                Image
                                {
                                    id: systemOptionImage
                                    width: imageSize
                                    height: imageSize
                                    source: model.MenuIcon
                                    fillMode: Image.PreserveAspectFit
                                    sourceSize.width: imageSize
                                    sourceSize.height: imageSize
                                    smooth: true
                                    visible: model.MenuVisible
                                }

                                Text
                                {
                                    id: systemOptionText
                                    anchors.top: systemOptionImage.bottom
                                    height: imageSize
                                    color: model.MenuColor
                                    font.family: Style.regular.name
                                    text: model.MenuName
                                    anchors.horizontalCenter: systemOptionImage.horizontalCenter
                                    verticalAlignment: Text.AlignVCenter
                                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                                    visible: model.MenuVisible
                                }
                            }

                            MouseArea
                            {
                                id: mouseAreaSystemOption
                                anchors.fill: systemImageTextLayout
                                hoverEnabled: true
                                visible: model.MenuVisible
                                onEntered:
                                {
                                    cursorShape = Qt.PointingHandCursor
                                }

                                onClicked:
                                {
                                    if(model.MenuIndex !== UIScreenEnum.LOGOUT)
                                    {
                                        rightActionAnimationReturn.restart()
                                    }
                                    if(model.MenuIndex === UIScreenEnum.EXIT)
                                    {
                                        Qt.quit()
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.LANGUAGE)
                                    {
                                        mainWindow.hideMainWindowOpacity()
                                        mainWindow.showLanguageView()
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.SYSTEM_CONFIG_USER_LIST_RESET_PASSWORD && !(mainWindow.isAuthorityCheckEnable))
                                    {
                                        if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                        {
                                        mainWindow.isUserModifingPassword = false
                                        mainWindow.showResetPasswordPopup()
                                        }
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.LOGOUT && !(mainWindow.isAuthorityCheckEnable))
                                    {
                                        rightActionPopupMsg.isMultiButtonPopup = true
                                        rightActionPopupMsg.qmltextOk = qmltextLogoutOkMsg
                                        rightActionPopupMsg.qmltextCancel = qmltextLogoutCancelMsg
                                        rightActionPopupMsg.qmltextLabel = qmltextLogoutLabel
                                        rightActionPopupMsg.visible = true;
                                        rightActionPopupMsg.qmltextWarningDialog = qmltextLogoutConfirmMsg
                                    }
                                    else if(model.MenuIndex === UIScreenEnum.SYSTEM_CONFIG_GENERAL)
                                    {
                                        if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                        {
                                            if(UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable)
                                            {
                                                mainWindow.showBransonUnitChangePopup()
                                                mainWindow.hideMainWindowOpacity()
                                            }
                                            else
                                            {
                                                mainWindow.showBransonPopupForAccessDenied()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle
            {
                id: machineInfo
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(6 * Style.scaleHint)
                height: Math.round(imageSize / 2)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(122 * Style.scaleHint)
                color: "transparent"
                border.color: "transparent"

                Image
                {
                    id: editDateTimeImage
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(20 * Style.scaleHint)
                    anchors.top: parent.top
                    width: Math.round(imageSize / 2)
                    height: Math.round(imageSize / 2)
                    source: "qrc:/Images/systemTimer.svg"
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: editDateTimeImage.width
                    sourceSize.height: editDateTimeImage.height
                    smooth: true

                    MouseArea
                    {
                        id: editDateTimeImageMA
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked:
                        {
                            /*On clicked all the current value shall get reflected
                              inside popup entries */

                            /*Date*/
                            addDayComboBox.currentIndex = addDayComboBox.indexOfValue(DateTimeSettings.Day)
                            addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(DateTimeSettings.Month)
                            addYearComboBox.currentIndex = addYearComboBox.indexOfValue(DateTimeSettings.Year)
                            dateFormatComboBox.currentIndex = DateTimeSettings.getDateFormat()

                            /*Time*/

                            if(timeFormatComboBox.currentIndex === timeFormatEnum.format_12HR)
                            {
                                addHoursComboBoxModel.clear()

                                for (var i = 01; i <= 12; i++)
                                {
                                    /*If value is single digit then append 0 followed by that value*/
                                    addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                                }
                            }

                            else
                            {
                                addHoursComboBoxModel.clear()

                                for (i = 00; i <= 23; i++)
                                {
                                    /*If value is single digit then append 0 followed by that value*/
                                    addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                                }
                            }

                            addHoursComboBox.currentIndex = (DateTimeSettings.Hours > 12) ? addHoursComboBox.indexOfValue(DateTimeSettings.Hours - 12) :
                                                                                            (DateTimeSettings.Hours === 0 ? addHoursComboBox.indexOfValue(12)
                                                                                                    : addHoursComboBox.indexOfValue(DateTimeSettings.Hours))
                            addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(DateTimeSettings.Minutes)
                            addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(DateTimeSettings.Seconds)
                            timeFormatComboBox.currentIndex = DateTimeSettings.getTimeFormat()
                            meridiemComboBox.currentIndex = DateTimeSettings.Merediem

                            updateDateTimePopup.visible = true
                        }
                    }
                }

                Connections
                {
                    target: DateTimeSettings

                    function onDateTimeSettingsChanged()
                    {
                        /*If value is single digit then append 0 followed by that value*/
                        machineDate.text = (DateTimeSettings.getDateFormat() === dateFormatEnum.format_DD_MM_YYYY) ? ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) + ":" + DateTimeSettings.Year :
                                                                                                                                                        (DateTimeSettings.getDateFormat() === dateFormatEnum.format_MM_DD_YYYY) ? ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) + ":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + DateTimeSettings.Year :
                                                                                                                                                         DateTimeSettings.Year + ":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month))
                        machineTimeMerediem.visible = (DateTimeSettings.getTimeFormat() === timeFormatEnum.format_12HR) ? true : false
                    }
                }

                Text
                {
                    id: machineDate
                    /*If value is single digit then append 0 followed by that value*/
                    text: (DateTimeSettings.getDateFormat() === dateFormatEnum.format_DD_MM_YYYY) ? ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) + ":" + DateTimeSettings.Year :
                                                                    (DateTimeSettings.getDateFormat() === 1) ? ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) + ":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + DateTimeSettings.Year :
                                                                     DateTimeSettings.Year + ":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month))
                    anchors.left: editDateTimeImage.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                Text
                {
                    id: machineTime
                    text:
                    {
                        if(DateTimeSettings.getTimeFormat() === timeFormatEnum.format_12HR)
                        {
                            if(DateTimeSettings.Hours >= 12)
                            {
                                if(DateTimeSettings.Hours !== 12)
                                {
                                    return ("0"+(DateTimeSettings.Hours - 12)+":")
                                }

                                else
                                {
                                    return 12+":"
                                }
                            }

                            else if(DateTimeSettings.Hours === 0)
                            {
                                return 12+":"
                            }

                            else
                            {
                                /*If value is single digit then append 0 followed by that value*/
                                return (DateTimeSettings.Hours < 10) ? ("0"+DateTimeSettings.Hours+":") : (DateTimeSettings.Hours+":")
                            }
                        }

                        else
                        {
                            /*If value is single digit then append 0 followed by that value*/
                            return (DateTimeSettings.Hours < 10) ? ("0"+DateTimeSettings.Hours+":") : (DateTimeSettings.Hours+":")
                        }
                    }

                    anchors.left: machineDate.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                Text
                {
                    id: machineMinutes
                    /*If value is single digit then append 0 followed by that value*/
                    text: (DateTimeSettings.Minutes < 10) ? ("0"+DateTimeSettings.Minutes) + ":" : (DateTimeSettings.Minutes) + ":"
                    anchors.left: machineTime.right
                    anchors.leftMargin: Math.round(0 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                Text
                {
                    id: machineSeconds
                    /*If value is single digit then append 0 followed by that value*/
                    text: (DateTimeSettings.Seconds < 10) ? ("0"+DateTimeSettings.Seconds) : (DateTimeSettings.Seconds)
                    anchors.left: machineMinutes.right
                    anchors.leftMargin: Math.round(0 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                Text
                {
                    id: machineTimeMerediem
                    visible: (DateTimeSettings.getTimeFormat() === timeFormatEnum.format_12HR)
                    text: (DateTimeSettings.Merediem === meridiemEnum.isAM) ? "AM" : "PM"
                    anchors.left: machineSeconds.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.top: parent.top
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
            }
        }
    }

    Rectangle
    {
        id: rightMenuOutsideArea
        width: parent.width/5 + parent.width - arcWidth
        height: parent.height
        opacity: 0
        anchors.left: parent.left
        anchors.top: parent.top
        color: "transparent"
        visible: true
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                rightActionAnimationReturn.restart()
                mainWindow.hideMainWindowOpacity()
                updateDateTimePopup.visible = false
            }
        }
    }

    /*Date & Time update settings*/

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        z: 5
        visible: ((rightActionPopupMsg.visible) || (rightActionPopupMsg2.visible))
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
        id: updateDateTimePopup
        z: 4
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.80
        height: Math.round(350 * Style.scaleHint)

        Rectangle
        {
            id: updateDateTimePopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: updateDateTimePopupHeaderName
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmlTextHeader
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
                id: updateDateTimePopupImageCross
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
                    id: updateDateTimePopupImageCrossMa
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        updateDateTimePopup.visible = false
                    }
                }
            }
        }

        Text
        {
            id: dateText
            text: qmlTextDate
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: updateDateTimePopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            color: "#000000"
        }

        Rectangle
        {
            id: addDateRect
            visible: true
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: dateText.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addDateText
                text: "DD :"
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addDayComboBox
                z: 1
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
                anchors.top: addDateText.bottom
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
                        /*If seconds value is single digit then append 0 followed by that value*/
                        addDayComboBoxModel.append({"day": i < 10 ? "0" + i : "" + i});
                    }

                    addDayComboBox.currentIndex = addDayComboBox.indexOfValue(DateTimeSettings.Day)
                }
            }

            Text
            {
                id: addMonthText
                text: "MM :"
                anchors.left: addDayComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
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
                anchors.left: addDayComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: addDateText.bottom
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
                        /*If seconds value is single digit then append 0 followed by that value*/
                        addMonthComboBoxModel.append({"month": i < 10 ? "0" + i : "" + i});
                    }

                    addMonthComboBox.currentIndex = addMonthComboBox.indexOfValue(DateTimeSettings.Month)
                }
            }

            Text
            {
                id: addYearText
                text: "YYYY :"
                anchors.left: addMonthComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addYearComboBox
                z: 1
                anchors.left: addMonthComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: addDateText.bottom
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
                    for (var i = 2025; i <= 2055; i++)
                    {
                        addYearComboBoxModel.append({"year": + i});
                    }

                    addYearComboBox.currentIndex = addYearComboBox.indexOfValue(DateTimeSettings.Year)
                }
            }

            MouseArea
            {
                id : addDateMA
                anchors.fill: parent
                onClicked:
                {
                }
            }
        }

        Text
        {
            id: dateFormatText
            text: qmlTextDateFormat
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            anchors.left: addDateRect.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: updateDateTimePopupHeader.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            color: "#000000"
        }

        Rectangle
        {
            id: dateFormatTextRect
            visible: true
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: addDateRect.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: dateText.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)


            ComboBox
            {
                id: dateFormatComboBox
                z: 1
                model: qmlTextDateFormatComboxModel
                currentIndex: DateTimeSettings.getDateFormat()
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(125 * Style.scaleHint)
            }
        }

        Text
        {
            id: timeText
            text: qmlTextTime
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: addDateRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            color: "#000000"
        }

        Rectangle
        {
            id: addTimeRect
            visible: true
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: parent.left
            anchors.leftMargin: Math.round(40 * Style.scaleHint)
            anchors.top: timeText.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            Text
            {
                id: addHourText
                text: "HH : "
                anchors.left: parent.left
                anchors.leftMargin: Math.round(25 * Style.scaleHint)
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
                anchors.top: addHourText.bottom
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
                    if(timeFormatComboBox.currentIndex === timeFormatEnum.format_12HR)
                    {
                        addHoursComboBoxModel.clear()

                        for (var i = 01; i <= 12; i++)
                        {
                            /*If seconds value is single digit then append 0 followed by that value*/
                            addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                        }
                    }

                    else
                    {
                        addHoursComboBoxModel.clear()

                        for (i = 00; i <= 23; i++)
                        {
                            /*If seconds value is single digit then append 0 followed by that value*/
                            addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                        }
                    }

                    addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(DateTimeSettings.Hours)
                }
            }

            Text
            {
                id: addMinutesText
                text: "MM :"
                anchors.left: addHoursComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addMinutesComboBox
                z: 1
                anchors.left: addHoursComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: addMinutesText.bottom
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
                    for (var i = 00; i <= 59; i++)
                    {
                        /*If seconds value is single digit then append 0 followed by that value*/
                        addMinutesComboBoxModel.append({"minutes": i < 10 ? "0" + i : "" + i});
                    }

                    addMinutesComboBox.currentIndex = addMinutesComboBox.indexOfValue(DateTimeSettings.Minutes)
                }
            }

            Text
            {
                id: addSecondsText
                text: "SS :"
                anchors.left: addMinutesComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top:parent.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            ComboBox
            {
                id: addSecondsComboBox
                z: 1
                anchors.left: addMinutesComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: addSecondsText.bottom
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
                    for (var i = 00; i <= 59; i++)
                    {
                        /*If seconds value is single digit then append 0 followed by that value*/
                        addSecondsComboBoxModel.append({"seconds": i < 10 ? "0" + i : "" + i});
                    }

                    addSecondsComboBox.currentIndex = addSecondsComboBox.indexOfValue(DateTimeSettings.Seconds)
                }
            }

            ComboBox
            {
                id: meridiemComboBox
                visible: (timeFormatComboBox.currentIndex === timeFormatEnum.format_12HR)
                z: 1
                anchors.left: addSecondsComboBox.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.top: addSecondsText.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                width: Math.round(50 * Style.scaleHint)
                model: qmlTextMeridiemFormatComboxModel
            }

            MouseArea
            {
                id : addTimeMA
                anchors.fill: parent
                onClicked:
                {

                }
            }
        }

        Text
        {
            id: timeFormatText
            text: qmlTextTimeFormat
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            anchors.left: addTimeRect.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: dateFormatTextRect.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            color: "#000000"
        }

        Rectangle
        {
            id: timeFormatTextRect
            visible: true
            width: parent.width * 0.40
            height: parent.height * 0.20
            color:Style.contentBackgroundColor
            anchors.left: addTimeRect.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: timeFormatText.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)


            ComboBox
            {
                id: timeFormatComboBox
                z: 1
                model: qmlTextTimeFormatComboxModel
                currentIndex: DateTimeSettings.getTimeFormat()
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(100 * Style.scaleHint)

                onCurrentIndexChanged:
                {
                    if(timeFormatComboBox.currentIndex === timeFormatEnum.format_12HR)
                    {
                        addHoursComboBoxModel.clear()

                        /*For 12HR format*/
                        for (var i = 01; i <= 12; i++)
                        {
                            /*If seconds value is single digit then append 0 followed by that value*/
                            addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                        }

                        addHoursComboBox.currentIndex = (DateTimeSettings.Hours > 12) ? addHoursComboBox.indexOfValue(DateTimeSettings.Hours - 12) :
                                                                                        (DateTimeSettings.Hours === 0 ? addHoursComboBox.indexOfValue(12)
                                                                                                : addHoursComboBox.indexOfValue(DateTimeSettings.Hours))
                    }

                    else
                    {
                        addHoursComboBoxModel.clear()

                        /*For 24HR format*/
                        for (i = 00; i <= 23; i++)
                        {
                            /*If seconds value is single digit then append 0 followed by that value*/
                            addHoursComboBoxModel.append({"hours": i < 10 ? "0" + i : "" + i});
                        }

                        addHoursComboBox.currentIndex = addHoursComboBox.indexOfValue(DateTimeSettings.Hours)
                    }

                }
            }
        }

        BransonPrimaryButton
        {
            id: oKBtn
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
                const day = addDayComboBox.currentValue;
                const month = addMonthComboBox.currentValue;
                const year = addYearComboBox.currentValue;

                if (! isValidDate(year, month, day))
                {
                    rightActionPopupMsg2.visible = true
                    rightActionPopupMsg2.qmltextWarningDialog = qmlTextInvalidData
                }

                else
                {
                    /*Update the date & time settings*/
                    DateTimeSettings.Day = addDayComboBox.currentValue
                    DateTimeSettings.Month = addMonthComboBox.currentValue
                    DateTimeSettings.Year = addYearComboBox.currentValue
                    DateTimeSettings.setDateFormat(dateFormatComboBox.currentIndex)

                    if(timeFormatComboBox.currentIndex === timeFormatEnum.format_12HR)
                    {
                        if(meridiemComboBox.currentIndex === meridiemEnum.isAM)
                        {
                            /*If hours value is 12 in AM then at backend it shall send 0, as we have converted it in 12 hour
                              format to display on screen*/
                            var val = parseInt(addHoursComboBox.currentValue)
                            DateTimeSettings.Hours = (val <= 11) ? val : 0
                        }

                        else
                        {
                            /*If hours value is less than 12 in PM then it shall convert in 0 to 23 hour format before sending it to backend*/
                            val = parseInt(addHoursComboBox.currentValue)
                            DateTimeSettings.Hours = (val <= 11) ? (val + 12) : val
                        }
                    }

                    else
                    {
                        DateTimeSettings.Hours = addHoursComboBox.currentValue
                    }

                    DateTimeSettings.Minutes = addMinutesComboBox.currentValue
                    DateTimeSettings.Seconds = addSecondsComboBox.currentValue
                    DateTimeSettings.setTimeFormat(timeFormatComboBox.currentIndex)
                    DateTimeSettings.Merediem = meridiemComboBox.currentIndex
                    DateTimeSettings.onSettingsUpdated()
                    /*Date format change*/
                    switch(dateFormatComboBox.currentIndex)
                    {
                    case dateFormatEnum.format_DD_MM_YYYY :
                        /*If value is single digit then append 0 followed by that value*/
                        machineDate.text = ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) +":" + DateTimeSettings.Year
                        break

                    case dateFormatEnum.format_MM_DD_YYYY :
                        /*If value is single digit then append 0 followed by that value*/
                        machineDate.text = ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month)) +":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + DateTimeSettings.Year
                        break

                    default :
                        /*If value is single digit then append 0 followed by that value*/
                        machineDate.text = DateTimeSettings.Year + ":" + ((DateTimeSettings.Day < 10) ? ("0"+DateTimeSettings.Day) : (DateTimeSettings.Day)) + ":" + ((DateTimeSettings.Month < 10) ? ("0"+DateTimeSettings.Month) : (DateTimeSettings.Month))
                        break
                    }

                    /*Time format change*/
                    switch(timeFormatComboBox.currentIndex)
                    {
                    case timeFormatEnum.format_12HR :
                        machineTimeMerediem.visible = true
                        break

                    default :
                        machineTimeMerediem.visible = false
                        break
                    }

                    updateDateTimePopup.visible = false
                }
            }
        }
    }
}

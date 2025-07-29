/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file popup the change password screen.

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
import QtQuick.Layouts 1.15
import "./../Diagnostics_Screens"
import "./../Common_Logic"
import "./../System_screens"

Popup
{
    id:resetPasswordPopup
    parent: Overlay.overlay
    closePolicy: Popup.NoAutoClose

    property string qmlTextResetPassword          : "RESET PASSWORD"
    property string qmlTextEnterDetails           : "Please enter below details to reset password"
    property string qmlTextCurrentPassword        : "Current Password"
    property string qmlTextNewPassword            : "New Password"
    property string qmlTextConfirmNewPassword     : "Confirm New Password"
    property string qmlTextCancel                 : "CANCEL"
    property string qmlTextSave                   : "SAVE"
    property string qmltextPasswordMismatchMsg    : "New Password and Confirm Password should be same"
    property string qmltextPassWordEmptyMsg       : "New Password or Confirm New Password is empty"
    property string qmltextCurrPassWordEmptyMsg   : "Current Password is empty"
    property string qmltextValidPasswordMsg       : "Password must be at least 8 characters in length, including 1 uppercase letter, 1 lowercase letter, 1 numeric character, 1 special character"
    property string qmltextPasswordResetMsg       : "Password reset successfully"
    property string qmltextPasswordUpdateMsg      : "Password updated successfully"
    property string qmltextConfLabelMsg           : "CONFIRMATION"
    property string qmltextWarningLabelMsg        : "Warning !"
    property string qmltextSubDialogMsg           : "Please login again"

    property string qmlTextConfirmation           : "Confirmation"
    property string qmlTextWarning                : "Warning !"

    property int currentActiveWindow              : -1
    property string currentUserId                 : ""
    property bool   clearedOnce                   : false

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property bool isErrorOccurred                 : false

    property var qmlTextArray: [qmlTextResetPassword, qmlTextEnterDetails, qmlTextCurrentPassword, qmlTextNewPassword,
        qmlTextConfirmNewPassword, qmlTextCancel, qmlTextSave, qmltextPasswordResetMsg,
        qmltextPasswordMismatchMsg, qmltextPassWordEmptyMsg, qmltextValidPasswordMsg, qmltextPasswordResetMsg,
        qmltextPasswordUpdateMsg, qmltextConfLabelMsg, qmltextWarningLabelMsg,qmltextSubDialogMsg ]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USER_LIST_CHANGE_PASSWORD, qmlTextArray)
        qmlTextResetPassword       = qmlTextArray[textEnum.textResetPasswordIdx]
        qmlTextEnterDetails        = qmlTextArray[textEnum.textEnterDetailsIdx]
        qmlTextCurrentPassword     = qmlTextArray[textEnum.textCurrentPasswordIdx]
        qmlTextNewPassword         = qmlTextArray[textEnum.textNewPasswordIdx]
        qmlTextConfirmNewPassword  = qmlTextArray[textEnum.textConfirmNewPasswordIdx]
        qmlTextCancel              = qmlTextArray[textEnum.textCancelIdx]
        qmlTextSave                = qmlTextArray[textEnum.textSaveIdx]
        qmltextPasswordResetMsg    = qmlTextArray[textEnum.textPasswordResetMsgIdx]
        qmltextPasswordMismatchMsg = qmlTextArray[textEnum.textPasswordMismatchMsgIdx]
        qmltextPassWordEmptyMsg    = qmlTextArray[textEnum.textPassWordEmptyMsgIdx]
        qmltextValidPasswordMsg    = qmlTextArray[textEnum.textValidPasswordMsgIdx]
        qmltextPasswordResetMsg    = qmlTextArray[textEnum.textSuccessfulPassResetMsgIdx]
        qmltextPasswordUpdateMsg   = qmlTextArray[textEnum.textPasswordUpdateMsgIdx]
        qmltextConfLabelMsg        = qmlTextArray[textEnum.textConfLabelMsgIdx]
        qmltextWarningLabelMsg     = qmlTextArray[textEnum.textWarningLabelMsgIdx]
        qmltextSubDialogMsg        = qmlTextArray[textEnum.textSubDialogMsgIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textResetPasswordIdx          : 0
        readonly property int textEnterDetailsIdx           : 1
        readonly property int textCurrentPasswordIdx        : 2
        readonly property int textNewPasswordIdx            : 3
        readonly property int textConfirmNewPasswordIdx     : 4
        readonly property int textCancelIdx                 : 5
        readonly property int textSaveIdx                   : 6
        readonly property int textPasswordResetMsgIdx       : 7
        readonly property int textPasswordMismatchMsgIdx    : 8
        readonly property int textPassWordEmptyMsgIdx       : 9
        readonly property int textValidPasswordMsgIdx       : 10
        readonly property int textSuccessfulPassResetMsgIdx : 11
        readonly property int textPasswordUpdateMsgIdx      : 12
        readonly property int textConfLabelMsgIdx           : 13
        readonly property int textWarningLabelMsgIdx        : 14
        readonly property int textSubDialogMsgIdx           : 15
    }

    QtObject
    {
        id: modifyErrorEnum
        readonly property int param_MODIFY_USER_ERROR_UNKNOWN               : 0
        readonly property int param_MODIFY_USER_SUCCESS                     : 1
        readonly property int param_MODIFY_USER_FAIL                        : 2
        readonly property int param_MODIFY_USER_NOT_EXIST_IN_DB             : 3
        readonly property int param_NEED_AT_LEAST_ONE_EXECUTIVE_USER        : 4
        readonly property int param_MODIFY_USER_DONT_HAVE_ACCESS            : 5
        readonly property int param_MODIFY_PASSWORD_SUCCESS                 : 6
        readonly property int param_MODIFY_PASSWORD_FAIL                    : 7
        readonly property int param_WRONG_EXISTING_PASSWORD                 : 8
        readonly property int param_MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED   : 9
        readonly property int param_DELETE_USER_SUCCESS                     : 10
        readonly property int param_DELETE_USER_FAIL                        : 11
        readonly property int param_CAN_NOT_DELETE_LOGGED_IN_USER           : 12
        readonly property int param_NEED_AT_LEAST_ONE_USER_IN_SYSTEM        : 13
    }

    Connections
    {
        target: mainWindow
        function onChangePasswordSignal(buserId)
        {
            currentUserId = buserId
            newPasswordTextField.text = ""
            confNewPasswordTextField.text = ""
        }
    }

    function passwordCheck(password, confPassword)
    {
        var passwordValidate = false
        if(password === "" || confPassword === "")
        {
            resetPasswordPopupMsg.visible = true
            resetPasswordPopupMsg.qmltextWarningDialog = qmltextPassWordEmptyMsg
            passwordValidate = false
            return passwordValidate

        }
        else
        {
            if(password !== confPassword)
            {
                resetPasswordPopupMsg.visible = true
                resetPasswordPopupMsg.qmltextWarningDialog = qmltextPasswordMismatchMsg
                passwordValidate = false
                return passwordValidate

            }
            else
            {
                var regExp = /(?=^.{8,20}$)(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;:;'?/&gt;.&lt;,])(?!.*\s).*$/;
                if(regExp.test(password))
                {
                    passwordValidate = true
                    return passwordValidate

                }
                else
                {
                    resetPasswordPopupMsg.visible = true
                    resetPasswordPopupMsg.qmltextWarningDialog = qmltextValidPasswordMsg
                    passwordValidate = false
                    return passwordValidate

                }
            }
        }
        return passwordValidate
    }

    function onSave()
    {
        var currPassword
        var isPasswordValidated = false;
        var errorflag = false

        var newPassword = ""
        var confPassword = ""

        resetPasswordPopupMsg.qmltextLabel = qmltextWarningLabelMsg
        resetPasswordPopupMsg.qmltextSubDialog = ""

        newPassword = newPasswordTextField.text
        confPassword = confNewPasswordTextField.text
        isPasswordValidated = passwordCheck(newPassword, confPassword)
        isErrorOccurred = (! isPasswordValidated)

        if(isPasswordValidated && (!errorflag))
        {
            UserListDetailsListModel.onChangePasswordRequest(currentUserId,newPasswordTextField.text)
            UserListDetailsListModel.IsChangeScreenNavigated = true
            UserListDetailsListModel.setCurrentActiveScreenUserChange(UIScreenEnum.SYSTEM_CONFIG_USER_LIST_CHANGE_PASSWORD)
        }
    }

    Connections
    {
        target: UserListDetailsListModel
        function onChangeUserpassResponseChanged()
        {
            resetPasswordPopup.close()

            switch(UserListDetailsListModel.changePassResponseFromASC())
            {

            case modifyErrorEnum.param_MODIFY_USER_SUCCESS:

                mainWindow.showBransonPopup(UserListDetailsListModel.changePasswordWarningMessages(),qmlTextConfirmation)
                resetPasswordPopup.close()
                break;

            case modifyErrorEnum.param_MODIFY_USER_FAIL:
            case modifyErrorEnum.param_MODIFY_USER_NOT_EXIST_IN_DB:
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_EXECUTIVE_USER:
            case modifyErrorEnum.param_MODIFY_USER_DONT_HAVE_ACCESS:
            case modifyErrorEnum.param_DELETE_USER_FAIL:
            case modifyErrorEnum.param_CAN_NOT_DELETE_LOGGED_IN_USER:
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_USER_IN_SYSTEM:
            case modifyErrorEnum.param_MODIFY_PASSWORD_FAIL:
            case modifyErrorEnum.param_WRONG_EXISTING_PASSWORD:
            case modifyErrorEnum.param_MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED:

                resetPasswordPopup.close()
                mainWindow.showBransonPopup(UserListDetailsListModel.changePasswordWarningMessages(),qmlTextWarning)
                break;

            case modifyErrorEnum.param_MODIFY_PASSWORD_SUCCESS:
            case modifyErrorEnum.param_DELETE_USER_SUCCESS:

                resetPasswordPopup.close()
                mainWindow.showBransonPopup(UserListDetailsListModel.changePasswordWarningMessages(),qmlTextConfirmation)
                resetPasswordPopup.close()
                break;

            default:

                resetPasswordPopup.close()
                mainWindow.showBransonPopup(UserListDetailsListModel.changePasswordWarningMessages(),qmlTextWarning)

                break;
            }
        }
    }

    Component.onCompleted:
    {
        updateLanguage();
        inputPanel.visible = false
        resetPasswordPopupMsg.visible = false
    }

    BransonPopup
    {
        id:resetPasswordPopupMsg
        onOKButtonClicked:
        {
            resetPasswordPopupMsg.visible = false
            mainWindow.hideMainWindowOpacity()

            if(mainWindow.isUserModifingPassword === false)
            {
                if(resetPasswordPopupMsg.qmltextWarningDialog === qmltextPasswordResetMsg)
                {
                    resetPasswordPopup.close()
                    currentPasswordTextField.text = ""
                    newPasswordTextField.text = ""
                    confNewPasswordTextField.text = ""
                }
            }
        }
    }

    InputPanel
    {
        id: inputPanel
        z: 1
        height: mainWindow.showHeight * 0.80
        width: parent.width
        visible: Qt.inputMethod.visible
        anchors.bottom: parent.bottom
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    background: Rectangle {
        id:rectMain
        color:"transparent"
        MouseArea{
            anchors.fill: parent
            onClicked:{
                inputPanel.visible = false
            }
        }
    }

    Rectangle
    {
        id:resetPasswordPopupRect
        anchors.fill: parent
        width: parent.width
        height:parent.height
        color:"#FFFFFF"
        Rectangle
        {
            id:resetPasswordTextRect
            width: parent.width
            height: parent.height * 0.08
            color: Style.headerBackgroundColor
            Text
            {
                id:resetPasswordText
                text: qmlTextResetPassword
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                color: "#ffffff"
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.06
                anchors.verticalCenter: parent.verticalCenter
                font.weight : Font.DemiBold
            }
            Image {
                id: popupClose
                source: "qrc:/Images/crossMark.svg"
                sourceSize.width:  Math.round(18* Style.scaleHint)
                sourceSize.height: Math.round(18* Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin:Math.round(16 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        resetPasswordPopup.close()
                        currentPasswordTextField.text = ""
                        newPasswordTextField.text = ""
                        confNewPasswordTextField.text = ""
                        mainWindow.opacityFlag = false
                    }
                }
            }
        }
        Text
        {
            id:enterDetailsText
            text: qmlTextEnterDetails
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.75
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#000000"
            anchors.top:resetPasswordTextRect.bottom
            anchors.topMargin:Math.round(9 * Style.scaleHint)
            font.weight : Font.Medium * 0.90
        }

        Rectangle
        {
            id:currentPasswordRect
            width: parent.width * 0.82
            height: parent.height * 0.16
            color:Style.contentBackgroundColor
            anchors.top:resetPasswordTextRect.bottom
            anchors.topMargin: parent.height * 0.10
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.09
            visible: mainWindow.isUserModifingPassword ? false : true
            Text
            {
                id: currentPasswordText
                text: qmlTextCurrentPassword
                anchors.left:parent.left
                anchors.leftMargin: parent.width * 0.05
                anchors.top:parent.top
                anchors.topMargin:parent.height * 0.06
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id:currentPasswordTextField
                width: parent.width* 0.90
                height: parent.height * 0.45
                anchors.top: currentPasswordText.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Password

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#ffffff"
                    radius: 5
                    border.color: "#707070"
                }

                onActiveFocusChanged:
                {
                    /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                    if(activeFocus)
                    {
                        clearedOnce = true
                        currentPasswordTextField.selectAll()
                    }

                    else
                    {
                        clearedOnce = false
                    }
                }

                /*Clear data once only*/
                Keys.onPressed:
                {
                    if (clearedOnce)
                    {
                        currentPasswordTextField.clear()
                        clearedOnce = false
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        currentPasswordTextField.focus = true
                        currentPasswordTextField.color = "#000000"
                        Qt.inputMethod.hide()
                        inputPanel.visible = true
                    }
                }
            }
        }

        Rectangle
        {
            id:newPasswordRect
            width: parent.width * 0.82
            height: parent.height * 0.16
            color:Style.contentBackgroundColor
            anchors.top:mainWindow.isUserModifingPassword ? resetPasswordTextRect.bottom : currentPasswordRect.bottom
            anchors.topMargin: mainWindow.isUserModifingPassword ? parent.height * 0.13 : parent.height * 0.06
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.09
            Text
            {
                id: newPasswordText
                text: qmlTextNewPassword
                anchors.left:parent.left
                anchors.leftMargin: parent.width * 0.05
                anchors.top:parent.top
                anchors.topMargin:parent.height * 0.06
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id:newPasswordTextField
                width: parent.width* 0.90
                height: parent.height * 0.45
                anchors.top: newPasswordText.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Password

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#ffffff"
                    radius: 5
                    border.color: "#707070"
                }

                onActiveFocusChanged:
                {
                    /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                    if(activeFocus)
                    {
                        clearedOnce = true
                        newPasswordTextField.selectAll()
                    }

                    else
                    {
                        clearedOnce = false
                    }
                }

                /*Clear data once only*/
                Keys.onPressed:
                {
                    if (clearedOnce)
                    {
                        newPasswordTextField.clear()
                        clearedOnce = false
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        newPasswordTextField.focus = true
                        newPasswordTextField.color = "#000000"
                        Qt.inputMethod.hide()
                        inputPanel.visible = true
                    }
                }
            }
        }

        Rectangle
        {
            id:confNewPasswordRect
            width: parent.width * 0.82
            height: parent.height * 0.16
            color:Style.contentBackgroundColor
            anchors.top:newPasswordRect.bottom
            anchors.topMargin: parent.height * 0.06
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.09
            Text
            {
                id: confNewPasswordText
                text: qmlTextConfirmNewPassword
                anchors.left:parent.left
                anchors.leftMargin: parent.width * 0.05
                anchors.top:parent.top
                anchors.topMargin:parent.height * 0.06
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                color: "#000000"
            }

            TextField
            {
                id:confNewPasswordTextField
                width: parent.width* 0.90
                height: parent.height * 0.47
                anchors.top: confNewPasswordText.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                anchors.left:parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                mouseSelectionMode: TextInput.SelectCharacters
                font.pixelSize: Math.round(10 * Style.scaleHint)
                font.family: Style.regular.name
                echoMode: TextInput.Password

                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 1
                    color: "#ffffff"
                    radius: 5
                    border.color: "#707070"
                }

                onActiveFocusChanged:
                {
                    /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                    if(activeFocus)
                    {
                        clearedOnce = true
                        confNewPasswordTextField.selectAll()
                    }

                    else
                    {
                        clearedOnce = false
                    }
                }

                /*Clear data once only*/
                Keys.onPressed:
                {
                    if (clearedOnce)
                    {
                        confNewPasswordTextField.clear()
                        clearedOnce = false
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        confNewPasswordTextField.focus = true
                        confNewPasswordTextField.color = "#000000"
                        Qt.inputMethod.hide()
                        inputPanel.visible = true
                    }
                }
            }
        }

        Row
        {
            id:buttonRow
            anchors.top: confNewPasswordRect.bottom
            topPadding: mainWindow.isUserModifingPassword ? parent.height * 0.12 : parent.height * 0.06
            leftPadding: parent.width * 0.15
            spacing: parent.width * 0.03

            BransonPrimaryButton
            {
                id: cancelButton
                width: parent.width * 0.3888
                height: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: qmlTextCancel
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.cancelButtonTextColor
                onClicked:
                {
                    resetPasswordPopup.close()
                    mainWindow.hideMainWindowOpacity()
                    currentPasswordTextField.text = ""
                    newPasswordTextField.text = ""
                    confNewPasswordTextField.text = ""
                    mainWindow.opacityFlag = false
                }
            }

            BransonPrimaryButton
            {
                id: saveButton
                width: parent.width * 0.3888
                height: Math.round(30 * Style.scaleHint)
                anchors.right: confNewPasswordRect.right
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: qmlTextSave
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked:
                {
                    onSave()

                    if(! isErrorOccurred)
                    {
                        mainWindow.opacityFlag = false
                    }
                }
            }
        }
    }
}

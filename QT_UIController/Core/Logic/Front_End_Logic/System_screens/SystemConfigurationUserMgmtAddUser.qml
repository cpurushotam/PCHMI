/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 System Configuration User Management Add User Pop up Screen

 **********************************************************************************************************/
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import Com.Branson.UIScreenEnum 1.0
import QtQuick.VirtualKeyboard.Settings 2.15
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"

Popup
{
    id: addUserPopup
    parent: Overlay.overlay
    closePolicy: Popup.NoAutoClose

    property string qmltextAddUser:                     "Add User"
    property string qmltextUserId:                      "User ID"
    property string qmltextPassword:                    "Password"
    property string qmltextAuthLevel:                   "Authority Level"
    property string qmltextConfPassword:                "Confirm Password"
    property string qmltextStatus:                      "Status"
    property string qmltextEnable:                      "Enable"
    property string qmltextDisable:                     "Disable"
    property string qmltextEnterUsername:               "Enter Username"
    property string qmltextEnterPassWord:               "Enter Password"
    property string qmltextEnterConfPass:               "Enter Confirm Password"
    property string qmltextSelect:                      "Select"
    property string qmltextCancel:                      "Cancel"
    property string qmltextSave:                        "Save"
    property string qmltextIsLockedUser:                "Is Locked User"
    property string qmltexLocked:                       "Locked"
    property string qmltextUnLocked:                    "Unlocked"
    property string qmltextModifyUser:                  "Modify User"
    property string qmltextUpdate:                      "Update"
    property string qmltextPasswordMismatchMsg:         "Password and Confirm Password can not be same"
    property string qmltextPassWordEmptyMsg:            "Password or Confirm Password is empty"
    property string qmltextValidPasswordMsg:            "Password must be at least 8 characters in length, including 1 uppercase letter, 1 lowercase letter, 1 numeric character, 1 special character"
    property string qmltextEmptyUserIdMsg:              "User Name is Empty"
    property string qmltextAssignAuthorityLevelMsg:     "Please Add Authority Level"

    property string qmlTextConfirmation           : "Confirmation"
    property string qmlTextWarning                : "Warning !"

    property string userId:                     ""
    property var authorityLevel
    property string password:                   ""
    property string confrmPass:                 ""
    property bool status
    property bool islocked
    property bool clearedOnce                     : false
    property bool isErrorOccurred                 : false

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property var qmlTextArray: [qmltextAddUser,qmltextUserId,qmltextPassword,qmltextAuthLevel,qmltextConfPassword,qmltextStatus,
                               qmltextEnable,qmltextDisable,qmltextEnterUsername,qmltextEnterPassWord,qmltextEnterConfPass,qmltextSelect,
                               qmltextCancel,qmltextSave,qmltextIsLockedUser,qmltexLocked,qmltextUnLocked, qmltextModifyUser,qmltextUpdate,
                               qmltextPasswordMismatchMsg,qmltextPassWordEmptyMsg, qmltextValidPasswordMsg, qmltextEmptyUserIdMsg, qmltextAssignAuthorityLevelMsg, qmlTextConfirmation, qmlTextWarning]


    function statusEnableDisbale()
    {

        if(status === 0)
        {

            return true
        }

        else
        {
            return false
        }
    }

    Connections
    {
        target: mainWindow

        function onCurrentSelectedUserDetail( buserId,  bauthorityLevel,   bstatus,  bislocked)
        {
            authorityLevelTextField.model = mainWindow.getUserLevelModel()
            enterUserNameTextField.text = ""
            passwordTextField.text = ""
            confirmPasswordField.text = ""

            if(SystemConfiguration.UserAccessLevelType === SystemTypeDef.STANDARD_USER_ACCESS_LEVEL)
            {
                if(bauthorityLevel === "Executive")
                {
                     authorityLevelTextField.currentIndex = 0
                }

                else if(bauthorityLevel === "Operator")
                {
                    authorityLevelTextField.currentIndex = 1
                }

                else if(bauthorityLevel === "")
                {
                    authorityLevelTextField.currentIndex = -1
                }
            }

            else if(SystemConfiguration.UserAccessLevelType === SystemTypeDef.ADVANCED_USER_ACCESS_LEVEL)
            {
                if(bauthorityLevel === "Executive")
                {
                     authorityLevelTextField.currentIndex = 3
                }
                else if(bauthorityLevel === "Operator")
                {
                     authorityLevelTextField.currentIndex = 0
                }
                else if(bauthorityLevel === "Technician")
                {
                     authorityLevelTextField.currentIndex = 1
                }
                else if(bauthorityLevel === "Supervisor")
                {
                     authorityLevelTextField.currentIndex = 2
                }
                else if(bauthorityLevel === ""){
                    authorityLevelTextField.currentIndex = -1
                }
            }


            if(bstatus !== -1 )
            {
                if(bstatus === 0)
                {
                   enableRadioButton.checked = true
                    disableRadioButton.checked = false
                }

                else
                {
                     enableRadioButton.checked = false
                     disableRadioButton.checked = true
                }
            }

            else
            {
                enableRadioButton.checked = false
                 disableRadioButton.checked = false
            }

            if(bislocked !== -1)
            {
                if(bislocked === 0)
                {
                   unlockedRadioButton.checked = true
                   lockedRadioButton.checked = false
                }

                else
                {
                   unlockedRadioButton.checked = false
                   lockedRadioButton.checked = true
                }
            }

            else
            {
                unlockedRadioButton.checked = false
                lockedRadioButton.checked = false
            }
        }
    }

    QtObject
    {
        id: textEnum
        readonly property int textAddUserIdx:                0
        readonly property int textUserIdx:                   1
        readonly property int textPasswordIdx:               2
        readonly property int textAuthLevelIdx:              3
        readonly property int textStatusIdx:                 4
        readonly property int textEnableIdx:                 5
        readonly property int textDisableIdx:                6
        readonly property int textEnterUsernameIdx:          7
        readonly property int textEnterPassWordIdx:          8
        readonly property int textEnterConfPassIdx:          9
        readonly property int textSelectIdx:                 10
        readonly property int textConfPasswordIdx:           11
        readonly property int textCancelIdx:                 12
        readonly property int textSaveIdx:                   13
        readonly property int textIsLockedUserIdx:           14
        readonly property int texLockedIdx:                  15
        readonly property int textUnLockedIdx:               16
        readonly property int textModifyUserIdx:             17
        readonly property int textUpdateIdx:                 18
        readonly property int textPasswordMismatchMsgIdx:    19
        readonly property int textPassWordEmptyMsgIdx:       20
        readonly property int textValidPasswordMsgIdx:       21
        readonly property int textEmptyUserIdMsgIdx:         22
        readonly property int textAssignAuthorityLevelMsgIdx:23
        readonly property int textConfirmationIdx:           24
        readonly property int textWarningIdx:                25
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT_ADD_USER, qmlTextArray)
        qmltextAddUser = qmlTextArray[textEnum.textUserIdx]
        qmltextPassword = qmlTextArray[textEnum.textPasswordIdx]
        qmltextAuthLevel = qmlTextArray[textEnum.textAuthLevelIdx]
        qmltextConfPassword = qmlTextArray[textEnum.textConfPasswordIdx]
        qmltextStatus = qmlTextArray[textEnum.textStatusIdx]
        qmltextEnable = qmlTextArray[textEnum.textEnableIdx]
        qmltextDisable = qmlTextArray[textEnum.textDisableIdx]
        qmltextEnterUsername = qmlTextArray[textEnum.textEnterUsernameIdx]
        qmltextEnterPassWord = qmlTextArray[textEnum.textEnterPassWordIdx]
        qmltextEnterConfPass = qmlTextArray[textEnum.textEnterConfPassIdx]
        qmltextSelect = qmlTextArray[textEnum.textSelectIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextIsLockedUser = qmlTextArray[textEnum.textIsLockedUserIdx]
        qmltexLocked = qmlTextArray[textEnum.texLockedIdx]
        qmltextUnLocked = qmlTextArray[textEnum.textUnLockedIdx]
        qmltextModifyUser = qmlTextArray[textEnum.textModifyUserIdx]
        qmltextUpdate = qmlTextArray[textEnum.textUpdateIdx]
        qmltextPasswordMismatchMsg = qmlTextArray[textEnum.textPasswordMismatchMsgIdx]
        qmltextPassWordEmptyMsg = qmlTextArray[textEnum.textPassWordEmptyMsgIdx]
        qmltextValidPasswordMsg = qmlTextArray[textEnum.textValidPasswordMsgIdx]
        qmltextEmptyUserIdMsg = qmlTextArray[textEnum.textEmptyUserIdMsgIdx]
        qmltextAssignAuthorityLevelMsg = qmlTextArray[textEnum.textAssignAuthorityLevelMsgIdx]
        qmlTextConfirmation = qmlTextArray[textEnum.textConfirmationIdx]
        qmlTextWarning = qmlTextArray[textEnum.textWarningIdx]
    }


    QtObject
    {
        id: addUsrErrorEnum
        readonly property int param_ADD_USER_ERROR_UNKNOWN               : 0
        readonly property int param_ADD_USER_SUCCESS                     : 1
        readonly property int param_ADD_USER_FAIL                        : 2
        readonly property int param_USER_ALREADY_EXIST                   : 3
        readonly property int param_ADD_USER_LIMIT_CROSSED               : 4
        readonly property int param_EXECUTIVE_USER_NOT_LOGGED_IN         : 5
        readonly property int param_ADD_USER_DOES_NOT_MEET_PASSWORD_POLICY    : 6

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
        readonly property int param_DOES_NOT_MEET_PASSWORD_POLICY           : 14

    }

    function passwordCheck(password, confPassword)
    {
        var flag = true

        if(password === "" || confPassword === "")
        {
            adduserPopupMsg.visible = true
            adduserPopupMsg.qmltextWarningDialog = qmltextPassWordEmptyMsg
            flag = false
        }

        else
        {
            if(password !== confPassword)
            {
                adduserPopupMsg.visible = true
                adduserPopupMsg.qmltextWarningDialog = qmltextPasswordMismatchMsg
                flag = false
            }

            else
            {
                var regExp = /(?=^.{8,20}$)(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;:;'?/&gt;.&lt;,])(?!.*\s).*$/;
                if(!regExp.test(password))
                {
                    adduserPopupMsg.visible = true
                    adduserPopupMsg.qmltextWarningDialog = qmltextValidPasswordMsg
                    flag = false
                }
            }
        }

        return flag
    }

    function assignAuthoritymodelIdx()
    {
        if(authorityLevelTextField.currentText == "Executive")
        {
            return 3
        }
        else if(authorityLevelTextField.currentText == "Operator")
        {
            return 0
        }
        else if(authorityLevelTextField.currentText == "Technician")
        {
            return 1
        }
        else if(authorityLevelTextField.currentText == "Supervisor")
        {
            return 2
        }
        else if(authorityLevelTextField.currentText == "")
        {
            return -1
        }
    }

    function onSave()
    {
        var flag = true
        var userName = enterUserNameTextField.text
        if(userName === "")
        {
            adduserPopupMsg.visible = true
            adduserPopupMsg.qmltextWarningDialog = qmltextEmptyUserIdMsg
            flag = false
        }
        if(flag === true)
        {
            if(assignAuthoritymodelIdx() === -1)
            {
                adduserPopupMsg.visible = true
                adduserPopupMsg.qmltextWarningDialog = qmltextAssignAuthorityLevelMsg
                flag = false
            }
            if(flag === true)
            {
                var password = passwordTextField.text
                var confPassword = confirmPasswordField.text
                flag = passwordCheck(password, confPassword)
                if(flag === true)
                {
                    UserListDetailsListModel.onAddUserRequest(enterUserNameTextField.text, password, assignAuthoritymodelIdx(), status, islocked)
                }
            }
        }

        isErrorOccurred = (! flag)
    }

    Connections
    {

        target:UserListDetailsListModel
        function onAddUserResponseChanged()
        {
            addUserPopup.close()

            switch(UserListDetailsListModel.addUserResponseFromASC())
            {

            case addUsrErrorEnum.param_ADD_USER_SUCCESS:
                enterUserNameTextField.text = ""
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextConfirmation)

                break;
            case addUsrErrorEnum.param_ADD_USER_FAIL:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            case addUsrErrorEnum.param_USER_ALREADY_EXIST:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            case addUsrErrorEnum.param_ADD_USER_LIMIT_CROSSED:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            case addUsrErrorEnum.param_EXECUTIVE_USER_NOT_LOGGED_IN:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            case addUsrErrorEnum.param_ADD_USER_DOES_NOT_MEET_PASSWORD_POLICY:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            default:
                mainWindow.showBransonPopup(UserListDetailsListModel.addUserWarningMessages(),qmlTextWarning)

                break;
            }

        }
    }



    Connections
    {
        target: UserListDetailsListModel
        function onModifyUserResponseChanged()
        {
            addUserPopup.close()

            switch(UserListDetailsListModel.modifyuserResponseFromASC()){

            case modifyErrorEnum.param_MODIFY_USER_SUCCESS:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextConfirmation)

                break;
            case modifyErrorEnum.param_MODIFY_USER_FAIL:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_MODIFY_USER_NOT_EXIST_IN_DB:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_EXECUTIVE_USER:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_MODIFY_USER_DONT_HAVE_ACCESS:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_MODIFY_PASSWORD_SUCCESS:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextConfirmation)

                break;
            case modifyErrorEnum.param_MODIFY_PASSWORD_FAIL:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_WRONG_EXISTING_PASSWORD:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_DELETE_USER_SUCCESS:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextConfirmation)

                break;
            case modifyErrorEnum.param_DELETE_USER_FAIL:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_CAN_NOT_DELETE_LOGGED_IN_USER:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_USER_IN_SYSTEM:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)
                break;

            case modifyErrorEnum.param_DOES_NOT_MEET_PASSWORD_POLICY:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            default:
                mainWindow.showBransonPopup(UserListDetailsListModel.editUserWarningMessages(),qmlTextWarning)

                break;
            }
        }
    }

    Component.onCompleted:
    {
        inputPanelKeyBoard.visible = false    
    }

    InputPanel
    {
        id: inputPanelKeyBoard
        z: 1
        width: parent.width
        height: parent.height*0.68
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible
    }

    BransonPopup
    {
        id:adduserPopupMsg
        onOKButtonClicked:
        {
            adduserPopupMsg.visible = false
            isErrorOccurred = false
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

    background: Rectangle
    {
        id:rectMain
        color:"transparent"
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                inputPanelKeyBoard.visible = false
            }
        }
    }

    Rectangle
    {
        id:addUserPopuprect
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color:"#ffffff"
        radius: 12
        Rectangle
        {
            id: clipper
            width: parent.width
            height: parent.height/12
            color: "transparent"
            clip: true
            Rectangle
            {
                id:addUsertopbluerect
                width:parent.width + radius
                height: parent.height + radius
                radius:addUserPopuprect.radius
                anchors.left: parent.left
                anchors.right: parent.right
                color: Style.headerBackgroundColor
                Text
                {
                    id: addUserHeader
                    text: mainWindow.isUserModifing ? qmltextModifyUser : qmltextAddUser
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    color: "#ffffff"
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(16 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(4 * Style.scaleHint)
                }

                Image
                {
                    id: popupClose
                    source: "qrc:/Images/crossMark.svg"
                    sourceSize.width:  Math.round(15* Style.scaleHint)
                    sourceSize.height: Math.round(15* Style.scaleHint)
                    anchors.right: parent.right
                    anchors.rightMargin:Math.round(16 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(5.5 * Style.scaleHint)
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            addUserPopup.close()
                            enterUserNameTextField.text = ""
                            authorityLevelTextField.currentIndex = -1
                            selectLabel.text = "Select"
                            enableRadioButton.checked = true
                            unlockedRadioButton.checked = true
                            mainWindow.opacityFlag = false
                        }
                    }
                }
            }
       }

        Rectangle
        {
            id:addUserRectRow1
            width: parent.width
            height: Math.round(60 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(15 * Style.scaleHint)
            anchors.top:clipper.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            color:"transparent"
            Rectangle
            {
                id:userIdRect
                width:parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                Text
                {
                    id: userIdText
                    text: qmltextUserId
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                TextField
                {
                    id:enterUserNameTextField
                    width: parent.width* 0.90
                    height: Math.round(23 * Style.scaleHint)
                    anchors.top: userIdText.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    mouseSelectionMode: TextInput.SelectCharacters
                    font.pixelSize: Math.round(10 * Style.scaleHint)
                    font.family: Style.regular.name
                    echoMode: TextInput.Normal

                    Text
                    {
                        id:userNameText
                        text: userId
                        anchors.verticalCenter:  parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        font.pixelSize: Math.round(10 * Style.scaleHint)
                        font.family: Style.regular.name
                        color: "black"
                    }

                    background: Rectangle
                    {
                        anchors.fill: parent
                        border.width: 1
                        color: mainWindow.isUserModifing ? "#dddddd" : "#ffffff"
                        radius: 5
                        border.color: "#707070"
                    }

                    onActiveFocusChanged:
                    {
                        /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                        if(activeFocus)
                        {
                            clearedOnce = true
                            enterUserNameTextField.selectAll()
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
                            enterUserNameTextField.clear()
                            clearedOnce = false
                        }
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            if(mainWindow.isUserModifing == false)
                            {
                                enterUserNameTextField.focus = true
                                enterUserNameTextField.color = "#000000"
                                Qt.inputMethod.hide()
                                inputPanelKeyBoard.visible = true
                            }
                        }
                    }
                }
            }

            Rectangle
            {
                id:authorityLevelRect
                width:parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                anchors.left:userIdRect.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.right: addUserRectRow1.right

                Text
                {
                    id: authorityLevelText
                    text: qmltextAuthLevel
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                BransonComboBox
                {
                    id:authorityLevelTextField
                    width: parent.width* 0.90
                    height: Math.round(23 * Style.scaleHint)
                    anchors.top: authorityLevelText.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    model: mainWindow.getUserLevelModel()
                    currentIndex: -1
                    textFontSize : Math.round(10 * Style.scaleHint)
                    Label
                    {
                        id:selectLabel
                        color: Style.backgroundColor
                        anchors.verticalCenter:  parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        font.pixelSize: authorityLevelTextField.height*0.40
                        textFormat: Style.regular.name
                    }

                    onCurrentIndexChanged:
                    {
                        if(currentIndex >= 0 )
                        {                           
                            selectLabel.text = ""
                            selectLabel.text = model.get(currentIndex)
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:addUserRectRow2
            width: parent.width
            height: Math.round(60 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(15 * Style.scaleHint)
            anchors.top:addUserRectRow1.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            color:"transparent"
            visible: mainWindow.isUserModifing ? false : true
            Rectangle
            {
                id:passwordRect
                width: parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                Text
                {
                    id: passwordText
                    text: qmltextPassword
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                TextField
                {
                    id:passwordTextField
                    width: parent.width* 0.90
                    height: Math.round(23 * Style.scaleHint)
                    anchors.top: passwordText.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    mouseSelectionMode: TextInput.SelectCharacters
                    font.pixelSize: Math.round(10 * Style.scaleHint)
                    font.family: Style.regular.name
                    echoMode: TextInput.Password

                    Text
                    {
                        text: password
                        color: Style.backgroundColor
                        visible: !passwordTextField.text
                        anchors.verticalCenter:  parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        font.pixelSize: Math.round(10 * Style.scaleHint)
                        font.family: Style.regular.name
                    }

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
                            enterUserNameTextField.selectAll()
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
                            passwordTextField.clear()
                            clearedOnce = false
                        }
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            passwordTextField.focus = true
                            passwordTextField.color = "#000000"
                            Qt.inputMethod.hide()
                            inputPanelKeyBoard.visible = true
                        }
                    }
                }
            }

            Rectangle
            {
                id:confirmPasswordRect
                width: parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                anchors.left:passwordRect.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.right: addUserRectRow2.right
                visible: mainWindow.isUserModifing ? false : true

                Text
                {
                    id: confirmPasswordText
                    text: qmltextConfPassword
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                TextField
                {
                    id:confirmPasswordField
                    width: parent.width* 0.90
                    height: Math.round(23 * Style.scaleHint)
                    anchors.top: confirmPasswordText.bottom
                    anchors.topMargin: Math.round(2 * Style.scaleHint)
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    mouseSelectionMode: TextInput.SelectCharacters
                    font.pixelSize: Math.round(10 * Style.scaleHint)
                    font.family: Style.regular.name
                    echoMode: TextInput.Password

                    Text
                    {
                        text: confrmPass
                        color: Style.backgroundColor
                        visible: !confirmPasswordField.text
                        anchors.verticalCenter:  parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        font.pixelSize: Math.round(10 * Style.scaleHint)
                        font.family: Style.regular.name
                    }

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
                            confirmPasswordField.selectAll()
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
                            confirmPasswordField.clear()
                            clearedOnce = false
                        }
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            confirmPasswordField.focus = true
                            confirmPasswordField.color = "#000000"
                            Qt.inputMethod.hide()
                            inputPanelKeyBoard.visible = true
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:addUserRectRow3
            width: parent.width
            height: Math.round(60 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(15 * Style.scaleHint)
            anchors.top: mainWindow.isUserModifing ? addUserRectRow1.bottom : addUserRectRow2.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            color:"transparent"
            Rectangle
            {
                id:statusRect
                width: parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                Text
                {
                    id: statusText
                    text: qmltextStatus
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                RowLayout
                {
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:statusText.bottom
                    anchors.topMargin: Math.round(8 * Style.scaleHint)
                    spacing: Math.round(55 * Style.scaleHint)

                    BransonRadioButton
                    {
                        id:enableRadioButton
                        circleSize:Math.round(18 * Style.scaleHint)
                        labelText: qmltextEnable

                        onCheckedChanged:
                        {
                            if(checked == true)
                            {
                                status = 0
                            }

                            else
                            {
                                status = 1
                            }
                        }
                    }

                    BransonRadioButton
                    {
                        id:disableRadioButton
                        circleSize:Math.round(18 * Style.scaleHint)
                        offColor:Style.blackFontColor
                        labelText:qmltextDisable
                        onCheckedChanged:
                        {
                            if(checked == true)
                            {
                                status = 1
                            }

                            else
                            {
                                status = 0
                            }
                        }
                    }
                }
            }

            Rectangle
            {
                id:userLockRect
                width: parent.width *0.48
                height: parent.height
                color:Style.contentBackgroundColor
                anchors.top:parent.top
                anchors.left:statusRect.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.right: addUserRectRow3.right

                Text
                {
                    id: userLockText
                    text: qmltextIsLockedUser
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:parent.top
                    anchors.topMargin:Math.round(6 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.weight : Font.DemiBold
                    color: "#000000"
                }

                RowLayout
                {
                    anchors.left:parent.left
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    anchors.top:userLockText.bottom
                    anchors.topMargin: Math.round(8 * Style.scaleHint)
                    spacing: Math.round(52 * Style.scaleHint)

                    BransonRadioButton
                    {
                        id:lockedRadioButton
                        circleSize:Math.round(18 * Style.scaleHint)
                        offColor:Style.blackFontColor
                        labelText: qmltexLocked
                        textSize:Math.round(10 * Style.scaleHint)
                        onCheckedChanged:
                        {
                            if(checked === true)
                            {
                                islocked = 1
                            }

                            else
                            {
                                islocked = 0
                            }
                        }
                    }

                    BransonRadioButton
                    {
                        id:unlockedRadioButton
                        circleSize:Math.round(18 * Style.scaleHint)
                        labelText:qmltextUnLocked
                        textSize:Math.round(10 * Style.scaleHint)

                        onCheckedChanged:
                        {
                            if(checked === true)
                            {
                                islocked = 0
                            }

                            else
                            {
                                islocked = 1
                            }
                        }
                    }
                }
            }
        }

        Row
        {
            anchors.top:addUserRectRow3.bottom
            topPadding:mainWindow.isUserModifing ? Math.round(85 * Style.scaleHint) : Math.round(18 * Style.scaleHint)
            leftPadding: parent.width *0.515
            spacing: parent.width *0.023

            BransonPrimaryButton
            {
                id: cancelButton
                width: parent.width * 0.22
                height: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: qmltextCancel
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.cancelButtonTextColor
                onClicked:
                {
                    addUserPopup.close()
                    enterUserNameTextField.text = ""
                    authorityLevelTextField.currentIndex = -1
                    selectLabel.text = "Select"
                    enableRadioButton.checked = true
                    unlockedRadioButton.checked = true
                    mainWindow.opacityFlag = false
                }
            }

            BransonPrimaryButton
            {
                id: saveButton
                width: parent.width * 0.22
                height: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: mainWindow.isUserModifing ? qmltextUpdate : qmltextSave
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked:
                {
                    if(saveButton.text == qmltextUpdate)
                    {
                        UserListDetailsListModel.onModifyUserButtonClicked(userId,assignAuthoritymodelIdx(), status , islocked)
                    }

                    else
                    {
                        onSave()
                    }

                    if(! isErrorOccurred)
                    {
                        mainWindow.opacityFlag = false
                    }
                }
            }
        }
    }
}

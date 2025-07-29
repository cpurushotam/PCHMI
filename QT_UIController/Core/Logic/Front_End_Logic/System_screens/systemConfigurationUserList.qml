/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the User List.

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
import QtQuick.Layouts 1.15
import "./../Diagnostics_Screens"
import "./../Common_Logic"
import "./../System_screens"


Item
{
    id:userlist
    property string qmlTextUserName          : "User ID"
    property string qmlTextAuthLevel         : "Authority Level"
    property string qmlTextUserStatus        : "User Status"
    property string qmlTextDateTime          : "Date/Time"
    property string qmlTextAction            : "Action"
    property string qmlTextEdit              : "Edit User"
    property string qmlTextPassword          : "Password"
    property string qmlTextDeleteUser        : "Delete User"
    property string qmltextUserDeleteConfirm : "Are you sure you want to delete ?"

    property string qmlTextConfirmation      : "Confirmation"
    property string qmlTextWarning           : "Warning !"

    property string  userNameToDelete : ""

    property var qmlTextArray: [qmlTextUserName, qmlTextAuthLevel, qmlTextUserStatus, qmlTextDateTime,
                                qmlTextAction, qmlTextEdit, qmlTextPassword, qmlTextDeleteUser, qmltextUserDeleteConfirm, qmlTextConfirmation, qmlTextWarning]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT, qmlTextArray)
        qmlTextUserName        = qmlTextArray[textEnum.textUserNameIdx]
        qmlTextAuthLevel       = qmlTextArray[textEnum.textAuthLevelIdx]
        qmlTextUserStatus      = qmlTextArray[textEnum.textUserStatusIdx]
        qmlTextDateTime        = qmlTextArray[textEnum.textDateTimeIdx]
        qmlTextAction          = qmlTextArray[textEnum.textActionIdx]
        qmlTextEdit            = qmlTextArray[textEnum.textEditIdx]
        qmlTextPassword        = qmlTextArray[textEnum.textPasswordIdx]
        qmlTextDeleteUser      = qmlTextArray[textEnum.textDeleteUserIdx]
        qmltextUserDeleteConfirm = qmlTextArray[textEnum.textUserDeleteConfirmIdx]
        qmlTextConfirmation = qmlTextArray[textEnum.textConfirmationIdx]
        qmlTextWarning = qmlTextArray[textEnum.textWarningIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textUserNameIdx           : 0
        readonly property int textAuthLevelIdx          : 1
        readonly property int textUserStatusIdx         : 2
        readonly property int textDateTimeIdx           : 3
        readonly property int textActionIdx             : 4
        readonly property int textEditIdx               : 5
        readonly property int textPasswordIdx           : 6
        readonly property int textDeleteUserIdx         : 7
        readonly property int textUserDeleteConfirmIdx  : 8
        readonly property int textConfirmationIdx       : 9
        readonly property int textWarningIdx            : 10
    }


    QtObject {
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
    Component.onCompleted:
    {
        updateLanguage();
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }


    BransonPopup
    {
        id:changePasswordPopupMsg
        x : 200
        y: mainWindow.height *0.15
        focus:true
        onOKButtonClicked:
        {
            changePasswordPopupMsg.visible = false
        }
    }
    Rectangle
    {
        id: userListTitleRect
        width: mainWindow.showWidth * 0.932
        height: mainWindow.showHeight * 0.07
        anchors.top: parent.top
        anchors.topMargin: mainWindow.showHeight * 0.11
        anchors.left: parent.left
        anchors.leftMargin: mainWindow.isPasswordRestDongleInserted ? mainWindow.showWidth * 0.03 : mainWindow.showWidth * 0.01
        border.color:"#0F0F0F"
        color: Style.contentBackgroundColor
        clip:true

        Text
        {
            id: userIDText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.01
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextUserName
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: authLevelText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.12
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextAuthLevel
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: userStatusText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.28
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextUserStatus
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: dateTimeText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.42
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextDateTime
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: actionText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.60
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextAction
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: changePasswordText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.73
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextAction
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }
        Text
        {
            id: deletePasswordText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.88
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextAction
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }
    }


    Connections{

        target:UserListDetailsListModel
            function onDeleteUserResponseChanged()
            {

                switch(UserListDetailsListModel.deleteUserResponseFromASC()){

                case modifyErrorEnum.param_MODIFY_USER_SUCCESS:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages() ,qmlTextConfirmation )
                    break;
                case modifyErrorEnum.param_MODIFY_USER_FAIL:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(), qmlTextWarning)
                    break;
                case modifyErrorEnum.param_MODIFY_USER_NOT_EXIST_IN_DB:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)
                    break;
                case modifyErrorEnum.param_NEED_AT_LEAST_ONE_EXECUTIVE_USER:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)
                    break;
                case modifyErrorEnum.param_MODIFY_USER_DONT_HAVE_ACCESS:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)
                    break;
                case modifyErrorEnum.param_MODIFY_PASSWORD_SUCCESS:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextConfirmation)
                    break;
                case modifyErrorEnum.param_MODIFY_PASSWORD_FAIL:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                case modifyErrorEnum.param_WRONG_EXISTING_PASSWORD:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                case modifyErrorEnum.param_MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                case modifyErrorEnum.param_DELETE_USER_SUCCESS:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextConfirmation)

                    break;
                case modifyErrorEnum.param_DELETE_USER_FAIL:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                case modifyErrorEnum.param_CAN_NOT_DELETE_LOGGED_IN_USER:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                case modifyErrorEnum.param_NEED_AT_LEAST_ONE_USER_IN_SYSTEM:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)

                    break;
                default:
                    mainWindow.showBransonPopup(UserListDetailsListModel.modifyUserWarningMessages(),qmlTextWarning)
                    break;
                }
            }
    }

//    BransonPopup
//    {
//        id: deleteconfirmPopup
//        onOKButtonClicked:
//        {
//            UserListDetailsListModel.onDeleteUserRequest(userNameToDelete)

//            deleteconfirmPopup.visible = false

//        }
//        onCancelButtonClicked:
//        {
//            deleteconfirmPopup.visible = false
//        }
//    }
    ListView
    {
        id: userDetailsListView
        width: mainWindow.showWidth * 0.932
        height: mainWindow.showHeight
        anchors.top: userListTitleRect.bottom
        anchors.topMargin: mainWindow.showHeight * 0.02
        anchors.left: userListTitleRect.left
        anchors.bottom: parent.bottom
        spacing: Math.round(10 * Style.scaleHint)
        model: UserListDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCurrentIndexChanged:
        {
        }
        delegate: Rectangle
        {
            id: userDetailsInfo
            width: userDetailsListView.width
            height: Math.round(35 * Style.scaleHint)
            anchors.left: parent.left
            border.color:"#0F0F0F"
            color: Style.contentBackgroundColor
            clip:true

            Text
            {
                id: userIDTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.01
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.UserId//"ADMIN" // Todo: will change text while integration
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: authLevelTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.12
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.AuthorityLevel//"Supervisor" // Todo: will change text while integration
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: userStatusTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.28
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.UserStatus//"Enabled" // Todo: will change text while integration
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: dateTimeTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.42
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.DateTime//"2024-06-26 03:27" // Todo: will change text while integration
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: actionTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.617
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: qmlTextEdit
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.buttonColor
                font.weight : Font.Medium
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            mainWindow.isUserModifing = true
                            mainWindow.showUserMgmtAddUserScreen(model.UserId, model.AuthorityLevel, model.UserStatus, model.UserLockUnlock)
                        }
                    }
                }
            }
            Image
            {
                id: editActionImage
                source: "qrc:/Images/Edit_icon.svg"
                width: parent.width*0.014
                height: parent.width*0.014
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.60
                anchors.verticalCenter: parent.verticalCenter
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            mainWindow.isUserModifing = true
                            mainWindow.showUserMgmtAddUserScreen(model.UserId, model.AuthorityLevel, model.UserStatus, model.UserLockUnlock)
                        }
                    }
                }
            }

            Text
            {
                id: actionPasswordTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.752
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: qmlTextPassword
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.buttonColor
                font.weight : Font.Medium
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            mainWindow.isUserModifingPassword = true
                            mainWindow.showChangePasswordPopup(model.UserId)
                        }
                    }
                }
            }
            Image
            {
                id: editPasswordActionImage
                source: "qrc:/Images/Blue_Change_password_icon.svg"
                width: parent.width*0.019
                height: parent.width*0.019
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.728
                anchors.verticalCenter: parent.verticalCenter
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            mainWindow.isUserModifingPassword = true
                            mainWindow.showChangePasswordPopup(model.UserId)
                        }
                    }
                }
            }

            Text
            {
                id: actionDeleteUserTextDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.887
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: qmlTextDeleteUser
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.buttonColor
                font.weight : Font.Medium
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            userNameToDelete = model.UserId
                            mainWindow.showBransonPopupForDel(userNameToDelete)
                        }
                    }
                }
            }
            Image
            {
                id: deleteUserActionImage
                source: "qrc:/Images/Blue_Trash_icon.svg"
                width: parent.width*0.014
                height: parent.width*0.014
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.87
                anchors.verticalCenter: parent.verticalCenter
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            userNameToDelete = model.UserId
                            mainWindow.showBransonPopupForDel(userNameToDelete)
                        }
                    }
                }
            }
        }
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Login Screen

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.LoginIndexEnum 1.0
import "./../Common_Logic"
Rectangle
{
    id:loginWindow
    property int fontPixelSize: Math.round(Style.style6 * Style.scaleHint)
    property string qmltextEnterUsername:       "Enter Username"
    property string qmltextEnterPassWord:       "Enter Password"
    property string qmltextBransonPolaris:      "Branson Polaris"
    property string qmltextLogin:               "LOGIN"
    property string qmltextMultipleLoginFailed: "Too many failed login attempts. System will be locked for 15 minutes."
    property string qmltextLoginFail:           "Invalid Password. Please re-enter and try again."
    property string qmltextLoginSuccess:        "Login Successful"
    property string qmltextPasscodeEmpty:       "Password is Empty"
    property string qmltextUserNameEmpty:       "User Name is Empty"
    property string qmltextAlert                 : "Alert"

    property string qmlLoginErrorMessage:       qmltextLoginSuccess
    property bool   clearedOnce: false

    property var    qmlTextArray: [qmltextEnterPassWord, qmltextLogin,
        qmltextMultipleLoginFailed, qmltextLoginFail, qmltextLoginSuccess, qmltextPasscodeEmpty,qmltextEnterUsername,qmltextBransonPolaris,qmltextUserNameEmpty,
        qmltextAlert]

    /*Background picture of login interface*/
    visible: true

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.LOGIN, qmlTextArray)
        qmltextEnterPassWord = qmlTextArray[textEnum.enterPasswordIdx]
        qmltextLogin = qmlTextArray[textEnum.loginIdx]
        qmltextMultipleLoginFailed = qmlTextArray[textEnum.multipleLoginFailedIdx]
        qmltextLoginFail = qmlTextArray[textEnum.loginFailIdx]
        qmltextLoginSuccess = qmlTextArray[textEnum.loginSuccessIdx]
        qmltextPasscodeEmpty = qmlTextArray[textEnum.passcodeEmptyIdx]
        qmltextEnterUsername = qmlTextArray[textEnum.textEnterUsernameIdx]
        qmltextBransonPolaris = qmlTextArray[textEnum.textBransonPolarisIdx]
        qmltextUserNameEmpty = qmlTextArray[textEnum.textUserNameEmptyIdx]
        qmltextAlert = qmlTextArray[textEnum.alertIdx]
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
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.LOGIN
        inputPanelLoginKeyBoard.visible = false
        updateLanguage()
    }

    /*Make sure the active screen data shall get updated to resume communication after disconnection*/
    onVisibleChanged:
    {
        if(visible)
        {
            /*To make sure warnings popups are not visible unless login not performed*/
            isLoggedIn = false
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.LOGIN
        }
    }

    InputPanel
    {
        id: inputPanelLoginKeyBoard
        z: 1
        x: 0
        y: mainWindow.showHeight * 0.85
        height:mainWindow.showHeight * 0.15
        width: mainWindow.showWidth
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible
    }

    QtObject
    {
        id: textEnum
        readonly property int enterPasswordIdx:         0
        readonly property int loginIdx:                 1
        readonly property int multipleLoginFailedIdx:   2
        readonly property int loginFailIdx:             3
        readonly property int loginSuccessIdx:          4
        readonly property int passcodeEmptyIdx:         5
        readonly property int textEnterUsernameIdx:     6
        readonly property int textBransonPolarisIdx:    7
        readonly property int textUserNameEmptyIdx:     8
        readonly property int alertIdx:                 9

    }

    QtObject
    {
        id: loginErrorsEnum
        readonly property int loginErrorUnknownIdx:         0
        readonly property int loginSuccessIdx:              1
        readonly property int invalidUsrPassIdx:            2
        readonly property int userLockedIdx:                3
        readonly property int userDisabledIdx:              4
        readonly property int passExpiredIdx:               5
        readonly property int passExpireSoonIdx:            6
        readonly property int firstTimeLoginIdx:            7
        readonly property int passwordNotExpiredIdx:        8
    }
   
    BorderImage
    {
        id: backgroundLoginUi
        source: "qrc:/Images/Login_bg.svg"
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                inputPanelLoginKeyBoard.visible =false
            }
        }
    }
    Image
    {
        id: emersonLogo
        source: "qrc:/Images/Emerson_logo.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
    }
    Rectangle
    {
        id:rectangle
        anchors.centerIn: parent
        width: Math.round(300 * Style.scaleHint)
        height: Math.round(340 * Style.scaleHint)
        color: "#FFFFFF"
        radius: 10
        Flickable
        {
            id:loginFlick
            flickableDirection: Flickable.VerticalFlick
            width: parent.width
            height: parent.height
            flickDeceleration: 10000
            contentHeight: true ? height* 3.4: height* 1.9
            contentY: (textFildPassword.focus) ?  (110) :  (0)
            clip: true
            Text
            {
                id:bransonPolaris
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: qmltextBransonPolaris
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: "#000000"
            }
            Image
            {
                id: imageLoginUiUserName
                height: Math.round(12 * Style.scaleHint)
                width: Math.round(12 * Style.scaleHint)
                source: "qrc:/Images/user_icon.svg"
                sourceSize.width:  imageLoginUiUserName.width
                sourceSize.height: imageLoginUiUserName.height
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                anchors.verticalCenter: textLoginUiTooltip.verticalCenter
            }
            Text
            {
                id: textLoginUiTooltip
                text: qmltextEnterUsername
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                height: Math.round(27 * Style.scaleHint)
                anchors.left: imageLoginUiUserName.right
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(75 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }
            TextField
            {
                id: textFildUserName
                z: 1
                anchors.top: textLoginUiTooltip.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                echoMode: TextInput.Normal
                mouseSelectionMode: TextInput.SelectCharacters
                Text
                {
                    text: qmltextEnterUsername
                    color: "#E9ECEF"
                    visible: !textFildUserName.text
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    font.pixelSize: Math.round(11 * Style.scaleHint)
                    font.family: Style.regular.name
                }
                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 2
                    color: "transparent"
                    border.color: Style.activeFrameBorderColor
                }

                onActiveFocusChanged:
                {
                    /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                    if(activeFocus)
                    {
                        clearedOnce = true
                        textFildUserName.selectAll()
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
                        textFildUserName.clear()
                        clearedOnce = false
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        textFildUserName.focus = true
                        textFildUserName.color = "#000000"
                        inputPanelLoginKeyBoard.visible = true
                        Qt.inputMethod.hide()
                    }
                }
            }
            Image
            {
                id: imageLoginUiPassword
                source: "qrc:/Images/password_icon.svg"
                height: Math.round(12 * Style.scaleHint)
                width: Math.round(12 * Style.scaleHint)
                sourceSize.width:  imageLoginUiPassword.width
                sourceSize.height: imageLoginUiPassword.height
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                anchors.verticalCenter: textLoginUiPassword.verticalCenter
            }
            Text
            {
                id: textLoginUiPassword
                text: qmltextEnterPassWord
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                height: Math.round(27 * Style.scaleHint)
                anchors.left: imageLoginUiPassword.right
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                anchors.top: textFildUserName.bottom
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }
            TextField
            {
                id: textFildPassword
                z: 1
                anchors.top: textLoginUiPassword.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                passwordCharacter: "*"
                echoMode: TextInput.Password
                mouseSelectionMode: TextInput.SelectCharacters
                Text
                {
                    text: "Enter Password"
                    color: "#E9ECEF"
                    visible: !textFildPassword.text
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    font.pixelSize: Math.round(11 * Style.scaleHint)
                    font.family: Style.regular.name
                }
                background: Rectangle
                {
                    anchors.fill: parent
                    border.width: 2
                    color: "transparent"
                    border.color: Style.activeFrameBorderColor
                }

                onActiveFocusChanged:
                {
                    /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                    if(activeFocus)
                    {
                        clearedOnce = true
                        textFildPassword.selectAll()
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
                        textFildPassword.clear()
                        clearedOnce = false
                    }

                    if(event.key === Qt.Key_V && event.modifiers & Qt.ControlModifier)
                    {
                        event.accepted = true
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        textFildPassword.focus = true
                        textFildPassword.color = "#000000"
                        inputPanelLoginKeyBoard.visible = true
                        Qt.inputMethod.hide()
                    }
                }
            }

            Button
            {
                id:loginButton
                z: 1
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(40 * Style.scaleHint)
                anchors.top: textFildPassword.bottom
                anchors.topMargin: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                highlighted: true
                Text
                {
                    text: qmltextLogin
                    color: "#FFFFFF"
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(50 * Style.scaleHint)
                    font.bold: true
                    font.capitalization:Font.AllUppercase
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                }
                background: Rectangle
                {
                    color: "#23395D"
                    border.width: 1
                }
                onClicked:
                {
                    var Errorflag = false
                    mainWindow.userNameTxt = textFildUserName.text
                    mainWindow.passwordTxt = textFildPassword.text

                    if(mainWindow.userNameTxt === "")
                    {
                        mainWindow.showBransonPopup(qmltextUserNameEmpty, qmltextAlert)
                        Errorflag = true
                    }

                    else if(mainWindow.passwordTxt === "")
                    {
                        mainWindow.showBransonPopup(qmltextPasscodeEmpty, qmltextAlert)
                        Errorflag = true
                    }

                    if(Errorflag === false)
                    {
                        LoginObj.onLoginButtonClicked(textFildUserName.text, textFildPassword.text)
                    }
                }
            }


            MouseArea
            {
                id :loginRectMA
                anchors.fill: parent
                onClicked:
                {
                    textFildUserName.focus = false
                    textFildPassword.focus = false
                    inputPanelLoginKeyBoard.visible = false
                    Qt.inputMethod.hide()
                }
            }
        }
    }

    Connections
    {
        target: LoginObj
        function onLoadingDataChangedd()
        {
            if(mainWindow.isAutoLoginEnable === false)
            {
                mainWindow.userLevelTxt = LoginObj.getLoginUserLevel()
                mainWindow.loginProcess()
                UserPrivilegeObj.processUserPrivilige()
                textFildUserName.text = ""
                textFildPassword.text = ""
            }
        }
    }
}

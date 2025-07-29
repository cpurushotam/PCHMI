import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import Style 1.0
import QtQuick.Layouts 1.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"

Rectangle
{
    id:changePasswordWindow

    property string qmltextBransonPolaris             :"Branson Polaris"
    property string qmltextcurrentPasswordLabel       :"Current Password"
    property string qmltextnewPasswordLabel           :"New Password"
    property string qmltextconfirmPasswordLabel       :"Confirm Password"
    property string qmltextEnterCurrPass              :"Enter Current Password"
    property string qmltextEnterNewPass               :"Enter New Password"
    property string qmltextEnterConfPass              :"Enter Confirm Password"
    property string qmltextReset                      :"RESET"
    property string qmltextCancel                     :"CANCEL"
    property string qmltextResetPassword              :"Please reset your login password"
    property string qmltextWrongPassword              :"Wrong Password"
    property string qmltextPasswordSameMsg            :"New Password and Confirm Password should be same"
    property string qmltextPassWordEmptyMsg           :"New Password or Confirm Password is empty"
    property string qmltextCurrentNewPasswordDiffMsg  :"Current Password and New Password should be different"
    property string qmltextValidPasswordMsg           :"Password must be at least 8 characters in length, including 1 uppercase letter, 1 lowercase letter, 1 numeric character, 1 special character"
    property string qmltextAlert                      :"Alert"

    property bool   clearedOnce: false

    visible: true

    property var qmlTextArray:[qmltextBransonPolaris,qmltextcurrentPasswordLabel,qmltextnewPasswordLabel,qmltextconfirmPasswordLabel,qmltextEnterCurrPass,
        qmltextEnterNewPass,qmltextEnterConfPass,qmltextReset,qmltextCancel, qmltextResetPassword,qmltextWrongPassword, qmltextPasswordSameMsg,
        qmltextPassWordEmptyMsg,qmltextCurrentNewPasswordDiffMsg,qmltextValidPasswordMsg, qmltextAlert]

    QtObject
    {
        id: textEnum
        readonly property int textBransonPolarisIdx                     : 0
        readonly property int textcurrentPasswordLabelIdx               : 1
        readonly property int textnewPasswordLabelIdx                   : 2
        readonly property int textconfirmPasswordLabelIdx               : 3
        readonly property int textEnterCurrPassIdx                      : 4
        readonly property int textEnterNewPassIdx                       : 5
        readonly property int textEnterConfPassIdx                      : 6
        readonly property int textResetIdx                              : 7
        readonly property int textCancelIdx                             : 8
        readonly property int textResetPasswordIdx                      : 9
        readonly property int textWrongPasswordIdx                      : 10
        readonly property int textPasswordSameMsgIdx                    : 11
        readonly property int textPassWordEmptyMsgIdx                   : 12
        readonly property int textCurrentNewPasswordDiffMsgIdx          : 13
        readonly property int textValidPasswordMsgIdx                   : 14
        readonly property int alertIdx                                  : 15
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.FIRST_TIME_LOGIN_CHANGE_PASSWORD, qmlTextArray)
        qmltextBransonPolaris = qmlTextArray[textEnum.textBransonPolarisIdx]
        qmltextcurrentPasswordLabel = qmlTextArray[textEnum.textcurrentPasswordLabelIdx]
        qmltextnewPasswordLabel = qmlTextArray[textEnum.textnewPasswordLabelIdx]
        qmltextconfirmPasswordLabel = qmlTextArray[textEnum.textconfirmPasswordLabelIdx]
        qmltextEnterCurrPass = qmlTextArray[textEnum.textEnterCurrPassIdx]
        qmltextEnterNewPass = qmlTextArray[textEnum.textEnterNewPassIdx]
        qmltextEnterConfPass = qmlTextArray[textEnum.textEnterConfPassIdx]
        qmltextReset = qmlTextArray[textEnum.textResetIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextResetPassword = qmlTextArray[textEnum.textResetPasswordIdx]
        qmltextWrongPassword = qmlTextArray[textEnum.textWrongPasswordIdx]
        qmltextPasswordSameMsg = qmlTextArray[textEnum.textPasswordSameMsgIdx]
        qmltextPassWordEmptyMsg = qmlTextArray[textEnum.textPassWordEmptyMsgIdx]
        qmltextCurrentNewPasswordDiffMsg = qmlTextArray[textEnum.textCurrentNewPasswordDiffMsgIdx]
        qmltextValidPasswordMsg = qmlTextArray[textEnum.textValidPasswordMsgIdx]
        qmltextAlert = qmlTextArray[textEnum.alertIdx]
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
        readonly property int param_CURRENT_AND_NEW_PASSWORD_SAME           : 14
    }

    function passwordCheck(currPassword, newPassword, confPassword)
    {
        var flag = true

        if(newPassword === "" || confPassword === "")
        {
            mainWindow.showBransonPopup(qmltextPassWordEmptyMsg, qmltextAlert)
            flag = false
        }
        else
        {
            if(newPassword !== confPassword)
            {
                mainWindow.showBransonPopup(qmltextPasswordSameMsg, qmltextAlert)
                flag = false
            }
            else if(newPassword === currPassword)
            {
                mainWindow.showBransonPopup(qmltextCurrentNewPasswordDiffMsg, qmltextAlert)
                flag = false
            }
            else
            {
                var regExp = /(?=^.{8,20}$)(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;:;'?/&gt;.&lt;,])(?!.*\s).*$/;
                if(!regExp.test(newPassword))
                {
                    mainWindow.showBransonPopup(qmltextValidPasswordMsg, qmltextAlert)
                    flag = false
                }
            }
        }
        return flag
    }


    Connections
    {
        target: LoginObj
        function onModifyPassChangedd()
        {
            switch(LoginObj.passWordResetValidationFromASC())
            {
            case modifyErrorEnum.param_MODIFY_USER_SUCCESS:
            case modifyErrorEnum.param_MODIFY_USER_FAIL:
            case modifyErrorEnum.param_MODIFY_USER_NOT_EXIST_IN_DB:
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_EXECUTIVE_USER:
            case modifyErrorEnum.param_MODIFY_USER_DONT_HAVE_ACCESS:
            case modifyErrorEnum.param_MODIFY_PASSWORD_FAIL:
            case modifyErrorEnum.param_WRONG_EXISTING_PASSWORD:
            case modifyErrorEnum.param_MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED:
            case modifyErrorEnum.param_DELETE_USER_SUCCESS:
            case modifyErrorEnum.param_DELETE_USER_FAIL:
            case modifyErrorEnum.param_CAN_NOT_DELETE_LOGGED_IN_USER:
            case modifyErrorEnum.param_NEED_AT_LEAST_ONE_USER_IN_SYSTEM:
            case modifyErrorEnum.param_CURRENT_AND_NEW_PASSWORD_SAME:
                mainWindow.showBransonPopup(LoginObj.modifyUserWarningMessages(), qmltextAlert)
                break;

            case modifyErrorEnum.param_MODIFY_PASSWORD_SUCCESS:
                changePasswordWindow.visible =false
                loginLayout.visible = false
                configLayout.visible =false
                clearStackView()
                menuParentOptionSelect(UIScreenEnum.PRODUCTION)
                break;

            default:
                mainWindow.showBransonPopup(LoginObj.modifyUserWarningMessages(), qmltextAlert)
                break;
            }
        }
    }

    function onSave()
    {
        var currPassword =  textFildCurrentPassword.text
        var newPassword =   textFildNewPassword.text
        var confPassword =  textFildConfirmPassword.text

        if(passwordCheck(currPassword,newPassword, confPassword))
        {
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.LOGIN
            LoginObj.IsResetScreenNavigated = true
            LoginObj.setCurrentActiveScreen(  ActiveScreen.CurrentActiveScreen )
            LoginObj.onLoginResetButtonClicked(mainWindow.userNameTxt,currPassword,newPassword)
            textFildCurrentPassword.text = ""
            textFildNewPassword.text =""
            textFildConfirmPassword.text = ""
        }

    }


    Component.onCompleted:{
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.FIRST_TIME_LOGIN_CHANGE_PASSWORD
        inputPanelChangePasswordKeyBoard.visible = false
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }
    InputPanel
    {
        id: inputPanelChangePasswordKeyBoard
        z: 1
        x: 0
        y: mainWindow.showHeight * 0.85
        height:mainWindow.showHeight * 0.15
        width: mainWindow.showWidth
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible
    }
    BorderImage {
        id: backgroundChangePassUi
        source: "qrc:/Images/Login_bg.svg"
        anchors.fill: parent
        MouseArea{
            anchors.fill: parent
            onClicked: {
                inputPanelChangePasswordKeyBoard.visible = false
            }
        }
    }
    Image {
        id: emersonLogo1
        source: "qrc:/Images/Emerson_logo.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: Math.round(25 * Style.scaleHint)
    }
    Rectangle{
        id:rectangle1
        anchors.top:emersonLogo1.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        width: Math.round(300 * Style.scaleHint)
        height: Math.round(380 * Style.scaleHint)
        color: "#FFFFFF"
        radius: 10
        Flickable{
            id:loginFlick
            flickableDirection: Flickable.VerticalFlick
            width: parent.width
            height: parent.height
            contentHeight: true ? height* 3.4: height* 1.9
            clip: true
            Text{
                id:bransonPolaris
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: qmltextBransonPolaris
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: "#000000"
            }
            Text{
                id:resetPasswordtext
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top:bransonPolaris.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                text:qmltextResetPassword
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                ///font.family: Style.Regular.name
                color: "#868686"
            }
            Image{
                id: imageCurrentPassword
                source: "qrc:/Images/password_icon.svg"
                height: Math.round(12 * Style.scaleHint)
                width: Math.round(12 * Style.scaleHint)
                sourceSize.width:  imageLoginUiPassword.width
                sourceSize.height: imageLoginUiPassword.height
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                anchors.verticalCenter: textCurrentPassword.verticalCenter
            }
            Text{
                id: textCurrentPassword
                text: qmltextcurrentPasswordLabel
                //font.family: Style.Regular.name
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                height: Math.round(27 * Style.scaleHint)
                anchors.left: imageCurrentPassword.right
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                anchors.top: resetPasswordtext.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                //color: Style.BlackFontColor
            }

            TextField
            {
                id: textFildCurrentPassword
                anchors.top: textCurrentPassword.bottom
                anchors.topMargin: Math.round(1 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                passwordCharacter: "*"
                echoMode: TextInput.Password
                mouseSelectionMode: TextInput.SelectCharacters

                Text
                {
                    text: qmltextEnterCurrPass
                    color: "#E9ECEF"
                    visible: !textFildCurrentPassword.text
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(7 * Style.scaleHint)
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
                        textFildCurrentPassword.selectAll()
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
                        textFildCurrentPassword.clear()
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
                        textFildCurrentPassword.focus = true
                        textFildCurrentPassword.color = "#000000"
                        inputPanelChangePasswordKeyBoard.visible = true
                        Qt.inputMethod.hide()
                    }
                }
            }

            Image
            {
                id: imageNewPassword
                source: "qrc:/Images/password_icon.svg"
                height: Math.round(12 * Style.scaleHint)
                width: Math.round(12 * Style.scaleHint)
                sourceSize.width:  imageLoginUiPassword.width
                sourceSize.height: imageLoginUiPassword.height
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                anchors.verticalCenter: textNewPassword.verticalCenter
            }

            Text
            {
                id: textNewPassword
                text: qmltextnewPasswordLabel
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                height: Math.round(27 * Style.scaleHint)
                anchors.left: imageNewPassword.right
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                anchors.top: textFildCurrentPassword.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)//Math.round(11 * Style.scaleHint)
            }

            TextField
            {
                id: textFildNewPassword
                anchors.top: textNewPassword.bottom
                anchors.topMargin: Math.round(1 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                passwordCharacter: "*"
                echoMode: TextInput.Password
                mouseSelectionMode: TextInput.SelectCharacters

                Text
                {
                    text: qmltextEnterNewPass
                    color: "#E9ECEF"
                    visible: !textFildNewPassword.text
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(7 * Style.scaleHint)
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
                        textFildNewPassword.selectAll()
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
                        textFildNewPassword.clear()
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
                        textFildNewPassword.focus = true
                        textFildNewPassword.color = "#000000"
                        inputPanelChangePasswordKeyBoard.visible = true
                        Qt.inputMethod.hide()
                    }
                }
            }

            Image
            {
                id: imageConfirmPassword
                source: "qrc:/Images/password_icon.svg"
                height: Math.round(12 * Style.scaleHint)
                width: Math.round(12 * Style.scaleHint)
                sourceSize.width:  imageConfirmPassword.width
                sourceSize.height: imageConfirmPassword.height
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                anchors.verticalCenter: textConfirmPassword.verticalCenter
            }

            Text
            {
                id: textConfirmPassword
                text: qmltextconfirmPasswordLabel
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                height: Math.round(27 * Style.scaleHint)
                anchors.left: imageConfirmPassword.right
                anchors.leftMargin: Math.round(8 * Style.scaleHint)
                anchors.top: textFildNewPassword.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }

            TextField
            {
                id: textFildConfirmPassword
                anchors.top: textConfirmPassword.bottom
                anchors.topMargin: Math.round(1 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                passwordCharacter: "*"
                echoMode: TextInput.Password
                mouseSelectionMode: TextInput.SelectCharacters

                Text
                {
                    text: qmltextEnterConfPass
                    color: "#E9ECEF"
                    visible: !textFildConfirmPassword.text
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(7 * Style.scaleHint)
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
                        textFildConfirmPassword.selectAll()
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
                        textFildConfirmPassword.clear()
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
                        textFildConfirmPassword.focus = true
                        textFildConfirmPassword.color = "#000000"
                        inputPanelChangePasswordKeyBoard.visible = true
                        Qt.inputMethod.hide()
                    }
                }
            }

            Button{
                id:resetButton
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.top: textFildConfirmPassword.bottom
                anchors.topMargin: Math.round(25 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                highlighted: true
                Text{
                    text: qmltextReset
                    color: "#FFFFFF"
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(50 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                }
                background: Rectangle
                {
                    color: "#23395d"
                    border.width: 1
                }
                onClicked: {
                    onSave()

                    textFildCurrentPassword.text = ""
                    textFildNewPassword.text =""
                    textFildConfirmPassword.text = ""

                }
            }
            Button{
                id:cancelButton
                width: Math.round(160 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.top: resetButton.bottom
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(75 * Style.scaleHint)
                highlighted: true
                Text{
                    text: qmltextCancel
                    color: "#FFFFFF"
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(50 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                }
                background: Rectangle
                {
                    color: "#868686"
                    border.width: 1
                }
                onClicked: {
                    mainWindow.closeChangePasswordScreen()
                }
            }
        }
    }
}

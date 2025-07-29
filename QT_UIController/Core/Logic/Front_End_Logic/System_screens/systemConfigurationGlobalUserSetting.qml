/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Global User Setting Screen

 **********************************************************************************************************/
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Window 2.12
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"

Item {
    id:globalUserSettingItem

    property string qmltextPasswordExpiration:       "Password Expiration"
    property string qmltextIdleTimeLogOut:           "Idle Time Logout"
    property string qmltextDays:                     "day(s)"
    property string qmltextMins:                     "min(s)"
    property string qmltextResetToDefault:           "RESET TO DEFAULT"
    property string qmltextSave:                     "SAVE"
    property string qmltextLockOutTime:              "Lock Out Time"
    property string qmltextOk:                       "OK"
    property string qmltextConfirmation:             "CONFIRMATION"
    property string qmltextWarning:                  "Warning..!"
    property string qmltextSaveMsg:                  "Global User Settings saved successfully"
    property string qmltextErrorToSaveMsg:           "Failed to save Global User Settings"
    property string qmltextResetMsg:                 "Global User Settings reset successfully"
    property string qmltextErrorToResetMsg:          "Failed to reset Global User Settings"
    property string qmltextAutoLogin:                "AutoLogin"
    property string qmltextAutoLoginMsg:             "Please select AutoLogin User Name"
    property string qmltextOperLevelUserMsg:         "Operator Level User Not Exist"
    property string qmltextAuthCheckMsg:             "Authority check is disabled, please enable it"

    property var qmlTextArray:[qmltextPasswordExpiration,qmltextIdleTimeLogOut,qmltextDays,qmltextMins,qmltextResetToDefault,qmltextSave,
                              qmltextLockOutTime, qmltextOk, qmltextConfirmation, qmltextWarning, qmltextSaveMsg, qmltextErrorToSaveMsg,
                              qmltextResetMsg, qmltextErrorToResetMsg,qmltextAutoLogin, qmltextAutoLoginMsg, qmltextOperLevelUserMsg,
                              qmltextAuthCheckMsg]

    readonly property int updateGlobalUserSettingFailure: 1
    readonly property int updateGlobalUserSettingSuccess: 2
    property bool isResetToDefaultBtnClicked: false
    property int modelListSize: -1
    property int modelCurrentIndex:-1
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    QtObject{
        id: textEnum
        readonly property int textPasswordExpirationIdx     : 0
        readonly property int textIdleTimeLogOutIdx         : 1
        readonly property int textDaysIdx                   : 2
        readonly property int textMinsIdx                   : 3
        readonly property int textResetToDefaultIdx         : 4
        readonly property int textSaveIdx                   : 5
        readonly property int textLockOutTimeIdx            : 6
        readonly property int textOkIdx                     : 7
        readonly property int textConfirmationIdx           : 8
        readonly property int textWarningIdx                : 9
        readonly property int textSaveMsgIdx                : 10
        readonly property int textErrorToSaveMsgIdx         : 11
        readonly property int textResetMsgIdx               : 12
        readonly property int textErrorToResetMsgIdx        : 13
        readonly property int textAutoLoginIdx              : 14
        readonly property int textAutoLoginMsgIdx           : 15
        readonly property int textOperLevelUserMsgIdx       : 16
        readonly property int textAuthCheckMsgIdx           : 17
    }
    function updateLanguage(){
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT_GLOBAL_USER_SETTINGS, qmlTextArray)
        qmltextPasswordExpiration = qmlTextArray[textEnum.textPasswordExpirationIdx]
        qmltextIdleTimeLogOut = qmlTextArray[textEnum.textIdleTimeLogOutIdx]
        qmltextDays = qmlTextArray[textEnum.textDaysIdx]
        qmltextMins = qmlTextArray[textEnum.textMinsIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextLockOutTime = qmlTextArray[textEnum.textLockOutTimeIdx]
        qmltextOk = qmlTextArray[textEnum.textOkIdx]
        qmltextConfirmation = qmlTextArray[textEnum.textConfirmationIdx]
        qmltextWarning = qmlTextArray[textEnum.textWarningIdx]
        qmltextSaveMsg = qmlTextArray[textEnum.textSaveMsgIdx]
        qmltextErrorToSaveMsg = qmlTextArray[textEnum.textErrorToSaveMsgIdx]
        qmltextResetMsg = qmlTextArray[textEnum.textResetMsgIdx]
        qmltextErrorToResetMsg = qmlTextArray[textEnum.textErrorToResetMsgIdx]
        qmltextAutoLogin = qmlTextArray[textEnum.textAutoLoginIdx]
        qmltextAutoLoginMsg = qmlTextArray[textEnum.textAutoLoginMsgIdx]
        qmltextOperLevelUserMsg = qmlTextArray[textEnum.textOperLevelUserMsgIdx]
        qmltextAuthCheckMsg = qmlTextArray[textEnum.textAuthCheckMsgIdx]
    }
    
    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        target: GlobalUserSetting

        function onGlobalUserSettingDataChanged()
        {
            comboBoxModel.clear()
            var list = GlobalUserSetting.loadOperatorUser()
            modelListSize = list.length
            for (var i = 0; i < list.length; i++)
            {
                if(list[i] === GlobalUserSetting.AutoLoginUser)
                {
                    modelCurrentIndex = i;
                }
                comboBoxModel.append({name: list[i]});
            }
            autoLoginEnableSwitch.checked = GlobalUserSetting.AutoLoginStatus
        }
    }

    ListModel{
        id:comboBoxModel
    }
    
    Component.onCompleted: {
        updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT_GLOBAL_USER_SETTINGS
        comboBoxModel.clear()
        var list = GlobalUserSetting.loadOperatorUser()
        modelListSize = list.length
        for (var i = 0; i < list.length; i++)
        {
            if(list[i] === GlobalUserSetting.AutoLoginUser)
            {
                modelCurrentIndex = i;
            }
           comboBoxModel.append({name: list[i]});
        }
    }

    Popup
    {
        id:userSettingPopup
        x: mainWindow.showWidth * 0.27
        y: mainWindow.showHeight *0.20
        width: mainWindow.showWidth * 0.35
        height: mainWindow.showHeight *0.28
        modal:true
        focus: true
        closePolicy: Popup.NoAutoClose

        background: Rectangle
        {
            id:rectMain
            color:"transparent"
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }

        Rectangle
        {
            id: clipper
            anchors.fill: parent
            color:"white"
            clip:true

            Rectangle
            {
                id: clipped
                anchors.left: parent.left
                anchors.right: parent.right
                width: parent.width
                height: parent.height*0.20
                color: Style.headerBackgroundColor
                Text
                {
                    id:textHeader
                    text:""
                    font.pixelSize:parent.height * 0.40
                    font.family: Style.regular.name
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.02
                    anchors.verticalCenter: parent.verticalCenter
                    font.weight : Font.Medium
                }
            }

            Text
            {
                id:dailogMsg
                anchors.top: clipped.bottom
                anchors.topMargin: parent.height*0.19
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.09
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.05
                font.pixelSize:Math.round(Style.style1 * Style.scaleHint)*0.90
                font.family: Style.regular.name
                text:""
                font.weight : Font.Medium
                wrapMode: Text.Wrap
                width:parent.width
            }

            BransonPrimaryButton
            {
                id: btnOk
                implicitWidth: Math.round(90 * Style.scaleHint)
                implicitHeight: Math.round(22 * Style.scaleHint)
                fontSize: Math.round(Style.style1  * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.25 - (implicitWidth/2)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(10 * Style.scaleHint)
                text: qmltextOk
                buttonColor: "#17345C"
                font.family: Style.regular.name
                onClicked:
                {
                    userSettingPopup.close()
                }
            }
        }
    }

    Connections
        {
            target: GlobalUserSetting
            /*On every save and Reset to default click Error code should get refresh*/
            function onGlobalUserSettingErrorCodeUpdated()
            {
                messagePopup()
            }
        }

    function messagePopup()
    {
        if(isResetToDefaultBtnClicked === true)
        {
            if(GlobalUserSetting.UpdateErrorCode === updateGlobalUserSettingSuccess)
            {
                if(GlobalUserSetting.AuthorityCheck === true && idleTimeLogoutTextField.text !== "0")
                {
                    //To convert idleTimeLogOut in millisec and set timer to logout
                    IdleTimeLogout.setTimeOut(parseInt(idleTimeLogoutTextField.text)*(mainWindow.minuteToMilliSecTimeConvFact))
                }

                else
                {
                    IdleTimeLogout.setTimeOut(mainWindow.idleTimeLogoutMaxVal)
                }
            }

            else if(GlobalUserSetting.UpdateErrorCode === updateGlobalUserSettingFailure)
            {
                textHeader.text = qmltextWarning
                dailogMsg.text = qmltextErrorToResetMsg
                userSettingPopup.open()
            }

            isResetToDefaultBtnClicked = false
        }

        else
        {
            if(GlobalUserSetting.UpdateErrorCode === updateGlobalUserSettingSuccess)
            {
                if(GlobalUserSetting.AuthorityCheck === true && idleTimeLogoutTextField.text !== "0")
                {
                    //To convert idleTimeLogOut in millisec and set timer to logout
                    IdleTimeLogout.setTimeOut(parseInt(idleTimeLogoutTextField.text)*(mainWindow.minuteToMilliSecTimeConvFact))
                }

                else
                {
                    IdleTimeLogout.setTimeOut(mainWindow.idleTimeLogoutMaxVal)
                }
            }

            else if(GlobalUserSetting.UpdateErrorCode === updateGlobalUserSettingFailure)
            {
                textHeader.text = qmltextWarning
                dailogMsg.text = qmltextErrorToSaveMsg
                userSettingPopup.open()
            }
        }

    }

    Rectangle{
        id:passwordExpirationRect
        width: Math.round(260 * Style.scaleHint)
        height: Math.round(52 * Style.scaleHint)
        color:Style.contentBackgroundColor
        anchors.top:parent.top
        anchors.topMargin: Math.round(45 * Style.scaleHint)
        anchors.left:parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        Text{
            id:passwordExpirationtext
            text: qmltextPasswordExpiration
            anchors.top:parent.top
            anchors.topMargin:Math.round(5 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(6 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }
        Image {
            id: passwordExpirationtInfo
            source: "qrc:/Images/Info_icon.svg"
            width: parent.width*0.06
            height: parent.width*0.06
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.03
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        TextField{
            id:passwordExpirationTextField
            width: Math.round(170 * Style.scaleHint)
            height: Math.round(21 * Style.scaleHint)
            anchors.top: passwordExpirationtext.bottom
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left:passwordExpirationtext.left
            mouseSelectionMode: TextInput.SelectCharacters
            font.pixelSize: Math.round(12 * Style.scaleHint)
            font.family: Style.regular.name
            text:GlobalUserSetting.PasswordExpiration
            background: Rectangle{
                anchors.fill: parent
                border.width: 1
                color: "transparent"
                radius: 8
                border.color: "#707070"
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    passwordExpirationTextField.focus = true
                    passwordExpirationTextField.color = "#000000"
                    Qt.inputMethod.hide()
                    mainWindow.showPrimaryNumpad(qmltextPasswordExpiration, qmltextDays, 0, 0, 365, passwordExpirationTextField.text)
                }
            }
        }
        Text{
            id:passwordExpirationDays
            y: parent.height * 0.48571
            text: qmltextDays
            anchors.left: passwordExpirationTextField.right
            anchors.leftMargin: 25
            font.family: Style.regular.name
            font.pixelSize: Math.round(10 * Style.scaleHint)
            color: Style.blackFontColor
        }
    }
    Rectangle{
        id:autoLoginRect
        width: Math.round(240 * Style.scaleHint)
        height: Math.round(52 * Style.scaleHint)
        color:Style.contentBackgroundColor
        anchors.top:parent.top
        anchors.topMargin: Math.round(45 * Style.scaleHint)
        anchors.left:passwordExpirationRect.right
        anchors.leftMargin: Math.round(22 * Style.scaleHint)
        Text{
            id:autoLogintext
            text: qmltextAutoLogin
            anchors.top:parent.top
            anchors.topMargin:Math.round(3 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(6 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }
        BransonSwitch{
            id:autoLoginEnableSwitch
            anchors.top:autoLogintext.bottom
            anchors.topMargin:Math.round(7.5 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(8 * Style.scaleHint)
            rectWidth: Math.round(35 * Style.scaleHint)
            rectHeight: Math.round(12 * Style.scaleHint)
            maxWidth: Math.round(17 * Style.scaleHint)
            maxHeight: Math.round(17 * Style.scaleHint)
            checked:GlobalUserSetting.AutoLoginStatus
            onCheckedChanged:
            {
                if(GlobalUserSetting.AuthorityCheck === false && autoLoginEnableSwitch.checked)
                {
                    autoLoginEnableSwitch.checked = false
                    textHeader.text = qmltextWarning
                    dailogMsg.text = qmltextAuthCheckMsg
                    userSettingPopup.open()
                }
                if(modelListSize === 0 && autoLoginEnableSwitch.checked)
                {
                    autoLoginEnableSwitch.checked = false
                    textHeader.text = qmltextWarning
                    dailogMsg.text = qmltextOperLevelUserMsg
                    userSettingPopup.open()
                }
                if(autoLoginEnableSwitch.checked === false)
                {
                    autoLoginComboBox.currentIndex = -1
                }
            }
        }
        BransonComboBox{
            id:autoLoginComboBox
            currentIndex: modelCurrentIndex
            enabled: autoLoginEnableSwitch.checked
            anchors.verticalCenter: autoLoginEnableSwitch.verticalCenter
            anchors.left:autoLoginEnableSwitch.right
            anchors.leftMargin: Math.round(12 * Style.scaleHint)
            minWidth: Math.round(175 * Style.scaleHint)
            minHeight: Math.round(25 * Style.scaleHint)
            textFontSize :Math.round(12* Style.scaleHint)
            model:comboBoxModel
            onCurrentIndexChanged: {
                if((currentIndex < 0) && (autoLoginEnableSwitch.checked))
                {
                    autoLoginComboBox.currentIndex = modelCurrentIndex
                }
                if(currentIndex >= 0)
                {
                    modelCurrentIndex = currentIndex
                }
            }
        }
    }

    Rectangle{
        id:idleTimeLogoutRect
        width: Math.round(260 * Style.scaleHint)
        height: Math.round(52 * Style.scaleHint)
        color:Style.contentBackgroundColor
        anchors.top:passwordExpirationRect.bottom
        anchors.topMargin: Math.round(16 * Style.scaleHint)
        anchors.left:parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        Text{
            id:idleTimeLogouttext
            text: qmltextIdleTimeLogOut
            anchors.top:parent.top
            anchors.topMargin:Math.round(6 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(6 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)* 0.90
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            color: Style.blackFontColor
        }
        Image {
            id: idleTimeLogoutInfo
            source: "qrc:/Images/Info_icon.svg"
            width: parent.width*0.06
            height: parent.width*0.06
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.03
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        TextField{
            id:idleTimeLogoutTextField
            width: Math.round(170 * Style.scaleHint)
            height: Math.round(21 * Style.scaleHint)
            anchors.top: idleTimeLogouttext.bottom
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left:idleTimeLogouttext.left
            mouseSelectionMode: TextInput.SelectCharacters
            font.pixelSize: Math.round(12 * Style.scaleHint)
            font.family: Style.regular.name
            text:GlobalUserSetting.IdleTimeLogout
            background: Rectangle{
                anchors.fill: parent
                border.width: 1
                color: "transparent"
                radius: 8
                border.color: "#707070"
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    passwordExpirationTextField.focus = true
                    passwordExpirationTextField.color = "#000000"
                    Qt.inputMethod.hide()
                    if(GlobalUserSetting.AuthorityCheck === true)
                    {
                        mainWindow.showPrimaryNumpad(qmltextIdleTimeLogOut, qmltextMins, 0, 0, 60, idleTimeLogoutTextField.text)
                    }
                    else
                    {
                        textHeader.text = qmltextWarning
                        dailogMsg.text = qmltextAuthCheckMsg
                        userSettingPopup.open()
                    }
                }
            }
        }
        Text{
            id:idleTimeLogoutMins
            y: parent.height * 0.48571
            text: qmltextMins
            anchors.left: idleTimeLogoutTextField.right
            anchors.leftMargin: 25
            font.family: Style.regular.name
            font.pixelSize: Math.round(11 * Style.scaleHint)
            color: Style.blackFontColor
        }
    }
    Rectangle
    {
        id:lockOutTimeRect
        width: Math.round(260 * Style.scaleHint)
        height: Math.round(52 * Style.scaleHint)
        color:Style.contentBackgroundColor
        anchors.top:idleTimeLogoutRect.bottom
        anchors.topMargin: Math.round(16 * Style.scaleHint)
        anchors.left:parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        Text{
            id:lockOutTimetext
            text: qmltextLockOutTime
            anchors.top:parent.top
            anchors.topMargin:Math.round(6 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: Math.round(6 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            color: Style.blackFontColor
        }
        Image {
            id: lockOutTimeInfo
            source: "qrc:/Images/Info_icon.svg"
            width: parent.width*0.06
            height: parent.width*0.06
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.03
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        TextField{
            id:lockOutTimeTextField
            width: Math.round(170 * Style.scaleHint)
            height: Math.round(21 * Style.scaleHint)
            anchors.top: lockOutTimetext.bottom
            anchors.topMargin: Math.round(2 * Style.scaleHint)
            anchors.left:lockOutTimetext.left
            mouseSelectionMode: TextInput.SelectCharacters
            font.pixelSize: Math.round(12 * Style.scaleHint)
            font.family: Style.regular.name
            text:GlobalUserSetting.LockOutTime
            background: Rectangle{
                anchors.fill: parent
                border.width: 1
                color: "transparent"
                radius: 8
                border.color: "#707070"
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    lockOutTimeTextField.focus = true
                    lockOutTimeTextField.color = "#000000"
                    Qt.inputMethod.hide()
                    mainWindow.showPrimaryNumpad(qmltextLockOutTime, qmltextMins, 0, 15, 43200, lockOutTimeTextField.text)
                }
            }
        }
        Text{
            id:lockOutTimeInMins
            y: parent.height * 0.48571
            text: qmltextMins
            anchors.left: lockOutTimeTextField.right
            anchors.leftMargin: 25
            font.family: Style.regular.name
            font.pixelSize: Math.round(11 * Style.scaleHint)
            color: Style.blackFontColor
        }
    }
    BransonPrimaryButton{
        id: resetToDefalutButton
        anchors.left: parent.left
        anchors.leftMargin:Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(140 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextResetToDefault
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked: {
            isResetToDefaultBtnClicked = true
            GlobalUserSetting.resetToDefaultRequest()
        }
    }
    BransonPrimaryButton{
        id: saveButton
        anchors.left: resetToDefalutButton.right
        anchors.leftMargin:Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(15 * Style.scaleHint)
        width: Math.round(90 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextSave
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            if(autoLoginEnableSwitch.checked)
            {
                if(autoLoginComboBox.currentText === "")
                {
                    textHeader.text = qmltextWarning
                    dailogMsg.text = qmltextAutoLoginMsg
                    userSettingPopup.open()
                }
                else
                {
                    GlobalUserSetting.setAutoLogin(autoLoginEnableSwitch.checked, autoLoginComboBox.currentText)
                    GlobalUserSetting.saveRequest()
                }
            }
            else
            {
                GlobalUserSetting.setAutoLogin(autoLoginEnableSwitch.checked, autoLoginComboBox.currentText)
                GlobalUserSetting.saveRequest()
            }
        }
    }
}

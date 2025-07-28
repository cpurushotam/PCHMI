/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

Branson System Configuration Service Screen

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
import "./../System_screens"
Item {
    id: bransonSystemConfItem
    property string qmltextSerialNumber:           "Serial Number"
    property string qmltextSytemSerNum:            "System Serial Number"
    property string qmltextPowerSupSerNum:         "Power Supply Serial Number"
    property string qmltextActuatorSerNum:         "Actuator Serial Number"
    property string qmltextCancel:                 "CANCEL"
    property string qmltextSave:                   "SAVE"
    property string qmltextConfLabel:              "Confirmation"
    property string qmltextKeyWarningLabel:        "Warning"
    property string qmltextSaveMsg:                "System Configuration saved successfully"
    property string qmltextErrorMsg:               "Fail to save System Configuration"
    property string qmltextEmptySystemMsg:         "System Serial Number is empty"
    property string qmltextEmptyPowerMsg:          "Power Supply Serial Number is empty"
    property string qmltextEmptyActMsg:            "Actuator Serial Number is empty"

    property bool isSysFieldEmpty: false
    property bool isPSFieldEmpty: false
    property bool isActFieldEmpty: false
    property string sytSerialNumber: ""
    property string psSerialNumber: ""
    property string actSerialNumber: ""

    property var qmlTextArray:[qmltextSerialNumber,qmltextSytemSerNum,qmltextPowerSupSerNum, qmltextActuatorSerNum,
                qmltextCancel, qmltextSave, qmltextConfLabel, qmltextKeyWarningLabel,qmltextSaveMsg, qmltextErrorMsg,
                qmltextEmptySystemMsg, qmltextEmptyPowerMsg, qmltextEmptyActMsg]

    QtObject
    {
        id: textEnum
        readonly property int textSerialNumberIdx             : 0
        readonly property int textSytemSerNumIdx              : 1
        readonly property int textPowerSupSerNumIdx           : 2
        readonly property int textActuatorSerNumIdx           : 3
        readonly property int textCancelIdx                   : 4
        readonly property int textSaveIdx                     : 5
        readonly property int textConfLabelIdx                : 6
        readonly property int textKeyWarningLabelIdx          : 7
        readonly property int textSaveMsgIdx                  : 8
        readonly property int textErrorMsgIdx                 : 9
        readonly property int textEmptySystemMsgIdx           :10
        readonly property int textEmptyPowerMsgIdx            :11
        readonly property int textEmptyActMsgIdx              :12
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.BRANSON_SYSTEM_CONFIGURATION, qmlTextArray)
        qmltextSerialNumber = qmlTextArray[textEnum.textSerialNumberIdx]
        qmltextSytemSerNum = qmlTextArray[textEnum.textSytemSerNumIdx]
        qmltextPowerSupSerNum = qmlTextArray[textEnum.textPowerSupSerNumIdx]
        qmltextActuatorSerNum = qmlTextArray[textEnum.textActuatorSerNumIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextConfLabel = qmlTextArray[textEnum.textConfLabelIdx]
        qmltextKeyWarningLabel = qmlTextArray[textEnum.textKeyWarningLabelIdx]
        qmltextSaveMsg = qmlTextArray[textEnum.textSaveMsgIdx]
        qmltextErrorMsg = qmlTextArray[textEnum.textErrorMsgIdx]
        qmltextEmptySystemMsg = qmlTextArray[textEnum.textEmptySystemMsgIdx]
        qmltextEmptyPowerMsg = qmlTextArray[textEnum.textEmptyPowerMsgIdx]
        qmltextEmptyActMsg = qmlTextArray[textEnum.textEmptyActMsgIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections {
        target: BransonSystConfgService
        function onBransonSystemConfigurationErrorCodeUpdated()
        {
            var errorode = BransonSystConfgService.UpdatedErrorCode
            if(errorode == 2)
            {
                systemPopUpMsg.qmltextLabel = qmltextConfLabel
                systemPopUpMsg.qmltextWarningDialog = qmltextSaveMsg
                systemPopUpMsg.visible = true
            }
            else
            {
                systemPopUpMsg.qmltextLabel = qmltextKeyWarningLabel
                systemPopUpMsg.qmltextWarningDialog = qmltextErrorMsg
                systemPopUpMsg.visible = true
            }

        }
        function onBransonSystemConfigurationChanged()
        {
            systemSerialNumTextField.text = BransonSystConfgService.MachineSerialNumber
            powerSupplySerialNumTextField.text = BransonSystConfgService.PowerSupplySerialNumber
            actuatorSerialNumTextField.text = BransonSystConfgService.ActuatorSerialNumber
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.BRANSON_SYSTEM_CONFIGURATION
        inputPanelKeyBoard.visible = false
    }

    BransonPopup
    {
        id:systemPopUpMsg
        onOKButtonClicked:
        {
            systemPopUpMsg.visible = false
            systemPopUpMsg.qmltextLabel = qmltextKeyWarningLabel
        }
    }

    Rectangle
    {
        id:machineRect
        height: parent.height
        width: mainWindow.showWidth * 0.70
        anchors.top:parent.top
        anchors.left:parent.left
        color:Style.contentBackgroundColor
        MouseArea {
                id: screenMouseArea
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    inputPanelKeyBoard.visible = false;
                }
            }

            InputPanel {
                id: inputPanelKeyBoard
                z: 1
                x: 0
                height: mainWindow.showHeight * 0.40
                width: mainWindow.showWidth * 0.60
                anchors.bottom: parent.bottom
                visible: Qt.inputMethod.visible
            }
        Text {
            id:serailNumText
            text: qmltextSerialNumber
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            anchors.top:parent.top
            anchors.topMargin:parent.height * 0.06
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.07
            color: "#333333"
        }
        Flickable
        {
            id:bransonServiceFlick
            flickableDirection: Flickable.VerticalFlick
            width: parent.width
            height: parent.height
            anchors.top:serailNumText.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left:parent.left
            anchors.leftMargin: parent.width * 0.07
            flickDeceleration: 10000
            contentHeight: true ? height* 3.4: height* 1.9
            clip: true
            Column
            {
                id:serialNumColumn
                spacing: Math.round(10 * Style.scaleHint)

                Rectangle
                {
                    id:powerSupplySerialNumRect
                    width: Math.round(290 * Style.scaleHint)
                    height: Math.round(54 * Style.scaleHint)
                    color:Style.backgroundColor
                    Text{
                        id:powerSupplySerNumText
                        text: qmltextPowerSupSerNum
                        anchors.top:parent.top
                        anchors.topMargin:Math.round(2 * Style.scaleHint)
                        anchors.left:parent.left
                        anchors.leftMargin: Math.round(6 * Style.scaleHint)
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.92
                        font.family: Style.regular.name
                        color: Style.blackFontColor
                        font.weight : Font.DemiBold
                    }
                    Image {
                        id: powerSupplySerialNumInfoImg
                        source: "qrc:/Images/Info_icon.svg"
                        width: parent.width*0.075
                        height: parent.width*0.075
                        anchors.top: parent.top
                        anchors.topMargin: parent.height*0.1
                        anchors.right: parent.right
                        anchors.rightMargin: parent.width*0.03
                        MouseArea{
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                    BransonLineEdit{
                        id:powerSupplySerialNumTextField
                        width: Math.round(210 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        anchors.top: powerSupplySerNumText.bottom
                        anchors.topMargin: Math.round(2 * Style.scaleHint)
                        anchors.left:powerSupplySerNumText.left
                        mouseSelectionMode: TextInput.SelectCharacters
                        font.pixelSize: Math.round(12 * Style.scaleHint)
                        font.family: Style.regular.name
                        echoMode: TextInput.Normal
                        text:BransonSystConfgService.PowerSupplySerialNumber
                        background: Rectangle{
                            anchors.fill: parent
                            border.width: 1
                            color: "#ffffff"
                            radius: Math.round(5 * Style.scaleHint)
                            border.color: "#707070"
                        }
                        onActiveFocusChanged:
                        {
                            if(activeFocus)
                            {
                                powerSupplySerialNumTextField.focus = true
                                powerSupplySerialNumTextField.color = "#000000"
                                Qt.inputMethod.hide()
                                inputPanelKeyBoard.visible = true
                            }
                            else
                            {                               
                                inputPanelKeyBoard.visible = false
                            }
                        }                       
                    }
                }
                Rectangle
                {
                    id:actuatorRect
                    width: Math.round(290 * Style.scaleHint)
                    height: Math.round(54 * Style.scaleHint)
                    color:Style.backgroundColor
                    Text{
                        id:actuatorSerNumText
                        text: qmltextActuatorSerNum
                        anchors.top:parent.top
                        anchors.topMargin:Math.round(2 * Style.scaleHint)
                        anchors.left:parent.left
                        anchors.leftMargin: Math.round(6 * Style.scaleHint)
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.90
                        font.family: Style.regular.name
                        color: Style.blackFontColor
                        font.weight : Font.DemiBold
                    }
                    Image {
                        id: actuatorSerialNumInfoImg
                        source: "qrc:/Images/Info_icon.svg"
                        width: parent.width*0.075
                        height: parent.width*0.075
                        anchors.top: parent.top
                        anchors.topMargin: parent.height*0.1
                        anchors.right: parent.right
                        anchors.rightMargin: parent.width*0.03
                        MouseArea{
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                    BransonLineEdit{
                        id:actuatorSerialNumTextField
                        width: Math.round(210 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        anchors.top: actuatorSerNumText.bottom
                        anchors.topMargin: Math.round(2 * Style.scaleHint)
                        anchors.left:actuatorSerNumText.left
                        mouseSelectionMode: TextInput.SelectCharacters
                        font.pixelSize: Math.round(12 * Style.scaleHint)
                        font.family: Style.regular.name
                        echoMode: TextInput.Normal
                        text:BransonSystConfgService.ActuatorSerialNumber
                        background: Rectangle{
                            anchors.fill: parent
                            border.width: 1
                            color: "#ffffff"
                            radius: Math.round(5 * Style.scaleHint)
                            border.color: "#707070"
                        }
                        onActiveFocusChanged:
                        {
                            if(activeFocus)
                            {
                                actuatorSerialNumTextField.focus = true
                                actuatorSerialNumTextField.color = "#000000"
                                Qt.inputMethod.hide()
                                inputPanelKeyBoard.visible = true
                            }
                            else
                            {                               
                                inputPanelKeyBoard.visible = false
                            }
                        }
                       
                    }
                }
            }
        }
        Row
        {
            spacing: 15
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.22
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(20 * Style.scaleHint)
            BransonPrimaryButton{
                id: cancelButton
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: qmltextCancel
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.cancelButtonTextColor
                onClicked: {
                    isSysFieldEmpty = false
                    isPSFieldEmpty = false
                    isActFieldEmpty = false
                    systemSerialNumTextField.text = BransonSystConfgService.MachineSerialNumber
                    powerSupplySerialNumTextField.text = BransonSystConfgService.PowerSupplySerialNumber
                    actuatorSerialNumTextField.text = BransonSystConfgService.ActuatorSerialNumber
                }
            }
            BransonPrimaryButton{
                id: saveButton
                width: Math.round(90 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint)
                text: qmltextSave
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked: {
                    inputPanelKeyBoard.visible = false
                    var emptyFlag = false
                     if(powerSupplySerialNumTextField.text === "")
                    {
                        emptyFlag = true
                        systemPopUpMsg.qmltextLabel = qmltextKeyWarningLabel
                        systemPopUpMsg.qmltextWarningDialog = qmltextEmptyPowerMsg
                        systemPopUpMsg.visible = true
                    }
                    else if(actuatorSerialNumTextField.text === "")
                    {
                        emptyFlag = true
                        systemPopUpMsg.qmltextLabel = qmltextKeyWarningLabel
                        systemPopUpMsg.qmltextWarningDialog = qmltextEmptyActMsg
                        systemPopUpMsg.visible = true
                    }
                    if(emptyFlag === false)
                    {
                        BransonSystConfgService.updatePowerSupplySerialNumber(powerSupplySerialNumTextField.text)
                        BransonSystConfgService.updateActuatorSerialNumber(actuatorSerialNumTextField.text)
                        BransonSystConfgService.saveRequest()
                    }
                }
            }
        }
    }
}

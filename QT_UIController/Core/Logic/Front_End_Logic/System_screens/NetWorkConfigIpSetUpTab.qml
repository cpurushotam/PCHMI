/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Network Configuration IPSETUP Screen related QML implemetation.


 **********************************************************************************************************/
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick 2.0
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Window 2.12
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"

Item {
    id:networkConfigurationItem

    property string qmltextConfigCommun:             "Configuration - Communication :"
    property string qmltextIPSetUp:                  "IP SETUP"
    property string qmltextStaticIP:                 "STATIC IP"
    property string qmltextDHCPClient:               "DHCP CLIENT"
    property string qmltextIPAddress:                "IP Address"
    property string qmltextSubnetMask:               "Subnet Mask"
    property string qmltexDefaultGateway:            "Default Gateway"
    property string qmltextDefaultBtn:               "RESET TO DEFAULT"
    property string qmltextCancelBtn:                "CANCEL"
    property string qmltextSaveBtn:                  "SAVE"
    property string qmltextEnterDigit:               "Enter Digit Only"

    property string qmltextConfLabel:                "Confirmation"
    property string qmltextWarningLabel:             "Warning"
    property string qmltextEmptyMsg:                 "Please Make Sure All Text Inputs are Filled"


    property string qmlTextNote: "Note : Do not enter IP Address in the range of '192.168.1'."
    readonly property int ethernetStaticIPEnabled        : 0
    readonly property int ethernetDHCPClientEnabled      : 1

    property bool isInputTextEmpty :false
    property string ethernetIPAdress : ""
    property string ethernetSubnetMask : ""
    property string ethernetDefaultGateway : ""

    property var qmlTextArray:[qmltextConfigCommun,qmltextIPSetUp,qmltextStaticIP,qmltextDHCPClient,qmltextIPAddress,
                             qmltextSubnetMask,qmltexDefaultGateway,qmltextDefaultBtn,qmltextCancelBtn,qmltextSaveBtn,qmltextEnterDigit,qmltextConfLabel,
                            qmltextWarningLabel,qmltextEmptyMsg]

    QtObject{
        id: textEnum
        readonly property int textConfigCommunIdx           : 0
        readonly property int textIPSetUpIdx                : 1
        readonly property int textInduEthernetIdx           : 2
        readonly property int textStaticIPIdx               : 3
        readonly property int textDHCPClientIdx             : 4
        readonly property int textIPAddressIdx              : 5
        readonly property int textSubnetMaskIdx             : 6
        readonly property int texDefaultGatewayIdx          : 7
        readonly property int textDefaultBtnIdx             : 11
        readonly property int textCancelBtnIdx              : 12
        readonly property int textSaveBtnIdx                : 13
        readonly property int textEnterDigitIdx             : 14
        readonly property int textEnterDomainNameIdx        : 15
        readonly property int textConfLabelIdx              : 16
        readonly property int textWarningLabelIdx           : 17
        readonly property int textSaveMsgIdx                : 18
        readonly property int textErrorMsgIdx               : 19
        readonly property int textEmptyMsgIdx               : 20
    }
    function updateLanguage(){
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION, qmlTextArray)
        qmltextConfigCommun = qmlTextArray[textEnum.textConfigCommunIdx]
        qmltextIPSetUp = qmlTextArray[textEnum.textIPSetUpIdx]
        qmltextStaticIP = qmlTextArray[textEnum.textStaticIPIdx]
        qmltextDHCPClient = qmlTextArray[textEnum.textDHCPClientIdx]
        qmltextIPAddress = qmlTextArray[textEnum.textIPAddressIdx]
        qmltextSubnetMask = qmlTextArray[textEnum.textSubnetMaskIdx]
        qmltexDefaultGateway = qmlTextArray[textEnum.texDefaultGatewayIdx]

        qmltextDefaultBtn = qmlTextArray[textEnum.textDefaultBtnIdx]
        qmltextCancelBtn = qmlTextArray[textEnum.textCancelBtnIdx]
        qmltextSaveBtn = qmlTextArray[textEnum.textSaveBtnIdx]
        qmltextEnterDigit = qmlTextArray[textEnum.textEnterDigitIdx]
        qmltextConfLabel = qmlTextArray[textEnum.textConfLabelIdx]
        qmltextWarningLabel = qmlTextArray[textEnum.textWarningLabelIdx]
        qmltextEmptyMsg = qmlTextArray[textEnum.textEmptyMsgIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    BransonPopup
    {
        id:ipConfigPopUpMsg
        rectleftMargin:Math.round(230 * Style.scaleHint)
        onOKButtonClicked:
        {
            ipConfigPopUpMsg.visible = false
            ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
        }
    }

    function networkConfigurationDataChanged()
    {

        if(NetworkConfiguration.EthernetIPConfig)
        {
            staticcIPRadioButton.checked = true
        }
        else
        {
            dhcpClientRadioButton.checked = true
        }



        for(let x=0; x<ipSetupRepeater.count; x++)
        {
            let item = ipSetupRepeater.itemAt(x)
            if(item)
            {
                let textField = item.children[1]
                if(textField)
                {
                    if(x === 0)
                    {
                        textField.text = NetworkConfiguration.EthernetIPAdress
                        ethernetIPAdress = NetworkConfiguration.EthernetIPAdress
                    }
                    else if(x === 1)
                    {
                        textField.text = NetworkConfiguration.EthernetSubnetMask
                        ethernetSubnetMask = NetworkConfiguration.EthernetSubnetMask
                    }
                    else if(x === 2)
                    {
                        textField.text = NetworkConfiguration.EthernetDefaultGateway
                        ethernetDefaultGateway = NetworkConfiguration.EthernetDefaultGateway
                    }
                }
            }
        }
    }


    Connections
    {
        target: NetworkConfiguration
        function onNetworkConfigurationDataChanged()
        {
           networkConfigurationDataChanged()
        }
    }


    Connections
    {
        target: NetworkConfiguration
        function onNetworkConfigurationErrorCodeUpdated()
        {
            var errorCode = NetworkConfiguration.getNetworkConfigUpdateResult()
            if(errorCode === 1)
            {
                ipConfigPopUpMsg.qmltextLabel = qmltextConfLabel
                ipConfigPopUpMsg.visible = false
            }
            else
            {
                ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
                ipConfigPopUpMsg.visible = true
                networkConfigurationDataChanged()
            }
        }
    }

    Component.onCompleted:
    {
        updateLanguage();
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION
        networkConfigurationDataChanged()
        inputPanelKeyBoard.visible = false
    }


    Rectangle {
        id:mainRectangle
        width: mainWindow.showWidth
        height: mainWindow.showHeight *0.65
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        color: Style.backgroundColor
        clip:true
        enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
        InputPanel {
            id: inputPanelKeyBoard
            z: 1
            x: 0
            height: parent.height //* 0.35
            width: parent.width //* 0.40
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            visible: Qt.inputMethod.visible
        }

        Text {
            id: configHeaderText
            anchors.top:parent.top
            anchors.topMargin: parent.height * 0.04
            anchors.left:parent.left
            anchors.leftMargin:parent.width * 0.03
            text: qmltextConfigCommun
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: Style.regular.name
            font.weight : Font.DemiBold
            color:"#000000"
        }

        Item {
            id: networkConfigItem
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.03
            anchors.top: configHeaderText.bottom
            anchors.topMargin: parent.height*0.01
            height: parent.height * 0.78
            width: parent.width * 0.95
            Row
            {
                id:networkConfigRow
                anchors.fill: parent
                spacing: parent.width * 0.03

                //left IP Setup section
                Rectangle
                {
                    id:ipSetupRectangle
                    width: parent.width * 0.36
                    height:parent.height
                    color: "transparent"
                    Text
                    {
                        id:ipsetupText
                        text: qmltextIPSetUp
                        anchors.top: parent.top
                        anchors.topMargin: parent.width * 0.015
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                        font.family: Style.regular.name
                        font.weight : Font.DemiBold
                        color: Style.textFontColor
                    }
                    Rectangle
                    {
                        id:ipSetupUnderLine
                        width: parent.width
                        height: parent.height * 0.003
                        anchors.top:ipsetupText.bottom
                        anchors.topMargin:  parent.width * 0.015
                        color: Style.placeHolderTextColor
                    }
                    RowLayout
                    {
                        id:ipSetupRadiobutton
                        spacing: parent.width * 0.30
                        anchors.top: ipSetupUnderLine.bottom
                        anchors.topMargin: parent.height * 0.035
                        BransonRadioButton
                        {
                            id:staticcIPRadioButton
                            circleSize:Math.round(18 * Style.scaleHint)
                            labelText: qmltextStaticIP
                            checked: NetworkConfiguration.EthernetIPConfig ? true:false
                            onCheckedChanged:
                            {

                            }
                        }
                        BransonRadioButton
                        {
                            id:dhcpClientRadioButton
                            circleSize:Math.round(18 * Style.scaleHint)
                            offColor:Style.blackFontColor
                            labelText:qmltextDHCPClient
                            checked:NetworkConfiguration.EthernetIPConfig ? false : true
                            onCheckedChanged:
                            {
                                if(checked === true)
                                {
                                    inputPanelKeyBoard.visible = false
                                }
                            }
                        }
                    }
                    Item {
                        id: ipSetupRowItem
                        anchors.top: ipSetupRadiobutton.bottom
                        anchors.topMargin: parent.height * 0.02
                        width: parent.width
                        height: parent.height * 0.75
                        Flickable
                        {
                            id:ipSetupFlick
                            flickableDirection: Flickable.VerticalFlick
                            width: parent.width
                            height: parent.height
                            flickDeceleration: 10000
                            contentHeight: true ? height* 2.0: height* 1.3
                            clip: true
                            Column
                            {
                                id:ipSetupColumn
                                spacing: Math.round(10.2 * Style.scaleHint)
                                anchors.fill: parent
                                Repeater
                                {
                                    id:ipSetupRepeater
                                    model: [qmltextIPAddress, qmltextSubnetMask, qmltexDefaultGateway]
                                    Rectangle
                                    {
                                        id:ipSetUpRect
                                        width: parent.width
                                        height: Math.round(50 * Style.scaleHint)
                                        color: Style.contentBackgroundColor
                                        Text {
                                            id: ipSetupParamName
                                            text:modelData
                                            anchors.top: parent.top
                                            anchors.topMargin: parent.height * 0.02
                                            anchors.left: parent.left
                                            anchors.leftMargin: parent.width * 0.03
                                            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)* 0.90
                                            font.family: Style.regular.name
                                            font.weight : Font.DemiBold
                                            color: Style.textFontColor
                                        }
                                        BransonLineEdit
                                        {
                                            id:ipSetupParamInputText
                                            width:parent.width*0.90
                                            height:parent.height * 0.5
                                            anchors.top :ipSetupParamName.bottom
                                            anchors.topMargin: parent.height * 0.02
                                            anchors.left :parent.left
                                            anchors.leftMargin: parent.width * 0.03
                                            focus: false
                                            font.family: Style.regular.name
                                            font.weight :470
                                            font.pixelSize: Math.round(10 * Style.scaleHint)
                                            placeholderText: qmltextEnterDigit
                                            selectByMouse: true
                                            background: Rectangle
                                            {
                                                color: "#FFFFFF"
                                                radius: Math.round(5 * Style.scaleHint)
                                                border.color: Style.frameBorderColor
                                                border.width: 1
                                            }

                                            onTextChanged:{
                                            }
                                            validator: RegularExpressionValidator
                                            {
                                                regularExpression: /^(?!192\.168\.1\.)(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)$/
                                            }
                                            onActiveFocusChanged:
                                            {
                                                if(activeFocus)
                                                {
                                                    ipSetupParamInputText.focus = true
                                                    ipSetupParamInputText.color = "#000000"
                                                    inputPanelKeyBoard.visible = true
                                                }
                                                else
                                                {
                                                    ipSetupParamInputText.focus = false
                                                    inputPanelKeyBoard.visible = false
                                                    if(ipSetupParamInputText.text !== "")
                                                    {
                                                        if(index === 0)
                                                        {
                                                            ethernetIPAdress = ipSetupParamInputText.text
                                                        }
                                                        else if(index === 1)
                                                        {
                                                            ethernetSubnetMask = ipSetupParamInputText.text
                                                        }
                                                        else if(index === 2)
                                                        {
                                                            ethernetDefaultGateway = ipSetupParamInputText.text
                                                        }
                                                    }
                                                    else
                                                    {
                                                        isInputTextEmpty = true
                                                    }
                                                }
                                                if(dhcpClientRadioButton.checked === true)
                                                {
                                                    inputPanelKeyBoard.visible = false
                                                    ipSetupParamInputText.focus = false
                                                }
                                            }
                                            Component.onCompleted:
                                            {
                                                if(index=== 0)
                                                {
                                                    ipSetupParamInputText.text = NetworkConfiguration.EthernetIPAdress
                                                }
                                                else if(index === 1)
                                                {
                                                    ipSetupParamInputText.text = NetworkConfiguration.EthernetSubnetMask
                                                }
                                                else if(index === 2)
                                                {
                                                    ipSetupParamInputText.text = NetworkConfiguration.EthernetDefaultGateway
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }


                    Item
                    {
                        id: induEthernetRowItem2
                        anchors.top: ipSetupRadiobutton.bottom
                        anchors.topMargin: parent.height * 0.02
                        anchors.left: ipSetupRowItem.right
                        anchors.leftMargin: parent.width * 0.02
                        anchors.right: parent.right
                        height: mainRectangle.height * 0.3
                        Rectangle{
                            id:noterect
                            width: parent.width *3
                            height: Math.round(50 * Style.scaleHint)
                             color: Style.contentBackgroundColor
                            Text
                            {
                                id: noteTextDelegate
                                width: Math.round(150 * Style.scaleHint)
                                anchors.left: parent.left
                                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                                anchors.verticalCenter: parent.verticalCenter
                                wrapMode: Text.WordWrap
                                text:qmlTextNote
                                font.pixelSize: Math.round(Style.style3 * Style.scaleHint) * 0.90
                            }
                        }
                    }

                }

            }
        }

        BransonPrimaryButton
        {
            id:resetToDefaultButton
            width: parent.width * 0.14
            height: Math.round(25 * Style.scaleHint)
            anchors.top:networkConfigItem.bottom
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.03
            fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
            text: qmltextDefaultBtn
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            buttonColor: Style.cancelButtonTextColor
            onClicked:
            {
                NetworkConfiguration.resetToDefaultRequest()
            }
        }
        RowLayout
        {
            id:btnRow
            spacing: parent.width * 0.02
            anchors.top:networkConfigItem.bottom
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.03

            BransonPrimaryButton
            {
                id:cancelButton
                implicitWidth: Math.round(80 * Style.scaleHint)
                implicitHeight: Math.round(25 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
                text: qmltextCancelBtn
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.cancelButtonTextColor
                onClicked:
                {
                    NetworkConfiguration.cancelRequest()
                    networkConfigurationDataChanged()
                }
            }

            BransonPrimaryButton
            {
                id:saveButton
                implicitWidth: Math.round(80 * Style.scaleHint)
                implicitHeight: Math.round(25 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
                text: qmltextSaveBtn
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked:
                {
                    if(staticcIPRadioButton.checked)
                    {
                        NetworkConfiguration.updateEthernetIPConfigStatus(ethernetStaticIPEnabled)
                    }
                    else if(dhcpClientRadioButton.checked)
                    {
                        NetworkConfiguration.updateEthernetIPConfigStatus(ethernetDHCPClientEnabled)
                    }


                    if(isInputTextEmpty === true)
                    {
                        ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
                        ipConfigPopUpMsg.qmltextWarningDialog = qmltextEmptyMsg
                        ipConfigPopUpMsg.visible = true
                        isInputTextEmpty = false
                    }
                    else
                    {
                        NetworkConfiguration.updateEthernetIPSetup(ethernetIPAdress,ethernetSubnetMask,ethernetDefaultGateway)
                        NetworkConfiguration.saveRequest()
                    }
                }
            }
        }
    }
}

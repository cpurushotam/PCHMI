/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Network Configuration Screen

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
import Com.Branson.SystemTypeDef 1.0
import QtQuick.Window 2.12
import "./../Common_Logic"
import "./../System_screens"

Item {
    id:networkConfigurationItem

    property string qmltextConfigCommun:             "Configuration - Communication :"
    property string qmltextInduEthernet:             "INDUSTRIAL ETHERNET"
    property string qmltextStaticIP:                 "STATIC IP"
    property string qmltextDHCPClient:               "DHCP CLIENT"
    property string qmltextIPAddress:                "IP Address"
    property string qmltextSubnetMask:               "Subnet Mask"
    property string qmltexDefaultGateway:            "Default Gateway"
    property string qmltextNameServer:               "Name Server"
    property string qmltextNameServer2:              "Name Server2"
    property string qmltextDomainName:               "Domain Name"
    property string qmltextDefaultBtn:               "RESET TO DEFAULT"
    property string qmltextCancelBtn:                "CANCEL"
    property string qmltextSaveBtn:                  "SAVE"
    property string qmltextEnterDigit:               "Enter Digit Only"
    property string qmltextEnterDomainName:          "Enter Domin Name"

    property string qmltextConfLabel:                "Confirmation"
    property string qmltextWarningLabel:             "Warning"
    property string qmltextSaveMsg:                  "Network Configuration saved successfully"
    property string qmltextErrorMsg:                 "Fail To Update Network Configuration"
    property string qmltextEmptyMsg:                 "Please Make Sure All Text Inputs are Filled"

    readonly property int indEthernetStaticIPEnabled        : 0
    readonly property int indEthernetDHCPClientEnabled      : 1

    property bool isInputTextEmpty :false

    property string induEthernetIPAdress : ""
    property string induEthernetSubnetMask : ""
    property string induEthernetDefaultGateway : ""

    property string nameServer : ""
    property string nameServer2 : ""
    property string domainName : ""

    property var qmlTextArray:[qmltextConfigCommun,qmltextInduEthernet,qmltextStaticIP,qmltextDHCPClient,qmltextIPAddress,
                             qmltextSubnetMask,qmltexDefaultGateway,qmltextNameServer,qmltextNameServer2,qmltextDomainName,
                            qmltextDefaultBtn,qmltextCancelBtn,qmltextSaveBtn,qmltextEnterDigit, qmltextEnterDomainName,qmltextConfLabel,
                            qmltextWarningLabel,qmltextSaveMsg,qmltextErrorMsg,qmltextEmptyMsg]

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
        readonly property int textNameServerIdx             : 8
        readonly property int textNameServer2Idx            : 9
        readonly property int textDomainNameIdx             : 10
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
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_ETHERNETIP, qmlTextArray)
        qmltextConfigCommun = qmlTextArray[textEnum.textConfigCommunIdx]
        qmltextInduEthernet = qmlTextArray[textEnum.textInduEthernetIdx]
        qmltextStaticIP = qmlTextArray[textEnum.textStaticIPIdx]
        qmltextDHCPClient = qmlTextArray[textEnum.textDHCPClientIdx]
        qmltextIPAddress = qmlTextArray[textEnum.textIPAddressIdx]
        qmltextSubnetMask = qmlTextArray[textEnum.textSubnetMaskIdx]
        qmltexDefaultGateway = qmlTextArray[textEnum.texDefaultGatewayIdx]
        qmltextNameServer = qmlTextArray[textEnum.textNameServerIdx]
        qmltextNameServer2 = qmlTextArray[textEnum.textNameServer2Idx]
        qmltextDomainName = qmlTextArray[textEnum.textDomainNameIdx]
        qmltextDefaultBtn = qmlTextArray[textEnum.textDefaultBtnIdx]
        qmltextCancelBtn = qmlTextArray[textEnum.textCancelBtnIdx]
        qmltextSaveBtn = qmlTextArray[textEnum.textSaveBtnIdx]
        qmltextEnterDigit = qmlTextArray[textEnum.textEnterDigitIdx]
        qmltextEnterDomainName = qmlTextArray[textEnum.textEnterDomainNameIdx]
        qmltextConfLabel = qmlTextArray[textEnum.textConfLabelIdx]
        qmltextWarningLabel = qmlTextArray[textEnum.textWarningLabelIdx]
        qmltextSaveMsg = qmlTextArray[textEnum.textSaveMsgIdx]
        qmltextErrorMsg = qmlTextArray[textEnum.textErrorMsgIdx]
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

        if(SystemNetworkConfigurationEthIp.InduEthernetIPConfig)
        {
            inEthStaticIPRadioButton.checked = true
        }
        else
        {
            inEthdhcpClientRadioButton.checked = true
        }
        for(let y=0; y<induEthernetRepeater.count; y++)
        {
            let induItem = induEthernetRepeater.itemAt(y)
            if(induItem)
            {
                let induTextField = induItem.children[1]
                if(induTextField)
                {
                    if(y === 0)
                    {
                        induTextField.text = SystemNetworkConfigurationEthIp.InduEthernetIPAdress
                        induEthernetIPAdress = SystemNetworkConfigurationEthIp.InduEthernetIPAdress
                    }
                    else if(y === 1)
                    {
                        induTextField.text = SystemNetworkConfigurationEthIp.InduEthernetSubnetMask
                        induEthernetSubnetMask = SystemNetworkConfigurationEthIp.InduEthernetSubnetMask
                    }
                    else if(y === 2)
                    {
                        induTextField.text = SystemNetworkConfigurationEthIp.InduEthernetDefaultGateway
                        induEthernetDefaultGateway = SystemNetworkConfigurationEthIp.InduEthernetDefaultGateway
                    }
                }
            }
        }

        for(let z=0; z<induEthernetRepeater2.count; z++)
        {
            let induItem1 = induEthernetRepeater2.itemAt(z)
            if(induItem1)
            {
                let induTextField1 = induItem1.children[1]
                if(induTextField1)
                {
                    if(z === 0)
                    {
                        induTextField1.text = SystemNetworkConfigurationEthIp.NameServer
                        nameServer = SystemNetworkConfigurationEthIp.NameServer
                    }
                    else if(z === 1)
                    {
                        induTextField1.text = SystemNetworkConfigurationEthIp.NameServer2
                        nameServer2 = SystemNetworkConfigurationEthIp.NameServer2
                    }
                    else if(z === 2)
                    {
                        induTextField1.text = SystemNetworkConfigurationEthIp.DomainName
                        domainName = SystemNetworkConfigurationEthIp.DomainName
                    }
                }
            }
        }
    }



    Connections
    {
        target: SystemNetworkConfigurationEthIp
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
            var errorCode = SystemNetworkConfigurationEthIp.getNetworkConfigUpdateResult()
            if(errorCode === 1)
            {
                ipConfigPopUpMsg.qmltextLabel = qmltextConfLabel
                ipConfigPopUpMsg.qmltextWarningDialog = qmltextSaveMsg
                ipConfigPopUpMsg.visible = true
            }
            else
            {
                ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
                ipConfigPopUpMsg.qmltextWarningDialog = qmltextErrorMsg
                ipConfigPopUpMsg.visible = true
                networkConfigurationDataChanged()
            }
        }
    }

    Component.onCompleted: {

        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_ETHERNETIP
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
        Image {
            id: ethernetIpImg
            source: "qrc:/Images/Ethernet_IP.svg"
            width: parent.width*0.15
            height: parent.height*0.06
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.04
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.01
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


                //Industrial Ethernet section
                Rectangle
                {
                    id:industrialEthernetRect
                    width: parent.width * 0.61
                    height:parent.height
                    color: "transparent"
                    Text
                    {
                        id:induEthernetText
                        text: qmltextInduEthernet
                        anchors.top: parent.top
                        anchors.topMargin: parent.height * 0.01
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                        font.family: Style.regular.name
                        font.weight : Font.DemiBold
                        color: Style.textFontColor
                    }
                    Rectangle
                    {
                        id:induEthernetTextUnderLine
                        width: parent.width
                        height: parent.height * 0.004
                        anchors.top:induEthernetText.bottom
                        anchors.topMargin:  parent.width * 0.013
                        color: Style.placeHolderTextColor
                    }
                    RowLayout
                    {
                        id:induEthernetRadiobutton
                        spacing: parent.width * 0.30
                        anchors.top: induEthernetTextUnderLine.bottom
                        anchors.topMargin: parent.height * 0.035
                        BransonRadioButton
                        {
                            id:inEthStaticIPRadioButton
                            circleSize:Math.round(18 * Style.scaleHint)
                            labelText: qmltextStaticIP
                            checked: SystemNetworkConfigurationEthIp.InduEthernetIPConfig ? true:false
                            onCheckedChanged:
                            {
                            }
                        }
                        BransonRadioButton
                        {
                            id:inEthdhcpClientRadioButton
                            circleSize:Math.round(18 * Style.scaleHint)
                            offColor:Style.blackFontColor
                            labelText:qmltextDHCPClient
                            checked:SystemNetworkConfigurationEthIp.InduEthernetIPConfig ? false : true
                            onCheckedChanged:
                            {
                                if(checked === true)
                                {
                                    inputPanelKeyBoard.visible = false
                                }
                            }
                        }
                    }

                    Item
                    {
                        id: induEthernetRowItem
                        anchors.top: induEthernetRadiobutton.bottom
                        anchors.topMargin: parent.height * 0.02
                        width: parent.width * 0.48
                        height: parent.height * 0.75
                        Flickable
                        {
                            id:induEthernetRowItemFlick
                            flickableDirection: Flickable.VerticalFlick
                            width: parent.width
                            height: parent.height
                            flickDeceleration: 10000
                            contentHeight: true ? height* 2.0: height* 1.3
                            boundsBehavior:Flickable.StopAtBounds
                            clip: true
                            Column
                            {
                                id:induEthernetColumn
                                spacing: Math.round(10.2 * Style.scaleHint)
                                anchors.fill: parent
                                Repeater
                                {
                                    id:induEthernetRepeater
                                    model: [qmltextIPAddress, qmltextSubnetMask, qmltexDefaultGateway]
                                    Rectangle
                                    {
                                        id:induEthernetRect
                                        width: parent.width
                                        height: Math.round(50 * Style.scaleHint)
                                        color: Style.contentBackgroundColor
                                        Text {
                                            id: induEthernetParamName
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
                                            id:induEthernetParamInputText
                                            width:parent.width*0.90
                                            height:parent.height * 0.5
                                            anchors.top :induEthernetParamName.bottom
                                            anchors.topMargin: parent.height * 0.02
                                            anchors.left :parent.left
                                            anchors.leftMargin: parent.width * 0.03
                                            font.family: Style.regular.name
                                            font.weight :470
                                            font.pixelSize: Math.round(10 * Style.scaleHint)
                                            placeholderText: qmltextEnterDigit
                                            enabled: true
                                            background: Rectangle
                                            {
                                                color: inEthdhcpClientRadioButton.checked ? Style.dialogBackgroundColor : "#FFFFFF"
                                                radius: Math.round(5 * Style.scaleHint)
                                                border.color: Style.frameBorderColor
                                                border.width: 1
                                            }
                                            focus: false
                                            text: ""
                                            selectByMouse: true
                                            validator: RegularExpressionValidator
                                            {
                                                regularExpression:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                                            }
                                            onActiveFocusChanged:
                                            {
                                                if(activeFocus)
                                                {
                                                    induEthernetParamInputText.focus = true
                                                    induEthernetParamInputText.color = "#000000"
                                                    inputPanelKeyBoard.visible = true
                                                }
                                                else
                                                {
                                                    induEthernetParamInputText.focus = false
                                                    inputPanelKeyBoard.visible = false
                                                    if(induEthernetParamInputText.text != "")
                                                    {
                                                        if(index === 0)
                                                        {
                                                            induEthernetIPAdress = induEthernetParamInputText.text
                                                        }
                                                        else if(index === 1)
                                                        {
                                                            induEthernetSubnetMask = induEthernetParamInputText.text
                                                        }
                                                        else if(index === 2)
                                                        {
                                                            induEthernetDefaultGateway = induEthernetParamInputText.text
                                                        }
                                                    }
                                                    else
                                                    {
                                                        isInputTextEmpty = true
                                                    }
                                                }
                                                if(inEthdhcpClientRadioButton.checked === true)
                                                {
                                                    inputPanelKeyBoard.visible = false
                                                    induEthernetParamInputText.focus = false
                                                }
                                            }

                                            Component.onCompleted:
                                            {
                                                if(index === 0)
                                                {
                                                    induEthernetParamInputText.text = "255.255.255.255"
                                                }
                                                else if(index === 1)
                                                {
                                                    induEthernetParamInputText.text = "255.255.255.255"
                                                }
                                                else if(index === 2)
                                                {
                                                    induEthernetParamInputText.text = "0.0.0.0"
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
                        anchors.top: induEthernetRadiobutton.bottom
                        anchors.topMargin: parent.height * 0.02
                        anchors.left: induEthernetRowItem.right
                        anchors.leftMargin: parent.width * 0.02
                        anchors.right: parent.right
                        height: parent.height * 0.75
                        Flickable
                        {
                            id:induEthernetRowItem2Flick
                            flickableDirection: Flickable.VerticalFlick
                            width: parent.width
                            height: parent.height
                            flickDeceleration: 10000
                            contentHeight: true ? height* 2.0: height* 1.3
                            boundsBehavior:Flickable.StopAtBounds
                            clip: true
                            Column
                            {
                                id:induEthernetColumn2
                                spacing: Math.round(10.2 * Style.scaleHint)
                                anchors.fill: parent
                                Repeater
                                {
                                    id:induEthernetRepeater2
                                    model: [qmltextNameServer, qmltextNameServer2, qmltextDomainName]
                                    Rectangle
                                    {
                                        id:induEthernetRect2
                                        width: parent.width
                                        height: Math.round(50 * Style.scaleHint)
                                        color: Style.contentBackgroundColor
                                        Text {
                                            id: induEthernetParamName2
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
                                            id:induEthernetParamInputText2
                                            width:parent.width*0.90
                                            height:parent.height * 0.5
                                            anchors.top :induEthernetParamName2.bottom
                                            anchors.topMargin: parent.height * 0.02
                                            anchors.left :parent.left
                                            anchors.leftMargin: parent.width * 0.03
                                            font.family: Style.regular.name
                                            font.weight :470
                                            font.pixelSize: Math.round(10 * Style.scaleHint)
                                            placeholderText: index !== 2 ? qmltextEnterDigit : qmltextEnterDomainName
                                            background: Rectangle
                                            {
                                                color: inEthdhcpClientRadioButton.checked ? Style.dialogBackgroundColor : "#FFFFFF"
                                                radius: Math.round(5 * Style.scaleHint)
                                                border.color: Style.frameBorderColor
                                                border.width: 1
                                            }
                                            focus: false
                                            text: ""
                                            selectByMouse: true
                                            validator: RegularExpressionValidator
                                            {


                                                regularExpression: (index !== 2) ? /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/ :
                                                                    /^[A-Za-z]+$/

                                            }
                                            onTextChanged: {

                                            }
                                            onActiveFocusChanged:
                                            {
                                                if(activeFocus)
                                                {
                                                    induEthernetParamInputText2.focus = true
                                                    induEthernetParamInputText2.color = "#000000"
                                                    inputPanelKeyBoard.visible = true
                                                }
                                                else
                                                {
                                                    induEthernetParamInputText2.focus = false
                                                    inputPanelKeyBoard.visible = false
                                                    if(induEthernetParamInputText2.text != "")
                                                    {
                                                        if(index === 0)
                                                        {
                                                            nameServer = induEthernetParamInputText2.text
                                                        }
                                                        else if(index === 1)
                                                        {
                                                            nameServer2 = induEthernetParamInputText2.text
                                                        }
                                                        else if(index === 2)
                                                        {
                                                            domainName = induEthernetParamInputText2.text
                                                        }
                                                    }
                                                    else
                                                    {
                                                        isInputTextEmpty = true
                                                    }
                                                }
                                                if(inEthdhcpClientRadioButton.checked === true)
                                                {
                                                    inputPanelKeyBoard.visible = false
                                                    induEthernetParamInputText2.focus = false
                                                }
                                            }
                                            Component.onCompleted:
                                            {
                                                if(index === 0)
                                                {
                                                    induEthernetParamInputText2.text = "0.0.0.0"
                                                }
                                                else if(index === 1)
                                                {
                                                    induEthernetParamInputText2.text = "0.0.0.0"
                                                }
                                                else if(index === 2)
                                                {
                                                    induEthernetParamInputText2.text = "Domain Test"
                                                }
                                            }
                                        }
                                    }
                                }
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
                SystemNetworkConfigurationEthIp.resetToDefaultRequest()
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
                    SystemNetworkConfigurationEthIp.cancelRequest()
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
                    if(inEthStaticIPRadioButton.checked)
                    {
                        SystemNetworkConfigurationEthIp.updateInduEthernetIPConfigStatus(indEthernetStaticIPEnabled)
                    }
                    else if(inEthdhcpClientRadioButton.checked)
                    {
                        SystemNetworkConfigurationEthIp.updateInduEthernetIPConfigStatus(indEthernetDHCPClientEnabled)
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
                        SystemNetworkConfigurationEthIp.updateIndustrialEthernetIP(induEthernetIPAdress,induEthernetSubnetMask,induEthernetDefaultGateway)
                        SystemNetworkConfigurationEthIp.updateIndustrialServerAndDomainName(nameServer,nameServer2,domainName)
                        SystemNetworkConfigurationEthIp.saveRequest()
                    }
                }
            }
        }
    }
}

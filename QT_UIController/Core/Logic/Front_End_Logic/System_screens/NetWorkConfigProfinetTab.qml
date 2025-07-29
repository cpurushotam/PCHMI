/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Network Configuration Profinet Screen related QML implenetation.

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
    property string qmltextProfinet:                 "PROFINET"
    property string qmltextIPAddress:                "IP Address"
    property string qmltextSubnetMask:               "Subnet Mask"
    property string qmltexDefaultGateway:            "Default Gateway"
    property string qmltexStationName:                "Station Name"

    property string qmltextDefaultBtn:               "RESET TO DEFAULT"
    property string qmltextCancelBtn:                "CANCEL"
    property string qmltextSaveBtn:                  "SAVE"
    property string qmltextEnterDigit:               "Enter Digit Only"

    property string qmltextConfLabel:                "Confirmation"
    property string qmltextWarningLabel:             "Warning"
    property string qmltextEmptyMsg:                 "Please Make Sure All Text Inputs are Filled"


    property bool isInputTextEmpty :false
    property string ipAddress : ""
    property string netMask : ""
    property string gateWay : ""
    property string stationName : ""



    property var qmlTextArray:[qmltextConfigCommun,qmltextIPAddress,
                             qmltextSubnetMask,qmltexDefaultGateway,
                            qmltextDefaultBtn,qmltextCancelBtn,qmltextSaveBtn,qmltextEnterDigit,qmltextConfLabel,
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
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_PROFINET, qmlTextArray)
        qmltextConfigCommun = qmlTextArray[textEnum.textConfigCommunIdx]
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
        id:ipConfigPopUpMsg
        rectleftMargin:Math.round(230 * Style.scaleHint)
        onOKButtonClicked:
        {
            ipConfigPopUpMsg.visible = false
            ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
        }
    }

    function networkConfigurationProfinetDataChanged()
    {
        for(let x=0; x<profinetRepeater.count; x++)
        {
            let item = profinetRepeater.itemAt(x)
            if(item)
            {
                let textField = item.children[1]
                if(textField)
                {
                    if(x === 0)
                    {
                        textField.text = SystemNetworkConfigurationProfinet.IpAddress
                        ipAddress = SystemNetworkConfigurationProfinet.IpAddress
                    }
                    else if(x === 1)
                    {
                        textField.text = SystemNetworkConfigurationProfinet.Netmask
                        netMask = SystemNetworkConfigurationProfinet.Netmask
                    }
                    else if(x === 2)
                    {
                        textField.text = SystemNetworkConfigurationProfinet.Gateway
                        gateWay = SystemNetworkConfigurationProfinet.Gateway
                    }
                    else if(x === 3)
                    {
                        textField.text = SystemNetworkConfigurationProfinet.StationName
                        stationName = SystemNetworkConfigurationProfinet.StationName
                    }
                }
            }
        }
    }

    Connections
    {
        target: SystemNetworkConfigurationProfinet
        function onProfinetConfigurationDataChanged()
        {
           networkConfigurationProfinetDataChanged()
        }
    }

    Component.onCompleted: {
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_PROFINET
        networkConfigurationProfinetDataChanged()
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

                //left Profinet  section
                Rectangle
                {
                    id:profinetRectangle
                    width: parent.width * 0.36
                    height:parent.height
                    color: "transparent"
                    Text
                    {
                        id:profinettext
                        text: qmltextProfinet
                        anchors.top: parent.top
                        anchors.topMargin: parent.width * 0.015
                        font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                        font.family: Style.regular.name
                        font.weight : Font.DemiBold
                        color: Style.textFontColor
                    }
                    Rectangle
                    {
                        id:profinetUnderLine
                        width: parent.width
                        height: parent.height * 0.003
                        anchors.top:profinettext.bottom
                        anchors.topMargin:  parent.width * 0.015
                        color: Style.placeHolderTextColor
                    }


                    Item {
                        id: ipSetupRowItem
                        anchors.top: profinetUnderLine.bottom
                        anchors.topMargin: parent.height * 0.02
                        width: parent.width
                        height: parent.height * 0.75
                        Flickable
                        {
                            id:profinetflick
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
                                    id:profinetRepeater
                                    model: [qmltextIPAddress, qmltextSubnetMask, qmltexDefaultGateway, qmltexStationName]
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
                                            id:profinetParamInputText
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
                                            validator: RegularExpressionValidator
                                            {

                                                regularExpression:  (index !== 3) ? /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/ :
                                                    /^[A-Za-z]+$/
                                            }

                                            onTextChanged: {

                                            }
                                            onActiveFocusChanged:
                                            {
                                                if(activeFocus)
                                                {
                                                    profinetParamInputText.focus = true
                                                    profinetParamInputText.color = "#000000"
                                                    inputPanelKeyBoard.visible = true
                                                }
                                                else
                                                {
                                                    profinetParamInputText.focus = false
                                                    inputPanelKeyBoard.visible = false
                                                    if(profinetParamInputText.text !== "")
                                                    {
                                                        if(index === 0)
                                                        {
                                                            ipAddress = profinetParamInputText.text
                                                        }
                                                        else if(index === 1)
                                                        {
                                                            netMask = profinetParamInputText.text
                                                        }
                                                        else if(index === 2)
                                                        {
                                                            gateWay = profinetParamInputText.text
                                                        }
                                                        else if(index == 3)
                                                        {
                                                            stationName = profinetParamInputText.text
                                                        }
                                                    }
                                                    else
                                                    {
                                                        isInputTextEmpty = true
                                                    }
                                                }

                                            }
                                            Component.onCompleted:
                                            {
                                                if(index=== 0)
                                                {
                                                    profinetParamInputText.text = SystemNetworkConfigurationProfinet.IpAddress
                                                }
                                                else if(index === 1)
                                                {
                                                    profinetParamInputText.text = SystemNetworkConfigurationProfinet.Netmask
                                                }
                                                else if(index === 2)
                                                {
                                                    profinetParamInputText.text = SystemNetworkConfigurationProfinet.Gateway
                                                }
                                                else if(index === 3)
                                                {
                                                    profinetParamInputText.text = SystemNetworkConfigurationProfinet.StationName
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
                SystemNetworkConfigurationProfinet.resetToDefaultRequest()
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
                    SystemNetworkConfigurationProfinet.cancelRequest()
                    networkConfigurationProfinetDataChanged()
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



                    if(isInputTextEmpty === true)
                    {
                        ipConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
                        ipConfigPopUpMsg.qmltextWarningDialog = qmltextEmptyMsg
                        ipConfigPopUpMsg.visible = true
                        isInputTextEmpty = false
                    }
                    else
                    {
                        SystemNetworkConfigurationProfinet.updateProfinetDetails(ipAddress,netMask,gateWay,stationName)
                        SystemNetworkConfigurationProfinet.saveRequest()
                    }
                }
            }
        }
    }
}

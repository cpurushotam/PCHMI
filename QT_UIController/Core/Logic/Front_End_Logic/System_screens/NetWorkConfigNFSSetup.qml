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

    property string qmltextIPSetUp:                  "NFS SETUP"
    property string qmltextNFSIPAddress:                "NFS IP Address"
    property string qmltextMountPath:               "NFS Mount Path"
    property string qmltextCancelBtn:                "CANCEL"
    property string qmltextSaveBtn:                  "SAVE"
    property string qmltextEnterDigit:               "Enter Digit Only"
    property string qmltextEnterText:                "Enter mount path."

    property string qmltextWarningLabel:             "Warning"
    property string qmltextEmptyMsg:                 "Please Make Sure All Text Inputs are Filled"
    property int inputlimit:  256
    property int inputIplimit: 47

    property bool isInputTextEmpty :false
    property string nfsIPAdress : ""
    property string nfsMountPath : ""

    property var qmlTextArray:[qmltextIPSetUp,qmltextNFSIPAddress,
                             qmltextMountPath,qmltextCancelBtn,qmltextSaveBtn,qmltextEnterDigit,
                            qmltextWarningLabel,qmltextEmptyMsg]

    QtObject
    {
        id: textEnum
        readonly property int textConfigCommunIdx           : 0
        readonly property int textNFSIPSetUpIdx             : 1
        readonly property int textNFSIPAddressIdx           : 2
        readonly property int textNFSMountIdx               : 3
        readonly property int textSaveBtnIdx                : 4
        readonly property int textEnterDigitIdx             : 5
        readonly property int textWarningLabelIdx           : 6
        readonly property int textEmptyMsgIdx               : 7

    }
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_NFS, qmlTextArray)
        qmltextIPSetUp = qmlTextArray[textEnum.textNFSIPSetUpIdx]
        qmltextNFSIPAddress = qmlTextArray[textEnum.textNFSIPAddressIdx]
        qmltextMountPath = qmlTextArray[textEnum.textNFSMountIdx]
        qmltextSaveBtn = qmlTextArray[textEnum.textSaveBtnIdx]
        qmltextEnterDigit = qmlTextArray[textEnum.textEnterDigitIdx]
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
        id:nfsConfigPopUpMsg
        rectleftMargin:Math.round(230 * Style.scaleHint)
        onOKButtonClicked:
        {
            nfsConfigPopUpMsg.visible = false
            nfsConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
        }
    }

    Component.onCompleted:
    {
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_NFS
        inputPanelKeyBoard.visible = false
    }


    Rectangle
    {
        id:mainRectangle
        width: mainWindow.showWidth
        height: mainWindow.showHeight *0.65
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        color: Style.backgroundColor
        clip:true
        enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
        InputPanel
        {
            id: inputPanelKeyBoard
            z: 1
            x: 0
            height: parent.height
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            visible: Qt.inputMethod.visible
        }

        Item {
            id: networkConfigItem
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.03
            anchors.top: mainRectangle.top
            anchors.topMargin: parent.height*0.04
            height: parent.height * 0.78
            width: parent.width * 0.95
            Row
            {
                id:networkConfigRow
                anchors.fill: parent
                spacing: parent.width * 0.03
                // NFS IP Setup section
                Rectangle
                {
                    id:nfsSetupRectangle
                    width: parent.width * 0.36
                    height:parent.height
                    color: "transparent"
                    Text
                    {
                        id:nfssetupText
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
                        id:nfsipSetupUnderLine
                        width: parent.width
                        height: parent.height * 0.003
                        anchors.top:nfssetupText.bottom
                        anchors.topMargin:  parent.width * 0.015
                        color: Style.placeHolderTextColor
                    }
                    RowLayout
                    {
                        id:nfsSetupRadiobutton
                        spacing: parent.width * 0.30
                        anchors.top: nfsipSetupUnderLine.bottom
                        anchors.topMargin: parent.height * 0.035

                    }
                    Item {
                        id: nfsIpSetupRowItem
                        anchors.top: nfsSetupRadiobutton.bottom
                        anchors.topMargin: parent.height * 0.02
                        width: parent.width
                        height: parent.height * 0.75
                        Flickable
                        {
                            id:nfsSetupFlick
                            flickableDirection: Flickable.VerticalFlick
                            width: parent.width
                            height: parent.height
                            flickDeceleration: 10000
                            contentHeight: true ? height* 2.0: height* 1.3
                            clip: true
                            Column
                            {
                                id:nfsSetupColumn
                                spacing: Math.round(10.2 * Style.scaleHint)
                                anchors.fill: parent
                                Repeater
                                {
                                    id:nfsSetupRepeater
                                    model: [qmltextNFSIPAddress, qmltextMountPath]
                                    Rectangle
                                    {
                                        id:nfsSetUpRect
                                        width: parent.width
                                        height: Math.round(50 * Style.scaleHint)
                                        color: Style.contentBackgroundColor
                                        Text {
                                            id: nfsSetupParamName
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
                                            id:nfsSetupParamInputText
                                            width:parent.width*0.90
                                            height:parent.height * 0.5
                                            anchors.top :nfsSetupParamName.bottom
                                            anchors.topMargin: parent.height * 0.02
                                            anchors.left :parent.left
                                            anchors.leftMargin: parent.width * 0.03
                                            focus: false
                                            font.family: Style.regular.name
                                            font.weight :470
                                            font.pixelSize: Math.round(10 * Style.scaleHint)
                                            placeholderText:  index == 0 ? qmltextEnterDigit : qmltextEnterText
                                            maximumLength: index == 1 ? inputlimit : inputIplimit
                                            selectByMouse: true
                                            background: Rectangle
                                            {
                                                color: "#FFFFFF"
                                                radius: Math.round(5 * Style.scaleHint)
                                                border.color: Style.frameBorderColor
                                                border.width: 1
                                            }
                                            onTextChanged:
                                            {
                                                if(index == 1)
                                                {
                                                    if (nfsSetupParamInputText.text.length > inputlimit)
                                                    {
                                                        nfsSetupParamInputText.text = nfsSetupParamInputText.text.substring(0, inputlimit)
                                                    }
                                                }
                                            }
                                            validator: RegularExpressionValidator
                                            {
                                                regularExpression: index !== 1 ?                                                                       
                                                    /^(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)\.(25[0-5]|2[0-4][0-9]|1\d{2}|[1-9]?\d)$/
                                                     : undefined                                            }
                                            onActiveFocusChanged:
                                            {
                                                if(activeFocus)
                                                {
                                                    nfsSetupParamInputText.focus = true
                                                    nfsSetupParamInputText.color = "#000000"
                                                    inputPanelKeyBoard.visible = true
                                                }
                                                else
                                                {
                                                    nfsSetupParamInputText.focus = false
                                                    inputPanelKeyBoard.visible = false
                                                    if(nfsSetupParamInputText.text !== "")
                                                    {
                                                        if(index === 0)
                                                        {
                                                            nfsIPAdress = nfsSetupParamInputText.text
                                                        }
                                                        else if(index === 1)
                                                        {
                                                            nfsMountPath = nfsSetupParamInputText.text
                                                        }

                                                    }
                                                    else
                                                    {
                                                        isInputTextEmpty = true
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
                id:saveButton
                implicitWidth: Math.round(100 * Style.scaleHint)
                implicitHeight: Math.round(30 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
                text: qmltextSaveBtn
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked:
                {
                    if(nfsMountPath != "" && nfsIPAdress != "")
                    {
                        SystemNetworkConfigurationNFSSetup.saveRequest(nfsIPAdress,nfsMountPath)
                    }
                    else
                    {
                        nfsConfigPopUpMsg.qmltextLabel = qmltextWarningLabel
                        nfsConfigPopUpMsg.qmltextWarningDialog = qmltextEmptyMsg
                        nfsConfigPopUpMsg.visible = true
                    }
                }
            }
        }
    }
}

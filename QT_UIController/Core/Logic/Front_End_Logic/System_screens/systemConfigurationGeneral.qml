/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

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

Item {

    id:generaltab
    readonly property int qmlscreenIndicator:   UIScreenEnum.SYSTEM_CONFIG_GENERAL
    property string qmltextMachineName:                ("Welder Name")
    property string qmltextMemFullAction:              ("Memory Full Action")
    property string qmltextPowerUpOption:              ("Power Up Option")

    property string qmltextKey:                        ("Key")

    property string qmltextClearmemoryAtPowerup :       "Clear Memory At Powerup"
    property string qmltextClearmemoryWithReset :       "Clear Memory With Reset "

    property string qmltextAuthCheck:                  ("Authority Check")
    property string qmltextBarcodePrefix:              ("Barcode Recall Recipe Prefix")
    property string qmltextPartId:                     ("Part ID")
    property string qmltextVerify:                     ("VERIFY")
    property string qmltextReset:                     ("RESET")
    property string qmltextCancel:                     ("CANCEL")
    property string qmltextSave:                       ("SAVE")
    property string qmlResetToDefault:                 ("RESET TO DEFAULT")

    property string qmltextUnitDisplay:                ("Unit Display")
    property string qmltextMetricUnit:                 ("SI (Metric)")
    property string qmltextImperialUnit:               ("SAE (Imperial)")
    property string qmltextKeyVerifyMsg:              "Key verified successfully"
    property string qmltextKeyVerifyFailMsg:          "Wrong Key Entered"
    property string qmltextConfLabel:                 "Confirmation"
    property string qmltextKeyWarningLabel:           "Warning"
    property string qmltextWelderNameEmpty:           "Welder name cannot be empty."

    property string qmltextParallelWeldResult :       "Parallel Weld Result Storage"
    property string qmltextClampOn:                   "Clamp On"
    property string qmltextUniqueRecipeNumberStaus:   "Use Unique Recipe Numbers"

    property string qmltextWelderIpChange:            "IP Address for Welder"
    property string qmltextKeyVerifyMsg2:             "Branson tab is now activated."
    property string qmltextPopupMsg                    : "Do you want to logout Branson service person?"
    property string qmltextPopupMsg2                    : "Press Ok to logout.";

    property string qmlTextContinue : "Continue"
    property string qmlTextStop     : "Stop"
    property string qmlTextOff      : "Off"
    property string qmlTextBasic    : "Basic"
    property string qmlTextNone     : "None"
    property string qmlTextSeek     : "Seek"
    property string qmlTextScan     : "Scan"

    property var memFullActionsModel: [qmlTextContinue, qmlTextStop]
    property var authCheckModel: [qmlTextOff, qmlTextBasic]
    property var powerUpOptionModel: [qmlTextNone, qmlTextSeek, qmlTextScan]
    property bool clearedOnce: false

    property int inputlimitForWelderName: SystemGeneral.maxWelderNameLength()

    property int curUnit:  -1

    property var qmlTextArray: [qmltextMachineName, qmltextMemFullAction, qmltextKey,
        qmltextAuthCheck, qmltextBarcodePrefix, qmltextVerify,
        qmltextCancel, qmltextSave,qmlResetToDefault,qmltextUnitDisplay,qmltextMetricUnit,
        qmltextImperialUnit,qmltextPartId, qmltextClearmemoryAtPowerup, qmltextClearmemoryWithReset, qmltextKeyVerifyMsg,
        qmltextKeyVerifyFailMsg,qmltextConfLabel,qmltextKeyWarningLabel,qmltextParallelWeldResult,qmltextWelderIpChange, qmltextPowerUpOption, qmltextWelderNameEmpty, qmltextClampOn, qmltextUniqueRecipeNumberStaus,
        qmltextKeyVerifyMsg2, qmltextPopupMsg, qmltextPopupMsg2, qmlTextContinue, qmlTextStop, qmlTextOff, qmlTextBasic, qmlTextNone, qmlTextSeek, qmlTextScan]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_GENERAL, qmlTextArray)
        qmltextMachineName = qmlTextArray[textEnum.textMachineNameIdx]
        qmltextMemFullAction = qmlTextArray[textEnum.textMemFullActionIdx]
        qmltextKey = qmlTextArray[textEnum.textKeyIdx]
        qmltextAuthCheck = qmlTextArray[textEnum.textAuthCheckIdx]
        qmltextBarcodePrefix = qmlTextArray[textEnum.textBarcodePrefixIdx]
        qmltextVerify = qmlTextArray[textEnum.textVerifyIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmlResetToDefault= qmlTextArray[textEnum.textResetIdx]
        qmltextUnitDisplay = qmlTextArray[textEnum.textUnitDisplayIdx]
        qmltextMetricUnit = qmlTextArray[textEnum.textMetricUnitIdx]
        qmltextImperialUnit = qmlTextArray[textEnum.textImperialUnitIdx]
        qmltextPartId = qmlTextArray[textEnum.textPartIDIdx]
        qmltextClearmemoryAtPowerup = qmlTextArray[textEnum.textClearmemoryatPowerupIdx]
        qmltextClearmemoryWithReset = qmlTextArray[textEnum.textClearmemoryRestIdx]
        qmltextKeyVerifyMsg = qmlTextArray[textEnum.textKeyVerifyMsgIdx]
        qmltextKeyVerifyFailMsg = qmlTextArray[textEnum.textKeyVerifyFailMsgIdx]
        qmltextConfLabel = qmlTextArray[textEnum.textConfLabelIdx]
        qmltextKeyWarningLabel = qmlTextArray[textEnum.textKeyWarningLabelIdx]
        qmltextParallelWeldResult = qmlTextArray[textEnum.textParallelWeldResultIdx]
        qmltextWelderIpChange = qmlTextArray[textEnum.textWelderIPAddressChngIdx]
        qmltextPowerUpOption = qmlTextArray[textEnum.textPowerUpOptionIdx]
        qmltextWelderNameEmpty = qmlTextArray[textEnum.textWelderNameEmptyIdx]
        qmltextClampOn = qmlTextArray[textEnum.textClampOnIdx]
        qmltextUniqueRecipeNumberStaus = qmlTextArray[textEnum.textUniqueRecipeNumberStausIdx]
        qmltextKeyVerifyMsg2 = qmlTextArray[textEnum.textKeyVerifyMsg2Idx]
        qmltextPopupMsg = qmlTextArray[textEnum.qmltextPopupMsgIdx]
        qmltextPopupMsg2 = qmlTextArray[textEnum.qmltextPopupMsgIdx2]
        qmlTextContinue = qmlTextArray[textEnum.textContinueIdx]
        qmlTextStop = qmlTextArray[textEnum.textStopIdx]
        qmlTextOff = qmlTextArray[textEnum.textOffIdx]
        qmlTextBasic = qmlTextArray[textEnum.textBasicIdx]
        qmlTextNone = qmlTextArray[textEnum.textNoneIdx]
        qmlTextSeek = qmlTextArray[textEnum.textSeekIdx]
        qmlTextScan = qmlTextArray[textEnum.textScanIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textMachineNameIdx                    :0
        readonly property int textMemFullActionIdx                  :1
        readonly property int textKeyIdx                            :2
        readonly property int textAuthCheckIdx                      :3
        readonly property int textBarcodePrefixIdx                  :4
        readonly property int textVerifyIdx                         :5
        readonly property int textCancelIdx                         :6
        readonly property int textSaveIdx                           :7
        readonly property int textResetIdx                          :8
        readonly property int textUnitDisplayIdx                    :9
        readonly property int textMetricUnitIdx                     :10
        readonly property int textImperialUnitIdx                   :11
        readonly property int textPartIDIdx                         :12
        readonly property int textClearmemoryatPowerupIdx           :13
        readonly property int textClearmemoryRestIdx                :14
        readonly property int textKeyVerifyMsgIdx                   :15
        readonly property int textKeyVerifyFailMsgIdx               :16
        readonly property int textConfLabelIdx                      :17
        readonly property int textKeyWarningLabelIdx                :18
        readonly property int textParallelWeldResultIdx             :19
        readonly property int textWelderIPAddressChngIdx            :20
        readonly property int textPowerUpOptionIdx                  :21
        readonly property int textWelderNameEmptyIdx                :22
        readonly property int textClampOnIdx                        :23
        readonly property int textUniqueRecipeNumberStausIdx        :24
        readonly property int textKeyVerifyMsg2Idx                  :25
        readonly property int qmltextPopupMsgIdx                    :26
        readonly property int qmltextPopupMsgIdx2                   :27
        readonly property int textContinueIdx                       :28
        readonly property int textStopIdx                           :29
        readonly property int textOffIdx                            :30
        readonly property int textBasicIdx                          :31
        readonly property int textNoneIdx                           :32
        readonly property int textSeekIdx                           :33
        readonly property int textScanIdx                           :34
    }

    QtObject
    {
        id: unitTypeEnum
        readonly property int unitTypeMetric           : 0
        readonly property int unitTypeImperial         : 1
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    ListModel{
        id:ipAddressModel
    }

    Connections
    {
        target: SystemGeneral
        function onSysConfigDataChanged()
        {

            clearMemorySwitch.checked =  SystemGeneral.MemeoryClearAtPowerup
            clearMemoryresetSwitch.checked = SystemGeneral.MemoryClearReset
            partIdSwitch.checked =  SystemGeneral.PartID
            clamponSwitch.checked = SystemGeneral.Clampon
            setComboBoxIndexForIp(SystemGeneral.ipAddress)


            if(SystemGeneral.Unit === unitTypeEnum.unitTypeMetric)
            {
                metricRadioButton.checked=true
            }

            else if(SystemGeneral.Unit === unitTypeEnum.unitTypeImperial)
            {
                imperialRadioButton.checked = true
            }
        }
    }

    Connections
    {
        target: SystemGeneral
        function onKeyVerifiedDataChanged()
        {
            if(SystemGeneral.KeyVerifyStatus === true)
            {
                mainWindow.bransonTabEnable = true
                mainWindow.showBransonPopup(qmltextKeyVerifyMsg + "\n" +qmltextKeyVerifyMsg2, qmltextConfLabel)
                mainWindow.showBransonScreen()
            }

            else
            {
                mainWindow.showBransonPopup(qmltextKeyVerifyFailMsg, qmltextKeyWarningLabel)
            }
        }
    }

    function setComboBoxIndexForIp(targetIp)
    {
        for (var i = 0; i < ipAddressModel.count; i++)
        {
            if (ipAddressModel.get(i).IpAddress === targetIp)
            {
                ipAddressCombbox.currentIndex = i;
                break;
            }
        }
    }

    Component.onCompleted:
    {
         ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_GENERAL

        if(SystemGeneral.Unit === unitTypeEnum.unitTypeMetric)
        {
            metricRadioButton.checked=true
        }

        else if(SystemGeneral.Unit === unitTypeEnum.unitTypeImperial)
        {
            imperialRadioButton.checked=true
        }

        updateLanguage()

        for (var i=0; i < SystemGeneral.maxIpAddressInMap();i++)
        {
            ipAddressModel.append({ "IpAddress": SystemGeneral.getIpAddressForComboboxModel(i)})
        }

        keyIPText.text = ""
        setComboBoxIndexForIp(SystemGeneral.ipAddress)

    }

    InputPanel
    {
        id: inputPanelKey
        z: 1
        x:0
        y: mainWindow.showHeight*0.85
        height: mainWindow.showHeight *0.15
        width: mainWindow.showWidth
        anchors.bottom: mainRect.bottom
        anchors.bottomMargin: zoomingSize(-35)
        visible: Qt.inputMethod.visible
    }

    InputPanel
    {
        id: welderName
        z: 1
        x:0
        y: mainWindow.showHeight*0.65
        height: mainWindow.showHeight *0.10
        width: mainWindow.showWidth
        anchors.bottom: mainRect.bottom
        anchors.bottomMargin: zoomingSize(-35)
        visible: Qt.inputMethod.visible
    }

    InputPanel
    {
        id: inputPanelBarcode
        z: 1
        x:0
        y: mainWindow.showHeight*0.85
        height: mainWindow.showHeight *0.15
        width: mainWindow.showWidth
        anchors.bottom: mainRect.bottom
        anchors.bottomMargin: zoomingSize(-35)
        visible: Qt.inputMethod.visible
    }

    MouseArea
    {
        id: backGroundMa
        anchors.fill: parent
        onClicked:
        {
            inputPanelBarcode.visible = false
            inputPanelBarcode.focus = false
        }
    }
    Rectangle
    {
        id: mainRect
        anchors.left: parent.left
        anchors.leftMargin: zoomingSize(30)
        anchors.top: parent.top
        anchors.topMargin: zoomingSize(18)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: zoomingSize(18)
        width:mainWindow.showWidth
        height: mainWindow.showHeight*0.80
        color:"transparent"
        clip: true

        Flickable
        {
            id: flickable
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: parent.height*2.5
            contentY: (inputPanelKey.visible) ?  (300) : (inputPanelBarcode.visible) ?
                                                    (120) : 0
            clip: true

            Rectangle
            {
                id: machineNameRect
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                width: zoomingSize(300)
                height: zoomingSize(60)
                color: UserPrivilegeObj.getLogedInUserLevel() === "Executive" || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === "Executive" || mainWindow.isAuthorityCheckEnable  ? true :false

                Text
                {
                    id:machineNmaeText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextMachineName
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }


                Rectangle
                {
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    width:parent.width*0.90
                    height:zoomingSize(23)
                    BransonLineEdit
                    {
                        id:weldernametextedit
                        x:zoomingSize(10)
                        y:zoomingSize(5)
                        text:SystemGeneral.WelderName == " " ? mainWindow.activeWelderNameTxt : SystemGeneral.WelderName
                        z:1
                        width:parent.width*0.90
                        height:zoomingSize(23)
                        focus: true
                        selectByMouse: true
                        mouseSelectionMode: TextInput.SelectWords
                        onTextChanged: if (length > inputlimitForWelderName) remove(inputlimitForWelderName, length);
                        onActiveFocusChanged:
                        {
                            Qt.inputMethod.hide()

                            /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                            if(activeFocus)
                            {
                                welderName.visible = true
                                clearedOnce = true
                                weldernametextedit.selectAll()
                            }

                            else
                            {
                                welderName.visible = false
                                clearedOnce = false
                            }
                        }

                        /*Clear data once only*/
                        Keys.onPressed:
                        {
                            if (clearedOnce)
                            {
                                weldernametextedit.clear()
                                clearedOnce = false
                            }
                        }
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        welderName.visible = true
                        inputPanelKey.visible =false
                        inputPanelBarcode.visible=false
                        keyIPText.focus = false
                        barcodeText.focus = false
                    }
                }
            }
            BransonConfirmationPopup
            {
                id: confirmationPopup
                visible:false
                qmltextWarningMessage: qmltextPopupMsg + "\n" + qmltextPopupMsg2
                x:mainWindow.showWidth *0.25
                y:mainWindow.showHeight *0.001
                z :10
                focus:true
                width:mainWindow.showWidth*0.40
                height: mainWindow.showHeight*0.30
                closePolicy: Popup.NoAutoClose

                onCancelButtonClicked:
                {
                    confirmationPopup.visible = false
                    mainWindow.opacityFlag = false
                }

                onOkButtonClicked:
                {
                    SystemGeneral.resrtBrsnSrvcKeyRequestFromHMI()
                    mainWindow.bransonTabEnable = false
                    keyIPText.text = ""
                    confirmationPopup.visible = false
                    mainWindow.opacityFlag = false
                }
            }
            //2nd
            Rectangle
            {
                id: memfullRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: machineNameRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false
                Text
                {
                    id:memfullText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextMemFullAction
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonComboBox
                {
                    id: memfullCombobox
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    minWidth:parent.width*0.90
                    minHeight:zoomingSize(23)
                    model: memFullActionsModel
                    isNormal: true
                    currentIndex:SystemGeneral.MemoryfullAction
                    /*Uncomment below part when model data available from backend*/
                    /*comboBoxProperty.currentIndex: model.index*/
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }
            //3rd
            Rectangle
            {
                id: powerUpRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: memfullRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false
                Text
                {
                    id:powerupText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextPowerUpOption
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
                BransonComboBox
                {
                    id: powerUpModel
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    minWidth:parent.width*0.90
                    minHeight:zoomingSize(23)
                    model: powerUpOptionModel
                    isNormal: true
                    currentIndex: SystemGeneral.PowerUpOption

                    onCurrentIndexChanged:
                    {
                        SystemGeneral.PowerUpOption = powerUpModel.currentIndex
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }

            //4th
            Rectangle
            {
                id: keyRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: powerUpRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false
                Text
                {
                    id:keyText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextKey
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonLineEdit
                {
                    id:keyIPText
                    x:zoomingSize(9)
                    y:zoomingSize(31)
                    z:1
                    width:parent.width*0.60
                    height:zoomingSize(23)
                    text:SystemGeneral.Key
                    focus: true
                    selectByMouse: true
                    mouseSelectionMode: TextInput.SelectWords
                    onActiveFocusChanged:
                    {
                        Qt.inputMethod.hide()

                        /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                        if(activeFocus)
                        {
                            inputPanelKey.visible = true
                            clearedOnce = true
                            keyIPText.selectAll()
                        }

                        else
                        {
                            inputPanelKey.visible = false
                            clearedOnce = false
                        }
                    }

                    /*Clear data once only*/
                    Keys.onPressed:
                    {
                        if (clearedOnce)
                        {
                            keyIPText.clear()
                            clearedOnce = false
                        }
                    }
                }


                BransonPrimaryButton
                {
                    id: resetButton
                    x:zoomingSize(200)
                    y:zoomingSize(30)
                    z:1
                    width:zoomingSize(80)
                    implicitHeight:zoomingSize(22)
                    fontSize: zoomingSize(Style.style4)
                    text: qmltextReset
                    textColor: Style.buttonTextColor
                    font.family: Style.regular.name
                    buttonColor: Style.buttonColor
                    onClicked:
                    {
                        confirmationPopup.visible = true

                    }
                }

                BransonPrimaryButton
                {
                    id: verifyButton
                    x:zoomingSize(200)
                    y:zoomingSize(5)

                    z:1
                    width:zoomingSize(80)
                    implicitHeight:zoomingSize(22)
                    fontSize: zoomingSize(Style.style4)
                    text: qmltextVerify
                    textColor: Style.buttonTextColor
                    font.family: Style.regular.name
                    buttonColor: Style.buttonColor
                    onClicked:
                    {
                        SystemGeneral.Key=keyIPText.text
                        SystemGeneral.keyVerifyRequest()
                    }
                }

                MouseArea
                {
                    id: keyRectMa
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }


            //5th memoery clear
            Rectangle
            {
                id: clearMemoryRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: keyRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:clearmemoryText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextClearmemoryAtPowerup
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:clearMemorySwitch
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.MemeoryClearAtPowerup

                    onCheckedChanged:
                    {
                        SystemGeneral.MemeoryClearAtPowerup = checked
                    }


                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }

            //6th Parallel Weld Cycle storage status
            Rectangle
            {
                id: parallelWeldCycleRect
                color: Style.contentBackgroundColor
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: clearMemoryRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)

                Text
                {
                    id:parallelWeldCycleText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextParallelWeldResult
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:parallelWeldCycleSwitch
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.ParallelWeldResultStorageStatus
                    onCheckedChanged:
                    {
                        SystemGeneral.ParallelWeldResultStorageStatus = checked
                    }
                }
            }

            //5th
            Rectangle
            {
                id: authCheckRect
                color: UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: machineNameRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled: UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed || mainWindow.isAuthorityCheckEnable
                Text
                {
                    id:authCheckText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextAuthCheck
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
                BransonComboBox
                {
                    id: authCheckCombobox
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    minWidth:parent.width*0.90
                    minHeight:zoomingSize(23)
                    model: authCheckModel
                    isNormal: true
                    currentIndex: SystemGeneral.AuthorityChk
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        welderName.visible = false
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }
            //6th
            Rectangle
            {
                id: barcodeRect
                color: UserPrivilegeObj.IsBarcoderecipeRecallAllowed || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: memfullRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: authCheckRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled: UserPrivilegeObj.IsBarcoderecipeRecallAllowed || mainWindow.isAuthorityCheckEnable
                Text
                {
                    id:barcodeText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextBarcodePrefix
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
                BransonLineEdit
                {
                    id:barcodeIPText
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    width:parent.width*0.90
                    height:zoomingSize(23)
                    focus: true
                    text: SystemGeneral.BarcodeRecallRecipePrefix
                    selectByMouse: true
                    mouseSelectionMode: TextInput.SelectWords
                    onActiveFocusChanged:
                    {
                        Qt.inputMethod.hide()

                        /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                        if(activeFocus)
                        {
                            inputPanelBarcode.visible = true
                            clearedOnce = true
                            barcodeIPText.selectAll()
                        }
                        else
                        {
                            inputPanelBarcode.visible = false
                            clearedOnce = false
                        }
                    }

                    /*Clear data once only*/
                    Keys.onPressed:
                    {
                        if (clearedOnce)
                        {
                            barcodeIPText.clear()
                            clearedOnce = false
                        }
                    }

                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }

            }
            //PartId
            Rectangle
            {
                id: partIdRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: memfullRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: barcodeRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:partIdText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextPartId
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:partIdSwitch
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.PartID

                    onCheckedChanged:
                    {
                        SystemGeneral.PartID =checked
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }

            //7th
            Rectangle
            {
                id: unitRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: keyRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: partIdRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false
                Text
                {
                    id:unitText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextUnitDisplay
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }
                RowLayout
                {
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    spacing:4
                    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
                    RadioButton
                    {
                        id:metricRadioButton
                        text: qmltextMetricUnit
                        font.pixelSize: zoomingSize(Style.style4)
                        font.family: Style.regular.name
                        onClicked:
                        {
                            curUnit =  unitTypeEnum.unitTypeMetric
                        }
                    }
                    RadioButton
                    {
                        id: imperialRadioButton
                        text: qmltextImperialUnit
                        font.pixelSize: zoomingSize(Style.style4)
                        font.family: Style.regular.name
                        onClicked:
                        {
                            curUnit = unitTypeEnum.unitTypeImperial
                        }
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }


            Rectangle
            {
                id: clearMemorywithResetRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: clearMemoryRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: unitRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:clearmemoryresetText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextClearmemoryWithReset
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:clearMemoryresetSwitch
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.MemoryClearReset
                    onCheckedChanged:
                    {
                        SystemGeneral.MemoryClearReset = checked
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }

            Rectangle
            {
                id: clampon
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: clearMemoryRect.right
                anchors.leftMargin: zoomingSize(125)
                anchors.top: clearMemorywithResetRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:clamponText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextClampOn
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:clamponSwitch
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.Clampon
                    onCheckedChanged:
                    {
                        SystemGeneral.Clampon = checked
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }

            //UniqueRecipe No Stauts Rect.
            Rectangle
            {
                id: uniqueRecipeRect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: parallelWeldCycleRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:uniqueRecipeText
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextUniqueRecipeNumberStaus
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonSwitch
                {
                    id:uniqueRecipeTxt
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight:Math.round(15 * Style.scaleHint)
                    rectWidth:Math.round(35 * Style.scaleHint)
                    rectHeight:Math.round(12 * Style.scaleHint)
                    checked: SystemGeneral.UniqueWeldRecipeStatus
                    onCheckedChanged:
                    {
                        SystemGeneral.UniqueWeldRecipeStatus = checked
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }


            //Change welder IP Address

            Rectangle
            {
                id: ipAddresschangerect
                color: UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? Style.contentBackgroundColor : "#d7d9db"
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(30)
                anchors.top: parallelWeldCycleRect.bottom
                anchors.topMargin: zoomingSize(10)
                width: zoomingSize(300)
                height: zoomingSize(60)
                enabled:  UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable ? true :false

                Text
                {
                    id:ipAddressext
                    x:zoomingSize(10)
                    y:zoomingSize(5)
                    z:1
                    text: qmltextWelderIpChange
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                BransonComboBox
                {
                    id: ipAddressCombbox
                    x:zoomingSize(10)
                    y:zoomingSize(31)
                    z:1
                    minWidth:parent.width*0.90
                    minHeight:zoomingSize(23)
                    model: ipAddressModel
                    isNormal: true
                    currentIndex:-1
                    comboboxpopupheight: Math.round(105 * Style.scaleHint)
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        keyIPText.focus = false
                        barcodeText.focus = false
                        inputPanelKey.visible = false
                        inputPanelBarcode.visible = false
                    }
                }
            }


        }
    }

    //8th

    BransonPrimaryButton
    {
        id: resetToDefalutButton
        anchors.left: mainRect.left
        anchors.leftMargin:  zoomingSize(30)
        anchors.top: mainRect.bottom
        anchors.topMargin: zoomingSize(4)
        width:zoomingSize(125)
        implicitHeight:zoomingSize(30)
        fontSize: resetToDefalutButton.height*0.40
        text: qmlResetToDefault
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked:
        {
            SystemGeneral.resetToDefaultRequest()
        }
    }

    BransonPrimaryButton{
        id: cancelButton
        anchors.left: parent.left
        anchors.leftMargin: zoomingSize(500)
        anchors.top: mainRect.bottom
        anchors.topMargin: zoomingSize(4)
        width:zoomingSize(125)
        implicitHeight:zoomingSize(30)
        fontSize: zoomingSize(Style.style4)
        text: qmltextCancel
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked:
        {
            SystemGeneral.cancelRequestFromHMI()
        }
    }

    BransonPrimaryButton{
        id: saveButton
        anchors.left: parent.left
        anchors.leftMargin: zoomingSize(650)
        anchors.top: mainRect.bottom
        anchors.topMargin: zoomingSize(4)
        width:zoomingSize(125)
        implicitHeight:zoomingSize(30)
        fontSize: zoomingSize(Style.style4)
        text: qmltextSave
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked:
        {
            if(curUnit === unitTypeEnum.unitTypeMetric)
            {
                metricRadioButton.checked = true
                imperialRadioButton.checked = false
                SystemGeneral.getHMIUnit(curUnit)
            }

            if(curUnit === unitTypeEnum.unitTypeImperial)
            {
                imperialRadioButton.checked = true
                metricRadioButton.checked = false
                SystemGeneral.getHMIUnit(curUnit)
            }

            if(weldernametextedit.text === "")
            {
                mainWindow.showBransonPopup(qmltextWelderNameEmpty, qmltextKeyWarningLabel)
                weldernametextedit.text =  mainWindow.activeWelderNameTxt
            }

            else
            {
                SystemGeneral.WelderName = weldernametextedit.text
                SystemGeneral.AuthorityChk = authCheckCombobox.currentIndex
                SystemGeneral.MemoryfullAction=memfullCombobox.currentIndex
                SystemGeneral.BarcodeRecallRecipePrefix=barcodeIPText.text
                SystemGeneral.IpAddress = ipAddressModel.get(ipAddressCombbox.currentIndex).IpAddress
                SystemGeneral.changeRequestFromHMI();

            }
        }
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 SoftwareUpgrade - This screen is used to displays information about software upgrade.

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.15
import Style 1.0
import QtQuick.Layouts
import QtQuick.Layouts 1.3
import QtQml.Models 2.15
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Popup
{
    id: softwareUpgradePopup
    parent: Overlay.overlay
    dim: true
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    property string qmltextChooseParameter            : "CHOOSE PARAMETER"
    property string qmltextReadUsb                    : "READ USB"
    property string qmltextReadUsbMsg                 : "To begin, insert USB drive and click \" Read USB \"."
    property string qmltextFIRMWARE_UPGRADE_SC        : "Supervisory Controller"
    property string qmltextFIRMWARE_UPGRADE_AC        : "Actuator Controller"
    property string qmltextFIRMWARE_UPGRADE_HMI       : "UI Controller"
    property string qmltextDone                       : "DONE"
    property string qmltextUpgrade                    : "UPGRADE"
    property string qmltextConfirmation               : "CONFIRMATION"
    property string qmltextComplete                   : "Complete"
    property string qmltextProgress                   : "In progress"
    property string qmltextWarningLabel               : "Warning"
    property string qmltextConfLabel                  : "Confirmation"
    property string qmltextUpgradeSuccess             : "Upgrade is successful, Please reboot the system"
    property string qmltextUpgradeFail                : "Upgrade failure, Please reboot the system"
    property string qmltextSelectFile                 : "Please select the file name"


    property bool readUsbFlag : false
    property bool upgradeBtnFlag : false
    property int scModelCurrentIndex: 0
    property int acModelCurrentIndex: 0
    property int hmiModelCurrentIndex: 0

    readonly property string emptyList : "None"
    property string emptyProgressStatus  : ""

    property var    qmlTextArray: [qmltextChooseParameter,qmltextReadUsb, qmltextReadUsbMsg,
        qmltextFIRMWARE_UPGRADE_SC,qmltextFIRMWARE_UPGRADE_AC,qmltextFIRMWARE_UPGRADE_HMI,
        qmltextDone,qmltextUpgrade,qmltextConfirmation,qmltextComplete,qmltextProgress,qmltextWarningLabel,qmltextConfLabel,
        qmltextUpgradeSuccess,qmltextUpgradeFail,qmltextSelectFile]

    /* Enum declaration for text index */
    QtObject
    {
        id: textEnum
        readonly property int textChooseParameterIdx:       0
        readonly property int textReadUsbIdx:               1
        readonly property int textReadUsbMsgIdx:            2
        readonly property int textFirmwareUpgradeSCIdx:     3
        readonly property int textFirmwareUpgradeACIdx:     4
        readonly property int textFirmwareUpgradeHMIIdx:    5
        readonly property int textDoneIdx:                  6
        readonly property int textUpgradeIdx:               7
        readonly property int textConfirmationIdx :         8
        readonly property int textCompleteIdx :             9
        readonly property int textProgressIdx :             10
        readonly property int textWarningLabelIdx :         11
        readonly property int textConfLabelIdx :            12
        readonly property int textUpgradeSuccessIdx :       13
        readonly property int textUpgradeFailIdx :          14
        readonly property int textSelectFileIdx :           15
    }

    /* To update texts as per selected language */
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE, qmlTextArray)
        qmltextChooseParameter       = qmlTextArray[textEnum.textChooseParameterIdx]
        qmltextReadUsb               = qmlTextArray[textEnum.textReadUsbIdx]
        qmltextReadUsbMsg            = qmlTextArray[textEnum.textReadUsbMsgIdx]
        qmltextFIRMWARE_UPGRADE_SC   = qmlTextArray[textEnum.textFirmwareUpgradeSCIdx]
        qmltextFIRMWARE_UPGRADE_AC   = qmlTextArray[textEnum.textFirmwareUpgradeACIdx]
        qmltextFIRMWARE_UPGRADE_HMI  = qmlTextArray[textEnum.textFirmwareUpgradeHMIIdx]
        qmltextDone        = qmlTextArray[textEnum.textDoneIdx]
        qmltextUpgrade     = qmlTextArray[textEnum.textUpgradeIdx]
        qmltextConfirmation   = qmlTextArray[textEnum.textConfirmationIdx]
        qmltextComplete   = qmlTextArray[textEnum.textCompleteIdx]
        qmltextProgress   = qmlTextArray[textEnum.textProgressIdx]
        qmltextWarningLabel   = qmlTextArray[textEnum.textWarningLabelIdx]
        qmltextConfLabel   = qmlTextArray[textEnum.textConfLabelIdx]
        qmltextUpgradeSuccess   = qmlTextArray[textEnum.textUpgradeSuccessIdx]
        qmltextUpgradeFail   = qmlTextArray[textEnum.textUpgradeFailIdx]
        qmltextSelectFile   = qmlTextArray[textEnum.textSelectFileIdx]
    }

    /* Slot called on signal signalCurrentLanguageChanged */
    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
        softwareUpgradePopupMsg.visible = false
        supervisoryContrComboBox.currentIndex = 0
        actuatorContrComboBox.currentIndex = 0
        hmiComboBox.currentIndex = 0
        scProgress.value = 0.0
        acProgress.value = 0.0
        uiProgress.value = 0.0
    }

    background: Rectangle {
        id:backgroundRectMain
        color:"transparent"
    }
    Overlay.modal: Rectangle {
        color: "#aacfdbe7"
    }
    Connections
    {
        target: SoftwareUpgradeInterface

        function onSoftwareUpgradeErrorCodeUpdated()
        {
            if(SoftwareUpgradeInterface.getSoftwareUpgradeErrorCode() === 2)
            {
                if((supervisoryContrComboBox.currentText !== emptyList))
                {
                    scProgress.value = 1.0
                    scTxtProgressTitle.text = qmltextComplete
                }
                else
                {
                    scProgress.value = 0.0
                    scTxtProgressTitle.text = emptyProgressStatus

                }
                if(actuatorContrComboBox.currentText !== emptyList)
                {
                    acProgress.value = 1.0
                    acTxtProgressTitle.text =  qmltextComplete
                }
                else
                {
                    acProgress.value = 0.0
                    acTxtProgressTitle.text = emptyProgressStatus
                }
                if(hmiComboBox.currentText !== emptyList)
                {
                    uiProgress.value = 1.0
                    uiTxtProgressTitle.text = qmltextComplete
                }
                else
                {
                    uiProgress.value = 0.0
                    uiTxtProgressTitle.text = emptyProgressStatus
                }

                softwareUpgradePopupMsg.qmltextLabel = qmltextConfLabel
                softwareUpgradePopupMsg.qmltextWarningDialog = qmltextUpgradeSuccess
                softwareUpgradePopupMsg.visible = true
            }
            else
            {
                scProgress.value = 0.0
                acProgress.value = 0.0
                uiProgress.value = 0.0
                scTxtProgressTitle.text = emptyProgressStatus
                acTxtProgressTitle.text = emptyProgressStatus
                uiTxtProgressTitle.text = emptyProgressStatus
                softwareUpgradePopupMsg.qmltextLabel = qmltextWarningLabel
                softwareUpgradePopupMsg.qmltextWarningDialog = qmltextUpgradeFail
                softwareUpgradePopupMsg.visible = true
            }
        }
    }
    Connections
    {
        target: SoftwareUpgradeInterface

        function onSoftwareUpgradeReadUsbDataChanged()
        {
            readUsbFlag = true
            supervisoryControllerModel.clear()
            var list = SoftwareUpgradeInterface.getSCFileNameList()
            for (var i = 0; i < list.length; i++)
            {
                supervisoryControllerModel.append({name: list[i]});
            }

            actuatorControllerModel.clear()
            var acList = SoftwareUpgradeInterface.getACFileNameList()
            for (var j = 0; j < acList.length; j++)
            {
                actuatorControllerModel.append({name: acList[j]});
            }

            hmiModel.clear()
            var hmiList = SoftwareUpgradeInterface.getHMIFileNameList()
            for (var k = 0; k < hmiList.length; k++)
            {
                hmiModel.append({name: hmiList[k]});
            }

            supervisoryContrComboBox.currentIndex = 0
            actuatorContrComboBox.currentIndex = 0
            hmiComboBox.currentIndex = 0
        }
    }

    ListModel{
        id:supervisoryControllerModel
    }

    ListModel{
        id:actuatorControllerModel
    }

    ListModel{
        id:hmiModel
    }

    BransonPopup
    {
        id:softwareUpgradePopupMsg
        rectleftMargin:Math.round(60 * Style.scaleHint)
        onOKButtonClicked:
        {
            softwareUpgradePopupMsg.visible = false
        }
    }

    Rectangle
    {
        id:mainRect
        anchors.fill: parent
        color:"#FFFFFF"
        clip:true
        Rectangle
        {
            id: headerRect
            anchors.left: parent.left
            anchors.right: parent.right
            width: parent.width
            height: parent.height*0.10
            color: Style.headerBackgroundColor
            Text {
                id: softUpgradeTextHeader
                text:qmltextChooseParameter
                font.family: Style.regular.name
                font.pointSize: parent.height*0.30
                color: "white"
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.03
                anchors.verticalCenter: parent.verticalCenter
            }
            Image{
                id: softUpgPopupClose
                source: "qrc:/Images/crossMark.svg"
                sourceSize.width:  Math.round(17* Style.scaleHint)
                sourceSize.height: Math.round(17* Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin:parent.width*0.02
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        upgradeBtnFlag = false
                        readUsbFlag = false
                        supervisoryContrComboBox.currentIndex = 0
                        actuatorContrComboBox.currentIndex = 0
                        hmiComboBox.currentIndex = 0
                        scProgress.value = 0.0
                        acProgress.value = 0.0
                        uiProgress.value = 0.0
                        softwareUpgradePopup.close()
                        ActiveScreen.CurrentActiveScreen  = mainWindow.currentActiveWindow
                    }
                }
            }
        }
        Text {
            id: softUpgReadUsbMsg
            text: qmltextReadUsbMsg
            anchors.top: headerRect.bottom
            anchors.topMargin: parent.height * 0.04
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            font.family: Style.regular.name
            color: "#000000"
            font.weight : Font.Medium
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
        }

        BransonPrimaryButton{
            id:readUsbButton
            height: Math.round(22 * Style.scaleHint)
            width: Math.round(90 * Style.scaleHint)
            anchors.top: softUpgReadUsbMsg.bottom
            anchors.topMargin: parent.height * 0.04
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            text: qmltextReadUsb
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
            buttonColor : "#17345C"
            onClicked:
            {
                scModelCurrentIndex = 0
                acModelCurrentIndex = 0
                hmiModelCurrentIndex = 0
                SoftwareUpgradeInterface.readUSBRequest()
            }
        }
        Rectangle
        {
            id:firmwareUpgradeSCRect
            height: parent.height * 0.10
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            anchors.top: readUsbButton.bottom
            anchors.topMargin: parent.height * 0.04
            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.04
            color: "transparent"
            Text {
                id: supervisoryContrText
                text: qmltextFIRMWARE_UPGRADE_SC
                anchors.verticalCenter:supervisoryContrComboBox.verticalCenter
                anchors.left: parent.left
                font.family: Style.regular.name
                color: "#000000"
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                visible: readUsbFlag ===  true ? true : false
            }

            BransonComboBox{
                id:supervisoryContrComboBox
                currentIndex: scModelCurrentIndex
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.04
                anchors.left:supervisoryContrText.right
                anchors.leftMargin: Math.round(24 * Style.scaleHint)
                minWidth: Math.round(150 * Style.scaleHint)
                minHeight: Math.round(24 * Style.scaleHint)
                textFontSize :Math.round(10* Style.scaleHint)
                comboBoxBorderColor:"transparent"
                comboBoxColor:BransonStyle.backgroundColor
                model:supervisoryControllerModel
                visible: readUsbFlag ===  true ? true : false
                onCurrentIndexChanged:
                {
                    scModelCurrentIndex = currentIndex
                }
            }

            ProgressBar
            {
                id: scProgress
                height: Math.round(6 * Style.scaleHint)
                anchors.left: supervisoryContrComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.right: firmwareUpgradeSCRect.right
                anchors.rightMargin: parent.width*0.05
                anchors.top: scTxtProgressTitle.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                value: supervisoryContrComboBox.currentText === emptyList ? 0.0 : 0.5
                visible: upgradeBtnFlag? true: false
            }

            Text {
                id: scTxtProgressTitle
                anchors.left: supervisoryContrComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.045
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.70
                font.family: Style.regular.name
                color: Style.blackFontColor
                text: supervisoryContrComboBox.currentText === emptyList ? "" : qmltextProgress
                visible: upgradeBtnFlag? true: false
            }
        }

        Rectangle
        {
            id:firmwareUpgradeACRect
            height: parent.height * 0.12
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            anchors.top: firmwareUpgradeSCRect.bottom
            anchors.topMargin: parent.height * 0.04
            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.04
            color: "transparent"

            Text {
                id: actuatorContrText
                text: qmltextFIRMWARE_UPGRADE_AC
                anchors.verticalCenter:actuatorContrComboBox.verticalCenter
                anchors.left: parent.left
                font.family: Style.regular.name
                color: "#000000"
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                visible: readUsbFlag ===  true ? true : false
            }
            BransonComboBox{
                id:actuatorContrComboBox
                currentIndex:acModelCurrentIndex
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.04
                anchors.left:actuatorContrText.right
                anchors.leftMargin: Math.round(39 * Style.scaleHint)
                minWidth: Math.round(150 * Style.scaleHint)
                minHeight: Math.round(24 * Style.scaleHint)
                textFontSize :Math.round(10* Style.scaleHint)
                comboBoxBorderColor:"transparent"
                comboBoxColor:BransonStyle.backgroundColor
                visible: readUsbFlag ===  true ? true : false
                model:actuatorControllerModel
                onCurrentIndexChanged:
                {
                    acModelCurrentIndex = currentIndex
                }
            }
            ProgressBar
            {
                id: acProgress
                height: Math.round(6 * Style.scaleHint)
                anchors.left: actuatorContrComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.right: firmwareUpgradeACRect.right
                anchors.rightMargin: parent.width*0.05
                anchors.top: acTxtProgressTitle.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                value: actuatorContrComboBox.currentText === emptyList ? 0.0 : 0.5
                visible: upgradeBtnFlag? true: false
            }

            Text {
                id: acTxtProgressTitle
                anchors.left: actuatorContrComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.045
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.70
                font.family: Style.regular.name
                color: Style.blackFontColor
                text: actuatorContrComboBox.currentText === emptyList ? "" : qmltextProgress
                visible: upgradeBtnFlag? true: false
            }
        }

        Rectangle
        {
            id:firmwareUpgradeHMIRect
            height: parent.height * 0.12
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            anchors.top: firmwareUpgradeACRect.bottom
            anchors.topMargin: parent.height * 0.04
            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.04
            color: "transparent"

            Text {
                id: hmiText
                text: qmltextFIRMWARE_UPGRADE_HMI
                anchors.verticalCenter:hmiComboBox.verticalCenter
                anchors.left: parent.left
                font.family: Style.regular.name
                color: "#000000"
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.80
                visible: readUsbFlag ===  true ? true : false
            }

            BransonComboBox{
                id:hmiComboBox
                currentIndex: hmiModelCurrentIndex
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.04
                anchors.left:hmiText.right
                anchors.leftMargin: Math.round(70 * Style.scaleHint)
                minWidth: Math.round(150 * Style.scaleHint)
                minHeight: Math.round(24 * Style.scaleHint)
                textFontSize :Math.round(10* Style.scaleHint)
                comboBoxBorderColor:"transparent"
                comboBoxColor:BransonStyle.backgroundColor
                visible: readUsbFlag ===  true ? true : false
                model:hmiModel
                onCurrentIndexChanged:
                {
                    hmiModelCurrentIndex = currentIndex
                }
            }

            ProgressBar
            {
                id: uiProgress
                height: Math.round(6 * Style.scaleHint)
                anchors.left: hmiComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.right: firmwareUpgradeHMIRect.right
                anchors.rightMargin: parent.width*0.05
                anchors.top: uiTxtProgressTitle.bottom
                anchors.topMargin: Math.round(2 * Style.scaleHint)
                value: hmiComboBox.currentText === emptyList ? 0.0 : 0.5
                visible: upgradeBtnFlag? true: false
            }

            Text {
                id: uiTxtProgressTitle
                anchors.left: hmiComboBox.right
                anchors.leftMargin: Math.round(18 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.045
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.70
                font.family: Style.regular.name
                color: Style.blackFontColor
                text: hmiComboBox.currentText === emptyList ? "" : qmltextProgress
                visible: upgradeBtnFlag? true: false
            }
        }
        Row
        {
            id:buttons
            anchors.top:firmwareUpgradeHMIRect.bottom
            topPadding:parent.height * 0.07
            anchors.right: parent.right
            rightPadding: parent.height * 0.10
            spacing: parent.width *0.023
            visible: readUsbFlag ===  true ? true : false

            BransonPrimaryButton{
                id: upgradeButton
                width: Math.round(80 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
                text: qmltextUpgrade
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                buttonColor: Style.buttonColor
                onClicked: {
                    if(supervisoryContrComboBox.currentText === emptyList && actuatorContrComboBox.currentText === emptyList && hmiComboBox.currentText === emptyList)
                    {
                        softwareUpgradePopupMsg.qmltextLabel = qmltextWarningLabel
                        softwareUpgradePopupMsg.qmltextWarningDialog = qmltextSelectFile
                        softwareUpgradePopupMsg.visible = true
                    }
                    else
                    {
                        upgradeBtnFlag = true
                        SoftwareUpgradeInterface.softwareUpgradeRequest(supervisoryContrComboBox.currentText,actuatorContrComboBox.currentText,hmiComboBox.currentText)
                        if(supervisoryContrComboBox.currentText !== emptyList)
                        {
                            scTxtProgressTitle.text = qmltextProgress
                        }
                        if(actuatorContrComboBox.currentText.currentText !== emptyList)
                        {
                            acTxtProgressTitle.text = qmltextProgress
                        }
                        if(hmiComboBox.currentText !== emptyList)
                        {
                            uiTxtProgressTitle.text = qmltextProgress
                        }
                    }
                }
            }

            BransonPrimaryButton{
                id: doneButton
                width: Math.round(80 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                fontSize:Math.round(Style.style1 * Style.scaleHint) * 0.80
                text: qmltextDone
                textColor: Style.buttonTextColor
                font.family: Style.regular.name
                font.weight : Font.DemiBold
                buttonColor: Style.buttonColor
                onClicked:
                {
                    upgradeBtnFlag = false
                    readUsbFlag = false
                    supervisoryContrComboBox.currentIndex = 0
                    actuatorContrComboBox.currentIndex = 0
                    hmiComboBox.currentIndex = 0
                    scTxtProgressTitle.text = emptyProgressStatus
                    acTxtProgressTitle.text = emptyProgressStatus
                    uiTxtProgressTitle.text = emptyProgressStatus
                    scProgress.value = 0.0
                    acProgress.value = 0.0
                    uiProgress.value = 0.0
                    softwareUpgradePopup.close()
                    ActiveScreen.CurrentActiveScreen  = mainWindow.currentActiveWindow
                }
            }
        }
    }
}


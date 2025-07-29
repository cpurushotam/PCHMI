/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 ConfigUpgrade - This screen is used to displays information about platform config upgrade.

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Dialogs

import "./../Common_Logic"
Popup
{
    closePolicy: Popup.NoAutoClose

    property string qmltextUSBMode       :   qsTr("USB MODE")
    property string qmltextReadUsb       :   qsTr("READ USB")
    property string qmltextUpgrade       :   qsTr("UPGRADE")
    property string qmltextTryAgain      :   qsTr("TRY AGAIN")
    property string qmltextAbort         :   qsTr("ABORT")
    property string qmltextDone          :   qsTr("DONE")
    property string qmltextEthernetMode  :   qsTr("ETHERNET MODE")
    property string qmltextCancel        :   qsTr("CANCEL")
    property string qmltextconfigUpgrade :   qsTr("CONFIGURATION UPGRADE")

    property string qmltextSelectMode    :   qsTr("To begin configuration upgrade, select from below options")
    property string qmltextWarning       :   qsTr("Warning: Please connect USB device and do not remove until configurartion upgrade is completed.")
    property string qmltextNote          :   qsTr("The welder is restarting, please wait...")
    property string qmltextUpgradeSuccess:   qsTr("Configuration files has been upgraded successfully")
    property string qmltextConfigVersion :   qsTr("Configuration Version : ")
    property string qmltextConfigDate    :   qsTr(" Configuration Date : ")
    property string qmltextRestartAck    :   qsTr("Welder restarted successfully")
    property string qmltextBrowse        :   qsTr("BROWSE")
    property string qmltextSelectFiles   :   qsTr("Select configuration files path")
    property string qmltextConfirmation  :   "CONFIRMATION"

    property var    qmlTextArray: [qmltextUSBMode, qmltextReadUsb, qmltextUpgrade, qmltextTryAgain,
                                   qmltextAbort, qmltextDone, qmltextEthernetMode, qmltextCancel,
                                   qmltextconfigUpgrade, qmltextSelectMode, qmltextWarning, qmltextNote,
                                   qmltextUpgradeSuccess, qmltextConfigVersion, qmltextConfigDate,
                                   qmltextRestartAck, qmltextBrowse,qmltextSelectFiles, qmltextConfirmation]

    readonly property int cmd_usb_mode_select       : 0x51
    readonly property int cmd_usb_read_version      : 0x52
    readonly property int cmd_usb_start_upgrade     : 0x53
    readonly property int cmd_eth_mode_select       : 0x61
    readonly property int cmd_eth_upload_config     : 0x62
    readonly property int cmd_eth_start_upgrade     : 0x63

    readonly property int usbMode:               0
    readonly property int ethernetMode:          1

    property int        command:                -1
    property int        selectedMode:           -1
    property string     configFilePath:""

    /* Enum declaration for text index */
    QtObject
    {
        id: textEnum
        readonly property int textUSBModeIdx:               0
        readonly property int textReadUsbIdx:               1
        readonly property int textUpgradeIdx:               2
        readonly property int textTryAgainIdx:              3
        readonly property int textAbortIdx:                 4
        readonly property int textDoneIdx:                  5
        readonly property int textEthernetModeIdx:          6
        readonly property int textCancelIdx:                7
        readonly property int textconfigUpgradeIdx:         8
        readonly property int textSelectModeIdx:            9
        readonly property int textWarningIdx:               10
        readonly property int textNoteIdx:                  11
        readonly property int textUpgradeSuccessIdx:        12
        readonly property int textConfigVersionIdx :        13
        readonly property int textConfigDateIdx :           14
        readonly property int textRestartAckIdx :           15
        readonly property int textBrowseIdx :               16
        readonly property int textSelectFilesIdx:           17
        readonly property int textConfirmationIdx :         18
    }

    /* To update texts as per selected language */
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.PLATFORM_CONFIG_UPGRADE, qmlTextArray)
        qmltextUSBMode          = qmlTextArray[textEnum.textUSBModeIdx]
        qmltextReadUsb          = qmlTextArray[textEnum.textReadUsbIdx]
        qmltextUpgrade          = qmlTextArray[textEnum.textUpgradeIdx]
        qmltextTryAgain         = qmlTextArray[textEnum.textTryAgainIdx]
        qmltextAbort            = qmlTextArray[textEnum.textAbortIdx]
        qmltextDone             = qmlTextArray[textEnum.textDoneIdx]
        qmltextEthernetMode     = qmlTextArray[textEnum.textEthernetModeIdx]
        qmltextCancel           = qmlTextArray[textEnum.textCancelIdx]
        qmltextconfigUpgrade    = qmlTextArray[textEnum.textconfigUpgradeIdx]
        qmltextSelectMode       = qmlTextArray[textEnum.textSelectModeIdx]
        qmltextWarning          = qmlTextArray[textEnum.textWarningIdx]
        qmltextNote             = qmlTextArray[textEnum.textNoteIdx]
        qmltextUpgradeSuccess   = qmlTextArray[textEnum.textUpgradeSuccessIdx]
        qmltextConfigVersion    = qmlTextArray[textEnum.textConfigVersionIdx]
        qmltextConfigDate       = qmlTextArray[textEnum.textConfigDateIdx]
        qmltextRestartAck       = qmlTextArray[textEnum.textRestartAckIdx]
        qmltextBrowse           = qmlTextArray[textEnum.textBrowseIdx]
        qmltextSelectFiles      = qmlTextArray[textEnum.textSelectFilesIdx]
        qmltextConfirmation     = qmlTextArray[textEnum.textConfirmationIdx]
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
    }

    /* Timer for delay */
    Timer {
        id: timer
    }

    /* Delay in milliseconds */
    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }

    /* On configuartion upgrade success */
    function upgradeSuccess()
    {
        configUpgradeTextHeader.text = qmltextConfirmation
        /* Enable text of upgrade success */
        upgradeSuccessText.visible = true        

        /* Disable all others texts */
        statusText.visible = false
        noteText.visible = false
        noteTextRect.visible = false
        usbConfigInfoText.visible = false;

        /* Enable abort button and change text to done */
        abortButton.visible = true;
        abortButton.text = qmltextDone
    }

    /* Set default parameters on close window */
    function setDefaultParameters()
    {
        /* Disable all texts */
        upgradeSuccessText.visible = false
        statusText.visible = false
        noteText.visible = false
        noteTextRect.visible = false
        warningText.visible = false
        usbConfigInfoText.visible = false

        /* Change reactangle background of command button to transparent */
        usbConfigInfoLayoutRect.color="transparent"

        /* Update window size to select mode window size */
        configUpgrade.width = mainWindow.width*0.40
        configUpgrade.height = mainWindow.height*0.40

        /* Change anchors of USB command mode button */
        usbModeCommandButton.anchors.topMargin = usbConfigInfoLayoutRect.height*0.55
        usbModeCommandButton.anchors.leftMargin= usbConfigInfoLayoutRect.width*0.050

        /* Enable and change text of USB and ethernet command mode button*/
        ethUploadFileInfoText.visible = false
        usbModeCommandButton.visible = true;
        ethernetModeCommandButton.visible = true
        usbModeCommandButton.text = qmltextUSBMode;
        configUpgradeTextHeader.text = qmltextconfigUpgrade


        /* Ethernet mode*/
        ethernetModeCommandButton.text = qmltextEthernetMode
        ethUpgradeButtonColor.color = "#A9A9B1"
        ethUploadFilesTextField.visible=false
        ethUpgradeButton.visible = false
        ethUpgradeButton.enabled = false
        abortButton.anchors.rightMargin = parent.width*0.05

        /*Initilize command */
        command = -1
        selectedMode = -1

        /* Enable USB mode command button */
        usbModeCommandButton.enabled = true

        /* if abort action perform then send default(-1) command to ASC to exit comm*/
        if (abortButton.text === qmltextAbort)
        {
            configurationUpgrade.sendCommand(command)
        }

        /* Enable and Change abort button to cancel button */
        abortButton.visible = true; abortButton.text = qmltextCancel
    }

    /* Prepare command based on selection of upgrade mode */
    function createCommand()
    {
        switch(selectedMode)
        {
            case usbMode:
            {
                /* While processing command disable USB mode command button */
                usbModeCommandButton.enabled = false

                /* on Select USB mode or Try again send  cmd_usb_mode_select i.e 51 */
                if ((usbModeCommandButton.text === qmltextUSBMode) || (usbModeCommandButton.text === qmltextTryAgain))
                {
                    /* Request USB command to send */
                    command = cmd_usb_mode_select

                    /* Disable Ethernet Mode button and select mode text */
                    ethernetModeCommandButton.visible = false
                    selectModeText.visible = false

                    /* Change cancel button to abort button */
                    abortButton.visible = true
                    abortButton.text = qmltextAbort
                }
                /* On Selection of Read USB, send request read USB command*/
                else if (usbModeCommandButton.text === qmltextReadUsb)
                {
                    /* Read USB command to send */
                    command = cmd_usb_read_version;
                }
                /* On Selection of Upgrade, send request configuration upgrade command*/
                else if (usbModeCommandButton.text === qmltextUpgrade)
                {
                    /* Upgrade command to send */
                    command = cmd_usb_start_upgrade;
                }
                break
            }
            case ethernetMode:
            {
                /* On selection of ethernet mode send  cmd_eth_mode_select i.e 61 */
                if (ethernetModeCommandButton.text === qmltextEthernetMode)
                {
                    /* Request Ethernet command to send */
                    command = cmd_eth_mode_select

                    ethernetModeCommandButton.text = qmltextBrowse

                    /* Disable USB Mode button and select mode text */
                    usbModeCommandButton.visible = false
                    selectModeText.visible = false

                    /* Change cancel button to abort button */
                    abortButton.visible = true
                    abortButton.text = qmltextAbort

                    ethUploadFilesTextField.visible = true

                    /* Send command - add command into command queue */
                    configurationUpgrade.sendCommand(command)

                }
                else if ((ethernetModeCommandButton.text === qmltextBrowse) || (ethernetModeCommandButton.text === qmltextTryAgain))
                {
                    folderDialog.open()                    
                }
                break;
            }
            default:
            {
                console.log("Invalid selected mode")
            }
        }
    }

    function handleResponse()
    {
        /* Update statusText */
        statusText.text = configurationUpgrade.statusMessage

        switch(selectedMode)
        {
            case usbMode:
            {
                /* Enable USB mode command button */
                usbModeCommandButton.enabled = true

                /* On Failure */
                if (statusText.text !== "")
                {
                    /* Enable statusText and change color of text */
                    statusText.visible = true
                    statusText.color = "red"

                    /* Disable configuration info details */
                    usbConfigInfoText.visible = false
                    usbConfigInfoLayoutRect.color="transparent"

                    /* Change anchors of command window */
                    usbModeCommandButton.anchors.topMargin = usbConfigInfoLayoutRect.height*0.50

                    /* Change text of USB mode command button to TRY AGAIN*/
                    usbModeCommandButton.text = qmltextTryAgain
                }
                else /* On Success */
                {
                    usbModeCommandButton.anchors.topMargin = usbConfigInfoLayoutRect.height*0.10
                    statusText.visible = false
                    if (command == cmd_usb_mode_select)
                    {
                        /* Change text of USB mode command button READ USB */
                        usbModeCommandButton.text = qmltextReadUsb
                    }
                    else if (command == cmd_usb_read_version)
                    {
                        /* Change text of USB mode command button UPGRADE */
                        usbModeCommandButton.text = qmltextUpgrade

                        /* On Read USB success, Enable configuration info details */
                        usbConfigInfoText.visible = true
                        usbConfigInfoLayoutRect.color="#EEEEF3"
                        usbConfigInfoText.text =  qmltextConfigVersion + configurationUpgrade.readConfiVersion() + qmltextConfigDate + configurationUpgrade.readConfigDate()
                    }
                    else if (command == cmd_usb_start_upgrade)
                    {
                        /* Disable USB mode command button */
                        usbModeCommandButton.visible = false

                        /* On Upgrade success, enable status text and note to user restaring welder */
                        statusText.visible = true
                        statusText.text = qmltextUpgradeSuccess
                        statusText.color = "#0e0f0f"
                        noteText.visible = true
                        noteTextRect.visible = true

                        /* Disable warning text and abort button */
                        warningText.visible = false
                        abortButton.visible = false
                        usbConfigInfoLayoutRect.color="transparent"

                        /* TODO: HMI switches other welder when current welder is being rebooted after configuration upgrade */
                        delay(35000, function() {upgradeSuccess();})
                    }
                }
                break
            }
            case ethernetMode:
            {
                /* On Failure */
                if (statusText.text !== "")
                {
                    /* Enable statusText and change color of text */
                    statusText.visible = true
                    statusText.color = "red"

                    /* Disable configuration info details */
                    ethUploadFileInfoText.visible = false
                }
                else /* On Success */
                {
                    statusText.visible = false
                    if (command == cmd_eth_mode_select)
                    {

                    }
                    else if (command == cmd_eth_upload_config)
                    {
                        /* On Read USB success, Enable configuration info details */
                        ethUpgradeButton.enabled=true
                        ethUpgradeButtonColor.color = "#141464"
                        ethUploadFileInfoText.visible = true
                        ethUploadFileInfoText.text= qmltextConfigVersion + configurationUpgrade.readConfiVersion() + qmltextConfigDate + configurationUpgrade.readConfigDate()
                    }
                    else if (command == cmd_eth_start_upgrade)
                    {
                        /* Disable ethernet mode command button */
                        ethernetModeCommandButton.visible = false

                        /* On Upgrade success, enable status text and note to user restaring welder */
                        statusText.visible = true
                        noteText.visible = true
                        noteTextRect.visible = true
                        statusText.text = qmltextUpgradeSuccess
                        statusText.color = "#0e0f0f"

                        ethUploadFileInfoText.visible = false
                        ethUploadFilesTextField.visible = false
                        ethUpgradeButton.visible = false
                        abortButton.visible = false
                        abortButton.anchors.rightMargin = parent.width*0.05

                        /* TODO: HMI switches other welder when current welder is being rebooted after configuration upgrade. */
                       delay(35000, function() {upgradeSuccess();})
                    }
                }
                break
            }
        }
    }

    /* Slot on signal update screen */
    Connections
    {
        target: configurationUpgrade
        function onUpdatedScreen()
        {
            handleResponse()
        }
    }

    id: configUpgradePopup
    dim: true
    modal: true
    focus: true

    background: Rectangle {
        id:backgroundRectMain
        color:"transparent"
    }
    Overlay.modal: Rectangle {
        color: "#aacfdbe7"
    }

    Rectangle
    {
        anchors.fill: parent
        id:root
        color:"white"
        clip:true

        /* Rectangle for configUpgradeTextHeader */
        Rectangle {
            id: headerRect
            anchors.left: parent.left
            anchors.right: parent.right
            width: parent.width
            height: parent.height*0.15
            color: '#1261a6'

            Text {
                id: configUpgradeTextHeader
                text:qmltextconfigUpgrade
                font.pointSize: parent.height*0.30
                color: "white"
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.05
                anchors.topMargin: parent.height*0.35
                anchors.top: parent.top
            }
        }

        /* Rectangle for USB Mode command button */
        Rectangle
        {
            id:usbConfigInfoLayoutRect
            width: parent.width*0.94
            height: parent.height*0.35
            color:"transparent"
            visible: true            
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.20
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03

            /* USB Mode command button */
            BransonPrimaryButton
            {
                id:usbModeCommandButton
                visible:true
                enabled: true
                background: Rectangle {color: "#141464"}

                width: usbConfigInfoLayoutRect.width*0.36; height: usbConfigInfoLayoutRect.height*0.35
                anchors.top: usbConfigInfoLayoutRect.top
                anchors.topMargin: usbConfigInfoLayoutRect.height*0.55
                anchors.left: usbConfigInfoLayoutRect.left
                anchors.leftMargin: usbConfigInfoLayoutRect.width*0.050

                fontSize: usbConfigInfoLayoutRect.height*0.15
                text: qmltextUSBMode
                onClicked:
                {
                    selectedMode = usbMode

                    configUpgradeTextHeader.text = qmltextUSBMode

                    /* Change to command window */
                    configUpgrade.width = mainWindow.width*0.50
                    configUpgrade.height = mainWindow.height*0.45

                    if (usbModeCommandButton.text !== qmltextTryAgain)
                    {
                        /* Change anchors of USB command mode button */
                        usbModeCommandButton.anchors.topMargin = usbConfigInfoLayoutRect.height*0.10
                        usbModeCommandButton.anchors.leftMargin= usbConfigInfoLayoutRect.width*0.05
                    }

                    /* Enable warningText on select USB mode */
                    warningText.visible = true

                    /* Prepare command */
                    createCommand()

                    /* Send command - add command into command queue */
                    configurationUpgrade.sendCommand(command)
                }
            }
            Text {
                id:usbConfigInfoText
                font.pointSize: usbConfigInfoLayoutRect.width*0.018; color: "#43434B"
                anchors.top: usbModeCommandButton.bottom
                anchors.topMargin: parent.height*0.25
                anchors.left: usbModeCommandButton.left
                visible: false
            }
        }

        /* Ethernet mode command button */
        BransonPrimaryButton
        {
            id:ethernetModeCommandButton

            visible: true
            background: Rectangle {color: "#141464"}
            width: parent.width*0.30; height: parent.height*0.12

            fontSize: parent.height*0.05
            text: qmltextEthernetMode

            anchors.top: usbConfigInfoLayoutRect.top
            anchors.topMargin: usbConfigInfoLayoutRect.height*0.55
            anchors.left: usbConfigInfoLayoutRect.left
            anchors.leftMargin: usbConfigInfoLayoutRect.width*0.50
            onClicked:
            {
                selectedMode = ethernetMode

                configUpgradeTextHeader.text = qmltextEthernetMode

                /* Change to command window */
                configUpgrade.width = mainWindow.width*0.50
                configUpgrade.height = mainWindow.height*0.45

                /* Prepare command */
                createCommand()

                ethUpgradeButton.visible = true
                abortButton.anchors.rightMargin = parent.width*0.40
            }
        }

        /* Ethernet mode upgrade button */
        BransonPrimaryButton
        {
            id:ethUpgradeButton

            visible: false
            background: Rectangle {id:ethUpgradeButtonColor; color: "#A9A9B1"}
            width: parent.width*0.30; height: parent.height*0.12

            fontSize: parent.height*0.05
            text: qmltextUpgrade
            enabled : false

            anchors.bottom:parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 30
            anchors.rightMargin: parent.width*0.05

            onClicked:{
                if (ethUpgradeButton.enabled === true)
                {
                    /* Request Ethernet upload config files command to send */
                    command = cmd_eth_start_upgrade

                    /* Send command - add command into command queue */
                    configurationUpgrade.sendCommand(command)
                }
            }
        }

        /* Abort button */
        BransonPrimaryButton
        {
            id:abortButton

            visible: true
            background: Rectangle {color: "#A9A9B1"}
            width: parent.width*0.30; height: parent.height*0.12

            fontSize: parent.height*0.05
            text: qmltextCancel

            anchors.bottom:parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 30
            anchors.rightMargin: parent.width*0.05

            onClicked:{
                /* Set default parameter and close popup */
                setDefaultParameters()
                configUpgradePopup.close()
            }
        }

        /* Text to display warning message */
        Text {
            id: warningText
            visible: false
            font.pointSize: parent.height*0.036; color: "#858c8c"
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.25
            anchors.left: usbConfigInfoLayoutRect.left
            text:qmltextWarning
            wrapMode: Text.WordWrap
        }

        /* Text to display note */
        Rectangle
        {
            id:noteTextRect
            width: parent.width*0.94
            height: parent.height*0.25
            color: "#EEEEF3"
            visible: false
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.40
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.03
            Text {
                id: noteText
                visible: false
                font.family: "Helvetica";font.pointSize: noteTextRect.height*0.16; color: "#284D96"
                anchors.left: noteTextRect.left
                anchors.top: noteTextRect.top
                anchors.leftMargin: noteTextRect.width*0.05
                anchors.topMargin: parent.height*0.30
                text:qmltextNote
            }
        }

        /* Text to select mode */
        Text {
            id: selectModeText
            visible: true
            font.family: "Helvetica"; font.pointSize: parent.width*0.025; color: "black"
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.20
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.09
            text:qmltextSelectMode
        }

        /* Text to display status message */
        Text {
            id: statusText
            visible: false
            font.family: "Helvetica"; font.pointSize: parent.height*0.04; font.bold:true; color: "#0e0f0f"
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.20
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.050
        }

        /* Text to display upgrade success  message */
        Text {
            id: upgradeSuccessText
            visible: false
            font.family: "Helvetica"; font.pointSize: parent.height*0.04; font.bold:true ; color: "#0e0f0f"
            anchors.centerIn: parent
            text: qmltextRestartAck
        }

        FileDialog {
            id: folderDialog
            onAccepted:
            {
                configFilePath = selectedFiles.toString()
                ethUploadFilesTextField.text = configFilePath.substring(7, configFilePath.lastIndexOf("/"))

                if (ethUploadFilesTextField.text.length > 0)
                {
                    configurationUpgrade.setConfigFilesPath(ethUploadFilesTextField.text)

                    /* Request Ethernet upload config files command to send */
                    command = cmd_eth_upload_config

                    /* Send command - add command into command queue */
                    configurationUpgrade.sendCommand(command)
                }
            }
        }

        Text {
            id:ethUploadFileInfoText
            font.pointSize: parent.height*0.03; color: "#43434B"
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.60
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.05
            visible: false
        }

        BransonTextField {
           id: ethUploadFilesTextField
           visible: false
           font.pixelSize:parent.width*0.020
           maximumLength : 150
           placeholderText:qmltextSelectFiles

           focus: true
           width: parent.width*0.44; height: parent.height*0.12

           anchors.top: parent.top
           anchors.topMargin: parent.height*0.395
           anchors.left: parent.left
           anchors.leftMargin: parent.width*0.05
       }        
    }
}


/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file displays the Batch Setting Screen.

 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Layouts
import Com.Branson.SystemTypeDef 1.0
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Qt5Compat.GraphicalEffects
import "../Common_Logic"

Item {

    property string qmltextMenuName                    : "BATCH SETUP"
    property string qmltextCountWithAlarms             : "COUNT WITH ALARMS"
    property string qmltextBatchCounterLimit           : "BATCH COUNTER LIMIT"
    property string qmltextBatchCounter                : "BATCH COUNTER"
    property string qmltextBatchId                     : "BATCH ID"
    property string qmltextResetBatchCounter           : "RESET BATCH COUNTER"
    property string qmltextCancel                      : "CANCEL"
    property string qmltextDone                        : "DONE"
    property string qmltextPopupMsg                    : "Are you sure want to reset batch counter?"
    property string qmltextBatchCounterReset           : "Modifying the batch count limit cause\nbatch counter reset."
    property string qmltextAlert                       : "Alert"

    property var qmlTextArray: [qmltextMenuName, qmltextCountWithAlarms, qmltextBatchCounterLimit, qmltextBatchCounter, qmltextBatchId, qmltextResetBatchCounter, qmltextCancel,
                                qmltextDone, qmltextPopupMsg, qmltextBatchCounterReset, qmltextAlert]

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    signal batchCountLimitUpdate()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_BATCH_SETTING, qmlTextArray)
        qmltextMenuName = qmlTextArray[textEnum.textBatchSetupIdx]
        qmltextCountWithAlarms = qmlTextArray[textEnum.textCountWithAlarmsIdx]
        qmltextBatchCounterLimit = qmlTextArray[textEnum.textBatchCounterLimitIdx]
        qmltextBatchCounter = qmlTextArray[textEnum.textBatchCounterIdx]
        qmltextBatchId = qmlTextArray[textEnum.textBatchIdIdx]
        qmltextResetBatchCounter = qmlTextArray[textEnum.textResetBatchCounterIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextDone = qmlTextArray[textEnum.textDoneIdx]
        qmltextPopupMsg = qmlTextArray[textEnum.textPopupMsgIdx]
        qmltextBatchCounterReset = qmlTextArray[textEnum.textBatchCounterResetIdx]
        qmltextAlert = qmlTextArray[textEnum.textAlerIdx]
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    /*To invoke confirmation popup*/
    Connections
    {
        target: RecipeLabData
        function onBatchCountLimitUpdate()
        {
            confirmationPopup2.visible = true
            mainWindow.opacityFlag = true
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject
    {
        id:textEnum
        readonly property int textBatchSetupIdx              : 0
        readonly property int textCountWithAlarmsIdx         : 1
        readonly property int textBatchCounterLimitIdx       : 2
        readonly property int textBatchCounterIdx            : 3
        readonly property int textBatchIdIdx                 : 4
        readonly property int textResetBatchCounterIdx       : 5
        readonly property int textCancelIdx                  : 6
        readonly property int textDoneIdx                    : 7
        readonly property int textPopupMsgIdx                : 8
        readonly property int textBatchCounterResetIdx       : 9
        readonly property int textAlerIdx                    : 10
    }

    QtObject
    {
        id:paramEnum
        readonly property int paramBatchCounter              : 0
        readonly property int paramBatchCounterLimit         : 1
    }

    BransonLeftBorderRectangle
    {
        id: batchSetupEnableTitle
        width: parent.width*0.48
        height: parent.height*0.25
        checked: batchSetupEnableSwitch.checked

        Text
        {
            id: txtBatchSetupTitle
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.top: parent.top
            text: qmltextMenuName
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }

        Image
        {
            id: infoIcon
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            source: "qrc:/Images/info.png"
            width: parent.width*0.08
            height: parent.width*0.08
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }

        BransonSwitch
        {
            id: batchSetupEnableSwitch
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.25
            maxWidth: rectHeight*1.3
            maxHeight: rectHeight*1.3
            rectWidth: parent.width* 0.1
            rectHeight: parent.height* 0.15
            checked: RecipeLabData.BatchSetup
            onCheckedChanged:
            {
                if(batchSetupEnableSwitch.checked)
                {
                    RecipeLabData.BatchSetup = true
                }

                else
                {
                    RecipeLabData.BatchSetup = false
                }
            }
        }

        MouseArea
        {
            id:clickBatchSetupEnable
            anchors.fill: batchSetupEnableSwitch
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                batchSetupEnableSwitch.toggle()
            }
        }
    }

    BransonLeftBorderRectangle
    {
        id: countWithAlarmsEnableTitle
        width: parent.width*0.48
        height: parent.height*0.25
        checked: countWithAlarmsEnableSwitch.checked
        anchors.left: batchSetupEnableTitle.right
        anchors.leftMargin: height*0.15
        Text
        {
            id: txtcountWithAlarmsTitle
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.top: parent.top
            text: qmltextCountWithAlarms
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }

        Image
        {
            id: infoIconCountWithAlarms
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            source: "qrc:/Images/info.png"
            width: parent.width*0.08
            height: parent.width*0.08
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }

        BransonSwitch
        {
            id: countWithAlarmsEnableSwitch
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.25
            maxWidth: rectHeight*1.3
            maxHeight: rectHeight*1.3
            rectWidth: parent.width* 0.1
            rectHeight: parent.height* 0.15
            checked: RecipeLabData.CountWithAlarms
            onCheckedChanged:
            {
                if(countWithAlarmsEnableSwitch.checked)
                {
                    RecipeLabData.CountWithAlarms = true
                }

                else
                {
                    RecipeLabData.CountWithAlarms = false
                }
            }
        }
        MouseArea{
            id:clickCountWithAlarmsEnable
            anchors.fill: countWithAlarmsEnableSwitch
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                countWithAlarmsEnableSwitch.toggle()
            }
        }
    }

    Rectangle
    {
        id: batchCounterLimitTitle
        color:Style.contentBackgroundColor
        anchors.left: parent.left
        anchors.top: batchSetupEnableTitle.bottom
        anchors.topMargin: height * 0.15
        width: parent.width*0.48
        height: parent.height*0.25
        enabled: batchSetupEnableSwitch.checked

        Text
        {
            id:txtBatchCountLimit
            text: qmltextBatchCounterLimit
            font.pixelSize: parent.height * 0.18
            color: Style.blackFontColor
            anchors.top :parent.top
            anchors.topMargin: parent.height * 0.15
            anchors.left :parent.left
            anchors.leftMargin: parent.height * 0.15
        }

        BransonLineEdit
        {
            id:batchCounterLimitInputText
            width:parent.width*0.90
            height:parent.height * 0.3
            anchors.top :parent.top
            anchors.topMargin: parent.height * 0.5
            anchors.left :parent.left
            anchors.leftMargin: parent.height * 0.15
            font.pixelSize: parent.height * 0.18
            background: Rectangle
            {
                color: "#FFFFFF"
                radius: Math.round(5 * Style.scaleHint)
                border.color: "#707070"
                border.width: 1
            }

            focus: true
            text: RecipeLabData.BatchCounterLimit
            selectByMouse: true
            mouseSelectionMode: TextInput.SelectWords

            MouseArea
            {
                id:  batchCounterLimitMouseArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    mainWindow.showPrimaryNumpad(qmltextBatchCounterLimit, "", 0, RecipeLabData.getMinBatchSettingParametersValue(paramEnum.paramBatchCounterLimit), RecipeLabData.getMaxBatchSettingParametersValue(paramEnum.paramBatchCounterLimit), RecipeLabData.BatchCounterLimit.toFixed(0))
                }
            }
        }
    }

    Rectangle
    {
        id: batchCounterTitle
        color:Style.whiteBackgroundColor
        anchors.top: countWithAlarmsEnableTitle.bottom
        anchors.topMargin: height * 0.15
        anchors.left: batchCounterLimitTitle.right
        anchors.leftMargin: height * 0.15
        width: parent.width*0.48
        height: parent.height*0.25
        enabled: batchSetupEnableSwitch.checked

        Text
        {
            id:txtBatchCounter
            text: qmltextBatchCounter
            font.pixelSize: parent.height * 0.18
            color: Style.blackFontColor
            anchors.top :parent.top
            anchors.topMargin: parent.height * 0.15
            anchors.left :parent.left
            anchors.leftMargin: parent.height * 0.15
        }

        Text
        {
            id: textBatchCounter
            text: RecipeLabData.BatchCounter
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.15
        }
    }

    InputPanel
    {
        id: inputPanelBatchID
        z: 1
        y: mainWindow.showHeight*0.85
        height: mainWindow.showHeight *0.15
        width: mainWindow.showWidth
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        visible: Qt.inputMethod.visible
    }

    Rectangle
    {
        id: batchIDTitle
        color:Style.contentBackgroundColor
        anchors.top: batchCounterLimitTitle.bottom
        anchors.topMargin: height * 0.15
        anchors.left: parent.left
        width: parent.width*0.48
        height: parent.height*0.25
        enabled: batchSetupEnableSwitch.checked

        Text
        {
            id:txtBatchID
            text: qmltextBatchId
            font.pixelSize: parent.height * 0.18
            color: Style.blackFontColor
            anchors.top :parent.top
            anchors.topMargin: parent.height * 0.15
            anchors.left :parent.left
            anchors.leftMargin: parent.height * 0.15
        }

        BransonLineEdit
        {
            id:batchIDInputText
            width:parent.width*0.90
            height:parent.height * 0.3
            anchors.top :parent.top
            anchors.topMargin: parent.height * 0.5
            anchors.left :parent.left
            anchors.leftMargin: parent.height * 0.15
            font.pixelSize: parent.height * 0.18
            isBatchIDField: true

            background: Rectangle
            {
                color: "#FFFFFF"
                radius: Math.round(5 * Style.scaleHint)
                border.color: "#707070"
                border.width: 1
            }

            focus: true
            text: RecipeLabData.BatchId
            selectByMouse: true
            mouseSelectionMode: TextInput.SelectWords

            onAccepted:
            {
                batchIDInputText.focus = false
            }

            onActiveFocusChanged:
            {
                if(activeFocus)
                {
                    inputPanelBatchID.visible = true
                }

                else
                {
                    inputPanelBatchID.visible = false
                    RecipeLabData.BatchId = batchIDInputText.text
                }
            }

            onPressed:
            {
               isBatchIDField = true
            }
        }
    }

    BransonConfirmationPopup
    {
        id: confirmationPopup
        visible:false
        qmltextWarningMessage: qmltextPopupMsg
        x:mainWindow.showWidth *0.25
        y:mainWindow.showHeight *0.01
        focus:true
        width: parent.width*0.70
        height: parent.width*0.30
        closePolicy: Popup.NoAutoClose

        onCancelButtonClicked:
        {
            confirmationPopup.visible = false
            mainWindow.opacityFlag = false
        }

        onOkButtonClicked:
        {
            RecipeLabData.BatchCounter = 0
            confirmationPopup.visible = false
            mainWindow.opacityFlag = false
        }
    }

    BransonConfirmationPopup
    {
        id: confirmationPopup2
        visible: false
        qmltextWarningMessage: qmltextBatchCounterReset
        x: mainWindow.showWidth * 0.25
        y: mainWindow.showHeight * 0.01
        focus: true
        width: parent.width * 0.70
        height: parent.width * 0.30
        closePolicy: Popup.NoAutoClose

        onCancelButtonClicked:
        {
            confirmationPopup2.visible = false
        }

        onOkButtonClicked:
        {
            RecipeLabData.batchCountLimitUpdateConfirmed()
            RecipeLabData.BatchCounter = 0
            confirmationPopup2.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }
    }

    BransonPrimaryButton
    {
        id: btnResetBatchCounter
        implicitWidth: Math.round(170 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        text: qmltextResetBatchCounter
        buttonColor: "#17345C"
        font.family: Style.regular.name
        onClicked:
        {
            confirmationPopup.visible = true
            mainWindow.opacityFlag = true
        }
    }

}

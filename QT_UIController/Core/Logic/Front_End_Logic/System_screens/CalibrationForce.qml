/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the service count information.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/09/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import QtQuick.VirtualKeyboard 2.15
import AxisDefine 1.0
import QtQuick.Layouts 1.15
import Com.Branson.GraphAxisEnum 1.0
import "./../Diagnostics_Screens"
import "./../Common_Logic"


Item
{
    id: calibration
    property string qmlTextMenuName           : "Calibration"
    property string qmlTextCalibrateForce     : "Calibrate Force"
    property string qmlTextPositionLoadCell   : "POSITION LOAD CELL"
    property string qmlTextPressStartSwitches : "Press Start Switches"
    property string qmlEnter1stLoadCell       : "ENTER 1st LOAD CELL"
    property string qmlTextReadings           : "Readings"
    property string qmlTextUnit               : "lbs"
    property string qmlTextContinue           : "Continue"
    property string qmlTextCancel             : "Cancel"
    property string qmlTextCalibrationSaved   : "        Calibration Saved !"
    property string qmlTextConfirmation       : "CONFIRMATION"
    property string qmlTextCalibrationAbort   : " Are You Sure You Want To Abort The Calibration !"
    property string qmlTextYes                : "Yes"
    property string qmlTextNo                 : "No"
    property string qmlTextPleaseWait         : "Please Wait !"
    property string qmlTextClose              : "Close"
    property string qmlTextCalibratePressure  : "CALIBRATE PRESSURE"
    property string qmlTextVerify             : "VERIFY"
    property string qmlReEnterLoadCell        : "RE-ENTER LOAD CELL"
    property string qmlTextCalibrationSaved2  : "  Verify Using Horn Down !"
    property string qmlTextCalibrationAbort2  : "  The Calibration Process Will Be Aborted !"

    property int calibrationCounter : 0
    property bool setupFlag: false
    signal partContactDetected()

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibrateForce, qmlTextPositionLoadCell, qmlTextPressStartSwitches, qmlEnter1stLoadCell, qmlTextReadings, qmlTextUnit,
                                qmlTextContinue, qmlTextCancel, qmlTextCalibrationSaved, qmlTextConfirmation, qmlTextCalibrationAbort, qmlTextYes, qmlTextNo,
                                qmlTextPleaseWait, qmlTextClose, qmlReEnterLoadCell, qmlTextCalibrationSaved2, qmlTextCalibrationAbort2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_FORCE , qmlTextArray)
        qmlTextCalibrateForce  = qmlTextArray[textEnum.textCalibrateForceIdx]
        qmlTextPositionLoadCell  = qmlTextArray[textEnum.textPositionLoadCellIdx]
        qmlTextPressStartSwitches = qmlTextArray[textEnum.textPressStartSwitchesIdx]
        qmlEnter1stLoadCell = qmlTextArray[textEnum.textEnter1stLoadCellIdx]
        qmlTextReadings  = qmlTextArray[textEnum.textReadingsIdx]
        qmlTextUnit  = qmlTextArray[textEnum.textUnitIdx]
        qmlTextContinue  = qmlTextArray[textEnum.textContinueIdx]
        qmlTextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmlTextCalibrationSaved = qmlTextArray[textEnum.textCalibrationSavedIdx]
        qmlTextConfirmation = qmlTextArray[textEnum.textConfirmationIdx]
        qmlTextCalibrationAbort  = qmlTextArray[textEnum.textCalibrationAbortIdx]
        qmlTextYes = qmlTextArray[textEnum.textYesIdx]
        qmlTextNo = qmlTextArray[textEnum.textNoIdx]
        qmlTextPleaseWait  = qmlTextArray[textEnum.textPleaseWaitIdx]
        qmlTextClose  = qmlTextArray[textEnum.textCloseIdx]
        qmlTextCalibratePressure = qmlTextArray[textEnum.textCalibratePressureIdx]
        qmlTextVerify = qmlTextArray[textEnum.textVerifyIdx]
        qmlReEnterLoadCell = qmlTextArray[textEnum.textReEnterLoadCellIdx]
        qmlTextCalibrationSaved2 = qmlTextArray[textEnum.textCalibrationSaved2Idx]
        qmlTextCalibrationAbort2  = qmlTextArray[textEnum.textCalibrationAbort2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibrateForceIdx     : 0
        readonly property int textPositionLoadCellIdx   : 1
        readonly property int textPressStartSwitchesIdx : 2
        readonly property int textEnter1stLoadCellIdx   : 3
        readonly property int textReadingsIdx           : 4
        readonly property int textUnitIdx               : 5
        readonly property int textContinueIdx           : 6
        readonly property int textCancelIdx             : 7
        readonly property int textCalibrationSavedIdx   : 8
        readonly property int textConfirmationIdx       : 7
        readonly property int textCalibrationAbortIdx   : 8
        readonly property int textYesIdx                : 9
        readonly property int textNoIdx                 : 10
        readonly property int textPleaseWaitIdx         : 11
        readonly property int textCloseIdx              : 12
        readonly property int textCalibratePressureIdx  : 13
        readonly property int textVerifyIdx             : 14
        readonly property int textReEnterLoadCellIdx    : 15
        readonly property int textCalibrationSaved2Idx  : 16
        readonly property int textCalibrationAbort2Idx  : 17
    }

    QtObject
    {
        id: unitType
        readonly property int metricUnit     : 0
        readonly property int imperialUnit   : 1
    }

    Component.onCompleted:
    {
        updateLanguage();
//        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE_FORCE)
//        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_FORCE
        CalibrateForce.isScreenReNavigated(true)
        qmlTextUnit = UnitConversion.ForceUnit
        positionLoadCellText.visible = true
        continueBtn.visible = false
        continueBtnPrimary.visible = true
        textBackgroundRect.visible = false
        cancelBtn.visible = false
    }

    onVisibleChanged:
    {
        CalibrateForce.onCalibrationAbortPressed()
    }

    Connections
    {
        target: CalibrateForce
        function onPartContactDetected()
        {
            /*Below section make sure the load cell entering shall be happen
              only after partcontact detected*/
            if(textBackgroundRect.visible)
            {
                responseValidationTimer.interval = 500
                responseValidationTimer.running = true
                responseValidationTimer.start()
            }
        }
    }

    Text
    {
        id: calibrateForceText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrateForce
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
    }

    Text
    {
        id: positionLoadCellText
        visible: (! calibrationSavedText.visible)
        anchors.left: textBackgroundRect.left
        anchors.leftMargin: Math.round(150 * Style.scaleHint)
        anchors.bottom: textBackgroundRect.bottom
        anchors.bottomMargin: Math.round(75 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextPositionLoadCell
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        font.bold: true
    }

    Text
    {
        id: enter1stLoadCellText
        visible: false
        anchors.left: textBackgroundRect.left
        anchors.bottom: textBackgroundRect.top
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlEnter1stLoadCell
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        font.bold: true
    }

    Rectangle
    {
        id: textBackgroundRect
        visible: true
        width: Math.round(500 * Style.scaleHint)
        height: Math.round(150 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: Style.whiteBackgroundColor
        Text
        {
            id: readingsText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextPressStartSwitches
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            font.bold: true
        }
    }

    Rectangle
    {
        id: textBackgroundRect2
        visible: false
        width: Math.round(500 * Style.scaleHint)
        height: Math.round(150 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: Style.whiteBackgroundColor
        Text
        {
            id: readingsText2
            anchors.left: parent.left
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextReadings
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            font.bold: true
        }

        Rectangle
        {
            id: gaugeValueRect2
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            anchors.left: readingsText2.right
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            color: Style.whiteBackgroundColor
            border.color: Style.blackFontColor
            Text
            {
                id: gaugeValueText2
                anchors.left: parent.left
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: (UnitConversion.currentUnit() === unitType.metricUnit) ? CalibrateForce.CalibrationReadings.toFixed(0) :
                                                                               CalibrateForce.CalibrationReadings.toFixed(1)
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.bold: true
            }

            Text
            {
                id: gaugeValueTextUnit
                anchors.right: parent.right
                anchors.rightMargin: Math.round(2 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: mainWindow.qmltextForceUnit
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.bold: true
            }

            MouseArea
            {
                id: gaugeValueRect2MA
                anchors.fill: parent
                onClicked:
                {
                    if(UnitConversion.currentUnit() === unitType.metricUnit)
                    {
                        mainWindow.showPrimaryNumpad(qmlTextCalibrateForce.toUpperCase(), qmlTextUnit, 0, 0, 10000, gaugeValueText2.text)
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmlTextCalibrateForce.toUpperCase(), qmlTextUnit, 1, 0, 10000, gaugeValueText2.text)
                    }
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: cancelBtn
        visible: (continueBtn.visible)
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: continueBtn.left
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextCancel
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.cancelButtonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            abortConfirmationPopup.visible = true
        }
    }

    BransonPrimaryButton
    {
        id: continueBtnPrimary
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextContinue
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            setupFlag = true
            pleaseWaitText.visible = true
            continueBtnPrimary.visible = false
            positionLoadCellText.visible = false
            cancelBtn.visible = false
            responseValidationTimer.interval = 3000
            responseValidationTimer.running = true
            responseValidationTimer.start()
        }
    }

    BransonPrimaryButton
    {
        id: continueBtn
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextContinue
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            if(textBackgroundRect2.visible)
            {

                calibrationCounter = calibrationCounter + 1

                textBackgroundRect2.visible = false
                /*Trigger the response timer*/
                responseValidationTimer.interval = 3000
                responseValidationTimer.running = true
                responseValidationTimer.start()
                continueBtn.visible = false
                enter1stLoadCellText.visible = false
                cancelBtn.visible = false

                /*Send the iteration count to backend*/
                CalibrateForce.onContinuePressed(calibrationCounter)

                if(calibrationCounter === 2)
                {
                    calibrationSavedText.visible = true
                    textBackgroundRect2.visible = false
                    closeBtn.visible = true
                    continueBtn.visible = false
                    positionLoadCellText.visible = false
                    enter1stLoadCellText.visible = false
                }

                else
                {
                    textBackgroundRect.visible = false
                    pleaseWaitText.visible = true
                }
            }

            else
            {
                positionLoadCellText.visible = false
                enter1stLoadCellText.visible = true
                textBackgroundRect.visible = false
                textBackgroundRect2.visible = true
            }
        }
    }

    Text
    {
        id: calibrationSavedText
        visible: (calibrationCounter === 2)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(275 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrationSaved + "\n" + qmlTextCalibrationSaved2
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    }

    BransonPrimaryButton
    {
        id: calibratePressureBtn
        visible: (calibrationSavedText.visible)
        implicitWidth: Math.round(150 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: verifyBtn.left
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextCalibratePressure
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.cancelButtonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE)
        }
    }

    BransonPrimaryButton
    {
        id: verifyBtn
        visible: (calibrationSavedText.visible)
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: closeBtn.left
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextVerify
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.cancelButtonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuParentOptionSelect(UIScreenEnum.ACTUATORSETUP)
        }
    }

    BransonPrimaryButton
    {
        id: closeBtn
        visible: false
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextClose
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_SENSORS)
        }
    }

    /*Halt msg*/
    Text
    {
        id: pleaseWaitText
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WrapAnywhere
        text: qmlTextPleaseWait
        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        font.bold: true
    }

    /*Halt msg indicator*/
    Timer
    {
        id: responseValidationTimer
        running: false
        repeat: false
        onTriggered:
        {
            if(setupFlag)
            {
                pleaseWaitText.visible = false
                textBackgroundRect.visible = true
                setupFlag = false
            }

            else if(calibrationCounter !== 2)
            {
                pleaseWaitText.visible = false
                textBackgroundRect2.visible = true
                continueBtn.visible = true
                if(calibrationCounter === 1)
                enter1stLoadCellText.text = qmlReEnterLoadCell
                enter1stLoadCellText.visible = true
                cancelBtn.visible = true
            }
        }
    }

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        visible: abortConfirmationPopup.visible
        anchors.left: parent.Left
        anchors.top: parent.Top
        height: parent.height
        width: parent.width
        color: Style.headerBackgroundColor
        opacity: 0.25

        MouseArea
        {
            id: opacityEffectRectMa
            anchors.fill: parent
            onClicked:
            {
                /*Avoid false click*/
            }
        }
    }

    Rectangle
    {
        id: abortRect
        width: Math.round(50 * Style.scaleHint)
        height: Math.round(50 * Style.scaleHint)
        x:0
        y:Math.round(-50 * Style.scaleHint)
        color: "transparent"

        MouseArea
        {
            id: abortRectMA
            anchors.fill: parent

            onClicked:
            {
                if((calibrationCounter !== 2) && (!calibrationSavedText.visible))
                {
                   abortConfirmationPopup.visible = true
                }
            }
        }
    }

    Rectangle
    {
        id: abortRect2
        width: Math.round(50 * Style.scaleHint)
        height: Math.round(50 * Style.scaleHint)
        x:Math.round(750 * Style.scaleHint)
        y:Math.round(-50 * Style.scaleHint)
        color: "transparent"

        MouseArea
        {
            id: abortRectMA2
            anchors.fill: parent

            onClicked:
            {
                if((calibrationCounter !== 2) && (!calibrationSavedText.visible))
                {
                   abortConfirmationPopup.visible = true
                }
            }
        }
    }

    /*Abort msg*/
    Rectangle
    {
        id: abortConfirmationPopup
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.50
        height: Math.round(200 * Style.scaleHint)

        Rectangle
        {
            id: abortConfirmationPopupHeader
            width: parent.width
            implicitHeight: Math.round(50 * Style.scaleHint)
            color: Style.headerBackgroundColor

            Text
            {
                id: abortConfirmationPopupHeaderName
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmlTextConfirmation
                color: Style.whiteFontColor
                font
                {
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    bold: true
                }
            }
        }

        Text
        {
            id: abortConfirmationPopupAlertMsg
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            text: qmlTextCalibrationAbort + "\n" + qmlTextCalibrationAbort
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style3 * Style.scaleHint)
            }
        }

        BransonPrimaryButton
        {
            id: yesBtn
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.right: noBtn.left
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            text: qmlTextYes
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name

            onClicked:
            {
                CalibrateForce.onCalibrationAbortPressed()
                abortConfirmationPopup.visible = false
                mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_SENSORS)
            }
        }

        BransonPrimaryButton
        {
            id: noBtn
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            text: qmlTextNo
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name

            onClicked:
            {
                abortConfirmationPopup.visible = false
            }
        }
    }
}

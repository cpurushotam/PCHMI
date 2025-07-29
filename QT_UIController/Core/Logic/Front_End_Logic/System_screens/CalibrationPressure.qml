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
    property string qmlTextCalibratePressure  : "Calibrate Pressure"
    property string qmlTextEnterPressureGauge : "ENTER PRESSURE GAUGE"
    property string qmlTextReadings           : "Readings"
    property string qmlTextUnit               : "psi"
    property string qmlTextContinue           : "Continue"
    property string qmlTextCancel             : "Cancel"
    property string qmlTextCalibrationSaved   : "        Calibration Saved !"
    property string qmlTextConfirmation       : "CONFIRMATION"
    property string qmlTextCalibrationAbort   : " Are You Sure You Want To Abort The Calibration !"
    property string qmlTextYes                : "Yes"
    property string qmlTextNo                 : "No"
    property string qmlTextPleaseWait         : "Please Wait !"
    property string qmlTextClose              : "CLOSE"
    property string qmlTextCalibrateForce     : "CALIBRATE FORCE"
    property string qmlTextVerify             : "VERIFY"
    property string qmlTextCalibrationSaved2  : "  Verify Using Horn Down !"
    property string qmlTextCalibrationAbort2  : "  The Calibration Process Will Be Aborted !"

    property int calibrationCounter : 0

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibratePressure, qmlTextEnterPressureGauge, qmlTextReadings, qmlTextUnit,
                                qmlTextContinue, qmlTextCancel, qmlTextCalibrationSaved, qmlTextConfirmation, qmlTextCalibrationAbort, qmlTextYes, qmlTextNo,
                                qmlTextPleaseWait, qmlTextClose, qmlTextCalibrateForce, qmlTextVerify, qmlTextCalibrationSaved2, qmlTextCalibrationAbort2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE , qmlTextArray)
        qmlTextCalibratePressure  = qmlTextArray[textEnum.textCalibratePressureIdx]
        qmlTextEnterPressureGauge  = qmlTextArray[textEnum.textEnterPressureGaugeIdx]
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
        qmlTextCalibrateForce = qmlTextArray[textEnum.textCalibrateForceIdx]
        qmlTextVerify = qmlTextArray[textEnum.textVerifyIdx]
        qmlTextCalibrationSaved2 = qmlTextArray[textEnum.textCalibrationSaved2Idx]
        qmlTextCalibrationAbort2  = qmlTextArray[textEnum.textCalibrationAbort2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibratePressureIdx  : 0
        readonly property int textEnterPressureGaugeIdx : 1
        readonly property int textReadingsIdx           : 2
        readonly property int textUnitIdx               : 3
        readonly property int textContinueIdx           : 4
        readonly property int textCancelIdx             : 5
        readonly property int textCalibrationSavedIdx   : 6
        readonly property int textConfirmationIdx       : 7
        readonly property int textCalibrationAbortIdx   : 8
        readonly property int textYesIdx                : 9
        readonly property int textNoIdx                 : 10
        readonly property int textPleaseWaitIdx         : 11
        readonly property int textCloseIdx              : 12
        readonly property int textCalibrateForceIdx     : 13
        readonly property int textVerifyIdx             : 14
        readonly property int textCalibrationSaved2Idx  : 15
        readonly property int textCalibrationAbort2Idx  : 16
    }

    QtObject
    {
        id: unitType
        readonly property int metricUnit     : 0
        readonly property int imperialUnit   : 1
    }

    Component.onCompleted:
    {
        //        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE)
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE
        CalibratePressure.isScreenReNavigated(true)
        qmlTextUnit = UnitConversion.PressureUnit

        /*Trigger the response timer*/
        pleaseWaitText.visible = true
        textBackgroundRect.visible = false
        cancelBtn.visible = false
        continueBtn.visible = false
        responseValidationTimer.interval = 3000
        responseValidationTimer.running = true
        responseValidationTimer.start()
    }

    onVisibleChanged:
    {
        CalibratePressure.onCalibrationAbortPressed()
    }

    Text
    {
        id: calibratePressureText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibratePressure
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
    }

    Text
    {
        id: enterPressureGuazeText
        visible: (continueBtn.visible)
        anchors.left: textBackgroundRect.left
        anchors.bottom: textBackgroundRect.top
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextEnterPressureGauge
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        font.bold: true
    }

    Rectangle
    {
        id: textBackgroundRect
        width: Math.round(500 * Style.scaleHint)
        height: Math.round(150 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: Style.whiteBackgroundColor
        Text
        {
            id: readingsText
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
            id: gaugeValueRect
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            anchors.left: readingsText.right
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            color: Style.whiteBackgroundColor
            border.color: Style.blackFontColor
            Text
            {
                id: gaugeValueText
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
                text: (UnitConversion.currentUnit() === unitType.metricUnit) ? CalibratePressure.CalibrationReadings.toFixed(0) :
                                                                               CalibratePressure.CalibrationReadings.toFixed(1)
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
                text: mainWindow.qmltextPressureUnit
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.bold: true
            }

            MouseArea
            {
                id: gaugeValueRectMA
                anchors.fill: parent
                onClicked:
                {
                    if(UnitConversion.currentUnit() === unitType.metricUnit)
                    {
                        mainWindow.showPrimaryNumpad(qmlTextCalibratePressure.toUpperCase(), qmlTextUnit, 0, 0, 10000, gaugeValueText.text)
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmlTextCalibratePressure.toUpperCase(), qmlTextUnit, 1, 0, 10000, gaugeValueText.text)
                    }
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: cancelBtn
        visible: (! calibrationSavedText.visible)
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
            calibrationCounter = calibrationCounter + 1

            textBackgroundRect.visible = false
            /*Trigger the response timer*/
            responseValidationTimer.interval = 3000
            responseValidationTimer.running = true
            responseValidationTimer.start()
            cancelBtn.visible = false
            continueBtn.visible = false
            /*Send the iteration count to backend*/
            CalibratePressure.onContinuePressed(calibrationCounter)

            if(calibrationCounter === 3)
            {
                calibrationSavedText.visible = true
                textBackgroundRect.visible = false
                closeBtn.visible = true
                continueBtn.visible = false
            }

            else
            {
                pleaseWaitText.visible = true
            }
        }
    }

    Text
    {
        id: calibrationSavedText
        visible: (calibrationCounter === 3)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(275 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrationSaved + "\n" + qmlTextCalibrationSaved2
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    }

    BransonPrimaryButton
    {
        id: calibrateForceBtn
        visible: (calibrationSavedText.visible)
        implicitWidth: Math.round(150 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: verifyBtn.left
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        text: qmlTextCalibrateForce
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.cancelButtonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_FORCE)
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
            if(calibrationCounter !== 3)
            {
                pleaseWaitText.visible = false
                textBackgroundRect.visible = true
                cancelBtn.visible = true
                continueBtn.visible = true
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
            text: qmlTextCalibrationAbort + "\n" + qmlTextCalibrationAbort2
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
                CalibratePressure.onCalibrationAbortPressed()
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

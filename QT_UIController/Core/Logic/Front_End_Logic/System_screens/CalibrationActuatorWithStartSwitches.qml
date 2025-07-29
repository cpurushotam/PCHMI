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
    property string qmlTextMenuName            : "Calibration"
    property string qmlTextWithStartSwitches   : "Quick Calibration"
    property string qmlTextPressStartSwitches  : "Press Start Switches"
    property string qmlTextCalibrationSaved    : "      Calibration Saved"
    property string qmlTextClose               : "Close"
    property string qmlTextCalibrationSaved2   : " Release Start Switches"

    signal partContactDetected()

    property var qmlTextArray: [qmlTextMenuName, qmlTextWithStartSwitches, qmlTextPressStartSwitches, qmlTextCalibrationSaved, qmlTextClose, qmlTextCalibrationSaved2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR_WITH_START_SWITCHES , qmlTextArray)
        qmlTextWithStartSwitches  = qmlTextArray[textEnum.textWithStartSwitchesIdx]
        qmlTextPressStartSwitches  = qmlTextArray[textEnum.textPressStartSwitchesIdx]
        qmlTextCalibrationSaved  = qmlTextArray[textEnum.textCalibrationSavedIdx]
        qmlTextClose  = qmlTextArray[textEnum.textCloseIdx]
        qmlTextCalibrationSaved2  = qmlTextArray[textEnum.textCalibrationSaved2Idx]

    }

    QtObject
    {
        id: textEnum
        readonly property int textWithStartSwitchesIdx    : 0
        readonly property int textPressStartSwitchesIdx   : 1
        readonly property int textCalibrationSavedIdx     : 2
        readonly property int textCloseIdx                : 3
        readonly property int textCalibrationSaved2Idx    : 4
    }

    Component.onCompleted:
    {

    }

    Connections
    {
        target: CalibrateQuick
        function onPartContactDetected()
        {
            /*Below section make sure the quick calibration shall be happen
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
        id: withStartSwitchesText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextWithStartSwitches
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
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
            id: pressStartSwitchesText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextPressStartSwitches
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            font.bold: true
        }
    }

    Text
    {
        id: calibrationSavedText
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrationSaved + "\n" + qmlTextCalibrationSaved2
        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        font.bold: true
    }

    BransonPrimaryButton
    {
        id: closeBtn
        visible: false
        text: qmlTextClose
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR)
        }
    }

    /*Halt msg indicator*/
    Timer
    {
        id: responseValidationTimer
        running: false
        repeat: false
        onTriggered:
        {
            textBackgroundRect.visible = false
            calibrationSavedText.visible = true
            closeBtn.visible = true
        }
    }
}

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
    property string qmlTextCalibrateActuator   : "Calibrate Actuator"
    property string qmlTextWithStartSwitches   : "With Start Switches"
    property string qmlTextWithManualOverride  : "With Manual Override"

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibrateActuator, qmlTextWithStartSwitches, qmlTextWithManualOverride]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR , qmlTextArray)
        qmlTextCalibrateActuator = qmlTextArray[textEnum.textCalibrateActuatorIdx]
        qmlTextWithStartSwitches  = qmlTextArray[textEnum.textWithStartSwitchesIdx]
        qmlTextWithManualOverride  = qmlTextArray[textEnum.textWithManualOverrideIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibrateActuatorIdx  : 0
        readonly property int textWithStartSwitchesIdx  : 1
        readonly property int textWithManualOverrideIdx : 2
    }

    Component.onCompleted:
    {
//        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_SERVICE_COUNT)
//        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR
//        ServiceCountListModel.isScreenReNavigated(true)
    }

    Text
    {
        id: calibrateActuatorText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrateActuator
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
    }

    Button
    {
        id: withStartSwitchButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextWithStartSwitches
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: withStartSwitchButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: withStartSwitchButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: withStartSwitchButton.pressed ? 0 : 3
                verticalOffset: withStartSwitchButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            CalibrateActuator.onQuickCalibrationPressed()
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR_WITH_START_SWITCHES)
        }
    }

    /*Button
    {
        id: withManualOverrideButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: withStartSwitchButton.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextWithManualOverride
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: fullCallButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: withManualOverrideButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: withManualOverrideButton.pressed ? 0 : 3
                verticalOffset: withManualOverrideButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            CalibrateActuator.onQuickCalibrationPressed()
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR_WITH_START_SWITCHES)
        }
    }*/
}

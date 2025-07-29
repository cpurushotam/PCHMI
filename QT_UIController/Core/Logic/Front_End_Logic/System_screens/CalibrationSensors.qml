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
    property string qmlTextMenuName            : "Calibrate Sensors"
    property string qmlTextCalibrateSensors    : "Calibrate Sensors"
    property string qmlTextCalibrateForce      : "Calibrate "
    property string qmlTextCalibratePressure   : "Calibrate "
    property string qmlTextCalibrateForce2     : " Force"
    property string qmlTextCalibratePressure2  : " Pressure"

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibrateSensors, qmlTextCalibrateForce, qmlTextCalibratePressure, qmlTextCalibrateForce2, qmlTextCalibratePressure2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_SENSORS , qmlTextArray)
        qmlTextCalibrateSensors = qmlTextArray[textEnum.textCalibrateSensorsIdx]
        qmlTextCalibrateForce  = qmlTextArray[textEnum.textCalibrateForceIdx]
        qmlTextCalibratePressure  = qmlTextArray[textEnum.textCalibratePressureIdx]
        qmlTextCalibrateForce2  = qmlTextArray[textEnum.textCalibrateForce2Idx]
        qmlTextCalibratePressure2  = qmlTextArray[textEnum.textCalibratePressure2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibrateSensorsIdx       : 0
        readonly property int textCalibrateForceIdx         : 1
        readonly property int textCalibratePressureIdx      : 2
        readonly property int textCalibrateForce2Idx        : 3
        readonly property int textCalibratePressure2Idx     : 4
    }

    Component.onCompleted:
    {
        updateLanguage();
        if ((ActiveScreen.CurrentActiveScreen !== UIScreenEnum.SYSTEM_CALIBRATE_FORCE) && (ActiveScreen.CurrentActiveScreen !== UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE))
        {
            mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE_SENSORS)
        }
//        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_SENSORS
//        ServiceCountListModel.isScreenReNavigated(true)
    }

    Text
    {
        id: calibrateFullSstemText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrateSensors
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
    }

    Button
    {
        id: calibrateForceButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(200 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextCalibrateForce + "\n" +qmlTextCalibrateForce
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: calibrateForceButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: calibrateForceButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: calibrateForceButton.pressed ? 0 : 3
                verticalOffset: calibrateForceButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            CalibrateForce.onCalibrateForcePressed()
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_FORCE)
        }
    }

    Button
    {
        id: calibratePressureButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: calibrateForceButton.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextCalibratePressure + "\n" + qmlTextCalibratePressure2
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: calibratePressureButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: calibratePressureButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: calibratePressureButton.pressed ? 0 : 3
                verticalOffset: calibratePressureButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            CalibratePressure.onCalibratePressurePressed()
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE)
        }
    }
}

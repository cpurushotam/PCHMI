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
    property string qmlTextMenuName                : "Calibration"
    property string qmlTextCalibrateFullSystem     : "Calibrate Full System"
    property string qmlTextResetSensorCalibration  : "Reset"
    property string qmlTextCalibrateSensors        : "Calibrate"
    property string qmlTextResetSensorCalibration2 : " Sensor "
    property string qmlTextResetSensorCalibration3 : " Calibration"
    property string qmlTextCalibrateSensors2       : " Sensors"

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibrateFullSystem, qmlTextResetSensorCalibration, qmlTextCalibrateSensors, qmlTextResetSensorCalibration2, qmlTextResetSensorCalibration3, qmlTextCalibrateSensors2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM , qmlTextArray)
        qmlTextCalibrateFullSystem = qmlTextArray[textEnum.textCalibrateFullSystemIdx]
        qmlTextResetSensorCalibration  = qmlTextArray[textEnum.textResetSensorCalibrationIdx]
        qmlTextCalibrateSensors  = qmlTextArray[textEnum.textCalibrateSensorsIdx]
        qmlTextResetSensorCalibration2  = qmlTextArray[textEnum.textResetSensorCalibration2Idx]
        qmlTextResetSensorCalibration3  = qmlTextArray[textEnum.textResetSensorCalibration3Idx]
        qmlTextCalibrateSensors2 =  qmlTextArray[textEnum.textCalibrateSensors2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibrateFullSystemIdx     : 0
        readonly property int textResetSensorCalibrationIdx  : 1
        readonly property int textCalibrateSensorsIdx        : 2
        readonly property int textResetSensorCalibration2Idx : 3
        readonly property int textResetSensorCalibration3Idx : 4
        readonly property int textCalibrateSensors2Idx        : 5
    }

    Component.onCompleted:
    {
//        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM)
//        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM
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
        text: qmlTextCalibrateFullSystem
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
    }

    Button
    {
        id: resetSensorCalibrationButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(200 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextResetSensorCalibration + "\n" + qmlTextResetSensorCalibration2 + "\n" + qmlTextResetSensorCalibration3
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: resetSensorCalibrationButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: resetSensorCalibrationButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: resetSensorCalibrationButton.pressed ? 0 : 3
                verticalOffset: resetSensorCalibrationButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_RESET_SENSORS)
        }
    }

    Button
    {
        id: calibrateSensorsButton
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: resetSensorCalibrationButton.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextCalibrateSensors + "\n" + qmlTextCalibrateSensors
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name
        visible: mainWindow.bransonTabEnable

        background: Rectangle
        {
            id: calibrateSensorsButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: calibrateSensorsButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: calibrateSensorsButton.pressed ? 0 : 3
                verticalOffset: calibrateSensorsButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_SENSORS)
        }
    }
}

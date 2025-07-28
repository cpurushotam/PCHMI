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
    property string qmlTextMenuName               : "Calibration"
    property string qmlTextResetSensorCalibration : "Reset Sensor Calibration"
    property string qmlTextWarningMsg             : "This Will Revert To"
    property string qmlTextOK                     : "OK"
    property string qmlTextCancel                 : "Cancel"
    property string qmlTextCalibrationSaved       : "Reset Calibration Done !"
    property string qmlTextWarningMsg2            : " Factory Defaults !"

    property int calibrationCounter : 0


    property var qmlTextArray: [qmlTextMenuName, qmlTextResetSensorCalibration, qmlTextWarningMsg, qmlTextOK, qmlTextCancel, qmlTextCalibrationSaved, qmlTextWarningMsg2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE_RESET_SENSORS , qmlTextArray)
        qmlTextResetSensorCalibration  = qmlTextArray[textEnum.textResetSensorCalibrationIdx]
        qmlTextWarningMsg  = qmlTextArray[textEnum.textWarningMsgIdx]
        qmlTextOK = qmlTextArray[textEnum.textOKIdx]
        qmlTextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmlTextCalibrationSaved = qmlTextArray[textEnum.textCalibrationSavedIdx]
        qmlTextWarningMsg2  = qmlTextArray[textEnum.textWarningMsg2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textResetSensorCalibrationIdx : 0
        readonly property int textWarningMsgIdx             : 1
        readonly property int textOKIdx                     : 2
        readonly property int textCancelIdx                 : 3
        readonly property int textCalibrationSavedIdx       : 4
        readonly property int textWarningMsg2Idx            : 5
    }

    Component.onCompleted:
    {
//        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE_RESET_SENSORS)
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE_RESET_SENSORS
//        ServiceCountListModel.isScreenReNavigated(true)
    }

    Text
    {
        id: resetCalibrationText
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        wrapMode: Text.WrapAnywhere
        text: qmlTextResetSensorCalibration
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
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
            id: warningMsgText
            anchors.left: parent.left
            anchors.leftMargin: Math.round(175 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextWarningMsg + "\n" + qmlTextWarningMsg2
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            font.bold: true
        }
    }

    BransonPrimaryButton
    {
        id: okBtn
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.left: textBackgroundRect.left
        anchors.leftMargin: (! calibrationSavedText.visible) ? Math.round(125 * Style.scaleHint) : Math.round(185 * Style.scaleHint)
        anchors.top: textBackgroundRect.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        text: qmlTextOK
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            if (! calibrationSavedText.visible)
            {
                CalibrateResetSensors.onOKPressed()
                textBackgroundRect.visible = false
                calibrationSavedText.visible = true
            }

            else
            {
                mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM)
            }
        }
    }

    BransonPrimaryButton
    {
        id: cancelBtn
        visible: (! calibrationSavedText.visible)
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        anchors.left: okBtn.right
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.top: textBackgroundRect.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        text: qmlTextCancel
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name

        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM)
        }
    }

    Text
    {
        id: calibrationSavedText
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WrapAnywhere
        text: qmlTextCalibrationSaved
        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
    }
}

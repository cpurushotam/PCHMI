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
    property string qmlTextCalibrateActuator   : "Calibrate Actuator "
    property string qmlTextCalibrateFullSystem : "Calibrate Full System"
    property string qmlTextCalibrateActuator2   : " (Quick Cal)"

    property var qmlTextArray: [qmlTextMenuName, qmlTextCalibrateActuator, qmlTextCalibrateFullSystem, qmlTextCalibrateActuator2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CALIBRATE , qmlTextArray)
        qmlTextCalibrateActuator  = qmlTextArray[textEnum.textCalibrateActuatorIdx]
        qmlTextCalibrateFullSystem  = qmlTextArray[textEnum.textCalibrateFullSystemIdx]
        qmlTextCalibrateActuator2  = qmlTextArray[textEnum.textCalibrateActuator2Idx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textCalibrateActuatorIdx    : 0
        readonly property int textCalibrateFullSystemIdx  : 1
        readonly property int textCalibrateActuator2Idx   : 2
    }

    Component.onCompleted:
    {
        mainWindow.setHeaderTitle(qmlTextMenuName, UIScreenEnum.SYSTEM_CALIBRATE)
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CALIBRATE
//        ServiceCountListModel.isScreenReNavigated(true)
    }

    Button
    {
        id: quickCalButton
        visible: (UserPrivilegeObj.getLogedInUserLevel() !== (mainWindow.qmltextOperator))
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(200 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextCalibrateActuator + "\n" +qmlTextCalibrateActuator2
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: quickCalButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: quickCalButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: quickCalButton.pressed ? 0 : 3
                verticalOffset: quickCalButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR)
        }
    }

    Button
    {
        id: fullCallButton
        visible:  mainWindow.bransonTabEnable
        implicitWidth: Math.round(200 * Style.scaleHint)
        implicitHeight: Math.round(200 * Style.scaleHint)
        anchors.left: quickCalButton.right
        anchors.leftMargin: (quickCalButton.visible) ? Math.round(10 * Style.scaleHint) :
                                                       Math.round(-110 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qmlTextCalibrateFullSystem
        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
        font.family: Style.regular.name

        background: Rectangle
        {
            id: fullCallButtonRect
            color: Style.whiteBackgroundColor
            layer.enabled: fullCallButton.pressed ? false : true
            layer.effect: DropShadow
            {
                horizontalOffset: fullCallButton.pressed ? 0 : 3
                verticalOffset: fullCallButton.pressed ? 0 : 3
                color:  "#80000000"
                opacity: 0.2
            }
        }
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM)
        }
    }
}

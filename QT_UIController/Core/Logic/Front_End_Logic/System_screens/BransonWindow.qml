/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Branson Service Window

 **********************************************************************************************************/
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import Com.Branson.UIScreenEnum 1.0
import QtQuick.VirtualKeyboard.Settings 2.15
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"
Item {
    id: bransonItem
    property string qmltextSyatemConfig:           "System Configuration"
    property string qmltextService:                "Service"


    property var qmlTextArray:[qmltextSyatemConfig,qmltextService]

    QtObject
    {
        id: textEnum
        readonly property int textSyatemConfigIdx             : 0
        readonly property int textServiceIdx                  : 1
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.BRANSON_SYSTEM_CONFIGURATION, qmlTextArray)
        qmltextSyatemConfig = qmlTextArray[textEnum.textSyatemConfigIdx]
        qmltextFeature = qmlTextArray[textEnum.textFeatureIdx]
        qmltextService = qmlTextArray[textEnum.textServiceIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }
    Component.onCompleted:
    {
    }

    Rectangle
    {
        id:leftMenu
        height: parent.height
        width: Math.round(210 * Style.scaleHint)
        anchors.top:parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left:parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        color:Style.backgroundColor//Style.contentBackgroundColor
        Column
        {
            Rectangle
            {
                id:systConfigCol
                height: Math.round(50 * Style.scaleHint)
                width: leftMenu.width
                color: Style.activeFrameBorderColor//"transparent"
                Text
                {
                    id:systemconfigtxt
                    text: qmltextSyatemConfig
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.weight : Font.DemiBold
                    color: "#ffffff"
                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            serviceColumn.color = "transparent"
                            servicetxt.color = "#000000"
                            systConfigCol.color = Style.activeFrameBorderColor
                            systemconfigtxt.color = "#ffffff"
                            subBransonSystemConfig.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/BransonSystemConfiguration.qml"
                        }
                    }
                }
            }
            Rectangle
            {
                id:serviceColumn
                height: Math.round(50 * Style.scaleHint)
                width: leftMenu.width
                color: "transparent"
                Text
                {
                    id:servicetxt
                    text: qmltextService
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.weight : Font.DemiBold
                    color: "#000000"
                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {//BransonServiceTab.qml

                            serviceColumn.color = Style.activeFrameBorderColor
                            servicetxt.color = "#ffffff"
                            systConfigCol.color = "transparent"
                            systemconfigtxt.color = "#000000"
                            ActiveScreen.CurrentActiveScreen = UIScreenEnum.BRANSON_SERVICE_TAB
                            subBransonSystemConfig.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/BransonServiceTab.qml"

                        }
                    }
                }
            }
        }
    }

    Loader {
        id: subBransonSystemConfig
        anchors.top: parent.top
        anchors.left: leftMenu.right
        anchors.bottom: parent.bottom
        source:"qrc:/Core/Logic/Front_End_Logic/System_screens/BransonSystemConfiguration.qml"
    }
}

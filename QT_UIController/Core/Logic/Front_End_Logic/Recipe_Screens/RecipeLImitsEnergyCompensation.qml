/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

Files handles QML implementation for Energy compensation.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
Item {

    id: energycompensationtab
    property string qmlTextEnergyCompEnable:         "Energy Compensation Enabled"
    property string qmlTextEnergyLowVal:             "Energy Compensation Minimum Value"
    property string qmlTextEnergyHighVal:            "Energy Compensation Maximum Value"

    signal recipeLabDataChanged

    property var qmlTextArray: [qmlTextEnergyCompEnable,qmlTextEnergyLowVal,qmlTextEnergyHighVal]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_LIMITS_ENERGY_COMPENSATION, qmlTextArray)
        qmlTextEnergyCompEnable = qmlTextArray[textEnum.textEnergyEnableIdx]
        qmlTextEnergyLowVal = qmlTextArray[textEnum.textEnergyMinIdx]
        qmlTextEnergyHighVal = qmlTextArray[textEnum.textEnergyMaxIdx]
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject
    {
        id: textEnum
        readonly property int textEnergyEnableIdx:               0
        readonly property int textEnergyMinIdx:                  1
        readonly property int textEnergyMaxIdx:                  2
    }

    QtObject{
        id:paramEnum
        readonly property int energyCompensationMinimum:            0
        readonly property int energyCompensationMaximum:            1

    }

    Flickable
    {
        id: infoScrollRec
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        contentHeight:  height*1.5
        clip: true

        BransonLeftBorderRectangle {
            id: energyEnableTitle
            width: energycompensationtab.width*0.48
            height: energycompensationtab.height*0.30
            checked: energyEnableSwitch.checked

            Text {
                id: txtEnergyTitle
                width: parent.width * 0.75
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmlTextEnergyCompEnable.toLocaleUpperCase()
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.15
                wrapMode: Text.WordWrap
            }
            Image {
                id: infoIcon
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                source: "qrc:/Images/info.png"
                width: parent.width*0.08
                height: parent.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }

            BransonSwitch {
                id: energyEnableSwitch
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.10
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.EnergyCompensation
                onCheckedChanged: {
                    if(energyEnableSwitch.checked)
                    {
                        RecipeLabData.EnergyCompensation = true
                    }
                    else
                    {
                          RecipeLabData.EnergyCompensation = false
                    }
                }
            }
            MouseArea{
                id:clickBatchSetupEnable
                anchors.fill: energyEnableSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    energyEnableSwitch.toggle()
                }
            }
        }

        BransonLeftBorderRectangle {
            id: energylowTitle
            width: energycompensationtab.width*0.48
            height: energycompensationtab.height*0.30
            anchors.top: energyEnableTitle.bottom
            anchors.topMargin: energycompensationtab.height *0.06
            checked: energyEnableSwitch.checked
            clip: true
            Text {
                id: txtEnergylowTitle
                width: parent.width * 0.75
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.top: parent.top
                text: qmlTextEnergyLowVal.toLocaleUpperCase()
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.15
                wrapMode: Text.WordWrap
            }
            Image {
                id: infoIcon2
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                source: "qrc:/Images/info.png"
                width: parent.width*0.08
                height: parent.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }

            Text
            {
                id: txtLowValue
                text:  RecipeLabData.EnergyCompensationLowVal.toFixed(1) +" "+ mainWindow.qmltextEnergyUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
                font.family: Style.regular.name
                visible: energyEnableTitle.checked
            }

            MouseArea{
                id:clickEnergyLowVal
                anchors.fill: energylowTitle
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if( energyEnableSwitch.checked)
                    {
                        mainWindow.showPrimaryNumpad(qmlTextEnergyLowVal.toUpperCase(), mainWindow.qmltextEnergyUnit, 1, RecipeLabData.getMinEnergyCompensationVal(paramEnum.energyCompensationMinimum), RecipeLabData.getMaxEnergyCompensationVal(paramEnum.energyCompensationMinimum), RecipeLabData.EnergyCompensationLowVal.toFixed(1))
                    }
                }
            }
        }


        BransonLeftBorderRectangle {
            id: energyhighTitle
            width: energycompensationtab.width*0.48
            height: energycompensationtab.height*0.30
            anchors.top: energylowTitle.bottom
            anchors.topMargin: energycompensationtab.height *0.06
            checked: energyEnableSwitch.checked
            clip: true
            Text {
                id: txtEnergyhighTitle
                width: parent.width * 0.84
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.top: parent.top
                text: qmlTextEnergyHighVal.toUpperCase()
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.15
                wrapMode: Text.WordWrap
            }
            Image {
                id: infoIcon3
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                source: "qrc:/Images/info.png"
                width: parent.width*0.08
                height: parent.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }

            Text
            {
                id: txtHighValue
                text:  RecipeLabData.EnergyCompensationHighVal.toFixed(1) +" " +mainWindow.qmltextEnergyUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
                font.family: Style.regular.name
                visible: energyEnableTitle.checked

            }

            MouseArea{
                id:clickEnergyHighVal
                anchors.fill: energyhighTitle
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(energyEnableSwitch.checked)
                    {
                        mainWindow.showPrimaryNumpad(qmlTextEnergyHighVal.toUpperCase(), mainWindow.qmltextEnergyUnit, 1, RecipeLabData.getMinEnergyCompensationVal(paramEnum.energyCompensationMaximum), RecipeLabData.getMaxEnergyCompensationVal(paramEnum.energyCompensationMaximum), RecipeLabData.EnergyCompensationHighVal.toFixed(1))
                    }
                }
            }
        }
    }
}

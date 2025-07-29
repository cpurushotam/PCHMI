/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file displays the Afterburst Screen under weldprocess tab.

 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"
Item {
    property string qmltextMenuName:                "AFTERBURST"
    property string qmltextAfterburstTime:          "AFTERBURST TIME"
    property string qmltextAfterburstDelay:         "AFTERBURST DELAY"
    property string qmltextAfterburstAmplitude:     "AFTERBURST AMPLITUDE"
    property string qmltextResetToDefault:          "RESET TO DEFAULT"
    property var qmlTextArray: [qmltextMenuName,qmltextAfterburstTime, qmltextAfterburstDelay, qmltextAfterburstAmplitude,qmltextResetToDefault]

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDPROCESS_AFTERBURST, qmlTextArray)
        qmltextMenuName = qmlTextArray[textEnum.textMenuNameIdx]
        qmltextAfterburstTime = qmlTextArray[textEnum.textAfterburstTimeIdx]
        qmltextAfterburstDelay = qmlTextArray[textEnum.textAfterburstDelayIdx]
        qmltextAfterburstAmplitude = qmlTextArray[textEnum.textAfterburstAmplitudeIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
    }
    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }
    Component.onCompleted: {
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int textMenuNameIdx:                  0
        readonly property int textAfterburstTimeIdx:            1
        readonly property int textAfterburstDelayIdx:           2
        readonly property int textAfterburstAmplitudeIdx:       3
        readonly property int textResetToDefaultIdx:            4
    }
    QtObject {
        id: paramEnum
        readonly property int paramAfterburstTime:            0
        readonly property int paramAfterburstDelay:           1
        readonly property int paramAfterburstAmplitude:       2
    }
    BransonLeftBorderRectangle {
        id: afterburstEnableTitle
        width: parent.width*0.48
        height: parent.height*0.25

        Text {
            id: txtAfterburstTitle
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.15
            text: qmltextMenuName
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
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
            id: afterburstSwitch
            anchors.left: parent.left
            anchors.leftMargin:parent.width*0.08
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.25
            state: RecipeLabData.AfterburstEnable
            maxWidth: rectHeight*1.3
            maxHeight: rectHeight*1.3
            rectWidth: parent.width* 0.1
            rectHeight: parent.height* 0.15
            checked: RecipeLabData.AfterburstEnable
            onCheckedChanged: {
                if(afterburstSwitch.checked === true){
                    RecipeLabData.AfterburstEnable=true
                    afterburstEnableTitle.checked = true
                    afterburstDelayTitle.checked = true
                    afterburstTimeTitle.checked = true
                    afterburstAmplitudeTitle.checked = true
                }
                else{
                    RecipeLabData.AfterburstEnable=false
                    afterburstEnableTitle.checked = false
                    afterburstDelayTitle.checked = false
                    afterburstTimeTitle.checked = false
                    afterburstAmplitudeTitle.checked = false
                }
            }
        }
        MouseArea{
            id:clickAfterburstEnable
            anchors.fill: afterburstSwitch
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                afterburstSwitch.toggle()
            }
        }
    }
    BransonLeftBorderRectangle {
        id: afterburstDelayTitle
        width: parent.width*0.48
        height: parent.height*0.25
        anchors.left: afterburstEnableTitle.right
        anchors.leftMargin: height*0.15

        Text {
            id: textAfterburstDelay
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text: qmltextAfterburstDelay
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }
        Text {
            id: textDelay
            text: RecipeLabData.AfterburstDelay.toFixed(3)+" "+mainWindow.qmltextTimeUnit
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.15
        }
        MouseArea{
            id:clickAfterburstDelay
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(RecipeLabData.AfterburstEnable){
                    mainWindow.showPrimaryNumpad(qmltextAfterburstDelay, mainWindow.qmltextTimeUnit , 3, RecipeLabData.getMinAfterburstParametersValue(paramEnum.paramAfterburstDelay), RecipeLabData.getMaxAfterburstParametersValue(paramEnum.paramAfterburstDelay), RecipeLabData.AfterburstDelay.toFixed(3))
                }
            }
        }
    }
    BransonLeftBorderRectangle {
        id: afterburstTimeTitle
        width: parent.width*0.48
        height: parent.height*0.25
        anchors.top:afterburstEnableTitle.bottom
        anchors.topMargin: height*0.15
        anchors.leftMargin: height*0.15

        Text {
            id: textAfterburstTime
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text: qmltextAfterburstTime
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }
        Text {
            id: textTime
            text:RecipeLabData.AfterburstTime.toFixed(3)+" "+ mainWindow.qmltextTimeUnit
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.15
        }
        MouseArea{
            id:clickAfterburstTime
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(RecipeLabData.AfterburstEnable){
                    mainWindow.showPrimaryNumpad(qmltextAfterburstTime, mainWindow.qmltextTimeUnit , 3, RecipeLabData.getMinAfterburstParametersValue(paramEnum.paramAfterburstTime), RecipeLabData.getMaxAfterburstParametersValue(paramEnum.paramAfterburstTime),RecipeLabData.AfterburstTime.toFixed(3))
                }
            }
        }
    }
    BransonLeftBorderRectangle {
        id: afterburstAmplitudeTitle
        anchors.topMargin: height*0.15
        width: parent.width*0.48
        height: parent.height*0.25
        anchors.left: afterburstTimeTitle.right
        anchors.leftMargin: height*0.15
        anchors.top: afterburstDelayTitle.bottom

        Text {
            id: textAfterburstAmplitude
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text: qmltextAfterburstAmplitude
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }
        Text {
            id: textAmplitude
            text:RecipeLabData.AfterburstAmplitude+" "+ mainWindow.qmltextAmplitudeUnit
            color: Style.blackFontColor
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.15
            font.pixelSize: parent.height*0.18
        }
        MouseArea{
            id:clickAfterburstAmplitude
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(RecipeLabData.AfterburstEnable){
                    mainWindow.showPrimaryNumpad(qmltextAfterburstAmplitude,  mainWindow.qmltextAmplitudeUnit, 0, RecipeLabData.getMinAfterburstParametersValue(paramEnum.paramAfterburstAmplitude), RecipeLabData.getMaxAfterburstParametersValue(paramEnum.paramAfterburstAmplitude), RecipeLabData.AfterburstAmplitude)
                }
            }
        }
    }
    BransonPrimaryButton
    {
        id: btnResetDefault
        implicitWidth: Math.round(170 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        text: qmltextResetToDefault
        buttonColor: Style.blackFontColor
        font.family: Style.regular.name
        onClicked:
        {
            RecipeLabData.resetToDefault(true)
        }
    }
}

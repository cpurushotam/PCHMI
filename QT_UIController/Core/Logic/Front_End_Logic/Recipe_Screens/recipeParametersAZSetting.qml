/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

This file displays parameter A-Z related components.
 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Layouts
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"
Item {
    id:parentItem
    property string qmltextAfterburst:              "AFTERBURST"
    property string qmltextAfterburstTime:          "AFTERBURST TIME"
    property string qmltextAfterburstDelay:         "AFTERBURST DELAY"
    property string qmltextAfterburstAmplitude:     "AFTERBURST AMPLITUDE"
    property string qmltextEnergyBraking:           "ENERGY BRAKING"
    property string qmltextEnergyBrakeTime:         "ENERGY BRAKE TIME"
    property string qmltextEnergyBrakeAmplitude:    "ENERGY BRAKE AMPLITUDE"
    property string qmltextExtraCooling:            "EXTRA COOLING"
    property string qmltextMaxTimeout:              "MAX TIMEOUT"
    property string qmltextHoldForceRamp:           "HOLD FORCE RAMP"
    property string qmltextPreWeldSeek:             "PRE WELD SEEK"
    property string qmltextPostWeldSeek:            "POST WELD SEEK"
    property string qmltextPretrigger:              "PRETRIGGER"
    property string qmltextPretriggerDistance:      "PRETRIGGER DISTANCE"
    property string qmltextPretriggerAmplitude:     "PRETRIGGER AMPLITUDE"
    property string qmltextPretriggerTime:          "PRETRIGGER TIME"
    property string qmltextPretriggerStart:         "PRETRIGGER START"
    property string qmltextTime:                    "TIME"
    property string qmltextDistance:                "DISTANCE"
    property string qmltextAuto:                    "AUTO"
    property string qmltextActuatorClear:           "ACTUATOR CLEAR"
    property string qmltextSetting:                 "ACTUATOR SETTING"
    property string qmltextActTime:                 "ACTUATOR TIME"
    property string qmltextActDistance:             "ACTUATOR DISTANCE"
    property string qmltextRapidTraverse:           "RAPID TRAVERSE"
    property string qmltextRapidTraverseDistance:   "RAPID TRAVERSE DISTANCE"
    property string qmltextTriggerLost:              "TRIGGER LOST"
    property string qmltextExternalAmpltudeSetting:  "EXTERNAL AMPLITUDE"
    property string qmltextForce:                    "TRIGGER FORCE"
    property string qmltextTriggerDistance:          "TRIGGER DISTANCE"
    property string qmltextTrigForce:                "FORCE"
    property string qmltextTriggerType:              "TRIGGER TYPE"
    property string qmltextTimeSeekEnable:           "TIME SEEK ENABLE"
    property string qmltextTimeSeek:                 "TIME SEEK PERIOD"
    property string qmltextScrubAmplitude:           "SCRUB AMPLITUDE"
    property string qmltextMinUnit:                   "min"
    property string qmltextExternalAmpltudeSetting2: "SETTING"


    property int systemType: SystemConfiguration.CurrentSystemType
    property var qmlTextArray: [qmltextAfterburst, qmltextAfterburstTime, qmltextAfterburstDelay, qmltextAfterburstAmplitude, qmltextEnergyBraking,
        qmltextEnergyBrakeTime, qmltextEnergyBrakeAmplitude, qmltextExtraCooling, qmltextMaxTimeout, qmltextHoldForceRamp,
        qmltextPreWeldSeek, qmltextPostWeldSeek, qmltextPretrigger, qmltextPretriggerDistance,
        qmltextPretriggerAmplitude, qmltextPretriggerTime, qmltextPretriggerStart, qmltextTime, qmltextDistance,
        qmltextAuto, qmltextActuatorClear, qmltextSetting, qmltextRapidTraverse, qmltextRapidTraverseDistance, qmltextTriggerLost,
        qmltextExternalAmpltudeSetting, qmltextActTime  ,qmltextActDistance, qmltextForce, qmltextTriggerDistance, qmltextTrigForce,
        qmltextTriggerType,qmltextTimeSeekEnable, qmltextTimeSeek, qmltextScrubAmplitude,qmltextMinUnit, qmltextExternalAmpltudeSetting2]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_PARAMETERA2Z, qmlTextArray)
        qmltextAfterburst = qmlTextArray[textEnum.textAfterburstIdx]
        qmltextAfterburstTime = qmlTextArray[textEnum.textAfterburstTimeIdx]
        qmltextAfterburstDelay = qmlTextArray[textEnum.textAfterburstDelayIdx]
        qmltextAfterburstAmplitude = qmlTextArray[textEnum.textAfterburstAmplitudeIdx]
        qmltextEnergyBraking = qmlTextArray[textEnum.textEnergyBrakingIdx]
        qmltextEnergyBrakeTime = qmlTextArray[textEnum.textEnergyBrakeTimeIdx]
        qmltextEnergyBrakeAmplitude = qmlTextArray[textEnum.textEnergyBrakeAmplitudeIdx]
        qmltextExtraCooling = qmlTextArray[textEnum.textExtraCoolingIdx]
        qmltextMaxTimeout = qmlTextArray[textEnum.textMaxTimeoutIdx]
        qmltextHoldForceRamp = qmlTextArray[textEnum.textHoldForceRampIdx]
        qmltextPreWeldSeek = qmlTextArray[textEnum.textPreWeldSeekIdx]
        qmltextPostWeldSeek = qmlTextArray[textEnum.textPostWeldSeekIdx]
        qmltextPretrigger = qmlTextArray[textEnum.textPretriggerIdx]
        qmltextPretriggerDistance = qmlTextArray[textEnum.textPretriggerDistanceIdx]
        qmltextPretriggerAmplitude = qmlTextArray[textEnum.textPretriggerAmplitudeIdx]
        qmltextPretriggerTime = qmlTextArray[textEnum.textPretriggerTimeIdx]
        qmltextPretriggerStart = qmlTextArray[textEnum.textPretriggerStartIdx]
        qmltextTime = qmlTextArray[textEnum.textTimeIdx]
        qmltextDistance = qmlTextArray[textEnum.textDistanceIdx]
        qmltextAuto = qmlTextArray[textEnum.textAutoIdx]
        qmltextActuatorClear = qmlTextArray[textEnum.textActuatorClearIdx]
        qmltextSetting = qmlTextArray[textEnum.textSettingIdx]
        qmltextRapidTraverse = qmlTextArray[textEnum.textRapidTraverseIdx]
        qmltextTriggerLost = qmlTextArray[textEnum.textTriggerLostIdx]
        qmltextRapidTraverseDistance = qmlTextArray[textEnum.textRapidTraverseDistanceIDX]
        qmltextExternalAmpltudeSetting = qmlTextArray[textEnum.textExtAmpSettingIdx]
        qmltextActTime = qmlTextArray[textEnum.textActTimeIdx]
        qmltextActDistance = qmlTextArray[textEnum.textActDistanceIdx]
        qmltextForce = qmlTextArray[textEnum.textForceIdx]
        qmltextTriggerDistance = qmlTextArray[textEnum.textTriggerDistanceIdx]
        qmltextTrigForce = qmlTextArray[textEnum.textTrigForceIdx]
        qmltextTriggerType = qmlTextArray[textEnum.textTriggerTypeIdx]
        qmltextTimeSeekEnable = qmlTextArray[textEnum.textTimeSeekEnableIdx]
        qmltextTimeSeek = qmlTextArray[textEnum.textTimeSeekIdx]
        qmltextScrubAmplitude = qmlTextArray[textEnum.textScrubAmplitudeIdx]
        qmltextMinUnit=  qmlTextArray[textEnum.minIdx]
        qmltextExternalAmpltudeSetting2 = qmlTextArray[textEnum.textExtAmpSetting2Idx]
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
    QtObject{
        id:textEnum
        readonly property int textAfterburstIdx:                0
        readonly property int textAfterburstTimeIdx:            1
        readonly property int textAfterburstDelayIdx:           2
        readonly property int textAfterburstAmplitudeIdx:       3
        readonly property int textEnergyBrakingIdx:             4
        readonly property int textEnergyBrakeTimeIdx:           5
        readonly property int textEnergyBrakeAmplitudeIdx:      6
        readonly property int textExtraCoolingIdx:              7
        readonly property int textMaxTimeoutIdx:                8
        readonly property int textHoldForceRampIdx:             9
        readonly property int textPreWeldSeekIdx:               10
        readonly property int textPostWeldSeekIdx:              11
        readonly property int textPretriggerIdx:                12
        readonly property int textPretriggerDistanceIdx:        13
        readonly property int textPretriggerAmplitudeIdx:       14
        readonly property int textPretriggerTimeIdx:            15
        readonly property int textPretriggerStartIdx:           16
        readonly property int textTimeIdx:                      17
        readonly property int textDistanceIdx:                  18
        readonly property int textAutoIdx:                      19
        readonly property int textActuatorClearIdx:             20
        readonly property int textSettingIdx:                   21
        readonly property int textRapidTraverseIdx:             22
        readonly property int textRapidTraverseDistanceIDX:     23
        readonly property int textTriggerLostIdx:               24
        readonly property int textExtAmpSettingIdx:             25        
        readonly property int textActTimeIdx:                   26
        readonly property int textActDistanceIdx:               27
        readonly property int textForceIdx:                     28
        readonly property int textTriggerDistanceIdx:           29
        readonly property int textTrigForceIdx:                 30
        readonly property int textTriggerTypeIdx:               31
        readonly property int textTimeSeekEnableIdx:            32
        readonly property int textTimeSeekIdx:                  33
        readonly property int textScrubAmplitudeIdx:            34
        readonly property int minIdx:                           35
        readonly property int textExtAmpSetting2Idx:            36


    }
    QtObject{
        id:paramEnum
        readonly property int paramAfterburstTime:            0
        readonly property int paramAfterburstDelay:           1
        readonly property int paramAfterburstAmplitude:       2
        readonly property int paramEnergyBrakeTime:           3
        readonly property int paramEnergyBrakeAmplitude:      4
        readonly property int paramMaxTimeout:                5
        readonly property int paramHoldForceRamp:             6
        readonly property int paramPretriggerDistance:        7
        readonly property int paramPretriggerAmplitude:       8
        readonly property int paramPretriggerTime:            9
        readonly property int paramRapidTraverseDistance:     10
        readonly property int paramActuatorClearTime:         11
        readonly property int paramActuatorClearDistance:     12
        readonly property int paramTriggerForce:              13
        readonly property int paramTriggerDistance:           14
        readonly property int paramSeekTime:                  15
        readonly property int paramScrubAmplitude:            16

    }
    Flickable
    {
        id: infoScrollRec
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        contentHeight: (systemType === SystemTypeDef.ACTUATOR_ELECTRONIC)? height*5.0 : height*3.7
        clip: true

        BransonLeftBorderRectangle {
            id: afterburstEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25

            Text {
                id: txtAfterburstTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextAfterburst
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
                    if(afterburstSwitch.checked){
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
            height: parentItem.height*0.25
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
            Image {
                id: infoIconAfterburstDelay
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
            Text {
                id: textDelay
                text: RecipeLabData.AfterburstDelay.toFixed(3)+" "+ mainWindow.qmltextTimeUnit
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
                enabled: RecipeLabData.AfterburstEnable
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextAfterburstDelay, mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramAfterburstDelay), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramAfterburstDelay), RecipeLabData.AfterburstDelay.toFixed(2))
                }
            }
        }
        BransonLeftBorderRectangle {
            id: afterburstTimeTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:afterburstEnableTitle.bottom
            anchors.topMargin: height*0.1

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
            Image {
                id: infoIconAfterburstTime
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
            Text {
                id: textTime
                text:RecipeLabData.AfterburstTime.toFixed(3)+" "+mainWindow.qmltextTimeUnit
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
                enabled: RecipeLabData.AfterburstEnable
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextAfterburstTime, mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramAfterburstTime), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramAfterburstTime), RecipeLabData.AfterburstTime.toFixed(1))
                }
            }
        }
        BransonLeftBorderRectangle {
            id: afterburstAmplitudeTitle
            anchors.topMargin: height*0.1
            width: parent.width*0.48
            height: parentItem.height*0.25
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
            Image {
                id: infoIconAfterburstAmplitude
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
            Text {
                id: textAmplitude
                text:RecipeLabData.AfterburstAmplitude + " "+ mainWindow.qmltextAmplitudeUnit
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
                enabled: RecipeLabData.AfterburstEnable
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextAfterburstAmplitude, mainWindow.qmltextAmplitudeUnit, 0, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramAfterburstAmplitude), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramAfterburstAmplitude), RecipeLabData.AfterburstAmplitude)
                }
            }
        }

        Rectangle{
            id: separatorLine1
            width: parent.width
            height: 1
            anchors.top: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)?setting.bottom: afterburstTimeTitle.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
        }

        BransonLeftBorderRectangle {
            id: energyBrakingEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:separatorLine1.bottom
            anchors.topMargin: height*0.1
            checked: energyBrakingSwitch.checked
            Text {
                id: textEnergyBrakingTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextEnergyBraking
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconEnergyBraking
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
                id: energyBrakingSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.EnergyBraking
                onCheckedChanged: {
                    if(energyBrakingSwitch.checked)
                    {
                        RecipeLabData.EnergyBraking = true
                    }
                    else
                    {
                        RecipeLabData.EnergyBraking = false
                    }
                }
            }
            MouseArea{
                id:clickEnergyBraking
                anchors.fill: energyBrakingSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    energyBrakingSwitch.toggle()
                }
            }
        }
        BransonLeftBorderRectangle {
            id: energyBrakeTimeTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: energyBrakingEnableTitle.right
            anchors.leftMargin: height*0.15
            anchors.top:separatorLine1.bottom
            anchors.topMargin: height*0.1
            checked: energyBrakingSwitch.checked
            Text {
                id: textEnergyBrakeTime
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextEnergyBrakeTime
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconEnergyBrakeTime
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
            Text {
                id: textEnergyBrakeTimeValue
                text: RecipeLabData.EnergyBrakeTime.toFixed(3)  + " "+ mainWindow.qmltextTimeUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clickEnergyBrakeTime
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: RecipeLabData.EnergyBraking
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextEnergyBrakeTime, mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramEnergyBrakeTime), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramEnergyBrakeTime), RecipeLabData.EnergyBrakeTime.toFixed(3))
                }
            }
        }
        BransonLeftBorderRectangle {
            id: energyBrakeAmplitudeTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:energyBrakingEnableTitle.bottom
            anchors.topMargin: height*0.1
            checked: energyBrakingSwitch.checked

            Text {
                id: textEnergyBrakeAmplitude
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextEnergyBrakeAmplitude
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconEnergyBrakeAmplitude
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
            Text {
                id: textEnergyBrakeAmplitudeValue
                text: RecipeLabData.EnergyBrakeAmplitude + " "+ mainWindow.qmltextAmplitudeUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clickEnergyBrakeAmplitude
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: RecipeLabData.EnergyBraking
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextEnergyBrakeAmplitude,  mainWindow.qmltextAmplitudeUnit , 0, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramEnergyBrakeAmplitude), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramEnergyBrakeAmplitude), RecipeLabData.EnergyBrakeAmplitude)
                }
            }
        }

        Rectangle{
            id: separatorLine2
            width: parent.width
            height: 1
            anchors.top: energyBrakeAmplitudeTitle.bottom
            anchors.topMargin: energyBrakeAmplitudeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: energyBrakeTimeTitle.right
            color: Style.blackFontColor
        }

        BransonLeftBorderRectangle {
            id: extraCoolingEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:separatorLine2.bottom
            anchors.topMargin: height*0.1
            checked: extraCoolingSwitch.checked
            Text {
                id: textExtraCoolingTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextExtraCooling
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconExtraCooling
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
                id: extraCoolingSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked:RecipeLabData.ExtraCooling
                onCheckedChanged: {
                    if(extraCoolingSwitch.checked)
                    {
                        RecipeLabData.ExtraCooling = true
                    }
                    else
                    {
                        RecipeLabData.ExtraCooling = false
                    }
                }
            }
            MouseArea{
                id:clickExtraCooling
                anchors.fill: extraCoolingSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    extraCoolingSwitch.toggle()
                }
            }
        }
        BransonLeftBorderRectangle {
            id: maxTimeoutEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            checked: true
            /*anchors
            {
                top: systemType===SystemTypeDef.ACTUATOR_MANUAL? separatorLine2.bottom : extraCoolingEnableTitle.bottom
                topMargin: height*0.1
                left: systemType===SystemTypeDef.ACTUATOR_MANUAL? extraCoolingEnableTitle.right : parent.left
                leftMargin: systemType===SystemTypeDef.ACTUATOR_MANUAL? height*0.15 : 0
            }*/

            anchors
            {
                top: separatorLine2.bottom
                topMargin: height*0.1
                left: extraCoolingEnableTitle.right
                leftMargin: height*0.15
            }

            Text {
                id: textMaxTimeoutTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextMaxTimeout
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconMaxTimeout
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
            Text {
                id: textMaxTimeoutValue
                text: RecipeLabData.MaxWeldTimeout.toFixed(3) + " "+ mainWindow.qmltextTimeUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clickMaxTimeout
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextMaxTimeout,  mainWindow.qmltextTimeUnit, 3,  RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramMaxTimeout), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramMaxTimeout),RecipeLabData.MaxWeldTimeout.toFixed(3))
                }
            }
        }
        BransonLeftBorderRectangle {
            id: holdForceRampTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            checked: true
            visible: false//systemType === SystemTypeDef.ACTUATOR_ELECTRONIC

            anchors
            {
                top: separatorLine2.bottom
                topMargin: height*0.1
                left: extraCoolingEnableTitle.right
                leftMargin: height*0.15
            }

            Text {
                id: textHoldForceRampTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextHoldForceRamp
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconHoldForceRamp
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
            Text {
                id: textHoldForceRampValue
                text: RecipeLabData.HoldForceRamp.toFixed(0)+" %"
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clickHoldForceRamp
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextHoldForceRamp, "%", 0, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramHoldForceRamp), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramHoldForceRamp), RecipeLabData.HoldForceRamp)
                }
            }
        }

        Rectangle{
            id: separatorLine3
            width: parent.width
            height: 1
            anchors.top: maxTimeoutEnableTitle.bottom
            anchors.topMargin: maxTimeoutEnableTitle.height*0.1
            anchors.left: parent.left
            anchors.right: energyBrakeTimeTitle.right
            color: Style.blackFontColor
        }

        BransonLeftBorderRectangle {
            id: preWeldSeekTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            checked: preWeldSeekSwitch.checked
            anchors{
                top: separatorLine3.bottom
                topMargin: height*0.1
                left: parent.left
            }
            Text {
                id: textPreWeldSeekTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextPreWeldSeek
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconPreWeldSeek
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
                id: preWeldSeekSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.PreWeldSeek
                onCheckedChanged: {
                    if(preWeldSeekSwitch.checked)
                    {
                        RecipeLabData.PreWeldSeek = true
                    }
                    else
                    {
                        RecipeLabData.PreWeldSeek = false
                    }
                }
            }
            MouseArea{
                id:clickPreWeldSeek
                anchors.fill: preWeldSeekSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    preWeldSeekSwitch.toggle()
                }
            }
        }

        BransonLeftBorderRectangle {
            id: postWeldSeekTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            checked: postWeldSeekSwitch.checked
            anchors{
                top: separatorLine3.bottom
                topMargin: height*0.1
                left: preWeldSeekTitle.right
                leftMargin: height *0.15
            }
            Text {
                id: textPostWeldSeekTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextPostWeldSeek
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconPostWeldSeek
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
                id: postWeldSeekSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.PostWeldSeek
                onCheckedChanged: {
                    if(postWeldSeekSwitch.checked)
                    {
                        RecipeLabData.PostWeldSeek = true
                    }
                    else
                    {
                        RecipeLabData.PostWeldSeek = false
                    }
                }
            }
            MouseArea{
                id:clickPostWeldSeek
                anchors.fill: postWeldSeekSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    postWeldSeekSwitch.toggle()
                }
            }
        }

        Rectangle{
            id: separatorLine4
            width: parent.width
            height: 1
            anchors.top: preWeldSeekTitle.bottom
            anchors.topMargin: preWeldSeekTitle.height*0.1
            anchors.left: parent.left
            anchors.right: energyBrakeTimeTitle.right
            color: Style.blackFontColor
        }

        BransonLeftBorderRectangle {
            id: pretriggerEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: parent.left
            anchors.top: separatorLine4.bottom
            anchors.topMargin: height*0.1
            Text {
                id: txtPretriggerTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.top: parent.top
                text: qmltextPretrigger
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconPretriggerrEnable
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
                id: pretriggerEnableSwitch
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.PretriggerEnable
                onCheckedChanged: {
                    if(pretriggerEnableSwitch.checked){
                        RecipeLabData.PretriggerEnable = true
                        pretriggerEnableTitle.checked = true
                        pretriggerAmplitudeTitle.checked = true
                        pretriggerDistanceTitle.checked = true
                        pretriggerTimeTitle.checked = true
                        pretriggerType.checked = true
                    }
                    else{
                        RecipeLabData.PretriggerEnable=false
                        pretriggerEnableTitle.checked = false
                        pretriggerAmplitudeTitle.checked = false
                        pretriggerDistanceTitle.checked = false
                        pretriggerTimeTitle.checked = false
                        pretriggerType.checked = false
                    }
                }
            }
            MouseArea{
                id:clickPretriggerEnable
                anchors.fill: pretriggerEnableSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    pretriggerEnableSwitch.toggle()
                }
            }
        }
        BransonLeftBorderRectangle {
            id: pretriggerAmplitudeTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            checked: pretriggerEnableSwitch.checked
            anchors{
                left: systemType === SystemTypeDef.ACTUATOR_MANUAL? parent.left : pretriggerEnableTitle.right
                leftMargin: systemType === SystemTypeDef.ACTUATOR_MANUAL? 0: height*0.15
                top: systemType === SystemTypeDef.ACTUATOR_MANUAL? pretriggerEnableTitle.bottom : separatorLine4.bottom
                topMargin: height*0.1
            }
            Text {
                id: textPretriggerAmplitude
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextPretriggerAmplitude
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconPretriggerAmplitude
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
            Text {
                id: textPretriggerAmplitudeValue
                text:RecipeLabData.PretriggerAmplitude+ " "+ mainWindow.qmltextAmplitudeUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: parent.height*0.18
            }
            MouseArea{
                id:clickPretriggerAmplitude
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: RecipeLabData.PretriggerEnable
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextPretriggerAmplitude, mainWindow.qmltextAmplitudeUnit, 0, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramPretriggerAmplitude), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramPretriggerAmplitude), RecipeLabData.PretriggerAmplitude)
                }
            }
        }
        BransonLeftBorderRectangle {
            id: pretriggerType
            width: parent.width*0.48
            height: systemType === SystemTypeDef.ACTUATOR_MANUAL? parentItem.height*0.25 : parentItem.height*0.35
            anchors{
                left: systemType === SystemTypeDef.ACTUATOR_MANUAL? pretriggerEnableTitle.right : parent.left
                leftMargin: systemType === SystemTypeDef.ACTUATOR_MANUAL? height*0.15 : 0
                top: systemType === SystemTypeDef.ACTUATOR_MANUAL? separatorLine4.bottom : pretriggerEnableTitle.bottom
                topMargin: pretriggerEnableTitle.height*0.1
            }
            Text {
                id: textPreriggerTypeStart
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.1
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.08
                text: qmltextPretriggerStart
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIconPretriggerType
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Grid{
                anchors.top: textPreriggerTypeStart.bottom
                anchors.left: textPreriggerTypeStart.left
                anchors.topMargin: systemType === SystemTypeDef.ACTUATOR_MANUAL? pretriggerType.height*0.35 : pretriggerType.height*0.3
                anchors.leftMargin: pretriggerType.width*0.1
                anchors.fill: parent
                rowSpacing:systemType === SystemTypeDef.ACTUATOR_MANUAL? 0 : parent.height*0.3
                columns: 2
                BransonRadioButton{
                    id:radioButtonDistance
                     labelText: qmltextDistance
                    visible: systemType === SystemTypeDef.ACTUATOR_ELECTRONIC
                    enabled: systemType === SystemTypeDef.ACTUATOR_ELECTRONIC && RecipeLabData.PretriggerEnable
                    offColor:Style.blackFontColor
                    height: pretriggerType.height*0.18
                    width: pretriggerType.width*0.55
                    anchors.topMargin: pretriggerType.height *0.50
                    font.pixelSize: pretriggerEnableTitle.height*0.18
                    checked: RecipeLabData.PretriggerType===RecipeEnum.DISTANCE_PRETRIGGER_IDX
                    onClicked: {
                        radioButtonDistance.checked = true
                        RecipeLabData.PretriggerType = RecipeEnum.DISTANCE_PRETRIGGER_IDX
                    }
                }
                BransonRadioButton{
                    id:radioButtonAuto
                    labelText: qmltextAuto
                    height: pretriggerType.height*0.18
                    width: pretriggerType.width*0.40
                    font.pixelSize: pretriggerEnableTitle.height*0.18
                    checked: RecipeLabData.PretriggerType===RecipeEnum.AUTO_PRETRIGGER_IDX
                    enabled: RecipeLabData.PretriggerEnable
                    onClicked: {
                        radioButtonAuto.checked = true
                        RecipeLabData.PretriggerType = RecipeEnum.AUTO_PRETRIGGER_IDX
                    }
                }
                BransonRadioButton{
                    id:radioButtonTime
                    labelText: qmltextTime
                    height: pretriggerType.height*0.18
                    width: pretriggerType.width*0.40
                    font.pixelSize: pretriggerEnableTitle.height*0.18
                    checked: RecipeLabData.PretriggerType===RecipeEnum.TIME_PRETRIGGER_IDX
                    enabled: RecipeLabData.PretriggerEnable
                    onClicked: {
                        radioButtonTime.checked = true
                        RecipeLabData.PretriggerType = RecipeEnum.TIME_PRETRIGGER_IDX
                    }
                }
            }
        }

        Rectangle{
            id: separatorLine8
            width: parent.width
            height: 1
            anchors.top: pretriggerType.bottom
            anchors.topMargin: preWeldSeekTitle.height*0.1
            anchors.left: parent.left
            anchors.right: energyBrakeTimeTitle.right
            color: Style.blackFontColor
        }
        BransonLeftBorderRectangle {
            id: pretriggerDistanceTitle
            width: parent.width*0.48
            height: pretriggerType.height
            visible: systemType===SystemTypeDef.ACTUATOR_MANUAL || radioButtonAuto.checked? false : true
            anchors{
                top: pretriggerEnableTitle.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                leftMargin: pretriggerEnableTitle.height*0.15
                left:pretriggerEnableTitle.right
            }
            Text {
                id: textPretriggerDistance
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextPretriggerDistance
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIconPretriggerDistance
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text {
                id: textDistance
                text: (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.PretriggerDistance.toFixed(2) + " "+mainWindow.qmltextDistanceUnit :
                                                                  RecipeLabData.PretriggerDistance.toFixed(4) + " "+mainWindow.qmltextDistanceUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clickPretriggerDistance
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: RecipeLabData.PretriggerEnable
                onClicked:
                {
                    if(mainWindow.qmltextDistanceUnit === "mm")
                    {
                        mainWindow.showPrimaryNumpad(qmltextPretriggerDistance, mainWindow.qmltextDistanceUnit, 2, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramPretriggerDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramPretriggerDistance), RecipeLabData.PretriggerDistance.toFixed(2))
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmltextPretriggerDistance, mainWindow.qmltextDistanceUnit, 4, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramPretriggerDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramPretriggerDistance), RecipeLabData.PretriggerDistance.toFixed(4))
                    }
                }
            }
        }
        BransonLeftBorderRectangle {
            id: pretriggerTimeTitle
            width: parent.width*0.48
            height: pretriggerType.height
            visible: radioButtonTime.checked
            anchors{
                top: systemType === SystemTypeDef.ACTUATOR_MANUAL? pretriggerType.bottom : pretriggerAmplitudeTitle.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                left:pretriggerEnableTitle.right
                leftMargin: pretriggerEnableTitle.height*0.15
            }
            Text {
                id: textPretriggerTime
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextPretriggerTime
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIconPretriggerTime
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text{
                id: textPretriggerTimeValue
                text:RecipeLabData.PretriggerTime.toFixed(3) + " "+ mainWindow.qmltextTimeUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clickPretriggerTime
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: RecipeLabData.PretriggerEnable
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextPretriggerTime, mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramPretriggerTime), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramPretriggerTime), RecipeLabData.PretriggerTime.toFixed(3))
                }
            }
        }

        Rectangle{
            id: separatorLine5
            width: parent.width
            height: 1
            anchors.top: afterburstTimeTitle.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
            visible: true
            enabled: true
        }

        BransonLeftBorderRectangle {
            id: actuatorClearEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: parent.left
            anchors.top: separatorLine5.bottom
            anchors.topMargin: height*0.1
            checked: RecipeLabData.ActuatorClear
            visible: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC )? true :false
            Text {
                id: txtActuatorClear
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.top: parent.top
                text: qmltextActuatorClear
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconActuatorClear
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
                id: actuatorClearSwitch
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.ActuatorClear
                state: RecipeLabData.ActuatorClear
                onCheckedChanged: {
                    if(actuatorClearSwitch.checked)
                    {
                        RecipeLabData.ActuatorClear = true
                    }
                    else
                    {
                        RecipeLabData.ActuatorClear = false
                    }
                }
            }
            MouseArea{
                id:clickActuatorClear
                anchors.fill: actuatorClearSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    actuatorClearSwitch.toggle()
                }
            }
        }
        BransonLeftBorderRectangle {
                 id: setting
                 width: parent.width*0.48
                 height: parentItem.height*0.25
                 anchors.left: actuatorClearEnableTitle.left
                 anchors.top: actuatorClearEnableTitle.bottom
                 anchors.topMargin: height*0.1
                 checked: actuatorClearSwitch.checked
                 visible: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC )? true :false
                 Text {
                     id: settingTitle
                     anchors.left: parent.left
                     anchors.leftMargin: parent.width*0.1
                     anchors.top: parent.top
                     anchors.topMargin: parent.height*0.08
                     text: qmltextSetting
                     color: Style.blackFontColor
                     font.pixelSize: pretriggerEnableTitle.height*0.18
                 }
                 Image {
                     id: infoIconSetting
                     anchors.top: parent.top
                     anchors.topMargin: parent.height*0.15
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
                 Grid{
                     anchors.top: parent.top
                     anchors.left: parent.left
                     anchors.topMargin: setting.height*0.5
                     anchors.leftMargin: setting.width*0.1
                     anchors.fill: parent
                     columns: 2
                     BransonRadioButton{
                         id:settingDistance
                         labelText:qmltextDistance
                         offColor:Style.blackFontColor
                         height: setting.height*0.18
                         width: setting.width*0.55
                         font.pixelSize: setting.height*0.18
                         enabled: actuatorClearSwitch.checked
                         checked: (RecipeLabData.ActuatorClearType === RecipeEnum.ACTUTATOR_DISTANCE_IDX) ? true: false
                         onClicked: {
                             settingDistance.checked =true

                             actuatorDistance.checked = true
                             actuatorDistance.visible = true
                             actuatorTimeTitle.visible = false
                             actuatorTimeTitle.checked = false
                             RecipeLabData.ActuatorClearType = RecipeEnum.ACTUTATOR_DISTANCE_IDX
                         }
                     }
                     BransonRadioButton{
                         id:settingTime
                         labelText: qmltextTime
                         offColor:Style.blackFontColor
                         height: setting.height*0.18
                         width: setting.width*0.40
                         font.pixelSize: setting.height*0.18
                         enabled: actuatorClearSwitch.checked
                         checked: (RecipeLabData.ActuatorClearType === RecipeEnum.ACTUTATOR_TIME_IDX) ? true: false
                         onClicked: {
                             settingTime.checked =true
                             actuatorDistance.visible = false
                             actuatorTimeTitle.visible = true
                             actuatorTimeTitle.checked = true
                             actuatorDistance.checked = false
                             RecipeLabData.ActuatorClearType = RecipeEnum.ACTUTATOR_TIME_IDX
                         }
                     }
                 }
             }





        BransonLeftBorderRectangle {
            id: actuatorDistance
            width: parent.width*0.48
            height: pretriggerType.height
            visible:  (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC ) ? settingDistance.checked : false//settingDistance.checked
            enabled: setting.checked
            checked: RecipeLabData.ActuatorClear
            anchors{
                top: separatorLine5.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                leftMargin: pretriggerEnableTitle.height*0.15
                left:actuatorClearEnableTitle.right
            }
            Text {
                id: textactDistance
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextActDistance
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIconactDistance
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text {
                id: textactuatorDistance
                text: (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.ActuatorClearDistance.toFixed(2) + " "+mainWindow.qmltextDistanceUnit :
                                                                  RecipeLabData.ActuatorClearDistance.toFixed(4) + " "+mainWindow.qmltextDistanceUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clickactDistance
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(setting.checked)
                    {
                        if(mainWindow.qmltextDistanceUnit === "mm")
                        {
                            mainWindow.showPrimaryNumpad(qmltextActDistance, mainWindow.qmltextDistanceUnit, 2, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramActuatorClearDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramActuatorClearDistance), RecipeLabData.ActuatorClearDistance.toFixed(2))
                        }

                        else
                        {
                            mainWindow.showPrimaryNumpad(qmltextActDistance, mainWindow.qmltextDistanceUnit, 4, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramActuatorClearDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramActuatorClearDistance), RecipeLabData.ActuatorClearDistance.toFixed(4))
                        }
                    }
                }
            }
        }

        BransonLeftBorderRectangle {
            id: actuatorTimeTitle
            width: parent.width*0.48
            height: pretriggerType.height
            visible:(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC) ? settingTime.checked : false
            enabled: setting.checked
            checked: RecipeLabData.ActuatorClear
            anchors{
                top: separatorLine5.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                left:actuatorClearEnableTitle.right
                leftMargin: pretriggerEnableTitle.height*0.15
            }
            Text {
                id: textactTime
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextActTime
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIconActTime
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text{
                id: textActTimeValue
                text:RecipeLabData.ActuatorClearTime.toFixed(3) + " "+ mainWindow.qmltextTimeUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clickActTime
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if(setting.checked){
                        mainWindow.showPrimaryNumpad(qmltextActTime, mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramActuatorClearTime), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramActuatorClearTime), RecipeLabData.ActuatorClearTime.toFixed(3))
                    }
                }
            }
        }









        Rectangle{
            id: separatorLine6
            width: parent.width
            height: 1
            anchors.top: setting.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
            visible: systemType===SystemTypeDef.ACTUATOR_ELECTRONIC
        }

        BransonLeftBorderRectangle {
            id: rapidTraverseEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:separatorLine8.bottom
            anchors.topMargin: height*0.1
            checked: rapidTraverseSwitch.checked
            visible: systemType === SystemTypeDef.ACTUATOR_ELECTRONIC
            Text {
                id: texTrapidTraverseTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextRapidTraverse
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconTrapidTraverse
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
                id: rapidTraverseSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.RapidTraverse
                onCheckedChanged: {
                    if(rapidTraverseSwitch.checked)
                    {
                        RecipeLabData.RapidTraverse = true
                    }
                    else
                    {
                        RecipeLabData.RapidTraverse = false
                    }
                }
            }
            MouseArea{
                id:clickRapidTraverse
                anchors.fill: rapidTraverseSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    rapidTraverseSwitch.toggle()
                }
            }
        }

        BransonLeftBorderRectangle {
            id: rapidTraverseDistanceTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: rapidTraverseEnableTitle.right
            anchors.leftMargin: height*0.15
            anchors.top:separatorLine8.bottom
            anchors.topMargin: height*0.1
            checked: rapidTraverseSwitch.checked
            enabled: rapidTraverseSwitch.checked
            visible: systemType === SystemTypeDef.ACTUATOR_ELECTRONIC
            Text {
                id: textRapidTraverseDistance
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextRapidTraverseDistance
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image
            {
                id: infoIconRapidTraverseDistance
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                source: "qrc:/Images/info.png"
                width: parent.width*0.08
                height: parent.width*0.08
                MouseArea
                {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }

            Text
            {
                id: textRapidTraverseDistanceValue
                text: (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.RapidTraverseDistance.toFixed(2) + " "+mainWindow.qmltextDistanceUnit :
                                                                  RecipeLabData.RapidTraverseDistance.toFixed(4) + " "+mainWindow.qmltextDistanceUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }

            MouseArea
            {
                id:clickRapidTraverseDistance
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled:rapidTraverseSwitch.checked
                onClicked:
                {
                    if(mainWindow.qmltextDistanceUnit === "mm")
                    {
                        mainWindow.showPrimaryNumpad(qmltextRapidTraverseDistance, mainWindow.qmltextDistanceUnit, 2, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramRapidTraverseDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramRapidTraverseDistance), RecipeLabData.RapidTraverseDistance.toFixed(2))
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmltextRapidTraverseDistance, mainWindow.qmltextDistanceUnit, 4, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramRapidTraverseDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramRapidTraverseDistance), RecipeLabData.RapidTraverseDistance.toFixed(4))
                    }
                }
            }
        }

        BransonLeftBorderRectangle {
            id: triggerLostEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:rapidTraverseEnableTitle.bottom
            anchors.topMargin: height*0.1
            anchors.left: parent.left
            checked: triggerLostSwitch.checked
            visible: systemType === SystemTypeDef.ACTUATOR_ELECTRONIC
            Text {
                id: textTriggerLostTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextTriggerLost
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconTriggerLost
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
                id: triggerLostSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.TriggerLost
                onCheckedChanged: {
                    if(triggerLostSwitch.checked)
                    {
                        RecipeLabData.TriggerLost = true
                    }
                    else
                    {
                        RecipeLabData.TriggerLost = false
                    }
                }
            }
            MouseArea{
                id:clickTriggerLost
                anchors.fill: triggerLostSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    triggerLostSwitch.toggle()
                }
            }
        }

        BransonLeftBorderRectangle {
            id: externalAmpSettingEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top:rapidTraverseEnableTitle.bottom
            anchors.topMargin: height*0.1
            anchors.left:triggerLostEnableTitle.visible === true ? triggerLostEnableTitle.right : parent.left
            anchors.leftMargin: triggerLostEnableTitle.visible === true ? height*0.15 : 0

            checked: extAmpettingSwitch.checked
            visible: true
            Text {
                id: textExtAmplitudeSettingTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextExternalAmpltudeSetting + "\n" + qmltextExternalAmpltudeSetting2
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconExtAmpSettLost
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
                id: extAmpettingSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.ExternalAmplitudeSetting
                onCheckedChanged: {
                    if(extAmpettingSwitch.checked)
                    {
                        RecipeLabData.ExternalAmplitudeSetting = true
                    }
                    else
                    {
                        RecipeLabData.ExternalAmplitudeSetting = false
                    }
                }
            }
            MouseArea{
                id:extAmplitudeSetting
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    extAmpettingSwitch.toggle()
                }
            }
        }


        Rectangle{
            id: separatorLine0
            width: parent.width
            height: 1
            anchors.top: triggerLostEnableTitle.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
            visible: true
            enabled: true
        }


        BransonLeftBorderRectangle {
                 id: triggertype
                 width: parent.width*0.48
                 height: parentItem.height*0.25
                 anchors.left: actuatorClearEnableTitle.left
                 anchors.top: separatorLine0.bottom
                 anchors.topMargin: height*0.1
                 checked: true
                 visible: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC )? true :false
                 Text {
                     id: triggertypetext
                     anchors.left: parent.left
                     anchors.leftMargin: parent.width*0.1
                     anchors.top: parent.top
                     anchors.topMargin: parent.height*0.08
                     text: qmltextTriggerType
                     color: Style.blackFontColor
                     font.pixelSize: pretriggerEnableTitle.height*0.18
                 }
                 Image {
                     id: infoIcontriggertype
                     anchors.top: parent.top
                     anchors.topMargin: parent.height*0.15
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
                 Grid{
                     anchors.top: parent.top
                     anchors.left: parent.left
                     anchors.topMargin: setting.height*0.5
                     anchors.leftMargin: setting.width*0.1
                     anchors.fill: parent
                     columns: 2
                     BransonRadioButton{
                         id:triggertypeForce
                         labelText:qmltextTrigForce
                         offColor:Style.blackFontColor
                         height: setting.height*0.18
                         width: setting.width*0.55
                         font.pixelSize: setting.height*0.18
                         enabled: triggertype.checked
                         checked: (RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_FORCE_IDX || RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_SWITCH_IDX) ? true: false
                         onClicked: {
                             RecipeLabData.TriggerType = RecipeEnum.TRIGGER_TYPE_FORCE_IDX
                             triggertypeForce.checked =true
                             triggertypeForceTitle.checked = true
                         }
                     }
                     BransonRadioButton{
                         id:triggertypeDistnce
                         labelText: qmltextDistance
                         offColor:Style.blackFontColor
                         height: setting.height*0.18
                         width: setting.width*0.40
                         font.pixelSize: setting.height*0.18
                         enabled: triggertype.checked
                         checked: (RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_DISTANCE_IDX) ? true: false
                         onClicked: {
                             RecipeLabData.TriggerType = RecipeEnum.TRIGGER_TYPE_DISTANCE_IDX
                             triggertypeForceTitle.checked =false
                             triggertypeDistnce.checked =true
                             triggertypedistanceTitle.checked = true
                         }
                     }
                 }
             }

        BransonLeftBorderRectangle {
            id: triggertypeForceTitle
            width: parent.width*0.48
            height: triggertype.height
            visible: triggertypeForce.checked
            checked:  (RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_FORCE_IDX || RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_SWITCH_IDX) ? true: false
            anchors{
                top: separatorLine0.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                left:triggertype.right
                leftMargin: pretriggerEnableTitle.height*0.15
            }
            Text {
                id: texttriggertypeForce
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text:  qmltextForce
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIcontriggertypeForce
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text{
                id: texttriggertypeForcevalue
                text: (mainWindow.qmltextForceUnit === "N") ? RecipeLabData.TriggerTypeForce.toFixed(0) + " "+mainWindow.qmltextForceUnit :
                                                                  RecipeLabData.TriggerTypeForce.toFixed(1) + " "+mainWindow.qmltextForceUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clicktriggertypeForce
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(mainWindow.qmltextForceUnit === "N")
                    {
                        mainWindow.showPrimaryNumpad(qmltextForce, mainWindow.qmltextForceUnit, 0, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramTriggerForce), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramTriggerForce), RecipeLabData.TriggerTypeForce.toFixed(0))
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmltextForce, mainWindow.qmltextForceUnit, 1, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramTriggerForce), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramTriggerForce), RecipeLabData.TriggerTypeForce.toFixed(1))
                    }
                }
            }
        }

        BransonLeftBorderRectangle {
            id: triggertypedistanceTitle
            width: parent.width*0.48
            height: triggertype.height
            visible: triggertypeDistnce.checked
            checked:  RecipeLabData.TriggerType === RecipeEnum.TRIGGER_TYPE_DISTANCE_IDX ? true :false
            anchors{
                top: separatorLine0.bottom
                topMargin: pretriggerEnableTitle.height*0.1
                left:triggertype.right
                leftMargin: pretriggerEnableTitle.height*0.15
            }
            Text {
                id: texttriggertypedistance
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextTriggerDistance
                color: Style.blackFontColor
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            Image {
                id: infoIcontriggertypedistance
                anchors.top: parent.top
                anchors.topMargin: pretriggerEnableTitle.height*0.1
                anchors.right: parent.right
                anchors.rightMargin: pretriggerEnableTitle.width*0.05
                source: "qrc:/Images/info.png"
                width: pretriggerEnableTitle.width*0.08
                height: pretriggerEnableTitle.width*0.08
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Text{
                id: texttriggertypedistancevalue
                text: (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.TriggerTypeDistance.toFixed(2) + " "+mainWindow.qmltextDistanceUnit :
                                                                  RecipeLabData.TriggerTypeDistance.toFixed(4) + " "+mainWindow.qmltextDistanceUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: height*0.15
                font.pixelSize: pretriggerEnableTitle.height*0.18
            }
            MouseArea{
                id:clicktriggertypedistance
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    //  if(setting.checked){
                    if(mainWindow.qmltextDistanceUnit === "mm")
                    {
                        mainWindow.showPrimaryNumpad(qmltextTriggerDistance, mainWindow.qmltextDistanceUnit, 2, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramTriggerDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramTriggerDistance), RecipeLabData.TriggerTypeDistance.toFixed(2))
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmltextTriggerDistance, mainWindow.qmltextDistanceUnit, 4, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramTriggerDistance), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramTriggerDistance), RecipeLabData.TriggerTypeDistance.toFixed(4))

                    }
                    // }
                }
            }
        }



        Rectangle{
            id: separatorLine10
            width: parent.width
            height: 1
            anchors.top: triggertype.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
            visible: true
            enabled: true
        }




        BransonLeftBorderRectangle {
            id: timeSeekEnableTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.top: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL )? separatorLine0.bottom :separatorLine10.bottom
            anchors.topMargin: height*0.1
            anchors.left: triggertype.left
            checked: timeSeekSwitch.checked
            visible: true
            Text {
                id: texttimeSeekTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextTimeSeekEnable
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIcontimeSeek
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
                id: timeSeekSwitch
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.25
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                checked: RecipeLabData.IsTimeSeekEnable
                onCheckedChanged: {
                    if(timeSeekSwitch.checked)
                    {
                        RecipeLabData.IsTimeSeekEnable = true
                    }
                    else
                    {
                        RecipeLabData.IsTimeSeekEnable = false
                    }
                }
            }
            MouseArea{
                id:timeSeekClick
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    timeSeekSwitch.toggle()
                }
            }
        }

        BransonLeftBorderRectangle {
            id: timeSeekPeriodTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: timeSeekEnableTitle.right
            anchors.leftMargin: height*0.15
            anchors.top: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL )? separatorLine0.bottom :separatorLine10.bottom
            anchors.topMargin: height*0.1
            checked: RecipeLabData.IsTimeSeekEnable
            visible: true
            Text {
                id: texttimeSeekPeriod
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextTimeSeek
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIcontimeSeekPeriod
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
            Text {
                id: texttimeSeekPeriodValue
                text: RecipeLabData.TimeSeekPeriod.toFixed(3) + " "+ qmltextMinUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clicktimeSeekPeriod
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled:timeSeekSwitch.checked
                onClicked: {
                    if(timeSeekSwitch.checked)
                    {
                        mainWindow.showPrimaryNumpad(qmltextTimeSeek, qmltextMinUnit, 3, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramSeekTime), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramSeekTime), RecipeLabData.TimeSeekPeriod.toFixed(3))

                    }
                }
            }
        }

        Rectangle{
            id: separatorLine11
            width: parent.width
            height: 1
            anchors.top: timeSeekEnableTitle.bottom
            anchors.topMargin: afterburstTimeTitle.height*0.1
            anchors.left: parent.left
            anchors.right: afterburstAmplitudeTitle.right
            color: Style.blackFontColor
            visible: true
            enabled: true
        }

        BransonLeftBorderRectangle {
            id: scrubAmplitudeTitle
            width: parent.width*0.48
            height: parentItem.height*0.25
            anchors.left: parent.left
            anchors.top: separatorLine11.bottom
            anchors.topMargin: height*0.1
            checked: true
            visible: true
            Text {
                id: textscrubAmplitude
                anchors.leftMargin: parent.width*0.08
                anchors.topMargin: parent.height*0.15
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextScrubAmplitude
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: infoIconscrubAmplitude
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
            Text {
                id: textscrubAmplitudeValue
                text: RecipeLabData.ScrubAmplitude + " "+mainWindow.qmltextAmplitudeUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.15
            }
            MouseArea{
                id:clickscrubAmplitude
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    {
                        mainWindow.showPrimaryNumpad(qmltextScrubAmplitude, mainWindow.qmltextAmplitudeUnit, 2, RecipeLabData.getMinParameterAZParametersValue(paramEnum.paramScrubAmplitude), RecipeLabData.getMaxParameterAZParametersValue(paramEnum.paramScrubAmplitude), RecipeLabData.ScrubAmplitude.toFixed(2))
                    }
                }
            }
        }
    }
}




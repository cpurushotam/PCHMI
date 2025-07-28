/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file displays the Pretrigger Screen under weldprocess tab.

 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Layouts
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"
Item {

    property string qmltextMenuName:                 "PRETRIGGER"
    property string qmltextPretriggerDistance:       "PRETRIGGER DISTANCE"
    property string qmltextPretriggerAmplitude:      "PRETRIGGER AMPLITUDE"
    property string qmltextPretriggerTime:           "PRETRIGGER TIME"
    property string qmltextTime:                     "TIME"
    property string qmltextDistance:                 "DISTANCE"
    property string qmltextAuto:                     "AUTO"
    property string qmltextPretriggerStart:          "PRETRIGGER START"
    property string qmltextResetToDefault:           "RESET TO DEFAULT"

    property var qmlTextArray: [qmltextMenuName, qmltextPretriggerDistance, qmltextPretriggerAmplitude, qmltextPretriggerTime, qmltextTime, qmltextDistance, qmltextAuto,qmltextPretriggerStart,qmltextResetToDefault]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDPROCESS_PRETRIGGER, qmlTextArray)
        qmltextMenuName = qmlTextArray[textEnum.textMenuNameIdx]
        qmltextPretriggerDistance = qmlTextArray[textEnum.textPretrigerDistanceIdx]
        qmltextPretriggerAmplitude = qmlTextArray[textEnum.textPretrigerAmplitudeIdx]
        qmltextPretriggerTime = qmlTextArray[textEnum.textPretrigerTimeIdx]
        qmltextTime = qmlTextArray[textEnum.textTimeIdx]
        qmltextDistance = qmlTextArray[textEnum.textDistanceIdx]
        qmltextAuto = qmlTextArray[textEnum.textAutoIdx]
        qmltextPretriggerStart=qmlTextArray[textEnum.textPretriggerStartIdx]
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
    QtObject{
        id:textEnum
        readonly property int textMenuNameIdx :               0
        readonly property int textPretrigerDistanceIdx :      1
        readonly property int textPretrigerAmplitudeIdx :     2
        readonly property int textPretrigerTimeIdx :          3
        readonly property int textTimeIdx :                   4
        readonly property int textDistanceIdx :               5
        readonly property int textAutoIdx:                    6
        readonly property int textPretriggerStartIdx:         7
        readonly property int textResetToDefaultIdx:          8
    }
    QtObject
    {
        id: paramEnum
        readonly property int paramPretrigerDistance :      0
        readonly property int paramPretrigerAmplitude :     1
        readonly property int paramPretrigerTime :          2
    }
    BransonLeftBorderRectangle {
        id: pretriggerEnableTitle
        width: parent.width*0.48
        height: parent.height*0.25


        Text {
            id: txtPretriggerTitle
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.top: parent.top
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
                    RecipeLabData.PretriggerEnable=true
                    pretriggerEnableTitle.checked = true
                    pretriggerAmplitudeTitle.checked = true
                    pretriggerTimeTitle.checked = true
                    pretriggerType.checked = true
                    pretriggerDistanceTitle.checked = true
                }
                else{
                    RecipeLabData.PretriggerEnable=false
                    pretriggerEnableTitle.checked = false
                    pretriggerAmplitudeTitle.checked = false
                    pretriggerDistanceTitle.checked = false
                    pretriggerType.checked = false
                    pretriggerTimeTitle.checked = false
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
        height: parent.height*0.25
        anchors.left: pretriggerEnableTitle.right
        anchors.leftMargin: height*0.15
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
        Text {
            id: textAmplitude
            text:RecipeLabData.PretriggerAmplitude + " "+ mainWindow.qmltextAmplitudeUnit
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
            onClicked: {
                if(RecipeLabData.PretriggerEnable)
                {
                    mainWindow.showPrimaryNumpad(qmltextPretriggerAmplitude, mainWindow.qmltextAmplitudeUnit, 0, RecipeLabData.getMinPretriggerParametersValue(paramEnum.paramPretrigerAmplitude), RecipeLabData.getMaxPretriggerParametersValue(paramEnum.paramPretrigerAmplitude), RecipeLabData.PretriggerAmplitude)
                }
            }
        }
    }
    BransonLeftBorderRectangle {
        id: pretriggerDistanceTitle
        width: parent.width*0.48
        height: parent.height*0.25
        anchors.top:pretriggerEnableTitle.bottom
        anchors.topMargin: height*0.15
        anchors.leftMargin: height*0.15
        anchors.left:pretriggerEnableTitle.right
        visible: radioButtonAuto.checked?false:true

        Text {
            id: textPretriggerDistance
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text: qmltextPretriggerDistance
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
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
            font.pixelSize: parent.height*0.18
        }
        MouseArea{
            id:clickPretriggerDistance
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(RecipeLabData.PretriggerEnable)
                {
                    if(mainWindow.qmltextDistanceUnit === "mm")
                    {
                        mainWindow.showPrimaryNumpad(qmltextPretriggerDistance, mainWindow.qmltextDistanceUnit, 2, RecipeLabData.getMinPretriggerParametersValue(paramEnum.paramPretrigerDistance), RecipeLabData.getMaxPretriggerParametersValue(paramEnum.paramPretrigerDistance), RecipeLabData.PretriggerDistance.toFixed(2))
                    }

                    else
                    {
                        mainWindow.showPrimaryNumpad(qmltextPretriggerDistance, mainWindow.qmltextDistanceUnit, 4, RecipeLabData.getMinPretriggerParametersValue(paramEnum.paramPretrigerDistance), RecipeLabData.getMaxPretriggerParametersValue(paramEnum.paramPretrigerDistance), RecipeLabData.PretriggerDistance.toFixed(4))
                    }
                }
            }
        }
    }
    BransonLeftBorderRectangle {
        id: pretriggerTimeTitle
        width: parent.width*0.48
        height: parent.height*0.25
        anchors.top:pretriggerEnableTitle.bottom
        anchors.topMargin: height*0.15
        anchors.leftMargin: height*0.15
        anchors.left:pretriggerEnableTitle.right
        visible: radioButtonTime.checked?true:false
        Text {
            id: textPretriggerTime
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text: qmltextPretriggerTime
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.18
        }
        Text{
            id: textTime
            text:RecipeLabData.PretriggerTime.toFixed(3)+ " "+  mainWindow.qmltextTimeUnit
            color: Style.blackFontColor
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.05
            anchors.bottom: parent.bottom
            anchors.bottomMargin: height*0.15
            font.pixelSize: parent.height*0.18
        }
        MouseArea{
            id:clickPretriggerTime
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(RecipeLabData.PretriggerEnable){
                    mainWindow.showPrimaryNumpad(qmltextPretriggerTime,  mainWindow.qmltextTimeUnit, 3, RecipeLabData.getMinPretriggerParametersValue(paramEnum.paramPretrigerTime), RecipeLabData.getMaxPretriggerParametersValue(paramEnum.paramPretrigerTime), RecipeLabData.PretriggerTime.toFixed(3))
                }
            }
        }
    }
    BransonLeftBorderRectangle {
        id: pretriggerType
        width: parent.width*0.48
        height: parent.height*0.35
        anchors.left: parent.left
        anchors.top: pretriggerEnableTitle.bottom
        anchors.topMargin: pretriggerTimeTitle.height*0.15
        Text {
            id: xtextPretriggerTime
            anchors.leftMargin: parent.width*0.08
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.top: parent.top
            text:qmltextPretriggerStart
            color: Style.blackFontColor
            font.pixelSize: parent.height*0.14
        }
        Grid{
            anchors.top: xtextPretriggerTime.bottom
            anchors.left: xtextPretriggerTime.left
            anchors.topMargin: pretriggerType.height*0.4
            anchors.leftMargin: pretriggerType.width*0.07
            anchors.fill: parent
            rowSpacing: parent.height*0.2
            columns: 2
            BransonRadioButton{
                id:radioButtonDistance
                labelText: qmltextDistance
                offColor:Style.blackFontColor
                height: parent.height*0.25
                width: parent.width*0.55
                font.pixelSize: pretriggerDistanceTitle.height*0.18
                checked: (RecipeLabData.PretriggerType===RecipeEnum.DISTANCE_PRETRIGGER_IDX)?true:false
                enabled:   RecipeLabData.PretriggerEnable ?true:false
                visible: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC) ? true : false
                onClicked: {
                        radioButtonDistance.checked=true
                        RecipeLabData.PretriggerType = RecipeEnum.DISTANCE_PRETRIGGER_IDX
                }
            }
            BransonRadioButton{
                id:radioButtonAuto
                height: parent.height*0.25
                width: parent.width*0.40
                labelText: qmltextAuto
                font.pixelSize: pretriggerDistanceTitle.height*0.18
                checked: (RecipeLabData.PretriggerType===RecipeEnum.AUTO_PRETRIGGER_IDX)?true:false
                enabled:   RecipeLabData.PretriggerEnable ?true:false
                onClicked: {
                        radioButtonAuto.checked=true
                        RecipeLabData.PretriggerType = RecipeEnum.AUTO_PRETRIGGER_IDX
                }
            }
            BransonRadioButton{
                id:radioButtonTime
                labelText: qmltextTime
                height: parent.height*0.25
                width: parent.width*0.40
                font.pixelSize: pretriggerDistanceTitle.height*0.18
                checked: (RecipeLabData.PretriggerType===RecipeEnum.TIME_PRETRIGGER_IDX)?true:false
                enabled:   RecipeLabData.PretriggerEnable ?true:false
                onClicked: {
                        radioButtonTime.checked=true
                        RecipeLabData.PretriggerType = RecipeEnum.TIME_PRETRIGGER_IDX
                }
            }
        }
    }
    BransonPrimaryButton
    {
        id: btnResetDefaults
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

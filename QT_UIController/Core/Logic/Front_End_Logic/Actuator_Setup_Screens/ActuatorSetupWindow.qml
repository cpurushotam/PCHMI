/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

This file contains the Actuator Setup Window related implementation.

***************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {
    property string qmltextMenuName                        : "Actuator Setup"
    property string qmltextHornDownClamp                   : "Horn Down Clamp:"
    property string qmltextOn                              : "On"
    property string qmltextOff                             : "Off"
    property string qmltextRetract                         : "RETRACT"
    property string qmltextWeldPressure                    : "WELD PRESSURE"
    property string qmltextHornClamp                       : "Horn Clamp:"
    property string qmltextPressure                        : "Pressure"
    property string qmltextAbsolutlPosition                : "Absolute Position"
    property string qmltextActualForce                     : "Actual Force"
    property string qmltextMaximumVelocity                 : "Maximum Velocity"
    property string qmltextHornDown                        : "HORN DOWN"
    property string qmltextStrokeLength                    : "Stroke Length"
    property string qmltextHome                            : "Home"
    property string qmltextWarning                         : SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL ? "WARNING: Before using Manual override, make sure all" : ""
    property string qmltextWarning2                         : SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL ? "hands are clear of the Horn and base surface." : ""
    readonly property int weldPressureIdx : 11
    property var qmlTextArray: [qmltextHornDownClamp, qmltextOn, qmltextOff, qmltextRetract, qmltextWeldPressure, qmltextHornClamp, qmltextPressure,
        qmltextAbsolutlPosition, qmltextActualForce, qmltextMaximumVelocity,  qmltextHornDown, qmltextStrokeLength, qmltextHome, qmltextWarning, textWarning2Idx]
    property int systemType: SystemConfiguration.CurrentSystemType
    signal actuatorSetupDataChanged()
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ACTUATORSETUP, qmlTextArray)
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ACTUATORSETUP, qmltextMenuName)
        qmltextHornDownClamp     = qmlTextArray[textEnum.textHornDownClampIdx]
        qmltextOn= qmlTextArray[textEnum.textOnIdx]
        qmltextOff= qmlTextArray[textEnum.textOffIdx]
        qmltextRetract= qmlTextArray[textEnum.textRetractIdx]
        qmltextWeldPressure= qmlTextArray[textEnum.textWeldPressureIdx]
        qmltextHornClamp= qmlTextArray[textEnum.textHornClampIdx]
        qmltextPressure= qmlTextArray[textEnum.textPressureIdx]
        qmltextAbsolutlPosition= qmlTextArray[textEnum.textAbsolutlPositionIdx]
        qmltextActualForce= qmlTextArray[textEnum.textActualForceIdx]
        qmltextMaximumVelocity= qmlTextArray[textEnum.textMaximumVelocityIdx]
        qmltextHornDown= qmlTextArray[textEnum.textHornDownIdx]
        qmltextStrokeLength= qmlTextArray[textEnum.textStrokeLengthIdx]
        qmltextHome= qmlTextArray[textEnum.textHomeIdx]
        qmltextWarning = qmlTextArray[textEnum.textWarningIdx]
        qmltextWarning2 = qmlTextArray[textEnum.textWarning2Idx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    QtObject
    {
        id: textEnum
        readonly property int textHornDownClampIdx                   : 0
        readonly property int textOnIdx                              : 1
        readonly property int textOffIdx                             : 2
        readonly property int textRetractIdx                         : 3
        readonly property int textWeldPressureIdx                    : 4
        readonly property int textHornClampIdx                       : 5
        readonly property int textPressureIdx                        : 6
        readonly property int textAbsolutlPositionIdx                : 7
        readonly property int textActualForceIdx                     : 8
        readonly property int textMaximumVelocityIdx                 : 9
        readonly property int textFindPartContactIdx                 : 10
        readonly property int textHornDownIdx                        : 11
        readonly property int textStrokeLengthIdx                    : 12
        readonly property int textHomeIdx                            : 13
        readonly property int textWarningIdx                         : 14
        readonly property int textWarning2Idx                        : 15
    }

    QtObject
    {
        id: operationTypeEnum
        readonly property int noneOpType                             : 0
        readonly property int hornDownOpType                         : 1
        readonly property int findPartContactOpType                  : 2
    }

    Item
    {
        id: manualBackground
        width: parent.width
        height: parent.height
        visible: (systemType === SystemTypeDef.ACTUATOR_MANUAL)? true : false
        enabled: (systemType === SystemTypeDef.ACTUATOR_MANUAL)? true : false
        Text
        {
            id: txtRacipeNumberName
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            text: ActuatorSetupData.RecipeNumber+ ": "+ ActuatorSetupData.RecipeName
            color: Style.blackFontColor
        }
        Text
        {
            id: txtHornDownClamp
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            text: qmltextHornDownClamp
            color: Style.blackFontColor
        }
        Text
        {
            id: txtHornDownClampStatus
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: txtHornDownClamp.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            text: hornDownClampEnableSwitch.checked? qmltextOn : qmltextOff
            color: Style.blackFontColor
        }
        BransonSwitch
        {
            id: hornDownClampEnableSwitch
            anchors.left: parent.left
            anchors.leftMargin: Math.round(200 * Style.scaleHint)
            anchors.verticalCenter: txtHornDownClampStatus.verticalCenter
            maxWidth: Math.round(15 * Style.scaleHint)
            maxHeight:Math.round(15 * Style.scaleHint)
            rectWidth:Math.round(35 * Style.scaleHint)
            rectHeight:Math.round(12 * Style.scaleHint)
            onCheckedChanged: {
                ActuatorSetupData.updateHornDownClampOnOff(hornDownClampEnableSwitch.checked)
            }
        }
        Text
        {
            id: txtPressureManual
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(20 * Style.scaleHint)
            anchors.top: txtHornDownClamp.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            text: qmltextPressure
            color: Style.blackFontColor
        }
        Text
        {
            id: txtPressureValueManual
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: txtPressureManual.right
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.top: txtHornDownClamp.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            text: "= " + ActuatorSetupData.Pressure.toFixed(2) +" "+ mainWindow.qmltextPressureUnit
            color: Style.blackFontColor
        }
        BransonPrimaryButton
        {
            id: btnRetractManual
            implicitWidth: Math.round(130 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: txtHornDownClamp.bottom
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: qmltextRetract
            buttonColor:btnRetractManual.enabled ? Style.buttonBackgroundColor : Style.disabledButtonBackgroundColor
            font.family: Style.regular.name
            enabled: hornDownClampEnableSwitch.checked
            onClicked:
            {
                ActuatorSetupData.sendHornRetractRequest()
            }
        }
        Image {
            id: warningSymbol
            source: "qrc:/Images/WarningSymbol.png"
            anchors.left: btnRetractManual.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: btnRetractManual.top
            width:btnRetractManual.height
            height:btnRetractManual.height
        }
        Text {
            id: warningText
            anchors.left: warningSymbol.right
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.top: btnRetractManual.top
            text: qmltextWarning + "\n" + qmltextWarning2
            color: Style.blackFontColor
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
        }
    }

    Item
    {
        id: electricBackground
        width: parent.width
        height: parent.height
        visible:(systemType === SystemTypeDef.ACTUATOR_ELECTRONIC)? true : false
        enabled:(systemType === SystemTypeDef.ACTUATOR_ELECTRONIC)? true : false
        Rectangle
        {
            id:hornStateRect
            anchors.left: parent.left
            width: parent.width * 0.4
            height: parent.height
            anchors.top: parent.top
            color: Style.backgroundColor

            Rectangle
            {
                id:hornStatusRectangle
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: Math.round(100 * Style.scaleHint)
                height:Math.round(300 * Style.scaleHint)
                color: "#DAE8F5"
            }
            Image {
                id: hornPointerArrow
                source: "qrc:/Images/buoy.svg"
                x:hornStatusRectangle.x+Math.round(100 * Style.scaleHint)
                y: (hornStatusRectangle.y-height/2) + Math.round(2.4* ActuatorSetupData.AbsolutePosition * Style.scaleHint)
                width: Math.round(40 * Style.scaleHint)
                height:Math.round(20 * Style.scaleHint)
            }
            Text {
                id: hornPointerArrowValue
                text: ActuatorSetupData.AbsolutePosition.toFixed(2) + " "+ mainWindow.qmltextDistanceUnit
                font.pixelSize:Math.round(12  * Style.scaleHint)
                anchors.left: hornPointerArrow.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: hornPointerArrow.verticalCenter
                color: Style.blackFontColor
            }
            Rectangle
            {
                id:strokeLineRectangle
                anchors.top: hornStatusRectangle.bottom
                anchors.horizontalCenter: hornStatusRectangle.horizontalCenter
                width: Math.round(130 * Style.scaleHint)
                height:Math.round(5 * Style.scaleHint)
                color: "#B0B0B0"
            }
            Text {
                id: strokeLengthText
                text: qmltextStrokeLength
                font.pixelSize:Math.round(12  * Style.scaleHint)
                anchors.right: strokeLineRectangle.left
                anchors.rightMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: strokeLineRectangle.verticalCenter
                color: Style.blackFontColor
            }
            Text {
                id: strokeLengthValue
                text: ActuatorSetupData.StrokeLengthValue.toFixed(2) + " " + mainWindow.qmltextDistanceUnit
                font.pixelSize:Math.round(12  * Style.scaleHint)
                anchors.left: strokeLineRectangle.right
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: strokeLineRectangle.verticalCenter
                color: Style.blackFontColor
            }
            Text {
                id: homePositionText
                text: qmltextHome
                font.pixelSize:Math.round(12  * Style.scaleHint)
                anchors.right: hornStatusRectangle.left
                anchors.rightMargin: Math.round(60 * Style.scaleHint)
                anchors.top: hornStatusRectangle.top
                color: Style.blackFontColor
            }
        }

        Text
        {
            id: txtRacipeNameElectric
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: hornWeldPresure.left
            anchors.top: parent.top
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            text: ActuatorSetupData.RecipeNumber+ ": "+ ActuatorSetupData.RecipeName
            color: Style.blackFontColor
        }

        BransonLeftBorderRectangle {
            id: hornWeldPresure
            width: parent.width* 0.3
            height: parent.height*0.15
            anchors.right: txtHornClamp.left
            anchors.rightMargin: Math.round(10 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            checked: true

            Text {
                id: textHornWeldPresure
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.topMargin: Math.round(15 * Style.scaleHint)
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextWeldPressure
                color: Style.blackFontColor
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            }
            Text {
                id: textWeldPresure
                text:ActuatorSetupData.RecipeWeldPressure.toFixed(1) + " "+mainWindow.qmltextPressureUnit
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: Math.round(15 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(15 * Style.scaleHint)
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            }
            MouseArea{
                id:clickHornWeldPresure
                anchors.fill: textWeldPresure
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    mainWindow.showPrimaryNumpad(qmltextWeldPressure, mainWindow.qmltextPressureUnit, 2, RecipeLabData.getMinParamValue(weldPressureIdx), RecipeLabData.getMaxParamValue(weldPressureIdx), ActuatorSetupData.RecipeWeldPressure.toFixed(1))
                }
            }
        }

        Text
        {
            id: txtHornClamp
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin:  Math.round(130 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            text: qmltextHornClamp
            color: Style.blackFontColor
        }
        Text
        {
            id: txtHornClampStatus
            font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
            anchors.left: txtHornClamp.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(40 * Style.scaleHint)
            text: hornClampEnableSwitch.checked? qmltextOn : qmltextOff
            color: Style.blackFontColor
        }

        BransonSwitch
        {
            id: hornClampEnableSwitch
            anchors.right: parent.right
            anchors.rightMargin: Math.round(40 * Style.scaleHint)
            anchors.verticalCenter: txtHornClampStatus.verticalCenter
            maxWidth: Math.round(15 * Style.scaleHint)
            maxHeight:Math.round(15 * Style.scaleHint)
            rectWidth:Math.round(35 * Style.scaleHint)
            rectHeight:Math.round(12 * Style.scaleHint)
            onCheckedChanged: {
                ActuatorSetupData.updateHornDownClampOnOff(hornClampEnableSwitch.checked)
            }
        }

        Rectangle{
            id: hornParameterRect
            anchors.top: txtHornClamp.bottom
            anchors.topMargin: Math.round(30 * Style.scaleHint)
            anchors.left: txtHornClamp.left
            anchors.right: parent.right

            Text
            {
                id: txtPressure
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.top: parent.top
                text: qmltextPressure
                color: Style.blackFontColor
            }
            Text
            {
                id: txtPressureValue
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(125 * Style.scaleHint)
                anchors.top: parent.top
                text: "= " + ActuatorSetupData.Pressure.toFixed(2) + " "+ mainWindow.qmltextPressureUnit
                color: Style.blackFontColor
            }
            Text
            {
                id: txtAbsolutePosition
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.top: txtPressure.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: qmltextAbsolutlPosition
                color: Style.blackFontColor
            }
            Text
            {
                id: txtAbsolutePositionValue
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(125 * Style.scaleHint)
                anchors.top: txtPressure.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: "= " + ActuatorSetupData.AbsolutePosition.toFixed(2) + " "+ mainWindow.qmltextDistanceUnit
                color: Style.blackFontColor
            }
            Text
            {
                id: txtActualForce
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.top: txtAbsolutePosition.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: qmltextActualForce
                color: Style.blackFontColor
            }
            Text
            {
                id: txtActualForceValue
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(125 * Style.scaleHint)
                anchors.top: txtAbsolutePosition.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: /*"= " +ActuatorSetupData.ActualForce.toFixed(2) + " "+ mainWindow.qmltextForceUnit*/
                {
                    if(mainWindow.qmltextForceUnit === "N")
                    {
                        return "= " +ActuatorSetupData.ActualForce.toFixed(0) + " "+ mainWindow.qmltextForceUnit
                    }

                    else
                    {
                        return "= " +ActuatorSetupData.ActualForce.toFixed(1) + " "+ mainWindow.qmltextForceUnit
                    }
                }

                color: Style.blackFontColor
            }
            Text
            {
                id: txtMaximumVelocity
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.top: txtActualForce.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: qmltextMaximumVelocity
                color: Style.blackFontColor
            }
            Text
            {
                id: txtMaximumVelocityValue
                font.pixelSize:Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(125 * Style.scaleHint)
                anchors.top: txtActualForce.bottom
                anchors.topMargin: Math.round(20 * Style.scaleHint)
                text: "= " + ActuatorSetupData.MaximumVelocity.toFixed(2) + " "+ mainWindow.qmltextVelocityUnit
                color: Style.blackFontColor
            }
        }

        BransonPrimaryButton
        {
            id: btnRetract
            implicitWidth: Math.round(130 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin:  Math.round(20 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            text: qmltextRetract
            buttonColor:btnRetract.enabled ? Style.buttonBackgroundColor : Style.disabledButtonBackgroundColor
            font.family: Style.regular.name
            enabled: hornClampEnableSwitch.checked
            onClicked:
            {
                ActuatorSetupData.sendHornRetractRequest()
            }
        }
    }

    Connections {
        target: ActuatorSetupData
        function onActuatorSetupDataChanged(){
            ActuatorSetupData.ScreenOpenOnHMI = true
        }
    }

    Component.onCompleted: {
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.ACTUATORSETUP
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.ACTUATORSETUP)
        ActuatorSetupData.isActuatorScreenNav(true)
        updateLanguage()
    }

    Component.onDestruction: {
        ActuatorSetupData.ScreenOpenOnHMI = false
    }
}

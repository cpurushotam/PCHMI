/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

  ChooseParmeters.qml - file is responsible for displaying the column names selection by the user.

 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.12
import Style 1.0
import Com.Branson.LanguageEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {
    id: chooseParametersView
    readonly property int imageSize: Math.round(24 * Style.scaleHint)
    property string qmltextChooseParameters       : "CHOOSE PARAMETERS"
    property string qmltextDone                   : "DONE"
    property var qmlCheckedArray                  : []
    property var qmlWeldResultIndex               :"Weld Result Index"
    property var qmlWeldRecipeNumber              :"Weld Recipe Number"
    property var qmlWeldRecipeVersionNumber       :"Weld Recipe Version Number"
    property var qmlDateTime                      :"Date Time"
    property var qmlStackSerialNumber             :"Stack Serial Number"
    property var qmlPowerSupplySerialNumber       :"Power Supply Serial Number"
    property var qmlActuatorSerialNumber          :"Actuator Serial Number"
    property var qmlASCSerialNumber               :"ASCSerial Number"
    property var qmlCycleCounter                  :"Cycle Counter"
    property var qmlWeldMode                      :"Weld Mode"
    property var qmlWeldTime                      :"Weld Time"
    property var qmlHoldTime                      :"Hold Time"
    property var qmlWeldEnergy                    :"Weld Energy"
    property var qmlWeldPeakPower                 :"Weld Peak Power"
    property var qmlStartFrequency                :"Start Frequency"
    property var qmlFrequencyChange               :"Frequency Change"
    property var qmlCycleTime                     :"Cycle Time"
    property var qmlUserName                      :"User Name"
    property var qmlPartID                        :"Part ID"
    property var qmlBatchID                       :"Batch ID"
    property var qmlTriggerPoint                  :"Trigge rPoint"
    property var qmlWeldSonicPoint                :"Weld Sonic Point"
    property var qmlHoldPoint                     :"Hold Point"
    property var qmlAlarmID                       :"Alarm ID"
    property var qmlWeldStatus                    :"Weld Status"
    property var qmlRecipeStatus                  :"Recipe Status"
    property var qmlWeldPressure                  :"Weld Pressure"
    property var qmlHoldPressure                  :"Hold Pressure"
    property var qmlMaxWeldForce                  :"Max Weld Force"
    property var qmlMaxHoldForce                  :"Max Hold Force"
    property var qmlEndWeldForce                  :"End Weld Force"
    property var qmlEndHoldForce                  :"End Hold Force"
    property var qmlWeldAbsolute                  :"Weld Absolute"
    property var qmlTotalAbsolute                 :"Total Absolute"
    property var qmlVelocity                      :"Velocity"
    property var qmlDownSpeed                     :"Down Speed"
    property var qmlTriggerDistance               :"TriggerDistance"
    property var qmlWeldCollapseDistance          :"Weld Collapse Distance"
    property var qmlHoldCollapseDistance          :"Hold Collapse Distance"
    property var qmlTotalCollapseDistance         :"Total Collapse Distance"


    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    property var qmlTextArray: [qmltextChooseParameters, qmltextDone,qmltextDone, qmlCheckedArray,qmlWeldResultIndex,qmlWeldRecipeNumber,qmlDateTime
        ,qmlStackSerialNumber,qmlPowerSupplySerialNumber,qmlActuatorSerialNumber,qmlASCSerialNumber,qmlCycleCounter,qmlWeldMode,qmlHoldTime,qmlWeldEnergy,
        qmlWeldPeakPower,qmlStartFrequency,qmlFrequencyChange,qmlCycleTime,qmlUserName,qmlPartID,qmlBatchID,qmlTriggerPoint,qmlWeldSonicPoint,qmlHoldPoint,
        qmlAlarmID,qmlWeldStatus,qmlRecipeStatus,qmlWeldPressure,qmlHoldPressure,qmlMaxWeldForce,qmlMaxHoldForce,qmlEndWeldForce,qmlEndHoldForce,qmlWeldAbsolute,
        qmlTotalAbsolute,qmlVelocity,qmlTriggerDistance,qmlWeldCollapseDistance,qmlHoldCollapseDistance,qmlTotalCollapseDistance,qmlWeldTime]

    QtObject
    {
        id: textEnum
        readonly property int chooseParametersIdx           : 0
        readonly property int doneIdx                       : 1
        readonly property int checkedArrayIdx               : 2
        readonly property int weldResultIndexIdx            : 3
        readonly property int weldRecipeNumberIdx           : 4
        readonly property int dateTimeIdx                   : 5
        readonly property int stackSerialNumberIdx          : 6
        readonly property int powerSupplySerialNumberIdx    : 7
        readonly property int actuatorSerialNumberIdx       : 8
        readonly property int aSCSerialNumberIdx            : 9
        readonly property int cycleCounterIdx               : 10
        readonly property int weldModeIdx                   : 11
        readonly property int holdTimeIdx                   : 12
        readonly property int weldEnergyIdx                 : 13
        readonly property int weldPeakPowerIdx              : 14
        readonly property int startFrequencyIdx             : 15
        readonly property int frequencyChangeIdx            : 16
        readonly property int cycleTimeIdx                  : 17
        readonly property int userNameIdx                   : 18
        readonly property int partIDIdx                     : 19
        readonly property int batchIDIdx                    : 20
        readonly property int triggerPointIdx               : 21
        readonly property int weldSonicPointIdx             : 22
        readonly property int holdPointIdx                  : 23
        readonly property int alarmIDIdx                    : 24
        readonly property int weldStatusIdx                 : 25
        readonly property int recipeStatusIdx               : 26
        readonly property int weldPressureIdx               : 27
        readonly property int holdPressureIdx               : 28
        readonly property int maxWeldForceIdx               : 29
        readonly property int maxHoldForceIdx               : 30
        readonly property int endWeldForceIdx               : 31
        readonly property int endHoldForceIdx               : 32
        readonly property int weldAbsoluteIdx               : 33
        readonly property int totalAbsoluteIdx              : 34
        readonly property int velocityIdx                   : 35
        readonly property int triggerDistanceIdx            : 36
        readonly property int weldCollapseDistanceIdx       : 37
        readonly property int holdCollapseDistanceIdx       : 38
        readonly property int totalCollapseDistanceIdx      : 39
        readonly property int weldTimeIdx                   : 40
    }
    QtObject
    {
        id: actuatorTypeEnum
        readonly property int actuatorManual  : 1
        readonly property int actuatorElectric : 2
        readonly property int actuatorElectricPlus  : 3
        readonly property int noActuator : 4
        readonly property int actuatorConfigMax  : 5
    }
    QtObject
    {
        id: chooseparameter
        readonly property int weldRecipeNumberCP  : 0
        readonly property int weldRecipeVersionNumberCP : 1
        readonly property int dateTimeCP  : 2
        readonly property int stackSerialNumberCP : 3
        readonly property int powerSupplySerialNumberCP  : 4
        readonly property int actuatorSerialNumberCP  : 5
        readonly property int aSCSerialNumberCP : 6
        readonly property int cycleCounterCP  : 7
        readonly property int weldModeCP : 8
        readonly property int weldTimeCP  : 9
        readonly property int holdTimeCP  : 10
        readonly property int weldEnergyCP : 11
        readonly property int weldPeakPowerCP  : 12
        readonly property int startFrequencyCP : 13
        readonly property int frequencyChangeCP  : 14
        readonly property int cycleTimeCP  : 15
        readonly property int userNameCP : 16
        readonly property int partIDCP  : 17
        readonly property int batchIDCP : 18
        readonly property int triggerPointCP  : 19
        readonly property int weldSonicPointCP  : 20
        readonly property int holdPointCP : 21
        readonly property int alarmIDCP  : 22
        readonly property int weldStatusCP : 23
        readonly property int recipeStatusCP  : 24
        readonly property int weldPressureCP  : 25
        readonly property int holdPressureCP : 26
        readonly property int maxWeldForceCP  : 27
        readonly property int maxHoldForceCP : 28
        readonly property int endWeldForceCP  : 29
        readonly property int endHoldForceCP : 30
        readonly property int weldAbsoluteCP  : 31
        readonly property int totalAbsoluteCP : 32
        readonly property int velocityCP  : 33
        readonly property int triggerDistanceCP  : 34
        readonly property int weldCollapseDistanceCP : 35
        readonly property int holdCollapseDistanceCP  : 36
        readonly property int totalCollapseDistanceCP : 37

    }
    QtObject
    {
        id: chooseparameterElectric
        readonly property int weldPressureCPE  : 0
        readonly property int holdPressureCPE : 1
        readonly property int maxWeldForceCPE  : 2
        readonly property int maxHoldForceCPE : 3
        readonly property int endWeldForceCPE  : 4
        readonly property int endHoldForceCPE : 5
        readonly property int weldAbsoluteCPE  : 6
        readonly property int totalAbsoluteCPE : 7
        readonly property int velocityCPE  : 8
        readonly property int triggerDistanceCPE  : 9
        readonly property int weldCollapseDistanceCPE : 10
        readonly property int holdCollapseDistanceCPE  : 11
        readonly property int totalCollapseDistanceCPE : 12

    }
    signal checkedParams( var qmlCheckedArray);
    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS , qmlTextArray)
        qmltextChooseParameters                            = qmlTextArray[textEnum.textChooseParametersIdx]
        qmltextDone                                        = qmlTextArray[textEnum.textDoneIdx]
        qmltextWeldResultIndex                             = qmlTextArray[textEnum.textWeldResultIndexIdx]
        qmltextWeldRecipeNumber                            = qmlTextArray[textEnum.textWeldRecipeNumberIdx]
        qmltextWeldRecipeVersionNumber                     = qmlTextArray[textEnum.textWeldRecipeVersionNumberIdx]
        qmltextDateTime                                    = qmlTextArray[textEnum.textDateTimeIdx]
        qmltextStackSerialNumber                           = qmlTextArray[textEnum.textStackSerialNumberIdx]
        qmltextPowerSupplySerialNumber                     = qmlTextArray[textEnum.textPowerSupplySerialNumberIdx]
        qmltextActuatorSerialNumber                        = qmlTextArray[textEnum.textActuatorSerialNumberIdx]
        qmltextASCSerialNumber                             = qmlTextArray[textEnum.textASCSerialNumberIdx]
        qmltextCycleCounter                                = qmlTextArray[textEnum.textCycleCounterIdx]
        qmltextWeldMode                                    = qmlTextArray[textEnum.textWeldModeIdx]
        qmltextHoldTime                                    = qmlTextArray[textEnum.textHoldTimeIdx]
        qmltextWeldEnergy                                  = qmlTextArray[textEnum.textWeldEnergyIdx]
        qmltextWeldPeakPower                               = qmlTextArray[textEnum.textWeldPeakPowerIdx]
        qmltextStartFrequency                              = qmlTextArray[textEnum.textStartFrequencyIdx]
        qmltextFrequencyChange                             = qmlTextArray[textEnum.textFrequencyChangeIdx]
        qmltextCycleTime                                   = qmlTextArray[textEnum.textCycleTimeIdx]
        qmltextUserName                                    = qmlTextArray[textEnum.textUserNameIdx]
        qmltextPartID                                      = qmlTextArray[textEnum.textPartIDIdx]
        qmltextBatchID                                     = qmlTextArray[textEnum.textBatchIDIdx]
        qmltextTriggerPoint                                = qmlTextArray[textEnum.textTriggerPointIdx]
        qmltextWeldSonicPoint                              = qmlTextArray[textEnum.textWeldSonicPointIdx]
        qmltextHoldPoint                                   = qmlTextArray[textEnum.textHoldPointIdx]
        qmltextAlarmID                                     = qmlTextArray[textEnum.textAlarmIDIdx]
        qmltextWeldStatus                                  = qmlTextArray[textEnum.textWeldStatusIdx]
        qmltextRecipeStatus                                = qmlTextArray[textEnum.textRecipeStatusIdx]
        qmltextWeldPressure                                = qmlTextArray[textEnum.textWeldPressureIdx]
        qmltextHoldPressure                                = qmlTextArray[textEnum.textHoldPressureIdx]
        qmltextMaxWeldForce                                = qmlTextArray[textEnum.textMaxWeldForceIdx]
        qmltextMaxHoldForce                                = qmlTextArray[textEnum.textMaxHoldForceIdx]
        qmltextEndWeldForce                                = qmlTextArray[textEnum.textEndWeldForceIdx]
        qmltextEndHoldForce                                = qmlTextArray[textEnum.textEndHoldForceIdx]
        qmltextWeldAbsolute                                = qmlTextArray[textEnum.textWeldAbsoluteIdx]
        qmltextTotalAbsolute                               = qmlTextArray[textEnum.textTotalAbsoluteIdx]
        qmltextVelocity                                    = qmlTextArray[textEnum.textVelocityIdx]
        qmltextDownSpeed                                   = qmlTextArray[textEnum.textDownSpeedIdx]
        qmltextTriggerDistance                             = qmlTextArray[textEnum.textTriggerDistanceIdx]
        qmltextWeldCollapseDistance                        = qmlTextArray[textEnum.textWeldCollapseDistanceIdx]
        qmltextHoldCollapseDistance                        = qmlTextArray[textEnum.textHoldCollapseDistanceIdx]
        qmltextTotalCollapseDistance                       = qmlTextArray[textEnum.textTotalCollapseDistanceIdx]
        qmltextWeldTime                                    = qmlTextArray[textEnum.textCWeldTimeIdx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.ANALYTICS, qmlTextMenuName)
    }
    function createCheckBoxModel()
    {
        checkboxModel.clear()
        if(SystemConfiguration.CurrentSystemType == SystemTypeDef.ACTUATOR_MANUAL)
        {
            checkboxModel.append({ "text": qmlWeldRecipeNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldRecipeNumberCP)})
            checkboxModel.append({ "text": qmlWeldRecipeVersionNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldRecipeVersionNumberCP) })
            checkboxModel.append({ "text": qmlDateTime, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.dateTimeCP)})
            checkboxModel.append({ "text": qmlStackSerialNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.stackSerialNumberCP) })
            checkboxModel.append({ "text": qmlPowerSupplySerialNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.powerSupplySerialNumberCP) })
            checkboxModel.append({ "text": qmlActuatorSerialNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.actuatorSerialNumberCP) })
            checkboxModel.append({ "text": qmlASCSerialNumber, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.aSCSerialNumberCP) })
            checkboxModel.append({ "text": qmlCycleCounter, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.cycleCounterCP) })
            checkboxModel.append({ "text": qmlWeldMode, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldModeCP) })
            checkboxModel.append({ "text": qmlWeldTime, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldTimeCP) })
            checkboxModel.append({ "text": qmlHoldTime, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.holdTimeCP) })
            checkboxModel.append({ "text": qmlWeldEnergy, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldEnergyCP) })
            checkboxModel.append({ "text": qmlWeldPeakPower, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldPeakPowerCP) })
            checkboxModel.append({ "text": qmlStartFrequency, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.startFrequencyCP) })
            checkboxModel.append({ "text": qmlFrequencyChange, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.frequencyChangeCP) })
            checkboxModel.append({ "text": qmlCycleTime, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.cycleTimeCP) })
            checkboxModel.append({ "text": qmlUserName, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.userNameCP) })
            checkboxModel.append({ "text": qmlPartID, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.partIDCP) })
            checkboxModel.append({ "text": qmlBatchID, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.batchIDCP) })
            checkboxModel.append({ "text": qmlTriggerPoint, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.triggerPointCP) })
            checkboxModel.append({ "text": qmlWeldSonicPoint, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldSonicPointCP) })
            checkboxModel.append({ "text": qmlHoldPoint, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.holdPointCP) })
            checkboxModel.append({ "text": qmlAlarmID, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.alarmIDCP) })
            checkboxModel.append({ "text": qmlWeldStatus, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldStatusCP) })
            checkboxModel.append({ "text": qmlRecipeStatus, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.recipeStatusCP) })
            checkboxModel.append({ "text": qmlWeldPressure, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldPressureCP) })
            checkboxModel.append({ "text": qmlHoldPressure, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.holdPressureCP) })
            checkboxModel.append({ "text": qmlMaxWeldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.maxWeldForceCP) })
            checkboxModel.append({ "text": qmlMaxHoldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.maxHoldForceCP) })
            checkboxModel.append({ "text": qmlEndWeldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.endWeldForceCP) })
            checkboxModel.append({ "text": qmlEndHoldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.endHoldForceCP) })
            checkboxModel.append({ "text": qmlWeldAbsolute, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldAbsoluteCP) })
            checkboxModel.append({ "text": qmlTotalAbsolute, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.totalAbsoluteCP) })
            checkboxModel.append({ "text": qmlVelocity, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.velocityCP) })
            checkboxModel.append({ "text": qmlTriggerDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.triggerDistanceCP) })
            checkboxModel.append({ "text": qmlWeldCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.weldCollapseDistanceCP) })
            checkboxModel.append({ "text": qmlHoldCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.holdCollapseDistanceCP) })
            checkboxModel.append({ "text": qmlTotalCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameter.totalCollapseDistanceCP) })
        }
        else
        {
            checkboxModel.append({ "text": qmlWeldPressure, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.weldPressureCPE) })
            checkboxModel.append({ "text": qmlHoldPressure, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.holdPressureCPE) })
            checkboxModel.append({ "text": qmlMaxWeldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.maxWeldForceCPE) })
            checkboxModel.append({ "text": qmlMaxHoldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.maxHoldForceCPE) })
            checkboxModel.append({ "text": qmlEndWeldForce,"checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.endWeldForceCPE) })
            checkboxModel.append({ "text": qmlEndHoldForce, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.endHoldForceCPE) })
            checkboxModel.append({ "text": qmlWeldAbsolute, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.weldAbsoluteCPE) })
            checkboxModel.append({ "text": qmlTotalAbsolute, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.totalAbsoluteCPE) })
            checkboxModel.append({ "text": qmlVelocity, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.velocityCPE) })
            checkboxModel.append({ "text": qmlTriggerDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.triggerDistanceCPE) })
            checkboxModel.append({ "text": qmlWeldCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.weldCollapseDistanceCPE) })
            checkboxModel.append({ "text": qmlHoldCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.holdCollapseDistanceCPE) })
            checkboxModel.append({ "text": qmlTotalCollapseDistance, "checked": AnalyticsScreenTableViewOptions.getChooseParameterIndex(chooseparameterElectric.totalCollapseDistanceCPE) })
        }
        selectCheckboxModelPowerOn()
    }
    function selectCheckboxModelPowerOn()
    {
        for (var j=0; j<checkboxModel.count; j++)
        {
            qmlCheckedArray[j]=checkboxModel.get(j).checked
        }
        AnalyticsScreenTableViewOptions.getColumnCheckedList(qmlCheckedArray)
    }
    ListModel
    {
        id: checkboxModel
    }
    Rectangle
    {
        id: parameterView
        width: Math.round(520 * Style.scaleHint)
        height: Math.round(310 * Style.scaleHint)
        anchors.centerIn: parent
        Rectangle
        {
            id: parameterHeader
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            color: Style.headerBackgroundColor
            Text
            {
                id: headerTitle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Math.round(14 * Style.scaleHint)
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.whiteFontColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: qmltextChooseParameters
            }
            Image
            {
                id: closeMark
                width: imageSize
                height: imageSize
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                source: "qrc:/Images/crossMark.svg"
                fillMode: Image.PreserveAspectFit
                sourceSize.width: closeMark.width
                sourceSize.height: closeMark.height
                smooth: true
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                     chooseParametersView.visible = false
                    }
                }
            }
        }
        ScrollView {
            id: frame
            clip: true
            anchors.top: parameterHeader.bottom
            anchors.topMargin: 33
            anchors.bottom: doneButton.top
            anchors.bottomMargin:  33
            anchors.left: parameterHeader.left
            anchors.leftMargin: 24
            anchors.right: parameterHeader.right
            anchors.rightMargin: 24
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            Flickable {
                contentHeight: chooseParametersView.height *1.30
                width: parent.width

                Rectangle {
                    id: parameterLayout

                    anchors.fill: parent
                    border.color: "transparent"
                    clip: true

                    Grid {
                        anchors.fill: parent
                        rowSpacing: Math.round(36 * Style.scaleHint)
                        columns: 3
                        clip: true
                        Repeater {
                            model:checkboxModel
                            delegate:CheckBox
                            {
                                id: customerCheckBoxDelegate
                                height: Math.round(20 * Style.scaleHint)
                                implicitWidth:Math.round(40 * Style.scaleHint)
                                implicitHeight: Math.round(40 * Style.scaleHint)
                                width: parent.width/3
                                checked: model.checked
                                text: model.text
                                font.family: Style.regular.name
                                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                                onCheckedChanged: checkboxModel.setProperty(index, "checked", checked)

                            }
                        }
                    }
                }

            }
        }
        BransonPrimaryButton
        {
            id: doneButton
            anchors.right: parent.right
            anchors.rightMargin: Math.round(13 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(8 * Style.scaleHint)
            width: Math.round(125 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qmltextDone
            fontSize: Math.round(Style.style0 * Style.scaleHint)
            onClicked: {

                for (var j=0; j<checkboxModel.count; j++)
                {
                    qmlCheckedArray[j]=checkboxModel.get(j).checked
                }
                AnalyticsScreenTableViewOptions.getColumnCheckedList(qmlCheckedArray)

                chooseParametersView.visible = false
            }
        }
    }
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    stackRecipeSetting.qml file displays components regarding to stackrecipe screen.

***************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"
Item {
    id:parentItem
    property string qmltextDigitalTune                  : "DIGITAL TUNE"
    property string qmltextEndOfWeldStore               : "END OF WELD STORE"
    property string qmltextInternalFreqOffset           : "INTERNAL FREQ OFFSET"
    property string qmltextFrequencyOffset              : "FREQUENCY OFFSET"
    property string qmltextOn                           : "ON"
    property string qmltextOff                          : "OFF"
    property string qmltextInternal                     : "Internal"
    property string qmltextExternal                     : "External"
    property string qmltextFrequencyLow                 : "FREQUENCY LOW"
    property string qmltextFrequencyHigh                : "FREQUENCY HIGH"
    property string qmltextWeldRampTime                 : "WELD RAMP TIME"
    property string qmltextStartFrequency               : "START FREQUENCY"
    property string qmltextMemoryOffset                 : "MEMORY OFFSET"

    property string qmltextPhaseLimitTime               : "PHASE LIMIT TIME"
    property string qmltextPhaseLimit                   : "PHASE LIMIT"
    property string qmltextControlMode                  : "CONTROL MODE"
    property string qmltextBlindTimeWeld                : "BLIND TIME WELD"
    property string qmltextAmpProportionalGain          : "AMPLITUDE PROPORTIONAL GAIN"
    property string qmltextAmpIntegralGain              : "AMPLITUDE INTEGRAL GAIN"
    property string qmltextAmpDerivativeGain            : "AMPLITUDE DERIVATIVE GAIN"
    property string qmltextPhaseProportionalGain        : "PHASE PROPORTIONAL GAIN"
    property string qmltextPhaseIntegralGain            : "PHASE INTEGRAL GAIN"
    property string qmltextPhaseDerivativeGain          : "PHASE DERIVATIVE GAIN"
    property string qmltextResetToDefault               : "RESET TO DEFAULT"
    property string qmltextClearMemory                  : "CLEAR MEMORY"

    property var qmlTextArray: [qmltextDigitalTune, qmltextEndOfWeldStore, qmltextInternalFreqOffset, qmltextFrequencyOffset, qmltextOn, qmltextOff, qmltextInternal, qmltextExternal,
        qmltextFrequencyLow, qmltextFrequencyHigh, qmltextWeldRampTime, qmltextStartFrequency, qmltextMemoryOffset,qmltextPhaseLimitTime,
        qmltextPhaseLimit, qmltextControlMode, qmltextBlindTimeWeld, qmltextAmpProportionalGain, qmltextAmpIntegralGain, qmltextAmpDerivativeGain, qmltextPhaseProportionalGain,qmltextPhaseIntegralGain, qmltextPhaseDerivativeGain, qmltextResetToDefault, qmltextClearMemory]

    signal recipeLabDataChanged

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_STACKRECIPE, qmlTextArray)
        qmltextDigitalTune = qmlTextArray[textEnum.textDigitalTuneIdx]
        qmltextEndOfWeldStore = qmlTextArray[textEnum.textEndOfWeldStoreIdx]
        qmltextInternalFreqOffset = qmlTextArray[textEnum.textInternalFreqOffsetIdx]
        qmltextFrequencyOffset = qmlTextArray[textEnum.textFrequencyOffsetIdx]
        qmltextOn = qmlTextArray[textEnum.textOnIdx]
        qmltextOff = qmlTextArray[textEnum.textOffIdx]
        qmltextInternal = qmlTextArray[textEnum.textInternalIdx]
        qmltextExternal = qmlTextArray[textEnum.textExternalIdx]
        qmltextFrequencyLow = qmlTextArray[textEnum.textFrequencyLowIdx]
        qmltextFrequencyHigh = qmlTextArray[textEnum.textFrequencyHighIdx]
        qmltextWeldRampTime = qmlTextArray[textEnum.textWeldRampTimeIdx]
        qmltextStartFrequency = qmlTextArray[textEnum.textStartFrequencyIdx]
        qmltextMemoryOffset = qmlTextArray[textEnum.textMemoryOffsetIdx]
        qmltextPhaseLimitTime = qmlTextArray[textEnum.textPhaseLimitTimeIdx]
        qmltextPhaseLimit = qmlTextArray[textEnum.textPhaseLimitIdx]
        qmltextControlMode = qmlTextArray[textEnum.textControlModeIdx]
        qmltextBlindTimeWeld = qmlTextArray[textEnum.textBlindTimeWeldIdx]
        qmltextAmpProportionalGain = qmlTextArray[textEnum.textAmpProportionalGainIdx]
        qmltextAmpIntegralGain = qmlTextArray[textEnum.textAmpIntegralGainIdx]
        qmltextAmpDerivativeGain = qmlTextArray[textEnum.textAmpDerivativeGainIdx]
        qmltextPhaseProportionalGain = qmlTextArray[textEnum.textPhaseProportionalGainIdx]
        qmltextPhaseIntegralGain = qmlTextArray[textEnum.textPhaseIntegralGainIdx]
        qmltextPhaseDerivativeGain = qmlTextArray[textEnum.textPhaseDerivativeGainIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextClearMemory = qmlTextArray[textEnum.textMemoryClearIdx]
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
        stackRecipeModeModel.resetStackRecipeModel()
    }

    QtObject
    {
        id: textEnum
        readonly property int textDigitalTuneIdx               : 0
        readonly property int textEndOfWeldStoreIdx            : 1
        readonly property int textInternalFreqOffsetIdx        : 2
        readonly property int textFrequencyOffsetIdx           : 3
        readonly property int textOnIdx                        : 4
        readonly property int textOffIdx                       : 5
        readonly property int textInternalIdx                  : 6
        readonly property int textExternalIdx                  : 7
        readonly property int textFrequencyLowIdx              : 8
        readonly property int textFrequencyHighIdx             : 9
        readonly property int textWeldRampTimeIdx              : 10
        readonly property int textStartFrequencyIdx            : 11
        readonly property int textMemoryOffsetIdx              : 12
        readonly property int textPhaseLimitTimeIdx            : 13
        readonly property int textPhaseLimitIdx                : 14
        readonly property int textControlModeIdx               : 15
        readonly property int textBlindTimeWeldIdx             : 16
        readonly property int textAmpProportionalGainIdx       : 17
        readonly property int textAmpIntegralGainIdx           : 18
        readonly property int textAmpDerivativeGainIdx         : 19
        readonly property int textPhaseProportionalGainIdx     : 20
        readonly property int textPhaseIntegralGainIdx         : 21
        readonly property int textPhaseDerivativeGainIdx       : 22
        readonly property int textResetToDefaultIdx            : 23
        readonly property int textMemoryClearIdx               : 24
    }

    QtObject
    {
        id: paramEnum
        readonly property int paramDigitalTune               : 0
        readonly property int paramInternalFreqOffset        : 1
        readonly property int paramFrequencyLow              : 2
        readonly property int paramFrequencyHigh             : 3
        readonly property int paramWeldRampTime              : 4
        readonly property int paramMemoryOffset              : 5
        readonly property int paramPhaseLimitTime            : 6
        readonly property int paramPhaseLimit                : 7
        readonly property int paramControlMode               : 8
        readonly property int paramBlindTimeWeld             : 9
        readonly property int paramAmpProportionalGain       : 10
        readonly property int paramAmpIntegralGain           : 11
        readonly property int paramAmpDerivativeGain         : 12
        readonly property int paramPhaseProportionalGain     : 13
        readonly property int paramPhaseIntegralGain         : 14
        readonly property int paramPhaseDerivativeGain       : 15
    }

    Connections
    {
        target: RecipeLabData
        function onRecipeLabDataChanged()
        {
            stackRecipeModeModel.resetStackRecipeModel()
        }
    }
    Flickable
    {
        id: infoScrollRec
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        contentHeight:(RecipeLabData.BransonOnlyLogin ) ? height* 3.4: height* 1.9 //TO DO BRANSON ONLY LOGIN
        clip: true
        BransonLeftBorderRectangle {
            id: digitalTuneTitle
            width: parentItem.width*0.48
            height: parentItem.height*0.25
            checked: true
            Text {
                id: txtDigitalTuneTitle
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextDigitalTune
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Text {
                id: textDigitalTuneValue
                text: RecipeLabData.DigitalTune + " "+ mainWindow.qmltextFrequencyUnit//.FrequencyUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.1
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
            MouseArea{
                id:clickDigitalTune
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextDigitalTune, mainWindow.qmltextFrequencyUnit, 0, RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramDigitalTune), RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramDigitalTune), RecipeLabData.DigitalTune)
                }
            }
        }
        BransonLeftBorderRectangle {
            id: endOfWeldStoreTitle
            anchors.topMargin: height*0.15
            width: parentItem.width*0.48
            height: parentItem.height*0.25
            anchors.left: digitalTuneTitle.right
            anchors.leftMargin: height*0.15
            checked: endOfWeldStoreSwitch.checked
            Text {
                id: textEndOfWeldStore
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextEndOfWeldStore
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Text {
                id: textEndOfWeldStoreValue
                text: endOfWeldStoreSwitch.checked? qmltextOn: qmltextOff
                color: Style.blackFontColor
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.1
                font.pixelSize: parent.height*0.18
            }
            Image {
                id: endOfWeldStoreTitleinfoIcon
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
                id: endOfWeldStoreSwitch
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.18
                checked: RecipeLabData.EndOfWeldStore
                onCheckedChanged: {
                    if(endOfWeldStoreSwitch.checked === true)
                    {
                        RecipeLabData.EndOfWeldStore=true
                    }
                    else
                    {
                        RecipeLabData.EndOfWeldStore=false
                    }
                }
            }
            MouseArea{
                id:clickEndOfWeldStore
                anchors.fill: endOfWeldStoreSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    endOfWeldStoreSwitch.toggle()
                }
            }
        }
        BransonLeftBorderRectangle {
            id: internalFreqOffsetTitle
            width: parentItem.width*0.48
            height: parentItem.height*0.25
            anchors.top:endOfWeldStoreTitle.bottom
            anchors.left: frequencyOffsetTitle.right
            anchors.topMargin: height*0.15
            anchors.leftMargin: height*0.15
            checked: frequencyOffsetSwitch.checked
            enabled: frequencyOffsetSwitch.checked
            Text {
                id: textInternalFreqOffset
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextInternalFreqOffset
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Text {
                id: textInternalFreqOffsetValue
                text:RecipeLabData.InternalFreqOffset + " "+ mainWindow.qmltextFrequencyUnit//.FrequencyUnit
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.1
                visible: internalFreqOffsetTitle.enabled
            }
            Image {
                id: internalFreqOffsetTitleinfoicon
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
            MouseArea{
                id:clickInternalFreqOffset
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    mainWindow.showPrimaryNumpad(qmltextInternalFreqOffset, mainWindow.qmltextFrequencyUnit, 0, RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramInternalFreqOffset), RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramInternalFreqOffset),RecipeLabData.InternalFreqOffset)
                }
            }
        }
        BransonLeftBorderRectangle {
            id: frequencyOffsetTitle
            width: parentItem.width*0.48
            height: parentItem.height*0.25
            anchors.left: parent.left
            anchors.top: digitalTuneTitle.bottom
            anchors.topMargin: height*0.15
            checked: frequencyOffsetSwitch.checked
            Text {
                id: textFrequencyOffset
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.15
                text: qmltextFrequencyOffset
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
            }
            Text {
                id: textFrequencyOffsetValue
                text: frequencyOffsetSwitch.checked? qmltextInternal: qmltextExternal
                color: Style.blackFontColor
                font.pixelSize: parent.height*0.18
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.1
            }
            Image {
                id: frequencyOffsetTitleinfoicon
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
                id: frequencyOffsetSwitch
                maxWidth: rectHeight*1.3
                maxHeight: rectHeight*1.3
                rectWidth: parent.width* 0.1
                rectHeight: parent.height* 0.15
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.08
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height*0.18
                checked: RecipeLabData.FrequencyOffset
                onCheckedChanged: {
                    if(frequencyOffsetSwitch.checked === true)
                    {
                        RecipeLabData.FrequencyOffset=true
                    }
                    else
                    {
                        RecipeLabData.FrequencyOffset=false
                    }
                }
            }
            MouseArea{
                id:clickFrequencyOffset
                anchors.fill: frequencyOffsetSwitch
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    frequencyOffsetSwitch.toggle()
                }
            }
        }
        ListModel{
            id:stackRecipeModeModel
            function resetStackRecipeModel(){
                stackRecipeModeModel.clear()
                stackRecipeModeModel.append({"Name" : qmltextWeldRampTime,
                                                "Value" : RecipeLabData.WeldRampTime,
                                                "Decimals" : 3,
                                                "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramWeldRampTime),
                                                "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramWeldRampTime),
                                                "Unit" : mainWindow.qmltextTimeUnit})

                stackRecipeModeModel.append({"Name" : qmltextMemoryOffset,
                                                "Value" : RecipeLabData.MemoryOffset,
                                                "Decimals" : 0,
                                                "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramMemoryOffset),
                                                "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramMemoryOffset),
                                                "Unit" : mainWindow.qmltextFrequencyUnit})

                if(mainWindow.bransonTabEnable === true)
                {
                    stackRecipeModeModel.append({"Name" : qmltextAmpProportionalGain,
                                                    "Value" : RecipeLabData.AmpProportionalGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramAmpProportionalGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramAmpProportionalGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextAmpIntegralGain,
                                                    "Value" : RecipeLabData.AmpIntegralGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramAmpIntegralGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramAmpIntegralGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextAmpDerivativeGain,
                                                    "Value" : RecipeLabData.AmpDerivativeGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramAmpDerivativeGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramAmpDerivativeGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextPhaseProportionalGain,
                                                    "Value" : RecipeLabData.PhaseProportionalGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramPhaseProportionalGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramPhaseProportionalGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextPhaseIntegralGain,
                                                    "Value" : RecipeLabData.PhaseIntegralGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramPhaseIntegralGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramPhaseIntegralGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextPhaseDerivativeGain,
                                                    "Value" : RecipeLabData.PhaseDerivativeGain,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramPhaseDerivativeGain),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramPhaseDerivativeGain),
                                                    "Unit" : ""})
                    stackRecipeModeModel.append({"Name" : qmltextFrequencyLow,
                                                    "Value" : RecipeLabData.FrequencyLow,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramFrequencyLow),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramFrequencyLow),
                                                    "Unit" : mainWindow.qmltextFrequencyUnit})
                    stackRecipeModeModel.append({"Name" : qmltextFrequencyHigh,
                                                    "Value" : RecipeLabData.FrequencyHigh,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramFrequencyHigh),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramFrequencyHigh),
                                                    "Unit" : mainWindow.qmltextFrequencyUnit})
                    stackRecipeModeModel.append({"Name" : qmltextPhaseLimit,
                                                    "Value" : RecipeLabData.PhaseLimit,
                                                    "Decimals" : 0,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramPhaseLimit),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramPhaseLimit),
                                                    "Unit" : mainWindow.qmltextPhaseUnit})
                    stackRecipeModeModel.append({"Name" : qmltextPhaseLimitTime,
                                                    "Value" : RecipeLabData.PhaseLimitTime,
                                                    "Decimals" : 3,
                                                    "Minimum" : RecipeLabData.getMinStackRecipeParametersValue(paramEnum.paramPhaseLimitTime),
                                                    "Maximum" : RecipeLabData.getMaxStackRecipeParametersValue(paramEnum.paramPhaseLimitTime),
                                                    "Unit" : mainWindow.qmltextPhaseUnit})
                }
            }
        }

        Rectangle
        {
            id: gridviewRect
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: frequencyOffsetTitle.bottom
            anchors.topMargin: frequencyOffsetTitle.height*0.15
            clip : false
            BransonGridView
            {
                id: stackReciepModelGridView
                anchors.fill: parent
                gridViewModel: stackRecipeModeModel
                gridViewDelegate: stackRecipeModeDelegate
                gridViewCellHeight: parentItem.height*0.30
                gridViewCellWidth: parent.width*0.495
            }
        }

        Component
        {
            id: stackRecipeModeDelegate
            BransonLeftBorderRectangle
            {
                id: stackRect
                width: parentItem.width*0.48
                height: parentItem.height*0.26
                checked: true
                Text
                {
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.08
                    anchors.top: parent.top
                    anchors.topMargin: parent.height*0.15
                    text: model.Name
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
                Text
                {
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width*0.05
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height*0.1
                    text: model.Value.toFixed(3) + " " + model.Unit
                    color: Style.blackFontColor
                    font.pixelSize: parent.height*0.18

                }
                MouseArea
                {
                    anchors.fill: stackRect
                    enabled: model.Name !== qmltextMemoryOffset
                    cursorShape:{
                        if(model.Name !== qmltextMemoryOffset)
                        {
                            Qt.PointingHandCursor
                        }
                    }
                    onReleased:
                    {
                        mainWindow.showPrimaryNumpad(model.Name, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                    }
                }
            }
        }
    }
    Rectangle{
        id: bootomControl
        height: Math.round(30 * Style.scaleHint)
        width: parent.width
        anchors.bottom: parent.bottom
        color: Style.backgroundColor
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
        BransonPrimaryButton
        {
            id: btnClearMemory
            implicitWidth: Math.round(170 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.left: btnResetDefault.right
            anchors.leftMargin:  Math.round(5 * Style.scaleHint)
            anchors.bottom: parent.bottom
            text: qmltextClearMemory
            buttonColor: Style.blackFontColor
            font.family: Style.regular.name
            onClicked:
            {
                RecipeLabData.MemoryOffset = 0
            }
        }
    }

}

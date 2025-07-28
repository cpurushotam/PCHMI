/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the weld limit control configurable screen.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 29/01/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
Item {

    property string qmlTextControl:                  "CONTROL"
    property string qmlTextTurnSettingOn:            "Turn Settings On"
    property string qmlTextTurnSettingOff:           "Turn All Off"
    property string qmlTextFrequencyLowCutOff:       "FREQUENCY LOW CUTOFF"
    property string qmlTextPeakPowerCutOff:          "PEAK POWER CUTOFF"
    property string qmlTextFrequencyHigh:            "FREQUENCY HIGH CUTOFF"
    property string qmlTextAbsoluteDistanceCutOff:   "ABSOLUTE DISTANCE CUTOFF"
    property string qmlTextEnergyCutOff:             "ENERGY CUTOFF"
    property string qmlTextCollapseDistanceCutOff:   "COLLAPSE DISTANCE CUTOFF"
    property string qmlTextGroundDetectCutOff:       "GROUND DETECT CUTOFF"
    property string qmlTextTimeCutOff:               "TIME CUTOFF"

    signal recipeLabDataChanged

    property var qmlTextArray: [qmlTextControl,qmlTextTurnSettingOn,qmlTextFrequencyLowCutOff
                                  ,qmlTextPeakPowerCutOff,qmlTextFrequencyHigh,qmlTextAbsoluteDistanceCutOff,qmlTextEnergyCutOff,qmlTextCollapseDistanceCutOff,
                                  qmlTextGroundDetectCutOff,qmlTextTimeCutOff,qmlTextTurnSettingOff]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_LIMITS_CONTROL, qmlTextArray)
        qmlTextControl = qmlTextArray[textEnum.textControlIdx]
        qmlTextTurnSettingOn = qmlTextArray[textEnum.textTurnSettingsOn]
        qmlTextTurnSettingOff = qmlTextArray[textEnum.textTurnSettingsOff]
        qmlTextFrequencyLowCutOff = qmlTextArray[textEnum.textFrequencyLowCutOffIdx]
        qmlTextPeakPowerCutOff = qmlTextArray[textEnum.textPeakPowerCutOffIdx]
        qmlTextFrequencyHigh = qmlTextArray[textEnum.textFrequencyHighIdx]
        qmlTextAbsoluteDistanceCutOff = qmlTextArray[textEnum.textAbsoluteDistanceCutOff]
        qmlTextEnergyCutOff = qmlTextArray[textEnum.textEnergyCutOff]
        qmlTextCollapseDistanceCutOff = qmlTextArray[textEnum.textCollapseDistanceCutOff]
        qmlTextGroundDetectCutOff = qmlTextArray[textEnum.textGroundDetectCutOff]
        qmlTextTimeCutOff = qmlTextArray[textEnum.textTimeCutOff]
        listControlModel.resetControlModel()
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
        updatedataONScreen()
    }

    QtObject
    {
        id: textEnum
        readonly property int textControlIdx:                  0
        readonly property int textTurnSettingsOn:              1
        readonly property int textFrequencyLowCutOffIdx:       2
        readonly property int textPeakPowerCutOffIdx:          3
        readonly property int textFrequencyHighIdx:            4
        readonly property int textAbsoluteDistanceCutOff:      5
        readonly property int textEnergyCutOff:                6
        readonly property int textCollapseDistanceCutOff:      7
        readonly property int textGroundDetectCutOff:          8
        readonly property int textTimeCutOff:                  9
        readonly property int textTurnSettingsOff:             10


    }

    QtObject{
        id:paramEnum
        readonly property int paramPeakPowerCuttoffValue:            0
        readonly property int paramTimeCuttoffValue:                 1
        readonly property int paramFrequencyLowCuttoffValue:         2
        readonly property int paramFrequencyHighCuttoffValue:        3
        readonly property int paramEnergyCuttoffValue:               4
        readonly property int paramGroundDetectCuttoffValue:         5
        readonly property int paramABSDistanceCuttoffValue:          6
        readonly property int paramCollapseDistanceCuttoffValue:     7
    }
    Connections
    {
        target: RecipeLabData
        function onRecipeLabDataChanged()
        {
            listControlModel.resetControlModel()

            listControlModel.setProperty(0, "Value", RecipeLabData.FreqLowCuttoffValue)
            listControlModel.setProperty(1, "Value", RecipeLabData.PeakPowerCuttoffValue)
            listControlModel.setProperty(2, "Value", RecipeLabData.FreqHighCuttoffValue)
            listControlModel.setProperty(3, "Value", RecipeLabData.EnergyCuttoffValue.toFixed(1))
            listControlModel.setProperty(4, "Value", RecipeLabData.GroundDetectCuttoffValue.toFixed(3))
            listControlModel.setProperty(5, "Value", RecipeLabData.TimeCuttoffValue.toFixed(3))

            if (mainWindow.qmltextDistanceUnit === "mm")
            {
                listControlModel.setProperty(6, "Value", RecipeLabData.ABSDistanceCutoffValue.toFixed(2))
                listControlModel.setProperty(7, "Value", RecipeLabData.CollapseDistanceCutoffValue.toFixed(2))
            }

            else
            {
                listControlModel.setProperty(6, "Value", RecipeLabData.ABSDistanceCutoffValue.toFixed(4))
                listControlModel.setProperty(7, "Value", RecipeLabData.CollapseDistanceCutoffValue.toFixed(4))
            }

        }
    }

     function updatedataONScreen()
     {

         listControlModel.setProperty(0, "Value", RecipeLabData.FreqLowCuttoffValue)
         listControlModel.setProperty(1, "Value", RecipeLabData.PeakPowerCuttoffValue)
         listControlModel.setProperty(2, "Value", RecipeLabData.FreqHighCuttoffValue)
         listControlModel.setProperty(3, "Value", RecipeLabData.EnergyCuttoffValue.toFixed(1))
         listControlModel.setProperty(4, "Value", RecipeLabData.GroundDetectCuttoffValue.toFixed(3))
         listControlModel.setProperty(5, "Value", RecipeLabData.TimeCuttoffValue.toFixed(3))

         if (mainWindow.qmltextDistanceUnit === "mm")
         {
             listControlModel.setProperty(6, "Value", RecipeLabData.ABSDistanceCutoffValue.toFixed(2))
             listControlModel.setProperty(7, "Value", RecipeLabData.CollapseDistanceCutoffValue.toFixed(2))
         }

         else
         {
             listControlModel.setProperty(6, "Value", RecipeLabData.ABSDistanceCutoffValue.toFixed(4))
             listControlModel.setProperty(7, "Value", RecipeLabData.CollapseDistanceCutoffValue.toFixed(4))
         }

     }
    function updateSwitchEnabled(qmlText,checked){

        if(qmlText === qmlTextFrequencyLowCutOff){
            RecipeLabData.FreqLowCuttoffEnable = checked
        }
        else if(qmlText === qmlTextPeakPowerCutOff){
            RecipeLabData.PeakPowerCuttOffEnabled = checked
        }
        else if(qmlText === qmlTextFrequencyHigh){
            RecipeLabData.FreqHighCuttoffEnable = checked
        }
        else if(qmlText === qmlTextEnergyCutOff){
            RecipeLabData.EnergyCuttoffEnable = checked
        }
        else if(qmlText === qmlTextGroundDetectCutOff){
            RecipeLabData.GroundDetectCuttoffEnable = checked
        }
        else if(qmlText === qmlTextTimeCutOff){
            RecipeLabData.TimeCuttoffEnable = checked
        }
        else if(qmlText === qmlTextCollapseDistanceCutOff){
            RecipeLabData.CollapseDistanceCutoffEnable = checked
        }
        else if(qmlText === qmlTextAbsoluteDistanceCutOff){
            RecipeLabData.ABSDistanceCutoffEnable = checked
        }

    }


    ListModel
    {
        id: listControlModel
        function resetControlModel()
        {
            listControlModel.clear()

            listControlModel.append({"Title":      qmlTextFrequencyLowCutOff,
                                          "Value":      "",
                                          "Unit":      mainWindow.qmltextFrequencyUnit,
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramFrequencyLowCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramFrequencyLowCuttoffValue),
                                          "Decimals":   0,
                                          "Check":      RecipeLabData.FreqLowCuttoffEnable,
                                          "Index":      0})
            listControlModel.append({"Title":      qmlTextPeakPowerCutOff,
                                          "Value":      "",
                                          "Unit":       mainWindow.qmltextPowerUnit,
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramPeakPowerCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramPeakPowerCuttoffValue),
                                          "Decimals":   0,
                                          "Check":      RecipeLabData.PeakPowerCuttOffEnabled,
                                          "Index":      1})
            listControlModel.append({"Title":      qmlTextFrequencyHigh,
                                          "Value":      "",
                                          "Unit":       mainWindow.qmltextFrequencyUnit,
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramFrequencyHighCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramFrequencyHighCuttoffValue),
                                          "Decimals":   0,
                                          "Check":      RecipeLabData.FreqHighCuttoffEnable,
                                          "Index":      2})
            listControlModel.append({"Title":      qmlTextEnergyCutOff,
                                          "Unit":       mainWindow.qmltextEnergyUnit,
                                          "Value":      "",
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramEnergyCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramEnergyCuttoffValue),
                                          "Decimals":   1,
                                          "Check":      RecipeLabData.EnergyCuttoffEnable,
                                          "Index":      4})
            listControlModel.append({"Title":      qmlTextGroundDetectCutOff,
                                          "Value":      "",
                                          "Unit":       mainWindow.qmltextTimeUnit,
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramGroundDetectCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramGroundDetectCuttoffValue),
                                          "Decimals":   3,
                                          "Check":      RecipeLabData.GroundDetectCuttoffEnable,
                                          "Index":      6})
            listControlModel.append({"Title":           qmlTextTimeCutOff,
                                          "Value":      "",
                                          "Unit":        mainWindow.qmltextTimeUnit,
                                          "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramTimeCuttoffValue),
                                          "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramTimeCuttoffValue),
                                          "Decimals":   3,
                                          "Check":      RecipeLabData.TimeCuttoffEnable,
                                          "Index":      7})


            if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)
            {
                if (mainWindow.qmltextDistanceUnit === "mm")
                {
                    listControlModel.append({"Title":      qmlTextAbsoluteDistanceCutOff,
                                                "Value":      RecipeLabData.ABSDistanceCutoffValue.toFixed(2),
                                                "Unit":       mainWindow.qmltextDistanceUnit,
                                                "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramABSDistanceCuttoffValue),
                                                "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramABSDistanceCuttoffValue),
                                                "Decimals":   2,
                                                "Check":      RecipeLabData.ABSDistanceCutoffEnable,
                                                "Index":      3})
                    listControlModel.append({"Title":      qmlTextCollapseDistanceCutOff,
                                                "Value":      RecipeLabData.CollapseDistanceCutoffValue.toFixed(2),
                                                "Unit":       mainWindow.qmltextDistanceUnit,
                                                "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramCollapseDistanceCuttoffValue),
                                                "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramCollapseDistanceCuttoffValue),
                                                "Decimals":   2,
                                                "Check":      RecipeLabData.CollapseDistanceCutoffEnable,
                                                "Index":      5})
                }

                else
                {
                    listControlModel.append({"Title":      qmlTextAbsoluteDistanceCutOff,
                                                "Value":      RecipeLabData.ABSDistanceCutoffValue.toFixed(4),
                                                "Unit":       mainWindow.qmltextDistanceUnit,
                                                "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramABSDistanceCuttoffValue),
                                                "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramABSDistanceCuttoffValue),
                                                "Decimals":   4,
                                                "Check":      RecipeLabData.ABSDistanceCutoffEnable,
                                                "Index":      3})
                    listControlModel.append({"Title":      qmlTextCollapseDistanceCutOff,
                                                "Value":      RecipeLabData.CollapseDistanceCutoffValue.toFixed(4),
                                                "Unit":       mainWindow.qmltextDistanceUnit,
                                                "Minimum":    RecipeLabData.getMinCuttOffLimitParametersValue(paramEnum.paramCollapseDistanceCuttoffValue),
                                                "Maximum":    RecipeLabData.getMaxCuttOffLimitParametersValue(paramEnum.paramCollapseDistanceCuttoffValue),
                                                "Decimals":   4,
                                                "Check":      RecipeLabData.CollapseDistanceCutoffEnable,
                                                "Index":      5})
                }
            }
        }
    }

    BransonLeftBorderRectangle
    {
        id: switchControlRec
        width: Math.round(parent.width - 11 * Style.scaleHint)
        height: Math.round(parent.height / 3.5 - 8 * Style.scaleHint)
        property bool isTurnAllOn: RecipeLabData.CutoffLimtsEnable
        checked:  RecipeLabData.CutoffLimtsEnable

        Text
        {
            id: txtControlTitle
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(7 * Style.scaleHint)
            text: qmlTextControl
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }

        Text
        {
            id: txtTurnSettingOnTitle
            anchors.right: parent.right
            anchors.rightMargin: Math.round(13 * Style.scaleHint)
            anchors.verticalCenter: txtControlTitle.verticalCenter
            text: qmlTextTurnSettingOn
            color: Style.blackFontColor
            font.family: Style.italic.name
            font.italic: true
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        }

        BransonSwitch
        {
            id: controlSwitch
            anchors.right: parent.right
            anchors.rightMargin: Math.round(25 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(13 * Style.scaleHint)
            maxWidth: rectHeight*1.5
            maxHeight: rectHeight*1.5
            rectWidth: parent.width* 0.08
            rectHeight: parent.height* 0.2
            checked:  RecipeLabData.CutoffLimtsEnable
            onCheckedChanged:
            {
                if(controlSwitch.checked)
                {
                    RecipeLabData.CutoffLimtsEnable =true
                    switchControlRec.isTurnAllOn = true
                    txtTurnSettingOnTitle.text = qmlTextTurnSettingOff
                }

                else
                {
                    RecipeLabData.CutoffLimtsEnable =false
                    switchControlRec.isTurnAllOn = false
                    txtTurnSettingOnTitle.text = qmlTextTurnSettingOn
                }
            }
        }
    }


    BransonGridView
    {
        id: recipeControlGridView
        anchors.top: switchControlRec.bottom
        anchors.topMargin: Math.round(8 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        gridViewCellHeight: Math.round(parent.height / 3.5)
        gridViewCellWidth: Math.round(parent.width / 2) - 1
        gridViewModel: listControlModel
        gridViewDelegate: BransonLeftBorderRectangle
        {
            id: optionControl
            width: switchControlRec.width * 0.50
            height: Math.round(recipeControlGridView.gridViewCellHeight - Math.round(8 * Style.scaleHint))
            checked: RecipeLabData.CutoffLimtsEnable
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                enabled: model.Check && RecipeLabData.CutoffLimtsEnable
                onClicked:
                {
                        mainWindow.showPrimaryNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                }
            }

            Text
            {
                id: txtTitle
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: Math.round(7 * Style.scaleHint)
                anchors.bottom: parent.bottom
                text: model.Title
                lineHeight: Math.round(1 * Style.scaleHint)
                wrapMode: Text.WordWrap
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: parent.height * 0.20
            }

            BransonSwitch
            {
                id: switchControl
                anchors.right:  parent.right
                anchors.rightMargin:  Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(13 * Style.scaleHint)

                maxWidth: rectHeight*1.5
                maxHeight: rectHeight*1.5
                rectWidth: parent.width* 0.15
                rectHeight: parent.height* 0.2
                enabled: RecipeLabData.CutoffLimtsEnable
                checked: model.Check
                onCheckedChanged: {
                       updateSwitchEnabled(model.Title,checked)
                }
            }

            Text
            {
                id: txtControlValue
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.1
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.55
                font.bold: true
                text: model.Value + model.Unit
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                visible: switchControl.checked

            }
        }
    }
}

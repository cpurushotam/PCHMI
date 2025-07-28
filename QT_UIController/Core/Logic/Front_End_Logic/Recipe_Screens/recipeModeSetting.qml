/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the weld mode configurable screen.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/08/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
Item {
    property string qmltextTime:            qsTr("TIME")
    property string qmltextEnergy:          qsTr("ENERGY")
    property string qmltextPeakPower:       qsTr("PEAK POWER")
    property string qmltextGroundDetect:    qsTr("GROUND DETECT")
    property string qmltextAbsoluteDistance:qsTr("ABSOLUTE DISTANCE")
    property string qmltextCollapseDistance:qsTr("COLLAPSE DISTANCE")
    property string qmltextResetToDefault:    "RESET TO DEFAULT"

    property var qmlTextArray: [qmltextTime, qmltextEnergy, qmltextPeakPower, qmltextGroundDetect,
        qmltextAbsoluteDistance, qmltextCollapseDistance,qmltextResetToDefault]

    property int imageSize: Math.round(30 * Style.scaleHint)
    property color activatedBackgroundColor: Style.titleBackgroundColor
    property color normalBackgroundColor: Style.recipeModeFrameColor

    signal signalCurrentWeldModeIdxChanged(int index)
    signal recipeLabDataChanged()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_WELDMODE, qmlTextArray)
        qmltextTime = qmlTextArray[textEnum.textTimeIdx]
        qmltextEnergy = qmlTextArray[textEnum.textEnergyIdx]
        qmltextPeakPower = qmlTextArray[textEnum.textPeakPowerIdx]
        qmltextGroundDetect = qmlTextArray[textEnum.textGroudDetectIdx]
        qmltextAbsoluteDistance = qmlTextArray[textEnum.textAbsoluteDistanceIdx]
        qmltextCollapseDistance = qmlTextArray[textEnum.textCollapseDistanceIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefault]
        recipeModeModel.setProperty(textEnum.textTimeIdx, "modeName", qmltextTime)
        recipeModeModel.setProperty(textEnum.textEnergyIdx, "modeName", qmltextEnergy)
        recipeModeModel.setProperty(textEnum.textPeakPowerIdx, "modeName", qmltextPeakPower)
        recipeModeModel.setProperty(textEnum.textGroudDetectIdx, "modeName", qmltextGroundDetect)
        recipeModeModel.setProperty(textEnum.textAbsoluteDistanceIdx, "modeName", qmltextAbsoluteDistance)
        recipeModeModel.setProperty(textEnum.textCollapseDistanceIdx, "modeName", qmltextCollapseDistance)
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        recipeModeModel.resetModel()
        updateLanguage()
    }

    Connections
    {
        target: RecipeLabData
        function onRecipeLabDataChanged()
        {
           recipeModeModel.resetModel()
        }
    }

    QtObject {
        id: textEnum
        readonly property int textTimeIdx:              0
        readonly property int textEnergyIdx:            1
        readonly property int textPeakPowerIdx:         2
        readonly property int textGroudDetectIdx:       3
        readonly property int textAbsoluteDistanceIdx:  4
        readonly property int textCollapseDistanceIdx:  5
        readonly property int textResetToDefault:       6

    }

    ListModel {
        id: recipeModeModel
        function resetModel()
        {
            recipeModeModel.clear()

            recipeModeModel.append({"modeName": qmltextTime,
                                   "modeIndex": RecipeEnum.TIME_IDX,
                                   "checked": (RecipeLabData.WeldMode === RecipeEnum.TIME_IDX)})
            recipeModeModel.append({"modeName": qmltextEnergy,
                                   "modeIndex": RecipeEnum.ENERGY_IDX,
                                   "checked": (RecipeLabData.WeldMode === RecipeEnum.ENERGY_IDX)})
            recipeModeModel.append({"modeName": qmltextPeakPower,
                                   "modeIndex": RecipeEnum.PEAKPOWER_IDX,
                                   "checked": (RecipeLabData.WeldMode === RecipeEnum.PEAKPOWER_IDX)})
            recipeModeModel.append({"modeName": qmltextGroundDetect,
                                   "modeIndex": RecipeEnum.GROUND_IDX,
                                   "checked": (RecipeLabData.WeldMode === RecipeEnum.GROUND_IDX)})

            if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)
            {
                recipeModeModel.append({"modeName": qmltextAbsoluteDistance,
                                       "modeIndex": RecipeEnum.ABSDISTANCE_IDX,
                                       "checked": (RecipeLabData.WeldMode === RecipeEnum.ABSDISTANCE_IDX)})
                recipeModeModel.append({"modeName": qmltextCollapseDistance,
                                       "modeIndex": RecipeEnum.COLDISTANCE_IDX,
                                       "checked": (RecipeLabData.WeldMode === RecipeEnum.COLDISTANCE_IDX)})
            }
        }
    }

    BransonGridView
    {
        id: reciepModelGridView
        anchors.fill: parent
        gridViewModel: recipeModeModel
        gridViewDelegate: recipeModeDelegate
        gridViewCellHeight: Math.round(parent.height / 3.5)
        gridViewCellWidth: Math.round(parent.width / 2) - 1
        ButtonGroup
        {
            id: checkGroup
        }
    }

    Component
    {
        id: recipeModeDelegate
        BransonLeftBorderRectangle
        {
            id: btnRecipeMode
            width: Math.round(reciepModelGridView.gridViewCellWidth - Math.round(11 * Style.scaleHint))
            height: Math.round(reciepModelGridView.gridViewCellHeight - Math.round(8 * Style.scaleHint))
            Text
            {
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(7 * Style.scaleHint)
                text: model.modeName
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            RadioButton
            {
                id: radioBtnRecipeMode
                visible: false
                ButtonGroup.group: checkGroup
                checked: model.checked
                onCheckedChanged:
                {
                    if(radioBtnRecipeMode.checked)

                        btnRecipeMode.checked = true
                    else
                        btnRecipeMode.checked = false
                }
            }

            Image
            {
                id: recipeIcon
                visible: true
                anchors.right: parent.right
                anchors.rightMargin: 10 * Style.scaleHint
                anchors.verticalCenter: parent.verticalCenter
                source:
                {
                    switch(model.modeIndex)
                    {
                    case RecipeEnum.TIME_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/Time_icon_Blue.png"
                        }

                        else
                        {
                            return "qrc:/Images/Time_icon_Grey.png"
                        }

                    case RecipeEnum.ENERGY_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/Energy_Icon_Blue.png"
                        }

                        else
                        {
                            return "qrc:/Images/Energy_Icon_Grey.png"
                        }

                    case RecipeEnum.PEAKPOWER_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/PeakPower_Icon_Blue.png"
                        }

                        else
                        {
                            return "qrc:/Images/PeakPower_Icon_Grey.png"
                        }

                    case RecipeEnum.GROUND_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/Groun Detect_Icon_Blue.png"
                        }

                        else
                        {
                            return "qrc:/Images/Groun Detect_Icon_Grey.png"
                        }
                    case RecipeEnum.ABSDISTANCE_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/Blue_Absolute_Distance_icon.svg"
                        }

                        else
                        {
                            return "qrc:/Images/Absolute_Distance_icon.svg"
                        }
                    case RecipeEnum.COLDISTANCE_IDX :

                        if(model.checked)
                        {
                            return "qrc:/Images/Blue_Collapse_Distance_icon.svg"
                        }

                        else
                        {
                            return "qrc:/Images/Collapse_Distance_icon.svg"
                        }

                    default :

                        if(model.checked)
                        {
                            return "qrc:/Images/Time_icon_Blue.png"
                        }

                        else
                        {
                            return "qrc:/Images/Time_icon_Grey.png"
                        }
                    }
                }

                height: imageSize
                width: imageSize
                fillMode: Image.PreserveAspectFit
                sourceSize.width: recipeIcon.width
                sourceSize.height: recipeIcon.height
                smooth: true
            }

            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    radioBtnRecipeMode.checked = true
                    signalCurrentWeldModeIdxChanged(model.modeIndex)
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
          buttonColor: Style.disabledButtonBackgroundColor
          font.family: Style.regular.name
          onClicked:
          {
              RecipeLabData.resetToDefault(true)
          }
      }
}

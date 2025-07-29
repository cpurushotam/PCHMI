/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn seek recipe screen.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/

import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"

Item
{
    property string qmltextSeekFreqLimitHigh           : "SEEK FREQUENCY LIMIT HIGH"
    property string qmltextSeekFreqLimitLow            : "SEEK FREQUENCY LIMIT LOW"
    property string qmltextSeekFreqOffset              : "SEEK FREQUENCY OFFSET"
    property string qmltextSeekMemClearBeforeSeek      : "MEMORY CLEAR BEFORE SEEK"
    property string qmltextSeekTime                    : "SEEK TIME"
    property string qmltextSeekAmplitudeRampTime       : "SEEK AMPLITUDE RAMP TIME"
    property string qmltextSeekAmplitude               : "SEEK AMPLITUDE"
    property string qmltextSeekAmpProportionalGain     : "SEEK AMPLITUDE PROPOTIONAL GAIN"
    property string qmltextSeekAmpIntegralGain         : "SEEK AMPLITUDE INTEGRAL GAIN"
    property string qmltextSeekAmpDerivativeGain       : "SEEK AMPLITUDE DERIVATIVE GAIN"
    property string qmltextSeekPhaseProportionalGain   : "SEEK PHASE PROPOTIONAL GAIN"
    property string qmltextSeekPhaseIntegralGain       : "SEEK PHASE INTEGRAL GAIN"
    property string qmltextSeekPhaseDerivativeGain     : "SEEK PHASE DERIVATIVE GAIN"
    property string qmltextSeekBlindTimeSeek           : "SEEK BLIND TIME SEEK"
    property string qmltextSeekPhaseLoopCF             : "SEEK PHASE LOOP CF"

    property string qmltextResetToDefault        : "RESET TO DEFAULT"
    property string qmltextCancel                : "CANCEL"
    property string qmltextSave                  : "SAVE"
    property bool   isBranSonServiceKeyEntered   : false
    property int imageSize: Math.round(20 * Style.scaleHint)

    signal seekDataChanged()
    signal areSeekRecipeValuesEqual()

    property var qmlTextArray: [qmltextSeekFreqLimitHigh, qmltextSeekFreqLimitLow, qmltextSeekFreqOffset, qmltextSeekMemClearBeforeSeek, qmltextSeekTime,
        qmltextSeekAmplitudeRampTime, qmltextSeekAmplitude, qmltextSeekAmpProportionalGain, qmltextSeekAmpIntegralGain, qmltextSeekAmpDerivativeGain,
        qmltextSeekPhaseProportionalGain, qmltextSeekPhaseIntegralGain, qmltextSeekPhaseDerivativeGain, qmltextSeekBlindTimeSeek, qmltextSeekPhaseLoopCF,
        qmltextResetToDefault, qmltextCancel, qmltextSave]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SEEK_RECIPE, qmlTextArray)
        qmltextSeekFreqLimitHigh = qmlTextArray[textEnum.textSeekFreqLimitHighIdx]
        qmltextSeekFreqLimitLow = qmlTextArray[textEnum.textSeekFreqLimitLowIdx]
        qmltextSeekFreqOffset = qmlTextArray[textEnum.textSeekFreqOffsetIdx]
        qmltextSeekMemClearBeforeSeek = qmlTextArray[textEnum.textSeekMemClearBeforeSeekIdx]
        qmltextSeekTime = qmlTextArray[textEnum.textSeekTimeIdx]
        qmltextSeekAmplitudeRampTime = qmlTextArray[textEnum.textSeekAmplitudeRampIdx]
        qmltextSeekAmplitude = qmlTextArray[textEnum.textSeekAmplitudeIdx]
        qmltextSeekAmpProportionalGain = qmlTextArray[textEnum.textSeekAmpProportionalGainIdx]
        qmltextSeekAmpIntegralGain = qmlTextArray[textEnum.textSeekAmpIntegralGainIdx]
        qmltextSeekAmpDerivativeGain = qmlTextArray[textEnum.textSeekAmpDerivativeGainIdx]
        qmltextSeekPhaseProportionalGain = qmlTextArray[textEnum.textSeekPhaseProportionalGainIdx]
        qmltextSeekPhaseIntegralGain = qmlTextArray[textEnum.textSeekPhaseIntegralGainIdx]
        qmltextSeekPhaseDerivativeGain = qmlTextArray[textEnum.textSeekPhaseDerivativeGainIdx]
        qmltextSeekBlindTimeSeek = qmlTextArray[textEnum.textSeekBlindTimeSeek]
        qmltextSeekPhaseLoopCF = qmlTextArray[textEnum.textSeekPhaseLoopCFIdx]

        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        seekRecipeModeModel.setProperty(textEnum.textSeekFreqLimitHighIdx, "seekName", qmltextSeekFreqLimitHigh)
        seekRecipeModeModel.setProperty(textEnum.textSeekFreqLimitLowIdx, "seekName", qmltextSeekFreqLimitLow)
        seekRecipeModeModel.setProperty(textEnum.textSeekFreqOffsetIdx, "seekName", qmltextSeekFreqOffset)
        seekRecipeModeModel.setProperty(textEnum.textSeekMemClearBeforeSeekIdx, "seekName", qmltextSeekMemClearBeforeSeek)
        seekRecipeModeModel.setProperty(textEnum.textSeekTimeIdx, "seekName", qmltextSeekTime)
        seekRecipeModeModel.setProperty(textEnum.textSeekAmplitudeRampIdx, "seekName", qmltextSeekAmplitudeRampTime)
        seekRecipeModeModel.setProperty(textEnum.textSeekAmplitudeIdx, "seekName", qmltextSeekAmplitude)

        if(isBranSonServiceKeyEntered)
        {
            seekRecipeModeModel.setProperty(textEnum.textSeekAmpProportionalGainIdx, "seekName", qmltextSeekAmpProportionalGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekAmpIntegralGainIdx, "seekName", qmltextSeekAmpIntegralGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekAmpDerivativeGainIdx, "seekName", qmltextSeekAmpDerivativeGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekPhaseProportionalGainIdx, "seekName", qmltextSeekPhaseProportionalGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekPhaseIntegralGainIdx, "seekName", qmltextSeekPhaseIntegralGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekPhaseDerivativeGainIdx, "seekName", qmltextSeekPhaseDerivativeGain)
            seekRecipeModeModel.setProperty(textEnum.textSeekBlindTimeSeek, "seekName", qmltextSeekBlindTimeSeek)
            seekRecipeModeModel.setProperty(textEnum.textSeekPhaseLoopCFIdx, "seekName", qmltextSeekPhaseLoopCF)
        }
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        target: SeekData

        function onSeekDataChanged()
        {
            seekRecipeModeModel.resetModel()
            seekRecipeModeModel.setProperty(textEnum.textSeekTimeIdx, "seekValue", SeekData.SeekTime.toFixed(3))
            seekRecipeModeModel.setProperty(textEnum.textSeekAmplitudeRampIdx, "seekValue", SeekData.SeekAmplitudeRampTime.toFixed(3))
            loadingPage.visible = false
        }

        function onAreSeekRecipeValuesEqual(value)
        {
            if(value)
            {
                loadingPage.visible = false
            }

            else
            {
                loadingPage.visible = true
            }
        }
    }

    Component.onCompleted:
    {
        SeekData.onSeekRecipeScreenReNavigated()
        updateLanguage()
        seekRecipeModeModel.resetModel()
    }

    QtObject
    {
        id: textEnum
        readonly property int textSeekFreqLimitHighIdx         : 0
        readonly property int textSeekFreqLimitLowIdx          : 1
        readonly property int textSeekFreqOffsetIdx            : 2
        readonly property int textSeekMemClearBeforeSeekIdx    : 3
        readonly property int textSeekTimeIdx                  : 4
        readonly property int textSeekAmplitudeRampIdx         : 5
        readonly property int textSeekAmplitudeIdx             : 6
        readonly property int textSeekAmpProportionalGainIdx   : 7
        readonly property int textSeekAmpIntegralGainIdx       : 8
        readonly property int textSeekAmpDerivativeGainIdx     : 9
        readonly property int textSeekPhaseProportionalGainIdx : 10
        readonly property int textSeekPhaseIntegralGainIdx     : 11
        readonly property int textSeekPhaseDerivativeGainIdx   : 12
        readonly property int textSeekBlindTimeSeek            : 13
        readonly property int textSeekPhaseLoopCFIdx           : 14

        readonly property int textResetToDefaultIdx            : 15
        readonly property int textCancelIdx                    : 16
        readonly property int textSaveIdx                      : 17
    }

    QtObject
    {
        id: paramEnum
        readonly property int paramSeekFreqLimitHigh            : 0
        readonly property int paramSeekFreqLimitLow             : 1
        readonly property int paramSeekFreqOffset               : 2
        readonly property int paramSeekMemClear                 : 3
        readonly property int paramSeekTime                     : 4
        readonly property int paramSeekAmplitudeRampTime        : 5
        readonly property int paramSeekAmplitude                : 6
        readonly property int paramSeekAmpProportionalGain      : 7
        readonly property int paramSeekAmpIntegralGain          : 8
        readonly property int paramSeekAmpDerivativeGain        : 9
        readonly property int paramSeekPhaseProportionalGain    : 10
        readonly property int paramSeekPhaseIntegralGain        : 11
        readonly property int paramSeekPhaseDerivativeGain      : 12
        readonly property int paramSeekBlindTimeSeek            : 13
        readonly property int paramSeekPhaseLoopCF              : 14
    }   
    ListModel
    {
        id: seekRecipeModeModel
        function resetModel()
        {
            seekRecipeModeModel.clear()

            seekRecipeModeModel.append({"seekName"        : qmltextSeekFreqLimitHigh,
                                           "seekUnit"     : mainWindow.qmltextFrequencyUnit,
                                           "seekDecimals" : 1,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekFreqLimitHigh),
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekFreqLimitHigh),
                                           "seekValue"    : SeekData.SeekFreqLimitHigh,
                                           "seekIndex"    : 0})
            seekRecipeModeModel.append({"seekName": qmltextSeekFreqLimitLow,
                                           "seekUnit":  mainWindow.qmltextFrequencyUnit,
                                           "seekDecimals" : 1,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekFreqLimitLow) ,
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekFreqLimitLow),
                                           "seekValue"    : SeekData.SeekFreqLimitLow,
                                           "seekIndex": 1})
            seekRecipeModeModel.append({"seekName": qmltextSeekFreqOffset,
                                           "seekUnit":  mainWindow.qmltextFrequencyUnit,
                                           "seekDecimals" : 1,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekFreqOffset) ,
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekFreqOffset),
                                           "seekValue"    : SeekData.SeekFreqOffset,
                                           "seekIndex": 2})
            seekRecipeModeModel.append({"seekName": qmltextSeekMemClearBeforeSeek,
                                           "seekUnit":  "NA",
                                           "seekDecimals" : 1,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekMemClear) ,
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekMemClear),
                                           "seekValue"    : SeekData.SeekMemClear,
                                           "seekIndex": 3})
            seekRecipeModeModel.append({"seekName": qmltextSeekTime,
                                           "seekUnit":  mainWindow.qmltextTimeUnit,
                                           "seekDecimals" : 3,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekTime),
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekTime),
                                           "seekValue"    : SeekData.SeekTime.toFixed(3),
                                           "seekIndex": 4})
            seekRecipeModeModel.append({"seekName": qmltextSeekAmplitudeRampTime,
                                           "seekUnit":  mainWindow.qmltextTimeUnit,
                                           "seekDecimals" : 3,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekAmplitudeRampTime) ,
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekAmplitudeRampTime),
                                           "seekValue"    : SeekData.SeekAmplitudeRampTime.toFixed(3),
                                           "seekIndex": 5})
            seekRecipeModeModel.append({"seekName": qmltextSeekAmplitude,
                                           "seekUnit":  mainWindow.qmltextAmplitudeUnit,
                                           "seekDecimals" : 1,
                                           "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekAmplitude) ,
                                           "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekAmplitude),
                                           "seekValue"    : SeekData.SeekAmplitude,
                                           "seekIndex": 6})

            /*TBD : Service screen enable/disable status read logic*/
            if(isBranSonServiceKeyEntered)
            {
                seekRecipeModeModel.append({"seekName": qmltextSeekAmpProportionalGain,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekAmpProportionalGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekAmpProportionalGain),
                                               "seekValue"    : SeekData.SeekAmpProportionalGain,
                                               "seekIndex": 7})
                seekRecipeModeModel.append({"seekName": qmltextSeekAmpIntegralGain,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekAmpIntegralGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekAmpIntegralGain),
                                               "seekValue"    : SeekData.SeekAmpIntegralGain,
                                               "seekIndex": 8})
                seekRecipeModeModel.append({"seekName": qmltextSeekAmpDerivativeGain,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 3,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekAmpDerivativeGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekAmpDerivativeGain),
                                               "seekValue"    : SeekData.SeekAmpDerivativeGain,
                                               "seekIndex": 9})
                seekRecipeModeModel.append({"seekName": qmltextSeekPhaseProportionalGain,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekPhaseProportionalGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekPhaseProportionalGain),
                                               "seekValue"    : SeekData.SeekPhaseProportionalGain,
                                               "seekIndex": 10})
                seekRecipeModeModel.append({"seekName": qmltextSeekPhaseIntegralGain,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 3,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekPhaseIntegralGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekPhaseIntegralGain),
                                               "seekValue"    : SeekData.SeekPhaseIntegralGain,
                                               "seekIndex": 11})
                seekRecipeModeModel.append({"seekName": qmltextSeekPhaseDerivativeGain,
                                               "seekUnit": "NA",
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekPhaseDerivativeGain) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekPhaseDerivativeGain),
                                               "seekValue"    : SeekData.SeekPhaseDerivativeGain,
                                               "seekIndex": 12})
                seekRecipeModeModel.append({"seekName": qmltextSeekBlindTimeSeek,
                                               "seekUnit":  mainWindow.qmltextTimeUnit,
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekBlindTimeSeek) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekBlindTimeSeek),
                                               "seekValue"    : SeekData.SeekBlindTimeSeek,
                                               "seekIndex": 13})
                seekRecipeModeModel.append({"seekName": qmltextSeekPhaseLoopCF,
                                               "seekUnit":  "NA",
                                               "seekDecimals" : 1,
                                               "seekMinimum"  : SeekData.getMinSeekParametersValue(paramEnum.paramSeekPhaseLoopCF) ,
                                               "seekMaximum"  : SeekData.getMaxSeekParametersValue(paramEnum.paramSeekPhaseLoopCF),
                                               "seekValue"    : SeekData.SeekPhaseloopCF,
                                               "seekIndex": 14})
            }
        }
    }

    Rectangle
    {
        id: gridviewRect
        width: parent.width
        height: parent.height * 0.9
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)

        BransonGridView
        {
            id: reciepModelGridView
            anchors.fill: parent
            gridViewModel: seekRecipeModeModel
            gridViewDelegate: recipeModeDelegate
            gridViewCellHeight: Math.round(parent.height / 5.5)
            gridViewCellWidth: Math.round(parent.width / 3) - 1
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
            checked: true

            Text
            {
                anchors.left: parent.left
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: model.seekName
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            }

            Text
            {
                visible: (model.seekName !== qmltextSeekMemClearBeforeSeek)
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(5 * Style.scaleHint)
                text: ((model.seekName === qmltextSeekTime) || (model.seekName === qmltextSeekAmplitudeRampTime)) ? model.seekValue.toFixed(3) + " " + model.seekUnit :
                                                                           model.seekValue + " " + model.seekUnit
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            BransonSwitch
            {
                id: switchControl
                visible: (model.seekName === qmltextSeekMemClearBeforeSeek)
                checked: SeekData.SeekMemClear
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(8 * Style.scaleHint)
                onCheckedChanged:
                {
                    SeekData.SeekMemClear = switchControl.checked
                }
            }

            MouseArea
            {
                anchors.fill: parent
                enabled: (model.seekName !== qmltextSeekMemClearBeforeSeek)
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    mainWindow.showPrimaryNumpad(model.seekName, model.seekUnit, model.seekDecimals, model.seekMinimum, model.seekMaximum, model.seekValue)
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: btnRestoreDefault
        implicitWidth: Math.round(175 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        text: qmltextResetToDefault
        buttonColor: Style.disabledButtonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            loadingPage.visible = true
            SeekData.onResetToDefaultPressed()
        }
    }

    BransonPrimaryButton
    {
        id: btnCancel
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(150 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        text: qmltextCancel
        buttonColor: Style.disabledButtonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SEEK)
            mainWindow.clearHeaderTitle(UIScreenEnum.DIAGNOSTICS_SEEK)
        }
    }

    BransonPrimaryButton
    {
        id: btnSave
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        text: qmltextSave
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            SeekData.onSavedPressed()
        }
    }

    Rectangle
    {
        id: loadingPage
        visible: false
        width: parent.width
        height:parent.height + Math.round(50 * Style.scaleHint)
        opacity: 0.5
        color: "#000000"

        Image
        {
            id: recipeLoadingIcon
            visible: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Loading.png"
            height: imageSize * 5
            width: imageSize * 5
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeLoadingIcon.width
            sourceSize.height: recipeLoadingIcon.height
            smooth: true
        }

        RotationAnimator
        {
            target: recipeLoadingIcon
            from: 0
            to: 360
            duration: 1000
            running: true
            loops: Animation.Infinite
        }

        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }
}

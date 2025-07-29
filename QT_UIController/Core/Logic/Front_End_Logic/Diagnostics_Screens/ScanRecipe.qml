/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn scan recipe screen.
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
    property string qmltextScanFrequencyStep               : "SCAN FREQUENCY STEP"
    property string qmltextScanMaxAmplitude                : "SCAN MAX AMPLITUDE"
    property string qmltextScanMaxCurrent                  : "SCAN MAX CURRENT"
    property string qmltextScanSetDigitalTuneWithHornScan  : "SET DIGITAL TUNE WITH HORN SCAN"
    property string qmltextScanStartFrequency              : "SCAN START FREQUENCY"
    property string qmltextScanStopFrequency               : "SCAN STOP FREQUENCY"
    property string qmltextScanTimeDelay                   : "SCAN TIME DELAY"

    property string qmltextResetToDefault        : "RESET TO DEFAULT"
    property string qmltextCancel                : "CANCEL"
    property string qmltextSave                  : "SAVE"
    property bool   isBranSonServiceKeyEntered   : false
    property int imageSize: Math.round(20 * Style.scaleHint)

    signal scanRecipeDataChanged()
    signal areScanRecipeValuesEqual()

    property var qmlTextArray: [qmltextScanFrequencyStep, qmltextScanMaxAmplitude, qmltextScanMaxCurrent, qmltextScanSetDigitalTuneWithHornScan,
        qmltextScanStartFrequency, qmltextScanStopFrequency, qmltextScanTimeDelay, qmltextResetToDefault, qmltextCancel, qmltextSave]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SCAN_RECIPE, qmlTextArray)
        qmltextScanFrequencyStep = qmlTextArray[textEnum.textScanFrequencyStepIdx]
        qmltextScanMaxAmplitude = qmlTextArray[textEnum.textScanMaxAmplitudeIdx]
        qmltextScanMaxCurrent = qmlTextArray[textEnum.textScanMaxCurrentIdx]
        qmltextScanSetDigitalTuneWithHornScan = qmlTextArray[textEnum.textScanSetDigitalTuneWithHornScanIdx]
        qmltextScanStartFrequency = qmlTextArray[textEnum.textScanStartFrequencyIdx]
        qmltextScanStopFrequency = qmlTextArray[textEnum.textScanStopFrequencyIdx]
        qmltextScanTimeDelay = qmlTextArray[textEnum.textScanTimeDelayIdx]

        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        scanRecipeModeModel.setProperty(textEnum.textScanFrequencyStepIdx, "scanName", qmltextScanFrequencyStep)
        scanRecipeModeModel.setProperty(textEnum.textScanMaxAmplitudeIdx, "scanName", qmltextScanMaxAmplitude)
        scanRecipeModeModel.setProperty(textEnum.textScanMaxCurrentIdx, "scanName", qmltextScanMaxCurrent)
        scanRecipeModeModel.setProperty(textEnum.textScanSetDigitalTuneWithHornScanIdx, "scanName", qmltextScanSetDigitalTuneWithHornScan)
        scanRecipeModeModel.setProperty(textEnum.textScanStartFrequencyIdx, "scanName", qmltextScanStartFrequency)
        scanRecipeModeModel.setProperty(textEnum.textScanStopFrequencyIdx, "scanName", qmltextScanStopFrequency)
        scanRecipeModeModel.setProperty(textEnum.textScanTimeDelayIdx, "scanName", qmltextScanTimeDelay)
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
        target: ScanCycleDetailsListModel
        function onScanRecipeDataChanged()
        {
            scanRecipeModeModel.resetModel()
            scanRecipeModeModel.setProperty(textEnum.textScanTimeDelayIdx, "scanValue", ScanCycleDetailsListModel.ScanTimeDelay.toFixed(3))
            loadingPage.visible = false
        }

        function onAreScanRecipeValuesEqual(value)
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
        ScanCycleDetailsListModel.onScanRecipeScreenReNavigated()
        scanRecipeModeModel.resetModel()
        updateLanguage()
    }

    QtObject
    {
        id: textEnum
        readonly property int textScanFrequencyStepIdx                 : 0
        readonly property int textScanMaxAmplitudeIdx                  : 1
        readonly property int textScanMaxCurrentIdx                    : 2
        readonly property int textScanSetDigitalTuneWithHornScanIdx    : 3
        readonly property int textScanStartFrequencyIdx                : 4
        readonly property int textScanStopFrequencyIdx                 : 5
        readonly property int textScanTimeDelayIdx                     : 6

        readonly property int textResetToDefaultIdx                    : 7
        readonly property int textCancelIdx                            : 8
        readonly property int textSaveIdx                              : 9
    }

    QtObject
    {
        id: paramEnum
        readonly property int paramScanFrequencyStep                   : 0
        readonly property int paramScanMaxAmplitude                    : 1
        readonly property int paramScanMaxCurrent                      : 2
        readonly property int paramScanStartFrequency                  : 3
        readonly property int paramScanStopFrequency                   : 4
        readonly property int paramScanTimeDelay                       : 5
    }
    ListModel
    {
        id: scanRecipeModeModel
        function resetModel()
        {
            scanRecipeModeModel.clear()

            scanRecipeModeModel.append({"scanName"        : qmltextScanFrequencyStep,
                                           "scanUnit"     : mainWindow.qmltextFrequencyUnit,
                                           "scanDecimals" : 0,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanFrequencyStep),
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanFrequencyStep),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanFreqStep,
                                           "scanIndex"    : 0})
            scanRecipeModeModel.append({"scanName": qmltextScanMaxAmplitude,
                                           "scanUnit": mainWindow.qmltextAmplitudeUnit,
                                           "scanDecimals" : 0,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanMaxAmplitude) ,
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanMaxAmplitude),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanMaxAmplitude,
                                           "scanIndex": 1})
            scanRecipeModeModel.append({"scanName": qmltextScanMaxCurrent,
                                           "scanUnit": mainWindow.qmltextCurrentUnit,
                                           "scanDecimals" : 0,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanMaxCurrent) ,
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanMaxCurrent),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanMaxCurrent,
                                           "scanIndex": 2})
            scanRecipeModeModel.append({"scanName": qmltextScanSetDigitalTuneWithHornScan,
                                           "scanUnit": "NA",
                                           "scanDecimals" : 1,
                                           "scanMinimum"  : "0",
                                           "scanMaximum"  : "0",
                                           "scanValue"    : 0,
                                           "scanIndex": 4})
            scanRecipeModeModel.append({"scanName": qmltextScanStartFrequency,
                                           "scanUnit": mainWindow.qmltextFrequencyUnit,
                                           "scanDecimals" : 0,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanStartFrequency) ,
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanStartFrequency),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanStartFrequency,
                                           "scanIndex": 5})
            scanRecipeModeModel.append({"scanName": qmltextScanStopFrequency,
                                           "scanUnit": mainWindow.qmltextFrequencyUnit,
                                           "scanDecimals" : 0,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanStopFrequency) ,
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanStopFrequency),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanStopFrequency,
                                           "scanIndex": 6})
            scanRecipeModeModel.append({"scanName": qmltextScanTimeDelay,
                                           "scanUnit": mainWindow.qmltextTimeUnit,
                                           "scanDecimals" : 3,
                                           "scanMinimum"  : ScanCycleDetailsListModel.getMinScanParametersValue(paramEnum.paramScanTimeDelay) ,
                                           "scanMaximum"  : ScanCycleDetailsListModel.getMaxScanParametersValue(paramEnum.paramScanTimeDelay),
                                           "scanValue"    : ScanCycleDetailsListModel.ScanTimeDelay.toFixed(3),
                                           "scanIndex": 7})
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
            gridViewModel: scanRecipeModeModel
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
                text: model.scanName
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }

            Text
            {
                visible: (model.scanName !== qmltextScanSetDigitalTuneWithHornScan)
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(5 * Style.scaleHint)
                text: (model.scanName === qmltextScanTimeDelay) ? model.scanValue.toFixed(3) + " " + model.scanUnit :
                                                                  model.scanValue + " " + model.scanUnit
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            BransonSwitch
            {
                id: switchControl
                visible: (model.scanName === qmltextScanSetDigitalTuneWithHornScan)
                checked: ScanCycleDetailsListModel.ScanSetDigitalTune
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(8 * Style.scaleHint)
                onCheckedChanged:
                {
                    ScanCycleDetailsListModel.ScanSetDigitalTune = switchControl.checked
                }
            }

            MouseArea
            {
                anchors.fill: parent
                enabled: (model.scanName !== qmltextScanSetDigitalTuneWithHornScan)
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    mainWindow.showPrimaryNumpad(model.scanName, model.scanUnit, model.scanDecimals, model.scanMinimum, model.scanMaximum, model.scanValue)
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
            ScanCycleDetailsListModel.onResetToDefaultPressed()
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
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SCAN)
            mainWindow.clearHeaderTitle(UIScreenEnum.DIAGNOSTICS_SCAN)
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
            ScanCycleDetailsListModel.onSavedPressed()
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

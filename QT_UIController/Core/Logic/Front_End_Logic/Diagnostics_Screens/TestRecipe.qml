/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn test recipe screen.
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
    property string qmltextTestFreqLimitHigh           : "TEST FREQUENCY HIGH"
    property string qmltextTestFreqLimitLow            : "TEST FREQUENCY LOW"
    property string qmltextTestFreqOffset              : "TEST FREQUENCY OFFSET"
    property string qmltextTestMemClearBeforeTest      : "CLEAR MEMORY BEFORE TEST"
    property string qmltextTestAmplitudeRampTime       : "TEST AMPLITUDE RAMP TIME"
    property string qmltextTestAmplitude               : "TEST AMPLITUDE"
    property string qmltextTestAmpProportionalGain     : "TEST AMPLITUDE PROPOTIONAL GAIN"
    property string qmltextTestAmpIntegralGain         : "TEST AMPLITUDE INTEGRAL GAIN"
    property string qmltextTestAmpDerivativeGain       : "TEST AMPLITUDE DERIVATIVE GAIN"
    property string qmltextTestPhaseProportionalGain   : "TEST PHASE PROPOTIONAL GAIN"
    property string qmltextTestPhaseIntegralGain       : "TEST PHASE INTEGRAL GAIN"
    property string qmltextTestPhaseDerivativeGain     : "TEST PHASE DERIVATIVE GAIN"
    property string qmltextTestPhaseLoopCF             : "TEST PHASE LOOP CF"

    property string qmltextResetToDefault        : "RESET TO DEFAULT"
    property string qmltextCancel                : "CANCEL"
    property string qmltextSave                  : "SAVE"
    property bool   isBranSonServiceKeyEntered   : false
    property int imageSize: Math.round(20 * Style.scaleHint)

    signal testDataChanged()
    signal areTestRecipeValuesEqual()

    property var qmlTextArray: [qmltextTestFreqLimitHigh, qmltextTestFreqLimitLow, qmltextTestFreqOffset, qmltextTestMemClearBeforeTest,
        qmltextTestAmplitudeRampTime, qmltextTestAmplitude, qmltextTestAmpProportionalGain, qmltextTestAmpIntegralGain, qmltextTestAmpDerivativeGain,
        qmltextTestPhaseProportionalGain, qmltextTestPhaseIntegralGain, qmltextTestPhaseDerivativeGain, qmltextTestPhaseLoopCF,
        qmltextResetToDefault, qmltextCancel, qmltextSave]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_TEST_RECIPE, qmlTextArray)
        qmltextTestFreqLimitHigh = qmlTextArray[textEnum.textTestFreqLimitHighIdx]
        qmltextTestFreqLimitLow = qmlTextArray[textEnum.textTestFreqLimitLowIdx]
        qmltextTestFreqOffset = qmlTextArray[textEnum.textTestFreqOffsetIdx]
        qmltextTestMemClearBeforeTest = qmlTextArray[textEnum.textTestMemClearBeforeTestIdx]
        qmltextTestAmplitudeRampTime = qmlTextArray[textEnum.textTestAmplitudeRampIdx]
        qmltextTestAmplitude = qmlTextArray[textEnum.textTestAmplitudeIdx]
        qmltextTestAmpProportionalGain = qmlTextArray[textEnum.textTestAmpProportionalGainIdx]
        qmltextTestAmpIntegralGain = qmlTextArray[textEnum.textTestAmpIntegralGainIdx]
        qmltextTestAmpDerivativeGain = qmlTextArray[textEnum.textTestAmpDerivativeGainIdx]
        qmltextTestPhaseProportionalGain = qmlTextArray[textEnum.textTestPhaseProportionalGainIdx]
        qmltextTestPhaseIntegralGain = qmlTextArray[textEnum.textTestPhaseIntegralGainIdx]
        qmltextTestPhaseDerivativeGain = qmlTextArray[textEnum.textTestPhaseDerivativeGainIdx]
        qmltextTestPhaseLoopCF = qmlTextArray[textEnum.textTestPhaseLoopCFIdx]

        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        testRecipeModeModel.setProperty(textEnum.textTestFreqLimitHighIdx, "testName", qmltextTestFreqLimitHigh)
        testRecipeModeModel.setProperty(textEnum.textTestFreqLimitLowIdx, "testName", qmltextTestFreqLimitLow)
        testRecipeModeModel.setProperty(textEnum.texttextTestFreqOffsetIdx, "testName", qmltextTestFreqOffset)
        testRecipeModeModel.setProperty(textEnum.textTestMemClearBeforeTestIdx, "testName", qmltextTestMemClearBeforeTest)
        testRecipeModeModel.setProperty(textEnum.textTestAmplitudeRampIdx, "testName", qmltextTestAmplitudeRampTime)
        testRecipeModeModel.setProperty(textEnum.textTestAmplitudeIdx, "testName", qmltextTestAmplitude)
        testRecipeModeModel.setProperty(textEnum.textTestAmpProportionalGainIdx, "testName", qmltextTestAmpProportionalGain)
        testRecipeModeModel.setProperty(textEnum.textTestAmpIntegralGainIdx, "testName", qmltextTestAmpIntegralGain)
        testRecipeModeModel.setProperty(textEnum.textTestAmpDerivativeGainIdx, "testName", qmltextTestAmpDerivativeGain)
        testRecipeModeModel.setProperty(textEnum.textTestPhaseProportionalGainIdx, "testName", qmltextTestPhaseProportionalGain)
        testRecipeModeModel.setProperty(textEnum.textTestPhaseIntegralGainIdx, "testName", qmltextTestPhaseIntegralGain)
        testRecipeModeModel.setProperty(textEnum.textTestPhaseDerivativeGainIdx, "testName", qmltextTestPhaseDerivativeGain)
        testRecipeModeModel.setProperty(textEnum.textTestPhaseLoopCFIdx, "testName", qmltextTestPhaseLoopCF)
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
        target: TestData

        function onTestDataChanged()
        {
            testRecipeModeModel.resetModel()
            testRecipeModeModel.setProperty(textEnum.textTestAmplitudeRampIdx, "testValue", TestData.TestAmplitudeRampTime.toFixed(3))
            loadingPage.visible = false
        }

        function onAreTestRecipeValuesEqual(value)
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
        TestData.onTestRecipeScreenReNavigated()
        updateLanguage()
        testRecipeModeModel.resetModel()
    }

    QtObject
    {
        id: textEnum
        readonly property int textTestFreqLimitHighIdx         : 0
        readonly property int textTestFreqLimitLowIdx          : 1
        readonly property int textTestFreqOffsetIdx            : 2
        readonly property int textTestMemClearBeforeTestIdx    : 3
        readonly property int textTestAmplitudeRampIdx         : 4
        readonly property int textTestAmplitudeIdx             : 5
        readonly property int textTestAmpProportionalGainIdx   : 6
        readonly property int textTestAmpIntegralGainIdx       : 7
        readonly property int textTestAmpDerivativeGainIdx     : 8
        readonly property int textTestPhaseProportionalGainIdx : 9
        readonly property int textTestPhaseIntegralGainIdx     : 10
        readonly property int textTestPhaseDerivativeGainIdx   : 11
        readonly property int textTestPhaseLoopCFIdx           : 12

        readonly property int textResetToDefaultIdx            : 13
        readonly property int textCancelIdx                    : 14
        readonly property int textSaveIdx                      : 15
    }

    QtObject
    {
        id: paramEnum
        readonly property int paramTestFreqLimitHigh            : 0
        readonly property int paramTestFreqLimitLow             : 1
        readonly property int paramTestFreqOffset               : 2
        readonly property int paramTestMemClear                 : 3
        readonly property int paramTestAmplitudeRampTime        : 4
        readonly property int paramTestAmplitude                : 5
        readonly property int paramTestAmpProportionalGain      : 6
        readonly property int paramTestAmpIntegralGain          : 7
        readonly property int paramTestAmpDerivativeGain        : 8
        readonly property int paramTestPhaseProportionalGain    : 9
        readonly property int paramTestPhaseIntegralGain        : 10
        readonly property int paramTestPhaseDerivativeGain      : 11
        readonly property int paramTestPhaseLoopCF              : 12
    }
    ListModel
    {
        id: testRecipeModeModel
        function resetModel()
        {
            testRecipeModeModel.clear()

            testRecipeModeModel.append({"testName"        : qmltextTestFreqLimitHigh,
                                           "testUnit"     : mainWindow.qmltextFrequencyUnit,
                                           "testDecimals" : 1,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestFreqLimitHigh),
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestFreqLimitHigh),
                                           "testValue"    : TestData.TestFreqLimitHigh,
                                           "testIndex"    : 0})
            testRecipeModeModel.append({"testName": qmltextTestFreqLimitLow,
                                           "testUnit":  mainWindow.qmltextFrequencyUnit,
                                           "testDecimals" : 1,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestFreqLimitLow) ,
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestFreqLimitLow),
                                           "testValue"    : TestData.TestFreqLimitLow,
                                           "testIndex": 1})
            testRecipeModeModel.append({"testName": qmltextTestFreqOffset,
                                           "testUnit": mainWindow.qmltextFrequencyUnit,
                                           "testDecimals" : 1,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestFreqOffset) ,
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestFreqOffset),
                                           "testValue"    : TestData.TestFreqOffset,
                                           "testIndex": 2})
            testRecipeModeModel.append({"testName": qmltextTestMemClearBeforeTest,
                                           "testUnit": "NA",
                                           "testDecimals" : 1,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestMemClear) ,
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestMemClear),
                                           "testValue"    : TestData.TestMemClear,
                                           "testIndex": 3})
            testRecipeModeModel.append({"testName": qmltextTestAmplitudeRampTime,
                                           "testUnit": mainWindow.qmltextTimeUnit,
                                           "testDecimals" : 3,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestAmplitudeRampTime) ,
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestAmplitudeRampTime),
                                           "testValue"    : TestData.TestAmplitudeRampTime.toFixed(3),
                                           "testIndex": 4})
            testRecipeModeModel.append({"testName": qmltextTestAmplitude,
                                           "testUnit": mainWindow.qmltextAmplitudeUnit,
                                           "testDecimals" : 1,
                                           "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestAmplitude) ,
                                           "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestAmplitude),
                                           "testValue"    : TestData.TestAmplitude,
                                           "testIndex": 5})

            /*TBD : Service screen enable/disable status read logic*/
            if(isBranSonServiceKeyEntered)
            {
                testRecipeModeModel.append({"testName": qmltextTestAmpProportionalGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 1,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestAmpProportionalGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestAmpProportionalGain),
                                               "testValue"    : TestData.TestAmpProportionalGain,
                                               "testIndex": 6})
                testRecipeModeModel.append({"testName": qmltextTestAmpIntegralGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 1,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestAmpIntegralGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestAmpIntegralGain),
                                               "testValue"    : TestData.TestAmpIntegralGain,
                                               "testIndex": 7})
                testRecipeModeModel.append({"testName": qmltextTestAmpDerivativeGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 3,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestAmpDerivativeGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestAmpDerivativeGain),
                                               "testValue"    : TestData.TestAmpDerivativeGain,
                                               "testIndex": 8})
                testRecipeModeModel.append({"testName": qmltextTestPhaseProportionalGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 1,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestPhaseProportionalGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestPhaseProportionalGain),
                                               "testValue"    : TestData.TestPhaseProportionalGain,
                                               "testIndex": 9})
                testRecipeModeModel.append({"testName": qmltextTestPhaseIntegralGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 3,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestPhaseIntegralGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestPhaseIntegralGain),
                                               "testValue"    : TestData.TestPhaseIntegralGain,
                                               "testIndex": 10})
                testRecipeModeModel.append({"testName": qmltextTestPhaseDerivativeGain,
                                               "testUnit": "NA",
                                               "testDecimals" : 1,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestPhaseDerivativeGain) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestPhaseDerivativeGain),
                                               "testValue"    : TestData.TestPhaseDerivativeGain,
                                               "testIndex": 11})
                testRecipeModeModel.append({"testName": qmltextTestPhaseLoopCF,
                                               "testUnit": "NA",
                                               "testDecimals" : 1,
                                               "testMinimum"  : TestData.getMinTestParametersValue(paramEnum.paramTestPhaseLoopCF) ,
                                               "testMaximum"  : TestData.getMaxTestParametersValue(paramEnum.paramTestPhaseLoopCF),
                                               "testValue"    : TestData.TestPhaseloopCF,
                                               "testIndex": 12})
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
            gridViewModel: testRecipeModeModel
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
                text: model.testName
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            }

            Text
            {
                visible: (model.testName !== qmltextTestMemClearBeforeTest)
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(5 * Style.scaleHint)
                text: (model.testName === qmltextTestAmplitudeRampTime) ? model.testValue.toFixed(3) + " " + model.testUnit :
                                                                           model.testValue + " " + model.testUnit
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            BransonSwitch
            {
                id: switchControl
                visible: (model.testName === qmltextTestMemClearBeforeTest)
                checked: TestData.TestMemClear
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(8 * Style.scaleHint)
                onCheckedChanged:
                {
                    TestData.TestMemClear = switchControl.checked
                }
            }

            MouseArea
            {
                anchors.fill: parent
                enabled: (model.testName !== qmltextTestMemClearBeforeTest)
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    mainWindow.showPrimaryNumpad(model.testName, model.testUnit, model.testDecimals, model.testMinimum, model.testMaximum, model.testValue)
                    TestData.AmpUpdateFlagStatus = false
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
            TestData.AmpUpdateFlagStatus = false
            loadingPage.visible = true
            TestData.onResetToDefaultPressed()
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
            TestData.invokeUpdateFlag()
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_TEST)
            mainWindow.clearHeaderTitle(UIScreenEnum.DIAGNOSTICS_TEST)
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
            TestData.onSavedPressed()
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

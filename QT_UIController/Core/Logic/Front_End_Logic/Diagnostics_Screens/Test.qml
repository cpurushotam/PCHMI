/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn test result parameters.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/03/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import "./../Common_Logic"

Item
{
    property string qmltextMenuName         : "Test"
    property string qmltextUltrasonicsTest  : "Ultrasonics Test"
    property string qmltextStartTest        : "START TEST"
    property string qmltextStopTest         : "STOP TEST"
    property string qmltextTestRecipe       : "TEST RECIPE"
    property string qmltextStatusText       : "Status"
    property string qmltextFrequency        : "Frequency"
    property string qmltextStoredFrequency  : "Stored Freq."
    property string qmltextPower            : "Power"
    property string qmltextTestAmplitude    : "TEST AMPLITUDE"
    property string qmltextInstruction      : "Press and hold START TEST button to run test"

    property bool isStartTest : true

    property var qmlTextArray: [qmltextUltrasonicsTest, qmltextStartTest, qmltextStopTest, qmltextTestRecipe, qmltextStatusText,
        qmltextFrequency, qmltextStoredFrequency, qmltextPower]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_TEST, qmlTextArray)
        qmltextUltrasonicsTest = qmlTextArray[textEnum.textUltrasonicsTestIdx]
        qmltextStartTest = qmlTextArray[textEnum.textStartTestIdx]
        qmltextStopTest = qmlTextArray[textEnum.textStopTestIdx]
        qmltextTestRecipe = qmlTextArray[textEnum.textTestRecipeIdx]
        qmltextStatusText = qmlTextArray[textEnum.textStatusTextIdx]
        qmltextFrequency = qmlTextArray[textEnum.textFrequencyIdx]
        qmltextStoredFrequency = qmlTextArray[textEnum.textStoredFrequencyIdx]
        qmltextPower = qmlTextArray[textEnum.textPowerIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS_TEST, qmltextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textUltrasonicsTestIdx : 0
        readonly property int textStartTestIdx       : 1
        readonly property int textStopTestIdx        : 2
        readonly property int textTestRecipeIdx      : 3
        readonly property int textStatusTextIdx      : 4
        readonly property int textFrequencyIdx       : 5
        readonly property int textStoredFrequencyIdx : 6
        readonly property int textPowerIdx           : 7
        readonly property int textTestAmplitudeIdx   : 8
        readonly property int textInstructionIdx     : 9
    }

    Component.onCompleted:
    {
        /*To reinitiate test signature read request*/
        TestData.isScreenReNavigated(true)

        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTICS_TEST)
        updateLanguage()
        loader.source = "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/TestGraphWindow.qml"

        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS_TEST
    }
    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Text
    {
        id: ultrasonicsTestText
        text: qmltextUltrasonicsTest
        anchors.left: parent.left
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        font.family: Style.regular.name
        font.bold: true
        color: Style.blackFontColor
    }

    BransonPrimaryButton
    {
        id: startTest
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(150 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmltextStartTest
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onPressAndHold:
        {
            TestData.startTest()
        }

        onReleased:
        {
            TestData.abortTest()
        }
        /*onClicked:
        {
            if(isStartTest)
            {
                TestData.startTest()
                startTest.text = qmltextStopTest
                isStartTest = false
            }

            else
            {
                TestData.abortTest()
                startTest.text = qmltextStartTest
                isStartTest = true
            }
        }*/
    }

    BransonPrimaryButton
    {
        id: testRecipe
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmltextTestRecipe
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_TEST_RECIPE)
        }
    }

    Rectangle
    {
        id: testRect
        anchors.left: parent.left
        anchors.leftMargin:  Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(45 * Style.scaleHint)
        implicitWidth: Math.round(500 * Style.scaleHint)
        implicitHeight: Math.round(120 * Style.scaleHint)
        color: "#FFFFFF"
        border.color: "#707070"

        Text
        {
            id: frequencyText
            text: qmltextFrequency
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(25 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: "#000000"
        }

        Text
        {
            id: frequencyMinValue
            text: TestData.getTestFrequencyMin() + " " + mainWindow.qmltextFrequencyUnit
            anchors.right: frequencyControl.left
            anchors.rightMargin:  Math.round(10 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(25 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Slider
        {
            id: frequencyControl
            enabled: false
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(145 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(25 * Style.scaleHint)
            from: TestData.getTestFrequencyMin()
            value: TestData.TestFrequency
            to: TestData.getTestFrequencyMax()

            background: Rectangle
            {
                x: frequencyControl.leftPadding
                y: frequencyControl.topPadding + frequencyControl.availableHeight / 2 - height / 2
                implicitWidth: Math.round(275 * Style.scaleHint)
                implicitHeight: Math.round(5 * Style.scaleHint)
                width: frequencyControl.availableWidth
                height: implicitHeight
                color: "#FFFFFF"
                border.color: "#AEAEAE"
                radius: 10
            }

            handle: Rectangle
            {
                x: frequencyControl.leftPadding + frequencyControl.visualPosition * (frequencyControl.availableWidth - width)
                y: frequencyControl.topPadding + frequencyControl.availableHeight / 2 - height / 2
                implicitWidth: Math.round(5 * Style.scaleHint)
                implicitHeight: Math.round(15 * Style.scaleHint)
                color: "#004B8D"
                Text
                {
                    text: TestData.TestFrequency
                    anchors.left: parent.left
                    anchors.leftMargin: -8
                    anchors.top: parent.top
                    anchors.topMargin: -20
                    color: Style.buttonBackgroundColor
                    font.pixelSize: 16
                }
            }
        }

        Text
        {
            id: frequencyMaxValue
            text: TestData.getTestFrequencyMax() + " " + mainWindow.qmltextFrequencyUnit
            anchors.left: frequencyControl.right
            anchors.leftMargin:  Math.round(15 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(23 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: storedFrequencyText
            text: qmltextStoredFrequency
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(5 * Style.scaleHint)
            anchors.top: frequencyText.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: "#000000"
        }

        Text
        {
            id: storedFrequencyMinValue
            text: TestData.getTestStoredFrequencyMin()+" "+ mainWindow.qmltextFrequencyUnit
            anchors.right: storedFrequencyControl.left
            anchors.rightMargin:  Math.round(10 * Style.scaleHint)
            anchors.top: frequencyMinValue.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Slider
        {
            id: storedFrequencyControl
            enabled: false
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(145 * Style.scaleHint)
            anchors.top: frequencyControl.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            from: TestData.getTestStoredFrequencyMin()
            value: TestData.TestStoredFrequency
            to: TestData.getTestStoredFrequencyMax()

            background: Rectangle
            {
                x: storedFrequencyControl.leftPadding
                y: storedFrequencyControl.topPadding + storedFrequencyControl.availableHeight / 2 - height / 2
                implicitWidth: Math.round(275 * Style.scaleHint)
                implicitHeight: Math.round(5 * Style.scaleHint)
                width: storedFrequencyControl.availableWidth
                height: implicitHeight
                color: "#FFFFFF"
                border.color: "#AEAEAE"
                radius: 10
            }

            handle: Rectangle
            {
                x: storedFrequencyControl.leftPadding + storedFrequencyControl.visualPosition * (storedFrequencyControl.availableWidth - width)
                y: storedFrequencyControl.topPadding + storedFrequencyControl.availableHeight / 2 - height / 2
                implicitWidth: Math.round(5 * Style.scaleHint)
                implicitHeight: Math.round(15 * Style.scaleHint)
                color: "#004B8D"
                Text
                {
                    text: TestData.TestStoredFrequency
                    anchors.left: parent.left
                    anchors.leftMargin: -8
                    anchors.top: parent.top
                    anchors.topMargin: -18
                    color: Style.buttonBackgroundColor
                    font.pixelSize: 16
                }
            }
        }

        Text
        {
            id: storedFrequencyMaxValue
            text: TestData.getTestStoredFrequencyMax() +  " "+ mainWindow.qmltextFrequencyUnit
            anchors.left: storedFrequencyControl.right
            anchors.leftMargin:  Math.round(15 * Style.scaleHint)
            anchors.top: frequencyMaxValue.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
        }

        Text
        {
            id: powerText
            text: qmltextPower
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(5 * Style.scaleHint)
            anchors.top: storedFrequencyText.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: "#000000"
        }

                Text
                {
                    id: powerMinValue
                    text: "0" + " "+ mainWindow.qmltextPowerUnit
                    anchors.right: powerControl.left
                    anchors.rightMargin:  Math.round(10 * Style.scaleHint)
                    anchors.top: storedFrequencyMinValue.bottom
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

                Slider
                {
                    id: powerControl
                    enabled: false
                    anchors.left: parent.left
                    anchors.leftMargin:  Math.round(145 * Style.scaleHint)
                    anchors.top: storedFrequencyControl.bottom
                    anchors.topMargin: Math.round(20 * Style.scaleHint)
                    from: 0.0
                    value: (TestData.TestPower/TestData.getTestPowerMax())// 0.5
                    to: 1.0

                    background: Rectangle
                    {
                        x: powerControl.leftPadding
                        y: powerControl.topPadding + powerControl.availableHeight / 2 - height / 2
                        implicitWidth: Math.round(275 * Style.scaleHint)
                        implicitHeight: Math.round(5 * Style.scaleHint)
                        width: powerControl.availableWidth
                        height: implicitHeight
                        color: "#FFFFFF"
                        border.color: "#AEAEAE"
                        radius: 10
                    }

                    handle: Rectangle
                    {
                        x: powerControl.leftPadding + powerControl.visualPosition * (powerControl.availableWidth - width)
                        y: powerControl.topPadding + powerControl.availableHeight / 2 - height / 2
                        implicitWidth: Math.round(5 * Style.scaleHint)
                        implicitHeight: Math.round(15 * Style.scaleHint)
                        color: "#004B8D"
                        Text
                        {
                            text: TestData.TestPower.toFixed(3)
                            anchors.left: parent.left
                            anchors.leftMargin: -8
                            anchors.top: parent.top
                            anchors.topMargin: -18
                            color: Style.buttonBackgroundColor
                            font.pixelSize: 16
                        }
                    }
                }

                Text
                {
                    id: powerMaxValue
                    text: TestData.getTestPowerMax() + " " + mainWindow.qmltextPowerUnit
                    anchors.left: powerControl.right
                    anchors.leftMargin:  Math.round(15 * Style.scaleHint)
                    anchors.top: storedFrequencyMaxValue.bottom
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                    font.family: Style.regular.name
                    color: Style.blackFontColor
                }

       }

    Rectangle
    {
        id: amplitudeRect
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(45 * Style.scaleHint)
        implicitWidth: Math.round(270 * Style.scaleHint)
        implicitHeight: Math.round(120 * Style.scaleHint)
        color: "#FFFFFF"
        border.color: "#707070"

        BransonLeftBorderRectangle
        {
            id: btnRecipeMode
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            width: Math.round(Math.round(240 * Style.scaleHint))
            height: Math.round(Math.round(50 * Style.scaleHint))
            checked: true

            Text
            {
                anchors.left: parent.left
                anchors.leftMargin: Math.round(15 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: qmltextTestAmplitude
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            }

            Text
            {
                id: testAmp2
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(5 * Style.scaleHint)
                text: TestData.TestAmplitude2 + " "+mainWindow.qmltextAmplitudeUnit
                color: "#000000"
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }

            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    TestData.AmpUpdateFlagStatus = true
                    mainWindow.showPrimaryNumpad(qmltextTestAmplitude, mainWindow.qmltextAmplitudeUnit , 0, 10, 100, TestData.TestAmplitude2)
                }
            }
        }

        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(5 * Style.scaleHint)
            text: qmltextInstruction
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
        }
    }

    Loader
    {
        id: loader
        anchors.left: parent.left
        anchors.leftMargin: Math.round(8 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(7 * Style.scaleHint)
        anchors.top: testRect.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        source: "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/TestGraphWindow.qml"
    }
}

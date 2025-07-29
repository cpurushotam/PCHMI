/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AnalyticsWindow.qml file loads the analytics menu related subscreens.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 13/10/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"

Item {
    id: analyticsCardWindowItem


    property string qmltextMenuName               : "Analytics"
    property string qmltextEditRecipe             : "Edit Recipe"
    property string qmltextGenerateReport         : "Generate Report"
    property string qmltextResults                : "Results"
    property string qmltextAlarms                 : "Alarms"

    property var qmlTextArray: [qmltextEditRecipe, qmltextGenerateReport, qmltextResults, qmltextAlarms]

    function updateTabBar()
    {
        analyticsTabBarModel.clear()
        analyticsTabBarModel.append({"Title":      qmltextResults,
                                     "Width":      Math.round(50 * Style.scaleHint)})
        /*analyticsTabBarModel.append({"Title":      qmltextAlarms,
                                     "Width":      Math.round(50 * Style.scaleHint)})*/
    }

    QtObject
    {
        id: textEnum
        readonly property int editRecipeIdx      : 0
        readonly property int generateReportIdx  : 1
        readonly property int resultsIdx         : 2
        readonly property int alarmsIdx          : 3
    }

    QtObject
    {
        id: enumTabBarIndex
        readonly property int resultsIdx      : 0
        readonly property int alarmsIdx       : 1
    }

    function updateScreen(index)
    {
        switch(index)
        {
        case enumTabBarIndex.resultsIdx:
            loader.source = "qrc:/Core/Logic/Front_End_Logic/Analytics_Screens/NormalGraphWindow.qml"
            break;

        case enumTabBarIndex.alarmsIdx:
            /*TODO : Screen To Be Design*/
            break;

        default:
            break;
        }
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS, qmlTextArray)
        qmltextEditRecipe     = qmlTextArray[textEnum.editRecipeIdx]
        qmltextGenerateReport = qmlTextArray[textEnum.generateReportIdx]
        qmltextResults        = qmlTextArray[textEnum.resultsIdx]
        qmltextAlarms         = qmlTextArray[textEnum.alarmsIdx]
        qmltextMenuName       = LanguageConfig.getLanguageMenuName(UIScreenEnum.ANALYTICS, qmltextMenuName)
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
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.ANALYTICS)
        updateTabBar()
        updateLanguage()
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.ANALYTICS
    }

    ListModel
    {
        id: analyticsTabBarModel
    }

    Text
    {
        id: titleText
        text: qmltextResults
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style2  * Style.scaleHint)
        font.family: Style.regular.name
        font.bold: true
        color: Style.blackFontColor
    }

    /*Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.leftMargin: Math.round(14 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(200 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            spacing: Math.round(20 * Style.scaleHint)
            background: Rectangle
            {
                color: Style.backgroundColor
            }

            Repeater
            {
                id: tabbtn
                model: analyticsTabBarModel
                delegate: BransonTabButton
                {
                    width: model.width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked:
                    {
                        updateScreen(model.Index)
                    }
                }
            }
        }
    }*/

    BransonPrimaryButton
    {
        id: editRecipeButton
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(25 * Style.scaleHint)
        fontSize: Math.round(Style.style0  * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.right: generateReportButton.left
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        text: qmltextEditRecipe
        font.family: Style.regular.name
        buttonColor: Style.blueFontColor
        textColor: "#FFFFFF"
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES,UIScreenEnum.RECIPES_LAB)
        }
    }

    BransonPrimaryButton
    {
        id: generateReportButton
        implicitWidth: Math.round(180 * Style.scaleHint)
        implicitHeight: Math.round(25 * Style.scaleHint)
        fontSize: Math.round(Style.style0  * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(8 * Style.scaleHint)
        text: qmltextGenerateReport
        font.family: Style.regular.name
        buttonColor: Style.blueFontColor
        textColor: "#FFFFFF"
        onClicked:
        {
            mainWindow.menuParentOptionSelect(UIScreenEnum.GENERATEREPORT)
        }
    }


    Loader
    {
        id: loader
        anchors.left: parent.left
        anchors.leftMargin: Math.round(2 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(7 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(25 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(8 * Style.scaleHint)
        source: "qrc:/Core/Logic/Front_End_Logic/Analytics_Screens/NormalGraphWindow.qml"
    }

}

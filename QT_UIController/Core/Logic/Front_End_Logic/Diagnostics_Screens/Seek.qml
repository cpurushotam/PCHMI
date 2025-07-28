/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn seek result parameters.

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
    property string qmltextMenuName         : "Seek"
    property string qmltextSeek             : "Seek"
    property string qmltextSeekRun          : "SEEK RUN"
    property string qmltextSeekRecipe       : "SEEK RECIPE"

    property var qmlTextArray: [qmltextSeek, qmltextSeekRun, qmltextSeekRecipe]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SEEK, qmlTextArray)
        qmltextSeek = qmlTextArray[textEnum.textSeekIdx]
        qmltextSeekRun = qmlTextArray[textEnum.textSeekRunIdx]
        qmltextSeekRecipe = qmlTextArray[textEnum.textSeekRecipeIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS_SEEK, qmltextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textSeekIdx            : 0
        readonly property int textSeekRunIdx         : 1
        readonly property int textSeekRecipeIdx      : 2
    }

    Component.onCompleted:
    {
        /*To reinitiate seek signature read request*/
        SeekData.isScreenReNavigated(true)

        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTICS_SEEK)
        updateLanguage()
        loader.source = "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/SeekGraphWindow.qml"
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS_SEEK
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Text
    {
        id: seekText
        text: qmltextSeek
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
        id: seekRun
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(150 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmltextSeekRun
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            SeekData.seekRun()
        }
    }

    BransonPrimaryButton
    {
        id: seekRecipe
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        text: qmltextSeekRecipe
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SEEK_RECIPE)
        }
    }

    Loader
    {
        id: loader
        anchors.left: parent.left
        anchors.leftMargin: Math.round(8 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(7 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(50 * Style.scaleHint)
        source: "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/SeekGraphWindow.qml"
    }
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the horn scan result parameters.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 03/04/2024 - Initial version.
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
    property string qmltextMenuName               : "Scan"
    property string qmltextHornScan               : "Horn Scan"
    property string qmltextStartHornScan          : "START HORN SCAN"
    property string qmltextAbortScan              : "ABORT SCAN"
    property string qmltextHornRecipe             : "HORN RECIPE"
    property string qmltextScanInProgress         : "Scan In Progress..."
    property string qmltextCancel                 : "CANCEL"
    property string qmltextNavigationConfirmation : "Do you want to abort the scan operation..?"
    signal scanRunStatusDataChanged()

    property var qmlTextArray: [qmltextHornScan, qmltextStartHornScan, qmltextAbortScan, qmltextHornRecipe,
                                qmltextScanInProgress, qmltextCancel]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_SCAN, qmlTextArray)
        qmltextHornScan = qmlTextArray[textEnum.textHornScanIdx]
        qmltextStartHornScan = qmlTextArray[textEnum.textStartHornScanIdx]
        qmltextAbortScan = qmlTextArray[textEnum.textAbortScanIdx]
        qmltextHornRecipe = qmlTextArray[textEnum.textHornRecipeIdx]
        qmltextScanInProgress = qmlTextArray[textEnum.textScanInProgressIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextNavigationConfirmation = qmlTextArray[textEnum.textNavigationConfirmationIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS_SCAN, qmltextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textHornScanIdx                       : 0
        readonly property int textStartHornScanIdx                  : 1
        readonly property int textAbortScanIdx                      : 2
        readonly property int textHornRecipeIdx                     : 3
        readonly property int textScanInProgressIdx                 : 4
        readonly property int textCancelIdx                         : 5
        readonly property int textNavigationConfirmationIdx         : 6

    }

    Connections
    {
        target: ScanCycleDetailsListModel
        function onScanRunStatusDataChanged()
        {
           if(ScanCycleDetailsListModel.ScanRunStatus)
           {
               actionBlockerLayer.visible = true
           }

           else
           {
               actionBlockerLayer.visible = false
           }
        }
    }

    Component.onCompleted:
    {
        /*To reinitiate seek signature read request*/
        ScanCycleDetailsListModel.isScreenReNavigated(true)

        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTICS_SCAN)
        updateLanguage()
        loader.source = "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/ScanGraphWindow.qml"

        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS_SCAN
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Text
    {
        id: hornScanText
        text: qmltextHornScan
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
        id: startHornScan
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style0  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(300 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        text: qmltextStartHornScan
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            ScanCycleDetailsListModel.ScanRunStatus = true
            ScanCycleDetailsListModel.startHornScan(true)
        }
    }

    BransonPrimaryButton
    {
        id: abortHornScan
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(150 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        text: qmltextAbortScan
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            if(ScanCycleDetailsListModel.ScanRunStatus)
            {
                scanPopup.visible = true
                abortHornScan.enabled = false
            }
        }
    }

    BransonPrimaryButton
    {
        id: hornRecipe
        implicitWidth: Math.round(124 * Style.scaleHint)
        implicitHeight: Math.round(30 * Style.scaleHint)
        fontSize: Math.round(Style.style2  * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        text: qmltextHornRecipe
        buttonColor: Style.buttonBackgroundColor
        font.family: Style.regular.name
        onClicked:
        {
            if(! ScanCycleDetailsListModel.ScanRunStatus)
            {
                mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SCAN_RECIPE)
            }

            else
            {
               scanPopup.visible = true
            }
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
        anchors.bottom: parent.bottom
        source: "qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/ScanGraphWindow.qml"
    }

    Rectangle
    {
        id: scanInProgressStatusRect
        visible: ScanCycleDetailsListModel.ScanRunStatus
        anchors.left: parent.left
        anchors.leftMargin: Math.round(25 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(25 * Style.scaleHint)
        width: Math.round(250 * Style.scaleHint)
        height: Math.round(50 * Style.scaleHint)
        color: "#2D383F"
        radius: Math.round(5 * Style.scaleHint)

        Text
        {
            id: scanInProgressStatusText
            text: qmltextScanInProgress
            anchors.left: parent.left
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            color: "#FFFFFF"
        }

        Text
        {
            id: scanInProgressStatusCancelText
            text: qmltextCancel
            anchors.right: parent.right
            anchors.rightMargin: Math.round(20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            font.family: Style.regular.name
            font.bold: true
            color: "#759EE1"

            MouseArea
            {
                id: scanInProgressStatusCancelTextMA
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    scanPopup.visible = true
                }
            }
        }
    }

    Rectangle
    {
        id: actionBlockerLayer
        visible: false
        y: Math.round(-50 * Style.scaleHint)
        z: 10
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
        color: "transparent"
        radius: Math.round(5 * Style.scaleHint)
        opacity: 0.5
        MouseArea
        {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                scanPopup.visible = true
            }
        }
    }

    BransonPopup
    {
        id: scanPopup
        isMultiButtonPopup : true
        visible : false
        qmltextWarningDialog : qmltextNavigationConfirmation

        onOKButtonClicked:
        {
            ScanCycleDetailsListModel.ScanRunStatus = false
            ScanCycleDetailsListModel.abortHornScan(true)
            scanPopup.visible = false
            abortHornScan.enabled = true
        }

        onCancelButtonClicked:
        {
           scanPopup.visible = false
            abortHornScan.enabled = true
        }
    }
}

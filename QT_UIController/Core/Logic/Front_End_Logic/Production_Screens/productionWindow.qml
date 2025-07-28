/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ProductionWindow.qml file displays production screen's data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/05/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Controls
import "./../Common_Logic"
Item {
    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    readonly property int qmlscreenIndicator:  UIScreenEnum.PRODUCTION
    property string qmltextMenuName:        qsTr("Production")
    property string qmltextActiveRecipe:    qsTr("Active Recipe")
    property string qmltextTotalCycleTIme:  qsTr("Total Cycle Time")
    property string qmltextCycleCount:      qsTr("Cycle Count")
    property string qmltextPeakPower:       qsTr("Peak Power")
    property string qmltextBatchCount:      qsTr("Batch Count")
    property string qmltextPartsPerMin:     qsTr("Parts Per Min")
    property string qmltextCyclesOK:        qsTr("Cycles OK : ")
    property string qmltextRejected:        qsTr("Reject : ")
    property string qmltextSuspected:       qsTr("Suspect : ")
    property string qmltextYieldPercentage: qsTr("Yield Percentage : ")
    property string qmltextPartId:          qsTr("Part Id : ")

    readonly property int marginSize: Math.round(20 * Style.scaleHint)
    readonly property int topHeightSize: Math.round(140 * Style.scaleHint)
    readonly property int midHeightSize: Math.round(150 * Style.scaleHint)
    readonly property int widthSize: Math.round(380 * Style.scaleHint)
    readonly property int titleSize: Math.round(30 * Style.scaleHint)

    property int cyclesOKEndAngle : 0
    property int suspectedCyclesEndAngle : 0
    property int yeildPercentage : ProductionRunInterface.YieldPercentage.toFixed(2)
    property int startAngle : 0

    property var qmlTextArray: [qmltextActiveRecipe, qmltextTotalCycleTIme, qmltextCycleCount, qmltextPeakPower, qmltextBatchCount,qmltextPartsPerMin,qmltextCyclesOK,qmltextRejected,qmltextSuspected,qmltextYieldPercentage]

    id: productionWindowItem

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.PRODUCTION, qmlTextArray)
        qmltextActiveRecipe = qmlTextArray[textEnum.activeRecipeIdx]
        qmltextTotalCycleTIme = qmlTextArray[textEnum.totalCycleTImeIdx]
        qmltextCycleCount = qmlTextArray[textEnum.cycleCountnIdx]
        qmltextPeakPower = qmlTextArray[textEnum.peakPowerIdx]
        qmltextBatchCount = qmlTextArray[textEnum.batchCountIdx]
        qmltextPartsPerMin = qmlTextArray[textEnum.partsPerMinIdx]
        qmltextCyclesOK = qmlTextArray[textEnum.cyclesOKIdx]
        qmltextRejected = qmlTextArray[textEnum.rejectedIdx]
        qmltextSuspected = qmlTextArray[textEnum.suspectedIdx]
        qmltextYieldPercentage = qmlTextArray[textEnum.yieldPercentageIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.PRODUCTION, qmltextMenuName)
    }

    function getYieldPercentage()
    {
        /*Divided by 10 to ckeck that if some digits are there after decimal points*/
        if((yeildPercentage / 10) === 0)
        {
            return ProductionRunInterface.YieldPercentage;
        }
        else{
            return yeildPercentage;
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }


    Component.onCompleted:
    {
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.PRODUCTION)
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.PRODUCTION
    }

    QtObject {
        id: textEnum
        readonly property int activeRecipeIdx:      0
        readonly property int totalCycleTImeIdx:    1
        readonly property int cycleCountnIdx:       2
        readonly property int peakPowerIdx:         3
        readonly property int batchCountIdx:        4
        readonly property int partsPerMinIdx:       5
        readonly property int cyclesOKIdx:          6
        readonly property int rejectedIdx:          7
        readonly property int suspectedIdx:         8
        readonly property int yieldPercentageIdx:   9
    }

    Rectangle {
        id: rectBackground
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Rectangle {
        id: rectActionRecipe
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.02
        anchors.left: rectCycleCount.right
        anchors.leftMargin: parent.width * 0.02
        anchors.top: rectTotalCycleTime.bottom
        anchors.topMargin: parent.width * 0.02
        width: rectCycleCount.width
        height: rectCycleCount.height * 0.48
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectActionRecipeTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextActiveRecipe
            }
        }

        Rectangle
        {
            id: rectActionRecipeInfo
            anchors.left: parent.left
            anchors.leftMargin: parent.border.width
            anchors.top: rectActionRecipeTitle.bottom
            width: parent.width - 2 * parent.border.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.border.width
            Column{
                anchors.centerIn: parent
                spacing: 10

                Text
                {
                    id: txtRecipeName
                    visible: RecipeLabData.IsRecipeSaved
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    color: Style.blackFontColor
                    text: ProductionRunInterface.ActiveRecipeNum + " : " + ProductionRunInterface.ActiveRecipeName
                }

                Text
                {
                    id: txtRecipeNameWithAsterisk
                    visible: (! RecipeLabData.IsRecipeSaved)
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    color: Style.blackFontColor
                    text: "*" + ProductionRunInterface.ActiveRecipeNum + " : " + ProductionRunInterface.ActiveRecipeName
                }

                Text
                {
                    id: txtRecipeMode
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                    color: Style.blackFontColor
                    text: mainWindow.getWeldModeText(ProductionRunInterface.RecipeWeldMode) + ": " +
                          ProductionRunInterface.RecipeWeldModeValue +
                          ProductionRunInterface.RecipeWeldModeUnit//"Collapse Distance: 0.40 mm"
                }
            }
        }
    }

    Rectangle {
        id: rectTotalCycleTime
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.02
        anchors.top: parent.top
        anchors.topMargin: parent.width * 0.02
        anchors.left: rectCycleCount.right
        anchors.leftMargin: parent.width * 0.02
        height: rectCycleCount.height * 0.48
        width: rectCycleCount.width
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectTotalCycleTimeTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                id: totaltime
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextTotalCycleTIme +  " ("+mainWindow.qmltextTimeUnit +")"
            }
        }
        Rectangle {
            id: rectTotalCycleTimeValue
            anchors.left: parent.left
            anchors.leftMargin: parent.border.width
            anchors.top: rectTotalCycleTimeTitle.bottom
            width: parent.width - 2 * parent.border.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.border.width
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style8 * Style.scaleHint)
                color: Style.blackFontColor
                text: ProductionRunInterface.TotalCycleTime
            }
        }
    }

    Rectangle {
        id: rectCycleCount
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.02
        anchors.rightMargin: parent.width * 0.02
        anchors.top: parent.top
        anchors.topMargin: parent.width * 0.02
        width: parent.width * 0.48
        height: parent.height * 0.75
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        Rectangle {
            id: rectCycleCountTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: titleSize
            color: Style.titleBackgroundColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.whiteFontColor
                text: qmltextCycleCount
            }
        }
        Rectangle {
            id: rectBatchCountTitle
            anchors.top: rectCycleCountTitle.bottom
            anchors.topMargin : marginSize
            anchors.left: parent.left
            anchors.leftMargin: Math.round(70 * Style.scaleHint)
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.blackFontColor
                text: qmltextBatchCount
            }
        }

        Rectangle {
            id: rectCyclePartsPerMinTitle
            anchors.top: rectCycleCountTitle.bottom
            anchors.topMargin : marginSize
            anchors.right: parent.right
            anchors.rightMargin: Math.round(70 * Style.scaleHint)
            color: Style.backgroundlightBlueColor
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.blackFontColor
                text: qmltextPartsPerMin
            }
        }

        Rectangle {
            id: rectBatchCountValue
            width : Math.round(70 * Style.scaleHint)
            height : Math.round(25 * Style.scaleHint)
            anchors.top: rectBatchCountTitle.bottom
            anchors.topMargin : marginSize
            anchors.left: parent.left
            anchors.horizontalCenter: rectBatchCountTitle.horizontalCenter
            anchors.leftMargin : Math.round(50 * Style.scaleHint)
            color: Style.backgroundlightBlueColor
            z:0
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.blackFontColor
                text: ProductionRunInterface.BatchCount
                z:1
            }
        }
        Rectangle {
            id: rectCyclePartsPerMinValue
            width : Math.round(70 * Style.scaleHint)
            height : Math.round(25 * Style.scaleHint)
            anchors.top: rectCyclePartsPerMinTitle.bottom
            anchors.topMargin : marginSize
            anchors.right: parent.right
            anchors.rightMargin : Math.round(50 * Style.scaleHint)
            anchors.horizontalCenter: rectCyclePartsPerMinTitle.horizontalCenter
            color: Style.backgroundlightBlueColor
            z:0
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                color: Style.blackFontColor
                text:  ProductionRunInterface.PartsPerMin
                z:1
            }
        }
        Rectangle{
            id: rectCycleDetailsPercentage
            width: parent.width * 0.40
            height: parent.width * 0.40
            anchors.top: parent.top
            anchors.topMargin: Math.round(50 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                anchors.centerIn: parent
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style8 * Style.scaleHint)
                color: Style.blackFontColor
                text: ProductionRunInterface.CycleCount
                z:1
            }
            Canvas {
                id: cycleDetailsCircleCanvas
                width: parent.width
                height: parent.width
                z: 0
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = Math.round(Style.style1 * Style.scaleHint);
                    ctx.beginPath();
                    ctx.strokeStyle = "#00AA7E";
                    if(ProductionRunInterface.CyclesOkCount != 0)
                    {
                        ctx.arc(parent.width/2, parent.width/2, parent.width * 0.45, startAngle, ProductionRunInterface.CyclesOkEndAngle, false);
                        ctx.stroke();
                    }
                    ctx.beginPath();
                    ctx.strokeStyle = "darkGray";
                    if(ProductionRunInterface.SuspectedCycles != 0)
                    {
                        ctx.arc(parent.width/2, parent.width/2, parent.width * 0.45,  ProductionRunInterface.CyclesOkEndAngle , ProductionRunInterface.SuspectedCyclesEndAngle, false);
                        ctx.stroke();
                    }
                    ctx.beginPath();
                    ctx.strokeStyle = "#D31313"
                    if(ProductionRunInterface.RejectedCycles != 0)
                    {
                        ctx.arc(parent.width/2, parent.width/2, parent.width * 0.45, ProductionRunInterface.SuspectedCyclesEndAngle, startAngle, false);
                        ctx.stroke();
                    }
                }
                //This timer updates the canvas(circular ProgressBar) continously as per values changed
                Timer{
                    interval : 1000
                    running : true
                    repeat: true
                    onTriggered:{
                        cycleDetailsCircleCanvas.requestPaint()
                    }
                }
            }
        }
        
        Rectangle{
            id: rectCycleDetailsLabels
            width: parent.width * 0.90
            height: Math.round(20 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rectCycleDetailsPercentage.bottom
            anchors.topMargin: Math.round(20 * Style.scaleHint)
            Image
            {
                id: cyclesOKImage
                source: "qrc:/Images/Cycle_ok_icon.svg"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                sourceSize.width: cyclesOKImage.width
                sourceSize.height: cyclesOKImage.height
                smooth: true
            }
            Label{
                id: lblCycleOk
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: cyclesOKImage.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                text: qmltextCyclesOK + ProductionRunInterface.CyclesOkCount
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }
            Image
            {
                id: cyclesRejectedImage
                source: "qrc:/Images/Reject_icon.svg"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: lblCycleOk.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                sourceSize.width: cyclesRejectedImage.width
                sourceSize.height: cyclesRejectedImage.height
                smooth: true
            }
            Label{
                id: lblRejected
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: cyclesRejectedImage.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                text: qmltextRejected + ProductionRunInterface.RejectedCycles
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }
            Image
            {
                id: cyclesSuspectedImage
                source: "qrc:/Images/Suspect_icon.svg"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: lblRejected.right
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                sourceSize.width: cyclesSuspectedImage.width
                sourceSize.height: cyclesSuspectedImage.height
                smooth: true
            }
            Label{
                id: lblSuspected
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: cyclesSuspectedImage.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                text: qmltextSuspected + ProductionRunInterface.SuspectedCycles
                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            }
        }

        Rectangle{
            id: rectYieldPercentageLine
            width: parent.width * 0.70
            height: Math.round(1 * Style.scaleHint)
            border.color: "#707070"
            anchors.top: rectCycleDetailsLabels.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            border.width: Math.round(1 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text{
            id:yeildpercenttxt
            height: Math.round(1 * Style.scaleHint)
            anchors.top: rectYieldPercentageLine.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            text: qmltextYieldPercentage + getYieldPercentage()  + " % "
            color: "#707070"
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)

        }

        Text{
            height: Math.round(1 * Style.scaleHint)
            anchors.top: yeildpercenttxt.bottom
            anchors.topMargin: Math.round(25 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            text: qmltextPartId +ProductionRunInterface.PartId
            visible:  ProductionRunInterface.IsPartIdEnable ? true : false
            color: "#707070"
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)

        }
    }

    BransonProgressBar {
        id: recPeakPower
        anchors.left: parent.left
        anchors.leftMargin: productionWindowItem.marginSize
        anchors.right: parent.right
        anchors.rightMargin: marginSize
        anchors.bottom: parent.bottom
        fontFamily: Style.regular.name
        progressValue: ProductionRunInterface.PeakPowerRatio
        progressActualValue: ProductionRunInterface.PeakPower
        progressTitle: qmltextPeakPower
    }

    Rectangle{
        id: rectProgressBar
        anchors.left: parent.left
        color: "transparent"
        anchors.leftMargin: productionWindowItem.marginSize
        anchors.right: parent.right
        anchors.rightMargin: marginSize
        anchors.bottom: parent.bottom
        height: Math.round(30 * Style.scaleHint)
        border.width: Math.round(2 * Style.scaleHint)
        border.color: "black"
    }
}

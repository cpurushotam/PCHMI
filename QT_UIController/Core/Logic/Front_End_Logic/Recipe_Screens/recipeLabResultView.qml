/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    recipeLabResultView.qml file shows recipes lab result view page.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
***************************************************************************/

import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import QtQuick.Layouts
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Analytics_Screens"
import "./../Common_Logic"
Item {

    property string qmltextResult                           : "Result"
    property string qmltextGenerateReport                   : "Generate Report"
    property string qmltextChooseParameters                 : "Choose Parameters"

    property double timeMaxValue : GraphSettings.TimeAxisMaxValue
    property double timeMinValue : GraphSettings.TimeAxisMinValue

    signal tableViewListDataChanged()
    signal referenceGraphDataChanged()
    signal rowCountChanged();

    property var qmlTextArray: [qmltextResult, qmltextGenerateReport, qmltextChooseParameters ]

    QtObject
    {
        id: textEnum
        readonly property int resultIdx                  : 0
        readonly property int generateReportIdx          : 1
        readonly property int chooseParametersIdx        : 2
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_TABLE_VIEW, qmlTextArray)
        qmltextResult     = qmlTextArray[textEnum.resultIdx]
        qmltextGenerateReport = qmlTextArray[textEnum.generateReportIdx]
        qmltextChooseParameters= qmlTextArray[textEnum.chooseParametersIdx]
    }

    function fillComboBoxListModel()
    {
        comboBoxListModel.clear();
        for(var i = 0; i < proxyModel.rowCount; i++)
        {
            comboBoxListModel.append({"name" : proxyModel.getCycleNumberForListView(i)})
        }
    }

    Connections
    {
        target: CycleDetailtablemodel
        function onTableViewListDataChanged()
        {
            CycleDetailtablemodel.loadTableViewDetailsList();
            CycleDetailsListModel.loadCycleDetailsList();
            proxyModel.getWeldAndReferneceDataList(ReferenceWeldGraphData.copyReferenceGraphData(),CycleDetailtablemodel.copyWeldResultData());
            /*Active screen update*/
            ResultViewWeldProxyModel.getWeldAndReferneceDataList(ReferenceWeldGraphData.copyReferenceGraphData(),CycleDetailtablemodel.copyWeldResultData());
            fillComboBoxListModel();

        }
    }

    Connections
    {
        target: proxyModel
        function onRowCountChanged()
        {
            tableViewReferenceData.Layout.preferredHeight = proxyModel.getVisibleRowCount() * Math.round(45 * Style.scaleHint);
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

    Component.onCompleted:
    {
        CycleDetailtablemodel.loadTableViewDetailsList();
        CycleDetailsListModel.loadCycleDetailsList();
        proxyModel.getWeldAndReferneceDataList(ReferenceWeldGraphData.copyReferenceGraphData(),CycleDetailtablemodel.copyWeldResultData());
        ResultViewWeldProxyModel.getWeldAndReferneceDataList(ReferenceWeldGraphData.copyReferenceGraphData(),CycleDetailtablemodel.copyWeldResultData());
        fillComboBoxListModel();
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.ANALYTICS
        updateLanguage()
    }

    Row
    {
        id: btnArray
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(6 * Style.scaleHint)
        width: Math.round(92 * Style.scaleHint)
        height: Math.round(25 * Style.scaleHint)
        spacing: Math.round(2 * Style.scaleHint)
        Rectangle
        {
            id: recordsBtn
            width: parent.width/2
            height: parent.height
            border.width: 1
            border.color: Style.frameBorderColor
            radius: 2
            Image {
                id: recordsImage
                source: "qrc:/Images/Table.svg"
                width: Math.round(30 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.centerIn: parent
                sourceSize.width: recordsImage.width
                sourceSize.height: recordsImage.height
                smooth: true
            }
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    chartView.visible = false;
                    recordsBtn.border.color="#6699cc"
                    graphBtn.border.color="#9fa1a4"
                }
            }
        }

        Rectangle
        {
            id: graphBtn
            width: parent.width/2
            height: parent.height
            border.width: 1
            border.color: Style.frameBorderColor
            radius: 2
            Image {
                id: graphImage
                source: "qrc:/Images/Graph.svg"
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                anchors.centerIn: parent
                sourceSize.width: graphImage.width
                sourceSize.height: graphImage.height
                smooth: true
            }
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeLabResultViewGraph.qml"
                    chartView.visible = true;
                    graphBtn.border.color="#6699cc"
                    recordsBtn.border.color="#9fa1a4"
                }
            }
        }
    }

    ListModel{
        id: comboBoxListModel
    }
    Image{
        id: referenceGraphIconPopup
        // visible: model.column === 0
        anchors.verticalCenter: rectRefGraphComboBoxText.verticalCenter
        height: rectRefGraphComboBoxText.height / 2
        width: rectRefGraphComboBoxText.height / 2
        anchors.right: rectRefGraphComboBoxText.left
        anchors.rightMargin: Math.round(15 * Style.scaleHint)
        source: "qrc:/Images/star_icon.svg"
        sourceSize.width: referenceGraphIconPopup.width
        sourceSize.height: referenceGraphIconPopup.height
    }


    Rectangle{
        id: rectRefGraphComboBoxText
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(6 * Style.scaleHint)
        height: parent.height * 0.06
        width: parent.width * 0.1
        radius : 5
        border.color: "black"
        border.width : 2
        Text{
            height: parent.height / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: parent.width * 0.05
            width: parent.width
            text: proxyModel.refGraphCycleNumbers
        }
        MouseArea{
            anchors.fill: parent

            onClicked:{
                popup.open()
            }
        }
    }

    Popup{
        id: popup
        height:  Math.round(20 * Style.scaleHint) * proxyModel.rowCount
        width: rectRefGraphComboBoxText.width
        x: rectRefGraphComboBoxText.x - Math.round(5 * Style.scaleHint)
        y: rectRefGraphComboBoxText.y + rectRefGraphComboBoxText.height

        ListView {
            height:  rectRefGraphComboBoxText.height * proxyModel.rowCount
            width: rectRefGraphComboBoxText.width
            model: comboBoxListModel
            delegate: Rectangle {
                width: parent.width
                height: rectRefGraphComboBoxText.height
                color: ListView.isCurrentItem ? "lightblue" : "white"
                border.color: "black"
                CheckBox{
                    height: rectRefGraphComboBoxText.height
                    width: rectRefGraphComboBoxText.height
                    checked: true
                    onCheckedChanged: {
                        if(checked)
                        {
                            proxyModel.appendDataToList(model.index);
                        }
                        else
                        {
                            proxyModel.removeDataFromList(model.index);
                        }
                    }
                }

                Text {
                    text: model.name
                    anchors.centerIn: parent
                }
            }
        }
    }

    Rectangle {
        id: table
        width:parent.width* Math.round(0.95 * Style.scaleHint)
        height: parent.height * (0.95 * Style.scaleHint)
        anchors.left: parent.left
        anchors.top: btnArray.bottom

        anchors.bottom: parent.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(5 * Style.scaleHint)
        clip: true

        function columnWidthProvider(column) {
            return mainWindow.showWidth*0.15
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            HorizontalHeaderView {
                id: horizontalHeader
                reuseItems: false
                syncView: tableViewWeldData
                height: 90
                Layout.fillWidth: true
                boundsBehavior:Flickable.StopAtBounds

                delegate: Rectangle {
                    id: columnHeader
                    color: "#eee"
                    border.color: "transparent"
                    border.width: 1
                    implicitWidth: headerText.contentWidth + 5*splitter.width
                    implicitHeight: mainWindow.showHeight*0.05

                    Text {
                        id: headerText
                        anchors.centerIn: parent
                        font.pixelSize: Math.round(10 * Style.scaleHint)
                        font.bold: false
                        font.family: Style.regular.name
                        text: display
                    }

                    Rectangle {
                        id: splitter
                        x: table.columnWidths[index] - width
                        height: horizontalHeader.height
                        width: 4
                        color: "transparent"
                        visible: dragArea.containsMouse || dragArea.drag.active

                        onXChanged: {
                            if (dragArea.drag.active) {
                                table.columnWidths[index] = splitter.x + width;
                                tableView.forceLayout();
                            }
                        }
                    } // Rectangle splitter

                    MouseArea {
                        id: dragArea
                        anchors.fill: splitter
                        cursorShape: Qt.SizeHorCursor
                        drag.target: splitter
                        drag.axis: Drag.XAxis
                        drag.threshold: 0
                        drag.minimumX: parent.implicitWidth
                        hoverEnabled: true
                    }

                } // delegate Rectangle columnHeader

            } //
            TableView {
                id: tableViewReferenceData
                syncView: tableViewWeldData
                syncDirection : Qt.Horizontal
                Layout.fillWidth: true
                clip: true
                height: proxyModel.visibleRowCount * Math.round(50 * Style.scaleHint)
                boundsBehavior:Flickable.StopAtBounds
                columnWidthProvider: table.columnWidthProvider
                model: proxyModel
                Layout.preferredHeight : proxyModel.visibleRowCount * Math.round(45 * Style.scaleHint)
                // ScrollBar.vertical: ScrollBar {
                //     policy: ScrollBar.AsNeeded
                //     active: true
                //     onActiveChanged: {
                //         if (!active)
                //             active = true;
                //     }
                // }

                // ScrollBar.horizontal: ScrollBar {
                //     policy: ScrollBar.AsNeeded
                //     active: true
                //     onActiveChanged: {
                //         if (!active)
                //             active = true;
                //     }
                // }

                delegate: Rectangle {
                    implicitHeight:mainWindow.showHeight*0.07
                    border.color:"transparent"
                    border.width: 1
                    Text {
                        id: cellTextReferenceData
                        text: display
                        anchors.left: referenceGraphIcon.right
                        font.pixelSize: Math.round(8 * Style.scaleHint)
                        font.bold: false
                        font.family: Style.regular.name
                        anchors.centerIn: parent
                    }
                    Image{
                        id: referenceGraphIcon
                        visible: model.column === 0
                        anchors.verticalCenter: parent.verticalCenter
                        height: cellTextReferenceData.height / 2
                        width: cellTextReferenceData.height / 2
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(5 * Style.scaleHint)
                        source: "qrc:/Images/star_icon.svg"
                        sourceSize.width: referenceGraphIcon.width
                        sourceSize.height: referenceGraphIcon.height
                    }

                    Rectangle {
                        width: parent.width
                        height: 1
                        color:"#0a0a0a"
                        anchors.top: cellTextReferenceData.bottom
                    }
                }
            } // TableView

            TableView {
                id: tableViewWeldData
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                boundsBehavior:Flickable.StopAtBounds
                columnWidthProvider: table.columnWidthProvider
                model: ResultViewWeldProxyModel

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                    active: true
                    onActiveChanged: {
                        if (!active)
                            active = true;
                    }
                }

                // ScrollBar.horizontal: ScrollBar {
                //     policy: ScrollBar.AsNeeded
                //     active: true
                //     onActiveChanged: {
                //         if (!active)
                //             active = true;
                //     }
                // }

                delegate: Rectangle {
                    implicitHeight:mainWindow.showHeight*0.07
                    border.color:"transparent"
                    border.width: 1
                    Text {
                        id: cellTextWeldData
                        text: display
                        font.pixelSize: Math.round(8 * Style.scaleHint)
                        font.bold: false
                        font.family: Style.regular.name
                        anchors.centerIn: parent
                    }
                    Rectangle {
                        width: parent.width
                        height: 1
                        color:"#0a0a0a"
                        anchors.top: cellTextWeldData.bottom
                    }
                }
            } // TableView

        } // ColumnLayout

    } // Rectangle table

    BransonChartView
    {
        id: chartView
        visible: false
        width: parent.width
        anchors.left: parent.left
        anchors.top: parent.bottom
        anchors.bottom: parent.bottom
        timeMin: timeMinValue
        timeMax: timeMaxValue
    }

}


/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ColumnsTableView.qml file displays Table view for AnalyticsWindow related data :
***************************************************************************/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Style 1.0

Rectangle {
    id: table

    required property var model
    required property var columnWidths

    function columnWidthProvider(column) {
        return mainWindow.showWidth*0.15
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        HorizontalHeaderView {
            id: horizontalHeader

            reuseItems: false
            syncView: tableView
            height: 60
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

        } // HorizontalHeaderView

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            boundsBehavior:Flickable.StopAtBounds
            columnWidthProvider: table.columnWidthProvider
            model: table.model

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
                active: true
                onActiveChanged: {
                    if (!active)
                        active = true;
                }
            }

            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AsNeeded
                active: true
                onActiveChanged: {
                    if (!active)
                        active = true;
                }
            }

            delegate: Rectangle {
                implicitHeight:mainWindow.showHeight*0.07
                border.color:"transparent"
                border.width: 1
                Text {
                    id: cellText
                    text: display
                    color : CycleDetailtablemodel.isAlarmExist(row) ? "red" :"black"
                    font.pixelSize: Math.round(8 * Style.scaleHint)
                    font.bold: false
                    font.family: Style.regular.name
                    anchors.centerIn: parent
                }
                Rectangle {
                        width: parent.width
                        height: 1
                        color:"#0a0a0a"
                        anchors.top: cellText.bottom
                }
            }
        } // TableView

    } // ColumnLayout

} // Rectangle table

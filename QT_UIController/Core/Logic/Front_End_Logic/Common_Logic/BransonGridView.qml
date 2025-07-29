/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import Style 1.0
Item {
    property alias gridViewModel: gridView.model
    property alias gridViewDelegate: gridView.delegate
    property alias gridViewCellHeight: gridView.cellHeight
    property alias gridViewCellWidth: gridView.cellWidth
    Rectangle {
        id: gridParentFrame
        anchors.fill: parent
        clip: true
        color: Style.backgroundColor
        Flickable {
            anchors.fill: parent
            ScrollBar.vertical: ScrollBar {}
            contentHeight: parent.height
            contentWidth: parent.width
            GridView
            {
                id: gridView
                anchors.fill: parent
                layoutDirection: Qt.LeftToRight
                cellHeight: Math.round(parent.height / 1.3)
//                cellWidth: (Style.scaleHint === 1.0) ? parent.width / 3 : parent.width / 4
                cellWidth: parent.width / 3
                cacheBuffer: 0
            }
        }
    }
}

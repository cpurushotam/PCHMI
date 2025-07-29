/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanCycleDetailsList.qml file displays scan cycle related data : cycle counts,
    date and time.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 03/04/2024 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Recipe_Screens"
import "./../Common_Logic"

Item
{

    id: scanDetailListsWindowItem

    property int    selectedIndex
    property bool   updateFlag                          : true

    signal scanCycleDetailsListDataChanged()

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_HORN_CYCLE_DETAILS_LIST, qmlTextArray)
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
        updateLanguage()
        ScanCycleDetailsListModel.loadCycleDetailsList()
        selectedIndex = 0
    }

    Connections
    {
        target: ScanCycleDetailsListModel

        function onScanCycleDetailsListDataChanged()
        {
            ScanCycleDetailsListModel.loadCycleDetailsList()
        }
    }

    ListView
    {
        id: scanCycleDetailsListView
        width: parent.width
        height: Math.round(365 * Style.scaleHint)
        spacing: Math.round(0 * Style.scaleHint)
        model: ScanCycleDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCountChanged:
        {
        }

        delegate: Rectangle
        {
            id: cycleDetailsInfo
            width: scanCycleDetailsListView.width
            height: (38 * Style.scaleHint)
            color: (scanCycleDetailsListView.currentIndex === index) ? Style.activeFrameBorderColor : Style.backgroundColor

            Text
            {
                id: cycleIndexNoText
                anchors.top: parent.top
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: model.CycleIndex
                font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                font.bold: true
                color: (scanCycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
            }           

            Text
            {
                id: cycleDateTimeText
                anchors.top: cycleIndexNoText.bottom
                anchors.topMargin: Math.round(3 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: model.CycleDateTime
                font.pixelSize: Math.round(8 * Style.scaleHint)
                color: (scanCycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
            }

            MouseArea
            {
                id: cycleDetailsInfoMouseArea
                anchors.fill:parent
                onClicked:
                {
                    scanCycleDetailsListView.currentIndex = index
                    selectedIndex = index
                    ScanGraphData.requestSelectedCycleNo(model.CycleIndex)
                    ScanCycleDetailsListModel.getResonantFrequencies(index)
                }
            }
        }
    }
}

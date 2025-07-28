/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailsList.qml file displays cycle related data : cycle counts,
    date and time.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 11/10/2023 - Initial version.
***************************************************************************/
import QtQuick 2.0
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Recipe_Screens"
import "./../Common_Logic"

Item
{

    id: analyticsCardWindowItem

    property string qmltextSearchByCycleNo              : "Search By Cycle No"
    property int    selectedIndex
    property bool   updateFlag                          : true
    property int    selectedReferenceGraphIndex         : -1
    property string    selectedCycleNo
    property string    qmltextAlreadyExists             : "Selected Weld Cycle Already Marked"
    property string    qmltextAlreadyExists1             : "As A Reference Graph"
    property string    qmltextAlert                     : "Alert"

    property var qmlTextArray: [qmltextSearchByCycleNo, qmltextAlreadyExists, qmltextAlert, qmltextAlreadyExists1]
    signal cycleDetailsListDataChanged()
    property var weldResultIndex: []

    QtObject
    {
        id: textEnum
        readonly property int searchByCycleNoIdx         : 0
        readonly property int alreadyExistsIdx           : 1
        readonly property int alertIdx                   : 2
        readonly property int alreadyExists1Idx          : 3
    }

    QtObject
    {
        id: refGraphOperationEnum
        readonly property int setRefGraph               : 1
        readonly property int replaceRefGraph           : 2
        readonly property int successRefGraph           : 3
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW_CYCLE_DETAILS_LIST, qmlTextArray)
        qmltextSearchByCycleNo = qmlTextArray[textEnum.searchByCycleNoIdx]
        qmltextAlreadyExists   = qmlTextArray[textEnum.alreadyExistsIdx]
        qmltextAlert           = qmlTextArray[textEnum.alertIdx]
        qmltextAlreadyExists1  = qmlTextArray[textEnum.alreadyExists1Idx]
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
        ReferenceWeldGraphData.refereshRefGraphList()
        updateLanguage()
        CycleDetailsListModel.loadCycleDetailsList()
        selectedIndex = 0

    }

    Connections
    {
        target: ReferenceWeldGraphData

        function onReferenceGraphDataChanged()
        {
            weldResultIndex = []
            var size = ReferenceWeldGraphData.availableReferenceGraphSize()

            for (var i = 0; i < size; i++)
            {
                var Index = ReferenceWeldGraphData.refweldResultIndex(i)
                weldResultIndex.push(Index)
            }

            CycleDetailsListModel.loadCycleDetailsList()
        }
    }

    Connections
    {
        target: ReferenceWeldGraphData

        function onReplaceGraphSuccessfully()
        {
            mainWindow.showReferenceGraphPopup(refGraphOperationEnum.successRefGraph,-1,selectedCycleNo)
        }
    }

    Connections
    {
        target: CycleDetailsListModel

        function onCycleDetailsListDataChanged()
        {
            CycleDetailsListModel.loadCycleDetailsList()
            /*To avoid auto refresh of weld historical data*/
            if(! CycleDetailsListModel.isAutoRefreshGraph())
            {
                cycleDetailsListView.currentIndex = selectedIndex
            }
            /*When the list data is changed, then update the current Recipe No and Recipe version
            by emitting the signal.*/
            CycleDetailsListModel.updateCurrentIndex(selectedIndex)
        }
    }

    function isRefGraphAvailable(idx)
    {
        return weldResultIndex.indexOf(idx) !== -1;
    }

    BransonLineEdit
    {
        id: searchCycleNo
        anchors.left: parent.left
        width: parent.width * 0.80
        placeholderText: qmltextSearchByCycleNo
        font.pixelSize: Math.round(8 * Style.scaleHint)
        focus: true
        text: (CycleDetailsListModel.SearchByCycleNo !== -1) ? CycleDetailsListModel.SearchByCycleNo : ""
        background: Rectangle
        {
            color: "#FFFFFF"
            radius: width/2
            border.color: "#707070"
            border.width: 1
        }

        MouseArea
        {
            id: searchCycleNoMouseArea
            anchors.fill: parent
            onClicked:
            {
                mainWindow.showPrimaryNumpad(qmltextSearchByCycleNo.toUpperCase(), "", 0, 10, 100, "0")
            }
        }
    }
    Image
    {
        id: refgraphImage
        source: "qrc:/Images/add_ref_graph_icon.svg"
        width: Math.round(25 * Style.scaleHint)
        height: searchCycleNo.height
        anchors.left: searchCycleNo.right
        anchors.leftMargin: searchCycleNo.width *0.08
        sourceSize.width: graphImage.width*3
        sourceSize.height: searchCycleNo.height
        smooth: true

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                if((DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                {
                    if(! isRefGraphAvailable (CycleDetailsListModel.getWeldResultIndex(cycleDetailsListView.currentIndex)))
                    {
                        if(ReferenceWeldGraphData.availableReferenceGraphSize() < 3)
                        {
                            mainWindow.showReferenceGraphPopup(refGraphOperationEnum.setRefGraph, selectedReferenceGraphIndex, "")
                        }

                        else if(ReferenceWeldGraphData.availableReferenceGraphSize() === 3)
                        {
                            mainWindow.showReferenceGraphPopup(refGraphOperationEnum.replaceRefGraph,selectedReferenceGraphIndex, "")
                        }
                    }

                    else
                    {
                        mainWindow.showBransonPopup(qmltextAlreadyExists + "\n" + qmltextAlreadyExists1, qmltextAlert)
                    }
                }
            }
        }
    }

    ListView
    {
        id: cycleDetailsListView
        width: parent.width
        height: Math.round(330 * Style.scaleHint)
        anchors.top: searchCycleNo.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        spacing: Math.round(0 * Style.scaleHint)
        model: CycleDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCountChanged:
        {
            /*To avoid auto refresh of weld historical data*/
            if(! CycleDetailsListModel.isAutoRefreshGraph())
            {
                cycleDetailsListView.currentIndex = selectedIndex + 1
                selectedIndex++
            }

            /*To reset the index as auto graph refresh status changed*/
            else
            {
               selectedIndex = 0
            }
        }

        delegate: Rectangle
        {
            id: cycleDetailsInfo
            width: cycleDetailsListView.width
            height: 50
            color: (cycleDetailsListView.currentIndex === index) ? Style.activeFrameBorderColor : Style.backgroundColor

            Image
            {
                id: refGraphSelStar
                source: "qrc:/Images/star_icon.svg"
                width: Math.round(11 * Style.scaleHint)
                height: Math.round(11 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin:  parent.width*0.05
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.25
                sourceSize.width: graphImage.width
                sourceSize.height: graphImage.height
                smooth: true
                visible: isRefGraphAvailable(model.CycleWeldResultIndex)

            }
            Row
            {
                id: cycleDetailsRow
                anchors.top: parent.top
                anchors.topMargin: Math.round(0 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Math.round(1 * Style.scaleHint)

                Text
                {
                    id: cycleRecipeNoText
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(5 * Style.scaleHint)
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: model.CycleRecipeNo
                    font.pixelSize: Math.round(8 * Style.scaleHint)
                    font.bold: true
                    color: (cycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
                }

                Text
                {
                    id: cycleNoText
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(5 * Style.scaleHint)
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: " : Cycle " + model.CycleNo
                    font.pixelSize: Math.round(8 * Style.scaleHint)
                    font.bold: true
                    color: (cycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
                }

                Text
                {
                    id: recipeModeText
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(5 * Style.scaleHint)
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: mainWindow.getWeldModeText(model.CycleWeldMode)
                    font.pixelSize: Math.round(8 * Style.scaleHint)
                    font.bold: true
                    color: (cycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
                }
            }

            Text
            {
                id: cycleDateTimeText
                anchors.top: cycleDetailsRow.bottom
                anchors.topMargin: Math.round(8 * Style.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: model.CycleDateTime
                font.pixelSize: Math.round(7 * Style.scaleHint)
                color: (cycleDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"
            }

            MouseArea
            {
                id: cycleDetailsInfoMouseArea
                anchors.fill:parent
                onClicked:
                {
                    cycleDetailsListView.currentIndex = index
                    selectedIndex = index
                    WeldGraphObj.requestSelectedCycleNo(model.CycleIndex)
                    selectedReferenceGraphIndex = model.CycleWeldResultIndex
                    selectedCycleNo = "Cycle " + model.CycleNo
                    CycleDetailsListModel.updateTriggerPoint(model.CycleTriggerPoint)
                    CycleDetailsListModel.updateWeldSonicPoint(model.CycleWeldSonicPoint)
                    CycleDetailsListModel.updateHoldPoint(model.CycleHoldPoint)
                    CycleDetailsListModel.updateCurrentIndex(cycleDetailsListView.currentIndex)
                }
            }
        }
    }


}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the Eventlog table .

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
import QtQuick.Layouts 1.15
import Com.Branson.GraphAxisEnum 1.0
import "./../Diagnostics_Screens"
import "./../Common_Logic"

Item
{
    id:eventlog
    property string qmltextMenuName          : "Event Log"
    property string qmltextEventLog          : "Event Log : "
    property string qmltextMoreInfo          : "More Info"
    property string qmlTextEvent             : "Event #"
    property string qmlTextEventName         : "Event Name"
    property string qmltextDateAndTime       : "Date & Time"
    property string qmlTextEventId           : "Event ID"
    property string qmlTextIdentifier        : "Identifier"
    property string qmlTextFrom              : "From"
    property string qmlTextTo                : "To"
    property string qmlTextPSSerial          : "P/S Serial #"
    property string qmlTextActSerial         : "Act Serial #"
    property string qmlTextHMISerial         : "HMI Serial #"
    property string qmlTextComments          : "Comments"
    property string qmlTextSourceEvent       : "Source"
    property string qmlTextUser              : "User"
    property int    selectedIndex
    property string qmltextdateTime          : ""


    property var qmlTextArray: [qmltextEventLog,qmltextMoreInfo,qmltextMenuName,qmlTextEvent
                                ,qmlTextEventName,qmltextDateAndTime,qmlTextEventId ,qmlTextIdentifier,qmlTextFrom
                                ,qmlTextTo
                                ,qmlTextPSSerial ,qmlTextActSerial,qmlTextHMISerial,qmlTextComments,qmlTextSourceEvent,qmlTextUser]

    property var columnWidths: []

    function calculateColumnWidths()
    {
        // 13 columns, order must match header and delegate
        let headers = [
            qmlTextEvent, qmltextDateAndTime, qmlTextEventName, qmlTextUser, qmlTextEventId,
            qmlTextIdentifier, qmlTextFrom, qmlTextTo, qmlTextPSSerial, qmlTextActSerial,
            qmlTextHMISerial, qmlTextComments, qmlTextSourceEvent
        ]
        let widths = new Array(headers.length).fill(0)
        // Calculate header widths
        for (let i = 0; i < headers.length; ++i)
        {
            let headerText = headers[i]
            let headerMetrics = Qt.createQmlObject('import QtQuick 2.15; TextMetrics { text: "' + headerText + '"; font.pixelSize: 14 }', eventlog)

            // Update the width for the column if the header is wider than the current value
            widths[i] = Math.max(widths[i], headerMetrics.width + 20)
            headerMetrics.destroy()
        }
        // Calculate data widths
        let rowCount = EventLogDetailsListModel.rowCount() || 0
        for (let i = 0; i < rowCount; ++i)
        {
            // Get the data for the current row
            let row = EventLogDetailsListModel.get(i)

            let values = [
                row.EventIdxId, row.DateTime, row.EventName, row.UserName, row.EventId,
                row.ParameterId, row.OldParams, row.NewParams, row.PSSerialNo, row.ACSerialNo,
                row.HMISerialNo, row.Comment, row.SourceOfEvent
            ]
            for (let j = 0; j < values.length; ++j)
            {
                let text = values[j] || ""
                // Create a temporary TextMetrics object to measure the width of the text
                let metrics = Qt.createQmlObject('import QtQuick 2.15; TextMetrics { text: "' + text + '"; font.pixelSize: 14 }', eventlog)
                // Update the width if this text is wider than the current max
                widths[j] = Math.max(widths[j], metrics.width + 20)
                metrics.destroy()
            }
        }
        columnWidths = widths
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS_EVENT, qmlTextArray)
        qmltextEventLog = qmlTextArray[textEnum.textEventLogIdx]
        qmltextMoreInfo = qmlTextArray[textEnum.textMoreInfoIdx]
        qmltextDateAndTime=qmlTextArray[textEnum.textDateTimeIdx]
        qmlTextEvent      = qmlTextArray[textEnum.textEventIdx]
        qmlTextEventName  = qmlTextArray[textEnum.textEventNameIdx]
        qmlTextEventId    = qmlTextArray[textEnum.textEventIdIdx]
        qmlTextIdentifier = qmlTextArray[textEnum.textIdentifierIdx]
        qmlTextFrom       = qmlTextArray[textEnum.textFromIdx]
        qmlTextTo         = qmlTextArray[textEnum.textToIdx]
        qmlTextPSSerial   = qmlTextArray[textEnum.textPSSerialIdx]
        qmlTextActSerial  = qmlTextArray[textEnum.textActSerialIdx]
        qmlTextHMISerial  = qmlTextArray[textEnum.textHMISerialIdx]
        qmlTextComments   = qmlTextArray[textEnum.textCommentsIdx]
        qmlTextSourceEvent= qmlTextArray[textEnum.textSourceEventIdx]
        qmlTextUser= qmlTextArray[textEnum.textDateUserIdx]

        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS_EVENT, qmltextMenuName)
        calculateColumnWidths()
    }

    QtObject
    {
        id: textEnum
        readonly property int textEventLogIdx            : 0
        readonly property int textMoreInfoIdx            : 1
        readonly property int textEventIdx               :2
        readonly property int textEventNameIdx           :3
        readonly property int textEventIdIdx             :4
        readonly property int textIdentifierIdx          :5
        readonly property int textFromIdx                :6
        readonly property int textToIdx                  :7
        readonly property int textPSSerialIdx            :8
        readonly property int textActSerialIdx           :9
        readonly property int textHMISerialIdx           :10
        readonly property int textCommentsIdx            :11
        readonly property int textSourceEventIdx         :12
        readonly property int textDateTimeIdx            :13
        readonly property int textDateUserIdx            :14

    }
    QtObject
    {
        id: columnDataEnum
        readonly property int colEventIdxId         : 0
        readonly property int colDateTime           : 1
        readonly property int colEventName          :2
        readonly property int colUserName           :3
        readonly property int colEventId            :4
        readonly property int colParameterId        :5
        readonly property int colOldParams          :6
        readonly property int colNewParams          :7
        readonly property int colPSSerialNo         :8
        readonly property int colACSerialNo         :9
        readonly property int colHMISerialNo        :10
        readonly property int colComment            :11
        readonly property int colSourceOfEvent      :12
    }
    Component.onCompleted:
    {
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTICS_EVENT)
            /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS_EVENT
        eventDateTimeText.text = EventLogDetailsListModel.loadLastEventLogDateTime()
        selectedIndex = 0
        calculateColumnWidths()
    }

    Connections
    {
        target: EventLogDetailsListModel

        function onLastEvent()
        {
           eventDateTimeText.text = EventLogDetailsListModel.loadLastEventLogDateTime()
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


    Connections
    {
        target: EventLogDetailsListModel

        function onEventDetailsListDataChanged()
        {
            EventLogDetailsListModel.loadEventDetailsList()
            EventLogDetailsListModel.currentIndex = selectedIndex
            calculateColumnWidths()
        }
    }

    Rectangle
    {
        id: backgroundRect
        anchors.fill: parent
        color: Style.backgroundColor
    }

    Text
    {
        id: eventText
        text: qmltextEventLog
        anchors.left: parent.left
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(15 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
        font.family: Style.regular.name
        color: Style.blackFontColor
    }
    Text
    {
        id: eventDateTimeText
        text: qmltextdateTime
        anchors.left: eventText.right
        anchors.leftMargin:  Math.round(5 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(17 * Style.scaleHint)
        font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
        font.family: Style.regular.name
        color: Style.blackFontColor
    }

    Flickable {
        id: flickable
        anchors.top: eventText.bottom
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.01
        contentWidth: columnWidths.reduce((a, b) => a + b, 0)
        contentHeight: eventLogDetailsListView.contentHeight
        clip: true
        interactive: true
        flickableDirection: Flickable.HorizontalAndVerticalFlick


    Row{
        id: columnNameRow
        width: flickable.width
        height: eventlog.height*0.08
        anchors.top: eventText.bottom
        anchors.topMargin: parent.height *0.05
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            width: columnWidths[columnDataEnum.colEventIdxId]  || parent.width * 0.05
            height: parent.height
            color: "transparent"
            border.color: "black"
            Text { anchors.centerIn: parent; text: qmlTextEvent; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colDateTime]  || parent.width*(1.7/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmltextDateAndTime; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colEventName]  || parent.width*(2/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextEventName; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colUserName]  || parent.width*0.08
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextUser; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colEventId]  || parent.width *0.05
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextEventId; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colParameterId]  || parent.width*0.1
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextIdentifier; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colOldParams]  || parent.width/20
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextFrom; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colNewParams]  || parent.width/20
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextTo; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colPSSerialNo]  || parent.width*(1.7/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextPSSerial; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colACSerialNo]  || parent.width*(1.7/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextActSerial; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colHMISerialNo] || parent.width*(1.7/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextHMISerial; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colComment] || parent.width*(1.7/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextComments; font.bold: true }
        }
        Rectangle {
            width: columnWidths[columnDataEnum.colSourceOfEvent] || parent.width*(2/20)
            height: parent.height
            color: "transparent"
            border.color: "black"

            Text { anchors.centerIn: parent; text: qmlTextSourceEvent; font.bold: true }
        }
    }

        ListView {
            id: eventLogDetailsListView
            width: flickable.contentWidth
            height: flickable.height
            model: EventLogDetailsListModel

            anchors.top: columnNameRow.bottom
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { }
            clip: true
            verticalLayoutDirection : ListView.TopToBottom

            delegate: Rectangle
            {
                id: cycleDetailsInfo
                width: eventLogDetailsListView.width
                height: columnNameRow.height
                color:(eventLogDetailsListView.currentIndex === index) ? Style.activeFrameBorderColor : Style.backgroundColor
                border.color:"#0f0f0f"

                Row {
                    anchors.fill: parent
                    spacing: 0

                    Rectangle {
                        width: columnWidths[columnDataEnum.colEventIdxId]  || parent.width * 0.05  //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.EventIdxId;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"}
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colDateTime]  || parent.width*(1.7/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.DateTime ;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"}
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colEventName]  || parent.width*(2/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.EventName;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colUserName]  || parent.width*0.08 //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.UserName;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colEventId]  || parent.width *0.05 //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.EventId;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colParameterId]  || parent.width*0.1 //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.ParameterId; color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colOldParams]  || parent.width/20 //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.OldParams;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000"}
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colNewParams]  || parent.width/20 //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.NewParams;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colPSSerialNo]  || parent.width*(1.7/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.PSSerialNo;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colACSerialNo]  || parent.width*(1.7/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.ACSerialNo;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colHMISerialNo] || parent.width*(1.7/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.HMISerialNo;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colComment] || parent.width*(1.7/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.Comment; color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                    Rectangle {
                        width: columnWidths[columnDataEnum.colSourceOfEvent] || parent.width*(2/20) //Assign maximum width to rectangle if text present else default width to column rectangle.
                        height: parent.height
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: model.SourceOfEvent;  color: (eventLogDetailsListView.currentIndex === index) ? "#FFFFFF" : "#000000" }
                    }
                }
                MouseArea
                {
                    id: cycleDetailsInfoMouseArea
                    anchors.fill:parent
                    onClicked:
                    {
                        eventLogDetailsListView.currentIndex = index
                        selectedIndex = index
                        eventDateTimeText.text = model.DateTime
                        qmltextdateTime = model.DateTime
                        EventLogDetailsListModel.selectedRowDataDisplay(index)
                    }
                }
            }
        }

        ScrollBar.horizontal: ScrollBar { }
    }
}

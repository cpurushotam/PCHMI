/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

  AnalyticsResultTable.qml - Creates the creates the structure for Tableview and other components.

 **********************************************************************************************************/
import QtQuick 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import "./../Common_Logic"
import Qt.labs.qmlmodels
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import QtQuick.Layouts 1.12
import Com.Branson.LoginIndexEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Item {

    property string qmltextResult                           : "Result"
    property string qmltextGenerateReport                   : "Generate Report"
    property string qmltextChooseParameters                 : "Choose Parameters"

    signal tableViewListDataChanged()
    signal updateParmeterView()

    property var qmlTextArray: [qmltextResult, qmltextGenerateReport, qmltextChooseParameters ]

    QtObject
    {
        id: textEnum
        readonly property int resultIdx                  : 0
        readonly property int generateReportIdx          : 1
        readonly property int chooseParametersIdx        : 2
    }

    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL? true: false

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_TABLE_VIEW, qmlTextArray)
        qmltextResult     = qmlTextArray[textEnum.resultIdx]
        qmltextGenerateReport = qmlTextArray[textEnum.generateReportIdx]
        qmltextChooseParameters= qmlTextArray[textEnum.chooseParametersIdx]
    }

    Connections
    {
        target: CycleDetailtablemodel
        function onTableViewListDataChanged()
        {
            CycleDetailtablemodel.loadTableViewDetailsList();
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
    InputPanel
    {
        id: inputPanelLoginKeyBoard
        z: 1
        x: 0
        y: mainWindow.showHeight * 0.85
        height:mainWindow.showHeight * 0.15
        width: mainWindow.showWidth
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible
    }
    Component.onCompleted:
    {
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.ANALYTICS
        updateLanguage()
        updateParmeterView.connect(chooseParametersView.createCheckBoxModel)
        chooseParametersView.createCheckBoxModel();
        /*This function copies current weld result data from CycleDetailTableModel class to AnalyticsResultTableModel class.
        This data is required to get weldResultData to filter the cycle counter for searching the data on table.*/
        AnalyticsScreenTableViewOptions.getWeldResultList(CycleDetailtablemodel.sendWeldResultList())
    }

    Rectangle
    {
        id: chartViewHeader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width
        height: parent.height
        color: Style.backgroundColor

        Text
        {
            id: resultText
            text:qmltextResult
            anchors.left: parent.left
            anchors.leftMargin:  Math.round(5 * Style.scaleHint)
            anchors.top: parent.top
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
            font.family: Style.regular.name
            color: Style.blackFontColor
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
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    mainWindow.menuParentOptionSelect(UIScreenEnum.GENERATEREPORT)
                }
            }
        }
        Rectangle{
            id:searchRect
            x: Math.round(700 * Style.scaleHint)
            y: Math.round(30 * Style.scaleHint)
            width: Math.round(25 * Style.scaleHint)
            height:Math.round(20 * Style.scaleHint)
            BransonLineEdit{
                id:genreportLineEdit
                anchors.leftMargin : Math.round(400 * Style.scaleHint)
                anchors.rightMargin: Math.round(25 * Style.scaleHint)
                focus: true
                width: Math.round(125 * Style.scaleHint)
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectWords
                onFocusChanged:{
                    if(focus){
                        Qt.inputMethod.show()
                    }else{
                        Qt.inputMethod.hide()
                    }
                }
                onTextChanged:{
                    AnalyticsScreenTableViewOptions.getSearchData(genreportLineEdit.text)
                }
                Image {
                    id: searchImage
                    source: "qrc:/Images/Icon_search.svg"
                    width: Math.round(20 * Style.scaleHint)
                    height: Math.round(20 * Style.scaleHint)
                    x:Math.round(100 * Style.scaleHint)
                    y: Math.round(5 * Style.scaleHint)
                    smooth: true
                }
            }
        }
        Rectangle
        {
            id: chooseParametersButton
            width: Math.round(170 * Style.scaleHint)
            height: Math.round(25 * Style.scaleHint)
            anchors.top: generateReportButton.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(5 * Style.scaleHint)
            color: Style.backgroundColor
            Text
            {
                id: chooseParametersText
                text:qmltextChooseParameters
                anchors.left: parent.left
                font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.blackFontColor
            }
            Image {
                id: chooseParametersImage
                source: "qrc:/Images/Graph.svg"
                width: Math.round(15 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                anchors.left: chooseParametersText.right
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                sourceSize.width: chooseParametersButton.height
                sourceSize.height: chooseParametersButton.height
                smooth: true
            }
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    // CycleDetailtablemodel.checkTheActutorType()
                    updateParmeterView();
                    mainWindow.showChooseParametersView()
                }
            }
        }
        Row
        {
            id: btnArray
            anchors.top: resultText.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(6 * Style.scaleHint)
            width: Math.round(92 * Style.scaleHint)
            height: Math.round(25 * Style.scaleHint)
            spacing: Math.round(2 * Style.scaleHint)
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
                        graphBtn.border.color="#6699cc"
                        recordsBtn.border.color="#9fa1a4"
                        mainWindow.menuChildOptionSelect(UIScreenEnum.ANALYTICS, UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW)
                    }
                }
            }

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
                        recordsBtn.border.color="#6699cc"
                        graphBtn.border.color="#9fa1a4"
                    }
                }
            }
        }
        ColumnsTableView{
            id: resultTable
            width:chartViewHeader.width- Math.round(125 * Style.scaleHint)
            height: parent.height - (25 * Style.scaleHint)
            clip: true
            anchors.left: parent.left
            anchors.top:btnArray.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: Math.round(5 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(5 * Style.scaleHint)
            model: AnalyticsScreenTableViewOptions
            columnWidths: []
            color:"#fcfcfa"
        }
    }
}

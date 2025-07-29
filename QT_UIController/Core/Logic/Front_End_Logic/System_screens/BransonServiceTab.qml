/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

Branson Service Tab Screen

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
import "./../System_screens"

Item {
    id: bransonSystemConfItem
    property string qmltextFactoryReset: "Factory Reset"
    property string qmltextCopyToDb: "Copy DB to USB"
    property string qmltextDeleteDb: "Delete DB"
    property string qmltextEmmcMemUsage: "EMMC Memory Usage"
    property string qmltextBoardReplaced: "Board Replaced"
    property string qmltextSystemCleaned: "System Cleaned"
    property string qmltextNotes: "Notes"
    property string qmltextNotesHistory: "Notes History"
    property string qmltextSave: "Save"
    property string qmltextReset: "RESET"
    property string qmltextDelete: "DELETE"
    property string qmltextCopy: "COPY"
    property string qmltextBoard: "BOARD REPLACED"
    property string qmltextSystem: "SYSTEM CLEANED"
    property string qmltextEnterNote: "Enter your Notes here..."

    property string note: ""
    property int emmcUsgae : -1
    property bool isFactoryResetCompleted : true

    property int inputlimit: BransonServiceInterface.maxNotesChars()

    property var qmlTextArray: [qmltextFactoryReset, qmltextCopyToDb, qmltextDeleteDb, qmltextEmmcMemUsage, qmltextBoardReplaced, qmltextSystemCleaned, qmltextNotes,
        qmltextNotesHistory, qmltextSave, qmltextReset, qmltextDelete, qmltextCopy, qmltextBoard, qmltextSystem, qmltextEnterNote]

    QtObject
    {
        id: errorCodesEnum
        readonly property int textFactoryResetProgress: 1
        readonly property int textFactoryResetSUccess: 2
    }

    QtObject
    {
        id: textEnum
        readonly property int textFactoryResetIdx: 0
        readonly property int textCopyToDbIdx: 1
        readonly property int textDeleteDbIdx: 2
        readonly property int textEmmcMemUsageIdx: 3
        readonly property int textBoardReplacedIdx: 4
        readonly property int textSystemCleanedIdx: 5
        readonly property int textNotesIdx: 6
        readonly property int textNotesHistoryIdx: 7
        readonly property int textSaveIdx: 8
        readonly property int textResetIdx: 9
        readonly property int textDeleteIdx: 10
        readonly property int textCopyIdx: 11
        readonly property int textBoardIdx: 12
        readonly property int textSystemIdx: 13
        readonly property int textEnterNoteIdx: 14
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.BRANSON_SERVICE_TAB, qmlTextArray)
        qmltextFactoryReset = qmlTextArray[textEnum.textFactoryResetIdx]
        qmltextCopyToDb = qmlTextArray[textEnum.textCopyToDbIdx]
        qmltextDeleteDb = qmlTextArray[textEnum.textDeleteDbIdx]
        qmltextEmmcMemUsage = qmlTextArray[textEnum.textEmmcMemUsageIdx]
        qmltextBoardReplaced = qmlTextArray[textEnum.textBoardReplacedIdx]
        qmltextSystemCleaned = qmlTextArray[textEnum.textSystemCleanedIdx]
        qmltextNotes = qmlTextArray[textEnum.textNotesIdx]
        qmltextNotesHistory = qmlTextArray[textEnum.textNotesHistoryIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextReset = qmlTextArray[textEnum.textResetIdx]
        qmltextDelete = qmlTextArray[textEnum.textDeleteIdx]
        qmltextCopy = qmlTextArray[textEnum.textCopyIdx]
        qmltextBoard = qmlTextArray[textEnum.textBoardIdx]
        qmltextSystem = qmlTextArray[textEnum.textSystemIdx]
        qmltextEnterNote = qmlTextArray[textEnum.textEnterNoteIdx]
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
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.BRANSON_SERVICE_TAB
        serviceModel.resetServiceModel()
        BransonServiceInterface.serviceTabLoaded()
        updateLanguage()
    }

    BransonPopup
    {
        id: systemPopUpMsg
        anchors.centerIn: mainWindow

        onOKButtonClicked:
        {
            systemPopUpMsg.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }
    }

    QtObject
    {
        id: servicebuttonEnum
        readonly property int factoryresetButton: 0
        readonly property int deleteButton: 1
        readonly property int copyButton: 2
        readonly property int boardButton: 3
        readonly property int systemcleanButton: 4
    }

    ListModel
    {
        id: serviceModel
        function resetServiceModel()
        {
            serviceModel.clear()
            serviceModel.append({
                "Name": qmltextFactoryReset,
                "ButtonName": qmltextReset,
                "EmmcVisible": false,
                "NotesVisible": false,
                "Oper": servicebuttonEnum.factoryresetButton
            })

            serviceModel.append({
                "Name": qmltextDeleteDb,
                "ButtonName": qmltextDelete,
                "EmmcVisible": false,
                "NotesVisible": false,
                "Oper": servicebuttonEnum.deleteButton
            })

            serviceModel.append({
                "Name": qmltextCopyToDb,
                "ButtonName": qmltextCopy,
                "EmmcVisible": false,
                "NotesVisible": false,
                "Oper": servicebuttonEnum.copyButton
            })

            serviceModel.append({
                "Name": qmltextEmmcMemUsage,
                "ButtonName": "",
                "EmmcVisible": true,
                "NotesVisible": false
            })

            serviceModel.append({
                "Name": qmltextBoardReplaced,
                "ButtonName": qmltextBoard,
                "EmmcVisible": false,
                "NotesVisible": false,
                "Oper": servicebuttonEnum.boardButton
            })

            serviceModel.append({
                "Name": qmltextSystemCleaned,
                "ButtonName": qmltextSystem,
                "EmmcVisible": false,
                "NotesVisible": false,
                "Oper": servicebuttonEnum.systemcleanButton
            })

            serviceModel.append({
                "Name": qmltextNotes,
                "ButtonName": "",
                "EmmcVisible": true,
                "NotesVisible": true
            })
        }
    }

    ListModel
    {
        id: serviceNotesListModel
    }

    Connections
    {
        target: BransonServiceInterface
        function onServicenoteChanged()
        {
            serviceNotesListModel.clear()
            for (var i = 0; i < BransonServiceInterface.getNofServiceNotes(); ++i) {
                var serviceNote = BransonServiceInterface.getServiceNote(i)
                var datetime = BransonServiceInterface.getServiceNoteDateTime(i)
                var itemText = datetime + " - " + serviceNote
                serviceNotesListModel.append({ "datetime": datetime, "serviceNote": serviceNote })
            }
        }

        function onBransonServiceStatusMessage()
        {
            systemPopUpMsg.modal = true
            var str = BransonServiceInterface.getServiceResponse()
            systemPopUpMsg.visible = true
            systemPopUpMsg.qmltextWarningDialog = str
            if(BransonServiceInterface.getServiceResponseCode()!== errorCodesEnum.textFactoryResetProgress)
            {
                isFactoryResetCompleted = true
                systemPopUpMsg.okButtonToClosePopup = true
            }

            else
            {
                isFactoryResetCompleted = false
                systemPopUpMsg.okButtonToClosePopup = false
            }
        }
    }

    InputPanel
    {
        id: inputPanelNotes
        z: 1
        x: 1
        y: mainWindow.showHeight * 0.85
        height: mainWindow.showHeight * 0.15
        anchors.left: mainWindow.left
        width: mainWindow.showWidth * 0.80
        anchors.bottom: parent.bottom
        visible: Qt.inputMethod.visible
    }

    MouseArea
    {
        id: fullScreenMouseArea
        anchors.fill: parent
        onClicked:
        {
            if (Qt.inputMethod.visible)
            {
                inputPanelNotes.focus = false
                Qt.inputMethod.hide()
            }
        }
    }

    Rectangle
    {
        id: listRect
        height: parent.height * 0.90
        width: mainWindow.showWidth * 0.30
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: mainWindow.width * 0.02
        clip: true
        color: "transparent"
        Flickable
        {
            id: loginFlick
            flickableDirection: Flickable.VerticalFlick
            width: parent.width
            height: parent.height * 2
            flickDeceleration: 10000
            contentHeight: true ? height * 3.4 : height * 1.9
            clip: true
            ListView
            {
                id: listView
                width: parent.width
                height: listRect.height
                anchors.top: parent.top
                anchors.topMargin: listRect.height * 0.02
                boundsBehavior: parent.height * 3
                model: serviceModel

                delegate: Item
                {
                    id: item1
                    width: parent.width
                    height: model.Name === qmltextNotes ? listView.height * 0.30 : listView.height * 0.20

                    Rectangle
                    {
                        id: mainRect
                        width: parent.width
                        height: parent.height * 0.90
                        color: "#F0F0F0"
                        Text
                        {
                            id: servicename
                            text: model.Name
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width * 0.06
                            anchors.top: parent.top
                            anchors.topMargin: model.EmmcVisible === true ? parent.height * 0.1 : parent.height * 0.35
                            font.pixelSize: model.Name === qmltextNotes ? parent.height * 0.15 : parent.height * 0.20
                        }

                        BransonPrimaryButton
                        {
                            id: servicebuttons
                            width: parent.width * 0.40
                            height: parent.height * 0.40
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.topMargin: parent.height * 0.35
                            anchors.leftMargin: parent.width * 0.60
                            anchors.right: parent.right
                            anchors.rightMargin: parent.width * 0.1
                            text: model.ButtonName
                            buttonColor: "#17345C"
                            fontSize: servicebuttons.height * 0.35
                            visible: !model.EmmcVisible
                            enabled: isFactoryResetCompleted
                            onClicked:
                            {
                                // ADD CASES FOR EACH BUTTON OPERATION.
                                if (model.Oper === servicebuttonEnum.factoryresetButton)
                                {
                                    BransonServiceInterface.factoryResetRequest()
                                }

                                if (model.Oper === servicebuttonEnum.deleteButton)
                                {
                                    BransonServiceInterface.dbDeleteRequest()
                                }

                                if (model.Oper === servicebuttonEnum.copyButton)
                                {
                                    BransonServiceInterface.copyDbFilesToUSBRequest()
                                }

                                if (model.Oper === servicebuttonEnum.boardButton)
                                {
                                    mainWindow.showBransonService()
                                }

                                if (model.Oper === servicebuttonEnum.systemcleanButton)
                                {
                                    BransonServiceInterface.systemCleanedRequest()
                                }
                            }
                        }

                        TextField
                        {
                            id: emmcTxtField
                            width: parent.width * 0.90
                            height: parent.height * 0.4
                            anchors.top: servicename.bottom
                            anchors.topMargin: parent.height * 0.15
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width * 0.05
                            anchors.right: parent.right
                            anchors.rightMargin: parent.width * 0.05
                            text: BransonServiceInterface.emmcMemUsage
                            visible: model.Name === qmltextNotes ? false : model.EmmcVisible
                            enabled: false
                        }

                        Rectangle
                        {
                            width: parent.width * 0.90
                            height: parent.height * 0.5
                            anchors.top: servicename.bottom
                            anchors.topMargin: parent.height * 0.1
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width * 0.05
                            anchors.right: parent.right
                            anchors.rightMargin: parent.width * 0.05
                            visible: model.NotesVisible
                            enabled: model.NotesVisible
                            TextField
                            {
                                id: textlinenote
                                anchors.fill: parent
                                clip: true
                                focus: true
                                selectByMouse: true
                                mouseSelectionMode: TextInput.SelectWords
                                placeholderText: "Enter your Notes here..."
                                wrapMode: TextEdit.Wrap
                                onTextChanged:
                                {
                                    note = textlinenote.text

                                    if (textlinenote.text.length > inputlimit)
                                    {
                                        textlinenote.text = textlinenote.text.substring(0, inputlimit)
                                    }
                                }

                                Text
                                {
                                    id: notentered
                                    color: "#E9ECEF"
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: Math.round(7 * Style.scaleHint)
                                    font.pixelSize: Math.round(11 * Style.scaleHint)
                                    font.family: Style.regular.name
                                }

                                onActiveFocusChanged:
                                {
                                    Qt.inputMethod.hide()
                                    if (activeFocus)
                                    {
                                        inputPanelNotes.visible = true
                                    }

                                    else
                                    {
                                        inputPanelNotes.visible = false
                                        inputPanelNotes.focus = false
                                    }
                                }
                            }
                        }
                    }

                    Rectangle
                    {
                        id: spacingRectangle
                        width: mainRect.width
                        height: parent.height * 0.15
                        anchors.top: mainRect.bottom
                        color: "white"
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: notesHistory
        width: parent.width
        height: parent.height * 0.09
        anchors.left: listRect.right
        anchors.leftMargin: mainWindow.width * 0.02
        color: "#d6cece"
        border.color: "black"
        border.width: 2
        Text
        {
            anchors.fill: parent
            font.pixelSize: parent.height * 0.5
            anchors.centerIn: parent
            text: qmltextNotesHistory
        }
    }

    Rectangle
    {
        id: notesHistory1
        height: parent.height * 0.80
        width: mainWindow.showWidth * 0.30
        anchors.top: notesHistory.bottom
        anchors.left: listRect.right
        anchors.leftMargin: mainWindow.width * 0.02
        clip: true
        color: "transparent"

        ListView
        {
            id: listView1
            width: parent.width
            height: parent.height
            anchors.top: parent.top
            boundsBehavior: Flickable.StopAtBounds
            model: serviceNotesListModel

            delegate: Rectangle
            {
                id: delegateBackground
                color: "#F0F0F0"
                radius: 10
                width: listView1.width
                height: contentContainer.height + grayline.height + 20

                Item
                {
                    id: contentContainer
                    width: parent.width - 20
                    height: column.height
                    anchors.centerIn: delegateBackground

                    RowLayout
                    {
                        id: row1
                        width: parent.width

                        ColumnLayout
                        {
                            id: column
                            Layout.fillWidth: true
                            spacing: 12

                            TextEdit
                            {
                                selectByMouse: true
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignTop
                                id: messageText
                                text: model.serviceNote
                                wrapMode: TextEdit.WordWrap
                                readOnly: true
                                font.pixelSize: notesHistory.height * 0.32 //16 // Increase the text size here
                            }

                            RowLayout
                            {
                                spacing: parent.width * 0.30
                                Label
                                {
                                    id: dateText
                                    text: model.datetime
                                    font.pointSize: notesHistory.height * 0.20
                                    color: "grey"
                                }
                            }
                        }
                    }
                }

                Rectangle
                {
                    id: grayline
                    width: listView1.width
                    height: 1
                    anchors.top: contentContainer.bottom
                    anchors.topMargin: notesHistory.height * 0.1
                    color: "black"
                }
            }
        }
    }

    BransonPrimaryButton
    {
        id: savebutton
        width: mainWindow.showWidth * 0.1
        height: parent.height * 0.08
        anchors.left: notesHistory1.left
        anchors.leftMargin: notesHistory1.width *0.60
        anchors.top: notesHistory1.bottom
        anchors.topMargin: parent.height * 0.05
        text: qmltextSave
        buttonColor: "#17345C"
        fontSize: savebutton.height * 0.70
		enabled: isFactoryResetCompleted
        onClicked:
        {
            if (note !== "")
            {
                BransonServiceInterface.serviceNotesDetailsRequest(note)
                inputPanelNotes.focus = false
                inputPanelNotes.visible = false
                note = ""
                textlinenote.text = ""
                notentered.text = ""
            }

            textlinenote.text = ""
        }
    }
}

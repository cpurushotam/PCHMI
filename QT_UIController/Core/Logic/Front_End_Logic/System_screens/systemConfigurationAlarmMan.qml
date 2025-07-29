/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 QML File to display AlarmManagement related components.

 **********************************************************************************************************/
import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import QtQuick.Window 2.2
import Style
import QtQuick.Window
import QtQuick.Controls
import QtQuick
import Com.Branson.UIScreenEnum 1.0
import QtQuick.VirtualKeyboard.Settings 2.15
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"
import CheckboxModel

Item {

    readonly property int qmlscreenIndicator:   UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT

     property string qmltextAlarmMangement :"Alarm Management"
     property string qmltextResetDefaults :"RESET TO DEFAULTS"
     property string qmltextSave :"SAVE"
     property string qmltextCancel :"CANCEL"
     property string qmltextSaveSuccessMsg : "Alarm configuration saved successfully"
     property string qmltextSaveFailedMsg : "Failed to save alarm configuration"
     property string  qmltextAlarmType : "Alarm Type"
    property string qmltextInvalidValueMsg : "Invalid value is entered, Reverted to old value"

    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property var qmlTextArray: [qmltextAlarmMangement,qmltextResetDefaults,qmltextSave,qmltextCancel,qmltextSaveSuccessMsg,qmltextSaveFailedMsg,qmltextAlarmType]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT, qmlTextArray)
        qmltextAlarmMangement = qmlTextArray[textEnum.alarmMgmtIdx]
        qmltextResetDefaults = qmlTextArray[textEnum.resetToDefIdx]
        qmltextSave = qmlTextArray[textEnum.saveIdx]
        qmltextCancel = qmlTextArray[textEnum.cancelIdx]
        qmltextSaveSuccessMsg = qmlTextArray[textEnum.saveSuccessIdx]
        qmltextSaveFailedMsg = qmlTextArray[textEnum.saveFailIdx]
        qmltextAlarmType =qmlTextArray[textEnum.alarmTypeIdx]
        qmltextInvalidValueMsg = qmlTextArray[textEnum.invalidValueMsgIdx]
    }

    QtObject {
        id: textEnum
        readonly property int alarmMgmtIdx:         0
        readonly property int resetToDefIdx:        1
        readonly property int saveIdx:              2
        readonly property int cancelIdx:            3
        readonly property int saveSuccessIdx:       4
        readonly property int saveFailIdx:          5
        readonly property int alarmTypeIdx:         6
        readonly property int invalidValueMsgIdx:   7
    }

    Connections
    {
        target: BoolStructModel
        /*On every change of Reset to default click display should get refresh*/
        function onLoadingDataChanged()
        {
            boolStructModel.IsLoading = false
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }
    Component.onCompleted: {
         updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }

    id:alarmconfiguration
    width: mainWindow.showWidth
    height: mainWindow.showHeight

    Rectangle
    {
        id:gridview3
        width: mainWindow.showWidth * 0.15
        height: mainWindow.showHeight
        anchors.top: parent.top
        anchors.left :parent.left
        anchors.leftMargin: mainWindow.showWidth * 0.20
        anchors.topMargin: mainWindow.showHeight * 0.05
        anchors.bottom: parent.bottom
        anchors.bottomMargin:  mainWindow.showHeight * 0.05
        color: "transparent"

        GridLayout {
            id: gridView2

            width: parent.width
            height: parent.height
            columns: 1
            rows: boolStructModel.numberofRows()
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
            Repeater
            {
                model:boolStructModel.rowNames
                Rectangle {
                    width: gridview3.width
                    height: gridview3.height*0.02
                    color:"transparent"
                    Text {
                        text: modelData
                        anchors.right: parent.right
                        anchors.rightMargin: parent.width *0.42
                        font.pixelSize: gridview3 .width *0.07
                    }
                }
            }
        }
    }

    Rectangle {
        id:alarmTypeRect
        width: gridView2.width *0.80
        height: gridview2.height *0.95
        anchors.bottom: gridview3.top
        anchors.left: gridview3.left
        color:"transparent"
        clip :true
        Text {
            id:txtalrmtype
            text: qmltextAlarmType
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.16
            anchors.top: parent.top
            anchors.topMargin: parent.height *0.10
            font.pixelSize: parent.height*0.40
            font.bold: true
        }
    }


    Rectangle {
        id:gridview2
        width:  gridview1.width
        height: mainWindow.showHeight*0.05
        anchors.top: parent.top
        anchors.left :parent.left
        anchors.leftMargin:mainWindow.showWidth* 0.32
        color: "transparent"

        GridLayout {
            id: gridViewcol

            width: parent.width
            height: parent.height
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
            Repeater
            {
                model: boolStructModel.colNames
                Rectangle {
                    id:colnamesRect
                    width: txtcol.width
                    height: gridview2.height*0.8
                    color:"transparent"
                    clip :true
                    Text {
                        id:txtcol
                        text: modelData
                        anchors.left: parent.left
                        font.pixelSize: colnamesRect.height*0.50
                        font.bold: true
                    }
                }
            }
        }
    }

    BoolStructModel
    {
        id: boolStructModel
    }

    Rectangle {
        id:gridview1
        width: mainWindow.showWidth * 0.60
        height: mainWindow.showHeight// *0.85
        anchors.top: parent.top
        anchors.left :gridview3.right
        anchors.topMargin: mainWindow.showHeight * 0.05
        anchors.bottom: parent.bottom
        anchors.bottomMargin:  mainWindow.showHeight * 0.05
        color:"transparent"
        GridLayout {
            id: gridLayout
            columns: 5
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true

            Repeater {
                id:repeaterModel
                model: boolStructModel// Number of checkboxes

                delegate: CheckBox {
                    id: checkBox
                    indicator.width: gridview3 .width *0.1
                    indicator.height: gridview3 .width *0.1
                    font.pixelSize: gridview3 .width *0.1
                    checked: model.value
                    onCheckedChanged: boolStructModel.setData(index, checked)
                }
            }
        }
    }

    Rectangle {
        id:gridviewbuttons
        width: mainWindow.showWidth * 0.90
        height: mainWindow.showHeight*0.06
        anchors.bottom: parent.bottom
        anchors.left :parent.left
        anchors.leftMargin: gridviewbuttons.width * 0.05
        color: "transparent"

        BransonPrimaryButton{
            id: resetToDefalutButton
            anchors.bottom: parent.bottom
            width:zoomingSize(115)
            implicitHeight:zoomingSize(25)
            fontSize: resetToDefalutButton.height*0.40
            text: qmltextResetDefaults
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            buttonColor: Style.cancelButtonTextColor
            onClicked: {
                boolStructModel.resetToDefault()
            }
        }

        BransonPrimaryButton
        {
            id: cancelButton
            anchors.left: parent.left
            anchors.leftMargin: mainWindow.width *0.60
            anchors.bottom: parent.bottom
            width:zoomingSize(100)
            implicitHeight:zoomingSize(25)
            fontSize: zoomingSize(Style.style4)
            text: qmltextCancel
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            buttonColor: Style.cancelButtonTextColor
            onClicked:
            {
                boolStructModel.cancelReqFromHMI()
            }
        }

        BransonPrimaryButton
        {
            id: saveButton
            anchors.left: parent.left
            anchors.leftMargin: mainWindow.width *0.75
            anchors.bottom: parent.bottom
            width:zoomingSize(100)
            implicitHeight:zoomingSize(25)
            fontSize: zoomingSize(Style.style4)
            text: qmltextSave
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            buttonColor: Style.buttonColor
            onClicked:
            {
                boolStructModel.save()
            }
        }
    }

    Rectangle
    {
        id: loadingPage
        visible: boolStructModel.IsLoading
        opacity: 0.5
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        color:"#000000"
        x: mainWindow.showWidth * 0.001
        y: mainWindow.showHeight *0.001
        Image
        {
            id: recipeLoadingIcon
            visible: boolStructModel.IsLoading
            x: mainWindow.showWidth * 0.45
            y: mainWindow.showHeight *0.25
            source: "qrc:/Images/Loading.png"
            height: imageSize * 5
            width: imageSize * 5
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeLoadingIcon.width
            sourceSize.height: recipeLoadingIcon.height
            smooth: true
        }
        RotationAnimator
        {
            target: recipeLoadingIcon
            from: 0
            to: 360
            duration: 1000
            running: true
        }
        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }
}



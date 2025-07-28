/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Footer of the application is use to dispaly active welder and other components.

 **********************************************************************************************************/
import QtQuick 2.0
import QtQml.Models 2.15
import Style 1.0
import QtQuick.Layouts
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

Item {
    // Properties declarations
    property string qmltextactivewelderName:        "Welder"
    property string qmltextnote:                    "Note: HMI is in Read -Only/Lock mode !"
    property string qmltextnoteReadOnly:                  "Note: HMI is in Read -Only mode !"
    property string qmltextnoteLocked:                    "Note: HMI is in Lock mode !"
    property string qmltextnoteFunctional:                "Note: HMI is in fully functional mode!"
    property string qmltextfieldbustoken:           "Fieldbus Token"
    property string qmltextethernetConn:            "Ethernet Connected"
    property string qmltextusbPluggedIn:            "USB Plugged-In"
    property string qmltextuNoWelder:               "No Welder"

    signal signalCurrentScreenIndexChanged(int screenIndex)

    property var qmlTextArray: [qmltextactivewelderName, qmltextnote, qmltextfieldbustoken, qmltextethernetConn,qmltextusbPluggedIn,qmltextuNoWelder, qmltextnoteReadOnly
    ,qmltextnoteLocked, qmltextnoteFunctional]

    visible: false //Remove this line to display footer.
    QtObject {
        id: textEnum
        readonly property int textactivewelderNameIdx:  0
        readonly property int textnoteIdx:              1
        readonly property int textfieldbustokenIdx:     2
        readonly property int textethernetConnIdx:      3
        readonly property int textusbPluggedInIdx:      4
        readonly property int textNoWelderIdx:          5
        readonly property int textnoteReadOnlyIdx:      6
        readonly property int textnoteLockedIdx:        7
        readonly property int textnoteFunctionalIdx:    8
    }

    function updateLanguage() {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.FOOTER, qmlTextArray)
        qmltextactivewelderName = qmlTextArray[textEnum.textactivewelderNameIdx]
        qmltextnote = qmlTextArray[textEnum.textnoteIdx]
        qmltextfieldbustoken = qmlTextArray[textEnum.textfieldbustokenIdx]
        qmltextethernetConn = qmlTextArray[textEnum.textethernetConnIdx]
        qmltextusbPluggedIn = qmlTextArray[textEnum.textusbPluggedInIdx]
        qmltextuNoWelder = qmlTextArray[textEnum.textNoWelderIdx]
        qmltextnoteReadOnly = qmlTextArray[textEnum.textnoteReadOnlyIdx]
        qmltextnoteLocked = qmlTextArray[textEnum.textnoteLockedIdx]
        qmltextnoteFunctional = qmlTextArray[textEnum.textnoteFunctionalIdx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged() {
            updateLanguage()
        }
    }

    Connections {
        target: leftMenuLoader.item
        function onActiveWelder(actv) {
            if (actv === -1) {
                activeWelderNameTxt.text = qmltextuNoWelder
            } else {
                activeWelderNameTxt.text = qmltextactivewelderName + " " + (actv+1)
            }
            fieldBusTokenRect.visible = SystemConfiguration.FieldBusSupportSystemType !== SystemTypeDef.FIELDBUS_NOT_SUPPORTED ? true : false
        }
    }

    Connections
    {
        target: leftMenuLoader.item
        function onWelderRenamed(name)
        {
            activeWelderNameTxt.text = name
            fieldBusTokenRect.visible = SystemConfiguration.FieldBusSupportSystemType !== SystemTypeDef.FIELDBUS_NOT_SUPPORTED ? true : false
        }
    }

    Connections{
        target: DisplayModesHMI
        function onCurrentDisplayModeChanged()
        {
            if(DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY)
            {
                noteTxt.text = qmltextnoteReadOnly
                fieldbustokenImg.source = "qrc:/Images/Readonly_icon.png"
            }
            else if(DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_LOCKED)
            {
                noteTxt.text = qmltextnoteLocked
                fieldbustokenImg.source = "qrc:/Images/Locked_icon.png"
            }
            else
            {
                noteTxt.text = qmltextnoteFunctional
                fieldbustokenImg.source = "qrc:/Images/Full_functional_icon.png"
            }
        }
    }

    Component.onCompleted: {     
        updateLanguage()
    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "#2D383F"
    }

    Item {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width

        Row {
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.03
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.25
            spacing: parent.width * 0.01
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: activeWelderNameTxt
                color: "#ffffff"
                text: qmltextuNoWelder
                font.pixelSize: parent.height * 0.55
            }

            Text {
                text: "|"
                color: "#ffffff"
                font.pixelSize: parent.height * 0.6
                visible: false //Remove this line after demo.
            }

            Rectangle {
                id: fieldBusTokenRect
                width: fieldbustokenTxt.width + fieldbustokenImg.width
                height: parent.height * 0.90
                color: "transparent"
                visible: false
                RowLayout {
                    id: fieldbusTknRow
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    visible: false //Remove this line after demo.

                    Image {
                        id: fieldbustokenImg
                        sourceSize.height: fieldBusTokenRect.height * 0.95
                        source: "qrc:/Images/Full_functional_icon.png"
                        smooth: true
                    }

                    Text {
                        id: fieldbustokenTxt
                        color: "#ffffff"
                        text: qmltextfieldbustoken
                        Layout.alignment: Qt.AlignVCenter
                        font.pixelSize: fieldbustokenImg.height * 0.90
                    }
                }
            }

            Text {
                text: "|"
                color: "#ffffff"
                font.pixelSize: parent.height * 0.6
                visible: false //Remove this line after demo.

            }

            Rectangle {
                id: ethernetConnRect
                width: ethernetConnTxt.width + ethernetConnImg.width
                height: parent.height * 0.90
                color: "transparent"
                visible: false //Remove this line after demo.

                RowLayout {
                    id: ethernetConnrow
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    Image {
                        id: ethernetConnImg
                        sourceSize.height: ethernetConnRect.height * 0.95
                        source: "qrc:/Images/RightMenu.svg"
                        smooth: true
                    }

                    Text {
                        id: ethernetConnTxt
                        color: "#ffffff"
                        text: qmltextethernetConn
                        Layout.alignment: Qt.AlignVCenter
                        font.pixelSize: ethernetConnImg.height * 0.60
                    }
                }
            }

            Text {
                text: "|"
                color: "#ffffff"
                font.pixelSize: parent.height * 0.6
                visible: false //Remove this line after demo.

            }

            Rectangle {
                id: usbPluggedRect
                width: usbPluggedInTxt.width + usbPluggedInImg.width
                height: parent.height * 0.90
                color: "transparent"
                visible: false //Remove this line after demo.

                RowLayout {
                    id: usbPluggedInrow
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    Image {
                        id: usbPluggedInImg
                        sourceSize.height: usbPluggedRect.height * 0.95
                        source: "qrc:/Images/RightMenu.svg"
                        smooth: true
                    }

                    Text {
                        id: usbPluggedInTxt
                        Layout.alignment: Qt.AlignVCenter
                        color: "#ffffff"
                        text: qmltextusbPluggedIn
                        font.pixelSize: usbPluggedInImg.height * 0.60
                    }
                }
            }
        }

        Text {
            id: noteTxt
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.02
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.25
            color: "#ffffff"
            text: qmltextnoteFunctional
            font.pixelSize: parent.height * 0.40
        }
    }
}

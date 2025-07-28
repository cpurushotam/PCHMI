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
import AxisDefine 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Rectangle
{
    signal leftAxisChanged(var index)
    signal rightAxisChanged(var index)
    property color rectleftcolor: "#000000"
    property color rectrightcolor: "#000000"
    property color fontColor: Style.blackFontColor
    property int titleFontSize: Math.round(Style.style3  * Style.scaleHint)
    property int valueFontSize: Math.round(Style.style4  * Style.scaleHint)
    property string qmltextLeftAxisTitle: qsTr("Left")
    property string qmltextRightAxisTitle: qsTr("Right")
    property string qmltextAxisTitle: qsTr("Axis")
    property var qmlTextArray: [qmltextLeftAxisTitle, qmltextRightAxisTitle, qmltextAxisTitle]
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    id: chartVeiwHeader
    width: 800
    height: 50
    color: "#FFFFFF"

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.ANALYTICS_RESULT_GRAPH_HEADER_SETTING, qmlTextArray)
        qmltextLeftAxisTitle = qmlTextArray[textEnum.leftAxisTitleIdx]
        qmltextRightAxisTitle = qmlTextArray[textEnum.rightAxisTitleIdx]
        qmltextAxisTitle = qmlTextArray[textEnum.axisTitleIdx]
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
    }

    QtObject {
        id: textEnum
        readonly property int leftAxisTitleIdx:  0
        readonly property int rightAxisTitleIdx: 1
        readonly property int axisTitleIdx: 2
    }

    Row
    {
        id: btnArray
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        width: Math.round(92 * Style.scaleHint)
        height: Math.round(45 * Style.scaleHint)
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
                width: Math.round(30 * Style.scaleHint)
                height: Math.round(30 * Style.scaleHint)
                anchors.centerIn: parent
                sourceSize.width: graphImage.width
                sourceSize.height: graphImage.height
                smooth: true
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    graphBtn.border.color="#6699cc"
                    recordsBtn.border.color="#9fa1a4"
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
                onClicked:
                {
                    recordsBtn.border.color="#6699cc"
                    graphBtn.border.color="#9fa1a4"
                }
            }
        }
    }

    Text {
        id: cyclenum
        anchors.left: btnArray.right
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("178")
        font.pixelSize: Math.round(Style.style4  * Style.scaleHint)
        font.family: Style.regular.name
        color: fontColor
    }

    Image
    {
        id: normalBtn
        width: Math.round(30 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        source: "qrc:/Images/Minimize.svg"
        sourceSize.width: normalBtn.width
        sourceSize.height: normalBtn.height
        smooth: true
    }

    MouseArea
    {
        id: noramlBtnClickArea
        width: parent.height
        height: parent.height
        anchors.centerIn: normalBtn
        onClicked:
        {
            mainWindow.hideFullScreenChart()
        }
    }

    Rectangle
    {
        id: navigationBar
        border.width: 1
        border.color: Style.frameBorderColor
        width:  Math.round(550 * Style.scaleHint)
        height:  Math.round(45 * Style.scaleHint)
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: noramlBtnClickArea.left
        anchors.rightMargin: Math.round(20 * Style.scaleHint)
        Row
        {
            anchors.fill: parent
            spacing: Math.round(5 * Style.scaleHint)
            Rectangle
            {
                width: Math.round(parent.width / 2)
                height: parent.height
                color: "transparent"
                Text {
                    id: leftTitle
                    text: qmltextLeftAxisTitle + "\n" + qmltextAxisTitle + ":"
                    font.pixelSize: titleFontSize
                    font.family: Style.regular.name
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    color: fontColor
                }
                BransonComboBox
                {
                    id: leftCombobox
                    anchors.left: leftTitle.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    minWidth: Math.round(160 * Style.scaleHint)
                    model: AxisDefine.getAxisModel()
                    onCurrentTextChanged:
                    {
                        leftAxisChanged(currentIndex)
                    }
                }
                Rectangle
                {
                    id: leftIndicator
                    anchors.left: leftCombobox.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width:  Math.round(15 * Style.scaleHint)
                    height:  Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color: rectleftcolor
                }
                Text {
                    anchors.left: leftIndicator.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: leftIndicator.verticalCenter
                    text: "12%"
                    font.pixelSize: valueFontSize
                    font.family: Style.regular.name
                    color: fontColor
                }
            }

            Rectangle
            {
                width:  Math.round(parent.width / 2)
                height:  parent.height
                color: "transparent"
                Text {
                    id: rightTitle
                    text: qmltextRightAxisTitle + "\n" + qmltextAxisTitle + ":"
                    font.pixelSize: titleFontSize
                    font.family: Style.regular.name
                    anchors.verticalCenter: parent.verticalCenter
                    color: fontColor
                }
                BransonComboBox
                {
                    id: rightCombobox
                    anchors.left: rightTitle.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    minWidth: Math.round(160 * Style.scaleHint)
                    model: AxisDefine.getAxisModel()
                    onCurrentTextChanged:
                    {
                        rightAxisChanged(currentIndex)
                    }
                }
                Rectangle
                {
                    id: rightIndicator
                    anchors.left: rightCombobox.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    width:  Math.round(15 * Style.scaleHint)
                    height:  Math.round(15 * Style.scaleHint)
                    radius: width/2
                    color:rectrightcolor
                }

                Text {
                    anchors.left: rightIndicator.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("12W")
                    font.pixelSize: valueFontSize
                    font.family: Style.regular.name
                    color: fontColor
                }
            }
        }
    }
}


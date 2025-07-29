/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.12
//import QtGraphicalEffects 1.0
import Style 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

ComboBox {
    id: comboboxId
    property alias comboboxpopupheight:comboboxpopup.implicitHeight
    property int   minWidth: Math.round(120 * Style.scaleHint)
    property int   minHeight: Math.round(40 * Style.scaleHint)
    property int imageSize: Math.round(15 * Style.scaleHint)
    property bool  menuStatus: false
    property bool  isNormal: true
    property int   radiusWidth: Math.round(5 * Style.scaleHint)
    property color comboBoxTextColor: Style.blackFontColor
    property color comboBoxBorderColor: "#707070"
    property color comboBoxColor : "#FFFFFF"
    property color shadowColor: "#80000000"
    property alias dropDownImg:img
    property alias dropDownText:combo_text
    property string comboBoxText
    property real  selectedDataIndex : currentIndex
    property int textFontSize: Math.round(Style.style0 * Style.scaleHint)
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
    implicitWidth: minWidth
    implicitHeight: minHeight
    background: Rectangle{
        anchors.fill: parent
        color: (enabled === true) ? comboBoxColor : BransonStyle.backgroundColor
        border.color: comboBoxBorderColor
        border.width: 1
        height: Math.round(25 * Style.scaleHint)
        radius: Math.round(3 * Style.scaleHint)
        layer.enabled: comboboxId.pressed ? false : true
//                layer.effect: DropShadow {
//                    horizontalOffset: comboboxId.pressed ? 0 : 1
//                    verticalOffset: comboboxId.pressed ? 0 : 1
//                    color:  shadowColor
//                    opacity: 0.2
//                    samples: 10
//                }
    }
    popup: Popup {
        id:comboboxpopup
        y: comboboxId.height
        width: comboboxId.implicitWidth
        implicitHeight: contentItem.implicitHeight
        padding: 1
        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: comboboxId.popup.visible ? comboboxId.delegateModel : null
            ScrollIndicator.vertical: ScrollIndicator { }
            highlightRangeMode: ListView.StrictlyEnforceRange

        }

        background: Rectangle {

            border.color: comboBoxBorderColor
            id:comboBoxRectangle
            color: comboBoxColor
            radius: Math.round(2 * Style.scaleHint)
            layer.enabled: comboBoxRectangle
//                       layer.effect: DropShadow {
//                           horizontalOffset: 1
//                           verticalOffset: 1
//                           color:  shadowColor
//                           opacity: 0.2
//                           samples: 10
//                       }
        }
        onAboutToHide:
        {
            changeImageDown()
        }

    }
    onCurrentIndexChanged:
    {
        changeIndex(currentIndex)
        selectedDataIndex = currentIndex
    }

    contentItem: Text {
        id: combo_text
        color: comboBoxTextColor
        text: isNormal === true ? currentText : comboBoxText
        anchors.left:  comboboxId.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        verticalAlignment: Text.AlignVCenter
        font{
            family: Style.regular.name
            /*Make sure delegate data fit within combobox*/
            pixelSize:textFontSize
        }
    }

    delegate: ItemDelegate {
        width: minWidth
        height: minHeight
        contentItem: Rectangle
        {
            anchors.fill: parent
            color: hovered === true ? Style.titleBackgroundColor : "#ffffff"
            Text {
                anchors.fill: parent
                text: modelData
                color: hovered === true ? "#ffffff" : Style.blackFontColor
                font.family: Style.regular.name
                /*Make sure delegate data fit within combobox*/
                font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
//                elide: Text.ElideRight
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                leftPadding:  Math.round(10 * Style.scaleHint)
            }
        }
    }

    onPressedChanged:
    {
        comboboxId.changeImageUp()
    }

    /**
       *@breif: On click change image
       **/
    function changeImageUp()
    {
        img.source = "qrc:/Images/DropUpArrow.png"

    }

    /**
       *@breif: On click change image
       **/
    function changeImageDown()
    {
        img.source = "qrc:/Images/DropDownArrow.png"
    }

    /**
       *@breif: Change image
       **/
    function changeIndex(currentIndex)
    {
        comboboxId.changeImageDown()
    }

    indicator:  Image {
        id: img
        anchors.right: comboboxId.right
        anchors.rightMargin: Math.round(2* Style.scaleHint)
        anchors.top:comboboxId.top
        anchors.verticalCenter: comboboxId.verticalCenter
        width: imageSize
        height: imageSize
        sourceSize.width: comboboxId.width
        sourceSize.height:  comboboxId.height
        fillMode: Image.PreserveAspectFit
        source: comboboxId.changeImageDown()
    }
}

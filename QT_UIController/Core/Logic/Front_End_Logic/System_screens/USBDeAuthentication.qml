/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the usb device List to deregister the device.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/06/2025 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import QtQuick.Layouts 1.15
import "./../Common_Logic"
import "./../System_screens"

Item
{
    id:usbDeAutheItem
    property string qmlTextSelectName:             "Select "
    property string qmltextDeviceName:             "Device Name"
    property string qmltextVendorCode:             "Vendor Code"
    property string qmltextProductCode:             "Product Code"
    property string qmltextSerialNumber:            "Serial Number"
    property string qmltextUsedData:                "Used Date"
    property string qmltextDeregistration:          "Deregister"

    property var qmlTextArray: [qmlTextSelectName, qmltextDeviceName, qmltextVendorCode, qmltextProductCode ]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION, qmlTextArray)
        qmlTextSelectName        = qmlTextArray[textEnum.textUserNameIdx]
        qmltextDeviceName       = qmlTextArray[textEnum.textAuthLevelIdx]
        qmltextVendorCode      = qmlTextArray[textEnum.textUserStatusIdx]
        qmltextProductCode        = qmlTextArray[textEnum.textDateTimeIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textUserNameIdx          : 0
        readonly property int textAuthLevelIdx         : 1
        readonly property int textUserStatusIdx        : 2
        readonly property int textDateTimeIdx          : 3
        readonly property int textActionIdx            : 4
        readonly property int textEditIdx              : 5
        readonly property int textPasswordIdx          : 6
        readonly property int textDeleteUserIdx        : 7
    }

    Component.onCompleted:
    {
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Rectangle
    {
        id: usbDevlistRect
        width: mainWindow.showWidth * 0.932
        height: mainWindow.showHeight * 0.07
        anchors.top: parent.top
        anchors.topMargin: mainWindow.showHeight * 0.11
        anchors.left: parent.left
        anchors.leftMargin:  mainWindow.showWidth * 0.01
        border.color:"#0F0F0F"
        color: Style.contentBackgroundColor
        clip:true

        Text
        {
            id: selectText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.01
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmlTextSelectName
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: devNameTxt
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.12
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmltextDeviceName
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: vendorCodeTxt
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.28
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmltextVendorCode
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: prdCodeTxt
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.42
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmltextProductCode
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: serNumTxt
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.60
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmltextSerialNumber
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

        Text
        {
            id: usedDataTxt
            anchors.left: serNumTxt.right
            anchors.leftMargin: parent.width * 0.06
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WrapAnywhere
            text: qmltextUsedData
            font.pixelSize: Math.round(Style.style3 * Style.scaleHint) *0.90
            font.family: Style.regular.name
            color: Style.blackFontColor
            font.weight : Font.DemiBold
        }

    }

    //Listview to dispaly the USB Devices list
    ListView
    {
        id: userDetailsListView
        width: mainWindow.showWidth * 0.932
        height: mainWindow.showHeight
        anchors.top: usbDevlistRect.bottom
        anchors.topMargin: mainWindow.showHeight * 0.02
        anchors.left: usbDevlistRect.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height *0.20
        spacing: Math.round(10 * Style.scaleHint)
        model:UsbAuthDetailsListModel
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar {}
        clip: true
        verticalLayoutDirection : ListView.TopToBottom

        onCurrentIndexChanged:
        {
        }
        delegate: Rectangle
        {
            id: userDetailsInfo
            width: userDetailsListView.width
            height: Math.round(35 * Style.scaleHint)
            border.color:"#0F0F0F"
            color: Style.contentBackgroundColor
            clip:true

            CheckBox
            {
                id:usbdevselectchbox
                width:Math.round(40 * Style.scaleHint)
                height: Math.round(40 * Style.scaleHint)
                onCheckedChanged:
                {
                    //update the model to USB Device detail with it's enable or disable status
                    UsbAuthDetailsListModel.deRegisterTheSelectedUSBDevice(checked,model.UsbIndex)
                }
            }
            Text
            {
                id: devNameDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.13
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.DeviceName
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: vendorCodeDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.29
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.VendorCode
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: productCodeDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.43
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.ProductCode
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
            Text
            {
                id: serialnumDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.617
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.SerialNUmber
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }

            Text
            {
                id: usedDataDelegate
                width: Math.round(150 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.80
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                text: model.UsedDate
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint) * 0.80
                font.family: Style.regular.name
                color: Style.blackFontColor
                font.weight : Font.Medium
            }
        }
    }

    Rectangle
    {
        id:mainRectangle
        width: mainWindow.showWidth
        height: mainWindow.showHeight *0.08
        anchors.top: userDetailsListView.bottom
        anchors.topMargin: parent.height*0.05
        color: Style.backgroundColor
        clip:true
        enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

        BransonPrimaryButton
        {
            id:usbRegistrationbtn
            implicitWidth: mainRectangle.width * 0.20
            implicitHeight: mainRectangle.height
            fontSize: zoomingSize(Style.style4)
            text: qmltextDeregistration
            font.family: Style.regular.name
            anchors.centerIn: parent
            buttonColor: "#17345C"
            onClicked:
            {
                //Send the Deregistration request on Button clicked.
                UsbAuthDetailsListModel.deRegisterButtonClicked()
            }
        }
    }

}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

This file handles the frontend logic for USB Authentication process.
 **********************************************************************************************************/
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick 2.0
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Com.Branson.UIScreenEnum 1.0
import QtQuick.Window 2.12
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"

Item
{
    id:usbauthenticationItem

    property string qmltextRegister:             "Register"


    property var qmlTextArray:[qmltextRegister]

    QtObject
    {
        id: textEnum
        readonly property int textqmltextRegisterIdx           : 0


    }
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_NFS, qmlTextArray)
        qmltextRegister = qmlTextArray[textEnum.textConfigCommunIdx]

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
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }

    Rectangle
    {
        id:mainRectangle
        width: mainWindow.showWidth* 0.20
        height: mainWindow.showHeight *0.1
        x: mainWindow.showWidth* 0.40
        y: mainWindow.showHeight *0.30
        color: Style.backgroundColor
        clip:true
        enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

        BransonPrimaryButton
        {
            id:usbRegistrationbtn
            implicitWidth: mainRectangle.width
            implicitHeight: mainRectangle.height
            fontSize: zoomingSize(Style.style4)
            text: qmltextRegister
            font.family: Style.regular.name
            buttonColor: "#17345C"
            onClicked:
            {
                UsbAuthDetailsListModel.usbDeviceRegisterButtonClicked()
            }
        }
    }


}

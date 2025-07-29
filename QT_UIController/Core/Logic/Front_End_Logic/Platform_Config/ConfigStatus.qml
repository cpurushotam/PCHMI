/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 ConfigStatus - Displays HMI Platform configuration status message.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/10/2023 - Initial version.
 
***************************************************************************/

import QtQuick 2.15
import Com.Branson.UIScreenEnum 1.0


Item{
    id:configScreens

    Connections{
        target: configStatus

        function onFirmwareMismatchNotify()
        {
            txt.text = configStatus.StatusMsg
        }
    }

    /*To make sure warnings popups are not visible unless login not performed*/
    onVisibleChanged:
    {
        isLoggedIn = false
    }

    Rectangle {

        property string statusMsg:     configStatus.StatusMsg

        width: mainWindow.width
        height: mainWindow.height
        color:"white"
        anchors.fill: parent

        // Text object to display configuration status message on screen
        Text
        {
            id:txt
            text: configStatus.StatusMsg // Configuration status message defined in ConfigStatus class
            font.family: "Helvetica"
            font.pointSize: 24
            color: "red"
            wrapMode: Text.Wrap
            width: parent.width * 0.9 // Set the width to 90% of the parent width
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            /*To make sure warnings popups are not visible unless login not performed*/
            onTextChanged:
            {
                isLoggedIn = false
                alarmsPopup.visible = false
                warningsPopup.visible = false
                serviceReminderPopup.visible = false
            }
        }
    }
}

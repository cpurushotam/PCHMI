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

Rectangle {

    property string statusMsg:   "HMI is in Locked mode."

    width: mainWindow.width
    height: mainWindow.height
    color:"transparent"
    anchors.fill: parent

    MouseArea
    {
        anchors.fill: parent
        onClicked: {
            showBransonPopupForLockedScreen(statusMsg)
        }
    }
}


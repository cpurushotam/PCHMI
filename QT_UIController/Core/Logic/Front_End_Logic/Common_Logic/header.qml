/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import Style 1.0
import "./../Common_Logic"

Item {
    //    property alias titleText: title.text
    property alias alarmNumText: alarmNum.text
    property alias alarmNotificationVisible: alarmNotification.visible

    property int imageSize: Math.round(30 * Style.scaleHint)
    property int iconSize: Math.round(25 * Style.scaleHint)
    property int alarmNumSize: Math.round(22 * Style.scaleHint)

    signal signalCurrentScreenIndexChanged(int screenIndex)
    signal activeAlarmPopupSelected()

    function clearChildrenTitleModel()
    {
        childrenTitlesModel.clear()
    }




    function clearChildrenTitleModelLab(index)
    {   var size = childrenTitlesModel.count
        if(size>2)
        {
            childrenTitlesModel.remove(size-1,1)
            childrenTitlesModel.set(size- 2, {"Visible": false})
        }
    }

    function appendChildrenTitleModel(name, index)
    {
        var size = childrenTitlesModel.count
        if(size !== 0)
        {
            childrenTitlesModel.set(size - 1, {"Visible": true})
        }
        childrenTitlesModel.append({"Title": name, "Index": index, "Visible": false})
    }

    function removeChildrenTitleModel(index)
    {
        var size = childrenTitlesModel.count
        if(size === 0)
            return;
        while(index !== childrenTitlesModel.get(size - 1).Index)
        {
            childrenTitlesModel.remove(size - 1)
            size = childrenTitlesModel.count
            if(size === 0)
                break
        }
        if(size !== 0)
        {
            childrenTitlesModel.set(size - 1, {"Visible": false})
        }
    }

    function updateLanguage()
    {
        var strMenuTitle = ""
        var iMenuIndex = 0
        for(var i = 0; i < childrenTitlesModel.count; i++)
        {
            strMenuTitle = childrenTitlesModel.get(i).Title
            iMenuIndex = childrenTitlesModel.get(i).Index
            strMenuTitle = LanguageConfig.getLanguageMenuName(iMenuIndex, strMenuTitle)
            childrenTitlesModel.setProperty(i, "Title", strMenuTitle)
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
        childrenTitlesModel.resetModel()
        updateLanguage()
    }

    ListModel{
        id: childrenTitlesModel
        function resetModel()
        {
            childrenTitlesModel.clear()
        }
    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: Style.headerBackgroundColor
    }

    Item
    {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        Item{
            id: btnLeftMenu
            property bool isChecked: false
            height: imageSize
            width: imageSize
            anchors.left: parent.left
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            onIsCheckedChanged: {

            }

            Image {
                id: imageLeftMenu
                anchors.fill: parent
                source: "qrc:/Images/LeftMenu.svg"
                sourceSize.width: imageLeftMenu.width
                sourceSize.height: imageLeftMenu.height
                smooth: true
                height: parent.height
                width: parent.width
                fillMode: Image.PreserveAspectFit
            }
        }
        MouseArea {
            id: leftMenuMouseArea
            width: parent.height
            height: parent.height
            anchors.centerIn: btnLeftMenu
            hoverEnabled: true
            onReleased: {

                if(!mainWindow.isOnPartActive)
                {
                    //To show left action menu if Dongle key not connected
                    if(!(mainWindow.isPasswordRestDongleInserted))
                    {
                        Qt.inputMethod.hide()
                        mainWindow.showLeftActionMenu()
                        mainWindow.showMainWindowOpacity()
                    }
                }
                else
                {
                    mainWindow.showBransonPopupForHornRetract()
                }
            }
        }

        Item {
            anchors.left: btnLeftMenu.right
            anchors.leftMargin: Math.round(15 * Style.scaleHint)
            anchors.right: connectedNotification.left
            anchors.rightMargin: Math.round(15 * Style.scaleHint)
            anchors.top: parent.top
            height: parent.height
            Row {
                id: titleList
                anchors.fill: parent
                spacing: Math.round(6 * Style.scaleHint)
                Repeater {
                    id: childrenTitles
                    model: childrenTitlesModel
                    delegate: Item{
                        height: parent.height
                        width: Math.round(title.width + imageNavigationArrow.width) + Math.round(4 * Style.scaleHint)
                        Text {
                            id: title
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.Title
                            font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                            font.family: Style.regular.name
                            color: Style.whiteFontColor
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {

                                    if(!mainWindow.isOnPartActive)
                                    {
                                        Qt.inputMethod.hide()
                                        signalCurrentScreenIndexChanged(model.Index)
                                    }
                                    else
                                    {
                                        mainWindow.showBransonPopupForHornRetract()
                                    }
                                }
                            }
                        }
                        Image {
                            id: imageNavigationArrow
                            anchors.left: title.right
                            anchors.leftMargin: Math.round(4 * Style.scaleHint)
                            anchors.verticalCenter: title.verticalCenter
                            source: "qrc:/Images/Right Chevron.svg"
                            sourceSize.width: imageNavigationArrow.width
                            sourceSize.height: imageNavigationArrow.height
                            smooth: true
                            height: iconSize
                            width: iconSize
                            visible: model.Visible
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }
            }
        }

        Item{
            id: btnRightMenu
            property bool isChecked: false
            height: imageSize
            width: imageSize
            anchors.right: parent.right
            anchors.rightMargin: Math.round(24 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            onIsCheckedChanged: {

            }

            Image {
                id: imageRightMenu
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: iconSize
                height: iconSize
                source: "qrc:/Images/RightMenu.svg"
                sourceSize.width: imageRightMenu.width
                sourceSize.height: imageRightMenu.height
                smooth: true
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: imagePanIcon
                anchors.top: parent.top
                anchors.left: imageRightMenu.horizontalCenter
                width: Math.round(14 * Style.scaleHint)
                height: Math.round(15 * Style.scaleHint)
                source: "qrc:/Images/Pen.svg"
                sourceSize.width: imagePanIcon.width
                sourceSize.height: imagePanIcon.height
                smooth: true
                fillMode: Image.PreserveAspectFit
            }
        }

        MouseArea {
            id: rightMenuMouseArea
            width: parent.height
            height: parent.height
            anchors.centerIn: btnRightMenu
            hoverEnabled: true
            onReleased: {

                if(!mainWindow.isOnPartActive)
                {

                    //To show right action menu if Dongle key not connected
                    if(!(mainWindow.isPasswordRestDongleInserted))
                    {
                        Qt.inputMethod.hide()
                        mainWindow.showRightActionMenu()
                        mainWindow.showMainWindowOpacity()
                    }
                }
                else
                {
                    mainWindow.showBransonPopupForHornRetract()
                }
            }
        }

        Item
        {
            id: alarmNotification
            anchors.right: parent.right
            anchors.rightMargin: Math.round(85 * Style.scaleHint)
            height: imageSize
            width: imageSize
            anchors.verticalCenter: parent.verticalCenter

            Image
            {
                id: imageAlarmNotification
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                height: iconSize
                width: iconSize
                source: "qrc:/Images/AlarmNotification.svg"
                sourceSize.width: imageAlarmNotification.width
                sourceSize.height: imageAlarmNotification.height
                smooth: true
                fillMode: Image.PreserveAspectFit
            }

            Rectangle
            {
                id: alarmNum
                visible: ActiveAlarmDetailsListModel.TotalActiveAlarmsWarningsNotificationsCount
                anchors.left: parent.left
                anchors.leftMargin: Math.round(13 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(16 * Style.scaleHint)
                height: alarmNumSize
                width: alarmNumSize
                radius: Math.round(height/2)
                property alias text: txtAlarmNum.text
                color: "#FF0000"
                Text
                {
                    id: txtAlarmNum
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: Style.whiteBackgroundColor
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    font.family: Style.semibold.name
                    text: ActiveAlarmDetailsListModel.TotalActiveAlarmsWarningsNotificationsCount
                }
            }

            MouseArea
            {
                id: alarmMA
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(!mainWindow.isOnPartActive)
                    {
                        //To show alarm notification if Dongle key not connected
                        if(!(mainWindow.isPasswordRestDongleInserted))
                        {
                            activeAlarmPopupSelected()
                        }
                    }
                    else
                    {
                        mainWindow.showBransonPopupForHornRetract()
                    }
                }
            }
        }

        Item {
            id: connectedNotification
            anchors.right: parent.right
            anchors.rightMargin: Math.round(146 * Style.scaleHint)
            height: imageSize
            width: imageSize
            anchors.verticalCenter: parent.verticalCenter
            visible: false //Remove this line after demo.
            Image{
                id: imageConnectedNotification
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                height: iconSize
                width: iconSize
                source: "qrc:/Images/Connected.svg"
                sourceSize.width: imageConnectedNotification.width
                sourceSize.height: imageConnectedNotification.height
                smooth: true
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}



/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonNewCard.qml file displays new card on recipe cards screen.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 18/07/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.RecipeEnum 1.0
Item {
    readonly property color titleBackgroundColor: "#E1EAEA"
    readonly property int iconSize: 20
    readonly property int bigIconSize: 35
    readonly property int creatingIconSize: 44
    property bool isActive: false
    property bool isNewCard: false
    property string qmltextAction
    property string qmltextNewCard
    property string numberAssigned
    property string nameAssigned
    property string weldCountTitle
    property string weldCountValue
    property string recipeVersionTitle
    property string recipeVersionInfo
    property bool recipeSaveStatus
    property alias actionModel: actionButton.model
    property alias strDataModel: cardDetailsInfo.model

    signal signalActionEvent(var actionIndex)

    RectangularGlow {
        id: existingGlowEffective
        anchors.fill: existingCardFront
        glowRadius: 3
        spread: 0.2
        opacity: 0.2
        color: "#80000000"
        cornerRadius: existingCardFront.radius + glowRadius
        visible: isNewCard === true ? false : true
    }

    Rectangle {
        id: existingCardFront
        width: parent.width
        height: parent.height
        clip: true
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        color: isActive === true ? titleBackgroundColor : "#FFFFFF"
        border.color: isActive === true ? Style.activeFrameBorderColor: Style.frameBorderColor
        visible: isNewCard === true ? false : true
        Image
        {
            id: recipeIcon
            anchors.top: parent.top
            anchors.topMargin: 20 * Style.scaleHint
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/Images/RecipeSymbol.png"
            height: (40 * Style.scaleHint)
            width: (40 * Style.scaleHint)
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeIcon.width
            sourceSize.height: recipeIcon.height
            smooth: true
        }

        Rectangle
        {
            id: cardTitle
            anchors.top: parent.top
            anchors.topMargin: 75 * Style.scaleHint
            anchors.left: parent.left
            anchors.leftMargin: parent.border.width * 2
            height: (parent.height / 10 * Style.scaleHint)
            width: parent.width - (parent.border.width * 2 * Style.scaleHint)
            color: isActive === true ? Style.activeFrameBorderColor : "#808080"

            Text
            {
                id: unsavedAsterisk
                visible: (!recipeSaveStatus) && (isActive)
                anchors.top: cardTitle.top
                anchors.topMargin: 0 * Style.scaleHint
                anchors.right: cardName.left
                anchors.rightMargin: 2
                text: "*"
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                font.bold: true
                color: Style.recipeNameFontColor
            }

            Text
            {
                id: cardName
                anchors.centerIn: parent
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: numberAssigned + " : " + nameAssigned.substring(0,10)
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                font.bold: true
                color: Style.recipeNameFontColor
            }
        }

        Rectangle
        {
            id: cardDetails
            anchors.top: cardTitle.bottom
            anchors.topMargin: 50 * Style.scaleHint
            anchors.left: cardTitle.left
//            height: cardTitle.height
            width: cardTitle.width
            color: isActive === true ? titleBackgroundColor : "#FFFFFF"
            Column
            {
                anchors.centerIn: parent
                spacing: 7 * Style.scaleHint
                Repeater
                {
                    id: cardDetailsInfo
                    delegate: Text
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        text: model.TitleNum + ": " + model.TitleDetails
                        font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                        color: isActive === true ? Style.blueFontColor : Style.blackFontColor
                    }
                }

                Text
                {
                    id: cycleCount
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: weldCountTitle + " : " + weldCountValue
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    color: isActive === true ? Style.blueFontColor : Style.blackFontColor
                }

                Text
                {
                    id: versionInfo
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: recipeVersionTitle + ":" + recipeVersionInfo
                    font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
                    color: isActive === true ? Style.blueFontColor : Style.blackFontColor
                }
            }
        }

        MouseArea
        {
            id: frontRectangleMouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onReleased:
            {
                actionAnimation.restart()
                frontRectangleMouseArea.visible = false
            }
        }

        Rectangle {
            id: existingCardBack
            width: parent.width
            height: parent.height
            x: 0
            y: parent.height
            clip: true
            border.width: Style.scaleHint === 1.0 ? 1 : 3
            border.color: isActive === true ? Style.activeFrameBorderColor: Style.frameBorderColor
            Rectangle {
                id: actionHeader
                anchors.top: parent.top
                anchors.topMargin: existingCardBack.border.width
                anchors.left: parent.left
                anchors.leftMargin: existingCardBack.border.width
                width: parent.width - 2 * existingCardBack.border.width
                height: Math.round(40 * Style.scaleHint)
                color: titleBackgroundColor

                Image {
                    id: deleteIcon
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Images/Trash.svg"
                    height: Math.round(iconSize * Style.scaleHint)
                    width: Math.round(iconSize * Style.scaleHint)
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: deleteIcon.width
                    sourceSize.height: deleteIcon.height
                    smooth: true
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if( UserPrivilegeObj.IsDeleteRecipeAllowed || mainWindow.isAuthorityCheckEnable)
                            {
                                signalActionEvent(RecipeEnum.DELETE_IDX)
                                reverseActionAnimation.restart()
                                frontRectangleMouseArea.visible = true
                            }
                            else
                            {
                                //Add Popup logic.
                                mainWindow.showBransonPopupForAccessDenied()
                            }
                        }
                    }
                }

                Image {
                    id: infoIcon
                    anchors.right: parent.right
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Images/Info.svg"
                    height: Math.round(iconSize * Style.scaleHint)
                    width: Math.round(iconSize * Style.scaleHint)
                    sourceSize.width: infoIcon.width
                    sourceSize.height: infoIcon.height
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            signalActionEvent(RecipeEnum.INFORMATION_IDX)
                        }
                    }
                }

                Image {
                    id: copyIcon
                    anchors.right: infoIcon.left
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Images/Copy.png"
                    height: Math.round(iconSize * Style.scaleHint)
                    width: Math.round(iconSize * Style.scaleHint)
                    sourceSize.width: copyIcon.width
                    sourceSize.height: copyIcon.height
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if( UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed || mainWindow.isAuthorityCheckEnable)
                            {
                                signalActionEvent(RecipeEnum.COPY_IDX)
                                reverseActionAnimation.restart()
                                frontRectangleMouseArea.visible = true
                            }
                            else{
                                mainWindow.showBransonPopupForAccessDenied()

                            }
                        }
                    }
                }

                Row {
                    id: actionArea
                    anchors.left: deleteIcon.right
                    anchors.leftMargin: Math.round(1 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: Math.round(1 * Style.scaleHint)
                    Image {
                        id: actionIcon
                        source: "qrc:/Images/Chevron.svg"
                        height: Math.round(iconSize * Style.scaleHint)
                        width: Math.round(iconSize * Style.scaleHint)
                        fillMode: Image.PreserveAspectFit
                        anchors.bottom: actionTitle.bottom
                        sourceSize.width: actionIcon.width
                        sourceSize.height: actionIcon.height
                        smooth: true
                    }
                    Text {
                        id: actionTitle
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        text: qmltextAction
                        verticalAlignment: Text.AlignVCenter
                        font.family: Style.semibold.name
                        font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                        color: Style.blackFontColor
                    }
                }
                MouseArea {
                    id: backRectangleMouseArea
                    anchors.fill: actionArea
                    cursorShape: Qt.PointingHandCursor
                    onReleased: {
                        reverseActionAnimation.restart()
                        frontRectangleMouseArea.visible = true
                    }
                }
            }

            Rectangle {
                id: actionButtonArray
                anchors.top: actionHeader.bottom
                anchors.bottom: parent.bottom
                anchors.bottomMargin: existingCardBack.border.width
                anchors.left: actionHeader.left
                width: actionHeader.width

                Column {
                    anchors.centerIn: parent
                    spacing: 5
                    Repeater {
                        id: actionButton
                        delegate: BransonChildButton
                        {
                            enabled: true
                            buttonColor : model.userLevelAccess ?  "#17345C" : "#9b9e9c"
                            Text
                            {
                                id: name
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: model.ActionName
                                color: Style.buttonTextColor
                                font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
                            }
                            width: 140 * Style.scaleHint
                            height: 37 * Style.scaleHint
                            onChildButtonClicked: {
                                if(model.userLevelAccess)
                                {
                                    signalActionEvent(model.ActionIndex)
                                    reverseActionAnimation.restart()
                                    frontRectangleMouseArea.visible = true
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    NumberAnimation {
        id: actionAnimation
        target: existingCardBack
        property: "y"
        to: 0
        duration: 250
    }

    NumberAnimation {
        id: reverseActionAnimation
        target: existingCardBack
        property: "y"
        to: existingCardBack.height
        duration: 250
    }

    RectangularGlow {
        id: creatingGlowEffective
        anchors.fill: creatingCard
        glowRadius: 3
        spread: 0.2
        opacity: 0.2
        color: "#80000000"
        cornerRadius: creatingCard.radius + glowRadius
        visible: isNewCard === true ? true : false
    }

    Rectangle {
        id: creatingCard
        width: parent.width
        height: parent.height
        clip: true
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        visible: isNewCard === true ? true : false
        color: UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed || mainWindow.isAuthorityCheckEnable ? "#f2f5f3" : "#c5c7c9"
        Column{
            id: newCardMouseArea
            anchors.centerIn: parent
            spacing: 12
            Image {
                id: creatingImage
                source: "qrc:/Images/Add.svg"
                height: Math.round(creatingIconSize * Style.scaleHint)
                width: Math.round(creatingIconSize * Style.scaleHint)
                fillMode: Image.PreserveAspectFit
                sourceSize.width: creatingImage.width
                sourceSize.height: creatingImage.height
                smooth: true
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: newCardTitle
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: qmltextNewCard
                font.family: Style.semibold.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.blackFontColor
            }
        }
        MouseArea {
            anchors.fill: newCardMouseArea
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed || mainWindow.isAuthorityCheckEnable )
                {
                    signalActionEvent(RecipeEnum.CREATE_NEW_IDX)
                }
                else{
                    creatingCard.color = "#c5c7c9"
                    mainWindow.showBransonPopupForAccessDenied()
                }
            }
        }
    }
}

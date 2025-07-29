/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 MultiWelderScreen - This is a read-only screen where it displays information about connected welders .

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Window
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick 2.0
import QtQuick 2.11
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"

Popup {

    readonly property int qmlscreenIndicator:  UIScreenEnum.MULTIWELDERINFORMATION

    property string qmltextManageHeader:                          qsTr("Welder Info")
    property string qmltextWelderName:                            qsTr("Welder Name")
    property string qmltextIPAddress:                             qsTr("IP Address")
    property string qmltextOK:                                    qsTr("OK")
    property int num: 0
    property var qmltextWelder:                                   qsTr("Welder")
    //property int width: headerRect.width
    property var highlightActiveWelderId:  -1

    property var    qmlTextArray: [qmltextManageHeader, qmltextWelderName,
          qmltextOK, qmltextIPAddress]

    QtObject {
        id: textEnum
        readonly property int textManageHeaderIdx:           0
        readonly property int textWelderNameIdx:             1
        readonly property int textOKIdx:                     2
        readonly property int textIPAddressIdx:              3
        readonly property int textWelderIdx:                 4
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.MULTIWELDERINFORMATION, qmlTextArray)
        qmltextManageHeader = qmlTextArray[textEnum.textManageHeaderIdx]
        qmltextWelderName = qmlTextArray[textEnum.textWelderNameIdx]
        qmltextOK = qmlTextArray[textEnum.textOKIdx]
        qmltextIPAddress=qmlTextArray[textEnum.textIPAddressIdx]
        qmltextWelder="Welder"//qmlTextArray[textEnum.textWelderIdx]

        /*Update the language for dynamic strings.*/
        localmultiWelderListModel.clear()

        for (var j=0; j<welderListModel.count; ++j)
        {
            var value=welderListModel.get(j).value
            var key=qmltextWelder + " " + (welderListModel.get(j).id+1)
            var id=welderListModel.get(j).id
            var txtcolor="#211c1c"
            var activebckcolor="#f7fafa"
            var itemText = key + " - " + value+ " - " + id+ " - "+ txtcolor + " - " + activebckcolor;
            localmultiWelderListModel.append({ "text": itemText, "key": key, "value": value ,"id":id,"txtcolor":txtcolor,"activebckcolor":activebckcolor});
        }
    }
    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        target: multiWelderInterface
        function onWelderNameReceived( id,  name)
        {
            for (var i=0; i<localmultiWelderListModel.count; ++i)
            {
                if (localmultiWelderListModel.get(i).id === id)
                {
                    welderListModel.get(i).key = name
                    localmultiWelderListModel.get(i).key = name
                }
            }
        }
    }

    /*Toget the active welder from select welder screen. */
    Connections{
        target: leftMenuLoader.item
        function onActiveWelder(actv)
        {
            highlightActiveWelderId=actv
            for(var i = 0; i < localmultiWelderListModel.count; ++i)
            {
                if ((localmultiWelderListModel.get(i).id) === actv)
                {
                    localmultiWelderListModel.get(i).txtcolor="#1261a6"
                    localmultiWelderListModel.get(i).activebckcolor="#a8e4ed"

                    welderListModel.get(i).txtcolor="#1261a6"
                    welderListModel.get(i).activebckcolor="#a8e4ed"
                }
                else
                {
                    localmultiWelderListModel.get(i).txtcolor="#211c1c"
                    localmultiWelderListModel.get(i).activebckcolor="#f7fafa"

                    welderListModel.get(i).txtcolor="#1261a6"
                    welderListModel.get(i).activebckcolor="#a8e4ed"
                }
            }
        }
    }
    Component.onCompleted:
    {
        updateLanguage()
    }


    id: popup
    dim: true
    modal: true
    focus: true
    background: Rectangle {
        id:rectMain
        color:"transparent"
    }
    Overlay.modal: Rectangle {
        color: "#aacfdbe7"
    }

    Rectangle{
        anchors.fill: parent
        id:root
        radius:15
        color:"white"
        clip:true

        Rectangle {
            id: clipper
            width: parent.width
            height: parent.height/12
            color: 'transparent'
            clip: true

            Rectangle {
                id: clipped
                anchors.left: parent.left
                anchors.right: parent.right
                width: parent.width + radius
                height: parent.height + radius
                radius: root.radius
                color: '#1261a6'

                Text {
                    id: mangeTextHeader
                    text:qmltextManageHeader
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: Style.regular.name
                    font.bold: true
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.05
                    anchors.topMargin: parent.height*0.15
                    anchors.top: parent.top
                }

                Image {
                    id: crossMark
                    fillMode:Image.PreserveAspectFit;
                    clip:true
                    source: "qrc:/Images/crossMark.svg"
                    anchors.right: parent.right
                    anchors.top:          parent.top
                    anchors.topMargin:    parent.height*0.15
                    anchors.rightMargin:  parent.height/2
                    sourceSize.width:  Math.round(Style.style4 * Style.scaleHint)
                    sourceSize.height: Math.round(Style.style4 * Style.scaleHint)+5

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            popup.close()
                        }
                    }
                }
            }
        }
        Column{
            id:infoColumn
            width: root.width*0.90
            anchors.top: clipper.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle{
                id:headerRect
                width: parent.width
                border.color: "#212224"
                height: listRect.height*0.15

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: parent.width*0.05
                    spacing: (parent.width - (text1.width +  text3.width)) / 2

                    Text {
                        id: text1
                        text: qmltextWelderName
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        font.family: Style.regular.name
                        font.bold: false
                    }

                    Text {
                        id: text3
                        text: qmltextIPAddress
                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                        font.family: Style.regular.name
                        font.bold: false
                    }
                }
            }
        }
        Rectangle{
            id:listRect
            width: headerRect.width
            height: parent.height*0.65
            color: "transparent"
            anchors.left: infoColumn.left
            anchors.right: infoColumn.right
            anchors.top: infoColumn.bottom
            clip: true

            ListView {
                id: listView
                width: parent.width
                height: parent.height
                anchors.top: parent.top
                anchors.topMargin: listRect.height*0.05
                boundsBehavior: Flickable.StopAtBounds
                ListModel {
                    id:welderListModel
                }
                // Listmodel to store updating language for dynammic strings.
                ListModel{
                    id:localmultiWelderListModel
                }
                Component.onCompleted: {     }
                model:localmultiWelderListModel


                Connections{
                    target: multiWelderInterface

                    onWelderConnectedChanged:
                    {
                        var value=multiWelderInterface.m_WelderConnected
                        var id=multiWelderInterface.m_welderId
                        var key = qmltextWelder+" "+(id+1)
                        var txtcolor="#211c1c"
                        var activebckcolor="#f7fafa"
                        var itemText = key + " - " + value+ " - " + id+ " - "+ txtcolor + " - " + activebckcolor;
                        welderListModel.append({ "text": itemText, "key": key, "value": value ,"id":id,"txtcolor":txtcolor,"activebckcolor":activebckcolor});
                        localmultiWelderListModel.append({ "text": itemText, "key": key, "value": value ,"id":id,"txtcolor":txtcolor,"activebckcolor":activebckcolor});
                    }
                    onWelderDisconnectChanged:{
                        for (var i=0; i<welderListModel.count; ++i)
                        {
                            if (welderListModel.get(i).value==multiWelderInterface.m_welderDisconnect){
                                welderListModel.remove(i);
                                localmultiWelderListModel.remove(i);
                                break;
                            }
                        }
                    }
                }
                delegate: Item {
                    width: listView.width
                    height: listView.height*0.20
                    ColumnLayout {

                        spacing:  listView.height*0.17//listRect.height*0.15//

                        Rectangle{
                            width: listView.width-1
                            //implicitWidth: listView.width-1
                            height: listView.height*0.17
                            border.color: "#1c1c1c"
                            color:model.activebckcolor
                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: parent.width*0.05
                                spacing: (parent.width - (welderN.width +  ipAddressN.width))/1.5

                                Text {
                                    id:welderN
                                    text: model.key
                                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)-2
                                    font.family: Style.regular.name
                                    font.bold: false
                                    color:model.txtcolor
                                }
                                Text {
                                    id:ipAddressN
                                    text: model.value
                                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)-2
                                    font.family: Style.regular.name
                                    font.bold: false
                                    color:model.txtcolor
                                }

                            }
                        }
                    }
                }
            }
        }

        BransonPrimaryButton{
            id:resetButton
            width: listRect.width*0.35
            height: headerRect.height*0.85
            anchors.top: listRect.bottom
            //anchors.topMargin:  listView.height*0.05/3
            anchors.left: listRect.left
            anchors.leftMargin: listRect.width/3
            background: Rectangle {
                color: '#1261a6'
            }
            text: qmltextOK
            onClicked: {
                popup.close()
            }
        }
        ListModel{
            id:rectModel
        }
    }
}

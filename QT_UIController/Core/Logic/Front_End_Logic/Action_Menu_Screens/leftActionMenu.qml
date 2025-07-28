/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 LeftActionMenu - Displays screen related to active welder selection and access to windows like
                   recipes, production, analytics and system .
 **********************************************************************************************************/

import QtQuick 2.0
import QtQml.Models 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {
//    width: Math.round(800 * Style.scaleHint) //while using as element that value will over write this values
//    height: Math.round(480 * Style.scaleHint)

    property string qmltextMenu: qsTr("MENU")
    readonly property int arcWidth: Math.round((parent.width*0.50)) //* Style.scaleHint)
    readonly property int arcRadius: Math.round((parent.width*0.48))//* Style.scaleHint)
    readonly property int centerX: Math.round(arcWidth - arcRadius)
    readonly property int centerY: Math.round(height / 2)
    readonly property int imageSize: Math.round(30 * Style.scaleHint)
    readonly property int menuSepratorHeight: (Style.scaleHint == 1.0)? 1 : 2
    property alias leftActionAnimation: leftActionAnimation

    //qsTr can keep the word with English as the default without any messy code on the others Windows OS.
    property string qmltextDashboard:  qsTr("DASHBOARD")
    property string qmltextRecipe:     qsTr("RECIPES")
    property string qmltextProduction: qsTr("PRODUCTION")
    property string qmltextAnalytics:  qsTr("ANALYTICS")
    property string qmltextSystem:     qsTr("SYSTEM")
    property var qmltextWelder:        qsTr("Welder")
    property int activeWelderid:        -1
    property var prevactiveWelderid
    property int nextActiveWelder:      -1
    property var welderId
    property string qmltextSelectWelder:      qsTr("Select Welder")
    property var qmlTextArray: [qmltextMenu, qmltextRecipe, qmltextProduction, qmltextAnalytics, qmltextSystem, qmltextSelectWelder, qmltextWelder, qmltextDashboard]

    property var menuIndex: UIScreenEnum.PRODUCTION
    property var menuName: qmltextProduction

    signal activeWelder(int actv);                         /* Signal for active welder.                                                       */
    signal disContWelderID(var id);                        /* Signal for disconnected welder.                                                 */
    signal switchActiveWelderID(var id ,var nxtWelder);    /* Signal to inform user about switching of the active welder after disconnection.  */
    signal closeAlertWin(var id);                          /* Signal to close the popup window after reconnection of welder.                   */
    signal welderRenamed (var welderName);

    id: leftActionCenterItem

    ListModel{
        id:multiWelderListModel
    }

    // Listmodel to store updating language for dynammic strings.
    ListModel{
        id:localmultiWelderListModel
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
                    multiWelderListModel.get(i).key = name
                    localmultiWelderListModel.get(i).key = name
                }
            }
            welderdisplayLabel.text=localmultiWelderListModel.get(activeWelderid).key
            welderRenamed(localmultiWelderListModel.get(activeWelderid).key)
            closeAlertWin(localmultiWelderListModel.get(activeWelderid).key)

        }
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.LEFTMENU, qmlTextArray)
        qmltextMenu = qmlTextArray[textEnum.menuIdx]
        qmltextSelectWelder = qmlTextArray[textEnum.selectwelderIdx]
        qmltextWelder=qmlTextArray[textEnum.welderIdx]
        for(var i = 0; i < leftMenuModelData.count; i++)
        {
            leftMenuModelData.set(i, {"MenuName": qmlTextArray[i+1]})
        }

        /*Update the language for dynamic strings.*/
        localmultiWelderListModel.clear()
        activeWelder(activeWelderid);
        for (var j=0; j<multiWelderListModel.count; j++)
        {
            var welderIp=multiWelderListModel.get(j).value
            var welderName=qmltextWelder+multiWelderListModel.get(j).id
            var idd=multiWelderListModel.get(j).id
            localmultiWelderListModel.append({ "key": qmltextWelder+" "+(multiWelderListModel.get(j).id+1), "value": welderIp,"id":idd});

            if(activeWelderid===localmultiWelderListModel.get(j).id){
                 welderSelComboBox.currentIndex=j
                var actvname=localmultiWelderListModel.get(j).key
                welderdisplayLabel.text=actvname
                multiWelderInterface.setActiveWelder(localmultiWelderListModel.get(welderSelComboBox.currentIndex).id);
            }
        }
    }

    /* Function to check whether the activeWelder is disconnected or not. */
    function checkActvDisconWelder(){
        if(welderId === prevactiveWelderid && localmultiWelderListModel.count === 1)
        {
            switchActiveWelderID(welderId,localmultiWelderListModel.get(0).key)
        }
        else
        {
            disContWelderID(prevactiveWelderid)
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        leftActionAnimationReturn.restart()
        leftMenuModelData.resetModel()
        updateLanguage()
    }

    QtObject {
        id: textEnum
        readonly property int menuIdx:          0
        readonly property int recipeIdx:        1
        readonly property int productionIdx:    2
        readonly property int analyticsIdx:     3
        readonly property int systemIdx:        4
        readonly property int selectwelderIdx:  5
        readonly property int welderIdx:        6
        readonly property int dashboardIdx:     7
    }

    ListModel {
        id: leftMenuModelData
        function resetModel()
        {
            leftMenuModelData.clear()
            leftMenuModelData.append({"MenuName":   qmltextRecipe,
                                    "MenuIcon":     "qrc:/Images/recipe.svg",
                                    "MenuAction":   "RecipeListView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.RECIPES,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextProduction,
                                     "MenuIcon":     "qrc:/Images/production.svg",
                                    "MenuAction":   "ProductionView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.PRODUCTION,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextAnalytics,
                                     "MenuIcon":     "qrc:/Images/analytics.svg",
                                    "MenuAction":   "AnalyticsView.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.ANALYTICS,
                                    "MenuVisible":  true,
                                    "MenuSeparator": true
                                      })
            leftMenuModelData.append({"MenuName":   qmltextSystem,
                                    "MenuIcon":     "qrc:/Images/system.svg",
                                    "MenuAction":   "System.qml",
                                    "MenuColor":    "#ffffff",
                                    "MenuIndex":    UIScreenEnum.SYSTEM,
                                    "MenuVisible":  true,
                                    "MenuSeparator": false
                                     })
        }
    }

    NumberAnimation on x
    {
        id: leftActionAnimationReturn
        from: 0
        to: -width
        duration: 250

    }


    NumberAnimation on x
    {
        id: leftActionAnimation
        from: -width
        to: 0
        duration: 250
    }

    Item{
        id: rootRectangle
//        color: "transparent"
        anchors.top: parent.top
        anchors.left: parent.left
        width:  arcWidth
        height: parent.height
        //For mobile screen and small screen Canvas element is not required
        z: 3
        Canvas{
            id: canvash
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            opacity: 0.8
            onPaint:
            {
                var ctx = getContext("2d")
                ctx.fillStyle = Style.titleBackgroundColor
                ctx.beginPath()
                ctx.arc(0, centerY, arcRadius, 0.5 * Math.PI, 1.5 * Math.PI, true)
                ctx.fill()
            }
            MouseArea
            {
                anchors.fill: parent
            }
        }

        Item{
            id: menuDetails
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.top: parent.top
            Item {
                id: backMenuButton
                anchors.left: parent.left
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(14 * Style.scaleHint)
                height: imageSize
                width: Math.round(110 * Style.scaleHint)
                Rectangle{
                    anchors.fill: parent
                    border.color: "transparent"
                    color: "transparent"
                    Row{
                        id: menuLayout
                        spacing: Math.round(12 * Style.scaleHint)
                        Image
                        {
                            id: imageMenu
                            width: imageSize
                            height: imageSize
                            sourceSize.width: imageSize
                            sourceSize.height: imageSize
                            source: "qrc:/Images/menu_close_arrow.svg"
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            id:menuid
                            text: qmltextMenu
                            height: imageSize
                            font.family: Style.regular.name
                            anchors.verticalCenter: imageMenu.verticalCenter
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            color: Style.whiteFontColor
                        }
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            leftActionAnimationReturn.restart()
                            mainWindow.hideMainWindowOpacity()
                        }
                    }
                }
            }
            //Added for Multiwelder
            Item{
                id:multiWelderLayout
                anchors.left: parent.left
                anchors.top: backMenuButton.bottom
                anchors.topMargin: Math.round(10 * Style.scaleHint)

                Text{
                    id:selectWelderText
                    text: qmltextSelectWelder
                    anchors.top: backMenuButton.bottom
                    anchors.left: parent.left
                    anchors.topMargin: Math.round(60 * Style.scaleHint)
                    anchors.leftMargin: Math.round(48 * Style.scaleHint)
                    font.bold: true
                    font.pixelSize: welderSelComboBox.height*0.40
                    color: Style.whiteFontColor
                }
                RowLayout{
                    anchors.top: selectWelderText.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(48 * Style.scaleHint)
                    anchors.topMargin: Math.round(6 * Style.scaleHint)
                    spacing :Math.round(12 * Style.scaleHint)

                    BransonComboBox {
                        id: welderSelComboBox
                        implicitWidth: Math.round(150 * Style.scaleHint)
                        clip: true
                        // Use a separate ListModel to populate the ComboBox
                        Label {
                            id: welderdisplayLabel
                            Layout.fillWidth: welderSelComboBox
                            anchors.left: welderSelComboBox.left
                            anchors.leftMargin: welderSelComboBox.width*0.05
                            anchors.top: welderSelComboBox.top
                            anchors.topMargin: welderSelComboBox.height*0.30
                            font.pixelSize: welderSelComboBox.height*0.40
                            textFormat: Text.RichText
                            clip: true
                            text:welderSelComboBox.currentIndex>=0 ?welderSelComboBox.model.get(welderSelComboBox.currentIndex).key:""
                        }
                        model:localmultiWelderListModel

                        Connections{
                            target: multiWelderInterface
                            onWelderConnectedChanged:
                            {
                                var value=multiWelderInterface.m_WelderConnected
                                var id=multiWelderInterface.m_welderId
                                var key = "Welder"+" "+(id  +1)
                                var itemText = key + " - " + value+ " - " + id;
                                closeAlertWin(key)
                                multiWelderListModel.append({ "text": itemText, "key": key, "value": value ,"id":id });
                                localmultiWelderListModel.append({ "text": itemText, "key": key, "value": value ,"id":id});
                                if(multiWelderListModel.count==1){
                                    welderSelComboBox.currentIndex=0
                                    welderdisplayLabel.text=localmultiWelderListModel.get(0).key
                                }
                            }
                            onWelderDisconnectChanged:
                            {
                                var curValue="";
                                for (var i=0; i<localmultiWelderListModel.count; ++i)
                                {
                                    if (localmultiWelderListModel.get(i).value==multiWelderInterface.m_welderDisconnect)
                                    {
                                        prevactiveWelderid=localmultiWelderListModel.get(i).key
                                        var currentlySelectedIndex=welderSelComboBox.currentIndex
                                        if(currentlySelectedIndex==i){
                                            activeWelderid=-1
                                            welderSelComboBox.currentIndex=-1;
                                            welderdisplayLabel.text=""
                                            activeWelder(-1)
                                        }
                                        curValue=multiWelderListModel.get(i).key;
                                        mainWindow.showDisconnectionAlert()
                                        localmultiWelderListModel.remove(i);
                                        multiWelderListModel.remove(i)
                                        checkActvDisconWelder();
                                        welderSelComboBox.currentIndex=-1
                                        break;
                                    }
                                }

                                if(localmultiWelderListModel.count==0){
                                    welderdisplayLabel.text=""
                                    activeWelder(-1)
                                }
                                if(localmultiWelderListModel.count==1){
                                    welderSelComboBox.currentIndex=0
                                }
                            }
                        }
                        Component.onCompleted: {
                        }
                        onCurrentIndexChanged: {
                            if(currentIndex===-1 && localmultiWelderListModel.count===0){
                                activeWelder(-1);
                            }
                            if(currentIndex>=0){
                                welderId=multiWelderListModel.get(currentIndex).key
                                prevactiveWelderid=multiWelderListModel.get(currentIndex).key
                                activeWelderid=multiWelderListModel.get(currentIndex).id                               
                                mainWindow.currentIndex = localmultiWelderListModel.get(currentIndex).id                              
                                multiWelderInterface.setActiveWelder(localmultiWelderListModel.get(currentIndex).id);
                                welderdisplayLabel.text=localmultiWelderListModel.get(currentIndex).key
                                activeWelder(activeWelderid);
                                //multiWelderInterface.setActiveWelder(multiWelderListModel.get(currentIndex).id);
                            }
                        }
                        delegate: Item {
                            width: welderSelComboBox.width
                            height: welderSelComboBox.height*0.85
                            Rectangle{
                                width:parent.width
                                height: parent.height
                                border.color: "black"
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        welderSelComboBox.currentIndex = index
                                        welderSelComboBox.popup.visible=false
                                    }
                                    hoverEnabled: true
                                    onEntered: {
                                        parent.color="lightblue"
                                    }
                                    onExited: {
                                        parent.color="transparent"
                                    }
                                    ColumnLayout {
                                        anchors.left: parent.left
                                        anchors.leftMargin: welderSelComboBox.width*0.05
                                        anchors.top: parent.top
                                        anchors.topMargin: welderSelComboBox.height*0.15
                                        spacing: 2
                                        Text {
                                            id:welderNameCmbx
                                            text: model.key
                                            font.pixelSize: welderSelComboBox.height*0.40
                                        }
                                    }
                                }
                            }
                        }
                        popup: Popup {
                            y: welderSelComboBox.height
                            width: welderSelComboBox.width
                            implicitHeight: contentItem.implicitHeight
                            padding: 0
                            contentItem: ListView {
                                clip: true
                                implicitHeight: contentHeight
                                model: welderSelComboBox.popup.visible ? welderSelComboBox.delegateModel : null
                            }
                        }
                    }

                    Image
                    {
                        id: manageImageicon
                        source: "qrc:/Images/system.svg"
                        fillMode: Image.PreserveAspectFit
                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                mainWindow.showMultiWelderInformation()
                            }
                        }
                    }
                }
            }
            //Multiweldercombox --------END


            Item {
                id: menuParentList
                anchors.left: parent.left
                anchors.leftMargin: Math.round(48 * Style.scaleHint)
                anchors.top: multiWelderLayout.bottom
                anchors.topMargin: Math.round(90 * Style.scaleHint)           //  30 * Style.scaleHint--original
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                Column
                {
                    id: menuOptionLayout
                    anchors.fill: parent
                    spacing: Math.round(22 * Style.scaleHint)
                    Repeater
                    {
                        model: leftMenuModelData
                        delegate: Item
                        {
                            id: menuOptionDelegate
                            height: imageSize + Math.round(22 * Style.scaleHint)
                            width: parent.width
                            Rectangle{
                                id: menuImageTextLayout
                                height: imageSize
                                width: parent.width
                                color: "transparent"
                                border.color: "transparent"
                                Row
                                {
                                    spacing: Math.round(21 * Style.scaleHint)
                                    Image{
                                        id: menuOptionImage
                                        width: imageSize
                                        height: imageSize
                                        source: model.MenuIcon
                                        fillMode: Image.PreserveAspectFit
                                        sourceSize.width: imageSize
                                        sourceSize.height: imageSize
                                        smooth: true
                                    }
                                    Text{
                                        height: imageSize
                                        color: model.MenuColor
                                        font.family: Style.regular.name
                                        text: model.MenuName
                                        anchors.verticalCenter: menuOptionImage.verticalCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                                    }
                                }
                                MouseArea
                                {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:
                                    {
                                        cursorShape = Qt.PointingHandCursor
                                    }
                                    onClicked:
                                    {
                                        leftActionAnimationReturn.restart()
                                        mainWindow.hideMainWindowOpacity()
                                        menuIndex = model.MenuIndex
                                        menuName = model.MenuName
                                        mainWindow.menuParentOptionSelect(menuIndex)
                                    }

                                }
                            }

                            Rectangle{
                                id: lineSeparator
                                width: Math.round(221 * Style.scaleHint)
                                height: menuSepratorHeight
                                anchors.left: menuImageTextLayout.left
                                anchors.top: menuImageTextLayout.bottom
                                anchors.topMargin: Math.round(20 * Style.scaleHint)
                                color: Style.whiteFontColor
                                visible: model.MenuSeparator
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: leftMenuOutsideArea
        width: parent.width/5 + parent.width - arcWidth
        height: parent.height
        opacity: 0
        anchors.right: parent.right
        anchors.top: parent.top
        color: "transparent"
        visible: true
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                leftActionAnimationReturn.restart()
                mainWindow.hideMainWindowOpacity()
            }
        }
    }
}

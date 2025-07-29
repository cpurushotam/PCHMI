/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Alert popup window to notify user that welder is disconnected.

 **********************************************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Popup
{
    id: alertPopup

    /* Properties declaration */
    readonly property int qmlscreenIndicator:  UIScreenEnum.ALERTWINDOW
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    property string qmltextAlert:                 "Alert"
    property string qmltextReconnect:             "Troubleshooting Tips:"
    property string qmltextReconnect2:             "1. Check if the cable connections are intact."
    property string qmltextReconnect3:             "2. Ensure the power supply is running properly."
    property string qmltextReconnect4:             "3. Try rebooting the HMI and check again."

    property string qmltextDisconnected:          "Disconnected."
    property string qmltextWelder:                "Welder"
    property string  qmltextOk:                   "Ok"
    property string  qmltextSwitchActvWelder:     "Switching to "
    property var id
    property int actvId:                         -1
    property var qmlTextArray: [qmltextAlert, qmltextReconnect,qmltextDisconnected,qmltextWelder,qmltextOk,qmltextSwitchActvWelder, qmltextReconnect2, qmltextReconnect3, qmltextReconnect4]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum. ALERTWINDOW, qmlTextArray)
        qmltextAlert = qmlTextArray[textEnum.textAlertIdx]
        qmltextReconnect = qmlTextArray[textEnum.textReconnectIdx]
        qmltextDisconnected=qmlTextArray[textEnum.textDisconn]
        qmltextWelder=qmlTextArray[textEnum.textWelder]
        qmltextOk=qmlTextArray[textEnum.textOk]
        qmltextSwitchActvWelder=qmlTextArray[textEnum.textSwitchWelder]
        qmltextReconnect2 = qmlTextArray[textEnum.textReconnect2Idx]
        qmltextReconnect3 = qmlTextArray[textEnum.textReconnect3Idx]
        qmltextReconnect4 = qmlTextArray[textEnum.textReconnect4Idx]
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    /*Slot for getting disconnected welder id to display on AlertWindow.*/
    Connections {
        target: leftMenuLoader.item

        /* Slot to notify user about disconnection of welder. */
        function onDisContWelderID(discWelderId)
        {
            reconnectText.visible=true
            id=discWelderId;
            var itemText = id
            dialogText.visible=true
            dialogText.text = discWelderId + " " + qmltextDisconnected
            disconnectedWelderIds.append({"id":discWelderId})
            dialogText.leftPadding= popupBackground.width * 0.04
        }

        /* Function to notify user regarding active welder disconnected thus switing to next available welder */
        function onSwitchActiveWelderID(swtchId,nxtActvWelder)
        {
            disconnectedWelderIds.append({"id":swtchId})
            reconnectText.visible=false
            actvId=nxtActvWelder;
            dialogText.visible=true
            dialogText.text= swtchId + " " + qmltextDisconnected + " " +  qmltextSwitchActvWelder + " " +nxtActvWelder
        }

        /* Slot to notify user about reconnection of welder. */
        function onCloseAlertWin(reconnWelderId){
            for (var i=0; i<disconnectedWelderIds.count; i++)
            {
                if(disconnectedWelderIds.get(i).id === reconnWelderId)
                {
                    disconnectedWelderIds.remove(i);
                    if(disconnectedWelderIds.count === 0)
                    {
                        alertPopup.close()
                    }
                }
            }
        }
    }

    /* Listmodel to store disconnected welder info */
    ListModel
    {
        id:disconnectedWelderIds
    }

    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject
    {
        id: textEnum
        readonly property int textAlertIdx:       0
        readonly property int textReconnectIdx:   1
        readonly property int textDisconn:        2
        readonly property int textWelder:         3
        readonly property int textOk:             4
        readonly property int textSwitchWelder:   5
        readonly property int textReconnect2Idx:  6
        readonly property int textReconnect3Idx:  7
        readonly property int textReconnect4Idx:  8
    }

    visible: false
    x:mainWindow.width*0.30
    y:mainWindow.height*0.08
    width:    parent.width*0.30
    height: parent.height*0.40
    focus: true
    dim: true
    closePolicy: Popup.NoAutoClose
    background: Rectangle
    {
        id: popupBackground
        anchors.fill: parent
        implicitWidth: parent.width
        implicitHeight: parent.height
        opacity: 1
        color:"#ffffff"
        border.width: 0
        /*Header rectangle for dispalying name of window.*/
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            clip: true
            implicitHeight:parent.height*0.15
            color: "#004B8D"
            Text {
                id: headername
                anchors.left: parent.left
                anchors.leftMargin:parent.width*0.05
                anchors.verticalCenter: parent.verticalCenter
                text: qmltextAlert
                color: Style.whiteFontColor
                font{
                    family: Style.regular.name
                    pixelSize:numpadHeader.height*0.50
                }
            }
        }
        Image {
            id: alertIcon
            source: "qrc:/Images/WelderDisconnection.png"
            width: parent.width*0.20
            height:parent.height*0.20
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.45
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.25
            sourceSize.width: alertIcon.width
            sourceSize.height: alertIcon.height
            smooth: true
        }

        /*Text to display the disconnected welder on Alert window */
        Text {
            id: dialogText
            width: parent.width * 0.8  // Adjust the width as needed
            wrapMode: Text.Wrap  // Use Text.Wrap to prevent breaking individual words
            anchors.top: alertIcon.bottom
            anchors.topMargin: parent.height * 0.06
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.15
            visible: false
            color: "#000000"
            font {
                family: Style.regular.name
                pixelSize: numpadHeader.height * 0.45
            }
        }

        Text {
            id: reconnectText
            anchors.top: dialogText.bottom
            anchors.topMargin: Math.round(10 * Style.scaleHint)
            anchors.left: dialogText.left
            anchors.leftMargin: Math.round(25 * Style.scaleHint)
            text: qmltextReconnect + "\n" + qmltextReconnect2 + "\n" + qmltextReconnect3 + "\n" +qmltextReconnect4;
            color: "#000000"
            font {
                family: Style.regular.name
                pixelSize: numpadHeader.height * 0.25
            }
        }
    }

    BransonPrimaryButton
    {
        id: ok
        visible: false /*As no action permitted from HMI*/
        implicitWidth:parent.width*0.20
        implicitHeight: parent.height*0.10
        fontSize:parent.height* 0.05
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.10
        anchors.left: parent.left
        anchors.leftMargin:parent.width*0.40
        text: qmltextOk
        font.family: Style.regular.name
        buttonColor: Style.blueFontColor
        textColor: "#FFFFFF"
        onClicked: {
            reconnectText.visible=true
            if(disconnectedWelderIds.count === 0)
            {
                alertWindow.close()
            }
            else
            {
                disconnectedWelderIds.remove(disconnectedWelderIds.count-1)
                if(disconnectedWelderIds.count === 0)
                {
                    alertWindow.close()
                }
                var removedId = disconnectedWelderIds.get(disconnectedWelderIds.count-1).id;
                dialogText.text = qmltextWelder + " " + (removedId+1) + " " + qmltextDisconnected ;
            }
        }
    }
}

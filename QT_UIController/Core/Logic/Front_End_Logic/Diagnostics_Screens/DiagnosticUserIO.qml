/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the UserIO Screen .

***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import Style 1.0
import Qt5Compat.GraphicalEffects
import Com.Branson.UIScreenEnum 1.0
import AxisDefine 1.0
import QtQuick.Layouts 1.15
 import QtQuick.VirtualKeyboard 2.2
import "./../Diagnostics_Screens"
import "./../Common_Logic"

Item
{
    id:diagnosticUserIO

    property string qmltextMenuName           : "User IO"
    property string qmltextDigitalIP          : "Digital Inputs"
    property string qmltextDigitalOP          : "Digital Outputs"
    property string qmltextAnalogIP           : "Analog Inputs"
    property string qmltextAnalogOP           : "Analog Outputs"
    property string qmltextLowInput           : "0 V"
    property string qmltextHighInput          : "24 V"
    property string qmltextVoltage            : "V"
    property string qmltextStop               : "STOP"
    property string qmltextRefresh            : "REFRESH OUTPUT"

    property string qmltextDigitalIn_1        : "Digital_In_1"
    property string qmltextDigitalIn_2        : "Digital_In_2"
    property string qmltextDigitalIn_3        : "Digital_In_3"
    property string qmltextDigitalIn_4        : "Digital_In_4"
    property string qmltextDigitalIn_5        : "Digital_In_5"
    property string qmltextDigitalIn_6        : "Digital_In_6"
    property string qmltextDigitalIn_7        : "Digital_In_7"
    property string qmltextDigitalIn_8        : "Digital_In_8"
    property string qmltextDigitalIn_9        : "Digital_In_9"
    property string qmltextDigitalOut_1       : "Digital_Out_1"
    property string qmltextDigitalOut_2       : "Digital_Out_2"
    property string qmltextDigitalOut_3       : "Digital_Out_3"
    property string qmltextDigitalOut_4       : "Digital_Out_4"
    property string qmltextDigitalOut_5       : "Digital_Out_5"
    property string qmltextDigitalOut_6       : "Digital_Out_6"
    property string qmltextDigitalOut_7       : "Digital_Out_7"
    property string qmltextDigitalOut_8       : "Digital_Out_8"

    property string qmltextAnalogIn_1         : "Analog_In_1"
    property string qmltextAnalogIn_2         : "Analog_In_2"
    property string qmltextAnalogOut_1        : "Analog_Out_1"
    property string qmltextAnalogOut_2        : "Analog_Out_2"


    property var qmlTextArray: [qmltextDigitalIP, qmltextDigitalOP, qmltextAnalogIP, qmltextAnalogOP , qmltextStop, qmltextRefresh]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTIC_USERIO, qmlTextArray)
        qmltextDigitalIP = qmlTextArray[textEnum.textDigIpIdx]
        qmltextDigitalOP = qmlTextArray[textEnum.textDigOpIdx]
        qmltextAnalogIP = qmlTextArray[textEnum.textAnalogIPIdx]
        qmltextAnalogOP = qmlTextArray[textEnum.textAnalogOPIdx]
        qmltextStop      = qmlTextArray[textEnum.textStopIdx]
        qmltextRefresh = qmlTextArray[textEnum.textRefreshIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTIC_USERIO, qmltextMenuName)
    }

    QtObject
    {
        id: textEnum
        readonly property int textDigIpIdx            : 0
        readonly property int textDigOpIdx            : 1
        readonly property int textAnalogIPIdx         : 2
        readonly property int textAnalogOPIdx         : 3
        readonly property int textStopIdx             : 4
        readonly property int textRefreshIdx          : 5

    }

    Component.onCompleted:
    {
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTIC_USERIO)
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTIC_USERIO
        digitalIpModel.resetControlModel()
        digitalOpModel.resetControlModel()

        for(var i =0 ;i < digitalIpModel.count; i++ )
        {
            digitalIpModel.get(i).pinenabled = DiagnosticUserIOObj.setDigitalInputs(i)
        }
    }


    Connections
    {
        target: DiagnosticUserIOObj
        function onDiagnosticUserIOChanged()
        {
            digitalIpModel.resetControlModel()
            for(var i =0 ;i < digitalIpModel.count; i++ )
            {
                digitalIpModel.get(i).pinenabled = DiagnosticUserIOObj.setDigitalInputs(i)
            }
        }
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    function assignPinValues(index , value)
    {
        DiagnosticUserIOObj.setDigitalOpPinFromHMI(index ,value)
    }

    ListModel{

        id:digitalOpModel
        function resetControlModel()
        {
            digitalOpModel.clear()

            digitalOpModel.append({"Title":      qmltextDigitalOut_1,
                                      "pinenabled":    false,
                                      "Index":      0})
            digitalOpModel.append({"Title":      qmltextDigitalOut_2,
                                      "pinenabled":    false,
                                      "Index":      1})
            digitalOpModel.append({"Title":      qmltextDigitalOut_3,
                                      "pinenabled":    false,
                                      "Index":      2})
            digitalOpModel.append({"Title":      qmltextDigitalOut_4,
                                      "pinenabled":    false,
                                      "Index":      3})
            digitalOpModel.append({"Title":      qmltextDigitalOut_5,
                                      "pinenabled":    false,
                                      "Index":      4})
            digitalOpModel.append({"Title":      qmltextDigitalOut_6,
                                      "pinenabled":    false,
                                      "Index":      5})
            digitalOpModel.append({"Title":      qmltextDigitalOut_7,
                                      "pinenabled":    false,
                                      "Index":      6})
            digitalOpModel.append({"Title":      qmltextDigitalOut_8,
                                      "pinenabled":    false,
                                      "Index":      7})
        }
    }

    ListModel{

        id:digitalIpModel
        function resetControlModel()
        {
            digitalIpModel.clear()

            digitalIpModel.append({"Title":      qmltextDigitalIn_1,
                                      "pinenabled":    true,
                                      "Index":      0})
            digitalIpModel.append({"Title":      qmltextDigitalIn_2,
                                      "pinenabled":    true,
                                      "Index":      1})
            digitalIpModel.append({"Title":      qmltextDigitalIn_3,
                                      "pinenabled":    true,
                                      "Index":      2})
            digitalIpModel.append({"Title":      qmltextDigitalIn_4,
                                      "pinenabled":    true,
                                      "Index":      3})
            digitalIpModel.append({"Title":      qmltextDigitalIn_5,
                                      "pinenabled":    true,
                                      "Index":      4})
            digitalIpModel.append({"Title":      qmltextDigitalIn_6,
                                      "pinenabled":    true,
                                      "Index":      5})
            digitalIpModel.append({"Title":      qmltextDigitalIn_7,
                                      "pinenabled":    true,
                                      "Index":      6})
            digitalIpModel.append({"Title":      qmltextDigitalIn_8,
                                      "pinenabled":    false,
                                      "Index":      7})
            digitalIpModel.append({"Title":      qmltextDigitalIn_9,
                                      "pinenabled":    false,
                                      "Index":      8})
        }
    }



    Flickable
    {
        id: infoScrollRec
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        contentHeight: height*2.15
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar { }

        Rectangle{
            id:digitalIpTextRect
            width: parent.width* 0.42
            height: mainWindow.height *0.09
            border.color: "transparent"
            color:"transparent"
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.05
            anchors.top: infoScrollRec.top
            anchors.topMargin: mainWindow.height *0.1

            Text {
                id: digitalIPtext
                text: qmltextDigitalIP
                font.pixelSize: parent.height *0.40
                color: Style.blackFontColor
                anchors.top: digitalIpTextRect.top
                anchors.topMargin: parent.height *0.4
            }


        }
        Rectangle{
            id:digitalIp
            width: parent.width* 0.42
            height: mainWindow.height *0.60
            border.color: "black"
            color:"white"
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.05
            anchors.top: parent.top
            anchors.topMargin: mainWindow.height *0.10


            Rectangle{
                id: separatorLine1
                width: parent.width *0.90
                height: 1
                anchors.top: digitalIp.top
                anchors.topMargin: digitalIp.height*0.1
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                color: Style.blackFontColor
            }

            ListView
            {
                id: digitalIPListview
                width: parent.width
                height: parent.height *0.85
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: separatorLine1.bottom
                anchors.topMargin: parent.height *0.04
                model: digitalIpModel
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { }
                clip: true
                verticalLayoutDirection : ListView.TopToBottom

                delegate: RowLayout
                {
                    id:rowlayoutdigitalip
                    spacing: digitalIPListview.width *0.15

                    Rectangle{
                        width: digitalIPListview.width *0.25
                        height: digitalIPListview.height *0.09
                        color: "transparent"
                        Text
                        {
                            text: model.Title
                            font.pixelSize: 20
                        }
                    }
                    BransonRadioButton
                    {
                        id:inputLow
                        labelText:   qmltextLowInput
                        offColor:Style.blackFontColor
                        checked: model.pinenabled === false ? true : false
                        enabled: false
                        radioEnableColor: "green"
                    }
                    BransonRadioButton{
                        id:inputHigh
                        labelText: qmltextHighInput
                        checked: model.pinenabled === true ? true :false
                        enabled: false
                        radioEnableColor: "green"

                    }
                }

            }

        }


        Rectangle{
            id:digitalopTextRect
            width: parent.width* 0.42
            height: mainWindow.height *0.09
            border.color: "transparent"
            color:"transparent"
            anchors.left: digitalIpTextRect.right
            anchors.leftMargin: parent.width *0.05
            anchors.top: infoScrollRec.top
            anchors.topMargin: mainWindow.height *0.1

            Text {
                id: digitalOPtext
                text: qmltextDigitalOP
                font.pixelSize: parent.height *0.40
                color: Style.blackFontColor
                anchors.top: digitalopTextRect.top
                anchors.topMargin: parent.height *0.4
            }


        }
        Rectangle{
            id:digitalOp
            width: parent.width* 0.42
            height: mainWindow.height *0.60
            border.color: "black"
            color:"white"
            anchors.left: digitalIp.right
            anchors.leftMargin: parent.width *0.05
            anchors.top: parent.top
            anchors.topMargin: mainWindow.height *0.1

            Rectangle{
                id: separatorLine2
                width: parent.width *0.90
                height: 1
                anchors.top: digitalOp.top
                anchors.topMargin: digitalOp.height*0.1
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.05
                color: Style.blackFontColor
            }

            ListView
            {
                id: digitalOPListview
                width: parent.width
                height: parent.height *0.85
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: separatorLine2.bottom
                anchors.topMargin: parent.height *0.04
                model: digitalOpModel
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { }
                clip: true
                verticalLayoutDirection : ListView.TopToBottom

                delegate: RowLayout
                {
                    spacing: parent.width *0.15
                    id:rowlayoutdigitalOP

                    Rectangle{
                        width: digitalIPListview.width *0.25
                        height: digitalIPListview.height *0.09
                        color: "transparent"
                        Text
                        {
                            text: model.Title
                            font.pixelSize: 20
                        }
                    }
                    BransonRadioButton
                    {
                        id:inputLow1
                        labelText:   qmltextLowInput
                        offColor:Style.blackFontColor
                        checked: model.pinenabled === false ? true : false
                        onCheckedChanged: {
                            if(checked === true){
                                assignPinValues(model.Index, 0)

                            }
                        }
                    }
                    BransonRadioButton{
                        id:inputHigh1
                        labelText: qmltextHighInput
                        checked: model.pinenabled === true ? true :false
                        onCheckedChanged: {
                            if(checked === true){
                                assignPinValues(model.Index, 1)

                            }
                        }
                    }
                }

            }

        }


        /*Analog Input*/
        Rectangle{
            id:analogIpTextRect
            width:  parent.width* 0.42
            height: mainWindow.height *0.09
            border.color: "transparent"
            color:"transparent"
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.05
            anchors.top: digitalIp.bottom
            anchors.topMargin: mainWindow.height *0.02

            Text {
                id: analogIptext
                text: qmltextAnalogIP
                font.pixelSize: parent.height *0.40
                color: Style.blackFontColor
                anchors.top: analogIpTextRect.top
                anchors.topMargin: parent.height *0.3
            }

        }

        /*Analog input 1*/
        Rectangle{
            id: rectAnalogIp
            color:  "#d7d9db"
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.05
            anchors.top: analogIpTextRect.bottom
            width:  parent.width* 0.42
            height:  mainWindow.height *0.12
            enabled: false
            Text{
                id:anlogIPText
                text: qmltextAnalogIn_1
                font.pixelSize: parent.height *0.25
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
            }

            BransonLineEdit
            {
                id: analogInput1
                width: parent.width *0.40
                height: parent.height *0.40
                anchors.left: anlogIPText.right
                anchors.leftMargin: parent.width *0.25
                text:(DiagnosticUserIOObj.AnalogInput_1).toFixed(3)  + " "+ qmltextVoltage
                color: "black"
                focus: true
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectWords
                clip: true
            }

        }
        Rectangle{
            id: rectAnalogIp2
            color:  "#d7d9db"
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.05
            anchors.top: rectAnalogIp.bottom
            anchors.topMargin: mainWindow.height *0.02
            width:  parent.width* 0.42
            height:  mainWindow.height *0.12
            enabled: false

            Text{
                id:anlogIPText2
                text: qmltextAnalogIn_2
                font.pixelSize: parent.height *0.25
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
            }
            BransonLineEdit
            {
                id: analogInput2
                width: parent.width *0.40
                height: parent.height *0.40
                anchors.left: anlogIPText2.right
                anchors.leftMargin: parent.width *0.25
                text: (DiagnosticUserIOObj.AnalogInput_2).toFixed(3)  + " "+qmltextVoltage
                focus: true
                color: "black"
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectWords
                clip: true
            }

        }

        /*Analog Output*/
        Rectangle{
            id:analogOpTextRect
            width:  parent.width* 0.42
            height: mainWindow.height *0.09
            border.color: "transparent"
            color:"transparent"
            anchors.left: analogIpTextRect.right
            anchors.leftMargin: parent.width *0.05
            anchors.top: digitalOp.bottom
            anchors.topMargin: mainWindow.height *0.02

            Text {
                id: analogOptext
                text: qmltextAnalogOP
                font.pixelSize: parent.height *0.40
                color: Style.blackFontColor
                anchors.top: analogOpTextRect.top
                anchors.topMargin: parent.height *0.3
            }

        }

        /*Analog output 1*/
        Rectangle{
            id: rectAnalogOp
            color:  "#d7d9db"
            anchors.left: rectAnalogIp.right
            anchors.leftMargin: parent.width *0.05
            anchors.top: analogOpTextRect.bottom
            width:  parent.width* 0.42
            height:  mainWindow.height *0.12
            Text{
                id:anlogOPText
                text: qmltextAnalogOut_1
                font.pixelSize: parent.height *0.25
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
            }

            BransonLineEdit
            {
                id: analogOutput1
                width: parent.width *0.40
                height: parent.height *0.40
                anchors.left: anlogOPText.right
                anchors.leftMargin: parent.width *0.25
                text: (DiagnosticUserIOObj.AnalogOutput_1).toFixed(3)  + " "+ qmltextVoltage
                color: "black"
                focus: true
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectWords
                clip: true
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        mainWindow.showPrimaryNumpad(qmltextAnalogOut_1,qmltextVoltage, 3,  0, 10, DiagnosticUserIOObj.AnalogOutput_1)
                    }
                }
            }
        }

        Rectangle{
            id: rectAnalogOp2
            color:  "#d7d9db"
            anchors.left: rectAnalogIp2.right
            anchors.leftMargin: parent.width *0.05
            anchors.top: rectAnalogOp.bottom
            anchors.topMargin: mainWindow.height *0.02
            width:  parent.width* 0.42
            height:  mainWindow.height *0.12
            Text{
                id:anlogOPText2
                text: qmltextAnalogOut_2
                font.pixelSize: parent.height *0.25
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.05
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
            }

            BransonLineEdit
            {
                id: analogOutput2
                width: parent.width *0.40
                height: parent.height *0.40
                anchors.left: anlogOPText2.right
                anchors.leftMargin: parent.width *0.25
                text: (DiagnosticUserIOObj.AnalogOutput_2).toFixed(3)  + " "+ qmltextVoltage
                color: "black"
                focus: true
                anchors.top: parent.top
                anchors.topMargin: parent.height *0.35
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectWords
                clip: true

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        mainWindow.showPrimaryNumpad(qmltextAnalogOut_2,qmltextVoltage, 3,  0, 10, DiagnosticUserIOObj.AnalogOutput_2)
                    }
                }
            }
        }

        //Stop button
        BransonPrimaryButton
        {
            id: stopbutton
            implicitWidth: Math.round(115 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style0  * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: parent.width *0.20
            anchors.top: rectAnalogIp2.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            text: qmltextStop
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name
            onClicked:
            {
                //Onclicked screen must not the values of digital out and analog out to ASC.
                DiagnosticUserIOObj.sendStopRequest()
            }
        }

        //Refresh button
        BransonPrimaryButton
        {
            id: refreshbutton
            implicitWidth: Math.round(115 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style0  * Style.scaleHint)
            anchors.left: stopbutton.right
            anchors.leftMargin: parent.width *0.02
            anchors.top: rectAnalogIp2.bottom
            anchors.topMargin: Math.round(15 * Style.scaleHint)
            text: qmltextRefresh
            buttonColor: Style.buttonBackgroundColor
            font.family: Style.regular.name
            onClicked:
            {
                //Onclicked screen must send values of digital out and analog out to ASC.
                DiagnosticUserIOObj.sendRefreshRequest()
            }
        }
    }


}

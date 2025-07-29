/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 UserIO - Industrial Ethernet I/O tab implementation.

 **********************************************************************************************************/
import QtQml.Models 2.15
import QtQuick.Layouts
import Com.Branson.SystemTypeDef 1.0
import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Style 1.0
import QtQuick.Window 2.2
import Style
import QtQuick.Window
import QtQuick.Controls
import QtQuick
import Com.Branson.UIScreenEnum 1.0
import QtQuick.VirtualKeyboard.Settings 2.15
import "./../Common_Logic"

Item {

    property string qmltextControlWrdsInputs               : "CONTROL WORDS"
    property string qmltextStatusWrdsInputs              : "STATUS WORDS"
    property string qmltextResetToDefault              : "RESET TO DEFAULT"
    property string qmltextCancel                      : "CANCEL"
    property string qmltextSave                        : "SAVE"


    property string qmltextCntrlWrd_1                  : "Control Word 1"
    property string qmltextCntrlWrd_2                  : "Control Word 2"
    property string qmltextCntrlWrd_3                  : "Control Word 3"

    property string qmltextStatusWrd_1                 : "Status Word 1"
    property string qmltextStatusWrd_2                 : "Status Word 2"
    property string qmltextStatusWrd_3                 : "Status Word 3"

    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)

    property var qmlTextArray: [qmltextControlWrdsInputs, qmltextStatusWrdsInputs, qmltextResetToDefault, qmltextCancel, qmltextSave,qmltextCntrlWrd_1, qmltextCntrlWrd_2,qmltextStatusWrd_1, qmltextStatusWrd_1
                                ,qmltextCntrlWrd_3, qmltextStatusWrd_3]
    property var qmlTextCntrlWrdInPin: [qmltextCntrlWrd_1, qmltextCntrlWrd_2, qmltextCntrlWrd_3]
    property var qmlTextStsWrdOutPin: [qmltextStatusWrd_1, qmltextStatusWrd_2, qmltextStatusWrd_3]

    property var selectedControlWrdIponCombobx: []
    property var selectedStatusWrdonCombobx: []

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL , qmlTextArray)
        qmltextControlWrdsInputs = qmlTextArray[textEnum.textCntrlWrdInputsIdx]
        qmltextStatusWrdsInputs = qmlTextArray[textEnum.textStatusWrdOutputsIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextCntrlWrd_1 = qmlTextArray[textEnum.textCntrlWrdIn1Idx]
        qmltextCntrlWrd_2 = qmlTextArray[textEnum.textCntrlWrdIn2Idx]
        qmltextStatusWrd_1 =qmlTextArray[textEnum.textStatusWrd1Idx]
        qmltextStatusWrd_2= qmlTextArray[textEnum.textStatusWrd2Idx]
        qmltextCntrlWrd_3 = qmlTextArray[textEnum.textCntrlWrd3Idx]
        qmltextStatusWrd_3 =  qmlTextArray[textEnum.textStatusWrd3Idx]
    }


    QtObject{
        id:textEnum
        readonly property int textCntrlWrdInputsIdx         : 0
        readonly property int textStatusWrdOutputsIdx       : 1
        readonly property int textResetToDefaultIdx         : 2
        readonly property int textCancelIdx                 : 3
        readonly property int textSaveIdx                   : 4
        readonly property int textCntrlWrdIn1Idx            : 5
        readonly property int textCntrlWrdIn2Idx            : 6
        readonly property int textStatusWrd1Idx             : 7
        readonly property int textStatusWrd2Idx             : 8
        readonly property int textCntrlWrd3Idx              : 9
        readonly property int textStatusWrd3Idx             :10
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
        updateLanguage();
        IndustrialEthIOComboBoxManager.optionSelection()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL

        comboBoxIpModel.clear()
        //Control Word Input model
        for(var i = 0;i< IndustrialEthIOComboBoxManager.getCountOfControlWrdIpModel();i++)
        {
            var text=IndustrialEthIOComboBoxManager.getSelectedControlWrdComboBox(i)
            selectedControlWrdIponCombobx[i]=text
        }
        cntrlWrdInputListView.model = selectedControlWrdIponCombobx
        for(var i = 0;i< IndustrialEthIOComboBoxManager.getTotalSizeofControlWrdIpList();i++)
        {
            var text = IndustrialEthIOComboBoxManager.getControlWrdIp(i)
            comboBoxIpModel.append({"text":text});
        }
        cntrlWrdInputListView.update()


        //Status Word Output Model.
        for(var j = 0;j< IndustrialEthIOComboBoxManager.getCountOfStatusWrdOpModel();j++)
        {
            var text=IndustrialEthIOComboBoxManager.getSelectedStatusWrdOpComboBox(j)
            selectedStatusWrdonCombobx[j]=text
        }
        statusWrdOutputListView.model = selectedStatusWrdonCombobx
        comboBoxOpModel.clear()
        for(var k = 0;k< IndustrialEthIOComboBoxManager.getTotalSizeofStatusWordOPList();k++)
        {
            var text=IndustrialEthIOComboBoxManager.getStatusWordOP(k)
            comboBoxOpModel.append({"text":text});
        }

    }

    ListModel
    {
        id: comboBoxIpModel
    }

    ListModel
    {
        id: comboBoxOpModel
    }
    Rectangle {
        id:mainRectangle
        width: mainWindow.showWidth
        height: mainWindow.showHeight *0.65
        anchors.top: parent.top
        anchors.topMargin: Math.round(5 * Style.scaleHint)
        color: Style.backgroundColor
        clip:true

        Rectangle{
            id:controlwrdIpHeaderText
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            color: Style.backgroundColor
            clip:true
            Text{
                text:qmltextControlWrdsInputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
        }

        Rectangle{
            id:statusWrdOpHeadertext
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: controlwrdIpHeaderText.right
            color: Style.backgroundColor
            clip:true
            Text{
                text: qmltextStatusWrdsInputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        ListView{
            id: cntrlWrdInputListView
            width: parent.width*0.45
            height:Math.round(250 * Style.scaleHint)
            anchors.top: controlwrdIpHeaderText.bottom
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            spacing: Math.round(10 * Style.scaleHint)
            model: 2
            boundsBehavior: ListView.StopAtBounds
            clip: true
            highlightRangeMode: ListView.StrictlyEnforceRange

            delegate:
                Rectangle
            {
                id: cntrlWrdDelegateRectangle
                width: Math.round(380 * Style.scaleHint)
                height:Math.round(70 * Style.scaleHint)
                color: Style.contentBackgroundColor
                clip: true
                enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY) ? false: true

                Text {
                    id: textPinTitle
                    anchors.left: cntrlWrdIOEnableSwitch.left
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    color: Style.blackFontColor
                    font.pixelSize: Math.round(15 * Style.scaleHint)
                    text: qmlTextCntrlWrdInPin[index]
                }

                BransonSwitch {
                    id: cntrlWrdIOEnableSwitch
                    anchors.verticalCenter: cntrlWrdComboBox.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(15 * Style.scaleHint)
                    rectWidth: Math.round(30 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    checked:IndustrialEthIOComboBoxManager.getControlWrdUserIOIpPinEnable(index)
                    onCheckedChanged:
                    {
                        IndustrialEthIOComboBoxManager.setControlWrdIOPinEnable(index,checked)
                    }
                }

                Rectangle
                {
                    id:cntrlWrdComboBox
                    width: Math.round(175 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(40 * Style.scaleHint)
                    anchors.left: cntrlWrdIOEnableSwitch.right
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    color: "transparent"

                    BransonComboBox
                    {
                        id: cntrlWrdInputComboBox
                        currentIndex: -1
                        minWidth: Math.round(175 * Style.scaleHint)
                        minHeight: Math.round(25 * Style.scaleHint)
                        comboboxpopupheight: Math.round(105 * Style.scaleHint)
                        enabled: cntrlWrdIOEnableSwitch.checked
                        // Set the model for each ComboBox
                        model: comboBoxIpModel
                        Label {
                            id: cntrlWrdDisplayLabel
                            Layout.fillWidth: cntrlWrdInputComboBox
                            anchors.left: cntrlWrdInputComboBox.left
                            anchors.leftMargin: cntrlWrdInputComboBox.width*0.05
                            anchors.top: cntrlWrdInputComboBox.top
                            anchors.topMargin: cntrlWrdInputComboBox.height*0.30
                            font.pixelSize: cntrlWrdInputComboBox.height*0.40
                            textFormat: Text.RichText
                            text:selectedControlWrdIponCombobx[index]
                        }
                        onCurrentIndexChanged: {
                            if(index>=0)
                            {
                                var str =comboBoxIpModel.get(currentIndex).text
                                selectedControlWrdIponCombobx[index]=str
                                cntrlWrdDisplayLabel.text =str
                                IndustrialEthIOComboBoxManager.setComboBoxSelection(index,comboBoxIpModel.get(currentIndex).text) //set the values at backend
                                if(str !== "Not Used"){
                                    comboBoxIpModel.remove(currentIndex)                        // removes the current index from combobmodel
                                }
                                cntrlWrdInputListView.model = selectedControlWrdIponCombobx     // reassign the models to comboBox
                            }
                        }
                    }
                }

            }
        }

        ListView{
            id: statusWrdOutputListView
            width: parent.width*0.45
            height: Math.round(250 * Style.scaleHint)
            anchors.top: controlwrdIpHeaderText.bottom
            anchors.left: statusWrdOpHeadertext.left
            spacing: Math.round(10 * Style.scaleHint)
            model: 2
            boundsBehavior: ListView.StopAtBounds
            clip: true
            highlightRangeMode: ListView.StrictlyEnforceRange

            delegate:
                Rectangle
            {
                id: statusWrdIODelegateRectangleOut
                width: Math.round(380 * Style.scaleHint)
                height:Math.round(70 * Style.scaleHint)
                color: Style.contentBackgroundColor
                enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY)  ? false: true

                Text {
                    id: textPinTitleOut
                    anchors.left: statusWrdIOEnableSwitchOut.left
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    color: Style.blackFontColor
                    font.pixelSize: Math.round(15 * Style.scaleHint)
                    text: qmlTextStsWrdOutPin[index]
                }

                BransonSwitch {
                    id: statusWrdIOEnableSwitchOut
                    anchors.verticalCenter: statuswrdComboBoxOut.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(15 * Style.scaleHint)
                    rectWidth: Math.round(30 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    checked:IndustrialEthIOComboBoxManager.getOutputStatusWrdPinEnable(index)
                    onCheckedChanged:
                    {
                        IndustrialEthIOComboBoxManager.setOutputStatusWordPinEnable(index,checked)
                    }
                }

                Rectangle
                {
                    id:statuswrdComboBoxOut
                    width: Math.round(175 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(40 * Style.scaleHint)
                    anchors.left: statusWrdIOEnableSwitchOut.right
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    color: "transparent"

                    BransonComboBox
                    {
                        id: statusWrdOutputComboBox
                        currentIndex: -1
                        minWidth: Math.round(175 * Style.scaleHint)
                        minHeight: Math.round(25 * Style.scaleHint)
                        comboboxpopupheight: Math.round(105 * Style.scaleHint)
                        enabled: statusWrdIOEnableSwitchOut.checked
                        model: comboBoxOpModel
                        Label {
                            id: statusWrddisplayLabel
                            Layout.fillWidth: statusWrdOutputComboBox
                            anchors.left: statusWrdOutputComboBox.left
                            anchors.leftMargin: statusWrdOutputComboBox.width*0.05
                            anchors.top: statusWrdOutputComboBox.top
                            anchors.topMargin: statusWrdOutputComboBox.height*0.30
                            font.pixelSize: statusWrdOutputComboBox.height*0.40
                            textFormat: Text.RichText
                            text:selectedStatusWrdonCombobx[index]
                        }
                        onCurrentIndexChanged: {
                            if(index>=0)
                            {
                                var str =comboBoxOpModel.get(currentIndex).text
                                selectedStatusWrdonCombobx[index]=str
                                statusWrddisplayLabel.text =str
                                IndustrialEthIOComboBoxManager.setStatusWrdOutputComboBoxSelection(index,comboBoxOpModel.get(currentIndex).text) //set the values at backend
                                if(str !== "Not Used"){
                                    comboBoxOpModel.remove(currentIndex) // removes the current index from combobmodel
                                }
                                statusWrdOutputListView.model = selectedStatusWrdonCombobx     // reassign the models to comboBox
                            }
                        }
                    }
                }

            }
        }

        //SAVE RESET TO DEFAULT AND CANCEL BUTTON..
        Rectangle{
            id:bottomRectangle
            height: Math.round(45 * Style.scaleHint)
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color: Style.backgroundColor
            clip:true
            BransonPrimaryButton
            {
                id: btnResetToDefault
                implicitWidth: Math.round(175 * Style.scaleHint)
                implicitHeight: Math.round(30 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin:  Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(2 * Style.scaleHint)
                text: qmltextResetToDefault
                buttonColor: Style.blackFontColor
                font.family: Style.regular.name
                onClicked:
                {
                    IndustrialEthIOComboBoxManager.getResetToDefRequestForIndusEthIO()

                }
            }
            BransonPrimaryButton
            {
                id: btnCancel
                implicitWidth: Math.round(124 * Style.scaleHint)
                implicitHeight: Math.round(30 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin:  Math.round(170 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(2 * Style.scaleHint)
                text: qmltextCancel
                buttonColor: Style.blackFontColor
                font.family: Style.regular.name
                onClicked:
                {
                }
            }

            BransonPrimaryButton
            {
                id: btnSave
                implicitWidth: Math.round(124 * Style.scaleHint)
                implicitHeight: Math.round(30 * Style.scaleHint)
                fontSize: Math.round(Style.style2  * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin:  Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(2 * Style.scaleHint)
                text: qmltextSave
                buttonColor: Style.buttonBackgroundColor
                font.family: Style.regular.name
                onClicked:
                {
                    IndustrialEthIOComboBoxManager.getSaveRequestForIndusEthIO()
                }
            }
        }
    }
    Connections
    {
        target: IndustrialEthIOComboBoxManager
        function onIndustrialEthIOValuesUpdated()
        {
            comboBoxIpModel.clear()
            for(var i = 0;i< IndustrialEthIOComboBoxManager.getCountOfControlWrdIpModel();i++)
            {
                var text=IndustrialEthIOComboBoxManager.getSelectedControlWrdComboBox(i)
                selectedControlWrdIponCombobx[i]=text
            }
            cntrlWrdInputListView.model = selectedControlWrdIponCombobx
            for(var i = 0;i< IndustrialEthIOComboBoxManager.getTotalSizeofControlWrdIpList();i++)
            {
                var text=IndustrialEthIOComboBoxManager.getControlWrdIp(i)
                comboBoxIpModel.append({"text":text});
            }

            //Analog Output Model.
            for(var j = 0;j< IndustrialEthIOComboBoxManager.getCountOfStatusWrdOpModel();j++)
            {
                var text=IndustrialEthIOComboBoxManager.getSelectedStatusWrdOpComboBox(j)
                selectedStatusWrdonCombobx[j]=text
            }
            statusWrdOutputListView.model = selectedStatusWrdonCombobx
            comboBoxOpModel.clear()
            for(var k = 0;k< IndustrialEthIOComboBoxManager.getTotalSizeofStatusWordOPList();k++)
            {
                var text=IndustrialEthIOComboBoxManager.getStatusWordOP(k)
                comboBoxOpModel.append({"text":text});
            }

            cntrlWrdInputListView.model = null
            cntrlWrdInputListView.model = 3

            statusWrdOutputListView.model = null
            statusWrdOutputListView.model = 3
        }
    }
}

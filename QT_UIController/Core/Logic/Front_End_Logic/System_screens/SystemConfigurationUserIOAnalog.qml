/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 UserIO - Analog I/O tab implementation.

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

    property string qmltextAnalogInputs               : "ANALOG INPUTS"
    property string qmltextAnalogOutputs              : "ANALOG OUTPUTS"
    property string qmltextResetToDefault              : "RESET TO DEFAULT"
    property string qmltextCancel                      : "CANCEL"
    property string qmltextSave                        : "SAVE"
    property string qmltextAnalogIn_1                  : "Analog_In_1"
    property string qmltextAnalogIn_2                  : "Analog_In_2"

    property string qmltextAnalogOut_1                 : "Analog_Out_1"
    property string qmltextAnalogOut_2                 : "Analog_Out_2"

    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)

    property var qmlTextArray: [qmltextAnalogInputs, qmltextAnalogOutputs, qmltextResetToDefault, qmltextCancel, qmltextSave,qmltextAnalogIn_1, qmltextAnalogIn_2,qmltextAnalogOut_1, qmltextAnalogOut_2]
    property var qmlTextAnalogInPin: [qmltextAnalogIn_1, qmltextAnalogIn_2]
    property var qmlTextAnalogOutPin: [qmltextAnalogOut_1, qmltextAnalogOut_2]

    property var selectedAnalogIponCombobx: []
    property var selectedAnalogOponCombobx: []

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO , qmlTextArray)
        qmltextAnalogInputs = qmlTextArray[textEnum.textDigitalInputsIdx]
        qmltextAnalogOutputs = qmlTextArray[textEnum.textDigitalOutputsIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextAnalogIn_1 = qmlTextArray[textEnum.textAnalogIn1Idx]
        qmltextAnalogIn_2 = qmlTextArray[textEnum.textAnalogIn2Idx]
        qmltextAnalogOut_1 = qmlTextArray[textEnum.textAnalogOp1Idx]
        qmltextAnalogOut_2= qmlTextArray[textEnum.textAnalogOp2Idx]
    }


    QtObject{
        id:textEnum
        readonly property int textDigitalInputsIdx        : 0
        readonly property int textDigitalOutputsIdx       : 1
        readonly property int textResetToDefaultIdx       : 2
        readonly property int textCancelIdx               : 3
        readonly property int textSaveIdx                 : 4
        readonly property int textAnalogIn1Idx            : 5
        readonly property int textAnalogIn2Idx            : 6
        readonly property int textAnalogOp1Idx            : 7
        readonly property int textAnalogOp2Idx            : 8
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
        updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO

        comboBoxIpModel.clear()
        for(var i = 0;i< AnalogComboBoxManager.getCountOfAnalogIpModel();i++)
        {
            var text=AnalogComboBoxManager.getSelectedAnalogComboBox(i)
            selectedAnalogIponCombobx[i]=text
        }
        analogInputListView.model = selectedAnalogIponCombobx
        for(var i = 0;i< AnalogComboBoxManager.getTotalSizeofAnalogIpList();i++)
        {
            var text = AnalogComboBoxManager.getAnalogIp(i)
            comboBoxIpModel.append({"text":text});
        }
        analogInputListView.update()


        //Analog Output Model.
        for(var j = 0;j< AnalogComboBoxManager.getCountOfAnalogOpModel();j++)
        {
            var text=AnalogComboBoxManager.getSelectedAnalogOpComboBox(j)
            selectedAnalogOponCombobx[j]=text
        }
        analogOutputListView.model = selectedAnalogOponCombobx
        comboBoxOpModel.clear()
        for(var k = 0;k< AnalogComboBoxManager.getTotalSizeofAnalogOPList();k++)
        {
            var text=AnalogComboBoxManager.getAnalogOP(k)
            comboBoxOpModel.append({"text":text});
        }
        analogIpglobalSwitch.checked = AnalogComboBoxManager.IsGlobalAnalogIpSwtchEnable
        analogoPglobalSwitch.checked = AnalogComboBoxManager.IsGlobalAnalogOpSwtchEnable
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
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        color: Style.backgroundColor
        clip:true

        Rectangle{
            id:analogInputHeadertext
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            color: Style.backgroundColor
            clip:true
            Text{
                text: qmltextAnalogInputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            BransonSwitch {
                id: analogIpglobalSwitch
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.25//Math.round(75 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.35
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(15 * Style.scaleHint)
                rectWidth: Math.round(30 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                checked:AnalogComboBoxManager.IsGlobalAnalogIpSwtchEnable
                onCheckedChanged:
                {
                  AnalogComboBoxManager.IsGlobalAnalogIpSwtchEnable = checked
                }
            }
        }

        Rectangle{
            id:analogOutputHeadertext
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: analogInputHeadertext.right
            color: Style.backgroundColor
            clip:true
            Text{
                text: qmltextAnalogOutputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
            }

            BransonSwitch {
                id: analogoPglobalSwitch
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.25//Math.round(75 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.35
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(15 * Style.scaleHint)
                rectWidth: Math.round(30 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                checked:AnalogComboBoxManager.IsGlobalAnalogOpSwtchEnable
                onCheckedChanged:
                {
                  AnalogComboBoxManager.IsGlobalAnalogOpSwtchEnable = checked
                }
            }
        }

        ListView{
            id: analogInputListView
            width: parent.width*0.45
            height:Math.round(250 * Style.scaleHint)
            anchors.top: analogInputHeadertext.bottom
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
                id: analogIODelegateRectangle
                width: Math.round(380 * Style.scaleHint)
                height:Math.round(70 * Style.scaleHint)
                color: Style.contentBackgroundColor
                clip: true
                enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY) || (!analogIpglobalSwitch.checked) ? false: true

                Text {
                    id: textPinTitle
                    anchors.left: analogIOEnableSwitch.left
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    color: Style.blackFontColor
                    font.pixelSize: Math.round(15 * Style.scaleHint)
                    text: qmlTextAnalogInPin[index]
                }

                BransonSwitch {
                    id: analogIOEnableSwitch
                    anchors.verticalCenter: analogIOComboBox.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(15 * Style.scaleHint)
                    rectWidth: Math.round(30 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    checked:AnalogComboBoxManager.getAnalogUserIOIpPinEnable(index)
                    onCheckedChanged:
                    {
                        AnalogComboBoxManager.setAnalogUserIOPinEnable(index,checked)
                    }
                }

                Rectangle
                {
                    id:analogIOComboBox
                    width: Math.round(175 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(40 * Style.scaleHint)
                    anchors.left: analogIOEnableSwitch.right
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    color: "transparent"

                    BransonComboBox
                    {
                        id: analogInputComboBox
                        currentIndex: -1
                        minWidth: Math.round(175 * Style.scaleHint)
                        minHeight: Math.round(25 * Style.scaleHint)
                        comboboxpopupheight: Math.round(105 * Style.scaleHint)
                        enabled: analogIOEnableSwitch.checked
                        // Set the model for each ComboBox
                        model: comboBoxIpModel
                        Label {
                            id: welderdisplayLabel
                            Layout.fillWidth: analogInputComboBox
                            anchors.left: analogInputComboBox.left
                            anchors.leftMargin: analogInputComboBox.width*0.05
                            anchors.top: analogInputComboBox.top
                            anchors.topMargin: analogInputComboBox.height*0.30
                            font.pixelSize: analogInputComboBox.height*0.40
                            textFormat: Text.RichText
                            text:selectedAnalogIponCombobx[index]
                        }
                        onCurrentIndexChanged: {
                            if(index>=0)
                            {
                                var str =comboBoxIpModel.get(currentIndex).text
                                selectedAnalogIponCombobx[index]=str
                                welderdisplayLabel.text =str
                                AnalogComboBoxManager.setComboBoxSelection(index,comboBoxIpModel.get(currentIndex).text) //set the values at backend
                                if(str !== "Not Used"){
                                    comboBoxIpModel.remove(currentIndex)                        // removes the current index from combobmodel
                                }
                                analogInputListView.model = selectedAnalogIponCombobx     // reassign the models to comboBox
                            }
                        }
                    }
                }

            }
        }

        ListView{
            id: analogOutputListView
            width: parent.width*0.45
            height: Math.round(250 * Style.scaleHint)
            anchors.top: analogInputHeadertext.bottom
            anchors.left: analogOutputHeadertext.left
            spacing: Math.round(10 * Style.scaleHint)
            model: 2
            boundsBehavior: ListView.StopAtBounds
            clip: true
            highlightRangeMode: ListView.StrictlyEnforceRange

            delegate:
                Rectangle
            {
                id: analogIODelegateRectangleOut
                width: Math.round(380 * Style.scaleHint)
                height:Math.round(70 * Style.scaleHint)
                color: Style.contentBackgroundColor
                enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY) || (!analogoPglobalSwitch.checked) ? false: true

                Text {
                    id: textPinTitleOut
                    anchors.left: analogIOEnableSwitchOut.left
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    color: Style.blackFontColor
                    font.pixelSize: Math.round(15 * Style.scaleHint)
                    text: qmlTextAnalogOutPin[index]
                }

                BransonSwitch {
                    id: analogIOEnableSwitchOut
                    anchors.verticalCenter: analogIOComboBoxOut.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(15 * Style.scaleHint)
                    rectWidth: Math.round(30 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    checked:AnalogComboBoxManager.getOutputAnalogOpUserIOPinEnable(index)
                    onCheckedChanged:
                    {
                        AnalogComboBoxManager.setOutputAnalogOpUserIOPinEnable(index,checked)
                    }
                }

                Rectangle
                {
                    id:analogIOComboBoxOut
                    width: Math.round(175 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(40 * Style.scaleHint)
                    anchors.left: analogIOEnableSwitchOut.right
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    color: "transparent"

                    BransonComboBox
                    {
                        id: analogOutputComboBox
                        currentIndex: -1
                        minWidth: Math.round(175 * Style.scaleHint)
                        minHeight: Math.round(25 * Style.scaleHint)
                        comboboxpopupheight: Math.round(105 * Style.scaleHint)
                        enabled: analogIOEnableSwitchOut.checked
                        model: comboBoxOpModel
                        Label {
                            id: analogOPdisplayLabel
                            Layout.fillWidth: analogOutputComboBox
                            anchors.left: analogOutputComboBox.left
                            anchors.leftMargin: analogOutputComboBox.width*0.05
                            anchors.top: analogOutputComboBox.top
                            anchors.topMargin: analogOutputComboBox.height*0.30
                            font.pixelSize: analogOutputComboBox.height*0.40
                            textFormat: Text.RichText
                            text:selectedAnalogOponCombobx[index]
                        }
                        onCurrentIndexChanged: {
                            if(index>=0)
                            {
                                var str =comboBoxOpModel.get(currentIndex).text
                                selectedAnalogOponCombobx[index]=str
                                analogOPdisplayLabel.text =str
                                AnalogComboBoxManager.setOutputComboBoxSelection(index,comboBoxOpModel.get(currentIndex).text) //set the values at backend
                                if(str !== "Not Used"){
                                    comboBoxOpModel.remove(currentIndex) // removes the current index from combobmodel
                                }
                                analogOutputListView.model = selectedAnalogOponCombobx     // reassign the models to comboBox
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
                    AnalogComboBoxManager.getResetToDefRequestForAnalogUserIO()

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
                   AnalogComboBoxManager.getCancelRequestForAnalogUserIO()
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
                    AnalogComboBoxManager.getSaveRequestForAnalogUserIO()
                }
            }
        }
    }
    Connections
    {
        target: AnalogComboBoxManager
        function onAnalogIOValuesUpdated()
        {

            comboBoxIpModel.clear()
            for(var i = 0;i< AnalogComboBoxManager.getCountOfAnalogIpModel();i++)
            {
                var text=AnalogComboBoxManager.getSelectedAnalogComboBox(i)
                selectedAnalogIponCombobx[i]=text
            }
            analogInputListView.model = selectedAnalogIponCombobx
            for(var i = 0;i< AnalogComboBoxManager.getTotalSizeofAnalogIpList();i++)
            {
                var text=AnalogComboBoxManager.getAnalogIp(i)
                comboBoxIpModel.append({"text":text});
            }

            //Analog Output Model.
            for(var j = 0;j< AnalogComboBoxManager.getCountOfAnalogOpModel();j++)
            {
                var text=AnalogComboBoxManager.getSelectedAnalogOpComboBox(j)
                selectedAnalogOponCombobx[j]=text
            }
            analogOutputListView.model = selectedAnalogOponCombobx
            comboBoxOpModel.clear()
            for(var k = 0;k< AnalogComboBoxManager.getTotalSizeofAnalogOPList();k++)
            {
                var text=AnalogComboBoxManager.getAnalogOP(k)
                comboBoxOpModel.append({"text":text});
            }

            analogInputListView.model = null
            analogInputListView.model = 2

            analogOutputListView.model = null
            analogOutputListView.model = 2

            analogIpglobalSwitch.checked = AnalogComboBoxManager.IsGlobalAnalogIpSwtchEnable
            analogoPglobalSwitch.checked = AnalogComboBoxManager.IsGlobalAnalogOpSwtchEnable

        }
    }
}

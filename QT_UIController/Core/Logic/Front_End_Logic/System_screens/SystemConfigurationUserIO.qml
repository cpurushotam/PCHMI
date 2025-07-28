/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 UserIO - Digital I/O tab implementation.

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

    property string qmltextDigitalInputs               : "DIGITAL INPUTS"
    property string qmltextDigitalOutputs              : "DIGITAL OUTPUTS"
    property string qmltextResetToDefault              : "RESET TO DEFAULT"
    property string qmltextCancel                      : "CANCEL"
    property string qmltextSave                        : "SAVE"
    property string qmltextDigitalIn_1                  : "Digital_In_1"
    property string qmltextDigitalIn_2                  : "Digital_In_2"
    property string qmltextDigitalIn_3                  : "Digital_In_3"
    property string qmltextDigitalIn_4                  : "Digital_In_4"
    property string qmltextDigitalIn_5                  : "Digital_In_5"
    property string qmltextDigitalIn_6                  : "Digital_In_6"
    property string qmltextDigitalIn_7                  : "Digital_In_7"
    property string qmltextDigitalIn_8                  : "Digital_In_8"
    property string qmltextDigitalIn_9                  : "Digital_In_9"
    property string qmltextDigitalOut_1                 : "Digital_Out_1"
    property string qmltextDigitalOut_2                 : "Digital_Out_2"
    property string qmltextDigitalOut_3                 : "Digital_Out_3"
    property string qmltextDigitalOut_4                 : "Digital_Out_4"
    property string qmltextDigitalOut_5                 : "Digital_Out_5"
    property string qmltextDigitalOut_6                 : "Digital_Out_6"
    property string qmltextDigitalOut_7                 : "Digital_Out_7"
    property string qmltextDigitalOut_8                 : "Digital_Out_8"

    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)

    property var qmlTextArray: [qmltextDigitalInputs, qmltextDigitalOutputs, qmltextResetToDefault, qmltextCancel, qmltextSave,qmltextDigitalIn_1, qmltextDigitalIn_2, qmltextDigitalIn_3, qmltextDigitalIn_4, qmltextDigitalIn_5, qmltextDigitalIn_6, qmltextDigitalIn_7, qmltextDigitalIn_8, qmltextDigitalIn_9,qmltextDigitalOut_1, qmltextDigitalOut_2, qmltextDigitalOut_3, qmltextDigitalOut_4, qmltextDigitalOut_5, qmltextDigitalOut_6, qmltextDigitalOut_7, qmltextDigitalOut_8]
    property var qmlTextDigitalInPin: [qmltextDigitalIn_1, qmltextDigitalIn_2, qmltextDigitalIn_3, qmltextDigitalIn_4, qmltextDigitalIn_5, qmltextDigitalIn_6, qmltextDigitalIn_7, qmltextDigitalIn_8, qmltextDigitalIn_9]
    property var qmlTextDigitalOutPin: [qmltextDigitalOut_1, qmltextDigitalOut_2, qmltextDigitalOut_3, qmltextDigitalOut_4, qmltextDigitalOut_5, qmltextDigitalOut_6, qmltextDigitalOut_7, qmltextDigitalOut_8]

    property var selectedDigitalIponCombobx: []
    property var selectedDigitalOponCombobx: []

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO , qmlTextArray)
        qmltextDigitalInputs = qmlTextArray[textEnum.textDigitalInputsIdx]
        qmltextDigitalOutputs = qmlTextArray[textEnum.textDigitalOutputsIdx]
        qmltextResetToDefault = qmlTextArray[textEnum.textResetToDefaultIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
        qmltextDigitalIn_1 = qmlTextArray[textEnum.textDigitalIn1Idx]
        qmltextDigitalIn_2 = qmlTextArray[textEnum.textDigitalIn2Idx]
        qmltextDigitalIn_3 = qmlTextArray[textEnum.textDigitalIn3Idx]
        qmltextDigitalIn_4 = qmlTextArray[textEnum.textDigitalIn4Idx]
        qmltextDigitalIn_5 = qmlTextArray[textEnum.textDigitalIn5Idx]
        qmltextDigitalIn_6 = qmlTextArray[textEnum.textDigitalIn6Idx]
        qmltextDigitalIn_7 = qmlTextArray[textEnum.textDigitalIn7Idx]
        qmltextDigitalIn_8 = qmlTextArray[textEnum.textDigitalIn8Idx]
        qmltextDigitalIn_9 = qmlTextArray[textEnum.textDigitalIn9Idx]
        qmltextDigitalOut_1 = qmlTextArray[textEnum.textDigitalOut1Idx]
        qmltextDigitalOut_2 = qmlTextArray[textEnum.textDigitalOut2Idx]
        qmltextDigitalOut_3 = qmlTextArray[textEnum.textDigitalOut3Idx]
        qmltextDigitalOut_4 = qmlTextArray[textEnum.textDigitalOut4Idx]
        qmltextDigitalOut_5 = qmlTextArray[textEnum.textDigitalOut5Idx]
        qmltextDigitalOut_6 = qmlTextArray[textEnum.textDigitalOut6Idx]
        qmltextDigitalOut_7 = qmlTextArray[textEnum.textDigitalOut7Idx]
        qmltextDigitalOut_8 = qmlTextArray[textEnum.textDigitalOut8Idx]
    }


    QtObject
    {
        id:textEnum
        readonly property int textDigitalInputsIdx        : 0
        readonly property int textDigitalOutputsIdx       : 1
        readonly property int textResetToDefaultIdx       : 2
        readonly property int textCancelIdx               : 3
        readonly property int textSaveIdx                 : 4
        readonly property int textDigitalIn1Idx           : 5
        readonly property int textDigitalIn2Idx           : 6
        readonly property int textDigitalIn3Idx           : 7
        readonly property int textDigitalIn4Idx           : 8
        readonly property int textDigitalIn5Idx           : 9
        readonly property int textDigitalIn6Idx           : 10
        readonly property int textDigitalIn7Idx           : 11
        readonly property int textDigitalIn8Idx           : 12
        readonly property int textDigitalIn9Idx           : 13
        readonly property int textDigitalOut1Idx          : 14
        readonly property int textDigitalOut2Idx          : 15
        readonly property int textDigitalOut3Idx          : 16
        readonly property int textDigitalOut4Idx          : 17
        readonly property int textDigitalOut5Idx          : 18
        readonly property int textDigitalOut6Idx          : 19
        readonly property int textDigitalOut7Idx          : 20
        readonly property int textDigitalOut8Idx          : 21
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
           ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO

           for(var i = 0;i< ComboBoxManager.getCountOfIpModel();i++)
           {
              var text=ComboBoxManager.getSelectedComboBox(i)
               selectedDigitalIponCombobx[i]=text
           }

           digitalInputListView.model = selectedDigitalIponCombobx
           comboBoxIpModel.clear()

           for(var i = 0;i< ComboBoxManager.getTotalSizeofDigtialIpList();i++)
           {
              var text=ComboBoxManager.getDigitalIp(i)
              comboBoxIpModel.append({"text":text});
           }

           //Digital Output Model.
           for(var j = 0;j< ComboBoxManager.getCountOfOpModel();j++)
           {
              var text=ComboBoxManager.getSelectedOPComboBox(j)
               selectedDigitalOponCombobx[j]=text
           }

           digitalOutputListView.model = selectedDigitalOponCombobx
           comboBoxOpModel.clear()

           for(var k = 0;k< ComboBoxManager.getTotalSizeofDigtialOPList();k++)
           {
              var text=ComboBoxManager.getDigitalOP(k)
              comboBoxOpModel.append({"text":text});
           }

           digitaloPglobalSwitch.checked = ComboBoxManager.IsGlobalDgtOpSwtchEnable
           dgtIpglobalSwitch.checked = ComboBoxManager.IsGlobalDgtIpSwtchEnable
           updateLanguage()
       }

    ListModel
    {
        id: comboBoxIpModel
    }

    ListModel
    {
        id: comboBoxOpModel
    }

    Rectangle
    {
        id:mainRectangle
        width: mainWindow.showWidth
        height: mainWindow.showHeight *0.65
        anchors.top: parent.top
        anchors.topMargin: Math.round(30 * Style.scaleHint)
        color: Style.backgroundColor
        clip:true

        Rectangle
        {
            id:digitalInputHeadertext
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            color: Style.backgroundColor
            clip:true
            Text
            {
                text: qmltextDigitalInputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }

            BransonSwitch
            {
                id: dgtIpglobalSwitch
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.25//Math.round(75 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.35
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(15 * Style.scaleHint)
                rectWidth: Math.round(30 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                checked:ComboBoxManager.IsGlobalDgtIpSwtchEnable
                onCheckedChanged:
                {
                   ComboBoxManager. IsGlobalDgtIpSwtchEnable = checked
                }
            }
        }

        Rectangle
        {
            id:digitalOutputHeadertext
            width: parent.width/2
            height: Math.round(40 * Style.scaleHint)
            anchors.top: parent.top
            anchors.left: digitalInputHeadertext.right
            color: Style.backgroundColor
            clip:true
            Text
            {
                text: qmltextDigitalOutputs
                font.pixelSize: Math.round(15 * Style.scaleHint)
                color: Style.blackFontColor
                anchors.verticalCenter: parent.verticalCenter
            }

            BransonSwitch
            {
                id: digitaloPglobalSwitch
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.25//Math.round(75 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.35
                maxWidth: Math.round(15 * Style.scaleHint)
                maxHeight: Math.round(15 * Style.scaleHint)
                rectWidth: Math.round(30 * Style.scaleHint)
                rectHeight: Math.round(10 * Style.scaleHint)
                checked:ComboBoxManager.IsGlobalDgtOpSwtchEnable
                onCheckedChanged:
                {
                    ComboBoxManager.IsGlobalDgtOpSwtchEnable = checked
                }
            }
        }

        ListView
        {
            id: digitalInputListView
            width: parent.width*0.45
            height:Math.round(250 * Style.scaleHint)
            anchors.top: digitalInputHeadertext.bottom
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            spacing: Math.round(10 * Style.scaleHint)
            model: 9
            boundsBehavior: ListView.StopAtBounds
            clip: true
            highlightRangeMode: ListView.StrictlyEnforceRange

            delegate:
                Rectangle
            {
                id: digitalIODelegateRectangle
                width: Math.round(380 * Style.scaleHint)
                height:Math.round(70 * Style.scaleHint)
                color: Style.contentBackgroundColor
                clip: true
                enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY) || (!dgtIpglobalSwitch.checked)  ? false: true

                Text
                {
                    id: textPinTitle
                    anchors.left: digitalIOEnableSwitch.left
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(15 * Style.scaleHint)
                    color: Style.blackFontColor
                    font.pixelSize: Math.round(15 * Style.scaleHint)
                    text: qmlTextDigitalInPin[index]
                }

                BransonSwitch
                {
                    id: digitalIOEnableSwitch
                    anchors.verticalCenter: digitalIOComboBox.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    maxWidth: Math.round(15 * Style.scaleHint)
                    maxHeight: Math.round(15 * Style.scaleHint)
                    rectWidth: Math.round(30 * Style.scaleHint)
                    rectHeight: Math.round(10 * Style.scaleHint)
                    checked:ComboBoxManager.getDigitalUserIOPinEnable(index)
                    onCheckedChanged:
                    {
                        ComboBoxManager.setDigitalUserIOPinEnable(index,checked)
                    }
                }

                Rectangle
                {
                    id:digitalIOComboBox
                    width: Math.round(175 * Style.scaleHint)
                    height: Math.round(25 * Style.scaleHint)
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(40 * Style.scaleHint)
                    anchors.left: digitalIOEnableSwitch.right
                    anchors.leftMargin: Math.round(10 * Style.scaleHint)
                    color: "transparent"

                    BransonComboBox
                    {
                        id: digitalInputComboBox
                        currentIndex: -1
                        minWidth: Math.round(175 * Style.scaleHint)
                        minHeight: Math.round(25 * Style.scaleHint)
                        comboboxpopupheight: Math.round(105 * Style.scaleHint)
                        enabled: digitalIOEnableSwitch.checked
                        // Set the model for each ComboBox
                        model: comboBoxIpModel
                        Label
                        {
                            id: welderdisplayLabel
                            Layout.fillWidth: digitalInputComboBox
                            anchors.left: digitalInputComboBox.left
                            anchors.leftMargin: digitalInputComboBox.width*0.05
                            anchors.top: digitalInputComboBox.top
                            anchors.topMargin: digitalInputComboBox.height*0.30
                            font.pixelSize: digitalInputComboBox.height*0.40
                            textFormat: Text.RichText
                            text:selectedDigitalIponCombobx[index]
                        }

                        onCurrentIndexChanged:
                        {
                            if(index>=0)
                            {
                                var str =comboBoxIpModel.get(currentIndex).text
                                selectedDigitalIponCombobx[index]=str
                                welderdisplayLabel.text =str
                                ComboBoxManager.setComboBoxSelection(index,comboBoxIpModel.get(currentIndex).text) //set the values at backend
                                if(str !== "Not Used"){
                                    comboBoxIpModel.remove(currentIndex)                        // removes the current index from combobmodel
                                }
                                digitalInputListView.model = selectedDigitalIponCombobx     // reassign the models to comboBox
                            }
                        }
                    }
                }

                Row
                {
                    anchors.verticalCenter: digitalIOComboBox.verticalCenter
                    anchors.left: digitalIOComboBox.right
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    enabled: digitalIOEnableSwitch.checked

                    BransonRadioButton
                    {
                        id:radioBtn0Volt
                        labelText: "0 V"
                        offColor:Style.blackFontColor
                        height: Math.round(15 * Style.scaleHint)
                        width: Math.round(60 * Style.scaleHint)
                        font.pixelSize: Math.round(15 * Style.scaleHint)
                        checked:(ComboBoxManager.getDigitalUserIOState(index)) ? false : (ComboBoxManager.getIndexValue(index)) ? false : true
                        enabled: !(ComboBoxManager.getIndexValue(index))
                        onClicked:
                        {

                            ComboBoxManager.setDigitalUserIOState(index,0)

                        }
                    }

                    BransonRadioButton
                    {
                        id:radioBtn24Volt
                        height:Math.round(15 * Style.scaleHint)
                        width: Math.round(80 * Style.scaleHint)
                        labelText: "24 V"
                        font.pixelSize: Math.round(15 * Style.scaleHint)
                        checked:  !(radioBtn0Volt.checked)
                        enabled: !(ComboBoxManager.getIndexValue(index))
                        onClicked:
                        {

                            ComboBoxManager.setDigitalUserIOState(index,1)

                        }
                    }
                }
            }
        }

     ListView
     {
         id: digitalOutputListView
         width: parent.width*0.45
         height: Math.round(250 * Style.scaleHint)
         anchors.top: digitalInputHeadertext.bottom
         anchors.left: digitalOutputHeadertext.left
         spacing: Math.round(10 * Style.scaleHint)
         model: 8
         boundsBehavior: ListView.StopAtBounds
         clip: true
         highlightRangeMode: ListView.StrictlyEnforceRange

         delegate:
             Rectangle
         {
             id: digitalIODelegateRectangleOut
             width: Math.round(380 * Style.scaleHint)
             height:Math.round(70 * Style.scaleHint)
             color: Style.contentBackgroundColor
             enabled: (DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY) || (!digitaloPglobalSwitch.checked) ? false: true

             Text
             {
                 id: textPinTitleOut
                 anchors.left: digitalIOEnableSwitchOut.left
                 anchors.top: parent.top
                 anchors.topMargin: Math.round(15 * Style.scaleHint)
                 color: Style.blackFontColor
                 font.pixelSize: Math.round(15 * Style.scaleHint)
                 text: qmlTextDigitalOutPin[index]
             }

             BransonSwitch
             {
                 id: digitalIOEnableSwitchOut
                 anchors.verticalCenter: digitalIOComboBoxOut.verticalCenter
                 anchors.left: parent.left
                 anchors.leftMargin: Math.round(5 * Style.scaleHint)
                 maxWidth: Math.round(15 * Style.scaleHint)
                 maxHeight: Math.round(15 * Style.scaleHint)
                 rectWidth: Math.round(30 * Style.scaleHint)
                 rectHeight: Math.round(10 * Style.scaleHint)
                 checked:ComboBoxManager.getOutputDigitalUserIOPinEnable(index)
                 onCheckedChanged:
                 {
                     ComboBoxManager.setOutputDigitalUserIOPinEnable(index,checked)
                 }
             }

             Rectangle
             {
                 id:digitalIOComboBoxOut
                 width: Math.round(175 * Style.scaleHint)
                 height: Math.round(25 * Style.scaleHint)
                 anchors.top: parent.top
                 anchors.topMargin: Math.round(40 * Style.scaleHint)
                 anchors.left: digitalIOEnableSwitchOut.right
                 anchors.leftMargin: Math.round(10 * Style.scaleHint)
                 color: "transparent"

                 BransonComboBox
                 {
                     id: digitalOutputComboBox
                     currentIndex: -1
                     minWidth: Math.round(175 * Style.scaleHint)
                     minHeight: Math.round(25 * Style.scaleHint)
                     comboboxpopupheight: Math.round(105 * Style.scaleHint)
                     enabled: digitalIOEnableSwitchOut.checked
                     model: comboBoxOpModel

                     Label
                     {
                         id: disgitalOPdisplayLabel
                         Layout.fillWidth: digitalOutputComboBox
                         anchors.left: digitalOutputComboBox.left
                         anchors.leftMargin: digitalOutputComboBox.width*0.05
                         anchors.top: digitalOutputComboBox.top
                         anchors.topMargin: digitalOutputComboBox.height*0.30
                         font.pixelSize: digitalOutputComboBox.height*0.40
                         textFormat: Text.RichText
                         text:selectedDigitalOponCombobx[index]
                     }

                     onCurrentIndexChanged:
                     {
                         if(index>=0)
                         {
                             var str =comboBoxOpModel.get(currentIndex).text
                             selectedDigitalOponCombobx[index]=str
                             disgitalOPdisplayLabel.text =str
                             ComboBoxManager.setOutputComboBoxSelection(index,comboBoxOpModel.get(currentIndex).text) //set the values at backend

                             if(str !== "Not Used")
                             {
                                 comboBoxOpModel.remove(currentIndex) // removes the current index from combobmodel
                             }
                             digitalOutputListView.model = selectedDigitalOponCombobx     // reassign the models to comboBox
                         }
                     }
                 }
             }

             Row
             {
                 anchors.verticalCenter: digitalIOComboBoxOut.verticalCenter
                 anchors.left: digitalIOComboBoxOut.right
                 anchors.leftMargin: Math.round(5 * Style.scaleHint)
                 enabled: digitalIOEnableSwitchOut.checked

                 BransonRadioButton
                 {
                     id:radioBtn0VoltOut
                     labelText: "0 V"
                     offColor:Style.blackFontColor
                     height: Math.round(15 * Style.scaleHint)
                     width: Math.round(60 * Style.scaleHint)
                     font.pixelSize: Math.round(15 * Style.scaleHint)
                     checked:(ComboBoxManager.getOutputDigitalUserIOState(index)) ? false : true
                     onClicked:
                     {
                         ComboBoxManager.setOutputDigitalUserIOState(index,0)
                     }
                 }

                 BransonRadioButton
                 {
                     id:radioBtn24VoltOut
                     height:Math.round(15 * Style.scaleHint)
                     width: Math.round(80 * Style.scaleHint)
                     labelText: "24 V"
                     font.pixelSize: Math.round(15 * Style.scaleHint)
                     checked: (ComboBoxManager.getOutputDigitalUserIOState(index))? true : false
                     onClicked:
                     {
                         ComboBoxManager.setOutputDigitalUserIOState(index,1)
                     }
                 }
             }
         }
     }


        Rectangle
        {
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
                    ComboBoxManager.getResetToDefRequestForDigitalUserIO()
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
                    ComboBoxManager.getCancelRequestForDigitalUserIO()
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
                    ComboBoxManager.getSaveRequestForDigitalUserIO()
                }
            }
        }
    }
  //  ComboBoxManager
    Connections
    {
        target:  ComboBoxManager
       function onValuesUpdated()
        {
            comboBoxIpModel.clear()
            for(var i = 0;i< ComboBoxManager.getCountOfIpModel();i++)
            {
               var text=ComboBoxManager.getSelectedComboBox(i)
                selectedDigitalIponCombobx[i]=text
            }
            digitalInputListView.model = selectedDigitalIponCombobx
            for(var i = 0;i< ComboBoxManager.getTotalSizeofDigtialIpList();i++)
            {
                var text=ComboBoxManager.getDigitalIp(i)
                comboBoxIpModel.append({"text":text});
            }

            // Digital Outout IO Model .
            comboBoxOpModel.clear()
            for(var j = 0;j< ComboBoxManager.getCountOfOpModel();j++)
            {
               var text=ComboBoxManager.getSelectedOPComboBox(j)
               selectedDigitalOponCombobx[j]=text
            }
            digitalOutputListView.model = selectedDigitalOponCombobx

            for(var k = 0;k< ComboBoxManager.getTotalSizeofDigtialOPList();k++)
            {
                var text=ComboBoxManager.getDigitalOP(k)
                comboBoxOpModel.append({"text":text});
            }

            // Notify the ListView components about the changes
            digitalInputListView.model = null;
            digitalInputListView.model = 9;

            digitalOutputListView.model = null;
            digitalOutputListView.model = 8;
            digitaloPglobalSwitch.checked = ComboBoxManager.IsGlobalDgtOpSwtchEnable
           dgtIpglobalSwitch.checked = ComboBoxManager.IsGlobalDgtIpSwtchEnable

        }
    }
    Rectangle
    {
        id: loadingPage
        visible: false
        opacity: 0.5
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        color:"#000000"
        x: mainWindow.showWidth * 0.001
        y: mainWindow.showHeight *0.001
        Image
        {
            id: recipeLoadingIcon
            visible: ComboBoxManager.IsLoading
            x: mainWindow.showWidth * 0.45
            y: mainWindow.showHeight *0.25
            source: "qrc:/Images/Loading.png"
            height: imageSize * 5
            width: imageSize * 5
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeLoadingIcon.width
            sourceSize.height: recipeLoadingIcon.height
            smooth: true
        }
        RotationAnimator
        {
            target: recipeLoadingIcon
            from: 0
            to: 360
            duration: 1000
            running: true
        }
        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReport Storgae file provide the option to select the storgae option.

 **********************************************************************************************************/
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import Style 1.0
import QtQuick.Layouts 1.12
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.LoginIndexEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {
    id: storageoption
    readonly property int qmlscreenIndicator:  UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE
    property string qmltextTabBarGenerateReport             : "Generate Report"
    property string qmltextTabBarSavedReport                : "Saved Reports"
    property string qmltextType                             : "TYPE"
    property string qmltextStorageOption                    : "STORAGE OPTIONS"
    property string qmltextOutput                           : "OUTPUT"
    property string qmltextUsb                              : "USB"
    property string qmltextEthernet                         : "ETHERNET"
    property string qmltextCSV                              : "CSV"
    property string qmltextBinary                           : "BINARY"
    property string qmltextStorgeOutput                     : "STORAGE"
    property string qmltextStorgeOutput1                    : "& OUTPUT"
    property string qmltextDataFilters                      : "DATA"
    property string qmltextDataFilters1                     : "FILTERS"
    property string qmltextSummary                          : "SUMMARY"
    property string qmltextSingle                           : "SINGLE"
    property string qmltextContinuous                       : "CONTINUOUS"
    property string qmltextNext                             : "NEXT"
    property string qmltextPrevious                         : "PREVIOUS"
    property string qmltextMenuName                         : "Generate Report"
    property string qmltextYes                              : "YES"
    property string qmltextNo                               : "NO"
    property string qmltextEncryptData                      : "ENCRYPT DATA"
    property string qmltextNetworkAttachedStorage           : "Network Attached Storage"
    property string qmltextPlc                             : "PLC"
    enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true


    property var qmlTextArray: [qmltextTabBarGenerateReport, qmltextTabBarSavedReport, qmltextType, qmltextStorageOption, qmltextOutput, qmltextSingle,qmltextUsb,
        qmltextEthernet,qmltextCSV, qmltextBinary, qmltextStorgeOutput, qmltextDataFilters,qmltextSummary, qmltextContinuous, qmltextNext, qmltextMenuName,qmltextPrevious,qmltextYes, qmltextNo, qmltextEncryptData,qmltextStorgeOutput1,qmltextDataFilters1]

    QtObject
    {
        id: textEnum
        readonly property int qmltextTabBarGenerateReport             : 0
        readonly property int qmltextTabBarSavedReport                : 1
        readonly property int qmltextType                             : 2
        readonly property int qmltextStorageOption                    : 3
        readonly property int qmltextOutput                           : 4
        readonly property int qmltextUsb                              : 5
        readonly property int qmltextEthernet                         : 6
        readonly property int qmltextCSV                              : 7
        readonly property int qmltextBinary                           : 8
        readonly property int qmltextDataFilters                      : 9
        readonly property int qmltextPrevious                         : 10
        readonly property int qmltextYes                              : 11
        readonly property int qmltextNo                               : 12
        readonly property int qmltextEncryptData                      : 13
        readonly property int qmltextStorgeOutput                     : 14
        readonly property int qmltextSummary                          : 15
        readonly property int qmltextSingle                           : 16
        readonly property int qmltextContinuous                       : 17
        readonly property int qmltextNext                             : 18
        readonly property int qmltextMenuName                         : 19
        readonly property int qmltextPlc                              : 20
        readonly property int qmltextStorgeOutput1                    : 21
        readonly property int qmltextDataFilters1                     : 22

    }
    QtObject
    {
        id:generateReportEncryptionDataEnum
        readonly property int no            : 0
        readonly property int yes           : 1
    }
    QtObject
    {
        id:storageOptionEnum
        readonly property int usb                             : 0
        readonly property int networkAttacheStorage           : 1
        readonly property int plc                             : 2
    }
    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE , qmlTextArray)
        qmlTextTabBarGenerateReport        = qmlTextArray[textEnum.textTabBarGenerateReportIdx]
        qmlTextTabBarSavedReport           = qmlTextArray[textEnum.textTabBarSavedReportIdx]
        qmlTextType                        = qmlTextArray[textEnum.textTypeIdx]
        qmlTextStorageOption               = qmlTextArray[textEnum.textStorageOptionIdx]
        qmlTextOutput                      = qmlTextArray[textEnum.textOutputIdx]
        qmlTextUsb                         = qmlTextArray[textEnum.textUsbIdx]
        qmlTextEthernet                    = qmlTextArray[textEnum.textEthernetIdx]
        qmlTextCSV                         = qmlTextArray[textEnum.textCSVIdx]
        qmlTextBinary                      = qmlTextArray[textEnum.textBinaryIdx]
        qmlTextDataFilters                 = qmlTextArray[textEnum.textDataFiltersIdx]
        qmlTextPrevious                    = qmlTextArray[textEnum.textPreviousIdx]
        qmlTextYes                         = qmlTextArray[textEnum.textYesIdx]
        qmlTextNo                          = qmlTextArray[textEnum.textNoIdx]
        qmlTextEncryptData                 = qmlTextArray[textEnum.textEncryptDataIdx]
        qmlTextStorgeOutput                = qmlTextArray[textEnum.textStorgeOutputIdx]
        qmlTextSummary                     = qmlTextArray[textEnum.textSummaryIdx]
        qmlTextSingle                      = qmlTextArray[textEnum.textSingleIdx]
        qmlTextContinuous                  = qmlTextArray[textEnum.textContinuousIdx]
        qmlTextNext                        = qmlTextArray[textEnum.textNextIdx]
        qmlTextMenuName                    = qmlTextArray[textEnum.textMenuNameIdx]
        qmlTextPlc                         = qmlTextArray[textEnum.textPlcIdx]
        qmlTextStorgeOutput1               = qmlTextArray[textEnum.textStorgeOutput1Idx]
        qmlTextDataFilters1                = qmlTextArray[textEnum.textDataFilters1Idx]
        qmlTextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE, qmlTextMenuName)
    }
    Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: Math.round(190 * Style.scaleHint)
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            spacing: 26
            background: Rectangle
            {
                color: Style.backgroundColor
            }
            BransonTabButton
            {
                id: tabbtnGenerateReport
                width: Math.round(150 * Style.scaleHint)
                tabbtnText: qmltextTabBarGenerateReport
            }
            BransonTabButton
            {
                id: tabbtnSavedReport
                width: Math.round(125 * Style.scaleHint)
                tabbtnText: qmltextTabBarSavedReport
            }
        }
    }
    Rectangle{
        Rectangle {
            id : typeCircle
            x:Math.round(145*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextType
            anchors.top:typeCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:typeCircle.horizontalCenter
        }
        Rectangle {
            x:Math.round(195*Style.scaleHint)
            y:Math.round(85*Style.scaleHint)
            width: Math.round(380*Style.scaleHint)
            height: Math.round( 1*Style.scaleHint)
            color: Style.generateReportCircleColor
        }
        Rectangle {
            id : strageOutputCircle
            x:Math.round(290*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)
            color: Style.generateReportCircleHighlightColor
            border.color: Style.headerBackgroundColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextStorgeOutput+"\n"+qmltextStorgeOutput1
            color: Style.headerBackgroundColor
            anchors.top:strageOutputCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:strageOutputCircle.horizontalCenter
        }
        Rectangle {
            id : datafiltersCircle
            x:Math.round(435*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)

            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextDataFilters +"\n"+qmltextDataFilters1
            anchors.top:datafiltersCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:datafiltersCircle.horizontalCenter
        }
        Rectangle {
            id:summeryCircle
            x:Math.round(575*Style.scaleHint)
            y:Math.round(60*Style.scaleHint)
            width: Math.round(50*Style.scaleHint)
            height: Math.round(50*Style.scaleHint)
            radius: Math.round(25*Style.scaleHint)

            border.color: Style.generateReportCircleColor
            border.width: Math.round(1*Style.scaleHint)
        }
        Label{
            text: qmltextSummary
            anchors.top:summeryCircle.bottom
            anchors.topMargin:Math.round(10 * Style.scaleHint)
            anchors.horizontalCenter:summeryCircle.horizontalCenter
        }
    }
    Rectangle {
        id: centerlineStorageOption
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
        y:Math.round(220*Style.scaleHint)
        width: Math.round(773*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        id:labelStorageOption
        text: qmltextStorageOption
        anchors.bottom:centerlineStorageOption.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Item {
        id:radiobtnsinglecont
        anchors.top:centerlineStorageOption.bottom
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnUsb
            text: qmltextUsb
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            font.family: Style.regular.name
            checked: (DataFilterListModel.getStorageOptionValue() == storageOptionEnum.usb) ? true : false
            onClicked:
            {
                if(checked)
                {
                    DataFilterListModel.setStorageOptionValue(storageOptionEnum.usb)
                }
            }
        }
        RadioButton
        {
            id:rdbtnNetworkAttachedStorage
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnUsb.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: qmltextNetworkAttachedStorage
            font.family: Style.regular.name
            checked: (DataFilterListModel.getStorageOptionValue() == storageOptionEnum.networkAttacheStorage) ? true : false
            onClicked:
            {
                if(checked)
                {
                    DataFilterListModel.setStorageOptionValue(storageOptionEnum.networkAttacheStorage)
                }
            }
        }
        RadioButton
        {
            id:rdbtnPlc
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnNetworkAttachedStorage.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: qmltextPlc
            font.family: Style.regular.name
            checked: (DataFilterListModel.getStorageOptionValue() == storageOptionEnum.plc) ? true : false
            onClicked:
            {
                if(checked)
                {
                    DataFilterListModel.setStorageOptionValue(storageOptionEnum.plc)
                }
            }
        }
    }
    Rectangle {
        id: encryptedDataOutputline
        anchors.left:encryptedDataId.left
        y:Math.round(310*Style.scaleHint)
        width: Math.round(773*Style.scaleHint)
        height: Math.round( 1*Style.scaleHint)
        color: Style.generateReportCircleColor
    }
    Label{
        id:encryptedDataId
        text: qmltextEncryptData
        anchors.bottom:encryptedDataOutputline.top
        anchors.bottomMargin:Math.round(5 * Style.scaleHint)
        anchors.leftMargin:Math.round(80 * Style.scaleHint)
    }
    Item
    {
        id:radiobtnEncrypted
        anchors.top:encryptedDataOutputline.bottom
        anchors.left:encryptedDataOutputline.left
        anchors.topMargin:Math.round(10 * Style.scaleHint)
        RadioButton
        {
            id:rdbtnYes
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            text: qmltextYes
            font.family: Style.regular.name
            checked: DataFilterListModel.m_EncryptedDataButton ? false : true
            onClicked:
            {
                if(checked){
                  DataFilterListModel.onEncryptionData(generateReportEncryptionDataEnum.yes)
                  DataFilterListModel.m_EncryptedDataButton = false
                }
                else
                {
                    DataFilterListModel.onEncryptionData(generateReportEncryptionDataEnum.no)
                    DataFilterListModel.m_EncryptedDataButton = true
                }

            }
        }
        RadioButton
        {
            id:rdbtnNo
            indicator.width: Math.round(20 * Style.scaleHint)
            indicator.height: Math.round(20 * Style.scaleHint)
            anchors.left:rdbtnYes.right
            anchors.leftMargin:Math.round(60 * Style.scaleHint)
            text: storageoption.qmltextNo
            font.family: Style.regular.name
            checked: DataFilterListModel.m_EncryptedDataButton ? false : true
            onClicked:
            {
                if(checked){
                  DataFilterListModel.onEncryptionData(generateReportEncryptionDataEnum.no)
                  DataFilterListModel.m_EncryptedDataButton = true
                }
                else
                {
                    DataFilterListModel.onEncryptionData(generateReportEncryptionDataEnum.yes)
                    DataFilterListModel.m_EncryptedDataButton = false
                }

            }
        }
    }
    BransonPrimaryButton
    {
        id: prvbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(400 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:150
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextPrevious
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.cancelButtonTextColor
        onClicked: {
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT)
        }
    }
    BransonPrimaryButton
    {
        id: nextbtn
        width:Math.round(150 * Style.scaleHint)
        x : Math.round(600 * Style.scaleHint)
        y : Math.round(350 * Style.scaleHint)
        anchors.topMargin:150
        height: Math.round(35 * Style.scaleHint)
        fontSize:Math.round(Style.style1 * Style.scaleHint)
        text: qmltextNext
        textColor: Style.buttonTextColor
        font.family: Style.regular.name
        buttonColor: Style.buttonColor
        onClicked: {
            mainWindow.menuChildOptionSelect(UIScreenEnum.GENERATEREPORT, UIScreenEnum.GENERATE_REPORT_CONTINUOUS_DATA_FILTER)
        }
    }
}

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

This file is related to systemInformation window display .
 **********************************************************************************************************/


import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {
    id:systemInformation

    property string qmltextMenuName             : "Information"
    property string qmlTextMachineDetails       : "Machine Details"
    property string qmlTextModel                : "Model"
    property string qmlTextModelValue           : "ACE PRO"
    property string qmlTextGeneralAlarm         : "Number of Alarms"

    property string qmlTextSotwareVersion       : "Software Versions"
    property string qmlTextUIController         : "UI Controller"
    property string qmlTextSupervisory          : "Supervisory Controller"
    property string qmlTextActuatorController   : "Actuator Controller"
    property string qmlTextPowerController      : "Power Controller"
    property string qmlTextSafetyController     : "Safety Controller"

    property string qmlTextSoftwareUpgrade      : "SOFTWARE UPGRADE"

    property string qmlTextPowerSupply          : "Power Supply"
    property string qmlTextSerialNumber         : "Serial Number"
    property string qmlTextLifeTimeWelds        : "Life Time Welds"
    property string qmlTextOverloads            : "Overloads"
    property string qmlTextPsType               : " Power Supply Model"
    property string qmlTextPSFrequency          : "Frequency"
    property string qmlTextPsWatt               : "Wattage"

    property string qmlTextActuator             : "Actuator"
    property string qmlTextActuatorSerialNumber : "Serial Number"
    property string qmlTextLifeTimeCycle        : "LifeTime Cycles"
    property string qmlTextType                 : "Actuator Model"
    property string qmlTextCalibrationDate      : "Calibration Date"
    property string qmlTextStrokeLength         : "Stroke Length"

    property string qmlTextConnectivity         : "Connectivity"
    property string qmlTextMacID                : "MAC ID "
    property string qmlTextConfigurationUpgrade : "Configuration Upgrade"
    property string qmlTextSystemFeatures       : "System Features"
    property string qmlTextStorage              : "Storage"
    property string qmlTextCylinderSize         : "Cylinder Size"
    property string qmlTextIndustrialEthernet   :"Industrial Ethernet"

    property string qmlTextOPCUA                : "OPC UA"
    property string qmlTextLDAP                 : "LDAP"
    property string qmlTextUserIODiagnostics    : "User IO Diagnostics"
    property string qmlTextBarcodeScanner       : "Barcode Scanner"
    property string qmlTextUserAccessLevel      : "User Access Level"
    property int actuatorRowNumber              : 1
    property string qmlTextBatchControl         : "Batch Control"
    property string qmlTextEventLogging         : "Event Logging"
    property string qmlTextElite                : "Elite"
    property string qmlTextAdvance              : "Advance"
    property string qmlTextBasic                : "Basic"
    property string qmlTextSupport              : "Support"
    property string qmlTextLocalHMI             : "Local HMI"
    property string qmlTextPCHMI                : "PC HMI"
    property string qmlTextPCUtility            : "PC Utility"
    property string qmlTextHMIType              : "HMI Type"
    property string qmlTextCOnfigurationVersion : "Configuration Version"

    property string qmlTextHundredAlarms            :"100 Alarms"
    property string qmlTextTenThousendWeldStorage   :"10k Weld Storage"
    property string qmlTextSixteenRecipes           :"16 Recipes"
    property string qmlTextFiveHundredAlarms        :"500 Alarms"
    property string qmlTextHundredKAlarms           :"100k Weld Storage"
    property string qmlTextFiftyRecipes             :"50 Recipes"
    property string qmlTextOneThousedAlarms         :"1000 Alarms"
    property string qmlTextOneThousendRecipes       :"1000 Recipes"
    property string qmlTextOneMillionsWeldStorage   :"1M Weld Storage"
    property string qmlTextSupported                :"Supported"
    property string qmlTextNotSupported             :"Not Supported"
    property string qmlTextStandard                 :"Standard"
    property string qmlTextAdvanced                 :"Advanced"
    property string qmlTextPremium                  :"Premium"
    property string qmlTextProfinet                 :"Profinet"
    property string qmlTextEthernetIP               :"Ethernet IP"
    property string qmlTextBearingType               :"Bearing Type"
    property string qmlTextBearingStandardType       :"Standard"
    property string qmlTextBearingStainlessSteelType :"Stainless Steel"
    property string qmlTextMachineSerialNum          : "Machine Serial Number"


    property var qmlTextArray: [qmlTextMachineDetails, qmlTextModel, qmlTextGeneralAlarm,
        qmlTextSotwareVersion, qmlTextUIController, qmlTextSupervisory, qmlTextActuatorController, qmlTextPowerController,
        qmlTextSoftwareUpgrade,qmlTextPowerSupply, qmlTextLifeTimeWelds, qmlTextOverloads, qmlTextPsType, qmlTextPSFrequency, qmlTextPsWatt,
        qmlTextActuator, qmlTextLifeTimeCycle, qmlTextType, qmlTextCalibrationDate,qmlTextStrokeLength,
        qmlTextConnectivity, qmlTextMacID,qmlTextSerialNumber,qmlTextActuatorSerialNumber, qmlTextConfigurationUpgrade,qmlTextSafetyController,
        qmlTextSystemFeatures,qmlTextStorage,qmlTextCylinderSize,qmlTextIndustrialEthernet,qmlTextOPCUA,qmlTextLDAP,qmlTextUserIODiagnostics,qmlTextBarcodeScanner,qmlTextUserAccessLevel,
        qmlTextBatchControl,qmlTextEventLogging,qmlTextElite,qmlTextAdvance,qmlTextBasic,
        qmlTextSupport,qmlTextLocalHMI,qmlTextPCHMI,qmlTextPCUtility,qmlTextHundredAlarms,qmlTextTenThousendWeldStorage,
        qmlTextSixteenRecipes,qmlTextFiveHundredAlarms,qmlTextHundredKAlarms,qmlTextFiftyRecipes,qmlTextOneThousedAlarms,qmlTextOneThousendRecipes,qmlTextOneMillionsWeldStorage,
        qmlTextSupported,qmlTextNotSupported,qmlTextStandard,qmlTextAdvanced,qmlTextPremium,qmlTextProfinet,qmlTextEthernetIP, qmlTextHMIType,qmlTextCOnfigurationVersion,
        qmlTextBearingType,qmlTextBearingStandardType,qmlTextBearingStainlessSteelType,qmlTextMachineSerialNum]

    QtObject {
        id: textEnum
        readonly property int machineDetailsIdx: 0
        readonly property int modelIdx: 1
        readonly property int generalAlarmIdx: 2
        readonly property int softwareVersionIdx: 3
        readonly property int uIControllerIdx: 4
        readonly property int supervisoryIdx: 5
        readonly property int actuatorControllerIdx: 6
        readonly property int powerControllerIdx: 7
        readonly property int softwareUpgradeIdx: 8
        readonly property int powerSupplyIdx: 9
        readonly property int lifeTimeWeldIdx: 10
        readonly property int overloadsIdx: 11
        readonly property int psTypeIdx: 12
        readonly property int pSFrequencyIdx: 13
        readonly property int psWattIdx: 14
        readonly property int actuatorIdx: 15
        readonly property int lifeTimeCycleIdx: 16
        readonly property int typeIdx: 17
        readonly property int calibrationDateIdx: 18
        readonly property int strokeLengthIdx: 19
        readonly property int connectivityIdx: 20
        readonly property int macIDIdx: 21
        readonly property int serialNmberIdx: 22
        readonly property int actuatorserialNmberIdx: 23
        readonly property int configurationUpgradeIdx:24
        readonly property int safetyControllerIdx:25
        readonly property int systemFeatureIdx:26
        readonly property int storageIdx:27
        readonly property int cylinderSizeIdx:28
        readonly property int industrialEthernetIdx: 29
        readonly property int oPCUAIdx: 30
        readonly property int lDAPIdx: 31
        readonly property int userIODiagnosticsIdx: 32
        readonly property int barcodeScannerIdx: 33
        readonly property int userAccessLevelIdx: 34
        readonly property int batchControlIdx: 35
        readonly property int eventLoggingIdx: 36
        readonly property int eliteIdx: 37
        readonly property int advanceIdx: 38
        readonly property int basicIdx: 39
        readonly property int supportIdx: 40
        readonly property int localHMIIdx:41
        readonly property int pCHMIIdx:42
        readonly property int pCUtilityIdx:43
        readonly property int hundredAlarmsIdx: 44
        readonly property int tenThousendWeldStorageIdx: 45
        readonly property int sixteenRecipesIdx: 46
        readonly property int fiveHundredAlarmsIdx: 47
        readonly property int hundredKAlarmsIdx: 48
        readonly property int fiftyRecipesIdx: 49
        readonly property int oneThousedAlarmsIdx: 50
        readonly property int oneThousendRecipesIdx: 51
        readonly property int oneMillionsWeldStorageIdx: 52
        readonly property int supportedIdx: 53
        readonly property int notSupportedIdx: 54
        readonly property int standardIdx:55
        readonly property int advancedIdx:56
        readonly property int premiumIdx:57
        readonly property int profinetIdx:58
        readonly property int ethernetIPIdx:59
        readonly property int hmiTypeIdx:60
        readonly property int configVerUpgrdIdx:61
        readonly property int bearingTypeIdx:62
        readonly property int bearingStandardIdx:63
        readonly property int bearingStainlessStellIdx:64
        readonly property int machineSerialNumIdx:65


    }

    QtObject {
        id: storageEnum
        readonly property int basicStorage   :1
        readonly property int advanceStorage :2
        readonly property int eliteStorage   :3
    }

    QtObject {
        id: supportedNotSupportedEnum
        readonly property int notSupported  :1
        readonly property int supported     :2
    }

    QtObject {
        id: hmiTypeEnum
        readonly property int hmiLocal    :1
        readonly property int hmiPC       :2
        readonly property int hmiBoth     :3
    }



    QtObject {
        id: userAccessLevelEnum
        readonly property int standard  :1
        readonly property int advance   :2
    }

    QtObject {
        id: bearingTypeEnum
        readonly property int bearingstandard         :1
        readonly property int bearingstainlessSteel   :2
    }

    QtObject {
        id: fieldBusEnum
        readonly property int noFieldBus    :1
        readonly property int ethernetIP    :2
        readonly property int profinet      :3
    }



    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM_INFO, qmlTextArray)
        qmlTextMachineDetails = qmlTextArray[textEnum.machineDetailsIdx]
        qmlTextModel = qmlTextArray[textEnum.modelIdx]
        qmlTextGeneralAlarm = qmlTextArray[textEnum.generalAlarmIdx]
        qmlTextSotwareVersion = qmlTextArray[textEnum.softwareVersionIdx]
        qmlTextUIController = qmlTextArray[textEnum.uIControllerIdx]
        qmlTextSupervisory = qmlTextArray[textEnum.supervisoryIdx]
        qmlTextActuatorController = qmlTextArray[textEnum.actuatorControllerIdx]
        qmlTextPowerController = qmlTextArray[textEnum.powerControllerIdx]
        qmlTextSoftwareUpgrade = qmlTextArray[textEnum.softwareUpgradeIdx]
        qmlTextPowerSupply = qmlTextArray[textEnum.powerSupplyIdx]
        qmlTextSerialNumber=qmlTextArray[textEnum.serialNmberIdx]
        qmlTextLifeTimeWelds = qmlTextArray[textEnum.lifeTimeWeldIdx]
        qmlTextOverloads = qmlTextArray[textEnum.overloadsIdx]
        qmlTextPsType = qmlTextArray[textEnum.psTypeIdx]
        qmlTextPSFrequency = qmlTextArray[textEnum.pSFrequencyIdx]
        qmlTextPsWatt = qmlTextArray[textEnum.psWattIdx]
        qmlTextActuator = qmlTextArray[textEnum.actuatorIdx]
        qmlTextActuatorSerialNumber=qmlTextArray[textEnum.actuatorserialNmberIdx]
        qmlTextLifeTimeCycle = qmlTextArray[textEnum.lifeTimeCycleIdx]
        qmlTextType = qmlTextArray[textEnum.typeIdx]
        qmlTextCalibrationDate = qmlTextArray[textEnum.calibrationDateIdx]
        qmlTextStrokeLength = qmlTextArray[textEnum.strokeLengthIdx]
        qmlTextConnectivity = qmlTextArray[textEnum.connectivityIdx]
        qmlTextMacID = qmlTextArray[textEnum.macIDIdx]
        qmlTextConfigurationUpgrade = qmlTextArray[textEnum.configurationUpgradeIdx]
        qmlTextSafetyController = qmlTextArray[textEnum.safetyControllerIdx]
        qmlTextSystemFeatures = qmlTextArray[textEnum.systemFeatureIdx]
        qmlTextStorage = qmlTextArray[textEnum.storageIdx]
        qmlTextCylinderSize = qmlTextArray[textEnum.cylinderSizeIdx]
        qmlTextIndustrialEthernet = qmlTextArray[textEnum.industrialEthernetIdx]
        qmlTextOPCUA = qmlTextArray[textEnum.oPCUAIdx]
        qmlTextLDAP = qmlTextArray[textEnum.lDAPIdx]
        qmlTextUserIODiagnostics = qmlTextArray[textEnum.userIODiagnosticsIdx]
        qmlTextBarcodeScanner = qmlTextArray[textEnum.barcodeScannerIdx]
        qmlTextUserAccessLevel = qmlTextArray[textEnum.userAccessLevelIdx]
        qmlTextBatchControl=qmlTextArray[textEnum.batchControlIdx]
        qmlTextEventLogging = qmlTextArray[textEnum.eventLoggingIdx]
        qmlTextElite = qmlTextArray[textEnum.eliteIdx]
        qmlTextAdvance = qmlTextArray[textEnum.advanceIdx]
        qmlTextBasic = qmlTextArray[textEnum.basicIdx]
        qmlTextSupport = qmlTextArray[textEnum.supportIdx]
        qmlTextLocalHMI = qmlTextArray[textEnum.localHMIIdx]
        qmlTextPCHMI = qmlTextArray[textEnum.pCHMIIdx]
        qmlTextPCUtility = qmlTextArray[textEnum.pCUtilityIdx]
        qmlTextHundredAlarms = qmlTextArray[textEnum.hundredAlarmsIdx]
        qmlTextTenThousendWeldStorage = qmlTextArray[textEnum.tenThousendWeldStorageIdx]
        qmlTextSixteenRecipes = qmlTextArray[textEnum.sixteenRecipesIdx]
        qmlTextFiveHundredAlarms = qmlTextArray[textEnum.fiveHundredAlarmsIdx]
        qmlTextHundredKAlarms = qmlTextArray[textEnum.hundredKAlarmsIdx]
        qmlTextFiftyRecipes = qmlTextArray[textEnum.fiftyRecipesIdx]
        qmlTextOneThousedAlarms = qmlTextArray[textEnum.oneThousedAlarmsIdx]
        qmlTextOneThousendRecipes = qmlTextArray[textEnum.oneThousendRecipesIdx]
        qmlTextOneMillionsWeldStorage = qmlTextArray[textEnum.oneMillionsWeldStorageIdx]
        qmlTextSupported = qmlTextArray[textEnum.supportedIdx]
        qmlTextNotSupported = qmlTextArray[textEnum.notSupportedIdx]
        qmlTextStandard = qmlTextArray[textEnum.standardIdx]
        qmlTextAdvanced = qmlTextArray[textEnum.advancedIdx]
        qmlTextPremium = qmlTextArray[textEnum.premiumIdx]
        qmlTextProfinet = qmlTextArray[textEnum.profinetIdx]
        qmlTextEthernetIP = qmlTextArray[textEnum.ethernetIPIdx]        
        qmlTextHMIType = qmlTextArray[textEnum.hmiTypeIdx]
        qmlTextCOnfigurationVersion = qmlTextArray[textEnum.configVerUpgrdIdx]
        qmlTextBearingType = qmlTextArray[textEnum.bearingTypeIdx]
        qmlTextBearingStandardType = qmlTextArray[textEnum.bearingStandardIdx]
        qmlTextBearingStainlessSteelType = qmlTextArray[textEnum.bearingStainlessStellIdx]
        qmlTextMachineSerialNum = qmlTextArray[textEnum.machineSerialNumIdx]

        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_INFO, qmltextMenuName)

        softwareVersionModel.resetSoftwareVersionModel()
        actuatorModel.resetActuatorModel()
        powerSupplyModel.resetPowerSupplyModel()
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }

    function getPCUtilityIconSource(modelIndex,resultIndex)
    {
        if(modelIndex == 0)
        {
            if(supportedNotSupportedEnum.notSupported === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
        else if(modelIndex == 1)
        {
            if(supportedNotSupportedEnum.supported === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }

    }

    function getIconSource(modelIndex,resultIndex)
    {
        if(modelIndex == 0)
        {
            if(supportedNotSupportedEnum.supported === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else
            {
                return "qrc:/Images/Icon_close.svg";
            }
        }
        else if(modelIndex == 1)
        {
            if(supportedNotSupportedEnum.notSupported === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else
            {
                return "qrc:/Images/Icon_close.svg";
            }
        }
    }


    function getIconSourceForHMIType(modelIndex,resultIndex)
    {
        if(resultIndex !==hmiTypeEnum.hmiBoth )
        {
            if(modelIndex == 0)
            {
                if(hmiTypeEnum.hmiLocal === resultIndex)
                {
                    return "qrc:/Images/Icon_check.svg";
                }
                else
                {
                    return "qrc:/Images/Icon_close.svg";
                }
            }
            else if(modelIndex == 1)
            {
                if(hmiTypeEnum.hmiPC === resultIndex)
                {
                    return "qrc:/Images/Icon_check.svg";
                }
                else
                {
                    return "qrc:/Images/Icon_close.svg";
                }
            }
        }
        else
        {
            return "qrc:/Images/Icon_check.svg";
        }   
    }


    function getBearingTypeIconSource(modelIndex,resultIndex)
    {
        if(modelIndex == 0)
        {
            if(bearingTypeEnum.bearingstandard === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
        else if(modelIndex == 1)
        {
            if(bearingTypeEnum.bearingstainlessSteel === resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
    }


    function getIconSourceIndustrialEthernet(modelIndex,resultIndex)
    {
        if(modelIndex == 0)
        {
            if(fieldBusEnum.noFieldBus == resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
        else if(modelIndex == 1)
        {
            if(fieldBusEnum.ethernetIP == resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
        else if(modelIndex == 2)
        {
            if(fieldBusEnum.profinet == resultIndex)
            {
                return "qrc:/Images/Icon_check.svg";
            }
            else{
                return "qrc:/Images/Icon_close.svg";
            }
        }
    }
    function getIconSourceForAsscessLevel(modelIndex,resultIndex)
    {
        if(modelIndex == 0)
        {
            if(userAccessLevelEnum.standard != resultIndex)
            {
                return "qrc:/Images/Icon_close.svg";
            }
            else{
                return "qrc:/Images/Icon_check.svg";
            }
        }
        else
        {
            if(userAccessLevelEnum.advance != resultIndex)
            {
                return "qrc:/Images/Icon_close.svg";
            }
            else{
                return "qrc:/Images/Icon_check.svg";
            }
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

        updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_INFO
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_INFO)
        basicModel.resetbasicModel();
        advanceModel.resetAdvanceModel();
        eliteModel.resetAdvanceModel();
        supportedAndNOTSupportedModel.resetSupportedAndNOTSupportedModel();
        standardAndAdvancedModel.resetstandardAndAdvancedModel();
        notSupportedPremiumModel.resetnotSupportedPremiumModel();
        industrialEthernetModel.resetindustrialEthernetModel();
        bearingTypeModel.resetAdvanceModel()
        hmiTypeModel.resetHMITypeModel()
    }

    Connections
    {
        target: SystemInformationModel

        function onSystemInfoMachineDetailsChanged()
        {
            softwareVersionModel.resetSoftwareVersionModel()
            actuatorModel.resetActuatorModel()
            powerSupplyModel.resetPowerSupplyModel()
            bearingTypeModel.resetAdvanceModel()
            hmiTypeModel.resetHMITypeModel()

        }
    }


    //software version content model
    ListModel{
        id:softwareVersionModel
        function resetSoftwareVersionModel(){
            softwareVersionModel.clear()
            softwareVersionModel.append({
                                            "protyName": qmlTextUIController,
                                            "protyValue": ""+SystemInformationModel.UIControllerVersion
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextSupervisory,
                                            "protyValue": ""+SystemInformationModel.SupervisoryControllerVersion
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextActuatorController,
                                            "protyValue": ""+SystemInformationModel.ActuatorControllerVersion
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextPowerController,
                                            "protyValue": ""+SystemInformationModel.PowerControllerVersion
                                        })
            softwareVersionModel.append({
                                            "protyName": qmlTextSafetyController,
                                            "protyValue": ""+SystemInformationModel.SafetyControllerVersion
                                        })
        }
    }

    ListModel{
        id:basicModel
        function resetbasicModel(){
            basicModel.clear()
            basicModel.append({
                                  "protyName": qmlTextHundredAlarms,
                                  "protyValue": ""
                              })
            basicModel.append({
                                  "protyName": qmlTextTenThousendWeldStorage,
                                  "protyValue": ""
                              })
            basicModel.append({
                                  "protyName": qmlTextSixteenRecipes,
                                  "protyValue": ""
                              })
        }
    }

    ListModel{
        id:advanceModel
        function resetAdvanceModel(){
            advanceModel.clear()
            advanceModel.append({
                                    "protyName": qmlTextFiveHundredAlarms,
                                    "protyValue": ""
                                })
            advanceModel.append({
                                    "protyName": qmlTextHundredKAlarms,
                                    "protyValue": ""
                                })
            advanceModel.append({
                                    "protyName": qmlTextFiftyRecipes,
                                    "protyValue": ""
                                })
        }
    }

    ListModel{
        id:bearingTypeModel
        function resetAdvanceModel(){
            bearingTypeModel.clear()
            bearingTypeModel.append({
                                    "protyName": qmlTextBearingStandardType,
                                    "protyValue": ""
                                    })

            bearingTypeModel.append({
                                    "protyName": qmlTextBearingStainlessSteelType,
                                    "protyValue": ""
                                })
        }
    }


    ListModel{
        id:hmiTypeModel
        function resetHMITypeModel(){
            hmiTypeModel.clear()
            hmiTypeModel.append({
                                    "protyName": qmlTextLocalHMI,
                                    "protyValue": ""
                                    })

            hmiTypeModel.append({
                                    "protyName": qmlTextPCHMI,
                                    "protyValue": ""
                                })
        }
    }

    ListModel{
        id: eliteModel
        function resetAdvanceModel(){
            eliteModel.clear()
            eliteModel.append({
                                  "protyName": qmlTextOneThousedAlarms,
                                  "protyValue": ""
                              })
            eliteModel.append({
                                  "protyName": qmlTextOneMillionsWeldStorage,
                                  "protyValue": ""
                              })
            eliteModel.append({
                                  "protyName": qmlTextOneThousendRecipes,
                                  "protyValue": ""
                              })
        }
    }

    ListModel{
        id: supportedAndNOTSupportedModel
        function resetSupportedAndNOTSupportedModel(){
            supportedAndNOTSupportedModel.clear()
            supportedAndNOTSupportedModel.append({
                                                     "protyName": qmlTextSupported,
                                                     "protyValue": ""
                                                 })
            supportedAndNOTSupportedModel.append({
                                                     "protyName": qmlTextNotSupported,
                                                     "protyValue": ""
                                                 })
        }
    }

    ListModel{
        id: standardAndAdvancedModel
        function resetstandardAndAdvancedModel(){
            standardAndAdvancedModel.clear()
            standardAndAdvancedModel.append({
                                                "protyName": qmlTextStandard,
                                                "protyValue": ""
                                            })
            standardAndAdvancedModel.append({
                                                "protyName": qmlTextAdvanced,
                                                "protyValue": ""
                                            })
        }
    }

    ListModel{
        id: notSupportedPremiumModel
        function resetnotSupportedPremiumModel(){
            notSupportedPremiumModel.clear()
            notSupportedPremiumModel.append({
                                                "protyName": qmlTextNotSupported,
                                                "protyValue": ""
                                            })
            notSupportedPremiumModel.append({
                                                "protyName": qmlTextSupported,
                                                "protyValue": ""
                                            })

        }
    }

    ListModel{
        id: industrialEthernetModel
        function resetindustrialEthernetModel(){
            industrialEthernetModel.clear()
            industrialEthernetModel.append({
                                                "protyName": qmlTextNotSupported,
                                                "protyValue": ""
                                            })
            industrialEthernetModel.append({
                                                "protyName": qmlTextEthernetIP,
                                                "protyValue": ""
                                            })
            industrialEthernetModel.append({
                                                "protyName": qmlTextProfinet,
                                                "protyValue": ""
                                            })
        }
    }
    //Power supply model
    ListModel{
        id: powerSupplyModel
        function resetPowerSupplyModel()
        {
            powerSupplyModel.clear()
            powerSupplyModel.append({
                                        "protyName": qmlTextSerialNumber,
                                        "protyValue": ""+SystemInformationModel.PSSerialNumber
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextLifeTimeWelds,
                                        "protyValue": ""+SystemInformationModel.PSLifeWelds
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextOverloads,
                                        "protyValue": ""+SystemInformationModel.PSOverloads
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPsType,
                                        "protyValue": ""+SystemInformationModel.PSModel
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPSFrequency,
                                        "protyValue": ""+SystemInformationModel.PSFrequency + " kHz"
                                    })
            powerSupplyModel.append({
                                        "protyName": qmlTextPsWatt,
                                        "protyValue": "" + SystemInformationModel.PSWatt + " W"
                                    })

        }
    }
    //actuator model
    ListModel{
        id: actuatorModel
        function resetActuatorModel()
        {
            actuatorModel.clear()
            actuatorModel.append({
                                     "protyName": qmlTextActuatorSerialNumber,
                                     "protyValue": ""+SystemInformationModel.ACSerialNumber,
                                     "propertyVisible": SystemTypeDef.ACTUATOR_MANUAL
                                 })
            actuatorModel.append({
                                     "protyName": qmlTextLifeTimeCycle,
                                     "protyValue": ""+SystemInformationModel.ActuatorLifeCycle,
                                     "propertyVisible": SystemTypeDef.ACTUATOR_MANUAL
                                 })
            actuatorModel.append({
                                     "protyName": qmlTextType,
                                     "protyValue": ""+SystemInformationModel.ActuatorModel,
                                     "propertyVisible":  SystemTypeDef.ACTUATOR_MANUAL
                                 })
            actuatorModel.append({
                                     "protyName": qmlTextCalibrationDate,
                                     "protyValue": ""+SystemInformationModel.ActuatorCalibrationDate,
                                     "propertyVisible": SystemTypeDef.ACTUATOR_MANUAL
                                 })
            actuatorModel.append({
                                     "protyName": qmlTextStrokeLength,
                                     "protyValue": ""+SystemInformationModel.StrokeLength,
                                     "propertyVisible":  SystemTypeDef.ACTUATOR_MANUAL | SystemTypeDef.ACTUATOR_MANUAL
                                 })
            actuatorModel.append({
                                     "protyName": qmlTextCylinderSize,
                                     "protyValue": ""+SystemInformationModel.CylinderSize,
                                     "propertyVisible":  SystemTypeDef.ACTUATOR_MANUAL | SystemTypeDef.ACTUATOR_MANUAL
                                 })
        }
    }

    Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: Math.round(300 * Style.scaleHint)
        height: Math.round(25 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(20 * Style.scaleHint)
            spacing: Math.round(26 * Style.scaleHint)
            background: Rectangle
            {
                color: Style.backgroundColor
            }
            BransonTabButton
            {
                id: tabbtnMachineDetails
                width: recipeTabBar / 2
                tabbtnText: qmlTextMachineDetails
                onClicked:{
                    softwareUpgrade.visible = true
                    softwareUpgrade.enabled = true
                    configUpgrade.visible = false
                    configUpgrade.enabled = false
                    infoSystemScrollRec.visible = false
                    infoMachineDetailsRec.visible = true
                }
            }
            BransonTabButton
            {
                id: tabbtnSystemFeatures
                width: recipeTabBar / 2
                tabbtnText: qmlTextSystemFeatures
                onClicked:{
                    softwareUpgrade.visible = false
                    softwareUpgrade.enabled = false
                    configUpgrade.visible = true
                    configUpgrade.enabled = true
                    infoSystemScrollRec.visible = true
                    infoMachineDetailsRec.visible = false
                }
            }
        }
    }
    Flickable{
        id: infoSystemScrollRec
        width: parent.width//zoomingSize(800)
        height: zoomingSize(300)
        anchors.top: tabBarBackground.bottom
        anchors.topMargin: zoomingSize(17)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.02
        contentHeight: zoomingSize(1300)
        clip: true
        visible: false
        Rectangle{
            id:conifgTextID
            anchors.top:infoSystemScrollRec.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            color: Style.contentBackgroundColor
            Text{
                text:qmlTextCOnfigurationVersion + " : " +SystemFeature.ConfigurationVersion
                font.pixelSize: Math.round(style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }

        Rectangle{
            id:storageTextID
            anchors.top:conifgTextID.bottom
            anchors.topMargin:zoomingSize(30)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text:qmlTextStorage
                font.pixelSize: Math.round(style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectStorageData
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: storageTextID.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.20
            color: Style.contentBackgroundColor
            Row{
                id: rowStorage
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.05

                Rectangle{
                    id: rectBasic
                    width: parent.width * 0.20
                    border.width: zoomingSize(1)
                    border.color: Style.blackFontColor
                    color : "transparent"
                    height: rowStorage.height
                    Image{
                        id: imgBasic
                        height: txtBasic.height * 0.35
                        width: txtBasic.height * 0.35
                        anchors.top:txtBasic.top
                        anchors.topMargin: Math.round(10 * Style.scaleHint)
                        anchors.left: parent.left
                        anchors.leftMargin: rectBasicTitleBottomLine.width * 0.10
                        source: SystemFeature.storageType == storageEnum.basicStorage ? "qrc:/Images/Icon_check.svg" : "qrc:/Images/Icon_close.svg"
                    }
                    Text{
                        id: txtBasic
                        width: parent.width * 0.35
                        anchors.top:parent.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: rectBasicTitleBottomLine.top
                        anchors.left: imgBasic.right
                        anchors.leftMargin: zoomingSize(5)
                        anchors.verticalCenter: parent.verticalCenter
                        text:qmlTextBasic
                        font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                        font.family: Style.semibold.name
                    }
                    Rectangle{
                        id: rectBasicTitleBottomLine
                        width: parent.width
                        height: zoomingSize(1)
                        anchors.top: parent.top
                        anchors.topMargin: parent.height * 0.25
                        anchors.left : parent.left
                        anchors.right: parent.right
                        border.width: zoomingSize(1)
                        border.color: Style.blackFontColor
                        color : "transparent"
                    }
                    Column {
                        id: columnBasicData
                        anchors.top: rectBasicTitleBottomLine.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height * 0.03
                        anchors.left: parent.left
                        anchors.leftMargin: rectBasicTitleBottomLine.width * 0.10
                        spacing: zoomingSize(15)
                        Repeater {
                            id: repeaterBasicData
                            model: basicModel
                            delegate: Text {
                                text: protyName
                                font.pixelSize: 20
                                color:Style.blackFontColor
                            }
                        }
                    }
                }

                Rectangle{
                    id: rectAdvance
                    height: rowStorage.height
                    width: parent.width * 0.40
                    border.width: zoomingSize(1)
                    border.color: Style.blackFontColor
                    color : "transparent"

                    Image{
                        id: imgAdvance
                        height: txtAdvance.height * 0.35
                        width: txtAdvance.height * 0.35
                        anchors.top:txtAdvance.top
                        anchors.topMargin: Math.round(10 * Style.scaleHint)
                        anchors.left: parent.left
                        anchors.leftMargin: rectAdvanceTitleBottomLine.width * 0.10
                        source: SystemFeature.storageType == storageEnum.advanceStorage ? "qrc:/Images/Icon_check.svg" : "qrc:/Images/Icon_close.svg"
                    }
                    Text{
                        id: txtAdvance
                        width: parent.width * 0.35
                        anchors.top:parent.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: rectAdvanceTitleBottomLine.top
                        anchors.left: imgAdvance.right
                        anchors.leftMargin: zoomingSize(5)
                        anchors.verticalCenter: parent.verticalCenter
                        text:qmlTextAdvance
                        font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                        font.family: style.semibold.name
                    }
                    Rectangle{
                        id: rectAdvanceTitleBottomLine
                        width: parent.width
                        height: zoomingSize(1)
                        anchors.top: parent.top
                        anchors.topMargin: parent.height * 0.25
                        anchors.left : parent.left
                        anchors.right: parent.right
                        border.width: zoomingSize(1)
                        border.color: Style.blackFontColor
                        color : "transparent"
                    }
                    Column {
                        id: columnAdvanceData
                        anchors.top: rectAdvanceTitleBottomLine.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height * 0.03
                        anchors.left: parent.left
                        anchors.leftMargin: rectAdvanceTitleBottomLine.width * 0.10
                        spacing: zoomingSize(15)
                        Repeater {
                            id: repeaterAdvanceData
                            model: advanceModel
                            delegate: Text {
                                text: protyName
                                font.pixelSize: 20
                                color:Style.blackFontColor
                            }
                        }
                    }
                }

                Rectangle{
                    id: rectElite
                    height: rowStorage.height
                    width: parent.width * 0.30
                    border.width: zoomingSize(1)
                    border.color: Style.blackFontColor
                    color : "transparent"
                    Image{
                        id: imgElite
                        height: txtElite.height * 0.35
                        width: txtElite.height * 0.35
                        anchors.top:txtElite.top
                        anchors.topMargin: Math.round(10 * Style.scaleHint)
                        anchors.left: parent.left
                        anchors.leftMargin: rectAdvanceTitleBottomLine.width * 0.10
                        source: SystemFeature.storageType == storageEnum.eliteStorage ? "qrc:/Images/Icon_check.svg" : "qrc:/Images/Icon_close.svg"
                    }
                    Text{
                        id: txtElite
                        width: parent.width * 0.35
                        anchors.top:parent.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: rectEliteTitleBottomLine.top
                        anchors.left: imgElite.right
                        anchors.leftMargin: zoomingSize(5)
                        anchors.verticalCenter: parent.verticalCenter
                        text:qmlTextElite
                        font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                        font.family: Style.semibold.name
                    }
                    Rectangle{
                        id: rectEliteTitleBottomLine
                        width: parent.width
                        height: zoomingSize(1)
                        anchors.top: parent.top
                        anchors.topMargin: parent.height * 0.25
                        anchors.left : parent.left
                        anchors.right: parent.right
                        border.width: zoomingSize(1)
                        border.color: Style.blackFontColor
                        color : "transparent"
                    }
                    Column {
                        id: columnEliteData
                        anchors.top: rectEliteTitleBottomLine.top
                        anchors.topMargin: parent.height * 0.03
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height * 0.03
                        anchors.left: parent.left
                        anchors.leftMargin: rectEliteTitleBottomLine.width * 0.10
                        spacing: zoomingSize(15)
                        Repeater {
                            id: repeaterEliteData
                            model: eliteModel
                            delegate: Text {
                                text: protyName
                                font.pixelSize: 20
                                color:Style.blackFontColor
                            }
                        }
                    }
                }
            }
        }
        Rectangle{
            id: rectEventLoggingText
            anchors.top:rectStorageData.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text:qmlTextEventLogging
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectEventlogging
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectEventLoggingText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowEventLogging
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterEventLogging
                    model: supportedAndNOTSupportedModel
                    delegate:Row{
                        width: rectEventlogging.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOptionEventLogging
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source: getIconSource(model.index,SystemFeature.eventLogging);
                        }
                        Text{
                            id: txtOptionEventLogging
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }

        Rectangle{
            id: rectBatchControlText
            anchors.top:rectEventlogging.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextBatchControl
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectBatchControl
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectBatchControlText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowBatchControl
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterBatchControl
                    model: supportedAndNOTSupportedModel
                    delegate:Row{
                        width: rectBatchControl.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOptionBatchControl
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getIconSource(model.index,SystemFeature.batchControl);
                        }
                        Text{
                            id: txtOptionBatchControl
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }

        Rectangle{
            id: rectUserAccessLevelText
            anchors.top:rectBatchControl.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text:qmlTextUserAccessLevel
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectUserAccessLevel
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectUserAccessLevelText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowUserAccessLevel
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterUserAccessLevel
                    model: standardAndAdvancedModel
                    delegate:Row{
                        width: rectUserAccessLevel.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOptionUserAccessLevel
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source: getIconSourceForAsscessLevel(model.index,SystemFeature.userAccessLevel)
                        }
                        Text{
                            id: txtOptionUserAccessLevel
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }


        Rectangle{
            id: rectBarcodeScannerText
            anchors.top:rectUserAccessLevel.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextBarcodeScanner
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectBarcodeScanner
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectBarcodeScannerText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowBarcodeScanner
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterBarcodeScanner
                    model: supportedAndNOTSupportedModel
                    delegate:Row{
                        width: rectBarcodeScanner.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOptionBarcodeScanner
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getIconSource(model.index,SystemFeature.barcodeScanner);
                        }
                        Text{
                            id: txtOptionBarcodeScanner
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }


        Rectangle{
            id: rectUserIODiagnosticsText
            anchors.top:rectBarcodeScanner.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text:qmlTextUserIODiagnostics
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectUserIODiagnostics
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectUserIODiagnosticsText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowUserIODiagnostics
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterUserIODiagnostics
                    model: supportedAndNOTSupportedModel
                    delegate:Row{
                        width: rectUserIODiagnostics.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOptionUserIODiagnostics
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getIconSource(model.index,SystemFeature.userIODiagnostics);
                        }
                        Text{
                            id: txtOptionUserIODiagnostics
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }

        Rectangle{
            id: rectLDAPText
            anchors.top:rectUserIODiagnostics.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextLDAP
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectLDAP
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectLDAPText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowLDAP
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterLDAP
                    model: supportedAndNOTSupportedModel
                    delegate:Row{
                        width: rectLDAP.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgLDAP
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getIconSource(model.index,SystemFeature.ldap);
                        }
                        Text{
                            id: txtLDAP
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }


        Rectangle{
            id: rectOpcUaText
            anchors.top:rectLDAP.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextBearingType
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectOpcUa
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectOpcUaText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowOpcUa
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterOpcUa
                    model: bearingTypeModel
                    delegate:Row{
                        width: rowOpcUa.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgOpcUa
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getBearingTypeIconSource(model.index,SystemInformationModel.bearingType);
                        }
                        Text{
                            id: txtOpcUa
                            width: 70
                            text:  protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }


        Rectangle{
            id: rectIndustrialEnternetText
            anchors.top:rectOpcUa.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextIndustrialEthernet
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectIndustrialEnternet
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectIndustrialEnternetText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowIndustrialEnternet
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterIndustrialEnternet
                    model: industrialEthernetModel
                    delegate:Row{
                        width: rectIndustrialEnternet.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgIndustrialEnternet
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter

                            source: getIconSourceIndustrialEthernet(model.index,SystemFeature.industrialEthernet)
                        }
                        Text{
                            id: txtIndustrialEnternet
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }


        Rectangle{
            id: rectSupportText
            anchors.top:rectIndustrialEnternet.bottom
            anchors.topMargin:zoomingSize(5)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextSupport
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectLocalHMIText
            anchors.top:rectSupportText.bottom
            anchors.topMargin:zoomingSize(30)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextHMIType
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectLocalHMI
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectLocalHMIText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowLocalHMI
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterLocalHMI
                    model: hmiTypeModel
                    delegate:Row{
                        width: rectLocalHMI.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgLocalHMI
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source:getIconSourceForHMIType(model.index,SystemFeature.HMIType);
                        }
                        Text{
                            id: txtLocalHMI
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }

        Rectangle{
            id: rectPCUtilityText
            anchors.top:rectLocalHMI.bottom
            anchors.topMargin:zoomingSize(30)
            anchors.leftMargin: zoomingSize(29)
            anchors.left: parent.left
            Text{
                text: qmlTextPCUtility
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                font.family: Style.semibold.name
                color: Style.blackFontColor
            }
        }
        Rectangle{
            id: rectPCUtility
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            anchors.top: rectPCUtilityText.bottom
            anchors.topMargin: zoomingSize(30)
            height: parent.width * 0.05
            color: Style.contentBackgroundColor
            Row{
                id: rowPCUtility
                anchors.left: parent.left
                anchors.leftMargin: zoomingSize(18)
                anchors.right: parent.right
                anchors.rightMargin: zoomingSize(18)
                anchors.top: parent.top
                anchors.topMargin: zoomingSize(18)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: zoomingSize(18)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing : parent.width * 0.20
                Repeater{
                    id: repeaterPCUtility
                    model: notSupportedPremiumModel
                    delegate:Row{
                        width: rowPCUtility.width * 0.20
                        spacing: zoomingSize(10)
                        Image{
                            id: imgPCUtility
                            height: parent.height * 0.70
                            width: parent.height * 0.70
                            anchors.verticalCenter: parent.verticalCenter
                            source: getPCUtilityIconSource(model.index,SystemFeature.pcUtility)
                        }
                        Text{
                            id: txtPCUtility
                            width: 70
                            text: protyName
                            font.pixelSize: 20
                            color:Style.blackFontColor
                        }
                    }
                }
            }
        }
    }
    Rectangle{
        id: dashboardID
        anchors.bottom: parent.bottom
        anchors.bottomMargin: zoomingSize(5)
        anchors.left: parent.left
        anchors.right:  parent.right
        width: parent.width
        height: zoomingSize(40)
        color: Style.textFieldBackgoundColor
        BransonPrimaryButton{
            id: softwareUpgrade
            anchors.right: parent.right
            anchors.rightMargin:zoomingSize(10)
            anchors.verticalCenter:parent.verticalCenter
            visible: true
            enabled: true
            implicitWidth: zoomingSize(181)
            implicitHeight: zoomingSize(30)
            fontSize: zoomingSize(Style.style4)
            text: qmlTextSoftwareUpgrade
            font.family: Style.regular.name
            buttonColor: UserPrivilegeObj.IsUpdateSoftwareAllowed || mainWindow.isAuthorityCheckEnable ? "#17345C" : "#9B9E9C"
            onClicked: {
                if(UserPrivilegeObj.IsUpdateSoftwareAllowed || mainWindow.isAuthorityCheckEnable)
                {
                    mainWindow.currentActiveWindow =   ActiveScreen.CurrentActiveScreen
                    mainWindow.showSoftwareUpgrade()
                    ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_SOFTWARE_UPGRADE
                }
            }
        }
        BransonPrimaryButton{
            id: configUpgrade
            anchors.right: parent.right
            anchors.rightMargin:zoomingSize(10)
            anchors.verticalCenter:parent.verticalCenter
            visible: false
            enabled: false
            implicitWidth: zoomingSize(230)
            implicitHeight: zoomingSize(30)
            fontSize: zoomingSize(Style.style4)
            text: qmlTextConfigurationUpgrade
            font.family: Style.regular.name
            buttonColor: "#17345C"
            onClicked: {
                mainWindow.showConfigurationUpgrade()
            }
        }
    }
    Flickable{
        id: infoMachineDetailsRec
        width: parent.width//zoomingSize(800)
        height: zoomingSize(373)
        anchors.top: tabBarBackground.bottom
        anchors.topMargin: zoomingSize(17)
        anchors.bottom: dashboardID.top
        anchors.bottomMargin: parent.height*0.02
        contentHeight: zoomingSize(840)
        clip: true
        visible: true

        //model item and Gerneral Alarm
        Row{
            id: deviceInfoRow
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            spacing: zoomingSize(16)
            BransonInfoElement{
                id: generalAlarm
                width: softwareVersionRec.width*0.47
                protyName: qmlTextGeneralAlarm
                protyValue: SystemInformationModel.GerneralAlarms
            }
        }


        //software version text
        Text{
            id: softwareVersionText
            anchors.top: deviceInfoRow.bottom
            anchors.topMargin: zoomingSize(16)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(29)
            font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
            font.family: Style.semibold.name
            text: qmlTextSotwareVersion
            color: Style.blackFontColor
        }

        //software line
        Rectangle{
            id: softwareVersionLine
            anchors.top: softwareVersionText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right:  parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //software version content screen
        Rectangle{
            id: softwareVersionRec
            color: "transparent"//Style.backgroundColor
            anchors.top: softwareVersionText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: parent.left
            anchors.leftMargin: zoomingSize(18)
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * 3 + 30)
            GridView{
                id: gridViewSoftwareVersion
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 3
                cellWidth: parent.width / 2
                model: softwareVersionModel
                delegate: BransonInfoElement{
                    width: softwareVersionRec.width*0.47
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }

        //Machine Serial number content
        Text{
            id: machineSerialNoText
            anchors.top: softwareVersionRec.bottom
            anchors.topMargin: zoomingSize(20)
            anchors.left: softwareVersionText.left
            text: qmlTextMachineSerialNum
            font.pixelSize:  Math.round(Style.style6 * Style.scaleHint)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }

        //Machine Serial number line
        Rectangle{
            id: machineSerialNoLine
            anchors.top: machineSerialNoText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            anchors.right:  parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }
        BransonInfoElement{
            id: machineSerialNoContent
            width: softwareVersionRec.width*0.47
            anchors.top: machineSerialNoText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: machineSerialNoText.left
            protyName: qmlTextMachineSerialNum
            protyValue: SystemInformationModel.MachineSerialNumber
        }

        //Power Supply
        Text{
            id: powerSupplyText
            anchors.top: machineSerialNoContent.bottom
            anchors.topMargin: zoomingSize(20)
            anchors.left: softwareVersionText.left
            text: qmlTextPowerSupply
            font.pixelSize:  Math.round(Style.style6 * Style.scaleHint)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }

        //Power Supply line
        Rectangle{
            id: powerSupplyLine
            anchors.top: powerSupplyText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            anchors.right:  parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }


        //Power supply content screen
        Rectangle{
            id: powerSupplyContent
            color: "transparent"//Style.backgroundColor
            anchors.top: powerSupplyText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: softwareVersionRec.left
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * 3 + 30)
            GridView{
                id: powerSupplyGridView
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 3
                cellWidth: parent.width / 2
                model: powerSupplyModel
                delegate: BransonInfoElement{
                    width: softwareVersionRec.width*0.47
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }


        //actuator text
        Text{
            id: actuatorText
            anchors.top: powerSupplyContent.bottom
            anchors.topMargin: zoomingSize(7)
            anchors.left: powerSupplyText.left
            text: qmlTextActuator
            font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }
        //actuator line
        Rectangle{
            id: actuatorLine
            anchors.top: actuatorText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            anchors.right:  parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //actuator content screen
        Rectangle{
            id: actuatorContent
            color: "transparent"//Style.backgroundColor
            anchors.top: actuatorText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: softwareVersionRec.left
            anchors.right: parent.right
            anchors.rightMargin: zoomingSize(10)
            width: zoomingSize(374 * 2 + 32)
            height: zoomingSize(35 * 3 + 30)
            GridView{
                id: acturtorGridView
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 3
                cellWidth: parent.width / 2
                model: actuatorModel
                delegate: BransonInfoElement{
                    width: softwareVersionRec.width*0.47
                    protyName: model.protyName
                    protyValue: model.protyValue
                }
            }
        }

        //connectivity text
        Text{
            id: connectivityText
            anchors.top:actuatorContent.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: powerSupplyText.left
            text: qmlTextConnectivity
            font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
            color: Style.blackFontColor
            font.family: Style.semibold.name
        }
        //connectivity line
        Rectangle{
            id: connectivityLine
            anchors.top: connectivityText.bottom
            anchors.topMargin: zoomingSize(5)
            anchors.left: softwareVersionLine.left
            anchors.right:  parent.right
            anchors.rightMargin: zoomingSize(18)
            width: zoomingSize(770)
            height: zoomingSize(1)
            color: Style.blackFontColor
        }

        //MAC ID
        BransonInfoElement{
            id: macID
            width: softwareVersionRec.width*0.47
            anchors.top: connectivityText.bottom
            anchors.topMargin: zoomingSize(17)
            anchors.left: actuatorContent.left
            protyName: qmlTextMacID
            protyValue: SystemInformationModel.MACAddress
        }
    }
}

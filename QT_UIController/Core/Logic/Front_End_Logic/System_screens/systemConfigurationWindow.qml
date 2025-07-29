/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/
import QtQuick 2.12
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick 2.15
//import QtGraphicalEffects 1.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../System_screens"

Item {
    id: sysConfgGenWindow

    property string qmltextMenuName:                "Configuration"

    property string qmltextGeneral:                 "General"
    property string qmltextUserManagement:          "User Management"
    property string qmltextUserIO:                  "User I/O"

    property string qmltextIndusEthIO:              "Industrial Ethernet I/O"

    property string qmltextNtwrkConfig:             "Network Config"
    property string qmltextAlarmManagement:         "Alarm Mgmt"

    property string qmltextUSBAuthentication:       "USB Authentication"
    property string qmltextLDAPConfg:               "LDAP Config"
    property string qmltextGatewayData:             "Gateway Data"

    property string qmltextUserList                : "User List"
    property string qmltextGlobalUserSetting       : "Global User Setting"
    property string qmltextAddUser                 : "ADD USER"
    property string qmltextDigitalIo               : "Digital I/O"
    property string qmltextAnalogIo                : "Analog I/O"
    property string qmltextBranson                 : "Branson"
    property string qmltextIpSetUp                 : "IP Setup"
    property string qmltextEthernetIp              : "Ethernet IP"
    property string qmltextProfinet                : "Profinet"
    property string qmltextNFSSetup                : "NFS Setup"

    property string qmltextUSBRegistration         : "USB Device Registration "
    property string qmltextUSBDeRegistration       : "USB Device Deregistration "

    property int currentTabBarIndex: 0

    QtObject {
        id: enumTabBarIndex
        readonly property int generalIdx:              0
        readonly property int userManagementIdx:       1
        readonly property int userIOIdx:               2
        readonly property int indEthIOIdx:             3


        readonly property int ntwrkConfigIdx:          4
        readonly property int alarmManagementIdx:      5
        readonly property int ldapConfgIdx:            6
        readonly property int gatewayDataIdx:          7
        readonly property int userListIdx:             8
        readonly property int globalUserSettingIdx:    9
        readonly property int userDigitalIOIdx:        10
        readonly property int userAnalogIOIdx:         11
        readonly property int userIpSetUpIdx:          12
        readonly property int userEipIdx:              13
        readonly property int userProfinetIdx:         14
        readonly property int userNFSSetupIdx:         15
        readonly property int bransonIdx:              16
        readonly property int usbAuthenticationIdx:    17
        readonly property int usbRegistrationIdx:      18
        readonly property int usbDeRegistrationIdx:    19


    }

    function updateLanguage()
    {
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG, qmltextMenuName)
        qmltextGeneral = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_GENERAL, qmltextGeneral)
        qmltextUserManagement = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT, qmltextUserManagement)
        qmltextUserIO = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_USERIO, qmltextUserIO)
        qmltextIndusEthIO = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL, qmltextIndusEthIO)
        qmltextNtwrkConfig = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION, qmltextNtwrkConfig)
        qmltextAlarmManagement = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT, qmltextAlarmManagement)
        qmltextLDAPConfg = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_LDAP_CONFIG, qmltextLDAPConfg)
        qmltextGatewayData = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_GATEWAY_DATA, qmltextGatewayData)

        qmltextDigitalIo = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO , qmltextDigitalIo)
        qmltextAnalogIo = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO , qmltextAnalogIo)
        qmltextBranson = LanguageConfig.getLanguageMenuName(UIScreenEnum.BRANSON_SYSTEM_CONFIGURATION , qmltextBranson)

        switch(currentTabBarIndex)
        {
        case enumTabBarIndex.generalIdx:
            systemConfigTabBarModel.setProperty(0, "Title", qmltextGeneral)
            systemConfigTabBarModel.setProperty(1, "Title", qmltextUserManagement)
            systemConfigTabBarModel.setProperty(2, "Title", qmltextUserIO)
            systemConfigTabBarModel.setProperty(3, "Title", qmltextIndusEthIO)
            systemConfigTabBarModel.setProperty(4, "Title", qmltextNtwrkConfig)
            systemConfigTabBarModel.setProperty(5, "Title", qmltextAlarmManagement)
            systemConfigTabBarModel.setProperty(6, "Title", qmltextUSBAuthentication)
            systemConfigTabBarModel.setProperty(7, "Title", qmltextLDAPConfg)
            systemConfigTabBarModel.setProperty(8, "Title", qmltextGatewayData)
            systemConfigTabBarModel.setProperty(9, "Title", qmltextBranson)

            break
        default:
            break

        }
    }

    function updateSystemConfigTabBar()
    {
        systemConfigTabBarModel.clear()
        if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive || UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed || mainWindow.isAuthorityCheckEnable)
        {
            systemConfigTabBarModel.append({"Title":      qmltextGeneral,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.generalIdx})
        }

        if(UserPrivilegeObj.getLogedInUserLevel()  === mainWindow.qmltextExecutive|| mainWindow.isPasswordRestDongleInserted || !(mainWindow.isAuthorityCheckEnable))
        {
            if(UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextOperator && UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextTechnician && UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextSupervisor)
            {
                systemConfigTabBarModel.append({"Title":      qmltextUserManagement,
                                                   "Width":      Math.round(110 * Style.scaleHint),
                                                   "Index":      enumTabBarIndex.userManagementIdx})
            }
        }

        if(SystemConfiguration.UserIOSupportSystemType == SystemTypeDef.USER_IO_SUPPORTED  )
        {
            if ((UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextTechnician) ||
                    (UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextSupervisor) ||
                    (UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive) ||
                    (mainWindow.isAuthorityCheckEnable))
            {

                systemConfigTabBarModel.append({"Title":      qmltextUserIO,
                                                   "Width":      Math.round(100 * Style.scaleHint),
                                                   "Index":      enumTabBarIndex.userIOIdx})
            }
        }

        //Industrial User IO Tab
        if(SystemConfiguration.FieldBusSupportSystemType !== SystemTypeDef.FIELDBUS_NOT_SUPPORTED )
        {
            if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable)
            {
                systemConfigTabBarModel.append({"Title":      qmltextIndusEthIO,
                                                   "Width":      Math.round(100 * Style.scaleHint),
                                                   "Index":      enumTabBarIndex.indEthIOIdx})

            }
        }

        if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable)
        {
            systemConfigTabBarModel.append({"Title":      qmltextNtwrkConfig,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.ntwrkConfigIdx})
            systemConfigTabBarModel.append({"Title":      qmltextAlarmManagement,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.alarmManagementIdx})

            systemConfigTabBarModel.append({"Title":      qmltextUSBAuthentication,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.usbAuthenticationIdx})

            systemConfigTabBarModel.append({"Title":      qmltextLDAPConfg,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.ldapConfgIdx})
            systemConfigTabBarModel.append({"Title":      qmltextGatewayData,
                                               "Width":      Math.round(100 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.gatewayDataIdx})
            if(mainWindow.bransonTabEnable === true)
            {
                systemConfigTabBarModel.append({"Title":      qmltextBranson,
                                                   "Width":      Math.round(100 * Style.scaleHint),
                                                   "Index":      enumTabBarIndex.bransonIdx})
            }
        }
    }

    function updateUserIOTabBar()
    {
        userIOTabBarModel.clear()
        userIOTabBarModel.append({"Title":         qmltextDigitalIo,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.userDigitalIOIdx})
        userIOTabBarModel.append({"Title":         qmltextAnalogIo,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.userAnalogIOIdx})
    }

    function updateUSBAuthTabBar()
    {
        usbAuthTabBarModel.clear()
        usbAuthTabBarModel.append({"Title":         qmltextUSBRegistration,
                                     "Width":      Math.round(180 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.usbRegistrationIdx})
        usbAuthTabBarModel.append({"Title":         qmltextUSBDeRegistration,
                                     "Width":      Math.round(180 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.usbDeRegistrationIdx})
    }


    function updateNetWrkConfigTabBar()
    {
        ntwrkConfigTabBarModel.clear()
        ntwrkConfigTabBarModel.append({"Title":         qmltextIpSetUp,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.userIpSetUpIdx})

        ntwrkConfigTabBarModel.append({"Title":         qmltextNFSSetup,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.userNFSSetupIdx})

        if(SystemConfiguration.FieldBusSupportSystemType === SystemTypeDef.FIELDBUS_ETHERNET_IP)
        {
            ntwrkConfigTabBarModel.append({"Title":         qmltextEthernetIp,
                                              "Width":      Math.round(100 * Style.scaleHint),
                                              "Index":      enumTabBarIndex.userEipIdx})
        }
        else if(SystemConfiguration.FieldBusSupportSystemType === SystemTypeDef.FIELDBUS_PROFINET)
        {
            ntwrkConfigTabBarModel.append({"Title":         qmltextProfinet,
                                              "Width":      Math.round(100 * Style.scaleHint),
                                              "Index":      enumTabBarIndex.userProfinetIdx})
        }
    }


    function updateTabBar(index)
    {
        subSystemConfigDetails.source = ""
        currentTabBarIndex = index

        switch(index)
        {
        case enumTabBarIndex.generalIdx:
            if( UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive || UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed ||  mainWindow.isAuthorityCheckEnable)
            {
                mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_GENERAL)
                mainWindow.setHeaderTitle(qmltextGeneral, UIScreenEnum.SYSTEM_CONFIG_GENERAL)
                updateSystemConfigTabBar()
                subtabBarBackground1.visible = false
                subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationGeneral.qml"
            }
            break;
        case enumTabBarIndex.userManagementIdx:
            if(UserPrivilegeObj.getLogedInUserLevel()  === mainWindow.qmltextExecutive || mainWindow.isPasswordRestDongleInserted || !(mainWindow.isAuthorityCheckEnable))
            {
                if(UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextOperator && UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextTechnician && UserPrivilegeObj.getLogedInUserLevel()  !== mainWindow.qmltextSupervisor)
                {
                    mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT)
                    mainWindow.setHeaderTitle(qmltextUserManagement, UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT)
                    subtabtn.model = userMgmtTabBarModel
                    updateUserMgmtTabBar()
                    subtabBarBackground1.visible = true
                    addUserButton.visible = true
                    subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationUserList.qml"
                    ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT
                }
            }
            break;
        case enumTabBarIndex.userIOIdx:
            if(SystemConfiguration.UserIOSupportSystemType == SystemTypeDef.USER_IO_SUPPORTED  )
            {
                if (UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextTechnician ||
                        UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextSupervisor ||
                        UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextExecutive ||
                        mainWindow.isAuthorityCheckEnable)
                {
                    mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_USERIO)
                    mainWindow.setHeaderTitle(qmltextUserIO, UIScreenEnum.SYSTEM_CONFIG_USERIO)
                    subtabtn.model = userIOTabBarModel
                    updateUserIOTabBar()
                    addUserButton.visible = false
                    subtabBarBackground1.visible = true
                    subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/SystemConfigurationUserIO.qml"
                }
            }
            break;
        case enumTabBarIndex.indEthIOIdx:
            if(SystemConfiguration.FieldBusSupportSystemType !== SystemTypeDef.FIELDBUS_NOT_SUPPORTED )
            {
                if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable){
                    mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL)
                    mainWindow.setHeaderTitle(qmltextIndusEthIO, UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL)
                    subtabBarBackground1.visible = false
                    subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/SystemConfigurationIndusEthUserIO.qml"
                }
            }
            break;

        case enumTabBarIndex.ntwrkConfigIdx:
            if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable){
                mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION)
                mainWindow.setHeaderTitle(qmltextNtwrkConfig, UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION)
                subtabBarBackground1.visible = true
                subtabtn.model = ntwrkConfigTabBarModel
                updateNetWrkConfigTabBar()
                addUserButton.visible = false

               subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/NetWorkConfigIpSetUpTab.qml"
            }
            break;

        case enumTabBarIndex.usbAuthenticationIdx:
            {
                if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable)
                {
                    mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION)
                    mainWindow.setHeaderTitle(qmltextUSBAuthentication, UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION)
                    subtabBarBackground1.visible = true
                    subtabtn.model = usbAuthTabBarModel
                    updateUSBAuthTabBar()
                    addUserButton.visible = false
                    subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/USBAuthentication.qml"
                }
            }
            break;

        case enumTabBarIndex.usbRegistrationIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/USBAuthentication.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION
            break;

        case enumTabBarIndex.usbDeRegistrationIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/USBDeAuthentication.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USB_AUTHENTICATION
            break;

        case enumTabBarIndex.userNFSSetupIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/NetWorkConfigNFSSetup.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_NFS
            break;
        case enumTabBarIndex.userIpSetUpIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/NetWorkConfigIpSetUpTab.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION
            break;
        case enumTabBarIndex.userEipIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/NetWorkConfigEthernetIpTab.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_ETHERNETIP
            break;
        case enumTabBarIndex.userProfinetIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/NetWorkConfigProfinetTab.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_NETWORKCONFIGURATION_PROFINET
            break;


        case enumTabBarIndex.alarmManagementIdx:
            if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable)
            {
                mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT)
                mainWindow.setHeaderTitle(qmltextAlarmManagement, UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT)
                subtabBarBackground1.visible = false
                subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationAlarmMan.qml"
                ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_ALARMMANGEMENT
            }
            break;
        case enumTabBarIndex.ldapConfgIdx:
            if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable)
            {
                mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_LDAP_CONFIG)
                mainWindow.setHeaderTitle(qmltextLDAPConfg, UIScreenEnum.SYSTEM_CONFIG_LDAP_CONFIG)
                subtabBarBackground1.visible = false
                subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationLdapConfig.qml"
            }
            break;
        case enumTabBarIndex.gatewayDataIdx:
            if( UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive ||  mainWindow.isAuthorityCheckEnable){
                mainWindow.clearHeaderTitle(UIScreenEnum.SYSTEM_CONFIG_GATEWAY_DATA)
                mainWindow.setHeaderTitle(qmltextGatewayData, UIScreenEnum.SYSTEM_CONFIG_GATEWAY_DATA)
                subtabBarBackground1.visible = false
                subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationGatewayData.qml"
            }
            break;
        case enumTabBarIndex.userListIdx:
            subtabBarBackground1.visible = true
            addUserButton.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationUserList.qml"
            break;
        case enumTabBarIndex.globalUserSettingIdx:
            subtabBarBackground1.visible = true
            addUserButton.visible = false
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationGlobalUserSetting.qml"
            break;
        case enumTabBarIndex.userDigitalIOIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/SystemConfigurationUserIO.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO
            break;
        case enumTabBarIndex.userAnalogIOIdx:
            subtabBarBackground1.visible = true
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/SystemConfigurationUserIOAnalog.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO
            break;
        case enumTabBarIndex.bransonIdx:
            subtabBarBackground1.visible = false
            subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/BransonWindow.qml"
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.BRANSON_SYSTEM_CONFIGURATION
            break;
        default:
            break;
        }
    }

    function zoomingSize(inSize)
    {
        return Math.round(inSize * Style.scaleHint)
    }
    Connections {
        target: mainWindow
        function onSignalCurrentScreenChanged(index)
        {
            if(index === UIScreenEnum.SYSTEM_CONFIG)
            {
                subSystemConfigDetails.source = ""
                updateSystemConfigTabBar()
                subtabBarBackground1.visible = false
                subSystemConfigDetails.source = "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationGeneral.qml"
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
    Connections
    {
        target: mainWindow
        function onBransonKeyVerified()
        {
            updateSystemConfigTabBar()
        }
    }

    Connections
    {
        target: SystemGeneral
        function onKeyResetNotify()
        {
            mainWindow.bransonTabEnable = false
            updateSystemConfigTabBar()

        }
    }
    Connections
    {
        target: mainWindow
        function onBransonKeyReset()
        {
            mainWindow.bransonTabEnable = false
            updateSystemConfigTabBar()
        }
    }
    ListModel
    {
        id:ntwrkConfigTabBarModel
    }

    ListModel
    {
        id:userIOTabBarModel
    }

    ListModel
    {
        id:usbAuthTabBarModel
    }

    ListModel {
        id:userMgmtTabBarModel
    }
    function updateUserMgmtTabBar()
    {
        userMgmtTabBarModel.clear()
        userMgmtTabBarModel.append({"Title":      qmltextUserList,
                                       "Width":      Math.round(80 * Style.scaleHint),
                                       "Index":      enumTabBarIndex.userListIdx})
        userMgmtTabBarModel.append({"Title":      qmltextGlobalUserSetting,
                                       "Width":      Math.round(150 * Style.scaleHint),
                                       "Index":      enumTabBarIndex.globalUserSettingIdx})
    }

    function updateCurrentActiveTabBar()
    {
        var logedinUserLevel = UserPrivilegeObj.getLogedInUserLevel()

        if(mainWindow.isAuthorityCheckEnable)
        {
            mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
            ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
            updateTabBar(enumTabBarIndex.generalIdx)
        }

        switch (logedinUserLevel)
        {
           case mainWindow.qmltextOperator:             //For operator only General will be visible in case if Allowed but not other screens .
               if(UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed ||  mainWindow.isAuthorityCheckEnable){
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
                   updateTabBar(enumTabBarIndex.generalIdx)
               }
               break;
           case mainWindow.qmltextTechnician:         //SystemConfiguration is enabled for techcian then ENable "UserIO" Tab for "Technicain".
               if(UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed ||  mainWindow.isAuthorityCheckEnable )
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
                   updateTabBar(enumTabBarIndex.generalIdx)
               }
               else if(UserPrivilegeObj.IsSystemConfigurationAllowed)
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG_USERIO)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO
                   updateTabBar(enumTabBarIndex.userIOIdx)
               }
               else if(UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed || UserPrivilegeObj.IsSystemConfigurationAllowed ||  mainWindow.isAuthorityCheckEnable)
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
                   updateTabBar(enumTabBarIndex.generalIdx)
               }

               break;
           case mainWindow.qmltextSupervisor:       //Same as Technician
               if(UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed ||  mainWindow.isAuthorityCheckEnable)
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
                   updateTabBar(enumTabBarIndex.generalIdx)
               }
               else if(UserPrivilegeObj.IsSystemConfigurationAllowed ||  mainWindow.isAuthorityCheckEnable)
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG_USERIO)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG_USERIO
                   updateTabBar(enumTabBarIndex.userIOIdx)
               }
               else if(UserPrivilegeObj.IsBarcoderecipeRecallAllowed || UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed || UserPrivilegeObj.IsSystemConfigurationAllowed ||  mainWindow.isAuthorityCheckEnable)
               {
                   mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
                   ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
                   updateTabBar(enumTabBarIndex.generalIdx)
               }
               break;
           case mainWindow.qmltextExecutive:        //Will have access to all fields.
               mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM_CONFIG)
               ActiveScreen.CurrentActiveScreen = UIScreenEnum.SYSTEM_CONFIG
               updateTabBar(enumTabBarIndex.generalIdx)

               break;
           default:

        }

    }

    Component.onCompleted: {
    //To show User Management screen only if Password override dongle is connected.
        if(mainWindow.isPasswordRestDongleInserted)
        {
            systemConfigTabBarModel.append({"Title":      qmltextUserManagement,
                                               "Width":      Math.round(140 * Style.scaleHint),
                                               "Index":      enumTabBarIndex.userManagementIdx})
            updateTabBar(enumTabBarIndex.userManagementIdx)
        }
        else
        {
            updateSystemConfigTabBar()
            updateCurrentActiveTabBar()
        }
    }


    ListModel {
        id: systemConfigTabBarModel
    }

    Rectangle {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(47 * Style.scaleHint)
        color:Style.backgroundColor
        TabBar {
            id: configurationTabBar
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            spacing: 1
            background: Rectangle{
                color: Style.backgroundColor
            }

            Repeater {
                id: tabbtn
                model: systemConfigTabBarModel
                delegate: BransonTabButton {
                    width: model.Width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked: {
                        updateTabBar(model.Index)
                    }
                }
            }
        }
    }

    Rectangle {
        id: subtabBarBackground1
        anchors.left: parent.left
        anchors.top: tabBarBackground.bottom
        width: parent.width
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        visible: false
        TabBar
        {
            id: subSystemTabBar
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(600 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            spacing: 20
            background: Rectangle
            {
                color: Style.backgroundColor
            }

            Repeater
            {
                id: subtabtn
                delegate: BransonTabButton
                {
                    width: model.Width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked: {
                        updateTabBar(model.Index)
                    }
                }
            }
        }
        BransonPrimaryButton{
            id:addUserButton
            height: Math.round(30 * Style.scaleHint)
            width: Math.round(120 * Style.scaleHint)
            anchors.right: parent.right
            anchors.rightMargin: Math.round(60 * Style.scaleHint)
            text: qmltextAddUser
            textColor: Style.buttonTextColor
            font.family: Style.regular.name
            buttonColor : UserPrivilegeObj.IsAddModifyUserIDSetupAllowed || mainWindow.isPasswordRestDongleInserted ?  "#17345C" : "#9b9e9c"
            onClicked: {
                if(UserPrivilegeObj.IsAddModifyUserIDSetupAllowed || mainWindow.isPasswordRestDongleInserted)
                {
                    mainWindow.isUserModifing = false
                    mainWindow.showUserMgmtAddUserScreen("","Operator","Enable",0)
                }
            }
        }
    }

    Loader {
        id: subSystemConfigDetails
        anchors.top: tabBarBackground.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right:parent.left
        source: mainWindow.isPasswordRestDongleInserted ? "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationUserList.qml" : "qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationGeneral.qml"
    }
}


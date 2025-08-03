cmake_minimum_required(VERSION 3.14)

project(QT_UIController VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt6 REQUIRED COMPONENTS Charts)

include_directories(../../../_Branson_User_Common/Infrastructure/BIOWrapper)
include_directories(../../../_Branson_User_Common/Infrastructure/COMM_Class)
include_directories(../../../_Branson_User_Common/Infrastructure/Logger)
include_directories(../../../_Branson_User_Common/Infrastructure/DataInterface_Common)
include_directories(../../../_Branson_User_Common/Infrastructure/EncryptionDecryption)
include_directories(../../../_Branson_User_Common/Infrastructure/PlatformConfigLogic)
include_directories(../../../_Branson_User_Common/Commons)
include_directories(../../../_Branson_User_Common/Platform/ACE/Logic/Common)
include_directories(../../../_Branson_User_Common/Platform/ACE/Infra/DataInterfaceCommon)
include_directories(../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig)
include_directories(../../../_Branson_User_Common/Platform/ACE/Infra/AlarmManager)
include_directories(../../../_Branson_User_Common/Infrastructure/DataLogger)

include_directories(Core/Infra/COMM_Thread)
include_directories(Core/Infra/BgCommThread)
include_directories(Core/Infra/AlarmManager)

include_directories(Core/Infra/BIOWrapper)
include_directories(Core/Infra/DataInterface)
include_directories(Core/Infra/PlatformConfigLogic)
include_directories(Core/Infra/USBAuthentication)
include_directories(Platform/ACE/Logic/Common)
include_directories(Core/Infra/WDSServer)
include_directories(Core/Logic/Back_End_Logic/Common_Logic)
include_directories(Core/Logic/Back_End_Logic/Language_Update_Logic)
include_directories(Core/Logic/Back_End_Logic/Login_Screens)
include_directories(Core/Logic/Back_End_Logic/Production_Screens)
include_directories(Core/Logic/Back_End_Logic/Recipe_Screens)
include_directories(Core/Logic/Back_End_Logic/Analytics_Screens)
include_directories(Core/Logic/Back_End_Logic/Multi_Welder)
include_directories(Core/Logic/Back_End_Logic/PlatformConfig)
include_directories(Core/Logic/Back_End_Logic/Platform_Config_Upgrade)
include_directories(Core/Logic/Back_End_Logic/Diagnostics_Screens)
include_directories(Core/Logic/Back_End_Logic/Alarm_Screens)
include_directories(Core/Logic/Back_End_Logic/Actuator_Setup_Screens)
include_directories(Core/Logic/Back_End_Logic/Date_Time_Settings_Screens)
include_directories(Core/Logic/SC)
include_directories(Core/Logic/Common)
include_directories(Platform/ACE/Infra/BIOWrapper)
include_directories(Platform/ACE/Logic/Common)
include_directories(Platform/ACE/Infra/DataInterfaceCommon)
include_directories(Platform/ACE/Infra/PlatformConfig)
include_directories(Platform/ACE/Infra/ConfigUpgradeCommands)
include_directories(Platform/ACE/Infra/AlarmManager)
include_directories(Platform/ACE/Infra/USBStreaming)
include_directories(Platform/ACE/Infra/Profinet)
include_directories(Platform/ACE/Infra/USBConfigurationManagement)

include_directories(Core/Infra/Logger)
include_directories(Core/Logic/Back_End_Logic/System_Screens)
include_directories(Core/Logic/Back_End_Logic/Generate_Report_Screens)
set(PROJECT_SOURCES
        main.cpp
        qml.qrc

        Core/Logic/Back_End_Logic/Common_Logic/uiscreendef.h
        Core/Logic/Back_End_Logic/Common_Logic/UpdateScreens.h
        Core/Logic/Back_End_Logic/Common_Logic/UpdateScreens.cpp
        Core/Logic/Back_End_Logic/Common_Logic/ActiveScreen.h
        Core/Logic/Back_End_Logic/Common_Logic/ActiveScreen.cpp
        Core/Logic/Back_End_Logic/Common_Logic/SystemTypeDef.h
        Core/Logic/Back_End_Logic/Common_Logic/SystemConfiguration.h
        Core/Logic/Back_End_Logic/Common_Logic/SystemConfiguration.cpp
        Core/Logic/Back_End_Logic/Common_Logic/DataLoggerLogic.h
        Core/Logic/Back_End_Logic/Common_Logic/DataLoggerLogic.cpp
        Core/Logic/Back_End_Logic/Common_Logic/UnitConversionLogic.h
        Core/Logic/Back_End_Logic/Common_Logic/UnitConversionLogic.cpp

        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreeitem.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreeitemhash.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreemodel.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/languageconfig.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/languagedef.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/languageitem.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/languagemodel.h
        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreeitem.cpp
        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreeitemhash.cpp
        Core/Logic/Back_End_Logic/Language_Update_Logic/jsontreemodel.cpp
        Core/Logic/Back_End_Logic/Language_Update_Logic/languageconfig.cpp
        Core/Logic/Back_End_Logic/Language_Update_Logic/languageitem.cpp
        Core/Logic/Back_End_Logic/Language_Update_Logic/languagemodel.cpp
        Core/Logic/Back_End_Logic/Common_Logic/SystemInformationInterface.h
        Core/Logic/Back_End_Logic/Common_Logic/SystemInformationInterface.cpp
        Core/Logic/Back_End_Logic/Common_Logic/DisplayModesHMI.h
        Core/Logic/Back_End_Logic/Common_Logic/DisplayModesHMI.cpp

        Core/Logic/Back_End_Logic/Login_Screens/logindef.h
        Core/Logic/Back_End_Logic/Login_Screens/login.h
        Core/Logic/Back_End_Logic/Login_Screens/login.cpp

        Core/Logic/Back_End_Logic/Login_Screens/UserPrivilege.h
        Core/Logic/Back_End_Logic/Login_Screens/UserPrivilege.cpp

        Core/Logic/Back_End_Logic/Production_Screens/ProductionRunInterface.h
        Core/Logic/Back_End_Logic/Production_Screens/ProductionRunInterface.cpp

        Core/Logic/Back_End_Logic/Recipe_Screens/recipedef.h
        Core/Logic/Back_End_Logic/Recipe_Screens/recipegeneral.h
        Core/Logic/Back_End_Logic/Recipe_Screens/recipemodel.h
        Core/Logic/Back_End_Logic/Recipe_Screens/RecipeLabData.h
        Core/Logic/Back_End_Logic/Recipe_Screens/recipegeneral.cpp
        Core/Logic/Back_End_Logic/Recipe_Screens/recipemodel.cpp
        Core/Logic/Back_End_Logic/Recipe_Screens/RecipeLabData.cpp
        Core/Logic/Back_End_Logic/Recipe_Screens/ResultViewTableProxyModel.h
        Core/Logic/Back_End_Logic/Recipe_Screens/ResultViewTableProxyModel.cpp
        Core/Logic/Back_End_Logic/Recipe_Screens/ResultViewWeldProxyModel.h
        Core/Logic/Back_End_Logic/Recipe_Screens/ResultViewWeldProxyModel.cpp

        Core/Logic/Back_End_Logic/Analytics_Screens/GraphAxisDef.h
        Core/Logic/Back_End_Logic/Analytics_Screens/WeldGraphData.h
        Core/Logic/Back_End_Logic/Analytics_Screens/WeldGraphData.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailsListModel.h
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailsListData.h
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailsListData.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/GraphSettings.h
        Core/Logic/Back_End_Logic/Analytics_Screens/GraphSettings.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailTableModel.h
        Core/Logic/Back_End_Logic/Analytics_Screens/CycleDetailTableModel.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/AnalyticTableListData.h
        Core/Logic/Back_End_Logic/Analytics_Screens/AnalyticTableListData.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/ReferenceWeldGraphData.h
        Core/Logic/Back_End_Logic/Analytics_Screens/ReferenceWeldGraphData.cpp
        Core/Logic/Back_End_Logic/Analytics_Screens/AnalyticsScreenTableViewOptions.h
        Core/Logic/Back_End_Logic/Analytics_Screens/AnalyticsScreenTableViewOptions.cpp

        Core/Logic/Back_End_Logic/Multi_Welder/MultiwelderInterface.h
        Core/Logic/Back_End_Logic/Multi_Welder/MultiwelderInterface.cpp

        Core/Logic/Back_End_Logic/PlatformConfig/ConfigStatus.h
        Core/Logic/Back_End_Logic/PlatformConfig/ConfigStatus.cpp
        Core/Logic/Back_End_Logic/Platform_Config_Upgrade/PlatformConfigUpgrade.h
        Core/Logic/Back_End_Logic/Platform_Config_Upgrade/PlatformConfigUpgrade.cpp

        Core/Logic/Back_End_Logic/System_Screens/SystemGeneral.h
        Core/Logic/Back_End_Logic/System_Screens/SystemGeneral.cpp
        Core/Logic/Back_End_Logic/System_Screens/AlarmManConfiguration.h
        Core/Logic/Back_End_Logic/System_Screens/AlarmManConfiguration.cpp
        Core/Logic/Back_End_Logic/System_Screens/ServiceCountListData.h
        Core/Logic/Back_End_Logic/System_Screens/ServiceCountListData.cpp
        Core/Logic/Back_End_Logic/System_Screens/ServiceCountListModel.h
        Core/Logic/Back_End_Logic/System_Screens/ServiceCountListModel.cpp

        Core/Logic/Back_End_Logic/System_Screens/UserIODigital.h
        Core/Logic/Back_End_Logic/System_Screens/UserIODigital.cpp
        Core/Logic/Back_End_Logic/System_Screens/IdleTimeLogout.h
        Core/Logic/Back_End_Logic/System_Screens/IdleTimeLogout.cpp
        Core/Logic/Back_End_Logic/System_Screens/UserIOAnalog.h
        Core/Logic/Back_End_Logic/System_Screens/UserIOAnalog.cpp
        Core/Logic/Back_End_Logic/System_Screens/IndustrialEthernetIO.h
        Core/Logic/Back_End_Logic/System_Screens/IndustrialEthernetIO.cpp
        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationNFSSetup.h
        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationNFSSetup.cpp

        Core/Logic/Back_End_Logic/System_Screens/UserListDetailsListModel.h
        Core/Logic/Back_End_Logic/System_Screens/UserListDetailsListModel.cpp
        Core/Logic/Back_End_Logic/System_Screens/UserListDetailsListData.h
        Core/Logic/Back_End_Logic/System_Screens/UserListDetailsListData.cpp
        Core/Logic/Back_End_Logic/System_Screens/UsbAuthDetailsListData.cpp
        Core/Logic/Back_End_Logic/System_Screens/UsbAuthDetailsListData.h
        Core/Logic/Back_End_Logic/System_Screens/UsbAuthDetailsListModel.h
        Core/Logic/Back_End_Logic/System_Screens/UsbAuthDetailsListModel.cpp
        Core/Logic/Back_End_Logic/System_Screens/BransonSystemConfiguration.h
        Core/Logic/Back_End_Logic/System_Screens/BransonSystemConfiguration.cpp

        Core/Logic/Back_End_Logic/System_Screens/CalibrateActuator.h
        Core/Logic/Back_End_Logic/System_Screens/CalibrateActuator.cpp
        Core/Logic/Back_End_Logic/System_Screens/CalibrateForce.h
        Core/Logic/Back_End_Logic/System_Screens/CalibrateForce.cpp
        Core/Logic/Back_End_Logic/System_Screens/CalibratePressure.h
        Core/Logic/Back_End_Logic/System_Screens/CalibratePressure.cpp
        Core/Logic/Back_End_Logic/System_Screens/CalibrateQuick.h
        Core/Logic/Back_End_Logic/System_Screens/CalibrateQuick.cpp
        Core/Logic/Back_End_Logic/System_Screens/CalibrateResetSensors.h
        Core/Logic/Back_End_Logic/System_Screens/CalibrateResetSensors.cpp

        Core/Logic/Back_End_Logic/Diagnostics_Screens/Test.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/Test.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/TestGraphData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/TestGraphData.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/TestGraphSettings.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/TestGraphSettings.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/Seek.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/Seek.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/SeekGraphData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/SeekGraphData.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/SeekGraphSettings.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/SeekGraphSettings.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanGraphData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanGraphData.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanCycleDetailsListModel.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanCycleDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanCycleDetailsListData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanCycleDetailsListData.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanGraphSettings.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/ScanGraphSettings.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/EventLogDetailsListModel.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/EventLogDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/EventLogListData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/EventLogListData.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/AlarmDetailsListModel.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/AlarmDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Diagnostics_Screens/AlarmDetailsListData.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/AlarmDetailsListData.cpp

        Core/Logic/Back_End_Logic/Diagnostics_Screens/DiagnosticUserIo.h
        Core/Logic/Back_End_Logic/Diagnostics_Screens/DiagnosticUserIo.cpp

        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveAlarmDetailsListModel.h
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveAlarmDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveAlarmDetailsListData.h
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveAlarmDetailsListData.cpp

        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveServiceReminderDetailsListModel.h
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveServiceReminderDetailsListModel.cpp
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveServiceReminderDetailsListData.h
        Core/Logic/Back_End_Logic/Alarm_Screens/ActiveServiceReminderDetailsListData.cpp

        Core/Logic/Back_End_Logic/System_Screens/SystemConfGlobalUserSetting.cpp
        Core/Logic/Back_End_Logic/System_Screens/SystemConfGlobalUserSetting.h
        Core/Logic/Back_End_Logic/System_Screens/BransonServiceInterface.cpp
        Core/Logic/Back_End_Logic/System_Screens/BransonServiceInterface.h


        Core/Logic/Back_End_Logic/Actuator_Setup_Screens/ActuatorSetupData.cpp
        Core/Logic/Back_End_Logic/Actuator_Setup_Screens/ActuatorSetupData.h

        Core/Logic/Back_End_Logic/Date_Time_Settings_Screens/DateTimeSettings.h
        Core/Logic/Back_End_Logic/Date_Time_Settings_Screens/DateTimeSettings.cpp

        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfiguration.cpp
        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfiguration.h

        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationEthIp.cpp
        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationEthIp.h

        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationProfinet.cpp
        Core/Logic/Back_End_Logic/System_Screens/SystemNetworkConfigurationProfinet.h

        Core/Logic/Back_End_Logic/System_Screens/SoftwareUpgradeInterface.cpp
        Core/Logic/Back_End_Logic/System_Screens/SoftwareUpgradeInterface.h

        Core/Logic/Back_End_Logic/Generate_Report_Screens/GenerateReportComman.h
        Core/Logic/Back_End_Logic/Generate_Report_Screens/GenerateReportComman.cpp

        Core/Logic/Back_End_Logic/Generate_Report_Screens/DataFilterListModel.h
        Core/Logic/Back_End_Logic/Generate_Report_Screens/DataFilterListModel.cpp
		Core/Logic/Back_End_Logic/System_Screens/SystemFeature.h
        Core/Logic/Back_End_Logic/System_Screens/SystemFeature.cpp

        ../../../_Branson_User_Common/Infrastructure/BIOWrapper/BIOWrapper.h
        ../../../_Branson_User_Common/Infrastructure/BIOWrapper/BIOWrapper.cpp
        ../../../_Branson_User_Common/Infrastructure/BIOWrapper/BIOWrapperCommon.h
        ../../../_Branson_User_Common/Infrastructure/BIOWrapper/BIOWrapperInternal.h
        ../../../_Branson_User_Common/Infrastructure/COMM_Class/Comm.h
        ../../../_Branson_User_Common/Infrastructure/COMM_Class/Comm.cpp
        ../../../_Branson_User_Common/Infrastructure/COMM_Class/CommDataConfig.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/DataInterfaceCommon/CommStatAce.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/DataInterfaceCommon/CommStatAce.cpp
        ../../../_Branson_User_Common/Infrastructure/DataInterface_Common/DataInterface.h
        ../../../_Branson_User_Common/Infrastructure/DataInterface_Common/DataInterface_id.h
        ../../../_Branson_User_Common/Infrastructure/DataInterface_Common/ProductionScreen_MB.h
        ../../../_Branson_User_Common/Infrastructure/EncryptionDecryption/EncryptDecryptData.cpp
        ../../../_Branson_User_Common/Infrastructure/EncryptionDecryption/EncryptDecryptData.h
        ../../../_Branson_User_Common/Infrastructure/PlatformConfigLogic/PlatformConfigInterface.h
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/WeldRecipeStructuresAce.h
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/WeldRecipeStructuresAce.cpp
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/ActuatorSetupStructureAce.h
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/SysConfgGenStructureAce.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/DataInterfaceCommon/CommStatAce.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/DataInterfaceCommon/CommStatAce.cpp
				
        ../../../_Branson_User_Common/Platform/ACE/Infra/AlarmManager/AlarmNames.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/AlarmManager/AlarmNames.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/AlarmManager/AlarmNamesParam.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/ActuatorInit.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/AmplitudeAndPressureStepsSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/AmplitudeAndPressureStepsSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PowerSupplyType.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PowerSupplyType.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PowerLevelSysFrequencySupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PowerLevelSysFrequencySupport.cpp		
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/FieldbusSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/FieldbusSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/StorageSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/StorageSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/EventLogSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/EventLogSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BatchControlSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BatchControlSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/LDAPSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/LDAPSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/UserAccessLevelSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/UserAccessLevelSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BarcodeScannerSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BarcodeScannerSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/UserIOSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/UserIOSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PCUtilitySupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/PCUtilitySupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/CylinderSizeSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/CylinderSizeSupport.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/StrokeLength.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/StrokeLength.cpp
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/HMIDeviceSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BearingTypeSupport.h
        ../../../_Branson_User_Common/Platform/ACE/Infra/PlatformConfig/BearingTypeSupport.cpp

        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/DgtUserIOStructureAce.h
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/DisplayMgrStructureAce.h
        ../../../_Branson_User_Common/Platform/ACE/Logic/Common/FbUserIOStructureAce.h

        ../../../_Branson_User_Common/Commons/Common_Definitions.h
        ../../../_Branson_User_Common/Commons/SeekRecipeStructure.h
        ../../../_Branson_User_Common/Commons/SeekRecipeStructure.cpp
        ../../../_Branson_User_Common/Commons/HornScanRecipeStructure.h
        ../../../_Branson_User_Common/Commons/HornScanRecipeStructure.cpp
        ../../../_Branson_User_Common/Commons/WeldRecipe.h
        ../../../_Branson_User_Common/Commons/TestRecipeStructure.h
        ../../../_Branson_User_Common/Commons/TestRecipeStructure.cpp
        ../../../_Branson_User_Common/Commons/TestResultStructure.h
        ../../../_Branson_User_Common/Commons/TestSignatureStructure.h
        ../../../_Branson_User_Common/Commons/SeekSignatureStructure.h
        ../../../_Branson_User_Common/Commons/UserManagementStructure.h
        ../../../_Branson_User_Common/Commons/GlobalUserSettingStructure.h
        ../../../_Branson_User_Common/Commons/UnitConversion.h
        ../../../_Branson_User_Common/Commons/UnitConversion.cpp
        ../../../_Branson_User_Common/Commons/ServiceReminderStructure.h
        ../../../_Branson_User_Common/Commons/DateTime_Definations.h
        ../../../_Branson_User_Common/Commons/version_common.h
	    ../../../_Branson_User_Common/Commons/HMI_ASC_comms.h
        ../../../_Branson_User_Common/Commons/ProfinetStructure.h
        ../../../_Branson_User_Common/Commons/USBAuthenticationStructure.h
        ../../../_Branson_User_Common/Commons/CommonMapDefinitions.cpp
        ../../../_Branson_User_Common/Commons/ImportExportStructure.h
        

        ../../../_Branson_User_Common/Infrastructure/DataLogger/LoggerCommon.h
        ../../../_Branson_User_Common/Infrastructure/DataLogger/LoggerInterface.h
        ../../../_Branson_User_Common/Infrastructure/DataLogger/LoggerInterface.cpp
        ../../../_Branson_User_Common/Infrastructure/DataLogger/DataLogger.h
        ../../../_Branson_User_Common/Infrastructure/DataLogger/DataLogger.cpp
        ../../../_Branson_User_Common/Infrastructure/DataLogger/EventLogStructure.h
        ../../../_Branson_User_Common/Infrastructure/DataLogger/AlarmLogStructure.h
        ../../../_Branson_User_Common/Commons/USBAuthenticationStructure.h
        ../../../_Branson_User_Common/Commons/CommonMapDefinitions.cpp

        Core/Infra/BIOWrapper/BIOConfig.h
        Core/Infra/BIOWrapper/BIOConfig.cpp
        Core/Infra/COMM_Thread/CommPeerWrapper.cpp
        Core/Infra/COMM_Thread/CommPeerWrapper.h
        Core/Infra/COMM_Thread/CommThread.cpp
        Core/Infra/COMM_Thread/CommThread.h
        Core/Infra/COMM_Thread/CommCyclicActivity.cpp
        Core/Infra/COMM_Thread/CommCyclicActivity.h
        Core/Infra/COMM_Thread/CommPeerInfo.cpp
        Core/Infra/COMM_Thread/CommPeerInfo.h
        Core/Infra/DataInterface/DataInterfaceConfig_HMI.h
        Core/Infra/DataInterface/DataInterfaceConfig_HMI.cpp
        Core/Infra/DataInterface/BgDataInterfaceConfig_HMI.h
        Core/Infra/DataInterface/BgDataInterfaceConfig_HMI.cpp
        Core/Infra/DataInterface/ProductionScreen_MB.cpp
        Core/Infra/DataInterface/PlatformConfig.cpp
        Core/Infra/DataInterface/PlatformConfig.h        
        Core/Infra/WDSServer/WDSServer.h
        Core/Infra/WDSServer/WDSServer.cpp
        Core/Infra/BgCommThread/BgCommThread.h
        Core/Infra/BgCommThread/BgCommThread.cpp

        Core/Infra/Logger/SysLogger.h
        Core/Infra/Logger/SysLogger.cpp
        Core/Infra/Logger/SerialLogger.h
        Core/Infra/Logger/SerialLogger.cpp
        Core/Infra/Logger/DBLogger.h
        Core/Infra/Logger/DBLogger.cpp
        Core/Infra/Logger/LoggerTable.h
        Core/Infra/Logger/EventLog.cpp
        Core/Infra/Logger/EventLog.h
        Core/Infra/Logger/AlarmLog.cpp
        Core/Infra/Logger/AlarmLog.h
        Core/Infra/Logger/ActiveAlarm.h
        Core/Infra/Logger/ActiveAlarm.cpp
        Core/Infra/Logger/AlarmConfig.h
        Core/Infra/Logger/AlarmConfig.cpp
        Core/Infra/Logger/DataLoggerManager.cpp
        Core/Infra/Logger/DataLoggerManager.h
        Core/Infra/AlarmManager/AlarmManager.cpp
        Core/Infra/AlarmManager/AlarmManager.h
        Core/Infra/USBAuthentication/USBAuthentication.cpp
        Core/Infra/USBAuthentication/USBAuthentication.h

        Platform/ACE/Infra/BIOWrapper/BIOConfig_Ace.h
        Platform/ACE/Infra/BIOWrapper/BIOConfigUpgrade.h
        Platform/ACE/Infra/BIOWrapper/BIOConfig_BgCommAce.h
        Platform/ACE/Infra/PlatformConfig/ActuatorInit.cpp
        Platform/ACE/Infra/PlatformConfig/HMIDeviceSupport.cpp

        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigUpgradeCmdInterface.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigCommandsTable.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigStartUSBUpgrade.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigStartUSBUpgrade.cpp
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigReadVersionUSB.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigReadVersionUSB.cpp
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigPerformUpgradeUSB.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigPerformUpgradeUSB.cpp
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigStartEthernetUpgrade.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigStartEthernetUpgrade.cpp
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigReadVersionEthernet.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigReadVersionEthernet.cpp
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigPerformUpgradeEthernet.h
        Platform/ACE/Infra/ConfigUpgradeCommands/ConfigPerformUpgradeEthernet.cpp
        Platform/ACE/Infra/AlarmManager/AlarmManagerAce.h
        Platform/ACE/Infra/AlarmManager/AlarmManagerAce.cpp
        Platform/ACE/Infra/USBStreaming/USBStreaming.h
        Platform/ACE/Infra/USBStreaming/USBStreaming.cpp
        Platform/ACE/Infra/Profinet/ProfinetSetting.h
        Platform/ACE/Infra/Profinet/ProfinetSetting.cpp
        Platform/ACE/Infra/USBConfigurationManagement/ImportExport.h
        Platform/ACE/Infra/USBConfigurationManagement/ImportExport.cpp        

        Platform/ACE/Logic/Common/AcePlatformInit.h
        Platform/ACE/Logic/Common/AcePlatformInit.cpp
        Platform/ACE/Logic/Common/WeldRecipeAce.h
        Platform/ACE/Logic/Common/WeldRecipeAce.cpp
        Platform/ACE/Logic/Common/WeldResultAce.h
        Platform/ACE/Logic/Common/WeldResultAce.cpp
        Platform/ACE/Logic/Common/WeldResultAce.h
        Platform/ACE/Logic/Common/WeldResultAce.cpp
        Platform/ACE/Logic/Common/WeldSignatureAce.h
        Platform/ACE/Logic/Common/WeldSignatureAce.cpp
        Platform/ACE/Logic/Common/SystemConfigurationGeneral_MB.h
        Platform/ACE/Logic/Common/SystemConfigurationGeneral_MB.cpp
        Platform/ACE/Logic/Common/ActuatorSetupAce.h
        Platform/ACE/Logic/Common/ActuatorSetupAce.cpp
        Platform/ACE/Logic/Common/IOManager.h
        Platform/ACE/Logic/Common/IOManager.cpp
        Platform/ACE/Logic/Common/DisplayManager.h
        Platform/ACE/Logic/Common/DisplayManager.cpp
        Platform/ACE/Logic/Common/ReferenceWeldSignatureAce.h
        Platform/ACE/Logic/Common/ReferenceWeldSignatureAce.cpp
        Platform/ACE/Logic/Common/CalibrationAce.h
        Platform/ACE/Logic/Common/CalibrationAce.cpp
        Platform/ACE/Logic/Common/FieldBusIOManager.h
        Platform/ACE/Logic/Common/FieldBusIOManager.cpp

        Core/Logic/SC/SeekRecipe.h
        Core/Logic/SC/SeekRecipe.cpp
        Core/Logic/SC/TestRecipe.h
        Core/Logic/SC/TestRecipe.cpp
        Core/Logic/SC/HornScanRecipe.h
        Core/Logic/SC/HornScanRecipe.cpp
        Core/Logic/SC/TestSignature.h
        Core/Logic/SC/TestSignature.cpp
        Core/Logic/SC/SeekSignature.h
        Core/Logic/SC/SeekSignature.cpp
        Core/Logic/Common/SystemType.h
        Core/Logic/Common/SystemType.cpp
        Core/Logic/SC/SeekResult.cpp
        Core/Logic/SC/SeekResult.h
        Core/Logic/SC/SeekSignature.cpp
        Core/Logic/SC/SeekSignature.h
        Core/Logic/SC/TestResult.h
        Core/Logic/SC/TestResult.cpp
        Core/Logic/SC/HornScanSignature.h
        Core/Logic/SC/HornScanSignature.cpp
        Core/Logic/SC/HornScanResult.h
        Core/Logic/SC/HornScanResult.cpp
        Core/Logic/SC/UserManagement.h
        Core/Logic/SC/UserManagement.cpp
        Core/Logic/SC/GlobalUserSetting.h
        Core/Logic/SC/GlobalUserSetting.cpp
        Core/Logic/SC/ServiceReminderManagement.h
        Core/Logic/SC/ServiceReminderManagement.cpp
        Core/Logic/SC/SystemConfigBransonService.cpp
        Core/Logic/SC/SystemConfigBransonService.h
        Core/Logic/SC/SystemInformation.cpp
        Core/Logic/SC/SystemInformation.h        
        Core/Logic/SC/NetworkConfiguration.cpp
        Core/Logic/SC/NetworkConfiguration.h
        Core/Logic/SC/BransonServiceTab.cpp
        Core/Logic/SC/BransonServiceTab.h
        Core/Logic/SC/SoftwareUpgrade.cpp
        Core/Logic/SC/SoftwareUpgrade.h
        Core/Logic/SC/DateTimeConversion.cpp
        Core/Logic/SC/DateTimeConversion.h
        Core/Logic/SC/ReportManager.cpp
        Core/Logic/SC/ReportManager.h
        Core/Logic/SC/NetworkConfigurationEthernetIp.h
        Core/Logic/SC/NetworkConfigurationEthernetIp.cpp
        Core/Logic/SC/ConfigUtilityVersion.cpp
        Core/Logic/SC/ConfigUtilityVersion.h
        Core/Logic/SC/NfsManager.cpp
        Core/Logic/SC/NfsManager.h
        Core/Logic/SC/OpcuaClientCertificateUpload.h
        Core/Logic/SC/OpcuaClientCertificateUpload.cpp

        Images.qrc
        Data/VirtualKeyboard.qrc
        Fonts.qrc
        Jsonfile.qrc
        Misc.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_UIController
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QT_UIController APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT_UIController SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT_UIController
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT_UIController
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick -lrt

  # For Desktop Kit
      /usr/lib/x86_64-linux-gnu/libssl.a
      /usr/lib/x86_64-linux-gnu/libcrypto.a ${CMAKE_DL_LIBS})

  # For Ras-Pi Kit
#    /media/kshitij/Computer2/GSX-ACE_PRO_Build_Env_Qt-6.2.7/rpi-sysroot/usr/lib/aarch64-linux-gnu/libssl.a
#    /media/kshitij/Computer2/GSX-ACE_PRO_Build_Env_Qt-6.2.7/rpi-sysroot/usr/lib/aarch64-linux-gnu/libcrypto.a ${CMAKE_DL_LIBS})

  #For TI Kit
#/media/kshitij/Computer2/QT6_RENU/SSLLibs/libssl.a
#/media/kshitij/Computer2/QT6_RENU/SSLLibs/libcrypto.a ${CMAKE_DL_LIBS})

target_link_libraries(QT_UIController PRIVATE Qt6::Charts)
set_target_properties(QT_UIController PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QT_UIController
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(QT_UIController)
    qt_finalize_executable(QT_UIController)
endif()

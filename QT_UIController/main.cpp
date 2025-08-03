/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QMutex>
#include <QObject>

#include "uiscreendef.h"
#include "languagedef.h"
#include "logindef.h"
#include "languageconfig.h"
#include "recipemodel.h"
#include "recipedef.h"
#include "login.h"
#include "ActiveScreen.h"
#include "UpdateScreens.h"
#include "ProductionRunInterface.h"

#include "WDSServer.h"
#include "CommThread.h"
#include "CommCyclicActivity.h"
#include "MultiwelderInterface.h"
#include "ConfigStatus.h"
#include "AcePlatformInit.h"
#include "PlatformConfigUpgrade.h"

#include "UpdateScreens.h"
#include "ActiveScreen.h"
#include "RecipeLabData.h"
#include "SystemTypeDef.h"
#include "SystemConfiguration.h"
#include "SystemInformationInterface.h"
#include "SystemGeneral.h"
#include "GraphAxisDef.h"
#include "WeldGraphData.h"

#include "CycleDetailsListModel.h"
#include "GraphSettings.h"

#include "Test.h"
#include "TestGraphData.h"
#include "TestGraphSettings.h"
#include "Seek.h"
#include "SeekGraphData.h"
#include "SeekGraphSettings.h"
#include "ScanGraphData.h"
#include "ScanCycleDetailsListModel.h"
#include "ScanGraphSettings.h"
#include "CycleDetailTableModel.h"
#include "EventLogDetailsListModel.h"
#include "AlarmDetailsListModel.h"
#include "ActiveAlarmDetailsListModel.h"
#include "AlarmManConfiguration.h"
#include "UserIODigital.h"
#include "UserListDetailsListModel.h"
#include "SystemConfGlobalUserSetting.h"
#include "ActuatorSetupData.h"
#include "UnitConversionLogic.h"
#include "UserPrivilege.h"
#include "DiagnosticUserIo.h"
#include "DataLoggerLogic.h"
#include "IdleTimeLogout.h"
#include "BransonSystemConfiguration.h"

#include "ServiceCountListModel.h"
#include "ActiveServiceReminderDetailsListModel.h"

#include "CalibrateActuator.h"
#include "CalibrateForce.h"
#include "CalibratePressure.h"
#include "CalibrateQuick.h"
#include "CalibrateResetSensors.h"
#include "ReferenceWeldGraphData.h"
#include "DateTimeSettings.h"
#include "BransonServiceInterface.h"
#include "SystemNetworkConfiguration.h"
#include "SoftwareUpgradeInterface.h"
#include "DisplayModesHMI.h"
#include "AnalyticsScreenTableViewOptions.h"
#include "ResultViewTableProxyModel.h"
#include "ResultViewWeldProxyModel.h"
#include "UserIOAnalog.h"
#include "IndustrialEthernetIO.h"
#include "GenerateReportComman.h"
#include "DataFilterListModel.h"
#include "SystemFeature.h"
#include "SystemNetworkConfigurationEthIp.h"
#include "SystemNetworkConfigurationProfinet.h"
#include "SystemNetworkConfigurationNFSSetup.h"
#include "UsbAuthDetailsListModel.h"

#include "DashBoardWelderListModel.h"

QQmlContext *pQmlContext;

#include "CommPeerWrapper.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

     QApplication app(argc, argv);

    QString osName = QSysInfo::prettyProductName();

    LanguageConfig::getInstance()->checkLanguageFiles();

    qmlRegisterSingletonType(QUrl("qrc:/Core/Logic/Front_End_Logic/Common_Logic/BransonStyle.qml"), "Style", 1, 0, "Style");
    qmlRegisterSingletonType(QUrl("qrc:/Core/Logic/Front_End_Logic/Common_Logic/BransonNumpadDefine.qml"), "NumpadDefine", 1, 0, "NumpadDefine");
    qmlRegisterSingletonType(QUrl("qrc:/Core/Logic/Front_End_Logic/Common_Logic/BransonChartViewAxisDefine.qml"), "AxisDefine", 1, 0, "AxisDefine");
    UIScreenEnum::registerQMLType();
    RecipeEnum::registerQMLType();
    LoginIndexEnum::registerQMLType();
    LanguageEnum::registerQMLType();
    SystemTypeDef::registerQMLType();
    GraphAxisEnum::registerQMLType();

    QQmlApplicationEngine engine;
    engine.addImportPath(":/VirtualKeyboardStyles");
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "styleVirtualKeyboard");
    pQmlContext = engine.rootContext();
#ifdef QT_DEBUG
    pQmlContext->setContextProperty("debug", true);
#else
    pQmlContext->setContextProperty("debug", false);
#endif

    /*Check for platform on which HMI being operating*/
    if(osName == "Debian GNU/Linux 11 (bullseye)")
    {
        pQmlContext->setContextProperty("isRaspPI", true);
    }

    else
    {
        pQmlContext->setContextProperty("isRaspPI", false);
    }

    pQmlContext->setContextProperty("LanguageConfig", LanguageConfig::getInstance());
    pQmlContext->setContextProperty("LanguageModel", LanguageConfig::getInstance()->getLanguageModelInstance());
    ProductionRun m_ProductionRunObj;
    pQmlContext->setContextProperty("ProductionRunInterface", &m_ProductionRunObj);
    RecipeModel m_RecipeModelObj;
    pQmlContext->setContextProperty("RecipeModel", &m_RecipeModelObj);
    pQmlContext->setContextProperty("ActiveScreen", ActiveScreen::getInstance());

    UnitConversionLogic m_UnitConversionLogic;
    pQmlContext->setContextProperty("UnitConversion", &m_UnitConversionLogic);

    DataLoggerLogic m_DataLoggerLogic;
    pQmlContext->setContextProperty("DataLoggerLogic", &m_DataLoggerLogic);

    DisplayModesHMI m_DisplayModesHMI;
    pQmlContext->setContextProperty("DisplayModesHMI", &m_DisplayModesHMI);

    Login m_Login;
    pQmlContext->setContextProperty("LoginObj", &m_Login);

    IdleTimeLogout m_idleTimeLogout;
    pQmlContext->setContextProperty("IdleTimeLogout", &m_idleTimeLogout);

    UserPrivilege m_UserPrivilegen;
    pQmlContext->setContextProperty("UserPrivilegeObj", &m_UserPrivilegen);

    RecipeLabData m_RecipeLabDataObj;
    pQmlContext->setContextProperty("RecipeLabData", &m_RecipeLabDataObj);

    SystemConfiguration m_SystemConfiguration;
    pQmlContext->setContextProperty("SystemConfiguration", &m_SystemConfiguration);

    WeldGraphData m_WeldGraphData;
    pQmlContext->setContextProperty("WeldGraphObj", &m_WeldGraphData);

    CycleDetailsListModel m_CycleDetailsListModel;
    pQmlContext->setContextProperty("CycleDetailsListModel", &m_CycleDetailsListModel);

    CycleDetailTableModel m_CycleDetailtablemodel;
    pQmlContext->setContextProperty("CycleDetailtablemodel", &m_CycleDetailtablemodel);

    DashBoardWelderListModel dashBoardModel;
    engine.rootContext()->setContextProperty("dashBoardModel",&dashBoardModel);



    AnalyticsScreenTableViewOptions  m_AnalyticsScreenTableViewOptions;
    pQmlContext->setContextProperty("AnalyticsScreenTableViewOptions", &m_AnalyticsScreenTableViewOptions);
    m_AnalyticsScreenTableViewOptions.setSourceModel(&m_CycleDetailtablemodel);


    EventLogDetailsListModel m_EventLogDetailsListModel;
    pQmlContext->setContextProperty("EventLogDetailsListModel", &m_EventLogDetailsListModel);

    qmlRegisterType<AlarmManConfiguration>("CheckboxModel", 1, 0, "BoolStructModel");
    AlarmManConfiguration m_AlarmManConfiguration;
    pQmlContext->setContextProperty("BoolStructModel", &m_AlarmManConfiguration);

    GraphSettings m_GraphSettings;
    pQmlContext->setContextProperty("GraphSettings", &m_GraphSettings);

    /*For no weld signature but only settings*/
    QObject::connect(&m_WeldGraphData, &WeldGraphData::initiateNoWeldGraphSignatureSettings ,
                     &m_GraphSettings, &GraphSettings::OnNoWeldSignatureSettingsUpdated);

    /*For both weld signature and its settings*/
    QObject::connect(&m_WeldGraphData, &WeldGraphData::initiateWeldGraphSignatureSettings ,
                     &m_GraphSettings, &GraphSettings::OnWeldSignatureSettingsUpdated);

    Test m_Test;
    pQmlContext->setContextProperty("TestData", &m_Test);

    TestGraphData m_TestGraphData;
    pQmlContext->setContextProperty("TestGraphData", &m_TestGraphData);

    TestGraphSettings m_TestGraphSettings;
    pQmlContext->setContextProperty("TestGraphSettings", &m_TestGraphSettings);

    QObject::connect(&m_TestGraphData, &TestGraphData::initiateTestGraphSignatureSettings ,
                     &m_TestGraphSettings, &TestGraphSettings::OnTestSignatureSettingsUpdated);

    Seek m_Seek;
    pQmlContext->setContextProperty("SeekData", &m_Seek);

    SeekGraphData m_SeekGraphData;
    pQmlContext->setContextProperty("SeekGraphData", &m_SeekGraphData);

    SeekGraphSettings m_SeekGraphSettings;
    pQmlContext->setContextProperty("SeekGraphSettings", &m_SeekGraphSettings);

    QObject::connect(&m_SeekGraphData, &SeekGraphData::initiateSeekGraphSignatureSettings ,
                     &m_SeekGraphSettings, &SeekGraphSettings::OnSeekSignatureSettingsUpdated);

    ScanGraphData m_ScanGraphData;
    pQmlContext->setContextProperty("ScanGraphData", &m_ScanGraphData);

    ScanCycleDetailsListModel m_ScanCycleDetailsListModel;
    pQmlContext->setContextProperty("ScanCycleDetailsListModel", &m_ScanCycleDetailsListModel);

    ScanGraphSettings m_ScanGraphSettings;
    pQmlContext->setContextProperty("ScanGraphSettings", &m_ScanGraphSettings);

    QObject::connect(&m_ScanGraphData, &ScanGraphData::initiateScanGraphSignatureSettings ,
                     &m_ScanGraphSettings, &ScanGraphSettings::OnScanSignatureSettingsUpdated);

    // Create an instance of ComboBoxManager
    UserIODigital m_ComboBoxManager;
    pQmlContext->setContextProperty("ComboBoxManager",&m_ComboBoxManager);

    // Create an instance of AnalogComboBoxManager
    UserIOAnalog m_AnalogComboBoxManager;
    pQmlContext->setContextProperty("AnalogComboBoxManager",&m_AnalogComboBoxManager);

    // Create an instance of IndustrialEthIOComboBoxManager
    IndustrialEthIO m_IndustrialEthIOComboBoxManager;
    pQmlContext->setContextProperty("IndustrialEthIOComboBoxManager",&m_IndustrialEthIOComboBoxManager);

    SystemInformationInterface m_SystemInformationInterfaceObj;
    pQmlContext->setContextProperty("SystemInformationModel",&m_SystemInformationInterfaceObj);

    SystemGeneral m_SystemGeneral;
    pQmlContext->setContextProperty("SystemGeneral", &m_SystemGeneral);

    SystemConfGlobalUserSetting m_GlobalUserSettingObj;
    pQmlContext->setContextProperty("GlobalUserSetting", &m_GlobalUserSettingObj);

    ActuatorSetupData m_ActuatorSetupData;
    pQmlContext->setContextProperty("ActuatorSetupData", &m_ActuatorSetupData);

    AlarmDetailsListModel m_AlarmDetailsListModel;
    pQmlContext->setContextProperty("AlarmDetailsListModel", &m_AlarmDetailsListModel);

    ActiveAlarmDetailsListModel m_ActiveAlarmDetailsListModel;
    pQmlContext->setContextProperty("ActiveAlarmDetailsListModel", &m_ActiveAlarmDetailsListModel);

    UserListDetailsListModel m_UserListDetailsListModel;
    pQmlContext->setContextProperty("UserListDetailsListModel", &m_UserListDetailsListModel);

    UsbAuthDetailsListModel m_UsbAuthDetailsListModel;
    pQmlContext->setContextProperty("UsbAuthDetailsListModel", &m_UsbAuthDetailsListModel);

    BransonSystemConfiguration m_BransonSystemConfigurationObj;
    pQmlContext->setContextProperty("BransonSystConfgService", &m_BransonSystemConfigurationObj);

    DiagnosticUserIO m_DiagnosticUserIO;
    pQmlContext->setContextProperty("DiagnosticUserIOObj", &m_DiagnosticUserIO);


    GenerateReportComman m_GenerateReportIO;
    pQmlContext->setContextProperty("GenerateReportUserIOObj", &m_GenerateReportIO);

    DataFilterListModel m_dataFilterListModel;
    pQmlContext->setContextProperty("DataFilterListModel", &m_dataFilterListModel);

    ServiceCountListModel  m_ServiceCountListModel;
    pQmlContext->setContextProperty("ServiceCountListModel", &m_ServiceCountListModel);

    ActiveServiceReminderDetailsListModel m_ActiveServiceReminderDetailsListModel;
    pQmlContext->setContextProperty("ActiveServiceReminderDetailsListModel", &m_ActiveServiceReminderDetailsListModel);

    CalibrateActuator m_CalibrateActuator;
    pQmlContext->setContextProperty("CalibrateActuator", &m_CalibrateActuator);

    CalibrateForce m_CalibrateForce;
    pQmlContext->setContextProperty("CalibrateForce", &m_CalibrateForce);

    CalibratePressure m_CalibratePressure;
    pQmlContext->setContextProperty("CalibratePressure", &m_CalibratePressure);

    CalibrateQuick m_CalibrateQuick;
    pQmlContext->setContextProperty("CalibrateQuick", &m_CalibrateQuick);

    CalibrateResetSensors m_CalibrateResetSensors;
    pQmlContext->setContextProperty("CalibrateResetSensors", &m_CalibrateResetSensors);

    ReferenceWeldGraphData m_ReferenceWeldGraphData;
    pQmlContext->setContextProperty("ReferenceWeldGraphData", &m_ReferenceWeldGraphData);

    DateTimeSettings m_DateTimeSettings;
    pQmlContext->setContextProperty("DateTimeSettings", &m_DateTimeSettings);

    SystemNetworkConfiguration m_SystemNetworkConfiguration;
    pQmlContext->setContextProperty("NetworkConfiguration", &m_SystemNetworkConfiguration);

    SystemNetworkConfigurationEthIp m_SystemNetworkConfigurationEthIp;
    pQmlContext->setContextProperty("SystemNetworkConfigurationEthIp", &m_SystemNetworkConfigurationEthIp);

    SystemNetworkConfigurationProfinet m_SystemNetworkConfigurationProfinet;
    pQmlContext->setContextProperty("SystemNetworkConfigurationProfinet", &m_SystemNetworkConfigurationProfinet);

    SystemNetworkConfigurationNFSSetup m_SystemNetworkConfigurationNFSSetup;
    pQmlContext->setContextProperty("SystemNetworkConfigurationNFSSetup", &m_SystemNetworkConfigurationNFSSetup);

    BransonServiceInterface m_BransonServiceInterface;
    pQmlContext->setContextProperty("BransonServiceInterface", &m_BransonServiceInterface);

    SoftwareUpgradeInterface m_SoftwareUpgradeInterface;
    pQmlContext->setContextProperty("SoftwareUpgradeInterface", &m_SoftwareUpgradeInterface);
  
	SystemFeature m_SystemFeature;
    pQmlContext->setContextProperty("SystemFeature", &m_SystemFeature);

    ResultViewWeldProxyModel m_ResultViewWeldProxyModel;
    pQmlContext->setContextProperty("ResultViewWeldProxyModel", &m_ResultViewWeldProxyModel);
    m_ResultViewWeldProxyModel.setSourceModel(&m_CycleDetailtablemodel);

    ResultViewTableProxyModel m_ResultViewTableProxyModel;
    pQmlContext->setContextProperty("proxyModel", &m_ResultViewTableProxyModel);
    m_ResultViewTableProxyModel.setSourceModel(&m_CycleDetailtablemodel);

    // Initialize Ace system
    AcePlatformInit::AceInit();

    app.installEventFilter(&m_idleTimeLogout);
    
    ConfigStatus *ptrConfigStatus = new ConfigStatus();
    pQmlContext->setContextProperty("configStatus", ptrConfigStatus);

    // Created instance of PlatformConfigUpgrade class and start thread
    PlatformConfigUpgrade *ptrPlatformConfigUpgrade = new PlatformConfigUpgrade();
    pQmlContext->setContextProperty("configurationUpgrade", ptrPlatformConfigUpgrade);
    ptrPlatformConfigUpgrade->start();

    //============================================================//
    /*TODO : Below section is workaround for Production screen implementation with 3 welder represented by each CommThreads,
                 where dynamic welder approach implemented*/
    UpdateScreen *MyUpdateScreen = UpdateScreen::getInstance();
    CommThread *ptrCommThread[CONFIG_MAX_WELDERS];

    // Created instance of auto welder discovery server.
    WDSServer *WdsServer = WDSServer::GetInstance();

    // Start auto welder discovery service
    WdsServer->start();

    // Created instance of multiWelderInterface
    MultiwelderInterface multiWelderInterface;

  // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     ptrConfigStatus , &ConfigStatus::onSignalCurrentLanguageChanged);
    // Export MultiwelderInterface class to qml.
    pQmlContext->setContextProperty("multiWelderInterface", &multiWelderInterface);

    // Connect PeerConnected signal to MultiwelderInterface slot.
    QObject::connect(WdsServer, &WDSServer::PeerConnected,
                         &multiWelderInterface, &MultiwelderInterface::OnPeerConnected);

    // Connect PeerDisconnected signal to MultiwelderInterface slot.
    QObject::connect(WdsServer, &WDSServer::PeerDisconnected,
                     &multiWelderInterface, &MultiwelderInterface::OnwelderRemoved);

    // Connect selectWelderIndexChanged signal to onSelectWelderIndexChanged slot.
    QObject::connect(&multiWelderInterface, &MultiwelderInterface::selectWelderIndexChanged,
                     ptrConfigStatus , &ConfigStatus::onSelectWelderIndexChanged);

    // Connect IsFirmwareVersionMismatchChangeDetected signal to onFirmwareMismatchDetect slot.
    QObject::connect(WdsServer, &WDSServer::IsFirmwareVersionMismatchChangeDetected,
                     ptrConfigStatus, &ConfigStatus::onFirmwareMismatchDetect);

    // Created Cyclic Activity Timer
    CyclicActivityTimer *Cat = new CyclicActivityTimer();

    CommPeerWrapper::m_PeerMap.clear();

    for (int i = 0; i < CONFIG_MAX_WELDERS; i++)
    {
        // Created Communication Thread
        ptrCommThread[i] = new CommThread(i);

        // Connect HMIScreenUpdated signal to UpdateScreen slot.
        QObject::connect(ptrCommThread[i], &CommThread::HMIScreenUpdated,
                         MyUpdateScreen , &UpdateScreen::slotScreenUpdateReceived);

        // Connect HMIConfigStatusUpdated signal to onSelectWelderIndexChanged slot.
        QObject::connect(ptrCommThread[i], &CommThread::HMIConfigStatusUpdated,
                         ptrConfigStatus , &ConfigStatus::onSelectWelderIndexChanged);

        // Start Comm Thread
        ptrCommThread[i]->start();
    }

    // Start Scheduleing Cyclic Activity Timer
    Cat -> StartScheduleing();

    // update Scheduleing Cyclic Activity Timer to MAX WELDER
    Cat -> UpdateSchedule(CONFIG_MAX_WELDERS);

    //===========================================================//

#ifdef QT_DEBUG

#else
    qInstallMessageHandler(messageHandler);
    qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss:zzz}|%{type}|%{file}|%{function}|%{line}|%{message}");
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

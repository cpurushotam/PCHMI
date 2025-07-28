/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2023

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
This file includes declaration of signal and slots used by
    UpdateScreen.cpp

--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/05/2023 - Initial version.
***************************************************************************/
#ifndef UPDATESCREENS_H
#define UPDATESCREENS_H
#include "uiscreendef.h"
#include "ProductionScreen_MB.h"
#include <QObject>
#include "DataInterfaceConfig_HMI.h"
#include "WeldRecipeAce.h"
#include "ActiveScreen.h"
#include "uiscreendef.h"
#include "WeldResultAce.h"
#include "WeldSignatureAce.h"
#include "SystemConfigurationGeneral_MB.h"
#include "HornScanResult.h"
#include "HornScanSignature.h"
#include "HornScanRecipe.h"
#include "SeekResult.h"
#include "SeekSignature.h"
#include "SeekRecipe.h"
#include "TestResult.h"
#include "TestSignature.h"
#include "TestRecipe.h"
#include "DataLoggerLogic.h"
#include "BransonServiceTab.h"
#include "SoftwareUpgrade.h"
#include "FieldBusIOManager.h"
#include "SystemNetworkConfigurationEthIp.h"
#include "ProfinetSetting.h"

/*UpdateScreen class declaration*/
class UpdateScreen : public QObject
{
private:
    Q_OBJECT

    explicit UpdateScreen(QObject *parent = nullptr);
    UpdateScreen(const UpdateScreen&) = delete;
    UpdateScreen& operator=(const UpdateScreen&) = delete;

public:
    /*Method which retunrs singleton object of UpdateScreen class*/
    static UpdateScreen* getInstance();
    bool analyticsFlag = true;
    bool scanFlag = true;
    bool seekFlag = true;
    bool testFlag = true;

signals:
    /*Signal used for production Screen data updates*/
    void ProductionScreenUpdated(ProdScreenData *PtrProdScreen , SystemConfigurationGeneral_MB *MySysGenData);

    /*Signal used for Recipe Cards Screen data updates*/
    void RecipeCardsScreenUpdated(WeldRecipeACE *MyCommData, int WelderId);

    /*Signal used for Recipe Lab Screen data updates*/
    void RecipeLabScreenUpdated(WeldRecipeACE *MyCommData, int WelderId);

    /*Signal used for ActuatorSetup Table screen data updates*/
    void ActuatorSetupScreenUpdated(ActuatorSetupACE *MyCommData1, WeldRecipeACE *MyCommData2, SystemConfigurationGeneral_MB *MyCommData3, int WelderId);

    /*Signal used for Analytics Screen data updates*/
    void AnalyticsScreenUpdated(WeldResultACE *MyCommData, WeldSignatureACE *MyCommData2, int WelderId);
    void AnalyticsSignatureUpdated(WeldSignatureACE *MyCommData3, int WelderId);
    void AnalyticsTableViewUpdated(WeldResultACE *MyCommData1, int WelderId);

    /*Signal used for Reference Weld Sign Graph data updates*/
    void ReferenceWeldSignatureUpdated(ReferenceWeldSignature *MyCommData1, int WelderId);

    /*Signal used for EventLog Table Screen data updates*/
    void EventLogTableViewUpdated(EventLog *MyCommData1, int WelderId);

    /*Signal used for AlarmManagement Table Screen data updates*/
    void AlarmManagementViewUpdated(AlarmMgrACE *MyCommData1, int WelderId);

    /*Signal used for UserIODigital Tab Screen data updates*/
    void DigitalUserIOUpdated(DigitalIOMgr *MyCommData1, int WelderId);

    /*Signal used for UserIODigital Tab Screen data updates*/
    void DigitalUserIOAnalogUpdated(DigitalIOMgr *MyCommData1, int WelderId);

    /*Signal used for Industrial User IO Tab Screen data updates*/
    void IndustrialUserIOUpdated(FieldBusIOMgr *MyCommData1, int WelderId);

    /*Signal used for UserIOAnalog Tab Screen data updates*/
    void DiagnosticUserIOUpdated(DigitalIOMgr *MyCommData1, int WelderId);

    /*Signal used for System Config General Tab screen data updates*/
    void SysConfgGenScreenUpdated(SystemConfigurationGeneral_MB *MySysGenData, int WelderId);

    /*Signal used for Unit COnversion LOgic class  to update the data on screen*/
    void UnitChangedScreenUpdated(SystemConfigurationGeneral_MB *MySysGenData, int WelderId);
    /*Signal used for DataLogger Logic class to update the data on screen*/
    void DataLoggerMessageUpdated(DataLogger *MyLoggerData, int WelderId);
    /*Signal used for DisplayMgr Screen data updates*/
    void DisplayModeDataUpdated(DisplayMgr * MyCommData1, int WelderId);

    /*Signal used for Scan Screen data updates*/
    void ScanScreenUpdated(HornScanResult *MyCommData, HornScanSignature *MyCommData2, HornScanRecipe *MyCommData3, int WelderId);
    void ScanSignatureUpdated(HornScanSignature *MyCommData4, int WelderId);

    /*Signal used for Seek Screen data updates*/
    void SeekScreenUpdated(SeekResult *MyCommData, SeekSignature *MyCommData2, SeekRecipe *MyCommData3, int WelderId);
    void SeekSignatureUpdated(SeekSignature *MyCommData4, int WelderId);

    /*Signal used for Test Screen data updates*/
    void TestScreenUpdated(TestResult *MyCommData, TestSignature *MyCommData2, TestRecipe *MyCommData3, int WelderId);
    void TestSignatureUpdated(TestSignature *MyCommData4, int WelderId);

    /*Signal used for Alarm Events Log Screen data updates*/
    void AlarmEventsLogUpdated(AlarmMgrACE *MyCommData, ServiceManagement *MyCommData2, int WelderId);

    /*Signal used for Active Alarm Events Log Screen data updates*/
    void ActiveAlarmEventsLogUpdated(AlarmMgrACE *MyCommData1, int WelderId);

    /*Signal used for Global User Setting Screen data updates*/
    void GlobalUserSettingDataUpdated(GlobalUserSetting *MyCommData, UserManagement *MyCommData1, SystemConfigurationGeneral_MB *MyCommData2, int WelderId);

    /*Signal used for user list Screen data updates*/
    void UserListScreenViewUpdated(UserManagement *MyCommData1, int WelderId);

    /*Signal used for Service Count Screen data updates*/
    void ServiceCountScreenUpdated(ServiceManagement *MyCommData, int WelderId);

    /*Signal used for Branson System configuration Screen data updates*/
    void BransonSysConfgDataUpdated(SystemConfigBransonService *MyCommData, int WelderId);

    /*Signal used for Branson Service Screen data updates*/
    void BransonServiceDataUpdated(BransonServiceTab *MyCommData, int WelderId);

    /*Signal used for system information machine details Screen data updates*/
    void SystemInformationDataUpdated(SystemInformation *MyCommData, SystemConfigBransonService *MyCommData2, int WelderId);

    /*Signal used for system information machine details Screen data updates*/
    void SystemFeatureDataUpdated(ConfigUtilityVersion *MyCommData, int WelderId);

    /*Signal used for Login Screen data updates*/
    void LoginScreenViewUpdated(UserManagement *MyCommData1, int WelderId);

    /*Signal used for System Calibration Screen data updates*/
    void CalibrationDataChanged(CalibrationAce *MyCommData, int WelderId);

    /*Signal used for System Network configuration Screen data updates*/
    void SysNetworkConfgDataUpdated(NetworkConfiguration *MyCommData, int WelderId);

    /*Signal used for System Network configuration NfsManager Screen data updates*/
    void SysNetworkConfgNFSDataUpdated(NfsManager *MyCommData, int WelderId);

    /*Signal used for System Network configuration Industrial EIP Screen data updates*/
    void SysNetworkConfgIndusEthIpDataUpdated(NetworkConfigurationEthernetIp *MyCommData, int WelderId);

    /*Signal used for System Network configuration Profinet Screen data updates*/
    void SysNetworkConfgProfinetDataUpdated(ProfinetSetting *MyCommData, int WelderId);

    /*Signal used for System  configuration USB Screen data updates*/
    void SysConfgUSBAuthDataUpdated(USBAuthentication *MyCommData, int WelderId);

    /*Signal used for Date and Time Settings*/
    void DateAndTimeUpdated(DateTimeConversion *MyCommData3, int WelderId);

    /*Signal used for Software Upgrade Screen data updates*/
    void SoftwareUpgradeDataUpdated(SoftwareUpgrade * MyCommData1, int WelderId);

    /*Signal used for Generate Report Screen*/
     void GenerateReportSummaryScreenUpdated(ReportManager *MyCommData);
   	 void SummaryScreenUpdated(USBStreaming *MyCommData);

    /*Slot which gets called when data update signal generates by communication thread
      with welder ID*/
public slots:
    void slotScreenUpdateReceived(uint16_t WelderId, DataInterfaceConfig_HMI *m_DataInterfaceConfig_HMI_Obj);

};
#endif // UPDATESCREENS_H

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Peer Info -	Responsible for store each peer (welder) information-
  	  	  	  	  	    1. Current state of peer
  	  	  	  	  	    2. Communication status of peer - is peer shutdown or connected.
  	  	  	  	  	    3. Cyclic activity of respective peer.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.
 rev2: 16/10/2023 - Implementation of setter/getter function for HMI Platform Config
***************************************************************************/
#ifndef PeerInfo_H
#define PeerInfo_H

#include <semaphore.h>
#include <atomic>
#include <map>

#include "BIOConfig.h"
#include "DataLogger.h"
#include "PlatformConfigInterface.h"
#include "WeldRecipeAce.h"
#include "WeldSignatureAce.h"
#include "WeldResultAce.h"
#include "CommStatAce.h"
#include "DisplayManager.h"
#include "SeekResult.h"
#include "SeekSignature.h"
#include "EventLog.h"
#include "AlarmManagerAce.h"
#include "TestResult.h"
#include "TestSignature.h"
#include "HornScanResult.h"
#include "HornScanSignature.h"
#include  "IOManager.h"
#include "ActuatorSetupAce.h"
#include "UserManagement.h"
#include "GlobalUserSetting.h"
#include "SystemConfigurationGeneral_MB.h"
#include "DataLoggerManager.h"
#include "ReferenceWeldSignatureAce.h"
#include "ServiceReminderManagement.h"
#include "SystemConfigBransonService.h"
#include "SystemInformation.h"
#include "CalibrationAce.h"
#include "NetworkConfiguration.h"
#include "BransonServiceTab.h"
#include "DateTimeConversion.h"
#include "SoftwareUpgrade.h"
#include "ReportManager.h"
#include "USBStreaming.h"
#include "FieldBusIOManager.h"
#include "NetworkConfigurationEthernetIp.h"
#include "ConfigUtilityVersion.h"
#include "ProfinetSetting.h"
#include "NfsManager.h"
#include "USBAuthentication.h"
#include "ImportExport.h"
#include "OpcuaClientCertificateUpload.h"

// Rename of map data type to make readability better.
// Active configuration table to store configurations
typedef std::map <std::string, PlatformConfigInterface*> ActiveConfig;

// Max Retry count to start connection
constexpr unsigned int COMM_START_MAX_RETRY_COUNT = 3;

/* Enum to define states implemented by COMM thread & its transition*/
enum COMM_THREAD_STATES
{
    COMM_START_REQUEST = 0,  /* State machine for connection start request */
    COMM_START,         	 /* State machine for starting Communication  */
    COMM_PROCESS,       	 /* State machine for Communication process */
    COMM_EXIT,          	 /* State machine for exiting communication  */
    COMM_EVENT,         	 /* State machine for Logging Event */
    COMM_ALARM          	 /* State machine for logging alarm */
};

// Enum declaration for HMI Platform COnfiguration status
enum CONFIG_STATES
{
    E_NO_CONN = 0,              /* No Welder connected */
    E_IN_PROCESS,               /* Configuration validation Inprocess */
    E_SUCCESS,                  /* Configuration validation success */
    E_FAIL                      /* Configuration validation failed */
};

// PeerInfo class defination
class PeerInfo
{
private:
    // Semaphore for synchronization of comm thread
    sem_t m_ThreadCyclicActivitySem;

    // Semaphore for start request communication
    sem_t m_StartRequestSem;

    // Gracefully shutdown for communication process
    std::atomic<bool> m_GracefulShutdown;

    // Connect flag for peer connected or not
    COMM_THREAD_STATES m_CurrentState;

    // log identifier
    size_t m_LogId;

    // log buffer
    char m_LogBuffer[buff_size_config]={0};

    // Structure variable declaration to store configuration for communication.
    CommConfig m_SSLConfig;

    // connection details of peer
    char *m_PeerIpAddr;

    // Config status for HMI platform config
    int m_ConfigState;

    // AceActiveConfig table to store configuration of each welder.
    ActiveConfig *m_ActiveConfig = nullptr;

    comm_stat *m_ptrCommStatObj;
    WeldRecipe *m_ptrWeldRecipe;
    WeldResult *m_ptrWeldResult;
    WeldSignature *m_ptrWeldSignature;
    ReferenceWeldSignature *m_ptrRefWeldSignature;
    SeekResult *m_ptrSeekResult;
    SeekSignature *m_ptrSeekSignature;
    EventLog   *m_ptrEventLog;
    AlarmMgr   *m_ptrAlarmMgr;
    TestResult *m_ptrTestResult;
    TestSignature* m_ptrTestSignature;
    HornScanResult *m_ptrHornScanResult;
    HornScanSignature *m_ptrHornScanSignature;
    DigitalIOMgr  *m_ptrDgtUserIO;
    DisplayMgr *m_ptrDispMgrObj;
    ActuatorSetup *m_ptrActuatorSetup;
    UserManagement *m_ptrUserManagementObj;
    GlobalUserSetting *m_ptrGlobalUserSettingsObj;
    SystemConfigurationGeneral_MB *m_ptrSystemConfiguration;
    DataLogger *m_ptrDataLogger;
    ServiceManagement *m_ptrServiceManagementObj;
    SystemConfigBransonService *m_systemConfigBransonServiceObj;
    SystemInformation *m_systemInformationObj;
    CalibrationAce *m_CalibrationAceObj;
    NetworkConfiguration *m_NetworkConfigurationObj;
    BransonServiceTab *m_BransonServiceTabObj;
    DateTimeConversion * m_DateTimeConversionObj;
    SoftwareUpgrade * m_SoftwareUpgradeObj;
    ReportManager *m_ReportManagerPtrObj;
    USBStreaming *m_ptrUSBStream;
    FieldBusIOMgr *m_ptrFieldBusCustomIO;
    NetworkConfigurationEthernetIp *m_NetworkConfigurationEthernetIp;
    ConfigUtilityVersion *m_ptrConfigUtilityVersion;
	ProfinetSetting *m_ptrProfinetSettings;
	NfsManager *m_NfsManagerPtr;
	USBAuthentication *m_ptrUSBAuthentication;
	ImportExport *m_ptrImportExport;
	OpcuaClientCertificateUpload *m_OpcuaClientCertificateUploadObj;
	
public:
    // Contructor declaration
    PeerInfo();

    // Destructor declarion to perform cleanup activity
    ~PeerInfo();

    // Trigger cyclic activity semaphore.
    bool TriggerCyclicActivity();

    // Trigger start request semaphore.
    bool TriggerStartRequest(char *PeerIpAddr);

    // Wait for cyclic activity semaphore.
    bool WaitTriggerCyclicActivity();

    // Wait start request semaphore.
    char *WaitTriggerStartRequest();

    // Set status of graceful shutdown flag.
    bool SetGracefulShutdownFlag(bool);

    // Read status of graceful shutdown flag.
    bool GetGracefulShutdownFlag();

    // Set current state of peer
    bool SetCurrentState(int CurrentState);

    // Get current state of peer.
    int GetCurrentState();

    // Get communication SSL configuration for BIO Wrapper.
    CommConfig *GetCommSSLConfig();

    // Set platform config state
    void SetPlatformConfigState(const int ConfigState);

    // Get platform config state.
    int GetPlatformConfigState();

    // Get Active confgiuration.
    ActiveConfig *GetActiveConfiguration();

    comm_stat* GetCommStatObjPtr();
    WeldRecipe* GetWeldRecipeObjPtr();
    WeldResult* GetWeldResultObjPtr();
    WeldSignature* GetWeldSignatureObjPtr();
    ReferenceWeldSignature* GetReferenceWeldSignatureObjPtr();
    SeekResult* GetSeekResultObjPtr();
    SeekSignature* GetSeekSignatureObjPtr();
    EventLog*   GetEventLogObjPtr();
    AlarmMgr*   GetAlarmMgrObjPtr();
    TestResult* GetTestResultObjPtr();
    TestSignature* GetTestSignatureObjPtr();
    HornScanResult* GetHornScanResultObjPtr();
    HornScanSignature* GetHornScanSignatureObjPtr();
    DigitalIOMgr *GetDigitalIOObjPtr();
    DisplayMgr *GetDispMgrObjPtr();
    ActuatorSetup* GetActuatorSetupObjPtr();
    UserManagement* GetUserManagementObjPtr();
    GlobalUserSetting *GetGlobalUserSettingsObjPtr();
    SystemConfigurationGeneral_MB* GetSystemConfigObjPtr();
    DataLogger *GetDataLoggerObjPtr();
    ServiceManagement* GetServiceManagementObjPtr();
    SystemConfigBransonService *GetSystemConfigBransonServiceObjPtr();
    SystemInformation *GetSystemInformationObjPtr();
    CalibrationAce *GetCalibrationAceObjPtr();
    NetworkConfiguration *GetNetworkConfigObjPtr();
    NetworkConfigurationEthernetIp *GetNetworkConfigurationEthernetIp();
    BransonServiceTab *GetBransonServiceTabObjPtr();
    DateTimeConversion * GetDateTimeConversionObjPtr();
    SoftwareUpgrade * GetSoftwareUpgradeObjPtr();
    ReportManager *GetReportManagerObjPtr();
    USBStreaming *GetUsbStreamObjPtr();
    FieldBusIOMgr *GetFieldBusIOObjPtr();
    ConfigUtilityVersion *GetConfigUtilityVersionObjPtr();
	ProfinetSetting *GetProfinetSettingsObjPtr();
	NfsManager *GetNfsManagerObjPtr();
	USBAuthentication *GetUsbAuthenticationObjPtr();
	ImportExport *GetImportExportPtr();
	OpcuaClientCertificateUpload *GetOpcuaClientCertificateUploadObjPtr();
};

#endif // PeerInfo_H

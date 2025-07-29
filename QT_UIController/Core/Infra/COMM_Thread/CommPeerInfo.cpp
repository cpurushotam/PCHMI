/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Definition Peer Info -	Responsible for store each peer (welder) information-
  	  	  	  	  	    1. Current state of peer
  	  	  	  	  	    2. Communication status of peer - is peer shutdown or connected.
  	  	  	  	  	    3. Cyclic activity of respective peer.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.
 rev2: 16/10/2023 - Implementation of setter/getter function for HMI Platform Config
***************************************************************************/
#include "CommPeerInfo.h"

#include "ActuatorInit.h"
#include "PowerLevelSysFrequencySupport.h"
#include "PowerSupplyType.h" 
#include "CylinderSizeSupport.h"
#include "StrokeLength.h"
#include "FieldbusSupport.h"
#include "StorageSupport.h"
#include "EventLogSupport.h"
#include "BatchControlSupport.h"
#include "LDAPSupport.h"
#include "UserAccessLevelSupport.h"
#include "BarcodeScannerSupport.h"
#include "UserIOSupport.h"
#include "PCUtilitySupport.h"
#include "USBStreaming.h"
#include "HMIDeviceSupport.h"
#include "BearingTypeSupport.h"
#include "ImportExport.h"

/**************************************************************************//**
* \brief   - Initilize Peer info class.
*            1. Initilize graceful shutdown flag
*            2. Initialize current state as waiting for start request
*            3. Initilize semaphore for thread cyclic activity and start request.
* \param   - None
*
* \return  - None
******************************************************************************/
PeerInfo::PeerInfo()
{
    if (ASCConfig::ptrASCParameters == nullptr)
    {
        throw std::runtime_error("ASCParameters not initialized.");
    }

    // Initialize communication configuration.
    m_SSLConfig = (*ASCConfig::ptrASCParameters);

    ActuatorInit *ActuatorTypeObj =  new ActuatorInit();
	PowerSupplyTypeSupport *PowerSupplyTypeSupportObj = new PowerSupplyTypeSupport();
	PowerLevelSysFrequencySupport *PowerLevelSysFrequencySupportObj = new PowerLevelSysFrequencySupport();
	CylinderSizeSupport *CylinderSizeSupportObj = new CylinderSizeSupport();
	StrokelengthSupport *StrokelengthSupportObj = new StrokelengthSupport();
	FieldbusSupport *FieldbusSupportObj = new FieldbusSupport();
	StorageSupport *StorageSupportObj = new StorageSupport();
	EventLogSupport *EventLogSupportObj = new EventLogSupport();
	BatchControlSupport *BatchControlSupportObj = new BatchControlSupport();
	LDAPSupport *LDAPSupportObj = new LDAPSupport();
	UserAccessLevelSupport *UserAccessLevelSupportObj = new UserAccessLevelSupport();
	BarcodeScannerSupport *BarcodeScannerSupportObj = new BarcodeScannerSupport();
	UserIOSupport *UserIOSupportObj = new UserIOSupport();
	PCUtilitySupport *PCUtilitySupportObj = new PCUtilitySupport();
	HMIDeviceSupport *HMIDeviceSupportObj =  new HMIDeviceSupport();
    BearingTypeSupport *BearingTypeSupportObj =  new BearingTypeSupport();

    m_ActiveConfig = new ActiveConfig();

    *m_ActiveConfig = {
        /* Configuration,    object of configuration class */
        { ACTUATOR_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (ActuatorTypeObj)},
		{ POWER_SUPPLY_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (PowerSupplyTypeSupportObj)},
		{ POWER_LEVEL_SYSTEM_FREQUENCY_KEY, dynamic_cast<PlatformConfigInterface*> (PowerLevelSysFrequencySupportObj)},
		{ CYLINDER_SIZE_KEY, dynamic_cast<PlatformConfigInterface*> (CylinderSizeSupportObj)},
        { BEARING_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (BearingTypeSupportObj)},
		{ STROKE_LENGTH_KEY, dynamic_cast<PlatformConfigInterface*> (StrokelengthSupportObj)},
		{ FIELDBUS_SUPPORT_KEY, dynamic_cast<PlatformConfigInterface*> (FieldbusSupportObj)},
		{ STORAGE_KEY, dynamic_cast<PlatformConfigInterface*> (StorageSupportObj)},
		{ EVENT_LOG_KEY, dynamic_cast<PlatformConfigInterface*> (EventLogSupportObj)},
		{ BATCH_CONTROL_KEY, dynamic_cast<PlatformConfigInterface*> (BatchControlSupportObj)},
		{ LDAP_KEY, dynamic_cast<PlatformConfigInterface*> (LDAPSupportObj)},
		{ USER_ACCESS_LEVEL_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (UserAccessLevelSupportObj)},
		{ BARCODE_SCANNER_KEY, dynamic_cast<PlatformConfigInterface*> (BarcodeScannerSupportObj)},
		{ USER_IO_KEY, dynamic_cast<PlatformConfigInterface*> (UserIOSupportObj)},
        { PC_UTILITY_KEY, dynamic_cast<PlatformConfigInterface*> (PCUtilitySupportObj)},
        { HMI_DEVICE, dynamic_cast<PlatformConfigInterface*> (HMIDeviceSupportObj)},
    };

    m_ptrCommStatObj = new comm_stat();
    m_ptrWeldRecipe = new WeldRecipeACE();
    m_ptrWeldResult = new WeldResultACE();
    m_ptrWeldSignature = new WeldSignatureACE();
    m_ptrRefWeldSignature = new ReferenceWeldSignature();
    m_ptrSeekResult = new SeekResult();
    m_ptrSeekSignature = new SeekSignature();
    m_ptrEventLog   = new EventLog();
    m_ptrAlarmMgr   = new AlarmMgrACE();
    m_ptrTestSignature=new TestSignature();
    m_ptrTestResult =new TestResult();
    m_ptrHornScanResult = new HornScanResult();
    m_ptrHornScanSignature = new HornScanSignature();
    m_ptrActuatorSetup = new ActuatorSetupACE();
    m_ptrDgtUserIO = new DigitalIOMgr();
    m_ptrDispMgrObj = new DisplayMgr();
    m_ptrUserManagementObj = new UserManagement();
    m_ptrGlobalUserSettingsObj = new GlobalUserSetting();
    m_ptrSystemConfiguration = new SystemConfigurationGeneral_MB();
    m_ptrDataLogger = new DataLogger();
    m_ptrServiceManagementObj = new ServiceManagement();
    m_systemConfigBransonServiceObj = new SystemConfigBransonService();
    m_systemInformationObj = new SystemInformation();
    m_CalibrationAceObj = new CalibrationAce();
    m_NetworkConfigurationObj = new NetworkConfiguration();
    m_NetworkConfigurationEthernetIp = new NetworkConfigurationEthernetIp();
    m_BransonServiceTabObj = new BransonServiceTab();
    m_DateTimeConversionObj = new DateTimeConversion();
    m_SoftwareUpgradeObj = new SoftwareUpgrade();
    m_ReportManagerPtrObj = new ReportManager();
    m_ptrUSBStream = new USBStreaming();
    m_ptrFieldBusCustomIO = new FieldBusIOMgr();
    m_ptrConfigUtilityVersion = new ConfigUtilityVersion();
	m_ptrProfinetSettings = new ProfinetSetting();
	m_NfsManagerPtr =  new NfsManager();
	m_ptrUSBAuthentication = new USBAuthentication();
	m_ptrImportExport = new ImportExport();
	m_OpcuaClientCertificateUploadObj = new OpcuaClientCertificateUpload();

    /* Initially gracefull shutdown is off */
    this->m_GracefulShutdown=false;

    /* Initialize current state as waiting for start request*/
    this->m_CurrentState=COMM_START_REQUEST;

    /* Initilize semaphore for thread cyclic activity */
    if (sem_init(&this->m_ThreadCyclicActivitySem, 0, 0) != 0)
    {
        throw std::runtime_error ("CyclicActivitySem init failed");
    }

    /* Initilize semaphore for start request */
    if (sem_init(&this->m_StartRequestSem, 0, 0) != 0)
    {
        throw std::runtime_error ("StartRequestSem init failed");
    }
}

/**************************************************************************//**
* \brief   - Triggered cyclic activity for comm thread
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::TriggerCyclicActivity()
{
    /* Release semaphore for cyclic activity signal for comm thread */
    if (sem_post(&m_ThreadCyclicActivitySem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_post failed");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
        return false;
    }

    return  true;
}

/**************************************************************************//**
* \brief   - Triggered start request.
*
* \param   - PeerIpAddr - IP address of peer
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::TriggerStartRequest(char *PeerIpAddr)
{
    /* Release semaphore for connection start request */
    if (sem_post(&m_StartRequestSem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequestSem sem_post failed");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
        return false;
    }

    m_PeerIpAddr = PeerIpAddr;

    return true;
}

/**************************************************************************//**
* \brief   - Wait for cyclic activity semaphore
*
* \param   - None
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::WaitTriggerCyclicActivity()
{
    /* Waiting for cyclic activity signal for comm thread */
    if (sem_wait(&m_ThreadCyclicActivitySem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_wait failed");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
        return false;
    }
    return  true;
}

/**************************************************************************//**
* \brief   - wait for start request semaphore.
*
* \param   - None
*
* \return  - PeerIpAddr -  IP address of peer
******************************************************************************/
char *PeerInfo::WaitTriggerStartRequest()
{
    /* Waiting for connection start request */
    if (sem_wait(&m_StartRequestSem) != 0)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequestSem sem_wait failed");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
    }

    return  m_PeerIpAddr;
}

/**************************************************************************//**
* \brief   - Set status of graceful shutdown flag.
*
* \param   - bool status
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::SetGracefulShutdownFlag(bool status)
{
    // Set status of graceful shutdown flag.
    m_GracefulShutdown=status;
    return true;
}

/**************************************************************************//**
* \brief   - Read status of graceful shutdown flag.
*
* \param   - None
*
* \return  - status of graceful shutdown flag.
******************************************************************************/
bool PeerInfo::GetGracefulShutdownFlag()
{
    // Read status of graceful shutdown flag.
    return m_GracefulShutdown;
}

/**************************************************************************//**
* \brief   - Set current state of peer.
*
* \param   - bool    CurrentState
*
* \return  - if success true else false
******************************************************************************/
bool PeerInfo::SetCurrentState(int CurrentState)
{
    // Set current state of peer.
    m_CurrentState=(COMM_THREAD_STATES) CurrentState;
    return true;
}

/**************************************************************************//**
* \brief   - Get current state of peer.
*
* \param   - None
*
* \return  - int - Return current state of peer
******************************************************************************/
int PeerInfo::GetCurrentState()
{
    // Return current state of peer.
    return m_CurrentState;
}

/**************************************************************************//**
* \brief   - Return communication SSL configuration for BIO Wrapper.
*
* \param   - None
*
* \return  - CommConfig *- Pointer to communication SSL configuration.
******************************************************************************/
CommConfig *PeerInfo::GetCommSSLConfig()
{
    return &m_SSLConfig;
}

/**************************************************************************//**
* \brief   - Set configuration state of platform config.
*
* \param   - int ConfigState - configuration state of platform config
*
* \return  - None.
******************************************************************************/
void PeerInfo::SetPlatformConfigState(const int ConfigState)
{
    m_ConfigState = ConfigState;
}

/**************************************************************************//**
* \brief   - Return configuration state of platform config.
*
* \param   - None
*
* \return  - int ConfigState - configuration state of platform config.
******************************************************************************/
int PeerInfo::GetPlatformConfigState()
{
    return m_ConfigState;
}

/**************************************************************************//**
* \brief   - Return Active Configuration
*
* \param   - None
*
* \return  - ActiveConfig * - pointer to Active Configuration.
******************************************************************************/
ActiveConfig *PeerInfo::GetActiveConfiguration()
{
    return m_ActiveConfig;
}

/**************************************************************************//**
* \brief   - Return Weld Recipe object pointer
*
* \param   - None
*
* \return  - Weld Recipe object pointer
******************************************************************************/
WeldRecipe *PeerInfo::GetWeldRecipeObjPtr()
{
    return m_ptrWeldRecipe;
}

/**************************************************************************//**
* \brief   - Return Weld Result object pointer
*
* \param   - None
*
* \return  - WeldResult object pointer
******************************************************************************/
WeldResult *PeerInfo::GetWeldResultObjPtr()
{
    return m_ptrWeldResult;
}

/**************************************************************************//**
* \brief   - Return Event Log object pointer
*
* \param   - None
*
* \return  - EventLog object pointer
******************************************************************************/
EventLog *PeerInfo::GetEventLogObjPtr()
{
	return m_ptrEventLog;
}

/**************************************************************************//**
* \brief   - Return Alarm manager object pointer
*
* \param   - None
*
* \return  - AlarmMgr object pointer
******************************************************************************/
AlarmMgr *PeerInfo::GetAlarmMgrObjPtr()
{
    return m_ptrAlarmMgr;
}

/**************************************************************************//**
* \brief   - Return Weld Signature object pointer
*
* \param   - None
*
* \return  - WeldSignature object pointer
******************************************************************************/
WeldSignature *PeerInfo::GetWeldSignatureObjPtr()
{
    return m_ptrWeldSignature;
}


/**************************************************************************//**
* \brief   - Return Reference Weld Signature object pointer
*
* \param   - None
*
* \return  - ReferenceWeldSignature object pointer
******************************************************************************/
ReferenceWeldSignature *PeerInfo::GetReferenceWeldSignatureObjPtr()
{
    return m_ptrRefWeldSignature;
}

/**************************************************************************//**
* \brief   - Return seek Result object pointer
*
* \param   - None
*
* \return  - SeekResult object pointer
******************************************************************************/
SeekResult *PeerInfo::GetSeekResultObjPtr()
{
    return m_ptrSeekResult;
}

/*****************************************************************************//**
* \brief   - Return seek Signature object pointer
*
* \param   - None
*
* \return  - SeekSignature object pointer
******************************************************************************/
SeekSignature *PeerInfo::GetSeekSignatureObjPtr()
{
    return m_ptrSeekSignature;
}
/*****************************************************************************//**
* \brief   - Return TestResult object pointer
*
* \param   - None
*
* \return  - TestResult object pointer
******************************************************************************/
TestResult *PeerInfo::GetTestResultObjPtr()
{
    return m_ptrTestResult;
}
/*****************************************************************************//**
* \brief   - Return TestSignature object pointer
*
* \param   - None
*
* \return  - TestSignature object pointer
******************************************************************************/
TestSignature *PeerInfo::GetTestSignatureObjPtr()
{
    return m_ptrTestSignature;
}
/**************************************************************************//**
* \brief   - Return Horn Scan Result object pointer
*
* \param   - None
*
* \return  - Horn Scan Result object pointer
******************************************************************************/
HornScanResult *PeerInfo::GetHornScanResultObjPtr()
{
    return m_ptrHornScanResult;
}
/**************************************************************************//**
* \brief   - Return Horn Scan Signature object pointer
*
* \param   - None
*
* \return  - Horn Scan Signature object pointer
******************************************************************************/
HornScanSignature *PeerInfo::GetHornScanSignatureObjPtr()
{
    return m_ptrHornScanSignature;
}
/*****************************************************************************//*
* \brief   - Return comm stat object pointer
*
* \param   - None
*
* \return  - comm stat object pointer
******************************************************************************/
comm_stat *PeerInfo::GetCommStatObjPtr()
{
    return m_ptrCommStatObj;
}

/**************************************************************************//**
* \brief   - Return Actuator Setup object pointer
*
* \param   - None
*
* \return  - Actuator Setup object pointer
******************************************************************************/
ActuatorSetup *PeerInfo::GetActuatorSetupObjPtr()
{
    return m_ptrActuatorSetup;
}

/**************************************************************************//**
* \brief   - Return Digital IO object pointer
*
* \param   - None
*
* \return  - Digital IO object pointer
******************************************************************************/
DigitalIOMgr *PeerInfo::GetDigitalIOObjPtr()
{
    return m_ptrDgtUserIO;
}

/**************************************************************************//**
* \brief   - Return Display manager object pointer
*
* \param   - None
*
* \return  - Display manager object pointer
******************************************************************************/
DisplayMgr *PeerInfo::GetDispMgrObjPtr()
{
    return m_ptrDispMgrObj;
}

/**************************************************************************//**
* \brief   - Return User Management object pointer
*
* \param   - None
*
* \return  - User Management object pointer
******************************************************************************/
UserManagement *PeerInfo::GetUserManagementObjPtr()
{
    return m_ptrUserManagementObj;
}

/**************************************************************************//**
* \brief   - Return Global User Settings object pointer
*
* \param   - None
*
* \return  - Global User Settings object pointer
******************************************************************************/
GlobalUserSetting *PeerInfo::GetGlobalUserSettingsObjPtr()
{
    return m_ptrGlobalUserSettingsObj;
}

/**************************************************************************//**
* \brief   - Return System Configuration object pointer
*
* \param   - None
*
* \return  - System Configuration object pointer
******************************************************************************/
SystemConfigurationGeneral_MB *PeerInfo::GetSystemConfigObjPtr()
{
    return m_ptrSystemConfiguration;
}

/**************************************************************************//**
* \brief   - Return Data Logger object pointer
*
* \param   - None
*
* \return  - Data Logger object pointer
******************************************************************************/
DataLogger *PeerInfo::GetDataLoggerObjPtr()
{
    return m_ptrDataLogger;
}

/**************************************************************************//**
* \brief   - Return Service Management object pointer
*
* \param   - None
*
* \return  - Service Management object pointer
******************************************************************************/
ServiceManagement *PeerInfo::GetServiceManagementObjPtr()
{
    return m_ptrServiceManagementObj;
}

/**************************************************************************//**
* \brief   - Return Branson System Configuration object pointer
*
* \param   - None
*
* \return  - Branson System Configuration object pointer
******************************************************************************/
SystemConfigBransonService *PeerInfo::GetSystemConfigBransonServiceObjPtr()
{
    return m_systemConfigBransonServiceObj;
}

/**************************************************************************//**
* \brief   - Return System Information object pointer
*
* \param   - None
*
* \return  - System Information object pointer
******************************************************************************/
SystemInformation *PeerInfo::GetSystemInformationObjPtr()
{
    return m_systemInformationObj;
}

/**************************************************************************//**
* \brief   - Return calibration object pointer
*
* \param   - None
*
* \return  - calibration object pointer
******************************************************************************/
CalibrationAce *PeerInfo::GetCalibrationAceObjPtr()
{
    return m_CalibrationAceObj;
}

/**************************************************************************//**
* \brief   - Return Network Configuration object pointer
*
* \param   - None
*
* \return  - Network Configuration object pointer
******************************************************************************/
NetworkConfiguration *PeerInfo::GetNetworkConfigObjPtr()
{
    return m_NetworkConfigurationObj;
}

/**************************************************************************//**
* \brief   - Return NetworkConfigurationEthernetIp object pointer
*
* \param   - None
*
* \return  - NetworkConfigurationEthernetIp object pointer
******************************************************************************/
NetworkConfigurationEthernetIp *PeerInfo::GetNetworkConfigurationEthernetIp()
{
    return m_NetworkConfigurationEthernetIp;
}

/**************************************************************************//**
* \brief   - Return BransonServiceTab object pointer
*
* \param   - None
*
* \return  - BransonServiceTab object pointer
******************************************************************************/
BransonServiceTab *PeerInfo::GetBransonServiceTabObjPtr()
{
    return m_BransonServiceTabObj;
}

/**************************************************************************//**
* \brief   - Return DateTimeConversion object pointer
*
* \param   - None
*
* \return  - DateTimeConversion object pointer
******************************************************************************/
DateTimeConversion *PeerInfo::GetDateTimeConversionObjPtr()
{
    return m_DateTimeConversionObj;
}

/**************************************************************************//**
* \brief   - Return software upgrade object pointer
*
* \param   - None
*
* \return  - software upgrade object pointer
******************************************************************************/
SoftwareUpgrade *PeerInfo::GetSoftwareUpgradeObjPtr()
{
    return m_SoftwareUpgradeObj;
}

/**************************************************************************//**
* \brief   - Return report manager object pointer
*
* \param   - None
*
* \return  - Report Manager Object Pointer
******************************************************************************/
ReportManager *PeerInfo::GetReportManagerObjPtr()
{
    return m_ReportManagerPtrObj;
}

/**************************************************************************//**
* \brief   - Return USB streaming object pointer
*
* \param   - None
*
* \return  - System Configuration object pointer
******************************************************************************/
USBStreaming *PeerInfo::GetUsbStreamObjPtr()
{
    return m_ptrUSBStream;
}

/**************************************************************************//**
* \brief   - Return Config Utility Version object pointer
*
* \param   - None
*
* \return  - Config Utility Version object pointer
******************************************************************************/
ConfigUtilityVersion *PeerInfo::GetConfigUtilityVersionObjPtr()
{
    return m_ptrConfigUtilityVersion;
}

/**************************************************************************//**
* \brief   - Return FieldBus IO(control/status words) object pointer
*
* \param   - None
*
* \return  - FieldBus IO(control/status words) object pointer
******************************************************************************/
FieldBusIOMgr *PeerInfo::GetFieldBusIOObjPtr()
{
    return m_ptrFieldBusCustomIO;
}
/**************************************************************************//**
* \brief   - Return nfs manager object pointer
*
* \param   - None
*
* \return  - nfs Manager Object Pointer
******************************************************************************/
NfsManager *PeerInfo::GetNfsManagerObjPtr()
{
    return m_NfsManagerPtr;
}

/**************************************************************************//**
* \brief   - Return Profinet Settings object pointer
*
* \param   - None
*
* \return  - Profinet Settings object pointer
******************************************************************************/
ProfinetSetting *PeerInfo::GetProfinetSettingsObjPtr()
{
    return m_ptrProfinetSettings;
}

/**************************************************************************//**
* \brief   - Return USB Authentication object pointer
*
* \param   - None
*
* \return  - System Configuration object pointer
******************************************************************************/
USBAuthentication *PeerInfo::GetUsbAuthenticationObjPtr()
{
    return m_ptrUSBAuthentication;
}
/**************************************************************************//**
* \brief   - Return USB Import Export object pointer
*
* \param   - None
*
* \return  - USB Import Export object pointer
******************************************************************************/
ImportExport *PeerInfo::GetImportExportPtr()
{
    return m_ptrImportExport;
}
/**************************************************************************//**
* \brief   - Return Opcua Client Certifcate upload object pointer
*
* \param   - None
*
* \return  - Opcua Client Certificate object pointer
******************************************************************************/
OpcuaClientCertificateUpload *PeerInfo::GetOpcuaClientCertificateUploadObjPtr()
{
    return m_OpcuaClientCertificateUploadObj;
}

/**************************************************************************//**
* \brief   - Delete semaphore
*
* \param   - None
*
* \return  - None
******************************************************************************/
PeerInfo::~PeerInfo()
{
    // Delete semaphore of cyclic activity
    if(sem_destroy(&m_ThreadCyclicActivitySem) == -1)
    {
        snprintf(m_LogBuffer,buff_size_config,"CyclicActivity sem_destroy fail");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
    }

    // delete semaphore of start request
    if(sem_destroy(&m_StartRequestSem) == -1)
    {
        snprintf(m_LogBuffer,buff_size_config,"StartRequest sem_destroy failed");
        //Log with Severity: LOG_ALARM
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
    }

    delete m_ActiveConfig;
    delete m_ptrCommStatObj;
    delete m_ptrWeldRecipe;
    delete m_ptrWeldResult;
    delete m_ptrWeldSignature;
    delete m_ptrRefWeldSignature;
    delete m_ptrSeekResult;
    delete m_ptrSeekSignature;
    delete m_ptrEventLog;
    delete m_ptrAlarmMgr;
    delete m_ptrTestResult;
    delete m_ptrTestSignature;
    delete m_ptrHornScanResult;
    delete m_ptrHornScanSignature;
    delete m_ptrDgtUserIO;
    delete m_ptrDispMgrObj;
    delete m_ptrActuatorSetup;
    delete m_ptrUserManagementObj;
    delete m_ptrGlobalUserSettingsObj;
    delete m_ptrSystemConfiguration;
    delete m_ptrDataLogger;
    delete m_ptrServiceManagementObj;
    delete m_systemConfigBransonServiceObj;
    delete m_systemInformationObj;
    delete m_CalibrationAceObj;
    delete m_NetworkConfigurationObj;
    delete m_BransonServiceTabObj;
    delete m_DateTimeConversionObj;
    delete m_SoftwareUpgradeObj;
    delete m_ReportManagerPtrObj;
    delete m_ptrUSBStream;
    delete m_ptrFieldBusCustomIO;
    delete m_ptrConfigUtilityVersion;
	delete m_ptrProfinetSettings;
	delete m_NetworkConfigurationEthernetIp;
	delete m_NfsManagerPtr;
	delete m_ptrUSBAuthentication;
	delete m_ptrImportExport;
	delete m_OpcuaClientCertificateUploadObj;
}

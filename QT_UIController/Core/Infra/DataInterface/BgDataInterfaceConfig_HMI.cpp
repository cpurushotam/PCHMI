/**************************************************************************

		Copyright (c) Branson Ultrasonics Corporation, 1996-2024
		
		This program is the property of Branson Ultrasonics Corporation
		Copying of this software is expressly forbidden, without the prior
		written consent of Branson Ultrasonics Corporation.
		
---------------------------- MODULE DESCRIPTION ----------------------------
	This file includes memory block configuration for background communication.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 18/01/2024 - Initial version.
 
 ***************************************************************************/
#include "BgDataInterfaceConfig_HMI.h"
#include "CommPeerWrapper.h"
#include "WeldRecipeAce.h"
#include "OpcuaClientCertificateStructure.h"
/**************************************************************************//**
*
* \brief  - Create new memory block and insert into maps
*
* \param  - int             welder id
*
* \return - None.
*
******************************************************************************/
BgDataInterfaceConfig_HMI::BgDataInterfaceConfig_HMI(int PeerId)
{
    m_BgCommDataIntrConfig =
    {
        // TX frame configuration - used for preparing Background TX frame by reading MB from DataInterface
        .TXConfig =
        {
            {{MB_ID_COMM_STAT,SUB_ID_OWN_STAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCommStatObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,ACTIVE_WELD_RECIPE_DATA},dynamic_cast< DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_CARD_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_AMPLITUDE_STEP_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_PRESSURE_STEP_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
			{{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_CREATE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_DELETE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_PARAMETER_UPDATE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,SET_WELD_RECIPE_AS_ACTIVE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_COPY},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_RECALL},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
			{{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,READ_HISTORICAL_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,READ_WELD_SIGNATURE_CONFIG},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,UPDATE_AUTO_SAVE_GRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,UPDATE_GRAPH_SAMPLING_INTERVAL},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,READ_REQUESTED_WELD_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_SEEK_RESULT_DATA,SEEK_RUN_OPERATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekResultObjPtr())},
            {{MB_ID_SEEK_RESULT_DATA,SEEK_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekResultObjPtr())},
            {{MB_ID_SEEK_SIGNATURE_DATA,READ_SEEK_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekSignatureObjPtr())},
            {{MB_ID_EVENT_LOG_DATA,READ_HISTORICAL_EVENT_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetEventLogObjPtr())},
            {{MB_ID_ALARM_DATA,READ_HISTORICAL_ALARM_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_TEST_OPERATION,SUB_ID_START_OR_ABORT_OPERATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {{MB_ID_TEST_OPERATION,SUB_ID_SEND_TEST_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {{MB_ID_TEST_OPERATION,SUB_ID_SEND_TEST_PROGRESS_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {{MB_ID_TEST_SIGNATURE_DATA,SUB_ID_SEND_TEST_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestSignatureObjPtr())},
            {{MB_ID_HORN_SCAN_RESULT_DATA,READ_HISTORICAL_HORN_SCAN_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {{MB_ID_HORN_SCAN_RESULT_DATA,START_HORN_SCAN_OPERATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
			{{MB_ID_HORN_SCAN_RESULT_DATA,ABORT_HORN_SCAN_OPERATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {{MB_ID_HORN_SCAN_SIGNATURE_DATA,READ_REQUESTED_HORN_SCAN_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanSignatureObjPtr())},
            {{MB_ID_ALARM_DATA,READ_ACTIVE_ALARM_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,RESET_ACTIVE_ALARM},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,RESET_ALL_ACTIVE_ALARMS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ACTUATOR_SETUP_DATA,READ_ACTUATOR_SETUP_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_ACTUATOR_SETUP_DATA,ENTER_LEAVE_ACTUATOR_SETUP_SCREEN},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_ACTUATOR_SETUP_DATA,SELECT_ACTUATOR_SETUP_OPEARTION_TYPE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_ACTUATOR_SETUP_DATA,INITIATE_ACTUATOR_SETUP_HORN_RETRACT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_ACTUATOR_SETUP_DATA,ACTUATOR_SETUP_HORN_CLAMP_ON_OFF},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,SAVE_DIGITAL_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,DIGITAL_USER_IO_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,READ_DIGITAL_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,SAVE_ANALOG_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,ANALOG_USER_IO_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,READ_ANALOG_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
			//Fieldbus IO(Control/Status Words)
            {{MB_ID_FIELDBUS_USER_IO_DATA,SAVE_FIELDBUS_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetFieldBusIOObjPtr())},
            {{MB_ID_FIELDBUS_USER_IO_DATA,FIELDBUS_USER_IO_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetFieldBusIOObjPtr())},
            {{MB_ID_FIELDBUS_USER_IO_DATA,READ_FIELDBUS_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetFieldBusIOObjPtr())},

            {{MB_ID_ALARM_DATA,ALARM_CONFIG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
			{{MB_ID_ALARM_DATA,ALARM_CONFIG_SAVE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,ALARM_CONFIG_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
			{{MB_ID_ALARM_DATA,ESTOP_ACTIVE_INDICATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,ESTOP_RESET_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
			{{MB_ID_ALARM_DATA,ADD_ALARM_NOTES},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_USER_LIST_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_LOGIN_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_AUTO_LOGIN_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_LOGOUT_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_VERIFY_AND_CHANGE_PASSWORD_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_CHANGE_PASSWORD_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_ADD_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_MODIFY_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_DELETE_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
			{{MB_ID_USER_MANAGEMNT_DATA,MB_USER_PRIVILEGE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
			{{MB_ID_USER_MANAGEMNT_DATA,MB_LDAP_CONFIG_READ_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
			{{MB_ID_USER_MANAGEMNT_DATA,MB_LDAP_CONFIG_UPDATE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_READ_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_UPDATE_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_RESET_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_UPDATE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
			{{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_RESET_TO_DEFAULT_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_KEY_VERIFY_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_READDATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_RESET_BRSNSRVC_KEY},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},

            {{MB_ID_SERVICE_REMINDER_DATA,MB_REMINDER_LIST_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_ADD_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_MODIFY_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_DELETE_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_PAUSE_RESUME_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_RESET_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_SNOOZE_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA,MB_READ_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigBransonServiceObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA,MB_UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigBransonServiceObjPtr())},

            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_WELD_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_GRAPH_DATA_FOR_NAME},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,UPDATE_NAME_FOR_REFERENCE_WELD_GRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,REPLACE_OLD_REFGRAPH_BY_NEW_REFGRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,SEND_DATA_ON_REFERENCEWELDDATA_READ_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},

            {{MB_ID_SYSTEM_INFORMATION_DATA,MB_READ_SYSTEM_INFORMATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemInformationObjPtr())},

            {{MB_ID_CALIBRATION_DATA,SUB_ID_ABORT_CALIBRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_RESET_CALIBRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_START_QUICK_CALIBRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_START_PRESSURE_CALIBRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_START_FORCE_CALIBRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_USER_ENTERED_PRESSURE_1},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_USER_ENTERED_PRESSURE_2},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_USER_ENTERED_PRESSURE_3},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_USER_ENTERED_FORCE_1},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_CALIBRATION_DATA,SUB_ID_USER_ENTERED_FORCE_2},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_READ_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_UPDATE_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_RESET_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},

            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_READ_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},
            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_UPDATE_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},
            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_RESET_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},

            {{MB_ID_PROFINET_NETWORK_SETTINGS_DATA,PROFINET_NETWORK_DATA_READ},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetProfinetSettingsObjPtr())},
            {{MB_ID_PROFINET_NETWORK_SETTINGS_DATA,PROFINET_NETWORK_SETUP_DATA_SAVE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetProfinetSettingsObjPtr())},
            {{MB_ID_PROFINET_NETWORK_SETTINGS_DATA,PROFINET_NETWORK_DATA_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetProfinetSettingsObjPtr())},

            {{MB_ID_BRANSON_SERVICE,FACTORY_RESET_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,DB_DELETE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,DB_COPY_TO_USB_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,BOARD_REPLACED_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,SYSTEM_CLEANED_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,ADD_SERVICE_NOTES_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,READ_SERVICE_LOG},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},

            {{MB_ID_DATE_TIME_CONVERSION,SEND_DATE_TIME_FORMAT_FROM_HMI},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},
            {{MB_ID_DATE_TIME_CONVERSION,SEND_EPOCH_DATETIME_FROM_HMI},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},
            {{MB_ID_DATE_TIME_CONVERSION,GET_DATE_TIME_FORMAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},

            {{MB_ID_SOFTWARE_UPGRADE_DATA,MB_READ_USB_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSoftwareUpgradeObjPtr())},
            {{MB_ID_SOFTWARE_UPGRADE_DATA,MB_UPGRADE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSoftwareUpgradeObjPtr())},
			
			{{MB_ID_REPORT_GENERATION_DATA,REPORT_GENERATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReportManagerObjPtr())},
			{{MB_ID_REPORT_GENERATION_DATA,REPORT_CANCELLATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReportManagerObjPtr())},
			{{MB_ID_REPORT_GENERATION_DATA,REPORT_GENE_PROGRESS_STATUS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReportManagerObjPtr())},
			
			{{MB_ID_USB_STREAM_DATA,STREAM_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbStreamObjPtr())},
			{{MB_ID_USB_STREAM_DATA,STREAM_DATA_SAVE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbStreamObjPtr())},
			
			{{MB_ID_IMPORT_EXPORT_DATA,EXPORT_REFERENCE_GRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,IMPORT_REFERENCE_GRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,EXPORT_RECIPES},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,IMPORT_RECIPES},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,EXPORT_SYSTEM_CONFIGURATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,IMPORT_SYSTEM_CONFIGURATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,EXPORT_SYSTEM_BACKUP},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,IMPORT_SYSTEM_BACKUP},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,STORAGE_DEVICE_SELECTION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},

            {{MB_ID_CONFIG_UTILITY_VERSION_DATA,CONFIG_UTILITY_VERSION_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetConfigUtilityVersionObjPtr())},
			{{MB_ID_NFS_CONFIGURATION_DATA,NFS_MOUNT_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNfsManagerObjPtr())},
			
			{{MB_ID_USB_AUTHENTICATION_DATA,USB_DEVICE_REGISTRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
			{{MB_ID_USB_AUTHENTICATION_DATA,READ_USB_DEVICES_REGISTERED},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
			{{MB_ID_USB_AUTHENTICATION_DATA,USB_DEVICE_DEREGISTRATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
			{{MB_ID_USB_AUTHENTICATION_DATA,READ_USB_CONNECT_AUTHENTICATION_STATUS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},            
            
			{{MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA,MB_READ_OPCUA_CERTIFICATE_FROM_USB_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},
			{{MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA,MB_COPY_OPCUA_CERTIFICATE_USB_EMMC_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},
			{{MB_ID_OPCUA_PUBSUB_DATA,MB_READ_OPCUA_PUBSUB_IP_PORT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},
			{{MB_ID_OPCUA_PUBSUB_DATA,MB_WRITE_OPCUA_PUBSUB_IP_PORT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},

            },

        // RX frame configuration - used for processing Background RX frame by writing MB to DataInterface
        .RXConfig =
        {
            {{MB_ID_COMM_STAT,SUB_ID_PEER_STAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCommStatObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,ACTIVE_WELD_RECIPE_DATA},dynamic_cast< DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_CARD_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RECIPE_DATA,WELD_RECIPE_CHANGE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
			{{MB_ID_WELD_RECIPE_DATA,SYNCH_WELD_RECIPE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,READ_HISTORICAL_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,READ_HISTORICAL_WELD_RESULT_DATA_FOR_CYCLE_NUMBER},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,READ_LAST_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,SYNCH_HISTORICAL_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_RESULT_DATA,SYNCH_HISTORICAL_WELDRESULT_DATA_ON_DATETIME_FORMAT_CHANGE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,READ_WELD_SIGNATURE_CONFIG},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_WELD_SIGNATURE_DATA,READ_REQUESTED_WELD_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {{MB_ID_SEEK_RESULT_DATA,SEEK_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekResultObjPtr())},
            {{MB_ID_SEEK_RESULT_DATA,SYNC_SEEK_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekResultObjPtr())},
            {{MB_ID_SEEK_SIGNATURE_DATA,READ_SEEK_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekSignatureObjPtr())},
            {{MB_ID_EVENT_LOG_DATA,READ_HISTORICAL_EVENT_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetEventLogObjPtr())},
            {{MB_ID_EVENT_LOG_DATA,READ_LAST_EVENT_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetEventLogObjPtr())},
            {{MB_ID_EVENT_LOG_DATA,SYNC_EVENTLOG_DATA_ON_DATETIME_FORMAT_CHANGE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetEventLogObjPtr())},
			{{MB_ID_ALARM_DATA,READ_HISTORICAL_ALARM_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,READ_LAST_ALARM_LOG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,SYNCH_ALARMSLOG_ON_DATETIME_FORMAT_CHANGE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_TEST_OPERATION,SUB_ID_SEND_TEST_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {{MB_ID_TEST_OPERATION,SUB_ID_SEND_TEST_PROGRESS_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {{MB_ID_TEST_SIGNATURE_DATA,SUB_ID_SEND_TEST_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestSignatureObjPtr())},
            {{MB_ID_HORN_SCAN_RESULT_DATA,READ_HISTORICAL_HORN_SCAN_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {{MB_ID_HORN_SCAN_RESULT_DATA,READ_LAST_HORN_SCAN_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {{MB_ID_HORN_SCAN_RESULT_DATA,SYNC_HORN_SCAN_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {{MB_ID_HORN_SCAN_SIGNATURE_DATA,READ_REQUESTED_HORN_SCAN_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanSignatureObjPtr())},
            {{MB_ID_ALARM_DATA,READ_ACTIVE_ALARM_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,RESET_ACTIVE_ALARM},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,RESET_ALL_ACTIVE_ALARMS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,READ_DIGITAL_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {{MB_ID_DIGITAL_USER_IO_DATA,READ_ANALOG_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
			//Fieldbus IO(Control/Status Words)
            {{MB_ID_FIELDBUS_USER_IO_DATA,READ_FIELDBUS_USER_IO_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetFieldBusIOObjPtr())},

			{{MB_ID_ACTUATOR_SETUP_DATA,READ_ACTUATOR_SETUP_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
			{{MB_ID_ACTUATOR_SETUP_DATA,SYNCH_ACTUATOR_SETUP_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {{MB_ID_ALARM_DATA,ALARM_CONFIG_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,ALARM_CONFIG_UPDATE_RESULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,ESTOP_ACTIVE_INDICATION},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,ESTOP_RESET_RESPONSE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
			{{MB_ID_ALARM_DATA,ADD_ALARM_NOTES},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_ALARM_DATA,HORN_CLAMP_ON_ALARM_STATUS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_USER_LIST_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_LOGIN_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_LOGOUT_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_VERIFY_AND_CHANGE_PASSWORD_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_CHANGE_PASSWORD_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_ADD_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_MODIFY_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_DELETE_USER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
			{{MB_ID_USER_MANAGEMNT_DATA,MB_USER_PRIVILEGE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_PASSWORD_OVERRIDE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_USER_MANAGEMNT_DATA,MB_SYNC_USER_LIST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
			{{MB_ID_USER_MANAGEMNT_DATA,MB_LDAP_CONFIG_READ_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_READ_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},            
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_UPDATE_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {{MB_ID_GLOBAL_USER_SETTINGS_DATA,MB_RESET_GLOBAL_USER_SETTINGS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_READDATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
			{{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_RESULT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_GENERAL_DATA,SUB_ID_SYSTEM_CONFIG_GEN_KEY_VERIFY_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {{MB_ID_LOGGER_DATA,READ_LOGGER_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDataLoggerObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_REMINDER_LIST_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_ADD_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_MODIFY_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_DELETE_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_PAUSE_RESUME_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_RESET_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,MB_SNOOZE_REMINDER_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SERVICE_REMINDER_DATA,SYNCH_SERVICE_REMIDER_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA,MB_READ_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigBransonServiceObjPtr())},
            {{MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA,MB_UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigBransonServiceObjPtr())},

            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_WELD_SIGNATURE_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_WELD_RESULT_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,READ_REFERENCE_GRAPH_DATA_FOR_NAME},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {{MB_ID_REFERENCE_WELD_DATA,REPLACE_OLD_REFGRAPH_BY_NEW_REFGRAPH},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},

            {{MB_ID_DISPLAY_MANAGEMNT_DATA,SUB_ID_DISPLAY_MODE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDispMgrObjPtr())},
            {{MB_ID_DISPLAY_MANAGEMNT_DATA,SUB_ID_FIELDBUS_TOKEN_STATUS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDispMgrObjPtr())},

            {{MB_ID_SYSTEM_INFORMATION_DATA,MB_READ_SYSTEM_INFORMATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemInformationObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_READ_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_UPDATE_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},
            {{MB_ID_NETWORK_CONFIGURATION_DATA,MB_RESET_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},

            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_READ_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},
            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_UPDATE_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},
            {{MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,MB_RESET_NETWORK_CONFIGURATION_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},

            {{MB_ID_PROFINET_NETWORK_SETTINGS_DATA,PROFINET_NETWORK_DATA_READ},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetProfinetSettingsObjPtr())},

            {{MB_ID_BRANSON_SERVICE,EMMC_MEMORY_USAGE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,SEND_REQUEST_STATUS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,READ_SERVICE_LOG},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {{MB_ID_BRANSON_SERVICE,SYNC_SERVICE_LOG},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},

            {{MB_ID_SOFTWARE_UPGRADE_DATA,MB_READ_USB_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSoftwareUpgradeObjPtr())},
            {{MB_ID_SOFTWARE_UPGRADE_DATA,MB_UPGRADE_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSoftwareUpgradeObjPtr())},

            {{MB_ID_DATE_TIME_CONVERSION,GET_DATE_TIME_FORMAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},
            
			{{MB_ID_CALIBRATION_DATA,SUB_ID_CALIBRATION_PART_CONTACT_FOUND},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
			
			{{MB_ID_REPORT_GENERATION_DATA,REPORT_GENE_PROGRESS_STATUS_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReportManagerObjPtr())},

			{{MB_ID_USB_STREAM_DATA,STREAM_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbStreamObjPtr())},
			
			{{MB_ID_IMPORT_EXPORT_DATA,READ_REFERENCE_GRAPH_NAME_FROM_SYSTEM},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,READ_REFERENCE_GRAPH_NAMES_FROM_IMPORT_EXPORT_INTERFACE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,READ_RECIPE_NAME_FROM_SYSTEM},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,READ_RECIPE_NAMES_FROM_IMPORT_EXPORT_INTERFACE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			{{MB_ID_IMPORT_EXPORT_DATA,READ_SYSTEM_CONFIGURATION_FILES_FROM_IMPORT_EXPORT_INTERFACE},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetImportExportPtr())},
			
						
			{{MB_ID_CONFIG_UTILITY_VERSION_DATA,CONFIG_UTILITY_VERSION_DATA},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetConfigUtilityVersionObjPtr())},
			
			{{MB_ID_USB_AUTHENTICATION_DATA,READ_USB_DEVICES_REGISTERED},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
			{{MB_ID_USB_AUTHENTICATION_DATA,READ_USB_CONNECT_AUTHENTICATION_STATUS},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
			
            {{MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA,MB_READ_OPCUA_CERTIFICATE_FROM_USB_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},
			{{MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA,MB_COPY_OPCUA_CERTIFICATE_USB_EMMC_REQUEST},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},
			{{MB_ID_OPCUA_PUBSUB_DATA,MB_READ_OPCUA_PUBSUB_IP_PORT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetOpcuaClientCertificateUploadObjPtr())},

        }
    };
}

/**************************************************************************//**
*
* \brief  - Clean up activity - delete all memory blocks and clear maps
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
BgDataInterfaceConfig_HMI::~BgDataInterfaceConfig_HMI()
{
    m_BgCommDataIntrConfig.TXConfig.clear();
    m_BgCommDataIntrConfig.RXConfig.clear();
}

/**************************************************************************//**
*
* \brief  - This function returns Tx/Rx frame configuration map done by
*           structure CommDataConfig_HMI for background comm.
*
* \param  - None
*
* \return - CommDataConfig : Data Interface configuration for background comm.
*
******************************************************************************/
CommDataConfig *BgDataInterfaceConfig_HMI::GetBgCommDataIntrConfig()
{
    return &m_BgCommDataIntrConfig;
}

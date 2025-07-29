/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Data access interface identifiers. 

--------------------------- REVISION HISTORY ------------------------------

 rev1: 19/05/2023 - Initial implementation
 rev2: 05/06/2023 - Added MB ID for Production screen

***************************************************************************/
#ifndef DATAINTERFACE_ID_H_
#define DATAINTERFACE_ID_H_

// Data Interface ID declarations
typedef enum
{
	MB_ID_COMM_STAT=1,
	MB_ID_PRODUCTION_DATA,
	MB_ID_WELD_RESULT_DATA,
	MB_ID_WELD_SIGNATURE_DATA,
	MB_ID_WELD_RECIPE_DATA,
	MB_ID_SEEK_RECIPE_DATA,
	MB_ID_TEST_RECIPE_DATA,
	MB_ID_HORN_SCAN_DATA,  /* Memory Block ID for Horn Scan recipe */
    MB_ID_PLATFORM_CONFIG,
    MB_ID_SYSTEM_CONFIG_GENERAL_DATA,
	MB_ID_EVENT_LOG_DATA,
	MB_ID_ALARM_DATA,
	MB_ID_SEEK_RESULT_DATA,
    MB_ID_SEEK_SIGNATURE_DATA,
    MB_ID_TEST_OPERATION,
    MB_ID_TEST_SIGNATURE_DATA,
    MB_ID_HORN_SCAN_RESULT_DATA,
    MB_ID_HORN_SCAN_SIGNATURE_DATA,
    MB_ID_ACTUATOR_SETUP_DATA,
	MB_ID_DIGITAL_USER_IO_DATA,
	MB_ID_USER_MANAGEMNT_DATA,
	MB_ID_GLOBAL_USER_SETTINGS_DATA,
	MB_ID_LOGGER_DATA,
	MB_ID_SERVICE_REMINDER_DATA,
	MB_ID_DISPLAY_MANAGEMNT_DATA,
	MB_ID_SYSTEM_CONFIG_BRANSON_SERVICE_DATA,
	MB_ID_SYSTEM_INFORMATION_DATA,
	
	MB_ID_REFERENCE_WELD_DATA,
	MB_ID_CALIBRATION_DATA,
    MB_ID_BRANSON_SERVICE,
	MB_ID_SOFTWARE_UPGRADE_DATA,
	MB_ID_DATE_TIME_CONVERSION,
	MB_ID_REPORT_GENERATION_DATA,
	MB_ID_USB_STREAM_DATA,
	MB_ID_FIELDBUS_USER_IO_DATA,
	MB_ID_NETWORK_CONFIGURATION_DATA,
    MB_ID_NETWORK_CONFIGURATION_INDUS_ETHIP_DATA,
	MB_ID_PROFINET_NETWORK_SETTINGS_DATA,
    MB_ID_CONFIG_UTILITY_VERSION_DATA,
    MB_ID_NFS_CONFIGURATION_DATA,
    MB_ID_USB_AUTHENTICATION_DATA,
    MB_ID_IMPORT_EXPORT_DATA,
	MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA,
	MB_ID_OPCUA_PUBSUB_DATA,
}MEMORY_BLOCK_ID;

#endif //DATAINTERFACE_ID_H_

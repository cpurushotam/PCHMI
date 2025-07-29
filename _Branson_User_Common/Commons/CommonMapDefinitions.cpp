/**************************************************************************
      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Common Map definition
 ***************************************************************************/

#include "UserManagementStructure.h"
#include "NetworkConfigStructure.h"
#include "SystemConfigBransonServiceStructure.h"
#include "EventLogStructure.h"
#include "AlarmLogStructure.h"
#include "DgtUserIOStructureAce.h"
#include "Common_Definitions.h"
#include "FbUserIOStructureAce.h"
#include "SysConfgGenStructureAce.h"

#include <map>
#include <tuple>
#include <string.h>


//User Management Maps
const std::map <MODIFY_USER_ERROR_CODES , std::string> ModifyUserErrorCodesMap =
{
    {MODIFY_USER_ERROR_UNKNOWN,"Modify User Error Unknown"},
    {MODIFY_USER_SUCCESS,"Modify User Success"},
    {MODIFY_USER_FAIL,"Modify User Fail"},
    {MODIFY_USER_NOT_EXIST_IN_DB,"Modify User Not Exists in Database"},
    {NEED_AT_LEAST_ONE_EXECUTIVE_USER,"Need atleast one executive user"},
    {MODIFY_USER_DONT_HAVE_ACCESS,"Modify User don't Have Access"},
    {MODIFY_PASSWORD_SUCCESS,"Modify Password Success"},
    {MODIFY_PASSWORD_FAIL,"Modify Password Fail"},
    {WRONG_EXISTING_PASSWORD,"Wrong Existing Password"},
    {MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED,"Minimum One Executive Level User Required"},
    {DELETE_USER_SUCCESS,"Delete User Success"},
    {DELETE_USER_FAIL,"Delete User Fail"},
    {CAN_NOT_DELETE_LOGGED_IN_USER,"Cannot Delete Logged In User"},
    {NEED_AT_LEAST_ONE_USER_IN_SYSTEM,"Need At Least One User In System"},
    {DOES_NOT_MEET_PASSWORD_POLICY,"Does not meet password policy"},
    {CURRENT_AND_NEW_PASSWORD_SAME,"Current Password and New Password can not be same"},
};


const std::map <LOGIN_ERROR_CODES , std::string> LoginErrorCodesMap =
{
    {LOGIN_ERROR_UNKNOWN,"Login Error Unknown"},
    {LOGIN_SUCCESS,"Login Success"},
    {INVALID_USER_NAME_OR_PASSWORD,"Invalid Username or Password"},
    {USER_LOCKED,"User Locked"},
    {USER_DISABLED,"User Disabled"},
    {PASSWORD_EXPIRED,"Password Expired"},
    {PASSWORD_WILL_EXPIRE_SOON,"Password will expire soon"},
    {FIRST_TIME_LOGIN,"First time login"},
    {PASSWORD_NOT_EXPIRED,"Password Not Expired"},
    {AUTHORITY_CHECK_DISABLE, "Authortiy Check Disable. Please login using Admin crediantials."},
	{TWO_UNSUCCESSFUL_LOGIN_ATTEMPT,"User will lockout on the next failed login attempt"}
};


const std::map <ADD_USER_ERROR_CODES , std::string> AddUserErrorCodesMap =
    {
        {ADD_USER_ERROR_UNKNOWN,"Add User Error Unknown"},
        {ADD_USER_SUCCESS,"Add User Success"},
        {ADD_USER_FAIL,"Add User Fail"},
        {USER_ALREADY_EXIST,"User Already Exists"},
        {ADD_USER_LIMIT_CROSSED,"Maximum Users Already Exist"},
        {EXECUTIVE_USER_NOT_LOGGED_IN,"Executive User Not Logged In"},
        {ADD_USER_DOES_NOT_MEET_PASSWORD_POLICY,"Does not meet password policy"}
    };


const std::map <USER_LEVEL , std::string> UserLevelStringMap =
    {
        {UNKNOWN_USER_LEVEL,"Unknown User Level"},
        {OPERATOR,"Operator"},
        {TECHNICIAN,"Technician"},
        {SUPERVISOR,"Supervisor"},
        {EXECUTIVE,"Executive"},
};


const std::map <USER_ISLOCKED , std::string> IsUserLockedStringMap =
    {
        {UNLOCKED,"Unlocked"},
        {LOCKED,"Locked"}
};


//Network Configuration Maps
const std::map<ETHERNET_IP_SETUP_STATUS, std::string> EthernetIpStatusStringMap =
 {
     {ETHERNET_STATIC_IP_ENABLED, "Static IP"},
     {ETHERNET_DHCP_CLIENT_ENABLED, "DHCP Client"}
 };


const std::map<INDUSTRIAL_ETHERNET_IP_SETUP_STATUS, std::string> InduEthIpStatusStringMap =
 {
     {INDU_ETHERNET_STATIC_IP_ENABLED, "Static IP"},
     {INDU_ETHERNET_DHCP_CLIENT_ENABLED, "DHCP Client"}
 };


//Common Definitions Map
const std::map <bool , std::string> boolStringTypeName =
{
           {true,"Enable"},
           {false,"Disable"}
};

///System Config Branson Service Map
const std::map <BRANSON_SERVICE_REQUESTS_RESPONSE_CODES , std::string> BransonServiceErrorType =
{
	{FACTORY_RESET_REQUEST_IN_PROGRESS,"Factory Reset In Progress."},
    {FACTORY_RESET_REQUEST_SUCCESSFULL,"Factory Reset Successful."},
    {FACTORY_RESET_REQUEST_FAIL,"Factory Reset Fail"},
    {DB_DELETE_REQUEST_SUCCESS,"Database Delete Successful."},
    {DB_DELETE_REQUEST_FAIL,"Database Delete Fail."},
    {DB_COPY_TO_USB_REQUEST_SUCCESS,"Database Copy to USB success."},
    {DB_COPY_TO_USB_REQUEST_FAIL,"Database Copy to USB Fail"},
    {BOARD_REPLACED_REQUEST_SUCCESS,"Board Replaced Success."},
    {BOARD_REPLACED_REQUEST_FAIL,"Board Replaced Fail."},
    {SYSTEM_CLEANED_REQUEST_SUCCESS,"System Cleaned Success."},
    {SYSTEM_CLEANED_REQUEST_FAIL,"System Cleaned Fail."},
    {SERVICE_UNKNOWN_ERROR,"Service Unknown Error."}

};


//Alaram Log Map
const std::map<ALARMNAMEENUM, std::string> AlarmActionsStringMap = {
    {NO_CYCLE_RESET, "NoCycle Reset Required"},
    {NO_CYCLE_LOG, "NoCycle Log Alarm"},
    {NO_CYCLE_ALARM, "NoCycle General Alarm"},
    {NO_CYCLE_CUSTOM, "NoCycle Custom AlarmOutput"},
    {NO_CYCLE_COUNT, "NoCycle Cycle Counter"},
    {HARD_FAIL_RESET, "Hardware Failure Reset Required"},
    {HARD_FAIL_LOG, "Hardware Failure Log Alarm"},
    {HARD_FAIL_ALARM, "Hardware Failure General Alarm"},
    {HARD_FAIL_CUSTOM, "Hardware Failure Custom AlarmOutput"},
    {HARD_FAIL_COUNT, "Hardware Failure Cycle Counter"},
    {CYCLE_MOD_RESET, "Cycle Modified Reset Required"},
    {CYCLE_MOD_LOG, "Cycle Modified Log Alarm"},
    {CYCLE_MOD_ALARM, "Cycle Modified General Alarm"},
    {CYCLE_MOD_CUSTOM, "Cycle Modified Custom AlarmOutput"},
    {CYCLE_MOD_COUNT, "Cycle Modified Cycle Counter"},
    {REJECT_RESET, "Reject Reset Required"},
    {REJECT_LOG, "Reject Log Alarm"},
    {REJECT_ALARM, "Reject General Alarm"},
    {REJECT_CUSTOM, "Reject Custom AlarmOutput"},
    {REJECT_COUNT, "Reject Cycle Counter"},
    {WARN_RESET, "Warning Reset Required"},
    {WARN_LOG, "Warning Log Alarm"},
    {WARN_ALARM, "Warning General Alarm"},
    {WARN_CUSTOM, "Warning Custom AlarmOutput"},
    {WARN_COUNT, "Warning Cycle Counter"},
    {OVERLOAD_RESET, "Overload Reset Required"},
    {OVERLOAD_LOG, "Overload Log Alarm"},
    {OVERLOAD_GALARM, "Overload General Alarm"},
    {OVERLOAD_CUSTOM, "Overload Custom AlarmOutput"},
    {OVERLOAD_COUNT, "Overload Cycle Counter"},
    {NO_CYCLE_OVER_RESET, "NoCycle Overload Reset Required"},
    {NO_CYCLE_OVER_LOG, "NoCycle Overload Log Alarm"},
    {NO_CYCLE_OVER_ALARM, "NoCycle Overload General Alarm"},
    {NO_CYCLE_OVER_CUSTOM, "NoCycle Overload Custom AlarmOutput"},
    {NO_CYCLE_OVER_COUNT, "NoCycle Overload Cycle Counter"},
    {SUSPECT_RESET, "Suspect Reset Required"},
    {SUSPECT_LOG, "Suspect Log Alarm"},
    {SUSPECT_ALARM, "Suspect General Alarm"},
    {SUSPECT_CUSTOM, "Suspect Custom AlarmOutput"},
    {SUSPECT_COUNT, "Suspect Cycle Counter"}
};

//Event Log Map
const std::map <EVENT_IDS , std::string> EventTypeName =
{
           {EVENT_NONE,"None"},
           {ESTOP_RELEASE,"Estop Release"},
           {ESTOP_PRESS,"Estop Press"},
           {USER_LOGIN,"Login"},
           {USER_LOGOUT,"Logout"},
           {USER_CREATED,"User Create"},
           {USER_MODIFIED,"User Modify"},
           {HORN_SCAN_COMPLETED,"HornScan Complete"},
           {SEEK_PERFORM,"Seek"},
           {PART_CONTACT_PERFORM,"Part Contact"},
           {CALIBRATION_COMPLETED,"Calibration Complete"},
           {RECIPE_CREATED,"Recipe Create"},
           {RECIPE_DELETED,"Recipe Delete"},
           {RECIPE_SAVED,"Recipe Save"},
           {RECIPE_COPIED,"Recipe Copy"},
           {RECIPE_MODIFIED,"Weld Recipe Modify"},
           {RECIPE_VALIDATION,"Recipe Validation"},
		   {RECIPE_RESET, "Weld Recipe Reset"},
           {CYCLE_COUNT_RESET,"Cycle Count"},
		   {HORN_SCAN_RECIPE_MODIFIED,"Scan Recipe Modify"},
		   {HORN_SCAN_RECIPE_RESET,"Scan Recipe Reset"},
		   {SEEK_RECIPE_MODIFIED,"Seek Recipe Modify"},
		   {SEEK_RECIPE_RESET,"Seek Recipe Reset"},
		   {TEST_RECIPE_MODIFIED,"Test Recipe Modify"},
		   {TEST_RECIPE_RESET,"Test Recipe Reset"},

           {SYSTEM_HW_CHANGED,"System Hardware changed"},
           {SYSTEM_CLEANED,"System Clean"},
           {SYSTEM_FACTORY_RESET,"System Factory Reset"},
           {SYSTEM_TIME_CHANGED,"SystemTime Change"},
           {SYSTEM_CONFIGURATION,"System Configuration"},
           {SYSTEM_DB_DELETED,"System Db Deleted"},
           {SYSTEM_LOG_DELETED,"System Log deleted"},
           {SYSTEM_BATT_LOW,"System Battery Low"},
           {SYSTEM_SW_VER_CHANGE,"System SoftwareVersion Change"},
           {REMINDER_CREATED,"Reminder Create"},
           {REMINDER_MODIFIED,"Reminder Modify"},
           {REMINDER_DELETED,"Reminder Deleted"},
		   {GRAPH_SAMPLING_CHANGE,"Graph Sampling Interval Change"},
		   {AUTO_SAVE_GRAPH,"Auto Save Graph"},
		   {CONFIGURATION_UPGRADE,"Configuration Upgrade"}

};

//Dgt User IO Map
const std::map <INPUT_LINE_FUNCTION , std::string> UserInputEventName =
{
        {INPUT_FUNCTION_NONE,"Not Used"},
        {INPUT_DISABLE,"Input Disable"},
        {IN_ULTRASONIC_SONIC_DISABLE,"UltraSonic disable"},
        {IN_CABLE_DETECT,"Cable Detect"},
        {IN_DISPLAY_LOCK,"Display Lock"},
        {IN_CYCLE_ABORT,"Cycle Abort"},
        {IN_ALARM_RESET,"Alarm Reset"},
        {IN_ULTRASONIC_DELAY,"Ultrasonic delay"},
        {IN_HOLD_DELAY,"Hold Delay"},
        {IN_LOAD_RECIPE,"Load Recipe"},
        {EXT_TOOLING_INPUT,"Tooling input"},
        {IN_HORN_SCAN,"Horn Scan"},
        {IN_HORN_SEEK,"Horn Seek"},
        {IN_HORN_TEST,"Horn Test"},
        {IN_MEMORY_CLEAR,"Memory clear"},
		{PART_PRESENT_INPUT, "Part Present input"},
        {IN_ESTOP_RESET,"Estop Reset"},
        {RECIPE_1,"Recipe bit 1"},
        {RECIPE_2,"Recipe bit 2"},
        {RECIPE_4,"Recipe bit 4"},
        {RECIPE_8,"Recipe bit 8"},
		{EXTERNAL_AMPLITUDE_TRIGGER_1,"External Amplitude Trigger 1"},
		{EXTERNAL_AMPLITUDE_TRIGGER_2,"External Amplitude Trigger 2"},
		{EXTERNAL_AMPLITUDE_TRIGGER_3,"External Amplitude Trigger 3"}
};

const std::map <OUTPUT_LINE_FUNCTION , std::string> UserOutputEventName =
    {
        {OUTPUT_FUNCTION_NONE,"Not Used"},
        {OUTPUT_DISABLED,"Output Disable"},
        {SYSTEM_READY,"System Ready"},
        {CYCLE_RUNNING,"Cycle Running"},
        {CYCLE_OK,"Cycle Ok"},
        {ULTRASONIC_ACTIVE,"Ultrsonic Active"},
        {SOLENOID_ACTIVE,"Solenoid Active"},
        {ACTUATOR_CLEAR,"Actuator Clear"},
        {AFTERBURST_DELAY,"AfterBurst Delay"},
        {AFTERBURST_TIME,"AfterBurst Time"},
        {PB_RELEASE,"Pb Release"},
        {HOLD_TIME_ACTIVE,"Hold Time Active"},
        {ACTUATOR_HOME,"Actuator Home"},
        {HORN_SEEK,"Horn Seek"},
        {HORN_SCAN,"Horn Scan"},
		{HORN_TEST, "Horn Test"},
        {ALARM_GENERAL,"Alarm General"},
        {ALARM_CUSTOM,"Alarm Custom"},
        {ALARM_REJECT_PART,"Alarm Reject Part"},
        {ALARM_CUTTOFF,"Alarm Cuttoff"},
        {ALARM_OVERLOAD,"Alarm Overload"},
        {EXT_TOOLING_OUTPUT,"Tooling Output"},
        {CONFIRM_RECIPE,"Confirm Recipe"},
		{MEMORY_CLEAR_ACTIVE, "Memory Clear Output"}
};

const std::map <ANALOG_INPUT_LINE_FUNCTION , std::string> UserIOAnalogIpEventName =
{
    {AN_INPUT_FUNCTION_NONE,"Not Used"},
    {AN_INPUT_DISABLE,"Input Disable"},
    {AN_INPUT_AMPLITUDE,"Input Amplitude"},
    {AN_INPUT_FREQUENCY_OFFSET,"Frequency offset"},
    {AN_INPUT_FUNCTION_MAX,"Input Function max"},
};

const std::map <ANALOG_OUTPUT_LINE_FUNCTION , std::string> UserIOAnalogOpEventName =
{
        {AN_OUTPUT_FUNCTION_NONE,"Not Used"},
        {AN_OUTPUT_DISABLE,"Output Disable"},
        {AN_OUTPUT_POWER,"Output Power"},
        {AN_OUTPUT_AMPLITUDE,"Output Amplitude"},
        {AN_OUTPUT_CURRENT,"Output Current"},
        {AN_OUTPUT_FREQUENCY,"Output Frequency"},
        {AN_OUTPUT_FUNCTION_MAX,"Output Function max"},
};

const std::map<DGTUSERIOENUM, std::string> DigitalUserIOStringMap = {
    {DIGITAL_INPUT1, "Digital Input 1"},
    {DIGITAL_INPUT2, "Digital Input 2"},
    {DIGITAL_INPUT3, "Digital Input 3"},
    {DIGITAL_INPUT4, "Digital Input 4"},
    {DIGITAL_INPUT5, "Digital Input 5"},
    {DIGITAL_INPUT6, "Digital Input 6"},
    {DIGITAL_INPUT7, "Digital Input 7"},
    {DIGITAL_INPUT8, "Digital Input 8"},
    {DIGITAL_INPUT9, "Digital Input 9"},
    {DIGITAL_OUTPUT1, "Digital Output 1"},
    {DIGITAL_OUTPUT2, "Digital Output 2"},
    {DIGITAL_OUTPUT3, "Digital Output 3"},
    {DIGITAL_OUTPUT4, "Digital Output 4"},
    {DIGITAL_OUTPUT5, "Digital Output 5"},
    {DIGITAL_OUTPUT6, "Digital Output 6"},
    {DIGITAL_OUTPUT7, "Digital Output 7"},
    {DIGITAL_OUTPUT8, "Digital Output 8"}
};

const std::map<ANALOGUSERIOENUM, std::string> AnalogUserIOStringMap = {
    {ANALOG_INPUT1, "Analog Input 1"},
    {ANALOG_INPUT2, "Analog Input 2"},
    {ANALOG_OUTPUT1, "Analog Output 1"},
    {ANALOG_OUTPUT2, "Analog Output 2"}
};


//Fb User IO Map
const std::map <INPUT_FB_FUNCTION , std::string> UserIOFieldbusIpEventName =
{
    {FB_INPUT_FUNCTION_NONE,"Not Used"},
    {FB_INPUT_DISABLE,"Input Disable"},
    {IN_WELD_MODE, "Weld Mode"},
    {IN_TIME_MODE, "Time Mode"},
    {IN_ENERGY_MODE, "Energy Mode"},
    {IN_PEAK_POWER_MODE, "Peak Power Mode"},
    {IN_GRD_DETECT_MODE, "Ground Detect Mode"},
    {IN_ABS_MODE, "Absolute Distance Mode"},
    {IN_COLLAPSE_MODE, "Collapse Distance Mode"},
    {IN_WELD_AMPLITUDE,"Weld Amplitude"},
    {IN_DOWN_SPEED,"Down Speed"},
    {IN_TRIGGER_FORCE,"Trigger Force"},
    {IN_WELD_PRESSURE,"Weld Pressure"},
    {IN_HOLD_TIME,"Hold Time"},
    {IN_HOLD_PRESSURE,"Hold Pressure"},
    {FB_INPUT_FUNCTION_MAX,"Input Function max"},
};

const std::map <OUTPUT_FB_FUNCTION , std::string> UserIOFieldbusOpEventName =
{
	{FB_OUTPUT_FUNCTION_NONE,"Not Used"},
	{FB_OUTPUT_DISABLED,"Output Disable"},
    {OUT_WELD_MODE, "Weld Mode"},
    {OUT_TIME_MODE, "Time Mode"},
    {OUT_ENERGY_MODE, "Energy Mode"},
    {OUT_PEAK_POWER_MODE, "Peak Power Mode"},
    {OUT_GRD_DETECT_MODE, "Ground Detect Mode"},
    {OUT_ABS_MODE, "Absolute Distance Mode"},
    {OUT_COLLAPSE_MODE, "Collapse Distance Mode"},
    {OUT_WELD_AMPLITUDE,"Weld Amplitude"},
    {OUT_DOWN_SPEED,"Down Speed"},
    {OUT_TRIGGER_FORCE,"Trigger Force"},
    {OUT_WELD_PRESSURE,"Weld Pressure"},
    {OUT_HOLD_TIME,"Hold Time"},
    {OUT_HOLD_PRESSURE,"Hold Pressure"},
	{FB_OUTPUT_FUNCTION_MAX,"Output Function max"},
};

const std::map<FIELDBUSUSERIOENUM, std::string> FieldbusUserIOStringMap = {
    {FIELDBUS_CONTROL_WORD1, "Fieldbus Control Word 1"},
    {FIELDBUS_CONTROL_WORD2, "Fieldbus Control Word 2"},
	{FIELDBUS_CONTROL_WORD3, "Fieldbus Control Word 3"},
    {FIELDBUS_STATUS_WORD1,  "Fieldbus Status Word 1"},
    {FIELDBUS_STATUS_WORD2,  "Fieldbus Status Word 2"},
	{FIELDBUS_STATUS_WORD3,  "Fieldbus Status Word 3"},
};


//Sys Config Gen Map
const std::map <MEMORYFULLACTION , std::string> MemmFullActTypeName =
{
           {CONTINUE,"Off"},
           {STOP,"Basic"}
};

const std::map <UNIT , std::string> UnitTypeName =
{
           {METRIC,"Metric"},
           {IMPERIAL,"Imperial"}
};

const std::map <AUTHORITYCHECK , std::string> AuthorityChkTypeName =
{
           {OFF,"Off"},
           {BASIC,"Basic"}
};

const std::map <POWERUPOPTION , std::string> PowerUpOptTypeName =
{
           {POWER_UP_NONE,"Power Up None"},
           {POWER_UP_SEEK,"Power Up Seek"},
           {POWER_UP_SCAN,"POwer Up Scan"}
};

const std::map<ASC_IP_ADDRESS_FOR_HMI, std::string> ASCIPAddressTypeNameForHMI = {
    {ASC_IP_ADDRESS_192_168_1_100, "192.168.1.100"},
    {ASC_IP_ADDRESS_192_168_1_101, "192.168.1.101"},
    {ASC_IP_ADDRESS_192_168_1_102, "192.168.1.102"},
    {ASC_IP_ADDRESS_192_168_1_103, "192.168.1.103"},
    {ASC_IP_ADDRESS_192_168_1_104, "192.168.1.104"},
    {ASC_IP_ADDRESS_192_168_1_105, "192.168.1.105"},
    {ASC_IP_ADDRESS_192_168_1_106, "192.168.1.106"},
    {ASC_IP_ADDRESS_192_168_1_107, "192.168.1.107"},
    {ASC_IP_ADDRESS_192_168_1_108, "192.168.1.108"},
    {ASC_IP_ADDRESS_192_168_1_109, "192.168.1.109"},
    {ASC_IP_ADDRESS_192_168_1_110, "192.168.1.110"},
    {ASC_IP_ADDRESS_192_168_1_111, "192.168.1.111"},
    {ASC_IP_ADDRESS_192_168_1_112, "192.168.1.112"},
    {ASC_IP_ADDRESS_192_168_1_113, "192.168.1.113"},
    {ASC_IP_ADDRESS_192_168_1_114, "192.168.1.114"},
    {ASC_IP_ADDRESS_192_168_1_115, "192.168.1.115"},
    {ASC_IP_ADDRESS_192_168_1_116, "192.168.1.116"},
    {ASC_IP_ADDRESS_192_168_1_117, "192.168.1.117"},
    {ASC_IP_ADDRESS_192_168_1_118, "192.168.1.118"},
    {ASC_IP_ADDRESS_192_168_1_119, "192.168.1.119"}
};

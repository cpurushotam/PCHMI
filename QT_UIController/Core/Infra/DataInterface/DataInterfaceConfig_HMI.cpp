/**************************************************************************

		Copyright (c) Branson Ultrasonics Corporation, 1996-2023
		
		This program is the property of Branson Ultrasonics Corporation
		Copying of this software is expressly forbidden, without the prior
		written consent of Branson Ultrasonics Corporation.
		
---------------------------- MODULE DESCRIPTION ----------------------------
	This file includes memory block configuration.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 22/05/2023 - Initial version.
 rev2: 20/10/2023 - Active configuration parameter of constructor and
                    MB implementation for PlatformConfig.
 ***************************************************************************/
#include "DataInterfaceConfig_HMI.h"
#include "WeldRecipeAce.h"
#include "WeldResultAce.h"
#include "SeekRecipe.h"
#include "TestRecipe.h"
#include "HornScanRecipe.h"
#include "CommPeerWrapper.h"
#include "TestResult.h"
#include "SystemConfigurationGeneral_MB.h"
#include "IOManager.h"
#include "DataLoggerManager.h"

/**************************************************************************//**
*
* \brief  - Create new memory block and insert into maps
*
* \param  - int             welder id
*           ActiveConfig*   ActiveConfiguration of respecive welder id
*
* \return - None.
*
******************************************************************************/
DataInterfaceConfig_HMI::DataInterfaceConfig_HMI(int PeerId, ActiveConfig* ActiveConfiguration)
{
     m_PeerId = PeerId;
    prod_screen_object = new ProductionScreen_MB();
    platform_config_object = new PlatformConfig(ActiveConfiguration);
    SeekRecipe *seek_recipe_object = new SeekRecipe();
    TestRecipe *test_recipe_object_HMI = new TestRecipe();
    HornScanRecipe *obj_HornScanRecipe = new HornScanRecipe();
    DigitalIOMgr *obj_DigitalIOMgr = new DigitalIOMgr();

    CommDataConfig_HMI[PeerId] =
    {
        // TX frame configuration - used for preparing TX frame by reading MB from DataInterface
        .TXConfig =
        {
        		 {{MB_ID_COMM_STAT,SUB_ID_OWN_STAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCommStatObjPtr())},
                {{MB_ID_SEEK_RECIPE_DATA,SEEK_RECIPE_DATA},dynamic_cast<DataInterface*>(seek_recipe_object)},
                {{MB_ID_SEEK_RECIPE_DATA,SEEK_RECIPE_SAVE},dynamic_cast<DataInterface*>(seek_recipe_object)},
                {{MB_ID_SEEK_RECIPE_DATA,SEEK_RECIPE_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(seek_recipe_object)},
                {{MB_ID_HORN_SCAN_DATA,HORN_SCAN_RECIPE_DATA},dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
                {{MB_ID_HORN_SCAN_DATA,HORN_SCAN_RECIPE_SAVE},dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
                {{MB_ID_HORN_SCAN_DATA,HORN_SCAN_RECIPE_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
                {{MB_ID_TEST_RECIPE_DATA,TEST_RECIPE_DATA},dynamic_cast<DataInterface*>(test_recipe_object_HMI)},
                {{MB_ID_TEST_RECIPE_DATA,TEST_RECIPE_SAVE},dynamic_cast<DataInterface*>(test_recipe_object_HMI)},
                {{MB_ID_TEST_RECIPE_DATA,TEST_RECIPE_RESET_TO_DEFAULT},dynamic_cast<DataInterface*>(test_recipe_object_HMI)},
                {{MB_ID_PLATFORM_CONFIG,SUB_ID_PLATFORM_CONFIG },dynamic_cast<DataInterface*>(platform_config_object)},
                {{MB_ID_DIGITAL_USER_IO_DATA,READ_DIAGNOSTIC_USERIO_DATA},dynamic_cast<DataInterface*>(obj_DigitalIOMgr)},
                {{MB_ID_DIGITAL_USER_IO_DATA,REFRESH_DIAGNOSTIC_USERIO},dynamic_cast<DataInterface*>(obj_DigitalIOMgr)},

        },
        // RX frame configuration - used for processing RX frame by writing MB to DataInterface
        .RXConfig =
        {
                {{MB_ID_COMM_STAT,SUB_ID_PEER_STAT},dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCommStatObjPtr())},
                {{MB_ID_PRODUCTION_DATA,SUB_ID_DEFAULT},dynamic_cast<DataInterface*>(prod_screen_object)},
                {{MB_ID_SEEK_RECIPE_DATA,SEEK_RECIPE_DATA},dynamic_cast<DataInterface*>(seek_recipe_object)},
                {{MB_ID_SEEK_RECIPE_DATA,SEEK_RECIPE_UPDATE_RESULT},dynamic_cast<DataInterface*>(seek_recipe_object)},
                {{MB_ID_HORN_SCAN_DATA,HORN_SCAN_RECIPE_DATA},dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
                {{MB_ID_HORN_SCAN_DATA,HORN_SCAN_RECIPE_UPDATE_RESULT},dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
                {{MB_ID_TEST_RECIPE_DATA,TEST_RECIPE_DATA},dynamic_cast<DataInterface*>(test_recipe_object_HMI)},
                {{MB_ID_TEST_RECIPE_DATA,TEST_RECIPE_UPDATE_RESULT},dynamic_cast<DataInterface*>(test_recipe_object_HMI)},       
                {{MB_ID_DIGITAL_USER_IO_DATA,READ_DIAGNOSTIC_USERIO_DATA},dynamic_cast<DataInterface*>(obj_DigitalIOMgr)},
                {{MB_ID_PLATFORM_CONFIG,SUB_ID_PLATFORM_CONFIG },dynamic_cast<DataInterface*>(platform_config_object)},
                {{MB_ID_DATE_TIME_CONVERSION,UPDATE_LIVE_DATE_TIME_ON_HMI },dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},

        }
    };

    HMIScreenDataMap[PeerId] =
    {
        .WelderMap  =
        {
            {"Comm_Stat_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCommStatObjPtr())},
            {"Prod_Screen", dynamic_cast<DataInterface*>(prod_screen_object)},
            {"Recipe_Card_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {"Recipe_Lab_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldRecipeObjPtr())},
            {"System_Confg_General_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigObjPtr())},
            {"Anlytics_Graph_Screen_Weld_Result", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {"Analytical_Table_View", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldResultObjPtr())},
            {"Anlytics_Graph_Screen_Weld_Signature", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetWeldSignatureObjPtr())},
            {"Diagnostics_Scan_Result_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanResultObjPtr())},
            {"Diagnostics_Scan_Signature_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetHornScanSignatureObjPtr())},
            {"Diagnostics_Scan_Recipe_Screen", dynamic_cast<DataInterface*>(obj_HornScanRecipe)},
            {"Diagnostics_Seek_Result_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekResultObjPtr())},
            {"Diagnostics_Seek_Signature_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSeekSignatureObjPtr())},
            {"Diagnostics_Seek_Recipe_Screen", dynamic_cast<DataInterface*>(seek_recipe_object)},
            {"Diagnostics_Test_Result_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestResultObjPtr())},
            {"Diagnostics_Test_Signature_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetTestSignatureObjPtr())},
            {"Diagnostics_Test_Recipe_Screen", dynamic_cast<DataInterface*>(test_recipe_object_HMI)},
            {"EventLog_Table_View", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetEventLogObjPtr())},
            {"Alarm_Management_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {"Alarm_Events_Log_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {"Active_Alarm_Events_Log_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetAlarmMgrObjPtr())},
            {"UserIO_Digital_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDigitalIOObjPtr())},
            {"Actuator_Setup_Screens", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetActuatorSetupObjPtr())},
            {"Global_User_Setting_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetGlobalUserSettingsObjPtr())},
            {"Login_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {"System_Config_User_Management", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUserManagementObjPtr())},
            {"Data_Logger_Message", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDataLoggerObjPtr())},
            {"Diagnostic_UserIO_Digital_Screen", dynamic_cast<DataInterface*>(obj_DigitalIOMgr)},
            {"System_Service_Count_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetServiceManagementObjPtr())},
            {"Branson_System_Configuration_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemConfigBransonServiceObjPtr())},
            {"System_Informtaion_Machine_Details_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSystemInformationObjPtr())},
            {"Reference_Weld_Sign_View", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReferenceWeldSignatureObjPtr())},
            {"System_Calibration", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetCalibrationAceObjPtr())},
            {"Branson_Service_Screen", dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetBransonServiceTabObjPtr())},
            {"System_Network_Configuration_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigObjPtr())},
            {"Date_Time_Settings_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDateTimeConversionObjPtr())},
            {"Software_Upgrade_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetSoftwareUpgradeObjPtr())},
            {"Display_Modes_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetDispMgrObjPtr())},
            {"IndustrialEthernet_IO_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetFieldBusIOObjPtr())},
            {"Generate_Report_Single_Summary",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetReportManagerObjPtr())},
            {"System_Network_Configuration_Ind_Eip_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNetworkConfigurationEthernetIp())},
            {"System_Network_Configuration_Profinet_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetProfinetSettingsObjPtr())},
            {"System_Network_Configuration_NFS_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetNfsManagerObjPtr())},
            {"System_Configuration_USBAuthentication_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbAuthenticationObjPtr())},
           	{"Generate_Report_Continous_Summary",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetUsbStreamObjPtr())},            
            {"System_Feature_Screen",dynamic_cast<DataInterface*>(CommPeerWrapper::GetPeerData(PeerId)->GetConfigUtilityVersionObjPtr())},

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
DataInterfaceConfig_HMI::~DataInterfaceConfig_HMI()
{
    CommDataConfig_HMI.erase(m_PeerId);

    HMIScreenDataMap.erase(m_PeerId);
    delete prod_screen_object;
    delete platform_config_object;
}

/**************************************************************************//**
*
* \brief  - GetCommDataConfig function returns Tx/Rx frame configuration
*           map done by structure CommDataConfig_HMI.
*
* \param  - PeerId : ID of active Welder.
*
* \return - CommDataConfig : Communication configuration mapping structure.
*
******************************************************************************/
CommDataConfig *DataInterfaceConfig_HMI::GetCommDataConfig(uint16_t PeerId)
{
    return &CommDataConfig_HMI[PeerId];
}

/**************************************************************************//**
*
* \brief  - GetHMIScreenData function returns screen configuration map done by
*           structure HMIScreenDataMap
*
* \param  - WelderID : ID of welder for which data requested.
*
* \return - HMIScreenData : Structure for screen mapping config details.
*
******************************************************************************/
HMIScreenData DataInterfaceConfig_HMI::GetHMIScreenData(uint16_t WelderID)
{
    return HMIScreenDataMap[WelderID];
}

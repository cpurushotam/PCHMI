/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UpdateScreen.cpp file responsible to update each screen by fetching
    respective MB's contents by emmiting signal.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/05/2023 - Initial version.
***************************************************************************/
#include "UpdateScreens.h"
#include "DataInterfaceConfig_HMI.h"
#include "MultiwelderInterface.h"
/**************************************************************************//**
*
* \brief - Role of the UpdateScreen class constructor is to connect the data
*            update signal received from communication thread to that of slot which
*            fetches the respective updated MB's using getdata.
*
* \param - None.
*
* \return - None.
******************************************************************************/
UpdateScreen::UpdateScreen(QObject *parent) : QObject(parent)
{
}

/**************************************************************************//**
*
* \brief - Below function returns the instance of UpdateScreen class
*
* \param - None.
*
* \return - UpdateScreenObj : Object pointer of UpdateScreen class.
******************************************************************************/
UpdateScreen *UpdateScreen::getInstance()
{
    static UpdateScreen m_Instance;
    return &m_Instance;
}

/**************************************************************************//**
*
* \brief- Role of slotScreenUpdateReceived is :
*            1. To fetch the updated MB's of active screen using getdata.
*            2. Emit the signal with respective screen's data structure.
*
* \param - WeldorId : Id of welder for which update received.
*
* \return - None.
******************************************************************************/
void UpdateScreen::slotScreenUpdateReceived(uint16_t WelderId, DataInterfaceConfig_HMI *m_DataInterfaceConfig_HMI_Obj)
{

    if(ActiveScreen::getInstance()->getCurrentActiveScreen())
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {

            std::string SysConfgGenScreen = "System_Confg_General_Screen";
            DataInterface* ptrSysConfgGenScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfgGenScreen];
            SystemConfigurationGeneral_MB *MySysGenData = reinterpret_cast<SystemConfigurationGeneral_MB *>(ptrSysConfgGenScreen);
            emit UnitChangedScreenUpdated(MySysGenData, WelderId);

            std::string DataLoggerMessage = "Data_Logger_Message";
            DataInterface* ptrDataLoggerScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DataLoggerMessage];
            DataLogger *MyLoggerData = reinterpret_cast<DataLogger *>(ptrDataLoggerScreen);
            emit DataLoggerMessageUpdated(MyLoggerData, WelderId);


            std::string DisplayModesHMIScreen = "Display_Modes_Screen";
            DataInterface* ptrDisplayModesScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DisplayModesHMIScreen];
            DisplayMgr *MyDisplayMgrData = reinterpret_cast<DisplayMgr *>(ptrDisplayModesScreen);
            emit DisplayModeDataUpdated(MyDisplayMgrData, WelderId);
        }
    }
    /*Screen update for Production Screen section*/
    if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::PRODUCTION)
    {

        /*Buffer used for Production Screen data*/
        uint8_t ProductionScreenBuff[sizeof(ProdScreenData) + 10]={0};

        /*MB for Production Screen with ID and sub ID*/
        MEMORY_BLOCK ProductionScreenMB= { MB_ID_PRODUCTION_DATA, SUB_ID_DEFAULT, 0, sizeof(ProductionScreenBuff), ProductionScreenBuff, NULL};

        std::string ProdScreen = "Prod_Screen";

        /*Buffer used for Frame counter data*/
        uint8_t CommStatBuff[10]={0};

        /*MB for communication ststus with ID and sub ID*/
        MEMORY_BLOCK CommStatMB = { MB_ID_COMM_STAT, SUB_ID_PEER_STAT, 0, sizeof(CommStatBuff), CommStatBuff, NULL};

        std::string CommStatScreen = "Comm_Stat_Screen";

        /*DataInterface pointer object to fetch active screen*/
        DataInterface *ptrActiveProdScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[ProdScreen];

        /*Production Screen object pointer*/
        ProdScreenData *PtrProdScreen;

        /*Fetch Production Screen's updated MB*/
        if(ptrActiveProdScreen->GetData(&ProductionScreenMB) >= 0)
        {
            /*Type casting Production Screen buffered data to Production screen data contents*/
            PtrProdScreen = reinterpret_cast<ProdScreenData *>(ProductionScreenBuff);
        }

        /*DataInterface pointer object to fetch active screen*/
        DataInterface *ptrActiveCommStatScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[CommStatScreen];

        /*Fetch updated frame count MB*/
        if(ptrActiveCommStatScreen->GetData(&CommStatMB) >= 0)
        {
            /*Type casting communication status buffered data to frame counts data contents*/
            comm_stat_data *CommData = reinterpret_cast<comm_stat_data *>(CommStatBuff);
            PtrProdScreen->FrameCount = CommData->counter;
        }

        std::string SysConfgGenScreen = "System_Confg_General_Screen";
        DataInterface* ptrSysConfgGenScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfgGenScreen];
        SystemConfigurationGeneral_MB *MySysGenData = reinterpret_cast<SystemConfigurationGeneral_MB *>(ptrSysConfgGenScreen);

        /*Fill the welder ID and emit the screen update signal with production screen data updates*/
        PtrProdScreen->WelderID = WelderId;

        emit ProductionScreenUpdated(PtrProdScreen , MySysGenData);
    }

    /*Screen update for Recipe Cards Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::RECIPES)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string RecipeCardScreen = "Recipe_Card_Screen";
            DataInterface* ptrActiveRecipeCardScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[RecipeCardScreen];
            WeldRecipeACE *MyCommData = reinterpret_cast<WeldRecipeACE *>(ptrActiveRecipeCardScreen);

            emit RecipeCardsScreenUpdated(MyCommData, WelderId);
        }
    }

    /*Screen update for Recipe Lab Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::RECIPES_LAB)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string RecipeLabScreen = "Recipe_Lab_Screen";
            DataInterface* ptrRecipeLabScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[RecipeLabScreen];
            WeldRecipeACE *MyCommData = reinterpret_cast<WeldRecipeACE *>(ptrRecipeLabScreen);
            emit RecipeLabScreenUpdated(MyCommData, WelderId);
        }
    }

    /*Screen update for Actuator Setup screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::ACTUATORSETUP)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string ActuatorSetupScreen = "Actuator_Setup_Screens";
            DataInterface* ptrActuatorSetupScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[ActuatorSetupScreen];
            ActuatorSetupACE *MyCommData1 = reinterpret_cast<ActuatorSetupACE*>(ptrActuatorSetupScreen);

            std::string RecipeLabScreen = "Recipe_Lab_Screen";
            DataInterface* ptrRecipeLabScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[RecipeLabScreen];
            WeldRecipeACE *MyCommData2 = reinterpret_cast<WeldRecipeACE *>(ptrRecipeLabScreen);

            std::string SysConfgGenScreen = "System_Confg_General_Screen";
            DataInterface* ptrSysConfgGenScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfgGenScreen];
            SystemConfigurationGeneral_MB *MyCommData3 = reinterpret_cast<SystemConfigurationGeneral_MB *>(ptrSysConfgGenScreen);

            emit ActuatorSetupScreenUpdated(MyCommData1, MyCommData2, MyCommData3, WelderId);
        }
    }

    /*Screen update for Analytics Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::ANALYTICS)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            if(analyticsFlag)
            {
                std::string AnlyticsGraphScreenWeldSignature = "Anlytics_Graph_Screen_Weld_Signature";
                DataInterface* ptrAnlyticsGraphScreenWeldSignature = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AnlyticsGraphScreenWeldSignature];
                WeldSignatureACE *MyCommData3 = reinterpret_cast<WeldSignatureACE *>(ptrAnlyticsGraphScreenWeldSignature);
                analyticsFlag = false;

                emit AnalyticsSignatureUpdated(MyCommData3, WelderId);
            }

            else
            {
                std::string AnlyticsGraphScreenWeldResult = "Anlytics_Graph_Screen_Weld_Result";
                DataInterface* ptrAnlyticsGraphScreenWeldResult = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AnlyticsGraphScreenWeldResult];
                WeldResultACE *MyCommData = reinterpret_cast<WeldResultACE *>(ptrAnlyticsGraphScreenWeldResult);

                std::string AnlyticsGraphScreenWeldSignature = "Anlytics_Graph_Screen_Weld_Signature";
                DataInterface* ptrAnlyticsGraphScreenWeldSignature = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AnlyticsGraphScreenWeldSignature];
                WeldSignatureACE *MyCommData2 = reinterpret_cast<WeldSignatureACE *>(ptrAnlyticsGraphScreenWeldSignature);
                analyticsFlag = true;

                emit AnalyticsScreenUpdated(MyCommData, MyCommData2, WelderId);

                /*Screen update for Table view under Analytics Screen*/
                std::string AnalyticalTableview = "Analytical_Table_View";
                DataInterface* ptrAnalyticsTabView = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AnalyticalTableview];
                WeldResultACE *MyCommData3 = reinterpret_cast<WeldResultACE *>(ptrAnalyticsTabView);

                emit AnalyticsTableViewUpdated(MyCommData3, WelderId);
            }
        }

        std::string ReferenceWeldSignatureview = "Reference_Weld_Sign_View";
        DataInterface* ptrReferenceWeldSignView = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[ReferenceWeldSignatureview];
        ReferenceWeldSignature *MyCommData1 = reinterpret_cast<ReferenceWeldSignature *>(ptrReferenceWeldSignView);

        emit ReferenceWeldSignatureUpdated(MyCommData1, WelderId);
    }

    /*Screen update for Table view under EventLog Screen*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::DIAGNOSTICS_EVENT)
    {
        std::string EventLogTableview = "EventLog_Table_View";
        DataInterface* ptrEventLogTabView = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[EventLogTableview];
        EventLog *MyCommData = reinterpret_cast<EventLog *>(ptrEventLogTabView);

        emit EventLogTableViewUpdated(MyCommData, WelderId);
    }

    /*Screen update for Alarm Management */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_ALARMMANGEMENT)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string AlarmManagementScreen = "Alarm_Management_Screen";
            DataInterface* ptrAlrmMgmtScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AlarmManagementScreen];
            AlarmMgrACE *MyCommData1 = reinterpret_cast<AlarmMgrACE *>(ptrAlrmMgmtScreen);
            emit AlarmManagementViewUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for UserIO Digital */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string UserIODigitalScreen = "UserIO_Digital_Screen";
            DataInterface* ptrDigitalUserIO = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[UserIODigitalScreen];
            DigitalIOMgr *MyCommData1 = reinterpret_cast<DigitalIOMgr *>(ptrDigitalUserIO);
            emit DigitalUserIOUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for UserIO Analog */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string UserIODigitalScreen = "UserIO_Digital_Screen";
            DataInterface* ptrDigitalUserIO = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[UserIODigitalScreen];
            DigitalIOMgr *MyCommData1 = reinterpret_cast<DigitalIOMgr *>(ptrDigitalUserIO);
            emit DigitalUserIOAnalogUpdated(MyCommData1, WelderId);
        }
    }
    /*Screen update for Industrial User IO */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string IndusEthUserIOScreen = "IndustrialEthernet_IO_Screen";
            DataInterface* ptrIndEthUserIO = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[IndusEthUserIOScreen];
            FieldBusIOMgr *MyCommData1 = reinterpret_cast<FieldBusIOMgr *>(ptrIndEthUserIO);
            emit IndustrialUserIOUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System Network Configuration Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysNetworkConfScreen = "System_Network_Configuration_Screen";
            DataInterface* ptrSysNetworkConfScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysNetworkConfScreen];
            NetworkConfiguration *MyCommData1 = reinterpret_cast<NetworkConfiguration *>(ptrSysNetworkConfScreen);
            emit SysNetworkConfgDataUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System Network Configuration NFS Setup Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION_NFS)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysNetworkConfNfsScreen = "System_Network_Configuration_NFS_Screen";
            DataInterface* ptrSysNetworkConfScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysNetworkConfNfsScreen];
            NfsManager *MyCommData1 = reinterpret_cast<NfsManager *>(ptrSysNetworkConfScreen);
            emit SysNetworkConfgNFSDataUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System Network Configuration Industrial Ethernet Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION_ETHERNETIP)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysNetworkConfIndusEthScreen = "System_Network_Configuration_Ind_Eip_Screen";
            DataInterface* ptrSysNetworkConfIndusEthScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysNetworkConfIndusEthScreen];
            NetworkConfigurationEthernetIp *MyCommData1 = reinterpret_cast<NetworkConfigurationEthernetIp *>(ptrSysNetworkConfIndusEthScreen);
            emit SysNetworkConfgIndusEthIpDataUpdated(MyCommData1, WelderId);
        }
    }
    /*Screen update for System Network Configuration Profinet Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION_PROFINET)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysNetworkConfProfinetScreen = "System_Network_Configuration_Profinet_Screen";
            DataInterface* ptrSysNetworkConfProfinetScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysNetworkConfProfinetScreen];
            ProfinetSetting *MyCommData1 = reinterpret_cast<ProfinetSetting *>(ptrSysNetworkConfProfinetScreen);
            emit SysNetworkConfgProfinetDataUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System Configuration USB Authentication Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USB_AUTHENTICATION)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysConfUSBAuthScreen = "System_Configuration_USBAuthentication_Screen";
            DataInterface* ptrSysCOnfgUsbAuthscreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfUSBAuthScreen];
            USBAuthentication *MyCommData1 = reinterpret_cast<USBAuthentication *>(ptrSysCOnfgUsbAuthscreen);
            emit SysConfgUSBAuthDataUpdated(MyCommData1, WelderId);
        }
    }


    /*Screen update for Diagnostic UserIO Digital */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::DIAGNOSTIC_USERIO)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string DiagnosticUserIODigitalScreen = "Diagnostic_UserIO_Digital_Screen";
            DataInterface* ptrDigitalUserIO = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticUserIODigitalScreen];
            DigitalIOMgr *MyCommData1 = reinterpret_cast<DigitalIOMgr *>(ptrDigitalUserIO);
            emit DiagnosticUserIOUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System Configuration Genral */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_GENERAL)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SysConfgGenScreen = "System_Confg_General_Screen";
            DataInterface* ptrSysConfgGenScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfgGenScreen];
            SystemConfigurationGeneral_MB *MySysGenData = reinterpret_cast<SystemConfigurationGeneral_MB *>(ptrSysConfgGenScreen);
            emit SysConfgGenScreenUpdated(MySysGenData, WelderId);

        }
    }

    /*Screen update for User Management section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USERMANAGEMENT)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string UserManagementScreen = "System_Config_User_Management";
            DataInterface* ptrUserManagementScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[UserManagementScreen];
            UserManagement *MyCommData1 = reinterpret_cast<UserManagement *>(ptrUserManagementScreen);
            emit UserListScreenViewUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for Branson System Configuration Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CALIBRATE)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SystemCalibrationScreen = "System_Calibration";
            DataInterface* ptrSystemCalibrationScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SystemCalibrationScreen];
            CalibrationAce *MyCommData = reinterpret_cast<CalibrationAce *>(ptrSystemCalibrationScreen);
            emit CalibrationDataChanged(MyCommData, WelderId);
        }
    }

    /*Screen update for Scan Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::DIAGNOSTICS_SCAN)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            if(scanFlag)
            {
                std::string DiagnosticsScanSignatureScreen = "Diagnostics_Scan_Signature_Screen";
                DataInterface* ptrDiagnosticsScanSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsScanSignatureScreen];
                HornScanSignature *MyCommData4 = reinterpret_cast<HornScanSignature *>(ptrDiagnosticsScanSignatureScreen);
                scanFlag = false;

                emit ScanSignatureUpdated(MyCommData4, WelderId);
            }

            else
            {
                std::string DiagnosticsScanResultScreen = "Diagnostics_Scan_Result_Screen";
                DataInterface* ptrDiagnosticsScanResultScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsScanResultScreen];
                HornScanResult *MyCommData = reinterpret_cast<HornScanResult *>(ptrDiagnosticsScanResultScreen);

                std::string DiagnosticsScanSignatureScreen = "Diagnostics_Scan_Signature_Screen";
                DataInterface* ptrDiagnosticsScanSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsScanSignatureScreen];
                HornScanSignature *MyCommData2 = reinterpret_cast<HornScanSignature *>(ptrDiagnosticsScanSignatureScreen);

                std::string DiagnosticsScanRecipeScreen = "Diagnostics_Scan_Recipe_Screen";
                DataInterface* ptrDiagnosticsScanRecipeScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsScanRecipeScreen];
                HornScanRecipe *MyCommData3 = reinterpret_cast<HornScanRecipe *>(ptrDiagnosticsScanRecipeScreen);
                scanFlag = true;

                emit ScanScreenUpdated(MyCommData, MyCommData2, MyCommData3, WelderId);
            }
        }
    }

    /*Screen update for Seek Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::DIAGNOSTICS_SEEK)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            if(seekFlag)
            {
                std::string DiagnosticsSeekSignatureScreen = "Diagnostics_Seek_Signature_Screen";
                DataInterface* ptrDiagnosticsSeekSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsSeekSignatureScreen];
                SeekSignature *MyCommData4 = reinterpret_cast<SeekSignature *>(ptrDiagnosticsSeekSignatureScreen);
                seekFlag = false;

                emit SeekSignatureUpdated(MyCommData4, WelderId);
            }

            else
            {
                std::string DiagnosticsSeekResultScreen = "Diagnostics_Seek_Result_Screen";
                DataInterface* ptrDiagnosticsSeekResultScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsSeekResultScreen];
                SeekResult *MyCommData = reinterpret_cast<SeekResult *>(ptrDiagnosticsSeekResultScreen);

                std::string DiagnosticsSeekSignatureScreen = "Diagnostics_Seek_Signature_Screen";
                DataInterface* ptrDiagnosticsSeekSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsSeekSignatureScreen];
                SeekSignature *MyCommData2 = reinterpret_cast<SeekSignature *>(ptrDiagnosticsSeekSignatureScreen);

                std::string DiagnosticsSeekRecipeScreen = "Diagnostics_Seek_Recipe_Screen";
                DataInterface* ptrDiagnosticsSeekRecipeScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsSeekRecipeScreen];
                SeekRecipe *MyCommData3 = reinterpret_cast<SeekRecipe *>(ptrDiagnosticsSeekRecipeScreen);
                seekFlag = true;

                emit SeekScreenUpdated(MyCommData, MyCommData2, MyCommData3, WelderId);
            }
        }
    }

    /*Screen update for Test Screen section*/
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::DIAGNOSTICS_TEST)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            if(testFlag)
            {
                std::string DiagnosticsTestSignatureScreen = "Diagnostics_Test_Signature_Screen";
                DataInterface* ptrDiagnosticsTestSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsTestSignatureScreen];
                TestSignature *MyCommData4 = reinterpret_cast<TestSignature *>(ptrDiagnosticsTestSignatureScreen);
                testFlag = false;

                emit TestSignatureUpdated(MyCommData4, WelderId);
            }

            else
            {
                std::string DiagnosticsTestResultScreen = "Diagnostics_Test_Result_Screen";
                DataInterface* ptrDiagnosticsTestResultScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsTestResultScreen];
                TestResult *MyCommData = reinterpret_cast<TestResult *>(ptrDiagnosticsTestResultScreen);

                std::string DiagnosticsTestSignatureScreen = "Diagnostics_Test_Signature_Screen";
                DataInterface* ptrDiagnosticsTestSignatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsTestSignatureScreen];
                TestSignature *MyCommData2 = reinterpret_cast<TestSignature *>(ptrDiagnosticsTestSignatureScreen);

                std::string DiagnosticsTestRecipeScreen = "Diagnostics_Test_Recipe_Screen";
                DataInterface* ptrDiagnosticsTestRecipeScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DiagnosticsTestRecipeScreen];
                TestRecipe *MyCommData3 = reinterpret_cast<TestRecipe *>(ptrDiagnosticsTestRecipeScreen);
                testFlag = true;

                emit TestScreenUpdated(MyCommData, MyCommData2, MyCommData3, WelderId);
            }
        }
    }
    /*Generate Report Screen */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::GENERATE_REPORT_SUMMARY)
    {
        std::string GenerateReportSingleSummary = "Generate_Report_Single_Summary";
        DataInterface* ptrGenerateReportSingleSummary = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[GenerateReportSingleSummary];
        ReportManager *MyCommData = reinterpret_cast<ReportManager *>(ptrGenerateReportSingleSummary);
        emit GenerateReportSummaryScreenUpdated(MyCommData);
    }
	else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::GENERATE_REPORT_CONTINUOUS_SUMMARY)
    {
        std::string GenerateReportContinousSummary = "Generate_Report_Continous_Summary";
        DataInterface* ptrGenerateReportContinousSummary = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[GenerateReportContinousSummary];
        USBStreaming *MyCommData = reinterpret_cast<USBStreaming *>(ptrGenerateReportContinousSummary);
        emit SummaryScreenUpdated(MyCommData);
    }
    /*Screen update for Service Count Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_SERVICE_COUNT)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SystemServiceCountScreen = "System_Service_Count_Screen";
            DataInterface* ptrSystemServiceCountScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SystemServiceCountScreen];
            ServiceManagement *MyCommData1 = reinterpret_cast<ServiceManagement *>(ptrSystemServiceCountScreen);
            emit ServiceCountScreenUpdated(MyCommData1, WelderId);
        }
    }



    /*Screen update for Global User Setting */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_CONFIG_USERMANAGEMENT_GLOBAL_USER_SETTINGS)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string GlobalUserSettingScreen = "Global_User_Setting_Screen";
            DataInterface* ptrGlobalUserSettingScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[GlobalUserSettingScreen];
            GlobalUserSetting *MyCommData = reinterpret_cast<GlobalUserSetting *>(ptrGlobalUserSettingScreen);
            std::string UserManagementScreen = "System_Config_User_Management";
            DataInterface* ptrUserManagementScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[UserManagementScreen];
            UserManagement *MyCommData1 = reinterpret_cast<UserManagement *>(ptrUserManagementScreen);
            std::string SysConfgGenScreen = "System_Confg_General_Screen";
            DataInterface* ptrSysConfgGenScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SysConfgGenScreen];
            SystemConfigurationGeneral_MB *MyCommData2 = reinterpret_cast<SystemConfigurationGeneral_MB *>(ptrSysConfgGenScreen);
            emit GlobalUserSettingDataUpdated(MyCommData, MyCommData1, MyCommData2, WelderId);
        }
    }

    /*Screen update for Branson System Configuration Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::BRANSON_SYSTEM_CONFIGURATION)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string BransonSysConfScreen = "Branson_System_Configuration_Screen";
            DataInterface* ptrBransonSysConfScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[BransonSysConfScreen];
            SystemConfigBransonService *MyCommData1 = reinterpret_cast<SystemConfigBransonService *>(ptrBransonSysConfScreen);
            emit BransonSysConfgDataUpdated(MyCommData1, WelderId);
        }
    }
    /*Screen update for Software Upgrade Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SoftwareUpgradeScreen = "Software_Upgrade_Screen";
            DataInterface* ptrSoftwareUpgradeScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SoftwareUpgradeScreen];
            SoftwareUpgrade *MyCommData1 = reinterpret_cast<SoftwareUpgrade *>(ptrSoftwareUpgradeScreen);
            emit SoftwareUpgradeDataUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for System information machine details Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::SYSTEM_INFO)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string SystemInfoScreen = "System_Informtaion_Machine_Details_Screen";
            DataInterface* ptrSystemInfoScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SystemInfoScreen];
            SystemInformation *MyCommData1 = reinterpret_cast<SystemInformation *>(ptrSystemInfoScreen);

            std::string BransonSysConfScreen = "Branson_System_Configuration_Screen";
            DataInterface* ptrBransonSysConfScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[BransonSysConfScreen];
            SystemConfigBransonService *MyCommData2 = reinterpret_cast<SystemConfigBransonService *>(ptrBransonSysConfScreen);
            emit SystemInformationDataUpdated(MyCommData1,MyCommData2, WelderId);

            std::string SystemFeatureScreen = "System_Feature_Screen";
            DataInterface* ptrSystemFeatureScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SystemFeatureScreen];
            ConfigUtilityVersion *MyCommData3 = reinterpret_cast<ConfigUtilityVersion *>(ptrSystemFeatureScreen);
            emit SystemFeatureDataUpdated(MyCommData3, WelderId);
        }
    }

    /*Screen update for Login Screen section */
    else if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::LOGIN ||  UIScreenEnum::SYSTEM_CONFIG_USER_LIST_RESET_PASSWORD)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string LoginScreen = "Login_Screen";
            DataInterface* ptrLoginScreenScreenn = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[LoginScreen];
            UserManagement *MyCommData1 = reinterpret_cast<UserManagement *>(ptrLoginScreenScreenn);
            emit LoginScreenViewUpdated(MyCommData1, WelderId);
        }
    }

    /*Screen update for Branson Service Screen section */
   if(ActiveScreen::getInstance()->getCurrentActiveScreen() == UIScreenEnum::BRANSON_SERVICE_TAB)
    {
        /*Check for active welder*/
        if(WelderId == MultiwelderInterface::GetActiveWelder())
        {
            std::string BransonServiceScreen = "Branson_Service_Screen";
            DataInterface* ptrBransonServiceScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[BransonServiceScreen];
            BransonServiceTab *MyCommData1 = reinterpret_cast<BransonServiceTab *>(ptrBransonServiceScreen);
            emit BransonServiceDataUpdated(MyCommData1, WelderId);
        }
    }

    /*Check for active welder*/
    if(WelderId == MultiwelderInterface::GetActiveWelder())
    {
        std::string AlarmEventsLogScreen = "Alarm_Events_Log_Screen";
        DataInterface* ptrAlarmEventsLogScreenn = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[AlarmEventsLogScreen];
        AlarmMgrACE *MyCommData = reinterpret_cast<AlarmMgrACE *>(ptrAlarmEventsLogScreenn);

        std::string SystemServiceCountScreen = "System_Service_Count_Screen";
        DataInterface* ptrSystemServiceCountScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[SystemServiceCountScreen];
        ServiceManagement *MyCommData2 = reinterpret_cast<ServiceManagement *>(ptrSystemServiceCountScreen);

        emit AlarmEventsLogUpdated(MyCommData, MyCommData2, WelderId);

        std::string DateTimeSettingsScreen = "Date_Time_Settings_Screen";
        DataInterface* ptrDateTimeSettingsScreen = m_DataInterfaceConfig_HMI_Obj->GetHMIScreenData(WelderId).WelderMap[DateTimeSettingsScreen];
        DateTimeConversion *MyCommData3 = reinterpret_cast<DateTimeConversion *>(ptrDateTimeSettingsScreen);

        emit DateAndTimeUpdated(MyCommData3, WelderId);
    }
}



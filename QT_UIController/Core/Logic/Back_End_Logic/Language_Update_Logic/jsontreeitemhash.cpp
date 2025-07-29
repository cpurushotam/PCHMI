/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
This file is used for loading the selected screen .
 
 **********************************************************************************************************/

#include "jsontreeitemhash.h"
#include "uiscreendef.h"
QMap<QString, JsonTreeItem*>* JsonTreeItemHash::_hashItemIndex = nullptr;
QList<int>* JsonTreeItemHash::_stackHierarchical = nullptr;
QMap<QString, QString>* JsonTreeItemHash::_textIndex = nullptr;
QHash<int, JsonTreeItem*>* JsonTreeItemHash::_hashScreenIndex = nullptr;
/**************************************************************************//**
*
* \brief  Constructor
*         Meanwhile, _hashItemIndex, _hashScreenIndex, _stackHierarchical and _textIndex need to be initialized.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeItemHash::JsonTreeItemHash()
{
    _hashItemIndex = new QMap<QString, JsonTreeItem*>();
    _hashScreenIndex = new QHash<int, JsonTreeItem*>();
    _stackHierarchical = new QList<int>();
    _textIndex = new QMap<QString, QString>();
}

/**************************************************************************//**
*
* \brief  Destructor
*         If _hashItemIndex, _hashScreenIndex, _stackHierarchical and _textIndex object pointer is not equal to nullptr,
*         the object pointers needs to clear the container and delete the object pointer then.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeItemHash::~JsonTreeItemHash()
{
    if(_hashItemIndex != nullptr)
    {
        QMap<QString, JsonTreeItem*>::const_iterator iterBegin = _hashItemIndex->constBegin();
        QMap<QString, JsonTreeItem*>::const_iterator iterEnd = _hashItemIndex->constEnd();
        qDeleteAll(iterBegin, iterEnd);
        _hashItemIndex->clear();
        delete _hashItemIndex;
    }
    if(_hashScreenIndex != nullptr)
    {
        QHash<int, JsonTreeItem*>::const_iterator iterBegin = _hashScreenIndex->constBegin();
        QHash<int, JsonTreeItem*>::const_iterator iterEnd = _hashScreenIndex->constEnd();
        qDeleteAll(iterBegin, iterEnd);
        _hashScreenIndex->clear();
        delete _hashScreenIndex;
    }
    if(_stackHierarchical != nullptr)
    {
        _stackHierarchical->clear();
        delete _stackHierarchical;
    }
    if(_textIndex != nullptr)
    {
        _textIndex->clear();
        delete _textIndex;
    }
}

/**************************************************************************//**
*
* \brief  Insert item object (language text string) to Map
*
* \param  _obj : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeItemHash::insertItemObjectToItemMap(JsonTreeItem *_obj)
{
    QString strIndex = "";
    if(_stackHierarchical != nullptr)
    {
        for(int i = 0; i < _stackHierarchical->size(); i++)
        {
            strIndex += QString::number(_stackHierarchical->at(i)) + ",";
        }
        strIndex = strIndex.left(strIndex.length() - 1);
        if(_hashItemIndex != nullptr)
        {
            _hashItemIndex->insert(strIndex, _obj);
        }
    }
}

/**************************************************************************//**
*
* \brief  Insert item Object (screen title text string) to Hash
*
* \param  screenName: QString; _obj : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeItemHash::insertItemObjectToScreenHash(QString screenName, JsonTreeItem *_obj)
{
    if(screenName == "leftMenu")
        _hashScreenIndex->insert(UIScreenEnum::LEFTMENU, _obj);
    else if(screenName == "rightMenu")
        _hashScreenIndex->insert(UIScreenEnum::RIGHTMENU, _obj);
    else if(screenName == "Recipes")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES, _obj);
    else if(screenName == "RecipesLab")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB, _obj);
    else if(screenName == "RecipeSettings")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_SETTING, _obj);
    else if(screenName == "RecipeWeldMode")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDMODE, _obj);
    else if(screenName == "RecipeWeldProcess")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS, _obj);
    else if(screenName == "Pretrigger")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS_PRETRIGGER, _obj);
    else if(screenName == "Afterburst")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS_AFTERBURST, _obj);
    else if(screenName == "ParametersAZ")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_PARAMETERA2Z, _obj);
    else if(screenName == "Limits")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS, _obj);
    else if(screenName == "Setup")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_SETUP, _obj);
    else if(screenName == "Control")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_CONTROL, _obj);
    else if(screenName == "SuspectReject")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_SUSPECT_REJECT, _obj);
    else if(screenName == "EnergyCompensation")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_ENERGY_COMPENSATION, _obj);
    else if(screenName == "StackRecipe")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_STACKRECIPE, _obj);
    else if(screenName == "ResultView")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_RESULTVIEW, _obj);
    else if(screenName == "GraphSettings")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_GRAPHSETTING, _obj);
    else if(screenName == "Production")
        _hashScreenIndex->insert(UIScreenEnum::PRODUCTION, _obj);
    else if(screenName == "Analytics")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS, _obj);
    else if(screenName == "graphView")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_VIEW, _obj);
    else if(screenName == "graphCycleDetailsList")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_VIEW_CYCLE_DETAILS_LIST, _obj);
    else if(screenName == "graphRightSetting")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_RIGHT_SETTING, _obj);
    else if(screenName == "graphHeaderSetting")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_HEADER_SETTING, _obj);
    else if(screenName == "graphAxis")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_AXIS, _obj);
    else if(screenName == "AnalyticsTableView")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_TABLE_VIEW, _obj);
    else if(screenName == "System")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM, _obj);
    else if(screenName == "Information")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_INFO, _obj);
    else if(screenName == "SoftwareUpgrade")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE, _obj);
    else if(screenName == "InsertUSBtoWelder")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE_WELDER, _obj);
    else if(screenName == "InsertUSBtoRaspPi")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE_RASPPI, _obj);
    else if(screenName == "Actuator Setup")
        _hashScreenIndex->insert(UIScreenEnum::ACTUATORSETUP, _obj);
    else if(screenName == "Diagnostics")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS, _obj);
    else if(screenName == "Scan")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SCAN, _obj);
    else if(screenName == "ScanRecipe")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SCAN_RECIPE, _obj);
    else if(screenName == "Scan Graph View")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SCAN_GRAPH_VIEW, _obj);
    else if(screenName == "Test")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_TEST, _obj);
    else if(screenName == "Test Recipe")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_TEST_RECIPE, _obj);
    else if(screenName == "Test Graph View")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_TEST_GRAPH_VIEW, _obj);
    else if(screenName == "Seek")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SEEK, _obj);
    else if(screenName == "Seek Recipe")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SEEK_RECIPE, _obj);
    else if(screenName == "Seek Graph View")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_SEEK_GRAPH_VIEW, _obj);
    else if(screenName == "Event Log")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_EVENT, _obj);
    else if(screenName == "Alarm Log")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_ALARM, _obj);
    else if(screenName == "User IO")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTIC_USERIO, _obj);
    else if(screenName == "Import/ Export")
        _hashScreenIndex->insert(UIScreenEnum::IMPORTEXPORT, _obj);
    else if(screenName == "Generate Report")
        _hashScreenIndex->insert(UIScreenEnum::GENERATEREPORT, _obj);
    else if(screenName == "Generate Report Storage Option")
        _hashScreenIndex->insert(UIScreenEnum::GENERATE_REPORT_STORAGE, _obj);
    else if(screenName == "Generate Report Data Filters")
        _hashScreenIndex->insert(UIScreenEnum::GENERATE_REPORT_DATA_FILTERS, _obj);
    else if(screenName == "Generate Report Summary")
        _hashScreenIndex->insert(UIScreenEnum::GENERATE_REPORT_SUMMARY, _obj);
    else if(screenName == "Logout")
        _hashScreenIndex->insert(UIScreenEnum::LOGOUT, _obj);
    else if(screenName == "selectLanguage")
        _hashScreenIndex->insert(UIScreenEnum::SELECTLANGUAGE, _obj);
    else if(screenName == "LowerWeldModeValue")
        _hashScreenIndex->insert(UIScreenEnum::WELDMODE_VALUE_LOWERSTRING, _obj);
    else if(screenName == "Login")
        _hashScreenIndex->insert(UIScreenEnum::LOGIN, _obj);
    else if(screenName == "NumericKeypad")
        _hashScreenIndex->insert(UIScreenEnum::NUMPAD, _obj);
    else if(screenName == "alarm")
        _hashScreenIndex->insert(UIScreenEnum::ALARM, _obj);
    else if(screenName == "alarmGeneral")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_GENERAL, _obj);
    else if(screenName == "alarmName")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_NAME, _obj);
    else if(screenName == "alarmDescription")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_DESCRIPTION, _obj);
    else if(screenName == "Alarms Log")
        _hashScreenIndex->insert(UIScreenEnum::ALARMEVENTSLOG, _obj);
    else if(screenName == "System")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM, _obj);
    else if(screenName == "Information")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_INFO, _obj);
    else if(screenName == "Configuration")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG, _obj);
    else if(screenName == "General")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_GENERAL, _obj);
    else if(screenName == "User Management")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERMANAGEMENT, _obj);
    else if(screenName == "Reset Password")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USER_LIST_RESET_PASSWORD, _obj);
    else if(screenName == "User Change Password")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USER_LIST_CHANGE_PASSWORD, _obj);
    else if(screenName == "LDAP Config")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_LDAP_CONFIG, _obj);
    else if(screenName == "Global User Settings")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERMANAGEMENT_GLOBAL_USER_SETTINGS, _obj);
    else if(screenName == "System Add User")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERMANAGEMENT_ADD_USER, _obj);
    else if(screenName == "Gateway Data")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_GATEWAY_DATA, _obj);
    else if(screenName == "User I/O")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERIO, _obj);
    else if(screenName == "Power Supply I/O")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO, _obj);
    else if(screenName == "Network Config")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION, _obj);
    else if(screenName == "Network Config EthernetIP")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION_ETHERNETIP, _obj);
    else if(screenName == "Network Config ProfinetIP")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_NETWORKCONFIGURATION_PROFINET, _obj);
    else if(screenName == "Alarm Mgmt")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_ALARMMANGEMENT, _obj);
    else if(screenName == "Popup")
        _hashScreenIndex->insert(UIScreenEnum::POPUP, _obj);
    else if(screenName == "MultiWelder Information")
        _hashScreenIndex->insert(UIScreenEnum::MULTIWELDERINFORMATION, _obj);
    else if(screenName == "footer")
        _hashScreenIndex->insert(UIScreenEnum::FOOTER, _obj);
    else if(screenName == "Platform Config")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG, _obj);
    else if(screenName == "Platform Config Upgrade")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE, _obj);
    else if(screenName == "Platform Config Upgrade Start USB")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_START_USB, _obj);
    else if(screenName == "Platform Config Upgrade Start Ethernet")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_START_ETH, _obj);
    else if(screenName == "Platform Config Upgrade Read USB")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_USB, _obj);
    else if(screenName == "Platform Config Upgrade Read Ethernet")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_ETH, _obj);
    else if(screenName == "Platform Config Upgrade USB")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_USB, _obj);
    else if(screenName == "Platform Config Upgrade Ethernet")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_ETHERNET, _obj);
    else if(screenName == "Platform Config Upgrade Interface")
        _hashScreenIndex->insert(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_INTERFACE, _obj);
    else if(screenName == "AlertWindow")
        _hashScreenIndex->insert(UIScreenEnum::ALERTWINDOW, _obj);
    else if(screenName == "MessagePopup")
        _hashScreenIndex->insert(UIScreenEnum::MESSAGEPOPUP, _obj);
    else if(screenName == "DiagnosticEvent")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS_EVENT, _obj);
    else if(screenName == "DiagnosticUserIO")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTIC_USERIO, _obj);
    else if(screenName == "Digital I/O")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_DIGITALIO, _obj);
    else if(screenName == "Analog I/O")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_ANALOGIO, _obj);
    else if(screenName == "Industrial I/O")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CONFIG_USERIO_POWERIO_INDUSTRIAL, _obj);
    else if(screenName == "BransonConfirmationPopup")
        _hashScreenIndex->insert(UIScreenEnum::CONFIRMATION_POPUP, _obj);
    else if(screenName == "Emergency Stop Popup")
        _hashScreenIndex->insert(UIScreenEnum::ESTOP_POPUP, _obj);
    else if(screenName == "BransonSystemConfiguration")
        _hashScreenIndex->insert(UIScreenEnum::BRANSON_SYSTEM_CONFIGURATION, _obj);
    else if(screenName == "BatchSetting")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_BATCH_SETTING, _obj);
    else if(screenName == "BransonSystemConfiguration")
        _hashScreenIndex->insert(UIScreenEnum::BRANSON_SYSTEM_CONFIGURATION, _obj);
    else if(screenName == "BransonService")
        _hashScreenIndex->insert(UIScreenEnum::BRANSON_SERVICE_TAB, _obj);
    else if(screenName == "SOFTWARE UPGRADE")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE, _obj);
    else if(screenName == "Service Count")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SERVICE_COUNT, _obj);
    else if(screenName == "Calibration")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE, _obj);
    else if(screenName == "CalibrationActuator")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_ACTUATOR, _obj);
    else if(screenName == "CalibrationActuatorStartSwitches")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_ACTUATOR_WITH_START_SWITCHES, _obj);
    else if(screenName == "CalibrationFullSystem")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_FULL_SYSTEM, _obj);
    else if(screenName == "CalibrationForce")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_FORCE, _obj);
    else if(screenName == "CalibrationPressure")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_PRESSURE, _obj);
    else if(screenName == "CalibrationResetSensors")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_RESET_SENSORS, _obj);
    else if(screenName == "CalibrationSensors")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_CALIBRATE_SENSORS, _obj);
    else if(screenName == "Chanage Password")
        _hashScreenIndex->insert(UIScreenEnum::FIRST_TIME_LOGIN_CHANGE_PASSWORD, _obj);
    else
        _hashScreenIndex->insert(UIScreenEnum::NONESCREEN, _obj);
}

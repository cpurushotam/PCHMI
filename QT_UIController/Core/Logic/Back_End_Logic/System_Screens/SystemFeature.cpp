/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares SystemFeature class which is responsible to do interaction between frontend and backend .

--------------------------- REVISION HISTORY ------------------------------
 rev1: 27-03-2025

***************************************************************************/
#include "SystemFeature.h"
#include "PlatformConfig.h"
#include "MultiwelderInterface.h"
#include "StorageSupport.h"
#include "EventLogSupport.h"
#include "BatchControlSupport.h"
#include "UserAccessLevelSupport.h"
#include "BarcodeScannerSupport.h"
#include "UserIOSupport.h"
#include "LDAPSupport.h"
#include "FieldbusSupport.h"
#include "PCUtilitySupport.h"
#include "HMIDeviceSupport.h"
#include "UpdateScreens.h"

/**************************************************************************//**
*
* \brief  - SystemFeature Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
SystemFeature::SystemFeature(QObject *parent)
    : QObject{parent}
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SystemFeatureDataUpdated, this, &SystemFeature::OnConfigVersionScreenUpdated);

}

/**************************************************************************//**
*
* \brief - Below function returns the storage type.
*
* \param - None.
*
* \return - storage type
******************************************************************************/

int SystemFeature::getstorageType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), STORAGE_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that event logging supported or not.
*
* \param - None.
*
* \return - event logging support
******************************************************************************/

int SystemFeature::getEventLogging() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), EVENT_LOG_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that batch control supported or not.
*
* \param - None.
*
* \return - batch control support
******************************************************************************/

int SystemFeature::getBatchControl() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), BATCH_CONTROL_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns the user access level.
*
* \param - None.
*
* \return - user access level
******************************************************************************/

int SystemFeature::getUserAccessLevel() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), USER_ACCESS_LEVEL_TYPE_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that barcode scanner supported or not.
*
* \param - None.
*
* \return - barcode scanner support.
******************************************************************************/

int SystemFeature::getBarcodeScanner() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), BARCODE_SCANNER_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that user io diagnostics supported or not.
*
* \param - None.
*
* \return - user io diagnostics support.
******************************************************************************/

int SystemFeature::getUserIODiagnostics() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), USER_IO_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that LDAP supported or not.
*
* \param - None.
*
* \return - LDAP support.
******************************************************************************/

int SystemFeature::getLdap() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), LDAP_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns the industrial ethernet type.
*
* \param - None.
*
* \return - industrial ethernet type.
******************************************************************************/

int SystemFeature::getIndustrialEthernet() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), FIELDBUS_SUPPORT_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns that PC utility supported or not.
*
* \param - None.
*
* \return - PC utility support
******************************************************************************/

int SystemFeature::getpcUtility() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), PC_UTILITY_KEY);
}

/**************************************************************************//**
*
* \brief - Below function returns HMI_Type supported.
*
* \param - None.
*
* \return - HMI_Type - Type of HMI supported
******************************************************************************/

int SystemFeature::getHMIType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), HMI_DEVICE);
}

/**************************************************************************//**
*
* \brief -  Role of the slot OnConfigVersionScreenUpdated is to update values on system information screen.
*
* \param - None.
*
* \return - NOne
******************************************************************************/

void SystemFeature::OnConfigVersionScreenUpdated(ConfigUtilityVersion *ConfigUtilityVersionData_Obj, int WelderId)
{
    m_ConfigUtilityVersion = ConfigUtilityVersionData_Obj;

    if(m_ConfigUtilityVersion->GetIsConfigVersionAvailable() || m_WelderId != WelderId )
    {
        m_ConfigurationVersion = QString::fromUtf8(m_ConfigUtilityVersion->GetConfigUtilityVersionNumber());
        m_ConfigUtilityVersion->SetIsConfigVersionAvailable();
        m_WelderId = WelderId;
        emit systemConfigVersionUpdated();
    }
}
/**************************************************************************//**
*
* \brief - Below function returns Configuration version number
*
* \param - None.
*
* \return - COnfiguration version numaber
******************************************************************************/
QString SystemFeature::getConfigurationVersion() const
{
    return m_ConfigurationVersion;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps track for current system type configured.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 15/09/2023 - Initial version.
***************************************************************************/
#include "SystemConfiguration.h"
#include "PlatformConfig.h"
#include "MultiwelderInterface.h"
#include "ActuatorInit.h"
#include "EventLogSupport.h"
#include "UserIOSupport.h"
#include "UserAccessLevelSupport.h"
#include "BatchControlSupport.h"
#include "FieldbusSupport.h"

/**************************************************************************//**
*
* \brief   - SystemConfiguration class constructor.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
SystemConfiguration::SystemConfiguration(QObject *parent)
{
}

/**************************************************************************//**
*
* \brief   - Below function returns the system type configured.
*
* \param   - None.
*
* \return  - GetConfigValue : System type value.
******************************************************************************/
int SystemConfiguration::getCurrentSystemType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), ACTUATOR_TYPE_KEY);
}

/**************************************************************************//**
*
* \brief   - Below function returns the configuration for Eventlog support or not.
*
* \param   - None.
*
* \return  - GetConfigValue : EventLog Support value.
******************************************************************************/
int SystemConfiguration::getEventLogSupportSystemType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), EVENT_LOG_KEY);
}

/**************************************************************************//**
*
* \brief   - Below function returns the configuration for UserIO support or not.
*
* \param   - None.
*
* \return  - GetConfigValue : UserIo support value.
******************************************************************************/
int SystemConfiguration::getUserIOSupportSystemType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), USER_IO_KEY);
}

/**************************************************************************//**
*
* \brief   - Below function returns the configuration for Batch Setting support or not.
*
* \param   - None.
*
* \return  - GetConfigValue : Batch Setting support value.
******************************************************************************/
int SystemConfiguration::getBatchSettingSupportSystemType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), BATCH_CONTROL_KEY);
}

/**************************************************************************//**
*
* \brief   - Below function returns the configuration for userlevel.
*
* \param   - None.
*
* \return  - GetConfigValue : USER_ACCESS_LEVEL_TYPE support value.
******************************************************************************/
int SystemConfiguration::getUserAccessLevelType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), USER_ACCESS_LEVEL_TYPE_KEY);
}

/**************************************************************************//**
*
* \brief   - Below function returns the configuration for fieldbus support type.
*
* \param   - None.
*
* \return  - GetConfigValue : FIELDBUS_SUPPORT_KEY support value.
******************************************************************************/
int SystemConfiguration::getFieldBusSupportSystemType() const
{
    return PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), FIELDBUS_SUPPORT_KEY);
}

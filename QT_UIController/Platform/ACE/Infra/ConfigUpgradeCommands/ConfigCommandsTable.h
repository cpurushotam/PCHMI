/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Declare m_CommandTable to store commands and it information

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#ifndef CONFIGCOMMANDSTABLE_H
#define CONFIGCOMMANDSTABLE_H

#include <map>

#include "ConfigStartUSBUpgrade.h"
#include "ConfigReadVersionUSB.h"
#include "ConfigPerformUpgradeUSB.h"

#include "ConfigStartEthernetUpgrade.h"
#include "ConfigReadVersionEthernet.h"
#include "ConfigPerformUpgradeEthernet.h"

// Table to store information of commands
std::map <int, ConfigUpgradeCmdInterface*> m_CommandTable =
{
    {CMD_USB_MODE_SELECT,          new ConfigStartUSBUpgrade},
    {CMD_READ_USB,                 new ConfigReadVersionUSB},
    {CMD_CONFIG_UPGRADE_USB,       new ConfigPerformUpgradeUSB},
    {CMD_ETHERNET_MODE_SELECT,     new ConfigStartEthernetUpgrade},
    {CMD_ETHERNET_UPLOAD_FILES,    new ConfigReadVersionEthernet},
    {CMD_ETHERNET_CONFIG_UPGRADE,  new ConfigPerformUpgradeEthernet}
};

#endif // CONFIGCOMMANDSTABLE_H

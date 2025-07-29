/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares ConfigUpgradeCmdInterface to create command and handle response.

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#ifndef CONFIGUPGRADECMDINTERFACE_H
#define CONFIGUPGRADECMDINTERFACE_H

#include <QStringList>
#include <QObject>

static constexpr uint8_t CMD_USB_MODE_SELECT        = 0X51;     // Command for start USB upgrade
static constexpr uint8_t CMD_READ_USB               = 0X52;     // Command for config file information.
static constexpr uint8_t CMD_CONFIG_UPGRADE_USB     = 0X53;     // Command for perform USB upgrade
static constexpr uint8_t CMD_ETHERNET_MODE_SELECT   = 0X61;     // Command for start Ethernet upgrade
static constexpr uint8_t CMD_ETHERNET_UPLOAD_FILES  = 0X62;     // Command for upload config files.
static constexpr uint8_t CMD_ETHERNET_CONFIG_UPGRADE = 0X63;     // Command for perform ethernet upgrade

static constexpr char    CMD_UPGRADE []             = "UPGRADE";

enum ERROR_CODES{
    CONFIG_A_NOT_FOUND  = 1,
    CONFIG_B_NOT_FOUND  = 2
};

//ConfigUpgradeCmdInterface class definition
class ConfigUpgradeCmdInterface:public QObject
{
protected:    
    static constexpr uint16_t   ACK_INDEX            = 1;       /* Ack index */
    static constexpr uint16_t   CMD_INDEX            = 0;       /* Command index */
    static constexpr uint16_t   CMD_SIZE             = 1;       /* Command size */

public:    
    virtual int PrepareCommand(uint8_t* cmd, int &size) = 0;                 // Prepare command
    virtual QString handleResponse(uint8_t* response, int size) = 0;     // Handle response
};

#endif // CONFIGUPGRADECMDINTERFACE_H

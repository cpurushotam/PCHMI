/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for start USB upgrade related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/

#ifndef CONFIGSTARTUSBUPGRADE_H
#define CONFIGSTARTUSBUPGRADE_H

#include "ConfigUpgradeCmdInterface.h"

// ConfigStartUSBUpgrade Class definition
class ConfigStartUSBUpgrade : public ConfigUpgradeCmdInterface
{
    static constexpr uint8_t ACK                     = 0X1;         /* Success resonse */
    static constexpr uint8_t INVALID_STATE           = 0X2;         /* Invalid state */
    static constexpr uint8_t NO_USB_DEVICE           = 0X3;         /* No USB mass storage */
    static constexpr uint8_t NO_CONFIG_FILES         = 0X4;         /* No Configuration files present */

    /* Text Strings for language change support */
    QString m_InvalidStateText   = "Invalid state";
    QString m_NoDeviceText       = "No USB mass storage device";
    QString m_NoConfigFileText   = "No config files present";
    QString m_InvalidCommandText = "Invalid command";

    /* list of language strings */
    QStringList m_LangList;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        InvalidStateTextIdx = 0,
        NoDeviceTextIdx,
        NoConfigFileTextIdx,
        InvalidCommandTextIdx
    };

public:
    // Constructor declaration
    ConfigStartUSBUpgrade();

    // Prepare Start USB upgrade command to send to ASC.
    int PrepareCommand(uint8_t* cmd, int &size) override;

    // Handle response sent by ASC
    QString handleResponse(uint8_t* response, int size) override;

public slots:
    /* Slot on language change from HMI */
    void onSignalCurrentLanguageChanged();
};

#endif // CONFIGSTARTUSBUPGRADE_H

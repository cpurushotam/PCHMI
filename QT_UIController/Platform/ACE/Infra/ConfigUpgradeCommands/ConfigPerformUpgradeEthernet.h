/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for perform ethernet upgrade related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 18/12/2023 - Initial implementation.

***************************************************************************/
#ifndef CONFIGPERFORMUPGRADEETHERNET_H
#define CONFIGPERFORMUPGRADEETHERNET_H

#include "ConfigUpgradeCmdInterface.h"

// ConfigPerformUpgradeUSB class definition
class ConfigPerformUpgradeEthernet : public ConfigUpgradeCmdInterface
{

    static constexpr uint8_t    ACK                     = 0X1;         /* Success resonse */
    static constexpr uint8_t    INVALID_STATE           = 0X2;         /* Invalid state */
    static constexpr uint8_t    UPGRADE_FAILED          = 0X8;         /* Failed to upgrade config files */

    /* Text Strings for language change support */
    QString m_InvalidStateText   = "Invalid state";
    QString m_UpgradeFailText    = "Failed to upgrade Configuration file";
    QString m_InvalidCommandText = "Invalid command";

    /* list of language strings */
    QStringList m_LangList;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        InvalidStateTextIdx = 0,
        UpgradeFailTextIdx,
        InvalidCommandTextIdx
    };

public:
    // Constructor declaration
    ConfigPerformUpgradeEthernet();

    // Prepare perform USB upgrade command.
    int PrepareCommand(uint8_t* cmd, int &size) override;

    // Handle response sent by ASC
    QString handleResponse(uint8_t* response, int size) override;

public slots:
    /* Slot on language change from HMI */
    void onSignalCurrentLanguageChanged();
};

#endif // CONFIGPERFORMUPGRADEETHERNET_H

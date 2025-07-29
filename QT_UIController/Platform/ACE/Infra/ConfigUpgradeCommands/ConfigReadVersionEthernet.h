/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for config file upload over ethernet related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 13/12/2023 - Initial implementation.

***************************************************************************/
#ifndef CONFIGREADVERSIONETHERNET_H
#define CONFIGREADVERSIONETHERNET_H


#include "ConfigUpgradeCmdInterface.h"

// ConfigReadVersionUSB class definition
class ConfigReadVersionEthernet : public ConfigUpgradeCmdInterface
{
    static constexpr uint16_t   PAYLOAD_INDEX           = 5;           /* Payload index */
    static constexpr uint8_t    ACK                     = 0X1;         /* Success resonse */
    static constexpr uint8_t    INVALID_STATE           = 0X2;         /* Invalid state */
    static constexpr uint8_t    DECRYPTION_FAILED       = 0X3;         /* Failed to decrypt config files */
    static constexpr uint8_t    VALIDATION_FAILED       = 0X4;         /* Failed to validate config files */
    static constexpr uint8_t    INVALID_VERSION_INFO    = 0X5;         /* Invalid version information */

    // JSON keys to parse version and date.
    static constexpr char *DATE_TIME_JSON_KEY   = (char *)"Date_Time";
    static constexpr char *VERSION_JSON_KEY     = (char *)"Version";

    QString m_ConfigVersion;     // Store config version
    QString m_ConfigDate;        // Store config date

    /* Text Strings for language change support */
    QString m_InvalidStateText   = "Invalid state";
    QString m_ParseFailText      = "Failed to parse configuration";
    QString m_DecryptFailText    = "Failed to decrypt file";
    QString m_ValidFailText      = "Configuration file validation failed";
    QString m_InvalidVersionText = "Invalid version information";
    QString m_InvalidCommandText = "Invalid command";

    /* list of language strings */
    QStringList m_LangList;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        InvalidStateTextIdx = 0,
        ParseFailTextIdx,
        DecryptFailTextIdx,
        ValidFailTextIdx,
        InvalidVersionTextIdx,
        InvalidCommandTextIdx
    };

public:
    // Constructor declaration
    ConfigReadVersionEthernet();

    int PrepareCommand(uint8_t* cmd, int &size) override;               // Prepare perform USB upgrade command.
    QString handleResponse(uint8_t* response, int size) override;       // Handle response sent by ASC

public slots:
    /* Slot on language change from HMI */
    void onSignalCurrentLanguageChanged();
};

#endif // CONFIGREADVERSIONETHERNET_H

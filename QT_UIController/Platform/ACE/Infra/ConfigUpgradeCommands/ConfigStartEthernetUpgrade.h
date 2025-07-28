/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for start configuration upgrade via ethernet related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 12/12/2023 - Initial implementation.

***************************************************************************/
#ifndef CONFIGSTARTETHERNETUPGRADE_H
#define CONFIGSTARTETHERNETUPGRADE_H


#include "ConfigUpgradeCmdInterface.h"

// ConfigStartEthernetUpgrade Class definition
class ConfigStartEthernetUpgrade : public ConfigUpgradeCmdInterface
{
    static constexpr uint8_t ACK                     = 0X1;         /* Success resonse */
    static constexpr uint8_t INVALID_STATE           = 0X2;         /* Invalid state */

    /* Text Strings for language change support */
    QString m_InvalidStateText   = "Invalid state";
    QString m_InvalidCommandText = "Invalid command";

    /* list of language strings */
    QStringList m_LangList;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        InvalidStateTextIdx = 0,
        InvalidCommandTextIdx
    };

public:
    // Constructor Declaration
    ConfigStartEthernetUpgrade();

    // Prepare Start USB upgrade command to send to ASC.
    int PrepareCommand(uint8_t* cmd, int &size) override;

    // Handle response sent by ASC
    QString handleResponse(uint8_t* response, int size) override;

public slots:
    /* Slot on language change from HMI */
    void onSignalCurrentLanguageChanged();
};

#endif // CONFIGSTARTETHERNETUPGRADE_H

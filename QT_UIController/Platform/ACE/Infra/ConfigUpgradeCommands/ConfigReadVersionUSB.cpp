/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for config file information related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/

#include "ConfigReadVersionUSB.h"
#include "PlatformConfigUpgrade.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "uiscreendef.h"
#include "languageconfig.h"

/**************************************************************************//**
*
* \brief   - ConfigStartUSBUpgrade class constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
ConfigReadVersionUSB::ConfigReadVersionUSB()
{
    // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     this , &ConfigReadVersionUSB::onSignalCurrentLanguageChanged);

    // Create list of language strings
    m_LangList = {m_InvalidStateText, m_ParseFailText, m_DecryptFailText, m_ValidFailText, m_InvalidVersionText, m_InvalidCommandText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_USB, m_LangList);
}
/*************************************************************************//**
* \brief   - Prepare command for config file information
*
* \param   - uint8_t* Command - Buffer for command
*            int      size    - Size of command
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int ConfigReadVersionUSB::PrepareCommand(uint8_t *Command, int &size)
{
    int Status = -1;

    if (Command != nullptr)
    {
        // Update command buffer with config file information command
        Command[CMD_INDEX] = CMD_READ_USB;

        // Total Size of command
        size = CMD_SIZE;

        Status = 0;
    }

    return Status;
}

/*************************************************************************//**
* \brief   - Haldle response for config file information
*
* \param   - uint8_t* ResponseBuff -  Response Buffer
*            int      size          - Size of Buffer
*
* \return  - std::string - Status Message
******************************************************************************/
QString ConfigReadVersionUSB::handleResponse(uint8_t *ResponseBuff, int buff_size)
{
    QString StatusMessage = m_LangList[ParseFailTextIdx];

    if(ResponseBuff != nullptr)
    {
        switch (ResponseBuff[ACK_INDEX])
        {
        case ACK:
        {
            uint32_t *VersionInfoSize = reinterpret_cast<uint32_t *>(&ResponseBuff[ACK_INDEX+1]);

            char *JSONString = reinterpret_cast<char*>(&ResponseBuff [ACK_INDEX+PAYLOAD_INDEX]);

            if ((JSONString!=nullptr) && (*VersionInfoSize > 0))
            {
                // Parse JSON string
                QJsonDocument jsonDoc = QJsonDocument::fromJson(JSONString);
                if (!jsonDoc.isNull() && jsonDoc.isObject())
                {
                    // Extract JSON object
                    m_ConfigVersion = jsonDoc.object().value(VERSION_JSON_KEY).toString();
                    m_ConfigDate    = jsonDoc.object().value(DATE_TIME_JSON_KEY).toString();

                    PlatformConfigUpgrade::UpdateConfigDetails(m_ConfigVersion, m_ConfigDate);

                    // On success, initilize status message
                    StatusMessage = "";
                }               
            }
            break;
        }            
        case INVALID_STATE:
            StatusMessage = m_LangList[InvalidStateTextIdx];
            break;
        case DECRYPTION_FAILED:
            StatusMessage = m_LangList[DecryptFailTextIdx];
            break;
        case VALIDATION_FAILED:
            StatusMessage = m_LangList[ValidFailTextIdx];
            break;
        case INVALID_VERSION_INFO:
            StatusMessage = m_LangList[InvalidVersionTextIdx];
            break;
        default:
            StatusMessage = m_LangList[InvalidCommandTextIdx];
        }
    }

    return StatusMessage;
}

/**************************************************************************//**
*
* \brief   - Slot on language change from HMI.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ConfigReadVersionUSB::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_USB, m_LangList);
}

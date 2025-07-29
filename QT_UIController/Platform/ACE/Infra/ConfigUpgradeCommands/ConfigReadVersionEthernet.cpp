/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for config file upload over ethernet related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#include <fstream>
#include "ConfigReadVersionEthernet.h"
#include "PlatformConfigUpgrade.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "uiscreendef.h"
#include "languageconfig.h"

static constexpr uint16_t CONFIG_A_FILE_SIZE_IDX    = 1;
static constexpr uint16_t CONFIG_B_FILE_SIZE_IDX    = 5;
static constexpr uint16_t CONFIG_A_FILE_IDX         = 9;
static constexpr uint16_t HEADER_SIZE               = 8;

/**************************************************************************//**
*
* \brief   - ConfigReadVersionEthernet class constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
ConfigReadVersionEthernet::ConfigReadVersionEthernet()
{
    // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     this , &ConfigReadVersionEthernet::onSignalCurrentLanguageChanged);

    // Create list of language strings
    m_LangList = {m_InvalidStateText, m_ParseFailText, m_DecryptFailText, m_ValidFailText, m_InvalidVersionText, m_InvalidCommandText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_ETH, m_LangList);
}
/*************************************************************************//**
* \brief   - Prepare command for config file information
*
* \param   - uint8_t* Command - Buffer for command
*            int      size    - Size of command
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int ConfigReadVersionEthernet::PrepareCommand(uint8_t *Command, int &TotalSize)
{
    int Status = -1;
    std::streampos file_size;
    uint32_t *ConfigAFileSize;
    uint32_t *ConfigBFileSize;

    // config file names on selected config file path.
    std::string EthConfigA = "config_A.out";
    std::string EthConfigB = "config_B.out";

    std::string ConfigFilesPath = PlatformConfigUpgrade::GetConfigFilesPath().toStdString();

    if (Command != nullptr)
    {
        // Update command buffer with config file information command
        Command[CMD_INDEX] = CMD_ETHERNET_UPLOAD_FILES;

        std::ifstream FileAHandler(ConfigFilesPath + "/" + EthConfigA, std::ios::in|std::ios::binary|std::ios::ate);
        if (FileAHandler.is_open())
        {
            file_size = FileAHandler.tellg();
            ConfigAFileSize = reinterpret_cast<uint32_t *>(&Command[CONFIG_A_FILE_SIZE_IDX]);
            *ConfigAFileSize = file_size;
            FileAHandler.seekg (0, std::ios::beg);
            FileAHandler.read ((char*)(Command+CONFIG_A_FILE_IDX), file_size);
            FileAHandler.close();

            Status = 0;
        }

        if (Status == 0)
        {
            std::ifstream FileBHandler(ConfigFilesPath + "/" + EthConfigB, std::ios::in|std::ios::binary|std::ios::ate);
            if (FileBHandler.is_open())
            {
                file_size=0;
                file_size = FileBHandler.tellg();
                ConfigBFileSize = reinterpret_cast<uint32_t *>(&Command[CONFIG_B_FILE_SIZE_IDX]);
                *ConfigBFileSize = file_size;
                FileBHandler.seekg (0, std::ios::beg);
                FileBHandler.read ((char*)(Command+CONFIG_A_FILE_IDX+(*ConfigAFileSize)), file_size);
                FileBHandler.close();

                TotalSize = (HEADER_SIZE + *ConfigAFileSize + *ConfigBFileSize + 1);
            }
            else
            {
                return CONFIG_B_NOT_FOUND;
            }
        }
        else
        {
            return CONFIG_A_NOT_FOUND;
        }
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
QString ConfigReadVersionEthernet::handleResponse(uint8_t *ResponseBuff, int buff_size)
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
void ConfigReadVersionEthernet::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_READ_ETH, m_LangList);
}

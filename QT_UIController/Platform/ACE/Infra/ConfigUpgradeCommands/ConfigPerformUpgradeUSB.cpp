/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for perform USB upgrade related command/response

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#include "ConfigPerformUpgradeUSB.h"
#include "uiscreendef.h"
#include "languageconfig.h"

/**************************************************************************//**
*
* \brief   - ConfigPerformUpgradeUSB class constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
ConfigPerformUpgradeUSB::ConfigPerformUpgradeUSB()
{
    // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     this , &ConfigPerformUpgradeUSB::onSignalCurrentLanguageChanged);

    // Create list of language strings
    m_LangList = {m_InvalidStateText, m_UpgradeFailText, m_InvalidCommandText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_USB, m_LangList);
}
/*************************************************************************//**
* \brief   - Prepare command for perform USB upgrade.
*
* \param   - uint8_t* Command - Buffer for command
*            int      size    - Size of command
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int ConfigPerformUpgradeUSB::PrepareCommand(uint8_t *Command, int &size)
{
    int Status = -1;
    if (Command != nullptr)
    {
        // Update command buffer with config file information command
        Command[CMD_INDEX] = CMD_CONFIG_UPGRADE_USB;

        // Total Size of command
        size = CMD_SIZE;
        Status = 0;
    }

    return Status;
}

/*************************************************************************//**
* \brief   - Haldle response of perform USB upgrade.
*
* \param   - uint8_t* ResponseBuff -  Response Buffer
*            int      size          - Size of Buffer
*
* \return  - std::string - Status Message
******************************************************************************/
QString ConfigPerformUpgradeUSB::handleResponse(uint8_t *ResponseBuff, int buff_size)
{
    QString StatusMessage = m_LangList[InvalidCommandTextIdx];
    if(ResponseBuff != nullptr)
    {
        switch (ResponseBuff[ACK_INDEX])
        {
        case ACK:
            StatusMessage = CMD_UPGRADE;
            break;
        case INVALID_STATE:
            StatusMessage = m_LangList[InvalidStateTextIdx];
            break;
        case UPGRADE_FAILED:
            StatusMessage = m_LangList[UpgradeFailTextIdx];
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
void ConfigPerformUpgradeUSB::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_USB, m_LangList);
}

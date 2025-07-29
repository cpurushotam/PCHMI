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

#include "ConfigStartUSBUpgrade.h"
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
ConfigStartUSBUpgrade::ConfigStartUSBUpgrade()
{
    // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     this , &ConfigStartUSBUpgrade::onSignalCurrentLanguageChanged);

    // Create list of language strings
    m_LangList = {m_InvalidStateText, m_NoDeviceText, m_NoConfigFileText, m_InvalidCommandText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_START_USB, m_LangList);
}

/*************************************************************************//**
* \brief   - Prepare command for start USB upgrade.
*
* \param   - uint8_t* Command - Buffer for command
*            int      size    - Size of command
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int ConfigStartUSBUpgrade::PrepareCommand(uint8_t *Command, int &size)
{
    int Status = -1;

    if(Command != nullptr)
    {
        // Update command buffer with config file information command
        Command[CMD_INDEX] = CMD_USB_MODE_SELECT;

        // Total Size of command
        size = CMD_SIZE;

        Status = 0;
    }

    return Status;
}

/*************************************************************************//**
* \brief   - Haldle response of start USB upgrade
*
* \param   - uint8_t* ResponseBuff -  Response Buffer
*            int      size          - Size of Buffer
*
* \return  - std::string - Status Message
******************************************************************************/
QString ConfigStartUSBUpgrade::handleResponse(uint8_t *ResponseBuff, int buff_size)
{
    QString StatusMessage = m_LangList[InvalidCommandTextIdx];

    if(ResponseBuff != nullptr)
    {
        switch (ResponseBuff[ACK_INDEX])
        {
        case ACK:
            StatusMessage = "";
            break;
        case INVALID_STATE:
            StatusMessage = m_LangList[InvalidStateTextIdx];
            break;
        case NO_USB_DEVICE:
            StatusMessage = m_LangList[NoDeviceTextIdx];
            break;
        case NO_CONFIG_FILES:
            StatusMessage = m_LangList[NoConfigFileTextIdx];
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
void ConfigStartUSBUpgrade::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_START_USB, m_LangList);
}

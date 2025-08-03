/**************************************************************************

          Copyright (c) Branson Ultrasonics Corporation, 1996-2023

          This program is the property of Branson Ultrasonics Corporation
          Copying of this software is expressly forbidden, without the prior
          written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
 Implements ConfigStatus class, used for interface between of QML and Backend

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/10/2023 - Initial version.
***************************************************************************/
#include "MultiwelderInterface.h"
#include "ConfigStatus.h"
#include "CommPeerWrapper.h"
#include "uiscreendef.h"
#include "languageconfig.h"

/**************************************************************************//**
*
* \brief   - ConfigStatus class constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
ConfigStatus::ConfigStatus()
{
    // Create list of language strings
    m_LangList = {m_NoConnText, m_WelderNameText, m_ConfigFailText, m_ConfigWaitingText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG, m_LangList);
}

/**************************************************************************//**
*
* \brief   - Slot on Welder index changed and config status update.
*
* \param   - int WelderId -- changed welder id
*
* \return  - None
*
******************************************************************************/
void ConfigStatus::onSelectWelderIndexChanged(int WelderId)
{
    char msg[50]={0};
    int ConfigState =  E_FAIL;

    int active_welder_id = MultiwelderInterface::GetActiveWelder();

    if (active_welder_id != -1)
    {
        if ( active_welder_id == WelderId)
        {
            switch(CommPeerWrapper::GetPeerData(WelderId)->GetPlatformConfigState())
            {
            case E_SUCCESS:
                ConfigState = E_SUCCESS;
                break;
            case E_FAIL:
                sprintf(msg, "%s %d : %s", m_LangList[WelderNameTextIdx].toStdString().c_str(), WelderId+1, m_LangList[ConfigFailTextIdx].toStdString().c_str());
                m_StatusMsg = msg;
                ConfigState = E_FAIL;
                break;
            case E_IN_PROCESS:
                sprintf(msg, "%s %d : %s", m_LangList[WelderNameTextIdx].toStdString().c_str(), WelderId+1, m_LangList[ConfigWaitingTextIdx].toStdString().c_str());
                m_StatusMsg = msg;
                ConfigState = E_IN_PROCESS;
                break;
            default:
                break;
            }
            emit platformConfigStateUpdated(ConfigState);
        }
    }
    else
    {
        m_StatusMsg = m_LangList[NoConnTextIdx];
        emit platformConfigStateUpdated(ConfigState);
    }

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
void ConfigStatus::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG, m_LangList);

    // Update status message on language change
    onSelectWelderIndexChanged(MultiwelderInterface::GetActiveWelder());
}

/**************************************************************************//**
*
* \brief   - Slot on Firmware mismatch detect .
*
* \param   - Error Message to display
*
* \return  - None
*
******************************************************************************/
void ConfigStatus::onFirmwareMismatchDetect(std::string ErrorMismatchMsg)
{
    // Update status message on Firmware mismatch detected.
    m_StatusMsg = QString::fromStdString(ErrorMismatchMsg);
    emit firmwareMismatchNotify();
}

/**************************************************************************//**
*
* \brief   - Update welder status message on HMI.
*
* \param   - None
*
* \return  - QString -- Status Message
*
******************************************************************************/
QString ConfigStatus::getConfigWelderStatusMsg()
{
    return m_StatusMsg;
}

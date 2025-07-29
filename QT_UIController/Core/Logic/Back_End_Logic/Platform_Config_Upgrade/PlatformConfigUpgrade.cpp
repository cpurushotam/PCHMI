/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for platform config upgrade

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#include "PlatformConfigUpgrade.h"
#include "MultiwelderInterface.h"
#include "ConfigCommandsTable.h"
#include "BIOConfigUpgrade.h"
#include "WDSServer.h"
#include "uiscreendef.h"
#include "languageconfig.h"

/*****************************************************************************
* Initilization of static variables
******************************************************************************/
QString PlatformConfigUpgrade::m_ConfigFilesPath;
QString PlatformConfigUpgrade::m_ConfigVersion;
QString PlatformConfigUpgrade::m_ConfigDate;

/*****************************************************************************
* \brief   - Constructor : Initialize the PlatformConfigUpgrade class
*
* \param   - parent - QObject
*
* \return  - None
*
******************************************************************************/
PlatformConfigUpgrade::PlatformConfigUpgrade(QObject *parent)
{
    // Connect signalCurrentLanguageChanged signal to onSignalCurrentLanguageChanged slot.
    QObject::connect(LanguageConfig::getInstance(), &LanguageConfig::signalCurrentLanguageChanged,
                     this , &PlatformConfigUpgrade::onSignalCurrentLanguageChanged);

    // initialize log ID
    m_log_id = Logger::enroll(this);

    // Initilize secure secket configuration
    m_ptrSSLConfig = &SSLConfig;

    // copy configure port in bio_config to create DestinationIPandPort
    strcpy(m_BIOPort, m_ptrSSLConfig->DestinationIPandPort);

    // Create list of language strings
    m_LangList = {m_ConfigANotFoundText, m_ConfigBNotFoundText, m_CommErrorText};

    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_INTERFACE, m_LangList);
}

/*****************************************************************************
* \brief   - Create instance of BIO wrapper class by providing required SSL
*            configuration and start communication.
*
* \param   - None
*
* \return  -if success returns 0, else returns -1 (failure)
*
******************************************************************************/
int PlatformConfigUpgrade::StartComm()
{
    int status = -1; 

    char *IpAddr = WDSServer::GetInstance()->GetActiveWelderIPAddress(MultiwelderInterface::GetActiveWelder());
    if (IpAddr == nullptr)
    {
        return status;
    }

    /* Use this for configuring destination IP and Port */
    sprintf(m_ptrSSLConfig->DestinationIPandPort, "%s:%s", IpAddr, m_BIOPort);

    try
    {
        // Start secure connection
        m_ptrBIOInstance = new BIOWrapper(m_ptrSSLConfig);
        status = 0;
    }
    catch (std::exception &e)
    {
        // Log fault
        snprintf ( m_log_buffer, buff_size_config, "BIOError:%s",e.what() );
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (m_log_buffer));

        status = -1;
    }

    return status;
}

/*****************************************************************************
* \brief   - Prepare commands and send to ASC and handled response.
*
* \param   - None
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int PlatformConfigUpgrade::Process()
{
    int status = -1;
    int command_size =1;

    // Initiize status message
    m_StatusMessage = m_LangList[CommErrorTextIdx];

    auto it = m_CommandTable.find(m_CommandQueue.dequeue());

    if (it != m_CommandTable.end())
    {
        memset(m_CommandBuff,0,buff_size);

        /* Prepare command */
        int RetValue = it->second->PrepareCommand(m_CommandBuff, command_size);
        if (RetValue == 0)
        {
            /* Send command */
            RetValue = m_ptrBIOInstance->BIOWrite(m_CommandBuff, command_size);
            if (RetValue > 0)
            {
                // Log Event
                snprintf ( this->m_log_buffer, buff_size_config, "%x Command sent successfully", (int)m_CommandBuff[0]);
                Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_log_buffer));

                // Initilize response buffer.
                memset(m_RxBuff, 0, buff_size);

                /* Send command */
                RetValue = m_ptrBIOInstance->BIORead(m_RxBuff, buff_size);
                if (RetValue > 0)
                {
                    // Log Event
                    snprintf ( this->m_log_buffer, buff_size_config, "Response received for %x ", (int)m_RxBuff[0]);
                    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_log_buffer));

                    m_StatusMessage = it->second->handleResponse(m_RxBuff, RetValue);
                    if (m_StatusMessage.isEmpty())
                    {
                        // Log Debug
                        snprintf ( this->m_log_buffer, buff_size_config, "Handled Response successfully for %x ", (int)m_RxBuff[0]);
                        Logger::add_entry(E_SEVERITY::E_LOG_DEB, (this->m_log_buffer));

                        status = 0;
                    }
                    else if (m_StatusMessage == CMD_UPGRADE)
                    {
                        // Log Debug
                        snprintf ( this->m_log_buffer, buff_size_config, "Configuration files upgraded successfully");
                        Logger::add_entry(E_SEVERITY::E_LOG_DEB, (this->m_log_buffer));
                        m_StatusMessage = "";
                    }
                    else
                    {
                        // Log Alarm
                        snprintf ( this->m_log_buffer, buff_size_config, "Upgrade Failed: %s", m_StatusMessage.toStdString().c_str());
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                    }
                }
                else
                {
                    // Log fault
                    snprintf ( this->m_log_buffer, buff_size_config, "Failed to read command for : %d ", (int)m_CommandBuff[0]);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                }
            }
            else
            {
                // Log fault
                snprintf ( this->m_log_buffer, buff_size_config, "Failed to send command for : %d ", (int)m_CommandBuff[0]);
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
            }
        }
        else
        {
            if (RetValue == CONFIG_A_NOT_FOUND)
            {
                m_StatusMessage = m_LangList [ConfigANotFoundTextIdx];
            }
            else if(RetValue == CONFIG_B_NOT_FOUND)
            {
                m_StatusMessage = m_LangList [ConfigBNotFoundTextIdx];
            }

            // Log fault
            snprintf ( this->m_log_buffer, buff_size_config, "Failed to prepare command for : %d ", it->first);
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
        }        
    }
    // Send signal to update HMI
    emit updatedScreen();

    return status;
}

/*****************************************************************************
* \brief   - Exit communication with peer
*
* \param   - None
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int PlatformConfigUpgrade::ExitComm()
{
    try
    {
        // delete BIO Wrapper instance to initiate SSL shutdown
        delete m_ptrBIOInstance;
        m_ptrBIOInstance = nullptr;
    }
    catch(std::exception &e)
    {
        snprintf ( m_log_buffer, buff_size_config, "ExitFailed:%s",e.what());
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (m_log_buffer));
        return (-1);
    }

    // Log Event
    snprintf ( m_log_buffer, buff_size_config, "Detached:%s",m_ptrSSLConfig->DestinationIPandPort);
    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (m_log_buffer));
    return (0);
}

/*****************************************************************************
* \brief   - State machine to process commands
*
* \param   - None
*
* \return  - None
******************************************************************************/
void PlatformConfigUpgrade::run()
{
    int Status = -1;
    uint8_t CurrentCommand = 0;

    // current state of config upgrade thread
    CONFIG_THREAD_STATES CurrentState = CONFIG_COMM_START_REQUEST;

    while(1)
    {
        if (!m_CommandQueue.empty())
        {
            CurrentCommand = m_CommandQueue.first();
            switch (CurrentState)
            {
                case CONFIG_COMM_START_REQUEST:
                {
                    if ((CurrentCommand == CMD_USB_MODE_SELECT) || (CurrentCommand == CMD_ETHERNET_MODE_SELECT))
                    {
                        CurrentState = CONFIG_COMM_START;
                        continue;
                    }
                    else if (CurrentCommand == ABORT_COMMAND)
                    {
                        CurrentCommand = m_CommandQueue.dequeue();
                    }
                    break;
                }
                case CONFIG_COMM_START:
                {
                    /* Created instance of BIO Wrapper class */
                    Status= StartComm();
                    if(Status == -1)
                    {
                        // Log fault
                        snprintf ( this->m_log_buffer, buff_size_config, "Config Upgrade: Error in starting communication" );
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));

                        // wait for some time and try to start server again
                        sleep(10);
                        CurrentState = CONFIG_COMM_START_REQUEST;
                    }
                    else
                    {
                        // Log Event
                        snprintf ( this->m_log_buffer, buff_size_config, "Secure communication started");
                        Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_log_buffer));

                        CurrentState = CONFIG_COMM_PROCESS;
                        continue;
                    }
                    break;
                }
                case CONFIG_COMM_PROCESS:
                {
                    Status = Process();
                    if(Status < 0)
                    {
                        Status = ExitComm();
                        if(Status < 0)
                        {                            
                            // Log fault
                            snprintf ( this->m_log_buffer, buff_size_config, "Failed to disconnect with peer");
                            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                        }

                        CurrentState = CONFIG_COMM_START_REQUEST;
                    }
                    break;
                }
            }
        }
        msleep(SLEEP_TIME);
    }
}

/*****************************************************************************
* \brief   - Add configuration upgrade command to command queue.
*
* \param   - int command - Upgrade command
*
* \return  - None
******************************************************************************/
void PlatformConfigUpgrade::sendCommand(int command)
{
    m_CommandQueue.enqueue(command);
}

/*****************************************************************************
* \brief   - Qinvokable function to read configuration version
*
* \param   - None
*
* \return  - configuration version
******************************************************************************/
QString PlatformConfigUpgrade::readConfiVersion()
{
    return m_ConfigVersion;
}

/*****************************************************************************
* \brief   - Qinvokable function to read configuration date
*
* \param   - None
*
* \return  - configuration date
******************************************************************************/
QString PlatformConfigUpgrade::readConfigDate()
{
    return m_ConfigDate;
}

/*****************************************************************************
* \brief   - Update configuration files path selected by user.
*
* \param   - std::string -  Configuration File Path
*
* \return  - None
******************************************************************************/
void PlatformConfigUpgrade::setConfigFilesPath(const QString configFilePath)
{
    m_ConfigFilesPath = configFilePath;
}

/*****************************************************************************
* \brief   - Return configuration files path selected by user.
*
* \param   - None
*
* \return  - std::string -  Configuration File Path
******************************************************************************/
QString PlatformConfigUpgrade::GetConfigFilesPath()
{
    return m_ConfigFilesPath;
}

/*****************************************************************************
* \brief   - Update configuration version and configuration date.
*
* \param   - const std::string configuration version
*            const std::string configuration date
*
* \return  - None
******************************************************************************/
void PlatformConfigUpgrade::UpdateConfigDetails(const QString ConfigVersion, const QString ConfigDate)
{
    m_ConfigVersion = ConfigVersion;
    m_ConfigDate    = ConfigDate;
}

/*****************************************************************************
* \brief   - Qinvokable function to Read configuration status message
*
* \param   - None
*
* \return  - configuration status message
******************************************************************************/
QString PlatformConfigUpgrade::statusMessage()
{
    return m_StatusMessage;
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
void PlatformConfigUpgrade::onSignalCurrentLanguageChanged()
{
    // Update language list as per selected language.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::PLATFORM_CONFIG_UPGRADE_INTERFACE, m_LangList);
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Implements platform config data interface, used for configuration of HMI

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/10/2023 - Initial implementation.

***************************************************************************/

#include <cstring>
#include <QJsonDocument>
#include <QJsonObject>

#include "PlatformConfig.h"
#include "CommPeerWrapper.h"

/**************************************************************************//**
*
* \brief   - PlatformConfig class constructor.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
PlatformConfig::PlatformConfig(ActiveConfig* ActiveConfiguration)
{
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);

    m_CurrentState = STATES::E_WAITING_FOR_CONFIG;

    m_ActiveConfiguration = ActiveConfiguration;
}

/**************************************************************************//**
*
* \brief   - Parse JSON configuration.
*
* \param   - JSON Config.
*
* \return  - On Success returns true, else returns false
*
******************************************************************************/
bool PlatformConfig::ParseConfigJSON(const char *JSONConfig)
{
    bool status = false;
    std::string ConfigTag;

    // Parse JSON like string
    QJsonDocument jsonDoc = QJsonDocument::fromJson(JSONConfig);

    if (!jsonDoc.isNull() && jsonDoc.isObject())
    {
        if (m_ActiveConfiguration != nullptr)
        {
            // Extract JSON object
            QJsonObject jsonObj = jsonDoc.object();

            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it)
            {
                ConfigTag = it.key().toStdString();
                auto config_it = m_ActiveConfiguration->find(ConfigTag);
                if ( config_it != m_ActiveConfiguration->end())
                {
                    m_HMI_Config[ConfigTag] = it->toInt();
                    status = true;
                }
                else
                {
                    status = false;
                    //Log Alarm
                    snprintf(m_LogBuffer,buff_size_config,"%s : not configured in active configuration", ConfigTag.c_str());
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, m_LogBuffer);
                    break;
                }
            }
        }
        else
        {
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Active Configuration is empty");
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Failed to parse JSON");
    }
    return status;
}

/**************************************************************************//**
*
* \brief   - Retrive status of configuration exchange.
*
* \param   - Address of destination MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int PlatformConfig::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	if((destination != NULL) && (destination->id == MB_ID_PLATFORM_CONFIG) && (destination->size >= sizeof(HMIConfigJSON)))
	{
		switch(this->m_CurrentState)
		{
            case STATES::E_WAITING_FOR_CONFIG:
            {
                if(destination->size >= sizeof(HMIConfigJSON))
                {
                    //fill data
                    HMIConfigJSON *header = reinterpret_cast<HMIConfigJSON *>(destination->data);
                    header->ConfigSize = E_RESPONSE_IN_PROCESS;

                    // update size in destination
                    destination->size = (sizeof(HMIConfigJSON));

                    // set valid bit
                    destination->config = VALID_BIT;

                    // update retval to success
                    retVal = 0;
                }
                break;
            }

            case STATES::E_SUCCESS:
            {
                if(destination->size >= sizeof(HMIConfigJSON))
                {
                    //fill data
                    HMIConfigJSON *header = reinterpret_cast<HMIConfigJSON *>(destination->data);
                    header->ConfigSize = E_RESPONSE_SUCCESS;

                    // update size in destination
                    destination->size = (sizeof(HMIConfigJSON));

                    // set valid bit
                    destination->config = VALID_BIT;

                    // update retval to success
                    retVal = 0;
                }
                break;
            }

            case STATES::E_STATES_FAIL:
            {
                if(destination->size >= sizeof(HMIConfigJSON))
                {
                    //fill data
                    HMIConfigJSON *header = reinterpret_cast<HMIConfigJSON *>(destination->data);
                    header->ConfigSize = E_RESPONSE_FAIL;

                    // update size in destination
                    destination->size = (sizeof(HMIConfigJSON));

                    // set valid bit
                    destination->config = VALID_BIT;

                    // update retval to success
                    retVal = 0;
                }
                break;
            }
			default:
			{
				// Error ! default retVal (failure) will be returned
				// clear valid bit, reset size
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				break;
			}
		}
	}
	else
	{
		// error! invalid sub-id, default retVal (failure) will be returned
		// clear valid bit, reset size
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
	}
	return (retVal);
}

/**************************************************************************//***
* \brief   - Install JSON configuration receive from ASC
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int PlatformConfig::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
    bool status = false;

	// check parameter
	if((source != NULL) && (source->id == MB_ID_PLATFORM_CONFIG) && ((source->config & VALID_BIT) == (VALID_BIT)))
	{
        switch(this->m_CurrentState)
		{
			case STATES::E_WAITING_FOR_CONFIG:
			{
                char *JSONConfig;     /* HMI specific configuration elements in JSON format */

                // Retrive json size
                int JsonSize = *(reinterpret_cast<int *>(source->data));

                JSONConfig = new char [JsonSize + 1];

                memset(JSONConfig, 0, JsonSize + 1);
                memcpy(JSONConfig, source->data+sizeof(int), JsonSize);

                // Parse JSON
                status = ParseConfigJSON(JSONConfig);
                if (status)
                {
                    for (auto config_it : *(m_ActiveConfiguration))
                    {
                        // Load Configuration into RAM
                        retVal = config_it.second->SetConfigParameter(m_HMI_Config[config_it.first]);
                        if (retVal != 0)
                        {
                            status = false;

                            //Log Debug
                            snprintf(m_LogBuffer,buff_size_config,"Config parameter not supported for: %s", config_it.first.c_str());
                            Logger::add_entry(E_SEVERITY::E_LOG_DEB, m_LogBuffer);
                            break;
                        }
                    }

                }

                if (status)
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, "Configuration Exchange Success");
                    this->m_CurrentState = E_SUCCESS;
                }
                else
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Configuration Exchange Failed");
                    this->m_CurrentState = E_STATES_FAIL;
                }

				// update retval to success
				retVal = 0;

                // Delete JSON object
                delete[] JSONConfig;

				break;
			}

			case STATES::E_SUCCESS:
            case STATES::E_STATES_FAIL:
			{
				// do nothing
				retVal = 0;
				break;
			}

			default:
			{
				// Error ! default retVal (failure) will be returned
				break;
			}
		}
	}
	else
	{
		// error! parameter check failed, default retVal (failure) will be returned
	}
	return (retVal);
}

/**************************************************************************//**
* \brief   - Return configured parameter (received from ASC) using configuration tag.
*
* \param   - int         PeerId    -  Welder ID
*            std::string ConfigTag - Configuration Tag.
*
* \return  - If success return configured value, else returns -1 (failure)
*
******************************************************************************/
int PlatformConfig::GetConfigValue(int PeerId, std::string ConfigTag)
{
    int ConfigValue = -1;

    if (CommPeerWrapper::GetPeerData(PeerId) != NULL)
    {
        auto it = CommPeerWrapper::GetPeerData(PeerId)->GetActiveConfiguration()->find(ConfigTag);
        if (it != CommPeerWrapper::GetPeerData(PeerId)->GetActiveConfiguration()->end())
        {
            ConfigValue = it->second->GetConfigParameter();
        }
    }

    return ConfigValue;
}

/**************************************************************************//**
* \brief   - Return configured state.
*
* \param   - None.
*
* \return  - Configuration state
*            E_WAITING_FOR_CONFIG,
*            E_SUCCESS,
*            E_FAIL
*
******************************************************************************/
int PlatformConfig::GetConfigState()
{
    return m_CurrentState;
}

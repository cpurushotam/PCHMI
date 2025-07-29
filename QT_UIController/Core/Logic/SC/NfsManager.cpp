/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Nfs Manager Implementation on HMI side.
 ***************************************************************************/
#include <cstring>
#include "NfsManager.h"
#include "DataLogger.h"


/**************************************************************************//**
 *
 * \brief   - constructor
 *
 * \param   - none
 *
 * \return  - none
 *
 ******************************************************************************/
NfsManager::NfsManager()
{
	m_LogID = Logger::enroll(this);
	m_SendNfsMountRequest= false;
}

/**************************************************************************//**
 *
 * \brief   - destructor
 *
 * \param   - none
 *
 * \return  - none
 *
 ******************************************************************************/
NfsManager::~NfsManager() = default;

/**************************************************************************//**
 *
 * \brief   - Send the request to ASC server for nfs manager memory block
 *
 * \param   - destination - Memory block containing data to be sent to ASC
 *
 * \return  - 0 on success, -1 on failure
 *
 ******************************************************************************/
int NfsManager::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	if((destination != nullptr) && (destination->id == MB_ID_NFS_CONFIGURATION_DATA))
	{
		switch(destination->sub_id)
		{
		case NFS_MOUNT_REQUEST:
		{
			retVal = 0;
			SendNfsMountRequest(destination);
			break;
		}

		default:
		{
			destination->size = 0;
			destination->config = 0; // clear valid bit

			char  msg[buff_size_config] = {0};
			snprintf(msg,buff_size_config,"Invalid Request.");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
			break;
		}
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0; // clear valid bit

		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"Invalid MB ID :  MB_ID_NFS_CONFIGURATION_DATA");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}

	return retVal;
}

/**************************************************************************//**
 *
 * \brief   - process the data coming from ASC server
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - If success returns 0, else returns -1 (failure)
 *
 ******************************************************************************/
int NfsManager::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if( (source != nullptr) && (source->id == MB_ID_NFS_CONFIGURATION_DATA))
	{
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
			default:
			{
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config," Invalid nfs mount status request coming from ASC");
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				break;
			}
			}
		}
		else
		{
			retVal = 0;
		}
	}
	else
	{
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"Nfs Manager SetData invalid MB ID");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	return retVal;
}

/**************************************************************************//**
 *
 * \brief   - Send the nfs configuration save request to ASC
 *
 * \param   - destination - memory block to hold the request data.
 *
 * \return  - none
 *
 ******************************************************************************/
void NfsManager::SendNfsMountRequest(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(m_NfsConfigData))
	{
		if(m_SendNfsMountRequest == true)
		{
			NfsConfig* nfsConfigPtr  = reinterpret_cast<NfsConfig *>(destination->data);
			memcpy(nfsConfigPtr,&m_NfsConfigData,sizeof(m_NfsConfigData));
			destination->size = sizeof(m_NfsConfigData);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_SendNfsMountRequest = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}

/**************************************************************************//**
 *
 * \brief   - QML should call this method to on nfs configuration save request
 *
 * \param   - m_NfsConfigData - Data to be sent to ASC
 *
 * \return  - none
 *
 ******************************************************************************/
void NfsManager::InitiateNfsMountRequest(NfsConfig nfsConfiData)
{
	m_NfsConfigData = nfsConfiData;
	m_SendNfsMountRequest = true;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Implements communication statistics data interface, used for HMI-ASC communication

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.
 rev2: 05/06/2023 - Added feature to clear frame counter

***************************************************************************/

#include "CommStatAce.h"
#include <pthread.h>

/**************************************************************************//**
*
* \brief   - Read Communication statistics. Read operation is performed based on Sub_ID of MB
*
* \param   - Address of destination MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int comm_stat::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	// check parameter
	if((destination != NULL) && (destination->id == MB_ID_COMM_STAT) && (destination->size >=sizeof(comm_stat_data)))
	{
		// perform operation based on sub id
		// Note : No locks necessary as COMM class is expected to be only user
		switch(destination->sub_id)
		{
			case SUB_ID_OWN_STAT:
			{
				// locks get function
				pthread_mutex_lock(&m_comm_stat_mutex);

				// increment own counter
				this->m_own_stat.counter ++;

				// cast MB data pointer to comm_stat_data for easy access
				comm_stat_data *own_stat = reinterpret_cast<comm_stat_data *>(destination->data);

				// copy counter value to destination
				own_stat->counter = this->m_own_stat.counter;

				// update sub-id to PEER stat (this will be peer information for destination node)
				destination->sub_id = SUB_ID_PEER_STAT;

				// update size in destination
				destination->size = sizeof(comm_stat_data);

				// set valid bit
				destination->config = VALID_BIT;

				// update retval to success
				retVal = 0;

				// locks get function
				pthread_mutex_unlock(&m_comm_stat_mutex);

				break;
			}
			case SUB_ID_PEER_STAT:
			{
				// locks get function
				pthread_mutex_lock(&m_comm_stat_mutex);

				// cast MB data pointer to comm_stat_data for easy access
				comm_stat_data *peer_stat = reinterpret_cast<comm_stat_data *>(destination->data);

				// copy counter value to destination
				peer_stat->counter = this->m_peer_stat.counter;

				// update size in destination
				destination->size = sizeof(comm_stat_data);

				// set valid bit
				destination->config = VALID_BIT;

				// update retval to success
				retVal = 0;

				// locks get function
				pthread_mutex_unlock(&m_comm_stat_mutex);

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

/**************************************************************************//**
*
* \brief   - Write Communication statistics. Write operation is performed based on Sub_ID of MB
*            Note: Write operation on own statistics is not allowed.
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int comm_stat::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	// check parameter
	if((source != NULL) && (source->id == MB_ID_COMM_STAT) && ((source->config & VALID_BIT) == (VALID_BIT)))
	{
		// perform operation based on sub id
		// Note : No locks necessary as COMM class is expected to be only user
		switch(source->sub_id)
		{
			case SUB_ID_OWN_STAT:
			{

				// Error ! manual write on own stat not allowed !!

				// default retVal (failure) will be returned

				break;
			}
			case SUB_ID_PEER_STAT:
			{

				// locks get function
				pthread_mutex_lock(&m_comm_stat_mutex);

				// cast MB data pointer to comm_stat_data for easy access
				comm_stat_data *peer_stat = reinterpret_cast<comm_stat_data *>(source->data);

				// copy counter value to destination
				this->m_peer_stat.counter = peer_stat->counter;

				// update retval to success
				retVal = 0;

				// locks get function
				pthread_mutex_unlock(&m_comm_stat_mutex);

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
*
* \brief   - Clear own and peer frame counter 
*
* \param   - None.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int comm_stat::ClearCommStatCounter() 
{
	int retVal = 0;
	
	m_own_stat.counter = 0;
	m_peer_stat.counter = 0;
	
	return (retVal);
}




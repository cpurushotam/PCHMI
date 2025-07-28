/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Report Manager Implementation on HMI side.
 ***************************************************************************/
#include <cstring>
#include "ReportManager.h"
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
ReportManager::ReportManager()
{
	//enroll to use logger functionality
	m_LogID = Logger::enroll(this);
	m_ShouldSendReportGenerationRequest = false;
	m_ShouldSendReportGenerationCancellationRequest = false;
	m_ShouldSendReportGenerationProgressRequest = true;
	m_ReportGenerationProgressStatus = NOT_STARTED;
}

/**************************************************************************//**
 *
 * \brief   - QML should call this method to initiate report generation request
 *            on Generate Report button
 *
 * \param   - m_ReportConfigurationData - Data to be sent to ASC
 *
 * \return  - none
 *
 ******************************************************************************/
void ReportManager::InitiateReportGenerationRequest(ReportConfig reportConfigData)
{
	m_ReportConfigurationData = reportConfigData;
	m_ShouldSendReportGenerationRequest = true;
}

/**************************************************************************//**
 *
 * \brief   - QML should call this method to initiate current report cancellation
 *
 * \param   - isReportGenerationCancelled - Data to be sent to ASC
 *
 * \return  - none
 *
 ******************************************************************************/
void ReportManager::InitialteReportGenerationCancellationRequest(bool isReportGenCancelled)
{
	m_ShouldSendReportGenerationCancellationRequest = isReportGenCancelled;
}

/**************************************************************************//**
 *
 * \brief   - QML should call this method to check the report progress status
 *
 * \param   - none
 *
 * \return  - Report Generation Status
 *
 ******************************************************************************/
PROGRESS_STATUS ReportManager::GetReportGenerationProgressStatus()
{
	return m_ReportGenerationProgressStatus;
}

/**************************************************************************//**
 *
 * \brief   - Send the request to ASC server for report generation memory block
 *
 * \param   - destination - Memory block containing data to be sent to ASC
 *
 * \return  - 0 on success, -1 on failure
 *
 ******************************************************************************/
int ReportManager::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	if((destination != nullptr) && (destination->id == MB_ID_REPORT_GENERATION_DATA))
	{
		switch(destination->sub_id)
		{
		case REPORT_GENERATION_REQUEST:
		{
			retVal = 0;
			SendReportGenerationRequest(destination);
			break;
		}

		case REPORT_CANCELLATION_REQUEST:
		{
			retVal = 0;
			SendReportGenerationCancellationRequest(destination);
			break;
		}

		case REPORT_GENE_PROGRESS_STATUS_REQUEST:
		{
			retVal = 0;
			SendReportGenerationProgressStatusRequest(destination);
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
		snprintf(msg,buff_size_config,"Invalid MB ID :  MB_ID_REPOST_GENERATION_DATA");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}

	return retVal;
}

/**************************************************************************//**
 *
 * \brief   - Send the current report cancellation request to ASC
 *
 * \param   - destination - memory block to hold the request data.
 *
 * \return  - none
 *
 ******************************************************************************/
void ReportManager::SendReportGenerationCancellationRequest(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(bool))
	{
		if(m_ShouldSendReportGenerationCancellationRequest == true)
		{
			destination->data = 0;
			destination->size = sizeof(bool);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_ShouldSendReportGenerationCancellationRequest = false;
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
 * \brief   - Send the report generation request to ASC
 *
 * \param   - destination - memory block to hold the request data.
 *
 * \return  - none
 *
 ******************************************************************************/
void ReportManager::SendReportGenerationRequest(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(m_ReportConfigurationData))
	{
		if(m_ShouldSendReportGenerationRequest == true)
		{
			ReportConfig* reportConfPtr  = reinterpret_cast<ReportConfig *>(destination->data);
			memcpy(reportConfPtr,&m_ReportConfigurationData,sizeof(m_ReportConfigurationData));
			destination->size = sizeof(m_ReportConfigurationData);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_ShouldSendReportGenerationRequest = false;
			m_ReportConfigurationData.resetToDefault();
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
 * \brief   - Send the report generation progress status to ASC
 *
 * \param   - destination - memory block to hold the request data.
 *
 * \return  - none
 *
 ******************************************************************************/
void ReportManager::SendReportGenerationProgressStatusRequest(MEMORY_BLOCK *const destination)
{
	if(destination->size >= sizeof(bool))
	{
		if(m_ShouldSendReportGenerationProgressRequest == true)
		{
			destination->data = 0;
			destination->size = sizeof(bool);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_ShouldSendReportGenerationProgressRequest = false;
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
 * \brief   - process the data coming from ASC server for report generation memory block
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \return  - If success returns 0, else returns -1 (failure)
 *
 ******************************************************************************/
int ReportManager::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;

	if( (source != nullptr) && (source->id == MB_ID_REPORT_GENERATION_DATA))
	{
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
			case REPORT_GENE_PROGRESS_STATUS_REQUEST:
			{
				retVal = 0;
				ProcessReportGenerationProgressStatusResponse(source);
				break;
			}

			default:
			{
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config," Invalid Request coming from ASC");
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
		snprintf(msg,buff_size_config,"Report Generation SetData invalid MB ID");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	return retVal;
}

/**************************************************************************//**
 *
 * \brief   - Process the report generation progress status coming from ASC
 *
 * \param   - source - Memory block containing data coming from ASC
 *
 * \todo    - Implement the function logic to process the report generation progress status
 * 			  e.g. Completed, Failed
 *
 * \return  - none
 *
 *
 ******************************************************************************/
void ReportManager::ProcessReportGenerationProgressStatusResponse(const MEMORY_BLOCK *const source)
{
	if (source && source->data)
	{
		PROGRESS_STATUS* Data = reinterpret_cast<PROGRESS_STATUS*>(source->data);
		std::memcpy(&m_ReportGenerationProgressStatus, Data, sizeof(PROGRESS_STATUS));
	}
	else
	{
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"Invalid source or source->data is null.");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
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
ReportManager::~ReportManager() = default;

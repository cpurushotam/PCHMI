/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Weld Report Manager Implementation on HMI side.
 
***************************************************************************/

#ifndef REPORTMANAGER_H_
#define REPORTMANAGER_H_

#include "DataInterface.h"
#include "ReportConfig.h"

class ReportManager : public DataInterface
{
	public :
		ReportManager();
		~ReportManager();

		int GetData(MEMORY_BLOCK * const destination) override;
		int SetData(const MEMORY_BLOCK *const source) override;
		void InitiateReportGenerationRequest(ReportConfig reportConfigData);
		void InitialteReportGenerationCancellationRequest(bool isReportGenCancelled);
		PROGRESS_STATUS GetReportGenerationProgressStatus();

	private :
		size_t m_LogID;
		//Stores the Report Generation Data Coming From HMI
		ReportConfig m_ReportConfigurationData;
		//Stores the Report Generation Progress Status Coming From ASC
		PROGRESS_STATUS m_ReportGenerationProgressStatus;
		bool m_ShouldSendReportGenerationRequest;
		bool m_ShouldSendReportGenerationCancellationRequest;
		bool m_ShouldSendReportGenerationProgressRequest;

		void SendReportGenerationRequest(MEMORY_BLOCK * const destination);
		void SendReportGenerationCancellationRequest(MEMORY_BLOCK * const destination);
		void SendReportGenerationProgressStatusRequest(MEMORY_BLOCK * const destination);
		void ProcessReportGenerationProgressStatusResponse(const MEMORY_BLOCK *const source);
};
#endif /* REPORTMANAGER_H_ */

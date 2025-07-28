/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Report Generation Configuration common for HMI and ASC
 ***************************************************************************/
#ifndef REPORT_CONFIG_H_
#define REPORT_CONFIG_H_

#include <string.h>
#include "Common_Definitions.h"

typedef enum
{
	REPORT_GENERATION_REQUEST = 1,
	REPORT_CANCELLATION_REQUEST,
	REPORT_GENE_PROGRESS_STATUS_REQUEST
} REPORT_GENERATION_SUB_ID;

typedef enum
{
	USB,
	NFS
} STORAGE_OPTIONS;

typedef enum
{
	CSV,
	PDF
} REPORT_FORMATS;

typedef enum
{
	NOT_DELETE,
    IS_DELETE //kb
} DELETION_STATUS;

typedef enum
{
	NOT_STARTED,
	IN_PROGRESS,
	COMPLETED,
	CANCELLED
} PROGRESS_STATUS;

typedef enum
{
	WELD_RESULT_RERORT                     = 1 << 0,  // 1st bit (000000001 in binary) - Weld Result Type Report (1)
	WELD_GRAPH_REPORT                      = 1 << 1,  // 2nd bit (000000010 in binary) - Weld Graph Type Report  (2)
	ALARM_LOG_REPORT                       = 1 << 2,  // Decimal value 4
	EVENT_LOG_REPORT                       = 1 << 3,  // Decimal value 8
	HORN_SCAN_RESULT_REPORT                = 1 << 4,  // Decimal value 16
	HORN_SCAN_SIGNATURE_REPORT             = 1 << 5,  // Decimal value 32
	REFERENCE_WELD_SIGNATURE_REPORT        = 1 << 6,  // Decimal value 64
	CALIBRATION_DATA_REPORT                = 1 << 7,  // Decimal value 128

} REPORT_CATEGORY;

typedef struct ReportConfig
{
	STORAGE_OPTIONS storageOptions;
	REPORT_FORMATS reportFormats;
	PROGRESS_STATUS progressFlags;
	uint32_t reportFlags;
	uint32_t deleteFlags;

	//Initialize default values
	ReportConfig()
	{
		resetToDefault();
	}

	void resetToDefault()
	{
		storageOptions = USB;
		reportFormats = CSV;
		reportFlags = 0;
		deleteFlags = static_cast<uint32_t>(NOT_DELETE);
		progressFlags = NOT_STARTED;
	}

	//To Select the Storage Option, default USB
	void SelectStorageOption(STORAGE_OPTIONS storageType)
	{
		storageOptions = storageType;
	}

	//To select report format, default CSV
	void SelectReportFormat(REPORT_FORMATS formatType)
	{
		reportFormats = formatType;
	}

	//To select the specific type of report
	void SelectReport(REPORT_CATEGORY reportType)
	{
		reportFlags |= reportType;
	}

	//To disselect the specific type of report
	void DisselectReport(REPORT_CATEGORY reportType)
	{
		reportFlags &= ~reportType;
	}

	//To delete specific selected report
	void DeleteReport(REPORT_CATEGORY reportType)
	{
		deleteFlags |= reportType;
	}

	//To reset delete specific report
	void ResetDeleteReport(REPORT_CATEGORY reportType)
	{
		deleteFlags &= ~reportType;
	}

	//To delete all selected reports on single click
	void DeleteAllReports()
	{
		deleteFlags = reportFlags;
	}

	//To reset delete all selected reports on single click
	void ResetDeleteAllReports()
	{
		deleteFlags = static_cast<uint32_t>(NOT_DELETE);
	}

}__attribute__((packed))ReportConfig;

#endif //REPORT_CONFIG_H_

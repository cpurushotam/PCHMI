
/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    GenerateReportComman.cpp file provides mode details and status of button and checkboxses.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 17/02/2025 - Initial version.
***************************************************************************/
#ifndef GENERATEREPORTCOMMAN_H
#define GENERATEREPORTCOMMAN_H
#include "ReportConfig.h"
#include "ReportManager.h"
#include <QObject>
#include <memory>
#include "UpdateScreens.h"

class GenerateReportComman:public QObject
{
    Q_OBJECT
public:

     GenerateReportComman(QObject *parent = nullptr);
    ~GenerateReportComman();
    Q_INVOKABLE bool m_TypeRadioButton = true;
    Q_INVOKABLE bool m_EncryptRadioButton = false;
    Q_INVOKABLE bool m_StorageoptButton = false;
    Q_INVOKABLE bool m_OutputRadioButton = true;
    Q_INVOKABLE bool m_StorageRadioButton = false;
    Q_INVOKABLE bool m_SaveOnAlarmRadioButton = false;

    Q_INVOKABLE void setMode(QString filterMode ,int index,bool checkState);
    Q_INVOKABLE QString getMode(int index);
    Q_INVOKABLE void setDeleteRecord(bool deleteRecordchecks ,int index);
    Q_INVOKABLE bool getDeleteRecord(int index);
    Q_INVOKABLE bool getCheckedFilterModeStatus(int index);
    Q_INVOKABLE QString getDatafiltersList();
    Q_INVOKABLE void ClearTheFilterList();
    Q_INVOKABLE void updateReportType(bool reportType);
    Q_INVOKABLE void onCheckboxSelectionFormatType(int formatType);
    Q_INVOKABLE void onCheckboxSelectionStorageOption(int storgaeOption);
    Q_INVOKABLE void onCheckboxSelectionDataFilter(int dataFilter);
    Q_INVOKABLE void onSelectDeleteReport(int reportType);
    Q_INVOKABLE void onDeSelectDeleteReport(int reportType);
    Q_INVOKABLE void onGenerateReportClicked();
    Q_INVOKABLE PROGRESS_STATUS onStatusChanged();
    Q_INVOKABLE void onDeSelectReport(int dataFilter);


private:
    ReportConfig m_ReportConfig;
    ReportManager * m_ReportManger;

    QString m_ReportType;
    int m_ModeListCount = 8;
    struct datafilters{
        QString m_filterMode;
        bool m_deleterecordchecks = false;
    };
     struct datafilters m_mode[8];

public slots:
    void onSingleGenerateReportUpdated(ReportManager *ReportManager_Obj );
};

#endif // GENERATEREPORTCOMMAN_H

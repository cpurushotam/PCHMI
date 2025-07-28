/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Branson Service Interface class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef BransonServiceInterface_H
#define BransonServiceInterface_H

#include <QObject>
#include "SystemConfigBransonServiceStructure.h"
#include "UpdateScreens.h"
#include "BransonServiceTab.h"

class BransonServiceInterface : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/

    Q_PROPERTY(int emmcMemUsage  READ getemmcMemUsage  NOTIFY servicenoteChanged)


public:
    explicit BransonServiceInterface(QObject *parent = nullptr);

    Q_INVOKABLE void factoryResetRequest();
    Q_INVOKABLE void dbDeleteRequest();
    Q_INVOKABLE void copyDbFilesToUSBRequest();
    Q_INVOKABLE void systemCleanedRequest();
    Q_INVOKABLE void serviceNotesDetailsRequest(const QString& serviceNOte);
    Q_INVOKABLE int maxNotesChars();
    Q_INVOKABLE int emmcMemoryUsgae();
    Q_INVOKABLE void serviceTabLoaded();
    Q_INVOKABLE int getNofServiceNotes();
    Q_INVOKABLE QString getServiceNote(int Index);
    Q_INVOKABLE QString getServiceNoteDateTime(int Index);
    Q_INVOKABLE QString getServiceResponse();
    Q_INVOKABLE int getServiceResponseCode();
    Q_INVOKABLE void getOldBoardNewBoardName(const QString &OldBoard, const QString &NewBoard,  const QString &BoardName);

    int getemmcMemUsage() ;

signals:
    /*Signals used to notify QML*/
    void servicenoteChanged();
    void bransonServiceStatusMessage();

private:
    /*Holds Branson System Configuration data*/
    std::deque<BransonServiceTabStructure> m_BransonServiceLogData;

    BransonServiceTab *m_BransonServiceTab;

    BRANSON_SERVICE_REQUESTS_RESPONSE_CODES m_ReceviedResponse ;

    QString m_ServiceNote;

    QString m_DateTime;

    int m_emmcMemUsage;

    int m_ActiveWelderId = -1;


private slots:
    void OnBransonServiceInterfaceUpdated(BransonServiceTab *BransonServiceTab_Obj, int welderId);
};

#endif // BransonServiceInterface_H



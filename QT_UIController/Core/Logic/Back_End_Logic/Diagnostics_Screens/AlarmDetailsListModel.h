/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AlarmDetailsListModel.h file handles alarm details list model container.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/05/2024 - Initial version.
***************************************************************************/
#ifndef ALARMDETAILSLISTMODEL_H
#define ALARMDETAILSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QSettings>
#include "UpdateScreens.h"
#include "AlarmDetailsListData.h"
#include "WeldResultAce.h"
#include "AlarmLog.h"
#include "AlarmNames.h"

class AlarmDetailsListModel : public QAbstractListModel
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT   
    Q_PROPERTY(bool AlarmCountCheck           READ getAlarmCountCheck           NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool WarningCountCheck         READ getWarningCountCheck         NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool NotificationsCountCheck   READ getNotificationsCountCheck   NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(int  ServiceReminderCountCheck READ getServiceReminderCountCheck NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(int  AlarmCount                READ getAlarmCount                NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(int  WarningCount              READ getWarningCount              NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(int  NotificationsCount        READ getNotificationsCount        NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(int  ServiceReminderCount      READ getServiceReminderCount      NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool IsScreenNavigatedFromAlarmsPopup          READ getIsScreenNavigatedFromAlarmsPopup          WRITE updateIsScreenNavigatedFromAlarmsPopup          NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool IsScreenNavigatedFromWarningsPopup        READ getIsScreenNavigatedFromWarningsPopup        WRITE updateIsScreenNavigatedFromWarningsPopup        NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool IsScreenNavigatedFromNotificationsPopup   READ getIsScreenNavigatedFromNotificationsPopup   WRITE updateIsScreenNavigatedFromNotificationsPopup   NOTIFY alarmDetailsListDataChanged)
    Q_PROPERTY(bool IsScreenNavigatedFromServiceReminderPopup READ getIsScreenNavigatedFromServiceReminderPopup WRITE updateIsScreenNavigatedFromServiceReminderPopup NOTIFY alarmDetailsListDataChanged)

public:
    enum AlarmRoles
    {
        IndexRole = Qt::UserRole + 1,
        AlarmErrorTypeRole,
        AlarmIDRole,
        AlarmSubTypeRole,
        AlarmRecipeNoRole,
        AlarmRecipeVersionRole,
        AlarmCycleNoRole,
        AlarmDateTimeRole,
        AlarmUserNameRole,
        AlarmTypeRole,
        AlarmAddNotesRole,
        AlarmLogIndexRole
    };

public:
    explicit AlarmDetailsListModel(QObject *parent = nullptr);
    ~AlarmDetailsListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;

    Q_INVOKABLE void isScreenReNavigated(bool Value);
    Q_INVOKABLE void loadAlarmDetailsList();
    Q_INVOKABLE void reset();
    Q_INVOKABLE QString getSaveNotes(int index);
    Q_INVOKABLE void updateSaveNotes(QString SaveNotes, int index);
    Q_INVOKABLE int getMaxCharInput();

    Q_INVOKABLE int getAlarmSubCategory(ALARM_IDS AlarmID);
    Q_INVOKABLE QString getAlarmTypeString(ALARM_IDS AlarmID);
    Q_INVOKABLE QString getAlarmDescriptionString(ALARM_IDS AlarmID);
    Q_INVOKABLE QString getAlarmProbableReasonString(ALARM_IDS AlarmID);
    Q_INVOKABLE bool isActiveAlarm(ALARM_IDS AlarmID);
    Q_INVOKABLE void onResetAlarmPressed(ALARM_IDS AlarmID);
    Q_INVOKABLE bool getHornClampOnAlarmStatus();

    Q_INVOKABLE void isScreenNavigatedWhenAlarmLogIsVisibleFromAlarmsPopup(bool Value);
    Q_INVOKABLE void isScreenNavigatedWhenAlarmLogIsVisibleFromWarningsPopup(bool Value);
    Q_INVOKABLE void isScreenNavigatedWhenAlarmLogIsVisibleFromNotificationsPopup(bool Value);
    Q_INVOKABLE void isScreenNavigatedWhenAlarmLogIsVisibleFromServiceReminderPopup(bool Value);

private:

    /*List of private varibles used by methods under RecipeLabData class*/
    bool m_IsScreenReNavigated;
    bool m_AlarmCountCheck;
    bool m_WarningCountCheck;
    bool m_NotificationsCountCheck;
    bool m_ServiceReminderCountCheck;
    int m_AlarmCount = 0;
    int m_WarningCount = 0;
    int m_NotificationsCount = 0;
    int m_ServiceReminderCount = 0;
    bool m_IsScreenNavigatedFromAlarmsPopup = false;
    bool m_IsScreenNavigatedFromWarningsPopup = false;
    bool m_IsScreenNavigatedFromNotificationsPopup = false;
    bool m_IsScreenNavigatedFromServiceReminderPopup = false;

    /*List of get and set functions to update qml variables*/
    bool getAlarmCountCheck() const;

    bool getWarningCountCheck() const;

    bool getNotificationsCountCheck() const;

    bool getServiceReminderCountCheck() const;

    int getAlarmCount() const;

    int getWarningCount() const;

    int getNotificationsCount() const;

    int getServiceReminderCount() const;

    bool getIsScreenNavigatedFromAlarmsPopup() const;
    void updateIsScreenNavigatedFromAlarmsPopup(const bool& IsScreenNavigatedFromAlarmsPopup);

    bool getIsScreenNavigatedFromWarningsPopup() const;
    void updateIsScreenNavigatedFromWarningsPopup(const bool& IsScreenNavigatedFromWarningsPopup);

    bool getIsScreenNavigatedFromNotificationsPopup() const;
    void updateIsScreenNavigatedFromNotificationsPopup(const bool& IsScreenNavigatedFromNotificationsPopup);

    bool getIsScreenNavigatedFromServiceReminderPopup() const;
    void updateIsScreenNavigatedFromServiceReminderPopup(const bool& IsScreenNavigatedFromServiceReminderPopup);

    int m_ActiveWelderId = -1;
    /*Holds historical alarm log data*/
    AlarmMgrACE *m_AlarmMgrACE;

    /*Holds historical alarm log data*/
    std::deque<AlarmLogEntry> m_HistoricalAlarmLogData;

    /*Holds active alarm data*/
    std::deque<ActiveAlarmEntry> m_ActiveAlarmData;

    AlarmNames m_AlarmNames;

    /*For service name reminder name extraction*/
    ServiceManagement *m_ServiceManagement;
    std::map<int,reminderListStruct> m_ServiceReminderDetails;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:

    QList<AlarmDetailsListData*> m_ListData;

    void createNewAlarmDetailsList();
    void clearAlarmDetailsList();
    void addNewAlarmDetailsList(AlarmDetailsListData *AlarmDetailsList);

    pthread_mutex_t mtx;

    /*Signals used to notify qml screen*/
signals:
    void alarmDetailsListDataChanged();
    void alarmDetailsPressed();
    void warningDetailsPressed();
    void notificationDetailsPressed();
    void serviceReminderDetailsPressed();

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnAlarmDetailsListUpdated(AlarmMgrACE *AlarmEventsLogScreen_Obj, ServiceManagement *ServiceManagement_Obj, int WelderId);
};
#endif // ALARMDETAILSLISTMODEL_H

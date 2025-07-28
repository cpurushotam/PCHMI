/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AlarmDetailsListModel.cpp file handles Alarm details list model container includes :
    Alarm counts, date and time.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 30/05/2024 - Initial version.
***************************************************************************/
#include "AlarmDetailsListModel.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <algorithm>
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
AlarmDetailsListModel::AlarmDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::AlarmEventsLogUpdated, this, &AlarmDetailsListModel::OnAlarmDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
AlarmDetailsListModel::~AlarmDetailsListModel()
{
    qDeleteAll(m_ListData.begin(), m_ListData.end());
    m_ListData.clear();
}

/**************************************************************************//**
*
* \brief - Qt Item model standard interface
*          The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*          Note: This function can be invoked via the meta-object system and from QML.
*          To get the list size number.
*
* \param  - QModelIndex object to determine the size.
*
* \return - Return weld alarm details list size.
*
******************************************************************************/
int AlarmDetailsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ListData.count();
}

/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*           The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*           To locate at the specific object using the Model Index and get the data from the specific object then.
*           Note: This function can be invoked via the meta-object system and from QML.
*           Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index and role : To determine the row for designated role.
*
* \return - The property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant AlarmDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const AlarmDetailsListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {
    case AlarmErrorTypeRole:
        return ptrListObj->getErrorType();
        break;

    case AlarmIDRole:
        return ptrListObj->getAlarmID();
        break;

    case AlarmSubTypeRole:
        return ptrListObj->getAlarmSubType();
        break;

    case AlarmRecipeNoRole:
        return ptrListObj->getRecipeNo();
        break;

    case AlarmRecipeVersionRole:
        return ptrListObj->getRecipeVersion();
        break;

    case AlarmCycleNoRole:
        return ptrListObj->getCycleNo();
        break;

    case AlarmDateTimeRole:
        return ptrListObj->getCycleDateTime();
        break;

    case AlarmUserNameRole:
        return ptrListObj->getUserName();
        break;

    case AlarmTypeRole:
        return ptrListObj->getAlarmType();
        break;

    case AlarmAddNotesRole:
        return ptrListObj->getAddedNotes();
        break;

    case AlarmLogIndexRole:
        return ptrListObj->getAlarmLogIndex();
        break;

    default:
        return QVariant();
        break;
    }

    return QVariant();
}

/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*         - The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*         - Returns the index of the data in row and column with parent.
*         - Note: This function can be invoked via the meta-object system and from QML.
*         - Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index.row should be in the range of the weld cycle details list.
*
* \return - If the row is in the range of the weld cycle details list,
*         - the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex AlarmDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    AlarmDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<AlarmDetailsListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - Value : Status of request.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief - To clear the alarm details list.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void AlarmDetailsListModel::clearAlarmDetailsList()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    qDeleteAll(m_ListData);
    m_ListData.clear();
    endRemoveRows();
}

/**************************************************************************//**
*
* \brief - Below function add new content into the detail list.  .
*
* \param  - AlarmDetailsList : List data of type AlarmDetailsList.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::addNewAlarmDetailsList(AlarmDetailsListData *AlarmDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(AlarmDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadAlarmDetailsList function called by qml while loading of
*            alarm detail list, to display available alarm details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::loadAlarmDetailsList()
{
    createNewAlarmDetailsList();
    clearAlarmDetailsList();

    AlarmDetailsListData* ptrListObj = nullptr;
    m_AlarmCount = 0; m_WarningCount = 0; m_NotificationsCount = 0; m_ServiceReminderCount = 0;
    int m_AlarmID;
    int m_IndexID;
   for (unsigned int Index = 0; Index < m_HistoricalAlarmLogData.size(); Index++)
   {
       int i_AlarmID = getAlarmSubCategory(m_HistoricalAlarmLogData[Index].AlarmID);

       if (i_AlarmID == ALARM_SUBCAT)
           m_AlarmCount++;
       if (i_AlarmID == WARNING_SUBCAT)
           m_WarningCount++;
       if  (i_AlarmID == NOTIFICATION_SUBCAT)
           m_NotificationsCount++;
       if  (i_AlarmID == REMINDER_SUBCAT)
       {
           m_ServiceReminderCount++;
           m_AlarmID = (static_cast<int> (m_HistoricalAlarmLogData[Index].AlarmID));
           m_IndexID = (m_AlarmID % 10);

           if(m_IndexID == 0)
           {
               m_IndexID = 10;
           }
       }

       /* Below conditional statement is to distinguish the alarms between service reminder and rest of others, as it needs service name to be fetch from service management class.
          Along with this we used UserName parameter to send service name of service reminder as UserName parameter is unused in service reminder case*/
       if(i_AlarmID != REMINDER_SUBCAT)
       {
           ptrListObj = new AlarmDetailsListData(m_HistoricalAlarmLogData[Index].AlarmType, m_HistoricalAlarmLogData[Index].AlarmID, i_AlarmID,
                                                 m_HistoricalAlarmLogData[Index].WeldRecipeNumber, m_HistoricalAlarmLogData[Index].WeldRecipeVersionNumber,
                                                 m_HistoricalAlarmLogData[Index].CycleCounter, m_HistoricalAlarmLogData[Index].DateTime,
                                                 m_HistoricalAlarmLogData[Index].UserName, m_HistoricalAlarmLogData[Index].AlarmType, m_HistoricalAlarmLogData[Index].AlarmNotes, m_HistoricalAlarmLogData[Index].AlarmLogIndex);

       }

       else
       {
           ptrListObj = new AlarmDetailsListData(m_HistoricalAlarmLogData[Index].AlarmType, m_HistoricalAlarmLogData[Index].AlarmID, i_AlarmID,
                                                 m_HistoricalAlarmLogData[Index].WeldRecipeNumber, m_HistoricalAlarmLogData[Index].WeldRecipeVersionNumber,
                                                 m_HistoricalAlarmLogData[Index].CycleCounter, m_HistoricalAlarmLogData[Index].DateTime,
                                                 m_ServiceReminderDetails[m_IndexID - 1].serviceName, m_HistoricalAlarmLogData[Index].AlarmType, m_HistoricalAlarmLogData[Index].AlarmNotes, m_HistoricalAlarmLogData[Index].AlarmLogIndex);

       }

       addNewAlarmDetailsList(ptrListObj);
   }
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type AlarmDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::createNewAlarmDetailsList()
{
    AlarmDetailsListData* ptrListObj = new AlarmDetailsListData();
    addNewAlarmDetailsList(ptrListObj);
}

/**************************************************************************//**
*
* \brief - Below function perform the reset operation on request.
*
* \param  - TBD.
*
* \return - TBD.
*
******************************************************************************/
void AlarmDetailsListModel::reset()
{
    m_AlarmMgrACE->SetResetAllActiveAlarm();
}

/**************************************************************************//**
*
* \brief - Below function fetches the saved notes.
*
* \param  - Index : Index for which saved notes to be fetch.
*
* \return - TBD.
*
******************************************************************************/
QString AlarmDetailsListModel::getSaveNotes(int Index)
{
/*TBD*/
}

/**************************************************************************//**
*
* \brief - Below function updates the saved notes.
*
* \param  - SaveNotes : Notes provided by user via HMI.
*           Index : Index for which saved notes to be fetch.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::updateSaveNotes(QString SaveNotes, int index)
{
    m_AlarmMgrACE->SetAddAlarmNotesFlag(index ,SaveNotes.toStdString());
}

/**************************************************************************//**
*
* \brief - Below returns the maximum input characters that user can enter for Alarm Add Notes
*
* \param  - None
*
* \return - Maximum number of characters.
*
******************************************************************************/
int AlarmDetailsListModel::getMaxCharInput()
{
    return ALARM_NOTES_SIZE - 1;
}
/**************************************************************************//**
*
* \brief - Below function fetches the alarm's sub category.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - m_AlarmString : The alarm's sub category.
*
******************************************************************************/
int AlarmDetailsListModel::getAlarmSubCategory(ALARM_IDS AlarmID)
{
    ALARM_SUBCATEGORY retVal;

    retVal = m_AlarmNames.GetAlarmSubcategory(AlarmID);
    return retVal;
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarm's type.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - m_AlarmString : The alarm's type.
*
******************************************************************************/
QString AlarmDetailsListModel::getAlarmTypeString(ALARM_IDS AlarmID)
{
    std::string m_AlarmString;

    m_AlarmString = m_AlarmNames.GetAlarmErrorType(AlarmID);
    return QString::fromLocal8Bit(m_AlarmString.c_str());
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarm's description.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - m_AlarmString : The alarm's description.
*
******************************************************************************/
QString AlarmDetailsListModel::getAlarmDescriptionString(ALARM_IDS AlarmID)
{
    std::string m_AlarmString;

    m_AlarmString = m_AlarmNames.GetAlarmDescription(AlarmID);
    return QString::fromLocal8Bit(m_AlarmString.c_str());
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarm's probable reason.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - m_AlarmString : The alarm's probable reason.
*
******************************************************************************/
QString AlarmDetailsListModel::getAlarmProbableReasonString(ALARM_IDS AlarmID)
{
    std::string m_AlarmString;

    m_AlarmString = m_AlarmNames.GetAlarmReason(AlarmID);
    return QString::fromLocal8Bit(m_AlarmString.c_str());
}

/**************************************************************************//**
*
* \brief - Below function fetches the status whether given alarm id is active or not.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - flag : The status whether given alarm is active or not.
*
******************************************************************************/
bool AlarmDetailsListModel::isActiveAlarm(ALARM_IDS AlarmID)
{
    bool activeAlarmFlag = false;
    for (unsigned int Index = 0; Index < m_ActiveAlarmData.size(); Index++)
    {

        if(m_ActiveAlarmData[Index].AlarmID == AlarmID)
        {
            activeAlarmFlag = true;
            break;
        }

        else
        {
            activeAlarmFlag = false;
        }
    }

    return activeAlarmFlag;
}

/**************************************************************************//**
*
* \brief - Below function reset the active alarm for given alarm id.
*
* \param  - AlarmID : Alarm's ID.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::onResetAlarmPressed(ALARM_IDS AlarmID)
{
    m_AlarmMgrACE->SetAlarmIDtoBeReset(AlarmID);
}

/**************************************************************************//**
*
* \brief - Below function determines whether the alarms log screen called when
*          its visible or not.
*
* \param  - Value : The alarm log screen visible status.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::isScreenNavigatedWhenAlarmLogIsVisibleFromAlarmsPopup(bool Value)
{
    if (Value)
    {
        emit alarmDetailsPressed();
    }
}

/**************************************************************************//**
*
* \brief - Below function determines whether the warning log screen called when
*          its visible or not.
*
* \param  - Value : The warning log screen visible status.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::isScreenNavigatedWhenAlarmLogIsVisibleFromWarningsPopup(bool Value)
{
    if (Value)
    {
        emit warningDetailsPressed();
    }
}

/**************************************************************************//**
*
* \brief - Below function determines whether the notifications log screen called when
*          its visible or not.
*
* \param  - Value : The notifications log screen visible status.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::isScreenNavigatedWhenAlarmLogIsVisibleFromNotificationsPopup(bool Value)
{
    if (Value)
    {
        emit notificationDetailsPressed();
    }
}

/**************************************************************************//**
*
* \brief - Below function determines whether the service reminder screen called when
*          its visible or not.
*
* \param  - Value : The service reminder screen visible status.
*
* \return - None.
*
******************************************************************************/
void AlarmDetailsListModel::isScreenNavigatedWhenAlarmLogIsVisibleFromServiceReminderPopup(bool Value)
{
    if (Value)
    {
        emit serviceReminderDetailsPressed();
    }
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarms count check status.
*
* \param  - None.
*
* \return - m_AlarmCountCheck : The alarms count check status.
*
******************************************************************************/
bool AlarmDetailsListModel::getAlarmCountCheck() const
{
    return m_AlarmCountCheck;
}

/**************************************************************************//**
*
* \brief - Below function fetches the warnings count check status.
*
* \param  - None.
*
* \return - m_WarningCountCheck : The warnings count check status.
*
******************************************************************************/
bool AlarmDetailsListModel::getWarningCountCheck() const
{
    return m_WarningCountCheck;
}

/**************************************************************************//**
*
* \brief - Below function fetches the notifications reminders count check status.
*
* \param  - None.
*
* \return - m_NotificationsCountCheck : The notifications count check status.
*
******************************************************************************/
bool AlarmDetailsListModel::getNotificationsCountCheck() const
{
    return m_NotificationsCountCheck;
}

/**************************************************************************//**
*
* \brief - Below function fetches the service reminders count check status.
*
* \param  - None.
*
* \return - m_ServiceReminderCountCheck : The service reminders count check status.
*
******************************************************************************/
bool AlarmDetailsListModel::getServiceReminderCountCheck() const
{
    return m_ServiceReminderCountCheck;
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarms count.
*
* \param  - None.
*
* \return - m_AlarmCount : The alarms count.
*
******************************************************************************/
int AlarmDetailsListModel::getAlarmCount() const
{
    return m_AlarmCount;
}

/**************************************************************************//**
*
* \brief - Below function fetches the warnings count.
*
* \param  - None.
*
* \return - m_WarningCount : The warnings count.
*
******************************************************************************/
int AlarmDetailsListModel::getWarningCount() const
{
    return m_WarningCount;
}

/**************************************************************************//**
*
* \brief - Below function fetches the notifications count.
*
* \param  - None.
*
* \return - m_NotificationsCount : The notifications count.
*
******************************************************************************/
int AlarmDetailsListModel::getNotificationsCount() const
{
    return m_NotificationsCount;
}

/**************************************************************************//**
*
* \brief - Below function fetches the service reminder count.
*
* \param  - None.
*
* \return - m_ServiceReminderCount : The service reminder count.
*
******************************************************************************/
int AlarmDetailsListModel::getServiceReminderCount() const
{
    return m_ServiceReminderCount;
}

/**************************************************************************//**
*
* \brief   - Below function returns screen navigation status.
*
* \param   - None.
*
* \return  - m_IsScreenNavigatedFromAlarmsPopup : The navigation status.
******************************************************************************/
bool AlarmDetailsListModel::getIsScreenNavigatedFromAlarmsPopup() const
{
    return m_IsScreenNavigatedFromAlarmsPopup;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - IsScreenNavigatedFromAlarmsPopup : The navigation status.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::updateIsScreenNavigatedFromAlarmsPopup(const bool &IsScreenNavigatedFromAlarmsPopup)
{
    m_IsScreenNavigatedFromAlarmsPopup = IsScreenNavigatedFromAlarmsPopup;
    emit alarmDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns screen navigation status.
*
* \param   - None.
*
* \return  - m_IsScreenNavigatedFromWarningsPopup : The navigation status.
******************************************************************************/
bool AlarmDetailsListModel::getIsScreenNavigatedFromWarningsPopup() const
{
    return m_IsScreenNavigatedFromWarningsPopup;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - IsScreenNavigatedFromWarningsPopup : The navigation status.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::updateIsScreenNavigatedFromWarningsPopup(const bool &IsScreenNavigatedFromWarningsPopup)
{
    m_IsScreenNavigatedFromWarningsPopup = IsScreenNavigatedFromWarningsPopup;
    emit alarmDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns screen navigation status.
*
* \param   - None.
*
* \return  - m_IsScreenNavigatedFromNotificationsPopup : The navigation status.
******************************************************************************/
bool AlarmDetailsListModel::getIsScreenNavigatedFromNotificationsPopup() const
{
    return m_IsScreenNavigatedFromNotificationsPopup;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - IsScreenNavigatedFromNotificationsPopup : The navigation status.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::updateIsScreenNavigatedFromNotificationsPopup(const bool &IsScreenNavigatedFromNotificationsPopup)
{
    m_IsScreenNavigatedFromNotificationsPopup = IsScreenNavigatedFromNotificationsPopup;
    emit alarmDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns screen navigation status.
*
* \param   - None.
*
* \return  - m_IsScreenNavigatedFromServiceReminderPopup : The navigation status.
******************************************************************************/
bool AlarmDetailsListModel::getIsScreenNavigatedFromServiceReminderPopup() const
{
    return m_IsScreenNavigatedFromServiceReminderPopup;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - m_IsScreenNavigatedFromServiceReminderPopup : The navigation status.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::updateIsScreenNavigatedFromServiceReminderPopup(const bool &IsScreenNavigatedFromServiceReminderPopup)
{
    m_IsScreenNavigatedFromServiceReminderPopup = IsScreenNavigatedFromServiceReminderPopup;
    emit alarmDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief -  Define which properties need to expose to QML under the cycle details list
*        -  Model. Generate a link table between Model and list data.
*
* \param -  None
*
* \return - Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> AlarmDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AlarmRoles::AlarmErrorTypeRole]     = "AlarmErrorType";
    roles[AlarmRoles::AlarmIDRole]            = "AlarmID";
    roles[AlarmRoles::AlarmSubTypeRole]       = "AlarmSubType";
    roles[AlarmRoles::AlarmRecipeNoRole]      = "AlarmRecipeNo";
    roles[AlarmRoles::AlarmRecipeVersionRole] = "AlarmRecipeVersion";
    roles[AlarmRoles::AlarmCycleNoRole]       = "AlarmCycleNo";
    roles[AlarmRoles::AlarmDateTimeRole]      = "AlarmDateTime";
    roles[AlarmRoles::AlarmUserNameRole]      = "AlarmUserName";
    roles[AlarmRoles::AlarmTypeRole]          = "AlarmType";
    roles[AlarmRoles::AlarmAddNotesRole]      = "AlarmAddedNotes";
    roles[AlarmRoles::AlarmLogIndexRole]      = "AlarmLogIndex";

    return roles;
}


/**************************************************************************//**
*
* \brief - Below returns the Clamp on status to HMI
*
* \param  - None
*
* \return - Clamp on Status.
*
******************************************************************************/
bool AlarmDetailsListModel::getHornClampOnAlarmStatus()
{
   return m_AlarmMgrACE->GetHornClampOnAlrmStatus();
}
/**************************************************************************//**
*
* \brief   - Role of the slot OnAlarmDetailsListUpdated to update the alarm
*            details list data.
*
* \param   - AlarmEventsLogScreen_Obj : The alarm events object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void AlarmDetailsListModel::OnAlarmDetailsListUpdated(AlarmMgrACE *AlarmEventsLogScreen_Obj, ServiceManagement *ServiceManagement_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_AlarmMgrACE = AlarmEventsLogScreen_Obj;
    m_ServiceManagement = ServiceManagement_Obj;

    if((m_AlarmMgrACE->IsAlarmLogUpdated()) || (m_AlarmMgrACE->IsActiveAlarmLogUpdated()) || (m_IsScreenReNavigated))
    {
        m_HistoricalAlarmLogData = m_AlarmMgrACE->GetHistoricalAlarmLogData();
        m_ActiveAlarmData = m_AlarmMgrACE->GetActiveAlarmLogData();
        m_AlarmMgrACE->UpdateAlarmLogUpdatedFlag(false);

        m_ServiceReminderDetails = m_ServiceManagement->GetReminderList();
        /*No need to disable active alarm log updated flag as it shall be handled in active alarm details slot*/
        /*m_AlarmMgrACE->UpdateActiveAlarmLogUpdatedFlag(false);*/
        m_IsScreenReNavigated = false;
        m_ActiveWelderId = WelderId;
        loadAlarmDetailsList();
        emit alarmDetailsListDataChanged();
    }

    pthread_mutex_unlock(&mtx);
}

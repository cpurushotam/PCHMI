/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ServiceCountListModel.cpp file handles service count details list model
    container.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 03/10/2024 - Initial version.
***************************************************************************/
#include "ServiceCountListModel.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <algorithm>
#include <QDateTime>
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the Alarms details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
ServiceCountListModel::ServiceCountListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::ServiceCountScreenUpdated, this, &ServiceCountListModel::OnServiceCountListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ServiceCountListModel::~ServiceCountListModel()
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
int ServiceCountListModel::rowCount(const QModelIndex &parent) const
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
QVariant ServiceCountListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const ServiceCountListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {

    case ServiceCountServiceNameRole:
        return ptrListObj->getServiceName();
        break;

    case ServiceCountCounterRole:
        return ptrListObj->getCounter();
        break;

    case ServiceCountLimitRole:
        return ptrListObj->getLimit();
        break;

    case ServiceCountStartTimeRole:
        return ptrListObj->getStartTime();
        break;

    case ServiceCountReminderMethodRole:
        return ptrListObj->getReminderMethod();
        break;

    case ServiceCountReminderStatusRole:
        return ptrListObj->getReminderStatus();
        break;

    case ServiceCountSnoozeDurationRole:
        return ptrListObj->getSnoozeDuration();
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
QModelIndex ServiceCountListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    ServiceCountListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<ServiceCountListData*>(index.internalPointer());

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
void ServiceCountListModel::isScreenReNavigated(bool Value)
{
    m_IsScreenReNavigated = Value;
}

/**************************************************************************//**
*
* \brief - To clear the service count details list.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void ServiceCountListModel::clearServiceCountList()
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
* \param  - ServiceCountList : List data of type ServiceCountList.
*
* \return - None.
*
******************************************************************************/
void ServiceCountListModel::addNewServiceCountList(ServiceCountListData *ServiceCountList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(ServiceCountList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadServiceCountList function called by qml while loading of
*            service count detail list, to display available service count details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::loadServiceCountList()
{
    createNewServiceCountList();
    clearServiceCountList();

    ServiceCountListData* ptrListObj = nullptr;
    time_t timeVal;
    QDateTime q_TimeVal;
    QString str_TimeVal;

    for (unsigned int Index = 0; Index < m_ServiceReminderDetails.size(); Index++)
    {
        timeVal = m_ServiceReminderDetails[Index].dateTimeLimit;
        q_TimeVal = QDateTime::fromSecsSinceEpoch(timeVal);
        str_TimeVal = q_TimeVal.toString("MM/dd/yyyy HH:mm:ss");

        m_IndexMonth[Index] = q_TimeVal.date().month();
        m_IndexDay[Index] = q_TimeVal.date().day();
        m_IndexYear[Index] = q_TimeVal.date().year();
        m_IndexHours[Index] = q_TimeVal.time().hour();
        m_IndexMinutes[Index] = q_TimeVal.time().minute();
        m_IndexSeconds[Index] = q_TimeVal.time().second();

        int method = (static_cast<int>(m_ServiceReminderDetails[Index].method));
        int status = (static_cast<int>(m_ServiceReminderDetails[Index].status));
        int snooze = (static_cast<int>(m_ServiceReminderDetails[Index].snooze));

        ptrListObj = new ServiceCountListData(m_ServiceReminderDetails[Index].serviceName, m_ServiceReminderDetails[Index].counter,
                                              m_ServiceReminderDetails[Index].counterLimit, str_TimeVal, method,
                                              status, snooze);
        addNewServiceCountList(ptrListObj);
    }
}


/**************************************************************************//**
*
* \brief   - Below function updates service name.
*
* \param   - p_ServiceName : Service name.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::serviceName(QString p_ServiceName)
{
    m_ServiceName = p_ServiceName;
}

/**************************************************************************//**
*
* \brief   - Below function updates service type.
*
* \param   - p_ServiceType : Service type.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::serviceType(int p_ServiceType)
{
    m_ServiceType = p_ServiceType;
}

/**************************************************************************//**
*
* \brief   - Below function updates service count.
*
* \param   - p_ServiceCountReminder : Service count.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::serviceCountReminder(int p_ServiceCountReminder)
{
    m_ServiceCountReminder = p_ServiceCountReminder;
}

/**************************************************************************//**
*
* \brief   - Below function updates month value.
*
* \param   - p_Month : Month value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::month(int p_Month)
{
    m_Month = p_Month;
}

/**************************************************************************//**
*
* \brief   - Below function updates day value.
*
* \param   - p_Day : Day Value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::day(int p_Day)
{
    m_Day = p_Day;
}

/**************************************************************************//**
*
* \brief   - Below function updates year value.
*
* \param   - p_Year : Year Value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::year(int p_Year)
{
    m_Year = p_Year;
}

/**************************************************************************//**
*
* \brief   - Below function updates hour value.
*
* \param   - p_Hours : Hour value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::hours(int p_Hours)
{
    m_Hours = p_Hours;
}

/**************************************************************************//**
*
* \brief   - Below function updates minutes value.
*
* \param   - p_Minutes : Minutes value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::minutes(int p_Minutes)
{
    m_Minutes = p_Minutes;
}

/**************************************************************************//**
*
* \brief   - Below function updates seconds value.
*
* \param   - p_Seconds : Seconds value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::seconds(int p_Seconds)
{
    m_Seconds = p_Seconds;
}

/**************************************************************************//**
*
* \brief   - Below function returns month of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexMonth[indexVal] : Month at given Index.
******************************************************************************/
int ServiceCountListModel::indexMonth(int indexVal)
{
    return m_IndexMonth[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function returns day of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexDay[indexVal] : Day at given Index.
******************************************************************************/
int ServiceCountListModel::indexDay(int indexVal)
{
    return m_IndexDay[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function returns year of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexYear[indexVal] : Year at given Index.
******************************************************************************/
int ServiceCountListModel::indexYear(int indexVal)
{
    return m_IndexYear[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function returns hours of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexHours[indexVal] : Hours at given Index.
******************************************************************************/
int ServiceCountListModel::indexHours(int indexVal)
{
    return m_IndexHours[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function returns minutes of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexMinutes[indexVal] : Minutes at given Index.
******************************************************************************/
int ServiceCountListModel::indexMinutes(int indexVal)
{
    return m_IndexMinutes[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function returns seconds of given index.
*
* \param   - indexVal : Index.
*
* \return  - m_IndexSeconds[indexVal] : Seconds at given Index.
******************************************************************************/
int ServiceCountListModel::indexSeconds(int indexVal)
{
    return m_IndexSeconds[indexVal];
}

/**************************************************************************//**
*
* \brief   - Below function saves the new service reminder entry data.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onAddSavePressed()
{
    qstrncpy(m_AddReminderStruct.serviceName, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_AddReminderStruct.method = (static_cast<REMINDER_METHOD>(m_ServiceType));
    m_AddReminderStruct.counterLimit = m_ServiceCountReminder;

    QDate date (m_Year, m_Month, m_Day);
    QTime time (m_Hours, m_Minutes, m_Seconds);
    QDateTime dateTime(date, time);
    dateTime.setTimeSpec(Qt::UTC);
    time_t timeValue = dateTime.toSecsSinceEpoch();

    m_AddReminderStruct.dateTimeLimit = timeValue;

    m_ServiceManagement->InitiateAddReminderRequest(m_AddReminderStruct);
}

/**************************************************************************//**
*
* \brief   - Below function saves the edited service reminder entry data.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onEditSavePressed()
{
    m_ServiceManagement->SetIsReminderListUpdated(true);
    qstrncpy(m_AddReminderStruct.serviceName, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_AddReminderStruct.method = (static_cast<REMINDER_METHOD>(m_ServiceType));
    m_AddReminderStruct.counterLimit = m_ServiceCountReminder;
    QDate date (m_Year, m_Month, m_Day);
    QTime time (m_Hours, m_Minutes, m_Seconds);
    QDateTime dateTime(date, time);
    dateTime.setTimeSpec(Qt::UTC);
    time_t timeValue = dateTime.toSecsSinceEpoch();

    m_AddReminderStruct.dateTimeLimit = timeValue;

   m_ServiceManagement->InitiateModifyReminderRequest(m_AddReminderStruct);
}

/**************************************************************************//**
*
* \brief   - Below function pauses the given service reminder.
*
* \param   - p_ServiceName : Service name to be pause.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onPausePressed(QString p_ServiceName)
{
    m_ServiceName = p_ServiceName;

    qstrncpy(m_ReminderPauseResumeStruct.serviceName, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_ReminderPauseResumeStruct.status = REMINDER_STATUS_DISABLED;
    m_ServiceManagement->InitiatePauseResumeReminderRequest(m_ReminderPauseResumeStruct);
}

/**************************************************************************//**
*
* \brief   - Below function resumes the given service reminder.
*
* \param   - p_ServiceName : Service name to be resume.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onResumePressed(QString p_ServiceName)
{
    m_ServiceName = p_ServiceName;

    qstrncpy(m_ReminderPauseResumeStruct.serviceName, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_ReminderPauseResumeStruct.status = REMINDER_STATUS_ENABLED;
    m_ServiceManagement->InitiatePauseResumeReminderRequest(m_ReminderPauseResumeStruct);
}

/**************************************************************************//**
*
* \brief   - Below function resets the given service reminder.
*
* \param   - p_ServiceName : Service name to be reset.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onResetPressed(QString p_ServiceName)
{
    m_ServiceName = p_ServiceName;

    qstrncpy(m_ReminderResetStruct.serviceName, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_ServiceManagement->InitiateResetReminderRequest(m_ReminderResetStruct);
}

/**************************************************************************//**
*
* \brief   - Below function deletes the given service reminder.
*
* \param   - p_ServiceName : Service name to be delete.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::onDeletePressed(QString p_ServiceName)
{
    m_ServiceName = p_ServiceName;
    char serviceNameLocal[SERVICE_NAME_SIZE];

    qstrncpy(serviceNameLocal, (m_ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_ServiceManagement->InitiateDeleteReminderRequest(serviceNameLocal);
}

/**************************************************************************//**
*
* \brief   - Below function return the status of addition of new service reminder.
*
* \param   - None.
*
* \return  - ADD_REMINDER_ERROR_CODES : Respective response code.
******************************************************************************/
ADD_REMINDER_ERROR_CODES ServiceCountListModel::getAddReminderResponse()
{
    m_AddReminderResponse = m_ServiceManagement->GetAddReminderResponse();
    return m_AddReminderResponse;
}

/**************************************************************************//**
*
* \brief   - Below function return the status of delete of new service reminder.
*
* \param   - None.
*
* \return  - MODIFY_REMINDER_ERROR_CODES : Respective response code.
******************************************************************************/
MODIFY_REMINDER_ERROR_CODES ServiceCountListModel::getDeleteReminderResponse()
{
    m_DeleteReminderResponse = m_ServiceManagement->GetDeleteReminderResponse();
    return m_DeleteReminderResponse;
}

/**************************************************************************//**
*
* \brief   - Below function return the status of modify of new service reminder.
*
* \param   - None.
*
* \return  - MODIFY_REMINDER_ERROR_CODES : Respective response code.
******************************************************************************/
MODIFY_REMINDER_ERROR_CODES ServiceCountListModel::getModifyReminderResponse()
{
    m_ModifyReminderResponse = m_ServiceManagement->GetModifyReminderResponse();
    return m_ModifyReminderResponse;
}

/**************************************************************************//**
*
* \brief   - Below function returns service reminder counter value.
*
* \param   - None.
*
* \return  - m_CounterReminder : Service reminder counter value.
******************************************************************************/
int ServiceCountListModel::getCounterReminder() const
{
    return m_CounterReminder;
}

/**************************************************************************//**
*
* \brief   - Below function updates service reminder counter value.
*
* \param   - m_CounterReminder : Service reminder counter value.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::updateCounterReminder(const int &CounterReminder)
{
    m_CounterReminder = CounterReminder;
    emit counterReminderChanged();
}
/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type ServiceCountListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::createNewServiceCountList()
{
    ServiceCountListData* ptrListObj = new ServiceCountListData();
    addNewServiceCountList(ptrListObj);
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
QHash<int, QByteArray> ServiceCountListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ServiceCountRoles::ServiceCountServiceNameRole]    = "ServiceCountServiceName";
    roles[ServiceCountRoles::ServiceCountCounterRole]        = "ServiceCountCounter";
    roles[ServiceCountRoles::ServiceCountLimitRole]          = "ServiceCountLimit";
    roles[ServiceCountRoles::ServiceCountStartTimeRole]      = "ServiceCountStartTime";
    roles[ServiceCountRoles::ServiceCountReminderMethodRole] = "ServiceCountReminderMethod";
    roles[ServiceCountRoles::ServiceCountReminderStatusRole] = "ServiceCountReminderStatus";
    roles[ServiceCountRoles::ServiceCountSnoozeDurationRole] = "ServiceCountSnoozeDuration";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnServiceCountListUpdated to update the service
*            reminders list data.
*
* \param   - ServiceManagement_Obj : The service reminders object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void ServiceCountListModel::OnServiceCountListUpdated(ServiceManagement *ServiceManagement_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_ServiceManagement = ServiceManagement_Obj;

    if(m_ServiceManagement->GetIsReminderListUpdated() || (m_IsScreenReNavigated))
    {
        m_ServiceReminderDetails = m_ServiceManagement->GetReminderList();
        m_IsScreenReNavigated = false;
        m_ActiveWelderId = WelderId;
        loadServiceCountList();
        m_ServiceManagement->SetIsReminderListUpdated(false);
        emit serviceCountListDataChanged();
    }

    pthread_mutex_unlock(&mtx);
}

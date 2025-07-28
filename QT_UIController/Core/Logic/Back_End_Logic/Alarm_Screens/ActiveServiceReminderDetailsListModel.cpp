/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ActiveAlarmDetailsListModel.cpp file handles Alarm details list model container includes :
    Alarm counts, date and time.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 30/05/2024 - Initial version.
***************************************************************************/
#include "ActiveServiceReminderDetailsListModel.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <algorithm>
/**************************************************************************//**
*
* \brief  - Constructor to clear alarm data list that will save all the ServiceReminders details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
ActiveServiceReminderDetailsListModel::ActiveServiceReminderDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    qstrncpy(m_ReminderSnoozeStruct.serviceName, "NULL", SERVICE_NAME_SIZE);
    m_ReminderSnoozeStruct.snooze = AFTER_NONE;
    connect(UpdateScreen::getInstance(), &UpdateScreen::AlarmEventsLogUpdated, this, &ActiveServiceReminderDetailsListModel::OnActiveServiceReminderDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ActiveServiceReminderDetailsListModel::~ActiveServiceReminderDetailsListModel()
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
int ActiveServiceReminderDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant ActiveServiceReminderDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const ActiveServiceReminderDetailsListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {

    case ServiceReminderIDRole:
        return ptrListObj->getServiceReminderID();
        break;

    case ServiceReminderSubTypeRole:
        return ptrListObj->getServiceReminderSubType();
        break;

    case ServiceReminderIsLogRequiredRole:
        return ptrListObj->getIsServiceReminderLogRequired();
        break;

    case ServiceReminderServiceNameRole:
        return ptrListObj->getServiceName();
        break;

    case ServiceReminderSnoozeDurationRole:
        return ptrListObj->getSnoozeDuration();

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
QModelIndex ActiveServiceReminderDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    ActiveServiceReminderDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<ActiveServiceReminderDetailsListData*>(index.internalPointer());

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
void ActiveServiceReminderDetailsListModel::isScreenReNavigated(bool Value)
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
void ActiveServiceReminderDetailsListModel::clearActiveServiceReminderDetailsList()
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
* \param  - ActiveServiceReminderDetailsList : List data of type ActiveServiceReminderDetailsList.
*
* \return - None.
*
******************************************************************************/
void ActiveServiceReminderDetailsListModel::addNewActiveServiceReminderDetailsList(ActiveServiceReminderDetailsListData *ActiveServiceReminderDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(ActiveServiceReminderDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadActiveServiceReminderDetailsList function called by qml while loading of
*            alarm detail list, to display available alarm details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActiveServiceReminderDetailsListModel::loadActiveServiceReminderDetailsList()
{
    createNewActiveServiceReminderDetailsList();
    clearActiveServiceReminderDetailsList();

    ActiveServiceReminderDetailsListData* ptrListObj = nullptr;
    int m_AlarmID;
    int m_IndexID;
    int m_SnoozeDuration;

    for (unsigned int Index = 0; Index < m_ActiveServiceReminderData.size(); Index++)
    {
        int i_AlarmID = getServiceReminderSubCategory(m_ActiveServiceReminderData[Index].AlarmID);

        if  (i_AlarmID == REMINDER_SUBCAT)
        {
            m_AlarmID = (static_cast<int> (m_ActiveServiceReminderData[Index].AlarmID));
            m_IndexID = (m_AlarmID % 10);

            if(m_IndexID == 0)
            {
                m_IndexID = 10;
            }

            m_SnoozeDuration = (static_cast<int> (m_ServiceReminderDetails[m_IndexID - 1].snooze));
            ptrListObj = new ActiveServiceReminderDetailsListData(m_ActiveServiceReminderData[Index].AlarmID, i_AlarmID, m_ActiveServiceReminderData[Index].IsLogRequired,
                                                                  m_ServiceReminderDetails[m_IndexID - 1].serviceName, m_SnoozeDuration);
            addNewActiveServiceReminderDetailsList(ptrListObj);
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type ActiveServiceReminderDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActiveServiceReminderDetailsListModel::createNewActiveServiceReminderDetailsList()
{
    ActiveServiceReminderDetailsListData* ptrListObj = new ActiveServiceReminderDetailsListData();
    addNewActiveServiceReminderDetailsList(ptrListObj);
}

/**************************************************************************//**
*
* \brief - Below function fetches the alarm's sub category.
*
* \param  - ServiceReminderID : ServiceReminder's ID.
*
* \return - m_ServiceReminderString : The alarm's sub category.
*
******************************************************************************/
int ActiveServiceReminderDetailsListModel::getServiceReminderSubCategory(ALARM_IDS ServiceReminderID)
{
    ALARM_SUBCATEGORY retVal;

    retVal = m_AlarmNames.GetAlarmSubcategory(ServiceReminderID);
    return retVal;
}

void ActiveServiceReminderDetailsListModel::onSetSnoozePressed(QString ServiceName, int SnoozeDuration)
{
    qstrncpy(m_ReminderSnoozeStruct.serviceName, (ServiceName.toStdString().c_str()), SERVICE_NAME_SIZE);
    m_ReminderSnoozeStruct.snooze = (static_cast<SNOOZE_DURATION>(SnoozeDuration));
    m_ServiceManagement->InitiateSnoozeReminderRequest(m_ReminderSnoozeStruct);
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
QHash<int, QByteArray> ActiveServiceReminderDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ServiceReminderRoles::ServiceReminderIDRole]            = "ServiceReminderID";
    roles[ServiceReminderRoles::ServiceReminderSubTypeRole]       = "ServiceReminderSubType";
    roles[ServiceReminderRoles::ServiceReminderIsLogRequiredRole] = "ServiceReminderIsLogRequired";
    roles[ServiceReminderRoles::ServiceReminderServiceNameRole]   = "ServiceReminderServiceName";
    roles[ServiceReminderRoles::ServiceReminderSnoozeDurationRole]= "ServiceReminderSnoozeDuration";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnActiveServiceReminderDetailsListUpdated to update the service reminder
*            details list data.
*
* \param   - ActiveServiceReminderEventsLogScreen_Obj : The active alarm events object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void ActiveServiceReminderDetailsListModel::OnActiveServiceReminderDetailsListUpdated(AlarmMgrACE *ActiveServiceReminderEventsLogScreen_Obj, ServiceManagement *ServiceManagement_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_ServiceReminderMgrACE = ActiveServiceReminderEventsLogScreen_Obj;
    m_ServiceManagement = ServiceManagement_Obj;

    /*The Active alarm Section*/

    if(m_ServiceReminderMgrACE->IsActiveAlarmLogUpdated())
    {
        m_ActiveServiceReminderData = m_ServiceReminderMgrACE->GetActiveAlarmLogData();
        m_ServiceReminderMgrACE->UpdateActiveAlarmLogUpdatedFlag(false);
        m_ServiceReminderDetails = m_ServiceManagement->GetReminderList();

        m_IsScreenReNavigated = false;
        m_ActiveWelderId = WelderId;
        loadActiveServiceReminderDetailsList();
    }

    pthread_mutex_unlock(&mtx);
}

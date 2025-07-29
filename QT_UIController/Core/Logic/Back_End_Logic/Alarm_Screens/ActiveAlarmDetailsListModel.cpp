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
#include "ActiveAlarmDetailsListModel.h"
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
ActiveAlarmDetailsListModel::ActiveAlarmDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::AlarmEventsLogUpdated, this, &ActiveAlarmDetailsListModel::OnActiveAlarmDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ActiveAlarmDetailsListModel::~ActiveAlarmDetailsListModel()
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
int ActiveAlarmDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant ActiveAlarmDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const ActiveAlarmDetailsListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {

    case AlarmIDRole:
        return ptrListObj->getAlarmID();
        break;

    case AlarmSubTypeRole:
        return ptrListObj->getAlarmSubType();
        break;

    case AlarmIsLogRequiredRole:
        return ptrListObj->getIsAlarmLogRequired();
        break;

    case AlarmServiceNameRole:
        return ptrListObj->getServiceName();
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
QModelIndex ActiveAlarmDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    ActiveAlarmDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<ActiveAlarmDetailsListData*>(index.internalPointer());

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
void ActiveAlarmDetailsListModel::isScreenReNavigated(bool Value)
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
void ActiveAlarmDetailsListModel::clearActiveAlarmDetailsList()
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
* \param  - ActiveAlarmDetailsList : List data of type ActiveAlarmDetailsList.
*
* \return - None.
*
******************************************************************************/
void ActiveAlarmDetailsListModel::addNewActiveAlarmDetailsList(ActiveAlarmDetailsListData *ActiveAlarmDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(ActiveAlarmDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadActiveAlarmDetailsList function called by qml while loading of
*            alarm detail list, to display available alarm details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActiveAlarmDetailsListModel::loadActiveAlarmDetailsList()
{
    createNewActiveAlarmDetailsList();
    clearActiveAlarmDetailsList();

    ActiveAlarmDetailsListData* ptrListObj = nullptr;
    int m_AlarmID;
    int m_IndexID;

    for (unsigned int Index = 0; Index < m_ActiveAlarmData.size(); Index++)
    {
        int i_AlarmID = getAlarmSubCategory(m_ActiveAlarmData[Index].AlarmID);

        /*When system generarted alarm occurred*/
        if(m_IsNotificationSystemGenerated)
        {
            if (i_AlarmID == ALARM_SUBCAT)
            {
                m_IsAlarmOccurred = true;
                ptrListObj = new ActiveAlarmDetailsListData(m_ActiveAlarmData[Index].AlarmID, i_AlarmID, m_ActiveAlarmData[Index].IsLogRequired, "NA");
                addNewActiveAlarmDetailsList(ptrListObj);
            }

            else if (i_AlarmID == WARNING_SUBCAT)
            {
                m_IsWarningOccurred = true;
            }

            else if  (i_AlarmID == NOTIFICATION_SUBCAT)
            {
                m_IsNotificationOccurred = true;
            }
        }

        /*When user requested to see the alarms/warnings/notifications/service reminder*/
        else
        {
            if (i_AlarmID == ALARM_SUBCAT)
            {
                m_IsAlarmOccurred = true;
            }

            else if (i_AlarmID == WARNING_SUBCAT)
            {
                m_IsWarningOccurred = true;
            }

            else if  (i_AlarmID == NOTIFICATION_SUBCAT)
            {
                m_IsNotificationOccurred = true;
            }

            else if  (i_AlarmID == REMINDER_SUBCAT)
            {
                m_IsServiceReminderOccurred = true;
                m_AlarmID = (static_cast<int> (m_ActiveAlarmData[Index].AlarmID));
                m_IndexID = (m_AlarmID % 10);

                if(m_IndexID == 0)
                {
                    m_IndexID = 10;
                }
            }

            /*ESTOP is exceptional alarm which shall not display in active lists*/
            if ((m_ActiveAlarmData[Index].AlarmID) != ALARM_ESTOP_NCA)
            {
                ptrListObj = new ActiveAlarmDetailsListData(m_ActiveAlarmData[Index].AlarmID, i_AlarmID, m_ActiveAlarmData[Index].IsLogRequired, m_ServiceReminderDetails[m_IndexID - 1].serviceName);
                addNewActiveAlarmDetailsList(ptrListObj);
            }

            else
            {
                continue;
            }
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type ActiveAlarmDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ActiveAlarmDetailsListModel::createNewActiveAlarmDetailsList()
{
    ActiveAlarmDetailsListData* ptrListObj = new ActiveAlarmDetailsListData();
    addNewActiveAlarmDetailsList(ptrListObj);
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
void ActiveAlarmDetailsListModel::reset()
{
    m_AlarmMgrACE->SetResetAllActiveAlarm();
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
int ActiveAlarmDetailsListModel::getAlarmSubCategory(ALARM_IDS AlarmID)
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
QString ActiveAlarmDetailsListModel::getAlarmTypeString(ALARM_IDS AlarmID)
{
    std::string m_AlarmString;

    m_AlarmString = m_AlarmNames.GetAlarmErrorType(AlarmID);
    return QString::fromLocal8Bit(m_AlarmString.c_str());
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
void ActiveAlarmDetailsListModel::onResetAlarmPressed(ALARM_IDS AlarmID)
{
    m_AlarmMgrACE->SetAlarmIDtoBeReset(AlarmID);
}

/**************************************************************************//**
*
* \brief - Below function intitiate reset request for EStop.
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
void ActiveAlarmDetailsListModel::setEstopResetRequest()
{
    m_ResetSuccessFlag = false;
    m_AlarmMgrACE->SetEstopResetRequest();
}

/**************************************************************************//**
*
* \brief - Below function return the status of syetem generated notifications.
*
* \param  - None.
*
* \return - m_IsNotificationSystemGenerated : The status of syetem generated notifications.
*
******************************************************************************/
bool ActiveAlarmDetailsListModel::getIsNotificationSystemGenerated() const
{
    return m_IsNotificationSystemGenerated;
}

/**************************************************************************//**
*
* \brief - Below function updates the status of syetem generated notifications.
*
* \param  - IsNotificationSystemGenerated : The status of syetem generated notifications.
*
* \return - None.
*
******************************************************************************/
void ActiveAlarmDetailsListModel::updateIsNotificationSystemGenerated(const bool &IsNotificationSystemGenerated)
{
    m_IsNotificationSystemGenerated = IsNotificationSystemGenerated;
    emit isNotificationSystemGeneratedChanged();
}

/**************************************************************************//**
*
* \brief - Below function returns the active alarms entry counts.
*
* \param  - None.
*
* \return - m_ActiveAlarmData.size() : The active alarms entry counts.
*
******************************************************************************/
int ActiveAlarmDetailsListModel::getTotalActiveAlarmsWarningsNotificationsCount() const
{
    return m_ActiveAlarmData.size();
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
QHash<int, QByteArray> ActiveAlarmDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AlarmRoles::AlarmIDRole]            = "AlarmID";
    roles[AlarmRoles::AlarmSubTypeRole]       = "AlarmSubType";
    roles[AlarmRoles::AlarmIsLogRequiredRole] = "AlarmIsLogRequired";
    roles[AlarmRoles::AlarmServiceNameRole]   = "AlarmServiceName";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnActiveAlarmDetailsListUpdated to update the alarm
*            details list data.
*
* \param   - ActiveAlarmEventsLogScreen_Obj : The active alarm events object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void ActiveAlarmDetailsListModel::OnActiveAlarmDetailsListUpdated(AlarmMgrACE *ActiveAlarmEventsLogScreen_Obj, ServiceManagement *ServiceManagement_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_AlarmMgrACE = ActiveAlarmEventsLogScreen_Obj;
    m_ServiceManagement = ServiceManagement_Obj;

    /*The Active alarm Section*/

    if(m_AlarmMgrACE->IsActiveAlarmLogUpdated())
    {
        m_ActiveAlarmData = m_AlarmMgrACE->GetActiveAlarmLogData();
//        m_AlarmMgrACE->UpdateActiveAlarmLogUpdatedFlag(false);
        m_ServiceReminderDetails = m_ServiceManagement->GetReminderList();

        m_IsScreenReNavigated = false;
        m_ActiveWelderId = WelderId;
        loadActiveAlarmDetailsList();
        emit totalActiveAlarmsWarningsNotificationsCountChanged();

        if(m_ActiveAlarmData.size())
        {
            if(m_IsAlarmOccurred)
            {
                m_IsAlarmOccurred = false;
                emit activeAlarmDetailsListDataChanged();
            }

            if(m_IsWarningOccurred)
            {
                m_IsWarningOccurred = false;
                emit activeWarningDetailsListDataChanged();
            }

            if(m_IsNotificationOccurred)
            {
                m_IsNotificationOccurred = false;
                emit activeNotificationDetailsListDataChanged();
            }

            if(m_IsServiceReminderOccurred)
            {
                m_IsServiceReminderOccurred = false;
                emit activeServiceReminderDetailsListDataChanged();
            }
        }

        else
        {
            emit activeAlarmDetailsListEmpty();
        }
    }

    /*The Estop section*/

    if(m_AlarmMgrACE->GetEstopStatus())
    {
        /*To avoid repeated signal generation*/
        if(! m_IsEStopPressed)
        {
            /*To display EStop popup*/
            emit eStopEventOccurred(EStopPressedEventOccurred);
        }

        m_IsEStopPressed = true;
    }

    else
    {
        /*Check only if EStop button was pressed when GetEstopStatus status is false*/
        if(m_IsEStopPressed)
        {
            emit eStopEventOccurred(EStopReleasedEventOccurred);
            m_IsEStopPressed = false;
        }

        /*When reset button preesed on HMI*/
        else if((m_AlarmMgrACE->GetEstopResetResponse()) && (! m_IsEStopPressed) && (! m_ResetSuccessFlag))
        {
            emit eStopEventOccurred(EStopResetSuccess);
            m_ResetSuccessFlag = true;
        }
    }

    pthread_mutex_unlock(&mtx);
}

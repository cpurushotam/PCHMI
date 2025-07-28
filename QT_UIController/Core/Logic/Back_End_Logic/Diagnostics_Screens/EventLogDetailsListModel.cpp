/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    EventLogDetailsListModel.cpp file handles eventlog details list model.

***************************************************************************/
#include "EventLogDetailsListModel.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear Event details list that will save all the event details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
EventLogDetailsListModel::EventLogDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::EventLogTableViewUpdated, this, &EventLogDetailsListModel::OnEventLogDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
EventLogDetailsListModel::~EventLogDetailsListModel()
{
    qDeleteAll(m_ListData.begin(), m_ListData.end());
    m_ListData.clear();
}

/**************************************************************************//**
*
* \brief - Function to be invoked via the meta-object system and from QML.
*          To get the Data for specified row number.
*
* \param  - index - row index.
*
* \return - Return QVariantMap -Data for specific row based on row index as requested by QML.
*
******************************************************************************/
 QVariantMap EventLogDetailsListModel ::get(int index) const
{
    QVariantMap map;
    if (index < 0 || index >= rowCount())
        return map;
    QHash<int, QByteArray> roles = roleNames();
    for (auto it = roles.begin(); it != roles.end(); ++it)
        map[it.value()] = data(this->index(index, 0), it.key());
    return map;
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
* \return - Return event details list size.
*
******************************************************************************/
int EventLogDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant EventLogDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
   const EventLogListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {
    case EventIdx:
        return ptrListObj->getEventIndex();
        break;

    case EventIdRole:
        return ptrListObj->getEventID();
        break;

    case ParameterIdRole:
        return ptrListObj->getParameterID();
        break;

    case DateTimeRole:
        return ptrListObj->getDateTime();
        break;

    case UserNameRole:
        return ptrListObj->getUserName();
        break;

    case OldParametersRole:
        return ptrListObj->getOldParameters();
        break;

    case NewParametersRole:
        return ptrListObj->getNewParameters();
        break;

    case SourceOfEventRole:
        return ptrListObj->getSourceOfEvent();
        break;

    case PSSerialNumberRole:
        return ptrListObj->getPSSerialNumber();
        break;
    case ACSerialNumberRole:
        return ptrListObj->getACSerialNumber();
        break;

    case HMISerialNumberRole:
        return ptrListObj->getHMISerialNumber();
        break;

    case CommentRole:
        return ptrListObj->getComment();
        break;

    case EventName:
        return ptrListObj->getEventType();
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
QModelIndex EventLogDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    EventLogListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<EventLogListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief - To clear the Event details list before the entire event details are loaded.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void EventLogDetailsListModel::clearEventDetailsList()
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
* \param  - EventDetailsList : List data of type EventLogListData.
*
* \return - None.
*
******************************************************************************/
void EventLogDetailsListModel::addNewEventDetailsList(EventLogListData *EventDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(EventDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - loadEventDetailsList function called by qml while loading of
*            Event detail list, to display available events detail list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void EventLogDetailsListModel::loadEventDetailsList()
{
    createNewEventDetailsList();
    clearEventDetailsList();

    EventLogListData* ptrListObj = nullptr;

   for (unsigned int Index = 0; Index < m_EventLogResultData.size(); Index++)
   {
       ptrListObj = new EventLogListData(m_EventLogResultData[Index].EventIndex,m_EventLogResultData[Index].EventID, m_EventLogResultData[Index].ParameterID,
                                             m_EventLogResultData[Index].DateTime, m_EventLogResultData[Index].UserName,
                                             m_EventLogResultData[Index].OldParameters, m_EventLogResultData[Index].NewParameters,
                                             m_EventLogResultData[Index].SourceOfEvent, m_EventLogResultData[Index].PSSerialNumber,
                                             m_EventLogResultData[Index].ACSerialNumber,
                                             m_EventLogResultData[Index].HMISerialNumber, m_EventLogResultData[Index].Comment);
       addNewEventDetailsList(ptrListObj);
   }
   loadLastEventLogDateTime();
   emit lastEvent();

}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type EventLogDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void EventLogDetailsListModel::createNewEventDetailsList()
{
    EventLogListData* ptrListObj = new EventLogListData();
    addNewEventDetailsList(ptrListObj);
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
QHash<int, QByteArray> EventLogDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EventRoles::EventIdx]             = "EventIdxId";
    roles[EventRoles::EventIdRole]          = "EventId";
    roles[EventRoles::ParameterIdRole]      = "ParameterId";
    roles[EventRoles::DateTimeRole]         = "DateTime";
    roles[EventRoles::UserNameRole]         = "UserName";
    roles[EventRoles::OldParametersRole]    = "OldParams";
    roles[EventRoles::NewParametersRole]    = "NewParams";
    roles[EventRoles::SourceOfEventRole]    = "SourceOfEvent";
    roles[EventRoles::PSSerialNumberRole]   = "PSSerialNo";
    roles[EventRoles::ACSerialNumberRole]   = "ACSerialNo";
    roles[EventRoles::HMISerialNumberRole]  = "HMISerialNo";
    roles[EventRoles::CommentRole]          = "Comment";
    roles[EventRoles::EventName]            = "EventName";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnEventLogDetailsListUpdated to update the log
*            details list data.
*
* \param   - EventLogDetailsResult_Obj : Object pointer of type EventLog.
*
* \return  - None.
******************************************************************************/
void EventLogDetailsListModel::OnEventLogDetailsListUpdated(EventLog *EventLogDetailsResult_Obj, int WelderId)
{

    m_EventLog = EventLogDetailsResult_Obj;

    if(m_EventLog->GetIsLastEventLogUpdated() || m_ActiveWelderId != WelderId)
    {
       m_EventLogResultData.clear();
       m_EventLogResultData = m_EventLog->GetHistoricalEventLogData();
       loadEventDetailsList();
       m_ActiveWelderId = WelderId;
       m_EventLog->SetIsLastEventLogTableUpdated(false);
       emit eventDetailsListDataChanged();
    }

}

/**************************************************************************//**
*
* \brief   - Q_INVOKABLE functions to load the lastest event DateTime on HMI.
*
* \param   - None
*
* \return  - QString - event detail  - DateTime.
*
******************************************************************************/
QString EventLogDetailsListModel::loadLastEventLogDateTime()
{
    QString dateTime;
    dateTime = m_EventLogResultData[m_Index].DateTime;
    return dateTime;
}
/**************************************************************************//**
*
* \brief   - Below function emits the signal to display the selected event log detail.
*
* \param   - Idx - To display current index selected..
*
* \return  - NOne.
******************************************************************************/
void EventLogDetailsListModel::selectedRowDataDisplay(int Idx)
{
    m_Index = Idx;
    emit lastEvent();
}


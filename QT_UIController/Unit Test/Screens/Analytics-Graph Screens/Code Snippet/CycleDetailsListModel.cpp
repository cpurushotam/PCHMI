/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailsListModel.cpp file handles cycle details list model container includes :
    cycle counts, date and time.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 11/10/2023 - Initial version.
***************************************************************************/
#include "CycleDetailsListModel.h"
/**************************************************************************//**
*
* \brief  - Constructor to clear weld data list that will save all the graph cycles details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CycleDetailsListModel::CycleDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_ListData.clear();
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
CycleDetailsListModel::~CycleDetailsListModel()
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
* \return - Return weld cycle details list size.
*
******************************************************************************/
int CycleDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant CycleDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const CycleDetailsListData *ptrListObj = m_ListData[index.row()];
    switch (role)
    {
    case CycleNoRole:
        return ptrListObj->getCycleNo();
        break;

    case CycleDateRole:
        return ptrListObj->getCycleDate();
        break;

    case CycleTimeRole:
        return ptrListObj->getCycleTime();
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
QModelIndex CycleDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    CycleDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<CycleDetailsListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief - To clear the weld cycle details list before the entire weld cycle details are loaded.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void CycleDetailsListModel::ClearCycleDetailsList()
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
* \param  - CycleDetailsList : List data of type CycleDetailsList.
*
* \return - None.
*
******************************************************************************/
void CycleDetailsListModel::AddNewCycleDetailsList(CycleDetailsListData *CycleDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(CycleDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadCycleDetailsList function called by qml while loading of
*            weld cycle detail list, to display available cycle details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::LoadCycleDetailsList()
{
    ClearCycleDetailsList();

    CycleDetailsListData* ptrListObj = nullptr;

    for (int i = 0; i<51; i++)
    {
        ptrListObj = new CycleDetailsListData(i, "MM:DD:YYYY", "HH:MM:SS");
        AddNewCycleDetailsList(ptrListObj);
    }

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
QHash<int, QByteArray> CycleDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CycleRoles::CycleNoRole]       = "CycleNo";
    roles[CycleRoles::CycleDateRole]     = "CycleDate";
    roles[CycleRoles::CycleTimeRole]     = "CycleTime";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnCycleDetailsListUpdated to update the weld cycle
*            details list data.
*
* \param   - RecipeCardsData_Obj : Object pointer of type WeldRecipeACEPRO.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::OnCycleDetailsListUpdated()
{

}

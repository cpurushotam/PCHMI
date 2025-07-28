/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailTableModel.cpp file handles cycle details list model container includes : Analytical TableView data .

***************************************************************************/
#include "CycleDetailTableModel.h"

/**************************************************************************//**
*
* \brief  - Constructor to clear weld data list And Initilaze the columns in Table.
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
CycleDetailTableModel::CycleDetailTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_ListData.clear();
    connect(UpdateScreen::getInstance(), &UpdateScreen::AnalyticsTableViewUpdated, this, &CycleDetailTableModel::OnTableViewListUpdated);

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
int CycleDetailTableModel::rowCount(const QModelIndex &) const
{
    return m_ListData.count();
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
* \return - Return Total no. of Columns present in the Table.
*
******************************************************************************/
int CycleDetailTableModel::columnCount(const QModelIndex &) const
{
    return m_columnNames.count();
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
QVariant CycleDetailTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole)
        return QVariant();

    const AnalyticTableListData *ptrListObj = m_ListData[index.row()];

    switch(col)
    {
    case Recipe:
        return ptrListObj->getRecipeNo();
    case RecipeVersion :
        return ptrListObj->getRecipeVersionNo();
    case DateTime:
        return ptrListObj->getCycleDateTime();
    case StackSerial:
        return ptrListObj->getStackSerialNumber();
    case PowerSupplySerialNumber:
        return ptrListObj->getPowerSupplySerialNumber();
    case ActuatorSerialNumber:
        return ptrListObj->getActuatorSerialNumber();
    case ASCSerialNumber :
        return ptrListObj->getASCSerialNumber();
    case CycleCounter:
        return ptrListObj->getCycleCounter();
    case WeldMode:
        return ptrListObj->getWeldModeType();
    case WeldTime:
        return ptrListObj->getWeldTime();
    case HoldTime:
        return ptrListObj->getHoldTime();
    case WeldEnergy:
        return ptrListObj->getWeldEnergy();
    case PeakPower:
        return ptrListObj->getWeldPeakPower();
    case StartFrequency:
        return ptrListObj->getStartFrequency();
    case FrequencyChange:
        return ptrListObj->getFrequencyChange();
    case CycleTime:
        return ptrListObj->getCycleTime();
    case UserName:
        return ptrListObj->getUserName();
    case PartID:
        return ptrListObj->getPartID();
    case BatchID:
        return ptrListObj->getBatchID();
    case TriggerPoint:
        return ptrListObj->getTriggerPoint();
    case WeldSonicPoint:
        return ptrListObj->getWeldSonicPoint();
    case HoldPoint:
        return ptrListObj->getHoldPoint();
    case AlarmID:
        return ptrListObj->getAlarmID();
    case WeldStatus:
        return ptrListObj->getWeldStatus();
    case RecipeStatus:
        return ptrListObj->getRecipeStatus();
    case WeldPressure:
        return ptrListObj->getWeldPressure();
    case HoldPressure:
        return ptrListObj->getHoldPressure();
    case MaxWeldForce:
        return ptrListObj->getMaxWeldForce();
    case MaxHoldForce:
        return ptrListObj->getMaxHoldForce();
    case EndWeldForce:
        return ptrListObj->getEndWeldForce();
    case EndHoldForce:
        return ptrListObj->getEndHoldForce();
    case WeldAbsolute:
        return ptrListObj->getWeldAbsolute();
    case TotalAbsolute:
        return ptrListObj->getTotalAbsolute();
    case Velocity:
        return ptrListObj->getVelocity();
    case TriggerDistance:
        return ptrListObj->getTriggerDistance();
    case WeldCollapseDist:
        return ptrListObj->getWeldCollapseDistance();
    case HoldCollapseDist:
        return ptrListObj->getHoldCollapseDistance();
    case TotalCollapseDistance:
        return ptrListObj->getTotalCollapseDistance();
    }
    return QVariant();
}
/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*           The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*           Returns the data for the given role and section in the header with the specified orientation.
*           Note: This function can be invoked via the meta-object system and from QML.
*           Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index and role : For horizontal headers, the section number corresponds to the column number. Similarly,
*           for vertical headers, the section number corresponds to the row number..
*
* \return - Returns the data for the given role.
*
******************************************************************************/

QVariant CycleDetailTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}
/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*           The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*           To locate at the specific object using the Model Index and get the data from the specific object then.
*
* \param  - None
*
* \return - Returns the model's role names.
*
******************************************************************************/

QHash<int, QByteArray> CycleDetailTableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

/**************************************************************************//**
*
* \brief   - checkTheActutorType function called by qml while loading of
*            TableView detail list, to check the which type of actuator.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CycleDetailTableModel::checkTheActutorType()
{
    ACTUATOR_TYPE sysType = static_cast<ACTUATOR_TYPE>(m_SystemConfiguration->getCurrentSystemType());
    m_columnNames.clear();
    if(sysType == ACTUATOR_ELECTRONIC || sysType == ACTUATOR_ELECTRONIC_PLUS)
    {
        m_columnNames.clear();
        m_columnNames << tr("WeldPressure")  << tr("HoldPressure") << tr("MaxWeldForce") << tr("MaxHoldForce") << tr("EndWeldForce") << tr("EndHoldForce")  << tr("WeldAbsolute") << tr("TotalAbsolute") << tr("Velocity") << tr("DownSpeed") << tr("TriggerDistance") << tr("WeldCollapseDistance") << tr("HoldCollapseDistance") << tr("TotalCollapseDistance");
    }
    else
    {
         m_columnNames.clear();
         m_columnNames <<tr("WeldRecipeNumber") << tr("WeldRecipeVersionNumber") << tr("DateTime") << tr("StackSerialNumber") << tr("PowerSupplySerialNumber") << tr("ActuatorSerialNumber")<< tr("ASCSerialNumber")<< tr("CycleCounter")<< tr("WeldMode")<< tr("WeldTime")<< tr("HoldTime")  << tr("WeldEnergy") << tr("WeldPeakPower") << tr("StartFrequency") << tr("FrequencyChange") << tr("CycleTime") << tr("UserName") << tr("PartID") << tr("BatchID") << tr("TriggerPoint") << tr("WeldSonicPoint") << tr("HoldPoint") << tr("AlarmID") << tr("WeldStatus") << tr("RecipeStatus")<< tr("WeldPressure")  << tr("HoldPressure") << tr("MaxWeldForce") << tr("MaxHoldForce") << tr("EndWeldForce") << tr("EndHoldForce")  << tr("WeldAbsolute") << tr("TotalAbsolute") << tr("Velocity") << tr("TriggerDistance") << tr("WeldCollapseDistance") << tr("HoldCollapseDistance") << tr("TotalCollapseDistance");
    }
}

/**************************************************************************//**
*
* \brief   - loadTableViewDetailsList function called by qml while loading of
*            TableView detail list, to display available cycle details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CycleDetailTableModel::loadTableViewDetailsList()
{
    checkTheActutorType();
    createNewTableViewDetailsList();
    clearTableViewDetailsList();

    AnalyticTableListData* ptrListObj = nullptr;

   for (unsigned int Index = 0; Index < m_WeldResultData.size(); Index++)
   {
       ptrListObj = new AnalyticTableListData(m_WeldResultData[Index].WeldRecipeNumber, m_WeldResultData[Index].WeldMode,
                                             m_WeldResultData[Index].DateTime, m_WeldResultData[Index].WeldCollapseDistance,
                                             m_WeldResultData[Index].HoldCollapseDistance, m_WeldResultData[Index].TotalCollapseDistance,
                                             m_WeldResultData[Index].MaxWeldForce, m_WeldResultData[Index].MaxHoldForce,
                                             m_WeldResultData[Index].StackSerialNumber,m_WeldResultData[Index].CycleCounter,
                                             m_WeldResultData[Index].WeldAbsolute,m_WeldResultData[Index].TotalAbsolute,
                                             m_WeldResultData[Index].TriggerDistance, m_WeldResultData[Index].Velocity,
                                             m_WeldResultData[Index].WeldRecipeVersionNumber,m_WeldResultData[Index].WeldTime,
                                             m_WeldResultData[Index].WeldEnergy,m_WeldResultData[Index].WeldPeakPower,m_WeldResultData[Index].PowerSupplySerialNumber,
                                             m_WeldResultData[Index].ActuatorSerialNumber,
                                             m_WeldResultData[Index].ASCSerialNumber, m_WeldResultData[Index].HoldTime,
                                             m_WeldResultData[Index].StartFrequency, m_WeldResultData[Index].FrequencyChange,
                                             m_WeldResultData[Index].CycleTime,m_WeldResultData[Index].UserName,
                                             m_WeldResultData[Index].PartID,m_WeldResultData[Index].BatchID,
                                             m_WeldResultData[Index].TriggerPoint, m_WeldResultData[Index].WeldSonicPoint,
                                             m_WeldResultData[Index].HoldPoint,m_WeldResultData[Index].AlarmID,
                                             m_WeldResultData[Index].WeldStatus,m_WeldResultData[Index].RecipeStatus,
                                             m_WeldResultData[Index].WeldPressure,m_WeldResultData[Index].HoldPressure,
                                             m_WeldResultData[Index].EndWeldForce,m_WeldResultData[Index].EndHoldForce);

       addNewTableViewDetailsList(ptrListObj);
   }
}

/**************************************************************************//**
* \brief - Below function returns the status for a weldresult if Aalrm exists or not.
*
* \param  - WeldResultRowIndex no from HMI.
*
* \return - bool flag.
*
******************************************************************************/
bool CycleDetailTableModel::isAlarmExist(int WeldResultRowIndex)
{
    m_AlarmName = m_WeldResultData[WeldResultRowIndex].AlarmID;
    bool isAlarmExistsflag = true;
    if(m_AlarmName == "N/A")
    {
        isAlarmExistsflag = false;
    }
    return isAlarmExistsflag;
}

/**************************************************************************//**
*
/**************************************************************************//**
*
* \brief- This function copies current weld result data from CycleDetailTableModel
* class to AnalyticsResultTableModel class.This data is required to get weldResultData
* to filter the cycle counter for searching the data on table.
*
* \param   - None.
*
* \return  - m_WeldResultData : weld result queue.
*
******************************************************************************/
std::deque<WeldResultACEStruct> CycleDetailTableModel::copyWeldResultData()
{
    return m_WeldResultData;
}

/**************************************************************************//**
*
* \brief - Below function add new content into the detail list.  .
*
* \param  - AnalyticTableList : List data of type AnalyticTableList.
*
* \return - None.
*
******************************************************************************/
void CycleDetailTableModel::addNewTableViewDetailsList(AnalyticTableListData *AnalyticTableList)
{
   beginInsertRows(QModelIndex(), rowCount(), rowCount());
   m_ListData.append(AnalyticTableList);
   endInsertRows();
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
void CycleDetailTableModel::clearTableViewDetailsList()
{
   beginRemoveRows(QModelIndex(), 0, rowCount());
   qDeleteAll(m_ListData);
   m_ListData.clear();
   endRemoveRows();
}
/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type TableViewDetailsList.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CycleDetailTableModel::createNewTableViewDetailsList()
{
    AnalyticTableListData* ptrListObj = new AnalyticTableListData();
    addNewTableViewDetailsList(ptrListObj);
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnTableViewListUpdated to update the weld cycle
*            details list data.
*
* \param   - AnlyticsGraphScreenWeldResult_Obj : Object pointer of type WeldRecipeACEPRO.
*
* \return  - None.
******************************************************************************/
void CycleDetailTableModel::OnTableViewListUpdated(WeldResultACE *AnlyticsGraphScreenWeldResult_Obj,int WelderId)
{
    m_WeldResultACE = AnlyticsGraphScreenWeldResult_Obj;

    if(m_WeldResultACE->GetIsLastWeldResultUpdated() || m_ActiveWelderId != WelderId)
    {
       m_WeldResultData = m_WeldResultACE->GetHistoricalWeldResultData();
       loadTableViewDetailsList();
       m_ActiveWelderId = WelderId;
       emit tableViewListDataChanged();
    }
}

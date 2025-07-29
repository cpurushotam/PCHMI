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
    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::AnalyticsScreenUpdated, this, &CycleDetailsListModel::OnCycleDetailsListUpdated);

    /*Make sure search by cycle no off*/
    m_SearchByCycleNo = -1;

    /*No serch by cycle no at loading*/
    m_IsLastWeldResultUpdated = true;
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
    case CycleIndexRole:
        return ptrListObj->getCycleIndex();
        break;

    case CycleRecipeNoRole:
        return ptrListObj->getRecipeNo();
        break;

    case CycleNoRole:
        return ptrListObj->getCycleNo();
        break;

    case CycleWeldModeRole:
        return ptrListObj->getRecipeMode();
        break;

    case CycleDateTimeRole:
        return ptrListObj->getCycleDateTime();
        break;

    case CycleTriggerPointRole:
        return ptrListObj->getTriggerPoint();
        break;

    case CycleWeldSonicPointRole:
        return ptrListObj->getWeldSonicPoint();
        break;

    case CycleHoldPointRole:
        return ptrListObj->getHoldPoint();
        break;

    case  CycleWeldResultIdxRole:
        return ptrListObj->getWeldResultIndex();
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
* \brief - To get the current index of the cycle details list.
*
* \param  - None
*
* \return - m_modelListCurrIndex : current index of the cycle details list
*
******************************************************************************/

int CycleDetailsListModel::getCurrentIndex()
{
    return m_modelListCurrIndex;
}


/**************************************************************************//**
*
* \brief - To get the update index of the cycle details list.
*
* \param  - currentIndex : updated index of the list.
*
* \return - None
*
******************************************************************************/
void CycleDetailsListModel::updateCurrentIndex(int currentIndex)
{
    m_modelListCurrIndex = currentIndex;
    emit currentIndexUpdated();
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
void CycleDetailsListModel::clearCycleDetailsList()
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
void CycleDetailsListModel::addNewCycleDetailsList(CycleDetailsListData *CycleDetailsList)
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
void CycleDetailsListModel::loadCycleDetailsList()
{
    createNewCycleDetailsList();
    clearCycleDetailsList();

    CycleDetailsListData* ptrListObj = nullptr;
   for (unsigned int Index = 0; Index < m_WeldResultData.size(); Index++)
   {
       ptrListObj = new CycleDetailsListData(m_WeldResultData[Index].WeldResultIndex, m_WeldResultData[Index].WeldRecipeNumber,
                                             m_WeldResultData[Index].CycleCounter, m_WeldResultData[Index].WeldMode,
                                             m_WeldResultData[Index].DateTime, m_WeldResultData[Index].TriggerPoint,
                                             m_WeldResultData[Index].WeldSonicPoint, m_WeldResultData[Index].HoldPoint,
                                             m_WeldResultData[Index].WeldResultIndex);
       addNewCycleDetailsList(ptrListObj);
   }
}

/**************************************************************************//**
*
* \brief   - Below function fetches the status of weld result update status.
*
* \param   - None.
*
* \return  - m_IsLastWeldResultUpdated : Status of request.
******************************************************************************/
bool CycleDetailsListModel::isLastWeldResultUpdated()
{
    return m_IsLastWeldResultUpdated;
}

/**************************************************************************//**
*
* \brief   - Below function fetches auto graph request status.
*
* \param   - None.
*
* \return  - storedValue : Status of request.
******************************************************************************/
bool CycleDetailsListModel::isAutoRefreshGraph()
{
    bool storedValue = settings.value("AutoRefreshGraph").toBool();
    return storedValue;
}

/**************************************************************************//**
*
* \brief   - Below function updates auto graph request status.
*
* \param   - value : Status of request.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::autoRefreshGraphRequest(bool value)
{
    settings.setValue("AutoRefreshGraph", value);
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - value : Status of request.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::isScreenReNavigated(bool value)
{
    m_IsScreenReNavigated = value;
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status for Analyticls screen from Result button.
*
* \param   - value : Status of request.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::isScreenNavigatedFromResultsBtn(bool value, int target)
{
    m_IsScreenReNavigatedFrmResultBtn = value;
    m_SearchByCycleNo = target;
}

/**************************************************************************//**
*
* \brief   - Below function checks if particular weld cycle counter exists or not.
*
* \param   - CycleCounter : int CycleCounter.
*
* \return  - bool.
******************************************************************************/
bool CycleDetailsListModel::doesCycleCounterExist(int CycleCounter)
{
    for(const auto& result : m_WeldResultData)
    {
        if(result.CycleCounter == CycleCounter)
        {
            return true;// Found the matching CycleCounter
        }
    }
    return false;
}
/**************************************************************************//**
*
* \brief   - Below function return the weld signature object pointer.
*
* \param   - None.
*
* \return  - m_WeldSignatureACE : The weld signature object pointer.
******************************************************************************/
WeldSignatureACE *CycleDetailsListModel::getWeldSignatureACE()
{
    return m_WeldSignatureACE;
}

/**************************************************************************//**
*
* \brief   - Below function return the search by cycle no value.
*
* \param   - None.
*
* \return  - m_SearchByCycleNo : The search by cycle no value.
******************************************************************************/
int CycleDetailsListModel::getSearchByCycleNo() const
{
    return m_SearchByCycleNo;
}

/**************************************************************************//**
*
* \brief   - Below function updates the search by cycle no value.
*
* \param   - SearchByCycleNo : The search by cycle no value.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::updateSearchByCycleNo(const int &SearchByCycleNo)
{
        m_SearchByCycleNo = SearchByCycleNo;

        if(m_SearchByCycleNo >= 0)
        {
            /*Rendering logic*/
            m_IsLastWeldResultUpdated = false;
            m_WeldResultACE->InitiateSearchByCycleNumReadRequestToASC(m_SearchByCycleNo);
        }

        else
        {
            /*To initiate weld historical data read*/
            m_Counter = 0;
            m_WeldResultACE->SetIsLastWeldResultUpdated(true);
        }

        emit cycleDetailsListDataChanged();
}
/**************************************************************************//**
*
* \brief   - Below function return the recipe number of active list element.
*
* \param   - None.
*
* \return  - m_WeldResultData[getCurrentIndex()].WeldRecipeNumber : The recipe number of active list.
******************************************************************************/
int CycleDetailsListModel::getRecipeNumberFunc()
{
    if(m_WeldResultData.size() > getCurrentIndex() && (getCurrentIndex() != -1))
    {
        return m_WeldResultData[getCurrentIndex()].WeldRecipeNumber;
    }
    return 0;
}

/**************************************************************************//**
*
* \brief   - Below function return the recipe version of active list element.
*
* \param   - None.
*
* \return  - m_WeldResultData[getCurrentIndex()].WeldRecipeVersionNumber : The recipe version of active list.
******************************************************************************/
int CycleDetailsListModel::getRecipeVersionFunc()
{
    if(m_WeldResultData.size() > getCurrentIndex() && (getCurrentIndex() != -1))
    {
        return m_WeldResultData[getCurrentIndex()].WeldRecipeVersionNumber;
    }
    return 0;
}


/**************************************************************************//**
*
* \brief   - Below function fetches the weld trigger point to be shown on graph.
*
* \param   - None.
*
* \return  - m_SelectedTriggerPoint : The weld trigger point.
******************************************************************************/
float CycleDetailsListModel::getTriggerPoint()
{
    return m_SelectedTriggerPoint;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld trigger point to be shown on graph.
*
* \param   - TriggerPoint : The weld trigger point.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::updateTriggerPoint(float TriggerPoint)
{
    m_SelectedTriggerPoint = TriggerPoint;
}

/**************************************************************************//**
*
* \brief   - Below function fetches the weld sonic point to be shown on graph.
*
* \param   - None.
*
* \return  - m_SelectedWeldSonicPoint : The weld sonic point.
******************************************************************************/
float CycleDetailsListModel::getWeldSonicPoint()
{
    return m_SelectedWeldSonicPoint;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld sonic point to be shown on graph.
*
* \param   - WeldSonicPoint : The weld sonic point.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::updateWeldSonicPoint(float WeldSonicPoint)
{
    m_SelectedWeldSonicPoint = WeldSonicPoint;
}

/**************************************************************************//**
*
* \brief   - Below function fetches the weld hold point to be shown on graph.
*
* \param   - None.
*
* \return  - m_SelectedHoldPoint : The weld hold point.
******************************************************************************/
float CycleDetailsListModel::getHoldPoint()
{
    return m_SelectedHoldPoint;
}

/**************************************************************************//**
*
* \brief   - Below function updates the weld hold point to be shown on graph.
*
* \param   - HoldPoint : The weld hold point.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::updateHoldPoint(float HoldPoint)
{
    m_SelectedHoldPoint = HoldPoint;
}

/**************************************************************************//**
*
* \brief   - Below function returns the weld result index.
*
* \param   - Value : The Index at which weld result is requested.
*
* \return  - WeldResultIndex : The weld result index.
******************************************************************************/
int CycleDetailsListModel::getWeldResultIndex(int Value)
{
    return m_WeldResultData[Value].WeldResultIndex;
}

/**************************************************************************//**
*
* \brief   - Below function returns the recipe number.
*
* \param   - Value : The Index at which recipe number is requested.
*
* \return  - WeldRecipeNumber : The recipe number.
******************************************************************************/
int CycleDetailsListModel::getRecipeNumber(int Value)
{
    return m_WeldResultData[Value].WeldRecipeNumber;
}
/**************************************************************************//**
*
* \brief   - Below function returns the recipe version.
*
* \param   - Value : The Index at which recipe version is requested.
*
* \return  - WeldRecipeVersionNumber : The recipe version.
******************************************************************************/
int CycleDetailsListModel::getRecipeVersion(int Value)
{
    return m_WeldResultData[Value].WeldRecipeVersionNumber;
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type CycleDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void CycleDetailsListModel::createNewCycleDetailsList()
{
    CycleDetailsListData* ptrListObj = new CycleDetailsListData();
    addNewCycleDetailsList(ptrListObj);
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
    roles[CycleRoles::CycleIndexRole]    = "CycleIndex";
    roles[CycleRoles::CycleRecipeNoRole] = "CycleRecipeNo";
    roles[CycleRoles::CycleNoRole]       = "CycleNo";
    roles[CycleRoles::CycleWeldModeRole] = "CycleWeldMode";
    roles[CycleRoles::CycleDateTimeRole] = "CycleDateTime";
    roles[CycleRoles::CycleTriggerPointRole]   = "CycleTriggerPoint";
    roles[CycleRoles::CycleWeldSonicPointRole] = "CycleWeldSonicPoint";
    roles[CycleRoles::CycleHoldPointRole]      = "CycleHoldPoint";
    roles[CycleRoles::CycleWeldResultIdxRole]  = "CycleWeldResultIndex";

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
void CycleDetailsListModel::OnCycleDetailsListUpdated(WeldResultACE *AnlyticsGraphScreenWeldResult_Obj, WeldSignatureACE *AnlyticsGraphScreenWeldSignature_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_WeldResultACE = AnlyticsGraphScreenWeldResult_Obj;
    m_WeldSignatureACE = AnlyticsGraphScreenWeldSignature_Obj;
    bool storedValueAutoRefresh = settings.value("AutoRefreshGraph").toBool();

    if(((m_WeldResultACE->GetIsLastWeldResultUpdated()) || (m_IsScreenReNavigated)) && (m_Counter == 0))
    {
        m_Counter = 2;
    }
    //To check if Analyticals screen is navigated from Results button or not to initate search by cycle no.
    if(m_IsScreenReNavigatedFrmResultBtn)
    {
          m_WeldResultData = m_WeldResultACE->GetHistoricalWeldResultData();
        //Check if cycle exists or not.
        if(doesCycleCounterExist(m_SearchByCycleNo))
        {
            //Initiate cycle search to display data on screen
          m_WeldResultACE->InitiateSearchByCycleNumReadRequestToASC(m_SearchByCycleNo);
        }
        else
        {
            //Notify QML that weld cycle data is not present in historical data.
            emit cycleNumberAlarmDataChanged();
        }
        m_IsScreenReNavigatedFrmResultBtn = false;
    }

    if(m_ActiveWelderId != WelderId)
    {
        /*To decide which graph data to be display i.e. all or as per cycle number*/
        /*All historical weld data*/
        if((m_SearchByCycleNo < 0) && (m_Counter))
        {
            m_WeldResultData = m_WeldResultACE->GetHistoricalWeldResultData();
            /*To clear the update status flag*/
            /*To make sure historical weld data only gets read*/
            m_SearchByCycleNo = -1;
            loadCycleDetailsList();

            /*To avoid auto refresh of graph signature*/
            if(((storedValueAutoRefresh) || (m_IsScreenReNavigated)) && (m_Counter == 1))
            {
                /*Update T,W and H points*/
                m_SelectedTriggerPoint = m_WeldResultData.front().TriggerPoint;
                m_SelectedWeldSonicPoint = m_WeldResultData.front().WeldSonicPoint ;
                m_SelectedHoldPoint = m_WeldResultData.front().HoldPoint;

                /*Below parameter helps qml to display which weld graph shall get fetch*/
                emit initiateWeldGraphSignatureDisplay(m_WeldResultData.front().WeldResultIndex, true);
                /*To handle Auto Graph Refresh when its "off" condition*/
                m_IsScreenReNavigated = false;
            }

            emit cycleDetailsListDataChanged();
            m_Counter--;
        }

        /*Search by cycle*/
        else
        {
            if(m_Counter)
            {
                m_WeldResultData = m_WeldResultACE->GetCycleNumWeldResultData();
                /*To clear the update status flag*/
                m_IsLastWeldResultUpdated = true;
                loadCycleDetailsList();

                /*To avoid auto refresh of graph signature*/
                if((storedValueAutoRefresh) && (m_Counter == 1))
                {
                    /*Update T,W and H points*/
                    m_SelectedTriggerPoint = m_WeldResultData.front().TriggerPoint;
                    m_SelectedWeldSonicPoint = m_WeldResultData.front().WeldSonicPoint ;
                    m_SelectedHoldPoint = m_WeldResultData.front().HoldPoint;

                    /*Below parameter helps qml to display which weld graph shall get fetch*/
                    emit initiateWeldGraphSignatureDisplay(m_WeldResultData.front().WeldResultIndex, true);
                    /*To handle Auto Graph Refresh when its "off" condition*/
                    m_IsScreenReNavigated = false;
                }

                emit cycleDetailsListDataChanged();
                m_Counter--;
            }
        }

        if(m_WeldResultACE->GetIsLastWeldResultUpdated() && m_Counter == 0)
        {
            m_WeldResultACE->SetIsLastWeldResultUpdated(false);
        }
    }

    pthread_mutex_unlock(&mtx);
}

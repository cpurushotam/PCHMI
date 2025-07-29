/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file updates the recipe card screen.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 21/07/2023 - Initial version.
***************************************************************************/

#include "recipemodel.h"
#include "recipedef.h"
#include "MultiwelderInterface.h"
#include "StorageSupport.h"
/**************************************************************************//**
*
* \brief Constructor and initialize recipe list that will save all the properties of each recipe.
*
* \param QObject* parent
*
* \return None
*
******************************************************************************/
RecipeModel::RecipeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    pthread_mutex_init(&mtx, nullptr);
    connect(UpdateScreen::getInstance(), &UpdateScreen::RecipeCardsScreenUpdated, this, &RecipeModel::OnRecipeCardsUpdated);
    m_listRecipe.clear();
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
RecipeModel::~RecipeModel()
{
    pthread_mutex_destroy(&mtx);
    qDeleteAll(m_listRecipe.begin(), m_listRecipe.end());
    m_listRecipe.clear();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        Note: This function can be invoked via the meta-object system and from QML.
*        To get the recipe list size number.
*
* \param It can be ignored in here.
*
* \return Return recipe list size.
*
******************************************************************************/
int RecipeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listRecipe.count();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        To locate at the specific object using the Model Index and get the data from the specific object then.
*        Note: This function can be invoked via the meta-object system and from QML.
*        Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param index.row should be in the range of the recipe list.
*
* \return the property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_listRecipe.count())
        return QVariant();
    const RecipeGeneral *ptrRecipeObj = m_listRecipe[index.row()];
    switch (role)
    {
    case NumberRole:
        return QString::number(ptrRecipeObj->getRecipeNumber(), 10);
        break;
    case NameRole:
        return ptrRecipeObj->getRecipeName();
        break;
    case ActiveStatusRole:
        return ptrRecipeObj->getRecipeActiveStatus();
        break;
    case ValidateStatusRole:
        return ptrRecipeObj->getRecipeValidateStatus();
        break;
    case ModifiedStatusRole:
        return ptrRecipeObj->getRecipeModifiedStatus();
        break;
    case NewCardStatusRole:
        return ptrRecipeObj->getRecipeNewCardStatus();
        break;
    case WeldModeRole:
        return ptrRecipeObj->getWeldModeEnum();
        break;
    case WeldModeValueRole:
        return ptrRecipeObj->getWeldModeValue();
        break;
    case WeldModeUnitRole:
        return ptrRecipeObj->getWeldModeUnit();
        break;
    case CycleCountRole:
        return ptrRecipeObj->getRecipeWeldCycleCount();
        break;
    case VersionInfoRole:
        return ptrRecipeObj->getRecipeVersionInfo();
        break;
    case IsSavedRole:
        return ptrRecipeObj->getRecipeSaveStatus();
        break;
    default:
        return QVariant();
        break;
    }
    return QVariant();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        Returns the index of the data in row and column with parent.
*        Note: This function can be invoked via the meta-object system and from QML.
*        Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param index.row should be in the range of the recipe list.
*
* \return If the row is in the range of the recipe list, the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex RecipeModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    RecipeGeneral *ptrRecipeObj = nullptr;
    if(index.isValid() == false)
        ptrRecipeObj = m_listRecipe.at(0);
    else
        ptrRecipeObj = static_cast<RecipeGeneral*>(index.internalPointer());

    if (ptrRecipeObj)
        return createIndex(row, column, ptrRecipeObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief Insert a single recipe for the qml request action, such as Copy and Create a New Recipe.
*        Note: This function calls the virtual method insertRows.
*        Returns true if the row is inserted; otherwise returns false.
*        If the row is 0, it will be to create a new recipe for the qml Create New request,
*        else it will be copy the indicated recipe using the row number.
*
*
* \param row is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::insertRow(int row)
{
    /*Recipe create call*/
    m_MyRecipeCardsData->InitiateRecipeCreateRequest();

    if(row < 0 || row >= m_listRecipe.size())
        return false;

    if(m_listRecipe.size() > StorageSupport::GetMaxRecipeNumberSupportedFromJSON())
    {
        emit maxRecipeCountReached();
        return false;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    RecipeGeneral* ptrSrcRecipeObj = m_listRecipe.at(row);
    RecipeGeneral* ptrDecRecipeObj = nullptr;

    /*******************************************************************************/
    /* TODO : Implementation against create new recipe response from server
    /*******************************************************************************/

    if(row != 0)
    {
        ptrDecRecipeObj = new RecipeGeneral(m_listRecipe.size(), ptrSrcRecipeObj->getRecipeName(),
                                                       ptrSrcRecipeObj->getWeldModeEnum(),
                                                       ptrSrcRecipeObj->getWeldModeUnit(), ptrSrcRecipeObj->getWeldModeValue(),
                                                       ptrSrcRecipeObj->getRecipeActiveStatus(), ptrSrcRecipeObj->getRecipeValidateStatus(),
                                                       ptrSrcRecipeObj->getRecipeModifiedStatus(), false,
                                                       ptrSrcRecipeObj->getRecipeWeldCycleCount(),
                                                       ptrSrcRecipeObj->getRecipeVersionInfo(),
                                                       ptrSrcRecipeObj->getRecipeSaveStatus());
    }

    else
    {
        ptrDecRecipeObj = new RecipeGeneral(m_listRecipe.size(), strNewRecipeName,
                                                       RecipeEnum::TIME_IDX,
                                                       RecipeEnum::TIME_IDX, 0,
                                                       ptrSrcRecipeObj->getRecipeActiveStatus(), ptrSrcRecipeObj->getRecipeValidateStatus(),
                                                       ptrSrcRecipeObj->getRecipeModifiedStatus(), false,
                                                       ptrSrcRecipeObj->getRecipeWeldCycleCount(),
                                                       ptrSrcRecipeObj->getRecipeVersionInfo(),
                                                       ptrSrcRecipeObj->getRecipeSaveStatus());
    }
    m_listRecipe.append(ptrDecRecipeObj);
    endInsertRows();
    return true;
}

/**************************************************************************//**
*
* \brief Delete a single recipe for the qml request action, Delete.
*        Note: This function calls the virtual method removeRows.
*        Returns true if the row is deleted; otherwise returns false.
*        The empty card is not able to be removed, the screen always keep the empty card available upon the screen.
*
* \param row is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::removeRow(int row, int index)
{
    if(index <= 0 || index > StorageSupport::GetMaxRecipeNumberSupportedFromJSON())
    {
        return false;
    }

    if(m_MyRecipeCardsData->GetActiveWeldRecipeNumber() != row)
    {
        /*Recipe delete call*/
        m_MyRecipeCardsData->InitiateRecipeDeleteRequest(row);
    }

    else
    {
        emit recipeDeleteError();
        return false;
    }

    return true;
}

/**************************************************************************//**
*
* \brief To reset cycle count for the response from the qml.
*
* \param index is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::resetCycleCount(int row, int index)
{
    if(index <= 0 || index > m_listRecipe.size())
        return false;

    RecipeGeneral *ptrRecipeObj = m_listRecipe.at(index);

    /*Initiate request to reset cycle count*/
    m_MyRecipeCardsData->InitiateRecipeCycleCountResetRequest(row);

    ptrRecipeObj->setRecipeWeldCycleCount(0);

    QModelIndex rowVal = createIndex(index, 0, ptrRecipeObj);
    emit dataChanged(rowVal, rowVal, {RecipeModel::CycleCountRole});
    return true;
}

/**************************************************************************//**
*
* \brief To set Active status for the response from the qml
*
* \param index is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::setAsActive(int row, int index, bool isValidated)
{
    if(index <= 0 || index > StorageSupport::GetMaxRecipeNumberSupportedFromJSON())
    {
        return false;
    }

    RecipeGeneral *ptrRecipeObj = nullptr;
    for(int i = 0; i < m_listRecipe.size(); i++)
    {
        ptrRecipeObj = m_listRecipe.at(i);
        if(i != index)
        {
            if(ptrRecipeObj->getRecipeActiveStatus() != false)
            {
                ptrRecipeObj->setRecipeActiveStatus(false);
            }
        }

        else
        {
            if(ptrRecipeObj->getRecipeActiveStatus() != true)
            {
                /*Initiate request to set recipe as a active*/
                m_MyRecipeCardsData->InitiateRecipeSetAsActiveRequest(row);
                ptrRecipeObj->setRecipeActiveStatus(true);
                initProductionValue();
            }
        }

        /*Go for activation only if validated*/
        if(isValidated)
        {
            QModelIndex row = createIndex(i, 0, ptrRecipeObj);
            emit dataChanged(row, row, {RecipeModel::ActiveStatusRole});
        }
    }

    return true;
}

/**************************************************************************//**
*
* \brief To initialize parameters that needs to show upon the Production Run Screen.
*        Once the current Active recipe card is changed, the parameters need to synchronize with Production Run mode.
*
* \param None.
*
* \return If there is any issue on the parameters updating, the result is false; else the result is true.
*
******************************************************************************/
bool RecipeModel::initProductionValue()
{
    /*TODO : Implementation for synchoronization of active recipe that with
             Production Screen*/
    return true;
}

/**************************************************************************//**
*
* \brief To append a new recipe object to the recipe list.
*
* \param recipe object
*
* \return none
*
******************************************************************************/
void RecipeModel::addNewRecipe(RecipeGeneral *recipe)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_listRecipe.append(recipe);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief To clear the recipe list before the entire recipes are loaded for SC so
*        the data of recipe list can be synchronize with SC.    .
*
* \param none
*
* \return none
*
******************************************************************************/
void RecipeModel::clearRecipes()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    qDeleteAll(m_listRecipe);
    m_listRecipe.clear();
    endRemoveRows();
}

/**************************************************************************//**
*
* \brief   - loadRecipeCards function called by qml while loading of
*            recipe card screen, to display available recipes.
*
* \param   - RecipeCardsData_Obj : Object pointer of type WeldRecipeACEPRO.
*
* \return  - None.
******************************************************************************/
void RecipeModel::loadRecipeCards()
{
    clearRecipes();
    createNewRecipe();
    RecipeGeneral* ptrRecipeObj = nullptr;
     /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    for (auto it=m_MyRecipeCardDataMap.begin(); it!=m_MyRecipeCardDataMap.end(); ++it)
    {
        /*Check if recipe is active or not*/
        if(m_MyRecipeCardsData->GetActiveWeldRecipeNumber() != it->second.WeldRecipeNumber)
        {
            ptrRecipeObj = new RecipeGeneral(it->second.WeldRecipeNumber, it->second.WeldRecipeName, it->second.WeldMode, it->second.WeldMode,   it->second.ModeValue, false, false, false, false,
                                             it->second.CycleCount, it->second.WeldRecipeVersionNumber, true);
        }

        else
        {
            ptrRecipeObj = new RecipeGeneral(it->second.WeldRecipeNumber, it->second.WeldRecipeName, it->second.WeldMode, it->second.WeldMode,   it->second.ModeValue, true,  false, false, false,
                                             it->second.CycleCount, it->second.WeldRecipeVersionNumber, m_IsActiveRecipeSaved);
        }

        addNewRecipe(ptrRecipeObj);
    }
     /*Mutex unlock*/
    pthread_mutex_unlock(&mtx);
}

/**************************************************************************//**
*
* \brief   - Role of the createRecipe to create recipe as request initiated
*            from weld mode screen.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
bool RecipeModel::createNewRecipeFromWeldMode()
{
    /*Recipe create call*/
    m_MyRecipeCardsData->InitiateRecipeCreateRequest();

    /*To verify max recipe count reached or not*/
    if(m_listRecipe.size() > StorageSupport::GetMaxRecipeNumberSupportedFromJSON())
    {
        emit maxRecipeCountReached();
        return false;
    }

    return true;
}

/**************************************************************************//**
*
* \brief   - Role of the initiateRecipeCopyRequest to initiate recipe copy functionality which includes below scenarios.
*            1. When copy request made for unique recipe number then copy operation get executed.
*            2. When destination recipe number is not unique then this funtion
*               generates popup to reconfirm override over alredy available destination recipe.
*               If yes selected then copy operation gets execute, or cancels when no selected.
*
* \param   - SourceRecipeNo : Source recipe number.
*          - DestinationRecipeNo : Destination recipe number.
*          - IsReConfirmed : Input given after notifying override operation.
*
* \return  - None.
******************************************************************************/
void RecipeModel::initiateRecipeCopyRequest(int SourceRecipeNo, int DestinationRecipeNo, bool IsReConfirmed)
{
    bool isOverlapped = false;

    if(! IsReConfirmed)
    {
        for (auto it = m_MyRecipeCardDataMap.begin(); it != m_MyRecipeCardDataMap.end(); ++it)
        {
            if(it->second.WeldRecipeNumber == DestinationRecipeNo)
            {
                emit recipeOverride(DestinationRecipeNo);
                isOverlapped = true;
                break;
            }
        }
    }

    if (! isOverlapped)
    {
        m_MyRecipeCardsData->InitiateWeldRecipeCopyRequest(SourceRecipeNo, DestinationRecipeNo);
    }

    if((m_listRecipe.size() > StorageSupport::GetMaxRecipeNumberSupportedFromJSON()) && (! isOverlapped))
    {
        emit maxRecipeCountReached();
    }
}

/**************************************************************************//**
*
* \brief   - Role of the function getActiveRecipeNumber to return active
*            recipe number.
*
* \param   - None.
*
* \return  - Active recipe number.
******************************************************************************/
int RecipeModel::getActiveRecipeNumber()
{
    return m_MyRecipeCardsData->GetActiveWeldRecipeNumber();
}

/**************************************************************************//**
*
* \brief To create a empty recipe only for the new recipe creating card shown on the screen.
*
* \param none
*
* \return none
*
******************************************************************************/
void RecipeModel::createNewRecipe()
{
    RecipeGeneral* ptrRecipeObj = new RecipeGeneral();
    addNewRecipe(ptrRecipeObj);
}

/**************************************************************************//**
*
* \brief Define which properties need to expose to QML under the recipe Model.
*        Generate a link table between Model and list data.
*
* \param None
*
* \return Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> RecipeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RecipesRoles::NumberRole]         = "assignedNum";
    roles[RecipesRoles::NameRole]           = "assignedName";
    roles[RecipesRoles::CompanyNameRole]    = "companyName";
    roles[RecipesRoles::ActiveStatusRole]   = "isActive";
    roles[RecipesRoles::ValidateStatusRole] = "isValidate";
    roles[RecipesRoles::ModifiedStatusRole] = "isModefied";
    roles[RecipesRoles::NewCardStatusRole]  = "isNewCard";
    roles[RecipesRoles::WeldModeRole]       = "weldModeEnum";
    roles[RecipesRoles::WeldModeValueRole]  = "weldModeValue";
    roles[RecipesRoles::WeldModeUnitRole]   = "weldModeUnit";
    roles[RecipesRoles::CycleCountRole]     = "cycleCount";
    roles[RecipesRoles::VersionInfoRole]    = "versionInfo";
    roles[RecipesRoles::IsSavedRole]        = "isSaved";
    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnRecipeCardsUpdated to update the recipe cards data.
*
* \param   - RecipeCardsData_Obj : Object pointer of type WeldRecipeACEPRO.
*
* \return  - None.
******************************************************************************/
void RecipeModel::OnRecipeCardsUpdated(WeldRecipeACE *RecipeCardsData_Obj, int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    /*Local copy of received data*/
    m_MyRecipeCardsData = RecipeCardsData_Obj;

    if(m_MyRecipeCardsData->IsMapUpdated() || (m_ActiveWelderId != WelderId))
    {
        m_MyRecipeCardDataMap = m_MyRecipeCardsData->GetRecipeCardDataMap();
        pthread_mutex_unlock(&mtx);
        m_IsActiveRecipeSaved = m_MyRecipeCardsData->IsActiveWeldRecipeSaved();
        loadRecipeCards();

        m_ActiveWelderId = WelderId;
    }

    else
    {
        /*Mutex unlock*/
        pthread_mutex_unlock(&mtx);
    }
}

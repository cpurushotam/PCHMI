/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanCycleDetailsListModel.cpp file handles cycle details list model container.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 02/04/2024 - Initial version.
***************************************************************************/
#include "ScanCycleDetailsListModel.h"

/* init log variable */
size_t ScanCycleDetailsListModel::m_Sclog_id = 0 ;
/**************************************************************************//**
*
* \brief  - Constructor to clear scan data list that will save all the graph cycles details
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
ScanCycleDetailsListModel::ScanCycleDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    /* enroll to use logger functionality */
    m_Sclog_id = Logger::enroll(this);

    pthread_mutex_init(&mtx, nullptr);
    m_ListData.clear();

    connect(UpdateScreen::getInstance(), &UpdateScreen::ScanScreenUpdated, this, &ScanCycleDetailsListModel::OnCycleDetailsListUpdated);

    m_IsLastScanResultUpdated = true;
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
ScanCycleDetailsListModel::~ScanCycleDetailsListModel()
{
    qDeleteAll(m_ListData.begin(), m_ListData.end());
    m_ListData.clear();
}

/**************************************************************************//**
*
* \brief   - Below function triggers the start scan operation command.
*
* \param   - Type : The start operation flag.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::startHornScan(bool Value)
{
    m_StartHornScan = Value;
    m_ScanResult->InitiateScanRunOperation();
//    emit scanCycleDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function triggers the abort scan operation command.
*
* \param   - Type : The abort operation flag.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::abortHornScan(bool Value)
{
    m_AbortHornScan = Value;
    m_ScanResult->AbortScanRunOperation();
//    emit scanCycleDetailsListDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan cycle number.
*
* \param   - None.
*
* \return  - m_ScanCycleNo : The scan cycle number.
******************************************************************************/
int ScanCycleDetailsListModel::getScanCycleNo() const
{
    return m_ScanCycleNo;
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan frequency.
*
* \param   - None.
*
* \return  - m_ScanFreq : The scan frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanFreq() const
{
    return m_ScanFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 1st parallel frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 1st parallel frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanMainParallelResFreq() const
{
    return m_ScanMainParallelResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 2nd parallel frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 2nd parallel frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanSecondParallelResFreq() const
{
    return m_ScanSecondParallelResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 3rd parallel frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 3rd parallel frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanThirdParallelResFreq() const
{
    return m_ScanThirdParallelResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 1st series frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 1st series frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanMainSeriesResFreq() const
{
    return m_ScanMainSeriesResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 2nd series frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 2nd series frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanSecondSeriesResFreq() const
{
    return m_ScanSecondSeriesResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the 3rd series frequency.
*
* \param   - None.
*
* \return  - m_ScanMainParallelResFreq : The 3rd series frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanThirdSeriesResFreq() const
{
    return m_ScanThirdSeriesResFreq;
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan frequency step value.
*
* \param   - None.
*
* \return  - m_ScanFreqStep : The scan frequency step value.
******************************************************************************/
int ScanCycleDetailsListModel::getScanFreqStep() const
{
    return m_ScanFreqStep;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan frequency step value.
*
* \param   - ScanFreqStep : The scan frequency step value.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanFreqStep(const int &ScanFreqStep)
{
    m_ScanFreqStep = ScanFreqStep;
    m_ScanRecipeDataLocal.FrequencyStep = m_ScanFreqStep;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan maximum amplitude.
*
* \param   - None.
*
* \return  - m_ScanMaxAmplitude : The scan maximum amplitude.
******************************************************************************/
int ScanCycleDetailsListModel::getScanMaxAmplitude() const
{
    return m_ScanMaxAmplitude;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan maximum amplitude.
*
* \param   - ScanMaxAmplitude : The scan maximum amplitude.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanMaxAmplitude(const int &ScanMaxAmplitude)
{
    m_ScanMaxAmplitude = ScanMaxAmplitude;
    m_ScanRecipeDataLocal.MaxAmplitude = m_ScanMaxAmplitude;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan maximum current.
*
* \param   - None.
*
* \return  - m_ScanMaxCurrent : The scan maximum current.
******************************************************************************/
int ScanCycleDetailsListModel::getScanMaxCurrent() const
{
    return m_ScanMaxCurrent;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan maximum current.
*
* \param   - ScanMaxCurrent : The scan maximum current.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanMaxCurrent(const int &ScanMaxCurrent)
{
    m_ScanMaxCurrent = ScanMaxCurrent;
    m_ScanRecipeDataLocal.MaxCurrent = m_ScanMaxCurrent;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan digital tune flag.
*
* \param   - None.
*
* \return  - m_ScanSetDigitalTune : The scan digital tune flag.
******************************************************************************/
bool ScanCycleDetailsListModel::getScanSetDigitalTune() const
{
    return m_ScanSetDigitalTune;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan digital tune flag.
*
* \param   - ScanSetDigitalTune : The scan digital tune flag.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanSetDigitalTune(const bool &ScanSetDigitalTune)
{
    m_ScanSetDigitalTune = ScanSetDigitalTune;
    m_ScanRecipeDataLocal.SetDigTuneWithHornScan = m_ScanSetDigitalTune;
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan start frequency.
*
* \param   - None.
*
* \return  - m_ScanStartFrequency : The scan start frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanStartFrequency() const
{
    return m_ScanStartFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan start frequency.
*
* \param   - ScanStartFrequency : The scan start frequency.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanStartFrequency(const int &ScanStartFrequency)
{
    m_ScanStartFrequency = ScanStartFrequency;
    m_ScanRecipeDataLocal.FrequencyStart = m_ScanStartFrequency;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan stop frequency.
*
* \param   - None.
*
* \return  - m_ScanStopFrequency : The scan stop frequency.
******************************************************************************/
int ScanCycleDetailsListModel::getScanStopFrequency() const
{
    return m_ScanStopFrequency;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan stop frequency.
*
* \param   - ScanStopFrequency : The scan stop frequency.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanStopFrequency(const int &ScanStopFrequency)
{
    m_ScanStopFrequency = ScanStopFrequency;
    m_ScanRecipeDataLocal.FrequencyStop = m_ScanStopFrequency;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan time delay.
*
* \param   - None.
*
* \return  - m_ScanTimeDelay : The scan time delay.
******************************************************************************/
float ScanCycleDetailsListModel::getScanTimeDelay() const
{
    return m_ScanTimeDelay;
}

/**************************************************************************//**
*
* \brief   - Below function updates the scan time delay.
*
* \param   - ScanTimeDelay : The scan scan time delay.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanTimeDelay(const float &ScanTimeDelay)
{
    m_ScanTimeDelay = ScanTimeDelay;
    m_ScanRecipeDataLocal.TimeDelay = m_ScanTimeDelay;
    emit scanRecipeDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function returns the scan run operation status.
*
* \param   - None
*
* \return  - m_ScanRunStatus : The scan run operation status.
******************************************************************************/
float ScanCycleDetailsListModel::getScanRunStatus() const
{
    return m_ScanRunStatus;
}

/**************************************************************************//**
*
* \brief   - Below function updates scan run operation status.
*
* \param   - ScanRunStatus : The scan run operation status.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::updateScanRunStatus(const float &ScanRunStatus)
{
    m_ScanRunStatus = ScanRunStatus;
    emit scanRunStatusDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function updates screen navigation status.
*
* \param   - value : Status of request.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::isScreenReNavigated(bool value)
{
    m_IsScreenReNavigated = value;
}

/**************************************************************************//**
*
* \brief   - Below function returns min parameter values.
*
* \param   - Type : The type for which value need to fetch.
*
* \return  - None.
******************************************************************************/
QString ScanCycleDetailsListModel::getMinScanParametersValue(int Type)
{
    std::string strMinVal;
    switch (Type)
    {
    case SCAN_FREQ_STEP :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(FREQUENCY_STEP);
        break;

    case SCAN_MAX_AMPLITUDE :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(MAX_AMPLITUDE);

        break;

    case SCAN_MAX_CURRENT :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(MAX_CURRENT);

        break;

    case SCAN_START_FREQUENCY :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(FREQUENCY_START);

        break;

    case SCAN_STOP_FREQUENCY :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(FREQUENCY_STOP);

        break;

    case SCAN_TIME_DELAY :
        strMinVal=  m_ScanRecipe->GetHornScanRecipeParamMinValue(TIMEDELAY);

        break;

    default :
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "getMinScanParametersValue failed");

        break;
    }
    return QString::fromLocal8Bit(strMinVal.c_str());
}

/**************************************************************************//**
*
* \brief   - Below function returns max parameter values.
*
* \param   - Type : The type for which value need to fetch.
*
* \return  - None.
******************************************************************************/
QString ScanCycleDetailsListModel::getMaxScanParametersValue(int Type)
{
    std::string strMaxVal;
    switch (Type)
    {
    case SCAN_FREQ_STEP :
          strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(FREQUENCY_STEP);
        break;

    case SCAN_MAX_AMPLITUDE :
        strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(MAX_AMPLITUDE);

        break;

    case SCAN_MAX_CURRENT :
        strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(MAX_CURRENT);

        break;

    case SCAN_START_FREQUENCY :
        strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(FREQUENCY_START);

        break;

    case SCAN_STOP_FREQUENCY :
        strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(FREQUENCY_STOP);

        break;

    case SCAN_TIME_DELAY :
        strMaxVal=  m_ScanRecipe->GetHornScanRecipeParamMaxValue(TIMEDELAY);

        break;

    default :
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "getMaxScanParametersValue failed");

        break;
    }
    return QString::fromLocal8Bit(strMaxVal.c_str());

}

/**************************************************************************//**
*
* \brief   - Role of onSavedPressed is to save the scan recipedata.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::onSavedPressed()
{
    m_ScanRecipe->SetHornScanRecipeData(m_ScanRecipeDataLocal);
}

/**************************************************************************//**
*
* \brief   - Role of onResetToDefaultPressed is to restore default scan
*            recipe settings.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::onResetToDefaultPressed()
{
    m_ScanRecipe->InitiateResetToDefaultRequest();
}

/**************************************************************************//**
*
* \brief   - Role of onScanRecipeScreenReNavigated is to make sure updated
*            recipe data available.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::onScanRecipeScreenReNavigated()
{
    m_ScanRecipe->SetIsHornScanRecipeUpdated(true);
}

/**************************************************************************//**
*
* \brief   - Role of getResonantFrequencies is to update all resonant frequencies
*            values.
*
* \param   - Index : Index of requested historical scan cycle.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::getResonantFrequencies(int Index)
{
    m_ScanMainParallelResFreq = m_ScanResultData[Index].MainParallelResonantFrequency;
    m_ScanSecondParallelResFreq = m_ScanResultData[Index].SecondParallelResonantFrequency;
    m_ScanThirdParallelResFreq = m_ScanResultData[Index].ThirdParallelResonantFrequency;
    m_ScanMainSeriesResFreq = m_ScanResultData[Index].FirstSeriesResonantFrequency;
    m_ScanSecondSeriesResFreq = m_ScanResultData[Index].SecondSeriesResonantFrequency;
    m_ScanThirdSeriesResFreq = m_ScanResultData[Index].ThirdSeriesResonantFrequency;

    emit scanResonantFreqDataChanged();
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
* \return - Return scan cycle details list size.
*
******************************************************************************/
int ScanCycleDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant ScanCycleDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const ScanCycleDetailsListData *ptrListObj = m_ListData[index.row()];
    switch (role)
    {
    case CycleIndexRole:
        return ptrListObj->getCycleIndex();
        break;

    case CycleDateTimeRole:
        return ptrListObj->getCycleDateTime();
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
* \param  - index.row should be in the range of the scan cycle details list.
*
* \return - If the row is in the range of the scan cycle details list,
*         - the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex ScanCycleDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    ScanCycleDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<ScanCycleDetailsListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief - To clear the scan cycle details list before the entire scan cycle details are loaded.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void ScanCycleDetailsListModel::clearCycleDetailsList()
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
void ScanCycleDetailsListModel::addNewCycleDetailsList(ScanCycleDetailsListData *ScanCycleDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(ScanCycleDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - LoadCycleDetailsList function called by qml while loading of
*            scan cycle detail list, to display available cycle details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::loadCycleDetailsList()
{
    createNewCycleDetailsList();
    clearCycleDetailsList();

    ScanCycleDetailsListData* ptrListObj = nullptr;

   for (unsigned int Index = 0; Index < m_ScanResultData.size(); Index++)
   {
       ptrListObj = new ScanCycleDetailsListData(m_ScanResultData[Index].HornScanResultIndex, m_ScanResultData[Index].DateTime);
       addNewCycleDetailsList(ptrListObj);
   }

}

/**************************************************************************//**
*
* \brief   - Below function fetches the status of scan result update status.
*
* \param   - None.
*
* \return  - m_IsLastScanResultUpdated : Status of request.
******************************************************************************/
bool ScanCycleDetailsListModel::isLastScanResultUpdated()
{
    return m_IsLastScanResultUpdated;
}

/**************************************************************************//**
*
* \brief   - Returns the info whether recipe structures are equal are not.
*
* \param   - ScanRecipestruct : The recipe structure which is being compare.
*
* \return  - The info whether recipe structures are equal are not.
******************************************************************************/
bool ScanCycleDetailsListModel::areRecipeValuesEqual(const structHornScanRecipe &ScanRecipestruct_1, const structHornScanRecipe &ScanRecipestruct_2)
{
    return std::memcmp(&ScanRecipestruct_1, &ScanRecipestruct_2, sizeof(structHornScanRecipe)) == 0;
}

/**************************************************************************//**
*
* \brief   - Below function return the scan signature object pointer.
*
* \param   - None.
*
* \return  - m_ScanSignature : The scan signature object pointer.
******************************************************************************/
//ScanSignature *ScanCycleDetailsListModel::getScanSignature()
//{
//    return m_ScanSignature;
//}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type ScanCycleDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::createNewCycleDetailsList()
{
    ScanCycleDetailsListData* ptrListObj = new ScanCycleDetailsListData();
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
QHash<int, QByteArray> ScanCycleDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CycleRoles::CycleIndexRole]    = "CycleIndex";
    roles[CycleRoles::CycleDateTimeRole] = "CycleDateTime";

    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnCycleDetailsListUpdated to update the scan cycle
*            details list data.
*
* \param   - RecipeCardsData_Obj : Object pointer of type ScanRecipeACEPRO.
*
* \return  - None.
******************************************************************************/
void ScanCycleDetailsListModel::OnCycleDetailsListUpdated(HornScanResult *DiagnosticsScanResultScreen_Obj, HornScanSignature *DiagnosticsScanSignatureScreen_Obj, HornScanRecipe *DiagnosticsScanRecipeScreen_Obj,
                                                          int WelderId)
{
    /*Mutex lock*/
    pthread_mutex_lock(&mtx);
    m_ScanResult = DiagnosticsScanResultScreen_Obj;
    m_ScanSignature = DiagnosticsScanSignatureScreen_Obj;
    m_ScanRecipe = DiagnosticsScanRecipeScreen_Obj;

    if((m_ScanResult->GetIsLastHornScanResultUpdated() || m_IsScreenReNavigated) && (m_Counter == 0))
    {
        m_Counter = 2;
        m_IsScreenReNavigated = false;
    }

    if(m_ActiveWelderId != WelderId)
    {
        /*All historical scan data*/
        if((m_Counter))
        {
            m_ScanResultData = m_ScanResult->GetHistoricalHornScanResultData();
            /*To clear the update status flag*/
            m_IsLastScanResultUpdated = true;
            /*To make sure historical scan data only gets read*/
            loadCycleDetailsList();

            if(m_Counter == 1)
            {
                /*Below parameter helps qml to display which scan graph shall get fetch*/
                emit initiateScanGraphSignatureDisplay(m_ScanResultData.front().HornScanResultIndex, true);

                /*Update all frequencies*/
                m_ScanMainParallelResFreq = m_ScanResultData.front().MainParallelResonantFrequency;
                m_ScanSecondParallelResFreq = m_ScanResultData.front().SecondParallelResonantFrequency;
                m_ScanThirdParallelResFreq = m_ScanResultData.front().ThirdParallelResonantFrequency;
                m_ScanMainSeriesResFreq = m_ScanResultData.front().FirstSeriesResonantFrequency;
                m_ScanSecondSeriesResFreq = m_ScanResultData.front().SecondSeriesResonantFrequency;
                m_ScanThirdSeriesResFreq = m_ScanResultData.front().ThirdSeriesResonantFrequency;

                emit scanResonantFreqDataChanged();
            }

            emit scanCycleDetailsListDataChanged();
            m_Counter--;
        }

        m_scanRecipeData = m_ScanRecipe->GetHornScanRecipeData();
        /*Below statement make sure update shall happend when either screen navigated or
          restored to default request generated*/

        if(m_ScanRecipe->GetIsHornScanRecipeUpdated())
        {
            /*To check whether both recipe structures are equal or not to control
              loading status on the screen*/

            if(areRecipeValuesEqual(m_scanRecipeData, m_ScanRecipeDataLocal))
            {
                emit areScanRecipeValuesEqual(true);
            }

            else
            {
                emit areScanRecipeValuesEqual(false);
            }

            m_ScanRecipeDataLocal = m_scanRecipeData;

            m_ScanFreqStep = m_scanRecipeData.FrequencyStep;
            m_ScanMaxAmplitude = m_scanRecipeData.MaxAmplitude;
            m_ScanMaxCurrent = m_scanRecipeData.MaxCurrent;
            m_ScanSetDigitalTune = m_scanRecipeData.SetDigTuneWithHornScan;
            m_ScanStartFrequency = m_scanRecipeData.FrequencyStart;
            m_ScanStopFrequency = m_scanRecipeData.FrequencyStop;
            m_ScanTimeDelay = m_scanRecipeData.TimeDelay;

            emit scanRecipeDataChanged();

            m_ScanRecipe->SetIsHornScanRecipeUpdated(false);
        }

        if(m_ScanResult->GetIsLastHornScanResultUpdated() && m_Counter == 0)
        {
            m_ScanResult->SetIsLastHornScanResultUpdated(false);
        }
    }

    pthread_mutex_unlock(&mtx);
}

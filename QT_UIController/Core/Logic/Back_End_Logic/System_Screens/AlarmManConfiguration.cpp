/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares AlarmManConfiguration class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include "AlarmManConfiguration.h"
/**************************************************************************//**
*
* \brief  - Constructor to initliaze rowNames and colNames.
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
AlarmManConfiguration::AlarmManConfiguration(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::AlarmManagementViewUpdated, this, &AlarmManConfiguration::OnAlarmConfigDetailsUpdated);
    m_AlarmManagementData = {0};
    m_ColNames <<"Reset Required" << "Log Alarm"<< "General Alarm"<< "Custom Alarm" << "Cycle Counter";
    noOfRows = 8;
    noOfColumns = 5;
    m_RowNames <<  "No Cycle" <<"Hardware Failure" << "Cycle Modified"<< "Reject"<< "Warnings"<< "Overloads"<< "Non Cycle Overloads" << "Suspect";
}

/**************************************************************************//**
*
* \brief   - Below function is used to return the RowNames to HMI.
*
* \param   - None.
*
* \return  - QStringList.
******************************************************************************/
QStringList AlarmManConfiguration::rowNames() const
{
    return m_RowNames;
}

/**************************************************************************//**
*
* \brief   - Below function is used to return the column names to HMI.
*
* \param   - None.
*
* \return  - QStringList.
******************************************************************************/

QStringList AlarmManConfiguration::colNames() const
{
    return m_ColNames;
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
int AlarmManConfiguration::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return noOfRows * noOfColumns;
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
QVariant AlarmManConfiguration::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= rowCount() || role != ValueRole)
        return QVariant();

    switch (index.row()) {
    case 0: return m_AlarmManagementData.NoCycleAlarmActions.ResetRequired;
    case 1: return m_AlarmManagementData.NoCycleAlarmActions.LogAlarm;
    case 2: return m_AlarmManagementData.NoCycleAlarmActions.GeneralAlarm;
    case 3: return m_AlarmManagementData.NoCycleAlarmActions.CustomAlarmOutput;
    case 4: return m_AlarmManagementData.NoCycleAlarmActions.CycleCounter;

    case 5: return m_AlarmManagementData.HardwareFailureAlarmActions.ResetRequired;
    case 6: return m_AlarmManagementData.HardwareFailureAlarmActions.LogAlarm;
    case 7: return m_AlarmManagementData.HardwareFailureAlarmActions.GeneralAlarm;
    case 8: return m_AlarmManagementData.HardwareFailureAlarmActions.CustomAlarmOutput;
    case 9: return m_AlarmManagementData.HardwareFailureAlarmActions.CycleCounter;

    case 10: return m_AlarmManagementData.CycleModifiedAlarmActions.ResetRequired;
    case 11: return m_AlarmManagementData.CycleModifiedAlarmActions.LogAlarm;
    case 12: return m_AlarmManagementData.CycleModifiedAlarmActions.GeneralAlarm;
    case 13: return m_AlarmManagementData.CycleModifiedAlarmActions.CustomAlarmOutput;
    case 14: return m_AlarmManagementData.CycleModifiedAlarmActions.CycleCounter;

    case 15: return m_AlarmManagementData.RejectAlarmActions.ResetRequired;
    case 16: return m_AlarmManagementData.RejectAlarmActions.LogAlarm;
    case 17: return m_AlarmManagementData.RejectAlarmActions.GeneralAlarm;
    case 18: return m_AlarmManagementData.RejectAlarmActions.CustomAlarmOutput;
    case 19: return m_AlarmManagementData.RejectAlarmActions.CycleCounter;


    case 20: return m_AlarmManagementData.WarningAlarmActions.ResetRequired;
    case 21: return m_AlarmManagementData.WarningAlarmActions.LogAlarm;
    case 22: return m_AlarmManagementData.WarningAlarmActions.GeneralAlarm;
    case 23: return m_AlarmManagementData.WarningAlarmActions.CustomAlarmOutput;
    case 24: return m_AlarmManagementData.WarningAlarmActions.CycleCounter;

    case 25: return m_AlarmManagementData.OverloadAlarmActions.ResetRequired;
    case 26: return m_AlarmManagementData.OverloadAlarmActions.LogAlarm;
    case 27: return m_AlarmManagementData.OverloadAlarmActions.GeneralAlarm;
    case 28: return m_AlarmManagementData.OverloadAlarmActions.CustomAlarmOutput;
    case 29: return m_AlarmManagementData.OverloadAlarmActions.CycleCounter;

    case 30: return m_AlarmManagementData.NoCycleOverloadAlarmActions.ResetRequired;
    case 31: return m_AlarmManagementData.NoCycleOverloadAlarmActions.LogAlarm;
    case 32: return m_AlarmManagementData.NoCycleOverloadAlarmActions.GeneralAlarm;
    case 33: return m_AlarmManagementData.NoCycleOverloadAlarmActions.CustomAlarmOutput;
    case 34: return m_AlarmManagementData.NoCycleOverloadAlarmActions.CycleCounter;

    case 35: return m_AlarmManagementData.SuspectAlarmActions.ResetRequired;
    case 36: return m_AlarmManagementData.SuspectAlarmActions.LogAlarm;
    case 37: return m_AlarmManagementData.SuspectAlarmActions.GeneralAlarm;
    case 38: return m_AlarmManagementData.SuspectAlarmActions.CustomAlarmOutput;
    case 39: return m_AlarmManagementData.SuspectAlarmActions.CycleCounter;

    default: return QVariant();
    }
}
/**************************************************************************//**
*
* \brief  - Qt Item model standard interface
*           The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*           To locate at the specific object using the Model Index and set the data from the specific object then.
*           Note: This function can be invoked via the meta-object system and from QML.
*           Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - row and value : To determine the row for designated value.
*
* \return - The property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
bool AlarmManConfiguration::setData(int row, bool value) {
    if (row < 0 || row >= rowCount())
        return false;

    bool boolValue = value;
    switch (row) {
    case 0: m_AlarmManagementData.NoCycleAlarmActions.ResetRequired     = boolValue; break;
    case 1: m_AlarmManagementData.NoCycleAlarmActions.LogAlarm          = boolValue; break;
    case 2: m_AlarmManagementData.NoCycleAlarmActions.GeneralAlarm      = boolValue; break;
    case 3: m_AlarmManagementData.NoCycleAlarmActions.CustomAlarmOutput = boolValue; break;
    case 4: m_AlarmManagementData.NoCycleAlarmActions.CycleCounter      = boolValue; break;

    case 5: m_AlarmManagementData.HardwareFailureAlarmActions.ResetRequired     = boolValue; break;
    case 6: m_AlarmManagementData.HardwareFailureAlarmActions.LogAlarm          = boolValue; break;
    case 7: m_AlarmManagementData.HardwareFailureAlarmActions.GeneralAlarm      = boolValue; break;
    case 8: m_AlarmManagementData.HardwareFailureAlarmActions.CustomAlarmOutput = boolValue; break;
    case 9: m_AlarmManagementData.HardwareFailureAlarmActions.CycleCounter      = boolValue; break;

    case 10: m_AlarmManagementData.CycleModifiedAlarmActions.ResetRequired     = boolValue; break;
    case 11: m_AlarmManagementData.CycleModifiedAlarmActions.LogAlarm          = boolValue; break;
    case 12: m_AlarmManagementData.CycleModifiedAlarmActions.GeneralAlarm      = boolValue; break;
    case 13: m_AlarmManagementData.CycleModifiedAlarmActions.CustomAlarmOutput = boolValue; break;
    case 14: m_AlarmManagementData.CycleModifiedAlarmActions.CycleCounter      = boolValue; break;

    case 15: m_AlarmManagementData.RejectAlarmActions.ResetRequired     = boolValue; break;
    case 16: m_AlarmManagementData.RejectAlarmActions.LogAlarm          = boolValue; break;
    case 17: m_AlarmManagementData.RejectAlarmActions.GeneralAlarm      = boolValue; break;
    case 18: m_AlarmManagementData.RejectAlarmActions.CustomAlarmOutput = boolValue; break;
    case 19: m_AlarmManagementData.RejectAlarmActions.CycleCounter      = boolValue; break;

    case 20: m_AlarmManagementData.WarningAlarmActions.ResetRequired     = boolValue; break;
    case 21: m_AlarmManagementData.WarningAlarmActions.LogAlarm          = boolValue; break;
    case 22: m_AlarmManagementData.WarningAlarmActions.GeneralAlarm      = boolValue; break;
    case 23: m_AlarmManagementData.WarningAlarmActions.CustomAlarmOutput = boolValue; break;
    case 24: m_AlarmManagementData.WarningAlarmActions.CycleCounter      = boolValue; break;

    case 25: m_AlarmManagementData.OverloadAlarmActions.ResetRequired     = boolValue; break;
    case 26: m_AlarmManagementData.OverloadAlarmActions.LogAlarm          = boolValue; break;
    case 27: m_AlarmManagementData.OverloadAlarmActions.GeneralAlarm      = boolValue; break;
    case 28: m_AlarmManagementData.OverloadAlarmActions.CustomAlarmOutput = boolValue; break;
    case 29: m_AlarmManagementData.OverloadAlarmActions.CycleCounter      = boolValue; break;

    case 30: m_AlarmManagementData.NoCycleOverloadAlarmActions.ResetRequired     = boolValue; break;
    case 31: m_AlarmManagementData.NoCycleOverloadAlarmActions.LogAlarm          = boolValue; break;
    case 32: m_AlarmManagementData.NoCycleOverloadAlarmActions.GeneralAlarm      = boolValue; break;
    case 33: m_AlarmManagementData.NoCycleOverloadAlarmActions.CustomAlarmOutput = boolValue; break;
    case 34: m_AlarmManagementData.NoCycleOverloadAlarmActions.CycleCounter      = boolValue; break;

    case 35: m_AlarmManagementData.SuspectAlarmActions.ResetRequired     = boolValue; break;
    case 36: m_AlarmManagementData.SuspectAlarmActions.LogAlarm          = boolValue; break;
    case 37: m_AlarmManagementData.SuspectAlarmActions.GeneralAlarm      = boolValue; break;
    case 38: m_AlarmManagementData.SuspectAlarmActions.CustomAlarmOutput = boolValue; break;
    case 39: m_AlarmManagementData.SuspectAlarmActions.CycleCounter      = boolValue; break;

    default: return false;
    }

    emit dataChanged(index(row), index(row), {ValueRole});

    return true;
}
/**************************************************************************//**
*
* \brief -  Define which properties need to expose to QML under the AalrmMangement
*        -  Model. Generate a link table between Model and list data.
*
* \param -  None
*
* \return - Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> AlarmManConfiguration::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    return roles;
}
/**************************************************************************//**
*
* \brief   - Below function is used to receive the resetToDefault request from HMI
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AlarmManConfiguration::resetToDefault()
{
    isScreenUpdated =true;

     m_AlarmMgrACE->setResetToDefaultAlarmRequest(true);

    m_IsLoadingFlag =true;

    emit loadingDataChanged();

    m_AlarmManagementData =m_AlarmMgrACE->GetAlarmConfiguration();

    emit dataChanged(index(0), index(rowCount() - 1), {ValueRole});
}

/**************************************************************************//**
*
* \brief   - Below function is used to receive the save request from HMI
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AlarmManConfiguration::save()
{
    m_AlarmMgrACE->saveAlarmConfigValues(m_AlarmManagementData);
}
/**************************************************************************//**
*
* \brief   - Below function is used to return noOf rows to HMI for displaying.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/

int AlarmManConfiguration::numberofRows()
{
    return noOfRows;
}

/**************************************************************************//**
*
* \brief   - Below function updates the  loading status.
*
* \param   - IsLoading
*
* \return  - None.
******************************************************************************/
void AlarmManConfiguration::updateIsLoading(const bool &IsLoading)
{
    m_IsLoadingFlag = IsLoading;
    emit loadingDataChanged();
}
/**************************************************************************//**
*
* \brief   - Below function returns the AlarmMangement loading status.
*
* \param   - None.
*
* \return  - m_IsLoadingFlag : The AlarmManagement loading status.
******************************************************************************/
bool AlarmManConfiguration::getIsLoading() const
{
    return m_IsLoadingFlag;
}

/**************************************************************************//**
*
* \brief   - Below function is used to receive the Cancel request from HMI
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void AlarmManConfiguration::cancelReqFromHMI()
{
    m_AlarmManagementData = m_AlarmMgrACE->GetAlarmConfiguration();
    emit dataChanged(index(0), index(rowCount() - 1), {ValueRole});
    isScreenUpdated = false;
    m_IsLoadingFlag = false;
    emit loadingDataChanged();
}
/**************************************************************************//**
*
* \brief   - Role of the slot OnAlarmConfigDetailsUpdated to update the checkboxes.
*
* \param   - AlarmConfigDetailsResult_Obj : Object pointer of type AlarmMgrACE.
*
* \return  - None.
******************************************************************************/
void AlarmManConfiguration::OnAlarmConfigDetailsUpdated(AlarmMgrACE *AlarmMgrACEDetailsResult_Obj, int WelderId)
{
    m_AlarmMgrACE =AlarmMgrACEDetailsResult_Obj;

    if(  m_AlarmMgrACE->IsAlarmConfigurationUpdated() || m_ActiveWelderId != WelderId  || isScreenUpdated )
    {
        m_AlarmManagementData = m_AlarmMgrACE->GetAlarmConfiguration();
        emit dataChanged(index(0), index(rowCount() - 1), {ValueRole});
        m_AlarmMgrACE->ResetAlarmConfigurationUpdatedFlag ();
        m_ActiveWelderId = WelderId;
        isScreenUpdated = false;
        m_IsLoadingFlag = false;
        emit loadingDataChanged();
    }
}

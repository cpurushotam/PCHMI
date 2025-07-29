/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    DataFilterListModel.cpp file provides mode details and status of button and checkboxses.
--------------------------- REVISION HISTORY ------------------------------
***************************************************************************/
#include "DataFilterListModel.h"
#include "languageconfig.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the  variables required under generate report screen data display.
*
*
* \param  - None
*
* \return - None
*
******************************************************************************/
DataFilterListModel::DataFilterListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // Load language list.
    m_LangList = LanguageConfig::getInstance()->getLanguageStringList(UIScreenEnum::GENERATE_REPORT_CONTINUOUS_DATA_FILTER, m_LangList);
    insertData(m_WeldData, false);
    insertData(m_AmplitudeGraph, false);
    insertData(m_FrequencyGraph, false);
    insertData(m_PhaseGraph, false);
    insertData(m_CurrentGraph, false);
    insertData(m_EnergyGraph, false);
    insertData(m_RequestAmplitudeGraph, false);
    insertData(m_VelocityGraph, false);
    insertData(m_ForceGraph, false);
    insertData(m_AbsoluteDistanceGraph, false);
    insertData(m_CollapseDistanceGraph, false);
    insertData(m_PowerGraph, false);

    connect(UpdateScreen::getInstance(), &UpdateScreen::SummaryScreenUpdated, this, &DataFilterListModel::onContinousDataStremmingUpdated);
}
/**************************************************************************//**
*
* \brief   - Below function check the status of data filters parameters the
*            list of mode selcted from the row.
* \param   - bool checkStatus , int index
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onCheckStatusChanged(bool checkStatus,int index)
{
   struct modelData *mPtr = m_dataList.at(index);
    mPtr->checkStatus = checkStatus;
}
/**************************************************************************//**
*
* \brief   - Below function returns the checkd list of all the parameters.
*
* \param   - int index.
*
* \return  - bool - m_dataList.
******************************************************************************/
bool DataFilterListModel::getCheckStatus(int index)
{
    if(index < m_dataList.size())
    {
        return m_dataList.at(index)->checkStatus;
    }
}
/**************************************************************************//**
*
* \brief  - This function inherited from QAbstarctModel used for locate the specific object using the QModelIndex
*           and get the data from get the data from specfic object.
*           Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param  - index and role : To determine the row for designated role.
*
* \return - The property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant DataFilterListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > m_dataList.count())
    {
        return QVariant();
    }
    struct modelData *mPtr = m_dataList.at(index.row());
    switch(role)
    {
    case nameRole:
        return mPtr->Name;
        break;
    case checkStatus:
        return mPtr->checkStatus;
        break;

    }
    return QVariant();


}
/**************************************************************************//**
*
* \brief - This Function we used or invoked from QAbstactModel to find the the row count from the Model.
*
* \param  - QModelIndex object to determine the size.
*
* \return - Returns the count of rows.
*
******************************************************************************/
int DataFilterListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_dataList.count();
}
/**************************************************************************//**
*
* \brief -  This function invoked from QAbstractModel to find out the Parameter name in the Model.
*
* \param -  None
*
* \return - Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> DataFilterListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nameRole]    = "Name";
    return roles;
}
/**************************************************************************//**
*
* \brief   - Below function insert and append the data in m_datalist.
*
* \param   - QString name - parameter name ,bool checkStatus - Chek the status of parameter
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::insertData(QString name, bool checkStatus)
{
    beginInsertRows(QModelIndex(), m_dataList.size(), m_dataList.size());
    m_dataList.append(new modelData{name, checkStatus});
    endInsertRows();
}
/**************************************************************************//**
*
* \brief   - Below slots set the USBStreaming objects.
*
* \param   - *USBStreaming_Obj - USBStreaming Pointer .
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onContinousDataStremmingUpdated(USBStreaming *USBStreaming_Obj)
{
    if(USBStreaming_Obj != NULL)
    {
        m_USBStreaming = USBStreaming_Obj;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the  list of mode selcted from the row.
*
* \param   - None.
*
* \return  - QString - modelist.
******************************************************************************/
QString DataFilterListModel::getDatafiltersList()
{
    QString modelist;
    for(int i=0;i<m_dataList.count();i++)
    {
        if(m_dataList.at(i)->checkStatus)
        {
            modelist.append(m_dataList.at(i)->Name);
            modelist.append("\n");
        }
    }
    modelist.remove(modelist.size() - 1, 1);
    return modelist;
}
/**************************************************************************//**
*
* \brief   - Below function clear the list of filter.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::clearFilterList()
{
    for(int i = 0; i < m_dataList.size(); i++)
    {
        delete m_dataList.at(i);
    }
    m_dataList.clear();
}
/**************************************************************************//**
*
* \brief   - Below function returnning the cycle count value.
*
* \param   - None.
*
* \return  - m_CycleCount - No of cycle count.
******************************************************************************/
QString DataFilterListModel::getCycleCount() const
{
    return m_CycleCount;
}
/**************************************************************************//**
*
* \brief   - Below function updateing the cycle count value.
*
* \param   - iCycleCount - No of cycles.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::updateCycleCount(const QString &iCycleCount)
{
    if(m_CycleCount != iCycleCount)
    {
        m_CycleCount = iCycleCount;
        emit cycleCountUpdated();
    }
}
/**************************************************************************//**
*
* \brief   - Below function returns the  list of mode selcted from the row.
*
* \param   - None.
*
* \return  - QString - modelist.
******************************************************************************/
void DataFilterListModel::createDataFilterList()
{
    ACTUATOR_TYPE sysType = static_cast<ACTUATOR_TYPE>(m_SystemConfiguration->getCurrentSystemType());
    if(m_dataList.isEmpty())
    {
        clearFilterList();
        if (sysType == Manual)
        {
            insertData(m_WeldData, false);
            insertData(m_AmplitudeGraph, false);
            insertData(m_FrequencyGraph, false);
            insertData(m_PhaseGraph, false);
            insertData(m_CurrentGraph, false);
            insertData(m_EnergyGraph, false);
            insertData(m_RequestAmplitudeGraph, false);
            insertData(m_VelocityGraph, false);
            insertData(m_ForceGraph, false);
            insertData(m_AbsoluteDistanceGraph, false);
            insertData(m_CollapseDistanceGraph, false);
            insertData(m_PowerGraph, false);
        }
        else
        {
            insertData(m_WeldData, false);
            insertData(m_AmplitudeGraph, false);
            insertData(m_FrequencyGraph, false);
            insertData(m_PhaseGraph, false);
            insertData(m_CurrentGraph, false);
            insertData(m_EnergyGraph, false);
            insertData(m_RequestAmplitudeGraph, false);
        }
    }
}
/**************************************************************************//**
*
* \brief   - Below function update save on alarm enable or not.
*
* \param   - alarmValue.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onClickOnSaveOnAlarm(bool alarmValue)
{
    if(alarmValue == true)
    {
        m_USBStreamStruct.SaveOnAlarm = true;
    }
    else
    {
        m_USBStreamStruct.SaveOnAlarm = false;
    }
}
/**************************************************************************//**
*
* \brief   - Below function update Cycle count.
*
* \param   - cycleCount.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onCycleCount(QString cycleCount)
{
    m_CycleCount = cycleCount;
    m_USBStreamStruct.WeldCyclesCompleted = m_CycleCount.toInt();
}
/**************************************************************************//**
*
* \brief   - Below function fetch the Cycle count.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
QString DataFilterListModel::getCycleCount()
{
    return m_CycleCount;
}
/**************************************************************************//**
*
* \brief   - Below function get the Storage Option.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
int DataFilterListModel::getStorageOptionValue()
{
    return m_StorageRadioButton;
}

/**************************************************************************//**
*
* \brief   - Below function set the Storage Option.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::setStorageOptionValue(int storageType)
{
    m_StorageRadioButton = storageType;
    if(storageType == usbStorgaeOption)
    {
        m_USBStreamStruct.StreamingStorageOption = USB_STREAM;
    }
    if(storageType == networkAttachedStorage)
    {
        m_USBStreamStruct.StreamingStorageOption = NFS_STREAM;
    }
    if(storageType == plc)
    {
        m_USBStreamStruct.StreamingStorageOption = TCP_IP_STREAM;
    }
}
/**************************************************************************//**
*
* \brief   - Below function update Encryption Data from HMI.
*
* \param   - cycleCount.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onEncryptionData(bool encryptValue)
{
    if(encryptValue == true)
    {
        m_USBStreamStruct.EnableEncryption = true;
    }
    else
    {
        m_USBStreamStruct.EnableEncryption = false;
    }
}
/**************************************************************************//**
*
* \brief   - Below function Update the selcted filter list from HMI.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onSelectionOfDataFilterParameter()
{
    for(int i = 0; i < m_dataList.size(); i++)
    {
        switch(i)
        {
        case 0: m_USBStreamStruct.EnableWeldData = m_dataList.at(i)->checkStatus;
            break;
        case 1: m_USBStreamStruct.UsbAmplitude = m_dataList.at(i)->checkStatus;
            break;
        case 2: m_USBStreamStruct.UsbFrequency = m_dataList.at(i)->checkStatus;
            break;
        case 3: m_USBStreamStruct.UsbPhase = m_dataList.at(i)->checkStatus;
            break;
        case 4: m_USBStreamStruct.UsbCurrent = m_dataList.at(i)->checkStatus;
            break;
        case 5: m_USBStreamStruct.UsbEnergy = m_dataList.at(i)->checkStatus;
            break;
        case 6: m_USBStreamStruct.UsbRequestAmplitude = m_dataList.at(i)->checkStatus;
            break;
        case 7: m_USBStreamStruct.UsbVelocity = m_dataList.at(i)->checkStatus;
            break;
        case 8: m_USBStreamStruct.UsbForce = m_dataList.at(i)->checkStatus;
            break;
        case 9: m_USBStreamStruct.UsbAbsoluteDist = m_dataList.at(i)->checkStatus;
            break;
        case 10: m_USBStreamStruct.UsbColDist = m_dataList.at(i)->checkStatus;
            break;
        case 11: m_USBStreamStruct.UsbPower = m_dataList.at(i)->checkStatus;
            break;

        }
    }
}
/**************************************************************************//**
*
* \brief   - Below function Update the to ASC from HMI.
* \param   - None.
*
* \return  - None.
******************************************************************************/
void DataFilterListModel::onSaveConfigurationClicked()
{
    if(m_USBStreaming != NULL)
    {
        m_USBStreaming->InitiateStreamDataSaveRequest(m_USBStreamStruct);
    }
}


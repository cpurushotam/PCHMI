/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

    UsbAuthDetailsListModel.cpp file handles USB Device details list model container includes :
DEvice info , Vendor code,Used date,serial no. etc
***************************************************************************/
#include "UsbAuthDetailsListModel.h"
#include <iostream>
#include <deque>
/**************************************************************************//**
*
* \brief  - Constructor to clear USB Auth details data list that will save all the USB Device details.
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
UsbAuthDetailsListModel::UsbAuthDetailsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_ListData.clear();
    connect(UpdateScreen::getInstance(), &UpdateScreen::SysConfgUSBAuthDataUpdated, this, &UsbAuthDetailsListModel::OnUSBDetailsListUpdated);
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
UsbAuthDetailsListModel::~UsbAuthDetailsListModel()
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
int UsbAuthDetailsListModel::rowCount(const QModelIndex &parent) const
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
QVariant UsbAuthDetailsListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_ListData.count())
        return QVariant();
    const UsbAuthDetailsListData *ptrListObj = m_ListData[index.row()];

    switch (role)
    {

    case USBIndexNumRole:
        return ptrListObj->getUsbIndexNumber();
        break;
    case USBEnableRole:
        return ptrListObj->isDeregistrationEnabled();
        break;

    case DeviceNameRole:
        return ptrListObj->getDeviceName();
        break;

    case VendorCodeRole:
        return ptrListObj->getVendorCode();
        break;

    case ProductCodeRole:
        return ptrListObj->getProductCode();
        break;

    case SerialNumberRole:
        return ptrListObj->getSerialCode();
        break;

    case UsedDateRole:
        return ptrListObj->getUsedDate();
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
* \param  - index.row should be in the range of the User list.
*
* \return - If the row is in the range of the User list list,
*         - the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex UsbAuthDetailsListModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    UsbAuthDetailsListData *ptrListObj = nullptr;
    if(index.isValid() == false)
        ptrListObj = m_ListData.at(0);
    else
        ptrListObj = static_cast<UsbAuthDetailsListData*>(index.internalPointer());

    if (ptrListObj)
        return createIndex(row, column, ptrListObj);
    else
        return QModelIndex();
}


/**************************************************************************//**
*
* \brief - To clear the UsbAuthDetailsListData list.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
void UsbAuthDetailsListModel::clearUSBDetailsList()
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
* \param  - UsbAuthDetailsList : List data of type UsbAuthDetailsListData.
*
* \return - None.
*
******************************************************************************/
void UsbAuthDetailsListModel::addNewUSBDetailsList(UsbAuthDetailsListData *UsbAuthDetailsList)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListData.append(UsbAuthDetailsList);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief   - loadUSBDevDetailsList function called by qml while loading of
*            USB detail list, to display available USB details list.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UsbAuthDetailsListModel::loadUSBDevDetailsList()
{
    createNewUSBDetailsList();
    clearUSBDetailsList();

    UsbAuthDetailsListData* ptrListObj = nullptr;

    for (unsigned int Index = 0; Index < m_UsbDeviceDescriptionData.size(); Index++)
    {
        ptrListObj = new UsbAuthDetailsListData(m_UsbDeviceDescriptionData[Index].EnableDeregistration, m_UsbDeviceDescriptionData[Index].UsbIndexNumber,m_UsbDeviceDescriptionData[Index].VendorCode,m_UsbDeviceDescriptionData[Index].ProductCode,
                                                m_UsbDeviceDescriptionData[Index].SerialCode,m_UsbDeviceDescriptionData[Index].DeviceName,m_UsbDeviceDescriptionData[Index].UsedDate);
        addNewUSBDetailsList(ptrListObj);
    }
}

/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type UsbAuthDetailsListData.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UsbAuthDetailsListModel::createNewUSBDetailsList()
{
    UsbAuthDetailsListData* ptrListObj = new UsbAuthDetailsListData();
    addNewUSBDetailsList(ptrListObj);
}


/**************************************************************************//**
*
* \brief   - Below function creates object pointer of type UsbAuthDetailsListModel.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/

void UsbAuthDetailsListModel::deRegisterTheSelectedUSBDevice(bool status, int usbDevInDEX)
{
    for (auto& usbDevice : m_UsbDeviceDescriptionData)
    {
        if (usbDevice.UsbIndexNumber == usbDevInDEX)
        {
            usbDevice.EnableDeregistration = status;
            break;
        }
    }
}

/**************************************************************************//**
*
* \brief   - Below function is used to Intiate Deregistration process for selcted USB devices.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UsbAuthDetailsListModel::deRegisterButtonClicked()
{
    m_USBAuthentication->InitiateUsbDeviceDeregistrationRequest(m_UsbDeviceDescriptionData);
}
/**************************************************************************//**
*
* \brief   - Below function is used to Register the unregistered device from HMI.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/

void UsbAuthDetailsListModel::usbDeviceRegisterButtonClicked()
{
    m_USBAuthentication->InitiateUsbDeviceRegistrationRequest();
}
/**************************************************************************//**
*
* \brief -  Define which properties need to expose to QML under the User details list
*        -  Model. To generate a link table between Model and list data.
*
* \param -  None
*
* \return - Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> UsbAuthDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[USBDevAuthRoles::USBIndexNumRole]     = "UsbIndex";
    roles[USBDevAuthRoles::USBEnableRole]       = "UsbDeregister";
    roles[USBDevAuthRoles::DeviceNameRole]      = "DeviceName";
    roles[USBDevAuthRoles::VendorCodeRole]      = "VendorCode";
    roles[USBDevAuthRoles::ProductCodeRole]     = "ProductCode";
    roles[USBDevAuthRoles::SerialNumberRole]    = "SerialNUmber";
    roles[USBDevAuthRoles::UsedDateRole]        = "UsedDate";
    return roles;
}

/**************************************************************************//**
*
* \brief   - Role of the slot OnUSBDetailsListUpdated to update the usb details list data.
*
* \param   - USBAuthentication_Obj : The USBAuthentication object.
*            WelderId : The active welder Id.
*
* \return  - None.
******************************************************************************/
void UsbAuthDetailsListModel::OnUSBDetailsListUpdated(USBAuthentication *USBAuthentication_Obj, int WelderId)
{
    m_USBAuthentication = USBAuthentication_Obj;
    if(m_USBAuthentication->GetIsUSBDevDescriptionDetailsUpdated() || m_ActiveWelderId != WelderId)
    {
        m_UsbDeviceDescriptionData = m_USBAuthentication->GetUSBDeviceDescriptionList();
        loadUSBDevDetailsList();
        m_USBAuthentication->SetIsUSBDeviceDescriptionDetailsUpdatedFlag();
        m_ActiveWelderId = WelderId;
    }
}


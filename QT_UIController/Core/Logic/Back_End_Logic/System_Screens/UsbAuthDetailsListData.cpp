
/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UsbAuthDetailsListData.h file provides USB device detail list container data
    handled by UsbAuthDetailsListDataModel.
***************************************************************************/
#include "UsbAuthDetailsListData.h"
/**************************************************************************//**
*
* \brief  - Constructor to initialize the variables.
*
* \param  - None
*
* \return - None
*
******************************************************************************/
UsbAuthDetailsListData::UsbAuthDetailsListData()
{

}

UsbAuthDetailsListData::UsbAuthDetailsListData(bool enableDeregistration,
                                               int usbIndexNumber, const QString& vendorCode,
                                               const QString& productCode, const QString& serialCode,
                                               const QString& deviceName, const QString& usedDate)
    :m_EnableDeregistration(enableDeregistration),
     m_UsbIndexNumber(usbIndexNumber),
     m_VendorCode(vendorCode),
     m_ProductCode(productCode),
     m_SerialCode(serialCode),
     m_DeviceName(deviceName),
     m_UsedDate(usedDate)
    {
    }

/**************************************************************************//**
*
* \brief  - Returns whether deregistration is enabled.
*
*           This function indicates if the user is allowed to be deregistered.
*
* \param  - None.
*
* \return - bool
*           True if deregistration is enabled, false otherwise.
*
******************************************************************************/
bool UsbAuthDetailsListData::isDeregistrationEnabled() const
{
    return m_EnableDeregistration;
}

/**************************************************************************//**
*
* \brief  - Returns the USB index number.
*
*           This function retrieves the index number assigned to the USB device.
*
* \param  - None.
*
* \return - int
*           The USB index number.
*
******************************************************************************/
int UsbAuthDetailsListData::getUsbIndexNumber() const
{
    return m_UsbIndexNumber;
}

/**************************************************************************//**
*
* \brief  - Returns the USB vendor code.
*
*           This function retrieves the vendor code of the connected USB device.
*
* \param  - None.
*
* \return - QString
*           The vendor code string.
*
******************************************************************************/
QString UsbAuthDetailsListData::getVendorCode() const
{
    return m_VendorCode;
}

/**************************************************************************//**
*
* \brief  - Returns the USB product code.
*
*           This function retrieves the product code of the connected USB device.
*
* \param  - None.
*
* \return - QString
*           The product code string.
*
******************************************************************************/
QString UsbAuthDetailsListData::getProductCode() const
{
    return m_ProductCode;
}

/**************************************************************************//**
*
* \brief  - Returns the USB serial code.
*
*           This function retrieves the serial number of the connected USB device.
*
* \param  - None.
*
* \return - QString
*           The serial code string.
*
******************************************************************************/
QString UsbAuthDetailsListData::getSerialCode() const
{
    return m_SerialCode;
}

/**************************************************************************//**
*
* \brief  - Returns the USB device name.
*
*           This function retrieves the name of the connected USB device.
*
* \param  - None.
*
* \return - QString
*           The device name string.
*
******************************************************************************/
QString UsbAuthDetailsListData::getDeviceName() const
{
    return m_DeviceName;
}

/**************************************************************************//**
*
* \brief  - Returns the last used date of the USB.
*
*           This function retrieves the date when the USB device was last used.
*
* \param  - None.
*
* \return - QString
*           The last used date string.
*
******************************************************************************/
QString UsbAuthDetailsListData::getUsedDate() const
{
    return m_UsedDate;
}



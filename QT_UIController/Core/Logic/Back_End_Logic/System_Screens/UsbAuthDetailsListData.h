/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UsbAuthDetailsListData.h file provides USB detail list container data
    handeled by UsbAuthDetailsListModel.
***************************************************************************/
#ifndef USBAUTHDETAILSLISTDATA_H
#define USBAUTHDETAILSLISTDATA_H

#include <QString>
class UsbAuthDetailsListData
{
public:
   UsbAuthDetailsListData();
    UsbAuthDetailsListData( bool enableDeregistration, int usbIndexNumber, const QString& vendorCode,
                           const QString& productCode, const QString& serialCode, const QString& deviceName,
                           const QString& usedDate);

private:

    bool m_EnableDeregistration;
    int m_UsbIndexNumber;
    QString m_VendorCode;
    QString m_ProductCode;
    QString m_SerialCode;
    QString m_DeviceName;
    QString m_UsedDate;

public:

    bool isDeregistrationEnabled() const;
    int getUsbIndexNumber() const;
    QString getVendorCode() const;
    QString getProductCode() const;
    QString getSerialCode() const;
    QString getDeviceName() const;
    QString getUsedDate() const;

};

#endif // USBAUTHDETAILSLISTDATA_H

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanCycleDetailsListData.h file provides cycle detail list container data
    handeled by CycleDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 03/04/2024 - Initial version.
***************************************************************************/
#ifndef SCANCYCLEDETAILSLISTDATA_H
#define SCANCYCLEDETAILSLISTDATA_H

#include <QString>

class ScanCycleDetailsListData
{
public:
    ScanCycleDetailsListData();
    ScanCycleDetailsListData(const int& p_CycleIndex, const QString & p_CycleDateTime);

private:

    int m_CycleIndex;
    QString m_CycleDateTime;
    
public:

    int getCycleIndex() const;
    QString getCycleDateTime() const;

};

#endif // SCANCYCLEDETAILSLISTDATA_H

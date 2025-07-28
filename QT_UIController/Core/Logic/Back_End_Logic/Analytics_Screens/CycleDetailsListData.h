/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailsListData.h file provides cycle detail list container data
    handeled by CycleDetailsListModel.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 12/10/2023 - Initial version.
***************************************************************************/
#ifndef CYCLEDETAILSLISTDATA_H
#define CYCLEDETAILSLISTDATA_H

#include <QString>

class CycleDetailsListData
{
public:
    CycleDetailsListData();
    CycleDetailsListData(const int& p_CycleIndex, const int& p_RecipeNo, const int& p_CycleNo, const int& p_RecipeMode, const QString & p_CycleDateTime,
                         const float& p_TriggerPoint, const float& p_WeldSonicPoint, const float& p_HoldPoint, const int& p_WeldResultIndex);

private:

    int m_CycleIndex;
    int m_RecipeNo;
    int m_CycleNo;
    int m_RecipeMode;
    int m_WeldResultIdx;
    QString m_CycleDateTime;
    float m_TriggerPoint;
    float m_WeldSonicPoint;
    float m_HoldPoint;

public:

    int getCycleIndex() const;
    int getRecipeNo() const;
    int getCycleNo() const;
    int getRecipeMode() const;
    int getWeldResultIndex() const;
    QString getCycleDateTime() const;
    float getTriggerPoint() const;
    float getWeldSonicPoint() const;
    float getHoldPoint() const;
};

#endif // CYCLEDETAILSLISTDATA_H

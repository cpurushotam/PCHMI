/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps maintains general recipe information.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/07/2023 - Initial version.
***************************************************************************/

#ifndef RECIPEGENERAL_H
#define RECIPEGENERAL_H

#include <QString>
#include "recipedef.h"

class RecipeGeneral
{
public:
    RecipeGeneral();
    RecipeGeneral(const int& iRecipeNum, const QString& strRecipeName, const int& iWeldMode,
                         const int iWeldModeUnit, float iWeldModeValue,
                         const bool& bActiveStatus, const bool& bValidateStatus,
                         const bool& bModifiedStatus, const bool& bNewCardStatus,
                         const int& iCycleCount, const int&iRecipeVersionInfo,
                         const int&bRecipeSaveStatus);

private:
    int m_iRecipeNumber;
    QString m_strRecipeName;
    int m_iWeldMode;
    int m_iModeUnit;
    float m_iWeldModeValue;
    bool m_bActiveStatus;
    bool m_bValidateStatus;
    bool m_bModifiedStatus;
    bool m_bNewCardStatus;
    int m_iCycleCount;
    int m_iRecipeVersionInfo;
    bool m_bRecipeSaveStatus;

public:
    int getRecipeNumber() const;
    QString getRecipeName() const;
    int getWeldModeEnum() const;
    int getWeldModeUnit() const;
    float getWeldModeValue() const;
    bool getRecipeActiveStatus() const;
    void setRecipeActiveStatus(const int activeflag);
    bool getRecipeValidateStatus() const;
    bool getRecipeModifiedStatus() const;
    bool getRecipeNewCardStatus() const;
    int getRecipeWeldCycleCount() const;
    void setRecipeWeldCycleCount(const int cycleNumber);
    int getRecipeVersionInfo() const;
    bool getRecipeSaveStatus() const;
};

#endif // RECIPEGENERAL_H

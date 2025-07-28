/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes production screen qml variables declarations.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/05/2023 - Initial version.
***************************************************************************/

#ifndef PRODUCTIONRUN_H
#define PRODUCTIONRUN_H

#include <QObject>
#include "ProductionScreen_MB.h"
#include "UpdateScreens.h"
#include "UnitConversionLogic.h"

/*Below macro is used to convert percentage of cycle OK,
suspect and Reject count accourding to circle's percentage*/
#define CIRCLE_PERC_FACTOR 3.6


/*Below macro is used to convert percentage of cycle OK,
suspect and Reject count accourding to circle's percentage*/
#define HALF_CIRCLE 180.0

/*Below enums used for framecount update purpose, should get remove in final version.*/
/*Welder ID enums*/
enum WELDER_NAMES{
    WELDER1 = 0,
    WELDER2,
    WELDER3
};

class ProductionRun : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT
    Q_PROPERTY(int ActiveRecipeNum READ getActiveRecipeNum WRITE updateActiveRecipeNum NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(QString ActiveRecipeName READ getActiveRecipeName WRITE updateActiveRecipeName NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(int RecipeWeldMode READ getRecipeWeldMode WRITE updateRecipeWeldMode NOTIFY OnProductionScreenDataChanged )
    Q_PROPERTY(QString RecipeWeldModeUnit READ getRecipeWeldModeUnit WRITE updateRecipeWeldModeUnit NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(QString RecipeWeldModeValue READ getRecipeWeldModeValue WRITE updateRecipeWeldModeValue NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(QString TotalCycleTime READ getTotalCycleTime WRITE updateTotalCycleTime NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(QString CycleCount READ getCycleCount  WRITE updateCycleCount NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(float PeakPowerRatio READ getPeakPowerRatio WRITE updatePeakPowerRatio NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(float PeakPower READ getPeakPower WRITE updatePeakPower NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(int WelderFrameCounter READ getWelderFrameCounter WRITE updateWelderFrameCounter NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(int WelderFrameCounter2 READ getWelderFrameCounter2 WRITE updateWelderFrameCounter2 NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(int WelderFrameCounter3 READ getWelderFrameCounter3 WRITE updateWelderFrameCounter3 NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(double CyclesOkCount READ getCyclesOkCountNum WRITE updateCyclesOkCountNum NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(int BatchCount READ getBatchCountNum WRITE updateBatchCountNum NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(int PartsPerMin READ getPartsPerMinNum WRITE updatePartsPerMinNum NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(double RejectedCycles READ getRejectedCyclesNum WRITE updateRejectedCyclesNum NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(double SuspectedCycles READ getSuspectedCyclesNum WRITE updateSuspectedCyclesNum NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(double CyclesOkEndAngle READ getCyclesOkEndAngle NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(double SuspectedCyclesEndAngle READ getSuspectedCyclesEndAngle NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(double YieldPercentage READ getYieldPercentage NOTIFY OnProductionScreenDataChanged)

    Q_PROPERTY(QString PartId READ getPartId NOTIFY OnProductionScreenDataChanged)
    Q_PROPERTY(bool IsPartIdEnable READ getIsPartIdEnable NOTIFY OnProductionScreenDataChanged)


private:

    /*List of private varibles used by methods under ProductionRun class*/
    int     m_iActiveRecipeNum;
    QString m_strActiveRecipeName;
    int     m_iRecipeWeldMode;
    QString m_strRecipeWeldModeUnit;
    QString m_strRecipeWeldModeValue;
    QString m_strTotalCycleTime;
    QString m_strCycleCount;
    float   m_realPeakPowerRatio;
    float   m_realPeakPower;
    int     m_WelderFrameCounter  = 0;
    int     m_WelderFrameCounter2 = 0;
    int     m_WelderFrameCounter3 = 0;
    double  m_CyclesOKCount = 0;
    int     m_BatchCount = 0;
    int     m_PartsPerMin = 0;
    double  m_RejectedCycles = 0;
    double  m_SuspectedCycles = 0;
    double  m_CyclesOKEndAngle = 0;
    double  m_SuspectedCyclesEndAngle = 0;
    int     m_YieldPercentage = 0;
    QString m_PartId;
    bool m_IsPartIdEnable;

    SystemConfigurationGeneral_MB *systemConfigPtr;

public:

    explicit ProductionRun(QObject *parent = nullptr);

    /*List of get and set functions to update qml variables*/
    int getActiveRecipeNum() const;
    void updateActiveRecipeNum(const int& iRecipeNum);

    QString getActiveRecipeName() const;
    void updateActiveRecipeName(const QString& strRecipeName);

    int getRecipeWeldMode() const;
    void updateRecipeWeldMode(const int& weldMode);

    QString getRecipeWeldModeUnit() const;
    void updateRecipeWeldModeUnit(const QString& weldModeUnit);

    QString getRecipeWeldModeValue() const;
    void updateRecipeWeldModeValue(const QString& weldModeValue);

    QString getTotalCycleTime() const;
    void updateTotalCycleTime(const QString& totalCycleTime);

    QString getCycleCount() const;
    void updateCycleCount(const QString& cycleCount);

    float getPeakPowerRatio() const;
    void updatePeakPowerRatio(const float& peakPowerRatio);

    float getPeakPower() const;
    void updatePeakPower(const float& peakPowerRatio);

    int getWelderFrameCounter() const;
    void updateWelderFrameCounter(const int& welderFrameCounter);

    int getWelderFrameCounter2() const;
    void updateWelderFrameCounter2(const int& welderFrameCounter2);

    int getWelderFrameCounter3() const;
    void updateWelderFrameCounter3(const int& welderFrameCounter3);

    int getBatchCountNum() const;
    void updateBatchCountNum(const int& iBatchCount);

    double getCyclesOkCountNum() const;
    void updateCyclesOkCountNum(const int& iCyclesOK);

    int getPartsPerMinNum() const;
    void updatePartsPerMinNum(const int& iPartsPerMin);

    double getRejectedCyclesNum() const;
    void updateRejectedCyclesNum(const int& iRejectedCycles);

    double getSuspectedCyclesNum() const;
    void updateSuspectedCyclesNum(const int& iSuspectedCycles);

    double getCyclesOkEndAngle();
    double getSuspectedCyclesEndAngle();
    double getYieldPercentage();
    QString getPartId() const;
    bool getIsPartIdEnable() const;

    void setUnit(int Idx);
    /*Signals used to notify qml screen*/

signals:
    void OnProductionScreenDataChanged();

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnScreenUpdated(ProdScreenData *Obj , SystemConfigurationGeneral_MB *SysConfgGenData_Obj);

};

#endif // PRODUCTIONRUN_H

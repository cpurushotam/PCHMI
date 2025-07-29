/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file updates the production screen qml variables.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 22/05/2023 - Initial version.
 rev2: 16/08/2023 - Get Active welder from front end.
***************************************************************************/

#include "ProductionRunInterface.h"
#include "recipedef.h"
#include "MultiwelderInterface.h"
#include "PowerLevelSysFrequencySupport.h"
#include <math.h>
/**************************************************************************//**
*
* \brief Constructor and initialize all the parameters that will show upon the screen.
*
* \param QObject* parent
*
* \return None
*
******************************************************************************/
ProductionRun::ProductionRun(QObject *parent) : QObject(parent)
    , m_iActiveRecipeNum(-1)
    , m_strActiveRecipeName("N/A")
    , m_iRecipeWeldMode(0)
    , m_strRecipeWeldModeUnit("N/A")
    , m_strRecipeWeldModeValue("N/A")
    , m_strTotalCycleTime("00.000")
    , m_strCycleCount("N/A")
    , m_realPeakPowerRatio(0.00)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::ProductionScreenUpdated, this, &ProductionRun::OnScreenUpdated);
}

/**************************************************************************//**
*
* \brief To get the active recipe number
*
* \param none
*
* \return m_iActiveRecipeNum
*
******************************************************************************/
int ProductionRun::getActiveRecipeNum() const
{
    return m_iActiveRecipeNum;
}

/**************************************************************************//**
*
* \brief To update current active recipe number.
* If the new coming recipe number is not equal to the current active recipe,
* the active recipe number need to be updated and need to recall the detailed information under the recipe.
*
* \param iRecipeNum
*
* \return none
*
******************************************************************************/
void ProductionRun::updateActiveRecipeNum(const int &iRecipeNum)
{
    if(iRecipeNum != m_iActiveRecipeNum)
    {
        m_iActiveRecipeNum = iRecipeNum;
    }
}

/**************************************************************************//**
*
* \brief To get Active Recipe Name for the external recall
*
* \param none.
*
* \return actived recipe name
*
******************************************************************************/
QString ProductionRun::getActiveRecipeName() const
{
    return m_strActiveRecipeName;
}

/**************************************************************************//**
*
* \brief To set Active Recipe Name for the external setting.
*        If the variable strRecipeName is not equal to m_strActiveRecipeName?
*        m_strActiveRecipeName value will be replaced with strRecipeName.
*
* \param QString strRecipeName
*
* \return none
*
******************************************************************************/
void ProductionRun::updateActiveRecipeName(const QString &strRecipeName)
{
    if(m_strActiveRecipeName != strRecipeName)
    {
        m_strActiveRecipeName = strRecipeName;
    }
}

/**************************************************************************//**
*
* \brief To get the weld mode enum index.
*
* \param none.
*
* \return weld mode enum index.
*
******************************************************************************/
int ProductionRun::getRecipeWeldMode() const
{
    return m_iRecipeWeldMode;
}

/**************************************************************************//**
*
* \brief To set recipe weld mode for the external setting.
*        If the variable weldMode is not equal to m_iRecipeWeldMode?
*        m_iRecipeWeldMode value will be replaced with weldMode.
*
* \param QString weldMode
*
* \return none
*
******************************************************************************/
void ProductionRun::updateRecipeWeldMode(const int &weldMode)
{
    if(m_iRecipeWeldMode != weldMode)
    {
        m_iRecipeWeldMode = weldMode;
    }
}

/**************************************************************************//**
*
* \brief To get unit string that related to the specific weld mode.
*
* \param none
*
* \return QString
*
******************************************************************************/
QString ProductionRun::getRecipeWeldModeUnit() const
{
    return m_strRecipeWeldModeUnit;
}

/**************************************************************************//**
*
* \brief To set value unit for the external setting.
*        If the variable weldModeUnit is not equal to m_strRecipeWeldModeUnit?
*        m_strRecipeWeldModeUnit value will be replaced with weldModeUnit.
*
* \param QString weldModeUnit
*
* \return none
*
******************************************************************************/
void ProductionRun::updateRecipeWeldModeUnit(const QString &weldModeUnit)
{
    if(m_strRecipeWeldModeUnit != weldModeUnit)
    {
        m_strRecipeWeldModeUnit = weldModeUnit;
    }
}

/**************************************************************************//**
*
* \brief To get value string that related to the specific weld mode.
*
* \param none
*
* \return QString
*
******************************************************************************/
QString ProductionRun::getRecipeWeldModeValue() const
{
    return m_strRecipeWeldModeValue;
}

/**************************************************************************//**
*
* \brief To set recipe value for the external setting.
*        If the variable weldModeValue is not equal to m_strRecipeWeldModeValue?
*        m_strRecipeWeldModeValue value will be replaced with weldModeValue.
*
* \param QString weldModeValue
*
* \return none
*
******************************************************************************/
void ProductionRun::updateRecipeWeldModeValue(const QString &weldModeValue)
{
    if(m_strRecipeWeldModeValue != weldModeValue)
    {
        m_strRecipeWeldModeValue = weldModeValue;
    }
}

/**************************************************************************//**
*
* \brief To get the Total Cycle Time for the any external recall
*
* \param None
*
* \return QString m_strTotalCycleTime
*
******************************************************************************/
QString ProductionRun::getTotalCycleTime() const
{
    QString retVal;
    return retVal.setNum(m_strTotalCycleTime.toFloat(), 'f', 3);
}

/**************************************************************************//**
*
* \brief To set value total cycle time for the external setting.
*        If the variable totalCycleTime is not equal to m_strTotalCycleTime?
*        m_strTotalCycleTime value will be replaced with totalCycleTime.
*
* \param QString totalCycleTime
*
* \return none
*
******************************************************************************/
void ProductionRun::updateTotalCycleTime(const QString &totalCycleTime)
{
    if(m_strTotalCycleTime != totalCycleTime)
    {
        m_strTotalCycleTime = totalCycleTime;
    }
}

/**************************************************************************//**
*
* \brief To get Cycle Count for the external recall
*
* \param none
*
* \return QString m_strCycleCount
*
******************************************************************************/
QString ProductionRun::getCycleCount() const
{
    return m_strCycleCount;
}

/**************************************************************************//**
*
* \brief To set cycle count for the external setting.
*        If the variable totalCycleTime is not equal to m_strTotalCycleTime?
*        m_strTotalCycleTime value will be replaced with totalCycleTime.
*
* \param QString cycleCount
*
* \return none
*
******************************************************************************/
void ProductionRun::updateCycleCount(const QString &cycleCount)
{
    if(m_strCycleCount != cycleCount)
    {
        m_strCycleCount = cycleCount;
    }
}

/**************************************************************************//**
*
* \brief To get the Peak Power Ratio for the external recall
*
* \param none
*
* \return float m_realPeakPowerRatio
*
******************************************************************************/
float ProductionRun::getPeakPowerRatio() const
{
    return m_realPeakPowerRatio;
}

/**************************************************************************//**
*
* \brief To set peak power ratio for the external setting.
*        If the variable peakPowerRatio is not equal to m_realPeakPowerRatio?
*        m_realPeakPowerRatio value will be replaced with peakPowerRatio.
*
* \param QString peakPowerRatio
*
* \return none
*
******************************************************************************/
void ProductionRun::updatePeakPowerRatio(const float &peakPowerRatio)
{
    if(m_realPeakPowerRatio != peakPowerRatio)
    {
        m_realPeakPowerRatio = peakPowerRatio;
    }
}

/**************************************************************************//**
*
* \brief To get the Peak Power for the external recall
*
* \param none
*
* \return float m_realPeakPower
*
******************************************************************************/
float ProductionRun::getPeakPower() const
{
    return m_realPeakPower;
}

/**************************************************************************//**
*
* \brief To set peak power for the external setting.
*        If the variable peakPower is not equal to m_realPeakPower?
*        m_realPeakPower value will be replaced with peakPower.
*
* \param QString peakPowerRatio
*
* \return none
*
******************************************************************************/
void ProductionRun::updatePeakPower(const float &peakPower)
{
    if(m_realPeakPower != peakPower)
    {
        m_realPeakPower = peakPower;
    }
}

/**************************************************************************//**
*
* \brief  - To get the welder fram count value.
*
* \param  - None.
*
* \return - m_WelderFrameCounter : Welder1 frame counter.
*
******************************************************************************/
int ProductionRun::getWelderFrameCounter() const
{
    return m_WelderFrameCounter;
}

/**************************************************************************//**
*
* \brief  - To set welder frame count.
          - If the variable welderFrameCounter is not equal to m_WelderFrameCounter
            m_WelderFrameCounter value will be replaced with welderFrameCounter.
*
* \param  - welderFrameCounter : Welder1 frame counter.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateWelderFrameCounter(const int &welderFrameCounter)
{
    if(m_WelderFrameCounter != welderFrameCounter)
    {
        m_WelderFrameCounter = welderFrameCounter;
    }
}

/**************************************************************************//**
*
* \brief  - To get the welder fram count value.
*
* \param  - None.
*
* \return - m_WelderFrameCounter2 : Welder2 frame counter.
*
******************************************************************************/
int ProductionRun::getWelderFrameCounter2() const
{
    return m_WelderFrameCounter2;
}

/**************************************************************************//**
*
* \brief  - To set welder frame count.
          - If the variable welderFrameCounter is not equal to m_WelderFrameCounter
            m_WelderFrameCounter value will be replaced with welderFrameCounter.
*
* \param  - welderFrameCounter : Welder2 frame counter.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateWelderFrameCounter2(const int &welderFrameCounter2)
{
    if(m_WelderFrameCounter2 != welderFrameCounter2)
    {
        m_WelderFrameCounter2 = welderFrameCounter2;
    }
}

/**************************************************************************//**
*
* \brief  - To get the welder fram count value.
*
* \param  - None.
*
* \return - m_WelderFrameCounter3 : Welder3 frame counter.
*
******************************************************************************/
int ProductionRun::getWelderFrameCounter3() const
{
    return m_WelderFrameCounter3;
}

/**************************************************************************//**
*
* \brief  - To set welder frame count.
          - If the variable welderFrameCounter is not equal to m_WelderFrameCounter
            m_WelderFrameCounter value will be replaced with welderFrameCounter.
*
* \param  - welderFrameCounter : Welder3 frame counter.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateWelderFrameCounter3(const int &welderFrameCounter3)
{
    if(m_WelderFrameCounter3 != welderFrameCounter3)
    {
        m_WelderFrameCounter3 = welderFrameCounter3;
    }
}

/**************************************************************************//**
*
* \brief  - To get the Batch count value.
*
* \param  - None.
*
* \return - m_BatchCount : batch count value.
*
******************************************************************************/
int ProductionRun::getBatchCountNum() const
{
    return m_BatchCount;
}


/**************************************************************************//**
*
* \brief  - To set batch count value.
          - If the variable iBatchCount is not equal to m_BatchCount
            m_BatchCount value will be replaced with iBatchCount.
*
* \param  - iBatchCount : batch count value.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateBatchCountNum(const int &iBatchCount)
{
    if(m_BatchCount != iBatchCount)
    {
        m_BatchCount = iBatchCount;
        emit OnProductionScreenDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - To get the Cycles OK count value.
*
* \param  - None.
*
* \return -  : m_CyclesOKCount :cycles OK count value.
*
******************************************************************************/
double ProductionRun::getCyclesOkCountNum() const
{
    return m_CyclesOKCount;
}

/**************************************************************************//**
*
* \brief  - To set cycles ok count value.
          - If the variable iCyclesOK is not equal to m_CyclesOKCount
            m_CyclesOKCount value will be replaced with iCyclesOK.
*
* \param  - iCyclesOK : cycles OK count value.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateCyclesOkCountNum(const int &iCyclesOK)
{
    if(m_CyclesOKCount != iCyclesOK)
    {
        m_CyclesOKCount = iCyclesOK;
        emit OnProductionScreenDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - To get the Parts Per Min value.
*
* \param  - None.
*
* \return - m_PartsPerMin : Parts Per Min value.
*
******************************************************************************/
int ProductionRun::getPartsPerMinNum() const
{
    return m_PartsPerMin;
}


/**************************************************************************//**
*
* \brief  - To set parts per min value.
          - If the variable iPartsPerMin is not equal to m_CyclesCount
            m_CyclesCount value will be replaced with iBatchCount.
*
* \param  - iBatchCount : batch count value.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updatePartsPerMinNum(const int &iPartsPerMin)
{
    if(m_PartsPerMin != iPartsPerMin)
    {
        m_PartsPerMin = iPartsPerMin;
        emit OnProductionScreenDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - To get the Rejected Cycles value.
*
* \param  - None.
*
* \return - m_RejectedCycles : Rejected Cycles value.
*
******************************************************************************/
double ProductionRun::getRejectedCyclesNum() const
{
    return m_RejectedCycles;
}


/**************************************************************************//**
*
* \brief  - To set Rejected Cycles value.
          - If the variable iRejectedCycles is not equal to m_RejectedCycles
            m_RejectedCycles value will be replaced with iRejectedCycles.
*
* \param  - iRejectedCycles :  Rejected Cycles value.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateRejectedCyclesNum(const int &iRejectedCycles)
{
    if(m_RejectedCycles != iRejectedCycles)
    {
        m_RejectedCycles = iRejectedCycles;
        emit OnProductionScreenDataChanged();
    }
}

/**************************************************************************//**
*
* \brief  - To get the Suspected Cycles value.
*
* \param  - None.
*
* \return - m_SuspectedCycles : Suspected Cycles value.
*
******************************************************************************/
double ProductionRun::getSuspectedCyclesNum() const
{
    return m_SuspectedCycles;
}


/**************************************************************************//**
*
* \brief  - To set Suspected Cycles value.
          - If the variable iSuspectedCycles is not equal to m_SuspectedCycles
            m_SuspectedCycles value will be replaced with iSuspectedCycles.
*
* \param  - iSuspectedCycles :  Suspected Cycles value.
*
* \return - None.
*
******************************************************************************/
void ProductionRun::updateSuspectedCyclesNum(const int &iSuspectedCycles)
{
    if(m_SuspectedCycles != iSuspectedCycles)
    {
        m_SuspectedCycles = iSuspectedCycles;
        emit OnProductionScreenDataChanged();
    }
}


/**************************************************************************//**
*
* \brief  - To get cycles Ok end angle value.
          - This function is used in qml to get cycles ok end angle to show circular progress bar
*
* \param  - None.
*
* \return - m_CyclesOKEndAngle cycles Ok end angle.
*
******************************************************************************/
double ProductionRun::getCyclesOkEndAngle()
{
    if((m_CyclesOKCount + m_RejectedCycles + m_SuspectedCycles) != 0)
    {
        double percentage = (m_CyclesOKCount / (m_CyclesOKCount + m_RejectedCycles + m_SuspectedCycles)) * 100;
        double angleInDegree = percentage * CIRCLE_PERC_FACTOR;
        m_CyclesOKEndAngle = angleInDegree * (M_PI/HALF_CIRCLE);
    }
    return m_CyclesOKEndAngle;
}

/**************************************************************************//**
*
* \brief  - To get cycles suspected end angle value.
          - This function is used in qml to get cycles suspected end angle to show circular progress bar
*
* \param  - None.
*
* \return - m_SuspectedCyclesEndAngle cycles suspected end angle.
*
******************************************************************************/
double ProductionRun::getSuspectedCyclesEndAngle()
{
    if((m_CyclesOKCount + m_RejectedCycles + m_SuspectedCycles) != 0)
    {
        double percentage = (m_SuspectedCycles / (m_CyclesOKCount + m_RejectedCycles + m_SuspectedCycles)) * 100;
        double angleInDegree = percentage * CIRCLE_PERC_FACTOR;
        double angleInRadians = angleInDegree * (M_PI/HALF_CIRCLE);
        m_SuspectedCyclesEndAngle = angleInRadians + m_CyclesOKEndAngle;
    }
    return m_SuspectedCyclesEndAngle;
}

/**************************************************************************//**
*
* \brief  - To get yield percentage value.
          - This function is used in qml to show yeild percentage
*
* \param  - None.
*
* \return - m_YieldPercentage : yeild percentage value
*
******************************************************************************/
double ProductionRun::getYieldPercentage()
{
    if((m_CyclesOKCount + m_RejectedCycles + m_SuspectedCycles) != 0)
    {
        m_YieldPercentage = (m_CyclesOKCount / (m_CyclesOKCount + m_SuspectedCycles + m_RejectedCycles)) * 100;
    }
    return m_YieldPercentage;
}

/**************************************************************************//**
*
* \brief  - To get Part Id.
          - This function is used in qml to show PartId
*
* \param  - None.
*
* \return - QString m_PartId : PartId value
*
******************************************************************************/
QString ProductionRun::getPartId() const
{
    return m_PartId;
}


/**************************************************************************//**
*
* \brief  - To get Part Id enable.
          - This function is used in qml to show PartId based on the PartIdEnable status.
*
* \param  - None.
*
* \return - bool m_IsPartIdEnable : PartId Enable or disable status
*
******************************************************************************/
bool ProductionRun::getIsPartIdEnable() const
{
    return m_IsPartIdEnable;
}
/**************************************************************************//**
*
* \brief  - To set weld mode unit on HMI.

* \param  - Index of the weldmode unit to be setted.
*
* \return - None.
*
******************************************************************************/
void ProductionRun:: setUnit(int Idx)
{

    UNIT unit  = systemConfigPtr->GetSystemUnitType();

    if(unit == METRIC)
    {
        switch (Idx)
        {

           case RecipeEnum::TIME_IDX :
               updateRecipeWeldModeUnit( "s");
               break;

           case RecipeEnum::ENERGY_IDX :
               updateRecipeWeldModeUnit("j");
               break;

           case RecipeEnum::PEAKPOWER_IDX :
               updateRecipeWeldModeUnit( "W");
               break;

           case RecipeEnum::GROUND_IDX :
               updateRecipeWeldModeUnit( "s");
               break;

           case RecipeEnum::ABSDISTANCE_IDX :
               updateRecipeWeldModeUnit("mm");
               break;

           case RecipeEnum::COLDISTANCE_IDX :
               updateRecipeWeldModeUnit("mm");
               break;
        }

    }
    else if(unit == IMPERIAL)
    {
        switch (Idx)
        {

        case RecipeEnum::TIME_IDX :
               updateRecipeWeldModeUnit( "s");
               break;

        case RecipeEnum::ENERGY_IDX :
               updateRecipeWeldModeUnit("j");
               break;

        case RecipeEnum::PEAKPOWER_IDX :
               updateRecipeWeldModeUnit( "W");
               break;

        case RecipeEnum::GROUND_IDX :
               updateRecipeWeldModeUnit( "s");
               break;

        case RecipeEnum::ABSDISTANCE_IDX :
               updateRecipeWeldModeUnit("in");
               break;

        case RecipeEnum::COLDISTANCE_IDX :
               updateRecipeWeldModeUnit("in");
               break;
        }

    }
}
/**************************************************************************//**
*
* \brief   - Role of the slot OnScreenUpdated to update the all the qml variables
*            of production screen and emit the signal to notify qml to update
*            the value upon the screen.
*
* \param   - Obj : Object pointer of type ProdScreenData.
*
* \return  - None.
******************************************************************************/
void ProductionRun::OnScreenUpdated(ProdScreenData *Obj, SystemConfigurationGeneral_MB *SysConfgGenData_Obj)
{
    systemConfigPtr = SysConfgGenData_Obj;

    // Read active welder from front end.
    if(Obj->WelderID == MultiwelderInterface::GetActiveWelder())
    {
        updateActiveRecipeNum(Obj->RecipeNum);
        updateActiveRecipeName(Obj->RecipeName);
        updateRecipeWeldMode(Obj->WeldMode);

        switch(Obj->WeldMode)
        {
        case RecipeEnum::TIME_IDX :
            setUnit(RecipeEnum::TIME_IDX);
            break;

        case RecipeEnum::ENERGY_IDX :
            setUnit(RecipeEnum::ENERGY_IDX);
            break;

        case RecipeEnum::PEAKPOWER_IDX :
            setUnit(RecipeEnum::PEAKPOWER_IDX);
            break;

        case RecipeEnum::GROUND_IDX :
            setUnit(RecipeEnum::GROUND_IDX);
            break;

        case RecipeEnum::ABSDISTANCE_IDX :
            setUnit(RecipeEnum::ABSDISTANCE_IDX );
            break;

        case RecipeEnum::COLDISTANCE_IDX :
            setUnit(RecipeEnum::COLDISTANCE_IDX);
            break;
        }

        updateRecipeWeldModeValue(QString::number(Obj->WeldModeValue));
        updateCycleCount(QString::number(Obj->CycleCount));
        updateTotalCycleTime(QString::number(Obj->TotalCycleTime));
        updatePeakPowerRatio(Obj->PeakPower / PowerLevelSysFrequencySupport::GetMaxPowerFromJSON());
        updatePeakPower(Obj->PeakPower);
        updateCyclesOkCountNum(Obj->CycleOKCount);
        updatePartsPerMinNum(Obj->PartsPerMinuteCount);
        updateRejectedCyclesNum(Obj->CycleRejectCount);
        updateSuspectedCyclesNum(Obj->CycleSuspectCount);
        updateBatchCountNum(Obj->BatchCount);

        m_PartId = Obj->PartID;
        m_IsPartIdEnable = systemConfigPtr->GetSystemDetailsFromASC().PartID;
    }

    switch (Obj->WelderID)
    {
    case WELDER1:
        updateWelderFrameCounter(Obj->FrameCount);
        break;

    case WELDER2:
        updateWelderFrameCounter2(Obj->FrameCount);
        break;

    case WELDER3:
        updateWelderFrameCounter3(Obj->FrameCount);
        break;

    default:
        break;
    }

    emit OnProductionScreenDataChanged();
}




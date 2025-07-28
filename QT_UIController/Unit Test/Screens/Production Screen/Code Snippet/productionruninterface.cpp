/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "productionruninterface.h"
#include "communicationinterface.h"
#include "recipedef.h"
#include "shareDefine.h"

/*Change by KDP*/
#include "UpdateScreens.h"

ProductionRun* ProductionRun::m_pProductionRunObj = nullptr;
//QMutex ProductionRun::mutex;
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
//    connect(CommunicationInterface::getInstance(), &CommunicationInterface::signalHeartbeatUpdated, this, &ProductionRun::slotHeartbeatUpdated);
    connect(UpdateScreen::getInstance(), &UpdateScreen::ProductionScreenUpdated, this, &ProductionRun::OnScreenUpdated);
}

/**************************************************************************//**
*
* \brief In order to avoid any affect on the screen performance,
* the communication for the recipes basic information getting will be running on the thread.
*
* \param none
*
* \return none
*
******************************************************************************/
//void ProductionRun::run()
//{
//    mutex.lock();
//    updateActiveRecipeBasicInfo();
//    mutex.unlock();
//}

/**************************************************************************//**
*
* \brief  To get Production Run interface singleton object.
*         The class is designed to the singleton class so the Production Run object can used in the everywhere
*         without any new instantiation.
*         And the Production Run object can be get easily using the this function
*         without any external declaration before using.
*
*
* \param  none
*
* \return Existing Production Run object
*
******************************************************************************/
ProductionRun *ProductionRun::getInstance()
{
    if(m_pProductionRunObj == nullptr)
    {
        m_pProductionRunObj = new ProductionRun();
    }
    return m_pProductionRunObj;
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
//        this->start();
        emit OnActiveRecipeNumChanged();
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
*        If the variable strRecipeName is not equal to m_strActiveRecipeName，
*        m_strActiveRecipeName value will be replaced with strRecipeName
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnActiveRecipeNameChanged();
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
*        If the variable weldMode is not equal to m_iRecipeWeldMode，
*        m_iRecipeWeldMode value will be replaced with weldMode
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnRecipeWeldModeChanged();
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
*        If the variable weldModeUnit is not equal to m_strRecipeWeldModeUnit，
*        m_strRecipeWeldModeUnit value will be replaced with weldModeUnit
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnRecipeWeldModeUnitChanged();
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
*        If the variable weldModeValue is not equal to m_strRecipeWeldModeValue，
*        m_strRecipeWeldModeValue value will be replaced with weldModeValue
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnRecipeWeldModeValueChanged();
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
    return m_strTotalCycleTime;
}

/**************************************************************************//**
*
* \brief To set value total cycle time for the external setting.
*        If the variable totalCycleTime is not equal to m_strTotalCycleTime，
*        m_strTotalCycleTime value will be replaced with totalCycleTime
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnTotalCycleTimeChanged();
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
*        If the variable totalCycleTime is not equal to m_strTotalCycleTime，
*        m_strTotalCycleTime value will be replaced with totalCycleTime
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnCycleCountChanged();
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
*        If the variable peakPowerRatio is not equal to m_realPeakPowerRatio，
*        m_realPeakPowerRatio value will be replaced with peakPowerRatio
*        and emit the signal to notify qml to update the value upon the screen.
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
        emit OnPeakPowerRatioChanged();
    }
}
/**************************************************************************//**
*
* \brief Once the heartbeat message coming, the function will handle with the screen data updating.
*
* \param HeartbeatFormat object pointer.
*
* \return none
*
******************************************************************************/
void ProductionRun::OnScreenUpdated(ProdScreenData *Obj)
{
    updateActiveRecipeNum(Obj->RecipeNum);
    updateActiveRecipeName(Obj->RecipeName);
    updateRecipeWeldMode(Obj->WeldMode);
    /*TODO : Unit type implimentaion (imperial/metric)*/
    updateRecipeWeldModeUnit("S");
    updateRecipeWeldModeValue(QString::number(Obj->WeldData));
    updateCycleCount(QString::number(Obj->CycleCount));
    updateTotalCycleTime(QString::number(Obj->TotalCycleTimeInSec));
    updatePeakPowerRatio(Obj->PeakPowerRatio / 100.00);
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
/**************************************************************************//**
*
* \brief To get the basic information from SC and update them for the current active Recipe and the screen.
*
* \param none
*
* \return none
*
******************************************************************************/
void ProductionRun::updateActiveRecipeBasicInfo()
{
    QByteArray sendMessage, recvMessage;
    sendMessage.clear();
    recvMessage.clear();
    const char* tmpBuf = reinterpret_cast<const char*>(&m_iActiveRecipeNum);
    sendMessage.append(tmpBuf, sizeof(int));
    CommunicationInterface::getInstance()->sendMessage(requestIdentities::GET_BASIC_RECIPE_INFO, sendMessage);
    if(CommunicationInterface::getInstance()->receivedMessage(requestIdentities::GET_BASIC_RECIPE_INFO, recvMessage) == true)
    {
        recvMessage.remove(0, sizeof(int));

        int weldmode = 0;
        tmpBuf = recvMessage.left(sizeof(int));
        memcpy(&weldmode, tmpBuf, sizeof(int));
        recvMessage.remove(0, sizeof(int));

        int modevalue = 0;
        tmpBuf = recvMessage.left(sizeof(int));
        memcpy(&modevalue, tmpBuf, sizeof(int));
        recvMessage.remove(0, sizeof(int));

        QString strRecipeName = QString(recvMessage.left(recvMessage.size()));

        QString strUnit = "s";
        switch (weldmode)
        {
        case RecipeEnum::TIME_IDX:
            strUnit = "s";
            break;
        case RecipeEnum::ENERGY_IDX:
            strUnit = "J";
            break;
        case RecipeEnum::PEAKPOWER_IDX:
            strUnit = "%";
            break;
        case RecipeEnum::COLDISTANCE_IDX:
            strUnit = "mm";
            break;
        case RecipeEnum::ABSDISTANCE_IDX:
            strUnit = "mm";
            break;
        case RecipeEnum::GROUND_IDX:
            strUnit = "s";
            break;
        default:
            strUnit = "s";
            break;
        }
        updateRecipeWeldMode(weldmode);
        updateRecipeWeldModeValue(QString::number(modevalue));
        updateActiveRecipeName(strRecipeName);
        updateRecipeWeldModeUnit(strUnit);
    }
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UpdateScreen.cpp file responsible to update each screen by fetching
    respective MB's contents by emmiting signal.
***************************************************************************/
#include "UpdateScreens.h"
#include "CommDataConfig_HMI.h"
/**************************************************************************/
/*Initialize the UpdateScreenObj pointer to null*/
UpdateScreen* UpdateScreen::UpdateScreenObj = nullptr;

/**************************************************************************//**
*
* \brief   - Role of the UpdateScreen class constructor is to connect the data
*            update signal received from communication thread to that of slot which
*            fetches the respective updated MB's using getdata.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
UpdateScreen::UpdateScreen(QObject *parent) : QObject(parent)
{
    std::cout<< "InConstructor\n";
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UpdateScreen::slotScreenUpdateReceived);
    timer->start(1000);
    std::cout<< "InConstructor2\n";
}

/**************************************************************************//**
*
* \brief   - Below function returns the instance of UpdateScreen class
*
* \param   - None.
*
* \return  - UpdateScreenObj : Object pointer of UpdateScreen class.
******************************************************************************/
UpdateScreen *UpdateScreen::getInstance()
{
    if(UpdateScreenObj == nullptr)
    {
        UpdateScreenObj = new UpdateScreen();
    }

    return UpdateScreenObj;
}

/**************************************************************************//**
*
* \brief   - Role of slotScreenUpdateReceived is :
*            1. To fetch the updated MB's of active screen using getdata.
*            2. Emit the signal with respective screen's data structure.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
void UpdateScreen::slotScreenUpdateReceived(void)
{
    uint8_t ProductionScreenBuff[100]={0};
    MEMORY_BLOCK ProductionScreenMB= { PRODUCTION_SCREEN_DATA, SUB_ID_DEFAULT, 0, sizeof(ProductionScreenBuff), ProductionScreenBuff, NULL};
    if(prod_screen_object1.GetData(&ProductionScreenMB)>=0)
    {
        static int Cyclecount=0,PPR=0;
        ProdScreenData *PtrProdScreen = reinterpret_cast<ProdScreenData *>(ProductionScreenBuff);
        std::cout<< "Recipe Name : " << PtrProdScreen->RecipeName << std::endl;
        std::cout<< "Recipe Number : " << PtrProdScreen->RecipeNum << std::endl;
        std::cout<< "WeldMode : " << PtrProdScreen->WeldMode << std::endl;
        std::cout<< "WeldData : " << PtrProdScreen->WeldData << std::endl;
        std::cout<< "WeldUnit : " << PtrProdScreen->WeldUnit << std::endl;
        std::cout<< "CycleCount : " << PtrProdScreen->CycleCount << std::endl;
        std::cout<< "TotalCycleTimeInSec : " << PtrProdScreen->TotalCycleTimeInSec << std::endl;
        std::cout<< "PeakPowerRatio : " << PtrProdScreen->PeakPowerRatio << std::endl;

        PtrProdScreen->CycleCount = Cyclecount++;
        PtrProdScreen->PeakPowerRatio = PPR++;
//        if(Cyclecount<100)
//            PtrProdScreen->PeakPowerRatio = PPR++;
//        else
//            PtrProdScreen->PeakPowerRatio = PPR--;
        emit ProductionScreenUpdated(PtrProdScreen) ;
    }
}

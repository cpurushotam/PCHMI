/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares Cyclic Activity Timer -	Responsible for Cyclic activity between threads

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.

***************************************************************************/
#include "CommCyclicActivity.h"
#include "CommPeerWrapper.h"
#include "WDSServer.h"

/*****************************************************************************
* \brief   - Initialize instance of CyclicActivityTimer class
*            1. Create timer
*            2. Setup signal and slot
*            3. Set timer interval
*
* \param   - QObject    *parent
*
* \return  - None
******************************************************************************/
CyclicActivityTimer::CyclicActivityTimer( QObject *parent)
    : QObject{parent}
{
    m_ScheduleTable.clear();

    // Create a timer
    this->m_Timer = new QTimer(this);

    // Setup signal and slot
    QObject::connect(this->m_Timer, SIGNAL(timeout()),
                     this, SLOT(CyclicActivityTimerHandler()));

    // Set timer interval as time precision
    this->m_Timer->setInterval(TIME_PRECISION);
}

/*****************************************************************************
* \brief   - Timer handler - Trigger cyclic activity for comm thread.
*
* \param   - None
*
* \return  - None
******************************************************************************/
void CyclicActivityTimer::CyclicActivityTimerHandler()
{   
    // Check whether schedule table need to update or not
    if (m_IsUpdateScheduleTable)
    {
    	// clear last values
        m_ScheduleTable.clear();
        m_PeerTickCntr=0;
        m_CurrentWelder=0;

        if (m_CurrentWelderCount)
        {
            unsigned int TotalSlots      = (TOTAL_SCHEDULE_TIME/TIME_PRECISION);
            unsigned int OffsetPerWelder = (TotalSlots/m_CurrentWelderCount);

            unsigned int CurrentWelder  = 0;
            unsigned int CurrentSlot    = 0;

            while(CurrentWelder < m_CurrentWelderCount)
            {
            	// insert trigger values in schedule table
                m_ScheduleTable.push_back(CurrentSlot);
                CurrentSlot = CurrentSlot + OffsetPerWelder;
                CurrentWelder++;
            }
        }

        m_IsUpdateScheduleTable =  false;
    }
    else
    {
        if ((!CommPeerWrapper::m_PeerMap.empty()))
        {

            if (m_CurrentWelder >= CONFIG_MAX_WELDERS )
            {
                m_CurrentWelder=0;
            }

            if (m_PeerTickCntr == m_ScheduleTable[m_CurrentWelder])
            {
                if (CommPeerWrapper::m_PeerMap[m_CurrentWelder] != nullptr)
                {
                    // check peer information is available for configure welder
                     if ((CommPeerWrapper::m_PeerMap[m_CurrentWelder]->GetCurrentState()) == COMM_PROCESS)
                     {
                         // Send cyclic activity signal to configure comm thread
                         CommPeerWrapper::m_PeerMap[m_CurrentWelder]->TriggerCyclicActivity();
                     }
                }
                m_CurrentWelder++;
            }

            if (m_PeerTickCntr == (TOTAL_SCHEDULE_TIME/TIME_PRECISION))
            {
                   m_PeerTickCntr = 0; // Cleared/Reset tick counter to 0
            }
            else
            {
                m_PeerTickCntr++;      // Increment tick counter
            }
        }
    }
}

/*****************************************************************************
* \brief   - Update scheduling table of comm thread
*
* \param   - unsigned int TotalWelders - Configured number of welders
*
* \return  - None
******************************************************************************/
void CyclicActivityTimer::UpdateSchedule(unsigned int TotalWelders)
{
    m_CurrentWelderCount = TotalWelders;

    m_IsUpdateScheduleTable = true;
}

/*****************************************************************************
* \brief   - Start timer
*
* \param   - None
*
* \return  - None
******************************************************************************/
void CyclicActivityTimer::StartScheduleing()
{
    // Start Timer
    this->m_Timer->start();
}

/*****************************************************************************
* \brief   - Stop timer
*
* \param   - None
*
* \return  - None
******************************************************************************/
void CyclicActivityTimer::StopScheduleing()
{
    // Start Timer
    this->m_Timer->stop();

}

/*****************************************************************************
* \brief   - Destructor to perform cleanup activity
*
* \param   - None
*
* \return  - None
******************************************************************************/
CyclicActivityTimer::~CyclicActivityTimer()
{
    // Delete instance of timer class
    delete this->m_Timer;
}

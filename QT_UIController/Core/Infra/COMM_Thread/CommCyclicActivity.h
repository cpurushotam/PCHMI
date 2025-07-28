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
#ifndef CYCLICACTIVITYTIMER_H
#define CYCLICACTIVITYTIMER_H

#include <QObject>
#include <QTimer>
#include <vector>

// Total thread schedule time
constexpr unsigned int TOTAL_SCHEDULE_TIME=500;

// Time precision for timer 
constexpr unsigned int TIME_PRECISION=50;

// CyclicActivityTimer class definition
class CyclicActivityTimer : public QObject
{
private:
    // Declaration of Q_OBJECT for signals and slots mechanism
    Q_OBJECT

    // Timer pointer for interface to timer class functions
    QTimer *m_Timer;

    // schedule table to store trigger value
    std::vector <int> m_ScheduleTable;

    // PeerTickCntr for timer handler
    unsigned int m_PeerTickCntr=0;

    // To store current welder for schedule table
    unsigned int m_CurrentWelder=0;

    // To store total number of welders.
    unsigned int m_CurrentWelderCount=0;

    // To update schedule table or not
    std::atomic<bool> m_IsUpdateScheduleTable;

public:
    // Constructor declaration
    explicit CyclicActivityTimer(QObject *parent = nullptr);

    // Destructor declaration to perform cleanup activity
    ~CyclicActivityTimer();

    // update schedule
    void UpdateSchedule(unsigned int TotalWelders);

    // Start Timer
    void StartScheduleing();

    // Stop Timer
    void StopScheduleing();

public slots:
    // Handles cyclic activity of comm thread
    void CyclicActivityTimerHandler();
};

#endif // CYCLICACTIVITYTIMER_H

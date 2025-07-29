/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps track for current active screen.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 20/07/2023 - Initial version.
***************************************************************************/
#ifndef ACTIVESCREEN_H
#define ACTIVESCREEN_H
#include <QObject>

/*ActiveScreen class declaration*/
class ActiveScreen : public QObject
{
private:
    Q_OBJECT

    Q_PROPERTY(int CurrentActiveScreen READ getCurrentActiveScreen WRITE updateCurrentActiveScreen NOTIFY OnACurrentActiveScreenChanged)

    explicit ActiveScreen(QObject *parent = nullptr);
    ActiveScreen(const ActiveScreen&) = delete;
    ActiveScreen& operator=(const ActiveScreen&) = delete;

    int m_CurrentActiveScreen;

public:

    /*Method which retunrs singleton object of ActiveScreen class*/
    static ActiveScreen* getInstance();

    int getCurrentActiveScreen(void);
    void updateCurrentActiveScreen(int m_IndexVal);

signals:
    void OnCurrentSystemTypeChanged();
    void OnACurrentActiveScreenChanged();


};
#endif // ACTIVESCREEN_H

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

 Declares IdleTimeLogout Class - responsible for interact between frontend and QT Timer

***************************************************************************/
#ifndef IdleTimeLogout_H
#define IdleTimeLogout_H

#include <QObject>
#include <QTimer>

#define MAX_TIMEOUT_VAL 2147483647 //Max default timeout i.e to 24 days

class IdleTimeLogout : public QObject
{
    Q_OBJECT

public:

    explicit IdleTimeLogout(QObject *parent = nullptr);
    Q_INVOKABLE void setTimeOut(int milliseconds);

private:

    int m_TimeOut;
    QTimer m_Timer;

    bool eventFilter(QObject *obj, QEvent *ev);

public slots:
    void appSlepp();

    // Signal to notify QML about updated values
signals:
   void idleTimeLogOut();

};
#endif // IdleTimeLogout_H



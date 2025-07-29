/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DisplayModesHMI related implementation
 ***************************************************************************/
#ifndef DISPLAYMODESHMI_H
#define DISPLAYMODESHMI_H

#include <QObject>
#include <QString>
#include "DisplayManager.h"

class DisplayModesHMI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int DisplayMode          READ getDisplayMode            NOTIFY currentDisplayModeChanged)

public:
    explicit DisplayModesHMI(QObject *parent = nullptr);
    int getDisplayMode() ;

signals:
    void currentDisplayModeChanged();

private:
    int m_DisplayMode = MODE_FULLY_FUNCTIONAL;

    FIELDBUS_TOKEN m_PlcTokenStatus; /*Todo - Backend not availble currently */

    int m_WelderId = -1;

    DisplayMgr *DisplayMgrPtr;

private slots:
    void OnDisplayModeUpdated(DisplayMgr *DisplayMgr_Obj, int WelderId);

};

#endif // DISPLAYMODESHMI_H

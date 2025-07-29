/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    GraphAxisDef.h file keeps graph axis index enum definitions.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 17/10/2023 - Initial version.
***************************************************************************/

#ifndef GRAPHAXISDEF_H
#define GRAPHAXISDEF_H

#include <QObject>
#include <QQmlEngine>

#define GRAPHAXISENUM_URI_NAME "Com.Branson.GraphAxisEnum"
#define GRAPHAXISENUM_QML_MAJOR_VERSION 1
#define GRAPHAXISENUM_QML_MINOR_VERSION 0
#define GRAPHAXISENUM_QML_NAME "GraphAxisEnum"

class GraphAxisEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(GRAPHAXISINDEX)
public:
    enum GRAPHAXISINDEX
    {
        AMP_IDX =          0,
        POWER_IDX          ,
        FREQ_IDX           ,
        PHASE_IDX          ,
        CURRENT_IDX        ,
        ENERGY_IDX         ,
        FORCE_IDX          ,
        ABSOLUTEDIST_IDX   ,
        COLLAPSEDIST_IDX   ,
        REQAMP_IDX         ,
        VELOCITY_IDX       ,
        TIME_IDX           ,
        TOTAL_IDX
    };

    static void registerQMLType()
    {
        qmlRegisterType<GraphAxisEnum>(GRAPHAXISENUM_URI_NAME,
                                       GRAPHAXISENUM_QML_MAJOR_VERSION,
                                       GRAPHAXISENUM_QML_MINOR_VERSION,
                                       GRAPHAXISENUM_QML_NAME);
    }
};

#endif // GRAPHAXISDEF_H

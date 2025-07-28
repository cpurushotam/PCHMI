/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef RECIPEDEF_H
#define RECIPEDEF_H
#include <QObject>
#include <QQmlEngine>

#define RECIPEENUM_URI_NAME "Com.Branson.RecipeEnum"
#define RECIPEENUM_QML_MAJOR_VERSION 1
#define RECIPEENUM_QML_MINOR_VERSION 0
#define RECIPEENUM_QML_NAME "RecipeEnum"

class RecipeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(WELDMODEINDEX)
    Q_ENUMS(RECIPEACTIONS)
    Q_ENUMS(PRETRIGGER_TYPE_IDX)
    Q_ENUMS(ACTUATOR_TYPE_IDX)
    Q_ENUMS(TRIGGER_TYPE_IDX)


public:
    enum WELDMODEINDEX
    {
        NONE_IDX = -1,
        TIME_IDX,
        ENERGY_IDX,
        PEAKPOWER_IDX,
        GROUND_IDX,
        ABSDISTANCE_IDX,
        COLDISTANCE_IDX,
        TOTALWELDMODE_IDX
    };

    enum RECIPEACTIONS
    {
        CREATE_NEW_IDX = 0,
        PRODUCTION_RUN_IDX,
        EDIT_IDX,
        RESET_CYCLE_COUNT_IDX,
        SET_AS_ACTIVE_IDX,
        DELETE_IDX,
        COPY_IDX,
        INFORMATION_IDX
    };

    enum PRETRIGGER_TYPE_IDX
    {
        AUTO_PRETRIGGER_IDX,
        TIME_PRETRIGGER_IDX,
        DISTANCE_PRETRIGGER_IDX
    };

    enum ACTUATOR_TYPE_IDX
    {
        ACTUTATOR_TIME_IDX,
        ACTUTATOR_DISTANCE_IDX
    };

    enum TRIGGER_TYPE_IDX
    {
        TRIGGER_TYPE_SWITCH_IDX = 0,
        TRIGGER_TYPE_FORCE_IDX ,
        TRIGGER_TYPE_DISTANCE_IDX
    };
    static void registerQMLType()
    {
        qmlRegisterType<RecipeEnum>(RECIPEENUM_URI_NAME,
                                    RECIPEENUM_QML_MAJOR_VERSION,
                                    RECIPEENUM_QML_MINOR_VERSION,
                                    RECIPEENUM_QML_NAME);
    }
};
#endif // RECIPEDEF_H

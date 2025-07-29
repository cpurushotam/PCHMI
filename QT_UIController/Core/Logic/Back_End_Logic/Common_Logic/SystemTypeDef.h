/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file keeps enum for system types available to be configured.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 15/09/2023 - Initial version.
 rev2: 11/10/2023 - Updated SystemType Enum.
***************************************************************************/
#ifndef SYSTEMTYPEDEF_H
#define SYSTEMTYPEDEF_H

#include <QObject>
#include <QQmlEngine>
#include "ActuatorInit.h"
#include "EventLogSupport.h"
#include "UserIOSupport.h"

#define SYSTEMTYPEDEF_URI_NAME "Com.Branson.SystemTypeDef"
#define SYSTEMTYPEDEF_QML_MAJOR_VERSION 1
#define SYSTEMTYPEDEF_QML_MINOR_VERSION 0
#define SYSTEMTYPEDEF_QML_NAME "SystemTypeDef"

/*SystemTypeDef class declaration*/
class SystemTypeDef : public QObject
{
private:
    Q_OBJECT

public:

    enum ACTUATOR_TYPE
    {
        ACTUATOR_MANUAL = 1,			/* Mechanical trigger switch */
        ACTUATOR_ELECTRONIC,			/* Pressure and down speed control, Load Cell, Linear Encoder */
        ACTUATOR_ELECTRONIC_PLUS,
        NO_ACTUATOR,                	/* No Actuator configuration */
        ACTUATOR_CONFIG_MAX				/* Move ACTUATOR_CONFIG_MAX variable Below base on actuator configuration implementation */
    };
    Q_ENUM(ACTUATOR_TYPE)

    enum USER_IO_SUPPORT
    {
        USER_IO_NOT_SUPPORTED = 1,
        USER_IO_SUPPORTED,
    };
    Q_ENUM(USER_IO_SUPPORT)

    enum EVENT_LOG_SUPPORT
    {
        EVENT_LOG_NOT_SUPPORTED	= 1,
        EVENT_LOG_SUPPORTED
    };
    Q_ENUM(EVENT_LOG_SUPPORT)

    enum BATCH_CONTROL_SUPPORT
    {
        BATCH_CONTROL_NOT_SUPPORTED	= 1,
        BATCH_CONTROL_SUPPORTED,
    };
    Q_ENUM(BATCH_CONTROL_SUPPORT)

    enum DISPLAY_MODES_SUPPORT
    {
        DISPLAY_MODE_UNKNOWN = 0,
        DISPLAY_MODE_READ_ONLY,
        DISPLAY_MODE_LOCKED,
        DISPLAY_MODE_FULLY_FUNCTIONAL
    };
    Q_ENUM(DISPLAY_MODES_SUPPORT)

    enum FIELDBUS_TYPE_SUPPORT
    {
        FIELDBUS_NOT_SUPPORTED	= 1,
        FIELDBUS_ETHERNET_IP,
        FIELDBUS_PROFINET,
        FIELDBUS_ETHERCAT
    };
    Q_ENUM(FIELDBUS_TYPE_SUPPORT)

    enum USER_ACCESS_LEVEL_TYPE
    {
        STANDARD_USER_ACCESS_LEVEL = 1,
        ADVANCED_USER_ACCESS_LEVEL
    };
    Q_ENUM(USER_ACCESS_LEVEL_TYPE)

    static void registerQMLType()
    {
        qmlRegisterType<SystemTypeDef>(SYSTEMTYPEDEF_URI_NAME,
                                       SYSTEMTYPEDEF_QML_MAJOR_VERSION,
                                       SYSTEMTYPEDEF_QML_MINOR_VERSION,
                                       SYSTEMTYPEDEF_QML_NAME);
    }
};
#endif // SYSTEMTYPEDEF_H

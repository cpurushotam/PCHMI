/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LOGINDEF_H
#define LOGINDEF_H

#include <QObject>
#include <QQmlEngine>

#define LOGININDEXENUM_URI_NAME "Com.Branson.LoginIndexEnum"
#define LOGININDEXENUM_QML_MAJOR_VERSION 1
#define LOGININDEXENUM_QML_MINOR_VERSION 0
#define LOGININDEXENUM_QML_NAME "LoginIndexEnum"

class LoginIndexEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(LOGININDEX)
public:
    enum LOGININDEX
    {
        EMPTY_PASSCODE = -3,
        MULTIPLE_FAILED_LOGIN = -2,
        LOGIN_FAIL = -1,
        SUCCESS = 0
    };

    static void registerQMLType()
    {
        qmlRegisterType<LoginIndexEnum>(LOGININDEXENUM_URI_NAME,
                                       LOGININDEXENUM_QML_MAJOR_VERSION,
                                       LOGININDEXENUM_QML_MINOR_VERSION,
                                       LOGININDEXENUM_QML_NAME);
    }
};


#endif // LOGINDEF_H

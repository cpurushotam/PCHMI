/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2023

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*Header files*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CommonHeader.h"
#include "Communication.h"
#include "Config.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

/*Define BIO_USING_THREAD for enabling thread based communication and for that of Polling define BIO_USING_POLL*/
#define BIO_USING_THREAD

/*Thread based communication section*/
#ifdef BIO_USING_THREAD

/*Thread objects*/
pthread_t pClient_tid;
pthread_t pClient_tid2;

/*Thread 1 function pointer definition*/
void *ClientBIO(void*)
{
    try
    {
        /*Variable declaration*/
        int retValue,retValue2,ssl_err,ssl_err2;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        Communication* Client = new Communication (ClientParam);

        /*Buffer to be used for communication*/
        uint8_t MyBuff[] = "Thread 1 : Hi, this is Client writting,in Non-Secure Communication..!", MyBuff2[100];

        /*Bio Write request from client*/
        retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
        /*Get error status for write request*/
        ssl_err = SSL_get_error(Client->ssl, retValue);


        /*Bio Read request from client*/
        retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));
        /*Get error status for read request*/
        ssl_err2 = SSL_get_error(Client->ssl, retValue2);

    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        cout << ErrorString << endl;
    }
}

/*Thread 2 function pointer definition*/
void *ClientBIO2(void*)
{
    try
    {
        /*Variable declaration*/
        int retValue,retValue2,ssl_err,ssl_err2;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        Communication* Client2 = new Communication (ClientParam2);

        /*Buffer to be used for communication*/
        uint8_t MyBuff[] = "Thread 2 : Hi, this is Client writting,in Non-Secure Communication..!", MyBuff2[100];

        /*Bio Write request from client*/
        retValue = Client2->BIOWrite(MyBuff, sizeof(MyBuff));
        /*Get error status for write request*/
        ssl_err = SSL_get_error(Client2->ssl, retValue);


        /*Bio Read request from client*/
        retValue2 = Client2->BIORead(MyBuff2, sizeof(MyBuff2));
        /*Get error status for read request*/
        ssl_err2 = SSL_get_error(Client2->ssl, retValue2);

    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        cout << ErrorString << endl;
    }
}
#endif

int main(int argc, char *argv[])
{
#ifdef BIO_USING_THREAD

    /*Create Thread 1*/
    if (pthread_create(&pClient_tid, NULL, ClientBIO, NULL) != 0)
    {
        throw "pthread_create() error";
    }

    /*Create Thread 2*/
    if (pthread_create(&pClient_tid2, NULL, ClientBIO2, NULL) != 0)
    {
        throw "pthread_create() error";
    }

    /*Join Thread 1*/
    if (pthread_join(pClient_tid, NULL) != 0)
    {
        throw "pthread_join() error";
    }

    /*Join Thread 2*/
    if (pthread_join(pClient_tid2, NULL) != 0)
    {
        throw "pthread_join() error";
    }

#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    /*Polling based communication section*/
#ifdef BIO_USING_POLLING

    try
    {
        /*Variable declaration*/
        int retValue,retValue2,ssl_err,ssl_err2;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        Communication* Client = new Communication (ClientParam);

        /*Buffer to be used for communication*/
        uint8_t MyBuff[] = "Hi, this is Client writting,in Non-Secure Communication..!", MyBuff2[100];

        /*Bio Write request from client*/
        retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
        /*Get error status for write request*/
        ssl_err = SSL_get_error(Client->ssl, retValue);


        /*Bio Read request from client*/
        retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));
        /*Get error status for read request*/
        ssl_err2 = SSL_get_error(Client->ssl, retValue2);

    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        cout << ErrorString << endl;
    }
#endif
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

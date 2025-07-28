/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2023

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*Header files*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "BIOWrapperCommon.h"
#include "BIOWrapper.h"
#include "BIOConfig.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

/*Define BIO_USING_THREAD for enabling thread based communication and for that of Polling define BIO_USING_POLL*/
#define BIO_USING_POLLING

/*Thread based communication section*/
#ifdef BIO_USING_THREAD

/*Thread objects*/
pthread_t pServer_tid;
pthread_t pServer_tid2;

/*Thread 1 function pointer definition*/
void *ClientBIO(void*)
{
    try
        {
            /*Variable declaration*/
            int retValue,retValue2,ssl_err,ssl_err2;

            /*Instantiate Communication class object with configuration defined in Config.h file*/
            BIOWrapper* Client = new BIOWrapper (&ClientParam);

            /*Buffer to be used for communication*/
            uint8_t MyBuff[] = "HI, This is Client.", MyBuff2[100];

            /*Bio Write request from client*/
            retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
            sleep(10);
            /*Bio Write request from client*/
            retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
            /*Bio Read request from client*/
//            retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));
//            if(retValue < STATUS_CONNECTION_DEFAULT)
//            {

//                /*Re-instantiate the object to restart the communication*/
//                delete Client;
//                Client = new BIOWrapper (&ClientParam);

//            }
        }

        /*Catch error statement*/
        catch (const char *ErrorString)
        {
            std::cout << ErrorString << std::endl;
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
            BIOWrapper* Client2 = new BIOWrapper (&ClientParam2);

            /*Buffer to be used for communication*/
            uint8_t MyBuff[] = "HI, This is Client.", MyBuff2[100];

            /*Bio Write request from client*/
            retValue = Client2->BIOWrite(MyBuff, sizeof(MyBuff));
            sleep(10);
            /*Bio Write request from client*/
            retValue = Client2->BIOWrite(MyBuff, sizeof(MyBuff));
            /*Bio Read request from client*/
//            retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));
//            if(retValue < STATUS_CONNECTION_DEFAULT)
//            {

//                /*Re-instantiate the object to restart the communication*/
//                delete Client2;
//                Client2 = new BIOWrapper (&ClientParam2);

//            }
        }

        /*Catch error statement*/
        catch (const char *ErrorString)
        {
            std::cout << ErrorString << std::endl;
        }
}
#endif

int main(int argc, char *argv[])
{
#ifdef BIO_USING_THREAD
    /*Create Thread 1*/
    if (pthread_create(&pServer_tid, NULL, ClientBIO, NULL) != 0)
    {
        throw "pthread_create() error";
    }

    /*Create Thread 2*/
    if (pthread_create(&pServer_tid2, NULL, ClientBIO2, NULL) != 0)
    {
        throw "pthread_create() error";
    }

    /*Invoke Thread 1*/
    if (pthread_join(pServer_tid, NULL) != 0)
    {
        throw "pthread_join() error";
    }

    /*Invoke Thread 2*/
    if (pthread_join(pServer_tid2, NULL) != 0)
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
            BIOWrapper* Client = new BIOWrapper (&ClientParam);

            /*Buffer to be used for communication*/
            uint8_t MyBuff[] = "HI, This is Client2.", MyBuff2[100];

            /*Bio Write request from client*/
            sleep(5);
            retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
            sleep(5);
            /*Bio Write request from client*/
            retValue = Client->BIOWrite(MyBuff, sizeof(MyBuff));
            /*Bio Read request from server*/
//            sleep(3);
//            retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));
//            sleep(3);
//            retValue2 = Client->BIORead(MyBuff2, sizeof(MyBuff2));

//            std::cout<<"Initiating graceful shutdown in 5 sec";
//            sleep(5);
//            delete Client;

            if((retValue < STATUS_CONNECTION_DEFAULT)||(retValue2 < STATUS_CONNECTION_DEFAULT))
            {
                /*Perform graceful shutdown and delete client object*/
                delete Client;
            }
        }

        /*Catch error statement*/
        catch (const char *ErrorString)
        {
            std::cout << ErrorString << std::endl;
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

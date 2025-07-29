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
pthread_t pServer_tid;
pthread_t pServer_tid2;

/*Thread 1 function pointer definition*/
void *ServerBIO(void*)
{
    try
    {
        /*Variable declaration*/
        int retValue,retValue2,ssl_err,ssl_err2;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        Communication* Server = new Communication (ServerParam);

        do{
            /*Buffer to be used for communication*/
            uint8_t MyBuff[100], MyBuff2[]="Thread 1 : Hi, this is Server writting, in Non-Secure Communication..!";

            /*Bio read request from server*/
            retValue = Server->BIORead(MyBuff, sizeof(MyBuff));
            /*Get error status for read request*/
            ssl_err = SSL_get_error(Server->ssl, retValue);


            /*Bio write request from server*/
            retValue2 = Server->BIOWrite(MyBuff2, sizeof(MyBuff2));
            /*Get error status for write request*/
            ssl_err2 = SSL_get_error(Server->ssl, retValue2);


            /*Based on error status got from read/write request delete the original object and reinstantiate again*/
            if((ssl_err != STATUS_SSL_ERROR_NONE)||(ssl_err2 != STATUS_SSL_ERROR_NONE))
            {
                /*Get the details behind filure in communication*/
                if(ssl_err != STATUS_SSL_ERROR_NONE)
                {
                    /*Get error description*/
                    Server->GetCommStatus(ssl_err);
                }

                else if(ssl_err2 != STATUS_SSL_ERROR_NONE)
                {
                    /*Get error description*/
                    Server->GetCommStatus(ssl_err2);
                }

                /*Re-instantiate the object to restart the communication*/
                delete Server;
                Server = new Communication (ServerParam);
            }
        }

        while(1);
    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        cout << ErrorString << endl;
    }
}

/*Thread 2 function pointer definition*/
void *ServerBIO2(void*)
{
    try
    {
        /*Variable declaration*/
        int retValue,retValue2,ssl_err,ssl_err2;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        Communication* Server2 = new Communication (ServerParam2);

        do{
            /*Buffer to be used for communication*/
            uint8_t MyBuff[100], MyBuff2[]="Thread 2 : Hi, this is Server writting, in Non-Secure Communication..!";

            /*Bio Read request from server*/
            retValue = Server2->BIORead(MyBuff, sizeof(MyBuff));
            /*Get error status for read request*/
            ssl_err = SSL_get_error(Server2->ssl, retValue);


            /*Bio Write request from server*/
            retValue2 = Server2->BIOWrite(MyBuff2, sizeof(MyBuff2));
            /*Get error status for write request*/
            ssl_err2 = SSL_get_error(Server2->ssl, retValue2);


            /*Get the details behind filure in communication*/
            if((ssl_err != STATUS_SSL_ERROR_NONE)||(ssl_err2 != STATUS_SSL_ERROR_NONE))
            {
                if(ssl_err != STATUS_SSL_ERROR_NONE)
                {
                    /*Get error description*/
                    Server2->GetCommStatus(ssl_err);
                }

                else if(ssl_err2 != STATUS_SSL_ERROR_NONE)
                {
                    /*Get error description*/
                    Server2->GetCommStatus(ssl_err2);
                }

                /*Re-instantiate the object to restart the communication*/
                delete Server2;
                Server2 = new Communication (ServerParam2);
            }
        }

        while(1);
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
    if (pthread_create(&pServer_tid, NULL, ServerBIO, NULL) != 0)
    {
        throw "pthread_create() error";
    }

    /*Create Thread 2*/
    if (pthread_create(&pServer_tid2, NULL, ServerBIO2, NULL) != 0)
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
        Communication* Server = new Communication (ServerParam);

        do{

            /*Buffer to be used for communication*/
            uint8_t MyBuff[100], MyBuff2[]="Hi, this is Server writting, in Non-Secure Communication..!";

            /*Bio Read request from server*/
            retValue = Server->BIORead(MyBuff, sizeof(MyBuff));
            /*Get error status for read request*/
            ssl_err = SSL_get_error(Server->ssl, retValue);


            /*Bio Write request from server*/
            retValue2 = Server->BIOWrite(MyBuff2, sizeof(MyBuff2));
            /*Get error status for write request*/
            ssl_err2 = SSL_get_error(Server->ssl, retValue2);


            if((ssl_err != STATUS_SSL_ERROR_NONE)||(ssl_err2 != STATUS_SSL_ERROR_NONE))
            {
                /*Get the details behind filure in communication*/
                if((ssl_err != STATUS_SSL_ERROR_NONE)||(ssl_err2 != STATUS_SSL_ERROR_NONE))
                {
                    if(ssl_err != STATUS_SSL_ERROR_NONE)
                    {
                        /*Get error description*/
                        Server->GetCommStatus(ssl_err);
                    }

                    else if(ssl_err2 != STATUS_SSL_ERROR_NONE)
                    {
                        /*Get error description*/
                        Server->GetCommStatus(ssl_err2);
                    }
                }
                delete Server;
                Server = new Communication (ServerParam);
            }
        }

        while(1);
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

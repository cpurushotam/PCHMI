//============================================================================
// Name        : BIO_Wrapper_Server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "BIOWrapperCommon.h"
#include "BIOWrapper.h"
#include "BIOConfig.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "unistd.h"
/*Define BIO_USING_THREAD for enabling thread based communication and for that of Polling define BIO_USING_POLL*/
#define BIO_USING_POLLING

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
        BIOWrapper* Server = new BIOWrapper (&ServerParam);

        do{

            /*Buffer to be used for communication*/
            uint8_t MyBuff[100];
            std::cout<<"====================================\n"<<std::endl;
            /*Bio Read request from server*/
            retValue = Server->BIORead(MyBuff, sizeof(MyBuff));
            std::cout<<"====================================\n"<<std::endl;
            sleep(2);

            /*Buffer to be used for communication*/
//            uint8_t MyBuff[100], MyBuff2[]="Hi, This is Server.";
//            sleep(5);
//            std::cout<<"====================================\n"<<std::endl;
//            /*Bio Read request from server*/
//            retValue = Server->BIOWrite(MyBuff2, sizeof(MyBuff2));
//            std::cout<<"====================================\n"<<std::endl;

           if(retValue < STATUS_CONNECTION_DEFAULT)
           {

               /*Re-instantiate the object to restart the communication*/
               delete Server;
               Server = new BIOWrapper (&ServerParam);

           }
        }

        while(1);
    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        std::cout << ErrorString << std::endl;
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
        BIOWrapper* Server2 = new BIOWrapper (&ServerParam2);

        do{

            /*Buffer to be used for communication*/
            uint8_t MyBuff[100];
            std::cout<<"====================================\n"<<std::endl;
            /*Bio Read request from server*/
            retValue = Server2->BIORead(MyBuff, sizeof(MyBuff));
            std::cout<<"====================================\n"<<std::endl;
            sleep(2);

            /*Buffer to be used for communication*/
//            uint8_t MyBuff[100], MyBuff2[]="Hi, This is Server2.";
//            sleep(5);
//            std::cout<<"====================================\n"<<std::endl;
//            /*Bio Read request from server*/
//            retValue = Server2->BIOWrite(MyBuff2, sizeof(MyBuff2));
//            std::cout<<"====================================\n"<<std::endl;

           if(retValue < STATUS_CONNECTION_DEFAULT)
           {

               /*Re-instantiate the object to restart the communication*/
               delete Server2;
               Server2 = new BIOWrapper (&ServerParam2);

           }
        }

        while(1);
    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        std::cout << ErrorString << std::endl;
    }
}
#endif

using namespace std;

int main() {

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
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

    /*Polling based communication section*/
#ifdef BIO_USING_POLLING

    try
    {
        /*Variable declaration*/
        int retValue;

        /*Instantiate Communication class object with configuration defined in Config.h file*/
        BIOWrapper* Server = new BIOWrapper (&ServerParam);

        do{

        	/*Buffer to be used for communication*/
        	uint8_t MyBuff[100] = {0}, MyBuff2[] = "Hi, This is Server2";
        	std::cout<<"====================================\n"<<std::endl;
        	/*Bio Read request from server*/
        	retValue = Server->BIORead(MyBuff, sizeof(MyBuff));
        	sleep(2.5);
        	retValue = Server->BIOWrite(MyBuff2, sizeof(MyBuff2));
        	sleep(2);
        	retValue = Server->BIORead(MyBuff, sizeof(MyBuff));
        	sleep(2.5);
        	retValue = Server->BIOWrite(MyBuff2, sizeof(MyBuff2));
        	sleep(2);
        	std::cout<<"====================================\n"<<std::endl;

        	if(1);
//        	if(retValue < STATUS_CONNECTION_DEFAULT)
        	{

        		/*Re-instantiate the object to restart the communication*/
        		delete Server;
        		sleep(2);
        		Server = new BIOWrapper (&ServerParam);

        	}
        }

        while(1);
    }

    /*Catch error statement*/
    catch (const char *ErrorString)
    {
        std::cout << ErrorString << std::endl;
    }
#endif

	return 0;
}

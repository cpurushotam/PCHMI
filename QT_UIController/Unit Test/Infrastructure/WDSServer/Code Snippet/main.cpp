/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QMutex>
#include <QObject>
#include "uiscreendef.h"
#include "languagedef.h"
#include "logindef.h"
#include "languageconfig.h"
#include "jsontreemodel.h"
#include "recipemodel.h"
#include "recipedef.h"
#include "ProductionRunInterface.h"
#include "login.h"
#include "UpdateScreens.h"
#include "CommThread.h"
#include "CommCyclicActivity.h"
#include "CommPeerWrapper.h"

#include "UpdateScreens.h"
#include "BIOConfig.h"
#include "ActiveScreen.h"
#include "MultiwelderInterface.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QString strOSIndicator = "None";
#ifdef WIN32
    strOSIndicator = "WINDOWS OS";
#elif linux
#ifdef RASPBERRY
    strOSIndicator = "Raspbian OS";
#else
    strOSIndicator = "Ubuntu OS";
#endif
#endif

    LanguageConfig::getInstance()->checkLanguageFiles();

    qmlRegisterSingletonType(QUrl("qrc:/Core/Logic/Front_End_Logic/Common_Logic/BransonStyle.qml"), "Style", 1, 0, "Style");
    qmlRegisterSingletonType(QUrl("qrc:/Core/Logic/Front_End_Logic/Common_Logic/BransonNumpadDefine.qml"), "NumpadDefine", 1, 0, "NumpadDefine");
    UIScreenEnum::registerQMLType();
    RecipeEnum::registerQMLType();
    LoginIndexEnum::registerQMLType();
    LanguageEnum::registerQMLType();

    QQmlApplicationEngine engine;
    engine.addImportPath(":/VirtualKeyboardStyles");
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "styleVirtualKeyboard");
    QQmlContext *pQmlContext = engine.rootContext();
#ifdef QT_DEBUG
    pQmlContext->setContextProperty("debug", true);
#else
    pQmlContext->setContextProperty("debug", false);
#endif
    pQmlContext->setContextProperty("languageConfig", LanguageConfig::getInstance());
    pQmlContext->setContextProperty("languageModel", LanguageConfig::getInstance()->getLanguageModelInstance());
    ProductionRun m_ProductionRunObj;
    pQmlContext->setContextProperty("productionRunInterface", &m_ProductionRunObj);
    RecipeModel m_RecipeModelObj;
    pQmlContext->setContextProperty("recipeModel", &m_RecipeModelObj);
    pQmlContext->setContextProperty("login", Login::getInstance());
    pQmlContext->setContextProperty("activeScreen", ActiveScreen::getInstance());

    //============================================================//
    /*TODO : Below section is workaround for Production screen implementation with 3 welder represented by each CommThreads,
                 where dynamic welder approach implemented*/
    UpdateScreen *MyUpdateScreen = UpdateScreen::getInstance();
    CommThread *ptrCommThread[MAX_WELDERS];

    // Created instance of welder discovery service
    WDSServer WdsServer;

    // Start auto welder discovery service
    WdsServer.start();

    // Created instance of multiWelderInterface

    MultiwelderInterface multiWelderInterface;

    // Export MultiwelderInterface class to qml.
    pQmlContext->setContextProperty("multiWelderInterface", &multiWelderInterface);

    // Connect PeerConnected signal to MultiwelderInterface slot.
    QObject::connect(&WdsServer, &WDSServer::PeerConnected,
                         &multiWelderInterface, &MultiwelderInterface::OnPeerConnected);

    // Created Cyclic Activity Timer
    CyclicActivityTimer *Cat = new CyclicActivityTimer();

    for (int i = 0; i < MAX_WELDERS; i++)
    {
        // Created Communication Thread
        ptrCommThread[i] = new CommThread(i);

        // Connect HMIScreenUpdated signal to UpdateScreen slot.
        QObject::connect(ptrCommThread[i], &CommThread::HMIScreenUpdated,
                         MyUpdateScreen , &UpdateScreen::slotScreenUpdateReceived);

        // Start Comm Thread
        ptrCommThread[i]->start();

        // Connect PeerDisconnected signal to MultiwelderInterface slot.
        QObject::connect(ptrCommThread[i], &CommThread::PeerDisconnected,
                         &multiWelderInterface, &MultiwelderInterface::OnwelderRemoved);
    }

    // Start Scheduleing Cyclic Activity Timer
    Cat -> StartScheduleing();

    // update Scheduleing Cyclic Activity Timer to MAX WELDER
    Cat -> UpdateSchedule(MAX_WELDERS);

    //===========================================================//

    #ifdef QT_DEBUG

    #else
        qInstallMessageHandler(messageHandler);
        qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss:zzz}|%{type}|%{file}|%{function}|%{line}|%{message}");
    #endif
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if(engine.rootObjects().isEmpty())
            return -1;
        return app.exec();
}

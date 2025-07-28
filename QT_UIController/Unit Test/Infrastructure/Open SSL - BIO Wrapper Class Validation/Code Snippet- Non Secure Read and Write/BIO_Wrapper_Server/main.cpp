#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CommonHeader.h"
#include "Communication.h"
#include "Config.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    /*Instantiate Communication class object with configuration defined in Config.h file*/
    Communication Server(ServerParam);

    /*Buffer to be used for communication*/
    uint8_t MyBuff[100], MyBuff2[]="Hi, this is Server writting, in Non Secure Communication..!";

    /*Bio Read request from server*/
    Server.BIORead(MyBuff, sizeof(MyBuff));

    /*Bio Write request from server*/
    Server.BIOWrite(MyBuff2, sizeof(MyBuff2));


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

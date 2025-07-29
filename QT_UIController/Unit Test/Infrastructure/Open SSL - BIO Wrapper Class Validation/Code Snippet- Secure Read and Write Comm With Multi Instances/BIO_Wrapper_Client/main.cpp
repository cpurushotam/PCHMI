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
    Communication Client(ClientParam);

    /*Buffer to be used for communication*/
    uint8_t MyBuff[] = "Hi, this is Client1 writting, in Secure Communication..!", MyBuff2[100];

    /*Bio Write request from client*/
    Client.BIOWrite(MyBuff, sizeof(MyBuff));

    /*Bio Read request from client*/
    Client.BIORead(MyBuff2, sizeof(MyBuff2));

    /*Instantiate Communication class object with configuration defined in Config.h file*/
    Communication Client2(ClientParam2);

    /*Buffer to be used for communication*/
    uint8_t MyBuff3[] = "Hi, this is Client2 writting, in Secure Communication..!", MyBuff4[100];

    /*Bio Write request from client*/
    Client2.BIOWrite(MyBuff3, sizeof(MyBuff3));

    /*Bio Read request from client*/
    Client2.BIORead(MyBuff4, sizeof(MyBuff4));

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

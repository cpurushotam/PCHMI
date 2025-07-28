#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>

/*Define below line only if target board is Rasp-Pi*/
#define CROSS_COMPILE

using namespace std;

char buffer[100] = {0};

char port[]="8080";

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    SSL_CTX *ctx = SSL_CTX_new(TLS_method());
        SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
        SSL_CTX_set_ciphersuites(ctx,"TLS_AES_256_GCM_SHA384");

#ifdef CROSS_COMPILE
        if (SSL_CTX_use_certificate_file(ctx, "/home/pi/server-certificate.pem", SSL_FILETYPE_PEM) <= 0) {
#else
        if (SSL_CTX_use_certificate_file(ctx, "/home/kshitij/Desktop/server-certificate.pem", SSL_FILETYPE_PEM) <= 0) {
#endif
           cout<< "Error loading server certificate" << endl;
           return (0);
        }

#ifdef CROSS_COMPILE
        if (SSL_CTX_use_PrivateKey_file(ctx, "/home/pi/server-private-key.pem", SSL_FILETYPE_PEM) <= 0) {
#else
        if (SSL_CTX_use_PrivateKey_file(ctx, "/home/kshitij/Desktop/server-private-key.pem", SSL_FILETYPE_PEM) <= 0) {
#endif
            cout<<"Error loading server private key"<<endl;
            return (0);
        }


        BIO *bio = BIO_new_accept(port);

//         check port access
        if (BIO_do_accept(bio) <= 0) {
            cout<<"Error opening port"<<endl;
            return (0);
            }

        cout << "server started on " << port << endl;

//         wait for connection from client
        if (BIO_do_accept(bio) <= 0) {
                cout<<"Error connection from client"<<endl;
                return (0);
            }

//         get BIO of client connection
        BIO *connection_bio = BIO_pop(bio);

//         create SSL BIO
        BIO *ssl_bio = BIO_new_ssl(ctx,0);

//         chain SSL BIO with client connection socket BIO
        BIO_push(ssl_bio,connection_bio);

//         perform blocking read
        int len = BIO_read(ssl_bio, buffer, sizeof(buffer));

        if(len > 0)
        {
            cout << std::string(buffer, len) <<endl;
        }

//        return (0);

    return app.exec();
}

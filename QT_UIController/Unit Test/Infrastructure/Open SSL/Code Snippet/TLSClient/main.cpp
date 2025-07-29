#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <string>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
//#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/crypto.h>
#include <openssl/err.h>

/*Define below line only if target board is Rasp-Pi*/
#define CROSS_COMPILE

using namespace std;

void verify_the_certificate(SSL *ssl, const std::string& expected_hostname);

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

//     create context for client
        SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());

        SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);

        SSL_CTX_set_ciphersuites(ctx,"TLS_AES_256_GCM_SHA384");

#ifdef CROSS_COMPILE
//         set trusted certificate
        if (!SSL_CTX_load_verify_locations(ctx,"/home/pi/server-certificate.pem",NULL))
#else
        if (!SSL_CTX_load_verify_locations(ctx,"/path/for/server-certificate.pem",NULL))
#endif
        {
            cout << "SSL_CTX_load_verify_locations failed" << endl;
            return (0);
        }

#ifdef CROSS_COMPILE
//         connect to server
        BIO *connection_bio = BIO_new_connect("192.168.1.100:8080");
#else
        BIO *connection_bio = BIO_new_connect("127.0.0.1:8080");
#endif
         if (BIO_do_connect(connection_bio) <= 0) {
             cout << "Error connecting to port" << endl;
             return (0);
            }

//         create SSL bio
        BIO *ssl_bio = BIO_new_ssl(ctx,1);

//         chain SSL bio to socket connection bio
        BIO_push(ssl_bio, connection_bio);

//         get SSL session
        SSL *ssl = nullptr;
        BIO_get_ssl(ssl_bio, &ssl);

        if (ssl == nullptr) {
            cout<<"Error in BIO_get_ssl"<<endl;
            return (0);
        }

#ifdef CROSS_COMPILE
//         set hostname
        SSL_set_tlsext_host_name(ssl,"192.168.1.100");
#else
        SSL_set_tlsext_host_name(ssl,"127.0.0.1");
#endif
        cout << "client connected, performing TLS handshake..." << endl;

//         perform TLS handshake
        if (BIO_do_handshake(ssl_bio) <= 0) {
            cout << "Error in TLS handshake" << endl;
        }

#ifdef CROSS_COMPILE
//         verify server certificate
        verify_the_certificate(ssl, "192.168.1.100");
#else
        verify_the_certificate(ssl, "127.0.0.1");
#endif
        cout << "verified server certificate successfully" << endl;

//         send msg to server
        string request = "Hello from client";
        BIO_write(ssl_bio, request.data(), request.size());

        cout << "data sent to server"<<endl;

        return app.exec();
//        return (0);
    }

    void verify_the_certificate(SSL *ssl, const std::string& expected_hostname)
    {
        int err = SSL_get_verify_result(ssl);
        if (err != X509_V_OK) {
            const char *message = X509_verify_cert_error_string(err);
            fprintf(stderr, "Certificate verification error: %s (%d)\n", message, err);
            exit(1);
        }
        X509 *cert = SSL_get_peer_certificate(ssl);
        if (cert == nullptr) {
            fprintf(stderr, "No certificate was presented by the server\n");
            exit(1);
        }
        if (X509_check_host(cert, expected_hostname.data(), expected_hostname.size(), 0, nullptr) != 1) {
            fprintf(stderr, "Certificate verification error: Hostname mismatch\n");
            exit(1);
        }

}

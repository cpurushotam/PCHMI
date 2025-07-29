#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include "CommonHeader.h"

/*Class Communication definition*/
class Communication
{

private:
    /*Structure variable declaration to store config defined during class instantiation*/
    CommConfig GetInterfaceConfig;

public:
    /*Contructor declarion*/
    Communication(CommConfig InterfaceConfig);

    /*Destructor declarion*/
    ~Communication();

    /*Public variables*/
    BIO *unsec_bio;
    BIO *sec_bio;
    BIO *connection_bio;
    BIO *ssl_bio;
    SSL *ssl;
    SSL_CTX *ctx;
    X509 *cert;

    /*Public methods*/
    void BIORead(uint8_t * const buff, const int size);
    void BIOWrite(const uint8_t *const buff, const int size);
};
#endif // COMMUNICATION_H

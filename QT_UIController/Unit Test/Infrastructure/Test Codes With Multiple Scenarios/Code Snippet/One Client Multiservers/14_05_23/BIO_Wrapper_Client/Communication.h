/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
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

#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <regex>

#include "CommonHeader.h"

/*Class Communication definition*/
class Communication
{

private:
    /*Structure variable declaration to store config defined during class instantiation*/
    CommConfig m_GetInterfaceConfig;

public:
    /*Contructor declarion*/
    Communication(CommConfig InterfaceConfig);

    /*Destructor declarion to perform cleanup activity*/
    ~Communication();

    /*Public variables*/
    BIO *sec_bio;
    BIO *connection_bio;
    BIO *ssl_bio;
    SSL *ssl;
    SSL_CTX *ctx;
    X509 *cert;

    /*Public methods*/
    /*To perform read activity from respective connected peer*/
    int BIORead(uint8_t * const buff, const int size);
    /*To perform write activity to respective connected peer*/
    int BIOWrite(const uint8_t *const buff, const int size);
    /*Fetch the status of communication*/
    void GetCommStatus(int ErrorType);

    /*To verify each parameter provided under config.h file*/
    bool IsConfigValid (CommConfig InterfaceConfigVal);
    /*Configure server for non secure communication*/
    void NonSecureServerConfiguration (void);
    /*Configure client for non secure communication*/
    void NonSecureClientConfiguration (void);
    /*SecureConfigurationSetup performs below prerequisites for secure communication :
    1. Create new SSL object
    2. Set protocol version to be used
    3. Select ciphersuite to be used
    4. Load the certificates and private keys into the SSL object
    5. Set the default password callback called when loading/storing a PEM certificate with encryption
    6. Set trusted certificate*/
    void SecureConfigurationSetup(void);
    /*Configure server for secure communication*/
    void SecureServerConfiguration (void);
    /*Configure client for secure communication*/
    void SecureClientConfiguration (void);
    /*Check each parameter configured is correcet or not*/
    bool IsValid(const char ParamString[], ConfigInputs Type);
};
#endif // COMMUNICATION_H

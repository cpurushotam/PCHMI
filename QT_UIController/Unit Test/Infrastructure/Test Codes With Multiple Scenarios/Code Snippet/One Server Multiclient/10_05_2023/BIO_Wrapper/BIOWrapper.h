/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file works as BIO wrapper for all non secure and secure
    communication reuirements prerequisites.
***************************************************************************/
#ifndef BIOWRAPPER_H
#define BIOWRAPPER_H

#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include <exception>

#include <fstream>
#include <stdio.h>
#include <regex>

/*Common interface file for BIO utility*/
#include "BIOWrapperCommon.h"

/*Retry counter value*/
const int RETRYCOUNT = 3;

/*Class BIOWrapper definition*/
class BIOWrapper
{

private:
    /*Structure variable declaration to store config defined during class instantiation*/
    CommConfig *m_GetInterfaceConfig;

    /*Private variables*/
    BIO *bio;
    BIO *connection_bio;
    BIO *comm_bio;
    SSL *ssl;
    SSL_CTX *ctx;
    X509 *cert;
    CommStatus CommStatusResult;

    /*Private methods*/
    /*To verify each parameter provided under config.h file*/
    bool IsConfigValid (CommConfig *InterfaceConfigVal);
    /*Configure server for non secure communication*/
    void NonSecureServerConfiguration (void);
    /*Configure client for non secure communication*/
    void NonSecureClientConfiguration (void);
    /*Perform pre-requisite for secure communication establishment*/
    void SecureConfigurationSetup(void);
    /*Configure server for secure communication*/
    void SecureServerConfiguration (void);
    /*Configure client for secure communication*/
    void SecureClientConfiguration (void);
    /*Function to update secure communication status*/
    void SSLErrorStatusUpdate(int Value);

public:
    /*Contructor declarion*/
    BIOWrapper(CommConfig *InterfaceConfig);

    /*Destructor declarion to perform cleanup activity*/
    ~BIOWrapper();

    /*Public methods*/
    /*To perform read activity from respective connected peer*/
    int BIORead(uint8_t * const buff, const int size);
    /*To perform write activity to respective connected peer*/
    int BIOWrite(const uint8_t *const buff, const int size);
    /*Fetch the status of communication*/
    CommStatus GetCommStatus(void);

};
#endif // BIOWRAPPER_H

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

/*Enum to define role either SERVER or CLIENT*/
enum Role
{
    SERVER = 0,
    CLIENT
};

/*Enums to define status of communication*/
enum CommStatus
{
    STATUS_SSL_ERROR_NONE = 0        ,
    STATUS_SSL_ERROR_SSL             ,
    STATUS_SSL_ERROR_WANT_READ       ,
    STATUS_SSL_ERROR_WANT_WRITE      ,
    STATUS_SSL_ERROR_WANT_X509_LOOKUP,
    STATUS_SSL_ERROR_SYSCALL         ,
    STATUS_SSL_ERROR_ZERO_RETURN     ,
    STATUS_SSL_ERROR_WANT_CONNECT    ,
    STATUS_SSL_ERROR_WANT_ACCEPT     ,
    STATUS_SSL_ERROR_WANT_ASYNC      ,
    STATUS_SSL_ERROR_WANT_ASYNC_JOB
};

/*Enum to define TLS Version to be used*/
enum TLSVersions
{
    TLS1_VERSION_0  = 0x0301,
    TLS1_VERSION_1  = 0x0302,
    TLS1_VERSION_2  = 0x0303,
    TLS1_VERSION_3  = 0x0304
};

/*Enum for configuration inputs in config file*/
enum ConfigInputs
{
    ConfigRole = 1,
    ConfigExpectedHostName,
    ConfigSelfCertificate,
    ConfigSelfPrivateKey,
    ConfigCACertificate,
    ConfigPeerName,
    ConfigPassKey
};

/*Structure to define secure communication parametrs required*/
struct SecureConfig
{
    bool IsEnable ;                /*Use this to enable secure configuration*/
    const char*  SelfCertificate; /*Use this to configure Self Certificate*/
    const char*  SelfPrivateKey;  /*Use this to configure Self Private Key*/
    const char*  CACertificate;   /*Use this to configure CA Certificate*/
    const char*  ExpectedPeerName;/*Use this to configure Expected Peer Name*/
    const char*  PassKey;         /*Use this to configure Passkey*/
    TLSVersions  TLSVersionIs;    /*Use this to configure TLS Version*/
    const char*  CipherSuite;     /*Use this to select Ciphersuite*/
};

/*Structure to define communication parametrs required*/
struct CommConfig
{
    Role roleIs;                        /*Use this for defining the role i.e either Server or Client*/
    const char*  DestinationIPandPort;  /*Use this for configuring destination IP and Port*/
    string  ExpectedHostName;           /*Use this to configure Expected Host Name*/
    bool IsBlocking;                    /*Use this to configure Blocking or Non Blocking mode*/
    SecureConfig SecureConfigParam;     /*Use this structure to configure secure communications parameters*/
};

#endif // COMMONHEADER_H

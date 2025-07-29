/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H
#include "Communication.h"
#include "CommonHeader.h"

/*Configuration parameters to be initialized during communication object instantiation*/
CommConfig ServerParam = {
    .roleIs = SERVER,                         /*Use this for defining the role i.e either Server or Client*/
    .DestinationIPandPort = "localhost:8080", /*Use this for configuring destination IP and Port*/
    .ExpectedHostName = "BransonHMI",         /*Use this to configure Expected Host Name*/
    .IsBlocking = true,                       /*Use this to configure Blocking or Non Blocking mode*/
    .SecureConfigParam = {
        .IsEnable = true,                      /*Use this to enable secure configuration*/
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-cert.pem",/*Use this to configure Self Certificate*/
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-key.pem",/*Use this to configure Self Private Key*/
        .CACertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/ca-cert.pem",/*Use this to configure CA Certificate*/
        .ExpectedPeerName = "BransonHMI",/*Use this to configure Expected Peer Name*/
        .PassKey = "ServerPass",         /*Use this to configure Passkey*/
        .TLSVersionIs = TLS1_VERSION_3,  /*Use this to configure TLS Version*/
        .CipherSuite = "TLS_AES_256_GCM_SHA384"/*Use this to select Ciphersuite*/
    }
};

/*Configuration parameters to be initialized during communication object instantiation*/
CommConfig ServerParam2 = {
    .roleIs = SERVER,                         /*Use this for defining the role i.e either Server or Client*/
    .DestinationIPandPort = "localhost:8081", /*Use this for configuring destination IP and Port*/
    .ExpectedHostName = "BransonHMI",         /*Use this to configure Expected Host Name*/
    .IsBlocking = true,                       /*Use this to configure Blocking or Non Blocking mode*/
    .SecureConfigParam = {
        .IsEnable = true,                      /*Use this to enable secure configuration*/
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script2/server-cert.pem",/*Use this to configure Self Certificate*/
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script2/server-key.pem",/*Use this to configure Self Private Key*/
        .CACertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script2/ca-cert.pem",/*Use this to configure CA Certificate*/
        .ExpectedPeerName = "BransonHMI",/*Use this to configure Expected Peer Name*/
        .PassKey = "ServerPass",         /*Use this to configure Passkey*/
        .TLSVersionIs = TLS1_VERSION_3,  /*Use this to configure TLS Version*/
        .CipherSuite = "TLS_AES_256_GCM_SHA384"/*Use this to select Ciphersuite*/
    }
};


#endif // CONFIG_H


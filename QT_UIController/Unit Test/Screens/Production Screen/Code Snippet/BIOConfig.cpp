/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes configurations inputes needed for establishment of
    communication.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 22/05/2023 - Initial version, configuration for server
 ***************************************************************************/
#include "BIOConfig.h"

/*Configuration parameters to be initialized during communication object instantiation*/

std::vector<CommConfig> ClientParam = {
    {
        .RoleIs = CLIENT,                                             /*Use this for defining the role i.e either Server or Client*/
        .DestinationIPandPort = "localhost:8080",                     /*Use this for configuring destination IP and Port*/
        .IsBlocking = false,                                           /*Use this to configure Blocking or Non Blocking mode*/
        .SecureConfigParam = {
            .IsEnable = true,                                         /*Use this to enable secure configuration*/
            .ExpectedPeerName = "BransonSC",                         /*Use this to configure Expected Peer Name*/
            .SelfCertificate = "../SSL_Certificates/Certificates/client-cert.pem", /*Use this to configure Self Certificate*/
            .SelfPrivateKey = "../SSL_Certificates/Certificates/client-key.pem",   /*Use this to configure Self Encrypted Private Key*/
            .CACertificate = "../SSL_Certificates/Certificates/ca-cert.pem",       /*Use this to configure CA Certificate*/
            .PassKey = "ClientPass1$",                                 /*Use this to configure the password to be used during decryption of private key.
                                                                                Please refer above Build Machine Requirements for more details.*/
            .TLSVersionIs = TLS1_VERSION_3,                           /*Use this to configure TLS Version*/
            .CipherSuite = "TLS_AES_256_GCM_SHA384"                   /*Use this to select Ciphersuite. A cipher suite is a set of cryptographic algorithms.
                                                                                The TLS/SSL protocols use algorithms from a cipher suite to create keys and encrypt information*/
        }
    },
    {
        .RoleIs = CLIENT,                                             /*Use this for defining the role i.e either Server or Client*/
        .DestinationIPandPort = "localhost:8081",                     /*Use this for configuring destination IP and Port*/
        .IsBlocking = false,                                           /*Use this to configure Blocking or Non Blocking mode*/
        .SecureConfigParam = {
            .IsEnable = true,                                         /*Use this to enable secure configuration*/
            .ExpectedPeerName = "BransonSC",                         /*Use this to configure Expected Peer Name*/
            .SelfCertificate = "../SSL_Certificates/Certificates/client-cert.pem", /*Use this to configure Self Certificate*/
            .SelfPrivateKey = "../SSL_Certificates/Certificates/client-key.pem",   /*Use this to configure Self Encrypted Private Key*/
            .CACertificate = "../SSL_Certificates/Certificates/ca-cert.pem",       /*Use this to configure CA Certificate*/
            .PassKey = "ClientPass1$",                                 /*Use this to configure the password to be used during decryption of private key.
                                                                                    Please refer above Build Machine Requirements for more details.*/
            .TLSVersionIs = TLS1_VERSION_3,                           /*Use this to configure TLS Version*/
            .CipherSuite = "TLS_AES_256_GCM_SHA384"                   /*Use this to select Ciphersuite. A cipher suite is a set of cryptographic algorithms.
                                                                                    The TLS/SSL protocols use algorithms from a cipher suite to create keys and encrypt information*/
        }
    },
    {
        .RoleIs = CLIENT,                                             /*Use this for defining the role i.e either Server or Client*/
        .DestinationIPandPort = "localhost:8082",                     /*Use this for configuring destination IP and Port*/
        .IsBlocking = false,                                           /*Use this to configure Blocking or Non Blocking mode*/
        .SecureConfigParam = {
            .IsEnable = true,                                         /*Use this to enable secure configuration*/
            .ExpectedPeerName = "BransonSC",                         /*Use this to configure Expected Peer Name*/
            .SelfCertificate = "../SSL_Certificates/Certificates/client-cert.pem", /*Use this to configure Self Certificate*/
            .SelfPrivateKey = "../SSL_Certificates/Certificates/client-key.pem",   /*Use this to configure Self Encrypted Private Key*/
            .CACertificate = "../SSL_Certificates/Certificates/ca-cert.pem",       /*Use this to configure CA Certificate*/
            .PassKey = "ClientPass1$",                                 /*Use this to configure the password to be used during decryption of private key.
                                                                                    Please refer above Build Machine Requirements for more details.*/
            .TLSVersionIs = TLS1_VERSION_3,                           /*Use this to configure TLS Version*/
            .CipherSuite = "TLS_AES_256_GCM_SHA384"                   /*Use this to select Ciphersuite. A cipher suite is a set of cryptographic algorithms.
                                                                                    The TLS/SSL protocols use algorithms from a cipher suite to create keys and encrypt information*/
        }
    }
};




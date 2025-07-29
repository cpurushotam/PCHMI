/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes configurations inputes needed for establishment of
    communication.
***************************************************************************/
#ifndef BIOCONFIG_H
#define BIOCONFIG_H
/*Common interface file for BIO utility*/
#include "BIOWrapperCommon.h"

/*********************************TO DO*************************************
 Build Machine Requirements :

  - Build machine holds encrypted private CA key and responsible for code, keys, certificate build activities for client/server.
  - Build machine shall be restricted for access to trusted administrator and possibly not connected to any outside network.
  - Build procedure shall be automated and no human interaction involved.
  - CA private key shall be used to sign public certificates of server/client, and own public certificate (self-signed).
  - Private key for server and client shall be generated, encrypted and deployed in target binary for each new build.
    Once final binary is ready, then these keys should be deleted from build machine.
  - Passkey for encrypted client/server private keys shall be generated randomly during build and deployed in binary itself.
    Build machine should not store this passkey once build is complete.
  - Build machine shall record build results - along with hash of the public certificates and corresponding private keys.
    No confidential information shall be present in build results.
  - Same build machine can be used for secure boot build procedure, OPC_UA, LDAP (TBD).
  - Use of HSM module or USB crypto tokens can be considered for better security of CA private key to be explored (Optional).
**************************************************************************/

/*Configuration parameters to be initialized during communication object instantiation*/

CommConfig ClientParam = {
    .RoleIs = CLIENT,                                             /*Use this for defining the role i.e either Server or Client*/
    .DestinationIPandPort = "localhost:8080",                     /*Use this for configuring destination IP and Port*/
    .IsBlocking = true,                                           /*Use this to configure Blocking or Non Blocking mode*/
    .SecureConfigParam = {
        .IsEnable = false,                                         /*Use this to enable secure configuration*/
        .ExpectedPeerName = "BransonSC",                         /*Use this to configure Expected Host Name*/
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script3/client-cert.pem", /*Use this to configure Self Certificate*/
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script3/client-key.pem",   /*Use this to configure Self Encrypted Private Key*/
        .CACertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script3/ca-cert.pem",       /*Use this to configure CA Certificate*/
        .PassKey = "ClientPass1$",                                  /*Use this to configure the password to be used during decryption of private key.
                                                                    Please refer above Build Machine Requirements for more details.*/
        .TLSVersionIs = TLS1_VERSION_3,                           /*Use this to configure TLS Version*/
        .CipherSuite = "TLS_AES_256_GCM_SHA384"                   /*Use this to select Ciphersuite*/
    }
};

CommConfig ClientParam2 = {
    .RoleIs = CLIENT,                                             /*Use this for defining the role i.e either Server or Client*/
    .DestinationIPandPort = "localhost:8081",                     /*Use this for configuring destination IP and Port*/
    .IsBlocking = false,                                           /*Use this to configure Blocking or Non Blocking mode*/
    .SecureConfigParam = {
        .IsEnable = false,                                         /*Use this to enable secure configuration*/
        .ExpectedPeerName = "BransonSC",                         /*Use this to configure Expected Host Name*/
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script4/client-cert.pem", /*Use this to configure Self Certificate*/
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script4/client-key.pem",   /*Use this to configure Self Encrypted Private Key*/
        .CACertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script4/ca-cert.pem",       /*Use this to configure CA Certificate*/
        .PassKey = "ClientPass1$",                                  /*Use this to configure the password to be used during decryption of private key.
                                                                    Please refer above Build Machine Requirements for more details.*/
        .TLSVersionIs = TLS1_VERSION_3,                           /*Use this to configure TLS Version*/
        .CipherSuite = "TLS_AES_256_GCM_SHA384"                   /*Use this to select Ciphersuite*/
    }
};
#endif // BIOCONFIG_H


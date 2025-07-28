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
 rev2: 21/08/2023 - Common configuration for all peers of ACE_PRO
                    Platform.
 ***************************************************************************/

#ifndef BIOCONFIG_ACE_PRO_H
#define BIOCONFIG_ACE_PRO_H

#include "BIOConfig.h"

/*Configuration parameters */
CommConfig ASCAceProParam = {
    .RoleIs = CLIENT,                               /*Use this for defining the role i.e either Server or Client*/
    .DestinationIPandPort = {'8','0','8','0'},      /*Use this for configuring destination Port, IP will configure by WDS */
    .IsBlocking = false,                            /*Use this to configure Blocking or Non Blocking mode*/
    .SecureConfigParam = {
        .IsEnable = true,                           /*Use this to enable secure configuration*/
        .ExpectedPeerName = "BransonSC",            /*Use this to configure Expected Peer Name*/
        .SelfCertificate = "../Developer_Certificates/developer-client-cert.pem",    /*Use this to configure Self Certificate*/
        .SelfPrivateKey = "../Developer_Certificates/developer-client-key.pem",      /*Use this to configure Self Encrypted Private Key*/
        .CACertificate = "../Developer_Certificates/developer-ca-cert.pem",          /*Use this to configure CA Certificate*/
        .PassKey = "../Developer_Certificates/developer-client-data.enc",            /*Use this to configure the password to be used during decryption of private key.*/
        .TLSVersionIs = TLS1_VERSION_3,             /*Use this to configure TLS Version*/
        .CipherSuite = "TLS_AES_256_GCM_SHA384"     /*Use this to select Ciphersuite. A cipher suite is a set of cryptographic algorithms.
                                                      The TLS/SSL protocols use algorithms from a cipher suite to create keys and encrypt information*/
    }
};

#endif // BIOCONFIG_ACE_PRO_H


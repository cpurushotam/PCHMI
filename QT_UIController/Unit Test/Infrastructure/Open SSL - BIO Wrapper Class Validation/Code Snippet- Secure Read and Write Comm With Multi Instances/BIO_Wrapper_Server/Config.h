#ifndef CONFIG_H
#define CONFIG_H
#include "Communication.h"
#include "CommonHeader.h"

/*Configuration parameters to be initialized during communication object instantiation*/
CommConfig ServerParam = {
    .roleIs = SERVER,
    .DestinationIPandPort = "localhost:8080",
    .ExpectedHostName = "BransonHMI",
    .IsBlocking = true,
    .ConfigParam = {
        .IsEnable = true,
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-cert.pem",
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-key.pem",
        .PeerCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/ca-cert.pem",
        .PeerName = "BransonHMI",
        .PassKey = "ServerPass",
        .TLSVersionIs = TLS1_VERSION_3,
        .CipherSuit = "TLS_AES_256_GCM_SHA384"
    }
};

/*Configuration parameters to be initialized during communication object instantiation*/
CommConfig ServerParam2 = {
    .roleIs = SERVER,
    .DestinationIPandPort = "localhost:8081",
    .ExpectedHostName = "BransonHMI",
    .IsBlocking = true,
    .ConfigParam = {
        .IsEnable = true,
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-cert.pem",
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/server-key.pem",
        .PeerCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/ca-cert.pem",
        .PeerName = "BransonHMI",
        .PassKey = "ServerPass",
        .TLSVersionIs = TLS1_VERSION_3,
        .CipherSuit = "TLS_AES_256_GCM_SHA384"
    }
};
#endif // CONFIG_H


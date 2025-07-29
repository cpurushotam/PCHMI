#ifndef CONFIG_H
#define CONFIG_H
#include "Communication.h"
#include "CommonHeader.h"

/*Configuration parameters to be initialized during communication object instantiation*/
CommConfig ClientParam = {
    .roleIs = CLIENT,
    .DestinationIPandPort = "localhost:8080",
    .ExpectedHostName = "BransonSC",
    .IsBlocking = true,
    .ConfigParam = {
        .IsEnable = true,
        .SelfCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/client-cert.pem",
        .SelfPrivateKey = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/client-key.pem",
        .PeerCertificate = "/home/kshitij/Desktop/BIO_Wrapper_Test_Script/ca-cert.pem",
        .PeerName = "BransonSC",
        .PassKey = "ClientPass",
        .TLSVersionIs = TLS1_VERSION_3,
        .CipherSuit = "TLS_AES_256_GCM_SHA384"
    }
};

#endif // CONFIG_H


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

/*Enum to define TLS Version to be used*/
enum TLSVersions
{
    TLS1_VERSION_0  = 0x0301,
    TLS1_VERSION_1  = 0x0302,
    TLS1_VERSION_2  = 0x0303,
    TLS1_VERSION_3  = 0x0304
};

/*Structure to define secure communication parametrs required*/
struct SecureConfigParam
{
    int IsEnable ;
    const char*  SelfCertificate;
    const char*  SelfPrivateKey;
    const char*  PeerCertificate;
    const char*  PeerName;
    const char*  PassKey;
    TLSVersions  TLSVersionIs;
    const char*  CipherSuit;
};

/*Structure to define communication parametrs required*/
struct CommConfig
{
    Role roleIs;
    const char*  DestinationIPandPort;
    string  ExpectedHostName;
    bool IsBlocking;
    SecureConfigParam ConfigParam;
};

#endif // COMMONHEADER_H

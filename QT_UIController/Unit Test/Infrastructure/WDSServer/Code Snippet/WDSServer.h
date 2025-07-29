/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares WDSServer Class - responsible for auto discovery of welder

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.

***************************************************************************/

#ifndef WDSSERVER_H
#define WDSSERVER_H

/* QT related header file */
#include <QThread>

/* Standard header file */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* socket related header file */
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "logger.h"

static constexpr uint16_t BUFF_SIZE             = 1024;             /* Total buffer size for Tx/Rx meassgae. */
static constexpr uint16_t DISCOVERY_CODE        = 10;               /* Disccovery code for brodacast packet */
static constexpr uint16_t WDS_PORT              = 8081;             /* Port for WDS Server */
static constexpr uint16_t BIO_PORT              = 8080;             /* Port for BIO Wrapper */
static constexpr uint16_t IP_ADDR_SIZE          = 20;               /* size of ip address */
static constexpr char     BROADCAST_IP_ADDR []  = "192.168.1.255";  /* Broadcast ip address */
static constexpr long       BROADCAST             = '1';            /* To Enable/Disable broadcast communication */
// This is statcally configurable
// Max welders size is depend on product specific requirement.
static constexpr uint8_t  MAX_WELDERS           = 4;

// Connection status of peer
enum CONN_STATUS
{
    NEW         = 0,        /* New Peer(welder) Discovered */
    INPROCESS,              /* Communication in process with peer(welder) */
    SUCCESS,                /* Peer (Weldr) connected successfully */
    BLACKLIST               /* Failed to connect with Peer (Weldr) */
};

/* Structure declaration for broadcast/receive packet */
struct AuthenticationMsg {
    uint16_t    DiscoveryCode;  /* Discovery code for identfy auto welder discovery */
    int         AuthNumber;     /* Random number to autheticate welder */
};

struct PeerConnDetails
{
    uint16_t    Id;                     /* unique id to identify welder */
    char        IpAddr[IP_ADDR_SIZE];   /* IP address of Welder */
    uint16_t    Port;                   /* BIO Port for BIO Wrapper */
    CONN_STATUS ConnStatus;             /* Conection status of welder */
};

/* WDSServer Class definition */
class WDSServer : public QThread
{
    Q_OBJECT
    /* Socket file descriptor */
    int                 m_SockFd;

    /* lenght of addres structure */
    unsigned int        m_AddrLen;

    /* Declaration of broadcast peer and self address structure */
    struct sockaddr_in  m_BroadcastAddr, m_PeerAddr, m_SelfAddr;

    /* Broadcast and peer response message to send and recive packet */
    AuthenticationMsg  *m_BrodcastMsg, *m_PeerResponseMsg;

    /* Rx Buffer to store recived messages */
    uint8_t m_RxBuff [BUFF_SIZE]={0};

    /* Tx Buffer to send broadcast message */
    uint8_t m_TxBuff [BUFF_SIZE]={0};

    static std::map<int, PeerConnDetails> m_DiscoveryInfoTable;

    /* List of blacklisted welder */
    static std::vector<std::string> m_WelderBlackList;

    static uint16_t m_FreeWelders[MAX_WELDERS];

    /* locks for Read/write of DiscoveryInfoTable */
    static pthread_mutex_t m_DiscoveryInfoMutex;

    static uint16_t m_TotalAvailWelders;

    // log identifier
    size_t m_LogId;

    // log buffer
    char m_LogBuffer[buff_size_config]={0};

    int ToggleRandomNumber(int n);

signals:
    void PeerConnected(char *IpAddr);

public:

    /* Constructor declaration */
    WDSServer();

    /* Destructor declaration to perform cleanup activity */
    ~WDSServer();

    /* Implemention of logic for auto discovery of welder. */
    void run();

    static void SetPeerConnStatus(int WelderId, CONN_STATUS ConnStatus);

    static void RemovePeerInfo(int WelderId);
};

#endif // WDSSERVER_H

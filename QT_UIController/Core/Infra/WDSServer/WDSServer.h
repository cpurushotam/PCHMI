/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares WDSServer Class - responsible for auto discovery of welder

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.
 rev2: 23/11/2023 - Added API to return IP address of active welder.

***************************************************************************/

#ifndef WDSSERVER_H
#define WDSSERVER_H

/* QT related header file */
#include <QThread>

/* Standard header file */
#include <iostream>
#include <stdlib.h>
#include <string.h>


#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else

/* socket related header file */
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "DataLogger.h"
#include "version_common.h"
#include "HMI_ASC_comms.h"
#include "HMIDeviceSupport.h"

// This is statcally configurable
// Max welders size is depend on product specific requirement.
static constexpr uint16_t  CONFIG_MAX_WELDERS    = 4;

// Connection status of peer
enum CONN_STATUS
{
    NEW         = 0,        /* New Peer(welder) Discovered */
    INPROCESS,              /* Communication in process with peer(welder) */
    SUCCESS,                /* Peer (Weldr) connected successfully */
    BLACKLIST               /* Failed to connect with Peer (Weldr) */
};

/* WDSServer Class definition */
class WDSServer : public QThread
{
    // Declaration of Q_OBJECT for signals and slots mechanism
    Q_OBJECT

    // Static pointer which will points to the instance of this class
    static WDSServer* WdsInstance;

    // macro declaration
    static constexpr uint16_t BUFF_SIZE             = 100;              /* Total buffer size for Tx/Rx meassgae. */
    static constexpr uint16_t DISCOVERY_CODE        = 10;               /* Disccovery code for brodacast packet */
	static constexpr uint16_t WDS_PORT_SERVER   = 8083;			/* Port for WDS Server, server listens on this port and writes on port WDS_PORT_CLIENT */
	static constexpr uint16_t WDS_PORT_CLIENT  = 8084;			/* Port for WDS Client, client listens on this port and writes on port WDS_PORT_SERVER */
    static constexpr char     BROADCAST_IP_ADDR []  = "192.168.1.255";  /* Broadcast ip address */
    static constexpr long     BROADCAST             = '1';              /* To Enable/Disable broadcast communication */
    static constexpr uint16_t IP_ADDR_SIZE          = 20;               /* size of ip address */

    enum WDS_STATE
    {
        WDS_BROADCAST = 0,
        WDS_DISCOVERY,
        WDS_IDEAL
    };
    
    /* Structure declaration for broadcast packet */
    typedef struct {
        uint16_t    DiscoveryCode;                                  /* Discovery code for identify auto welder discovery */
        uint32_t    AuthNumber;                                     /* Random number to authenticate welder */
        char        FirmwareVersion[FIRMWARE_VERSION_SIZE];         /* Firmware version string */
        HMIDeviceSupport::HMI_DEVICE_SUPPORT    HmiType;										/* Enum for HMI type */
    } AuthenticationMsg;

    // Declaration of PeerConnDetails structure
    typedef struct {
        uint16_t    Id;                                             /* unique id to identify welder */
        uint16_t    Port;                                           /* Port of Welder */
        char        IpAddr[IP_ADDR_SIZE];                           /* IP address of Welder */
        CONN_STATUS ConnStatus;                                     /* Conection status of welder */
    } __attribute__((packed)) PeerConnDetails;

    // Members variable defined for auto welder discovery service feature.
    int                 m_SockFd;                                               /* Socket file descriptor */
    unsigned int        m_AddrLen;                                              /* lenght of addres structure */

    struct sockaddr_in  m_BroadcastAddr, m_PeerAddr, m_SelfAddr;                /* Declaration of broadcast peer and self address structure */
    AuthenticationMsg  *m_ptrBrodcastMsg, *m_ptrPeerResponseMsg;                /* Broadcast and peer response message to send and recive packet */

    char                m_RxBuff [BUFF_SIZE]={0};                               /* Rx Buffer to store recived messages */
    char                m_TxBuff [BUFF_SIZE]={0};                               /* Tx Buffer to send broadcast message */

    std::map<int, PeerConnDetails>  m_DiscoveryInfoTable;                       /* Discovery Info Table to store connected peer's details */
    std::vector<std::string>        m_WelderBlackList;                          /* List of blacklisted welder */

    uint16_t            m_FreeWelders[CONFIG_MAX_WELDERS];                      /* Array to identify which welder is available */
#ifdef _WIN32
    mutable std::mutex m_DiscoveryInfoMutex;
#else
    pthread_mutex_t     m_DiscoveryInfoMutex = PTHREAD_MUTEX_INITIALIZER;       /* locks for Read/write of DiscoveryInfoTable */
#endif

    // Members variable defined for logger feature.
    size_t              m_LogId;                                    /* log identifier */
    char                m_LogBuffer[buff_size_config]={0};          /* log buffer */

    /* Private Constructor and Destructor declaration  for singletone class */
    WDSServer();
    ~WDSServer();

    // Members function defined for auto welder discovery service feature.
    uint32_t ToggleRandomNumber(uint32_t n);                         /* Toggled random number */

    // Thread Function: Implemention of logic for auto discovery of welder.
    void run();
    
    //To compare HMI and ASC Major and Minor firmware versions
    bool CompareFirmwareMajorMinorVersions(const std::string& current);
    //To generate HMI firmware version major.minor.build.autos
    std::string GenerateHMIFirmwareVersionString();
    
    static const HMIDeviceSupport::HMI_DEVICE_SUPPORT IsPCHMI;

signals:
    // Send peer connected signal to HMI.
    void PeerConnected(uint16_t WelderId, char *IpAddr);

    // Send peer disconnected signal to HMI.
    void PeerDisconnected(char *IpAddr);

    //Send Firmware mismatch version signal to HMI.
    void IsFirmwareVersionMismatchChangeDetected(std::string MessageToBeDisplayed);

public:
    // Return Singletone instance of WDSServer class.
    static WDSServer* GetInstance();

    // Update status of connected peer's.
    void SetPeerConnStatus(uint16_t WelderId, CONN_STATUS ConnStatus);

    // Remove peer information from discovery info table.
    void UpdateDiscoveryInfoTable(uint16_t WelderId);

    // Return IP Address of specified welder id
    char* GetActiveWelderIPAddress(int WelderId);
};

#endif // WDSSERVER_H

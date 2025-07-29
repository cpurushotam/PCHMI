/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Implementation of WDSServer Class - responsible for auto discovery of welder

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.
 rev2: 23/11/2023 - Added API to return IP address of active welder.

***************************************************************************/
#include "WDSServer.h"
#include "CommPeerWrapper.h"
#include "PlatformConfig.h"
#include "HMIDeviceSupport.h"
#include <cstring>

#if defined(__linux__) && defined(__aarch64__)
    const  HMIDeviceSupport::HMI_DEVICE_SUPPORT    WDSServer::IsPCHMI = HMIDeviceSupport::LOCAL_HMI; // Raspberry Pi 64-bit ARM
#elif defined(__linux__) && defined(__arm__)
    const  HMIDeviceSupport::HMI_DEVICE_SUPPORT    WDSServer::IsPCHMI = HMIDeviceSupport::LOCAL_HMI; // Raspberry Pi 32-bit ARM 
#elif defined(__linux__)
    const  HMIDeviceSupport::HMI_DEVICE_SUPPORT    WDSServer::IsPCHMI = HMIDeviceSupport::PC_HMI; // Generic Linux x86/64   
#elif defined(_WIN32)
    const  HMIDeviceSupport::HMI_DEVICE_SUPPORT    WDSServer::IsPCHMI = HMIDeviceSupport::PC_HMI; // Windows x86/64 
#else
    const  HMIDeviceSupport::HMI_DEVICE_SUPPORT    WDSServer::IsPCHMI = HMIDeviceSupport::LOCAL_HMI; // Not Linux
#endif

/**************************************************************************//**
* @brief Defination of static variable
*******************************************************************************/
WDSServer* WDSServer::WdsInstance = nullptr;

/**************************************************************************//**
*
* \brief    - WDSServer class constructor Initialize below parameters:
             1. Initialize m_ptrBrodcastMsg and m_ptrPeerResponseMsg msg.
             2. Initialize address structure.
             3. Create UDP socket.
             4. Set socket option to broadcast.
             5. Socket set non-blocking mode.
             6. Filling self and m_BroadcastAddr address information and bind
                with m_BroadcastAddr address.
*
* \param    - None.
*
* \return   - None.
******************************************************************************/
WDSServer::WDSServer()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        throw std::runtime_error("WSAStartup failed");
    }
#endif
    // Initialize log ID
    this->m_LogId = Logger::enroll(this);

    m_ptrBrodcastMsg       = new AuthenticationMsg;
    m_ptrPeerResponseMsg   = new AuthenticationMsg;

    /* Initially all welders are available. */
    for (int i = 0; i < CONFIG_MAX_WELDERS; i++)
    {
        m_FreeWelders[i] = 1;
    }

    m_AddrLen = sizeof(m_SelfAddr);

    memset(&m_SelfAddr,      0, m_AddrLen);
    memset(&m_BroadcastAddr, 0, m_AddrLen);
    memset(&m_PeerAddr,      0, m_AddrLen);

    // Creating socket file descriptor
    m_SockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_SockFd < 0 )
    {
        throw std::runtime_error("socket creation failed");
    }

    // Log Alarm
    snprintf ( this->m_LogBuffer, buff_size_config, "WDS Server SockFd: %d", m_SockFd);
    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
#ifdef _WIN32
    if (setsockopt(m_SockFd, SOL_SOCKET, SO_BROADCAST, (const char*)&BROADCAST, sizeof(BROADCAST)) < 0)
#else
    if (setsockopt(m_SockFd, SOL_SOCKET, SO_BROADCAST, &BROADCAST, sizeof(BROADCAST)) < 0)
#endif
    {
        // raise error
        throw std::runtime_error("Failed to set socket broadcast");
    }

    const int enable = 1;
#ifdef _WIN32
    if (setsockopt(m_SockFd, SOL_SOCKET, SO_BROADCAST, (const char*)&enable, sizeof(enable)) < 0)
#else
    if (setsockopt(m_SockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
#endif
    {
        // raise error
        throw std::runtime_error("Failed to setsockopt SO_REUSEADDR");
    }

#ifdef _WIN32
    u_long mode = 1;
    if (ioctlsocket(m_SockFd, FIONBIO, &mode) == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        throw std::runtime_error("ioctlsocket FIONBIO failed, WSAGetLastError=" + std::to_string(err));
    }
#else
    // get default flags
    int flags = fcntl(m_SockFd, F_GETFL, 0);
    if(flags<0)
    {
        // raise error
        throw std::runtime_error( "Error: Flags during create socket");
    }

    // set non-blocking mode
    if(fcntl(m_SockFd, F_SETFL,flags | O_NONBLOCK) < 0)
    {
        // raise error
        throw std::runtime_error("Error: set own socket to non-blocking");
    }
#endif
    m_SelfAddr.sin_family      = AF_INET; // IPv4
    m_SelfAddr.sin_addr.s_addr = INADDR_ANY;
    m_SelfAddr.sin_port        = htons(WDS_PORT_SERVER);

    // Bind the socket with the self address
     if (bind(m_SockFd, (const struct sockaddr *)&m_SelfAddr, sizeof(m_SelfAddr)) < 0 )
     {
         throw std::runtime_error("Client bind failed");
     }

    // Filling broadcast address information
    m_BroadcastAddr.sin_family = AF_INET;
    m_BroadcastAddr.sin_port = htons(WDS_PORT_CLIENT);

#ifdef _WIN32
    m_BroadcastAddr.sin_addr.s_addr = inet_addr(BROADCAST_IP_ADDR);
    if (m_BroadcastAddr.sin_addr.s_addr == INADDR_NONE)
    {
        throw std::runtime_error("Error: Invalid IP format");
    }
#else
    if(inet_aton(BROADCAST_IP_ADDR, &m_BroadcastAddr.sin_addr) <0)
    {
        // raise error
        throw std::runtime_error("Error: Invalid IP format");
    }
#endif
}

/**************************************************************************//**
* \brief   - Toggle received random number
*
* \param   - uint32_t - Generated Random Number
*
* \return  - uint32_t - Toggled Random Number
******************************************************************************/
uint32_t WDSServer::ToggleRandomNumber(uint32_t RandomNumber)
{
    uint32_t Num = 1;
    while (Num <= RandomNumber) {
        RandomNumber = RandomNumber ^ Num;
        Num = Num << 1;
    }
    return RandomNumber;
}

/**************************************************************************//**
* \brief   - WDS Server thread function is responsible for auto discovery of welder.
*
* \param   - None
*
* \return  - None
******************************************************************************/
void WDSServer::run()
{
    int             status, RandomNumber;
    bool            FoundNewIP = true;
    PeerConnDetails ConnDetails;
    bool            IsWelderAvailable = false;
    uint16_t        WelderId=0;
    WDS_STATE       CurrentState = WDS_BROADCAST;

    while (1)
    {
        switch (CurrentState)
        {
            case WDS_BROADCAST:
            {
                if (m_DiscoveryInfoTable.size() < CONFIG_MAX_WELDERS)
                {
                    // Generate random number
                    srand(time(0));
                    RandomNumber = rand()%10000;
                    HMIDeviceSupport::HMI_DEVICE_SUPPORT hmiType = IsPCHMI;

                    m_ptrBrodcastMsg = reinterpret_cast<AuthenticationMsg*>(m_TxBuff);
                    m_ptrBrodcastMsg->DiscoveryCode = DISCOVERY_CODE;
                    m_ptrBrodcastMsg->AuthNumber = RandomNumber;
                    strncpy(m_ptrBrodcastMsg->FirmwareVersion, " ", FIRMWARE_VERSION_SIZE - 1);
                    m_ptrBrodcastMsg->HmiType = hmiType;
#ifdef _WIN32
                    status = sendto(m_SockFd,
                        (const char*)m_TxBuff,/* buffer as const char* */
                        BUFF_SIZE,
                        0,
                        (struct sockaddr*)&m_BroadcastAddr,
                        (int)m_AddrLen               // cast to int
                        );
#else
                    status = sendto(m_SockFd, (void *) m_TxBuff, BUFF_SIZE , 0, (struct sockaddr*)&m_BroadcastAddr, m_AddrLen);
#endif
                    if(status < 0)
                    {
                        // Log Alarm
                        snprintf ( this->m_LogBuffer, buff_size_config, "WDS Server: Failed to send");
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                    }
                    CurrentState = WDS_DISCOVERY;
                }
                else
                {
                    CurrentState = WDS_IDEAL;
                }
            }
            break;

            case WDS_DISCOVERY:
            {
                while(m_DiscoveryInfoTable.size() < CONFIG_MAX_WELDERS )
                {
                    memset(m_RxBuff, 0,BUFF_SIZE);
                    memset(&m_PeerAddr,0, m_AddrLen);
#ifdef _WIN32
                    status = recvfrom(m_SockFd, (char*) m_RxBuff, BUFF_SIZE, 0, (struct sockaddr*)&m_PeerAddr, (int*)&m_AddrLen);
#else

                    status = recvfrom(m_SockFd,(void *) m_RxBuff, BUFF_SIZE, 0, (struct sockaddr*)&m_PeerAddr, &m_AddrLen);
#endif

                    if(status<0)
                    {
#ifdef _WIN32
                        int lastErr = WSAGetLastError();
                        if(lastErr == WSAEWOULDBLOCK || lastErr == WSAEINPROGRESS)
                        {
                            // No data, do nothing, try again
                        }
#else
                        if(errno == EWOULDBLOCK || errno == EAGAIN)
                        {
                            // No data, do nothing, try again
                        }
#endif
                        else
                        {
                            // Log Alarm
                            snprintf ( this->m_LogBuffer, buff_size_config, "Error failed to receive data");
                            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));
                        }
                        CurrentState = WDS_BROADCAST;
                        break;
                    }
                    else
                    {
                        m_ptrPeerResponseMsg = reinterpret_cast<AuthenticationMsg*>(m_RxBuff);
                        FoundNewIP = true;

                        for (auto it : m_WelderBlackList)
                        {
                            if (it == inet_ntoa(m_PeerAddr.sin_addr))
                            {
                                FoundNewIP = false;
                                break;
                            }
                        }
                        
                           
                        bool isFirmwareVersionValid = false;
                        if(FoundNewIP)
                        {
                        	isFirmwareVersionValid = CompareFirmwareMajorMinorVersions(m_ptrPeerResponseMsg->FirmwareVersion);

                        	if(!isFirmwareVersionValid)
                        	{
                        		FoundNewIP = false; //To avoid IP blacklisting make it false
                        		// Convert IP address to string
                        		char ipStr[INET_ADDRSTRLEN] = "";
#ifdef _WIN32
                                strncpy(ipStr, inet_ntoa(m_PeerAddr.sin_addr), INET_ADDRSTRLEN - 1);
#else
                        		inet_ntop(AF_INET, &(m_PeerAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
#endif

                                snprintf(this->m_LogBuffer, buff_size_config, "FW maj/min version mismatch for IP: %s, ASC: %s, HMI: %s", ipStr, m_ptrPeerResponseMsg->FirmwareVersion, GenerateHMIFirmwareVersionString().c_str());
                        		Logger::add_entry(E_SEVERITY::E_LOG_WARN, this->m_LogBuffer);

                                std::string MessageToBeDisplayed = "Firmware version mismatch for IP: "+ std::string(ipStr) + "\n Welder Firmware: "+m_ptrPeerResponseMsg->FirmwareVersion + "\n HMI Firmware: " + GenerateHMIFirmwareVersionString();
                                emit IsFirmwareVersionMismatchChangeDetected(MessageToBeDisplayed);
                            }
                        }

                        if ((ToggleRandomNumber(RandomNumber) == m_ptrPeerResponseMsg->AuthNumber) && isFirmwareVersionValid && FoundNewIP)
                        {
                            // Initliaze ConnDetails structure
                            ConnDetails = {0};

                            // copy peer connection details
                            strncpy (ConnDetails.IpAddr, inet_ntoa(m_PeerAddr.sin_addr), IP_ADDR_SIZE);
                            ConnDetails.Port           = WDS_PORT_CLIENT;
                            ConnDetails.ConnStatus     = NEW;
                            ConnDetails.Id             = atoi(ConnDetails.IpAddr);

                            for (int i = 0; i<CONFIG_MAX_WELDERS; i++)
                            {
                                if (m_FreeWelders[i] == 1)
                                {
                                    // Welder Id is index of m_FreeWelders
                                    WelderId = i;

                                    // Update index of m_FreeWelders array.
                                    m_FreeWelders[i] = 0;

                                    IsWelderAvailable = true;
                                    break;
                                }
                            }

                            if (IsWelderAvailable)
                            {
                                IsWelderAvailable = false;

                                // Log Debug
                                snprintf ( this->m_LogBuffer, buff_size_config, "Authentication successful");
                                Logger::add_entry(E_SEVERITY::E_LOG_DEB, (this->m_LogBuffer));

                                if(CommPeerWrapper::GetPeerData(WelderId)->GetCurrentState() == COMM_START_REQUEST)
                                {
                                    ConnDetails.ConnStatus     = INPROCESS;

                                    // Log Event
                                    snprintf ( this->m_LogBuffer, buff_size_config, "Triggered for Welder:%d", WelderId);
                                    Logger::add_entry(E_SEVERITY::E_LOG_EVENT, (this->m_LogBuffer));

                                    /* Lock Discovery Info Table to insert connection details of welder */
#ifdef _WIN32
                                    std::lock_guard<std::mutex> lock(m_DiscoveryInfoMutex);
#else
                                    pthread_mutex_lock(&m_DiscoveryInfoMutex);
#endif
                                    /* Connection details inserted into Discovery Info Table */
                                    m_DiscoveryInfoTable[WelderId] =  ConnDetails;

                                    /* Triggered to respective welder and send connection details */
                                    CommPeerWrapper::GetPeerData(WelderId)->TriggerStartRequest(ConnDetails.IpAddr);

                                    /* Unlock Discovery Info Table */
#ifdef _WIN32
                                    // lock_guard unlocks automatically
#else
                                    pthread_mutex_unlock(&m_DiscoveryInfoMutex);
#endif
                                }
                            }

                        } // received correct random number
                        else
                        {
                            // To avoid duplicate entry in blacklist
                            if (FoundNewIP)
                            {
                                // If random number is incorrect then its IP blacklisted.
                                m_WelderBlackList.push_back(inet_ntoa(m_PeerAddr.sin_addr));
                            }
                        }

                    } // Recvfrom success

                    // wait for connection status to be updated.
                    msleep(1);

                } // Find total welders
                CurrentState = WDS_BROADCAST;
            }
            break;

            case WDS_IDEAL:
            {
                if (m_DiscoveryInfoTable.size() == CONFIG_MAX_WELDERS)
                {
                    CurrentState = WDS_IDEAL;
                }
                else
                {
                    CurrentState = WDS_BROADCAST;
                }

            }
            break;

            default:
            {
                // Log Debug
                snprintf ( this->m_LogBuffer, buff_size_config, "Invalid state");
                Logger::add_entry(E_SEVERITY::E_LOG_DEB, (this->m_LogBuffer));
            }

        }
        // WDS Server send discover packet every 5 seconds
        sleep(5);
    }

}

/**************************************************************************//**
* \brief   - Return the single instance of class.
*
* \param   - None.
*
* \return  - WDSServer* Object
*
******************************************************************************/
WDSServer *WDSServer::GetInstance()
{
    if (WdsInstance == nullptr)
    {
        WdsInstance = new WDSServer();
    }
    return WdsInstance;
}

/**************************************************************************//**
* \brief   - Set peer's (welder's) connection status.
*
* \param   - int            WelderId, - Id of welder to update status
*            CONN_STATUS    ConnStatus - connection status to update.
*                           i.e. NEW, INPROCESS, SUCCESS, FAILURE
*
* \return  - None
 ***************************************************************************/
void WDSServer::SetPeerConnStatus(uint16_t WelderId, CONN_STATUS ConnStatus)
{
    /* Lock discovery info table to update status */
#ifdef _WIN32
    std::lock_guard<std::mutex> lock(m_DiscoveryInfoMutex);
#else
    pthread_mutex_lock(&m_DiscoveryInfoMutex);
#endif
    /* Check connection status of welder if welder failed to connect then it will be blacklisted */
    if (ConnStatus == BLACKLIST)
    {
        // Log Event
        snprintf ( this->m_LogBuffer, buff_size_config, "Welder %s blacklisted", m_DiscoveryInfoTable[WelderId].IpAddr);
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_LogBuffer));

        m_WelderBlackList.push_back(m_DiscoveryInfoTable[WelderId].IpAddr);

        // Removed WelderId is available to connect
        m_FreeWelders[WelderId] = 1;

        // Remove information of blacklisted welder from discovery info table.
        m_DiscoveryInfoTable.erase(WelderId);
    }
    else
    {
        /* Update status of respective welder */
        m_DiscoveryInfoTable[WelderId].ConnStatus = ConnStatus;
    }

    /* Unlock discovery info table. */
#ifdef _WIN32
    //nothing do unlock automatically
#else
    pthread_mutex_unlock(&m_DiscoveryInfoMutex);
#endif

    if (ConnStatus == SUCCESS)
    {
        /* Send signal to multiwelder interface on welder connected */
        emit PeerConnected(WelderId, m_DiscoveryInfoTable[WelderId].IpAddr);
    }
}

/**************************************************************************//**
* \brief   - Remove welder information from Discovery Info Table.
*
* \param   - int   WelderId - Id of welder to remove welder information
*
* \return  - None
 ***************************************************************************/
void WDSServer::UpdateDiscoveryInfoTable(uint16_t WelderId)
{
    // Send PeerDisconnected signal to HMI.
    emit PeerDisconnected(m_DiscoveryInfoTable[WelderId].IpAddr);

    /* Lock discovery info table to remove welder information */
#ifdef _WIN32
    std::lock_guard<std::mutex> lock(m_DiscoveryInfoMutex);
#else
    pthread_mutex_lock(&m_DiscoveryInfoMutex);
#endif

    // Removed WelderId is available to connect
    m_FreeWelders[WelderId] = 1;

    /* Remove welder information from discovery info table */
    m_DiscoveryInfoTable.erase(WelderId);

    /* Unlock discovery info table. */
#ifdef _WIN32
    //nothing do unlock automatically
#else
    pthread_mutex_unlock(&m_DiscoveryInfoMutex);
#endif
}

/**************************************************************************//**
* \brief   - Return IP Address of specified welder id
*
* \param   - int - WelderId
*
* \return  - Char * - Ip Address of active welder
******************************************************************************/
char* WDSServer::GetActiveWelderIPAddress(int WelderId)
{
    char* IpAddr = nullptr;

    if (m_DiscoveryInfoTable.size() > 0)
    {
        IpAddr = m_DiscoveryInfoTable[WelderId].IpAddr;
    }

    return IpAddr;
}

/**************************************************************************//**
 * \brief   - Compare the major and minor versions of firmware
 *
 * \param   - const std::string& current - Current firmware version
 *
 * \return  - bool - True if major and minor versions match, false otherwise
 ******************************************************************************/
bool WDSServer::CompareFirmwareMajorMinorVersions(const std::string& current)
{
	int curMajor = 0, curMinor = 0;
	sscanf(current.c_str(), "%d.%d", &curMajor, &curMinor);

	return ((curMajor == UIC_VERSION_NUM_MAJOR) && (curMinor == UIC_VERSION_NUM_MINOR));
}

/**************************************************************************//**
 * \brief   - Generate a string representing the HMI firmware version
 *
 * \param   - None
 *
 * \return  - std::string - The firmware version string in the format "major.minor.build.autos"
 ******************************************************************************/
std::string WDSServer::GenerateHMIFirmwareVersionString()
{
	return std::to_string(UIC_VERSION_NUM_MAJOR) + "." +
			std::to_string(UIC_VERSION_NUM_MINOR) + "." +
			std::to_string(UIC_VERSION_NUM_BUILD) + "." +
			std::to_string(UIC_VERSION_NUM_AUTOS);
}

/**************************************************************************//**
* \brief   - Destructor to perform cleanup activity
* 			 1. Delete m_ptrBrodcastMsg and m_ptrPeerResponseMsg.
*
* \param   - None
*
* \return  - None
******************************************************************************/
WDSServer::~WDSServer()
{
#ifdef _WIN32
    WSACleanup();
#endif
    delete m_ptrBrodcastMsg;
    delete m_ptrPeerResponseMsg;
#ifdef _WIN32
    closesocket(m_SockFd);
#else
    close(m_SockFd);
#endif
}

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Implementation of WDSServer Class - responsible for auto discovery of welder

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.

***************************************************************************/
#include "WDSServer.h"
#include "CommPeerWrapper.h"

/**************************************************************************//**
* @brief Defination of static variable
*******************************************************************************/
std::map <int,PeerConnDetails > WDSServer::m_DiscoveryInfoTable;
std::vector<std::string>        WDSServer::m_WelderBlackList;
pthread_mutex_t                 WDSServer::m_DiscoveryInfoMutex = PTHREAD_MUTEX_INITIALIZER;
uint16_t                        WDSServer::m_FreeWelders[MAX_WELDERS];
uint16_t                        WDSServer::m_TotalAvailWelders = 0;

/**************************************************************************//**
*
* \brief    - WDSServer class constructor Initialize below parameters:
             1. Initialize m_BrodcastMsg and m_PeerResponseMsg msg.
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
    // Initialize log ID
    this->m_LogId = logger::enroll(this);

    m_BrodcastMsg       = new AuthenticationMsg;
    m_PeerResponseMsg   = new AuthenticationMsg;

    /* Initially all welders are available. */
    for (int i = 0; i < MAX_WELDERS; i++)
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
    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

    if (setsockopt(m_SockFd, SOL_SOCKET, SO_BROADCAST, &BROADCAST, sizeof(BROADCAST)) < 0)
    {
        // raise error
        throw std::runtime_error("Failed to set socket broadcast");
    }

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

    m_SelfAddr.sin_family      = AF_INET; // IPv4
    m_SelfAddr.sin_addr.s_addr = INADDR_ANY;
    m_SelfAddr.sin_port        = htons(WDS_PORT);

    // Bind the socket with the self address
     if (bind(m_SockFd, (const struct sockaddr *)&m_SelfAddr, sizeof(m_SelfAddr)) < 0 )
     {
         throw std::runtime_error("Client bind failed");
     }

    // Filling broadcast address information
    m_BroadcastAddr.sin_family = AF_INET;
    m_BroadcastAddr.sin_port = htons(WDS_PORT);
    if(inet_aton(BROADCAST_IP_ADDR, &m_BroadcastAddr.sin_addr) <0)
    {
        // raise error
        throw std::runtime_error("Error: Invalid IP format");
    }
}

/**************************************************************************//**
* \brief   - Toggle received random number
*
* \param   - None
*
* \return  - None
******************************************************************************/
int WDSServer::ToggleRandomNumber(int n)
{
    int temp = 1;
    while (temp <= n) {
        n = n ^ temp;
        temp = temp << 1;
    }
    return n;
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
    int             status, random_number;
    bool            found_new_ip = true;
    PeerConnDetails ConnDetails;
    bool            isWelderAvailable = false;
    uint16_t        welder_id=0;

    // Generate random number
    srand(time(0));
    random_number = rand()%100;

    while (1)
    {
        if(m_TotalAvailWelders < MAX_WELDERS )
        {
            memset(m_RxBuff, 0,BUFF_SIZE);
            memset(&m_PeerAddr,0, m_AddrLen);

            status = recvfrom(m_SockFd,(void *) m_RxBuff, BUFF_SIZE, 0, (struct sockaddr*)&m_PeerAddr, &m_AddrLen);

            if(status<0)
            {
                if(errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    // Log Alarm
                    snprintf ( this->m_LogBuffer, buff_size_config, "WDS Server: no data");
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
                }
                else
                {
                    // Log Alarm
                    snprintf ( this->m_LogBuffer, buff_size_config, "Error failed to receive data");
                    logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
                }
            }
            else
            {
                m_PeerResponseMsg = reinterpret_cast<AuthenticationMsg*>(m_RxBuff);

                if ((ToggleRandomNumber(random_number) == m_PeerResponseMsg->AuthNumber))
                {
                    strncpy (ConnDetails.IpAddr, inet_ntoa(m_PeerAddr.sin_addr), IP_ADDR_SIZE);
                    ConnDetails.Port           = BIO_PORT;
                    ConnDetails.ConnStatus     = NEW;
                    ConnDetails.Id             = atoi(ConnDetails.IpAddr);

                    found_new_ip = true;

                    for (auto it : m_WelderBlackList)
                    {
                        if (it == ConnDetails.IpAddr)
                        {
                            found_new_ip = false;
                            break;
                        }
                    }

                    for (auto it : WDSServer::m_DiscoveryInfoTable)
                    {
                         /* Check welder already connected */
                        if (strncmp (it.second.IpAddr, ConnDetails.IpAddr, IP_ADDR_SIZE) == 0)
                        {
                            found_new_ip = false;
                            break;
                        }
                    }

                    if ((found_new_ip))
                    {

                        for (int i = 0; i<MAX_WELDERS; i++)
                        {
                            if (m_FreeWelders[i] == 1)
                            {
                                welder_id = i;
                                m_FreeWelders[i] = 0;
                                isWelderAvailable = true;
                                break;
                            }
                        }
                        if (isWelderAvailable)
                        {
                            // Log Debug
                            snprintf ( this->m_LogBuffer, buff_size_config, "Authentication successful");
                            logger::add_entry(this->m_LogId,SEVERITY::LOG_DEB, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                            if(CommPeerWrapper::GetPeerData(welder_id)->GetCurrentState() == COMM_START_REQUEST)
                            {
                                // Log Event
                                snprintf ( this->m_LogBuffer, buff_size_config, "Triggered for Welder:%d", welder_id);
                                logger::add_entry(this->m_LogId,SEVERITY::LOG_EVENT, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);

                                /* Lock Discovery Info Table to insert connection details of welder */
                                pthread_mutex_lock(&m_DiscoveryInfoMutex);

                                /* Connection details inserted into Discovery Info Table */
                                WDSServer::m_DiscoveryInfoTable[welder_id] =  ConnDetails;

                                /* Triggered to respective welder and send connection details */
                                CommPeerWrapper::GetPeerData(welder_id)->TriggerStartRequest(ConnDetails);

                                m_TotalAvailWelders++;

                                /* Send signal to multiwelder interface on welder connected */
                                emit PeerConnected(ConnDetails.IpAddr);

                                /* Unlock Discovery Info Table */
                                pthread_mutex_unlock(&m_DiscoveryInfoMutex);
                            }
                        }
                    } // New IP found

                } // received correct random number

            } // Recvfrom success

            m_BrodcastMsg = reinterpret_cast<AuthenticationMsg*>(m_TxBuff);
            m_BrodcastMsg->DiscoveryCode = DISCOVERY_CODE;
            m_BrodcastMsg->AuthNumber = random_number;

            status = sendto(m_SockFd, (void *) m_TxBuff, BUFF_SIZE , 0, (struct sockaddr*)&m_BroadcastAddr, m_AddrLen);
            if(status < 0)
            {
                // Log Alarm
                snprintf ( this->m_LogBuffer, buff_size_config, "WDS Server: Failed to send");
                logger::add_entry(this->m_LogId,SEVERITY::LOG_ALARM, reinterpret_cast<uint8_t*>(this->m_LogBuffer), buff_size_config);
            }

        } // Find total welders
        sleep(5);
    }

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
void WDSServer::SetPeerConnStatus(int WelderId, CONN_STATUS ConnStatus)
{
    /* Lock discovery info table to update status */
    pthread_mutex_lock(&m_DiscoveryInfoMutex);

    /* Check connection status of welder if welder failed to connect then it will be blacklisted */
    if (ConnStatus == BLACKLIST)
    {
        m_WelderBlackList.push_back(m_DiscoveryInfoTable[WelderId].IpAddr);
    }

    /* Update status of respective welder */
    m_DiscoveryInfoTable[WelderId].ConnStatus = ConnStatus;

    /* Unlock discovery info table. */
    pthread_mutex_unlock(&m_DiscoveryInfoMutex);
}

/**************************************************************************//**
* \brief   - Remove welder information from Discovery Info Table.
*
* \param   - int   WelderId - Id of welder to remove welder information
*
* \return  - None
 ***************************************************************************/
void WDSServer::RemovePeerInfo(int WelderId)
{
    /* Lock discovery info table to remove welder information */
    pthread_mutex_lock(&m_DiscoveryInfoMutex);

    // Removed WelderId is available to connect
    m_FreeWelders[WelderId] = 1;

    /* Remove welder information from discovery info table */
    m_DiscoveryInfoTable.erase(WelderId);

    // Decreament total available welders
    m_TotalAvailWelders--;

    /* Unlock discovery info table. */
    pthread_mutex_unlock(&m_DiscoveryInfoMutex);
}

/**************************************************************************//**
* \brief   - Destructor to perform cleanup activity
* 			 1. Delete m_BrodcastMsg and m_PeerResponseMsg.
*
* \param   - None
*
* \return  - None
******************************************************************************/
WDSServer::~WDSServer()
{
    delete m_BrodcastMsg;
    delete m_PeerResponseMsg;
}

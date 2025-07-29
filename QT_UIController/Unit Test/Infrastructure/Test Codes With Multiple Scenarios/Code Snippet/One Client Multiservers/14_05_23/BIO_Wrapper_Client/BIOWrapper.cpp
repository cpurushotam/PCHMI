/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file works as BIO wrapper for all non secure and secure
    communication reuirements prerequisites.
***************************************************************************/
#include "BIOWrapper.h"
#include "BIOWrapperInternal.h"
/**************************************************************************/

/**************************************************************************//**
*
* \brief   - Role of the BIOWrapper class constructor is as follows:
             1. Accept the configuration as per Config.h file.
             2. Instantiate the BIOWrapper object with configuration parameter as per accepted configuration.
             3. Perform the prerequisite activity before actual data read/write takes place, like creation os SSL object,set protocol version,
                Set ciphersuite etc..
*
* \param   - InterfaceConfig : Configuration inputes.
*
* \return  - None.
******************************************************************************/
BIOWrapper::BIOWrapper(CommConfig *InterfaceConfig)
{
    /*Initialize/Reset status to default state*/
    CommStatusResult = STATUS_CONNECTION_DEFAULT;

    /*Initialize all pointers to NULL*/
    bio = nullptr;
    connection_bio = nullptr;
    comm_bio = nullptr;
    ssl = nullptr;
    ctx = nullptr;
    cert = nullptr;

    /*Check if parameters configured are valid*/
    IsConfigValid(InterfaceConfig);

    /*Copy the argument into local struct variable*/
    m_GetInterfaceConfig = InterfaceConfig;

    /*Secure communication is disabled*/
    if(!m_GetInterfaceConfig->SecureConfigParam.IsEnable)
    {
        /*Role is SERVER*/
        if(m_GetInterfaceConfig->RoleIs == SERVER)
        {
            /*Do non-secure communication Server configuration settings*/
            NonSecureServerConfiguration();
        }

        /*Role is CLIENT*/
        else
        {
            /*Do non-secure communication Client configuration settings*/
            NonSecureClientConfiguration();
        }
    }
    /*==============================================*/
    /*Secure communication is enabled*/
    else
    {
        /*Perform the prerequisite required for secure communication to be establish*/
        SecureConfigurationSetup();

        /*Role is secure SERVER*/
        if(m_GetInterfaceConfig->RoleIs == SERVER)
        {
            /*Do secure communication server configuration settings*/
            SecureServerConfiguration();
        }

        /*Role is secure CLIENT*/
        else
        {
            /*Do secure communication client configuration settings*/
            SecureClientConfiguration();
        }
    }
}

/**************************************************************************//**
*
* \brief   - To perform read activity from respective connected peer.

* \param   - buff : Buffer to perform read operation.
*          - size : Size of buffer.
*
* \return  - ReadStat > 0  : Total length of data read.
*          - ReadStat = 0  : No data available to read.
*          - ReadStat = -1 : Read operation error.
******************************************************************************/
int BIOWrapper::BIORead(uint8_t * const buff, const int size)
{
    /*Local variables*/
    int ReadLen = 0, ReadStat = -1, SSLRetVal = 0;

    /*Check whether error occured by previous communication iteration is acknowledged or not*/
    if(CommStatusResult >= STATUS_CONNECTION_DEFAULT)
    {
        /*For non-secure mode of communication*/
        if(!m_GetInterfaceConfig->SecureConfigParam.IsEnable)
        {
            /*Loop counter*/
            int i = RETRYCOUNT;

            /*For non-blocking mode of connection*/
            if(!m_GetInterfaceConfig->IsBlocking)
            {
                /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of read operation.
                  Here, we checks whether read error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
                do
                {
                    /*BIO read*/
                    ReadLen = BIO_read(comm_bio, buff, size);

                    /*Preserve the return value obtained by BIO_read*/
                    ReadStat = ReadLen;

                    /*Non zero positive ReadLen value*/
                    if(ReadStat > 0)
                    {
                        /*Positive return value indicates read successful so break the loop*/
                        break;
                    }

                    /*Zero or negative read return value indicates error occured. Check whether its recoverable or not*/
                    else
                    {
                        /*To determine if the error is recoverable, call BIO_should_retry.*/
                        if(BIO_should_retry(comm_bio) > 0)
                        {
                            /*If BIO_should_retry give positive value means error could be recoverable, so perform read retry*/
                            ReadStat = 0;
                            continue;
                        }

                        else
                        {
                            /*If BIO_should_retry give negative value means error could not be recoverable, so break the loop*/
                            ReadStat = -1;
                            break;
                        }
                    }
                }

                while(i--);

                /*Positive return value indicates read successful*/
                if(ReadStat > 0)
                {
                    /*Update the status as read successful*/
                    CommStatusResult = STATUS_READ_SUCCESSFUL ;
                }

                /*Zero return value indicates no data available to read*/
                else if(ReadStat == 0)
                {
                    /*In non-blocking mode of communication zero return value indicates no read data available.
                      Thus update the status as no data available to read*/
                    CommStatusResult = STATUS_NO_DATA_AVAILABLE_TO_READ;
                }

                /*Negative return value indicates error occured*/
                else
                {
                    /*Update the status as error occurred*/
                    CommStatusResult = ERROR_STATUS_READ_ERROR;
                }
            }

            /*For blocking mode of connection*/
            else
            {
                /*BIO read*/
                ReadLen = BIO_read(comm_bio, buff, size);

                /*Preserve the return value obtained by BIO_read*/
                ReadStat = ReadLen;

                /*Positive return value indicates read successful*/
                if(ReadStat > 0)
                {
                    /*Update the status as read successful*/
                    CommStatusResult = STATUS_READ_SUCCESSFUL ;
                }

                /*Zero return value indicates connection closed*/
                else if(ReadStat == 0)
                {
                    /*In blocking mode of communication zero return value indicates connection closed error.
                      Thus update the status as connection closed*/
                    CommStatusResult = ERROR_STATUS_SUDDEN_PEER_TERMINATION_ERROR;

                    /*Treat this as error*/
                    ReadStat = -1;
                }

                /*Negative return value indicates error occured*/
                else
                {
                    /*Update the status as error occurred*/
                    CommStatusResult = ERROR_STATUS_READ_ERROR;
                }
            }
        }

        /*For secure mode of communication*/
        else
        {
            /*For non-blocking mode of connection*/
            if(!m_GetInterfaceConfig->IsBlocking)
            {
                /*Loop counter*/
                int i = RETRYCOUNT;

                /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of read operation.
                  Here, we checks whether read error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
                do
                {
                    /*BIO read*/
                    ReadLen = BIO_read(comm_bio, buff, size);

                    /*Preserve the return value obtained by BIO_read*/
                    ReadStat = ReadLen;

                    /*Non zero positive ReadLen value*/
                    if(ReadStat > 0)
                    {
                        /*Positive return value indicates read successful so break the loop*/
                        break;
                    }

                    /*Zero or negative return value indicates error occured. Check whether its recoverable or not*/
                    else
                    {
                        /*Non positive return value indicates no data read. This could be because of either no datato read or error.
                          so to determine if the condition is recoverable, call BIO_should_retry.*/
                        /*Perform retry*/
                        if(BIO_should_retry(comm_bio) > 0)
                        {
                            /*If BIO_should_retry give positive value means no data to read currently, so update the status, still retry to verify*/
                            ReadStat = 0;
                            continue;
                        }

                        else
                        {
                            /*If BIO_should_retry give negative value means error is non recoverable, so update read staus and break the loop*/
                            ReadStat = -1;
                            break;
                        }
                    }
                }

                while(i--);

                if (ReadStat < 0)
                {
                    /*Get the read operation result. Here latest return value obtained during BIO_read operation, provided to SSL_get_error*/
                    SSLRetVal = SSL_get_error(ssl, ReadLen);

                    /*Update the error status of communication, based on error result captured using SSL_get_error*/
                    SSLErrorStatusUpdate(SSLRetVal);
                }
            }

            /*For blocking mode of connection*/
            else
            {
                /*BIO read*/
                ReadLen = BIO_read(comm_bio, buff, size);

                /*Preserve the return value obtained by BIO_read*/
                ReadStat = ReadLen;

                /*Get the read operation result*/
                SSLRetVal = SSL_get_error(ssl, ReadLen);

                /*SSL_get_error returns 0 on success*/
                if(SSLRetVal == 0)
                {
                    /*Update the status as read successful in secure mode*/
                    CommStatusResult = STATUS_READ_SUCCESSFUL;
                }

                else
                {
                    /*To update the error status of communication, based on error result captured using SSL_get_error*/
                    SSLErrorStatusUpdate(SSLRetVal);
                }
            }
        }
    }

    /*Read operation is restricted as no action taken on error occured in previous communication iteration.
      This is because to prevent overwiting of communication status variable withought acknowledging it*/
    else
    {
        ReadStat = -1;
    }

    /*Return status of read operation*/
    return ReadStat;

}

/**************************************************************************//**
*
* \brief   - To perform write activity to respective connected peer.

* \param   - buff : Buffer to perform read operation.
*          - size : Size of buffer.
*
* \return  - WriteStat > 0 : Total length of data written.
*          - WriteStat = -1 : Write operation error.
*
* NOTE : BIOWrite operation consists of only 2 return statuses either success
*        or failure. Unlike BIORead operation, as there is no condition where
*        no data written in BIOWrite as such.
******************************************************************************/
int BIOWrapper::BIOWrite(const uint8_t *const buff, const int size)
{
    /*Local variables*/
    int WriteLen = 0, WriteStat = -1, SSLRetVal = 0;

    /*Check whether error occured by previous communication iteration is acknowledged or not*/
    if(CommStatusResult >= STATUS_CONNECTION_DEFAULT)
    {
        /*For non-secure mode of communication*/
        if(!m_GetInterfaceConfig->SecureConfigParam.IsEnable)
        {
            /*For non-blocking mode of connection*/
            if(!m_GetInterfaceConfig->IsBlocking)
            {
                /*Loop counter*/
                int i = RETRYCOUNT;

                /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of write operation.
                  Here, we checks whether write error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
                do
                {
                    /*BIO write*/
                    WriteLen = BIO_write(comm_bio, buff, size);

                    /*Preserve the return value obtained by BIO_write*/
                    WriteStat = WriteLen;

                    /*Non zero positive WriteLen value*/
                    if(WriteStat > 0)
                    {
                        /*Positive return value indicates write successful so break the loop*/
                        break;
                    }

                    /*Zero or negative write return value indicates error occured. Check whether its recoverable or not*/
                    else
                    {
                        /*Determine if the error is recoverable, call BIO_should_retry.*/
                        if(BIO_should_retry(comm_bio) > 0)
                        {
                            /*If BIO_should_retry give positive value means error could be recoverable, so perform read retry*/
                            continue;
                        }

                        else
                        {
                            /*If BIO_should_retry give negative value means error could not be recoverable, so break the loop*/
                            break;
                        }
                    }
                }

                while(i--);

                /*Positive return value indicates write successful*/
                if(WriteStat > 0)
                {
                    /*Update the status as write successful*/
                    CommStatusResult = STATUS_WRITE_SUCCESSFUL;
                }

                /*Non positive return value indicates write error*/
                else
                {
                    /*Update the status as error occurred*/
                    CommStatusResult = ERROR_STATUS_WRITE_ERROR;

                    /*Non positive value is considered write error*/
                    WriteStat = -1;
                }
            }

            /*For blocking mode of connection*/
            else
            {
                /*BIO write*/
                WriteLen = BIO_write(comm_bio, buff, size);

                /*Preserve the return value obtained by BIO_write*/
                WriteStat = WriteLen;

                /*Positive return value indicates write successful*/
                if(WriteStat > 0)
                {
                    /*Update the status as write successful*/
                    CommStatusResult = STATUS_WRITE_SUCCESSFUL;
                }

                /*Non positive return value indicates write error*/
                else
                {
                    /*Update the status as write error occurred*/
                    CommStatusResult = ERROR_STATUS_WRITE_ERROR;

                    /*Non positive value is considered write error*/
                    WriteStat = -1;
                }
            }
        }

        /*For secure mode of communication*/
        else
        {
            /*For non-blocking mode of connection*/
            if(!m_GetInterfaceConfig->IsBlocking)
            {
                /*Loop counter*/
                int i = RETRYCOUNT;

                /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of write operation.
                  Here, we checks whether write error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
                do
                {
                    /*BIO write*/
                    WriteLen = BIO_write(comm_bio, buff, size);

                    /*Preserve the return value obtained by BIO_write*/
                    WriteStat = WriteLen;

                    /*Non zero positive WriteLen value*/
                    if(WriteStat > 0)
                    {
                        /*Positive return value indicates write successful so break the loop*/
                        break;
                    }

                    /*Zero or negative write return value indicates error occured. Check whether its recoverable or not*/
                    else
                    {
                        /*Determine if the error is recoverable, call BIO_should_retry.*/
                        if(BIO_should_retry(comm_bio) > 0)
                        {
                            /*If BIO_should_retry give positive value means error could be recoverable, so perform read retry*/
                            continue;
                        }

                        else
                        {
                            /*If BIO_should_retry give negative value means error could not be recoverable, so break the loop*/
                            break;
                        }
                    }
                }

                while(i--);

                /*Get the write operation result. Here latest return value obtained during BIO_write operation, provided to SSL_get_error*/
                SSLRetVal = SSL_get_error(ssl, WriteLen);

                /*SSL_get_error returns 0 on successess*/
                if(SSLRetVal == 0)
                {
                    /*Update the status as write successful*/
                    CommStatusResult = STATUS_WRITE_SUCCESSFUL;
                }

                else
                {
                    /*To update the error status of communication, based on error result captured using SSL_get_error*/
                    SSLErrorStatusUpdate(SSLRetVal);

                    /*SSLRetVal is non zero indicates write error so update the status*/
                    WriteStat = -1;
                }
            }

            /*For blocking mode of connection*/
            else
            {
                /*BIO write*/
                WriteLen = BIO_write(comm_bio, buff, size);

                /*Preserve the return value obtained by BIO_write*/
                WriteStat = WriteLen;

                /*Get the write operation result with return value obttain
                  during last BIO_write operation performed*/
                SSLRetVal = SSL_get_error(ssl, WriteLen);

                /*SSL_get_error returns 0 on successess*/
                if(SSLRetVal == 0)
                {
                    /*Update the status as write successful*/
                    CommStatusResult = STATUS_WRITE_SUCCESSFUL;
                }

                else
                {
                    /*To update the error status of communication, based on error result captured using SSL_get_error*/
                    SSLErrorStatusUpdate(SSLRetVal);

                    /*SSLRetVal is non zero indicates write error so update the status*/
                    WriteStat = -1;
                }
            }
        }
    }
    /*Write operation is restricted as no action taken on error occured in previous communication iteration.
      This is because to prevent overwiting of communication status variable withought acknowledging it*/
    else
    {
        WriteStat = -1;
    }

    /*Return status of write operation*/
    return WriteStat;
}

/**************************************************************************//**
*
* \brief   - Fetch the status of communication.

* \param   - None
*
* \return  - CommStatus : Enum to describe communication operation status.
******************************************************************************/
CommStatus BIOWrapper::GetCommStatus(void)
{
    /*Return the operation status captured*/
    return CommStatusResult;
}

/**************************************************************************//**
*
* \brief   - Each parameter provided under config.h file gets verified here.

* \param   - InterfaceConfigVal : Configuration inputs provided by user.
*
* \return  - Verification output either true or false.
******************************************************************************/
bool BIOWrapper::IsConfigValid(CommConfig *InterfaceConfigVal)
{
    /*Check valid Role is configured*/
    if((InterfaceConfigVal->RoleIs < SERVER) || (InterfaceConfigVal->RoleIs > CLIENT))
    {
        throw std::invalid_argument("Invalid Role");
    }

    /*Check valid Destination IP and Port is configured*/
    if(IsValid(InterfaceConfigVal->DestinationIPandPort, IS_VALID_IP_AND_PORT) != true)
    {
        throw std::invalid_argument("Invalid IP&Port");
    }

    /*Check valid Host Name is configured*/
    if(IsValid(InterfaceConfigVal->SecureConfigParam.ExpectedPeerName.c_str(), IS_VALID_PEER_NAME) != true)
    {
        throw std::invalid_argument("Invalid PeerName");
    }

    /*Check if Self Certificate is present*/
    if(IsValid(InterfaceConfigVal->SecureConfigParam.SelfCertificate, IS_VALID_SELF_CERT) != true)
    {
        throw std::invalid_argument("No Self Cert");
    }

    /*Check if Self Private Key is present*/
    if(IsValid(InterfaceConfigVal->SecureConfigParam.SelfPrivateKey, IS_VALID_SELF_PRIVATE_KEY) != true)
    {
        throw std::invalid_argument("No Private Key");
    }

    /*Check if CA Certificate is present*/
    if(IsValid(InterfaceConfigVal->SecureConfigParam.CACertificate, IS_VALID_CA_CERTIFICATE) != true)
    {
        throw std::invalid_argument("No CA Cert");
    }

    /*Check valid Pass Key is configured*/
    if(IsValid(InterfaceConfigVal->SecureConfigParam.PassKey, IS_VALID_PASSKEY) != true)
    {
        throw std::invalid_argument("Invalid Passkey");
    }

    /*Check valid Ciphersuite is configured*/
    if(strcmp(InterfaceConfigVal->SecureConfigParam.CipherSuite, "TLS_AES_128_GCM_SHA256") && strcmp(InterfaceConfigVal->SecureConfigParam.CipherSuite, "TLS_AES_256_GCM_SHA384") &&
            strcmp(InterfaceConfigVal->SecureConfigParam.CipherSuite, "TLS_CHACHA20_POLY1305_SHA256") && strcmp(InterfaceConfigVal->SecureConfigParam.CipherSuite, "TLS_AES_128_CCM_SHA256") &&
            strcmp(InterfaceConfigVal->SecureConfigParam.CipherSuite, "TLS_AES_128_CCM_8_SHA256"))
    {
        throw std::invalid_argument("Invalid C.Suite");
    }

    /*Check valid TLS Version is configured*/
    if((InterfaceConfigVal->SecureConfigParam.TLSVersionIs < TLS1_VERSION_0) || (InterfaceConfigVal->SecureConfigParam.TLSVersionIs > TLS1_VERSION_3))
    {
        throw std::invalid_argument("Invalid TLS Ver.");
    }

    return true;
}

/**************************************************************************//**
*
* \brief   - Configure server for non secure communication.

* \param   - None.
*
* \return  - None.
******************************************************************************/
void BIOWrapper::NonSecureServerConfiguration()
{
    /*Accept new connection for data transfer using BIO routine*/
    comm_bio = BIO_new_accept(m_GetInterfaceConfig->DestinationIPandPort);
    if (comm_bio == nullptr)
    {
        throw std::runtime_error("BIO_new_accept");
    }

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        if (BIO_set_nbio(comm_bio, 1) <= 0)
        {
            throw std::runtime_error("BIO_set_nbio");
        }
    }

    /*Check port access*/
    if (BIO_do_accept(comm_bio) <= 0)
    {
         throw std::runtime_error("BIO_do_accept");
    }

    std::cout << "server started on " << m_GetInterfaceConfig->DestinationIPandPort<<std::endl;

    /*Check port access*/
    if (BIO_do_accept(comm_bio) <= 0)
    {
         throw std::runtime_error("BIO_do_accept");
    }

    CommStatusResult = STATUS_SERVER_STARTED;
    return;
}

/**************************************************************************//**
*
* \brief   - Configure client for non secure communication.

* \param   - None.
*
* \return  - None.
******************************************************************************/
void BIOWrapper::NonSecureClientConfiguration()
{
    bool Retry = true;

    /*New connection creation for data transfer using BIO routine*/
    comm_bio = BIO_new_connect(m_GetInterfaceConfig->DestinationIPandPort);

    if (comm_bio == nullptr)
    {
        throw std::runtime_error("BIO_new_accept");
    }

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        if (BIO_set_nbio(comm_bio, 1) <= 0)
        {
            throw std::runtime_error("BIO_set_nbio");
        }

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_connect(comm_bio) <= 0)
            {
                if(BIO_should_retry(comm_bio)>0)
                {
                   /*Retry to connect the peer in nonblocking mode*/
                }

                else
                {
                    throw std::runtime_error("BIO_do_connect");
                }
            }

            else
            {
                Retry = false;
            }
        }
    }

    /*For blocking mode of connection*/
    else
    {
        /*Connect for port access*/
        if (BIO_do_connect(comm_bio) <= 0)
        {
            throw std::runtime_error("BIO_do_connect");
        }
    }

    CommStatusResult = STATUS_CLIENT_STARTED;
    return;
}

/**************************************************************************//**
*
* \brief   - SecureConfigurationSetup performs below prerequisites for secure communication :
             1.Create new SSL object.
             2.Set protocol version to be used.
             3.Select ciphersuite to be used.
             4.Load the certificates and private keys into the SSL object.
             5.Set the default password callback called when loading/storing a PEM certificate with encryption
             6.Set trusted certificate.

* \param   - None.
*
* \return  - None.
******************************************************************************/
void BIOWrapper::SecureConfigurationSetup()
{
    int RetVal;

    /* To create new SSL object which holds various configuration and data relevant
     * to SSL/TLS or DTLS session establishment*/
    ctx = SSL_CTX_new(TLS_method());

    if (ctx == nullptr)
    {
        throw std::runtime_error("SSL_CTX_new");
    }

    /*Set protocol version to be used*/
    RetVal = SSL_CTX_set_min_proto_version(ctx, m_GetInterfaceConfig->SecureConfigParam.TLSVersionIs);
    if(RetVal == 0)
    {
        throw std::runtime_error("SSL Prot Version");
    }

    /*Select ciphersuite to be used*/
    RetVal = SSL_CTX_set_ciphersuites(ctx,m_GetInterfaceConfig->SecureConfigParam.CipherSuite);
    if(RetVal == 0)
    {
        throw std::runtime_error("Set Ciphersuites");
    }

    /*Load the certificates and private keys into the SSL object*/
    if (SSL_CTX_use_certificate_file(ctx, m_GetInterfaceConfig->SecureConfigParam.SelfCertificate, SSL_FILETYPE_PEM) <= 0)
    {
        throw std::runtime_error("Certificate File");
    }

    /*Set the default password callback called when loading/storing a PEM certificate with encryption*/
    SSL_CTX_set_default_passwd_cb_userdata(ctx,(void*) m_GetInterfaceConfig->SecureConfigParam.PassKey);

    if (SSL_CTX_use_PrivateKey_file(ctx, m_GetInterfaceConfig->SecureConfigParam.SelfPrivateKey, SSL_FILETYPE_PEM) <= 0)
    {
        throw std::runtime_error("PrivateKey");
    }
    /*Set trusted certificate*/
    RetVal = SSL_CTX_load_verify_locations(ctx,m_GetInterfaceConfig->SecureConfigParam.CACertificate ,NULL);
    if(RetVal == 0)
    {
        throw std::runtime_error("Verify Locations");
    }
    /*Verification of certificates using below modes:
    SSL_VERIFY_PEER -
    Server Mode : The server sends a client certificate request to the client. The certificate returned (if any) is checked.
    If the verification process fails, the TLS/SSL handshake is immediately terminated with an alert message containing the
    reason for the verification failure.

    Client Mode : The server certificate is verified. If the verification process fails,
    the TLS/SSL handshake is immediately terminated with an alert message containing the reason for the verification failure.
    If no server certificate is sent, because an anonymous cipher is used, SSL_VERIFY_PEER is ignored.

    SSL_VERIFY_FAIL_IF_NO_PEER_CERT -
    Server Mode : if the client did not return a certificate, the TLS/SSL handshake is immediately terminated with a
    "handshake failure" alert. This flag must be used together with SSL_VERIFY_PEER.

    Client Mode : Ignored.*/
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);

    /*Prerequisites for secure communication configured successful*/
    CommStatusResult = STATUS_SECURED_COMMUNICATION_CONFIGURED;
    return;
}

/**************************************************************************//**
*
* \brief   - Configure server for secure communication.

* \param   - None.

* \return  - None.
******************************************************************************/
void BIOWrapper::SecureServerConfiguration()
{
    bool Retry = true;

    /*Accept new connection for data transfer using BIO routine*/
    bio = BIO_new_accept(m_GetInterfaceConfig->DestinationIPandPort);
    if (bio == nullptr)
    {
        throw std::runtime_error("BIO_new_accept");
    }
    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        if (BIO_set_nbio(bio, 1) <= 0)
        {
            throw std::runtime_error("BIO_set_nbio");
        }
    }
    /*Check port access*/
    if (BIO_do_accept(bio) <= 0)
    {
        throw std::runtime_error("BIO_do_accept");
    }

    std::cout << "Server started on " << m_GetInterfaceConfig->DestinationIPandPort<<"\n"<<std::endl;

    /*Wait for connection from client*/
    if (BIO_do_accept(bio) <= 0)
    {
        throw std::runtime_error("BIO_do_accept");
    }
    /*Get BIO of client connection*/
    connection_bio = BIO_pop(bio);
    if (connection_bio == nullptr)
    {
        throw std::runtime_error("BIO_pop");
    }
    /*Create SSL BIO*/
    comm_bio = BIO_new_ssl(ctx,0);
    if (comm_bio == nullptr)
    {
        throw std::runtime_error("BIO_new_ssl");
    }

    /*Chain SSL BIO with client connection socket BIO*/
    BIO_push(comm_bio,connection_bio);

    /*Get SSL session*/
    ssl = nullptr;
    BIO_get_ssl(comm_bio, &ssl);
    if (ssl == nullptr)
    {
        throw std::runtime_error("BIO_get_ssl");
    }

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        /*Perform TLS handshake*/
        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_handshake(comm_bio)<= 0)
            {
                if(BIO_should_retry(comm_bio)>0)
                {
                    /*Retry to connect the peer in nonblocking mode*/
                }

                /*Error occured in handshake*/
                else
                {
                    throw std::runtime_error("BIO_do_handshake");
                }
            }

            /*Handshake successful!*/
            else
            {
                Retry = false;
            }
        }
    }

    /*For blocking mode of connection*/
    else
    {
        /*Perform TLS handshake*/
        if (BIO_do_handshake(comm_bio) <= 0)
        {
            throw std::runtime_error("BIO_do_handshake");
        }
    }

    /*Verify server certificate*/
    int err = SSL_get_verify_result(ssl);
    if (err != X509_V_OK)
    {
        throw std::runtime_error("Sever Cert Err");
    }

    /*Fetch peer certificate*/
    cert = SSL_get_peer_certificate(ssl);
    if (cert == nullptr)
    {
        throw std::runtime_error("No Peer Cert");
    }

    /*Check whether a certificate matches a given hostname, email address, or IP address*/
    if (X509_check_host(cert, m_GetInterfaceConfig->SecureConfigParam.ExpectedPeerName.data() , m_GetInterfaceConfig->SecureConfigParam.ExpectedPeerName.size(), 0, nullptr) != 1)
    {
        throw std::runtime_error("Peer Name Err");
    }

    std::cout << "Verified client certificate successfully.\n"<<std::endl;

    CommStatusResult = STATUS_SERVER_STARTED;
    return;
}

/**************************************************************************//**
*
* \brief   - Configure client for secure communication.

* \param   - None.

* \return  - None.
******************************************************************************/
void BIOWrapper::SecureClientConfiguration()
{
    int RetVal;
    bool Retry = true;

    /*Connect to server*/
    connection_bio = BIO_new_connect(m_GetInterfaceConfig->DestinationIPandPort);

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        if (BIO_set_nbio(connection_bio, 1) <= 0)
        {
            throw std::runtime_error("BIO_set_nbio");
        }

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_connect(connection_bio) <= 0)
            {
                if(BIO_should_retry(connection_bio)>0)
                {
                    /*Retry to connect the peer in nonblocking mode*/
                }

                /*Error occured in peer connection*/
                else
                {
                    throw std::runtime_error("BIO_do_connect");
                }
            }

            /*Peer Connection successful!*/
            else
            {
                Retry = false;
            }
        }
    }

    /*For blocking mode of connection*/
    else
    {
        /*Connect for port access*/
        if (BIO_do_connect(connection_bio) <= 0)
        {
            throw std::runtime_error("BIO_do_connect");
        }
    }

    /*Create SSL bio*/
    comm_bio = BIO_new_ssl(ctx,1);
    if (comm_bio == nullptr)
    {
        throw std::runtime_error("BIO_new_ssl");
    }

    /*Chain SSL bio to socket connection bio*/
    BIO_push(comm_bio, connection_bio);

    /*Get SSL session*/
    ssl = nullptr;
    BIO_get_ssl(comm_bio, &ssl);

    if (ssl == nullptr)
    {
        throw std::runtime_error("BIO_get_ssl");
    }

    /*Set hostname*/
    RetVal = SSL_set_tlsext_host_name(ssl,m_GetInterfaceConfig->SecureConfigParam.ExpectedPeerName.data());
    if(RetVal == 0)
    {
        throw std::runtime_error("Peername Set Err");
    }

    std::cout << "Client connected, performing TLS handshake..."<<std::endl;

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig->IsBlocking)
    {
        Retry = true;

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_handshake(comm_bio)<= 0)
            {
                if(BIO_should_retry(comm_bio)>0)
                {
                    /*Retry to handshake the peer in nonblocking mode*/
                }

                /*Error occured in handshake*/
                else
                {
                    throw std::runtime_error("BIO_do_handshake");
                }
            }

            /*Handshake successful!*/
            else
            {
                Retry = false;
            }
        }
    }

    /*For blocking mode of connection*/
    else
    {
        /*Perform TLS handshake*/
        if (BIO_do_handshake(comm_bio) <= 0)
        {
            throw std::runtime_error("TLS handshake");
        }
    }


    /*Verify server certificate*/
    int err = SSL_get_verify_result(ssl);
    if (err != X509_V_OK)
    {
        /*Verification error msg*/
        const char *message = X509_verify_cert_error_string(err);
        throw message;
    }

    /*Fetch peer certificate*/
    cert = SSL_get_peer_certificate(ssl);
    if (cert == nullptr)
    {
        throw std::runtime_error("No Peer Cert");
    }

    /*Check whether a certificate matches a given hostname, email address, or IP address*/
    if (X509_check_host(cert, m_GetInterfaceConfig->SecureConfigParam.ExpectedPeerName.data(), m_GetInterfaceConfig->SecureConfigParam.ExpectedPeerName.size(), 0, nullptr) != 1)
    {
        throw std::runtime_error("Peer Name Err");
    }

    std::cout << "Verified server certificate successfully.\n"<<std::endl;
    CommStatusResult = STATUS_CLIENT_STARTED;
    return;
}

/**************************************************************************//**
*
* \brief   - Update the error status of communication, based on
             error result captured using SSL_get_error.

* \param   - Value : Error value captured by SSL_get_error.

* \return  - None.
******************************************************************************/
void BIOWrapper::SSLErrorStatusUpdate(int Value)
{
    switch (Value)
    {
    case 1 :
        CommStatusResult = ERROR_STATUS_PROTOCOL_ERROR;
        break;

    case 2 :
        CommStatusResult = ERROR_STATUS_NOT_ENOUGH_WRITE_DATA_AVAILBLE_ERROR;
        break;

    case 3  :
        CommStatusResult = ERROR_STATUS_NOT_ENOUGH_READ_DATA_AVAILBLE_ERROR;
        break;

    case 4:
        CommStatusResult = ERROR_STATUS_NOT_ENOUGH_DATA_TO_HANDSHAKE_ERROR;
        break;

    case 5 :
        CommStatusResult = ERROR_STATUS_PEER_CONNECTION_ERROR;
        break;

    case 6 :
        CommStatusResult = ERROR_STATUS_SUDDEN_PEER_TERMINATION_ERROR;
        break;

    case 7  :
        CommStatusResult = ERROR_STATUS_PEER_CONNECTION_FAILURE_ERROR;
        break;

    case 8   :
        CommStatusResult = ERROR_STATUS_WAITING_FOR_CONNECTION_ERROR;
        break;

    case 9  :
        CommStatusResult = ERROR_STATUS_WAITING_TO_FINISH_ASYNC_OPERATION_ERROR;
        break;

    case 10  :
        CommStatusResult = ERROR_STATUS_WAITING_TO_FINISH_CRYPTOGRAPHIC_ASYNC_OPERATION_ERROR;
        break;

    default :
        CommStatusResult = ERROR_STATUS_UNKNOWN_ERROR;
        break;
    }
}

/**************************************************************************//**
*
* \brief   - Check each parameter configured is correcet or not.

* \param   - ParamString : Input string to be validate.
*            Type : Type of input string provided.

* \return  - True if input string is valid else false.
******************************************************************************/
bool IsValid(const char ParamString[], IsValidConfigurations Type)
{
    switch (Type)
    {
    /*Check valid Role*/
    case IS_VALID_IP_AND_PORT :
    {
        std::regex pattern("^[a-zA-Z0-9.:]+$");

        /* Regex pattern details :

        - ^ : The beginning of the string.
        - [a-zA-Z0-9:] : String shall have consits of only capitals and small alphanumeric characters along with only ":" symbol allowed.
        - $ - The end of the string. */

        if (std::regex_match(ParamString, pattern))

            return true;

        else

            return false;
    }
        break;

        /*Check valid Peer Name*/
    case IS_VALID_PEER_NAME :
    {
        /* Regex pattern details :

        - ^ : The beginning of the string.
        - [a-zA-Z0-9] : String shall have consits of only capitals and small alphanumeric characters.
        - $ - The end of the string. */

        std::regex pattern("^[a-zA-Z0-9]+$");

        if (std::regex_match(ParamString, pattern))

            return true;

        else

            return false;
    }
        break;

        /*Check availablity of Self Certificate, Key and CA Certificate*/
    case IS_VALID_SELF_CERT :
    case IS_VALID_SELF_PRIVATE_KEY :
    case IS_VALID_CA_CERTIFICATE :

    {
        std::ifstream test(ParamString);
        if (test)
            return true;
        else
            return false;
    }
        break;

        /*Check valid Passkey*/
    case IS_VALID_PASSKEY:

    {
        /* Regex pattern details :

        - ^ : The beginning of the string.
        - (?=.*[!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?]) : Positive lookahead to ensure the string contains at least one special character.
          This matches any of the special characters !@#$%^&*()_+-=[]{};':\"\\|,.<>/?.
        - (?=.*\\d) : Positive lookahead to ensure the string contains at least one digit.
        - (?=.*[a-z]) : Positive lookahead to ensure the string contains at least one lowercase letter.
        - (?=.*[A-Z]) : Positive lookahead to ensure the string contains at least one uppercase letter.
        - [a-zA-Z\\d!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?]{8,32} : Matches any combination of uppercase and lowercase letters, digits,
          and special characters, with a minimum length of 8 characters and a maximum length of 32 characters.
        - $ - The end of the string. */

        std::regex pattern("^(?=.*[!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?])(?=.*\\d)"
                           "(?=.*[a-z])(?=.*[A-Z])[a-zA-Z\\d!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?]{8,32}$");

        if (std::regex_match(ParamString, pattern))

            return true;

        else

            return false;
    }
        break;

        /*Default case condition*/
    default:

         return false;
        break;
    }

}


/**************************************************************************//**
*
* \brief   - BIOWrapper : Destructor for secure poweroff.

* \param   - None.

* \return  - None.
******************************************************************************/
/*Destructor for clean up activity*/
BIOWrapper::~BIOWrapper()
{
    /*Free all allocations*/
    std::cout<<"Destructor called\n"<<std::endl;

    /*For non secure communication*/
    if(!m_GetInterfaceConfig->SecureConfigParam.IsEnable)
    {
        /*Free all BIO allocations*/
        BIO_free_all(comm_bio);
    }

    /*For secure communication*/
    else
    {
        /*BIO_flush() normally writes out any internally buffered data, in some cases
          it is used to signal EOF and that no more data will be written.*/
        BIO_flush(comm_bio);
        BIO_flush(connection_bio);

        /*BIO_set_close ()is used in a source/sink BIO to indicate that the underlying I/O stream
          should be closed when the BIO is free*/
        BIO_set_close(connection_bio,BIO_CLOSE);

        BIO_flush(bio);

        BIO_set_close(bio,BIO_CLOSE);

        /*Role is SERVER*/
        if(m_GetInterfaceConfig->RoleIs == SERVER)
        {
            /*Free all BIO allocations*/
            BIO_free_all(comm_bio);
        }

        /*Free all BIO allocations*/
        BIO_free_all(bio);
    }

    /*Connection closed with safe shutdown*/
    CommStatusResult = STATUS_CONNECTION_CLOSED_SECURELY;
}

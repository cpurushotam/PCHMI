/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
#include "Communication.h"
/**************************************************************************/
/*Role of the Communication class constructor is as follows:
1. Accept the configuration as per Config.h file.
2. Instantiate the Communication object with configuration parameter as per accepted configuration.
3. Perform the prerequisite activity before actual data read/write takes place, like creation os SSL object,set protocol version,
   Set ciphersuite etc.*/
Communication::Communication(CommConfig InterfaceConfig)
{
    /*Check if parameters configured are valid*/
    if (IsConfigValid(InterfaceConfig))
    {
        /*Copy the argument into local struct variable*/
        m_GetInterfaceConfig = InterfaceConfig;

        /*Secure communication is disabled*/
        if(!m_GetInterfaceConfig.SecureConfigParam.IsEnable)
        {
            /*Role is SERVER*/
            if(m_GetInterfaceConfig.roleIs == SERVER)
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
            if(m_GetInterfaceConfig.roleIs == SERVER)
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

    else
    {
        throw "Invalid Configuration!\n";
    }
}

/*To perform read activity from respective connected peer*/
int Communication::BIORead(uint8_t * const buff, const int size)
{
    /*Local variables*/
    int ReadLen=0, RetVal, ReadStat = -1, val=0;

    /*BIO read*/
//    ReadLen = BIO_read(ssl_bio, buff, size);
    std::cout<<"ReadLen : \n"<<ReadLen<<endl;
    /*For non-secure mode of communication*/
    if(!m_GetInterfaceConfig.SecureConfigParam.IsEnable)
    {
        /*For non-blocking mode of connection*/
        if(!m_GetInterfaceConfig.IsBlocking)
        {
            /*For ReadLen value 0 or -1*/
            if (ReadLen <= 0)
            {
                val=BIO_should_retry(ssl_bio);
                /*Perform retry, whether error is recoverable or not*/
                std::cout<<"BIO_should_retry(ssl_bio) read : \n"<<val<<"&"<<ReadLen<<endl;

            }
            /*non zero ReadLen value*/
            else
            {

            }
        }

    }

    /*For secure mode of communication*/
    else
    {
        /*For non-secure mode of communication*/
        if(!m_GetInterfaceConfig.SecureConfigParam.IsEnable)
        {
            /*Loop counter*/
            int i = 3;

            /*For non-blocking mode of connection*/
            if(!m_GetInterfaceConfig.IsBlocking)
            {
                /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of read operation.
                  Here, we checks whether read error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
                do
                {
                    /*BIO read*/
                    ReadLen = BIO_read(ssl_bio, buff, size);
                    std::cout<<"ReadLen : \n"<<ReadLen<<endl;
                    /*Preserve the return value obtained by BIO_read*/
                    ReadStat = ReadLen;

                    /*Non zero positive ReadLen value*/
                    if(ReadStat > 0)
                    {
                        /*Positive return value indicates read successful so break the loop*/
                        break;
                    }

                    /*Zero ReadLen value*/
                    else if(ReadStat == 0)
                    {
                        /*Zero return value indicates no data available to read so break the loop*/
                        break;
                    }

                    /*Negative read return value indicates error occured. Check whether its recoverable or not*/
                    else
                    {
                        /*To determine if the error is recoverable, call BIO_should_retry.*/
                        if(BIO_should_retry(ssl_bio) > 0)
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

            }
        }
        /*Get the read operation result for both non-blocking and blocking communication*/
        RetVal = SSL_get_error(ssl, ReadLen);
        std::cout<<"SSL_get_error : \n"<<RetVal<<endl;
        /*To update the status of communication, based on error result captured using SSL_get_error*/
//        SSLErrorStatusUpdate(RetVal);
    }

//    std::cout<<"Data read : \n"<<buff<<endl;

    /*Return total length read*/
    return ReadLen;

}


/*To perform write activity to respective connected peer*/
int Communication::BIOWrite(const uint8_t *const buff, const int size)
{
    /*Local variables*/
    int WriteLen=0, WriteStat = -1, RetVal, val;

    /*BIO write*/
//    WriteLen = BIO_write(ssl_bio, buff, size);
//    std::cout<<"WriteLen : \n"<<WriteLen<<endl;
    /*For non-secure mode of communication*/
    if(!m_GetInterfaceConfig.SecureConfigParam.IsEnable)
    {
        /*For non blocking mode of connection*/
        if(!m_GetInterfaceConfig.IsBlocking)
        {
            /*For WriteLen value 0 or -1*/
            if (WriteLen <= 0)
            {
                val=BIO_should_retry(ssl_bio);
                cout<<"BIO_should_retry(ssl_bio) write: \n"<<val<<"&"<<WriteLen;
                /*Perform retry, whether error is recoverable or not*/
            }

            /*non zero WriteLen value*/
            else
            {

            }
        }
        /*For blocking mode of connection*/
        else
        {

        }
    }
    /*For secure mode of communication*/
    else
    {
        /*For non-blocking mode of connection*/
        if(!m_GetInterfaceConfig.IsBlocking)
        {
            /*Loop counter*/
            int i = 3;

            /*Below loop is utilized to handle retry, during failure condition occurred in non-blocking mode of write operation.
              Here, we checks whether write error is occurred or not. If yes, then check if its recoverable or not by using BIO_should_retry*/
            do
            {
                /*BIO write*/
                WriteLen = BIO_write(ssl_bio, buff, size);
                std::cout<<"WriteLen : \n"<<WriteLen<<endl;

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
                    if(BIO_should_retry(ssl_bio) > 0)
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
}
        /*For non-blocking mode of connection*/
//        if(!m_GetInterfaceConfig.IsBlocking)
//        {
//            if (WriteLen <= 0)
//            {
//                val = BIO_should_retry(ssl_bio);
//                if(val > 0)
//                {
//                    std::cout<<"BIO_should_retry(ssl_bio) write: \n"<<val<<"&"<<WriteLen<<endl;
//                    /*Get the error update using SSL_get_error*/
//                }

//                else
//                {
//                   std::cout<<"BIO_should_retry(ssl_bio) write: 2\n"<<val<<"&"<<WriteLen<<endl;
//                }
//            }
//        }

        /*Get the write operation result for both non-secure and secure communication*/
        RetVal = SSL_get_error(ssl, WriteLen);
        std::cout<<"SSL_get_error write: \n"<<RetVal<<endl;
        /*To update the status of communication, based on error result captured using SSL_get_error*/
//        SSLErrorStatusUpdate(RetVal);
    }
//    std::cout<<"Data write : "<<buff<<endl;

    /*Return total length written*/
    return WriteLen;

}

/*Fetch the status of communication*/
void Communication::GetCommStatus(int ErrorType)
{
    switch ((CommStatus) ErrorType)
    {
    case STATUS_SSL_ERROR_SSL   :
        std::cout<<"A non-recoverable, fatal error in the SSL library occurred, usually a protocol error.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_WANT_READ   :
    case STATUS_SSL_ERROR_WANT_WRITE  :
        std::cout<<"The operation did not complete and can be retried later as not enough data was available at this"
              "time to complete the operation.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_WANT_X509_LOOKUP:
        std::cout<<"The operation did not complete because an application callback set by SSL_CTX_set_client_cert_cb()"
              " has asked to be called again.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_SYSCALL :
        std::cout<<"Peer connection error..! Communication disconnected.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_ZERO_RETURN :
        std::cout<<"The TLS/SSL peer has closed the connection for writing by sending the close_notify alert."
              "No more data can be read.\n"<<endl;
        break;
    case STATUS_SSL_ERROR_WANT_CONNECT  :
    case STATUS_SSL_ERROR_WANT_ACCEPT   :
        std::cout<<"The operation did not complete; the same TLS/SSL I/O function should be called again later.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_WANT_ASYNC  :
        std::cout<<"The operation did not complete because an asynchronous engine is still processing data.\n"<<endl;
        break;

    case STATUS_SSL_ERROR_WANT_ASYNC_JOB  :
        std::cout<<"The asynchronous job could not be started because there were no async jobs available in the pool.\n"<<endl;
        break;

    default :
        std::cout<<"Unknown error.\n"<<endl;
        break;
    }
}

/*Each parameter provided under config.h file gets verified here*/
bool Communication::IsConfigValid(CommConfig InterfaceConfigVal)
{
    /*Check valid Role is configured*/
    if((InterfaceConfigVal.roleIs < SERVER) || (InterfaceConfigVal.roleIs > CLIENT))
    {
        throw "Invalid role configured!\n";
        return false;
    }

    /*Check valid Destination IP and Port is configured*/
    if(IsValid(InterfaceConfigVal.DestinationIPandPort, ConfigRole) != true)
    {
        throw "Invalid DestinationIPandPort configured!\n";
        return false;
    }

    /*Check valid Host Name is configured*/
    if(IsValid(InterfaceConfigVal.ExpectedHostName.c_str(), ConfigExpectedHostName) != true)
    {
        throw "Invalid HostName configured!\n";
        return false;
    }

    /*Check if Self Certificate is present*/
    if(IsValid(InterfaceConfigVal.SecureConfigParam.SelfCertificate, ConfigSelfCertificate) != true)
    {
        throw "No Self Certificate presented!\n";
        return false;
    }

    /*Check if Self Private Key is present*/
    if(IsValid(InterfaceConfigVal.SecureConfigParam.SelfPrivateKey, ConfigSelfPrivateKey) != true)
    {
        throw "No Self Private Key presented!\n";
        return false;
    }

    /*Check if CA Certificate is present*/
    if(IsValid(InterfaceConfigVal.SecureConfigParam.CACertificate, ConfigCACertificate) != true)
    {
        throw "No CA Certificate presented!\n";
        return false;
    }

    /*Check valid Peer Name is configured*/
    if(IsValid(InterfaceConfigVal.SecureConfigParam.ExpectedPeerName, ConfigPeerName) != true)
    {
        throw "Invalid Expected Peername configured!\n";
        return false;
    }

    /*Check valid Pass Key is configured*/
    if(IsValid(InterfaceConfigVal.SecureConfigParam.PassKey, ConfigPassKey) != true)
    {
        throw "Invalid Passkey configured!\n";
        return false;
    }

    /*Check valid Ciphersuite is configured*/
    if(strcmp(InterfaceConfigVal.SecureConfigParam.CipherSuite, "TLS_AES_128_GCM_SHA256") && strcmp(InterfaceConfigVal.SecureConfigParam.CipherSuite, "TLS_AES_256_GCM_SHA384") &&
            strcmp(InterfaceConfigVal.SecureConfigParam.CipherSuite, "TLS_CHACHA20_POLY1305_SHA256") && strcmp(InterfaceConfigVal.SecureConfigParam.CipherSuite, "TLS_AES_128_CCM_SHA256") &&
            strcmp(InterfaceConfigVal.SecureConfigParam.CipherSuite, "TLS_AES_128_CCM_8_SHA256"))
    {
        throw "Invalid Ciphersuite selected!\n";
        return false;
    }

    /*Check valid TLS Version is configured*/
    if((InterfaceConfigVal.SecureConfigParam.TLSVersionIs < TLS1_VERSION_0) || (InterfaceConfigVal.SecureConfigParam.TLSVersionIs > TLS1_VERSION_3))
    {
        throw "Invalid TLS Version configured!\n";
        return false;
    }

    return true;
}

/*Configure server for non secure communication*/
void Communication::NonSecureServerConfiguration()
{
    /*Accept new connection for data transfer using BIO routine*/
    ssl_bio = BIO_new_accept(m_GetInterfaceConfig.DestinationIPandPort);
    if (ssl_bio == nullptr)
    {
        throw "Error in BIO_new_accept!";
    }

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        if (BIO_set_nbio(ssl_bio, 1) <= 0)
        {
            throw "Error in BIO_set_nbio!";
        }
    }

    /*Check port access*/
    if (BIO_do_accept(ssl_bio) <= 0)
    {
         throw "Error in BIO_do_accept!";
    }

    std::cout << "server started on " << m_GetInterfaceConfig.DestinationIPandPort << endl;

    return;
}

/*Configure client for non secure communication*/
void Communication::NonSecureClientConfiguration()
{
    bool Retry = true;
    /*New connection creation for data transfer using BIO routine*/
    ssl_bio = BIO_new_connect(m_GetInterfaceConfig.DestinationIPandPort);
    if (ssl_bio == nullptr)
    {
        throw "Error in BIO_new_accept!";
    }

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        if (BIO_set_nbio(ssl_bio, 1) <= 0)
        {
            throw "Error in BIO_set_nbio!";
        }

        else
        {
            std::cout<<"Client nbio set"<<endl;
        }

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_connect(ssl_bio) <= 0)
            {
                if(BIO_should_retry(ssl_bio)>0)
                {
                    /*Do nothing, perform retry*/
                }
                else
                {
                    throw "Error in BIO_do_connect!";
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
        if (BIO_do_connect(ssl_bio) <= 0)
        {
            throw "Error in BIO_do_connect!";
        }
    }


    return;
}

/*SecureConfigurationSetup performs below prerequisites for secure communication :
1. Create new SSL object
2. Set protocol version to be used
3. Select ciphersuite to be used
4. Load the certificates and private keys into the SSL object
5. Set the default password callback called when loading/storing a PEM certificate with encryption
6. Set trusted certificate*/
void Communication::SecureConfigurationSetup()
{
    int RetVal;

    /* To create new SSL object which holds various configuration and data relevant
     * to SSL/TLS or DTLS session establishment*/
    ctx = SSL_CTX_new(TLS_method());

    if (ctx == nullptr)
    {
        throw "Error in SSL_CTX_new!";
    }

    /*Set protocol version to be used*/
    RetVal = SSL_CTX_set_min_proto_version(ctx, m_GetInterfaceConfig.SecureConfigParam.TLSVersionIs);
    if(RetVal == 0)
    {
        throw "Error in SSL_CTX_set_min_proto_version!";
    }

    /*Select ciphersuite to be used*/
    RetVal = SSL_CTX_set_ciphersuites(ctx,m_GetInterfaceConfig.SecureConfigParam.CipherSuite);
    if(RetVal == 0)
    {
        throw "Error in SSL_CTX_set_ciphersuites!";
    }

    /*Load the certificates and private keys into the SSL object*/
    if (SSL_CTX_use_certificate_file(ctx, m_GetInterfaceConfig.SecureConfigParam.SelfCertificate, SSL_FILETYPE_PEM) <= 0)
    {
        throw "Error in SSL_CTX_use_certificate_file!";
    }

    /*Set the default password callback called when loading/storing a PEM certificate with encryption*/
    SSL_CTX_set_default_passwd_cb_userdata(ctx,(void*) m_GetInterfaceConfig.SecureConfigParam.PassKey);

    if (SSL_CTX_use_PrivateKey_file(ctx, m_GetInterfaceConfig.SecureConfigParam.SelfPrivateKey, SSL_FILETYPE_PEM) <= 0)
    {
        throw "Error in SSL_CTX_use_PrivateKey_file!";
    }
    /*Set trusted certificate*/
    RetVal = SSL_CTX_load_verify_locations(ctx,m_GetInterfaceConfig.SecureConfigParam.CACertificate ,NULL);
    if(RetVal == 0)
    {
        throw "Error in SSL_CTX_load_verify_locations!";
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

    return;
}

/*Configure server for secure communication*/
void Communication::SecureServerConfiguration()
{
    bool Retry = true;

    /*Accept new connection for data transfer using BIO routine*/
    sec_bio = BIO_new_accept(m_GetInterfaceConfig.DestinationIPandPort);
    if (sec_bio == nullptr)
    {
        throw "Error in BIO_new_accept!";
    }
    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        if (BIO_set_nbio(sec_bio, 1) <= 0)
        {
            throw "Error in BIO_set_nbio!";
        }

        else
        {
            std::cout<<"Server nbio set"<<endl;
        }
    }
    /*Check port access*/
    if (BIO_do_accept(sec_bio) <= 0)
    {
        throw "Error in BIO_do_accept!";
    }

    std::cout << "Server started on " << m_GetInterfaceConfig.DestinationIPandPort<<"\n"<<endl;

    /*Wait for connection from client*/
    if (BIO_do_accept(sec_bio) <= 0)
    {
        throw "Error in BIO_do_accept!";
    }
    /*Get BIO of client connection*/
    connection_bio = BIO_pop(sec_bio);
    if (connection_bio == nullptr)
    {
        throw "Error in BIO_pop!";
    }
    /*Create SSL BIO*/
    ssl_bio = BIO_new_ssl(ctx,0);
    if (ssl_bio == nullptr)
    {
        throw "Error in SSL_CTX_load_verify_locations!";
    }

    /*Chain SSL BIO with client connection socket BIO*/
    BIO_push(ssl_bio,connection_bio);

    /*Get SSL session*/
    ssl = nullptr;
    BIO_get_ssl(ssl_bio, &ssl);
    if (ssl == nullptr)
    {
        throw "Error in BIO_get_ssl!";
    }


    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        /*Perform TLS handshake*/
        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_handshake(ssl_bio)<= 0)
            {
                if(BIO_should_retry(ssl_bio)>0)
                {
                    /*Do nothing, perform retry*/
                }

                else
                {
                    throw "Error in BIO_do_handshake!";
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
        /*Perform TLS handshake*/
        if (BIO_do_handshake(ssl_bio) <= 0)
        {
            throw "Error in BIO_do_handshake!";
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
        throw "No certificate was presented!\n";
    }

    /*Check whether a certificate matches a given hostname, email address, or IP address*/
    if (X509_check_host(cert, m_GetInterfaceConfig.ExpectedHostName.data() , m_GetInterfaceConfig.ExpectedHostName.size(), 0, nullptr) != 1)
    {
        throw "Server Certificate verification error: Hostname mismatch!\n";
    }

    std::cout << "Verified server certificate successfully.\n" << endl;

    return;
}

/*Configure client for secure communication*/
void Communication::SecureClientConfiguration()
{
    int RetVal;
    bool Retry = true;

    /*Connect to server*/
    connection_bio = BIO_new_connect(m_GetInterfaceConfig.DestinationIPandPort);

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        if (BIO_set_nbio(connection_bio, 1) <= 0)
        {
            throw "Error in BIO_set_nbio!";
        }

        else
        {
            std::cout<<"Client nbio set"<<endl;
        }

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_connect(connection_bio) <= 0)
            {
                if(BIO_should_retry(connection_bio)>0)
                {
                    /*Do nothing, perform retry*/
                }
                else
                {
                    throw "Error in BIO_do_connect!";
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
        if (BIO_do_connect(connection_bio) <= 0)
        {
            throw "Error in BIO_do_connect!";
        }
    }

    /*Create SSL bio*/
    ssl_bio = BIO_new_ssl(ctx,1);
    if (ssl_bio == nullptr)
    {
        throw "Error in BIO_get_ssl!";
    }

    /*Chain SSL bio to socket connection bio*/
    BIO_push(ssl_bio, connection_bio);

    /*Get SSL session*/
    ssl = nullptr;
    BIO_get_ssl(ssl_bio, &ssl);

    if (ssl == nullptr)
    {
        throw "Error in BIO_get_ssl!";
    }

    /*Set hostname*/
    RetVal = SSL_set_tlsext_host_name(ssl,m_GetInterfaceConfig.ExpectedHostName.data());
    if(RetVal == 0)
    {
        throw "Error in SSL_set_tlsext_host_name!";
    }

    std::cout << "Client connected, performing TLS handshake..." << endl;

    /*For non blocking mode of connection*/
    if(!m_GetInterfaceConfig.IsBlocking)
    {
        Retry = true;

        while(Retry)
        {
            /*Connect for port access*/
            if (BIO_do_handshake(ssl_bio)<= 0)
            {
                if(BIO_should_retry(ssl_bio)>0)
                {
                    /*Do nothing, perform retry*/
                }

                else
                {
                    throw "Error in BIO_do_handshake!";
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
        /*Perform TLS handshake*/
        if (BIO_do_handshake(ssl_bio) <= 0)
        {
            throw "Error in TLS handshake";
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
        throw "No certificate was presented %s !\n";
    }

    /*Check whether a certificate matches a given hostname, email address, or IP address*/
    if (X509_check_host(cert, m_GetInterfaceConfig.ExpectedHostName.data(), m_GetInterfaceConfig.ExpectedHostName.size(), 0, nullptr) != 1)
    {
        throw "Client Certificate verification error: Hostname mismatch %s !\n";
    }

    std::cout << "Verified client certificate successfully.\n" << endl;

    return;
}

/*Check each parameter configured is correcet or not*/
bool Communication::IsValid(const char ParamString[], ConfigInputs Type)
{
    /*Define return variable*/
    bool flag = true;

    switch (Type)
    {
    /*Check valid Role*/
    case 1 :
    {
        std::regex pattern("^[a-zA-Z0-9:.]+$");

        if (std::regex_match(ParamString, pattern))

            return true;

        else

            return false;
    }
        break;

        /*Check valid Host Name*/
    case 2 :
    {
        std::regex pattern("^[a-zA-Z0-9]+$");

        if (std::regex_match(ParamString, pattern))

            return true;

        else

            return false;
    }
        break;

        /*Check availablity of Self Certificate, Key and CA Certificate*/
    case 3 :
    case 4 :
    case 5 :

    {
        std::ifstream test(ParamString);
        if (test)
            flag = true;
        else
            flag = false;
    }
        break;

        /*Check valid Peer Name and Passkey*/
//    case 6:
    case 7:
    {
//        std::regex pattern("^(?=.*[!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?])(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z\\d!@#$%^&*()_+\\-=\\[\\]{};':\"\\|,.<>\\/?]{8,32}$");
        std::regex pattern("^[a-zA-Z0-9]+$");
        if (std::regex_match(ParamString, pattern))
{
            cout<<"true\n"<<endl;
            return true;
        }

        else

            return false;
    }
        break;

        /*Default case condition*/
    default:

        return flag;
        break;
    }

    return flag;
}

/*Destructor for clean up activity*/
Communication::~Communication()
{
    /*Free all allocations*/
    std::cout<<"Destructor called\n"<<endl;

    /*For non secure communication*/
    if(!m_GetInterfaceConfig.SecureConfigParam.IsEnable)
    {
        /*Free all BIO allocations*/
        BIO_free_all(ssl_bio);
    }

    /*For secure communication*/
    else
    {
        /*Safe shutdown where, connection is being considered closed and the session is closed and correct*/
        SSL_set_shutdown(ssl,SSL_SENT_SHUTDOWN);

        if(SSL_get_shutdown(ssl) != SSL_SENT_SHUTDOWN)
        {
            throw "Error occured in SSL_set_shutdown!\n";
        }
        /*Free an allocated SSL_CTX object*/
        SSL_CTX_free(ctx);

        /*Free all BIO allocations*/
        BIO_free_all(sec_bio);
        BIO_free_all(ssl_bio);
    }
}

#include "Communication.h"

Communication::Communication(CommConfig InterfaceConfig)
{
    /*Copy the argument into local struct variable*/
    GetInterfaceConfig = InterfaceConfig;

    /*Secure communication is disabled*/
    if(!GetInterfaceConfig.ConfigParam.IsEnable)
    {
        /*Role is SERVER*/
        if(GetInterfaceConfig.roleIs == SERVER)
        {
            /*Accept new connection for data transfer using BIO routine*/
            unsec_bio = BIO_new_accept(GetInterfaceConfig.DestinationIPandPort);
            if (unsec_bio == nullptr)
            {
                cout << "Error in BIO_new_accept!" << endl;
                exit(1);
            }

            /*For non blocking mode of connection*/
            if(!GetInterfaceConfig.IsBlocking)
            {
                BIO_set_nbio(unsec_bio, 1);
            }
            /*Check port access*/
            if (BIO_do_accept(unsec_bio) <= 0)
            {
                cout << "Error in BIO_do_accept!" << endl;
                exit(1);
            }

            cout << "server started on " << GetInterfaceConfig.DestinationIPandPort << endl;
        }

        /*Role is CLIENT*/
        else
        {
            /*New connection creation for data transfer using BIO routine*/
            unsec_bio = BIO_new_connect(GetInterfaceConfig.DestinationIPandPort);

            /*For non blocking mode of connection*/
            if(!GetInterfaceConfig.IsBlocking)
            {
                BIO_set_nbio(unsec_bio, 1);
            }

            if(unsec_bio == NULL)
            {
                cout << "Error in BIO_new_connect!" << endl;
            }
            /*Connect for port access*/
            if(BIO_do_connect(unsec_bio) <= 0)
            {
                cout << "Error in BIO_do_connect!" << endl;
            }

        }

    }
//    ==============================================
    else
    {
        int RetVal;

        /* To create new SSL object which holds various configuration and data relevant
         * to SSL/TLS or DTLS session establishment*/
        ctx = SSL_CTX_new(TLS_method());

        if (ctx == nullptr)
        {
            cout << "Error in SSL_CTX_new!" << endl;
            exit(1);
        }

        /*Set protocol version to be used*/
        RetVal = SSL_CTX_set_min_proto_version(ctx, GetInterfaceConfig.ConfigParam.TLSVersionIs);
        if(RetVal == 0)
        {
            cout << "Error in SSL_CTX_set_min_proto_version!" << endl;
            exit(1);
        }

        /*Select ciphersuite to be used*/
        RetVal = SSL_CTX_set_ciphersuites(ctx,GetInterfaceConfig.ConfigParam.CipherSuit);
        if(RetVal == 0)
        {
            cout << "Error in SSL_CTX_set_ciphersuites!" << endl;
            exit(1);
        }

        /*Load the certificates and private keys into the SSL object*/
        if (SSL_CTX_use_certificate_file(ctx, GetInterfaceConfig.ConfigParam.SelfCertificate, SSL_FILETYPE_PEM) <= 0)
        {
            cout << "Error in SSL_CTX_use_certificate_file!" << endl;
            exit(1);
        }

        /*Set the default password callback called when loading/storing a PEM certificate with encryption*/
        SSL_CTX_set_default_passwd_cb_userdata(ctx,(void*) GetInterfaceConfig.ConfigParam.PassKey);

        if (SSL_CTX_use_PrivateKey_file(ctx, GetInterfaceConfig.ConfigParam.SelfPrivateKey, SSL_FILETYPE_PEM) <= 0)
        {
            cout << "Error in SSL_CTX_use_PrivateKey_file!" << endl;
            exit(1);
        }

        /*Set trusted certificate*/
        RetVal = SSL_CTX_load_verify_locations(ctx,GetInterfaceConfig.ConfigParam.PeerCertificate ,NULL);
        if(RetVal == 0)
        {
            cout << "Error in SSL_CTX_load_verify_locations!" << endl;
            exit(1);
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

        /*SERVER role configuration*/
        if(GetInterfaceConfig.roleIs == SERVER)
        {
            /*Accept new connection for data transfer using BIO routine*/
            sec_bio = BIO_new_accept(GetInterfaceConfig.DestinationIPandPort);
            if (sec_bio == nullptr)
            {
                cout << "Error in BIO_new_accept!" << endl;
                exit(1);
            }

             /*For non blocking mode of connection*/
            if(!GetInterfaceConfig.IsBlocking)
            {
                BIO_set_nbio(sec_bio, 1);
            }
            /*Check port access*/
            if (BIO_do_accept(sec_bio) <= 0)
            {
                cout << "Error in BIO_do_accept!" << endl;
                exit(1);
            }

            cout << "Server started on " << GetInterfaceConfig.DestinationIPandPort << endl;

            /*Wait for connection from client*/
            if (BIO_do_accept(sec_bio) <= 0)
            {
                cout << "Error in SSL_CTX_load_verify_locations!" << endl;
                exit(1);
            }

            /*Get BIO of client connection*/
            connection_bio = BIO_pop(sec_bio);
            if (connection_bio == nullptr)
            {
                cout << "Error in BIO_pop!" << endl;
                exit(1);
            }
            /*Create SSL BIO*/
            ssl_bio = BIO_new_ssl(ctx,0);
            if (ssl_bio == nullptr)
            {
                cout << "Error in SSL_CTX_load_verify_locations!" << endl;
                exit(1);
            }

            /*Chain SSL BIO with client connection socket BIO*/
            BIO_push(ssl_bio,connection_bio);

            /*Get SSL session*/
            ssl = nullptr;
            BIO_get_ssl(ssl_bio, &ssl);
            if (ssl == nullptr)
            {
                cout << "Error in BIO_get_ssl!" << endl;
                exit(1);
            }


            /*Perform TLS handshake*/
            if (BIO_do_handshake(ssl_bio) <= 0)
            {
                cout << "Error in BIO_do_handshake!" << endl;
                exit(1);
            }


            /*Verify server certificate*/
            int err = SSL_get_verify_result(ssl);
            if (err != X509_V_OK)
            {
                /*Verification error msg*/
                const char *message = X509_verify_cert_error_string(err);
                fprintf(stderr, "Certificate verification error: %s (%d) %s !\n", message, err, __FUNCTION__);
                exit(1);
            }

            /*Fetch peer certificate*/
            cert = SSL_get_peer_certificate(ssl);
            if (cert == nullptr)
            {
                fprintf(stderr, "No certificate was presented %s !\n",__FUNCTION__);
                exit(1);
            }

            /*Check whether a certificate matches a given hostname, email address, or IP address*/
            if (X509_check_host(cert, GetInterfaceConfig.ExpectedHostName.data() , GetInterfaceConfig.ExpectedHostName.size(), 0, nullptr) != 1)
            {
                fprintf(stderr, "Server Certificate verification error: Hostname mismatch %s!\n",__FUNCTION__);
                exit(1);
            }

            cout << "Verified server certificate successfully." << endl;

        }

        else
        {
            /*Connect to server*/
            connection_bio = BIO_new_connect(GetInterfaceConfig.DestinationIPandPort);

            /*For non blocking mode of connection*/
            if(!GetInterfaceConfig.IsBlocking)
            {
                BIO_set_nbio(connection_bio, 1);
            }

            /*Connect for port access*/
            if (BIO_do_connect(connection_bio) <= 0)
            {
                cout << "Error in BIO_do_connect!" << endl;
                exit(1);
            }

            /*Create SSL bio*/
            ssl_bio = BIO_new_ssl(ctx,1);
            if (ssl_bio == nullptr)
            {
                cout << "Error in BIO_get_ssl!" << endl;
                exit(1);
            }

            /*Chain SSL bio to socket connection bio*/
            BIO_push(ssl_bio, connection_bio);

            /*Get SSL session*/
            ssl = nullptr;
            BIO_get_ssl(ssl_bio, &ssl);

            if (ssl == nullptr)
            {
                cout << "Error in BIO_get_ssl!" << endl;
                exit(1);
            }

            /*Set hostname*/
            RetVal = SSL_set_tlsext_host_name(ssl,GetInterfaceConfig.ExpectedHostName.data());
            if(RetVal == 0)
            {
                cout << "Error in SSL_set_tlsext_host_name!" << endl;
                exit(1);
            }

            cout << "Client connected, performing TLS handshake..." << endl;

            /*Perform TLS handshake*/
            if (BIO_do_handshake(ssl_bio) <= 0)
            {
                cout << "Error in TLS handshake" << endl;
            }


            /*Verify server certificate*/
            int err = SSL_get_verify_result(ssl);
            if (err != X509_V_OK)
            {
                /*Verification error msg*/
                const char *message = X509_verify_cert_error_string(err);
                fprintf(stderr, "Certificate verification error: %s (%d) %s !\n", message, err, __FUNCTION__);
                exit(1);
            }

            /*Fetch peer certificate*/
            cert = SSL_get_peer_certificate(ssl);
            if (cert == nullptr)
            {
                fprintf(stderr, "No certificate was presented %s !\n",__FUNCTION__);
                exit(1);
            }

            /*Check whether a certificate matches a given hostname, email address, or IP address*/
            if (X509_check_host(cert, GetInterfaceConfig.ExpectedHostName.data() , GetInterfaceConfig.ExpectedHostName.size(), 0, nullptr) != 1)
            {
                fprintf(stderr, "Client Certificate verification error: Hostname mismatch %s !\n",__FUNCTION__);
                exit(1);
            }

            cout << "Verified client certificate successfully." << endl;

        }
    }    //==============================================
}

void Communication::BIORead(uint8_t * const buff, const int size)
{
    int len;

    /*Non secure configuration read*/
    if(!GetInterfaceConfig.ConfigParam.IsEnable)
    {
       len = BIO_read(unsec_bio, buff, size);
    }

    /*Secure configuration read*/
    else
    {
       len = BIO_read(ssl_bio, buff, size);
    }

    if(len > 0)
    {
        cout << "Length read : "<<buff<<len<<endl;

    }

    else if((len == 0) || (len == -1))
    {
        fprintf(stderr, "No data read : %s !\n", __FUNCTION__);
    }

    else if(len < -2)
    {
        fprintf(stderr, "Read operation failed! : %s !\n", __FUNCTION__);
    }

    return;
}

void Communication::BIOWrite(const uint8_t *const buff, const int size)
{
    int len;

    /*Non secure configuration write*/
    if(!GetInterfaceConfig.ConfigParam.IsEnable)
    {
        len = BIO_write(unsec_bio, buff, size);
    }

    /*Secure configuration write*/
    else
    {
        len = BIO_write(ssl_bio, buff, size);
    }

    if(len > 0)
    {
        cout << "Length written : "<<buff<<len<<endl;
    }

    else if((len == 0) || (len == -1))
    {
        fprintf(stderr, "No data write to server : %s !\n", __FUNCTION__);
    }

    else if(len < -2)
    {
        fprintf(stderr, "Write operation failed! : %s !\n", __FUNCTION__);
    }

    return;
}

Communication::~Communication()
{
    /*Free all allocations*/
    if(!GetInterfaceConfig.ConfigParam.IsEnable)
    {
        BIO_free_all(unsec_bio);
    }

    else
    {
        SSL_CTX_free(ctx);
        BIO_free_all(sec_bio);
        BIO_free_all(connection_bio);
        BIO_free_all(ssl_bio);
    }
}

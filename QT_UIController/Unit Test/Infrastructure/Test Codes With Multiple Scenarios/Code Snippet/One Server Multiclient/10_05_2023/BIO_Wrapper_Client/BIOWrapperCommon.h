/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes structures and enums definition used by BIOWrapper.cpp
***************************************************************************/
#ifndef BIOWRAPPERCOMMON_H
#define BIOWRAPPERCOMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Enum to define role either SERVER or CLIENT*/
enum Role
{
    SERVER = 0, /*SERVER role to be configured*/
    CLIENT      /*CLIENT role to be configured*/
};

/*Enums to define status of communication*/
enum CommStatus
{
    ERROR_STATUS_UNKNOWN_ERROR = -13,
    ERROR_STATUS_WAITING_TO_FINISH_CRYPTOGRAPHIC_ASYNC_OPERATION_ERROR = -12,/*TODO : Verify error*/
    ERROR_STATUS_WAITING_TO_FINISH_ASYNC_OPERATION_ERROR = -11 , /*TODO : Verify error*/
    ERROR_STATUS_WAITING_FOR_CONNECTION_ERROR = -10,             /*This error indicates waiting peer to reconnect*/
    ERROR_STATUS_PEER_CONNECTION_FAILURE_ERROR = -9,             /*This error indicates peer unable to connect*/
    ERROR_STATUS_SUDDEN_PEER_TERMINATION_ERROR = -8,             /*This error indicates peer suspended*/
    ERROR_STATUS_PEER_CONNECTION_ERROR = -7,                     /*This error indicates peer disconnected*/
    ERROR_STATUS_NOT_ENOUGH_DATA_TO_HANDSHAKE_ERROR = -6,        /*This error indicates insufficient data to handshake*/
    ERROR_STATUS_NOT_ENOUGH_READ_DATA_AVAILBLE_ERROR = -5,       /*This error indicates insufficient data to read*/
    ERROR_STATUS_NOT_ENOUGH_WRITE_DATA_AVAILBLE_ERROR = -4,      /*This error indicates insufficient data to write*/
    ERROR_STATUS_PROTOCOL_ERROR = -3,                            /*This error indicates protocol error*/
    ERROR_STATUS_WRITE_ERROR = -2,                 /*This error indicates write operation encountered an error*/
    ERROR_STATUS_READ_ERROR = -1,                  /*This error indicates read operation encountered an error*/
    STATUS_CONNECTION_DEFAULT = 0,           /*This indicates default state*/
    STATUS_SERVER_STARTED,                   /*This indicates server started successfuly*/
    STATUS_CLIENT_STARTED,                   /*This indicates client started successfuly*/
    STATUS_SECURED_COMMUNICATION_CONFIGURED, /*This indicates secure communication prerequisites configured successfuly*/
    STATUS_READ_SUCCESSFUL,                  /*This indicates read operation success*/
    STATUS_NO_DATA_AVAILABLE_TO_READ,        /*This indicates no data avaible to perform read operation*/
    STATUS_WRITE_SUCCESSFUL,                 /*This indicates write operation success*/
    STATUS_NO_DATA_WRITTEN,                  /*This indicates no data written on socket*/
    STATUS_CONNECTION_CLOSED_SECURELY,       /*This indicates connection clodes at peer side*/
};

/*Enum to define TLS Version to be used*/
enum TLSVersions
{
    TLS1_VERSION_0  = 0x0301,  /*TLS Version 0*/
    TLS1_VERSION_1  = 0x0302,  /*TLS Version 1*/
    TLS1_VERSION_2  = 0x0303,  /*TLS Version 2*/
    TLS1_VERSION_3  = 0x0304   /*TLS Version 3*/
};

/*Structure to define secure communication parametrs required*/
struct SecureConfig
{
    bool IsEnable ;                /*Use this to enable secure configuration*/
    std::string  ExpectedPeerName; /*Use this to configure Expected Peer Name*/
    const char*  SelfCertificate; /*Use this to configure Self Certificate*/
    const char*  SelfPrivateKey;  /*Use this to configure Self Private Key*/
    const char*  CACertificate;   /*Use this to configure CA Certificate*/
    const char*  PassKey;         /*Use this to configure Passkey*/
    TLSVersions  TLSVersionIs;    /*Use this to configure TLS Version*/
    const char*  CipherSuite;     /*Use this to select Ciphersuite*/
};

/*Structure to define communication parametrs required*/
struct CommConfig
{
    Role RoleIs;                        /*Use this for defining the role i.e either Server or Client*/
    const char*  DestinationIPandPort;  /*Use this for configuring destination IP and Port*/
    bool IsBlocking;                    /*Use this to configure Blocking or Non Blocking mode*/
    SecureConfig SecureConfigParam;     /*Use this structure to configure secure communications parameters*/
};

#endif // BIOWRAPPERCOMMON_H

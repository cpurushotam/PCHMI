/**************************************************************************

          Copyright (c) Branson Ultrasonics Corporation, 1996-2023

        This program is the property of Branson Ultrasonics Corporation
        Copying of this software is expressly forbidden, without the prior
        written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
This file includes enums used by BIOWrapper.cpp internally.
 
--------------------------- REVISION HISTORY ------------------------------
rev1: 18/05/2023 - Initial version
 
***************************************************************************/
#ifndef BIOWRAPPERINTERNAL_H
#define BIOWRAPPERINTERNAL_H

/*Enum to check whether configured inputs are valid or not*/
enum IsValidConfigurations
{
    IS_VALID_IP_AND_PORT = 1,   /*Enum to check role configured either SERVER or CLIENT*/
    IS_VALID_PEER_NAME,          /*Enum to check hostname to be configured*/
    IS_VALID_SELF_CERT,         /*Enum to check self certificate*/
    IS_VALID_SELF_PRIVATE_KEY,  /*Enum to check private Key*/
    IS_VALID_CA_CERTIFICATE,    /*Enum to check CA certificate*/
    IS_VALID_PASSKEY            /*Enum to check passkey provided*/
};

/*Function to check whether configured inputs are valid or not*/
bool IsValid(const char ParamString[], IsValidConfigurations Type);

#endif // BIOWRAPPERINTERNAL_H

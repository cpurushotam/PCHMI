/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Opcua Client Certificate related implementation
 
***************************************************************************/

#ifndef OPCUA_CLIENT_CERTIFICATE_UPLOAD_H_
#define OPCUA_CLIENT_CERTIFCATE_UPLOAD_H_

#include <queue>
#include "DataInterface.h"
#include "OpcuaClientCertificateStructure.h"

class OpcuaClientCertificateUpload : public DataInterface
{ 
public:
	
    OpcuaClientCertificateUpload();
    virtual ~OpcuaClientCertificateUpload();
    //QML will call this API , when user request to copy the Opcua Client certificate from the USB to Emmc
    void InitiateOpcuaClientCertificateCopyRequest
                        (std::string OpcuaClientCertFileName);

    //QML will call this API , when user request to read the USB connection status
    void InitiateOpcuaClientCertificateReadUSBRequest();

    //QML will call this API to update the Client Certificate Filename status. 
    bool GetOpcuaClientCertificateFileNameStatus();

    //QML will call this API to read Opcua Client Certificate File Name stored in the USB
    std::queue<OpcuaCertificateUploadStruct> GetOpcuaClientCertificateData();
    
    //QML will call this API to retrive the copy status from USB to Emmc 
    bool GetOpcuaClientCertifcateCopiedToEmmcStatus();

    //QML will call this API , when user request to save the IP adress & port of the PubSub Subscriber Node for unicast UDP mode
    void InitiateOpcuaCofigurationDataSaveRequest(OpcuaIpPortStruct OpcuaIpPortdata);

    //QML will call this API to retrive the Result code 
    OPCUA_CERTIFICATES_ERROR_CODES GetOpcuaClientCertifcateCopytoEmmcErrorCode();

    int GetData(MEMORY_BLOCK * const Destination) override;

    int SetData(const MEMORY_BLOCK *const Source) override;

private:
    
    size_t m_LogID;
    //to store list of Opcua Client Certificate File names
    std::queue<OpcuaCertificateUploadStruct> m_OpcuaCertificateUploadData;

    //Holds the Result code of the opcua client certificate upload from usb to emmc storage.
    OPCUA_CERTIFICATES_ERROR_CODES m_OpcuaCertificateUploadResult;
    //Holds the IP adress and Port Number of the PubSub subscriber Node.
    OpcuaIpPortStruct m_OpcuaPubSubIpPortStruct;
    
    //Read USB request is sent to ASC when this flag is true 
    bool m_SendOpcuaCertificateReadUsbRequest;
    //Read Opcua Client Certificate Copy request is sent to ASC when this flag is true
    bool m_SendOpcuaCertificateUploadRequest;
    //Holds the status whether file is copied from usb to emmc
    bool m_isOpcuaCertificateCopiedToEmmc;
    //Flag to update HMI upon Opcua File Name received from SC.
    bool m_isOpcuaClientCertificateFilenameRead;
    //Pubsub Subscriber IP adress & Port number is saved in DB when this flag is true
    bool m_InitiateOpcuaConfigurationDataSaveRequest;
    //Reads Pubsub Subscriber IP adress & Port number from DB when this flag is true
    bool m_InitiateOpcuaConfigurationDataReadRequest;
    
    void SendOpcuaClientCertificateReadUsbRequest(MEMORY_BLOCK * const Destination);
    void SendCopyOpcuaCertificateUsbToEmmcRequest(MEMORY_BLOCK * const Destination);
    void ProcessOpcuaClientCertificateReadUsbResponse(const MEMORY_BLOCK *const Source);
    void ProcessOpcuaClientCertificateUploadResponse(const MEMORY_BLOCK *const Source);
    void SendOpcuaCofigurationDataSaveRequestToASC(MEMORY_BLOCK * const Destination);
    void SendOpcuaCofigurationDataReadRequestToASC(MEMORY_BLOCK * const Destination);
    void ProcessOpcuaCofigurationDataReadRequestFromASC(const MEMORY_BLOCK *const Source);

};

#endif /* OPCUA_CLIENT_CERTIFCATE_UPLOAD_H_ */

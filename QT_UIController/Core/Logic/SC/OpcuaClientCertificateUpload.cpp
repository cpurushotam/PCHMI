/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Opcua Client Certificate related implementation
 
***************************************************************************/
#include <cstring>
#include "OpcuaClientCertificateUpload.h"
#include "DataLogger.h"

/******************************************************************************
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
OpcuaClientCertificateUpload::OpcuaClientCertificateUpload()
{
	//enroll to use logger functionality
    m_SendOpcuaCertificateReadUsbRequest = false;
    m_SendOpcuaCertificateUploadRequest = false;
    m_isOpcuaCertificateCopiedToEmmc = false;
    m_isOpcuaClientCertificateFilenameRead = false;
    m_OpcuaCertificateUploadResult = OPCUA_CERTIFICATES_ERROR_UNKNOWN;
	m_InitiateOpcuaConfigurationDataSaveRequest = false;
	//Send the request to read the OpcuaConfiguration data
	m_InitiateOpcuaConfigurationDataReadRequest = true;
}

/******************************************************************************
*
* \brief   - destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
OpcuaClientCertificateUpload::~OpcuaClientCertificateUpload()
{

}

/*****************************************************************************
*
* \brief   - QML should call this method to initiate Opcua Client Certificate copy
* Request
*
* \param   - ClientCertifcateFileName, PrivateKeyFilename - Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::InitiateOpcuaClientCertificateCopyRequest
                        (std::string OpcuaClientCertFileName)
{
    std::queue<OpcuaCertificateUploadStruct> OpcuaCertificateUploadEmptyData;
    //to clear the queue
    std::swap(m_OpcuaCertificateUploadData,OpcuaCertificateUploadEmptyData);

    OpcuaCertificateUploadStruct UpgradeFile;
    strncpy(UpgradeFile.OpcuaCertificateFileName, OpcuaClientCertFileName.c_str(), sizeof(OpcuaClientCertFileName));
    m_OpcuaCertificateUploadData.push(UpgradeFile);    
    m_SendOpcuaCertificateUploadRequest = true;
}

/******************************************************************************
*
* \brief   - QML should call this method to initiate read USB request for Opcua Client Certificate
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::InitiateOpcuaClientCertificateReadUSBRequest()
{
    m_SendOpcuaCertificateReadUsbRequest = true;
}

/******************************************************************************
*
* \brief   - send the request to ASC server for Opcua Client Certifcate
* and Ip, PortNumber memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int OpcuaClientCertificateUpload::GetData(MEMORY_BLOCK * const Destination)
{
    int RetVal = 0;

    if((Destination != nullptr) && ((Destination->id == MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA)||(Destination->id == MB_ID_OPCUA_PUBSUB_DATA)))
    { 
		switch (Destination->sub_id)
		{
			//Send OPCUA Client certificate read request to ASC
			case MB_READ_OPCUA_CERTIFICATE_FROM_USB_REQUEST:
			{
				RetVal = 0;
				SendOpcuaClientCertificateReadUsbRequest(Destination);
				break;
			}
			//Send OPCUA Client certificate copy request from USB to mmc1 of ASC
			case MB_COPY_OPCUA_CERTIFICATE_USB_EMMC_REQUEST:
			{
				RetVal = 0;
				SendCopyOpcuaCertificateUsbToEmmcRequest(Destination);
				break;
			}
			//Send OPCUA data save request to ASC
			case MB_WRITE_OPCUA_PUBSUB_IP_PORT:
			{
				RetVal = 0;
				SendOpcuaCofigurationDataSaveRequestToASC(Destination);
				break;
			}
			//Send OPCUA data read request to ASC
			case MB_READ_OPCUA_PUBSUB_IP_PORT:
			{
				RetVal = 0;
				SendOpcuaCofigurationDataReadRequestToASC(Destination);
				break;
			}
			default:
			{
				Destination->size = 0;
				// clear valid bit
				Destination->config = 0;
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM,
					"Opcua Client Certificate upload GetData default case");
				break;
			}
		}
    }
    else
    {
    	Destination->size = 0;
        // clear valid bit
    	Destination->config = 0;
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Opcua Client Certificate upload GetData invalid MB ID");
    }
    return RetVal;
}

/******************************************************************************
*
* \brief   - process the data coming from ASC server for Opcua Client Certificate
* and Ip, PortNumber memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int OpcuaClientCertificateUpload::SetData(const MEMORY_BLOCK *const Source)
{
    int RetVal = 0;

    if( (Source != nullptr) && ((Source->id == MB_ID_OPCUA_CLIENT_CERTIFICATE_UPLOAD_DATA)||(Source->id == MB_ID_OPCUA_PUBSUB_DATA)))
    {
        if( (Source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(Source->sub_id)
            {
                case MB_READ_OPCUA_CERTIFICATE_FROM_USB_REQUEST:
                {
                	RetVal = 0;
                    ProcessOpcuaClientCertificateReadUsbResponse(Source);                    
                    break;
                }
                
                case MB_COPY_OPCUA_CERTIFICATE_USB_EMMC_REQUEST:
                {
                	RetVal = 0;
                    ProcessOpcuaClientCertificateUploadResponse(Source);
                    break;
                }
        		
        		case MB_READ_OPCUA_PUBSUB_IP_PORT:
        		{
        			RetVal = 0;
        			ProcessOpcuaCofigurationDataReadRequestFromASC(Source);
        			break;
        		}
        		
                default:
                {
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Opcua Client Certificate upload SetData default case");
                    break;
                }
            }
        }
        else
        {
        	RetVal = 0;
        }
    }
    else
    {
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, "Opcua Client Certificate upload SetData invalid MB ID");
    }
    return RetVal;
}

/******************************************************************************
*
* \brief   - Send the USB read request to ASC for Opcua Client Certificate
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::SendOpcuaClientCertificateReadUsbRequest(MEMORY_BLOCK * const Destination)
{
    if(Destination->size >= sizeof(bool))
    {
        if(m_SendOpcuaCertificateReadUsbRequest == true)
        {
        	Destination->data = 0;
        	Destination->size = sizeof(bool);
        	Destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendOpcuaCertificateReadUsbRequest = false;
        }
        else
        {
        	Destination->size = 0;
        	Destination->config = VALID_BIT;
        }
    }
    else
    {
    	Destination->size = 0;
    	Destination->config = 0;
    }
}

/******************************************************************************
*
* \brief   - Send request to copy the Opcua Client Certificate from USB to Emmc
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::SendCopyOpcuaCertificateUsbToEmmcRequest(MEMORY_BLOCK * const Destination)
{    
    if(Destination->size >= (sizeof(OpcuaCertificateUploadStruct) * m_OpcuaCertificateUploadData.size()))
    {        
        if(m_SendOpcuaCertificateUploadRequest == true)
        {           
            OpcuaCertificateUploadStruct *OpcuaClientCertificateFiles = reinterpret_cast<OpcuaCertificateUploadStruct *>(Destination->data);
            int DataSize = 0;
            std::queue<OpcuaCertificateUploadStruct> TempQueue = m_OpcuaCertificateUploadData;
            while (!TempQueue.empty())
            {                
                *OpcuaClientCertificateFiles = TempQueue.front();
                TempQueue.pop();               
                OpcuaClientCertificateFiles++;

                DataSize += sizeof(OpcuaCertificateUploadStruct);
            }
            Destination->size = DataSize;
            Destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendOpcuaCertificateUploadRequest = false;
        }
        else
        {
        	Destination->size = 0;
        	Destination->config = VALID_BIT;
        }
    }
    else
    {
    	Destination->size = 0;
    	Destination->config = 0;
    }
}

/******************************************************************************
*
* \brief   - Process Opcua Client Certificate File Name coming from USB Stick(ASC).
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::ProcessOpcuaClientCertificateReadUsbResponse(const MEMORY_BLOCK *const Source)
{
    int *NumberOfFilesRead = reinterpret_cast<int *>(Source->data);
    OpcuaCertificateUploadStruct *Data = reinterpret_cast<OpcuaCertificateUploadStruct *>(Source->data + sizeof(int));
    std::queue<OpcuaCertificateUploadStruct> OpcuaCertificateUploadEmptyData;

    //to clear the queue
    std::swap(m_OpcuaCertificateUploadData,OpcuaCertificateUploadEmptyData);
    if(m_isOpcuaClientCertificateFilenameRead == false)
    {
        for(int FileNumber = 0; FileNumber < *NumberOfFilesRead; FileNumber++)
        {
            OpcuaCertificateUploadStruct FileName;
            strncpy(FileName.OpcuaCertificateFileName, Data->OpcuaCertificateFileName, sizeof(FileName.OpcuaCertificateFileName));
            m_OpcuaCertificateUploadData.push(FileName);
            Data++;
        }
        m_isOpcuaClientCertificateFilenameRead = true;
    }
}

/******************************************************************************
*
* \brief   - Process the Opcua Client Certificate response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload::ProcessOpcuaClientCertificateUploadResponse(const MEMORY_BLOCK *const Source)
{ 
        int *Data = reinterpret_cast<int *>(Source->data);
        memcpy(&m_OpcuaCertificateUploadResult,Data,sizeof(int));
        m_isOpcuaCertificateCopiedToEmmc = true;
}
/******************************************************************************
*
* \brief   - return Read USB status
*
* \param   - none
*
* \return  - bool - m_isUSBRead
*
******************************************************************************/
bool OpcuaClientCertificateUpload::GetOpcuaClientCertificateFileNameStatus()
{
    return m_isOpcuaClientCertificateFilenameRead;
}

/******************************************************************************
*
* \brief   - return Opcua Client Certificates copy Status
*
* \param   - none
*
* \return  - bool - Certificates Copy Status
*
******************************************************************************/
bool OpcuaClientCertificateUpload::GetOpcuaClientCertifcateCopiedToEmmcStatus()
{
    return m_isOpcuaCertificateCopiedToEmmc;
}

/******************************************************************************
*
* \brief   - Retriving the Opcua Client Certificate Filename stored in USB stick
* \param   - none

* \return  - Opcua Client Certificate Filename
*
******************************************************************************/
std::queue<OpcuaCertificateUploadStruct> OpcuaClientCertificateUpload::GetOpcuaClientCertificateData()
{
    std::queue<OpcuaCertificateUploadStruct> ReadUSBData;
    ReadUSBData = m_OpcuaCertificateUploadData;
    //Reset the flag to false once the value is read
    m_isOpcuaClientCertificateFilenameRead = false;

    return ReadUSBData;
}

/******************************************************************************
*
* \brief   - return the Opcua Client Certifcate Copy error code
*
* \param   - none

* \return  - copy of Opcua Client Certifcate  data error code
*
******************************************************************************/
OPCUA_CERTIFICATES_ERROR_CODES OpcuaClientCertificateUpload::GetOpcuaClientCertifcateCopytoEmmcErrorCode()
{
    OPCUA_CERTIFICATES_ERROR_CODES OpcuaCertificateUploadResult = m_OpcuaCertificateUploadResult;
    m_isOpcuaCertificateCopiedToEmmc = false;
    return OpcuaCertificateUploadResult;
}

/******************************************************************************
*
* \brief   - call this method on HMI side when you click save button.
*
* \param   - None.
*
* \return  - None
*
******************************************************************************/
void OpcuaClientCertificateUpload::InitiateOpcuaCofigurationDataSaveRequest(OpcuaIpPortStruct OpcuaIpPortdata)
{
	m_OpcuaPubSubIpPortStruct = OpcuaIpPortdata;
	m_InitiateOpcuaConfigurationDataSaveRequest = true;
}
/******************************************************************************
*
* \brief   - send the Opcua Configuration Data save request to ASC.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - None.
*
******************************************************************************/
void OpcuaClientCertificateUpload :: SendOpcuaCofigurationDataSaveRequestToASC(MEMORY_BLOCK * const Destination)
{
	if(Destination->size >=sizeof(OpcuaIpPortStruct))
	{
		if(m_InitiateOpcuaConfigurationDataSaveRequest == true)
		{
			// update size in destination
			Destination->size = sizeof(OpcuaIpPortStruct);

			// set valid bit
			Destination->config = VALID_BIT;
			m_InitiateOpcuaConfigurationDataSaveRequest = false;

			OpcuaIpPortStruct *OpcuaIpPortData = reinterpret_cast<OpcuaIpPortStruct *>(Destination->data);

			memcpy(&OpcuaIpPortData->IpAddress[0], &m_OpcuaPubSubIpPortStruct.IpAddress[0], sizeof(OpcuaIpPortStruct));
		}
		else
		{
			Destination->size = 0;
			Destination->config = VALID_BIT;
		}
	}
	else
	{
		Destination->size = 0;
		Destination->config = 0;
	}
}

/******************************************************************************
*
* \brief   - Send a Opcua Configuration data read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void OpcuaClientCertificateUpload :: SendOpcuaCofigurationDataReadRequestToASC(MEMORY_BLOCK * const Destination)
{
    if(Destination->size >= sizeof(int))
    {
        if( m_InitiateOpcuaConfigurationDataReadRequest == true)
        {
        	Destination->size = sizeof(int);
        	Destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateOpcuaConfigurationDataReadRequest = false;
        }
        else
        {
        	Destination->size = 0;
        	Destination->config = VALID_BIT;
        }
    }
    else
    {
    	Destination->size = 0;
    	Destination->config = 0;
    }
}

/******************************************************************************
*
* \brief   - process the Opcua Configuration data coming from ASC
*
* \param   - source - memory block holding the Opcua Configuration data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void OpcuaClientCertificateUpload :: ProcessOpcuaCofigurationDataReadRequestFromASC(const MEMORY_BLOCK *const Source)
{
	//copy incoming data to structure member variable
	OpcuaIpPortStruct *OpcuaConfigData = reinterpret_cast<OpcuaIpPortStruct *>(Source->data);
	memcpy(&m_OpcuaPubSubIpPortStruct, OpcuaConfigData, sizeof(m_OpcuaPubSubIpPortStruct));
}


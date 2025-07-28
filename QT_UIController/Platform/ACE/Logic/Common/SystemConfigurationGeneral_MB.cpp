/**************************************************************************

            Copyright (c) Branson Ultrasonics Corporation, 1996-2023

            This program is the property of Branson Ultrasonics Corporation
            Copying of this software is expressly forbidden, without the prior
            written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

            This file contains the SystemConfigurationGeneral screen related information

***************************************************************************/
#include <iostream>
#include <unistd.h>
#include "SysConfgGenStructureAce.h"
#include "SystemConfigurationGeneral_MB.h"
#include <string.h>
#include "MultiwelderInterface.h"

/**************************************************************************//**
* \brief - Constructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
SystemConfigurationGeneral_MB::SystemConfigurationGeneral_MB()
{
	m_IsDataUpdated = false;
	m_SendKeyVerifyRequest = false;
    m_SendResetToDefaultRequest = false;
    m_InitiateSaveRequest = false;
    m_InitiateSysConfigGenrealReadReq =true;
    m_IsBransonServiceUserLoggedIn = false;
    m_IsKeyVerifyDataRead = false;
	m_SysConfigUpdateProcessStatus = SYSTEM_CONFIG_UPDATE_FAILURE;
}

/**************************************************************************//**
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
SystemConfigurationGeneral_MB::~SystemConfigurationGeneral_MB()
{
}

/**************************************************************************//**
*
* \brief   - Read System Configuration General screen related data.
*            Read operation is performed based on Sub_ID of MB
*
* \param   - Address of destination MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SystemConfigurationGeneral_MB::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    // check parameter
    if((destination != NULL) && (destination->id == MB_ID_SYSTEM_CONFIG_GENERAL_DATA) && (destination->size >=sizeof(SystemConfigGeneralStruct)))
    {
        // perform operation based on sub id
        switch(destination->sub_id)
        {

        case SUB_ID_SYSTEM_CONFIG_GEN_UPDATE_DATA:
        {
            SystemConfigGeneralStruct *ptr_SystemConfigGenData = reinterpret_cast<SystemConfigGeneralStruct *>(destination->data);

            if(m_InitiateSaveRequest)
            {
                ptr_SystemConfigGenData->currUnit = this->m_SystemConfigGenScreenData.currUnit;
                ptr_SystemConfigGenData->AuthorityCheck=this->m_SystemConfigGenScreenData.AuthorityCheck;
                ptr_SystemConfigGenData->memoryFullAction=this->m_SystemConfigGenScreenData.memoryFullAction;
                strncpy( ptr_SystemConfigGenData->BarcodeRecipePrefix,this->m_SystemConfigGenScreenData.BarcodeRecipePrefix,BARCODE_RECIPE_PRFX_SIZE);
                ptr_SystemConfigGenData->powerupoption=this->m_SystemConfigGenScreenData.powerupoption;
                strncpy(ptr_SystemConfigGenData->welderName,this->m_SystemConfigGenScreenData.welderName,MAX_WELDER_NAME_LENGTH );
                ptr_SystemConfigGenData->ClearMemoryAtPowerup=this->m_SystemConfigGenScreenData.ClearMemoryAtPowerup;
                ptr_SystemConfigGenData->ClearMemoryWithReset=this->m_SystemConfigGenScreenData.ClearMemoryWithReset;
                ptr_SystemConfigGenData->PartID=this->m_SystemConfigGenScreenData.PartID;
                ptr_SystemConfigGenData->ParallelWeldResultStorageStatus = this->m_SystemConfigGenScreenData.ParallelWeldResultStorageStatus;
                ptr_SystemConfigGenData->ClampOnAlarm = this->m_SystemConfigGenScreenData.ClampOnAlarm;
                ptr_SystemConfigGenData->WeldRecipeUniqueSerialNumGenStatus = this->m_SystemConfigGenScreenData.WeldRecipeUniqueSerialNumGenStatus;
                ptr_SystemConfigGenData->ASCIPAddress = this->m_SystemConfigGenScreenData.ASCIPAddress;
                destination->size = sizeof(SystemConfigGeneralStruct);
                m_IsDataUpdated=false;
                m_InitiateSaveRequest = false;
            }
            else
            {
                destination->size = 0;
            }

            // set valid bit
            destination->config = VALID_BIT;

            // update retval to success
            retVal = 0;

            break;
        }

        case SUB_ID_SYSTEM_CONFIG_GEN_RESET_TO_DEFAULT_REQUEST:
        {
        	if (m_SendResetToDefaultRequest == true)
        	{
        		m_SendResetToDefaultRequest = false;
        		destination->size = sizeof(int);
        	}
        	else
        	{
        		destination->size = 0;
        	}

        	// set valid bit
        	destination->config = VALID_BIT;

        	// update retval to success
        	retVal = 0;

        	break;
        }

        case SUB_ID_SYSTEM_CONFIG_GEN_KEY_VERIFY_REQUEST:
        {
        	if (m_SendKeyVerifyRequest == true)
            {
            	// copy key data to sent to ASC
            	strncpy(reinterpret_cast<char*>(destination->data), this->m_SystemConfigGenScreenData.key, SERVICE_KEY_SIZE);

            	m_SendKeyVerifyRequest = false;
            	destination->size = SERVICE_KEY_SIZE;
            }
            else
            {
            	destination->size = 0;
            }

            // set valid bit
            destination->config = VALID_BIT;

            // update retval to success
            retVal = 0;

        	break;
        }
        case SUB_ID_SYSTEM_CONFIG_GEN_READDATA:
        {
            //Re-read data from ASC.
            retVal = 0;
            SendSysConfigGeneralReadRequestToASC(destination);
            break;
        }
        case SUB_ID_SYSTEM_CONFIG_GEN_RESET_BRSNSRVC_KEY:
        {

            //Re-read data from ASC.
            retVal = 0;
            SendSysConfigGeneralResetBrsnSrvcKey(destination);
            break;
        }

        default:
        {
            // Error ! default retVal (failure) will be returned
            // clear valid bit, reset size
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            break;
        }
        }
    }
    else
    {
        // error! invalid sub-id, default retVal (failure) will be returned
        // clear valid bit, reset size
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
    }
    return (retVal);
}

/**************************************************************************//**
*
* \brief   - Note:Write system general tab data. Write operation is performed based on Sub_ID of MB
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SystemConfigurationGeneral_MB::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;
    // check parameter
    if((source != NULL) && (source->id == MB_ID_SYSTEM_CONFIG_GENERAL_DATA) && ((source->config & VALID_BIT) == (VALID_BIT)))
    {
        // perform operation based on sub id
        switch(source->sub_id)
        {

        case SUB_ID_SYSTEM_CONFIG_GEN_READDATA:
        {
            // cast MB data pointer to SystemConfigGeneralStruct for easy access
            SystemConfigGeneralStruct *ptr_SystemConfigGenData = reinterpret_cast<SystemConfigGeneralStruct *>(source->data);
            // Copy the System Configuration General data to destination
            this->m_SystemConfigGenScreenData.currUnit = ptr_SystemConfigGenData->currUnit;
            strncpy(this->m_SystemConfigGenScreenData.BarcodeRecipePrefix ,ptr_SystemConfigGenData->BarcodeRecipePrefix,BARCODE_RECIPE_PRFX_SIZE);
            this->m_SystemConfigGenScreenData.memoryFullAction =ptr_SystemConfigGenData->memoryFullAction;
            this->m_SystemConfigGenScreenData.AuthorityCheck =ptr_SystemConfigGenData->AuthorityCheck;
            this->m_SystemConfigGenScreenData.powerupoption =ptr_SystemConfigGenData->powerupoption;
            strncpy(this->m_SystemConfigGenScreenData.welderName ,ptr_SystemConfigGenData->welderName,MAX_WELDER_NAME_LENGTH );
            this->m_SystemConfigGenScreenData.ClearMemoryAtPowerup = ptr_SystemConfigGenData->ClearMemoryAtPowerup;
            this->m_SystemConfigGenScreenData.ClearMemoryWithReset = ptr_SystemConfigGenData->ClearMemoryWithReset;
            this->m_SystemConfigGenScreenData.PartID = ptr_SystemConfigGenData->PartID;
            this->m_SystemConfigGenScreenData.ParallelWeldResultStorageStatus = ptr_SystemConfigGenData->ParallelWeldResultStorageStatus;
            this->m_SystemConfigGenScreenData.ClampOnAlarm = ptr_SystemConfigGenData->ClampOnAlarm;
            this->m_SystemConfigGenScreenData.WeldRecipeUniqueSerialNumGenStatus = ptr_SystemConfigGenData->WeldRecipeUniqueSerialNumGenStatus;
            this->m_SystemConfigGenScreenData.ASCIPAddress = ptr_SystemConfigGenData->ASCIPAddress;
            SystemConfigurationGeneral_MB::m_IsDataUpdated = true;
            m_DataChanged =true;
            m_IsDataAvailable = true;
            // update retval to success
            retVal = 0;

            break;
        }

        case SUB_ID_SYSTEM_CONFIG_GEN_RESULT:
		{
			// cast MB data pointer to int for easy access
			int* pSysConfigUpdateProcessStatus = reinterpret_cast<int*>(source->data);

			m_SysConfigUpdateProcessStatus = *pSysConfigUpdateProcessStatus;

			// update retval to success
			retVal = 0;

        	break;
		}

        case SUB_ID_SYSTEM_CONFIG_GEN_KEY_VERIFY_REQUEST:
        {
        	KEY_VERIFY_STATUS SysKeyVerificationProcessStatus = KEY_VERIFY_FAILURE;;

        	//cast MB data pointer to KEY_VERFIY enum for access
        	KEY_VERIFY_STATUS *pSysKeyVerificationStatus = reinterpret_cast<KEY_VERIFY_STATUS*>(source->data);

        	SysKeyVerificationProcessStatus = *pSysKeyVerificationStatus;

        	if(SysKeyVerificationProcessStatus == KEY_VERIFY_SUCCESS)
        	{
        		m_IsBransonServiceUserLoggedIn = true;
        	}
            m_IsKeyVerifyDataRead = true;
        	retVal = 0;

        	break;
        }

        default:
        {
            // Error ! default retVal (failure) will be returned
            break;
        }
        }
    }
    else
    {
        // error! parameter check failed, default retVal (failure) will be returned
    }
    return (retVal);
}



/**************************************************************************//**
*
* \brief   - Send a System Configuration General read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SystemConfigurationGeneral_MB::SendSysConfigGeneralReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_InitiateSysConfigGenrealReadReq == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_InitiateSysConfigGenrealReadReq = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}

/**************************************************************************//**
*
* \brief   - Send a Brason Service Key Reset request to ASC.
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  -  none
*
******************************************************************************/
void SystemConfigurationGeneral_MB::SendSysConfigGeneralResetBrsnSrvcKey(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(int))
    {
        if( m_ResetBransonServiceKey == true)
        {
            destination->size = sizeof(int);
            destination->config = VALID_BIT;

            //Reset the flag to false as we have sent the request.
            m_ResetBransonServiceKey = false;
        }
        else
        {
            destination->size = 0;
            destination->config = VALID_BIT;
        }
    }
    else
    {
        destination->size = 0;
        destination->config = 0;
    }
}
/**************************************************************************//**
*
* \brief   - setSystemDetailsFromHMI - Function updates the m_SystemConfigGenScreenData structure with the data on HMI .
*
* \param   - Instance of SystemConfigGeneralStruct.
*
* \return  -
*
******************************************************************************/
void SystemConfigurationGeneral_MB::setSystemDetailsFromHMI(SystemConfigGeneralStruct Local_SystemConfigGeneralStruct)
{
    m_SystemConfigGenScreenData.currUnit=Local_SystemConfigGeneralStruct.currUnit;
    m_SystemConfigGenScreenData.AuthorityCheck=Local_SystemConfigGeneralStruct.AuthorityCheck;
    m_SystemConfigGenScreenData.memoryFullAction=Local_SystemConfigGeneralStruct.memoryFullAction;
    m_SystemConfigGenScreenData.powerupoption=Local_SystemConfigGeneralStruct.powerupoption;
    m_SystemConfigGenScreenData.ClearMemoryAtPowerup=Local_SystemConfigGeneralStruct.ClearMemoryAtPowerup;
    m_SystemConfigGenScreenData.ClearMemoryWithReset=Local_SystemConfigGeneralStruct.ClearMemoryWithReset;
    m_SystemConfigGenScreenData.PartID=Local_SystemConfigGeneralStruct.PartID;
    m_SystemConfigGenScreenData.ParallelWeldResultStorageStatus = Local_SystemConfigGeneralStruct.ParallelWeldResultStorageStatus;
    m_SystemConfigGenScreenData.ClampOnAlarm = Local_SystemConfigGeneralStruct.ClampOnAlarm;
    strncpy( m_SystemConfigGenScreenData.BarcodeRecipePrefix, (Local_SystemConfigGeneralStruct.BarcodeRecipePrefix),BARCODE_RECIPE_PRFX_SIZE);
    strncpy( m_SystemConfigGenScreenData.welderName, (Local_SystemConfigGeneralStruct.welderName),MAX_WELDER_NAME_LENGTH );
    m_SystemConfigGenScreenData.WeldRecipeUniqueSerialNumGenStatus = Local_SystemConfigGeneralStruct.WeldRecipeUniqueSerialNumGenStatus;
    m_SystemConfigGenScreenData.ASCIPAddress = Local_SystemConfigGeneralStruct.ASCIPAddress;
    m_DataChanged =true;
    m_ConfigGeneralDataUpdated = true;
    m_InitiateSaveRequest = true;
}

/**************************************************************************//**
*
* \brief   - GetSystemDetailsFromASC - Function to return updated m_SystemConfigGenScreenData structure.
*
* \param   -
*
* \return  - m_SystemConfigGenScreenData
*
******************************************************************************/
SystemConfigGeneralStruct SystemConfigurationGeneral_MB::GetSystemDetailsFromASC()
{
    return m_SystemConfigGenScreenData;
}

/**************************************************************************//**
*
* \brief   - Read the current unit type from cache from system configuration data
*
* \param   - none 
* 
* \return  - returns current unit value.
*
******************************************************************************/
UNIT SystemConfigurationGeneral_MB::GetSystemUnitType()
{
    return m_SystemConfigGenScreenData.currUnit;
}

/**************************************************************************//**
*
* \brief   - Read the Authority Check from system configuration data
*
* \param   - none
*
* \return  - returns Authority Check staus
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::GetAuthorityCheck()
{
    if(m_SystemConfigGenScreenData.AuthorityCheck == BASIC)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**************************************************************************//**
*
* \brief   - Update HMI if the data is updated.
*
* \param   - none
*
* \return  - m_DataChanged.
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::getDataUpdatedFlag(){
    return m_DataChanged;
}
/**************************************************************************//**
*
* \brief   - Reset the flag to false after reading data
*
* \param   - none
*
* \return  - none.
*
******************************************************************************/
void SystemConfigurationGeneral_MB::setDataUpdatedFlag()
{

     m_DataChanged = false;
}
/**************************************************************************//**
*
* \brief   - Update HMI if the data is updated from ASC.
*
* \param   - none
*
* \return  - m_DataChanged.
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::getIsDataAvailableFlag()
{
     return m_IsDataAvailable;
}
/**************************************************************************//**
*
* \brief   - Reset the flag to false after reading data.
*
* \param   - none
*
* \return  - none.
*
******************************************************************************/
void SystemConfigurationGeneral_MB::setIsDataAvailableFlag()
{

     m_IsDataAvailable = false;
}
/**************************************************************************//**
*
* \brief   - Update Global User Setting Screen if System general data is updated.
*
* \param   - none
*
* \return  - m_ConfigGeneralDataUpdated.
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::getSysGeneralDataChangeFlag(){
    return m_ConfigGeneralDataUpdated;
}
/**************************************************************************//**
*
* \brief   - Reset the flag to false after reading data
*
* \param   - none
*
* \return  - none.
*
******************************************************************************/
void SystemConfigurationGeneral_MB::setSysGeneralDataChangeFlag()
{
    m_ConfigGeneralDataUpdated = false;
}
/**************************************************************************//**
*
* \brief   - HMI side code uses this method to decide when it needs to read the
*			  data present in the m_SystemConfigGenScreenData.
*			 When the data in the m_SystemConfigGenScreenData gets updated, then we
*			 set m_IsDataUpdated flag to true. HMI then rereads the
*			 m_SystemConfigGenScreenData and shows the updated data.
* \param   - none
*
* \return  - returns true when data is updated else
* 			 returns false
******************************************************************************/
bool SystemConfigurationGeneral_MB::IsDataUpdated()
{
    return SystemConfigurationGeneral_MB::m_IsDataUpdated;
}
/**************************************************************************//**
*
* \brief   - SetIsDataUpdated is used to set m_IsDataUpdated true or false if
*            data needs to be updated on HMI or not
*
* \param   - bool isUpdate
*
* \return  - None
*
******************************************************************************/

void SystemConfigurationGeneral_MB::SetIsDataUpdated(bool isUpdate)
{
    SystemConfigurationGeneral_MB::m_IsDataUpdated =isUpdate;
}

/**************************************************************************//**
*
* \brief   - This function is used to set m_SendKeyVerifyRequest to true and send
*            key entered by user to ASC for verification.
*
* \param   - std::string - key entered by user
*
* \return  - None
*
******************************************************************************/
void SystemConfigurationGeneral_MB::SetKeyVerifyRequest(std::string key)
{
    strncpy(m_SystemConfigGenScreenData.key, key.c_str(),SERVICE_KEY_SIZE);
    m_SendKeyVerifyRequest = true;
}

/**************************************************************************//**
*
* \brief  - This method is used to get the system config update process status.
*
* \param  - None
*
* \return - Returns fetched configuration update or Key processed status from ASC().
*
******************************************************************************/
int SystemConfigurationGeneral_MB::GetSystConfigUpdateProcessStatus()
{
	return m_SysConfigUpdateProcessStatus;
}

/**************************************************************************//**
*
* \brief  - This method is used by HMI/QML to know if Branson Service
*           person is logged in successfully or not.
*
* \param  - None.
*
* \return - Returns fetched Key verification processed status from ASC.
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::IsBransonServiceUserLoggedIn()
{
	return m_IsBransonServiceUserLoggedIn;
}

/**************************************************************************//**
*
* \brief   - Set the ResetToDefault system config Request from HMI.
*
* \param   - bool value.
*
* \return  - none
*
******************************************************************************/
void SystemConfigurationGeneral_MB::SetSystConfigResetToDefaultRequest()
{
    m_SendResetToDefaultRequest = true;
}

/**************************************************************************//**
*
* \brief   - Print System configuration Data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SystemConfigurationGeneral_MB::PrintSysConfigData()
{
	std::cout << "********** System Config Data**********" << std::endl;
	std::cout << "currUnit: " << m_SystemConfigGenScreenData.currUnit << std::endl;
	std::cout << "AuthorityCheck: " << m_SystemConfigGenScreenData.AuthorityCheck << std::endl;
	std::cout << "memoryFullAction: " << m_SystemConfigGenScreenData.memoryFullAction << std::endl;
	std::cout << "powerupoption: " << m_SystemConfigGenScreenData.powerupoption << std::endl;
	std::cout << "ClearMemoryAtPowerup: " << m_SystemConfigGenScreenData.ClearMemoryAtPowerup << std::endl;
	std::cout << "ClearMemoryWithReset: " << m_SystemConfigGenScreenData.ClearMemoryWithReset << std::endl;
	std::cout << "PartID: " << m_SystemConfigGenScreenData.PartID << std::endl;
    std::cout << "ParallelWeldResultStorageStatus: " << m_SystemConfigGenScreenData.ParallelWeldResultStorageStatus << std::endl;
	std::cout << "BarcodeRecipePrefix: " << m_SystemConfigGenScreenData.BarcodeRecipePrefix << std::endl;
	std::cout << "key: " << m_SystemConfigGenScreenData.key << std::endl;
	std::cout << "welderName: " << m_SystemConfigGenScreenData.welderName << std::endl;
    std::cout << "ClampOnAlarm: " << m_SystemConfigGenScreenData.ClampOnAlarm << std::endl;
    std::cout << "WeldRecipeUniqueSerialNumGenStatus: " << m_SystemConfigGenScreenData.WeldRecipeUniqueSerialNumGenStatus << std::endl;
    std::cout << "ASCIPAddress: " << m_SystemConfigGenScreenData.ASCIPAddress << std::endl;
	std::cout << "*************************************" << std::endl;
}

/**************************************************************************//**
*
* \brief   - return Authority Check Status.
*
* \param   - none
*
* \return  - int - Authority Check Status
*
******************************************************************************/
int SystemConfigurationGeneral_MB::GetAuthortiyCheckStatus()
{
    return m_SystemConfigGenScreenData.AuthorityCheck;
}

/**************************************************************************//**
*
* \brief   - return key verify data read Status.
*
* \param   - none
*
* \return  - bool - m_IsKeyVerifyDataRead
*
******************************************************************************/
bool SystemConfigurationGeneral_MB::GetKeyVerifyDataReadStatus()
{
    return m_IsKeyVerifyDataRead;
}
/**************************************************************************//**
*
* \brief   - return key verify data read Status.
*
* \param   - none
*
* \return  - bool - m_IsKeyVerifyDataRead
*
******************************************************************************/
void SystemConfigurationGeneral_MB::ResetBrsnSrvcKeyVerifyStatus()
{
    m_ResetBransonServiceKey = true;
}
/**************************************************************************//**
*
* \brief   - Reset key verify data read status.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SystemConfigurationGeneral_MB::ResetKeyVerifyDataReadStatus()
{
    m_IsKeyVerifyDataRead = false;
}

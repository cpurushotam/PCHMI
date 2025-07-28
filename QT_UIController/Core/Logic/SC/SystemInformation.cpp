/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the System Information related implementation
 
***************************************************************************/

#include <cstring>
#include "SystemInformation.h"
#include "DataLogger.h"


/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

SystemInformation::SystemInformation()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);
    m_SendSystemInformationMachineDetailsReadRequest = true;
    m_isSystemInformationMachineDetailsUpdated = false;
}

/**************************************************************************//**
*
* \brief   - destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
SystemInformation::~SystemInformation()
{

}


/**************************************************************************//**
*
* \brief   - send the request to ASC server for system information machine details memory block
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int SystemInformation::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    if((destination != nullptr) && (destination->id == MB_ID_SYSTEM_INFORMATION_DATA))
    {
        switch(destination->sub_id)
        {
        case MB_READ_SYSTEM_INFORMATION_REQUEST:
        {
            retVal = 0;
            sendSystemInformationMachineDetailsReadRequest(destination);
            break;
        }
        default:
        {
            destination->size = 0;
            // clear valid bit
            destination->config = 0;
            char  msg[buff_size_config] = {0};
            snprintf(msg,buff_size_config,"SystemInformation GetData default case");
            Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
            break;
        }
        }
    }
    else
    {
        destination->size = 0;
        // clear valid bit
        destination->config = 0;
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"SystemInformation GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming from ASC server for system information machine details memory block
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int SystemInformation::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_SYSTEM_INFORMATION_DATA))
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            case MB_READ_SYSTEM_INFORMATION_REQUEST:
            {
                retVal = 0;
                processSystemInformationMachineDetailsReadResponse(source);
                break;
            }

            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"SystemInformation SetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
                break;
            }
            }
        }
        else
        {
            retVal = 0;
        }
    }
    else
    {
        char  msg[buff_size_config] = {0};
        snprintf(msg,buff_size_config,"SystemInformation SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the system information machine details read request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void SystemInformation::sendSystemInformationMachineDetailsReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendSystemInformationMachineDetailsReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendSystemInformationMachineDetailsReadRequest = false;
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
* \brief   - Process the system information machine details coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void SystemInformation::processSystemInformationMachineDetailsReadResponse(const MEMORY_BLOCK *const source)
{
    MachineDetailsStruct *Data = reinterpret_cast<MachineDetailsStruct *>(source->data);
    memcpy(&m_MachineDetailsData,Data,sizeof(MachineDetailsStruct));
    m_isSystemInformationMachineDetailsUpdated = true;
}

/**************************************************************************//**
*
* \brief   - show system information machine details
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void SystemInformation::ShowSystemInformationMachineDetails()
{
    std::cout<<"/*........System Information Machine Details.......*/"<<std::endl;
    std::cout << "NumberOfAlarms: "  << m_MachineDetailsData.NumberOfAlarms << std::endl;
    std::cout << "PowerSupplyLifetimeWeld: "  << m_MachineDetailsData.PowerSupplyLifetimeWeld << std::endl;
    std::cout << "ActuatorLifetimeCycle: "  << m_MachineDetailsData.ActuatorLifetimeCycle << std::endl;
    std::cout << "PowerSupplyOverLoad: "  << m_MachineDetailsData.PowerSupplyOverLoad << std::endl;
    std::cout << "SCVersion: "  << m_MachineDetailsData.SCVersion << std::endl;
    std::cout << "ACVersion: "  << m_MachineDetailsData.ACVersion << std::endl;
    std::cout << "PCVersion: "  << m_MachineDetailsData.PCVersion << std::endl;
    std::cout << "PowerSupplySerialNumber: "  << m_MachineDetailsData.PowerSupplySerialNumber << std::endl;
    std::cout << "ActuatorSerialNumber: "  << m_MachineDetailsData.ActuatorSerialNumber << std::endl;
    std::cout << "CalibrationDate: "  << m_MachineDetailsData.CalibrationDate << std::endl;
    std::cout << "MacId: "  << m_MachineDetailsData.MacId << std::endl;
    std::cout << "SafetyVersion: "  << m_MachineDetailsData.SafetyVersion << std::endl;

}

/**************************************************************************//**
*
* \brief   - return system information machine details updated details
*
* \param   - none
*
* \return  - bool - m_isSystemInformationMachineDetailsUpdated
*
******************************************************************************/
bool SystemInformation::GetSystemInformationMachineDetailsUpdateStatus()
{
    return m_isSystemInformationMachineDetailsUpdated;
}

/**************************************************************************//**
*
* \brief   - return the copy of system information machine details structure data
*
* \param   - none

* \return  - copy of system information machine details structure data
*
******************************************************************************/
MachineDetailsStruct SystemInformation::GetSystemInformationMachineDetailsData()
{
    MachineDetailsStruct MachineDetailsData = m_MachineDetailsData;
    //Reset the flag to false once the value is read
    m_isSystemInformationMachineDetailsUpdated = false;
    return MachineDetailsData;
}


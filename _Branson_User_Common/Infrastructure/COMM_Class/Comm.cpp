/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

Implements COMM Class - responsible for  HMI/ASC communication frame handling

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.
 rev2. 05/07/2023 - Fix for recoverable and non-recoverable error

***************************************************************************/
#include <stdexcept>
#include "Comm.h"
#include "BIOWrapper.h"
#include "DataInterface.h"
#include "Common_Definitions.h"

/*****************************************************************************
* \brief   - Constructor : Initialize the communication class
*
* \param   - ptrCommConfig - BIO configuration
* 			 ptrCommDataConfig - Data Interface configuration
*
* \return  - None
*
******************************************************************************/
Comm::Comm(CommConfig *ptrCommConfig, CommDataConfig *ptrCommDataConfig, THREAD_MODE ThreadMode)
{
    // check arguments
    if((ptrCommConfig!=NULL) && (ptrCommDataConfig!=NULL))
    {
        m_ThreadMode = ThreadMode;        

        // store pointers for later use
        this->m_ptrCommConfig = ptrCommConfig;
        this->m_ptrCommDataConfig = ptrCommDataConfig;

        // Initialize iterator to tx config table
        m_ConfigMBItr  = this->m_ptrCommDataConfig->TXConfig.begin();

        // initialize log ID
        this->m_log_id = Logger::enroll(this);

        // verify if Comm Data configuration table has been initialized
        if((this->m_ptrCommDataConfig->RXConfig.size()>0) && (this->m_ptrCommDataConfig->TXConfig.size()>0))
        {
            // try to allocate memory for buffer
            // Note that - if memory allocation fails std::bad_alloc exception will be raised, user needs to handle it.
            this->rx_buff = new uint8_t[this->buff_size];
            this->tx_buff = new uint8_t[this->buff_size];
        }
        else
        {
            // throw exception Comm Data configuration is not initialized
            throw std::invalid_argument("Invalid Data Config");
        }
    }
    else
    {
        // throw exception if argument check fails
        throw std::invalid_argument("null ptr");
    }
}

/*****************************************************************************
* \brief   - Destructor to perform cleanup activity
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
Comm::~Comm()
{
    /* Delete the communication configuration */
    // release buffers
    delete[] this->rx_buff;
    delete[] this->tx_buff;

}

/*****************************************************************************
* \brief   - Create instance of BIO wrapper class by providing required SSL
*            configuration and start communication.
*
* \param   - None
*
* \return  - success 					returns 0,
* 			 Recoverable fault 			returns -1 (failure),
* 			 Non Recoverable fault   	return  -2  (failure)
******************************************************************************/
int Comm::Start()
{
    try
    {
        // start connection
        this->m_ptrBIOWrapperInstance = new BIOWrapper(this->m_ptrCommConfig);
    }
    catch (std::exception &e)
    {
        // Log fault
        snprintf ( this->m_log_buffer, buff_size_config, "BIOError:%s",e.what() );
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));

        if (strncmp(e.what(), "N", 1) == 0)
        {
            // Log Debug
            snprintf ( this->m_log_buffer, buff_size_config, "Non Recoverable BIOError ");
            Logger::add_entry(E_SEVERITY::E_LOG_DEB, (this->m_log_buffer));

            return (-2);
        }

        return (-1);
    }
    // Log Event
    snprintf ( this->m_log_buffer, buff_size_config, "Connected:%s",this->m_ptrCommConfig->DestinationIPandPort);
    Logger::add_entry(E_SEVERITY::E_LOG_GENERAL_INFO, (this->m_log_buffer));
    return (0);
}

/*****************************************************************************
* \brief   - Process RX frames contents.
*
* \param   - frame_size - size of the communication frame
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int Comm::process_rx(int frame_size)
{
    uint32_t current_index = 0;
    uint32_t remaining_size = frame_size;
    uint32_t id = 0;
    uint32_t sub_id = 0;
    int RetVal=0;
    if (m_ThreadMode == SYNC_THREAD) // Process all MB configured Rxconfig
    {
        while(remaining_size>(sizeof(FMB_HEADER)))
        {
            // get RX buffer pointer to retrieve the FMB
            FMB_HEADER *ptr_fmb = reinterpret_cast<FMB_HEADER*>(&(this->rx_buff[current_index]));

            // read id and sub id
            id = ptr_fmb->id;
            sub_id = ptr_fmb->sub_id;

            // get data interface
            DataInterface *dataInt = this->m_ptrCommDataConfig->RXConfig[std::make_pair(id,sub_id)];

            // check if DataInterface is valid (this value will be null if expected id & sub_id not found in configuration)
            if(dataInt == NULL)
            {
                RetVal = -1;
                // Log fault
                snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Err:ID-%d,SubID-%d",id,sub_id);
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                break;
            }
            else
            {
                // check Config & size fields
                if(
                    ((ptr_fmb->config & VALID_BIT) != VALID_BIT) &&
                    (ptr_fmb->size == 0) &&
                    (ptr_fmb->size > (remaining_size - sizeof(FMB_HEADER)))
                    )
                {
                    RetVal = -1;
                    // Log fault
                    snprintf ( this->m_log_buffer, buff_size_config, "Invalid_RX:ID-%d,SubID-%d",id,sub_id);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                    break;
                }
                else
                {
                    // prepare mb
                    MEMORY_BLOCK mb = {
                        ptr_fmb->id,
                        ptr_fmb->sub_id,
                        ptr_fmb->config,
                        ptr_fmb->size,
                        &(this->rx_buff[current_index + sizeof(FMB_HEADER)]),
                        NULL
                    };

                    // process received data using set function
                    if(dataInt->SetData(&mb)<0)
                    {
                        RetVal = -1;
                        // Log fault
                        snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Set_Err:ID-%d,SubID-%d",id,sub_id);
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
                        break;
                    }
                    else
                    {
                        // prepare variables for next FMB
                        int fmb_size = sizeof(FMB_HEADER) + mb.size;
                        current_index = current_index + fmb_size;

                        if (remaining_size > fmb_size)
                        {
                            remaining_size = remaining_size - (fmb_size);
                        }
                        else
                        {
                            remaining_size = 0;
                        }
                    }
                }
            }
        }
    }
    else // Process at time single MB configured Rxconfig
    {
        // get RX buffer pointer to retrieve the FMB
        FMB_HEADER *ptr_fmb = reinterpret_cast<FMB_HEADER*>(&(this->rx_buff[current_index]));

        // read id and sub id
        id = ptr_fmb->id;
        sub_id = ptr_fmb->sub_id;

        // get data interface
        DataInterface *dataInt = this->m_ptrCommDataConfig->RXConfig[std::make_pair(id,sub_id)];

        // check if DataInterface is valid (this value will be null if expected id & sub_id not found in configuration)
        if(dataInt == NULL)
        {
            RetVal = -1;
            // Log fault
            snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Err:ID-%d,SubID-%d",id,sub_id);
        }
        else
        {
            // check Config & size fields
            if(
                ((ptr_fmb->config & VALID_BIT) != VALID_BIT) &&
                (ptr_fmb->size == 0) &&
                (ptr_fmb->size > (remaining_size - sizeof(FMB_HEADER)))
                )
            {
                RetVal = -1;
                // Log fault
                snprintf ( this->m_log_buffer, buff_size_config, "Invalid_RX:ID-%d,SubID-%d",id,sub_id);
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
            }
            else
            {
                // prepare mb
                MEMORY_BLOCK mb = {
                    ptr_fmb->id,
                    ptr_fmb->sub_id,
                    ptr_fmb->config,
                    ptr_fmb->size,
                    &(this->rx_buff[current_index + sizeof(FMB_HEADER)]),
                    NULL
                };

                // process received data using set function
                if(dataInt->SetData(&mb)<0)
                {
                    RetVal = -1;
                    // Log fault
                    snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Set_Err:ID-%d,SubID-%d",id,sub_id);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, (this->m_log_buffer));
                }
            }
        }
    }
    return (RetVal);
}

/*****************************************************************************
* \brief   - Prepare TX frame
*
* \param   - frame_size - reference to communication frame size
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int Comm::process_tx(int &frame_size)
{
    uint32_t current_index = 0;
    uint32_t remaining_size = this->buff_size;
    int RetVal = 0;
    frame_size = 0;

    // clear past data
    memset(this->tx_buff,0,this->buff_size);

    if (m_ThreadMode == SYNC_THREAD) // Process all MB configured in Txconfig
    {
        // read configuration
        for (auto &mbconfig : this->m_ptrCommDataConfig->TXConfig)
        {
            // get TX buffer pointer to store FMB
            FMB_HEADER *ptr_fmb = reinterpret_cast<FMB_HEADER*>(&(this->tx_buff[current_index]));

            uint32_t size;

            if(remaining_size>sizeof(FMB_HEADER))
            {
                size = remaining_size - (uint32_t)sizeof(FMB_HEADER);
            }
            else
            {
                RetVal = -1;
                // Log fault
                snprintf ( this->m_log_buffer, buff_size_config, "Insufficient buff size, DatInt_Er:ID-%d,SubID-%d",mbconfig.first.first,mbconfig.first.second);
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
                break;
            }

            // prepare MB to make call data-interface
            MEMORY_BLOCK mb = {
                mbconfig.first.first,
                mbconfig.first.second,
                0,
                size,
                &(this->tx_buff[current_index + sizeof(FMB_HEADER)]),
                NULL
            };

            // get MB data
            if(mbconfig.second->GetData(&mb)<0)
            {
                RetVal = -1;
                // Log fault
                snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Get_Er:ID-%d,SubID-%d",mbconfig.first.first,mbconfig.first.second);
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
                break;
            }
            else
            {
                // verify config & size
                if(
                    ((mb.config & VALID_BIT) != VALID_BIT)
                    )
                {
                    RetVal = -1;
                    // log fault
                    snprintf ( this->m_log_buffer, buff_size_config, "MB_Err:ID-%d,SubID-%d",mbconfig.first.first,mbconfig.first.second);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
                    break;
                }
                else if(mb.size == 0)
                {
                    //do nothing
                }
                else
                {
                    //std::cout << "Sending Comm Data for MB ID: "  << mb.id << ", MB SUB_ID: " << mb.sub_id <<  ", MB SIZE: " << mb.size << std::endl;
                    // store ID and sub-ID to frame
                    ptr_fmb->id = mb.id;
                    ptr_fmb->sub_id = mb.sub_id;

                    // store cofig
                    ptr_fmb->config = mb.config;

                    // store size
                    ptr_fmb->size = mb.size;

                    // prepare variables for next MB
                    int fmb_size = sizeof(FMB_HEADER) + mb.size;
                    current_index = current_index + fmb_size;
                    frame_size = frame_size + fmb_size;
                    if (remaining_size > fmb_size)
                    {
                        remaining_size = remaining_size - (fmb_size);
                    }
                    else
                    {
                        remaining_size = 0;
                    }
                }
            }
        }
    }
    else // Process at time single MB configured in Txconfig
    {
    	static int HeartBeatCounter = 0;
    	
    	bool ExitLoop = false;
    	FMB_HEADER *ptr_fmb = reinterpret_cast<FMB_HEADER*>(&(this->tx_buff[current_index]));	
    	uint32_t size = this->buff_size;
        // get TX buffer pointer to store FMB
    	do
    	{
			// prepare MB to make call data-interface
			MEMORY_BLOCK mb = {
				m_ConfigMBItr->first.first,
				m_ConfigMBItr->first.second,
				0,
				size,
				&(this->tx_buff[current_index + sizeof(FMB_HEADER)]),
				NULL
			};
	
			//MB_ID_COMM_STAT acts as heartbeat message.
			//Send heartbeat/MB_ID_COMM_STAT message only after HEART_BEAT_MESSAGE_COUNTER i.e. every 1 second.
			if (mb.id == MB_ID_COMM_STAT && HeartBeatCounter < HEART_BEAT_MESSAGE_COUNTER)
			{
				//Do not send heartbeat message.
				RetVal = 1;
				ExitLoop = true;
				m_ConfigMBItr++;
			}
			else
			{
				// get MB data
				if(m_ConfigMBItr->second->GetData(&mb)<0)
				{
					ExitLoop = true;
					RetVal = -1;
					
					// Log fault
					snprintf ( this->m_log_buffer, buff_size_config, "DatInt_Get_Er:ID-%d,SubID-%d",m_ConfigMBItr->first.first,m_ConfigMBItr->first.second);
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
				}
				else
				{
					// verify config
					if(((mb.config & VALID_BIT) != VALID_BIT))
					{
						ExitLoop = true;
						RetVal = -1;
						// log fault
						snprintf ( this->m_log_buffer, buff_size_config, "MB_Err:ID-%d,SubID-%d",m_ConfigMBItr->first.first,m_ConfigMBItr->first.second);
						Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
					}
					else if(mb.size == 0)
					{
						//Do not process memory block that does not contain any data.
						//Skip such memory block and scan next memory block. 
						//If no data in next memory block then skip it and scan next and so on 
						//until the last memory block is scanned in tx map.
						
						ExitLoop = false;
						RetVal = 1;
						++m_ConfigMBItr;
						if (m_ConfigMBItr == this->m_ptrCommDataConfig->TXConfig.end())
						{
							ExitLoop = true;
							m_ConfigMBItr = this->m_ptrCommDataConfig->TXConfig.begin();
						}				
					}
					else
					{
						//We are sending data here over the TCP/IP socket.
						ExitLoop = true;
						RetVal = 0;		
						++m_ConfigMBItr;
						
						//reset heartbeat counter as we have sent a message.
						HeartBeatCounter = 0;
					
						
						// store ID and sub-ID to frame
						ptr_fmb->id = mb.id;
						ptr_fmb->sub_id = mb.sub_id;
		
						// store cofig
						ptr_fmb->config = mb.config;
		
						// store size
						ptr_fmb->size = mb.size;
						
						if (m_ConfigMBItr == this->m_ptrCommDataConfig->TXConfig.end())
						{
							m_ConfigMBItr = this->m_ptrCommDataConfig->TXConfig.begin();
						}
	
						frame_size = sizeof(FMB_HEADER) + mb.size;
						
						//Good statement to debug. So keeping it commented. It shows the memory block ID, sub ID and size that is being transfeered over background thread.
                       // std::cout << "Sending BG Data for MB ID: "  << mb.id << ", MB SUB_ID: " << mb.sub_id <<  ", MB SIZE: " << mb.size << std::endl;
					}
				}
			}
    	}while(ExitLoop == false);
    	
    	HeartBeatCounter++;
    }
    
    return (RetVal);
}

/*****************************************************************************
* \brief   - Process function prepares TX frames & handles RX frames contents.
*
* \param   - None
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int Comm::Process()
{
    int RetVal = 0;
    int frame_size=0;
    bool no_data = false;

    //----------- Check if new frame received--------------------------
    int readval = this->m_ptrBIOWrapperInstance->BIORead(rx_buff, buff_size);

    if(readval<0)
    {
        // error occurred
        RetVal = -1;

        // Log fault
        snprintf ( this->m_log_buffer, buff_size_config, "BIORead failed,retval %d",readval);
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
    }
    else if(readval == 0)
    {
        no_data = true;
        // no data available - don't do anything
    }
    else
    {
        // data available, process RX frame
        if(this->process_rx(readval)<0)
        {
            RetVal = -1;
            // no need to log error here, as it is already logged by process_rx function
        }
        else
        {
            // success, do nothing for now
        }
    }
    //---------- Prepare TX frame ------------------------------------
    if(RetVal != -1)
    {
        // server responds synchronous to client messages, thus don't respond if no data received from client.
        if((this->m_ptrCommConfig->RoleIs == SERVER) && (no_data == true) && (m_ThreadMode == SYNC_THREAD) )
        {
            return (RetVal);
        }
        else
        {
            RetVal = this->process_tx(frame_size);
            if(RetVal<0)
            {
                RetVal = -1;
            }
            else if (RetVal>0)
            {
                // do nothing
            }
            else
            {
                //--------------Send TX frame ------------------------------------
                int writeVal=this->m_ptrBIOWrapperInstance->BIOWrite(this->tx_buff, frame_size);
                if(writeVal<0)
                {
                    RetVal = -1;

                    // Log fault
                    snprintf ( this->m_log_buffer, buff_size_config, "BIOWrite failed,retval %d",writeVal);
                    Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
                }
                else
                {
                    // success, do nothing
                }
            }
        }
    }
    return (RetVal);
}

/*****************************************************************************
* \brief   - Delete instance of BIO Wrapper class
*
* \param   - None
*
* \return  - If success returns 0, else returns -1 (failure)
******************************************************************************/
int Comm::Exit()
{
    try
    {
        // delete BIO Wrapper instance to initiate SSL shutdown
        delete this->m_ptrBIOWrapperInstance;
        this->m_ptrBIOWrapperInstance = nullptr;
    }
    catch(std::exception &e)
    {
        snprintf ( this->m_log_buffer, buff_size_config, "ExitFailed:%s",e.what());
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM,(this->m_log_buffer));
        return (-1);
    }
    // Log Event
    snprintf ( this->m_log_buffer, buff_size_config, "Detached:%s",this->m_ptrCommConfig->DestinationIPandPort);
    Logger::add_entry(E_SEVERITY::E_LOG_EVENT,(this->m_log_buffer));
    return (0);
}

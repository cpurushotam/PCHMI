/**************************************************************************

        Copyright (c) Branson Ultrasonics Corporation, 1996-2024

        This program is the property of Branson Ultrasonics Corporation
        Copying of this software is expressly forbidden, without the prior
        written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares COMM Class - responsible for  HMI/ASC communication frame handling

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/05/2023 - Initial implementation.

***************************************************************************/
#ifndef COMM_H
#define COMM_H

#include "BIOWrapper.h"
#include "CommDataConfig.h"
#include "DataLogger.h"

// Enum declaration for background and synchronous communication
typedef enum
{
    SYNC_THREAD = 1,
    BACK_THREAD
}THREAD_MODE;

/* Comm Class definition */
class Comm
{
private:

	// size of TX & RX frame buffer
    static constexpr int buff_size = 1024*24;

	// Pointer to TX frame buffer
	uint8_t *tx_buff = NULL;

	// Pointer to RX frame buffer
	uint8_t *rx_buff = NULL;

    // Communication instance to access BIO wrapper class functions
    BIOWrapper *m_ptrBIOWrapperInstance = NULL;

    // COMM configuration pointer
    CommConfig *m_ptrCommConfig = NULL;

    // COMM data configuration pointer
    CommDataConfig *m_ptrCommDataConfig = NULL;

    // function to process RX frame
    int process_rx(int frame_size);

    // function to prepare TX frames
    int process_tx(int &frame_size);

    // declaration of FMB header
    typedef struct{
        uint32_t  id;        // Unique identifier for frame memory block.
        uint32_t  sub_id;    // sub identifier for frame memory block used to define for sub operation.
        uint32_t  config;    // configuration for frame memory block currently bit 0 is assigned for validity check and
                             // bit 1 is assigned to check if its for one time use .
        uint32_t  size;      // size of the Data followed
    }__attribute__((packed)) FMB_HEADER;

    // log identifier
    size_t m_log_id;

    // log buffer
    char m_log_buffer[buff_size_config]={0};

    // To store thread mode
    THREAD_MODE m_ThreadMode;

    // Iterator for background communication data interface
    std::map<std::pair<uint32_t,uint32_t>, DataInterface*> :: iterator m_ConfigMBItr;

public:
    // Contructor declarion
    Comm(CommConfig *ptrCommConfig, CommDataConfig *ptrCommDataConfig, THREAD_MODE ThreadMode=SYNC_THREAD);

    // Destructor declarion to perform cleanup activity
    ~Comm();

    // Create instance of BIO wrapper class to start communication with peer
    int Start();

    // Prepares TX frames & handles RX frames contents
    int Process();

    // Delete instance of BIO Wrapper class to stop communication with peer
    int Exit();
};

#endif // COMM_H

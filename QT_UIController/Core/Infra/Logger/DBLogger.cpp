/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Implementation of DB logger API.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 12/02/2024 -  Initial version.

***************************************************************************/

#include "DBLogger.h"

/**************************************************************************//**
* \brief   - Dummy implementation of DB Logger
*
* \param   - LogEntry* log_entry - Name of Logger entry
* 			 uint32_t msg_len    - Length of message.
*
* \return  - None
******************************************************************************/
void DBLogger::AddEntry(LogEntry* log_entry, uint32_t msg_len)
{
    std::cout << "Implementation of DB Logger On HMI side not Available" << std::endl;
}

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------
  	 It contains the function is responsible for FieldBus IO Manager
***************************************************************************/

#ifndef FIELDBUS_IO_MANAGER_H_
#define FIELDBUS_IO_MANAGER_H_

#include <fstream>
#include "FbUserIOStructureAce.h"
#include "DataInterface.h"

// FieldBus IO Manager Class
class FieldBusIOMgr : public DataInterface
{
public:
	FieldBusIOMgr ();
	~FieldBusIOMgr ();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    void PrintFieldBusUserIO();

    bool IsFieldBusUsrIOStructUpdated();
    FB_USERIO GetFieldBusUsrIOStruct();
    void ResetFieldBusUsrIOUpdatedFlag();
    void SaveIndFieldBusUserIOValues(FB_USERIO Fb_UserIO);
    void SetResetToDefaultIndFieldBusUsrIORequest(bool value);

private:
	static size_t m_log_id;
    /* Declaration for FieldBus user io(control/status word) save command request button notifier**/
    bool m_InitiateFieldBusUserIOSaveRequest;
    /* Declaration for FieldBus user io(control/status word) restore default command request button notifier*/
     bool m_InitiateResetToDefaultFieldBusUserIORequest;
    /* FieldBus user io(control/status words) data read request is sent to ASC when this flag is true */
    bool m_InitiateReadFieldBusUserIORequest;
	/* Mutex to access the FieldBus user io(control/status word) data */
	pthread_mutex_t m_FbUserIODataMutex;
    /* FieldBus user io(control/status words) data updated flag */
    bool m_IsLastFieldBusIOUpdated;

    /*FieldBus User IO(Control/Status words) Structure*/
    FB_USERIO m_strFieldBusUserIO;

    /* Send FieldBus User IO Save request to ASC */
     void sendFieldBusUserIOSaveRequest(MEMORY_BLOCK * const destination);
     /* Send FieldBus User IO Reset to Default value request */
     void sendResetToDefaultFieldBusUserIORequest(MEMORY_BLOCK * const destination);
     /* Send Analog User IO Read request to ASC */
     void sendReadFieldBusUserIORequestToASC(MEMORY_BLOCK * const destination);

     /* Read the FieldBus User IO Response from ASC */
     void processReadFieldBusUserIOResponseFromASC(const MEMORY_BLOCK *const source);
};


#endif /* FIELDBUS_IO_MANAGER_H_ */

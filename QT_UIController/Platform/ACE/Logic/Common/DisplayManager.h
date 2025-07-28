/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the function is responsible for Display Manager
***************************************************************************/

#ifndef DISP_MANAGER_H_
#define DISP_MANAGER_H_

#include "DisplayMgrStructureAce.h"
#include "DataInterface.h"

//Display Manager Class
class DisplayMgr : public DataInterface
{
public:
	DisplayMgr ();
	~DisplayMgr ();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    DISPLAY_MODE GetDisplayMode(void);
    bool GetIsDisplayModeUpdatedFlag();
    void SetIsDisplayModeUpdated();

    FIELDBUS_TOKEN GetFieldBusTokenStatus();

private:

	static size_t m_log_id;

    /*Stores the display mode*/
    DISPLAY_MODE m_displayMode;

    /*Stores the fieldbus token status*/
    FIELDBUS_TOKEN m_FieldBusTokenStatus;

    bool m_IsDisplayModeUpdated;

    void processDisplayModeFromASC(const MEMORY_BLOCK *const source);
    void processFieldBusTokenStatus(const MEMORY_BLOCK *const source);

}; 	

#endif /* DISP_MANAGER_H_ */

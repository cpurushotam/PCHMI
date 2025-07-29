/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the System Information related implementation
 
***************************************************************************/

#ifndef SYSTEMINFORMATION_H_
#define SYSTEMINFORMATION_H_

#include "DataInterface.h"
#include "SystemInformationStructure.h"

class SystemInformation : public DataInterface
{ 
public:
	
    SystemInformation();
    virtual ~SystemInformation();

    MachineDetailsStruct GetSystemInformationMachineDetailsData();
    bool GetSystemInformationMachineDetailsUpdateStatus();

    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    
private:
    
    size_t m_LogID;
    //cached System Informtation mavhine details data.
    MachineDetailsStruct m_MachineDetailsData;

    bool m_SendSystemInformationMachineDetailsReadRequest;

    bool m_isSystemInformationMachineDetailsUpdated;

    void sendSystemInformationMachineDetailsReadRequest(MEMORY_BLOCK * const destination);

    void processSystemInformationMachineDetailsReadResponse(const MEMORY_BLOCK *const source);
	
    void ShowSystemInformationMachineDetails();

};

#endif /* SYSTEMINFORMATION_H_ */

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

This file contains the ACE actuator setup related implementation

***************************************************************************/

#ifndef ACTUATOR_SETUP_ACE_H_
#define ACTUATOR_SETUP_ACE_H_

#include "ActuatorSetup.h"
#include "ActuatorSetupStructureAce.h"

class ActuatorSetupACE : public ActuatorSetup
{
public:
    ActuatorSetupACE();
    virtual ~ActuatorSetupACE();
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    // Dummy implementation on HMI side
    bool isHornDownClampOn() override {return false;}
    ACTUATOR_SETUP_OP_TYPE isHornDownRequested() override {return NONE_OP_TYPE;}
    ACTUATOR_SETUP_SCREEN_DATA isActuatorSetupScreenOpen() override {return REQUEST_ACTUATOR_SETUP_LEAVE_SCREEN;}

    void initiateActuatorSetupHornRetractRequest();
    void initiateActuatorSetupScreenOnRequestRequest();
    void initiateActuatorSetupOperationTypeRequest();
    void initiateActuatorSetupHornClampOnOffRequest();
    void setHornDownClampOnOff(bool status);
    void setActuatorSetupOperationType(ACTUATOR_SETUP_OP_TYPE type);
    ACTUATOR_SETUP_OP_TYPE getActuatorSetupOperationType();
    void setActuatorSetupScreenOpenOnHMI(ACTUATOR_SETUP_SCREEN_DATA data);
    ActuatorSetupStruct getActuatorSetupData();
    bool getIsDataFlagUpdated();
    void resetDataFlagUpdated();

private:
    void sendActuatorSetupReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendActuatorSetupScreenOnReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendActuatorSetupOperationTypeReadRequestToASC(MEMORY_BLOCK * const destination);
    void sendActuatorSetupHornRetractRequestToASC(MEMORY_BLOCK * const destination);
    void sendActuatorSetupHornClampOnOffRequestToASC(MEMORY_BLOCK * const destination);
    void processActuatorSetupReadResponseFromASC(const MEMORY_BLOCK *const source);
	void processSynchActuatorSetupDataFromASC(const MEMORY_BLOCK *const source);

    void ShowActuatorSetupData();

    static size_t static_log_id;

    bool m_HornDownClampOnOff;
    bool m_IsActuatorSetupDataUpdated;
    ACTUATOR_SETUP_OP_TYPE     m_ActuatorSetupOperationType;
    ACTUATOR_SETUP_SCREEN_DATA m_ActuatorSetupScreenOpenOnHMI;

    //Structure variable to store Actuator setup Data
    ActuatorSetupStruct m_SetupData;

    bool m_InitiateActuatorSetupReadOnPowerUp;
    bool m_InitiateActuatorSetupScreenOnRequest;
    bool m_InitiateActuatorSetupOperationType;
    bool m_InitiateActuatorSetupHornRetract;
    bool m_InitiateActuatorSetupHornClampOnOff;
    //mutex for Actuator setup data access
    pthread_mutex_t m_ActuatorSetupDataMutex;
};


#endif /* ACTUATOR_SETUP_ACE_H_ */

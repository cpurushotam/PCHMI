/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
---------------------------- MODULE DESCRIPTION ----------------------------   
  	 It contains the function is responsible for Digital IO Manager 
***************************************************************************/

#ifndef IO_MANAGER_H_
#define IO_MANAGER_H_
#include <fstream>
#include "DgtUserIOStructureAce.h"
#include "DataInterface.h"
//IO Manager Class
class DigitalIOMgr : public DataInterface
{
public:
	DigitalIOMgr ();
	~DigitalIOMgr ();		
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    USERIO GetDigitalIOStruct(void);
    bool IsDigitalIOStructUpdated(void);
    void ResetIsLastDigitalIOUpdatedFlag();
    void saveDigitalUserIOValues(USERIO userI0);
    void setResetToDefaultDigiUsrIORequest(bool value);

    void setDignUserIODigitalOP(DiagnosticUserIOOutputs diagnosticDigtalOp);
    void InitiateRefreshRequest();
    void InitiateStopRequest();

    DiagnosticDigitalInputs GetDignosticDigitalInputs();

    bool IsDiagnosticDigitalInputsUpdated(void);
    void ResetDiagnosticDigitalInputsUpdatedFlag();
    bool IsDiagnosticAnalogInputsUpdated();

    USERIO_ANALOG GetAnalogIOStruct(void);
    bool IsAnalogIOStructUpdated(void);
    void ResetIsLastAnalogIOUpdatedFlag();
    void SaveAnalogUserIOValues(USERIO_ANALOG analoguserI0);
    void SetResetToDefaultAnalogUsrIORequest(bool value);

    void PrintAnalogUserIO();

private:

	static size_t m_log_id;
    /* Declaration for save command request button notifier **/
	bool m_InitiateUserIOSaveRequest;
    /* Declaration for analog user io save command request button notifier**/
    bool m_InitiateAnalogUserIOSaveRequest;
	/* Declaration for restore default command request button notifier*/
	bool m_InitiateResetToDefaultRequest;
    /* Declaration for analog user io restore default command request button notifier*/
    bool m_InitiateResetToDefaultAnalogUserIORequest;
	//user io data read request is sent to ASC when this flag is true
	bool m_InitiateReadRequest;
    /* Analog user io data read request is sent to ASC when this flag is true */
    bool m_InitiateReadAnalogUserIORequest;
	/* Mutex to access the user io data */
	pthread_mutex_t m_DgtUserIODataMutex;
    /* user io data updated flag*/
    bool m_IsLastDigitalIOUpdated;
    /* Analog user io data updated flag */
    bool m_IsLastAnalogIOUpdated;


    //user io data read request is sent to ASC when this flag is true
    bool m_InitiateReadDigitalOPRequest;
    /* Declaration for Refresh request button notifier **/
    bool m_InitiateRefreshUserIORequest;
	//User IO Structure
	USERIO m_strUserIO;
    /*Analogue User IO Structure*/
    USERIO_ANALOG m_strAnalogUserIO;

    /* user io data updated flag*/
    bool m_IsLastDigitalInputsUpdated;

    DiagnosticDigitalInputs m_DiagnosticsDigitalInputs;  // Used to store the input pins state from ASC.
    DiagnosticUserIOOutputs m_DiagnosticsDigitalOutputs; // Used to store the output pin from HMI

	/* Method to check save command request is receive or not  */
    void InitiateUserIOSaveRequest();
    /* Method to initiate Analog User IO Save Request */
    void InitiateAnalogUserIOSaveRequest();
    //Reset to default
    void InitiateResetToDefaultRequest();
    /* Method to initiate Analog User IO Reset to Default Request */
    void InitiateResetToDefaultAnalogUserIORequest();
    
    //Send Save request to ASC
    void sendSaveRequest(MEMORY_BLOCK * const destination);
    /* Send Analog User IO Save request to ASC */
    void sendAnalogUserIOSaveRequest(MEMORY_BLOCK * const destination);
    //Send Reset to default value request
    void sendResetToDefaultRequest(MEMORY_BLOCK * const destination);
    /* Send Analog User IO Reset to Default value request */
    void sendResetToDefaultAnalogUserIORequest(MEMORY_BLOCK * const destination);
    void sendReadDgtUserIORequestToASC(MEMORY_BLOCK * const destination);
    /* Send Analog User IO Read request to ASC */
    void sendReadAnalogUserIORequestToASC(MEMORY_BLOCK * const destination);

    void sendReadDiagtUserIODigitalIpReq(MEMORY_BLOCK * const destination);

    //Send Diagnostic UserIo pin data to ASC.
    void sendDiagnosticUserIODigitalOpPins(MEMORY_BLOCK * const destination);

    //Read the Response from ASC
    void processReadResponseFromASC(const MEMORY_BLOCK *const source);
    /* Read the Analog User IO Response from ASC */
    void processReadAnalogUserIOResponseFromASC(const MEMORY_BLOCK *const source);

    void processReadUserIODgInputsFromASC(const MEMORY_BLOCK *const source);
}; 	

#endif /* IO_MANAGER_H_ */

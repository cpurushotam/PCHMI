/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE ReferenceWeldSignature  related implementation

 ***************************************************************************/

#include <cstring>
#include "ReferenceWeldSignatureAce.h"
#include "DataLogger.h"

size_t ReferenceWeldSignature::static_log_id = 0;
/******************************************************************************//**
 * \brief - Constructor.
 *
 * \param - None.
 *
 * \return - None.
 *
 ******************************************************************************/
ReferenceWeldSignature::ReferenceWeldSignature()
{
    m_SendRequestedRefWeldSignatureReadRequest = false;
    m_ReqReferenceWeldSignatureData= false;
    m_RefWeldSignSampleNumberToRead =0;
    m_RefWeldResultIndexNumberToRead = -1;

    m_SendReferenceWeldSignWeldResultReadRequest = false;
    m_WeldResultIndex = -1;
    m_WeldResultSampleNumberToRead = 0;
    m_RequestedReferenceWeldResultIndex = false;
    m_SendUpdateRefGraphNameRequest = false;

    m_SendReferenceWeldGraphSignatureReadRequest = false;
    m_SendReplaceRefGraphRequest= false;
    m_SendReferenceWeldReadRequestonPowerUp = true;

    m_IsReferenceGraphDetailsAvailable = false;
    m_sendNewDequeue = false;
}

/**************************************************************************//**
 *
 * \brief   - Send request to ASC for data request and update.
 *
 * \param   - Address of destination MB.
 *
 * \return  -  If success returns 0, else returns -1 (failure)
 *
 ******************************************************************************/
int ReferenceWeldSignature::GetData(MEMORY_BLOCK * const destination)
{
    int retVal = -1;

    //  check parameter
    if((destination != NULL) && (destination->id == MB_ID_REFERENCE_WELD_DATA))
    {
        // perform operation based on sub id
        switch(destination->sub_id)
        {
        case READ_REFERENCE_WELD_SIGNATURE_DATA:
        {
            retVal = 0;
            sendRequestedReferenceWeldSignatureReadRequestToASC(destination);
            break;
        }
        case READ_REFERENCE_WELD_RESULT_DATA:
        {
            retVal = 0;
            sendReferenceWeldResultReadRequestToASC(destination);
            break;
        }
        case READ_REFERENCE_GRAPH_DATA_FOR_NAME:
        {
            retVal = 0;
            sendReferenceGraphReadRequestToASC(destination);
            break;
        }
        case UPDATE_NAME_FOR_REFERENCE_WELD_GRAPH:
        {
            retVal = 0;
            sendReferenceGraphNameUpdateRequestToASC(destination);
            break;
        }
        case REPLACE_OLD_REFGRAPH_BY_NEW_REFGRAPH:
        {
            retVal = 0;
            sendReferenceGraphReplaceRequestToASC(destination);
            break;
        }
        case SEND_DATA_ON_REFERENCEWELDDATA_READ_REQUEST:
        {
            retVal = 0;
            sendReferenceGraphReadRequestToASConPowerUp(destination);
            break;
        }
        default:
        {

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
* \brief   - SetData Interface implementation for Reference Weld Signature data.
*
* \param   - Address of source Memory Block.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ReferenceWeldSignature::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if((source != nullptr) && (source->id == MB_ID_REFERENCE_WELD_DATA) )
    {
        // perform operation based on sub id
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
            switch(source->sub_id)
            {
            //Process response coming from ASC for requested weld signature data
            case READ_REFERENCE_WELD_SIGNATURE_DATA:
            {
                retVal = 0;
                procesRequestedReferenceWeldSignatureDataFromASC(source);
                break;
            }
            case READ_REFERENCE_WELD_RESULT_DATA:
            {
                retVal = 0;
                processRefereceWeldResultDataFromASC(source);
                break;
            }
            case READ_REFERENCE_GRAPH_DATA_FOR_NAME:
            {
                retVal = 0;
                processReferenceGraphDataFromASC(source);
                break;
            }
            case REPLACE_OLD_REFGRAPH_BY_NEW_REFGRAPH:
            {
                retVal = 0;
                processReplaceReferenceGraphStatusFromASC(source);
                break;
            }
            default:
            {
                char  msg[buff_size_config] = {0};
                snprintf(msg,buff_size_config,"ReferenceWeldSignature SetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
                //Error ! default retVal (failure) will be returned
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
        snprintf(msg,buff_size_config,"WeldSignatureACE SetData invalid request");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return (retVal);
}
/**************************************************************************//**
*
* \brief   - Send Reference weld signature read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  -  none
*
******************************************************************************/
void ReferenceWeldSignature::sendRequestedReferenceWeldSignatureReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if( destination->size >= ( sizeof( m_ReqReferenceWeldSignatureData )  + sizeof( m_RefWeldResultIndexNumberToRead ) + sizeof(m_RefWeldSignSampleNumberToRead) + sizeof(m_sendNewDequeue) ) )
    {
        if( m_SendRequestedRefWeldSignatureReadRequest == true )
        {
            destination->size = ( sizeof(m_ReqReferenceWeldSignatureData)  + sizeof(m_RefWeldResultIndexNumberToRead) + sizeof(m_RefWeldSignSampleNumberToRead) + sizeof(m_sendNewDequeue) );
            destination->config = VALID_BIT;

            bool *RequestNewWeldSignatureData = reinterpret_cast<bool *>(destination->data) ;
            //Set the ReferenceWeldSignatureData flag to indicate that user has requested different Ref Weld Signature in case data transfer for different ref weld signature is in progress.
            *RequestNewWeldSignatureData = m_ReqReferenceWeldSignatureData;

            if(m_ReqReferenceWeldSignatureData == true)
            {
                //Clear contents of existing weld signature data in case user has requested data for different weld signature
                m_RequestedReferenceWeldSignatureData.clear();
                m_RefWeldSignSampleNumberToRead = 0;
            }

            int *WeldResultIndexNumber = reinterpret_cast<int *>(destination->data + sizeof(bool));
            //Set the WeldResultIndex number for which weld signature is to be read.
            *WeldResultIndexNumber = m_RefWeldResultIndexNumberToRead;

            //Set the WeldSignature Sample Number to be read.
            int *WeldSignatureSampleNumber = reinterpret_cast<int *>(destination->data + sizeof(bool) + sizeof(int));
            *WeldSignatureSampleNumber = m_RefWeldSignSampleNumberToRead;

            bool *NewQUeue = reinterpret_cast<bool *>(destination->data + sizeof(bool) + sizeof(int) + sizeof(int));
            *NewQUeue = m_sendNewDequeue;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendRequestedRefWeldSignatureReadRequest = false;

            //Reset the flag to false as we have sent the request.
            m_ReqReferenceWeldSignatureData = false;
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
* \brief   - process the Reference weld signature data coming from ASC
*
* \param   - source - memory block holding the Reference weld signature data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::procesRequestedReferenceWeldSignatureDataFromASC(const MEMORY_BLOCK *const source)
{
    //First byte from response contains WeldResultndex Number to which the weld signature belongs
    int WeldResultIndexNumber = *reinterpret_cast< int*>(source->data);
    int TotalSignatureSamples = *reinterpret_cast< int*>(source->data + sizeof(int));
    bool IsCompleReferenceWeldSignatureRead = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int));
    int IsDataAvalable = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool));

    WeldSignatureACEStruct* RefWeldSignatureData = reinterpret_cast< WeldSignatureACEStruct*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool) + sizeof(int));

    if(WeldResultIndexNumber != m_RefWeldResultIndexNumberToRead)
    {
        //Clear older weld signature data
        m_RequestedReferenceWeldSignatureData.clear();
        m_RefWeldSignSampleNumberToRead = 0;
        m_SendRequestedRefWeldSignatureReadRequest = true;
    }
    else
    {
        for(int SignatureSampleNumber = 0; SignatureSampleNumber < TotalSignatureSamples; SignatureSampleNumber++)
        {
            m_RequestedReferenceWeldSignatureData.push_back(*RefWeldSignatureData);
            RefWeldSignatureData++;
        }

        m_RefWeldSignSampleNumberToRead = m_RefWeldSignSampleNumberToRead + TotalSignatureSamples;

        if(IsCompleReferenceWeldSignatureRead == true)
        {
            m_RefWeldResultIndexNumberToRead = -1;
            m_RefWeldSignSampleNumberToRead = 0;
            m_SendRequestedRefWeldSignatureReadRequest = false;
            m_IsCompleteRefWeldSignatureReceived = true;

            m_AvailableReferenceWeldData.push(m_RequestedReferenceWeldSignatureData);
            if(IsDataAvalable)
            {
                m_RequestedReferenceWeldSignatureData.clear();
                m_RefWeldSignSampleNumberToRead = 0;
                m_RefWeldResultIndexNumberToRead = -1;
                m_ReqReferenceWeldSignatureData = false;
                m_SendRequestedRefWeldSignatureReadRequest = true;
                m_sendNewDequeue = true;
            }

            else
            {
                m_IsReferenceGraphDetailsAvailable = true;
            }
        }
        else
        {
            m_SendRequestedRefWeldSignatureReadRequest = true;
            m_sendNewDequeue = false;
        }
    }

}
/**************************************************************************//**
*
* \brief   - Send Reference weld result read request to ASC
*
* \param   - destination - memory block to hold the request data to be sent to ASC
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::sendReferenceWeldResultReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if( destination->size >= ( sizeof( m_RequestedReferenceWeldResultIndex )  + sizeof( m_WeldResultIndex ) + sizeof(m_WeldResultSampleNumberToRead) ) )
    {
        if( m_SendReferenceWeldSignWeldResultReadRequest == true )
        {
            destination->size = ( sizeof(m_RequestedReferenceWeldResultIndex)  + sizeof(m_WeldResultIndex) + sizeof(m_WeldResultSampleNumberToRead) );
            destination->config = VALID_BIT;

            bool *RequestNewData = reinterpret_cast<bool *>(destination->data) ;
            //Set the RequestNewData flag to indicate that user has requested different weld cycle number data in case data transfer for different weld cycle is in progress.
            *RequestNewData = m_RequestedReferenceWeldResultIndex;

            if(m_RequestedReferenceWeldResultIndex == true)
            {
                //Clear contents of existing data in case user has requested data for different weld cycle number
                m_RequestedReferenceWeldResultData.clear();
                m_WeldResultSampleNumberToRead = 0;
            }

            int *WeldResultIndex = reinterpret_cast<int *>(destination->data + sizeof(bool));
            //Set the WeldResult Index to fetch data /
            *WeldResultIndex = m_WeldResultIndex;

            //Set the WeldResult Sample Number to be read.
            int *WeldResultSampleNumberToRead = reinterpret_cast<int *>(destination->data + sizeof(bool) + sizeof(int));
            *WeldResultSampleNumberToRead = m_WeldResultSampleNumberToRead;

            //Reset the flag to false as we have sent the request.
            //Next request will go when we have received a response for previous request.
            m_SendReferenceWeldSignWeldResultReadRequest = false;

            //Reset the flag to false as we have sent the request.
            m_RequestedReferenceWeldResultIndex = false;
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
* \brief   - process the requested ref weld result index number number weld result data coming from ASC
*
* \param   - source - memory block holding the Reference weld result data
*			 received from ASC
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::processRefereceWeldResultDataFromASC(const MEMORY_BLOCK *const source)
{
    //First byte from response contains WeldResultIndex to which the weld result belongs
    int WeldResultIndex = *reinterpret_cast< int*>(source->data);
    int TotalSamples = *reinterpret_cast< int*>(source->data + sizeof(int));
    bool IsCompleteDataRead = *reinterpret_cast< bool*>(source->data + sizeof(int) + sizeof(int));
    WeldResultACEStruct* WeldResultData = reinterpret_cast< WeldResultACEStruct*>(source->data + sizeof(int) + sizeof(int) + sizeof(bool));

    if(WeldResultIndex != m_WeldResultIndex)
    {
        //Clear older data
        m_RequestedReferenceWeldResultData.clear();
        m_WeldResultSampleNumberToRead = 0;
        m_SendReferenceWeldSignWeldResultReadRequest = true;
    }
    else
    {
        for(int SampleNumber = 0; SampleNumber < TotalSamples; SampleNumber++)
        {
            m_RequestedReferenceWeldResultData.push_back(*WeldResultData);
            WeldResultData++;
        }

        m_WeldResultSampleNumberToRead = m_WeldResultSampleNumberToRead + TotalSamples;

        if(IsCompleteDataRead == true)
        {
            m_WeldResultIndex = -1;
            m_WeldResultSampleNumberToRead = 0;
            m_SendReferenceWeldSignWeldResultReadRequest = false;
        }
        else
        {
            m_SendReferenceWeldSignWeldResultReadRequest = true;
        }
    }
}
/**************************************************************************//**
*
* \brief   - Send reference graph data read request to ASC.
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::sendReferenceGraphReadRequestToASC(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendReferenceWeldGraphSignatureReadRequest == true)
        {
            destination->size = sizeof(bool);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendReferenceWeldGraphSignatureReadRequest = false;
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
* \brief   - Send change reference graph name request to ASC.
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  - none
*
******************************************************************************/

void ReferenceWeldSignature::sendReferenceGraphNameUpdateRequestToASC(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the request data.
    if( destination->size >= (sizeof(m_ReferenceGraphIndexToUpdate) + sizeof(m_UpdateRefGraphName)) )
    {
        if(m_SendUpdateRefGraphNameRequest == true)
        {
            memcpy(reinterpret_cast<int*>(destination->data), &m_ReferenceGraphIndexToUpdate, sizeof(m_ReferenceGraphIndexToUpdate));
            strncpy(reinterpret_cast<char*>(destination->data + sizeof(m_ReferenceGraphIndexToUpdate)), m_UpdateRefGraphName, REF_GRAPH_NAME_SIZE);

            destination->size = sizeof(m_ReferenceGraphIndexToUpdate) + sizeof(m_UpdateRefGraphName);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendUpdateRefGraphNameRequest = false;

            //Reset the Graph Name holding variable once the request is sent
            memset(m_UpdateRefGraphName, 0, sizeof(m_UpdateRefGraphName));
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
* \brief   - Send Replace Old Reference Graph with new request to ASC.
*
* \param   - destination - memory block to hold the request data to be sent to ASC
*
* \return  - none
*
******************************************************************************/

void ReferenceWeldSignature::sendReferenceGraphReplaceRequestToASC(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the request data.
    if( destination->size >= (sizeof(m_ReferenceGraphOldWeldResultToUpdate) + sizeof(m_ReferenceGraphNewWeldResultToUpdate)) )
    {
        if(m_SendReplaceRefGraphRequest == true)
        {
            memcpy(reinterpret_cast<int*>(destination->data), &m_ReferenceGraphOldWeldResultToUpdate, sizeof(m_ReferenceGraphOldWeldResultToUpdate));
            memcpy(reinterpret_cast<int*>(destination->data +  + sizeof(int)), &m_ReferenceGraphNewWeldResultToUpdate, sizeof(m_ReferenceGraphNewWeldResultToUpdate));

            destination->size = sizeof(m_ReferenceGraphOldWeldResultToUpdate) + sizeof(m_ReferenceGraphNewWeldResultToUpdate);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendReplaceRefGraphRequest = false;
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
* \brief   - Process the referenceGraphData response coming from ASC containg GraphName,CycleNumber,WeldResultIndex.
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
*****************************************************************************/
void ReferenceWeldSignature::processReferenceGraphDataFromASC(const MEMORY_BLOCK *const source)
{
    int *NumberOfRefWeldSignatures = reinterpret_cast<int *>(source->data);
    ReferenceGraphStruct *ReferenceGraphStructDataPtr = reinterpret_cast<ReferenceGraphStruct *>(source->data + sizeof(int));
    m_ReferenceGraphStructData.clear();
    for(int i = 0; i < *NumberOfRefWeldSignatures; i++)
    {
        m_ReferenceGraphStructData.push_back( *ReferenceGraphStructDataPtr);
        ReferenceGraphStructDataPtr++;
    }
}

/**************************************************************************//**
*
* \brief   - Send read request (if data is available)to ASC when HMI is power up.
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::sendReferenceGraphReadRequestToASConPowerUp(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendReferenceWeldReadRequestonPowerUp == true)
        {
            destination->size = sizeof(bool);
            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendReferenceWeldReadRequestonPowerUp = false;
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
* \brief   - HMI/front end code should call this function when it wants
* 			 to read a particular weld signature.
*
*
* \param   - WeldResultIndexNumber - Weld Result Index Number for which the
* 			weld signature needs to be fetched
*
* \return  - void
******************************************************************************/
void ReferenceWeldSignature::SetReferenceWeldSignatureRequestFromHMI(int WeldResultIndexNumber)
{
    if(m_RefWeldResultIndexNumberToRead != WeldResultIndexNumber)
    {
        m_RefWeldResultIndexNumberToRead = WeldResultIndexNumber;

        //Clear the old data
        while(!m_AvailableReferenceWeldData.empty()){
            m_AvailableReferenceWeldData.pop();
        }
        m_RequestedReferenceWeldSignatureData.clear();
        //User has requested data for different weld signature.
        m_ReqReferenceWeldSignatureData = true;
        m_SendRequestedRefWeldSignatureReadRequest = true;
    }
}

/**************************************************************************
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to Update the Name for Reference Graph
*
* \param   - WeldResultIndexNumber - Weld Result Index Number for which the Name should update
*            Name - Name of the graph to Update.
*
*
* \return  - void
******************************************************************************/
void ReferenceWeldSignature::InitiateReferenceWeldSignatureNameUpdateRequest(int WeldResultIndexNumber, std::string Name)
{
    while(!m_AvailableReferenceWeldData.empty()){
        m_AvailableReferenceWeldData.pop();
    }
    m_RequestedReferenceWeldSignatureData.clear();

    m_ReferenceGraphIndexToUpdate = WeldResultIndexNumber;
    std::strncpy(m_UpdateRefGraphName, Name.c_str(), sizeof(m_UpdateRefGraphName) - 1);
    m_SendUpdateRefGraphNameRequest = true;
}

/**************************************************************************
*
* \brief   - HMI/front end code should call this function when it wants
* 			 to add new graph as reference graph if more than 3 graph are there in list.
*
* \param   - OldWeldResultIndexNumber - Index of whos to be replaced.
*            NewWeldResultIndexNumber - Index of Graph to add as reference graph.
*
* \return  - void
******************************************************************************/
void ReferenceWeldSignature::InitiateReplaceOldRefGraphWithNewRefGraphRequest(int OldWeldResultIndexNumber, int NewWeldResultIndexNumber)
{
    while(!m_AvailableReferenceWeldData.empty()){
        m_AvailableReferenceWeldData.pop();
    }
    m_RequestedReferenceWeldSignatureData.clear();

    m_ReferenceGraphOldWeldResultToUpdate = OldWeldResultIndexNumber;
    m_ReferenceGraphNewWeldResultToUpdate = NewWeldResultIndexNumber;
    m_SendReplaceRefGraphRequest = true;
}

/**************************************************************************
*
* \brief   - Used to return th Reference graph details data
*
* \param   - None
*
* \return  - m_ReferenceGraphStructData
******************************************************************************/
std::deque<ReferenceGraphStruct>  ReferenceWeldSignature::GetReferenceGraphStruct()
{
    return m_ReferenceGraphStructData;
}

/**************************************************************************
*
* \brief   - Used to return the Reference graph signature data
*
* \param   - None
*
* \return  - m_RequestedReferenceWeldSignatureData
******************************************************************************/
std::deque<WeldSignatureACEStruct> ReferenceWeldSignature::GetRequestedReferenceWeldSignatureData()
{
    return m_RequestedReferenceWeldSignatureData;
}

/**************************************************************************
*
* \brief   - Used to return the Reference graph signature data queue
*
* \param   - None
*
* \return  - m_AvailableReferenceWeldData
******************************************************************************/
std::queue<std::deque<WeldSignatureACEStruct> > ReferenceWeldSignature::GetAvailableReferenceWeldData()
{
    return m_AvailableReferenceWeldData;
}
/**************************************************************************
*
* \brief   - Used to set m_IsReferenceGraphDetailsAvailable to false.
*
* \param   - None
*
* \return  - none
******************************************************************************/
void  ReferenceWeldSignature::SetIsReferenceGraphDetailsAvailable()
{
    m_IsReferenceGraphDetailsAvailable= false;
}
/**************************************************************************
*
* \brief   - Function used by HMI to know if data is available.
*
* \param   - None
*
* \return  - m_IsReferenceGraphDetailsAvailable
******************************************************************************/
bool  ReferenceWeldSignature::GetIsReferenceGraphDetailsAvailable()
{
    return m_IsReferenceGraphDetailsAvailable;
}
/**************************************************************************
*
* \brief   - Function used by HMI to fetch the status of the replace request sent by HMI.
*
* \param   - None
*
* \return  - m_ReplaceRefGraphStatus
******************************************************************************/
bool  ReferenceWeldSignature::GetRefGraphStatusFromASC()
{
    return m_ReplaceRefGraphStatus;
}
/**************************************************************************
*
* \brief   - Set m_ReplaceRefGraphStatus to false once received from ASC.
*
* \param   - None
*
* \return  - None
******************************************************************************/
void  ReferenceWeldSignature::SetReplaceRefGraphStatus()
{
    m_ReplaceRefGraphStatus = false;
}
/**************************************************************************//**
 * \brief: Process the request form ASC to get the replace request status.
 *
 * \param: source - to hold the memory block containing the status of the replace request
 *
 * \return: None.
 *
 ******************************************************************************/
void ReferenceWeldSignature::processReplaceReferenceGraphStatusFromASC(const MEMORY_BLOCK *const source)
{
    m_ReplaceRefGraphStatus = true;
}
/**************************************************************************//**
*
* \brief   - print search by cycle number Weld Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::printSearchByCycleNumberdWeldResult()
{
    if(m_RequestedReferenceWeldResultData.empty())
    {
        std::cout << "No Weld Result Available for searched cycle number" << std::endl;
    }
    else
    {
        std::cout << "**********searched cycle number Weld Result Data**********" << std::endl;

        for (unsigned int Index = 0; Index < m_RequestedReferenceWeldResultData.size(); Index++)
        {
            std::cout << "WeldResultIndex: " << m_RequestedReferenceWeldResultData[Index].WeldResultIndex << std::endl;
            std::cout << "WeldRecipeNumber: " << m_RequestedReferenceWeldResultData[Index].WeldRecipeNumber << std::endl;
            std::cout << "WeldRecipeVersionNumber: " << m_RequestedReferenceWeldResultData[Index].WeldRecipeVersionNumber << std::endl;
            std::cout << "DateTime: " << m_RequestedReferenceWeldResultData[Index].DateTime << std::endl;
            std::cout << "StackSerialNumber: " << m_RequestedReferenceWeldResultData[Index].StackSerialNumber << std::endl;
            std::cout << "PowerSupplySerialNumber: " << m_RequestedReferenceWeldResultData[Index].PowerSupplySerialNumber << std::endl;
            std::cout << "ActuatorSerialNumber: " << m_RequestedReferenceWeldResultData[Index].ActuatorSerialNumber << std::endl;
            std::cout << "ASCSerialNumber: " << m_RequestedReferenceWeldResultData[Index].ASCSerialNumber << std::endl;
            std::cout << "CycleCounter: " << m_RequestedReferenceWeldResultData[Index].CycleCounter << std::endl;
            std::cout << "WeldMode: " << m_RequestedReferenceWeldResultData[Index].WeldMode << std::endl;
            std::cout << "WeldTime: " << m_RequestedReferenceWeldResultData[Index].WeldTime << std::endl;
            std::cout << "HoldTime: " << m_RequestedReferenceWeldResultData[Index].HoldTime << std::endl;
            std::cout << "WeldEnergy: " << m_RequestedReferenceWeldResultData[Index].WeldEnergy << std::endl;
            std::cout << "WeldPeakPower: " << m_RequestedReferenceWeldResultData[Index].WeldPeakPower << std::endl;
            std::cout << "StartFrequency: " << m_RequestedReferenceWeldResultData[Index].StartFrequency << std::endl;
            std::cout << "FrequencyChange: " << m_RequestedReferenceWeldResultData[Index].FrequencyChange << std::endl;
            std::cout << "CycleTime: " << m_RequestedReferenceWeldResultData[Index].CycleTime << std::endl;
            std::cout << "UserName: " << m_RequestedReferenceWeldResultData[Index].UserName << std::endl;
            std::cout << "PartID: " << m_RequestedReferenceWeldResultData[Index].PartID << std::endl;
            std::cout << "BatchID: " << m_RequestedReferenceWeldResultData[Index].BatchID << std::endl;
            std::cout << "TriggerPoint: " << m_RequestedReferenceWeldResultData[Index].TriggerPoint	 << std::endl;
            std::cout << "WeldSonicPoint: " << m_RequestedReferenceWeldResultData[Index].WeldSonicPoint << std::endl;
            std::cout << "HoldPoint: " << m_RequestedReferenceWeldResultData[Index].HoldPoint << std::endl;
            std::cout << "AlarmID: " << m_RequestedReferenceWeldResultData[Index].AlarmID << std::endl;
            std::cout << "WeldStatus: " << m_RequestedReferenceWeldResultData[Index].WeldStatus << std::endl;
            std::cout << "RecipeStatus: " << m_RequestedReferenceWeldResultData[Index].RecipeStatus << std::endl;
            std::cout << "WeldPressure: " << m_RequestedReferenceWeldResultData[Index].WeldPressure << std::endl;
            std::cout << "HoldPressure: " << m_RequestedReferenceWeldResultData[Index].HoldPressure << std::endl;
            std::cout << "MaxWeldForce: " << m_RequestedReferenceWeldResultData[Index].MaxWeldForce << std::endl;
            std::cout << "MaxHoldForce: " << m_RequestedReferenceWeldResultData[Index].MaxHoldForce << std::endl;
            std::cout << "EndWeldForce: " <<m_RequestedReferenceWeldResultData[Index].EndWeldForce << std::endl;
            std::cout << "EndHoldForce: " << m_RequestedReferenceWeldResultData[Index].EndHoldForce << std::endl;
            std::cout << "WeldAbsolute: " << m_RequestedReferenceWeldResultData[Index].WeldAbsolute << std::endl;
            std::cout << "TotalAbsolute: " << m_RequestedReferenceWeldResultData[Index].TotalAbsolute << std::endl;
            std::cout << "Velocity: " << m_RequestedReferenceWeldResultData[Index].Velocity << std::endl;
            std::cout << "DownSpeed: " << m_RequestedReferenceWeldResultData[Index].DownSpeed << std::endl;
            std::cout << "TriggerDistance: " << m_RequestedReferenceWeldResultData[Index].TriggerDistance << std::endl;
            std::cout << "WeldCollapseDistance: " << m_RequestedReferenceWeldResultData[Index].WeldCollapseDistance << std::endl;
            std::cout << "HoldCollapseDistance: " << m_RequestedReferenceWeldResultData[Index].HoldCollapseDistance << std::endl;
            std::cout << "TotalCollapseDistance: " << m_RequestedReferenceWeldResultData[Index].TotalCollapseDistance << std::endl;
            std::cout << "*************************************" << std::endl;
        }
    }
}
/**************************************************************************//**
*
* \brief   - print search by cycle number Weld Result data
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature:: printReferenceGraphDetails()
{
    if(m_ReferenceGraphStructData.empty())
    {
        std::cout << "************No Reference Weld Signature Available**************" << std::endl;
    }
    else
    {
        std::cout << "********** Data **********" << std::endl;

        for (unsigned int Index = 0; Index < m_ReferenceGraphStructData.size(); Index++)
        {
            std::cout << "RefGraphName: " << m_ReferenceGraphStructData[Index].RefGraphName << std::endl;
            std::cout << "RefweldResultIndex: " << m_ReferenceGraphStructData[Index].RefweldResultIndex << std::endl;
            std::cout << "RefGraphcycleCounter: " << m_ReferenceGraphStructData[Index].RefGraphcycleCounter << std::endl;
        }
        std::cout << "****************************" << std::endl;
    }
}
/**************************************************************************//**
*
* \brief   - print Reference weld signature data.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void ReferenceWeldSignature::ShowRequestedWeldSignatureDataFromCache()
{
    std::cout << "Available Reference Weld Data:" << std::endl;

    std::queue<std::deque<WeldSignatureACEStruct>> tempQueue = m_AvailableReferenceWeldData; // Create a copy of the queue
    int dequeIndex = 0;

    for (int i = 0; !tempQueue.empty(); ++i)
    {
        const std::deque<WeldSignatureACEStruct>& weldDataDeque = tempQueue.front();
        std::cout << "Deque " << dequeIndex++ << ":" << std::endl;
        int elementIndex = 0;
        for (unsigned int Index = 0; Index < weldDataDeque.size(); Index++)
        {
            std::cout << weldDataDeque[Index].Time << ',';
            std::cout << weldDataDeque[Index].Amplitude << ',';
            std::cout << weldDataDeque[Index].Phase << ',';
            std::cout << weldDataDeque[Index].Current << ',';
            std::cout << weldDataDeque[Index].Frequency << ',';
            std::cout << weldDataDeque[Index].Power << ',';
            std::cout << weldDataDeque[Index].Energy << ',';
            std::cout << weldDataDeque[Index].RequestAmplitude << ',';
            std::cout << weldDataDeque[Index].AbsoluteDistance << ',';
            std::cout << weldDataDeque[Index].CollapseDistance << ',';
            std::cout << weldDataDeque[Index].Force << ',';
            std::cout << weldDataDeque[Index].Velocity  << '\n';
        }
        tempQueue.pop();
    }
}


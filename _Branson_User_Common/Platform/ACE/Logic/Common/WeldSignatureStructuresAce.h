/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the ACE weld signature related structure definition.
 
***************************************************************************/

#ifndef WELD_SIGNATURE_STRUCTURES_ACE_H_
#define WELD_SIGNATURE_STRUCTURES_ACE_H_

#include "Common_Definitions.h"

constexpr unsigned int MIN_GRAPH_SAMPLING_INTERVAL_IN_MILLISECONDS = 1;
constexpr unsigned int MAX_GRAPH_SAMPLING_INTERVAL_IN_MILLISECONDS = 100;

//Maximum number of weld signature structures sent in one chunk
constexpr int MAX_NUM_OF_WELD_SIGNATURES_IN_ONE_CHUNK = 200; 

typedef struct WeldSignatureACEStruct
{
	float Time;
	uint32_t Amplitude;
	int32_t Phase;
	uint32_t Current;
	uint32_t Frequency;
	float Power;
	float Energy;
	uint32_t RequestAmplitude;
	float AbsoluteDistance;
	float CollapseDistance;
	float Force;
	float Velocity; 
		
	WeldSignatureACEStruct()
	{
		Time = 0.0f;
		Amplitude = 0;
		Phase = 0;
		Current = 0;
		Frequency = 0;
		Power = 0.0f;
		Energy = 0.0f;
		RequestAmplitude = 0;
		AbsoluteDistance = 0.0f;
		CollapseDistance = 0.0f;
		Force = 0.0f;
		Velocity = 0.0f;
	}
}__attribute__((packed))  WeldSignatureACEStruct;


typedef struct ReferenceGraphStruct
{
    char RefGraphName[REF_GRAPH_NAME_SIZE];
	int RefGraphcycleCounter;
	int RefweldResultIndex;
	
	// Constructor
	ReferenceGraphStruct()
	{
		// Initialize the name to an empty string
		strncpy(RefGraphName, "", REF_GRAPH_NAME_SIZE - 1);
		RefGraphName[REF_GRAPH_NAME_SIZE - 1] = '\0'; 
			RefGraphcycleCounter = 0;
		RefweldResultIndex = 0;
	}
}__attribute__((packed))  ReferenceGraphStruct;

typedef enum
{
	READ_REFERENCE_WELD_SIGNATURE_DATA = 1,
	READ_REFERENCE_WELD_RESULT_DATA ,
    READ_REFERENCE_GRAPH_DATA_FOR_NAME,
	UPDATE_NAME_FOR_REFERENCE_WELD_GRAPH,
    REPLACE_OLD_REFGRAPH_BY_NEW_REFGRAPH,
    SEND_DATA_ON_REFERENCEWELDDATA_READ_REQUEST,

}REFERENCE_WELD_RESULT_SUB_ID;



#endif /* WELD_SIGNATURE_STRUCTURES_ACE_H_ */

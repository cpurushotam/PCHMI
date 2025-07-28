/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Seek signature related implementation
 ***************************************************************************/

#ifndef SEEK_SIGNATURE_STRUCTURE_H_
#define SEEK_SIGNATURE_STRUCTURE_H_


typedef enum
{
	READ_SEEK_SIGNATURE_DATA = 1
}SEEK_SIGNATURE_ACE_SUB_ID;

//Maximum number of seek signature structures sent in one chunk
constexpr int MAX_NUM_OF_SEEK_SIGNATURES_IN_ONE_CHUNK = 400;

typedef struct SeekSignatureStruct
{
	float Time;
	uint32_t Amplitude;
	uint32_t Frequency;
	float Power;
	uint32_t Current;
	int32_t Phase;

	
	SeekSignatureStruct()
	{
		Time = 0.0f;
		Amplitude = 0;
		Frequency = 0;
		Power = 0.0f;
		Current = 0;
		Phase = 0;		
	}
}__attribute__((packed)) SeekSignatureStruct;

#endif //SEEK_SIGNATURE_STRUCTURE_H_

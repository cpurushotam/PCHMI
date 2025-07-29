/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Test signature related implementation
 ***************************************************************************/

#ifndef TEST_SIGNATURE_STRUCTURE_H_
#define TEST_SIGNATURE_STRUCTURE_H_

//Maximum number of test signature structures sent in one chunk
constexpr int MAX_NUM_OF_TEST_SIGNATURES_IN_ONE_CHUNK = 400; 

// definition for SUB-ID of memory block
typedef enum{
    SUB_ID_SEND_TEST_SIGNATURE_DATA = 1,
}TEST_SIGNATURE_SUB_ID;

typedef struct TestSignatureStruct
{
	float Time;
	uint32_t Amplitude;
	int32_t Phase;
	uint32_t Current;
	uint32_t Frequency;
	float Power;
	
	TestSignatureStruct()
	{
		Time = 0.0f;
		Amplitude = 0;
		Phase = 0;
		Current = 0;
		Frequency = 0;
		Power = 0.0f;
	}
}__attribute__((packed)) TestSignatureStruct;

#endif //TEST_SIGNATURE_STRUCTURE_H_

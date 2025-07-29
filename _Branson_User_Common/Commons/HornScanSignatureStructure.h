/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Horn Scan Signature related implementation
 ***************************************************************************/

#ifndef HORN_SCAN_SIGNATURE_STRUCTURE_H_
#define HORN_SCAN_SIGNATURE_STRUCTURE_H_

//Maximum number of horn scan signature structures sent in one chunk
constexpr int MAX_NUM_OF_HORN_SCAN_SIGNATURES_IN_ONE_CHUNK = 500; 

typedef enum
{
    READ_REQUESTED_HORN_SCAN_SIGNATURE_DATA = 1,
}HORN_SCAN_SIGNATURE_SUB_ID;

typedef struct HornScanSignatureStruct
{
	uint32_t Amplitude;
	uint32_t Current;
	int32_t Phase;
	uint32_t Frequency;
	uint32_t TargetAmplitude;
	
	HornScanSignatureStruct()
	{
		Amplitude = 0;
		Current = 0;
		Phase = 0;
		Frequency = 0;
		TargetAmplitude = 0;		
	}
}__attribute__((packed)) HornScanSignatureStruct;

#endif //HORN_SCAN_SIGNATURE_STRUCTURE_H_

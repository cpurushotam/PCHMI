/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the USB stream related implementation
 ***************************************************************************/

#ifndef USBSTREAMSTRUCTURE_H_
#define USBSTREAMSTRUCTURE_H_

#include "Common_Definitions.h"

// Data Interface ID declarations
typedef enum
{
	STREAM_DATA_SAVE = 1,
	STREAM_DATA,
}MEMORY_BLOCK_SUB_ID_STREAMING;
 
typedef enum
{
	USB_STREAM,
    NFS_STREAM,
	TCP_IP_STREAM
}STREAMING_STORAGE_OPTIONS;

typedef struct USBStreamStruct
{
    bool EnableWeldData;
    bool EnableEncryption;
    int32_t WeldCyclesCompleted;
    bool UsbAmplitude;
    bool UsbPower;
    bool UsbPhase;
    bool UsbCurrent;
    bool UsbFrequency;
    bool UsbEnergy;
    bool UsbRequestAmplitude;
    bool UsbAbsoluteDist;
    bool UsbColDist;
    bool UsbForce;
    bool UsbVelocity;
    bool SaveOnAlarm;
    STREAMING_STORAGE_OPTIONS StreamingStorageOption;
} __attribute__((packed)) USBStreamStruct;



#endif /* USBSTREAMSTRUCT_H_ */

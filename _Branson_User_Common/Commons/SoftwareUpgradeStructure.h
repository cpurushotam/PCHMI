/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains software upgrade related implementation
 ***************************************************************************/

#ifndef SOFTWARE_UPGRADE_STRUCTURE_H_
#define SOFTWARE_UPGRADE_STRUCTURE_H_

#include <stdint.h>
#include<string>
#include "Common_Definitions.h"

#define  FIRMWARE_UPGRADE_FILE_EXTENSION       ".bin"
#define  SC_FIRMWARE_UPGRADE_FILE_PREFIX       "SC_"
#define  AC_FIRMWARE_UPGRADE_FILE_PREFIX       "AC_"
#define  HMI_FIRMWARE_UPGRADE_FILE_PREFIX      "HMI_"
#define  FIRMWARE_UPGRADE_EMPTY_FILE_NAME      "None"
#define  FIRMWARE_UPGRADE_MAX_FILE_LIST         2
#define  SC_FIRMWARE_UPGRADE                    0
#define  AC_FIRMWARE_UPGRADE                    1

#define   FILE_SIZE_ZERO      0x0003
#define   FAILED			 -1
#define   ZERO_BYTES          0
#define	  READ_BYTE           1

#define   READ_BINARY        "rb"

#define UBOOT_VERSION_QSPI_OFFSET	           0x00020000
#define FW_PARTITION_INFO_QSPI_OFFSET_CRC	   0x001D0000
#define FW_PARTITION_INFO_QSPI_OFFSET		   0x001C0000

/* Allocated size of active VxWorks bin */
#define ACTIVE_PART_FIRMWARE_START	 	0x001E0000 

/* Allocated size of passive VxWorks bin */
#define PASSIVE_PART_FIRMWARE_START	 	0x02000000 


/* Allocated size of active VxWorks bin */
#define ACTIVE_PART_FIRMWARE_START	 	       0x001E0000 
/* Allocated size of passive VxWorks bin */
#define PASSIVE_PART_FIRMWARE_START	 	       0x02000000
#define ACTIVE_BOOTMODE 				0X00
#define PASSIVE_BOOTMODE  				0x01

/*	uboot version+timestamp	*/
#define UBOOT_VERSION				           0x133C648 //20170312

#define FIRMWARE_UPGRADE_FALSE			0x00
#define FIRMWARE_UPGRADE_TRUE	 		0x01

typedef struct FirmwarePartitionInfoCRC 
{
	volatile    uint32_t	boot_status;
	volatile    uint32_t	fw_upgrade;
	volatile    uint32_t	partition_a_offset;
	volatile    uint32_t	partition_b_offset;	 
	volatile    uint32_t	partition_a_size;
	volatile    uint32_t	partition_b_size;
	volatile    uint16_t	partition_a_crc;
	volatile    uint16_t	partition_b_crc;
	volatile    uint16_t	emmc_copy;
} FirmwarePartitionInfoCRC;

typedef struct FirmwarePartitionInfo 
{
	uint32_t bootMode;
	uint32_t fwUpgrade;
	uint32_t activePart;
	uint32_t passivePart;
} FirmwarePartitionInfo;

typedef enum
{
    MB_READ_USB_REQUEST = 1,
    MB_UPGRADE_REQUEST,
    MB_DONE_REQUEST
}SOFTWARE_UPGRADE_MB_SUB_ID;

typedef enum
{
	SOFTWARE_UPGRADE_ERROR_UNKNOWN = 0,
	SOFTWARE_UPGRADE_FAILURE,
	SOFTWARE_UPGRADE_SUCCESS
}SOFTWARE_UPGRADE_ERROR_CODES;

typedef struct SoftwareUpgradeStruct
{
    char SoftwareUpgradeFileName[SW_UPGRADE_MAX_FILE_NAME_SIZE];
    SoftwareUpgradeStruct()
    {
		// Use strncpy to copy the string and ensure null termination
		strncpy(SoftwareUpgradeFileName, "None", sizeof(SoftwareUpgradeFileName) - 1);
		SoftwareUpgradeFileName[sizeof(SoftwareUpgradeFileName) - 1] = '\0'; // Ensure null termination
    }
		
}__attribute__((packed)) SoftwareUpgradeStruct;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  Lookup Tables.  The "hardware" method of computing CRCs involves bit   */
/*  manipulations, which is very inefficient for a software computation.   */
/*  Instead of computing the CRC bit-by-bit, a 256-element lookup table    */
/*  can be used to perform the equivalent of 8 bit operations at a time.   */
/*  (This is described in "Byte-wise CRC Calculations" in IEEE Micro,      */
/*  June 1983, pp. 40-50.)  For a CRC-16, the lookup table consists of 256 */
/*  2-byte WORDs (see below, or the CRC16.PAS unit for the actual table,   */
/*  or the CRCTable program for computation of the lookup table for the    */
/*  x16 + x15 + x2 + 1 generator polynomial):                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/
const unsigned short CRCTable[256] =
{
  0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0,
  0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41,
  0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0,
  0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1,
  0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341,
  0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1,
  0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0,
  0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1, 0xE981, 0x2940,
  0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1,
  0xEC81, 0x2C40, 0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041, 0xA001, 0x60C0,
  0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740,
  0xA501, 0x65C0, 0x6480, 0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0,
  0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01, 0x7EC0,
  0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541,
  0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0,
  0x7080, 0xB041, 0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440, 0x9C01, 0x5CC0,
  0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40,
  0x9901, 0x59C0, 0x5880, 0x9841, 0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1,
  0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0,
  0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};

#endif


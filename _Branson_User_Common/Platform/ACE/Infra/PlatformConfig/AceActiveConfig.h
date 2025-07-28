/**************************************************************************

 	 	 Copyright (c) Branson Ultrasonics Corporation, 1996-2023

 	 	 This program is the property of Branson Ultrasonics Corporation
		 Copying of this software is expressly forbidden, without the prior
 	 	 written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
	ACE platform Configuration

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/09/2023 - Initial implementation,	Added actuator configuration.
 rev2: 12/10/2023 - Added HMI device support configuration.

***************************************************************************/

#ifndef ACEACTIVECONFIG_H_
#define ACEACTIVECONFIG_H_

#include "ActuatorInit.h"
#include "PowerSupplyType.h" 
#include "PowerLevelSysFrequencySupport.h"
#include "CylinderSizeSupport.h"
#include "StrokeLength.h"
#include "FieldbusSupport.h" 
#include "StorageSupport.h"
#include "EventLogSupport.h"
#include "BatchControlSupport.h"
#include "LDAPSupport.h"
#include "UserAccessLevelSupport.h"
#include "BarcodeScannerSupport.h"
#include "UserIOSupport.h"
#include "PCUtilitySupport.h"
#include "HMIDeviceSupport.h"
#include "ActiveConfiguration.h"
#include "BearingTypeSupport.h"

/**************************************************************************//**
* \brief   - Creation of configuration class objects for AceActiveConfig Table
*
******************************************************************************/

ActuatorInit *ActuatorTypeObj =  new ActuatorInit();
PowerSupplyTypeSupport *PowerSupplyTypeSupportObj = new PowerSupplyTypeSupport();
PowerLevelSysFrequencySupport *PowerLevelSysFrequencySupportObj = new PowerLevelSysFrequencySupport();
FieldbusSupport *FieldbusSupportObj = new FieldbusSupport();
CylinderSizeSupport *CylinderSizeSupportObj = new CylinderSizeSupport();
StrokelengthSupport *StrokelengthSupportObj = new StrokelengthSupport();
StorageSupport *StorageSupportObj = new StorageSupport();
EventLogSupport *EventLogSupportObj = new EventLogSupport();
BatchControlSupport *BatchControlSupportObj = new BatchControlSupport();
LDAPSupport *LDAPSupportObj = new LDAPSupport();
UserAccessLevelSupport *UserAccessLevelSupportObj = new UserAccessLevelSupport();
BarcodeScannerSupport *BarcodeScannerSupportObj = new BarcodeScannerSupport();
UserIOSupport *UserIOSupportObj = new UserIOSupport();
PCUtilitySupport *PCUtilitySupportObj = new PCUtilitySupport();
HMIDeviceSupport *HMIDeviceSupportObj =  new HMIDeviceSupport();
BearingTypeSupport *BearingTypeSupportObj = new BearingTypeSupport();

/**************************************************************************//**
* \brief   - Definition of active configuration for ACE platform .
*			 All supported configuration for ACE platform should configured in
*			 AceActiveConfig table.
*
******************************************************************************/
ActiveConfig AceActiveConfig =
{
	/* Configuration,    object of configuration class */
	{ ACTUATOR_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (ActuatorTypeObj)},
	{ POWER_SUPPLY_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (PowerSupplyTypeSupportObj)},
	{ POWER_LEVEL_SYSTEM_FREQUENCY_KEY, dynamic_cast<PlatformConfigInterface*> (PowerLevelSysFrequencySupportObj)},
	{ CYLINDER_SIZE_KEY, dynamic_cast<PlatformConfigInterface*> (CylinderSizeSupportObj)},
	{ BEARING_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (BearingTypeSupportObj)},
	{ STROKE_LENGTH_KEY, dynamic_cast<PlatformConfigInterface*> (StrokelengthSupportObj)},
	{ FIELDBUS_SUPPORT_KEY, dynamic_cast<PlatformConfigInterface*> (FieldbusSupportObj)},
	{ STORAGE_KEY, dynamic_cast<PlatformConfigInterface*> (StorageSupportObj)},
	{ EVENT_LOG_KEY, dynamic_cast<PlatformConfigInterface*> (EventLogSupportObj)}, 
	{ BATCH_CONTROL_KEY, dynamic_cast<PlatformConfigInterface*> (BatchControlSupportObj)},
	{ LDAP_KEY, dynamic_cast<PlatformConfigInterface*> (LDAPSupportObj)},
	{ USER_ACCESS_LEVEL_TYPE_KEY, dynamic_cast<PlatformConfigInterface*> (UserAccessLevelSupportObj)},
	{ BARCODE_SCANNER_KEY, dynamic_cast<PlatformConfigInterface*> (BarcodeScannerSupportObj)},
	{ USER_IO_KEY, dynamic_cast<PlatformConfigInterface*> (UserIOSupportObj)},
	{ PC_UTILITY_KEY, dynamic_cast<PlatformConfigInterface*> (PCUtilitySupportObj)},
	{ HMI_DEVICE, dynamic_cast<PlatformConfigInterface*> (HMIDeviceSupportObj)},
};

#endif /* ACEACTIVECONFIG_H_ */

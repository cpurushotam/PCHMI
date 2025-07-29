/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the User management related implementation
 ***************************************************************************/

#ifndef USER_MANAGEMENT_STRUCTURES_H_
#define USER_MANAGEMENT_STRUCTURES_H_

#include <map>
#include <tuple>
#include <string.h>
#include "Common_Definitions.h"

typedef enum
{
	MB_USER_LIST_REQUEST = 1,
	MB_LOGIN_REQUEST,
    MB_AUTO_LOGIN_REQUEST,
    MB_LOGOUT_REQUEST,
    MB_VERIFY_AND_CHANGE_PASSWORD_REQUEST,
	MB_CHANGE_PASSWORD_REQUEST,
	MB_ADD_USER_REQUEST,
    MB_MODIFY_USER_REQUEST,
	MB_DELETE_USER_REQUEST,
	MB_USER_PRIVILEGE_REQUEST,
	MB_PASSWORD_OVERRIDE_REQUEST,
	MB_SYNC_USER_LIST,
	MB_LDAP_CONFIG_READ_REQUEST,
	MB_LDAP_CONFIG_UPDATE_REQUEST
}USER_MANAGEMENT_MB_SUB_ID;

typedef enum
{
	LOGIN_ERROR_UNKNOWN = 0,
	LOGIN_SUCCESS,
	INVALID_USER_NAME_OR_PASSWORD,
	USER_LOCKED,
	USER_DISABLED,
	PASSWORD_EXPIRED,
	PASSWORD_WILL_EXPIRE_SOON, 
	FIRST_TIME_LOGIN,
    PASSWORD_NOT_EXPIRED,
	AUTHORITY_CHECK_DISABLE,
	TWO_UNSUCCESSFUL_LOGIN_ATTEMPT
}LOGIN_ERROR_CODES;

typedef enum
{
    LOGOUT_ERROR_UNKNOWN = 0,
    LOGOUT_SUCCESS,
}LOGOUT_ERROR_CODES;

typedef enum
{
	ADD_USER_ERROR_UNKNOWN = 0,
	ADD_USER_SUCCESS,
	ADD_USER_FAIL,
	USER_ALREADY_EXIST,
	ADD_USER_LIMIT_CROSSED,
    EXECUTIVE_USER_NOT_LOGGED_IN,
    ADD_USER_DOES_NOT_MEET_PASSWORD_POLICY
}ADD_USER_ERROR_CODES;

typedef enum
{
	MODIFY_USER_ERROR_UNKNOWN = 0,
	MODIFY_USER_SUCCESS,
	MODIFY_USER_FAIL,
	MODIFY_USER_NOT_EXIST_IN_DB,
    NEED_AT_LEAST_ONE_EXECUTIVE_USER,
	MODIFY_USER_DONT_HAVE_ACCESS,
    MODIFY_PASSWORD_SUCCESS,
	MODIFY_PASSWORD_FAIL,
    WRONG_EXISTING_PASSWORD,
	MIN_ONE_EXECUTIVE_LEVEL_USER_REQUIRED,
	DELETE_USER_SUCCESS,
    DELETE_USER_FAIL,
    CAN_NOT_DELETE_LOGGED_IN_USER,
    NEED_AT_LEAST_ONE_USER_IN_SYSTEM,
    DOES_NOT_MEET_PASSWORD_POLICY,
	CURRENT_AND_NEW_PASSWORD_SAME,
}MODIFY_USER_ERROR_CODES;

typedef enum
{
	ENABLE  = 0,
	DISABLE
}USER_STATUS;

typedef enum
{
	UNLOCKED = 0,
	LOCKED
	
}USER_ISLOCKED;

typedef enum
{
    UNKNOWN_USER_LEVEL = -1,
    OPERATOR,
	TECHNICIAN,
	SUPERVISOR,
	EXECUTIVE 
}USER_LEVEL;

typedef enum
{
	ADD_USER_OPERATION,
	MODIFY_USER_OPERATION,
	MODIFY_LOGIN_DATA_OPERATION,
	DELETE_USER_OPERATION,
	CHANGE_PASSWORD_OPERATION,
}USER_UPDATE_OPERATION;

typedef enum
{
	UNKNOWN_PARAM = -1,
	SEQ_FAILED_LOGIN_ATTEMPT,
	IS_LOCKED,
	LAST_LOGIN,
	LAST_SEQ_FAILED_LOGIN_TIME,
}USER_LOGIN_UPDATE_PARAM;

typedef enum
{
	NOT_ALLOWED = 0,
	ALLOWED
}USER_PRIVILEGE_STATUS;

typedef enum
 {
    IS_RUN_VALIDATED_WELD_RECIPE_ALLOWED,
    IS_RUN_UNVALIDATED_WELD_RECIPE_ALLOWED,
    IS_RESET_ALARMS_ALLOWED,
    IS_SET_RECIPE_AS_ACTIVE_ALLOWED,
    IS_RESET_BATCH_COUNTER_AND_ID_ALLOWED,
    IS_RESET_RECIPE_CYCLE_COUNTS_ALLOWED,
    IS_EDIT_RECIPES_ALLOWED,
    IS_CALIBRATION_ALLOWED,
    IS_ACTUATOR_SETUP_ALLOWED,
    IS_DIAGNOSTICS_ALLOWED,
    IS_SAVE_COPY_CREATE_RECIPE_ALLOWED,
    IS_EXTRACT_USB_DATA_FROM_WELDER_ALLOWED,
    IS_SYSTEM_CONFIGURATION_ALLOWED,
    IS_VALIDATE_AND_LOCK_WELD_RECIPES_ALLOWED,
    IS_ADD_MODIFY_USER_ID_SETUP_ALLOWED,
    IS_MODIFY_AUTHORITY_CHECK_ALLOWED,
    IS_DELETE_RECIPE_ALLOWED,
    IS_UPDATE_SOFTWARE_ALLOWED,
    IS_BARCODE_RECIPE_RECALL_ALLOWED,
	IS_USB_AUTHENTICATION_ALLOWED
}USER_PRIVILEGED_FEATURE;

typedef struct addUserStruct
{
	char UserID[USER_NAME_SIZE];
	char Password[PLAIN_TEXT_PASSWORD_SIZE];
	USER_LEVEL AuthLevel;
	USER_STATUS Status;
	USER_ISLOCKED IsUserLocked;
	
	addUserStruct()
	{
		memcpy(UserID, "0", sizeof(UserID));
		memcpy(Password, "0", sizeof(Password));
		AuthLevel = OPERATOR;
		Status = DISABLE;
		IsUserLocked = LOCKED;
	}
	
}__attribute__((packed)) addUserStruct;


typedef struct UserListStruct
{
	char UserID[USER_NAME_SIZE];
	USER_LEVEL Level;
	USER_STATUS Status;
	USER_ISLOCKED IsLocked;
	char CreationDateTime[DATE_SIZE_12_HR_FORMAT];

	UserListStruct()
	{
		memcpy(UserID, "0", sizeof(UserID));
		Level = OPERATOR;
		Status = DISABLE;
		IsLocked = LOCKED;
		memcpy(CreationDateTime, "0", sizeof(CreationDateTime));
	}

}__attribute__((packed))  UserListStruct;


typedef struct updateUserLoginDetailsInDb
{
	USER_LOGIN_UPDATE_PARAM updateParam;
	char UpdatingUserID[USER_NAME_SIZE];
	uint32_t UpdatingValue;
	char updatingValueInStr[DATE_SIZE_12_HR_FORMAT];
	updateUserLoginDetailsInDb()
	{
		updateParam = UNKNOWN_PARAM;
		memcpy(UpdatingUserID, "0", sizeof(UpdatingUserID));
		UpdatingValue = 0;
		memcpy(updatingValueInStr, "0", sizeof(updatingValueInStr));
	}
}__attribute__((packed)) updateUserLoginDetailsInDb;

typedef struct UserInfoStruct
{
	char UserID[USER_NAME_SIZE];
	char HashedPassword[HASHED_PASSWORD_SIZE];
	char salt[SALT_SIZE];
	USER_LEVEL Level;
	USER_STATUS Status;
	USER_ISLOCKED IsLocked;
	char CreationDateTime[DATE_SIZE_12_HR_FORMAT];
	char LastChangedPassword[DATE_SIZE_12_HR_FORMAT];
	char LastLogin[DATE_SIZE_12_HR_FORMAT];
	uint32_t SequentialFailedLoginAttempt;
	char LastSequentialFailedLoginTime[DATE_SIZE_12_HR_FORMAT];
	char TimeLoginFrom[DATE_SIZE_12_HR_FORMAT];
	char TimeLoginTo[DATE_SIZE_12_HR_FORMAT];
	
	UserInfoStruct()
	{
		strncpy(UserID, "0", USER_NAME_SIZE - 1);
		UserID[USER_NAME_SIZE - 1] = '\0'; 

		strncpy(HashedPassword, "0", HASHED_PASSWORD_SIZE - 1);
		HashedPassword[HASHED_PASSWORD_SIZE - 1] = '\0'; 

		strncpy(salt, "0", SALT_SIZE - 1);
		salt[SALT_SIZE - 1] = '\0'; 

		Level = OPERATOR;
		Status = DISABLE;
		IsLocked = LOCKED;
				
		strncpy(CreationDateTime, "0", DATE_SIZE_12_HR_FORMAT - 1);
		CreationDateTime[DATE_SIZE_12_HR_FORMAT - 1] = '\0';

		strncpy(LastChangedPassword, "0", DATE_SIZE_12_HR_FORMAT - 1);
		LastChangedPassword[DATE_SIZE_12_HR_FORMAT - 1] = '\0'; 

		strncpy(LastLogin, "0", DATE_SIZE_12_HR_FORMAT - 1);
		LastLogin[DATE_SIZE_12_HR_FORMAT - 1] = '\0'; 
		
		SequentialFailedLoginAttempt = 0;
				
		strncpy(LastSequentialFailedLoginTime, "0", DATE_SIZE_12_HR_FORMAT - 1);
		LastSequentialFailedLoginTime[DATE_SIZE_12_HR_FORMAT - 1] = '\0';

		strncpy(TimeLoginFrom, "0", DATE_SIZE_12_HR_FORMAT - 1);
		TimeLoginFrom[DATE_SIZE_12_HR_FORMAT - 1] = '\0'; 

		strncpy(TimeLoginTo, "0", DATE_SIZE_12_HR_FORMAT - 1);
		TimeLoginTo[DATE_SIZE_12_HR_FORMAT - 1] = '\0';
	}
			
}__attribute__((packed))  UserInfoStruct;

typedef struct UserPrivilegeStruct
{
	char UserPrivilegeLevel[USER_NAME_SIZE];
	USER_PRIVILEGE_STATUS IsRunValidatedWeldRecipeAllowed;
	USER_PRIVILEGE_STATUS IsRunUnValidatedWeldRecipeAllowed;
	USER_PRIVILEGE_STATUS IsResetAlarmsAllowed;
	USER_PRIVILEGE_STATUS IsSetRecipeAsActiveAllowed;
	USER_PRIVILEGE_STATUS IsResetBatchCounterAndIDAllowed;
	USER_PRIVILEGE_STATUS IsResetRecipeCycleCountsAllowed;
	USER_PRIVILEGE_STATUS IsEditRecipesAllowed;
	USER_PRIVILEGE_STATUS IsCalibrationAllowed;
	USER_PRIVILEGE_STATUS IsActuatorSetupAllowed;
	USER_PRIVILEGE_STATUS IsDignosticsAllowed;
	USER_PRIVILEGE_STATUS IsSaveCopyCreateRecipeAllowed;
	USER_PRIVILEGE_STATUS IsExtractUSBDataFromWelderAllowed;
	USER_PRIVILEGE_STATUS IsSystemConfigurationAllowed;
	USER_PRIVILEGE_STATUS IsValidateAndLockWeldRecipesAllowed;
	USER_PRIVILEGE_STATUS IsAddModifyUserIDSetupAllowed;
	USER_PRIVILEGE_STATUS IsModifyAuthoritiyCheckAllowed;
	USER_PRIVILEGE_STATUS IsDeleteRecipeAllowed;
	USER_PRIVILEGE_STATUS IsUpdateSoftwareAllowed;
	USER_PRIVILEGE_STATUS IsBarcoderecipeRecallAllowed;
	USER_PRIVILEGE_STATUS IsUsbAuthenticationAllowed;
	
	UserPrivilegeStruct()
	{
		strncpy(UserPrivilegeLevel, "0", USER_NAME_SIZE - 1);
		UserPrivilegeLevel[USER_NAME_SIZE - 1] = '\0'; 
		IsRunValidatedWeldRecipeAllowed     = NOT_ALLOWED;
		IsRunUnValidatedWeldRecipeAllowed   = NOT_ALLOWED;
		IsResetAlarmsAllowed                = NOT_ALLOWED;
		IsSetRecipeAsActiveAllowed          = NOT_ALLOWED;
		IsResetBatchCounterAndIDAllowed     = NOT_ALLOWED;
		IsResetRecipeCycleCountsAllowed     = NOT_ALLOWED;
		IsEditRecipesAllowed                = NOT_ALLOWED;
		IsCalibrationAllowed                = NOT_ALLOWED;
		IsActuatorSetupAllowed              = NOT_ALLOWED;
		IsDignosticsAllowed                 = NOT_ALLOWED;
		IsSaveCopyCreateRecipeAllowed       = NOT_ALLOWED;
		IsExtractUSBDataFromWelderAllowed   = NOT_ALLOWED;
		IsSystemConfigurationAllowed        = NOT_ALLOWED;
		IsValidateAndLockWeldRecipesAllowed = NOT_ALLOWED;
		IsAddModifyUserIDSetupAllowed  	    = NOT_ALLOWED;
		IsModifyAuthoritiyCheckAllowed      = NOT_ALLOWED;
		IsDeleteRecipeAllowed               = NOT_ALLOWED;
		IsUpdateSoftwareAllowed             = NOT_ALLOWED;
		IsBarcoderecipeRecallAllowed        = NOT_ALLOWED;
		IsUsbAuthenticationAllowed			= NOT_ALLOWED;
	}
	
}__attribute__((packed))  UserPrivilegeStruct;

extern const std::map <MODIFY_USER_ERROR_CODES , std::string> ModifyUserErrorCodesMap;
extern const std::map <LOGIN_ERROR_CODES , std::string> LoginErrorCodesMap;
extern const std::map <ADD_USER_ERROR_CODES , std::string> AddUserErrorCodesMap;
extern const std::map <USER_LEVEL , std::string> UserLevelStringMap;
extern const std::map <USER_ISLOCKED , std::string> IsUserLockedStringMap;
#endif


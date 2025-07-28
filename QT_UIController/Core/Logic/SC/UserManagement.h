/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the User Management related implementation
 
***************************************************************************/

#ifndef USERMANAGEMENT_H_
#define USERMANAGEMENT_H_

#include <map>
#include "DataInterface.h"
#include "UserManagementStructure.h"
#include "LdapManagementStructure.h"

//max count for user privilege level
#define MAX_USER_PRIVILEGE_LEVEL   4

class UserManagement : public DataInterface
{ 
public:
	
	UserManagement();
	virtual ~UserManagement();
    
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;

    bool IsUserListUpdated();
    void ResetUserListUpdatedFlag();

    bool IsUserListCopyUpdated();
    void ResetUserListCopyUpdatedFlag();

    std::string GetLoggedInUserName();
    std::string GetLoggedInUserAccessLevel();
    USER_LEVEL GetLoggedInUserAccessLevelAsEnum();

    void InitiateLoginRequest(std::string UserName, std::string Password);
    void InitiateAutoLoginRequest(std::string UserName);
    void InitiateLogoutRequest();
    void InitiateVerifyAndChangePasswordRequest(std::string UserName, std::string ExistingPassword, std::string NewPassword, bool isPasswordResetRequest);
    void InitiateChangePasswordRequest(std::string UserName, std::string NewPassword);
    void InitiateAddUserRequest(addUserStruct UserData);
    void InitiateModifyUserRequest(addUserStruct UserData);
    void InitiateDeleteUserRequest(std::string UserName);

    LOGIN_ERROR_CODES GetLoginErrorCodes();
    LOGOUT_ERROR_CODES GetLogoutErrorCodes();
    MODIFY_USER_ERROR_CODES GetChangePasswordResponse();
    MODIFY_USER_ERROR_CODES GetDeleteUserResponse();
    ADD_USER_ERROR_CODES GetAddUserResponse();
    MODIFY_USER_ERROR_CODES GetModifyUserResponse();

    bool GetLoginRepsonseChange();
    void SetLoginRepsonseChange();

    bool GetResetPassRepsonseChange();
    void SetResetPassRepsonseChange();

    bool GetDelUsrReqRepsonseChange();
    void SetDelUsrReqRepsonseChange();

    bool GetAddUsrReqRepsonseChange();
    void SetAddUsrReqRepsonseChange();

    bool GetModifyUsrReqRepsonseChange();
    void SetModifyUsrReqRepsonseChange();

    bool GetUsrPrivilegeRepsonseChange();
    void SetUsrPrivilegeRepsonseChange();

    bool GetPasswordOverride();
    bool getPasswordOverrideDataRead();
    void ResetPasswordOverrideDataRead();

    std::map<std::string,UserListStruct> GetUserList();

    std::map<std::string,UserPrivilegeStruct> GetUserPrivilege();
    
    //Initiates the Ldap Config update
    void InitiateLdapConfigurationUpdateRequest(LdapConfigurationData LdapConfigData);

private:
    size_t m_LogID;

    //Holds the User List data cached on HMI side.
    std::map<std::string,UserListStruct> m_UserDetails;

    //Holds the User Privilege data cached on HMI side.
    std::map<std::string,UserPrivilegeStruct> m_UserPrivilegeDetails;

    //This flag is set to true whenever the user list data gets updated in cached data m_UserDetails
    bool m_IsUserListUpdated;
    //user list screen used to set m_IsUserListUpdated flag whenever the user list data gets updated and
    //Global user setting screen used to set m_IsUserListUpdatedForGlobalUserSettingScreen flag whenever the user list data gets updated
    bool m_IsUserListUpdatedForGlobalUserSettingScreen;
    //This flag is set to true whenever the user privilege data gets cached in m_UserPrivilegeDetails data.
    bool m_UserPrivilegeRecived;

    //Login request is sent to ASC when this flag is true
    bool m_SendLoginRequest;
    //AutoLogin request is sent to ASC when this flag is true
    bool m_SendAutoLoginRequest;
    //Logout request is sent to ASC when this flag is true
    bool m_SendLogoutRequest;
    //verify and change password request is sent to ASC when this flag is true
    bool m_SendVerifyAndChangePasswordRequest;
    //change password request is sent to ASC when this flag is true
    bool m_SendChangePasswordRequest;
    //Read User List request is sent to ASC when this flag is true
    bool m_SendUserListReadRequest;
    //Add User request is sent to ASC when this flag is true
    bool m_SendAddUserRequest;
    //Modify User request is sent to ASC when this flag is true
    bool m_SendModifyUserRequest;
    //Delete User request is sent to ASC when this flag is true
    bool m_SendDeleteUserRequest;
    //From first time login screen reset password request is sent to ASC when this flag is true
    bool m_SendResetPasswordRequest;
    //User Privilege request is sent to ASC when this flag is true
    bool m_SendUserPrivilegeReadRequest;

    //Flag to update HMI upon Login error code received from SC.
    bool m_LoginResponseRecived;
    //Flag to update HMI upon Reset error code received from SC.
    bool m_ResetPassRecived;
    //Flag to update HMI upon delete user error code received from SC.
    bool m_DeleteUserRecieved;
    //Flag to update HMI upon Add user error code received from SC.
    bool m_AddUserRespRecieved;
    //Flag to update HMI upon modify user error code received from SC.
    bool m_ModifyUserRespRecieved;

    bool m_IsPasswordOverride;
    bool m_IsPasswordOverrideDataRead;

    //Holds the UserName to be sent to ASC during login request. This username is also cached on HMI side and is used as logged in user name.
    char m_LoginUserName[USER_NAME_SIZE] = {0};
    //Holds the plaintext password to be sent to ASC during login request
    char m_LoginPlainTextPassword[PLAIN_TEXT_PASSWORD_SIZE] = {0};
    //Holds the UserName to be sent to ASC during change password/verify and change request.
    char m_UserNameForPasswordChange[USER_NAME_SIZE] = {0};
    //Holds the new plaintext password to be sent to ASC during change password/verify and change password request.
    char m_NewPlainTextPasswordForPasswordChange[PLAIN_TEXT_PASSWORD_SIZE] = {0};
    //Holds the existing plaintext password to be sent to ASC during verify and change password request.
    char m_ExistingPlainTextPasswordForPasswordChange[PLAIN_TEXT_PASSWORD_SIZE] = {0};
    //Holds the Add/Modify User data to be sent to ASC during add user or modify user request
    addUserStruct m_AddOrModifyUserData;
    //Holds the user name to be sent to ASC during delete user request
    char m_DeleteUserName[USER_NAME_SIZE] = {0};

    //Holds the login response code coming from ASC
    LOGIN_ERROR_CODES m_LoginResponse;
    //Holds the login response code coming from ASC
    LOGOUT_ERROR_CODES m_LogoutResponse;
    //Holds the change password/verify and change password response code coming from ASC
    MODIFY_USER_ERROR_CODES m_ChangePasswordResponse;
    //Holds the add user response code coming from ASC
    ADD_USER_ERROR_CODES m_AddUserResponse;
    //Holds the modify user response code coming from ASC
    MODIFY_USER_ERROR_CODES m_ModifyUserResponse;
    //Holds the delete user response code coming from ASC
    MODIFY_USER_ERROR_CODES m_deleteUserResponse;


    void sendLoginRequest(MEMORY_BLOCK * const destination);
    void sendAutoLoginRequest(MEMORY_BLOCK * const destination);
    void sendLogoutRequest(MEMORY_BLOCK * const destination);
    void sendVerifyAndChangePasswordRequest(MEMORY_BLOCK * const destination);
    void sendChangePasswordRequest(MEMORY_BLOCK * const destination);
    void sendAddUserRequest(MEMORY_BLOCK * const destination);
    void sendModifyUserRequest(MEMORY_BLOCK * const destination);
    void sendDeleteUserRequest(MEMORY_BLOCK * const destination);
    void sendUserListReadRequest(MEMORY_BLOCK * const destination);
    void sendUserPrivilegeReadRequestToASC(MEMORY_BLOCK * const destination);

    void processLoginResponse(const MEMORY_BLOCK *const source);
    void processLogoutResponse(const MEMORY_BLOCK *const source);
    void processChangePasswordResponse(const MEMORY_BLOCK *const source);
    void processUserListResponse(const MEMORY_BLOCK *const source);
    void processAddUserResponse(const MEMORY_BLOCK *const source);
    void processModifyUserResponse(const MEMORY_BLOCK *const source);
    void processDeleteUserResponse(const MEMORY_BLOCK *const source);
    void processUserPrivilegeResponse(const MEMORY_BLOCK *const source);
    void processPasswordOverrideResponse(const MEMORY_BLOCK *const source);
    void processSyncReminderListonDateTimeFormatChg();

    void printUserList();
    void printUserPrivilegeData();

    //Ldap Read Config request is sent to ASC when this flag is true
    bool m_SendLdapConfigReadRequest;
    //Ldap Write Config is sent to ASC when this flag is true
    bool m_SendLdapConfigUpdateRequest;
    //Sets true when new ldap config is read from ASC board
    bool m_isLdapConfigDataReceived;
    //Hold the new ldap config data to be updated
    LdapConfigurationData m_LdapConfigData;
    //Sends Ldap Read request to ASC
    void SendLdapConfigReadRequestToASC(MEMORY_BLOCK * const destination);
    //Sends Ldap Write request to ASC
    void SendLdapConfigUpdateRequestToASC(MEMORY_BLOCK * const destination);
    //Process the incoming read Ldap Config from ASC
    void ProcessLdapConfigReadResponse(const MEMORY_BLOCK *const source);
};

#endif /* USERMANAGEMENT_H_ */

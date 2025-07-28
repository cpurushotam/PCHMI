/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the User Management related implementation
 
***************************************************************************/
#include <algorithm>
#include <cctype>
#include "UserManagement.h"
#include "DataLogger.h"


/**************************************************************************//**
*
* \brief   - constructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/

UserManagement::UserManagement()
{
	//enroll to use logger functionality
    m_LogID = Logger::enroll(this);

    m_IsUserListUpdated = false;
    m_IsUserListUpdatedForGlobalUserSettingScreen = false;
    m_UserPrivilegeRecived = false;
    m_SendUserListReadRequest = true;
    m_SendUserPrivilegeReadRequest = true;
    m_SendLoginRequest = false;
    m_SendAutoLoginRequest = false;
    m_SendLogoutRequest = false;
    m_SendVerifyAndChangePasswordRequest = false;
    m_SendChangePasswordRequest = false;
    m_SendAddUserRequest = false;
    m_SendModifyUserRequest = false;
    m_SendDeleteUserRequest = false;
    m_SendResetPasswordRequest = false;
    m_IsPasswordOverride = false;
    m_IsPasswordOverrideDataRead = false;

    m_LoginResponseRecived =false;
    m_ResetPassRecived = false;

    m_LoginResponse = LOGIN_ERROR_UNKNOWN;
    m_LogoutResponse = LOGOUT_ERROR_UNKNOWN;
    m_ChangePasswordResponse = MODIFY_USER_ERROR_UNKNOWN;
    m_AddUserResponse = ADD_USER_ERROR_UNKNOWN;
    m_ModifyUserResponse = MODIFY_USER_ERROR_UNKNOWN;
    m_deleteUserResponse = MODIFY_USER_ERROR_UNKNOWN;

    m_SendLdapConfigReadRequest = true;
	m_SendLdapConfigUpdateRequest = false;
	m_isLdapConfigDataReceived = false;

    strncpy(m_LoginUserName, "N/A", sizeof(m_LoginUserName));
}

/**************************************************************************//**
*
* \brief   - destructor
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
UserManagement::~UserManagement()
{

}

/**************************************************************************//**
*
* \brief   - QML should call this method to know if the cached User List data
*            is updated or not
* \param   - None
*
* \return  - true if user list is updated else false
*
******************************************************************************/
bool UserManagement::IsUserListUpdated()
{
    return m_IsUserListUpdated;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to reset the m_IsUserListUpdated
*            flag to false once it has read the updated user list data from cache
* \param   - None
*
* \return  - none
*
******************************************************************************/
void UserManagement::ResetUserListUpdatedFlag()
{
    m_IsUserListUpdated = false;
}

/**************************************************************************//**
*
* \brief   - Global User Setting Screen call this method to know if the cached User List data
*            is updated or not
* \param   - None
*
* \return  - true if user list is updated else false
*
******************************************************************************/
bool UserManagement::IsUserListCopyUpdated()
{
    return m_IsUserListUpdatedForGlobalUserSettingScreen;
}

/**************************************************************************//**
*
* \brief   - Global User Setting Screen call this method to reset the m_IsUserListUpdated
*            flag to false once it has read the updated user list data from cache
* \param   - None
*
* \return  - none
*
******************************************************************************/
void UserManagement::ResetUserListCopyUpdatedFlag()
{
    m_IsUserListUpdatedForGlobalUserSettingScreen = false;
}


/**************************************************************************//**
*
* \brief   - QML should call this method to know the logged in username
* \param   - None
*
* \return  - logged in user name
*
******************************************************************************/
std::string UserManagement::GetLoggedInUserName()
{
    return m_LoginUserName;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to know the logged in user access level
* \param   - None
*
* \return  - logged in user access level
*
******************************************************************************/
std::string UserManagement::GetLoggedInUserAccessLevel()
{
    std::string strAccessLevel = "";
    USER_LEVEL Level = OPERATOR;

    auto it = m_UserDetails.find(m_LoginUserName);
    if(it != m_UserDetails.end())
    {
       Level = it->second.Level;
       switch(Level)
       {
       case UNKNOWN_USER_LEVEL:
       {
           strAccessLevel = "Unknown";
       }
       break;

       case OPERATOR:
       {
           strAccessLevel = "Operator";
       }
       break;

       case TECHNICIAN:
       {
           strAccessLevel = "Technician";
       }
       break;

       case SUPERVISOR:
       {
           strAccessLevel = "Supervisor";
       }
       break;

       case EXECUTIVE:
       {
           strAccessLevel = "Executive";
       }
       break;

       default:
       {
           strAccessLevel = "Unknown";
       }
       break;
       }
    }
    return strAccessLevel;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to know the logged in user access level enum value
* \param   - None
*
* \return  - logged in user access level enum value
*
******************************************************************************/
USER_LEVEL UserManagement::GetLoggedInUserAccessLevelAsEnum()
{
    USER_LEVEL Level = UNKNOWN_USER_LEVEL;

    auto it = m_UserDetails.find(m_LoginUserName);
    if(it != m_UserDetails.end())
    {
       Level = it->second.Level;

    }
    return Level;
}

/**************************************************************************//**
*
* \brief   - QML should call this method when Auto Login is enabled
*
* \param   - UserName - UserName entered by user
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateAutoLoginRequest(std::string UserName)
{
    std::transform(UserName.begin(), UserName.end(), UserName.begin(), ::toupper);
    strncpy(m_LoginUserName, UserName.c_str(), sizeof(m_LoginUserName));
    m_SendAutoLoginRequest = true;
}
/**************************************************************************//**
*
* \brief   - QML should call this method on login button press to initiate
*            a login request to ASC
* \param   - UserName - UserName entered by user
*           Password - Password entered by user
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateLoginRequest(std::string UserName, std::string Password)
{
    std::transform(UserName.begin(), UserName.end(), UserName.begin(), ::toupper);
    strncpy(m_LoginUserName, UserName.c_str(), sizeof(m_LoginUserName));
    strncpy(m_LoginPlainTextPassword, Password.c_str(), sizeof(m_LoginPlainTextPassword));
    m_SendLoginRequest = true;
}
/**************************************************************************//**
*
* \brief   - QML should call this method on logout button press to initiate
*            a logout request to ASC
* \param   - None
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateLogoutRequest()
{
    m_SendLogoutRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate verify and change password
*            request to ASC
* \param   - UserName - UserName whose password needs to be changed.
*           ExistingPassword - Existing Password of the user.
*           NewPassword - New Password for the user.
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateVerifyAndChangePasswordRequest(std::string UserName, std::string ExistingPassword, std::string NewPassword , bool isPasswordResetRequest)
{
    strncpy(m_UserNameForPasswordChange, UserName.c_str(), sizeof(m_UserNameForPasswordChange));
    strncpy(m_ExistingPlainTextPasswordForPasswordChange, ExistingPassword.c_str(), sizeof(m_ExistingPlainTextPasswordForPasswordChange));
    strncpy(m_NewPlainTextPasswordForPasswordChange, NewPassword.c_str(), sizeof(m_NewPlainTextPasswordForPasswordChange));
    m_SendVerifyAndChangePasswordRequest = true;
    if(isPasswordResetRequest == true)
    {
       m_SendResetPasswordRequest = true;
    }
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate change password request
*            to ASC
* \param   - UserName - UserName whose password needs to be changed.
*           NewPassword - New Password for the user.
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateChangePasswordRequest(std::string UserName, std::string NewPassword)
{
    strncpy(m_UserNameForPasswordChange, UserName.c_str(), sizeof(m_UserNameForPasswordChange));
    strncpy(m_NewPlainTextPasswordForPasswordChange, NewPassword.c_str(), sizeof(m_NewPlainTextPasswordForPasswordChange));
    m_SendChangePasswordRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate add user request to ASC
*
* \param   - UserData - User Data containig username, password, access level,
*            status, locked status.
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateAddUserRequest(addUserStruct UserData)
{
    m_AddOrModifyUserData = UserData;
    m_SendAddUserRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate modify user request to ASC
*
* \param   - UserData - User Data containig username, access level,
*            status, locked status.
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateModifyUserRequest(addUserStruct UserData)
{
    m_AddOrModifyUserData = UserData;
    m_SendModifyUserRequest = true;
}

/**************************************************************************//**
*
* \brief   - QML should call this method to initiate delete user request to ASC
*
* \param   - UserName - UserName to be deleted.
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateDeleteUserRequest(std::string UserName)
{
    strncpy(m_DeleteUserName, UserName.c_str(), sizeof(m_DeleteUserName));
    m_SendDeleteUserRequest = true;
}

/**************************************************************************//**
*
* \brief   - send the request to ASC server for User Management
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - 0 on success, -1 on failure
*
******************************************************************************/
int UserManagement::GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;

	if((destination != nullptr) && (destination->id == MB_ID_USER_MANAGEMNT_DATA))
	{
		switch(destination->sub_id)
        {
            case MB_USER_LIST_REQUEST:
            {
               retVal = 0;
               sendUserListReadRequest(destination);
               break;
            }

			case MB_LOGIN_REQUEST:
			{
				retVal = 0;
                sendLoginRequest(destination);
				break;
			}
            case MB_AUTO_LOGIN_REQUEST:
            {
                retVal = 0;
                sendAutoLoginRequest(destination);
                break;
            }

            case MB_LOGOUT_REQUEST:
            {
                retVal = 0;
                sendLogoutRequest(destination);
                break;
            }

            case MB_VERIFY_AND_CHANGE_PASSWORD_REQUEST:
            {
                retVal = 0;
                sendVerifyAndChangePasswordRequest(destination);
                break;
            }

            case MB_CHANGE_PASSWORD_REQUEST:
            {
                retVal = 0;
                sendChangePasswordRequest(destination);
                break;
            }

            case MB_ADD_USER_REQUEST:
            {
                retVal = 0;
                sendAddUserRequest(destination);
                break;
            }

            case MB_MODIFY_USER_REQUEST:
            {
                retVal = 0;
                sendModifyUserRequest(destination);
                break;
            }

            case MB_DELETE_USER_REQUEST:
            {
                retVal = 0;
                sendDeleteUserRequest(destination);
                break;
            }

            case MB_USER_PRIVILEGE_REQUEST:
            {
            	retVal = 0;
            	sendUserPrivilegeReadRequestToASC(destination);
            	break;
            }

            case MB_LDAP_CONFIG_READ_REQUEST:
            {
            	retVal = 0;
            	SendLdapConfigReadRequestToASC(destination);
            	break;
            }

            case MB_LDAP_CONFIG_UPDATE_REQUEST:
            {
            	retVal = 0;
            	SendLdapConfigUpdateRequestToASC(destination);
            	break;
            }

			default:
			{
				destination->size = 0;
				// clear valid bit
				destination->config = 0;
				char  msg[buff_size_config] = {0};
				snprintf(msg,buff_size_config,"UserManagement GetData default case");
                Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				break;
			}
		}
	}
	else
	{
		destination->size = 0;
		// clear valid bit
		destination->config = 0;
		char  msg[buff_size_config] = {0};
		snprintf(msg,buff_size_config,"UserManagement GetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	return retVal;
}

/**************************************************************************//**
*
* \brief   - process the data coming to HMI from ASC for User Management
*
* \param   - source - Memory block containing data coming to HMI
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int UserManagement::SetData(const MEMORY_BLOCK *const source)
{
    int retVal = -1;

    if( (source != nullptr) && (source->id == MB_ID_USER_MANAGEMNT_DATA) )
    {
        if( (source->config & VALID_BIT) == (VALID_BIT) )
        {
                switch(source->sub_id)
                {
                    case MB_PASSWORD_OVERRIDE_REQUEST:
                    {
                        retVal = 0;
                        processPasswordOverrideResponse(source);
                        break;
                    }
                    case MB_USER_LIST_REQUEST:
                    {
                        retVal = 0;
                        processUserListResponse(source);
                        break;
                    }
                    case MB_LOGIN_REQUEST:
                    {
                        retVal = 0;
                        processLoginResponse(source);
                        break;
                    }

                    case MB_LOGOUT_REQUEST:
                    {
                        retVal = 0;
                        processLogoutResponse(source);
                        break;
                    }

                    case MB_VERIFY_AND_CHANGE_PASSWORD_REQUEST:
                    case MB_CHANGE_PASSWORD_REQUEST:
                    {
                        retVal = 0;
                        processChangePasswordResponse(source);
                        break;
                    }

                    case MB_ADD_USER_REQUEST:
                    {
                        retVal = 0;
                        processAddUserResponse(source);
                        break;
                    }

                    case MB_MODIFY_USER_REQUEST:
                    {
                        retVal = 0;
                        processModifyUserResponse(source);
                        break;
                    }

                    case MB_DELETE_USER_REQUEST:
                    {
                        retVal = 0;
                        processDeleteUserResponse(source);
                        break;
                    }

                    case MB_USER_PRIVILEGE_REQUEST:
                    {
                    	retVal = 0;
                    	processUserPrivilegeResponse(source);
                    	break;
                    }
                    case MB_SYNC_USER_LIST:
                    {
                        retVal = 0;
                        processSyncReminderListonDateTimeFormatChg();
                        break;
                    }

                    case MB_LDAP_CONFIG_READ_REQUEST:
                    {
                    	retVal = 0;
                    	ProcessLdapConfigReadResponse(source);
                    	break;
                    }

                    default:
                    {
                        char  msg[buff_size_config] = {0};
                        snprintf(msg,buff_size_config,"UserManagement SetData default case");
                        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
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
        snprintf(msg,buff_size_config,"UserManagement SetData invalid MB ID");
        Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    }
    return retVal;
}

/**************************************************************************//**
*
* \brief   - Send the read user list request to ASC
*
* \param   - destination - memory block to hold the request data.
*
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendUserListReadRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendUserListReadRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendUserListReadRequest = false;
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
* \brief   - Send the login request to ASC
*
* \param   - destination - memory block to hold the login request data
*            containing username and password in plaintext.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendLoginRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the login request data containing username and password.
    if( destination->size >= (sizeof(m_LoginUserName) + sizeof(m_LoginPlainTextPassword) ) )
    {
        if(m_SendLoginRequest == true)
		{
            strncpy(reinterpret_cast<char *>(destination->data), m_LoginUserName, sizeof(m_LoginUserName));
            strncpy(reinterpret_cast<char *>(destination->data + sizeof(m_LoginUserName)), m_LoginPlainTextPassword, sizeof(m_LoginPlainTextPassword));

            destination->size = sizeof(m_LoginUserName) + sizeof(m_LoginPlainTextPassword);

			destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendLoginRequest = false;
            //Reset the password holding variable once the request is sent to ASC.
            memset(m_LoginPlainTextPassword, 0, sizeof(m_LoginPlainTextPassword));
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
* \brief   - Send the Auto login request to ASC
*
* \param   - destination - memory block to hold the login request data
*            containing username.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendAutoLoginRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the login request data containing username.
    if( destination->size >= (sizeof(m_LoginUserName)))
    {
        if(m_SendAutoLoginRequest  == true)
        {
            strncpy(reinterpret_cast<char *>(destination->data), m_LoginUserName, sizeof(m_LoginUserName));

            destination->size = sizeof(m_LoginUserName);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendAutoLoginRequest  = false;
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
* \brief   - Send the logout request to ASC
*
* \param   - destination - memory block to hold the logout request data.
*
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendLogoutRequest(MEMORY_BLOCK * const destination)
{
    if(destination->size >= sizeof(bool))
    {
        if(m_SendLogoutRequest == true)
        {
            destination->data = 0;
            destination->size = sizeof(bool);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendLogoutRequest = false;

            strncpy(m_LoginUserName, "N/A", sizeof(m_LoginUserName));
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
* \brief   - Send the verify and change password request to ASC
*
* \param   - destination - memory block to hold the verify and change password
*            request data containing username, existing password and new password
*            in plaintext.
* \return  - none
*
******************************************************************************/
void UserManagement::sendVerifyAndChangePasswordRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the request data.
    if( destination->size >= (sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange) + sizeof(m_ExistingPlainTextPasswordForPasswordChange) +  sizeof(m_SendResetPasswordRequest)) )
    {
        if(m_SendVerifyAndChangePasswordRequest == true)
        {
            strncpy(reinterpret_cast<char *>(destination->data), m_UserNameForPasswordChange, sizeof(m_UserNameForPasswordChange));
            strncpy(reinterpret_cast<char *>(destination->data + sizeof(m_UserNameForPasswordChange)), m_NewPlainTextPasswordForPasswordChange, sizeof(m_NewPlainTextPasswordForPasswordChange));
            strncpy(reinterpret_cast<char *>(destination->data + sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange)), m_ExistingPlainTextPasswordForPasswordChange, sizeof(m_ExistingPlainTextPasswordForPasswordChange));

            memcpy(reinterpret_cast<bool *>(destination->data + sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange) + sizeof(m_ExistingPlainTextPasswordForPasswordChange)), &m_SendResetPasswordRequest, sizeof(m_SendResetPasswordRequest));
            
            destination->size = sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange) + sizeof(m_ExistingPlainTextPasswordForPasswordChange) + sizeof(m_SendResetPasswordRequest);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendVerifyAndChangePasswordRequest = false;
            
            //Reset the flag once the request is sent.
            m_SendResetPasswordRequest = false;
            
            //Reset the password holding variable once the request is sent to ASC.
            memset(m_NewPlainTextPasswordForPasswordChange, 0, sizeof(m_NewPlainTextPasswordForPasswordChange));
            memset(m_ExistingPlainTextPasswordForPasswordChange, 0, sizeof(m_ExistingPlainTextPasswordForPasswordChange));
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
* \brief   - Send the change password request to ASC
*
* \param   - destination - memory block to hold the change password request
*            data containing username and new password in plaintext.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendChangePasswordRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the request data.
    if( destination->size >= (sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange) ) )
    {
        if(m_SendChangePasswordRequest == true)
        {
            strncpy(reinterpret_cast<char *>(destination->data), m_UserNameForPasswordChange, sizeof(m_UserNameForPasswordChange));
            strncpy(reinterpret_cast<char *>(destination->data + sizeof(m_UserNameForPasswordChange)), m_NewPlainTextPasswordForPasswordChange, sizeof(m_NewPlainTextPasswordForPasswordChange));

            destination->size = sizeof(m_UserNameForPasswordChange) + sizeof(m_NewPlainTextPasswordForPasswordChange);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendChangePasswordRequest = false;
            //Reset the password holding variable once the request is sent to ASC.
            memset(m_NewPlainTextPasswordForPasswordChange, 0, sizeof(m_NewPlainTextPasswordForPasswordChange));
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
* \brief   - Send the add user request to ASC
*
* \param   - destination - memory block to hold the add user request data
*            containing username, password, access level, Enabled and Locked
*            status.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendAddUserRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the add user request data.
    if( destination->size >= sizeof(addUserStruct))
    {
        if(m_SendAddUserRequest == true)
        {
            addUserStruct *Data = reinterpret_cast<addUserStruct *>(destination->data);           
            strncpy(Data->UserID, m_AddOrModifyUserData.UserID, sizeof(m_AddOrModifyUserData.UserID));
            strncpy(Data->Password, m_AddOrModifyUserData.Password, sizeof(m_AddOrModifyUserData.Password));
            Data->AuthLevel = m_AddOrModifyUserData.AuthLevel;
            Data->Status = m_AddOrModifyUserData.Status;
            Data->IsUserLocked = m_AddOrModifyUserData.IsUserLocked;


            destination->size = sizeof(addUserStruct);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendAddUserRequest = false;
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
* \brief   - Send the modify user request to ASC
*
* \param   - destination - memory block to hold the modify user request data
*            containing username, access level, Enabled and Locked status.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendModifyUserRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the modify user request data.
    if( destination->size >= sizeof(addUserStruct))
    {
        if(m_SendModifyUserRequest == true)
        {
            addUserStruct *Data = reinterpret_cast<addUserStruct *>(destination->data);

            strncpy(Data->UserID, m_AddOrModifyUserData.UserID, sizeof(m_AddOrModifyUserData.UserID));
            strncpy(Data->Password, m_AddOrModifyUserData.Password, sizeof(m_AddOrModifyUserData.Password));
            Data->AuthLevel = m_AddOrModifyUserData.AuthLevel;
            Data->Status = m_AddOrModifyUserData.Status;
            Data->IsUserLocked = m_AddOrModifyUserData.IsUserLocked;

            destination->size = sizeof(addUserStruct);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendModifyUserRequest = false;
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
* \brief   - Send the delete user request to ASC
*
* \param   - destination - memory block to hold the delete user request data
*            containing username.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendDeleteUserRequest(MEMORY_BLOCK * const destination)
{
    //Check that sufficient buffer is available in memory block to hold the delete user request data containing username to be deleted.
    if( destination->size >= sizeof(m_DeleteUserName))
    {
        if(m_SendDeleteUserRequest == true)
        {
            strncpy(reinterpret_cast<char *>(destination->data), m_DeleteUserName, sizeof(m_DeleteUserName));

            destination->size = sizeof(m_DeleteUserName);

            destination->config = VALID_BIT;

            //Reset the flag once the request is sent.
            m_SendDeleteUserRequest = false;
            //Reset the variable once the request is sent to ASC.
            memset(m_DeleteUserName, 0, sizeof(m_DeleteUserName));
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
* \brief   - Send read user privilege request to ASC
*
* \param   - destination - memory block to hold the request data.
*
* \return  - none
*
******************************************************************************/
void UserManagement::sendUserPrivilegeReadRequestToASC(MEMORY_BLOCK * const destination)
{
   if(destination->size >= sizeof(bool))
	{
		if(m_SendUserPrivilegeReadRequest == true)
		{
			destination->size = sizeof(bool);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_SendUserPrivilegeReadRequest = false;
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
* \brief   - Process the user list data coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processUserListResponse(const MEMORY_BLOCK *const source)
{
    int *NumberOfUsers = reinterpret_cast<int *>(source->data);
    UserListStruct *Data = reinterpret_cast<UserListStruct *>(source->data + sizeof(int));
    m_UserDetails.clear();

    for(int UserNumber = 0; UserNumber < *NumberOfUsers; UserNumber++)
    {
        UserListStruct UserInfo;
        strncpy(UserInfo.UserID, Data->UserID, sizeof(UserInfo.UserID));
        UserInfo.Level = Data->Level;
        UserInfo.Status = Data->Status;
        UserInfo.IsLocked = Data->IsLocked;
        strncpy(UserInfo.CreationDateTime, Data->CreationDateTime, sizeof(UserInfo.CreationDateTime));
        m_UserDetails.insert(std::make_pair(UserInfo.UserID, UserInfo));
        Data++;
    }
    m_IsUserListUpdated = true;
    m_IsUserListUpdatedForGlobalUserSettingScreen = true;
}

/**************************************************************************//**
*
* \brief   - Process the login response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processLoginResponse(const MEMORY_BLOCK *const source)
{
    m_LoginResponse = *reinterpret_cast<LOGIN_ERROR_CODES *>(source->data);
    m_LoginResponseRecived =true ;
}

/**************************************************************************//**
*
* \brief   - Process the logout response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processLogoutResponse(const MEMORY_BLOCK *const source)
{
    m_LogoutResponse = *reinterpret_cast<LOGOUT_ERROR_CODES *>(source->data);
}

/**************************************************************************//**
*
* \brief   - Process the change password response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processChangePasswordResponse(const MEMORY_BLOCK *const source)
{
    m_ChangePasswordResponse = *reinterpret_cast<MODIFY_USER_ERROR_CODES *>(source->data);
    m_ResetPassRecived = true;
}

/**************************************************************************//**
*
* \brief   - Process the add user response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processAddUserResponse(const MEMORY_BLOCK *const source)
{
    m_AddUserResponse = *reinterpret_cast<ADD_USER_ERROR_CODES *>(source->data);
    m_AddUserRespRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the modify user response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processModifyUserResponse(const MEMORY_BLOCK *const source)
{
    m_ModifyUserResponse = *reinterpret_cast<MODIFY_USER_ERROR_CODES *>(source->data);
    m_ModifyUserRespRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the delete user response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processDeleteUserResponse(const MEMORY_BLOCK *const source)
{
    m_deleteUserResponse = *reinterpret_cast<MODIFY_USER_ERROR_CODES *>(source->data);
    m_DeleteUserRecieved = true;
}

/**************************************************************************//**
*
* \brief   - Process the user privilege response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
*****************************************************************************/
void UserManagement::processUserPrivilegeResponse(const MEMORY_BLOCK *const source)
{
   UserPrivilegeStruct *UserPrivilegeData = reinterpret_cast<UserPrivilegeStruct *>(source->data);
   m_UserPrivilegeDetails.clear();

   for(int UserLevel = 0; UserLevel < MAX_USER_PRIVILEGE_LEVEL; UserLevel++)
   {
	   UserPrivilegeStruct UserPrivilegeInfo;
	   //fill the map with recipe card data coming from ASC
	   strncpy(UserPrivilegeInfo.UserPrivilegeLevel, UserPrivilegeData->UserPrivilegeLevel, sizeof(UserPrivilegeInfo.UserPrivilegeLevel));
	   UserPrivilegeInfo.IsRunValidatedWeldRecipeAllowed = UserPrivilegeData->IsRunValidatedWeldRecipeAllowed;
	   UserPrivilegeInfo.IsRunUnValidatedWeldRecipeAllowed = UserPrivilegeData->IsRunUnValidatedWeldRecipeAllowed;
	   UserPrivilegeInfo.IsResetAlarmsAllowed = UserPrivilegeData->IsResetAlarmsAllowed;
	   UserPrivilegeInfo.IsSetRecipeAsActiveAllowed = UserPrivilegeData->IsSetRecipeAsActiveAllowed;
	   UserPrivilegeInfo.IsResetBatchCounterAndIDAllowed = UserPrivilegeData->IsResetBatchCounterAndIDAllowed;
	   UserPrivilegeInfo.IsResetRecipeCycleCountsAllowed = UserPrivilegeData->IsResetRecipeCycleCountsAllowed;
	   UserPrivilegeInfo.IsEditRecipesAllowed = UserPrivilegeData->IsEditRecipesAllowed;
	   UserPrivilegeInfo.IsCalibrationAllowed = UserPrivilegeData->IsCalibrationAllowed;
	   UserPrivilegeInfo.IsActuatorSetupAllowed = UserPrivilegeData->IsActuatorSetupAllowed;
	   UserPrivilegeInfo.IsDignosticsAllowed = UserPrivilegeData->IsDignosticsAllowed;
	   UserPrivilegeInfo.IsSaveCopyCreateRecipeAllowed = UserPrivilegeData->IsSaveCopyCreateRecipeAllowed;
	   UserPrivilegeInfo.IsExtractUSBDataFromWelderAllowed = UserPrivilegeData->IsExtractUSBDataFromWelderAllowed;
	   UserPrivilegeInfo.IsSystemConfigurationAllowed = UserPrivilegeData->IsSystemConfigurationAllowed;
	   UserPrivilegeInfo.IsValidateAndLockWeldRecipesAllowed = UserPrivilegeData->IsValidateAndLockWeldRecipesAllowed;
	   UserPrivilegeInfo.IsAddModifyUserIDSetupAllowed = UserPrivilegeData->IsAddModifyUserIDSetupAllowed;
	   UserPrivilegeInfo.IsModifyAuthoritiyCheckAllowed = UserPrivilegeData->IsModifyAuthoritiyCheckAllowed;
	   UserPrivilegeInfo.IsDeleteRecipeAllowed = UserPrivilegeData->IsDeleteRecipeAllowed;
	   UserPrivilegeInfo.IsUpdateSoftwareAllowed = UserPrivilegeData->IsUpdateSoftwareAllowed;
	   UserPrivilegeInfo.IsBarcoderecipeRecallAllowed = UserPrivilegeData->IsBarcoderecipeRecallAllowed;
	   m_UserPrivilegeDetails.insert(std::make_pair(UserPrivilegeInfo.UserPrivilegeLevel, UserPrivilegeInfo));
	   ++UserPrivilegeData;
   }
   m_UserPrivilegeRecived = true;
}

/**************************************************************************//**
*
* \brief   - process the UserManagement list read request on Datetime format change
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
void UserManagement::processSyncReminderListonDateTimeFormatChg()
{
   m_UserDetails.clear();
   m_SendUserListReadRequest = true;
}
/**************************************************************************//**
*
* \brief   - Process the Password Override response code coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
* \return  - none
*
******************************************************************************/
void UserManagement::processPasswordOverrideResponse(const MEMORY_BLOCK *const source)
{
    m_IsPasswordOverride = *reinterpret_cast<bool*>(source->data);
    m_IsPasswordOverrideDataRead = true;
}
/**************************************************************************//**
*
* \brief   - Function returns the login error code to HMI.
*
* \param   - None
*
* \return  - m_LoginResponse.
*
******************************************************************************/
LOGIN_ERROR_CODES UserManagement::GetLoginErrorCodes()
{
    return m_LoginResponse;
}

/**************************************************************************//**
*
* \brief   - Function returns the logout error code to HMI.
*
* \param   - None
*
* \return  - m_LogoutResponse.
*
******************************************************************************/
LOGOUT_ERROR_CODES UserManagement::GetLogoutErrorCodes()
{
    return m_LogoutResponse;
}

/**************************************************************************//**
*
* \brief   - Function returns the modify user error code to HMI.
*
* \param   - None
*
* \return  - m_ChangePasswordResponse.
*
******************************************************************************/
MODIFY_USER_ERROR_CODES UserManagement::GetChangePasswordResponse()
{
    return m_ChangePasswordResponse;
}

/**************************************************************************//**
*
* \brief   - Function returns the modify user error code to HMI.
*
* \param   - None
*
* \return  - m_ModifyUserResponse.
*
******************************************************************************/
MODIFY_USER_ERROR_CODES UserManagement::GetModifyUserResponse()
{
    return m_ModifyUserResponse;
}
/**************************************************************************//**
*
* \brief   - Function returns the delete user error code to HMI.
*
* \param   - None
*
* \return  - m_deleteUserResponse.
*
******************************************************************************/
MODIFY_USER_ERROR_CODES UserManagement::GetDeleteUserResponse()
{
    return m_deleteUserResponse;
}
/**************************************************************************//**
*
* \brief   - Function returns the Add user error code to HMI.
*
* \param   - None
*
* \return  - m_AddUserResponse.
*
******************************************************************************/
ADD_USER_ERROR_CODES UserManagement::GetAddUserResponse()
{
    return m_AddUserResponse;
}
/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving error code from ASC.
*
* \param   - none
*
* \return  - m_LoginResponseRecived.
*
******************************************************************************/
bool UserManagement::GetLoginRepsonseChange()
{
    return m_LoginResponseRecived;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing the error code on HMI.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetLoginRepsonseChange()
{
    m_LoginResponseRecived = false;
}

/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving error code from ASC.
*
* \param   - none
*
* \return  - m_ResetPassRecived.
*
******************************************************************************/

bool UserManagement::GetResetPassRepsonseChange()
{    
    return m_ResetPassRecived;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing the error code on HMI.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetResetPassRepsonseChange()
{
    m_ResetPassRecived = false;
}


/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving error code from ASC.
*
* \param   - none
*
* \return  - m_DeleteUserRecieved.
*
******************************************************************************/

bool UserManagement::GetDelUsrReqRepsonseChange()
{
    return m_DeleteUserRecieved;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing the error code on HMI.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetDelUsrReqRepsonseChange()
{
    m_DeleteUserRecieved = false;
}

/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving error code from ASC.
*
* \param   - none
*
* \return  - m_AddUserRespRecieved.
*
******************************************************************************/

bool UserManagement::GetAddUsrReqRepsonseChange()
{
    return m_AddUserRespRecieved;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing the error code on HMI.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetAddUsrReqRepsonseChange()
{
    m_AddUserRespRecieved = false;
}

/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving error code from ASC.
*
* \param   - none
*
* \return  - m_ModifyUserRespRecieved.
*
******************************************************************************/

bool UserManagement::GetModifyUsrReqRepsonseChange()
{
    return m_ModifyUserRespRecieved;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing the error code on HMI.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetModifyUsrReqRepsonseChange()
{
    m_ModifyUserRespRecieved = false;
}
/**************************************************************************//**
*
* \brief   - Function UserDetails map to HMI upon update.
*
* \param   - none.
*
* \return  - m_UserDetails.
*
******************************************************************************/
std::map<std::string,UserListStruct> UserManagement::GetUserList()
{
   return m_UserDetails;
}

/**************************************************************************//**
*
* \brief   - Function to update Password Override dongle connected or not to HMI.
*
* \param   - none.
*
* \return  - m_IsPasswordOverride.
*
******************************************************************************/
bool UserManagement::GetPasswordOverride()
{
    return m_IsPasswordOverride;
}

/**************************************************************************//**
*
* \brief   - Function to update Password Override dongle value read to HMI.
*
* \param   - none.
*
* \return  - m_IsPasswordOverrideDataRead.
*
******************************************************************************/
bool UserManagement::getPasswordOverrideDataRead()
{
    return m_IsPasswordOverrideDataRead;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after read the data.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::ResetPasswordOverrideDataRead()
{
    m_IsPasswordOverrideDataRead = false;
}
/**************************************************************************//**
*
* \brief   - Print the user List from cached data
* \param   - None
*
* \return  - none
*
******************************************************************************/
void UserManagement::printUserList()
{
    if(m_UserDetails.size() == 0)
    {
        std::cout << "**********HMI side User List is Empty " << std::endl;
    }
    else
    {
        for (auto it=m_UserDetails.begin(); it!=m_UserDetails.end(); ++it)
        {
            std::cout << "HMI side User List Data: " << std::endl;
            std::cout << "**********User Name in map key:" << it->first << std::endl;
            std::cout << "**********User Name:" << it->second.UserID << std::endl;
            std::cout << "**********CreationDateTime:" << it->second.CreationDateTime << std::endl;
            std::cout << "**********Level (0: Operator, 1: Technician, 2: Supervisor, 3: Executive): " << it->second.Level << std::endl;
            std::cout << "**********Status (0:Enable, 1: Disable): " << it->second.Status << std::endl;
            std::cout << "**********IsLocked (0:Unlocked, 1: Locked): " << it->second.IsLocked << std::endl;
        }
    }
}


/**************************************************************************//**
*
* \brief   - Function updates the flag to HMI upon receving data from ASC.
*
* \param   - none
*
* \return  - m_UserPrivilegeRecived.
*
******************************************************************************/

bool UserManagement::GetUsrPrivilegeRepsonseChange()
{
    return m_UserPrivilegeRecived;
}

/**************************************************************************//**
*
* \brief   - Function sets the flag to false after processing thedata.
*
* \param   - none.
*
* \return  - none.
*
******************************************************************************/
void UserManagement::SetUsrPrivilegeRepsonseChange()
{
    m_UserPrivilegeRecived = false;
}
/**************************************************************************//**
*
* \brief   - Function UserPrivilegeDetails map to HMI upon update.
*
* \param   - none.
*
* \return  - m_UserPrivilegeDetails.
*
******************************************************************************/
std::map<std::string,UserPrivilegeStruct> UserManagement::GetUserPrivilege()
{
    return m_UserPrivilegeDetails;
}
/**************************************************************************//**
*
* \brief   - Print the user privilege from cached data
*
* \param   - None
*
* \return  - none
*
******************************************************************************/
void UserManagement::printUserPrivilegeData()
{
    if(m_UserPrivilegeDetails.size() == 0)
    {
        std::cout << "**********HMI side User Privilege is Empty***************************" << std::endl;
    }
    else
    {
        for (auto it = m_UserPrivilegeDetails.begin(); it != m_UserPrivilegeDetails.end(); ++it)
        {
            std::cout << "**************HMI side User Privilege Data**********************" << std::endl;
            std::cout << "User Privilege Level in map key: " << it->first << std::endl;
            std::cout << "Run Validated Weld Recipe: " << it->second.IsRunValidatedWeldRecipeAllowed << std::endl;
            std::cout << "Run UnValidated Weld Recipe: " << it->second.IsRunUnValidatedWeldRecipeAllowed << std::endl;
            std::cout << "Reset Alarms: " << it->second.IsResetAlarmsAllowed << std::endl;
            std::cout << "Set Recipe as Active: " << it->second.IsSetRecipeAsActiveAllowed << std::endl;
            std::cout << "Reset Batch Counter And ID: " << it->second.IsResetBatchCounterAndIDAllowed << std::endl;
            std::cout << "Reset Recipe Cycle Counts: " << it->second.IsResetRecipeCycleCountsAllowed << std::endl;
            std::cout << "Edit Recipes: " << it->second.IsEditRecipesAllowed << std::endl;
            std::cout << "Calibration: " << it->second.IsCalibrationAllowed << std::endl;
            std::cout << "Actuator Setup: " << it->second.IsActuatorSetupAllowed << std::endl;
            std::cout << "Diagnostics: " << it->second.IsDignosticsAllowed << std::endl;
            std::cout << "Save copy create: " << it->second.IsSaveCopyCreateRecipeAllowed << std::endl;
            std::cout << "Extract USB data: " << it->second.IsExtractUSBDataFromWelderAllowed << std::endl;
            std::cout << "System Config: " << it->second.IsSystemConfigurationAllowed << std::endl;
            std::cout << "Validate And Lock Weld Recipes: " << it->second.IsValidateAndLockWeldRecipesAllowed << std::endl;
            std::cout << "Add modify user ID setup: " << it->second.IsAddModifyUserIDSetupAllowed << std::endl;
            std::cout << "Modify Authority check: " << it->second.IsModifyAuthoritiyCheckAllowed << std::endl;
            std::cout << "Delete Recipe: " << it->second.IsDeleteRecipeAllowed << std::endl;
            std::cout << "Update Software: " << it->second.IsUpdateSoftwareAllowed << std::endl;
            std::cout << "Barcode recipe recall: " << it->second.IsBarcoderecipeRecallAllowed << std::endl;
        }
    }
}

/**************************************************************************//**
*
* \brief   - Process the Ldap Config Read response coming from ASC
*
* \param   - source - Memory block containing data coming from ASC
*
* \return  - none
*
*****************************************************************************/
void UserManagement::ProcessLdapConfigReadResponse(const MEMORY_BLOCK *const source)
{
	LdapConfigurationData *LdapConfigResponse = reinterpret_cast<LdapConfigurationData *>(source->data);
	memcpy(&m_LdapConfigData,LdapConfigResponse,sizeof(LdapConfigurationData));
	m_isLdapConfigDataReceived = true;
}
/**************************************************************************//**
*
* \brief   - Sends the Ldap Config Read Request to ASC
*
* \param   - destination - Memory block containing request to ASC
*
* \return  - none
*
*****************************************************************************/
void UserManagement::SendLdapConfigReadRequestToASC(MEMORY_BLOCK * const destination)
{
   if(destination->size >= sizeof(bool))
	{
		if(m_SendLdapConfigReadRequest == true)
		{
			destination->size = sizeof(bool);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_SendLdapConfigReadRequest = false;
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
* \brief   - QML should call this method to initiate Ldap Configuration Update Request
*
* \param   - LdapConfigData - Config Data to be sent to ASC
*
* \return  - none
*
******************************************************************************/
void UserManagement::InitiateLdapConfigurationUpdateRequest(LdapConfigurationData LdapConfigData)
{
	m_LdapConfigData = LdapConfigData;
    m_SendLdapConfigUpdateRequest = true;
}

/**************************************************************************//**
*
* \brief   - Sends the Ldap Config Write Request to ASC
*
* \param   - destination - Memory block containing new config values to write to ASC
*
* \return  - none
*
*****************************************************************************/
void UserManagement::SendLdapConfigUpdateRequestToASC(MEMORY_BLOCK * const destination)
{
   if(destination->size >= sizeof(LdapConfigurationData))
	{
		if(m_SendLdapConfigUpdateRequest == true)
		{
            LdapConfigurationData *Data = reinterpret_cast<LdapConfigurationData *>(destination->data);

            strncpy(Data->Host,m_LdapConfigData.Host, sizeof(m_LdapConfigData.Host));
            Data->Port = m_LdapConfigData.Port;
            strncpy(Data->BaseDN,m_LdapConfigData.BaseDN, sizeof(m_LdapConfigData.BaseDN));
            strncpy(Data->ManagerDN,m_LdapConfigData.ManagerDN,
            		sizeof(m_LdapConfigData.ManagerDN));
            strncpy(Data->ManagerDNPwd,m_LdapConfigData.ManagerDNPwd, sizeof(m_LdapConfigData.ManagerDNPwd));

            destination->size = sizeof(LdapConfigurationData);
			destination->config = VALID_BIT;

			//Reset the flag once the request is sent.
			m_SendLdapConfigUpdateRequest = false;
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

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

SystemConfGlobalUserSetting class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef SystemConfGlobalUserSetting_H
#define SystemConfGlobalUserSetting_H

#include <QObject>
#include "GlobalUserSettingStructure.h"
#include "UpdateScreens.h"

class SystemConfGlobalUserSetting : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(int PasswordExpiration  READ getPasswordExpiration  WRITE updatePasswordExpiration  NOTIFY globalUserSettingDataChanged)
    Q_PROPERTY(int IdleTimeLogout  READ getIdleTimeLogout  WRITE updateIdleTimeLogout  NOTIFY globalUserSettingDataChanged)
    Q_PROPERTY(int LockOutTime  READ getLockOutTime  WRITE updateLockOutTime  NOTIFY globalUserSettingDataChanged)
    Q_PROPERTY(int UpdateErrorCode  READ getGlobalUserDataUpdateResult  NOTIFY globalUserSettingErrorCodeUpdated)
    Q_PROPERTY(bool AutoLoginStatus  READ getAutoLoginStatus WRITE updateAutoLoginStatus  NOTIFY globalUserSettingDataChanged)
    Q_PROPERTY(QString AutoLoginUser  READ getAutoLoginUser WRITE updateAutoLoginUser  NOTIFY globalUserSettingDataChanged)
    Q_PROPERTY(bool AuthorityCheck  READ getAuthorityCheck WRITE updateAuthorityCheck  NOTIFY globalUserSettingDataChanged)

public:
    explicit SystemConfGlobalUserSetting(QObject *parent = nullptr);
    QStringList operatorUserList;

    int getPasswordExpiration() const;
    void updatePasswordExpiration(int newPasswordExpirationValue);
    int getIdleTimeLogout() const;
    void updateIdleTimeLogout(int newIdleTimeLogoutValue);
    int getLockOutTime() const;
    void updateLockOutTime(int newLockOutTimeValue);
    bool getAutoLoginStatus() const;
    void updateAutoLoginStatus(bool autoLoginStaus);
    QString getAutoLoginUser() const;
    void updateAutoLoginUser(QString autoLoginUser);
    bool getAuthorityCheck();
    void updateAuthorityCheck(bool AuthorityCheck);

    UPDATE_GLOBAL_USER_SETTING_ERROR_CODES getGlobalUserDataUpdateResult();

    Q_INVOKABLE void saveRequest();
    Q_INVOKABLE void resetToDefaultRequest();
    Q_INVOKABLE QStringList loadOperatorUser();
    Q_INVOKABLE void setAutoLogin(bool autoLoginStatus, QString autoLoginUser);

    // Signal to notify QML about updated values
signals:
    void globalUserSettingDataChanged();
    void globalUserSettingErrorCodeUpdated();


private:
    /*Holds UserManagemangent data*/
    UserManagement *m_UserManagement;

    SystemConfigurationGeneral_MB *m_SysConfigGeneral;
    /*Holds User List data*/
    std::map<std::string,UserListStruct> m_UserDetailsList;

    GlobalUserSetting *m_GlobalUserSetting;
    UPDATE_GLOBAL_USER_SETTING_ERROR_CODES m_GlobalUserDataUpdateResult;
    int m_ActiveWelderId = -1;
    int m_PasswordExpirationValue;
    int m_IdleTimeLogoutValue;
    int m_LockOutTimeValue;
    bool m_AutoLoginStatus;
    bool m_AuthorityCheck;
    QString m_AutoLoginUser;

private slots:
    void OnGlobalUserSettingDataUpdated(GlobalUserSetting *GlobalUserSetting_Obj, UserManagement *UserManagementScreen_Obj, SystemConfigurationGeneral_MB *SysConfgGeneral_Obj, int welderId);
};

#endif // SystemConfGlobalUserSetting_H



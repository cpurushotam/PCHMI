/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef UserPrivilege_H
#define UserPrivilege_H

#include <QObject>
#include "UserManagement.h"

class UserPrivilege : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/



    Q_PROPERTY(bool IsRunValidatedWeldRecipeAllowed          READ getIsRunValidatedWeldRecipeAllowed       WRITE updateIsRunValidatedWeldRecipeAllowed         NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsRunUnValidatedWeldRecipeAllowed        READ getIsRunUnValidatedWeldRecipeAllowed     WRITE updateIsRunUnValidatedWeldRecipeAllowed       NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsResetAlarmsAllowed                     READ getIsResetAlarmsAllowed                  WRITE updateIsResetAlarmsAllowed                    NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsSetRecipeAsActiveAllowed               READ getIsSetRecipeAsActiveAllowed            WRITE updateIsSetRecipeAsActiveAllowed              NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsResetBatchCounterAndIDAllowed          READ getIsResetBatchCounterAndIDAllowed       WRITE updateIsResetBatchCounterAndIDAllowed         NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsResetRecipeCycleCountsAllowed          READ getIsResetRecipeCycleCountsAllowed       WRITE updateIsResetRecipeCycleCountsAllowed         NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsEditRecipesAllowed                     READ getIsEditRecipesAllowed                  WRITE updateIsEditRecipesAllowed                    NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsCalibrationAllowed                     READ getIsCalibrationAllowed                  WRITE updateIsCalibrationAllowed                    NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsActuatorSetupAllowed                   READ getIsActuatorSetupAllowed                WRITE updateIsActuatorSetupAllowed                  NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsDignosticsAllowed                      READ getIsDignosticsAllowed                   WRITE updateIsDignosticsAllowed                     NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsSaveCopyCreateRecipeAllowed            READ getIsSaveCopyCreateRecipeAllowed         WRITE updateIsSaveCopyCreateRecipeAllowed           NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsExtractUSBDataFromWelderAllowed        READ getIsExtractUSBDataFromWelderAllowed     WRITE updateIsExtractUSBDataFromWelderAllowed       NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsSystemConfigurationAllowed             READ getIsSystemConfigurationAllowed          WRITE updateIsSystemConfigurationAllowed            NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsValidateAndLockWeldRecipesAllowed      READ getIsValidateAndLockWeldRecipesAllowed   WRITE updateIsValidateAndLockWeldRecipesAllowed     NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsAddModifyUserIDSetupAllowed            READ getIsAddModifyUserIDSetupAllowed         WRITE updateIsAddModifyUserIDSetupAllowed           NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsModifyAuthoritiyCheckAllowed           READ getIsModifyAuthoritiyCheckAllowed        WRITE updateIsModifyAuthoritiyCheckAllowed          NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsDeleteRecipeAllowed                    READ getIsDeleteRecipeAllowed                 WRITE updateIsDeleteRecipeAllowed                   NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsUpdateSoftwareAllowed                  READ getIsUpdateSoftwareAllowed               WRITE updateIsUpdateSoftwareAllowed                 NOTIFY userPrivilegedChanged)
    Q_PROPERTY(bool IsBarcoderecipeRecallAllowed             READ getIsBarcoderecipeRecallAllowed          WRITE updateIsBarcoderecipeRecallAllowed            NOTIFY userPrivilegedChanged)

public:

    explicit UserPrivilege(QObject *parent = nullptr);

    /*Q_INVOKABLE functions to call from QML */


    Q_INVOKABLE void processUserPrivilige();
    Q_INVOKABLE QString getLogedInUserLevel();



   /* Changes for Operator Level Handle at HMI */
    bool getIsRunValidatedWeldRecipeAllowed() const;
    void updateIsRunValidatedWeldRecipeAllowed(bool newIsRunValidatedWeldRecipeAllowed);

    bool getIsRunUnValidatedWeldRecipeAllowed() const;
    void updateIsRunUnValidatedWeldRecipeAllowed(bool newIsRunUnValidatedWeldRecipeAllowed);

    bool getIsResetAlarmsAllowed() const;
    void updateIsResetAlarmsAllowed(bool newIsResetAlarmsAllowed);

    bool getIsSetRecipeAsActiveAllowed() const;
    void updateIsSetRecipeAsActiveAllowed(bool newIsSetRecipeAsActiveAllowed);

    bool getIsResetBatchCounterAndIDAllowed() const;
    void updateIsResetBatchCounterAndIDAllowed(bool newIsResetBatchCounterAndIDAllowed);

    bool getIsResetRecipeCycleCountsAllowed() const;
    void updateIsResetRecipeCycleCountsAllowed(bool newIsResetRecipeCycleCountsAllowed);

    bool getIsEditRecipesAllowed() const;
    void updateIsEditRecipesAllowed(bool newIsEditRecipesAllowed);

    bool getIsCalibrationAllowed() const;
    void updateIsCalibrationAllowed(bool newIsCalibrationAllowed);

    bool getIsActuatorSetupAllowed() const;
    void updateIsActuatorSetupAllowed(bool newIsActuatorSetupAllowed);

    bool getIsDignosticsAllowed() const;
    void updateIsDignosticsAllowed(bool newIsDignosticsAllowed);

    bool getIsSaveCopyCreateRecipeAllowed() const;
    void updateIsSaveCopyCreateRecipeAllowed(bool newIsSaveCopyCreateRecipeAllowed);

    bool getIsExtractUSBDataFromWelderAllowed() const;
    void updateIsExtractUSBDataFromWelderAllowed(bool newIsExtractUSBDataFromWelderAllowed);

    bool getIsSystemConfigurationAllowed() const;
    void updateIsSystemConfigurationAllowed(bool newIsSystemConfigurationAllowed);

    bool getIsValidateAndLockWeldRecipesAllowed() const;
    void updateIsValidateAndLockWeldRecipesAllowed(bool newIsValidateAndLockWeldRecipesAllowed);

    bool getIsAddModifyUserIDSetupAllowed() const;
    void updateIsAddModifyUserIDSetupAllowed(bool newIsAddModifyUserIDSetupAllowed);

    bool getIsModifyAuthoritiyCheckAllowed() const;
    void updateIsModifyAuthoritiyCheckAllowed(bool newIsModifyAuthoritiyCheckAllowed);

    bool getIsDeleteRecipeAllowed() const;
    void updateIsDeleteRecipeAllowed(bool newIsDeleteRecipeAllowed);

    bool getIsUpdateSoftwareAllowed() const;
    void updateIsUpdateSoftwareAllowed(bool newIsUpdateSoftwareAllowed);

    bool getIsBarcoderecipeRecallAllowed() const;
    void updateIsBarcoderecipeRecallAllowed(bool newIsBarcoderecipeRecallAllowed);

private:

    int m_ActiveWelderId = -1;

    UserManagement *m_UserManagement;

    int m_CurrentActiveScreen;

    std::map<std::string,UserPrivilegeStruct> m_UserPrivilegeDetails;


    /* Changes for Operator Level Handle at HMI */
    bool m_IsRunValidatedWeldRecipeAllowed;
    bool m_IsRunUnValidatedWeldRecipeAllowed;
    bool m_IsResetAlarmsAllowed;
    bool m_IsSetRecipeAsActiveAllowed;
    bool m_IsResetBatchCounterAndIDAllowed;
    bool m_IsResetRecipeCycleCountsAllowed;
    bool m_IsEditRecipesAllowed;
    bool m_IsCalibrationAllowed;
    bool m_IsActuatorSetupAllowed;
    bool m_IsDignosticsAllowed;
    bool m_IsSaveCopyCreateRecipeAllowed;
    bool m_IsExtractUSBDataFromWelderAllowed;
    bool m_IsSystemConfigurationAllowed;
    bool m_IsValidateAndLockWeldRecipesAllowed;
    bool m_IsAddModifyUserIDSetupAllowed;
    bool m_IsModifyAuthoritiyCheckAllowed;
    bool m_IsDeleteRecipeAllowed;
    bool m_IsUpdateSoftwareAllowed;
    bool m_IsBarcoderecipeRecallAllowed;
    bool m_IsUsbAuthenticationAllowed;
signals:
    /*Signals to notify qml about data update from ASC.*/

    /* Changes for Operator Level Handle at HMI */
    void userPrivilegedChanged();

private slots:
    /*Slot to be called when data update signal generated by communication thread*/
    void OnUserPrivilegeScreenDetailsUpdated(UserManagement *UserManagement_Obj, int WelderId);

};

#endif // UserPrivilege_H

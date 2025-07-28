/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

Branson System Configuration class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef BransonSystemConfiguration_H
#define BransonSystemConfiguration_H

#include <QObject>
#include "SystemConfigBransonServiceStructure.h"
#include "SystemConfigBransonService.h"
#include "UpdateScreens.h"

class BransonSystemConfiguration : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(int UpdatedErrorCode  READ getBransonSystemConfigUpdateResult  NOTIFY bransonSystemConfigurationErrorCodeUpdated)
    Q_PROPERTY(QString MachineSerialNumber  READ getMachineSerialNumber  NOTIFY bransonSystemConfigurationChanged)
    Q_PROPERTY(QString PowerSupplySerialNumber  READ getPowerSupplySerialNumber  NOTIFY bransonSystemConfigurationChanged)
    Q_PROPERTY(QString ActuatorSerialNumber  READ getActuatorSerialNumber  NOTIFY bransonSystemConfigurationChanged)


public:
    explicit BransonSystemConfiguration(QObject *parent = nullptr);

    QString getMachineSerialNumber() const;
    QString getPowerSupplySerialNumber() const;
    QString getActuatorSerialNumber() const;

    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES getBransonSystemConfigUpdateResult();

    Q_INVOKABLE void saveRequest();
    Q_INVOKABLE void updateMachineSerialNumber(QString machineSerialNumber);
    Q_INVOKABLE void updatePowerSupplySerialNumber(QString powerSupplySerialNumber);
    Q_INVOKABLE void updateActuatorSerialNumber(QString actuatorSerialNumber);

    // Signal to notify QML about updated values
signals:
    void bransonSystemConfigurationChanged();
    void bransonSystemConfigurationErrorCodeUpdated();


private:
    /*Holds Branson System Configuration data*/
    SystemConfigBransonService *m_SystemConfigBransonService;

    UPDATE_SYSTEM_CONFIG_BRANSON_SERVICE_ERROR_CODES m_BransonSystemConfigUpdateResult;
    int m_ActiveWelderId = -1;
    QString m_machineSerialNumber;
    QString m_powerSupplySerialNumber;
    QString m_actuatorSerialNumber;

private slots:
    void OnBransonSystemConfigurationUpdated(SystemConfigBransonService *SystemConfigBransonService_Obj, int welderId);
};

#endif // BransonSystemConfiguration_H



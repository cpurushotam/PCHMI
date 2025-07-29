/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file is a header file and it is the model file of system information window.

 **********************************************************************************************************/

#ifndef SystemInformationInterface_H
#define SystemInformationInterface_H

#include <QObject>
#include <QString>
#include "UpdateScreens.h"
#include "SystemInformation.h"
#include "SystemInformationStructure.h"
#include "CylinderSizeSupport.h"
#include "BearingTypeSupport.h"

#define ACT_MANUAL                      "Manual"
#define ACT_ELECTRONIC                  "Electric"
#define ACT_ELECTRONIC_PLUS             "Electric_Plus"

#define P_2100_PS                       "P_2100"
#define P_2200_PS                       "P_2200"
#define P_2300_PS                       "P_2300"

#define STROKE_LENGTH_100MM        "100 mm"
#define STROKE_LENGTH_125MM        "125 mm"

#define FORTY_MM_CYLINDER_Size                       40
#define FIFTY_MM_CYLINDER_Size                       50
#define SIXTY_THREE_MM_CYLINDER_Size                 63
#define EIGHTY_MM_CYLINDER_Size                      80

//SystemInformationInterface class declaration.
class SystemInformationInterface : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(int GerneralAlarms READ getGeneralAlarm  NOTIFY systemInfoMachineDetailsChanged)

    //software version
    Q_PROPERTY(QString UIControllerVersion READ getUIControllerVersion NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString SupervisoryControllerVersion READ getSupervisoryControllerVersion NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString ActuatorControllerVersion READ getActuatorControllerVersion NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString PowerControllerVersion READ getPowerControllerVersion NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString SafetyControllerVersion READ getSafetyControllerVersion NOTIFY systemInfoMachineDetailsChanged)

    Q_PROPERTY(QString PSSerialNumber READ getPSSerialNumber NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int PSLifeWelds READ getPSLifeWelds NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int PSOverloads READ getPSOverloads  NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString PSModel READ getPSModel NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int PSFrequency READ getPSFrequency NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int PSWatt READ getPSWattage NOTIFY systemInfoMachineDetailsChanged)

    Q_PROPERTY(QString ACSerialNumber READ getACSerialNumber NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int ActuatorLifeCycle READ getActuatorLifeCycle NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString ActuatorModel READ getActuatorModel NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString ActuatorCalibrationDate READ getActuatorCaliDate  NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString StrokeLength READ getStrokeLength  NOTIFY systemInfoMachineDetailsChanged)

    Q_PROPERTY(QString MACAddress READ getMACAddress NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(int CylinderSize READ getCylinderSize NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(BEARING_TYPE_CONFIG bearingType READ getbearingType NOTIFY systemInfoMachineDetailsChanged)
    Q_PROPERTY(QString MachineSerialNumber  READ getMachineSerialNumber  NOTIFY systemInfoMachineDetailsChanged)

public:
    explicit  SystemInformationInterface(QObject *parent = nullptr);

    int getGeneralAlarm() const;

    QString getUIControllerVersion() const;
    QString getSupervisoryControllerVersion() const;
    QString getActuatorControllerVersion() const;
    QString getPowerControllerVersion() const;
    QString getSafetyControllerVersion() const;

    QString getPSSerialNumber() const;
    int getPSLifeWelds() const;
    int getPSOverloads() const;
    QString getPSModel() const;
    int getPSFrequency() const;
    int getPSWattage() const;

    QString getACSerialNumber() const;
    int getActuatorLifeCycle() const;
    QString getActuatorModel() const;
    QString getActuatorCaliDate() const;
    QString getStrokeLength() const;

    QString getMACAddress() const;
    int getCylinderSize() const;
    BEARING_TYPE_CONFIG getbearingType() const;

    QString getMachineSerialNumber() const;

signals:
    void systemInfoMachineDetailsChanged();

private:

    //Holds system information machine details data
    SystemInformation *m_SystemInformationMachineDetails;
    SystemConfigBransonService *m_SystemConfigBransonService;
    int m_ActiveWelderId = -1;
    //Total no of alarms
    int m_NoOfAlarms;
    //Software version
    QString m_UIVersion;
    QString m_SCVersion;
    QString m_ACVersion;
    QString m_PCVersion;
    QString m_SafetyControllerVersion;
    //Power supply parameter
    QString m_PowerSupplySerialNumber;
    int m_PSLifeWelds;
    int m_PSOverloads;
    QString m_PSModel;
    int m_PSFrequency;
    int m_PSWattage;
    //Actuator parameter
    QString m_ActuatorSerialNumber;
    int m_ActuatorLifeCycle;
    QString m_ActuatorModel;
    QString m_CalibrationDate;
    QString m_StrokeLength;
    //Mac address
    QString m_MacAddress;
    BEARING_TYPE_CONFIG m_BearingType;
    QString m_MachineSerialNumber;

private slots:
    void OnSystemInformationDataUpdated(SystemInformation *SystemInformation_Obj,SystemConfigBransonService *SystemConfigBransonService_Obj, int welderId);

};



#endif // SystemInformationInterface_H

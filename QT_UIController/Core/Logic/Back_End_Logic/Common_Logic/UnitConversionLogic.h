/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the unit conversion related implementation
 ***************************************************************************/
#ifndef UNITCONVERSIONLOGIC_H
#define UNITCONVERSIONLOGIC_H

#include <QObject>
#include <QString>
#include "UnitConversion.h"
#include "SystemConfigurationGeneral_MB.h"

class UnitConversionLogic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString PressureUnit          READ getPressureUnit            NOTIFY currentUnitChanged)
    Q_PROPERTY(QString DistanceUnit          READ getDistanceUnit            NOTIFY currentUnitChanged)
    Q_PROPERTY(QString VelocityUnit          READ getVelocityUnit            NOTIFY currentUnitChanged)
    Q_PROPERTY(QString ForceUnit             READ getForceUnit               NOTIFY currentUnitChanged)
    Q_PROPERTY(QString TimeUnit              READ getTimeUnit                NOTIFY currentUnitChanged)
    Q_PROPERTY(QString EnergyUnit            READ getEnergyUnit              NOTIFY currentUnitChanged)
    Q_PROPERTY(QString PowerUnit             READ getPowerUnit               NOTIFY currentUnitChanged)
    Q_PROPERTY(QString FrequencyUnit         READ getFrequencyUnit           NOTIFY currentUnitChanged)
    Q_PROPERTY(QString PhaseUnit             READ getPhaseUnit               NOTIFY currentUnitChanged)
    Q_PROPERTY(QString CurrentUnit           READ getCurrentUnit             NOTIFY currentUnitChanged)
    Q_PROPERTY(QString AmplitudeUnit         READ getAmplitudeUnit           NOTIFY currentUnitChanged)
    Q_PROPERTY(QString RequestAmplitudeUnit  READ getRequestAmplitudeUnit    NOTIFY currentUnitChanged)
    Q_PROPERTY(QString DownSpeedUnit         READ getDownSpeedUnit           NOTIFY currentUnitChanged)

public:
    explicit UnitConversionLogic(QObject *parent = nullptr);
    QString getPressureUnit() const;
    QString getDistanceUnit() const;
    QString getVelocityUnit() const;
    QString getForceUnit() const;
    QString getTimeUnit() const;
    QString getEnergyUnit() const;
    QString getPowerUnit() const;
    QString getFrequencyUnit() const;
    QString getPhaseUnit() const;
    QString getCurrentUnit() const;
    QString getAmplitudeUnit() const;
    QString getRequestAmplitudeUnit() const;
    QString getDownSpeedUnit() const;

    Q_INVOKABLE UNIT currentUnit();
    Q_INVOKABLE void sendUnitChangeRequest(int unit);

signals:
    void currentUnitChanged();

private:
    QString m_PressureUnit;
    QString m_DistanceUnit;
    QString m_VelocityUnit;
    QString m_ForceUnit;
    QString m_TimeUnit;
    QString m_EnergyUnit;
    QString m_PowerUnit;
    QString m_FrequencyUnit;
    QString m_PhaseUnit;
    QString m_CurrentUnit;
    QString m_AmplitudeUnit;
    QString m_RequestAmplitudeUnit;
    QString m_DownSpeedUnit;

    SystemConfigurationGeneral_MB *systemConfigPtr;

private slots:

 void OnUnitChangedScreenUpdated(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId);

};

#endif // UNITCONVERSIONLOGIC_H

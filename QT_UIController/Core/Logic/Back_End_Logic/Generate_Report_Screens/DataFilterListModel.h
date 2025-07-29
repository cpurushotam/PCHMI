/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    DataFilterListModel.h file provides mode details and status of button and checkboxses.
--------------------------- REVISION HISTORY ------------------------------
***************************************************************************/
#ifndef DATAFILTERLISTMODEL_H
#define DATAFILTERLISTMODEL_H

#include <QAbstractListModel>
#include "USBStreamStructure.h"
#include "USBStreaming.h"
#include "UpdateScreens.h"
#include "SystemConfiguration.h"
#include "ActuatorInit.h"
enum StorageOptionsEnum
{
    usbStorgaeOption = 0,
    networkAttachedStorage,
    plc
};
class DataFilterListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString CycleCount READ getCycleCount WRITE updateCycleCount NOTIFY cycleCountUpdated)
public:
    Q_INVOKABLE bool m_EncryptRadioButton = false;
    Q_INVOKABLE bool m_StorageoptButton = false;
    Q_INVOKABLE bool m_OutputRadioButton = false;
    Q_INVOKABLE bool m_SaveOnAlarmRadioButton = false;
    Q_INVOKABLE int  m_StorageRadioButton = usbStorgaeOption;
    explicit DataFilterListModel(QObject *parent = nullptr);

    Q_INVOKABLE void onCheckStatusChanged(bool checkStatus, int index);
    Q_INVOKABLE bool getCheckStatus(int index);
    Q_INVOKABLE QString getDatafiltersList();
    Q_INVOKABLE void createDataFilterList();
    Q_INVOKABLE void onClickOnSaveOnAlarm(bool alarmValue);
    Q_INVOKABLE void onCycleCount(QString cycleCount);
    Q_INVOKABLE QString getCycleCount();
    Q_INVOKABLE void onEncryptionData(bool encryptValue);
    Q_INVOKABLE void onSelectionOfDataFilterParameter();
    Q_INVOKABLE void onSaveConfigurationClicked();
    Q_INVOKABLE int getStorageOptionValue();
    Q_INVOKABLE void setStorageOptionValue(int storageType);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    USBStreamStruct m_USBStreamStruct;
    USBStreaming * m_USBStreaming;
    SystemConfiguration * m_SystemConfiguration;
    struct modelData{
        QString Name;
        bool checkStatus;
    };
    QList<modelData *> m_dataList;
    QString m_CycleCount;
    void insertData(QString Name, bool checkStatus);
    enum dataRoles
    {
        nameRole = Qt::UserRole + 1,
        checkStatus
    };
    enum actuatorTypeValue
    {
        Manual = true
    };

    void clearFilterList();
    QString getCycleCount() const;
    void updateCycleCount(const QString& iCycleCount);

    /* Text Strings for language change support */
    QString m_WeldData = "WELD DATA";
    QString m_AmplitudeGraph = "AMPLITUDE GRAPH";
    QString m_FrequencyGraph = "FREQUENCY GRAPH";
    QString m_PhaseGraph = "PHASE GRAPH";
    QString m_CurrentGraph = "CURRENT GRAPH";
    QString m_EnergyGraph = "ENERGY GRAPH";
    QString m_RequestAmplitudeGraph = "REQUEST AMPLITUDE GRAPH";
    QString m_VelocityGraph = "VELOCITY GRAPH";
    QString m_ForceGraph = "FORCE GRAPH";
    QString m_AbsoluteDistanceGraph = "ABSOLUTE DISTANCE GRAPH";
    QString m_CollapseDistanceGraph = "COLLAPSE DISTANCE GRAPH";
    QString m_PowerGraph = "POWER GRAPH";

    /* list of language strings */
    QStringList m_LangList;

public slots:
    void onContinousDataStremmingUpdated(USBStreaming *USBStreaming_Obj );
signals:
  void cycleCountUpdated();

};

#endif // DATAFILTERLISTMODEL_H

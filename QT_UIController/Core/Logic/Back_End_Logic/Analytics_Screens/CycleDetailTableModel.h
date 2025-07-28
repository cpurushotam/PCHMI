/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailTableModel.h file handles cycle details list model container includes : Analytical TableView data .

***************************************************************************/
#ifndef CycleDetailTableModel_H
#define CycleDetailTableModel_H

#include <qqml.h>
#include <QAbstractTableModel>
#include "AnalyticTableListData.h"
#include "WeldResultAce.h"
#include "UpdateScreens.h"
#include "SystemConfiguration.h"
#include "ActuatorInit.h"

class CycleDetailTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:


    CycleDetailTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadTableViewDetailsList();
    Q_INVOKABLE bool isAlarmExist(int WeldResultRowIndex);
/*This function copies current weld result data from CycleDetailTableModel class to AnalyticsResultTableModel class.
    This data is required to get weldResultData to filter the cycle counter for searching the data on table.*/
    Q_INVOKABLE std::deque<WeldResultACEStruct> copyWeldResultData();

private:

    QString m_AlarmName = "";

    enum {
        Recipe = 0,
        RecipeVersion,
        DateTime ,
        StackSerial,
        PowerSupplySerialNumber,
        ActuatorSerialNumber,
        ASCSerialNumber,
        CycleCounter,
        WeldMode,
        WeldTime,
        HoldTime,
        WeldEnergy,
        PeakPower,
        StartFrequency,
        FrequencyChange,
        CycleTime,
        UserName,
        PartID,
        BatchID,
        TriggerPoint,
        WeldSonicPoint,
        HoldPoint,
        AlarmID,
        WeldStatus,
        RecipeStatus,
        WeldPressure,
        HoldPressure,
        MaxWeldForce,
        MaxHoldForce,
        EndWeldForce,
        EndHoldForce,
        WeldAbsolute,
        TotalAbsolute,
        Velocity,
        TriggerDistance,
        WeldCollapseDist,
        HoldCollapseDist,
        TotalCollapseDistance
    };

    QStringList m_columnNames;
    int m_ActiveWelderId = -1;

    void createNewTableViewDetailsList();
    void clearTableViewDetailsList();
    void addNewTableViewDetailsList(AnalyticTableListData *AnalyticTableList);
    void checkTheActutorType();

    QList<AnalyticTableListData*> m_ListData;
    WeldResultACE *m_WeldResultACE;

    std::deque<WeldResultACEStruct> m_WeldResultData;
    SystemConfiguration * m_SystemConfiguration;

signals:
    void tableViewListDataChanged();

private slots:
    void OnTableViewListUpdated(WeldResultACE *AnlyticsGraphScreenWeldResult_Obj, int WelderId);
};
#endif // CycleDetailtablemodel_H

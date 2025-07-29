/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    AnalyticsScreenTableViewOptions.h file provides cycle detail list container data
    handeled by CycleDetailsListModelto hide and show columns according to checks.
***************************************************************************/
#ifndef ANALYTICSSCREENTABLEVIEWOPTIONS_H
#define ANALYTICSSCREENTABLEVIEWOPTIONS_H
#define ParameterList 38 //No of Parameter Count of Manul and Electric Actuator
#include <QObject>
#include <QSortFilterProxyModel>
#include <QSettings>
#include "WeldResultAce.h"
#include "ActuatorInit.h"
#include "SystemConfiguration.h"
class AnalyticsScreenTableViewOptions : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    AnalyticsScreenTableViewOptions();
    Q_INVOKABLE void getColumnCheckedList(const QVariantList &indexes);
    Q_INVOKABLE bool getChooseParameterIndex(int index);
    Q_INVOKABLE void getWeldResultList(std::deque<WeldResultACEStruct> weldResultData);
    Q_INVOKABLE void getSearchData(QString searchCycleCount);

protected:
    bool filterAcceptsColumn(int sourceRow, const QModelIndex &) const override;
	bool filterAcceptsRow(int sourceRow, const QModelIndex &) const override;
private:
    void filterData();
    QList<int> hiddenRowsList;
    SystemConfiguration * m_SystemConfiguration;
    QString settingINIFilePath = "../ChooseParameterTable.ini";
    void setChooseParameterIndex(int index,bool val);
    std::deque<WeldResultACEStruct> m_WeldResultData;
    int m_cycleCounter;
    int rowFilterIndex;
    QString Manual= "Manual";
    QString Electric = "Electric";

};

#endif // ANALYTICSSCREENTABLEVIEWOPTIONS_H

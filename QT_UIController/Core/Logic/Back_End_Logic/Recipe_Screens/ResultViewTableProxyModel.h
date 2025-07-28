/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file filters the data from cycleDetailsTableModel to show reference
    graph data in qml.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
***************************************************************************/

#ifndef RESULTVIEWTABLEPROXYMODEL_H
#define RESULTVIEWTABLEPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "ReferenceWeldGraphData.h"
#include "WeldResultAce.h"

//Use to remove last comma from string
#define LAST_COMMA 1


class ResultViewTableProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ getNumberOfRows NOTIFY rowCountChanged)
    Q_PROPERTY(QString refGraphCycleNumbers READ getAllCycleNumber NOTIFY rowCountChanged)
public:
    explicit ResultViewTableProxyModel(QObject *parent = nullptr);
    Q_INVOKABLE void getWeldAndReferneceDataList(std::deque<ReferenceGraphStruct>
                                                     RequestedReferenceGraphData,std::deque<WeldResultACEStruct> WeldResultData);
    Q_INVOKABLE QString getCycleNumberForListView(int index);
    Q_INVOKABLE void removeDataFromList(int index);
    Q_INVOKABLE void appendDataToList(int index);
    Q_INVOKABLE int getVisibleRowCount();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &source_parent) const override;
private:
    QList<int> hiddenRowsList;
    QList<int> m_selectedCycleDetailsList;
    QList<int> cycleDetailsList;
    std::deque<ReferenceGraphStruct> m_RequestedReferenceGraphData;
    std::deque<WeldResultACEStruct> m_WeldResultData;
    int m_rowCount;
    void modifyReferenceGraphList();
    QString getAllCycleNumber();
    int getNumberOfRows();

    enum cycleCounterCheck{
        UNSELECTED,
        SELECTED
    };
signals:
    void rowCountChanged();
    void visibleRowCountChanged();


};

#endif // RESULTVIEWTABLEPROXYMODEL_H

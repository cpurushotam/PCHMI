/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file filters the data from cycleDetailsTableModel to show
    weld data excluding reference graph data in qml.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 19/03/2025 - Initial version.
***************************************************************************/

#ifndef RESULTVIEWWELDPROXYMODEL_H
#define RESULTVIEWWELDPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "ReferenceWeldGraphData.h"
#include "WeldResultAce.h"

class ResultViewWeldProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ResultViewWeldProxyModel(QObject *parent = nullptr);
    Q_INVOKABLE void getWeldAndReferneceDataList(std::deque<ReferenceGraphStruct> RequestedReferenceGraphData,std::deque<WeldResultACEStruct> WeldResultData);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &) const override {
        return !hiddenRowsList.contains(sourceRow); // Hide rows that are in the list
    }

private:
    QList<int> hiddenRowsList;
    std::deque<ReferenceGraphStruct> m_RequestedReferenceGraphData;
    std::deque<WeldResultACEStruct> m_WeldResultData;
    void modifyWeldGraphList();
};

#endif // RESULTVIEWWELDPROXYMODEL_H

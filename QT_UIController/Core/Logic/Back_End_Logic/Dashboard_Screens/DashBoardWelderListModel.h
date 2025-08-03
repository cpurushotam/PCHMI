#ifndef DASHBOARDWELDERLISTMODEL_H
#define DASHBOARDWELDERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "CommonUtils.h"

class QTimer;

class DashBoardWelderListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DashBoardWelderListModel(QObject *parent = nullptr);
    enum WELDER_DETAILS
    {
        WELDER_VAL = (Qt::UserRole + 1),
        BATCH_COUNT,
        YEILD_PERCENTAGE,
        TOTAL_CYCLE_COUNT,
        PEAK_POWER,
        SPEAKER_BOX_VAL,
        WELDER_TIME,
        CONNECTION_STATUS,
        PROGRESS_BAR_VAL_LIST
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:

public slots:
    void updateWelderData();

private:
    QList<WelderDetails> mWelderDetailsList;

    QTimer* simulateDataUpdate;
};

#endif // DASHBOARDWELDERLISTMODEL_H

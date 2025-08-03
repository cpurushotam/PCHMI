#include "DashBoardWelderListModel.h"

#include <QTimer>

#define MAX_WELDER_COUNT 4

DashBoardWelderListModel::DashBoardWelderListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    simulateDataUpdate = new QTimer(this);
    simulateDataUpdate->setInterval(500);
    connect(simulateDataUpdate,&QTimer::timeout,this,&DashBoardWelderListModel::updateWelderData);
    simulateDataUpdate->start();
}

int DashBoardWelderListModel::rowCount(const QModelIndex &parent) const
{
    return mWelderDetailsList.count();
}

QVariant DashBoardWelderListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= mWelderDetailsList.count())
    {
        return QVariant();
    }
    switch (role) {
    case WELDER_VAL:
        {
            return mWelderDetailsList.at(index.row()).welderVal;
        }
        break;
    case BATCH_COUNT:
        {
            return mWelderDetailsList.at(index.row()).batchCount;
        }
        break;
    case YEILD_PERCENTAGE:
        {
            return mWelderDetailsList.at(index.row()).yeildPercentage;
        }
        break;
    case TOTAL_CYCLE_COUNT:
        {
            return mWelderDetailsList.at(index.row()).totalCycleTime;
        }
        break;
    case PEAK_POWER:
        {
            return mWelderDetailsList.at(index.row()).peakPower;
        }
        break;
    case SPEAKER_BOX_VAL:
        {
            return mWelderDetailsList.at(index.row()).speakerBoxVal;
        }
        break;
    case WELDER_TIME:
        {
            return mWelderDetailsList.at(index.row()).welderTime;
        }
        break;
    case CONNECTION_STATUS:
        {
            return mWelderDetailsList.at(index.row()).connectionState;
        }
        break;
    case PROGRESS_BAR_VAL_LIST:
    {
        return mWelderDetailsList.at(index.row()).progressValList;
    }
    break;
    default:
        break;
    }
}


// unsigned short welderVal;
// unsigned int batchCount;
// float yeildPercentage;
// float totalCycleTime;
// unsigned short peakPower;
// unsigned int speakerBoxVal;
// float welderTime;
// bool connectionState;

QHash<int, QByteArray> DashBoardWelderListModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[WELDER_VAL]        = "welderVal";
    hash[BATCH_COUNT]       = "batchCount";
    hash[YEILD_PERCENTAGE]  = "yeildPercentage";
    hash[TOTAL_CYCLE_COUNT] = "totalCycleCount";
    hash[PEAK_POWER]        = "peackPower";
    hash[SPEAKER_BOX_VAL]   = "speakerBoxVal";
    hash[WELDER_TIME]       = "welderTime";
    hash[CONNECTION_STATUS] = "connectionStatus";
    hash[PROGRESS_BAR_VAL_LIST] = "progressValList";

    return hash;
}

void DashBoardWelderListModel::updateWelderData()
{
    // Add New welder data
    if(mWelderDetailsList.count() < MAX_WELDER_COUNT)
    {
        int row = mWelderDetailsList.count();
        beginInsertRows(QModelIndex(), row, row);
        mWelderDetailsList.push_back(WelderDetails(50,50000,45.2,12.456,52,7,0.500,false,"65,15,20"));

        // if(row == 0)
        //     mWelderDetailsList.push_back(WelderDetails(50,50000,45.2,12.456,52,7,0.500,false,"65,15,20"));
        // else if(row == 1)
        //     mWelderDetailsList.push_back(WelderDetails(90,95000,76.2,82.456,20,7,1.800,true,"55,35,10"));
        // else if(row == 2)
        //     mWelderDetailsList.push_back(WelderDetails(45,85000,76.2,82.456,80,7,0.700,true,"35,15,50"));
        // else if(row == 3)
        //     mWelderDetailsList.push_back(WelderDetails(72,100000,76.2,82.456,10,7,2.300,true,"25,50,25"));
        endInsertRows();
    }
    else
    {
        int welderRandomIndex = (rand()%MAX_WELDER_COUNT);
        if(welderRandomIndex < mWelderDetailsList.count())
        {
            mWelderDetailsList[welderRandomIndex].welderVal = (rand()%100);
            mWelderDetailsList[welderRandomIndex].batchCount = (rand()%100000);
            mWelderDetailsList[welderRandomIndex].yeildPercentage = (rand()%100 + (rand()%10)/10);
            mWelderDetailsList[welderRandomIndex].totalCycleTime = (rand()%100 + ((rand()%1000)/1000));
            mWelderDetailsList[welderRandomIndex].peakPower = (rand()%100);
            mWelderDetailsList[welderRandomIndex].speakerBoxVal = (rand()%10);
            mWelderDetailsList[welderRandomIndex].welderTime = (rand()%10 + ((rand()%1000)/1000));
            mWelderDetailsList[welderRandomIndex].connectionState = (rand()%2);

            int val1 = (rand()%50);
            int val2 = (rand()%40);
            int val3 = (100 - val1 - val2);
            mWelderDetailsList[welderRandomIndex].progressValList = QString::number(val1)+","+QString::number(val2)+","+QString::number(val3);

            // Notify the view that the data has changed for this row
            QModelIndex changedIndex = index(welderRandomIndex);
            emit dataChanged(changedIndex, changedIndex);
        }
    }
}

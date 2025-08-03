#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QVariantList>

//#pragma pack(1)

struct WelderDetails
{
    unsigned short welderVal;
    unsigned int batchCount;
    float yeildPercentage;
    float totalCycleTime;
    unsigned short peakPower;
    unsigned int speakerBoxVal;
    float welderTime;
    bool connectionState;
    QString progressValList;
    WelderDetails()
    {
        welderVal       = 0;
        batchCount      = 0;
        yeildPercentage = 0;
        totalCycleTime  = 0;
        peakPower       = 0;
        speakerBoxVal   = 0;
        welderTime      = 0;
        connectionState = false;
        progressValList = "";
    }
    WelderDetails(unsigned short welderVal,unsigned int batchCount, float yeildPercentage,float totalCycleTime,unsigned short peakPower,unsigned int speakerBoxVal,float welderTime,bool connectionState,QString progressValList) {
        this->welderVal         = welderVal;
        this->batchCount        = batchCount;
        this->yeildPercentage   = yeildPercentage;
        this->totalCycleTime    = totalCycleTime;
        this->peakPower         = peakPower;
        this->speakerBoxVal     = speakerBoxVal;
        this->welderTime        = welderTime;
        this->connectionState   = connectionState;
        this->progressValList   = progressValList;
    }
};

#endif // COMMONUTILS_H

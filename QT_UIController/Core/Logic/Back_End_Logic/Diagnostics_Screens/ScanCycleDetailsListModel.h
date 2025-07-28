/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    ScanCycleDetailsListModel.h file handles cycle details list model container.
--------------------------- REVISION HISTORY ------------------------------
    rev1: rev1: 02/04/2024 - Initial version.
***************************************************************************/
#ifndef SCANCYCLEDETAILSLIST_H
#define SCANCYCLEDETAILSLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QSettings>
#include "UpdateScreens.h"
#include "ScanCycleDetailsListData.h"
#include "HornScanRecipe.h"

class ScanCycleDetailsListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int ScanCycleNo                READ getScanCycleNo                NOTIFY scanCycleDetailsListDataChanged)
    Q_PROPERTY(int ScanFreq                   READ getScanFreq                   NOTIFY scanCycleDetailsListDataChanged)
    Q_PROPERTY(int ScanMainParallelResFreq    READ getScanMainParallelResFreq    NOTIFY scanResonantFreqDataChanged)
    Q_PROPERTY(int ScanSecondParallelResFreq  READ getScanSecondParallelResFreq  NOTIFY scanResonantFreqDataChanged)
    Q_PROPERTY(int ScanThirdParallelResFreq   READ getScanThirdParallelResFreq   NOTIFY scanResonantFreqDataChanged)
    Q_PROPERTY(int ScanMainSeriesResFreq      READ getScanMainSeriesResFreq      NOTIFY scanResonantFreqDataChanged)
    Q_PROPERTY(int ScanSecondSeriesResFreq    READ getScanSecondSeriesResFreq    NOTIFY scanResonantFreqDataChanged)
    Q_PROPERTY(int ScanThirdSeriesResFreq     READ getScanThirdSeriesResFreq     NOTIFY scanResonantFreqDataChanged)

    Q_PROPERTY(int ScanFreqStep           READ getScanFreqStep           WRITE updateScanFreqStep         NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(int ScanMaxAmplitude       READ getScanMaxAmplitude       WRITE updateScanMaxAmplitude     NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(int ScanMaxCurrent         READ getScanMaxCurrent         WRITE updateScanMaxCurrent       NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(bool ScanSetDigitalTune    READ getScanSetDigitalTune     WRITE updateScanSetDigitalTune   NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(int ScanStartFrequency     READ getScanStartFrequency     WRITE updateScanStartFrequency   NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(int ScanStopFrequency      READ getScanStopFrequency      WRITE updateScanStopFrequency    NOTIFY scanRecipeDataChanged)
    Q_PROPERTY(float ScanTimeDelay          READ getScanTimeDelay          WRITE updateScanTimeDelay        NOTIFY scanRecipeDataChanged)

    Q_PROPERTY(bool ScanRunStatus READ getScanRunStatus  WRITE updateScanRunStatus  NOTIFY scanRunStatusDataChanged)


private:

    static size_t m_Sclog_id;

    bool m_StartHornScan;
    bool m_AbortHornScan;
    int  m_ScanCycleNo;
    int  m_ScanFreq;
    int  m_ScanMainParallelResFreq;
    int  m_ScanSecondParallelResFreq;
    int  m_ScanThirdParallelResFreq;
    int  m_ScanMainSeriesResFreq;
    int  m_ScanSecondSeriesResFreq;
    int  m_ScanThirdSeriesResFreq;

    int  m_ScanFreqStep;
    int  m_ScanMaxAmplitude;
    int  m_ScanMaxCurrent;
    bool m_ScanSetDigitalTune;
    int  m_ScanStartFrequency;
    int  m_ScanStopFrequency;
    float  m_ScanTimeDelay;
    float m_ScanRunStatus = false;

public:

    enum CycleRoles
    {
        IndexRole = Qt::UserRole + 1,
        CycleIndexRole,
        CycleDateTimeRole,
    };

    explicit ScanCycleDetailsListModel(QObject *parent = nullptr);
    ~ScanCycleDetailsListModel();

    Q_INVOKABLE void startHornScan(bool Value);
    Q_INVOKABLE void abortHornScan(bool Value);

    int getScanCycleNo() const;
    int getScanFreq() const;
    int getScanMainParallelResFreq() const;
    int getScanSecondParallelResFreq() const;
    int getScanThirdParallelResFreq() const;
    int getScanMainSeriesResFreq() const;
    int getScanSecondSeriesResFreq() const;
    int getScanThirdSeriesResFreq() const;

    int getScanFreqStep() const;
    void updateScanFreqStep(const int& ScanFreqStep);

    int getScanMaxAmplitude() const;
    void updateScanMaxAmplitude(const int& ScanMaxAmplitude);

    int getScanMaxCurrent() const;
    void updateScanMaxCurrent(const int& ScanMaxCurrent);

    bool getScanSetDigitalTune() const;
    void updateScanSetDigitalTune(const bool& ScanSetDigitalTune);

    int getScanStartFrequency() const;
    void updateScanStartFrequency(const int& ScanStartFrequency);

    int getScanStopFrequency() const;
    void updateScanStopFrequency(const int& ScanStopFrequency);

    float getScanTimeDelay() const;
    void updateScanTimeDelay(const float& ScanTimeDelay);

    float getScanRunStatus() const;
    void updateScanRunStatus(const float& ScanRunStatus);

    enum SEEK_PARAMETERS_ENUMS
    {
        NONE_IDX = -1,
        SCAN_FREQ_STEP,
        SCAN_MAX_AMPLITUDE,
        SCAN_MAX_CURRENT,
        SCAN_START_FREQUENCY,
        SCAN_STOP_FREQUENCY,
        SCAN_TIME_DELAY
    };

    Q_INVOKABLE void isScreenReNavigated(bool Value);
    Q_INVOKABLE QString getMinScanParametersValue(int Type);
    Q_INVOKABLE QString getMaxScanParametersValue(int Type);
    Q_INVOKABLE void onSavedPressed();
    Q_INVOKABLE void onResetToDefaultPressed();
    Q_INVOKABLE void onScanRecipeScreenReNavigated();
    Q_INVOKABLE void getResonantFrequencies(int Index);

    QSettings settings;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;

    Q_INVOKABLE void loadCycleDetailsList();
    Q_INVOKABLE bool isLastScanResultUpdated();

    /*List of geter API's for graph's subscreens*/
    HornScanSignature* getScanSignatureACE();


protected:
    QHash<int, QByteArray> roleNames() const override;

private:

    int m_Counter = 0;

    QList<ScanCycleDetailsListData*> m_ListData;

    void createNewCycleDetailsList();
    void clearCycleDetailsList();
    void addNewCycleDetailsList(ScanCycleDetailsListData *ScanCycleDetailsList);

    int m_ActiveWelderId = -1;
    HornScanResult *m_ScanResult;
    HornScanSignature *m_ScanSignature;
    HornScanRecipe *m_ScanRecipe;

    std::deque<HornScanResultstruct> m_ScanResultData;
    structHornScanRecipe m_scanRecipeData, m_ScanRecipeDataLocal;

    pthread_mutex_t mtx;    
    bool m_IsLastScanResultUpdated;
    bool m_IsScreenReNavigated = false;

    bool areRecipeValuesEqual(const structHornScanRecipe &ScanRecipestruct_1, const structHornScanRecipe &ScanRecipestruct_2);

    /*Signals used to notify qml screen*/
signals:
    void scanCycleDetailsListDataChanged();
    void scanResonantFreqDataChanged();
    void scanRecipeDataChanged();
    void scanRunStatusDataChanged();
    void scanDataChanged();
    void areScanRecipeValuesEqual(bool Value);
    void initiateScanGraphSignatureDisplay(int CycleCountNo, bool Value);

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnCycleDetailsListUpdated(HornScanResult *DiagnosticsScanResultScreen_Obj, HornScanSignature *DiagnosticsScanSignatureScreen_Obj, HornScanRecipe *DiagnosticsScanRecipeScreen_Obj,
                                   int WelderId);
};
#endif // SCANCYCLEDETAILSLIST_H

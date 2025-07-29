/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    CycleDetailsListModel.h file handles cycle details list model container includes :
    cycle counts, date and time.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 11/10/2023 - Initial version.
***************************************************************************/
#ifndef CYCLEDETAILSLIST_H
#define CYCLEDETAILSLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QSettings>
#include "UpdateScreens.h"
#include "CycleDetailsListData.h"
#include "WeldResultAce.h"

class CycleDetailsListModel : public QAbstractListModel
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT   
    Q_PROPERTY(int SearchByCycleNo  READ getSearchByCycleNo  WRITE updateSearchByCycleNo NOTIFY cycleDetailsListDataChanged)
    Q_PROPERTY(float TriggerPoint   READ getTriggerPoint     /*WRITE updategetTriggerPoint*/ NOTIFY cycleDetailsListDataChanged)
    Q_PROPERTY(float WeldSonicPoint READ getWeldSonicPoint   /*WRITE updateWeldSonicPoint */ NOTIFY cycleDetailsListDataChanged)
    Q_PROPERTY(float HoldPoint      READ getHoldPoint        /*WRITE updateHoldPoint      */ NOTIFY cycleDetailsListDataChanged)
    Q_PROPERTY(int RecipeNumber      READ getRecipeNumberFunc NOTIFY currentIndexUpdated)
    Q_PROPERTY(int RecipeVersion      READ getRecipeVersionFunc NOTIFY currentIndexUpdated)

public:
    enum CycleRoles
    {
        IndexRole = Qt::UserRole + 1,
        CycleIndexRole,
        CycleRecipeNoRole,
        CycleNoRole,
        CycleWeldModeRole,
        CycleDateTimeRole,
        CycleTriggerPointRole,
        CycleWeldSonicPointRole,
        CycleHoldPointRole,
        CycleWeldResultIdxRole
    };



public:
    explicit CycleDetailsListModel(QObject *parent = nullptr);
    ~CycleDetailsListModel();

    QSettings settings;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;
    int m_modelListCurrIndex=0;
    Q_INVOKABLE int getCurrentIndex();
    Q_INVOKABLE void updateCurrentIndex(int currentIndex);
    Q_INVOKABLE void loadCycleDetailsList();
    Q_INVOKABLE bool isLastWeldResultUpdated();
    Q_INVOKABLE bool isAutoRefreshGraph();
    Q_INVOKABLE void autoRefreshGraphRequest(bool value);
    Q_INVOKABLE void isScreenReNavigated(bool value);
    Q_INVOKABLE void isScreenNavigatedFromResultsBtn(bool value, int tar);

    float getTriggerPoint();
    Q_INVOKABLE void updateTriggerPoint(float TriggerPoint);

    float getWeldSonicPoint();
    Q_INVOKABLE void updateWeldSonicPoint(float WeldSonicPoint);

    float getHoldPoint();
    Q_INVOKABLE void updateHoldPoint(float HoldPoint);

    Q_INVOKABLE int getWeldResultIndex(int Value);

    Q_INVOKABLE int getRecipeNumber(int Value);

    Q_INVOKABLE int getRecipeVersion(int Value);

    /*List of geter API's for graph's subscreens*/
    WeldSignatureACE* getWeldSignatureACE();


protected:
    QHash<int, QByteArray> roleNames() const override;

private:

    int m_Counter = 0;

    /*List of private varibles used by methods under RecipeLabData class*/
    int m_SearchByCycleNo;
    float m_SelectedTriggerPoint;
    float m_SelectedWeldSonicPoint;
    float m_SelectedHoldPoint;
    int m_AlarmCycleNumber;

    /*List of get and set functions to update qml variables*/
    int getSearchByCycleNo() const;
    void updateSearchByCycleNo(const int& SearchByCycleNo);

    int getRecipeNumberFunc();
    int getRecipeVersionFunc();
    bool  doesCycleCounterExist(int cycleNum);

    QList<CycleDetailsListData*> m_ListData;

    void createNewCycleDetailsList();
    void clearCycleDetailsList();
    void addNewCycleDetailsList(CycleDetailsListData *CycleDetailsList);

    int m_ActiveWelderId = -1;
    WeldResultACE *m_WeldResultACE;
    WeldSignatureACE *m_WeldSignatureACE;

    std::deque<WeldResultACEStruct> m_WeldResultData;
    pthread_mutex_t mtx;
    bool m_IsLastWeldResultUpdated;
    bool m_IsScreenReNavigated = false;
    bool m_IsScreenReNavigatedFrmResultBtn = false;


    /*Signals used to notify qml screen*/
signals:
    void cycleDetailsListDataChanged();
    void initiateWeldGraphSignatureDisplay(int CycleCountNo, bool Value);
    void currentIndexUpdated();
    void cycleNumberAlarmDataChanged();
    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnCycleDetailsListUpdated(WeldResultACE *AnlyticsGraphScreenWeldResult_Obj, WeldSignatureACE *AnlyticsGraphScreenWeldSignature_Obj, int WelderId);
};
#endif // CYCLEDETAILSLIST_H

/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares SystemGeneral class - which is responsible to do interaction between frontend and backend .

--------------------------- REVISION HISTORY ------------------------------
 rev1: 15-09-2023

***************************************************************************/
#ifndef UTILITY_H 
#define UTILITY_H

#include <QObject>
#include <QString>
#include "UpdateScreens.h"
#include "SysConfgGenStructureAce.h"


class SystemGeneral: public QObject
{
    // Declaration of Q_OBJECT for signals and slots mechanism
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(int Unit                READ getUnit                  WRITE updateUnit                 NOTIFY sysConfigDataChanged)
    Q_PROPERTY(QString WelderName      READ getWelderName            WRITE updateWelderName           NOTIFY sysConfigDataChanged)
    Q_PROPERTY(int MemoryfullAction    READ getMemoryfullAction      WRITE updateMemoryfullAction     NOTIFY sysConfigDataChanged)
    Q_PROPERTY(int AuthorityChk        READ getAuthorityChk          WRITE updateAuthorityChk         NOTIFY sysConfigDataChanged)
    Q_PROPERTY(QString Key             READ getKey                   WRITE updateKey                  NOTIFY sysConfigDataChanged)
    Q_PROPERTY(QString BarcodeRecallRecipePrefix      READ getBarcodeRecallRecipePrefix            WRITE updateBarcodeRecallRecipePrefix           NOTIFY sysConfigDataChanged)
    Q_PROPERTY(int PowerUpOption       READ getPowerupOption         WRITE updatePowerupOption        NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool PartID                  READ getPartID                   WRITE updatePartID                  NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool MemeoryClearAtPowerup   READ getMemeoryClearAtPowerup    WRITE updateMemeoryClearAtPowerup   NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool MemoryClearReset        READ getMemoryClearReset         WRITE updateMemoryClearReset        NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool KeyVerifyStatus        READ getKeyVerifyStatus  NOTIFY keyVerifiedDataChanged)
    Q_PROPERTY(bool ParallelWeldResultStorageStatus READ getParallelWeldResultStorageStatus WRITE updateParallelWeldResultStorageStatus NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool Clampon                  READ getClampon                   WRITE updateClampon                  NOTIFY sysConfigDataChanged)
    Q_PROPERTY(bool UniqueWeldRecipeStatus  READ getUniqueWeldRecipeStatus    WRITE updateUniqueWeldRecipeStatus    NOTIFY sysConfigDataChanged)
    Q_PROPERTY(QString IpAddress       READ getipAddress         WRITE updateipAddress        NOTIFY sysConfigDataChanged)


private:

    int m_Unit ;                                  /* Variable to store unit value                      */
    QString m_WelderName;                        /* Variable to store active welder Name              */
    int m_MemoryfullAction=-1;                  /* Variable to store option for memory full action   */
    int m_AuthorityChk=-1;                     /* Variable to store AuthorityCheck value            */
    QString m_Key;                            /* Variable to store unit value                      */
    int m_ActiveWelderId = -1;               /* Variable to store active Welder Id                */
    QString m_BarcodeRecallRecipePrefix;    /* Variable to store BarcodeRecallRecipePrefix value */
    int m_PowerUpOption =-1;               /* Variable to store PowerUpOption value             */
    bool m_PartID;                        /* Variable to store PartID status                   */
    bool m_MemeoryClearAtPowerup;        /* Variable to store clearmemory at power up status  */
    bool m_MemoryClearReset;            /* Variable to store memory clear status             */
    bool m_IsKeyVerified;
    bool m_ParallelWeldResultStorageStatus;  /* Variable to store Parallel Weld Result Storage status             */
    bool m_Clampon;                         /* Variable to store Clampon status                 */
    bool m_UniqueWeldRecipeStatus;         /* Variable to store UNiqueWeldRecipeNumber status  */

    SystemConfigurationGeneral_MB * m_SysConfgGen;           /* Pointer of SystemConfigurationGeneral_MB class */
    SystemConfigGeneralStruct m_SystemConfigGeneralStruct;  /* Instance of SystemConfigGeneralStruct structure*/

    /* To verify the data with min and max values before sending to database. */
    static bool VerifySysConfgGeneralParameter(SystemConfigGeneralStruct systemConfigGeneralStruct);

    QString m_ipAddress;                              /*Variable to store IPAddress in qstring type*/
    ASC_IP_ADDRESS_FOR_HMI m_ASC_IP_ADDRESS_FOR_HMI; /*Used to store enum value for ASC_IP_ADDRESS from HMI*/

public:
    //Constructor
    explicit SystemGeneral(QObject *parent = nullptr);

    /*List of get and set functions to update qml variables*/
    int getUnit() const;
    void updateUnit(const int& Unit);

    QString getWelderName() const;
    void updateWelderName(const QString &WelderName);

    int getMemoryfullAction() const;
    void updateMemoryfullAction(int MemoryfullAction);

    int getAuthorityChk() const;
    void updateAuthorityChk(int AuthorityChk);

    QString getKey() const;
    void updateKey(const QString &Key);

    QString getBarcodeRecallRecipePrefix() const;
    void updateBarcodeRecallRecipePrefix(const QString &BarcodeRecallRecipePrefix);

    /*Function to fill the data in structure */
    void dataUpdateRequestToDB();

    int getPowerupOption() const;
    void updatePowerupOption(int newPowerupOption);

    bool getPartID() const;
    void updatePartID(const bool &newPartID);

    bool getMemeoryClearAtPowerup() const;
    void updateMemeoryClearAtPowerup(const bool &newMemeoryClearAtPowerup);

    bool getMemoryClearReset() const;
    void updateMemoryClearReset(const bool &newMemoryClearReset);

    bool getKeyVerifyStatus()const;

    bool getParallelWeldResultStorageStatus() const;
    void updateParallelWeldResultStorageStatus(const bool & parallelWeldResultStorageStatus);

    bool getClampon() const;
    void updateClampon(const bool & newClampon);

    bool getUniqueWeldRecipeStatus() const;
    void updateUniqueWeldRecipeStatus(bool newUniqueWeldRecipeStatus);

    Q_INVOKABLE void resetToDefaultRequest();
    Q_INVOKABLE void keyVerifyRequest();
    Q_INVOKABLE int maxWelderNameLength();
    Q_INVOKABLE void cancelRequestFromHMI();

    Q_INVOKABLE void resrtBrsnSrvcKeyRequestFromHMI();
    Q_INVOKABLE QString getIpAddressForComboboxModel(int i);
    Q_INVOKABLE int maxIpAddressInMap();

    QString getipAddress() const;
    void updateipAddress(QString newIpAddress);

signals:
    /* Send signal to HMI on Data update */
    void sysConfigDataChanged();

    void keyVerifiedDataChanged();
    void keyResetNotify();

public slots:
    /*Slot to notify SystemGeneral class about data updated on HMI.*/
    void changeRequestFromHMI();

    /*Slot to get selected unit from HMI.*/
    void getHMIUnit(int a);

private slots:
    /*Slot to be called when data update signal generated by communication thread*/
    void OnSysConfgGenScreenUpdated(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId);
};

#endif // UTILITY_H

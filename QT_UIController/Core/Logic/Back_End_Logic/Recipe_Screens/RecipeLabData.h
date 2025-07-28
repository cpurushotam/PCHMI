/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file includes Recipe Lab Screen qml variables declarations.
--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/08/2023 - Initial version.
***************************************************************************/
#ifndef RECIPELABDATA_H
#define RECIPELABDATA_H

#include <QObject>
#include "UpdateScreens.h"
#include "WeldRecipeAce.h"

class RecipeLabData : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT
    Q_PROPERTY(int WeldRecipeNumber          READ getWeldRecipeNumber        WRITE updateWeldRecipeNumber        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int WeldRecipeVersionNumber   READ getWeldRecipeVersionNumber WRITE updateWeldRecipeVersionNumber NOTIFY recipeLabDataChanged)
    Q_PROPERTY(QString WeldRecipeName        READ getWeldRecipeName          WRITE updateWeldRecipeName          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int WeldMode                  READ getWeldMode                WRITE updateWeldMode                NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValueTime           READ getModeValueTime           WRITE updateModeValueTime           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValueEnergy         READ getModeValueEnergy         WRITE updateModeValueEnergy         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValuePeakPower      READ getModeValuePeakPower      WRITE updateModeValuePeakPower      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValueGroundDetect   READ getModeValueGroundDetect   WRITE updateModeValueGroundDetect   NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValueAbsDistance    READ getModeValueAbsDistance    WRITE updateModeValueAbsDistance    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ModeValueColDistance    READ getModeValueColDistance    WRITE updateModeValueColDistance    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int CycleCount                READ getCycleCount              WRITE updateCycleCount              NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int CyclesOKCount             READ getCyclesOKCount           WRITE updateCyclesOKCount           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int RejectCount               READ getRejectCount             WRITE updateRejectCount             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float WeldPressure            READ getWeldPressure            WRITE updateWeldPressure            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int NumPressureSteps          READ getNumPressureSteps        WRITE updateNumPressureSteps        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int PressureStepAt            READ getPressureStepAt          WRITE updatePressureStepAt          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float HoldPressure            READ getHoldPressure            WRITE updateHoldPressure            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float FlowRate                READ getFlowRate                WRITE updateFlowRate                NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float HoldTime                READ getHoldTime                WRITE updateHoldTime                NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float MaxWeldTimeout          READ getMaxWeldTimeout          WRITE updateMaxWeldTimeout          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int WeldAmplitude             READ getWeldAmplitude           WRITE updateWeldAmplitude           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int NumAmplitudeSteps         READ getNumAmplitudeSteps       WRITE updateNumAmplitudeSteps       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int AmplitudeStepAt           READ getAmplitudeStepAt         WRITE updateAmplitudeStepAt         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float TriggerForce            READ getTriggerForce            WRITE updateTriggerForce            NOTIFY recipeLabDataChanged)

    /*******************************Recipe Limits Suspect & Reject********************************/
    Q_PROPERTY(bool IsGlobalSuspect        READ getIsGlobalSuspect       WRITE updateIsGlobalSuspect       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsGlobalReject         READ getIsGlobalReject        WRITE updateIsGlobalReject        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsSuspectTime          READ getIsSuspectTime         WRITE updateIsSuspectTime         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsSuspectEnergy        READ getIsSuspectEnergy       WRITE updateIsSuspectEnergy       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsSuspectPeakPower     READ getIsSuspectPeakPower    WRITE updateIsSuspectPeakPower    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsSuspectFrequency     READ getIsSuspectFrequency    WRITE updateIsSuspectFrequency    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsRejectTime           READ getIsRejectTime          WRITE updateIsRejectTime          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsRejectEnergy         READ getIsRejectEnergy        WRITE updateIsRejectEnergy        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsRejectPeakPower      READ getIsRejectPeakPower     WRITE updateIsRejectPeakPower     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsRejectFrequency      READ getIsRejectFrequency     WRITE updateIsRejectFrequency     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectLowTime        READ getSuspectLowTime        WRITE updateSuspectLowTime        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighTime       READ getSuspectHighTime       WRITE updateSuspectHighTime       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectLowEnergy      READ getSuspectLowEnergy      WRITE updateSuspectLowEnergy      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighEnergy     READ getSuspectHighEnergy     WRITE updateSuspectHighEnergy     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectLowPeakPower   READ getSuspectLowPeakPower   WRITE updateSuspectLowPeakPower   NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighPeakPower  READ getSuspectHighPeakPower  WRITE updateSuspectHighPeakPower  NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectLowFrequency   READ getSuspectLowFrequency   WRITE updateSuspectLowFrequency   NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighFrequency  READ getSuspectHighFrequency  WRITE updateSuspectHighFrequency  NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowTime         READ getRejectLowTime         WRITE updateRejectLowTime         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighTime        READ getRejectHighTime        WRITE updateRejectHighTime        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowEnergy       READ getRejectLowEnergy       WRITE updateRejectLowEnergy       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighEnergy      READ getRejectHighEnergy      WRITE updateRejectHighEnergy      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowPeakPower    READ getRejectLowPeakPower    WRITE updateRejectLowPeakPower    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighPeakPower   READ getRejectHighPeakPower   WRITE updateRejectHighPeakPower   NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowFrequency    READ getRejectLowFrequency    WRITE updateRejectLowFrequency    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighFrequency   READ getRejectHighFrequency   WRITE updateRejectHighFrequency   NOTIFY recipeLabDataChanged)

    Q_PROPERTY(bool IsAbsDistSuspect         READ getIsAbsDistSuspect        WRITE updateIsAbsDistSuspect         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsAbsDistReject          READ getIsAbsDistReject         WRITE updateIsAbsDistReject          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsCollapseDistSuspect         READ getIsCollapseDistSuspect        WRITE updateIsCollapseDistSuspect         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsCollapseDistReject          READ getIsCollapseDistReject         WRITE updateIsCollapseDistReject          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsTriggerDistSuspect     READ getIsTriggerDistSuspect    WRITE updateIsTriggerDistSuspect     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsTriggerDistReject      READ getIsTriggerDistReject     WRITE updateIsTriggerDistReject      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsVelocitySuspect        READ getIsVelocitySuspect       WRITE updateIsVelocitySuspect        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsVelocityReject         READ getIsVelocityReject        WRITE updateIsVelocityReject         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsEndWeldForceSuspect        READ getIsEndWeldForceSuspect       WRITE updateIsEndWeldForceSuspect        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsEndWeldForceReject         READ getIsEndWeldForceReject        WRITE updateIsEndWeldForceReject         NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float SuspectLowAbsDist          READ getSuspectLowAbsDist          WRITE updateSuspectLowAbsDist          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighAbsDist         READ getSuspectHighAbsDist         WRITE updateSuspectHighAbsDist         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowAbsDist          READ getRejectLowAbsDist          WRITE updateRejectLowAbsDist          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighAbsDist         READ getRejectHighAbsDist         WRITE updateRejectHighAbsDist         NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float SuspectLowCollapseDist        READ getSuspectLowCollapseDist        WRITE updateSuspectLowCollapseDist        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighCollapseDist       READ getSuspectHighCollapseDist       WRITE updateSuspectHighCollapseDist       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowCollapseDist        READ getRejectLowCollapseDist        WRITE updateRejectLowCollapseDist        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighCollapseDist       READ getRejectHighCollapseDist       WRITE updateRejectHighCollapseDist       NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float SuspectLowTriggerDist        READ getSuspectLowTriggerDist        WRITE updateSuspectLowTriggerDist        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighTriggerDist       READ getSuspectHighTriggerDist       WRITE updateSuspectHighTriggerDist       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowTriggerDist        READ getRejectLowTriggerDist        WRITE updateRejectLowTriggerDist        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighTriggerDist       READ getRejectHighTriggerDist       WRITE updateRejectHighTriggerDist       NOTIFY recipeLabDataChanged)


    Q_PROPERTY(float SuspectLowVelocity        READ getSuspectLowVelocity        WRITE updateSuspectLowVelocity        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighVelocity       READ getSuspectHighVelocity       WRITE updateSuspectHighVelocity       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowVelocity        READ getRejectLowVelocity          WRITE updateRejectLowVelocity        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighVelocity       READ getRejectHighVelocity         WRITE updateRejectHighVelocity       NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float SuspectLowEndWeldForce        READ getSuspectLowEndWeldForce        WRITE updateSuspectLowEndWeldForce        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float SuspectHighEndWeldForce       READ getSuspectHighEndWeldForce       WRITE updateSuspectHighEndWeldForce       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectLowEndWeldForce        READ getRejectLowEndWeldForce        WRITE updateRejectLowEndWeldForce        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RejectHighEndWeldForce       READ getRejectHighEndWeldForce       WRITE updateRejectHighEndWeldForce       NOTIFY recipeLabDataChanged)

    /********************************************************************************************/

    Q_PROPERTY(bool IsRecipeSaved  READ getIsRecipeSaved NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsLoading      READ getIsLoading     WRITE updateIsLoading     NOTIFY loadingLabDataChanged)
    Q_PROPERTY(bool IsParamValid   READ getIsParamValid  WRITE updateIsParamValid  NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Weld Process (Pretrigger and Afterburst)*/
    Q_PROPERTY(bool PretriggerEnable       READ getPretriggerEnable        WRITE updatePretriggerEnable        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int PretriggerAmplitude     READ getPretriggerAmplitude     WRITE updatePretriggerAmplitude     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float PretriggerDistance    READ getPretriggerDistance      WRITE updatePretriggerDistance      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float PretriggerTime        READ getPretriggerTime          WRITE updatePretriggerTime          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int PretriggerType          READ getPretriggerType          WRITE setPretriggerType             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool AfterburstEnable       READ getAfterburstEnable        WRITE updateAfterburstEnable        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int AfterburstAmplitude     READ getAfterburstAmplitude     WRITE updateAfterburstAmplitude     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float AfterburstDelay       READ getAfterburstDelay         WRITE updateAfterburstDelay         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float AfterburstTime        READ getAfterburstTime          WRITE updateAfterburstTime          NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Stack Recipe*/
    Q_PROPERTY(int DigitalTune             READ getDigitalTune             WRITE updateDigitalTune             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int InternalFreqOffset      READ getInternalFreqOffset      WRITE updateInternalFreqOffset      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool EndOfWeldStore         READ getEndOfWeldStore          WRITE updateEndOfWeldStore          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool FrequencyOffset        READ getFrequencyOffset         WRITE updateFrequencyOffset         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  FrequencyLow           READ getFrequencyLow            WRITE updateFrequencyLow             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  FrequencyHigh          READ getFrequencyHigh           WRITE updateFrequencyHigh            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float WeldRampTime          READ getWeldRampTime            WRITE updateWeldRampTime             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  MemoryOffset           READ getMemoryOffset            WRITE updateMemoryOffset             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ClearMemoryAtPowerUp   READ getClearMemoryAtPowerUp    WRITE updateClearMemoryAtPowerUp     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ClearMemoryWithReset   READ getClearMemoryWithReset    WRITE updateClearMemoryWithReset     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float PhaseLimitTime        READ getPhaseLimitTime          WRITE updatePhaseLimitTime           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  PhaseLimit             READ getPhaseLimit              WRITE updatePhaseLimit               NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  ControlMode            READ getControlMode             WRITE updateControlMode              NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float  BlindTimeWeld        READ getBlindTimeWeld           WRITE updateBlindTimeWeld            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  AmpProportionalGain    READ getAmpProportionalGain     WRITE updateAmpProportionalGain      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  AmpIntegralGain        READ getAmpIntegralGain         WRITE updateAmpIntegralGain          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  AmpDerivativeGain      READ getAmpDerivativeGain       WRITE updateAmpDerivativeGain        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  PhaseProportionalGain  READ getPhaseProportionalGain   WRITE updatePhaseProportionalGain    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  PhaseIntegralGain      READ getPhaseIntegralGain       WRITE updatePhaseIntegralGain        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int  PhaseDerivativeGain    READ getPhaseDerivativeGain     WRITE updatePhaseDerivativeGain      NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used to check if Branson Only Login is done or not */
    Q_PROPERTY(bool BransonOnlyLogin       READ getBransonOnlyLogin        WRITE updateBransonOnlyLogin         NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Parameter A-Z Screen*/
    Q_PROPERTY(bool EnergyBraking          READ getEnergyBraking           WRITE updateEnergyBraking           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int EnergyBrakeAmplitude    READ getEnergyBrakeAmplitude    WRITE updateEnergyBrakeAmplitude    NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float EnergyBrakeTime       READ getEnergyBrakeTime         WRITE updateEnergyBrakeTime         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool PreWeldSeek            READ getPreWeldSeek             WRITE updatePreWeldSeek             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool PostWeldSeek           READ getPostWeldSeek            WRITE updatePostWeldSeek            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ExtraCooling           READ getExtraCooling            WRITE updateExtraCooling            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ActuatorClear          READ getActuatorClear           WRITE updateActuatorClear           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ActuatorClearTime     READ getActuatorClearTime       WRITE updateActuatorClearTime       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ActuatorClearDistance    READ getActuatorClearDistance     WRITE updateActuatorClearDistance       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int ActuatorClearType          READ getActuatorClearType          WRITE setActuatorClearType             NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float HoldForceRamp         READ getHoldForceRamp           WRITE updateHoldForceRamp           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool RapidTraverse          READ getRapidTraverse           WRITE updateRapidTraverse           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float RapidTraverseDistance READ getRapidTraverseDistance   WRITE updateRapidTraverseDistance   NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool TriggerLost            READ getTriggerLost             WRITE updateTriggerLost             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ExternalAmplitudeSetting        READ getExternalAmplitudeSetting         WRITE updateExternalAmplitudeSetting         NOTIFY recipeLabDataChanged)

    Q_PROPERTY(float TriggerTypeForce       READ getTriggerTypeForce        WRITE updateTriggerTypeForce          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float TriggerTypeDistance    READ getTriggerTypeDistance     WRITE updateTriggerTypeDistance       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int TriggerType              READ getTriggerType             WRITE updateTriggerType               NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool IsTimeSeekEnable        READ getIsTimeSeekEnable        WRITE updateIsTimeSeekEnable          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float TimeSeekPeriod         READ getTimeSeekPeriod          WRITE updateTimeSeekPeriod            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int ScrubAmplitude           READ getScrubAmplitude          WRITE updateScrubAmplitude            NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Control Screen*/
    Q_PROPERTY(bool CutoffLimtsEnable         READ getCutoffLimtsEnabled      WRITE updateCutoffLimtsEnabled          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool PeakPowerCuttOffEnabled   READ getPeakPowerCuttOffEnabled WRITE updatePeakPowerCuttOffEnabled     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float PeakPowerCuttoffValue    READ getPeakPowerCuttoffValue   WRITE updatePeakPowerCuttoffValue       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool TimeCuttoffEnable         READ getTimeCuttoff             WRITE updateTimeCuttoff                 NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float TimeCuttoffValue         READ getTimeCuttoffValue        WRITE updateTimeCuttoffValue            NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool FreqLowCuttoffEnable      READ getFreqLowCuttoff          WRITE updateFreqLowCuttoff              NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float FreqLowCuttoffValue      READ getFreqLowCuttoffValue     WRITE updateFreqLowCuttoffValue         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool FreqHighCuttoffEnable     READ getFreqHighCuttoff         WRITE updateFreqHighCuttoff             NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float FreqHighCuttoffValue     READ getFreqHighCuttoffValue    WRITE updateFreqHighCuttoffValue        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool EnergyCuttoffEnable       READ getEnergyCuttoff           WRITE updateEnergyCuttoff               NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float EnergyCuttoffValue       READ getEnergyCuttoffValue      WRITE updateEnergyCuttoffValue          NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool GroundDetectCuttoffEnable READ getGroundDetectCuttoff       WRITE updateGroundDetectCuttoff       NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float GroundDetectCuttoffValue READ getGroundDetectCuttoffValue  WRITE updateGroundDetectCuttoffValue  NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool ABSDistanceCutoffEnable   READ getABSDistanceCutoff       WRITE updateABSDistanceCutoff           NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float ABSDistanceCutoffValue   READ getABSDistanceCutoffValue  WRITE updateABSDistanceCutoffValue      NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool CollapseDistanceCutoffEnable  READ getCollapseDistanceCutoff       WRITE updateCollapseDistanceCutoff     NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float CollapseDistanceCutoffValue  READ getCollapseDistanceCutoffValue  WRITE updateCollapseDistanceCutoffValue  NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Batch Setting Screen*/
    Q_PROPERTY(bool BatchSetup            READ getBatchSetup          WRITE updateBatchSetup              NOTIFY recipeLabDataChanged)
    Q_PROPERTY(bool CountWithAlarms       READ getCountWithAlarms     WRITE updateCountWithAlarms         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int BatchCounterLimit        READ getBatchCounterLimit     WRITE updateBatchCounterLimit         NOTIFY recipeLabDataChanged)
    Q_PROPERTY(QString BatchId            READ getBatchId             WRITE updateBatchId                 NOTIFY recipeLabDataChanged)
    Q_PROPERTY(int BatchCounter            READ getBatchCounter          WRITE updateBatchCounter              NOTIFY recipeLabDataChanged)

    /*Q_PROPERTY macro is used for declaring properties in Energy Compensation Screen*/
    Q_PROPERTY(bool EnergyCompensation            READ getEnergyCompensation          WRITE updateEnergyCompensation              NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float EnergyCompensationLowVal     READ getEnergyCompensationLowVal    WRITE updateEnergyCompensationLowVal        NOTIFY recipeLabDataChanged)
    Q_PROPERTY(float EnergyCompensationHighVal    READ getEnergyCompensationHighVal   WRITE updateEnergyCompensationHighVal       NOTIFY recipeLabDataChanged)

private:

    /*List of private varibles used by methods under RecipeLabData class*/
    int m_WeldRecipeNumber;
    int m_WeldRecipeVersionNumber;
    QString m_WeldRecipeName;
    int m_WeldMode;
    float m_ModeValueTime;
    float m_ModeValueEnergy;
    float m_ModeValuePeakPower;
    float m_ModeValueGroundDetect;
    float m_ModeValueAbsDistance;
    float m_ModeValueColDistance;
    int m_CycleCount;
    int m_CyclesOKCount;
    int m_RejectCount;
    float m_WeldPressure;
    int m_NumPressureSteps;
    float m_PressureStepAt;
    float m_HoldPressure;
    float m_FlowRate;
    float m_HoldTime;
    float m_MaxWeldTimeout;
    int m_WeldAmplitude;
    int m_NumAmplitudeSteps;
    int m_AmplitudeStepAt;
    bool m_IsRecipeSaved;

    WeldRecipeACE *m_RecipeLabData;
    AmplitudeStepDataACE m_AmplitudeStepDataACE;
    PressureStepDataACE m_PressureStepDataACE;
    /*******************************Recipe Limits Suspect & Reject********************************/
    bool m_IsGlobalSuspect;
    bool m_IsGlobalReject ;
    bool m_IsSuspectTime;
    bool m_IsSuspectEnergy;
    bool m_IsSuspectPeakPower;
    bool m_IsSuspectFrequency;
    bool m_IsRejectTime;
    bool m_IsRejectEnergy;
    bool m_IsRejectPeakPower;
    bool m_IsRejectFrequency;

    float m_SuspectLowTime;
    float m_SuspectHighTime;
    float m_SuspectLowEnergy;
    float m_SuspectHighEnergy;
    float m_SuspectLowPeakPower;
    float m_SuspectHighPeakPower;
    float m_SuspectLowFrequency;
    float m_SuspectHighFrequency;
    float m_RejectLowTime;
    float m_RejectHighTime;
    float m_RejectLowEnergy;
    float m_RejectHighEnergy;
    float m_RejectLowPeakPower;
    float m_RejectHighPeakPower;
    float m_RejectLowFrequency;
    float m_RejectHighFrequency;

    bool m_IsAbsDistSuspect;
    bool m_IsAbsDistReject;
    bool m_IsTriggerDistSuspect;
    bool m_IsTriggerDistReject;
    bool m_IsVelocitySuspect;
    bool m_IsVelocityReject;
    bool m_IsEndWeldForceSuspect;
    bool m_IsEndWeldForceReject;
    bool m_IsCollapseDistSuspect;
    bool m_IsCollapseDistReject;

    float m_SuspectLowAbsDist;
    float m_SuspectHighAbsDist;
    float m_RejectLowAbsDist;
    float m_RejectHighAbsDist;
    float m_SuspectLowCollapseDist;
    float m_SuspectHighCollapseDist;
    float m_RejectLowCollapseDist;
    float m_RejectHighCollapseDist;
    float m_SuspectLowTriggerDist;
    float m_SuspectHighTriggerDist;
    float m_RejectLowTriggerDist;
    float m_RejectHighTriggerDist;
    float m_SuspectLowVelocity;
    float m_SuspectHighVelocity;
    float m_RejectLowVelocity;
    float m_RejectHighVelocity;
    float m_SuspectLowEndWeldForce;
    float m_SuspectHighEndWeldForce;
    float m_RejectLowEndWeldForce;
    float m_RejectHighEndWeldForce;



    /*********************************************************************************************/

    int m_ActiveWelderId = -1;
    bool m_IsLoadingFlag = false;
    bool m_IsParamValid = true;

    /*List of private varibles used by methods under RecipeLabData class Weld Process*/
    bool m_PretriggerEnable;
    int m_PretriggerAmplitude;
    float m_PretriggerDistance;
    float m_PretriggerTime;
    int m_PretriggerType;
    int m_AfterburstAmplitude;
    float m_AfterburstDelay;
    float m_AfterburstTime;
    bool m_AfterburstEnable;

    /*List of private varibles used by methods under RecipeLabData class Stack Recipe*/
    int m_DigitalTune ;
    int m_InternalFreqOffset;
    bool m_EndOfWeldStore;
    bool m_FrequencyOffset;
    int m_FrequencyLow;
    int m_FrequencyHigh;
    float m_WeldRampTime;
    int m_MemoryOffset;
    bool m_ClearMemoryAtPowerUp;
    bool m_ClearMemoryWithReset;
    float m_PhaseLimitTime;
    int m_PhaseLimit;
    int m_ControlMode;
    float m_BlindTimeWeld;
    int m_AmpProportionalGain;
    int m_AmpIntegralGain;
    int m_AmpDerivativeGain;
    int m_PhaseProportionalGain;
    int m_PhaseIntegralGain;
    int m_PhaseDerivativeGain;

    /*List of private varibles used by methods under RecipeLabData class Parameter A-Z*/
    bool m_EnergyBraking;
    int m_EnergyBrakeAmplitude;
    float m_EnergyBrakeTime;
    bool m_PreWeldSeek;
    bool m_PostWeldSeek;
    bool m_ExtraCooling;
    bool m_ActuatorClear;
    float m_HoldForceRamp;
    bool m_RapidTraverse;
    float m_RapidTraverseDistance;
    bool m_TriggerLost;
    float m_TriggerForce;
    float m_ActuatorClearTime;
    float m_ActuatorClearDistance;
    int m_ActuatorClearType;
    float m_TriggerTypeForce;
    float m_TriggerTypeDistance;
    int m_TriggerType;
    bool m_IsTimeSeekEnable;
    float m_TimeSeekPeriod;
    int m_ScrubAmplitude;

    /*List of private varibles used by methods under RecipeLabData class  Limits - Control */
    bool m_CutoffLimtsEnable;
    bool m_PeakPowerCuttOffEnabled;
    float m_PeakPowerCuttoffValue;
    bool m_TimeCuttoffEnable;
    float m_TimeCuttoffValue;
    bool m_FreqLowCuttoffEnable;
    float m_FreqLowCuttoffValue;
    bool m_FreqHighCuttoffEnable;
    float m_FreqHighCuttoffValue;
    bool m_EnergyCuttoffEnable;
    float m_EnergyCuttoffValue;
    bool m_GroundDetectCuttoffEnable;
    float m_GroundDetectCuttoffValue;
    bool m_ABSDistanceCutoffEnable;
    float m_ABSDistanceCutoffValue;
    bool m_CollapseDistanceCutoffEnable;
    float m_CollapseDistanceCutoffValue;

    bool m_BransonOnlyLogin = false;

    /*List of private varibles used by methods under RecipeLabData class Batch Setting */
    bool m_BatchSetup;
    bool m_CountWithAlarms;
    int m_BatchCounterLimit;
    int m_UpdatedBatchCounterLimit;
    QString m_BatchId;
    int m_BatchCounter;
    bool m_ExternalAmplitudeSetting;

    /*List of private varibles used by methods under RecipeLabData class Recipe Energy Compensation */
    bool m_EnergyCompensation;
    float m_EnergyCompensationLowVal;
    float m_EnergyCompensationHighVal;

public:

    explicit RecipeLabData(QObject *parent = nullptr);

    /*List of get and set functions to update qml variables*/
    int getWeldRecipeNumber() const;
    void updateWeldRecipeNumber(const int& WeldRecipeNumber);

    int getWeldRecipeVersionNumber() const;
    void updateWeldRecipeVersionNumber(const int& WeldRecipeVersionNumber);

    QString getWeldRecipeName() const;
    void updateWeldRecipeName(const QString WeldRecipeName);

    int getWeldMode() const;
    void updateWeldMode(const int& WeldMode);

    float getModeValueTime() const;
    void updateModeValueTime(const float& ModeValueTime);

    float getModeValueEnergy() const;
    void updateModeValueEnergy(const float& ModeValueEnergy);

    float getModeValuePeakPower() const;
    void updateModeValuePeakPower(const float& ModeValuePeakPower);

    float getModeValueGroundDetect() const;
    void updateModeValueGroundDetect(const float& ModeValueGroundDetect);

    float getModeValueAbsDistance() const;
    void updateModeValueAbsDistance(const float& ModeValueAbsDistance);

    float getModeValueColDistance() const;
    void updateModeValueColDistance(const float& ModeValueColDistance);

    int getCycleCount() const;
    void updateCycleCount(const int& CycleCount);

    int getCyclesOKCount() const;
    void updateCyclesOKCount(const int& CyclesOKCount);

    int getRejectCount() const;
    void updateRejectCount(const int& RejectCount);

    float getWeldPressure() const;
    void updateWeldPressure(const float& WeldPressure);

    int getNumPressureSteps() const;
    void updateNumPressureSteps(const int& NumPressureSteps);

    int getPressureStepAt() const;
    void updatePressureStepAt(const int& PressureStepAt);

    float getHoldPressure() const;
    void updateHoldPressure(const float& HoldPressure);

    float getFlowRate() const;
    void updateFlowRate(const float& FlowRate);

    float getHoldTime() const;
    void updateHoldTime(const float& HoldTime);

    float getMaxWeldTimeout() const;
    void updateMaxWeldTimeout(const float& MaxWeldTimeout);

    int getWeldAmplitude() const;
    void updateWeldAmplitude(const int& WeldAmplitude);

    int getNumAmplitudeSteps() const;
    void updateNumAmplitudeSteps(const int& NumAmplitudeSteps);

    int getAmplitudeStepAt() const;
    void updateAmplitudeStepAt(const int& AmplitudeStepAt);

    bool getIsRecipeSaved() const;

    bool getIsLoading() const;
    void updateIsLoading(const bool& IsLoading);

    bool getIsParamValid() const;
    void updateIsParamValid(const bool& IsParamValid);

    int getPretriggerAmplitude() const;
    void updatePretriggerAmplitude(int newPretriggerAmplitude);

    float getPretriggerDistance() const;
    void updatePretriggerDistance(float newPretriggerDistance);

    float getPretriggerTime() const;
    void updatePretriggerTime(float newPretriggerTime);

    int getPretriggerType() const;
    void setPretriggerType(int newPretriggerType);

    int getAfterburstAmplitude() const;
    void updateAfterburstAmplitude(int newAfterburstAmplitude);

    float getAfterburstDelay() const;
    void updateAfterburstDelay(float newAfterburstDelay);

    float getAfterburstTime() const;
    void updateAfterburstTime(float newAfterburstTime);

    bool getAfterburstEnable() const;
    void updateAfterburstEnable(bool newAfterburstEnable);

    bool getPretriggerEnable() const;
    void updatePretriggerEnable(bool newPretriggerEnable);

    /*******************************Stack Recipe*******************************/
    int getDigitalTune() const;
    void updateDigitalTune(int newDigitalTune);

    int getInternalFreqOffset() const;
    void updateInternalFreqOffset(int newInternalFreqOffset);

    bool getEndOfWeldStore() const;
    void updateEndOfWeldStore(bool newEndOfWeldStore);

    bool getFrequencyOffset() const;
    void updateFrequencyOffset(bool newFrequencyOffset);

    int getFrequencyLow() const;
    void updateFrequencyLow(int newFrequencyLow);

    int getFrequencyHigh() const;
    void updateFrequencyHigh(int newFrequencyHigh);

    float getWeldRampTime() const;
    void updateWeldRampTime(float newWeldRampTime);

    int getMemoryOffset() const;
    void updateMemoryOffset(int newMemoryOffset);

    bool getClearMemoryAtPowerUp() const;
    void updateClearMemoryAtPowerUp(bool newClearMemoryAtPowerUp);

    bool getClearMemoryWithReset() const;
    void updateClearMemoryWithReset(bool newClearMemoryWithReset);

    float getPhaseLimitTime() const;
    void updatePhaseLimitTime(float newPhaseLimitTime);

    int getPhaseLimit() const;
    void updatePhaseLimit(int newPhaseLimit);

    int getControlMode() const;
    void updateControlMode(int newControlMode);

    float getBlindTimeWeld() const;
    void updateBlindTimeWeld(float newBlindTimeWeld);

    int getAmpProportionalGain() const;
    void updateAmpProportionalGain(int newAmpProportionalGain);

    int getAmpIntegralGain() const;
    void updateAmpIntegralGain(int newAmpIntegralGain);

    int getAmpDerivativeGain() const;
    void updateAmpDerivativeGain(int newAmpDerivativeGain);

    int getPhaseProportionalGain() const;
    void updatePhaseProportionalGain(int newPhaseProportionalGain);

    int getPhaseIntegralGain() const;
    void updatePhaseIntegralGain(int newPhaseIntegralGain);

    int getPhaseDerivativeGain() const;
    void updatePhaseDerivativeGain(int newPhaseDerivativeGain);

    enum PARAMETERS_ENUMS
    {
        WELD_AMPLITUDE = 10,
        WELD_PRESSURE,
        WELD_FLOWRATE,
        WELD_HOLDTIME,
        WELD_TRIGGERFORCE,
        WELD_HOLDPRESSURE,
    };

    Q_INVOKABLE float getAmplitudeStepAtValue(int StepNo);
    Q_INVOKABLE float getAmplitudeStepRamp(int StepNo);
    Q_INVOKABLE float getAmplitudeStepTarget(int StepNo);

    Q_INVOKABLE float getPressureStepAtValue(int StepNo);
    Q_INVOKABLE float getPressureStepTarget(int StepNo);

    Q_INVOKABLE void setAmplitudeStepAtValue(float Value, int StepNo);
    Q_INVOKABLE void setAmplitudeStepRamp(float Value, int StepNo);
    Q_INVOKABLE void setAmplitudeStepTarget(float Value, int StepNo);

    Q_INVOKABLE void setPressureStepAtValue(float Value, int StepNo);
    Q_INVOKABLE void setPressureStepTarget(float Value, int StepNo);

    Q_INVOKABLE bool createNewRecipeRequest();
    Q_INVOKABLE void initiateRecipeSaveRequest();
    Q_INVOKABLE int getMaxAmplitudeStepCountSupported();
    Q_INVOKABLE int getMaxPressureStepCountSupported();

    Q_INVOKABLE QString getMinParamValue(int mode);
    Q_INVOKABLE QString getMinAmplitudeStepRamp();
    Q_INVOKABLE QString getMinAmplitudeStepTarget();
    Q_INVOKABLE QString getMinPressureStepTarget();

    Q_INVOKABLE QString getMaxParamValue(int mode);
    Q_INVOKABLE QString getMaxAmplitudeStepRamp();
    Q_INVOKABLE QString getMaxAmplitudeStepTarget();
    Q_INVOKABLE QString getMaxPressureStepTarget();

    Q_INVOKABLE QString getDefaultParamValue(int mode);
    Q_INVOKABLE QString getDefaultAmplitudeStepRamp();
    Q_INVOKABLE QString getDefaultAmplitudeStepTarget();
    Q_INVOKABLE QString getDefaultPressureStepTarget();

    /*To set all values with default irrespect of selected step count*/
    Q_INVOKABLE void setDefaultAmplitudeValues(int mode);
    Q_INVOKABLE void setDefaultPressureValues(int mode);

    /*Function to fetch the Min and Max values of Weld Recipe parameters according to system frequency*/
    Q_INVOKABLE QString getMinPretriggerParametersValue(int Type);
    Q_INVOKABLE QString getMaxPretriggerParametersValue(int Type);
    Q_INVOKABLE QString getMinAfterburstParametersValue(int Type);
    Q_INVOKABLE QString getMaxAfterburstParametersValue(int Type);
    Q_INVOKABLE QString getMinParameterAZParametersValue(int Type);
    Q_INVOKABLE QString getMaxParameterAZParametersValue(int Type);
    Q_INVOKABLE QString getMinStackRecipeParametersValue(int Type);
    Q_INVOKABLE QString getMaxStackRecipeParametersValue(int Type);
    Q_INVOKABLE QString getMinQuickEditListParametersValue(int Type);
    Q_INVOKABLE QString getMaxQuickEditListParametersValue(int Type);
    Q_INVOKABLE QString getMinCuttOffLimitParametersValue(int Type);
    Q_INVOKABLE QString getMaxCuttOffLimitParametersValue(int Type);

    Q_INVOKABLE QString getMinSuspectRejectLimitParametersValue(int Type);
    Q_INVOKABLE QString getMaxSuspectRejectLimitParametersValue(int Type);

    /*Reset To Default under Recipe Screens*/
    Q_INVOKABLE void resetToDefault(bool status);

    /*To send stepping structure to the SC*/
    Q_INVOKABLE void onDonePressedForAmplitude();
    Q_INVOKABLE void onDonePressedForPressure();

    /*.............Functions under Batch Setting Screen............*/
    Q_INVOKABLE QString getMinBatchSettingParametersValue(int Type);
    Q_INVOKABLE QString getMaxBatchSettingParametersValue(int Type);
    Q_INVOKABLE void    batchCountLimitUpdateConfirmed();

    /*.............Functions under Energy Compensation tab............*/
    Q_INVOKABLE QString getMinEnergyCompensationVal(int Type);
    Q_INVOKABLE QString getMaxEnergyCompensationVal(int Type);

    /*Enum for defining Parameters ID*/
    enum PRETRIGGER_PARAMETERS_ENUMS
    {
        PRETRIGGER_DISTANCE,
        PRETRIGGER_AMPLITUDE,
        PRETRIGGER_TIME
    };
    enum AFTERBURST_PARAMETERS_ENUMS
    {
        AFTERBURST_TIME,
        AFTERBURST_DELAY,
        AFTERBURST_AMPLITUDE
    };
    enum PARAM_AZ_PARAMETERS_ENUMS
    {
        PARAM_AZ_AFTERBURST_TIME,
        PARAM_AZ_AFTERBURST_DELAY,
        PARAM_AZ_AFTERBURST_AMPLITUDE,
        PARAM_AZ_ENERGY_BRAKE_TIME,
        PARAM_AZ_ENERGY_BRAKE_AMPLITUDE,
        PARAM_AZ_MAX_TIMEOUT,
        PARAM_AZ_HOLD_FORCE_RAMP,
        PARAM_AZ_PRETRIGGER_DISTANCE,
        PARAM_AZ_PRETRIGGER_AMPLITUDE,
        PARAM_AZ_PRETRIGGER_TIME,
        PARAM_AZ_RAPID_TRAVERSE_DISTANCE,
        PARAM_AZ_ACT_CLEAR_TIME,
        PARAM_AZ_ACT_CLEAR_DISTANCE,
        PARAM_AZ_TRIGGER_FORCE,
        PARAM_AZ_TRIGGER_DISTANCE,
        PARAM_AZ_TIME_SEEK,
        PARAM_AZ_SCRUB_AMPILTUDE
    };
    enum STACK_RECIPE_PARAMETERS_ENUMS
    {
        DIGITAL_TUNE,
        INTERNAL_FREQUENCY_OFFSET,
        FREQUENCY_LOW,
        FREQUENCY_HIGH,
        WELD_RAMP_TIME,
        MEMORY_OFFSET,
        PHASE_LIMIT_TIME,
        PHASE_LIMIT,
        CONTROL_MODE,
        BLIND_TIME_WELD,
        AMP_PROPORTIONAL_GAIN,
        AMP_INTEGRAL_GAIN,
        AMP_DERIVATIVE_GAIN,
        PHASE_PROPORTIONAL_GAIN,
        PHASE_INTEGRAL_GAIN,
        PHASE_DERIVATIVE_GAIN
    };
    enum PARAM_CUTTOFFLIMITS_ENUMS
    {
        PARAM_PEAKPOWER_CUTTOFF_VALUE,
        PARAM_TIME_CUTOFF_VALUE,
        PARAM_FREQUENCY_LOW_CUTOFF_VALUE,
        PARAM_FREQUENCY_HIGH_CUTOFF_VALUE,
        PARAM_ENERGY_CUTOFF_VALUE,
        PARAM_GROUND_DETECT_CUTOFF_VALUE,
        PARAM_ABS_DISTANCE_CUTOFF_VALUE,
        PARAM_COLLAPSE_DISTANCE_CUTOFF_VALUE
    };
    enum QUICK_EDIT_PARAMETERS_ENUM
    {
        MODE_VALUE_TIME,
        MODE_VALUE_ENERGY,
        MODE_VALUE_PEAK_POWER,
        MODE_VALUE_GROUND_DETECT,
        PARAM_WELD_PRESSURE,
        FLOW_RATE,
        HOLD_TIME,
        PARAM_WELD_AMPLITUDE
    };
    enum BATCH_SETTING_PARAMETERS_ENUM
    {
        PARAM_BATCH_COUNT,
        PARAM_BATCH_COUNT_LIMIT
    };

    enum ENERGY_COMPENSATION_ENUM
    {
        ENERGY_COMPENSATION_MINIMUM,
        ENERGY_COMPENSATION_MAXIUM
    };

    enum SUSPECT_REJECT_PARAMS_ENUMS
    {
        REJECT_TIME_LOW_LIMIT,
        REJECT_TIME_HIGH_LIMIT,
        REJECT_ENERGY_LOW_LIMIT,
        REJECT_ENERGY_HIGH_LIMIT,
        REJECT_PEAKPOWER_LOW_LIMIT,
        REJECT_PEAKPOWER_HIGH_LIMIT,
        REJECT_FREQUENCY_LOW_LIMIT,
        REJECT_FREQUENCY_HIGH_LIMIT,
        REJECT_ABS_DISTANCE_LOW_LIMIT,
        REJECT_ABS_DISTANCE_HIGH_LIMIT,
        REJECT_COLLAPSE_DISTANCE_LOW_LIMIT,
        REJECT_COLLAPSE_DISTANCE_HIGH_LIMIT,
        REJECT_TRIGGER_DISTANCE_LOW_LIMIT,
        REJECT_TRIGGER_DISTANCE_HIGH_LIMIT,
        REJECT_END_WELD_FORCE_LOW_LIMIT,
        REJECT_END_WELD_FORCE_HIGH_LIMIT,
        REJECT_VELOCITY_LOW_LIMIT,
        REJECT_VELOCITY_HIGH_LIMIT,

        SUSPECT_TIME_LOW_LIMIT,
        SUSPECT_TIME_HIGH_LIMIT,
        SUSPECT_ENERGY_LOW_LIMIT,
        SUSPECT_ENERGY_HIGH_LIMIT,
        SUSPECT_PEAKPOWER_LOW_LIMIT,
        SUSPECT_PEAKPOWER_HIGH_LIMIT,
        SUSPECT_FREQUENCY_LOW_LIMIT,
        SUSPECT_FREQUENCY_HIGH_LIMIT,
        SUSPECT_ABS_DISTANCE_LOW_LIMIT,
        SUSPECT_ABS_DISTANCE_HIGH_LIMIT,
        SUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT,
        SUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT,
        SUSPECT_TRIGGER_DISTANCE_LOW_LIMIT,
        SUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT,
        SUSPECT_END_WELD_FORCE_LOW_LIMIT,
        SUSPECT_END_WELD_FORCE_HIGH_LIMIT,
        SUSPECT_VELOCITY_LOW_LIMIT,
        SUSPECT_VELOCITY_HIGH_LIMIT
    };

    /*******************************Recipe Limits Suspect & Reject*******************************/
    bool getIsGlobalSuspect() const;
    void updateIsGlobalSuspect(const bool& IsGlobalSuspect);

    bool getIsGlobalReject() const;
    void updateIsGlobalReject(const bool& IsGlobalReject);

    bool getIsSuspectTime() const;
    void updateIsSuspectTime(const bool& IsSuspectTime);

    bool getIsSuspectEnergy() const;
    void updateIsSuspectEnergy(const bool& IsSuspectEnergy);

    bool getIsSuspectPeakPower() const;
    void updateIsSuspectPeakPower(const bool& IsSuspectPeakPower);

    bool getIsSuspectFrequency() const;
    void updateIsSuspectFrequency(const bool& IsSuspectFrequency);

    bool getIsRejectTime() const;
    void updateIsRejectTime(const bool& IsRejectTime);

    bool getIsRejectEnergy() const;
    void updateIsRejectEnergy(const bool& IsRejectEnergy);

    bool getIsRejectPeakPower() const;
    void updateIsRejectPeakPower(const bool& IsRejectPeakPower);

    bool getIsRejectFrequency() const;
    void updateIsRejectFrequency(const bool& IsRejectFrequency);

    float getSuspectLowTime() const;
    void updateSuspectLowTime(const float& SuspectLowTime);

    float getSuspectHighTime() const;
    void updateSuspectHighTime(const float& SuspectHighTime);

    float getSuspectLowEnergy() const;
    void updateSuspectLowEnergy(const float& SuspectLowEnergy);

    float getSuspectHighEnergy() const;
    void updateSuspectHighEnergy(const float& SuspectHighEnergy);

    float getSuspectLowPeakPower() const;
    void updateSuspectLowPeakPower(const float& SuspectLowPeakPower);

    float getSuspectHighPeakPower() const;
    void updateSuspectHighPeakPower(const float& SuspectHighPeakPower);

    float getSuspectLowFrequency() const;
    void updateSuspectLowFrequency(const float& SuspectLowFrequency);

    float getSuspectHighFrequency() const;
    void updateSuspectHighFrequency(const float& SuspectHighFrequency);

    float getRejectLowTime() const;
    void updateRejectLowTime(const float& RejectLowTime);

    float getRejectHighTime() const;
    void updateRejectHighTime(const float& RejectHighTime);

    float getRejectLowEnergy() const;
    void updateRejectLowEnergy(const float& RejectLowEnergy);

    float getRejectHighEnergy() const;
    void updateRejectHighEnergy(const float& RejectHighEnergy);

    float getRejectLowPeakPower() const;
    void updateRejectLowPeakPower(const float& RejectLowPeakPower);

    float getRejectHighPeakPower() const;
    void updateRejectHighPeakPower(const float& RejectHighPeakPower);

    float getRejectLowFrequency() const;
    void updateRejectLowFrequency(const float& RejectLowFrequency);

    float getRejectHighFrequency() const;
    void updateRejectHighFrequency(const float& RejectHighFrequency);

    bool getIsAbsDistSuspect() const;
    void updateIsAbsDistSuspect(const bool& IsGlobalSuspect);

    bool getIsAbsDistReject() const;
    void updateIsAbsDistReject(const bool& IsGlobalSuspect);

    bool getIsCollapseDistSuspect() const;
    void updateIsCollapseDistSuspect(const bool& IsGlobalSuspect);

    bool getIsCollapseDistReject() const;
    void updateIsCollapseDistReject(const bool& IsGlobalSuspect);

    bool getIsTriggerDistSuspect() const;
    void updateIsTriggerDistSuspect(const bool& IsGlobalSuspect);

    bool getIsTriggerDistReject() const;
    void updateIsTriggerDistReject(const bool& IsGlobalSuspect);

    bool getIsVelocitySuspect() const;
    void updateIsVelocitySuspect(const bool& IsGlobalSuspect);

    bool getIsVelocityReject() const;
    void updateIsVelocityReject(const bool& IsGlobalSuspect);

    bool getIsEndWeldForceSuspect() const;
    void updateIsEndWeldForceSuspect(const bool& IsGlobalSuspect);

    bool getIsEndWeldForceReject() const;
    void updateIsEndWeldForceReject(const bool& IsGlobalSuspect);



    float getSuspectLowAbsDist() const;
    void updateSuspectLowAbsDist(const float& RejectLowEnergy);

    float getSuspectHighAbsDist() const;
    void updateSuspectHighAbsDist(const float& RejectLowEnergy);

    float getRejectLowAbsDist() const;
    void updateRejectLowAbsDist(const float& RejectLowEnergy);

    float getRejectHighAbsDist() const;
    void updateRejectHighAbsDist(const float& RejectLowEnergy);

    float getSuspectLowCollapseDist() const;
    void updateSuspectLowCollapseDist(const float& RejectLowEnergy);

    float getSuspectHighCollapseDist() const;
    void updateSuspectHighCollapseDist(const float& RejectLowEnergy);

    float getRejectLowCollapseDist() const;
    void updateRejectLowCollapseDist(const float& RejectLowEnergy);

    float getRejectHighCollapseDist() const;
    void updateRejectHighCollapseDist(const float& RejectLowEnergy);

    float getSuspectLowTriggerDist() const;
    void updateSuspectLowTriggerDist(const float& RejectLowEnergy);

    float getSuspectHighTriggerDist() const;
    void updateSuspectHighTriggerDist(const float& RejectLowEnergy);

    float getRejectLowTriggerDist() const;
    void updateRejectLowTriggerDist(const float& RejectLowEnergy);

    float getRejectHighTriggerDist() const;
    void updateRejectHighTriggerDist(const float& RejectLowEnergy);

    float getSuspectLowVelocity() const;
    void updateSuspectLowVelocity(const float& RejectLowEnergy);

    float getSuspectHighVelocity() const;
    void updateSuspectHighVelocity(const float& RejectLowEnergy);

    float getRejectLowVelocity() const;
    void updateRejectLowVelocity(const float& RejectLowEnergy);

    float getRejectHighVelocity() const;
    void updateRejectHighVelocity(const float& RejectLowEnergy);

    float getSuspectLowEndWeldForce() const;
    void updateSuspectLowEndWeldForce(const float& RejectLowEnergy);

    float getSuspectHighEndWeldForce() const;
    void updateSuspectHighEndWeldForce(const float& RejectLowEnergy);

    float getRejectLowEndWeldForce() const;
    void updateRejectLowEndWeldForce(const float& RejectLowEnergy);

    float getRejectHighEndWeldForce() const;
    void updateRejectHighEndWeldForce(const float& RejectLowEnergy);

    /*********************************************************************************************/

    /*******************************Recipe Parameter A-Z *******************************/
    bool getEnergyBraking() const;
    void updateEnergyBraking(bool newEnergyBraking);

    int getEnergyBrakeAmplitude() const;
    void updateEnergyBrakeAmplitude(int newEnergyBrakeAmplitude);

    float getEnergyBrakeTime() const;
    void updateEnergyBrakeTime(float newEnergyBrakeTime);

    bool getPreWeldSeek() const;
    void updatePreWeldSeek(bool newPreWeldSeek);

    bool getPostWeldSeek() const;
    void updatePostWeldSeek(bool newPostWeldSeek);

    bool getExtraCooling() const;
    void updateExtraCooling(bool newExtraCooling);

    bool getActuatorClear() const;
    void updateActuatorClear(bool newActuatorClear);

    float getActuatorClearTime() const;
    void updateActuatorClearTime(float newActuatorClearTime);

    float getActuatorClearDistance() const;
    void updateActuatorClearDistance(float newActuatorClearDistance);

    int getActuatorClearType() const;
    void setActuatorClearType(int newActuatorClearType);

    float getHoldForceRamp() const;
    void updateHoldForceRamp(float newHoldForceRamp);

    bool getRapidTraverse() const;
    void updateRapidTraverse(bool newRapidTraverse);

    float getRapidTraverseDistance() const;
    void updateRapidTraverseDistance(float newRapidTraverseDistance);

    bool getTriggerLost() const;
    void updateTriggerLost(bool newTriggerLost);

    float getTriggerForce() const;
    void updateTriggerForce(float newTriggerForce);

 	bool getBransonOnlyLogin() const;
    void updateBransonOnlyLogin(bool newBransonOnlyLogin);
    
    float getTriggerTypeForce() const;
    void updateTriggerTypeForce(float newTriggerTypeForce);

    float getTriggerTypeDistance() const;
    void updateTriggerTypeDistance(float newTriggerTypeDistance);

    int getTriggerType() const;
    void updateTriggerType(int newTriggerType);

    bool getIsTimeSeekEnable() const;
    void updateIsTimeSeekEnable(bool newIsTimeSeekEnable);

    float getTimeSeekPeriod() const;
    void updateTimeSeekPeriod(float newTimeSeekPeriod);

    int getScrubAmplitude() const;
    void updateScrubAmplitude(int newScrubAmplitude);

    /*******************************Recipe Limits-Control *******************************/
    bool getCutoffLimtsEnabled() const;
    void updateCutoffLimtsEnabled(bool newCutoffLimtsEnable);

    bool getPeakPowerCuttOffEnabled() const;
    void updatePeakPowerCuttOffEnabled(bool newPeakPowerCuttOffEnabled);

    float getPeakPowerCuttoffValue() const;
    void updatePeakPowerCuttoffValue(float newPeakPowerCuttoffValue);

    bool getTimeCuttoff() const;
    void updateTimeCuttoff(bool newTimeCuttoffEnable);

    float getTimeCuttoffValue() const;
    void updateTimeCuttoffValue(float newTimeCuttoffValue);

    bool getFreqLowCuttoff() const;
    void updateFreqLowCuttoff(bool newFreqLowCuttoffEnable);

    float getFreqLowCuttoffValue() const;
    void updateFreqLowCuttoffValue(float newFreqLowCuttoffValue);

    bool getFreqHighCuttoff() const;
    void updateFreqHighCuttoff(bool newFreqHighCuttoffEnable);

    float getFreqHighCuttoffValue() const;
    void updateFreqHighCuttoffValue(float newFreqHighCuttoffValue);

    bool getEnergyCuttoff() const;
    void updateEnergyCuttoff(bool newEnergyCuttoffEnable);

    float getEnergyCuttoffValue() const;
    void updateEnergyCuttoffValue(float newEnergyCuttoffValue);

    bool getGroundDetectCuttoff() const;
    void updateGroundDetectCuttoff(bool newGroundDetectCuttoffEnable);

    float getGroundDetectCuttoffValue() const;
    void updateGroundDetectCuttoffValue(float newGroundDetectCuttoffValue);

    bool getABSDistanceCutoff() const;
    void updateABSDistanceCutoff(bool newABSDistanceCutoffEnable);

    float getABSDistanceCutoffValue() const;
    void updateABSDistanceCutoffValue(float newABSDistanceCutoffValue);

    bool getCollapseDistanceCutoff() const;
    void updateCollapseDistanceCutoff(bool newCollapseDistanceCutoffEnable);

    float getCollapseDistanceCutoffValue() const;
    void updateCollapseDistanceCutoffValue(float newCollapseDistanceCutoffValue);

    /*******************************Recipe Batch Setting *******************************/
    bool getBatchSetup() const;
    void updateBatchSetup(bool newBatchSetup);

    bool getCountWithAlarms() const;
    void updateCountWithAlarms(bool newCountWithAlarms);

    int getBatchCounterLimit() const;
    void updateBatchCounterLimit(int newBatchCounter);

    QString getBatchId() const;
    void updateBatchId(const QString &newBatchId);

    int getBatchCounter() const;
    void updateBatchCounter(int newBatchCounter);

    bool getExternalAmplitudeSetting() const;
    void updateExternalAmplitudeSetting(bool newExternalAmplitudeSetting);

    /*******************************Recipe Energy Compensation *******************************/
    bool getEnergyCompensation() const;
    void updateEnergyCompensation(bool newEnergyCompensation);

    float getEnergyCompensationLowVal() const;
    void updateEnergyCompensationLowVal(float newEnergyCompensationLowVal);

    float getEnergyCompensationHighVal() const;
    void updateEnergyCompensationHighVal(float newEnergyCompensationHighVal);



signals:
    void recipeLabDataChanged();
    /*Signal to notify recipe cards limit*/
    void maxRecipeCountReached();
    void loadingLabDataChanged();
    void batchCountLimitUpdate();

    /*Slot to be called when data update signal generated by communication thread*/
private slots:
    void OnRecipeLabDataUpdated(WeldRecipeACE *RecipeLabData_Obj, int WelderId);
};

#endif // RECIPELABDATA_H

/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

    RecipeSuspectRejectSetting.qml file handles suspect & reject feature
    of weld logic.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 05/02/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
import QtQml.Models 2.15

Item {

    property string qmlTextGlobalSuspect:    "GLOBAL SUSPECT"
    property string qmlTextGlobalReject:     "GLOBAL REJECT"
    property string qmlTextTime:             "TIME"
    property string qmlTextEnergy:           "ENERGY"
    property string qmlTextPeakPower:        "PEAK POWER"
    property string qmlTextFrequency:        "FREQUENCY"
    property string qmlTextAbsoluteDistance: "ABSOLUTE DISTANCE"
    property string qmlTextCollapseDistance: "COLLAPSE DISTANCE"
    property string qmlTextTriggerDistance:  "TRIGGER DISTANCE"
    property string qmlTextEndWeldFORCE:     "END WELD FORCE"
    property string qmlTextVelocity:         "VELOCITY"

property var qmlTextArray: [qmlTextGlobalSuspect,qmlTextGlobalReject,qmlTextTime,qmlTextEnergy,qmlTextPeakPower,qmlTextFrequency,qmlTextAbsoluteDistance,qmlTextCollapseDistance,qmlTextTriggerDistance,qmlTextEndWeldFORCE,qmlTextVelocity]

    function updateLanguage()
    {
        qmlTextArray = qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_LIMITS_SUSPECT_REJECT, qmlTextArray)
        qmlTextGlobalSuspect = qmlTextArray[textEnum.textGlobalSuspectIdx]
        qmlTextGlobalReject = qmlTextArray[textEnum.textGlobalReject]
        qmlTextTime = qmlTextArray[textEnum.textTimeIdx]
        qmlTextEnergy = qmlTextArray[textEnum.textEnergyIdx]
        qmlTextPeakPower = qmlTextArray[textEnum.textPeakPowerIdx]
        qmlTextFrequency = qmlTextArray[textEnum.textVelocityIdx]
        qmlTextAbsoluteDistance = qmlTextArray[textEnum.textAbsoluteDistanceIdx]
        qmlTextCollapseDistance = qmlTextArray[textEnum.textCollapseDistanceIdx]
        qmlTextTriggerDistance = qmlTextArray[textEnum.textTriggerDistanceIdx]
        qmlTextEndWeldFORCE = qmlTextArray[textEnum.textEndWeldFORCEIdx]
        qmlTextVelocity = qmlTextArray[textEnum.textFrequencyIdx]
        suspectRejectListModel.resetSuspectRejectModel()
    }

    QtObject{
        id:textEnum
        readonly property int textGlobalSuspectIdx :   0
        readonly property int textGlobalReject :       1
        readonly property int textTimeIdx :            2
        readonly property int textEnergyIdx :          3
        readonly property int textPeakPowerIdx:        4
        readonly property int textVelocityIdx:         5
        readonly property int textAbsoluteDistanceIdx: 6
        readonly property int textCollapseDistanceIdx: 7
        readonly property int textTriggerDistanceIdx : 8
        readonly property int textEndWeldFORCEIdx :    9
        readonly property int textFrequencyIdx:        10

    }
    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Connections
    {
        target: RecipeLabData
        function onRecipeLabDataChanged()
        {
            suspectRejectListModel.resetSuspectRejectModel()
        }
   }

    QtObject{
        id:paramEnum
        readonly property int paramREJECT_TIME_LOW_LIMIT              :0
        readonly property int paramREJECT_TIME_HIGH_LIMIT             :1
        readonly property int paramREJECT_ENERGY_LOW_LIMIT            :2
        readonly property int paramREJECT_ENERGY_HIGH_LIMIT           :3
        readonly property int paramREJECT_PEAKPOWER_LOW_LIMIT         :4
        readonly property int paramREJECT_PEAKPOWER_HIGH_LIMIT        :5
        readonly property int paramREJECT_FREQUENCY_LOW_LIMIT         :6
        readonly property int paramREJECT_FREQUENCY_HIGH_LIMIT        :7
        readonly property int paramREJECT_ABS_DISTANCE_LOW_LIMIT      :8
        readonly property int paramREJECT_ABS_DISTANCE_HIGH_LIMIT     :9
        readonly property int paramREJECT_COLLAPSE_DISTANCE_LOW_LIMIT :10

        readonly property int paramREJECT_COLLAPSE_DISTANCE_HIGH_LIMIT:11
        readonly property int paramREJECT_TRIGGER_DISTANCE_LOW_LIMIT  :12
        readonly property int paramREJECT_TRIGGER_DISTANCE_HIGH_LIMIT :13
        readonly property int paramREJECT_END_WELD_FORCE_LOW_LIMIT    :14
        readonly property int paramREJECT_END_WELD_FORCE_HIGH_LIMIT   :15
        readonly property int paramREJECT_VELOCITY_LOW_LIMIT          :16
        readonly property int paramREJECT_VELOCITY_HIGH_LIMIT         :17

        readonly property int paramSUSPECT_TIME_LOW_LIMIT             :18
        readonly property int paramSUSPECT_TIME_HIGH_LIMIT            :19
        readonly property int paramSUSPECT_ENERGY_LOW_LIMIT           :20
        readonly property int paramSUSPECT_ENERGY_HIGH_LIMIT          :21
        readonly property int paramSUSPECT_PEAKPOWER_LOW_LIMIT        :22
        readonly property int paramSUSPECT_PEAKPOWER_HIGH_LIMIT       :23
        readonly property int paramSUSPECT_FREQUENCY_LOW_LIMIT        :24
        readonly property int paramSUSPECT_FREQUENCY_HIGH_LIMIT       :25
        readonly property int paramSUSPECT_ABS_DISTANCE_LOW_LIMIT     :26
        readonly property int paramSUSPECT_ABS_DISTANCE_HIGH_LIMIT    :27
        readonly property int paramSUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT:28
        readonly property int paramSUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT:29
        readonly property int paramSUSPECT_TRIGGER_DISTANCE_LOW_LIMIT  :30
        readonly property int paramSUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT :31
        readonly property int paramSUSPECT_END_WELD_FORCE_LOW_LIMIT    :32
        readonly property int paramSUSPECT_END_WELD_FORCE_HIGH_LIMIT   :33
        readonly property int paramSUSPECT_VELOCITY_LOW_LIMIT          :34
        readonly property int paramSUSPECT_VELOCITY_HIGH_LIMIT         :35

    }


    Component.onCompleted:
    {
        updateLanguage()
    }


    ListModel
    {
        id: suspectRejectListModel
        function resetSuspectRejectModel()
        {
            suspectRejectListModel.clear()
                     suspectRejectListModel.append({"Title"          : qmlTextGlobalSuspect,
                                                    "GlobalCheck" : RecipeLabData.IsGlobalSuspect,
                                                    "Index"       : 0})


                     suspectRejectListModel.append({"Title" : qmlTextGlobalReject,
                                                    "GlobalCheck" : RecipeLabData.IsGlobalReject,
                                                    "Index"       : 1})

                     suspectRejectListModel.append({"Title" : qmlTextTime,
                                                       "SuspectCheck"  : RecipeLabData.IsSuspectTime,
                                                       "RejectCheck"   : RecipeLabData.IsRejectTime,
                                                       "SuspectLow"    : RecipeLabData.SuspectLowTime.toFixed(3),
                                                       "RejectLow"     : RecipeLabData.RejectLowTime.toFixed(3),
                                                       "SuspectHigh"   : RecipeLabData.SuspectHighTime.toFixed(3),
                                                       "RejectHigh"    : RecipeLabData.RejectHighTime.toFixed(3),
                                                       "Decimals"      : 3,
                                                       "Unit"          : mainWindow.qmltextTimeUnit,
                                                       "MinimumSuspectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TIME_LOW_LIMIT),
                                                       "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TIME_LOW_LIMIT),
                                                       "MaximumSuspectHigh"     :RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TIME_HIGH_LIMIT),
                                                       "MaximumRejectHigh"       :RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TIME_HIGH_LIMIT),
                                                       "Index"         : 3})

                     suspectRejectListModel.append({"Title" : qmlTextEnergy,
                                                       "SuspectCheck": RecipeLabData.IsSuspectEnergy,
                                                       "RejectCheck" : RecipeLabData.IsRejectEnergy,
                                                       "SuspectLow"  : RecipeLabData.SuspectLowEnergy.toFixed(1),
                                                       "RejectLow"   : RecipeLabData.RejectLowEnergy.toFixed(1),
                                                       "SuspectHigh" : RecipeLabData.SuspectHighEnergy.toFixed(1),
                                                       "RejectHigh"  : RecipeLabData.RejectHighEnergy.toFixed(1),
                                                       "Decimals"    : 1,
                                                        "Unit"          : mainWindow.qmltextEnergyUnit,
                                                       "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ENERGY_LOW_LIMIT),
                                                       "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ENERGY_LOW_LIMIT),
                                                       "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ENERGY_HIGH_LIMIT),
                                                       "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ENERGY_HIGH_LIMIT),
                                                       "Index"       : 4})

                     suspectRejectListModel.append({"Title":      qmlTextPeakPower,
                                                       "SuspectCheck"  : RecipeLabData.IsSuspectPeakPower,
                                                       "RejectCheck"   : RecipeLabData.IsRejectPeakPower,
                                                       "SuspectLow"    : RecipeLabData.SuspectLowPeakPower.toFixed(0),
                                                       "RejectLow"     : RecipeLabData.RejectLowPeakPower.toFixed(0),
                                                       "SuspectHigh"   : RecipeLabData.SuspectHighPeakPower.toFixed(0),
                                                       "RejectHigh"    : RecipeLabData.RejectHighPeakPower.toFixed(0),
                                                       "Decimals"      : 0,
                                                       "Unit"          : mainWindow.qmltextPowerUnit,

                                                       "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_PEAKPOWER_LOW_LIMIT),
                                                       "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_PEAKPOWER_LOW_LIMIT),
                                                       "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_PEAKPOWER_HIGH_LIMIT),
                                                       "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_PEAKPOWER_HIGH_LIMIT),
                                                       "Index"         : 5})

                     if((SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC) ||
                             (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC_PLUS))
                     {
                         if (mainWindow.qmltextDistanceUnit === "mm")
                         {
                             suspectRejectListModel.append({"Title":      qmlTextAbsoluteDistance,
                                                               "SuspectCheck" : RecipeLabData.IsAbsDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsAbsDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowAbsDist.toFixed(2),
                                                               "RejectLow"    : RecipeLabData.RejectLowAbsDist.toFixed(2),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighAbsDist.toFixed(2),
                                                               "RejectHigh"   : RecipeLabData.RejectHighAbsDist.toFixed(2),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ABS_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ABS_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ABS_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ABS_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 6})

                             suspectRejectListModel.append({"Title":      qmlTextCollapseDistance,
                                                               "SuspectCheck" : RecipeLabData.IsCollapseDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsCollapseDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowCollapseDist.toFixed(2),
                                                               "RejectLow"    : RecipeLabData.RejectLowCollapseDist.toFixed(2),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighCollapseDist.toFixed(2),
                                                               "RejectHigh"   : RecipeLabData.RejectHighCollapseDist.toFixed(2),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_COLLAPSE_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_COLLAPSE_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 7})
                         }

                         else
                         {
                             suspectRejectListModel.append({"Title":      qmlTextAbsoluteDistance,
                                                               "SuspectCheck" : RecipeLabData.IsAbsDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsAbsDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowAbsDist.toFixed(4),
                                                               "RejectLow"    : RecipeLabData.RejectLowAbsDist.toFixed(4),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighAbsDist.toFixed(4),
                                                               "RejectHigh"   : RecipeLabData.RejectHighAbsDist.toFixed(4),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ABS_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ABS_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_ABS_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_ABS_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 6})


                             suspectRejectListModel.append({"Title":      qmlTextCollapseDistance,
                                                               "SuspectCheck" : RecipeLabData.IsCollapseDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsCollapseDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowCollapseDist.toFixed(4),
                                                               "RejectLow"    : RecipeLabData.RejectLowCollapseDist.toFixed(4),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighCollapseDist.toFixed(4),
                                                               "RejectHigh"   : RecipeLabData.RejectHighCollapseDist.toFixed(4),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_COLLAPSE_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_COLLAPSE_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_COLLAPSE_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_COLLAPSE_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 7})
                         }

                         suspectRejectListModel.append({"Title":      qmlTextEndWeldFORCE,
                                                           "SuspectCheck" : RecipeLabData.IsEndWeldForceSuspect,
                                                           "RejectCheck"  : RecipeLabData.IsEndWeldForceReject,
                                                           "SuspectLow"   : RecipeLabData.SuspectLowEndWeldForce.toFixed(0),
                                                           "RejectLow"    : RecipeLabData.RejectLowEndWeldForce.toFixed(0),
                                                           "SuspectHigh"  : RecipeLabData.SuspectHighEndWeldForce.toFixed(0),
                                                           "RejectHigh"   : RecipeLabData.RejectHighEndWeldForce.toFixed(0),
                                                           "Decimals"     : (mainWindow.qmltextForceUnit === "N") ? 0 : 1,
                                                           "Unit"         : mainWindow.qmltextForceUnit,

                                                           "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_END_WELD_FORCE_LOW_LIMIT),
                                                           "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_END_WELD_FORCE_LOW_LIMIT),
                                                           "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_END_WELD_FORCE_HIGH_LIMIT),
                                                           "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_END_WELD_FORCE_HIGH_LIMIT),
                                                           "Index"        : 8})

                         if (mainWindow.qmltextDistanceUnit === "mm")
                         {
                             suspectRejectListModel.append({"Title":      qmlTextTriggerDistance,
                                                               "SuspectCheck" : RecipeLabData.IsTriggerDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsTriggerDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowTriggerDist.toFixed(2),
                                                               "RejectLow"    : RecipeLabData.RejectLowTriggerDist.toFixed(2),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighTriggerDist.toFixed(2),
                                                               "RejectHigh"   : RecipeLabData.RejectHighTriggerDist.toFixed(2),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TRIGGER_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TRIGGER_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TRIGGER_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 9})
                         }

                         else
                         {
                             suspectRejectListModel.append({"Title":      qmlTextTriggerDistance,
                                                               "SuspectCheck" : RecipeLabData.IsTriggerDistSuspect,
                                                               "RejectCheck"  : RecipeLabData.IsTriggerDistReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowTriggerDist.toFixed(4),
                                                               "RejectLow"    : RecipeLabData.RejectLowTriggerDist.toFixed(4),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighTriggerDist.toFixed(4),
                                                               "RejectHigh"   : RecipeLabData.RejectHighTriggerDist.toFixed(4),
                                                               "Decimals"     : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TRIGGER_DISTANCE_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TRIGGER_DISTANCE_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_TRIGGER_DISTANCE_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_TRIGGER_DISTANCE_HIGH_LIMIT),
                                                               "Index"        : 9})
                         }

                         if (mainWindow.qmltextVelocityUnit === "mm/s")
                         {
                             suspectRejectListModel.append({"Title":      qmlTextVelocity,
                                                               "SuspectCheck" : RecipeLabData.IsVelocitySuspect,
                                                               "RejectCheck"  : RecipeLabData.IsVelocityReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowVelocity.toFixed(0),
                                                               "RejectLow"    : RecipeLabData.RejectLowVelocity.toFixed(0),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighVelocity.toFixed(0),
                                                               "RejectHigh"   : RecipeLabData.RejectHighVelocity.toFixed(0),
                                                               "Decimals"     : 0,
                                                               "Unit"          : mainWindow.qmltextDistanceUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_VELOCITY_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_VELOCITY_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_VELOCITY_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_VELOCITY_HIGH_LIMIT),
                                                               "Index"        : 10})
                         }

                         else
                         {
                             suspectRejectListModel.append({"Title":      qmlTextVelocity,
                                                               "SuspectCheck" : RecipeLabData.IsVelocitySuspect,
                                                               "RejectCheck"  : RecipeLabData.IsVelocityReject,
                                                               "SuspectLow"   : RecipeLabData.SuspectLowVelocity.toFixed(1),
                                                               "RejectLow"    : RecipeLabData.RejectLowVelocity.toFixed(1),
                                                               "SuspectHigh"  : RecipeLabData.SuspectHighVelocity.toFixed(1),
                                                               "RejectHigh"   : RecipeLabData.RejectHighVelocity.toFixed(1),
                                                               "Decimals"     : 1,
                                                               "Unit"          : mainWindow.qmltextDownSpeedUnit,

                                                               "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_VELOCITY_LOW_LIMIT),
                                                               "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_VELOCITY_LOW_LIMIT),
                                                               "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_VELOCITY_HIGH_LIMIT),
                                                               "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_VELOCITY_HIGH_LIMIT),
                                                               "Index"        : 10})
                         }
                     }

                     suspectRejectListModel.append({"Title":      qmlTextFrequency,
                                                       "SuspectCheck" : RecipeLabData.IsSuspectFrequency,
                                                       "RejectCheck"  : RecipeLabData.IsRejectFrequency,
                                                       "SuspectLow"   : RecipeLabData.SuspectLowFrequency.toFixed(3),
                                                       "RejectLow"    : RecipeLabData.RejectLowFrequency.toFixed(3),
                                                       "SuspectHigh"  : RecipeLabData.SuspectHighFrequency.toFixed(3),
                                                       "RejectHigh"   : RecipeLabData.RejectHighFrequency.toFixed(3),
                                                       "Decimals"     : 3,
                                                       "Unit"          : mainWindow.qmltextFrequencyUnit,

                                                       "MinimumSuspectLow"      :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_FREQUENCY_LOW_LIMIT),
                                                       "MinimumRejectLow"       :  RecipeLabData.getMinSuspectRejectLimitParametersValue(paramEnum.paramREJECT_FREQUENCY_LOW_LIMIT),
                                                       "MaximumSuspectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramSUSPECT_FREQUENCY_HIGH_LIMIT),
                                                       "MaximumRejectHigh"     :  RecipeLabData.getMaxSuspectRejectLimitParametersValue(paramEnum.paramREJECT_FREQUENCY_HIGH_LIMIT),
                                                       "Index"        : 11})
                 }
    }


    BransonGridView
    {
        id: recipeSuspectRejectGridView
        anchors.top: parent.top
        anchors.topMargin: Math.round(8 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        gridViewCellHeight: Math.round(parent.height / 3.5)
        gridViewCellWidth: Math.round(parent.width / 2.2)
        gridViewModel:suspectRejectListModel
        gridViewDelegate: BransonLeftBorderRectangle
        {
            id: optionControl
            width: Math.round((recipeSuspectRejectGridView.gridViewCellWidth - Math.round(11 * Style.scaleHint)))
            height: Math.round(recipeSuspectRejectGridView.gridViewCellHeight - Math.round(8 * Style.scaleHint))
            checked: true
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onReleased:
                {
                    if (model.Title !== qmlTextGlobalSuspect && model.Title !== qmlTextGlobalReject)
                    {
                        mainWindow.showSuspectRejectNumpad(model.Title, model.SuspectCheck, model.RejectCheck, model.SuspectLow, model.RejectLow, model.SuspectHigh, model.RejectHigh, model.Decimals, model.MinimumSuspectLow, model.MinimumRejectLow, model.MaximumSuspectHigh, model.MaximumRejectHigh, model.Unit)
                    }
                }

            }

            Text
            {
                id: txtTitle
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: Math.round(7 * Style.scaleHint)
                anchors.bottom: parent.bottom
                text: model.Title
                lineHeight: Math.round(1 * Style.scaleHint)
                wrapMode: Text.WordWrap
                color: Style.blackFontColor
                font.family: Style.regular.name
                font.pixelSize: parent.height *0.25
            }

            BransonSwitch
            {
                id: switchControl
                visible: ((model.Title === qmlTextGlobalSuspect) || (model.Title === qmlTextGlobalReject))
                checked: model.GlobalCheck
                anchors.right:  parent.right
                anchors.rightMargin:  Math.round(20 * Style.scaleHint)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.round(13 * Style.scaleHint)
                onCheckedChanged:
                {
                    if(model.Title === qmlTextGlobalSuspect)
                    {
                        RecipeLabData.IsGlobalSuspect = switchControl.checked
                    }

                    else
                    {
                        RecipeLabData.IsGlobalReject = switchControl.checked
                    }
                }
            }

            Rectangle
            {
                id: txtRejectLowValueRect
                visible:((! switchControl.visible) && (model.RejectCheck))
                anchors.left: parent.left
                anchors.leftMargin: parent.width *0.10
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                width: Math.round(45 * Style.scaleHint)
                color: "#B91819"
                border.color: Style.titleBackgroundColor
                Text
                {
                    id: txtRejectLowValue
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: model.RejectLow
                    color: "#FFFFFF"
                    font.family: Style.regular.name
                    font.pixelSize: parent.height *0.40
                    visible: true
                }
            }

            Rectangle
            {
                id: txtSuspectLowValueRect
                visible: ((! switchControl.visible) && (model.SuspectCheck))
                anchors.left: txtRejectLowValueRect.right
                anchors.leftMargin: Math.round(0 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                width: Math.round(45 * Style.scaleHint)
                color: "#FECF22"
                border.color: Style.titleBackgroundColor
                Text
                {
                    id: txtSuspectLowValue
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: model.SuspectLow
                    color: "#FFFFFF"
                    font.family: Style.regular.name
                    font.pixelSize: parent.height *0.40
                    visible: true
                }
            }

            Rectangle
            {
                id: txtSuspectHighValueRect
                visible: ((! switchControl.visible) && (model.SuspectCheck))
                anchors.left: txtSuspectLowValueRect.right
                anchors.leftMargin: Math.round(10 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                width: Math.round(45 * Style.scaleHint)
                color: "#FECF22"
                border.color: Style.titleBackgroundColor
                Text
                {
                    id: txtSuspectHighValue
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: model.SuspectHigh
                    color: "#FFFFFF"
                    font.family: Style.regular.name
                    font.pixelSize: parent.height *0.40
                    visible: true
                }
            }

            Rectangle
            {
                id: txtRejectHighValueRect
                visible: ((! switchControl.visible) && (model.RejectCheck))
                anchors.left: txtSuspectHighValueRect.right
                anchors.leftMargin: Math.round(0 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(30 * Style.scaleHint)
                height: Math.round(25 * Style.scaleHint)
                width: Math.round(45 * Style.scaleHint)
                color: "#B91819"
                border.color: Style.titleBackgroundColor
                Text
                {
                    id: txtRejectHighValue
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: model.RejectHigh
                    color: "#FFFFFF"
                    font.family: Style.regular.name
                    font.pixelSize: parent.height *0.40
                    visible: true
                }
            }
        }
    }
}

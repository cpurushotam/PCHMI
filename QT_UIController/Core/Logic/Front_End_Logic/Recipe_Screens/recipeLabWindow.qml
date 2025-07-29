/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    recipeLabWindow.qml file displays recipe lab data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 29/08/2023 - Initial version.
***************************************************************************/
import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
Item {
    id: recipeLabWindow
    readonly property int qmlscreenIndicator:   UIScreenEnum.RECIPES_LAB
    readonly property color shadowColor: "#000000"

    property string qmltextMenuName         : "Lab"
    property string qmltextRecipeActions    : "Actions"
    property string qmltextRecipeNew        : "New"
    property string qmltextRecipeSave       : "Save"
    property string qmltextRecipeCopy       : "Copy"
    property string qmltextRecipeDelete     : "Delete"


    property string qmltextQuickEdit        : "QUICK EDIT"
    property string qmltextTime             : "TIME"
    property string qmltextEnergy           : "ENERGY"
    property string qmltextPeakPower        : "PEAK POWER"
    property string qmltextAbsoluteDistance : "ABSOLUTE DISTANCE"
    property string qmltextCollapseDistance : "COLLAPSE DISTANCE"
    property string qmltextScrubTime        : "SCRUB TIME"
    property string qmlTextScrubAmplitude   : "SCRUB AMPLITUDE"
    property string qmltextWeldAmplitude    : "WELD AMPLITUDE"
    property string qmltextHoldTime         : "HOLD TIME"
    property string qmltextTriggerForce     : "TRIGGER FORCE"
    property string qmltextHoldPressure     : "HOLD PRESSURE"

    property string qmltextWeldProcess      : "Weld Process"
    property string qmltextWeldMode         : "Weld Mode"
    property string qmltextParametersA2Z    : "Parameters A-Z"
    property string qmltextLimit            : "Limits"
    property string qmltextStackRecipe      : "Stack Recipe"
    property string qmltextPretrigger       : "Pretrigger"
    property string qmltextAfterburst       : "Afterburst"
    property string qmltextSetup            : "Setup"
    property string qmltextControl          : "Control"
    property string qmltextEnergyCmp        : "Energy Compensation"


    property string qmltextSuspectReject : ((SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC) ||
                                            (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC_PLUS)) ? "Suspect & Reject" : "Suspect"

    property string qmltextRecipeSetting : "RECIPE SETTINGS"
    property string qmltextResultView    : "RESULT VIEW"
    property string qmltextGraphSetting  : "GRAPH SETTINGS"

    property string qmltextPressure      : "WELD PRESSURE"
    property string qmltextFlowRate      : "DOWNSPEED"
    property string qmltextForceRampTime : "FORCE RAMP TIME"

    property string qmltextMaxRecipeCountError       : "Maximum recipe count reached...!"
    property string qmltextRecipeCopyOverrideConfirm : "Do you want to override recipe number ?"
    property string qmltextValidationError           : "Entered Values Outof Range, Restoring To Default..!"

    property string qmltextBatchSetting: "Batch Setting"
    property bool   clearedOnce: false

    property var qmlTextArray: [qmltextRecipeActions, qmltextRecipeNew, qmltextRecipeSave,
        qmltextRecipeCopy, qmltextRecipeDelete, qmltextQuickEdit, qmltextTime,
        qmltextEnergy, qmltextPeakPower, qmltextAbsoluteDistance, qmltextCollapseDistance,
        qmltextScrubTime, qmltextWeldAmplitude, qmltextHoldTime, qmltextPressure, qmltextFlowRate,
        qmltextForceRampTime, qmltextMaxRecipeCountError,qmltextTriggerForce,qmltextHoldPressure,qmltextEnergyCmp,qmltextRecipeCopyOverrideConfirm,qmltextValidationError]

    property var recipeActionsModel: [qmltextRecipeNew, qmltextRecipeSave, qmltextRecipeCopy, qmltextRecipeDelete]

    property string strRecipeNumber: RecipeLabData.WeldRecipeNumber
    property string strRecipeName: RecipeLabData.WeldRecipeName
    property int imageSize: Math.round(20 * Style.scaleHint)
    property int imageBigSize: Math.round(30 * Style.scaleHint)
    property int currentTabBarIndex: 0
    property int currentWeldMode: RecipeEnum.TIME_IDX
    property bool isOverrideOccurred : false
    property int sourceRecipeNo : RecipeLabData.WeldRecipeNumber
    property int destinationRecipeNo
    signal recipeLabDataChanged()
    signal recipeOverride()

    QtObject
    {
        id: textEnum
        readonly property int textRecipeActionsIdx:                 0
        readonly property int textRecipeNewIdx:                     1
        readonly property int textRecipeSaveIdx:                    2
        readonly property int textRecipeCopyIdx:                    3
        readonly property int textRecipeDeleteIdx:                  4
        readonly property int textQuickEditIdx:                     5
        readonly property int textTimeIdx:                          6
        readonly property int textEnergyIdx:                        7
        readonly property int textPeakPowerIdx:                     8
        readonly property int textAbsoluteDistanceIdx:              9
        readonly property int textCollapseDistanceIdx:              10
        readonly property int textScrubTimeIdx:                     11
        readonly property int textWeldAmplitudeIdx:                 12
        readonly property int textHoldTimeIdx:                      13
        readonly property int textPressureIdx:                      14
        readonly property int textFlowRateIdx:                      15
        readonly property int textForceRampTimeIdx:                 16
        readonly property int textMaxRecipeCountErrorIdx:           17
        readonly property int textTriggerForceIdx:                  18
        readonly property int textHoldPressureIdx:                  19
        readonly property int textEnergyCompIdx:                    20
        readonly property int textRecipeCopyOverrideConfirmIdx:     21
        readonly property int textValidationErrorIdx:               22
    }

    QtObject
    {
        id: enumTabBarIndex
        readonly property int weldModeIdx:      0
        readonly property int weldProcessIdx:   1
        readonly property int parametersA2ZIdx: 2
        readonly property int limitIdx:         3
        readonly property int stackRecipeIdx:   4
        readonly property int pretriggerIdx:    5
        readonly property int afterburstIdx:    6
        readonly property int setupIdx:         7
        readonly property int controlIdx:       8
        readonly property int suspectRejectIdx: 9
        readonly property int batchSettingIdx : 10
        readonly property int enegyCompIdx :    11
    }

    QtObject
    {
        id: enumParamIndex
        readonly property int weldAmplitudeIdx:     10
        readonly property int weldPressureIdx:      11
        readonly property int weldFlowRateIdx:      12
        readonly property int weldHoldTimeIdx:      13
        readonly property int weldTriggerForceIdx:  14
        readonly property int weldHoldPressureIdx:     15

    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES_LAB_SETTING, qmlTextArray)
        qmltextRecipeActions =      qmlTextArray[textEnum.textRecipeActionsIdx]
        qmltextRecipeNew =          qmlTextArray[textEnum.textRecipeNewIdx]
        qmltextRecipeSave =         qmlTextArray[textEnum.textRecipeSaveIdx]
        qmltextRecipeCopy =         qmlTextArray[textEnum.textRecipeCopyIdx]
        qmltextRecipeDelete =       qmlTextArray[textEnum.textRecipeDeleteIdx]
        qmltextQuickEdit =          qmlTextArray[textEnum.textQuickEditIdx]
        qmltextTime =               qmlTextArray[textEnum.textTimeIdx]
        qmltextEnergy =             qmlTextArray[textEnum.textEnergyIdx]
        qmltextPeakPower =          qmlTextArray[textEnum.textPeakPowerIdx]
        qmltextAbsoluteDistance =   qmlTextArray[textEnum.textAbsoluteDistanceIdx]
        qmltextCollapseDistance =   qmlTextArray[textEnum.textCollapseDistanceIdx]
        qmltextScrubTime =          qmlTextArray[textEnum.textScrubTimeIdx]
        qmltextWeldAmplitude =      qmlTextArray[textEnum.textWeldAmplitudeIdx]
        qmltextHoldTime =           qmlTextArray[textEnum.textHoldTimeIdx]
        /*qmltextPressure =           qmlTextArray[textEnum.textPressureIdx]
        qmltextFlowRate =           qmlTextArray[textEnum.textFlowRateIdx]
        qmltextForceRampTime =      qmlTextArray[textEnum.textForceRampTimeIdx]
        qmltextMaxRecipeCountError = qmlTextArray[textEnum.textMaxRecipeCountErrorIdx]*/
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB, qmltextMenuName)
        qmltextWeldProcess = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS, qmltextWeldProcess)
        qmltextWeldMode = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDMODE, qmltextWeldMode)
        qmltextParametersA2Z = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_PARAMETERA2Z, qmltextParametersA2Z)
        qmltextLimit = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS, qmltextLimit)
        qmltextStackRecipe = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_STACKRECIPE, qmltextStackRecipe)
        qmltextPretrigger = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_PRETRIGGER, qmltextPretrigger)
        qmltextAfterburst = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_WELDPROCESS_AFTERBURST, qmltextAfterburst)
        qmltextSetup = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_SETUP, qmltextSetup)
        qmltextControl = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_CONTROL, qmltextControl)
        qmltextSuspectReject = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_SUSPECT_REJECT, qmltextSuspectReject)
        qmltextEnergyCmp = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_LIMITS_ENERGY_COMPENSATION, qmltextEnergyCmp)
        qmltextRecipeSetting = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_SETTING, qmltextRecipeSetting)
        qmltextResultView = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_RESULTVIEW, qmltextResultView)
        qmltextGraphSetting = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_GRAPHSETTING, qmltextGraphSetting)
        qmltextBatchSetting = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES_LAB_BATCH_SETTING, qmltextBatchSetting)
        switch(currentTabBarIndex)
        {
        case enumTabBarIndex.weldModeIdx:
        case enumTabBarIndex.parametersA2ZIdx:
        case enumTabBarIndex.stackRecipeIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextWeldMode)
            recipeTabBarModel.setProperty(1, "Title", qmltextWeldProcess)
            recipeTabBarModel.setProperty(2, "Title", qmltextParametersA2Z)
            recipeTabBarModel.setProperty(3, "Title", qmltextLimit)
            recipeTabBarModel.setProperty(4, "Title", qmltextStackRecipe)
            break
        case enumTabBarIndex.weldProcessIdx:
        case enumTabBarIndex.pretriggerIdx:
        case enumTabBarIndex.afterburstIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextPretrigger)
            recipeTabBarModel.setProperty(1, "Title", qmltextAfterburst)
            break
        case enumTabBarIndex.limitIdx:
        case enumTabBarIndex.setupIdx:
        case enumTabBarIndex.controlIdx:
        case enumTabBarIndex.suspectRejectIdx:
            recipeTabBarModel.setProperty(0, "Title", qmltextSuspectReject)
            recipeTabBarModel.setProperty(1, "Title", qmltextControl)
            if(systemInformationModel.getSystemType() === SystemTypeEnum.GSX_E1)
            {
                recipeTabBarModel.setProperty(2, "Title", qmltextSetup)
            }
            break;
        }
        var strWeldModeTitle = qmltextTime
        switch(currentWeldMode)
        {
        case RecipeEnum.TIME_IDX:
            strWeldModeTitle    = qmltextTime
            break;
        case RecipeEnum.ENERGY_IDX:
            strWeldModeTitle    = qmltextEnergy
            break;
        case RecipeEnum.PEAKPOWER_IDX:
            strWeldModeTitle    = qmltextPeakPower
            break;
        case RecipeEnum.GROUND_IDX:
            strWeldModeTitle    = qmltextScrubTime
            break;
        case RecipeEnum.ABSDISTANCE_IDX:
            strWeldModeTitle    = qmltextAbsoluteDistance
            break;
        case RecipeEnum.COLDISTANCE_IDX:
            strWeldModeTitle    = qmltextCollapseDistance
            break;
        default:
            strWeldModeTitle    = qmltextTime
            break;
        }
    }

    function updateWeldModeTabBar()
    {
        recipeTabBarModel.clear()
        recipeTabBarModel.append({"Title":      qmltextWeldMode,
                                     "Width":      Math.round(90 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.weldModeIdx})
        recipeTabBarModel.append({"Title":      qmltextWeldProcess,
                                     "Width":      Math.round(105 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.weldProcessIdx})
        recipeTabBarModel.append({"Title":      qmltextParametersA2Z,
                                     "Width":      Math.round(120 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.parametersA2ZIdx})
        recipeTabBarModel.append({"Title":      qmltextLimit,
                                     "Width":      Math.round(60 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.limitIdx})
        recipeTabBarModel.append({"Title":      qmltextStackRecipe,
                                     "Width":      Math.round(100 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.stackRecipeIdx})

        if(SystemConfiguration.BatchSettingSupportSystemType === SystemTypeDef.BATCH_CONTROL_SUPPORTED)
        {
            recipeTabBarModel.append({"Title":      qmltextBatchSetting,
                                         "Width":      Math.round(100 * Style.scaleHint),
                                         "Index":      enumTabBarIndex.batchSettingIdx})
        }
    }

    function updateWeldProcessTabBar()
    {
        weldProcessTabBarModel.clear()
        weldProcessTabBarModel.append({"Title":      qmltextPretrigger,
                                          "Width":      Math.round(100 * Style.scaleHint),
                                          "Index":      enumTabBarIndex.pretriggerIdx})
        weldProcessTabBarModel.append({"Title":      qmltextAfterburst,
                                          "Width":      Math.round(100 * Style.scaleHint),
                                          "Index":      enumTabBarIndex.afterburstIdx})
    }

    function updateLimitsTabBar()
    {
        limitsTabBarModel.clear()
        limitsTabBarModel.append({"Title":      qmltextSuspectReject,
                                     "Width":      Math.round(150 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.suspectRejectIdx})
        limitsTabBarModel.append({"Title":      qmltextControl,
                                     "Width":      Math.round(70 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.controlIdx})
        limitsTabBarModel.append({"Title":      qmltextEnergyCmp,
                                     "Width":      Math.round(150 * Style.scaleHint),
                                     "Index":      enumTabBarIndex.enegyCompIdx})
    }

    Connections{
        target:mainWindow
        function onClearSubTabBar()
        {
            subtabBarBackground1.visible =false
            subRecipeDetails.anchors.topMargin =subtabBarBackground1.height/10
        }
    }

    function updateTabBarSetting(index)
    {
        if(index === UIScreenEnum.RECIPES_LAB_WELDPROCESS || index=== UIScreenEnum.RECIPES_LAB_LIMITS )
        {
            mainWindow.clearHeaderTitle(index)
            subRecipeDetails.anchors.topMargin =subtabBarBackground1.height
            subtabBarBackground1.visible =true
        }
        else{
            mainWindow.clearHeaderTitle(index)
            subRecipeDetails.anchors.topMargin =subtabBarBackground1.height/10
            subtabBarBackground1.visible =false
        }
    }

    ListModel {
        id:limitsTabBarModel
    }
    ListModel {
        id:weldProcessTabBarModel
    }

    function updateTabBar(index)
    {
        separator.visible = (index === enumTabBarIndex.weldProcessIdx|| index === enumTabBarIndex.limitIdx || index === enumTabBarIndex.afterburstIdx || index === enumTabBarIndex.pretriggerIdx)?true:false

        subRecipeDetails.source = ""
        currentTabBarIndex = index
        switch(index)
        {
        case enumTabBarIndex.weldModeIdx:
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_WELDMODE)
            updateWeldModeTabBar()
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeModeSetting.qml"
            break;
        case enumTabBarIndex.weldProcessIdx:
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_WELDPROCESS)
            mainWindow.setHeaderTitle(qmltextWeldProcess, UIScreenEnum.RECIPES_LAB_WELDPROCESS)
            subtabtn.model =weldProcessTabBarModel
            updateWeldProcessTabBar()
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipePretriggerSetting.qml"
            break;
        case enumTabBarIndex.parametersA2ZIdx:
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_PARAMETERA2Z)
            mainWindow.setHeaderTitle(qmltextParametersA2Z, UIScreenEnum.RECIPES_LAB_PARAMETERA2Z)
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeParametersAZSetting.qml"
            break;
        case enumTabBarIndex.limitIdx:
            subtabtn.model = limitsTabBarModel
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_LIMITS)
            mainWindow.setHeaderTitle(qmltextLimit, UIScreenEnum.RECIPES_LAB_LIMITS)
            updateLimitsTabBar()
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/RecipeSuspectRejectSetting.qml"
            break;
        case enumTabBarIndex.stackRecipeIdx:
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_STACKRECIPE)
            mainWindow.setHeaderTitle(qmltextStackRecipe, UIScreenEnum.RECIPES_LAB_STACKRECIPE)
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/stackRecipeSetting.qml"
            break;
        case enumTabBarIndex.pretriggerIdx:
            subRecipeDetails.anchors.topMargin =subtabBarBackground1.height
            subtabBarBackground1.visible =true
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipePretriggerSetting.qml"
            break;
        case enumTabBarIndex.afterburstIdx:
            subRecipeDetails.anchors.topMargin =subtabBarBackground1.height
            subtabBarBackground1.visible =true
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeAfterburstSetting.qml"
            break;
        case enumTabBarIndex.setupIdx:
            break;
        case enumTabBarIndex.controlIdx:
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/RecipeControlSetting.qml"
            break;
        case enumTabBarIndex.suspectRejectIdx:
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/RecipeSuspectRejectSetting.qml"
            break;
        case enumTabBarIndex.enegyCompIdx:
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/RecipeLImitsEnergyCompensation.qml"
            break;
        case enumTabBarIndex.batchSettingIdx:
            updateTabBarSetting(UIScreenEnum.RECIPES_LAB_BATCH_SETTING)
            mainWindow.setHeaderTitle(qmltextBatchSetting, UIScreenEnum.RECIPES_LAB_BATCH_SETTING)
            subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeBatchSetting.qml"
            break;
        default:
            break;
        }
    }



    function currentWeldModeIndexChanged(weldModeIndex)
    {

        var strTitle, iDecimals, strUnit, realMinimum, realMaximum, strValue
        currentWeldMode = weldModeIndex
        switch(weldModeIndex)
        {
        case RecipeEnum.TIME_IDX:

            strTitle    = qmltextTime
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.TIME_IDX)
            iDecimals   = 3
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.TIME_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.TIME_IDX)
            strValue    = RecipeLabData.ModeValueTime.toFixed(3)

            RecipeLabData.WeldMode = RecipeEnum.TIME_IDX
            break;

        case RecipeEnum.ENERGY_IDX:

            strTitle    = qmltextEnergy
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.ENERGY_IDX)
            iDecimals   = 1
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.ENERGY_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.ENERGY_IDX)
            strValue    = RecipeLabData.ModeValueEnergy.toFixed(1)

            RecipeLabData.WeldMode = RecipeEnum.ENERGY_IDX
            break;

        case RecipeEnum.PEAKPOWER_IDX:

            strTitle    = qmltextPeakPower
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.PEAKPOWER_IDX)
            iDecimals   = 0
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.PEAKPOWER_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.PEAKPOWER_IDX)
            strValue    = RecipeLabData.ModeValuePeakPower

            RecipeLabData.WeldMode = RecipeEnum.PEAKPOWER_IDX
            break;

        case RecipeEnum.GROUND_IDX:

            strTitle    = qmltextScrubTime
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.GROUND_IDX)
            iDecimals   = 3
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.GROUND_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.GROUND_IDX)
            strValue    = RecipeLabData.ModeValueGroundDetect.toFixed(3)

            RecipeLabData.WeldMode = RecipeEnum.GROUND_IDX
            break;

            /*Below 2 values are reserved for Pro mode which are yet to set*/
        case RecipeEnum.ABSDISTANCE_IDX:

            strTitle    = qmltextAbsoluteDistance
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.ABSDISTANCE_IDX)
            iDecimals   = (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.ABSDISTANCE_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.ABSDISTANCE_IDX)
            strValue    = RecipeLabData.ModeValueAbsDistance

            RecipeLabData.WeldMode = RecipeEnum.ABSDISTANCE_IDX
            break;

        case RecipeEnum.COLDISTANCE_IDX:

            strTitle    = qmltextCollapseDistance
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.COLDISTANCE_IDX)
            iDecimals   = (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.COLDISTANCE_IDX)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.COLDISTANCE_IDX)
            strValue    = RecipeLabData.ModeValueColDistance

            RecipeLabData.WeldMode = RecipeEnum.COLDISTANCE_IDX
            break;

        default:

            strTitle    = qmltextTime
            strUnit     = mainWindow.getWeldModeUnit(RecipeEnum.TIME_IDX)
            iDecimals   = 3
            realMinimum = RecipeLabData.getMinParamValue(RecipeEnum.TIME_ID)
            realMaximum = RecipeLabData.getMaxParamValue(RecipeEnum.TIME_ID)
            strValue    = RecipeLabData.ModeValueTime.toFixed(3)

            RecipeLabData.WeldMode = RecipeEnum.TIME_IDX
            break;
        }

        recipeParameterModel.resetModel()

        recipeParameterModel.setProperty(0, "Title",    strTitle)
        recipeParameterModel.setProperty(0, "Unit",     strUnit)
        recipeParameterModel.setProperty(0, "Decimals", iDecimals)
        recipeParameterModel.setProperty(0, "Minimum",  realMinimum)
        recipeParameterModel.setProperty(0, "Maximum",  realMaximum)
        recipeParameterModel.setProperty(0, "Value",    strValue)

    }

    Connections {
        target: mainWindow
        function onSignalCurrentScreenChanged(index)
        {
            if(index === UIScreenEnum.RECIPES_LAB)
            {
                subRecipeDetails.source = ""
                updateWeldModeTabBar()
                subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeModeSetting.qml"
                //when the recipe mode screen is loaded again, it will set the time model defaultly
                currentWeldModeIndexChanged(RecipeEnum.TIME_IDX)
            }
        }
    }

    Connections {
        target: subRecipeDetails.item
        ignoreUnknownSignals: true
        function onSignalCurrentWeldModeIdxChanged(index)
        {
            currentWeldModeIndexChanged(index)
        }
    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {
        recipeParameterModel.resetModel()
        updateWeldModeTabBar()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.RECIPES_LAB)
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.RECIPES_LAB
    }

    Connections
    {
        target: RecipeLabData

        /*On every change of Recipe Lab Data display should get refresh*/
        function onRecipeLabDataChanged()
        {
            recipeParameterModel.resetModel()
            RecipeLabData.IsLoading = false
        }
    }

    Connections
    {
        target: RecipeModel

        /*Recipe override notification*/
        function onRecipeOverride(getDestinationRecipeNo)
        {
            if (ActiveScreen.CurrentActiveScreen === UIScreenEnum.RECIPES_LAB)
            {
                destinationRecipeNo = getDestinationRecipeNo
                isOverrideOccurred = true
                recipePopup.isMultiButtonPopup = true
                recipePopup.visible = true
                recipePopup.qmltextWarningDialog = qmltextRecipeCopyOverrideConfirm
                mainWindow.opacityFlag = true
            }
        }
    }

    /*To display recipe related popups*/
    BransonPopup
    {
        id: recipePopup

        onOKButtonClicked:

        {
            if(isOverrideOccurred)
            {
                RecipeModel.initiateRecipeCopyRequest(sourceRecipeNo, destinationRecipeNo, true)
                isOverrideOccurred = false
            }

            recipePopup.visible = false
            mainWindow.opacityFlag = false
        }

        onCancelButtonClicked:
        {
            recipePopup.visible = false
            mainWindow.opacityFlag = false
        }
    }

    InputPanel
    {
        id: inputPanel
        z: 1
        height: parent.height
        width: parent.width
        visible: Qt.inputMethod.visible
        anchors.bottom: parent.bottom
    }

    MouseArea
    {
        id: backGroundMa
        anchors.fill: parent
        onClicked:
        {
            inputPanel.visible = false
            recipeNameEditable.focus = false
        }
    }

    Image {
        id: recipeNameBackground
        width: parent.width
        anchors.top: parent.top
        height: Math.round(50 * Style.scaleHint)
        source: "qrc:/Images/informationSecondNav.svg"
        enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

        Text
        {
            id: unsavedAsterisk
            visible: (! RecipeLabData.IsRecipeSaved)
            anchors.right: recipeNum.left
            anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            text: "*"
        }

        Text {
            id: recipeNum
            anchors.left: parent.left
            anchors.leftMargin: 21
            anchors.verticalCenter: parent.verticalCenter
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            text: strRecipeNumber + ":"
        }

        Text
        {
            id: recipeName
            visible: true
            anchors.left: recipeNum.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            color: Style.blackFontColor
            font.family: Style.regular.name
            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
            text: strRecipeName
        }

        Image
        {
            id: recipeNameEditIcon
            visible: true
            anchors.left: recipeName.right
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Edit.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeNameEditIcon.width
            sourceSize.height: recipeNameEditIcon.height
            smooth: true

            MouseArea
            {
                id: recipeEditMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    recipeName.visible = false
                    recipeNameEditIcon.visible = false
                    inputPanel.visible = false
                    recipeNameEditable.focus = false
                }
            }
        }

        BransonLineEdit
        {
            id: recipeNameEditable
            visible: (! recipeNameEditIcon.visible)
            anchors.left: recipeNum.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: strRecipeName
            focus: true
            selectByMouse: true
            mouseSelectionMode: TextInput.SelectWords
            onActiveFocusChanged:
            {
                /*To  avoid use of backspace for user to clear text before maintextfield entry*/
                if(activeFocus)
                {
                    inputPanel.visible = true
                    clearedOnce = true
                    recipeNameEditable.selectAll()
                }

                else
                {
                    inputPanel.visible = false
                    clearedOnce = false
                }
            }

            /*Clear data once only*/
            Keys.onPressed:
            {
                if (clearedOnce)
                {
                    recipeNameEditable.clear()
                    clearedOnce = false
                }
            }
        }

        Image
        {
            id: recipeNameSaveicon
            visible: (! recipeNameEditIcon.visible)
            anchors.left: recipeNameEditable.right
            anchors.leftMargin: Math.round(10 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Save.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeNameEditIcon.width
            sourceSize.height: recipeNameEditIcon.height
            smooth: true

            MouseArea
            {
                id: recipeSaveMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    RecipeLabData.WeldRecipeName = recipeNameEditable.text
                    recipeName.visible = true
                    recipeNameEditIcon.visible = true
                    inputPanel.visible = false
                    recipeNameEditable.focus = false
                }
            }
        }

        Image
        {
            id: createRecipeIcon
            anchors.left: parent.left
            anchors.leftMargin: Math.round(650 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/AddFolder.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: createRecipeIcon.width
            sourceSize.height: createRecipeIcon.height
            smooth: true

            MouseArea
            {
                id: createRecipeIconMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    /*To display alarm message if maximum recipe count reached*/
                    if(UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed || mainWindow.isAuthorityCheckEnable )
                    {
                        if(! RecipeLabData.createNewRecipeRequest())
                        {
                            recipePopup.visible = true
                            recipePopup.qmltextWarningDialog = qmltextMaxRecipeCountError
                            mainWindow.opacityFlag = true
                        }

                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                    else{
                        mainWindow.showBransonPopupForAccessDenied()

                    }
                }
            }
        }

        Image
        {
            id: copyRecipeIcon
            anchors.left: parent.left
            anchors.leftMargin: Math.round(700 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Copy.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: copyRecipeIcon.width
            sourceSize.height: copyRecipeIcon.height
            smooth: true

            MouseArea
            {
                id: copyRecipeIconMa
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed || mainWindow.isAuthorityCheckEnable )
                    {
                        mainWindow.showRecipeCopyNumpad(strRecipeNumber)
                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                    else{
                        mainWindow.showBransonPopupForAccessDenied()
                    }
                }
            }
        }

        Image
        {
            id: saveRecipeIcon
            anchors.left: parent.left
            anchors.leftMargin: Math.round(750 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Save.png"
            height: imageSize
            width: imageSize
            fillMode: Image.PreserveAspectFit
            sourceSize.width: saveRecipeIcon.width
            sourceSize.height: saveRecipeIcon.height
            smooth: true

            ColorOverlay
            {
                anchors.fill: saveRecipeIcon
                source: saveRecipeIcon
                color: (! RecipeLabData.IsRecipeSaved) ? "#000000" : "#9B9E9C"
            }

            MouseArea
            {
                id: saveRecipeIconMa
                enabled: (! RecipeLabData.IsRecipeSaved)
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    if(UserPrivilegeObj.IsSaveCopyCreateRecipeAllowed  || mainWindow.isAuthorityCheckEnable)
                    {
                        RecipeLabData.WeldRecipeName = recipeNameEditable.text
                        RecipeLabData.initiateRecipeSaveRequest()
                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                    else
                    {
                        mainWindow.showBransonPopupForAccessDenied()
                    }
                }
            }
        }
    }

    ListModel
    {
        id: recipeTabBarModel
    }

    Rectangle {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.top: recipeNameBackground.bottom
        height: Math.round(47 * Style.scaleHint)
        width: parent.width
        color: Style.backgroundColor
        TabBar {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(600 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            spacing: 20
            background: Rectangle{
                color: Style.backgroundColor
            }

            Repeater {
                id: tabbtn
                model: recipeTabBarModel
                delegate: BransonTabButton {
                    width: model.Width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked: {
                        updateTabBar(model.Index)
                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                }
            }
        }
        Rectangle
        {
            id: btnResultView
            anchors.top: parent.top
            height: imageBigSize
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: Math.round(126 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            color: Style.backgroundColor
            Row
            {
                anchors.right: parent.right
                height: parent.height
                Text
                {
                    anchors.verticalCenter: imageResultView.verticalCenter
                    color: Style.blueFontColor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    text: qmltextResultView
                    font.bold: true
                }
                Image
                {
                    id: imageResultView
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Images/ViewIcon.svg"
                    height: imageBigSize
                    width: imageBigSize
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: imageResultView.width
                    sourceSize.height: imageResultView.height
                    smooth: true
                }
            }
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked:
                {
                    inputPanel.visible = false
                    recipeNameEditable.focus = false
                    tabBarBackground.visible = false
                    rectQuickEdit.x = Math.round(17 * Style.scaleHint)
                    rectQuickEdit.anchors.top = btnRecipeSettings.bottom
                    rectQuickEdit.anchors.topMargin = Math.round(10 * Style.scaleHint)
                    rectQuickEdit.z = 0;
                    subRecipeDetails.z = 1;
                    btnRecipeSettings.visible = true
                    rectQuickEdit.width = Math.round(230 * Style.scaleHint)
                    subRecipeDetails.anchors.right = recipeLabWindow.right
                    subRecipeDetails.anchors.left = rectQuickEdit.right
                    subRecipeDetails.anchors.rightMargin = Math.round(17 * Style.scaleHint)
                    subRecipeDetails.anchors.top = btnRecipeSettings.bottom
                    subRecipeDetails.anchors.topMargin = 0
                    subRecipeDetails.anchors.topMargin = Math.round(10 * Style.scaleHint)
                    ActiveScreen.CurrentActiveScreen = UIScreenEnum.RECIPES_LAB
                    subRecipeDetails.source = "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeLabResultView.qml"
                }
            }
        }
    }

    Rectangle
    {
        id: btnRecipeSettings
        anchors.top: recipeNameBackground.bottom
        visible: false
        height: imageBigSize
        anchors.left: parent.left
        anchors.leftMargin: Math.round(55 * Style.scaleHint)
        width: Math.round(126 * Style.scaleHint)
        color: Style.backgroundColor
        Row
        {
            anchors.right: parent.right
            height: parent.height
            Image
            {
                id: imageRecipeSettings
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Images/back_arrow_icon.svg"
                height: imageBigSize
                width: imageBigSize
                fillMode: Image.PreserveAspectFit
                sourceSize.width: imageRecipeSettings.width
                sourceSize.height: imageRecipeSettings.height
                smooth: true
            }
            Text
            {
                anchors.verticalCenter: imageRecipeSettings.verticalCenter
                color: Style.blueFontColor
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                text: qmltextRecipeSetting
                font.bold: true
            }
        }
        MouseArea
        {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
            }
        }
    }

    Rectangle{
        id: separator
        anchors.top: tabBarBackground.bottom
        anchors.left: parent.left
        anchors.leftMargin: parent.width *0.02
        anchors.right:  parent.right
        anchors.rightMargin: parent.width *0.02
        width: parent.width *0.90
        height: 1
        color: Style.blackFontColor
        visible: false
    }
    Rectangle {
        id: subtabBarBackground1
        anchors.left: parent.left
        anchors.top: separator.bottom
        width: parent.width
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        visible: false
        TabBar {
            id: subrecipeTabBar
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            width: Math.round(600 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            spacing: 20
            background: Rectangle{
                color: Style.backgroundColor
            }

            Repeater {
                id: subtabtn
                delegate: BransonTabButton {
                    width: model.Width
                    height: parent.height
                    tabbtnText: model.Title
                    onClicked: {
                        updateTabBar(model.Index)
                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                }
            }
        }
    }
    ListModel
    {
        id: recipeParameterModel

        function resetModel()
        {
            recipeParameterModel.clear()

            switch (RecipeLabData.WeldMode)
            {

            case RecipeEnum.TIME_IDX:

                recipeParameterModel.append({"Title"       : qmltextTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.TIME_ID),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.TIME_ID),
                                                "Value"    : RecipeLabData.ModeValueTime.toFixed(3) ,
                                                "Index"    : 0})

                break;

            case RecipeEnum.ENERGY_IDX:

                recipeParameterModel.append({"Title"       : qmltextEnergy,
                                                "Unit"     : mainWindow.qmltextEnergyUnit,
                                                "Decimals" : 1,
                                                "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.ENERGY_IDX),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.ENERGY_IDX),
                                                "Value"    : RecipeLabData.ModeValueEnergy.toFixed(1),
                                                "Index"    : 0})

                break;

            case RecipeEnum.PEAKPOWER_IDX:

                recipeParameterModel.append({"Title"       : qmltextPeakPower,
                                                "Unit"     : mainWindow.qmltextPowerUnit,
                                                "Decimals" : 0,
                                                "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.PEAKPOWER_IDX),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.PEAKPOWER_IDX),
                                                "Value"    : RecipeLabData.ModeValuePeakPower.toString(),
                                                "Index"    : 0})

                break;

            case RecipeEnum.GROUND_IDX:

                recipeParameterModel.append({"Title"       : qmltextScrubTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.GROUND_IDX),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.GROUND_IDX),
                                                "Value"    : RecipeLabData.ModeValueGroundDetect.toFixed(3),
                                                "Index"    : 0})

                break;

            case RecipeEnum.ABSDISTANCE_IDX:
                if(SystemConfiguration.CurrentSystemType == SystemTypeDef.ACTUATOR_ELECTRONIC)
                {

                    recipeParameterModel.append({"Title"       : qmltextAbsoluteDistance,
                                                    "Unit"     : mainWindow.qmltextDistanceUnit,
                                                    "Decimals" : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                    "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.ABSDISTANCE_IDX),
                                                    "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.ABSDISTANCE_IDX),
                                                    "Value"    : (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.ModeValueAbsDistance.toFixed(2) :
                                                                                                             RecipeLabData.ModeValueAbsDistance.toFixed(4),
                                                    "Index"    : 0})
                }

                else
                {
                    recipeParameterModel.append({"Title"       : qmltextTime,
                                                    "Unit"     : mainWindow.qmltextTimeUnit,
                                                    "Decimals" : 3,
                                                    "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.TIME_IDX),
                                                    "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.TIME_IDX),
                                                    "Value"    : RecipeLabData.ModeValueTime.toFixed(3) ,
                                                    "Index"    : 0})

                    // break;
                }

                break;
            case RecipeEnum.COLDISTANCE_IDX:

                if(SystemConfiguration.CurrentSystemType == SystemTypeDef.ACTUATOR_ELECTRONIC)
                {
                    recipeParameterModel.append({"Title"       : qmltextCollapseDistance,
                                                    "Unit"     : mainWindow.qmltextDistanceUnit,
                                                    "Decimals" : (mainWindow.qmltextDistanceUnit === "mm") ? 2 : 4,
                                                    "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.COLDISTANCE_IDX),
                                                    "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.COLDISTANCE_IDX),
                                                    "Value"    : (mainWindow.qmltextDistanceUnit === "mm") ? RecipeLabData.ModeValueColDistance.toFixed(2) :
                                                                                                             RecipeLabData.ModeValueColDistance.toFixed(4),
                                                    "Index"    : 0})
                }

                else
                {
                    recipeParameterModel.append({"Title"       : qmltextTime,
                                                    "Unit"     : mainWindow.qmltextTimeUnit,
                                                    "Decimals" : 3,
                                                    "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.TIME_IDX),
                                                    "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.TIME_IDX),
                                                    "Value"    : RecipeLabData.ModeValueTime.toFixed(3) ,
                                                    "Index"    : 0})

                    //break;
                }


                break;
            default:

                recipeParameterModel.append({"Title"       : qmltextTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(RecipeEnum.TIME_IDX),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(RecipeEnum.TIME_IDX),
                                                "Value"    : RecipeLabData.ModeValueTime.toFixed(3) ,
                                                "Index"    : 0})

                break;
            }

            switch (SystemConfiguration.CurrentSystemType)
            {
            case SystemTypeDef.ACTUATOR_MANUAL:

                recipeParameterModel.append({"Title"       : qmltextWeldAmplitude,
                                                "Unit"     : mainWindow.qmltextAmplitudeUnit,
                                                "Decimals" : 0,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Value"    : RecipeLabData.WeldAmplitude.toString(),
                                                "Index"    : 1})

                recipeParameterModel.append({"Title":       qmltextHoldTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldHoldTimeIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldHoldTimeIdx),
                                                "Value"    : RecipeLabData.HoldTime.toFixed(3),
                                                "Index"    : 2})

                break;

            case SystemTypeDef.ACTUATOR_ELECTRONIC:

                recipeParameterModel.append({"Title"       : qmltextWeldAmplitude,
                                                "Unit"     : mainWindow.qmltextAmplitudeUnit,
                                                "Decimals" : 0,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Value"    : RecipeLabData.WeldAmplitude.toString(),
                                                "Index"    : 1})

                recipeParameterModel.append({"Title"       : qmltextFlowRate,
                                                "Unit"     : mainWindow.qmltextDownSpeedUnit,
                                                "Decimals" : 0,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldFlowRateIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldFlowRateIdx),
                                                "Value"    : RecipeLabData.FlowRate.toFixed(0),
                                                "Index"    : 2})

                recipeParameterModel.append({"Title"       : qmltextTriggerForce,
                                                "Unit"     : mainWindow.qmltextForceUnit,
                                                "Decimals" : (mainWindow.qmltextForceUnit === "N") ? 0 : 1,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldTriggerForceIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldTriggerForceIdx),
                                                "Value"    : (mainWindow.qmltextForceUnit === "N") ? RecipeLabData.TriggerForce.toFixed(0) :
                                                                                                     RecipeLabData.TriggerForce.toFixed(1),
                                                "Index"    : 3})

                recipeParameterModel.append({"Title"       : qmltextPressure,
                                                "Unit"     : mainWindow.qmltextPressureUnit,
                                                "Decimals" : (mainWindow.qmltextPressureUnit === "kPa") ? 0 : 1,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldPressureIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldPressureIdx),
                                                "Value"    : (mainWindow.qmltextPressureUnit === "kPa") ? RecipeLabData.WeldPressure.toFixed(0) :
                                                                                                          RecipeLabData.WeldPressure.toFixed(1),
                                                "Index"    : 4})

                recipeParameterModel.append({"Title"       : qmltextHoldTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldTriggerForceIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldTriggerForceIdx),
                                                "Value"    : RecipeLabData.HoldTime.toFixed(3),
                                                "Index"    : 5})

                recipeParameterModel.append({"Title"       : qmltextHoldPressure,
                                                "Unit"     : mainWindow.qmltextPressureUnit,
                                                "Decimals" : (mainWindow.qmltextPressureUnit === "kPa") ? 0 : 1,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldHoldPressureIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldHoldPressureIdx),
                                                "Value"    : (mainWindow.qmltextPressureUnit === "kPa") ? RecipeLabData.HoldPressure.toFixed(0) :
                                                                                                          RecipeLabData.HoldPressure.toFixed(1),
                                                "Index"    : 6})

                break;

            default:

                recipeParameterModel.append({"Title"       : qmltextWeldAmplitude,
                                                "Unit"     : mainWindow.qmltextAmplitudeUnit,
                                                "Decimals" : 0,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldAmplitudeIdx),
                                                "Value"    : RecipeLabData.WeldAmplitude.toString(),
                                                "Index"    : 1})

                recipeParameterModel.append({"Title":       qmltextHoldTime,
                                                "Unit"     : mainWindow.qmltextTimeUnit,
                                                "Decimals" : 3,
                                                "Minimum"  : RecipeLabData.getMinParamValue(enumParamIndex.weldHoldTimeIdx),
                                                "Maximum"  : RecipeLabData.getMaxParamValue(enumParamIndex.weldHoldTimeIdx),
                                                "Value"    : RecipeLabData.HoldTime.toFixed(3),
                                                "Index"    : 2})

                break;

            }
        }
    }

    Rectangle {
        id: rectQuickEdit
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.top: separator.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 11
        width: Math.round(292 * Style.scaleHint)
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        color: "#ECECEC"


        Rectangle {
            id: rectQuickEditTitle
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: Math.round(28 * Style.scaleHint)
            color: Style.titleBackgroundColor
            Text {
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style2 * Style.scaleHint)
                font.bold: true
                color: Style.whiteFontColor
                text: qmltextQuickEdit
            }
        }

        ListView {
            id: quickEditListView
            width: parent.width
            height: parent.height
            anchors.top: rectQuickEditTitle.bottom
            anchors.topMargin: 11
            anchors.bottom: parent.bottom
            spacing: Math.round(10 * Style.scaleHint)
            model: recipeParameterModel
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { }
            clip: true

            delegate: Item {
                id: quickEditListViewDelegate
                width: quickEditListView.width
                height: (SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL) ? quickEditListView.height/3.5 : quickEditListView.height/5
                anchors.leftMargin: 11
                anchors.rightMargin: 11
                enabled: DisplayModesHMI.DisplayMode == SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
                DropShadow {
                    source: btnRecipeSetting
                    anchors.fill: btnRecipeSetting
                    horizontalOffset: btnRecipeSettingMouseArea.pressed ? 0 : 1
                    verticalOffset: btnRecipeSettingMouseArea.pressed ? 0 : 1
                    color: shadowColor
                    opacity: 0.2
                    radius: 3
                }
                Rectangle {
                    id: btnRecipeSetting
                    anchors.fill: parent
                    border.width: Style.scaleHint === 1.0 ? 1 : 3
                    border.color: Style.activeFrameBorderColor
                    color: Style.frameButtonBackgroundColor
                    Column {
                        anchors.left: parent.left
                        anchors.leftMargin: 17
                        anchors.verticalCenter: parent.verticalCenter

                        Text
                        {
                            wrapMode: Text.NoWrap
                            elide: Text.ElideRight
                            text: model.Title
                            font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                            font.bold: true
                            color: Style.blackFontColor
                        }

                        Text
                        {
                            wrapMode: Text.NoWrap
                            elide: Text.ElideRight
                            text: model.Value + " " + model.Unit
                            font.pixelSize: Math.round(Style.style7 * Style.scaleHint)
                            color: Style.blueFontColor
                        }
                    }
                }

                MouseArea
                {
                    id: btnRecipeSettingMouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:
                    {
                        /*Selection of numpad*/

                        if(model.Title === qmltextWeldAmplitude)
                        {
                            mainWindow.showSteppingAmplitudeNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                        }

                        else if(model.Title === qmltextPressure)
                        {
                            /*As there is no pressure stepping feature for manual actuator*/
                            if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_MANUAL)
                            {
                                mainWindow.showPrimaryNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                            }

                            else
                            {
                                mainWindow.showSteppingPressureNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                            }
                        }

                        else
                        {
                            mainWindow.showPrimaryNumpad(model.Title, model.Unit, model.Decimals, model.Minimum, model.Maximum, model.Value)
                        }

                        inputPanel.visible = false
                        recipeNameEditable.focus = false
                    }
                }
            }
        }
    }

    Loader
    {
        id: subRecipeDetails
        anchors.top: tabBarBackground.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 17
        anchors.bottom: parent.bottom
        anchors.right: rectQuickEdit.left
        source: "qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeModeSetting.qml"
    }

    /*Alam to notify TODO implementation*/
    BransonPopup
    {
        id: warningPopup
        visible: (! RecipeLabData.IsParamValid)
        qmltextWarningDialog: qmltextValidationError

        onVisibleChanged:
        {
            mainWindow.opacityFlag = warningPopup.visible
        }

        onOKButtonClicked:
        {
            warningPopup.visible = false
            inputPanel.visible = false
            recipeNameEditable.focus = false
        }
    }

    Rectangle
    {
        id: loadingPage
        visible: RecipeLabData.IsLoading
        anchors.fill: parent
        opacity: 0.25
        color: Style.opacityEffectColor

        Image
        {
            id: recipeLoadingIcon
            visible: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/Images/Loading.png"
            height: imageSize * 5
            width: imageSize * 5
            fillMode: Image.PreserveAspectFit
            sourceSize.width: recipeLoadingIcon.width
            sourceSize.height: recipeLoadingIcon.height
            smooth: true
        }

        RotationAnimator
        {
            target: recipeLoadingIcon
            from: 0
            to: 360
            duration: 1000
            running: true
        }

        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }
}

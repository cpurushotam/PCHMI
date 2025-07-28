/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    recipeWindows.qml file displays recipe cards data.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 17/07/2023 - Initial version.
***************************************************************************/

import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import Qt5Compat.GraphicalEffects
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import Com.Branson.RecipeEnum 1.0
import "./../Common_Logic"
import "./../Recipe_Screens"
Item
{
    id: recipeCardWindowItem
    readonly property int qmlscreenIndicator:  UIScreenEnum.RECIPES

    property string qmltextMenuName                  : "Recipes"
    property string qmltextTabBarRecipe              : "Recipes"
    property string qmltextTabBarSequence            : "Sequence"
    property string qmltextNewRecipe                 : "New Recipe"
    property string qmltextNewSequence               : "New Sequence"
    property string qmltextActions                   : "Actions"
    property string qmltextProductionRun             : "PRODUCTION RUN"
    property string qmltextEditRecipe                : "EDIT RECIPE"
    property string qmltextEditSequence              : "EDIT SEQUENCE"
    property string qmltextResetCycleCount           : "RESET CYCLE COUNT"
    property string qmltextSetAsActive               : "SET AS ACTIVE"
    property string qmltextCycleCount                : "Cycle Count"
    property string qmltextSequenceCount             : "Sequence Count"
    property string qmltextMaxRecipeCountError       : "Maximum recipe count reached..!"
    property string qmltextRecipeDeleteError         : "Can not delete active recipe..!"
    property string qmltextRecipeDeleteConfirm       : "Are you sure you want to delete the recipe?"
    property string qmltextResetCycleCountConfirm    : "Are you sure you want to reset the cycle count?"
    property string qmltextRecipeCopyOverrideConfirm : "Do you want to override the recipe number ?"
    property string qmltextRecipeVersionInfoTitle    : "Recipe Ver"
    property string qmltextValidation                : "Validation In Progress..."
    property string qmltextRecipeEditFail            : "Recipe Edit Failed..!"
    property string qmltextRecipeActiveFail          : "Active Recipe Failed..!"
    property string qmltextAlert                     : "Alert"


    property bool isDeletePressed
    property bool isResetCycleCountPressed
    property int  recipeNo
    property int  recipeIndex
    property bool isOverrideOccurred : false
    property int  sourceRecipeNo
    property int  destinationRecipeNo
    property bool isUnsavedFlag : false
    property bool isErrorOccurred : false
    property int  selectedRecipeNo
    property int  selectedIndexNo
    property bool isValidated : false
    property int  actionIndexSelected
    property int  imageSize : Math.round(20 * Style.scaleHint)
    property int  attempCounter : 0
    property int  maxAttempCounter : 40

    signal maxRecipeCountReached()
    signal recipeDeleteError()
    signal recipeOverride()

    property var qmlTextArray: [qmltextTabBarRecipe, qmltextTabBarSequence,
                                qmltextNewRecipe, qmltextNewSequence,
                                qmltextActions, qmltextProductionRun, qmltextEditRecipe,
                                qmltextEditSequence, qmltextResetCycleCount, qmltextSetAsActive,
                                qmltextCycleCount, qmltextSequenceCount, qmltextMaxRecipeCountError, qmltextRecipeDeleteError,qmltextRecipeVersionInfoTitle,
                                qmltextRecipeDeleteConfirm, qmltextResetCycleCountConfirm, qmltextRecipeCopyOverrideConfirm,
                                qmltextValidation, qmltextRecipeEditFail, qmltextRecipeActiveFail, qmltextAlert]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.RECIPES, qmlTextArray)
        qmltextTabBarRecipe         = qmlTextArray[textEnum.recipeTabIdx]
        qmltextTabBarSequence       = qmlTextArray[textEnum.sequenceTabIdx]
        qmltextNewRecipe            = qmlTextArray[textEnum.newRecipeIdx]
        qmltextNewSequence          = qmlTextArray[textEnum.newSequenceIdx]
        qmltextActions              = qmlTextArray[textEnum.actionIdx]
        qmltextProductionRun        = qmlTextArray[textEnum.productionRunIdx]
        qmltextEditRecipe           = qmlTextArray[textEnum.editRecipeIdx]
        qmltextEditSequence         = qmlTextArray[textEnum.editSequenceIdx]
        qmltextResetCycleCount      = qmlTextArray[textEnum.resetCycleCountIdx]
        qmltextSetAsActive          = qmlTextArray[textEnum.setAsActiveIdx]
        qmltextCycleCount           = qmlTextArray[textEnum.recipeCycleCountIdx]
        qmltextSequenceCount        = qmlTextArray[textEnum.sequenceCountIdx]
        qmltextMaxRecipeCountError  = qmlTextArray[textEnum.maxRecipeCountErrorIdx]
        qmltextRecipeDeleteError    = qmlTextArray[textEnum.recipeDeleteErrorIdx]
        qmltextRecipeVersionInfoTitle = qmlTextArray[textEnum.recipeVersionInfoTitleIdx]
        qmltextRecipeDeleteConfirm    = qmlTextArray[textEnum.textRecipeDeleteConfirmIdx]
        qmltextResetCycleCountConfirm = qmlTextArray[textEnum.textResetCycleCountConfirmIdx]
        qmltextRecipeCopyOverrideConfirm = qmlTextArray[textEnum.textRecipeCopyOverrideConfirmIdx]
        qmltextValidation           = qmlTextArray[textEnum.validationIdx]
        qmltextRecipeEditFail       = qmlTextArray[textEnum.recipeEditFailIdx]
        qmltextRecipeActiveFail     = qmlTextArray[textEnum.recipeActiveFailIdx]
        qmltextAlert                = qmlTextArray[textEnum.alertIdx]
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.RECIPES, qmltextMenuName)
        recipeTabBar.currentIndex = 0
        recipeActionModel.resetModel()
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted:
    {

        RecipeModel.loadRecipeCards()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.RECIPES)
        /*Active screen update*/
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.RECIPES
    }

    BransonPopup
    {
        id: recipePopup
        onOKButtonClicked:
        {
            if(isDeletePressed)
            {
                RecipeModel.removeRow(recipeNo, recipeIndex)
                isDeletePressed = false
            }

            else if(isResetCycleCountPressed)
            {
                RecipeModel.resetCycleCount(recipeNo, recipeIndex)
                isResetCycleCountPressed = false
            }

            else if(isOverrideOccurred)
            {
                RecipeModel.initiateRecipeCopyRequest(sourceRecipeNo, destinationRecipeNo, true)
                isOverrideOccurred = false
            }

            recipePopup.visible = false

            if(! isErrorOccurred)
            {
                mainWindow.opacityFlag = false
            }
        }

        onCancelButtonClicked:
        {
            recipePopup.visible = false
            mainWindow.opacityFlag = false
        }
    }

    BransonPopup
    {
        id: recipePopup2
        onOKButtonClicked:
        {
            recipePopup2.visible = false
            mainWindow.opacityFlag = false
            isErrorOccurred = false
        }
    }

    Connections
    {
        target: RecipeModel

        /*Alarm message if maximum recipe creation count reached*/
        function onMaxRecipeCountReached()
        {
            if (ActiveScreen.CurrentActiveScreen === UIScreenEnum.RECIPES)
            {
                recipePopup.visible = true
                recipePopup.qmltextWarningDialog = qmltextMaxRecipeCountError
                mainWindow.opacityFlag = true
            }
        }

        /*Alarm message if recipe delete failed*/
        function onRecipeDeleteError()
        {
            recipePopup2.visible = true
            recipePopup2.isMultiButtonPopup = false
            recipePopup2.qmltextWarningDialog = qmltextRecipeDeleteError
            mainWindow.opacityFlag = true
            isErrorOccurred = true
        }

        /*Recipe override notification*/
        function onRecipeOverride(getDestinationRecipeNo)
        {
            if (ActiveScreen.CurrentActiveScreen === UIScreenEnum.RECIPES)
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

    QtObject
    {
        id: textEnum
        readonly property int recipeTabIdx:                         0
        readonly property int sequenceTabIdx:                       1
        readonly property int newRecipeIdx:                         2
        readonly property int newSequenceIdx:                       3
        readonly property int actionIdx:                            4
        readonly property int productionRunIdx:                     5
        readonly property int editRecipeIdx:                        6
        readonly property int editSequenceIdx:                      7
        readonly property int resetCycleCountIdx:                   8
        readonly property int setAsActiveIdx:                       9
        readonly property int recipeCycleCountIdx:                  10
        readonly property int sequenceCountIdx:                     11
        readonly property int maxRecipeCountErrorIdx:               12
        readonly property int recipeDeleteErrorIdx:                 13
        readonly property int recipeVersionInfoTitleIdx:            14
        readonly property int textRecipeDeleteConfirmIdx :          15
        readonly property int textResetCycleCountConfirmIdx :       16
        readonly property int textRecipeCopyOverrideConfirmIdx :    17
        readonly property int validationIdx                       : 18
        readonly property int recipeEditFailIdx                   : 19
        readonly property int recipeActiveFailIdx                 : 20
        readonly property int alertIdx                            : 21
    }

    ListModel
    {
        id: recipeActionModel
        function resetModel()
        {
            recipeActionModel.clear()
            recipeActionModel.append({"ActionName":      qmltextProductionRun,
                                 "ActionIndex":     RecipeEnum.PRODUCTION_RUN_IDX,
                                  "userLevelAccess": true,
                                 })
            recipeActionModel.append({"ActionName":      qmltextEditRecipe,
                                 "ActionIndex":     RecipeEnum.EDIT_IDX,
                                  "userLevelAccess": UserPrivilegeObj.IsEditRecipesAllowed || mainWindow.isAuthorityCheckEnable ,
                                })
            recipeActionModel.append({"ActionName":      qmltextResetCycleCount,
                                 "ActionIndex":     RecipeEnum.RESET_CYCLE_COUNT_IDX,
                                   "userLevelAccess": UserPrivilegeObj.IsResetRecipeCycleCountsAllowed || mainWindow.isAuthorityCheckEnable,

                                })

            recipeActionModel.append({"ActionName":      qmltextSetAsActive,
                                 "ActionIndex":     RecipeEnum.SET_AS_ACTIVE_IDX,
                                  "userLevelAccess": UserPrivilegeObj.IsSetRecipeAsActiveAllowed || mainWindow.isAuthorityCheckEnable,

                                })
        }
    }

    Rectangle
    {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: Math.round(190 * Style.scaleHint)
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar
        {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            spacing: 26
            background: Rectangle
            {
                color: Style.backgroundColor
            }

            BransonTabButton
            {
                id: tabbtnRecipe
                width: Math.round(72 * Style.scaleHint)
                tabbtnText: qmltextTabBarRecipe
            }
        }
    }

    SwipeView
    {
        id: recipeSwipeView
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.top: tabBarBackground.bottom
        anchors.bottom: parent.bottom
        currentIndex: recipeTabBar.currentIndex

        onCurrentIndexChanged:
        {
            recipeTabBar.currentIndex = recipeSwipeView.currentIndex
        }

        //Following is the classical factory design pattern for the recipe and sequence card.
        //The Viewer, Model and Delegate are three full independence components can be instantiated for the different cards regardless of Recipe card or Sequence card.
        Page
        {
            id: recipeGrid
            property alias model: recipeGridView.gridViewModel
            BransonGridView
            {
                id: recipeGridView
                anchors.fill: parent
                gridViewModel: RecipeModel
                gridViewDelegate: recipeDelegate
                gridViewCellHeight: Math.round(parent.height / 1.5)
                gridViewCellWidth: Math.round(parent.width / 5)
            }

            Component
            {
                id: recipeDelegate
                BransonNewCard
                {
                    id: recipeCard
                    width: recipeGridView.gridViewCellWidth - 10
                    height: recipeGridView.gridViewCellHeight - 10
                    actionModel: recipeActionModel
                    strDataModel: recipeDataModel
                    numberAssigned: model.assignedNum
                    nameAssigned:   model.assignedName
                    weldCountTitle: qmltextCycleCount
                    weldCountValue: model.cycleCount
                    isActive:       model.isActive
                    isNewCard:      model.isNewCard
                    qmltextAction:  qmltextActions
                    qmltextNewCard: qmltextNewRecipe
                    recipeVersionTitle : qmltextRecipeVersionInfoTitle
                    recipeVersionInfo : model.versionInfo
                    recipeSaveStatus: model.isSaved

                    ListModel
                    {
                        id: recipeDataModel
                        Component.onCompleted:
                        {
                            if((model.weldModeEnum === RecipeEnum.TIME_IDX) || (model.weldModeEnum === RecipeEnum.GROUND_IDX))
                            {
                                recipeDataModel.append({"TitleNum": mainWindow.getWeldModeText(model.weldModeEnum),
                                                           "TitleDetails": model.weldModeValue.toFixed(3) + mainWindow.getWeldModeUnit(model.weldModeEnum)})
                            }

                            else
                            {
                                recipeDataModel.append({"TitleNum": mainWindow.getWeldModeText(model.weldModeEnum),
                                                           "TitleDetails": model.weldModeValue.toFixed(1) + mainWindow.getWeldModeUnit(model.weldModeEnum)})
                            }
                        }
                    }

                    onSignalActionEvent:
                    {
                        if(((model.isActive) && (DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY)) || (DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                        {
                            switch(actionIndex)
                            {
                            case RecipeEnum.CREATE_NEW_IDX:

                                if(RecipeModel.insertRow(index))
                                {
                                    RecipeLabData.IsLoading = true
                                    mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
                                }

                                actionIndexSelected = RecipeEnum.CREATE_NEW_IDX
                                break;

                            case RecipeEnum.PRODUCTION_RUN_IDX:

                                if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                {
                                    recipePopup.isMultiButtonPopup = false
                                    recipePopup.visible = true
                                    recipePopup.qmltextWarningDialog = "This feature is yet to implement...!"
                                    /*mainWindow.menuParentOptionSelect(UIScreenEnum.PRODUCTION)*/
                                    mainWindow.opacityFlag = true
                                }

                                actionIndexSelected = RecipeEnum.PRODUCTION_RUN_IDX
                                break;

                            case RecipeEnum.EDIT_IDX:

                                if(model.isActive)
                                {
                                    RecipeLabData.IsLoading = false
                                }

                                else
                                {
                                    RecipeLabData.IsLoading = true
                                }

                                /*Validation for recipe operation*/
                                selectedRecipeNo = model.assignedNum
                                selectedIndexNo = index
                                actionIndexSelected = RecipeEnum.EDIT_IDX

                                /*Validation shall be done only if active recipe updated,
                                  not for alredy active recipe*/
                                if(RecipeModel.getActiveRecipeNumber() === selectedRecipeNo)
                                {
                                    RecipeModel.setAsActive(model.assignedNum, index, true)
                                    isValidated = true
                                    mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
                                }

                                else
                                {
                                    RecipeModel.setAsActive(model.assignedNum, index, false)
                                    isValidated = false

                                    loadingPage.visible = true
                                    rotor.running = true
                                    recipeValidationTimer.start()
                                    recipeValidationTimer.repeat = true
                                }
                                break;

                            case RecipeEnum.RESET_CYCLE_COUNT_IDX:

                                if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                {
                                    isResetCycleCountPressed = true
                                    recipeNo = model.assignedNum
                                    recipeIndex = index
                                    recipePopup.isMultiButtonPopup = true
                                    recipePopup.visible = true
                                    recipePopup.qmltextWarningDialog = qmltextResetCycleCountConfirm
                                    mainWindow.opacityFlag = true
                                }

                                actionIndexSelected = RecipeEnum.RESET_CYCLE_COUNT_IDX
                                break;

                            case RecipeEnum.SET_AS_ACTIVE_IDX:

                                /*Validation for recipe operation*/
                                selectedRecipeNo = model.assignedNum
                                selectedIndexNo = index
                                actionIndexSelected = RecipeEnum.SET_AS_ACTIVE_IDX

                                /*Validation shall be done only if active recipe updated,
                                  not for alredy active recipe*/
                                if(RecipeModel.getActiveRecipeNumber() === selectedRecipeNo)
                                {
                                    RecipeModel.setAsActive(model.assignedNum, index, true)
                                    isValidated = true
                                }

                                else
                                {
                                    RecipeModel.setAsActive(model.assignedNum, index, false)
                                    isValidated = false

                                    loadingPage.visible = true
                                    rotor.running = true
                                    recipeValidationTimer.start()
                                    recipeValidationTimer.repeat = true
                                }
                                break;

                            case RecipeEnum.DELETE_IDX:
                                if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                {
                                    isDeletePressed = true
                                    recipeNo = model.assignedNum
                                    recipeIndex = index
                                    recipePopup.isMultiButtonPopup = true
                                    recipePopup.visible = true
                                    recipePopup.qmltextWarningDialog = qmltextRecipeDeleteConfirm
                                    mainWindow.opacityFlag = true
                                }

                                actionIndexSelected = RecipeEnum.DELETE_IDX
                                break;

                            case RecipeEnum.COPY_IDX:
                                if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                {
                                    sourceRecipeNo = model.assignedNum
                                    mainWindow.showRecipeCopyNumpad(model.assignedNum)
                                }

                                actionIndexSelected = RecipeEnum.COPY_IDX
                                break;

                            case RecipeEnum.INFORMATION_IDX:
                                if((DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_FULLY_FUNCTIONAL))
                                {
                                    recipePopup.isMultiButtonPopup = false
                                    recipePopup.visible = true
                                    recipePopup.qmltextWarningDialog = "This feature is yet to implement...!"
                                    mainWindow.opacityFlag = true
                                }

                                actionIndexSelected = RecipeEnum.INFORMATION_IDX
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    /*Page loading indicator*/
    Rectangle
    {
        id: loadingPage
        visible: false
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
            id: rotor
            running: true
            loops: 3
            target: recipeLoadingIcon
            from: 0
            to: 360
            duration: 1000
        }

        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }

    /*Providing activation time where recipe activation process going through crosscheck,
      with maximum waiting period should not exceeds more than 50x40 i.e. 2000 mSec*/
    Timer
    {
        id: recipeValidationTimer
        interval: 50
        repeat: false
        onTriggered:
        {
            /*Recipe creation is successful*/
            if(RecipeModel.getActiveRecipeNumber() === selectedRecipeNo)
            {
                RecipeModel.setAsActive(selectedRecipeNo, selectedIndexNo, true)
                if(actionIndexSelected === RecipeEnum.EDIT_IDX)
                {
                    mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
                }

                isValidated = true
                attempCounter = 0
                loadingPage.visible = false
                recipeValidationTimer.stop()
                recipeValidationTimer.repeat = false
            }

            /*Wait for next cycle check, unless maximum attempt not done*/
            else if(attempCounter != maxAttempCounter)
            {
                attempCounter++
            }

            /*Maximum attempt cycle is reached, to confirm recipe operation got failed!*/
            else
            {
                if(actionIndexSelected === RecipeEnum.EDIT_IDX)
                {
                    mainWindow.showBransonPopup(qmltextRecipeEditFail, qmltextAlert)
                }

                else
                {
                    mainWindow.showBransonPopup(qmltextRecipeActiveFail, qmltextAlert)
                }

                isValidated = false
                attempCounter = 0
                loadingPage.visible = false
                recipeValidationTimer.stop()
                recipeValidationTimer.repeat = false
            }
        }
    }
}
